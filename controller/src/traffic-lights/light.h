#pragma once

class Light
{
public:
    Light(const int &pin);

    void loop();

    void turn(const bool &isLighting, const bool &isBlinking);

private:
    int _pin;
    bool _isTurned;

    bool _isBlinking;
    int _lastMillis;
};