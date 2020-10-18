#pragma once
#include <string>

#include "../lib/IRemote/IRremote.h"

class Counter;
class TrafficLights;
class Socket;
class IRrecv;

enum LightType
{
    RED,
    YELLOW,
    GREEN,
};

class Controller
{
public:
    Controller(const int &CLK,
               const int &DIO,
               const int &RED_PIN,
               const int &YELLOW_PIN,
               const int &GREEN_PIN,
               const int &LEFT_GREEN_PIN,
               const int &RIGHT_GREEN_PIN,
               const int &recv_pin,
               const int &button_pin);
    ~Controller();

    void loop();

    void setState(const bool &red, const bool &yellow, const bool &green, const bool &leftGreen, const bool &rightGreen);
    void setRedState(const bool &red);
    void setYellowState(const bool &yellow);
    void setGreenState(const bool &green);
    void setLeftGreenState(const bool &leftGreen);
    void setRightGreenState(const bool &rightGreen);

private:
    bool _isLocalControlling;
    bool _isTurned;

    Counter *_counter;
    TrafficLights *_trafficLights;
    Socket *_socket;

    LightType _currentLightType;

    IRrecv *_irrecv;
    decode_results results;

    int _buttonPin;

    void next();
    bool readIRAction();

    bool _redState;
    bool _yellowState;
    bool _greenState;
    bool _leftGreenState;
    bool _rightGreenState;
    bool _isStateUpdated;
};