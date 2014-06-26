var Block = require('./Block.js');

var Map = function(game, width, height) {
	var self = this;

	if (height <= 0 || width <= 0)
		throw new Error("Invalid Map size");

	this.width = width;
	this.height = height;
	this.blocks = [];
	this.game = game;

	function initBlocks() {

		for (var i = 0; i < width; i++) {
			self.blocks[i] = [];
			for (var j = 0; j < height; j++)
				self.blocks[i][j] = new Block(self, i, j);
		}
	}
	initBlocks();

	this.switchRessource = function(type) {

		if ($('#infoBar .t' + type).parent().hasClass('checked'))
			self.displayRessource(type);
		else
			self.hideRessource(type);
	}

	this.displayRessource = function(type) {

		// Display Ressource in each block
		for (var i in self.blocks)
			for (var j in self.blocks[i])
				self.blocks[i][j].displayRessource(type);

		// Remove class checked to Button
		$('#infoBar .t' + type).parent().removeClass('checked');
	}

	this.hideRessource = function(type) {

		// Hide Ressource in each block
		for (var i in self.blocks)
			for (var j in self.blocks[i])
				self.blocks[i][j].hideRessource(type);

		// Add class checked to Button
		$('#infoBar .t' + type).parent().addClass('checked');
	}
}

module.exports = Map;
