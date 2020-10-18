#include "env.h"

#include <Arduino.h>
#include <WiFi.h>

#include "counter/counter.h"
#include "traffic-lights/traffic-lights.h"
#include "socket/socket.h"
#include "controller/controller.h"

const int CLK = 12;
const int DIO = 14;

const int RED_PIN = 16;
const int YELLOW_PIN = 19;
const int GREEN_PIN = 33;
const int LEFT_GREEN_PIN = 25;
const int RIGHT_GREEN_PIN = 26;

const int RECV_PIN = 21;

const int SWITCH_CONTROL_BUTTON_PIN = 2;

Counter counter(CLK, DIO);
TrafficLights trafficLights(RED_PIN, YELLOW_PIN, GREEN_PIN, LEFT_GREEN_PIN, RIGHT_GREEN_PIN);
Socket socket;

Controller controller(&counter, &trafficLights, &socket, RECV_PIN, SWITCH_CONTROL_BUTTON_PIN);

void setup()
{
  Serial.begin(9600);

  while (!Serial)
    ;

  Serial.println("RostiKTawer");

  WiFi.begin(wifi_ssid.c_str(), wifi_password.c_str());
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.println("Wifi is connecting...");
    delay(500);
  }

  Serial.println("Wifi has been connected");
  socket.begin(IPAddress(192, 168, 0, 104), 9000);
}

void loop()
{
  controller.loop();
}