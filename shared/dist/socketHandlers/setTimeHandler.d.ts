import { types } from '..';
export declare const setTimeHandler: (info: types.Info, lightId: string, time: number) => {
    lights: import("../interfaces").ILight[];
    isLocalControlling: boolean;
    isTurned: boolean;
};
