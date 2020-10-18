import { types } from '..';

export const changeSpecLightLink = (
	info: types.Info,
	lightId: string,
	linkWithId: string
) => ({
	...info,
	lights: info.lights.map((light) => {
		if (light.id === lightId) {
			light.linksWithId = linkWithId;
		}

		return light;
	})
});
