class Trantorien
  MAX_LEVEL: 8

  constructor: (@team) ->
    @level = 1
    @inventory = false
    @around = false
    @path = []
    @elevation = []
    @elevation_failed = false
    @queries = 0

  seek_place: ->
    needed = this.needed_res()
    i = 0
    while i < @around.length
      for element in @around[i]
        if element is 'nourriture'
          @to_take = 'nourriture'
          return i
        if @inventory[element] < needed[element]
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
      if key isnt 'nb_players' and @inventory[key] < val then return -1
    if this.get_players_around() < needed['nb_players'] then return 0
    return 1

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
    required_level = parseInt(text)
    if required_level isnt @level then return
    switch k
      when 1 then @path = ['avance']
      when 2 then @path = ['avance', 'gauche', 'avance']
      when 3 then @path = ['gauche', 'avance']
      when 4 then @path = ['gauche', 'avance', 'gauche', 'avance']
      when 5 then @path = ['gauche', 'gauche', 'avance']
      when 6 then @path = ['droite', 'avance', 'droite', 'avance']
      when 7 then @path = ['droite', 'avance']
      when 8 then @path = ['avance', 'droite', 'avance']

  live: ->
    if ++@queries % 10 is 0 then return "connect_nbr"
    if @path.length > 0 then return this.next_move()
    if @elevation.length > 0 then return this.next_action()
    if not @around then return "voir"
    if @level isnt @MAX_LEVEL
      if @elevation_failed
        @elevation_failed = false
        @elevation = ['incantation']
        return "broadcast #{@level}"
      if not @inventory then return "inventaire"
      if this.will_try_to_fork() then return "fork"
      switch this.can_elevate()
        when 1
          this.prepare_elevation()
          return this.next_action()
        when 0
          return "broadcast #{@level}"
    i = this.seek_place()
    if i isnt -1
      if i is 0 then return "prend #{@to_take}"
      this.init_path i
      return this.next_move()
    @around = false
    return "avance"

module.exports = Trantorien
