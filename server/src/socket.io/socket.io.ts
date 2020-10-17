import { Server } from 'http';
import * as socketIo from 'socket.io';
import { getInfo } from '../info';

export const connect = (httpServer: Server) => {
	const io = socketIo(httpServer);

	io.on('connect', onConnect);
};

const onConnect = (socket: socketIo.Socket) => {
	const info = getInfo();

	socket.emit('init', {
		info
	});
};
