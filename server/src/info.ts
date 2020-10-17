import { types } from 'shared';
import { ILight } from 'shared/dist/interfaces';

let lights: ILight[] = [];

const info: types.Info = {
	isTurned: true,
	isLocalControlling: false,
	lights
};

export const getInfo = () => {
	return info;
};
