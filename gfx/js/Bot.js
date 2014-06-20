var Bot = function(game, number, x, y, orientation, level, team) {
	var self = this;
 
	this.name = number;
	this.x;
	this.y;
	this.orientation = orientation;
	this.level = level;
	this.team = team;

	var block = game.map.blocks[x][y];

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
		self.mesh.updateMatrix();

		self.mesh.rotation.set(Math.PI/2, 0, Math.PI/2 * (4 + (o - 3)));
	}

	function createMesh() {

		self.mesh = new THREE.Mesh(
			new THREE.CylinderGeometry(0, 0.4, 0.4, 4),
			game.materials.basic);

		self.mesh.scale.x = 0.4;
		self.mesh.scale.z = 0.1;

		game.scene.add(self.mesh);

		self.setPosition(block.position.x, block.position.y, orientation);
		self.mesh.onclick = function(e, pick) {
			// var pickedMesh = pick.pickedMesh;
			console.log(self);
		}
	}
	createMesh();
}

module.exports = Bot;
