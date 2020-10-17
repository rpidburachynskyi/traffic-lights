#pragma once
#include <string>
#include "../lib/TM1637-1.2.0/TM1637Display.h"

class Counter
{
public:
    Counter(const int &CLK, const int &DIO);
    ~Counter();

    void loop();

private:
    TM1637Display *_display;

    void show(std::string s);
};