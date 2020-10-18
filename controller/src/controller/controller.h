#pragma once
#include <string>

#include "counter/counter.h"
#include "traffic-lights/traffic-lights.h"
#include "socket/socket.h"
#include "../lib/IRemote/IRremote.h"

enum LightType
{
    RED,
    YELLOW,
    GREEN,
};

class Controller
{
public:
    Controller(Counter *counter, TrafficLights *trafficLights, Socket *socket, const int &recv_pin, const int &button_pin);
    ~Controller();

    void loop();

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
};