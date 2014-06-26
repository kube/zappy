global.THREE = THREE,
global.$ = $,
global.TWEEN = require('tween.js');

var	net = require('net'),
	gui = require('nw.gui'),
	Game = require('./js/Game.js');
	ResponseParser = require('./js/ResponseParser.js');


/*
**	Override exceptions handling to prevent crashes
*/
process.on('uncaughtException', function(e) {

	console.log(e);

	switch (e.code) {

		case 'ECONNREFUSED':
			displayConnectionForm();
			break;

		default:
			console.log(e.message);
	}
});


/*
**	Set Window Properties
*/
var win = gui.Window.get();
win.title = "Zappy";
win.width = 1300;
win.height = 900;


/*
**	Interface and Form
*/
function displayConnectionForm() {
	$("#loginForm").show();
	$("#renderCanvas").hide();
	$("#infoBar").hide();
}

function displayGame() {
	$("#loginForm").hide();
	$("#renderCanvas").show();
	$("#infoBar").show();
}

function validateConnectionForm() {
	var	host = document.getElementById('hostField').value,
		port = document.getElementById('portField').value;

	console.log('Connecting to ' + host + ':' + port);
	connectToServer(host, port);
}


/*
**	Server Connection
*/
function destroySession(client, game) {
	client.destroy();
	game.destroy();
	displayConnectionForm();
}

function connectToServer(host, port) {
	displayGame();

	var	client = new net.Socket(),
		game = new Game({client: client}),
		responseParser = new ResponseParser(client, game);

	// Attach event to Back button
	document.getElementById('btnBack').addEventListener('click', function _func() {
		destroySession(client, game);
		document.getElementById('btnBack').removeEventListener('click', _func);
	});

	client.connect(port, host, function() {
		console.log('Established connection');
	});

	client.on('data', function(data) {
		var responses = data.toString().split('\n');
		for (var i in responses)
			responseParser.push(responses[i]);
		// Push each response to the response parser
	});

	client.on('close', function() {
		console.log('Disconnected from Server');
		destroySession(client, game);
		game.clear();
		game = null;
	});
}

