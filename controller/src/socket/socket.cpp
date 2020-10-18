#include "socket.h"
#include "../lib/JSON/JSON.h"
#include "controller/controller.h"

Socket::Socket(Controller *controller) : _hasUpdate(false)
{
    this->_client = new WiFiClient();
    this->_controller = controller;
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

        if (data == "RESTART")
        {
            this->_controller->restart();
            return;
        }

        JSONValue *value = JSON::Parse(data.c_str());
        JSONObject root = value->AsObject();

        this->_info.isTurned = root[L"isTurned"]->AsBool();
        this->_info.isLocalControlling = root[L"isLocalControlling"]->AsBool();

        JSONArray lights = root[L"lights"]->AsArray();

        LightInfo *lightInfos[] = {
            &this->_info.redLightInfo,
            &this->_info.yellowLightInfo,
            &this->_info.greenLightInfo,
            &this->_info.leftGreenLightInfo,
            &this->_info.rightGreenLightInfo};

        for (int i = 0; i < lights.size(); i++)
        {
            JSONObject lightInfo = lights[i]->AsObject();

            lightInfos[i]->id = lightInfo[L"id"]->AsString();
            lightInfos[i]->clamped = lightInfo[L"clamped"]->AsBool();
            lightInfos[i]->duration = lightInfo[L"duration"]->AsNumber();
            lightInfos[i]->spec = lightInfo[L"spec"]->AsBool();
            lightInfos[i]->linkWithId = lightInfo[L"linksWithId"]->AsString();
        }

        this->_hasUpdate = true;

        delete value;
    }
}

void Socket::writeState(const bool &redState, const bool &yellowState, const bool &greenState, const bool &leftGreenState, const bool &rightGreenState)
{
    JSONObject root;

    root[L"red"] = new JSONValue(redState);
    root[L"yellow"] = new JSONValue(yellowState);
    root[L"green"] = new JSONValue(greenState);
    root[L"leftGreen"] = new JSONValue(leftGreenState);
    root[L"rightGreen"] = new JSONValue(rightGreenState);

    JSONValue *rootValue = new JSONValue(root);

    std::wstring doc = JSON::Stringify(rootValue);

    std::string res;

    res.assign(doc.begin(), doc.end());

    this->_client->write(res.c_str());

    delete rootValue;
}

bool Socket::hasUpdate()
{
    if (this->_hasUpdate)
    {
        this->_hasUpdate = false;
        return true;
    }
    return false;
}

Info Socket::info()
{
    return this->_info;
}