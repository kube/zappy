var Ressource = require('./Ressource.js');

var Block = function(map, x, y) {
	var self = this;
	var game = map.game;
	var _bots = [];

	this.x = x;
	this.y = y;
	this.map = map;
	this.mesh = null;
	this.position = {
		x: self.x - map.width / 2 + 0.5,
		y: self.y - map.height / 2 + 0.5
	};

	this.ressources = [];
	for (var i = 0; i < 7; i++)
		this.ressources[i] = new Ressource(this, x, y, i);

	this.mesh = new THREE.Mesh(new THREE.BoxGeometry(0.9, 0.005, 0.9), game.materials.block);
	this.mesh.position.set(this.position.x, 0, this.position.y);
	this.mesh.updateMatrix();
	this.mesh.matrixAutoUpdate = false;

	this.mesh.onClick = function(e, pick) {
	}
	this.mesh.onMouseOver = function(e, pick) {
		self.mesh.material = game.materials.blockSelected;
		for (var i in self.ressources)
			$('#infoBar .t' + i).text(self.ressources[i].quantity);
	}
	this.mesh.onMouseOut = function(e, pick) {
		self.mesh.material = game.materials.block;
		$('#infoBar a').text('');
	}
	game.scene.add(this.mesh);

	this.addBot = function(bot) {
		_bots.push(bot);
		bot.block = self;
	}

	this.removeBot = function(bot) {
		var index = _bots.indexOf(bot);
		if (index > -1) {
			_bots.slice(index, 1);
			bot.block = null;
		}
	}

	this.getBots = function() {
		return _bots;
	}

	this.displayRessource = function(type) {
		self.ressources[type].display();
	}

	this.hideRessource = function(type) {
		self.ressources[type].hide();
	}
}

module.exports = Block;
