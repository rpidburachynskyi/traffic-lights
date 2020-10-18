#pragma once
#include <string>
#include <functional>
#include "../lib/TM1637-1.2.0/TM1637Display.h"

class Counter
{
public:
    Counter(const int &CLK, const int &DIO);
    ~Counter();

    void loop();

    void from(const int &seconds);
    int remains();
    void show(std::string s);

private:
    TM1637Display *_display;

    int _lastMillis;
    int _fromSeconds;
};