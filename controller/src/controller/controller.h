#pragma once
#include <string>

#include "counter/counter.h"
#include "traffic-lights/traffic-lights.h"
#include "socket/socket.h"

class Controller
{
public:
    Controller(Counter *counter, TrafficLights *trafficLights, Socket *socket);
    ~Controller();

    void loop();

private:
    Counter *_counter;
    TrafficLights *_trafficLights;
    Socket *_socket;
};