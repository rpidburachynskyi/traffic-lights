#include "Light.h"

#include <Arduino.h>

Light::Light(const int &pin)
{
    this->_pin = pin;

    pinMode(this->_pin, OUTPUT);
}

void Light::loop()
{
}

void Light::turn(const bool &isLighting)
{
    digitalWrite(this->_pin, isLighting ? HIGH : LOW);
}
