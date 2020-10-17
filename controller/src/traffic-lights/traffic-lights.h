#pragma once

class TrafficLights
{
public:
    TrafficLights(const int &redPin, const int &yellowPin, const int &greenPin, const int &leftPin, const int &rightPin);

    void loop();

    void turnRed(const bool &isLighting);
    void turnYellow(const bool &isLighting);
    void turnGreen(const bool &isLighting);
    void turnLeftGreen(const bool &isLighting);
    void turnRightGreen(const bool &isLighting);

private:
    int _redPin;
    int _yellowPin;
    int _greenPin;
    int _leftPin;
    int _rightPin;
};