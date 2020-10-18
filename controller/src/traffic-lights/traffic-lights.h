#pragma once

#include "light.h"

class TrafficLights
{
public:
    TrafficLights(const int &redPin, const int &yellowPin, const int &greenPin, const int &leftPin, const int &rightPin);
    ~TrafficLights();

    void loop();

    void turnRed(const bool &isLighting);
    void turnYellow(const bool &isLighting);
    void turnGreen(const bool &isLighting);
    void turnLeftGreen(const bool &isLighting);
    void turnRightGreen(const bool &isLighting);

private:
    Light *_redLight;
    Light *_yellowLight;
    Light *_greenLight;
    Light *_leftGreenLight;
    Light *_rightGreenLight;
};