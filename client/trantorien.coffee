class Trantorien
  MAX_LEVEL: 8
  FOOD_THRESHOLD: 4
  MISSING_RESOURCES: -1
  MISSING_PLAYERS: 0
  OK: 1

  constructor: (@team) ->
    @level = 1
    @inventory = false
    @around = false
    @path = []
    @elevation = []
    @elevation_failed = false
    @connect_watcher = 0
    @locked = false
    @dead = false

  seek_place: ->
    needed = this.needed_res()
    i = 0
    while i < @around.length
      for element in @around[i]
        if element is 'nourriture'
          @to_take = 'nourriture'
          return i
        if @level isnt @MAX_LEVEL and @inventory[element] < needed[element]
          @to_take = element
          return i
      i++
    return -1

  get_players_around: ->
    nb_players = 0
    for element in @around[0]
      if element is 'joueur' then nb_players++
    return nb_players

  can_elevate: ->
    needed = this.needed_res()
    for key, val of needed
      if key isnt 'nb_players' and @inventory[key] < val then return @MISSING_RESOURCES
    if this.get_players_around() < needed['nb_players'] then return @MISSING_PLAYERS
    return @OK

  prepare_elevation: ->
    @elevation = []
    needed = this.needed_res()
    for key, val of needed
      if key isnt 'nb_players' and val > 0
        for i in [1..val]
          @elevation.push "pose #{key}"
    @elevation.push 'incantation'

  needed_res: ->
    switch @level
      when 1 then return {
        nb_players: 1
        linemate: 1,
        deraumere: 0,
        sibur: 0,
        mendiane: 0,
        phiras: 0,
        thystame: 0
      }
      when 2 then return {
        nb_players: 2
        linemate: 1,
        deraumere: 1,
        sibur: 1,
        mendiane: 0,
        phiras: 0,
        thystame: 0
      }
      when 3 then return {
        nb_players: 2
        linemate: 2,
        deraumere: 0,
        sibur: 1,
        mendiane: 0,
        phiras: 2,
        thystame: 0
      }
      when 4 then return {
        nb_players: 4
        linemate: 1,
        deraumere: 1,
        sibur: 2,
        mendiane: 0,
        phiras: 1,
        thystame: 0
      }
      when 5 then return {
        nb_players: 4
        linemate: 1,
        deraumere: 2,
        sibur: 1,
        mendiane: 3,
        phiras: 0,
        thystame: 0
      }
      when 6 then return {
        nb_players: 6
        linemate: 1,
        deraumere: 2,
        sibur: 3,
        mendiane: 0,
        phiras: 1,
        thystame: 0
      }
      when 7 then return {
        nb_players: 6
        linemate: 2,
        deraumere: 2,
        sibur: 2,
        mendiane: 2,
        phiras: 2,
        thystame: 1
      }
      else
        return false

  get_vision: ->
    vision = []
    first = 1
    last = 3
    i = 0
    while i < @level
      line = []
      for k in [first..last]
        line.push k
      vision.push line
      first = last + 1
      last = first + line.length + 1
      i++
    return vision

  init_path: (index) ->
    @path = ['avance']
    cur_index = 2
    cur_line = 0
    turned = false
    vision = this.get_vision()
    if not vision? then return
    while cur_index isnt index
      if index not in vision[cur_line]
        @path.push 'avance'
        cur_line++
        cur_index = vision[cur_line][Math.floor(vision[cur_line].length / 2)]
      else
        if index < cur_index
          if not turned then @path.push 'gauche'
          cur_index--
        else
          if not turned then @path.push 'droite'
          cur_index++
        turned = true
        @path.push 'avance'

  next_move: ->
    if @path.length is 1
      @around = false
    return @path.shift()

  next_action: ->
    if @elevation.length is 1
      @inventory = false
    return @elevation.shift()

  will_try_to_fork: ->
    if Math.floor(Math.random() * 10) is 1
      return true
    return false

  recv_message: (k, text) ->
    if @locked then return
    if @path.length > 0 and k isnt 0 then return
    required_level = parseInt(text)
    if required_level isnt @level then return
    switch k
      when 0
        @path = []
        @locked = true
      when 1 then @path = ['avance']
      when 2 then @path = ['avance', 'gauche', 'avance']
      when 3 then @path = ['gauche', 'avance']
      when 4 then @path = ['gauche', 'avance', 'gauche', 'avance']
      when 5 then @path = ['gauche', 'gauche', 'avance']
      when 6 then @path = ['droite', 'avance', 'droite', 'avance']
      when 7 then @path = ['droite', 'avance']
      when 8 then @path = ['avance', 'droite', 'avance']

  get_random_move: ->
    n = Math.floor(Math.random() * 5)
    switch n
      when 0 then return 'gauche'
      when 1 then return 'droite'
    return 'avance'

  elevation_did_fail: ->
    @elevation_failed = false
    @elevation = ['incantation']
    return "broadcast #{@level}"

  reset_state: ->
    @around = false
    @inventory = false
    @locked = false

  live: ->
    if not @inventory then return 'inventaire'
    if @inventory['nourriture'] < @FOOD_THRESHOLD then @locked = false
    if @connect_watcher++ % 10 is 0 or @locked
      @inventory = false
      return 'connect_nbr'
    if @path.length > 0 then return this.next_move()
    if @elevation.length > 0 then return this.next_action()
    if not @around then return 'voir'
    if @level isnt @MAX_LEVEL and @inventory['nourriture'] >= @FOOD_THRESHOLD
      if @elevation_failed then return this.elevation_did_fail()
      switch this.can_elevate()
        when @MISSING_PLAYERS
          @around = false
          @inventory = false
          if this.will_try_to_fork() then return 'fork'
          return "broadcast #{@level}"
        when @OK
          this.prepare_elevation()
          return this.next_action()
    i = this.seek_place()
    if i isnt -1
      if i is 0 then return "prend #{@to_take}"
      this.init_path i
      return this.next_move()
    @around = false
    return this.get_random_move()

module.exports = Trantorien
