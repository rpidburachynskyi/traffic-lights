import { Server } from 'http';
import * as socketIo from 'socket.io';
import { getInfo } from '../info';
import { getState } from '../state';
import { connectActions } from './connectActions';

let sockets: SocketIO.Socket[] = [];

export const connect = (httpServer: Server) => {
	const io = socketIo(httpServer);

	io.on('connect', onConnect);
};

const onConnect = (socket: socketIo.Socket) => {
	const info = getInfo();
	const state = getState();

	sockets.push(socket);

	socket.emit('init', {
		info,
		state
	});

	connectActions(socket);
};

export const updateSockets = () => {
	sockets.forEach((socket) => {
		const info = getInfo();
		const state = getState();

		socket.emit('update', { info, state });
	});
};
