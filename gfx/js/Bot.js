var Bot = function(game, number, x, y, orientation, level, teamName) {
	var self = this;

	this.name = number;
	this.x = x;
	this.y = y;
	this.orientation = orientation;
	this.level = level;

	// Set current block and Bot position in space
	var block = game.map.blocks[x][y];
	this.position = {
		x: block.position.x,
		y: block.position.y
	};
	this.inventory = [0, 0, 0, 0, 0, 0, 0];

	// Add Bot to Team
	game.getTeamByName(teamName).addBot(self);

	this.setPosition = function(x, y, o) {
		self.x = x;
		self.y = y;

		// Update block's players content
		block.removeBot(self);
		block = game.map.blocks[x][y];
		block.addBot(self);

		// Set placement in block from players quantity in block
		var index = block.getBots().indexOf(self) % 9,
			xa = parseInt(index) % 3,
			ya = parseInt(index / 3);

		// Check Mesh Rotation before animating it
		if (o == 4 && self.orientation == 1)
			self.mesh.rotation.y = -Math.PI / 2 * 6;
		else if (o == 1 && self.orientation == 4)
			self.mesh.rotation.y = -Math.PI / 2;
		self.orientation = o;

		// Animate Mesh Move
		var	newRotation = -(Math.PI / 2 * (1 + o));
		var tween = new TWEEN.Tween({
				x: self.position.x,
				y: self.position.y,
				a: self.mesh.rotation.y,
			})
			.to({
				x: block.position.x - 1 / 3 + xa * 1 / 3,
				y: block.position.y - 1 / 3 + ya * 1 / 3,
				a: newRotation
			}, 7000 / game.time)
			.easing(TWEEN.Easing.Cubic.InOut)
			.onUpdate(function() {

				self.mesh.position.set(this.x, 0, this.y);
				self.mesh.rotation.set(0, this.a, 0);

				// Update Self Position
				self.position = {
					x: block.position.x - 1 / 3 + xa * 1 / 3,
					y: block.position.y - 1 / 3 + ya * 1 / 3
				}
			})
			.start();

		self.mesh.updateMatrix();
	}

	this.setInventory = function(inventory) {
		self.inventory = inventory;
	}

	this.elevate = function() {

	}

	// Passes from Egg to Bot
	this.upgrade = function() {

		// Remove current mesh
		if (self.level == 0) {
			game.scene.remove(self.mesh);
			createBotMesh();
			self.setPosition(self.x, self.y, self.orientation);
		}
	}

	this.highlight = function() {
		self.mesh.material = self.team.materialSelected;
	}

	this.unlight = function() {
		self.mesh.material = self.team.material;
	}

	this.die = function() {

		// Remove current Mesh from scene and create new one
		game.scene.remove(self.mesh);
		self.mesh = new THREE.Mesh(game.RIPGeometry,
			self.team.material);

		self.mesh.scale.x = 0.05;
		self.mesh.scale.y = 0.05;
		self.mesh.scale.z = 0.05;

		self.setPosition(self.x, self.y, self.orientation);

		game.scene.add(self.mesh);
	}

	this.displayInventory = function() {
		console.log(self.inventory);
		for (var i in self.inventory)
			$('#infoBar .t' + i).text(self.inventory[i]);
	}

	this.jump = function(time, repeats) {

		// Animation Up
		var tweenUp = new TWEEN.Tween({
			z: 0.025
		})
		.to({
			z: 0
		}, time * 7000 / game.time)
		.easing(TWEEN.Easing.Bounce.InOut)
		.onUpdate(function() {
			self.mesh.position.y = this.z;
		});

		// Animation Down
		var tweenDown = new TWEEN.Tween({
			z: 0.76
		})
		.to({
			z: 0
		}, time * 7000 / game.time)
		.easing(TWEEN.Easing.Bounce.InOut)
		.onUpdate(function() {
			self.mesh.position.y = this.z;
		})
		.onComplete(function() {
			// Restart until repeats count down
			repeats--;
			if (repeats)
				tweenUp.start();
		});

		tweenUp.chain(tweenDown);
		tweenUp.start();
	}

	function createBotMesh() {
		self.mesh = new THREE.Mesh(game.stickmanGeometry,
			self.team.material);

		self.mesh.scale.x = 0.05;
		self.mesh.scale.y = 0.05;
		self.mesh.scale.z = 0.05;

		// Set Mesh position
		self.setPosition(self.x, self.y, self.orientation);

		self.mesh.onClick = function(e, pick) {
			// var pickedMesh = pick.pickedMesh;
			console.log(self);
		}
		self.mesh.onMouseOver = function(e, pick) {
			console.log();
			self.highlight();
			self.displayInventory();
		}
		self.mesh.onMouseOut = function(e, pick) {
			self.unlight();
			$('#infoBar a').text('');
		}
		game.scene.add(self.mesh);
	}


	function createEggMesh() {
		self.mesh = new THREE.Mesh(new THREE.SphereGeometry(1, 20, 20),
			self.team.material);

		self.mesh.scale.x = 0.04;
		self.mesh.scale.y = 0.04;
		self.mesh.scale.z = 0.04;

		// Set Mesh position
		self.setPosition(self.x, self.y, self.orientation);

		self.mesh.onClick = function(e, pick) {
		}
		game.scene.add(self.mesh);
	}
	if (level == 0)
		createEggMesh();
	else
		createBotMesh();
}

module.exports = Bot;
