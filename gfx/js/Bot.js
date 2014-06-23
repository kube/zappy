var Bot = function(game, number, x, y, orientation, level, team) {
	var self = this;

	this.name = number;
	this.x;
	this.y;
	this.orientation = orientation;
	this.level = level;
	this.team = team;

	console.log('Creating BOT');

	var block = game.map.blocks[x][y];

	// console.log(block)

	this.position = {
		x: block.position.x,
		y: block.position.y
	};

	this.setPosition = function(x, y, o) {

		self.x = x;
		self.y = y;
		block = game.map.blocks[x][y];

		// Check Mesh Rotation before animating it
		if (o == 4 && self.orientation == 1)
			self.mesh.rotation.y = -Math.PI / 2 * 6;
		else if (o == 1 && self.orientation == 4)
			self.mesh.rotation.y = -Math.PI / 2;
		self.orientation = o;

		// Animate Mesh Move
		var	newRotation = - (Math.PI / 2 * (1 + o));
		var tween = new TWEEN.Tween({
				x: self.position.x,
				y: self.position.y,
				a: self.mesh.rotation.y,
			})
			.to({
				x: block.position.x,
				y: block.position.y,
				a: newRotation
			}, 400)
			.easing(TWEEN.Easing.Cubic.InOut)
			.onUpdate(function () {
				self.mesh.position.set(this.x, 0.025, this.y);
				self.mesh.rotation.set(0, this.a, 0);
			})
			.start();

		// Update Self Position
		self.position = {
			x: block.position.x,
			y: block.position.y
		};

		// Mesh position update
		// self.mesh.position.set(block.position.x, 0.05, block.position.y);
		self.mesh.updateMatrix();
	}

	this.die = function() {
		game.scene.remove(self.mesh);
		self.mesh = new THREE.Mesh(game.RIPGeometry,
			game.materials.characters[2]);

		self.mesh.scale.x = 0.05;
		self.mesh.scale.y = 0.05;
		self.mesh.scale.z = 0.05;

		self.setPosition(self.x, self.y, self.orientation);

		game.scene.add(self.mesh);
	}

	function createMesh() {

		self.mesh = new THREE.Mesh(game.stickmanGeometry,
			game.materials.characters[2]);

		self.mesh.scale.x = 0.05;
		self.mesh.scale.y = 0.05;
		self.mesh.scale.z = 0.05;

		// Set Mesh position
		self.setPosition(x, y, orientation);
		// self.mesh.position.set(block.position.x, 0.025, block.position.y);
		// self.mesh.rotation.set(0, - (Math.PI / 2 * (1 + orientation)), 0);

		self.mesh.onclick = function(e, pick) {
			// var pickedMesh = pick.pickedMesh;
			console.log(self);
		}

		game.scene.add(self.mesh);
	}
	createMesh();
}

module.exports = Bot;
