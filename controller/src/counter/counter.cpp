#include "counter.h"

#include <Arduino.h>
#include <sstream>

std::string NumberToString(const int &n);

Counter::Counter(const int &CLK, const int &DIO) : _lastMillis(0), _fromSeconds(0)
{
    _display = new TM1637Display(CLK, DIO);
}

Counter::~Counter()
{
    delete _display;
}

void Counter::from(const int &seconds)
{
    _fromSeconds = seconds;
    _lastMillis = millis();
}

int Counter::remains()
{
    int subMillis = millis() - _lastMillis;

    int remainSeconds = subMillis / 1000;

    return (_fromSeconds - remainSeconds);
}

void Counter::loop()
{
    int remainSeconds = remains();

    if (remainSeconds < 0)
        return;

    int minutes = remainSeconds / 60;
    int seconds = remainSeconds % 60;

    std::string res = "";
    if (minutes < 10)
        res += "0";

    res += NumberToString(minutes);

    if (seconds < 10)
        res += "0";
    res += NumberToString(seconds);

    this->show(res);
}

void Counter::show(std::string s)
{
    uint8_t data[] = {0xff, 0xff, 0xff, 0xff};

    this->_display->setBrightness(0x0f);

    for (int i = 0; i < 4; i++)
    {
        if (i >= s.length() || s[i] == ' ')
        {
            data[i] = 0;
        }
        else
        {
            switch (s[i])
            {
            case '0':
                data[i] = this->_display->encodeDigit(0);
                break;
            case '1':
                data[i] = this->_display->encodeDigit(1);
                break;
            case '2':
                data[i] = this->_display->encodeDigit(2);
                break;
            case '3':
                data[i] = this->_display->encodeDigit(3);
                break;
            case '4':
                data[i] = this->_display->encodeDigit(4);
                break;
            case '5':
                data[i] = this->_display->encodeDigit(5);
                break;
            case '6':
                data[i] = this->_display->encodeDigit(6);
                break;
            case '7':
                data[i] = this->_display->encodeDigit(7);
                break;
            case '8':
                data[i] = this->_display->encodeDigit(8);
                break;
            case '9':
                data[i] = this->_display->encodeDigit(9);
                break;
            default:
                break;
            }
        }
    }

    this->_display->setSegments(data);
}

std::string NumberToString(const int &n)
{
    std::ostringstream ss;
    ss << n;
    return ss.str();
}