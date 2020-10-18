import { types } from 'shared';
import { updateSockets } from './socket.io/socket.io';

let _state: types.State = {
	redState: false,
	greenState: false,
	leftGreenState: false,
	rightGreenState: false,
	yellowState: false
};

export const getState = () => {
	return _state;
};

export const updateState = (state: types.State) => {
	_state = state;
	updateSockets();
};
