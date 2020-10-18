export interface ILight {
    id: string;
    name: string;
    color: string;
    clamped: boolean;
    duration: number;
    spec: boolean;
    linksWithId: string;
}
