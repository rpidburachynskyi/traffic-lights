import { Server } from 'http';
import * as socketIo from 'socket.io';

export const connect = (httpServer: Server) => {
	const io = socketIo(httpServer);

	io.on('connect', (socket) => {
		console.log('Connected socket from browser');
	});
};
