#include "socket.h"
#include "../lib/JSON/JSON.h"

Socket::Socket()
{
    this->_client = new WiFiClient();
}

Socket::~Socket()
{
    delete this->_client;
}

void Socket::begin(const IPAddress &ip, const int &port)
{
    this->_client->connect(ip, port);
}

void Socket::loop()
{
    if (this->_client->available())
    {
        std::string data = this->_client->readString().c_str();

        Serial.println(data.c_str());
    }
}

bool Socket::hasUpdate()
{
    return false;
}

Info Socket::info()
{
    return this->_info;
}