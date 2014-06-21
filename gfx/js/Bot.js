var Bot = function(game, number, x, y, orientation, level, team) {
	var self = this;

	this.name = number;
	this.x;
	this.y;
	this.orientation = orientation;
	this.level = level;
	this.team = team;

	// console.log('Creating BOT');

	var block = game.map.blocks[x][y];

	// console.log(block)

	this.position = {
		x: block.position.x,
		y: block.position.y
	};

	this.setPosition = function(x, y, o) {

		console.log(x + ' ' + y + ' ' + o);

		self.x = x;
		self.y = y;
		self.orientation = o;
		block = game.map.blocks[x][y];

		// Mesh position update
		self.mesh.position.set(block.position.x, 0.3, block.position.y);
		self.mesh.rotation.set(Math.PI/2, 0, Math.PI/2 * (4 + (o - 3)));
		self.mesh.updateMatrix();
	}

	function createMesh() {

		console.log('Creating Bot Mesh')

		self.mesh = new THREE.Mesh(
			new THREE.CylinderGeometry(0, 0.2, 0.2, 4),
			game.materials.basic);

		self.mesh.scale.x = 0.4;
		self.mesh.scale.z = 0.1;

		self.setPosition(x, y, orientation);
		game.scene.add(self.mesh);

		self.mesh.onclick = function(e, pick) {
			// var pickedMesh = pick.pickedMesh;
			console.log(self);
		}
	}
	createMesh();
}

module.exports = Bot;
