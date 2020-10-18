#pragma once

#include "light.h"

class TrafficLights
{
public:
    TrafficLights(const int &redPin, const int &yellowPin, const int &greenPin, const int &leftPin, const int &rightPin);
    ~TrafficLights();

    void loop();

    void turnRed(const bool &isLighting, const bool &isBlinking = false);
    void turnYellow(const bool &isLighting, const bool &isBlinking = false);
    void turnGreen(const bool &isLighting, const bool &isBlinking = false);
    void turnLeftGreen(const bool &isLighting, const bool &isBlinking = false);
    void turnRightGreen(const bool &isLighting, const bool &isBlinking = false);

private:
    Light *_redLight;
    Light *_yellowLight;
    Light *_greenLight;
    Light *_leftGreenLight;
    Light *_rightGreenLight;
};