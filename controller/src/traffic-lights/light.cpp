#include "Light.h"

#include <Arduino.h>

Light::Light(const int &pin) : _isTurned(false),
                               _isBlinking(false),
                               _lastMillis(0)
{
    this->_pin = pin;

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
}
