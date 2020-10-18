import { handlers } from 'shared';
import { setGlobalInfo } from '../../App';

let _socket: SocketIOClient.Socket;

export const connectActions = (socket: SocketIOClient.Socket) => {
	_socket = socket;
};

export const turn = (value: boolean) => {
	_socket.emit('turn', value);
};

export const setTime = (lightId: string, time: number) => {
	_socket.emit('setTime', lightId, time);
	setGlobalInfo((info) => handlers.setTimeHandler(info, lightId, time));
};

export const clamp = (lightId: string) => {
	_socket.emit('clamp', lightId);
	setGlobalInfo((info) => handlers.clampHandler(info, lightId));
};

export const unclamp = (lightId: string) => {
	_socket.emit('unclamp', lightId);
	setGlobalInfo((info) => handlers.unclampHandler(info, lightId));
};

export const changeLinkWithId = (lightId: string, linkWithId: string) => {
	_socket.emit('changeLinkWithId', lightId, linkWithId);
	setGlobalInfo((info) =>
		handlers.changeSpecLightLink(info, lightId, linkWithId)
	);
};
