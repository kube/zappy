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

		// console.log(a)

		switch (a[0]) {

			case 'BIENVENUE':
				client.write('GRAPHIC\n');
				break;

			case 'msz':
				game.createMap(a.i(1), a.i(2));
				game.run();
				break;

			case 'bct':
				for (var i = 3; i < 10; i++) {
					game.map.blocks[a.i(1)][a.i(2)].ressources[i - 3].update(a.i(i));
				}
				break;

			case 'pnw':
				var player = parseInt(a[1].replace('#', ''));
				game.createBot(player, a.i(2), a.i(3), a.i(3), a.i(4), a[5]);
				break;

			case 'ppo':
				var player = parseInt(a[1].replace('#', ''));
				if (game.bots[player])
					console.log(game.bots[player])
				game.bots[player].setPosition(a.i(2), a.i(3), a.i(4));
				break;

			case 'pdi':
				var player = parseInt(a[1].replace('#', ''));
				game.bots[player].die();
				console.log('Player ' + player + ' is dead');
				break;

		}
		self.next();
	}
};

module.exports = ResponseParser;
