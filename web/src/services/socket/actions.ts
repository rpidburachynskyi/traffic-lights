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
