"use strict";
var __assign = (this && this.__assign) || function () {
    __assign = Object.assign || function(t) {
        for (var s, i = 1, n = arguments.length; i < n; i++) {
            s = arguments[i];
            for (var p in s) if (Object.prototype.hasOwnProperty.call(s, p))
                t[p] = s[p];
        }
        return t;
    };
    return __assign.apply(this, arguments);
};
exports.__esModule = true;
exports.changeSpecLightLink = void 0;
exports.changeSpecLightLink = function (info, lightId, linkWithId) { return (__assign(__assign({}, info), { lights: info.lights.map(function (light) {
        if (light.id === lightId) {
            light.linksWithId = linkWithId;
        }
        return light;
    }) })); };