#pragma once
#include <string>

#include "counter/counter.h"
#include "traffic-lights/traffic-lights.h"

class Controller
{
public:
    Controller(Counter *counter, TrafficLights *trafficLights);
    ~Controller();

    void loop();

private:
    Counter *_counter;
    TrafficLights *_trafficLights;
};