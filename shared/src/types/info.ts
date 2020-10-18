import { ILight } from '../interfaces';

export type Info = {
	isLocalControlling: boolean;
	isTurned: boolean;
	lights: ILight[];
};
