var	Map = require('./Map.js'),
	Bot = require('./Bot.js'),
	Team = require('./Team.js');

var Game = function(options) {
	var self = this;
	var window = GLOBAL.window;
	var document = window.document;

	var canvas = document.getElementById("renderCanvas");
	var server = options.client;
	var scene = new THREE.Scene();
	var	camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
	camera.position.z = 5;
	var controls = new THREE.OrbitControls(camera);
	var renderer = new THREE.WebGLRenderer({
		canvas: canvas,
		antialias: true
	});

	renderer.setSize(window.innerWidth, window.innerHeight);

	this.scene = scene;
	this.renderer = renderer;
	this.time = 7;
	this.teams = [];
	this.bots = [];


	/*
	**	Define Game Materials
	*/
	this.materials = {

		basic: new THREE.MeshBasicMaterial({
			color: 0xada1e6
		}),

		block: new THREE.MeshBasicMaterial({
			color: 0x17171d
		}),

		blockSelected: new THREE.MeshBasicMaterial({
			color: 0x2e2e3f
		}),

		randomRainbow: new THREE.MeshBasicMaterial({
			color: 0xe91a70
		}),

		ressources: [
			new THREE.MeshBasicMaterial({
				color: 0xdacd60,
				opacity: 0.5
			}),
			new THREE.MeshBasicMaterial({
				color: 0xda428c,
				opacity: 0.5
			}),
			new THREE.MeshBasicMaterial({
				color: 0x8046db,
				opacity: 0.5
			}),
			new THREE.MeshBasicMaterial({
				color: 0x40abdb,
				opacity: 0.5
			}),
			new THREE.MeshBasicMaterial({
				color: 0x47dc37,
				opacity: 0.5
			}),
			new THREE.MeshBasicMaterial({
				color: 0xdc6a28,
				opacity: 0.5
			}),
			new THREE.MeshBasicMaterial({
				color: 0xb1dc41,
				opacity: 0.5
			})]
	};

	// Hackish way to make transparent material
	for (var i in self.materials.ressources)
		self.materials.ressources[i].transparent = true;


	/*
	**	Custom geometries generation
	*/
	function createRIPGeometry() {

		var	a = new THREE.Mesh(
				new THREE.BoxGeometry(1, 4, 1),
				self.materials.character),

			b = new THREE.Mesh(
				new THREE.BoxGeometry(3, 1, 1),
				self.materials.character);

		a.position.set(0, 2, 0);
		b.position.set(0, 2.5, 0);

		var geometry = new THREE.Geometry();
		THREE.GeometryUtils.merge(geometry, a);
		THREE.GeometryUtils.merge(geometry, b);

		return geometry;
	}
	this.RIPGeometry = createRIPGeometry();

	function createStickmanGeometry() {

		var	a = new THREE.Mesh(
				new THREE.BoxGeometry(0.8, 1.5, 1),
				self.materials.character),

			b = new THREE.Mesh(
				new THREE.BoxGeometry(0.8, 1.5, 1),
				self.materials.character),

			c = new THREE.Mesh(
				new THREE.BoxGeometry(2, 2.5, 1),
				self.materials.character),

			s = new THREE.Mesh(
				new THREE.SphereGeometry(1, 20, 20),
				self.materials.character),

			f = new THREE.Mesh(
				new THREE.CylinderGeometry(0, 1, 1, 4),
				self.materials.character);

		a.position.set(0.6, 0.75, 0);
		b.position.set(-0.6, 0.75, 0);
		c.position.set(0, 2.75, 0);
		s.position.set(0, 4.85, 0);

		f.scale.x = 1;
		f.scale.y = 2.7;
		f.scale.z = 0.3;
		f.position.z = 2.5;
		f.rotation.set(Math.PI/2, 0, 0);

		var geometry = new THREE.Geometry();
		THREE.GeometryUtils.merge(geometry, a);
		THREE.GeometryUtils.merge(geometry, b);
		THREE.GeometryUtils.merge(geometry, c);
		THREE.GeometryUtils.merge(geometry, s);
		THREE.GeometryUtils.merge(geometry, f);

		return geometry;
	}
	this.stickmanGeometry = createStickmanGeometry();


	/*
	**	Informations Bar initialization and clear
	*/
	function enableInfoBar() {
		var	items = document.getElementById('infoBar')
			.getElementsByTagName('ul')[0].getElementsByTagName('li');
		for (var i = 0; i < 7; i++) {
			items[i].addEventListener('click',
				(function (i) {
					return function a() {
						self.map.switchRessource(i);
					}})(i));
		}
	}

	function clearInfoBar() {
		var	items = document.getElementById('infoBar')
			.getElementsByTagName('ul')[0].getElementsByTagName('li');
		for (var i = 0; i < 7; i++) {
			items[i].removeEventListener('click', 'a');
		}
	}


	/*
	**	Game Mouse & Keyboard Events
	*/
	function pickMesh(x, y) {
		var projector = new THREE.Projector();
		var vector = new THREE.Vector3(( x / window.innerWidth ) * 2 - 1, -( y / window.innerHeight ) * 2 + 1, 0.5);
		projector.unprojectVector(vector, camera);
		var raycaster = new THREE.Raycaster(camera.position, vector.sub(camera.position).normalize());
		var intersects = raycaster.intersectObjects(scene.children);
		return intersects[0];
	}

	canvas.addEventListener('click', function(e) {
		var pick = pickMesh(e.x, e.y);
		if (pick && pick.object
			&& typeof pick.object.onClick == 'function')
			pick.object.onClick(e);
	});

	var currentMouseOver = null;
	canvas.addEventListener('mouseout', function(e) {
		if (currentMouseOver
			&& typeof currentMouseOver.onMouseOut == 'function')
			currentMouseOver.onMouseOut(e);
		currentMouseOver = null;
	});
	canvas.addEventListener('mousemove', function(e) {
		var pick = pickMesh(e.x, e.y);
		if (!pick || pick.object != currentMouseOver) {
			if (currentMouseOver
				&& typeof currentMouseOver.onMouseOut == 'function')
				currentMouseOver.onMouseOut(e);
			currentMouseOver = pick ? pick.object : null;
		}
		if (pick && pick.object
			&& typeof pick.object.onMouseOver == 'function')
			pick.object.onMouseOver(e);
	});

	window.addEventListener('keydown', function(e) {

		console.log('keyDown: ' + e.keyCode);
		switch (e.keyCode) {

			// Minus
			case 189:
				// Decrement server time
				if (game.time > 1) {
					var newTime = game.time;
						newTime--;
					server.write('sst ' + newTime + '\n');
				}
				break;

			// Plus
			case 187:
				// Increment server time
				var newTime = game.time + 1;
				server.write('sst ' + newTime + '\n');
				break;

			// Space
			case 32:
				// currentDisplayedRessource = (currentDisplayedRessource + 2) % 8 - 1;
				// self.map.displayRessource(currentDisplayedRessource);
				break;
		}
	});

	window.onresize = function() {
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
		renderer.setSize(window.innerWidth, window.innerHeight);
	}


	/*
	**	Game Content Methods
	*/
	this.createTeam = function(name) {
		self.teams.push(new Team(self, name));
	}

	this.getTeamByName = function(name) {
		for (var i in self.teams)
			if (self.teams[i].name == name)
				return self.teams[i];
		return null;
	}

	this.createMap = function(width, height) {
		self.map = new Map(self, width, height);
	}

	this.createBot = function(number, x, y, orientation, level, team) {
		var bot = new Bot(self, number, x, y, orientation, level, team);
		this.bots[number] = bot;
		return bot;
	}


	/*
	**	Render Loop
	*/
	function runRenderLoop(time) {
		window.requestAnimationFrame(runRenderLoop);
		TWEEN.update(time);

		var d = new Date();
		// Ressources opacity animation
		for (var i in self.materials.ressources)
			self.materials.ressources[i].opacity = 0.65 + Math.sin(d.getTime() * 0.005) * 0.25;

		// RandomRainbow Material color update
		self.materials.randomRainbow.color = Math.random();

		renderer.render(scene, camera);
	};

	this.run = function() {
		runRenderLoop();
	}

	this.clear = function() {

	}

	this.destroy = function() {

	}

	enableInfoBar();
}

module.exports = Game;
