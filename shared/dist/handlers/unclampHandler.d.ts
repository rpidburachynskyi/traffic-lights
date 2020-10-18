import { types } from '..';
export declare const unclampHandler: (info: types.Info, lightId: string) => {
    lights: import("../interfaces").ILight[];
    isLocalControlling: boolean;
    isTurned: boolean;
};
