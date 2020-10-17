import { types } from '..';

export const clampHandler = (
	info: types.Info,
	lightId: string,
	time: number
) => ({
	...info,
	lights: info.lights.map((light) => {
		if (light.id === lightId) {
			light.clamped = true;
		}

		return light;
	})
});
