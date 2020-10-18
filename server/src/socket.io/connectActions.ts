import { handlers } from 'shared';
import { updateInfo } from '../info';
import { updateAll } from '../utils';

export const connectActions = (socket: SocketIO.Socket) => {
	socket.on('turn', onTurn);
	socket.on('setTime', onSetTime);
	socket.on('clamp', onClamp);
	socket.on('unclamp', onUnlamp);
	socket.on('changeLinkWithId', onChangeLinkWithId);
};

const onTurn = (isTurned: boolean) => {
	updateInfo((info) => ({
		...info,
		isTurned
	}));
	updateAll();
};

const onSetTime = (lightId: string, time: number) => {
	updateInfo((info) => handlers.setTimeHandler(info, lightId, time));
	updateAll();
};

const onClamp = (lightId: string) => {
	updateInfo((info) => handlers.clampHandler(info, lightId));
	updateAll();
};

const onUnlamp = (lightId: string) => {
	updateInfo((info) => handlers.unclampHandler(info, lightId));
	updateAll();
};

const onChangeLinkWithId = (lightId: string, linkWithId: string) => {
	updateInfo((info) =>
		handlers.changeSpecLightLink(info, lightId, linkWithId)
	);
	updateAll();
};
