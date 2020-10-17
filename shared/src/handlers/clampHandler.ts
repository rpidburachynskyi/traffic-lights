import { types } from '..';

export const clampHandler = (info: types.Info, lightId: string) => ({
	...info,
	lights: info.lights.map((light) => {
		if (light.id === lightId) {
			light.clamped = true;
		}

		return light;
	})
});
