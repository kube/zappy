var teamColors = [
	0xcf2500,
	0xcf9700,
	0x9fcf00,
	0x3fcf00,
	0x00cf84,
	0x008bcf,
	0x0e00cf,
	0x7400cf,
	0xcf0094
];

var Team = function(game, name) {
	var self = this;

	this.name = name;
	var _bots = [];

	this.material = new THREE.MeshBasicMaterial({
			color: teamColors[game.teams.length]
		});

	this.addBot = function(bot) {

		console.log('Bot is joining ' + self.name);

		_bots.push(bot);
		bot.team = self;
	}

	this.removeBot = function(bot) {
		_bots.slice(_bots.indexOf(bot), 1);
	}

	this.getBots = function() {
		return _bots;
	}
}

module.exports = Team;
