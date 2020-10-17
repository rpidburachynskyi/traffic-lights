#include "controller.h"

#include <Arduino.h>

Controller::Controller(Counter *counter, TrafficLights *trafficLights, Socket *socket)
{
    this->_counter = counter;
    this->_trafficLights = trafficLights;
    this->_socket = socket;

    this->_counter->from(14);
}

Controller::~Controller()
{
    delete this->_counter;
    delete this->_trafficLights;
}

void Controller::loop()
{
    this->_counter->loop();
    this->_socket->loop();

    if (this->_counter->remains() < 0)
    {
        this->_counter->from(10);
    }
}