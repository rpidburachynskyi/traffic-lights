#include "Light.h"

#include <Arduino.h>

Light::Light(const Type &type, const int &pin, Controller *controller) : _isTurned(false),
                                                                         _isBlinking(false),
                                                                         _lastMillis(0)
{
    this->_pin = pin;
    this->_type = type;
    this->_controller = controller;

    pinMode(this->_pin, OUTPUT);
}

void Light::loop()
{
    if (!_isBlinking)
    {
        return;
    }

    int sub = millis() - _lastMillis;

    if (sub >= 500)
    {
        _lastMillis = millis();
        turn(!_isTurned, _isBlinking);
    }
}

void Light::turn(const bool &isLighting, const bool &isBlinking)
{
    digitalWrite(this->_pin, isLighting ? HIGH : LOW);
    this->_isTurned = isLighting;
    this->_isBlinking = isBlinking;

    switch (this->_type)
    {
    case Type::TRED:
        this->_controller->setRedState(isLighting);
        break;
    case Type::TYELLOW:
        this->_controller->setYellowState(isLighting);
        break;
    case Type::TGREEN:
        this->_controller->setGreenState(isLighting);
        break;
    case Type::LEFT_GREEN:
        this->_controller->setLeftGreenState(isLighting);
        break;
    case Type::RIGHT_GREEN:
        this->_controller->setRightGreenState(isLighting);
        break;

    default:
        break;
    }
}
