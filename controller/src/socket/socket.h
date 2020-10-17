#pragma once
#include <string>
#include <WiFi.h>

class Info
{
public:
    bool isTurned;
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

private:
    Info _info;

    WiFiClient *_client;
};