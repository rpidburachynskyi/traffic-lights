import { Server } from 'http';
import * as socketIo from 'socket.io';
import { getInfo } from '../info';
import { connectActions } from './connectActions';

let sockets: SocketIO.Socket[] = [];

export const connect = (httpServer: Server) => {
	const io = socketIo(httpServer);

	io.on('connect', onConnect);
};

const onConnect = (socket: socketIo.Socket) => {
	const info = getInfo();

	sockets.push(socket);

	socket.emit('init', {
		info
	});

	connectActions(socket);
};

export const updateAll = () => {
	sockets.forEach((socket) => {
		const info = getInfo();

		socket.emit('update', { info });
	});
};