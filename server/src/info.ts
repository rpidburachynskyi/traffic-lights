import { types } from 'shared';
import { ILight } from 'shared/dist/interfaces';

let lights: ILight[] = [
	{
		id: 'red',
		clamped: false,
		color: 'red',
		duration: 10
	},
	{
		id: 'yellow',
		clamped: false,
		color: 'yellow',
		duration: 10
	},
	{
		id: 'green',
		clamped: false,
		color: 'green',
		duration: 10
	},
	{
		id: 'leftGreen',
		clamped: false,
		color: 'green',
		duration: 10
	},
	{
		id: 'rightGreen',
		clamped: false,
		color: 'green',
		duration: 10
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
