#include "traffic-lights.h"

#include <Arduino.h>

TrafficLights::TrafficLights(const int &redPin, const int &yellowPin, const int &greenPin, const int &leftPin, const int &rightPin)
{
    this->_redPin = redPin;
    this->_yellowPin = yellowPin;
    this->_greenPin = greenPin;
    this->_leftPin = leftPin;
    this->_rightPin = rightPin;

    pinMode(this->_redPin, OUTPUT);
    pinMode(this->_yellowPin, OUTPUT);
    pinMode(this->_greenPin, OUTPUT);
    pinMode(this->_leftPin, OUTPUT);
    pinMode(this->_rightPin, OUTPUT);
}

void TrafficLights::turnRed(const bool &isLighting)
{
    digitalWrite(this->_redPin, isLighting ? HIGH : LOW);
}

void TrafficLights::turnYellow(const bool &isLighting)
{
    digitalWrite(this->_yellowPin, isLighting ? HIGH : LOW);
}

void TrafficLights::turnGreen(const bool &isLighting)
{
    digitalWrite(this->_greenPin, isLighting ? HIGH : LOW);
}

void TrafficLights::turnLeftGreen(const bool &isLighting)
{
    digitalWrite(this->_leftPin, isLighting ? HIGH : LOW);
}

void TrafficLights::turnRightGreen(const bool &isLighting)
{
    digitalWrite(this->_rightPin, isLighting ? HIGH : LOW);
}