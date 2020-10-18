import * as net from 'net';
import { getInfo } from '../info';

const server = net.createServer();

let _socket: net.Socket;

server.on('connection', (socket) => {
	console.log('Socket did connect');

	_socket = socket;

	_socket.write(JSON.stringify({ type: 'init', ...getInfo() }));
});

server.listen(process.env.SOCKET_PORT, () => {
	console.log(
		`Socket server listening to ${process.env.SOCKET_PORT} port...`
	);
});

export const updateController = () => {
	_socket.write(JSON.stringify({ type: 'update', ...getInfo() }));
};
