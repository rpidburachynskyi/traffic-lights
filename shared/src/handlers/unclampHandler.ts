import { types } from '..';

export const unclampHandler = (info: types.Info, lightId: string) => ({
	...info,
	lights: info.lights.map((light) => {
		if (light.id === lightId) {
			light.clamped = false;
		}

		return light;
	})
});
