var ResponseParser = function(client, game) {
	var self = this;
	var queue = [];

	this.push = function(response) {
		// console.log('Push')

		if (!queue.length)
			var play = true;
		var args = response.split(' ');
		queue.push(args);

		if (play)
			self.next();
	}

	this.next = function() {
		var first = queue[0];
		if (first) {
			queue.shift();
			parse(first);
		}
	}

	function parse(a) {

		a.i = function(i) {
			return parseInt(this[i]);
		}

		switch (a[0]) {

			/*
			**	Identification
			*/
			case 'BIENVENUE':
				client.write('GRAPHIC\n');
				break;

			/*
			**	Map Size
			**	msz X Y
			*/
			case 'msz':
				game.createMap(a.i(1), a.i(2));
				game.run();
				// Set game global for debugging
				global.game = game;
				break;

			/*
			**	Block Content
			**	bct X Y q q q q q q q
			*/
			case 'bct':
				for (var i = 3; i < 10; i++) {
					game.map.blocks[a.i(1)][a.i(2)].ressources[i - 3].update(a.i(i));
				}
				break;

			/*
			**	New Team
			**	tna N
			*/
			case 'tna':
				game.createTeam(a[1]);
				break;

			/*
			**	New Player
			**	pnw #n X Y O L N
			*/
			case 'pnw':
				var player = parseInt(a[1].replace('#', ''));

				if (game.bots[player])
					game.bots[player].upgrade();
				else
					game.createBot(player, a.i(2), a.i(3), a.i(4), a[5], a[6]);

				// Ask server current player's inventory
				client.write('pin ' + a[1] + '\n');
				break;

			/*
			**	Player Position
			**	ppo #n X Y O
			*/
			case 'ppo':
				var playerNumber = parseInt(a[1].replace('#', '')),
					player = game.bots[playerNumber];
				if (player) {	
					game.map.blocks[player.x][player.y].removeBot(player);
					player.setPosition(a.i(2), a.i(3), a.i(4));
				}
				break;

			/*
			**	Player level
			**	plv #n L
			*/
			case 'plv':
				var player = parseInt(a[1].replace('#', ''));
				game.bots[player].elevate(a[2]);
				break;

			/*
			**	Player Inventory
			**	pin #n X Y q q q q q q q
			*/
			case 'pin':
				var playerNumber = parseInt(a[1].replace('#', '')),
					player = game.bots[playerNumber];
				player.setInventory([a.i(4), a.i(5), a.i(6), a.i(7), a.i(8), a.i(9), a.i(10)]);
				break;
				
			/*
			**	Player Expulses
			**	pex #n
			*/
			case 'pex':
				var playerNumber = parseInt(a[1].replace('#', '')),
					player = game.bots[playerNumber],
					bots = game.map.blocks[player.x][player.y].getBots();

				for (var i in bots) {
					console.log(i)
					if (bots[i] != player)
						bots[i].jump(0.3, 1);
				}
				break;

			/*
			**	Player Broadcasts
			**	pbc #n M
			*/
			case 'pbc':

				break;

			/*
			**	Player starts Incantation
			**	pic X Y L #n #n ...
			*/
			case 'pic':
				var players = game.map.blocks[a.i(1)][a.i(2)].getBots();
				for (var i in players)
					players[i].startElevation();
				break;

			/*
			**	Player ends Incantation
			**	pie X Y R
			*/
			case 'pie':
				var players = game.map.blocks[a.i(1)][a.i(2)].getBots();
				for (var i in players)
					players[i].finishElevation();
				break;

			/*
			**	Player lays an Egg
			**	pfk #n
			*/
			case 'pfk':
				break;

			/*
			**	Player drops a Ressource
			**	pdr #n i
			*/
			case 'pdr':
				// Ask server current player's inventory
				client.write('pin ' + a[1] + '\n');
				break;

			/*
			**	Player gets a Ressource
			**	pgt #n i
			*/
			case 'pgt':
				// Ask server current player's inventory
				client.write('pin ' + a[1] + '\n');
				break;

			/*
			**	Bot dies
			**	pdi #n
			*/
			case 'pdi':
				var player = parseInt(a[1].replace('#', ''));
				game.bots[player].die();
				break;

			/*
			**	New Egg
			**	enw #e #n X Y
			*/
			case 'enw':
				var egg = parseInt(a[1].replace('#', ''));
				var player = parseInt(a[2].replace('#', ''));

				var team = game.bots[player].team;
				game.createBot(egg, a.i(3), a.i(4), 1, 0, team.name);
				break;

			/*
			**	Egg hatches
			**	eht #e
			*/
			case 'eht':
				var player = parseInt(a[1].replace('#', ''));
				game.bots[player].jump(0.2, 2);
				break;

			/*
			**	A Player connects to the Egg
			**	ebo #e
			*/
			case 'ebo':
				var player = parseInt(a[1].replace('#', ''));
				game.bots[player].jump(0.3, 1);
				break;

			/*
			**	Egg dies
			**	edi #e
			*/
			case 'edi':
				var egg = parseInt(a[1].replace('#', ''));
				game.bots[egg].die();
				break;

			/*
			**	Get Server Time
			**	sgt T
			*/
			case 'sgt':
				game.time = a.i(1);
				console.log('Time: ' + game.time);
				break;

			/*
			**	End of game (Given team wins game)
			**	seg N
			*/
			case 'seg':
				game.getTeamByName(a[1]).win();

			/*
			**	Message from Server
			**	smg M
			*/
			case 'smg':
				var regex = /^smg /,
					message = a.replace(regex, '');
				console.log(message);
				break;

			/*
			**	Unknown command
			*/
			case 'suc':
				console.error('Unknown command sent to server');
				break;

			/*
			**	Wrong command parameters
			*/
			case 'sbp':
				console.error('Wrong command parameters sent to server');
				break;
		}
		self.next();
	}
};

module.exports = ResponseParser;
