#pragma once

class Light
{
public:
    Light(const int &pin);

    void loop();

    void turn(const bool &isLighting);

private:
    int _pin;
};