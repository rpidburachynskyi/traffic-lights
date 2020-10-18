import { types } from '..';
export declare const changeSpecLightLink: (info: types.Info, lightId: string, linkWithId: string) => {
    lights: import("../interfaces").ILight[];
    isLocalControlling: boolean;
    isTurned: boolean;
};
