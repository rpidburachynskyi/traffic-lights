import { types } from 'shared';
import { ILight } from 'shared/dist/interfaces';

let lights: ILight[] = [
	{
		id: 'red',
		name: 'Red',
		clamped: false,
		color: 'red',
		duration: 10,
		spec: false,
		linksWithId: ''
	},
	{
		id: 'yellow',
		name: 'Yellow',
		clamped: false,
		color: 'yellow',
		duration: 10,
		spec: false,
		linksWithId: ''
	},
	{
		id: 'green',
		name: 'Green',
		clamped: false,
		color: 'green',
		duration: 10,
		spec: false,
		linksWithId: ''
	},
	{
		id: 'leftGreen',
		name: 'Left green',
		clamped: false,
		color: 'green',
		duration: 10,
		spec: true,
		linksWithId: 'green'
	},
	{
		id: 'rightGreen',
		name: 'Right green',
		clamped: false,
		color: 'green',
		duration: 10,
		spec: true,
		linksWithId: 'green'
	}
];

let info: types.Info = {
	isTurned: true,
	isLocalControlling: false,
	lights
};

export const getInfo = () => {
	return info;
};

export const updateInfo = (callback: (oldInfo: types.Info) => types.Info) => {
	const newInfo = callback(info);
	info = {
		...info,
		...newInfo
	};
};
