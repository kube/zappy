var Ressource = function(block, x, y, type) {
	var self = this;
	var game = block.map.game;

	this.visible = true;
	this.quantity = 0;
	this.position = {
		x: block.position.x + Math.cos(type / 7 * Math.PI * 2) / 3,
		y: block.position.y + Math.sin(type / 7 * Math.PI * 2) / 3
	};

	this.mesh = new THREE.Mesh(new THREE.BoxGeometry(0.04, 1.0, 0.04), game.materials.ressources[type]);
	this.mesh.position.set(this.position.x, 0, this.position.y);
	this.mesh.scale.y = 0;
	this.mesh.position.y = 0;
	game.scene.add(this.mesh);

	function refresh() {

		// Animation
		var tweenUp = new TWEEN.Tween({
			scale: self.mesh.scale.y,
			position: self.mesh.position.y
		})
		.to({
			scale: self.visible ? self.quantity / 5 : 0,
			position: self.visible ? self.quantity / 10 : 0
		}, 1300 / game.time)
		.easing(TWEEN.Easing.Cubic.InOut)
		.onUpdate(function() {

			self.mesh.scale.y = this.scale;
			self.mesh.position.y = this.position;

			// Hide mesh if quantity is null
			if (self.quantity > 0)
				self.mesh.visible = true;
			else
				self.mesh.visible = false;
			self.mesh.updateMatrix();
		}).start();
	}

	this.update = function(quantity) {
		self.quantity = quantity;
		refresh();
	}

	this.add = function(quantity) {
		self.quantity += quantity;
		refresh();
	}

	this.remove = function(quantity) {
		self.quantity -= quantity;
		refresh();
	}

	this.display = function() {
		self.visible = true;
		refresh();
	}

	this.hide = function() {
		self.visible = false;
		refresh();
	}

	refresh();
}

module.exports = Ressource;
