import * as net from 'net';

const server = net.createServer();

server.on('connection', (socket) => {
	console.log('Socket did connect');
});

server.listen(process.env.SOCKET_PORT, function () {
	console.log(
		`Socket server listening to ${process.env.SOCKET_PORT} port...`
	);
});
