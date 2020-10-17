import { types } from 'shared';
import io from 'socket.io-client';
import { setGlobalInfo } from '../../App';
import { connectActions } from './actions';

const socket = io('http://localhost:5000');

socket.on('connect', () => {
	socket.on('init', onInit);
	socket.on('update', onUpdate);
});

const onInit = ({ info }: { info: types.Info }) => {
	setGlobalInfo(info);
};

const onUpdate = ({ info }: { info: types.Info }) => {
	setGlobalInfo(info);
	console.log(info);
};

connectActions(socket);
