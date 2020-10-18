#include "traffic-lights.h"

#include <Arduino.h>
#include "controller/controller.h"
#include "light.h"

TrafficLights::TrafficLights(const int &redPin, const int &yellowPin, const int &greenPin, const int &leftPin, const int &rightPin, Controller *controller)
{
    this->_redLight = new Light(Type::TRED, redPin, controller);
    this->_yellowLight = new Light(Type::TYELLOW, yellowPin, controller);
    this->_greenLight = new Light(Type::TGREEN, greenPin, controller);
    this->_leftGreenLight = new Light(Type::LEFT_GREEN, leftPin, controller);
    this->_rightGreenLight = new Light(Type::RIGHT_GREEN, rightPin, controller);
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