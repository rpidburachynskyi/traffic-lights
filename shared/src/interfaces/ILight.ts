export interface ILight {
	id: string;
	color: string;
	clamped: boolean;
	duration: number; // seconds
	spec: boolean;
	linksWithId: string; // only if spec === true
}
