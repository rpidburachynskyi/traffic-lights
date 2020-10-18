import { updateSockets } from '../socket.io/socket.io';
import { updateController } from '../socket/socket';

export const updateAll = () => {
	updateSockets();
	updateController();
};
