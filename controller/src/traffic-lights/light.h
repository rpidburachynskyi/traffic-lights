#pragma once

#include "controller/controller.h"

enum Type
{
    TRED,
    TYELLOW,
    TGREEN,
    LEFT_GREEN,
    RIGHT_GREEN
};

class Light
{
public:
    Light(const Type &type, const int &pin, Controller *controller);

    void loop();

    void turn(const bool &isLighting, const bool &isBlinking);

private:
    Type _type;
    Controller *_controller;

    int _pin;
    bool _isTurned;

    bool _isBlinking;
    int _lastMillis;
};