#include "controller.h"

#include <Arduino.h>

#include "counter/counter.h"
#include "traffic-lights/traffic-lights.h"
#include "socket/socket.h"

Controller::Controller(
    const int &clk,
    const int &dio,
    const int &redPin,
    const int &yellowPin,
    const int &greenPin,
    const int &leftGreenPin,
    const int &rightGreenPin,
    const int &recv_pin,
    const int &button_pin) : _isLocalControlling(false),
                             _isTurned(false),
                             _currentLightType(GREEN),
                             _redState(false),
                             _yellowState(false),
                             _greenState(false),
                             _leftGreenState(false),
                             _rightGreenState(false)
{

    ;
    ;
    ;

    this->_counter = new Counter(clk, dio);
    this->_trafficLights = new TrafficLights(redPin, yellowPin, greenPin, leftGreenPin, rightGreenPin, this);

    this->_socket = new Socket;
    this->_socket->begin(IPAddress(192, 168, 0, 104), 9000);

    this->_irrecv = new IRrecv(recv_pin);
    this->_irrecv->enableIRIn();
    this->_irrecv->blink13(true);

    this->_buttonPin = button_pin;

    pinMode(this->_buttonPin, INPUT);

    next();
}

Controller::~Controller()
{
    delete this->_counter;
    delete this->_trafficLights;
}

void Controller::loop()
{
    static int prevButtonState = LOW;
    int buttonState = digitalRead(this->_buttonPin);

    if (buttonState != prevButtonState)
    {
        prevButtonState = buttonState;
        if (buttonState == HIGH)
        {

            this->_isLocalControlling = !this->_isLocalControlling;
        }
    }

    this->_socket->loop();

    if (!this->_isLocalControlling && this->_socket->hasUpdate())
    {
        this->_isTurned = this->_socket->info().isTurned;

        if (!this->_socket->info().isTurned)
        {
            this->_trafficLights->turnYellow(true);
        }
        else
        {
            this->_trafficLights->turnRed(this->_socket->info().redLightInfo.clamped);
            this->_trafficLights->turnYellow(this->_socket->info().yellowLightInfo.clamped);
            this->_trafficLights->turnGreen(this->_socket->info().greenLightInfo.clamped);
            this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.clamped);
            this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.clamped);
        }
    }

    if (this->_isLocalControlling || !this->_isTurned)
    {
        this->_counter->show("");
    }

    if (this->_isLocalControlling)
    {
        if (this->readIRAction())
        {
            this->_trafficLights->turnRed(false);
            this->_trafficLights->turnYellow(false);
            this->_trafficLights->turnGreen(false);

            if (!this->_isTurned)
            {
                this->_trafficLights->turnYellow(true, true);
                return;
            }

            switch (this->_currentLightType)
            {
            case RED:
                this->_trafficLights->turnRed(true);

                this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().redLightInfo.id);
                this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().redLightInfo.id);
                break;
            case YELLOW:
                this->_trafficLights->turnYellow(true);
                this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().yellowLightInfo.id);
                this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().yellowLightInfo.id);
                break;
            case GREEN:
                this->_trafficLights->turnGreen(true);
                this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().greenLightInfo.id);
                this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().greenLightInfo.id);
                break;

            default:
                break;
            }
        }
    }

    this->_trafficLights->loop();

    if (this->_isTurned && !this->_isLocalControlling)
    {
        this->_counter->loop();
        if (this->_counter->remains() < 0)
        {
            this->next();
        }
    }

    if (this->_isStateUpdated)
    {
        this->_isStateUpdated = false;
        this->_socket->writeState(this->_redState, this->_yellowState, this->_greenState, this->_leftGreenState, this->_rightGreenState);
    }
}

void Controller::next()
{
    switch (this->_currentLightType)
    {
    case RED:
        this->_currentLightType = YELLOW;

        this->_trafficLights->turnYellow(true);

        if (!this->_socket->info().redLightInfo.clamped)
            this->_trafficLights->turnRed(false);

        if (this->_socket->info().yellowLightInfo.duration < 60 * 1000 * 60)
            this->_counter->from(this->_socket->info().yellowLightInfo.duration);
        else
            this->_counter->from(10);

        this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().yellowLightInfo.id);
        this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().yellowLightInfo.id);
        break;
    case YELLOW:
        this->_currentLightType = GREEN;

        this->_trafficLights->turnGreen(true);

        if (!this->_socket->info().greenLightInfo.clamped)
            this->_trafficLights->turnYellow(false);

        this->_counter->from(this->_socket->info().greenLightInfo.duration);

        this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().greenLightInfo.id);
        this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().greenLightInfo.id);
        break;
    case GREEN:
        this->_currentLightType = RED;

        this->_trafficLights->turnRed(true);

        if (!this->_socket->info().greenLightInfo.clamped)
            this->_trafficLights->turnGreen(false);

        if (this->_socket->info().redLightInfo.duration < 60 * 1000 * 60)
            this->_counter->from(this->_socket->info().redLightInfo.duration);
        else
            this->_counter->from(10);

        this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().redLightInfo.id);
        this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().redLightInfo.id);
        break;

    default:
        break;
    }
}

void Controller::setState(const bool &red, const bool &yellow, const bool &green, const bool &leftGreen, const bool &rightGreen)
{
    setRedState(red);
    setYellowState(yellow);
    setGreenState(green);
    setLeftGreenState(leftGreen);
    setRightGreenState(rightGreen);
}

void Controller::setRedState(const bool &red)
{
    if (this->_redState != red)
    {
        this->_redState = red;
        this->_isStateUpdated = true;
    }
}

void Controller::setYellowState(const bool &yellow)
{
    if (this->_yellowState != yellow)
    {
        this->_yellowState = yellow;
        this->_isStateUpdated = true;
    }
}

void Controller::setGreenState(const bool &green)
{
    if (this->_greenState != green)
    {
        this->_greenState = green;
        this->_isStateUpdated = true;
    }
}

void Controller::setLeftGreenState(const bool &leftGreen)
{
    if (this->_leftGreenState != leftGreen)
    {
        this->_leftGreenState = leftGreen;
        this->_isStateUpdated = true;
    }
}

void Controller::setRightGreenState(const bool &rightGreen)
{
    if (this->_rightGreenState != rightGreen)
    {
        this->_rightGreenState = rightGreen;
        this->_isStateUpdated = true;
    }
}

bool Controller::readIRAction()
{
    if (this->_irrecv->decode(&results))
    {
        if (results.value == 0x1FE8A75)
            this->_isTurned = !this->_isTurned;
        if (results.value == 0x1FE906F)
            this->_currentLightType = RED;
        if (results.value == 0x1FE2AD5)
            this->_currentLightType = YELLOW;
        if (results.value == 0x1FE8877)
            this->_currentLightType = GREEN;

        this->_irrecv->resume();

        return true;
    }

    return false;
}