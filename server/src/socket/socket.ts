import * as net from 'net';
import { types } from 'shared';
import { getInfo } from '../info';
import { updateState } from '../state';

const server = net.createServer();

let _socket: net.Socket;

server.on('connection', (socket) => {
	console.log('Socket did connect');

	_socket = socket;

	_socket.write(JSON.stringify({ type: 'init', ...getInfo() }));

	socket.on('data', (data) => {
		const obj = JSON.parse(
			data.toString().slice(data.toString().lastIndexOf('}{') + 1)
		);

		const newState: types.State = {
			redState: !!obj.red,
			yellowState: !!obj.yellow,
			greenState: !!obj.green,
			leftGreenState: !!obj.leftGreen,
			rightGreenState: !!obj.rightGreen
		};

		updateState(newState);
	});

	socket.on('error', (err) => {
		console.log(err);
	});
});

server.listen(process.env.SOCKET_PORT, () => {
	console.log(
		`Socket server listening to ${process.env.SOCKET_PORT} port...`
	);
});

export const updateController = () => {
	if (!_socket) return;
	_socket.write(JSON.stringify({ type: 'update', ...getInfo() }));
};

export const restartController = () => {
	if (!_socket) return;
	_socket.write('RESTART');
};
