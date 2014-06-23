var	Map = require('./Map.js'),
	Bot = require('./Bot.js'),
	Team = require('./Team.js');

var Game = function(options) {
	var self = this;
	var window = GLOBAL.window;
	var document = window.document;
	global.game = this;

	var canvas = document.getElementById("renderCanvas");
	var scene = new THREE.Scene();
	var	camera = new THREE.PerspectiveCamera(75, window.innerWidth / window.innerHeight, 0.1, 1000);
	camera.position.z = 5;
	var controls = new THREE.OrbitControls(camera);
	var renderer = new THREE.WebGLRenderer({
		canvas: canvas,
		antialias: true
	});
	renderer.setSize(window.innerWidth, window.innerHeight);

	var ambientLight = new THREE.AmbientLight(0x111111);
	var directionalLight = new THREE.DirectionalLight(0x666666);
	directionalLight.position.set(1, 10, 1).normalize();
	scene.add(ambientLight);
	scene.add(directionalLight);

	this.scene = scene;
	this.renderer = renderer;
	this.materials = {

		basic: new THREE.MeshBasicMaterial({
			color: 0xada1e6
		}),
		block: new THREE.MeshPhongMaterial({
			color: 0x272831
		}),

		ressources: [
			new THREE.MeshBasicMaterial({
				color: 0xdacd60
			}),
			new THREE.MeshBasicMaterial({
				color: 0xda428c
			}),
			new THREE.MeshBasicMaterial({
				color: 0x8046db
			}),
			new THREE.MeshBasicMaterial({
				color: 0x40abdb
			}),
			new THREE.MeshBasicMaterial({
				color: 0x47dc37
			}),
			new THREE.MeshBasicMaterial({
				color: 0xdc6a28
			}),
			new THREE.MeshBasicMaterial({
				color: 0xb1dc41
			})]
	};

	this.teams = [];
	this.bots = [];


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



	function enableInfoBar() {

		var	items = document.getElementById('infoBar')
			.getElementsByTagName('ul')[0].getElementsByTagName('li');

		for (var i = 0; i < 7; i++) {
			items[i].addEventListener('click',
				(function (i) {
					return function() {
						self.map.displayRessource(i);
					}})(i));
		}
	}

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
			&& typeof pick.object.onclick == 'function')
			pick.object.onclick(e);
	});


	var currentDisplayedRessource = -1;

	window.addEventListener('keydown', function(e) {

		switch (e.keyCode) {

			case 32:
				currentDisplayedRessource = (currentDisplayedRessource + 2) % 8 - 1;
				self.map.displayRessource(currentDisplayedRessource);
				break;

		}

	});

	function runRenderLoop(time) {
		window.requestAnimationFrame(runRenderLoop);
		TWEEN.update(time);
		renderer.render(scene, camera);
	};

	window.onresize = function() {
		camera.aspect = window.innerWidth / window.innerHeight;
		camera.updateProjectionMatrix();
		renderer.setSize(window.innerWidth, window.innerHeight);
	}

	this.createTeam = function(name) {
		self.teams.push(new Team(self, name));
	}

	this.getTeamByName = function(name) {
		console.log('Get Team By Name');
		for (var i in self.teams)
			if (self.teams[i].name == name)
				return self.teams[i];
		return null;
	}

	this.createMap = function(width, height) {
		self.map = new Map(self, width, height);
	}

	this.createBot = function(number, x, y, orientation, level, team) {
		console.log('WELCOME');
		var bot = new Bot(self, number, x, y, orientation, level, team);
		this.bots[number] = bot;


		return bot;
	}

	this.run = function() {
		runRenderLoop();
	}

	this.clear = function() {
		// engine.stopRenderLoop();
		// engine.clear(new BABYLON.Color3(0, 0, 0), true, true);
	}

	this.destroy = function() {
		// scene.dispose();
		// engine.clear(new BABYLON.Color3(0, 0, 0), true, true);
	}

	enableInfoBar();
}

module.exports = Game;
