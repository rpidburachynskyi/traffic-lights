#include "controller.h"

#include <Arduino.h>

Controller::Controller(
    Counter *counter,
    TrafficLights *trafficLights,
    Socket *socket,
    const int &recv_pin,
    const int &button_pin) : _isLocalControlling(true),
                             _isTurned(false),
                             _currentLightType(GREEN)
{
    this->_counter = counter;
    this->_trafficLights = trafficLights;
    this->_socket = socket;

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
            Serial.println(this->_isLocalControlling);
        }
    }

    this->_socket->loop();

    if (!this->_isLocalControlling && this->_socket->hasUpdate())
    {
        if (!this->_socket->info().isTurned)
        {
            this->_trafficLights->turnYellow(true);
        }
        else
        {
            this->_trafficLights->turnRed(this->_socket->info().redLightInfo.clamped);
            this->_socket->writeState(this->_socket->info().redLightInfo.clamped);
            Serial.println("Write state");
            this->_trafficLights->turnYellow(this->_socket->info().yellowLightInfo.clamped);
            this->_trafficLights->turnGreen(this->_socket->info().greenLightInfo.clamped);
            this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.clamped);
            this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.clamped);
        }
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
                break;
            case YELLOW:
                this->_trafficLights->turnYellow(true);
                break;
            case GREEN:
                this->_trafficLights->turnGreen(true);
                break;

            default:
                break;
            }
        }
    }

    this->_trafficLights->loop();

    if (!this->_isTurned || this->_isLocalControlling)
        return;

    this->_counter->loop();

    if (this->_counter->remains() < 0)
    {
        this->next();
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

        this->_counter->from(this->_socket->info().redLightInfo.duration);

        this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().redLightInfo.id);
        this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().redLightInfo.id);
        break;
    case YELLOW:
        this->_currentLightType = GREEN;

        this->_trafficLights->turnGreen(true);

        if (!this->_socket->info().yellowLightInfo.clamped)
            this->_trafficLights->turnYellow(false);

        this->_counter->from(this->_socket->info().yellowLightInfo.duration);

        this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().yellowLightInfo.id);
        this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().yellowLightInfo.id);
        break;
    case GREEN:
        this->_currentLightType = RED;

        this->_trafficLights->turnRed(true);

        if (!this->_socket->info().greenLightInfo.clamped)
            this->_trafficLights->turnGreen(false);

        this->_counter->from(this->_socket->info().greenLightInfo.duration);

        this->_trafficLights->turnLeftGreen(this->_socket->info().leftGreenLightInfo.linkWithId == this->_socket->info().greenLightInfo.id);
        this->_trafficLights->turnRightGreen(this->_socket->info().rightGreenLightInfo.linkWithId == this->_socket->info().greenLightInfo.id);
        break;

    default:
        break;
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