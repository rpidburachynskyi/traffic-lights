let _socket: SocketIOClient.Socket;

export const connectActions = (socket: SocketIOClient.Socket) => {
	_socket = socket;
};

export const turn = (value: boolean) => {
	_socket.emit('turn', value);
};
