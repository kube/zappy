net = require 'net'
cp = require 'child_process'
keypress = require 'keypress'
Trantorien = require './trantorien'

usage = ->
  console.log 'Usage: ./client -n <team> -p <port> [-h <hostname>]\n' +
    '\t-n nom d\'equipe\n' +
    '\t-p port\n' +
    '\t-h nom de la machine par defaut c\'est le localhost\n' +
    '\t-k utilisation du clavier'
  process.exit 1

args = process.argv.slice(2)
i = 0
while i < args.length
  switch args[i]
    when "-n" then team = args[++i]
    when "-p" then port = args[++i]
    when "-h" then host = args[++i]
    when "-k" then use_keyboard = true
  i++

if not team? or not port? then usage()

tr = new Trantorien team
handshake = 0
last_cmd = null

client = net.connect {host: host, port: port}, ->
  console.log 'client connected'

client.on 'error', (err) ->
  console.log 'error:', err.message
  if use_keyboard? then process.stdin.pause()
  process.exit 1

client.on 'end', ->
  console.log 'client disconnected'
  if use_keyboard? then process.stdin.pause()
  process.exit

if use_keyboard?
  binding_help = ->
    console.log 'key bindings:\n' +
      '[up] avance, [left] gauche, [right] droite\n' +
      '[v]oir, [i]nventaire\n' +
      'resources:\n' +
      '\to [n]ourriture\n' +
      '\to [l]inemate\n' +
      '\to [d]eraumere\n' +
      '\to [s]ibur\n' +
      '\to [m]endiane\n' +
      '\to [p]hiras\n' +
      '\to [t]hystame\n' +
      '[ctrl] prend {resource}, [shift] pose {resource}\n' +
      '[e]xpulse, [pageup] incantation, [f]ork, [c]onnect_nbr\n'

  get_resource_name = (short) ->
    switch short
      when 'n' then return 'nourriture'
      when 'l' then return 'linemate'
      when 'd' then return 'deraumere'
      when 's' then return 'sibur'
      when 'm' then return 'mendiane'
      when 'p' then return 'phiras'
      when 't' then return 'thystame'
    return false

  binding_help()
  keypress process.stdin
  process.stdin.on 'keypress', (ch, key) ->
    if not key then return
    if key.ctrl and key.name is 'c'
      process.stdin.pause()
      client.end()
    else if key.name is 'up' then send_cmd 'avance'
    else if key.name is 'left' then send_cmd 'gauche'
    else if key.name is 'right' then send_cmd 'droite'
    else if key.name is 'v' then send_cmd 'voir'
    else if key.name is 'i' then send_cmd 'inventaire'
    else if key.ctrl
      res = get_resource_name key.name
      if res then send_cmd "prend #{res}"
    else if key.shift
      res = get_resource_name key.name
      if res then send_cmd "pose #{res}"
    else if key.name is 'return' then send_cmd 'prend mendiane'
    else if key.name is 'e' then console.log 'expulse is not supported'
    else if key.name is 'b' then send_cmd "broadcast #{tr.level}"
    else if key.name is 'pageup' then send_cmd 'incantation'
    else if key.name is 'f' then send_cmd 'fork'
    else if key.name is 'c' then send_cmd 'connect_nbr'
  process.stdin.setRawMode true
  process.stdin.resume()

fork_player = ->
  if use_keyboard? then return
  args = ['-n', team, '-p', port]
  if host? then args = args.concat ['-h', host]
  child = cp.fork './client', args
  child.disconnect()
  child.on 'exit', (code) ->
    console.log 'child exited'

send = (msg) ->
  client.write msg + '\n'

send_cmd = (cmd) ->
  last_cmd = cmd
  send cmd

welcome = ->
  handshake = 1
  send tr.team

die = ->
  console.log 'dead'
  tr.dead = true
  # client.end()
  # process.exit

voir = (msg) ->
  tr.around = []
  squares = msg.substring(1, msg.length - 1).split ','
  for sq in squares
    tr.around.push sq.trim().split(' ')

inventaire = (msg) ->
  tr.inventory = []
  items = msg.substring(1, msg.length - 1).split ','
  for it in items
    sp = it.trim().split(' ')
    tr.inventory[sp[0]] = parseInt sp[1]

prend = (msg) ->
  tr.inventory = false
  tr.around = false

incantation = (msg) ->
  if msg is 'ko'
    tr.elevation_failed = true
  tr.reset_state()

connect_nbr = (msg) ->
  if isNaN msg
    return false
  n = parseInt(msg)
  if n? and n > 0 then fork_player()
  return true

world_size = (msg) ->
  params = msg.split(' ')
  if params.length isnt 2
    return false
  tr.world_x = params[0]
  tr.world_y = params[1]
  return true

handle_response = (msg) ->
  if not last_cmd? then return
  console.log "(#{process.pid}) #{last_cmd}: #{msg}"
  if msg.search("elevation en cours") isnt -1
    tr.reset_state()
    if last_cmd? and last_cmd is 'incantation' then last_cmd = null
  else if msg.search("niveau actuel :") isnt -1
    i = msg.indexOf(':') + 1
    s = msg.substring i
    tr.level = parseInt s
    tr.reset_state()
    if last_cmd? and last_cmd is 'incantation' then last_cmd = null
  else if msg.search("deplacement ") isnt -1 then tr.reset_state()
  else
    cmd_name = last_cmd.split(' ')[0]
    switch cmd_name
      when "voir" then voir msg
      when "inventaire" then inventaire msg
      when "prend" then prend msg
      when "incantation" then incantation msg
      when "connect_nbr" then connect_nbr msg
    last_cmd = null

handle_message = (msg) ->
  console.log msg
  i = msg.indexOf(' ') + 1
  s = msg.substring i
  args = s.split ','
  if not args? or args.length isnt 2 then return
  tr.recv_message(parseInt(args[0]), args[1])

client.on 'data', (data) ->
  msgq = data.toString().split('\n')
  msgq.pop()
  for m in msgq
    process_msg m

process_msg = (msg) ->
  switch msg
    when "BIENVENUE" then welcome()
    when "mort" then die()
    else
      if handshake is 1
        if connect_nbr(msg) is true then handshake = 2
      else if handshake is 2
        if world_size(msg) is true
          handshake = 3
          if not use_keyboard? and not tr.dead then send_cmd tr.live()
      else if handshake >= 3
        if msg.search("message") is 0
          handle_message msg
        else
          handle_response msg
          if not last_cmd? and not use_keyboard? and not tr.dead then send_cmd tr.live()
