import { types } from 'shared';
import io from 'socket.io-client';
import { setGlobalInfo, setGlobalState } from '../../App';
import { connectActions } from './actions';

const socket = io('http://localhost:5000');

socket.on('connect', () => {
	socket.on('init', onInit);
	socket.on('update', onUpdate);
});

const onInit = ({ info, state }: { info: types.Info; state: types.State }) => {
	setGlobalInfo(info);
	setGlobalState(state);
};

const onUpdate = ({
	info,
	state
}: {
	info: types.Info;
	state: types.State;
}) => {
	setGlobalInfo(info);
	setGlobalState(state);
};

connectActions(socket);
