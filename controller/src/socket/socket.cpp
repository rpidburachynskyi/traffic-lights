#include "socket.h"

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
    std::string data = this->_client->readString().c_str();

    if (data.length() != 0)
        Serial.println(data.c_str());
}

bool Socket::hasUpdate()
{
    return false;
}

Info Socket::info()
{
    return this->_info;
}