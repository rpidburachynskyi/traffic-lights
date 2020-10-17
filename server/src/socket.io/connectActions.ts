import { updateInfo } from '../info';
import { updateAll } from './socket.io';

export const connectActions = (socket: SocketIO.Socket) => {
	socket.on('turn', onTurn);
};

const onTurn = (isTurned: boolean) => {
	updateInfo((info) => ({
		...info,
		isTurned
	}));
	updateAll();
};
