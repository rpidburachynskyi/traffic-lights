#pragma once
#include <string>
#include <WiFi.h>
#include <vector>

class LightInfo
{
public:
    std::wstring id;
    bool spec;
    std::wstring linkWithId; // only if spec == true
    bool clamped;
    int duration;
};

class Info
{
public:
    bool isTurned;
    bool isLocalControlling;

    LightInfo redLightInfo;
    LightInfo yellowLightInfo;
    LightInfo greenLightInfo;
    LightInfo leftGreenLightInfo;
    LightInfo rightGreenLightInfo;
};

class Socket
{
public:
    Socket();
    ~Socket();

    void begin(const IPAddress &ip, const int &port);

    void loop();

    bool hasUpdate();

    Info info();

    void writeState(const bool &redState, const bool &yellowState, const bool &greenState, const bool &leftGreenState, const bool &rightGreenState);

private:
    bool _hasUpdate;
    Info _info;

    WiFiClient *_client;
};