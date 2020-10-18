#include "traffic-lights.h"

#include <Arduino.h>

TrafficLights::TrafficLights(const int &redPin, const int &yellowPin, const int &greenPin, const int &leftPin, const int &rightPin)
{
    this->_redLight = new Light(redPin);
    this->_yellowLight = new Light(yellowPin);
    this->_greenLight = new Light(greenPin);
    this->_leftGreenLight = new Light(leftPin);
    this->_rightGreenLight = new Light(rightPin);
}

TrafficLights::~TrafficLights()
{
    delete this->_redLight;
    delete this->_yellowLight;
    delete this->_greenLight;
    delete this->_leftGreenLight;
    delete this->_rightGreenLight;
}

void TrafficLights::loop()
{
    this->_redLight->loop();
    this->_yellowLight->loop();
    this->_greenLight->loop();
    this->_leftGreenLight->loop();
    this->_rightGreenLight->loop();
}

void TrafficLights::turnRed(const bool &isLighting, const bool &isBlinking)
{
    this->_redLight->turn(isLighting, isBlinking);
}

void TrafficLights::turnYellow(const bool &isLighting, const bool &isBlinking)
{
    this->_yellowLight->turn(isLighting, isBlinking);
}

void TrafficLights::turnGreen(const bool &isLighting, const bool &isBlinking)
{
    this->_greenLight->turn(isLighting, isBlinking);
}

void TrafficLights::turnLeftGreen(const bool &isLighting, const bool &isBlinking)
{
    this->_leftGreenLight->turn(isLighting, isBlinking);
}

void TrafficLights::turnRightGreen(const bool &isLighting, const bool &isBlinking)
{
    this->_rightGreenLight->turn(isLighting, isBlinking);
}