import { types } from '..';

export const setTimeHandler = (
	info: types.Info,
	lightId: string,
	time: number
) => ({
	...info,
	lights: info.lights.map((light) => {
		if (light.id === lightId) {
			light.duration = time;
		}

		return light;
	})
});
