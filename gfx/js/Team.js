var teamColors = [
	0x3e3dff,
	0x61d33c,
	0xdea200,
	0x008bd0,
	0xe34934,
	0x00ea95,
	0x8e22ee,
	0xbbe546,
	0xe13bb5
];

var Team = function(game, name) {
	var self = this;

	this.name = name;
	var _bots = [];

	this.material = new THREE.MeshBasicMaterial({
			color: teamColors[game.teams.length]
		});

	this.addBot = function(bot) {
		_bots.push(bot);
		bot.team = self;
	}

	this.removeBot = function(bot) {
		_bots.slice(_bots.indexOf(bot), 1);
	}

	this.getBots = function() {
		return _bots;
	}

	this.win = function() {
		// DO THE STUFF WHEN TEAM WINS
		// - MAKE BOTS JUMP
		// - BLOCK SOCKET PARSING
		// - DISPLAY '#WINNER TEAM' TEXT
	}
}

module.exports = Team;
