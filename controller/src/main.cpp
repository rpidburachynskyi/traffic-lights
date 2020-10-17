#include <Arduino.h>

#include "counter/counter.h"
#include "traffic-lights/traffic-lights.h"
#include "controller/controller.h"

const int CLK = 12;
const int DIO = 14;

const int RED_PIN = 16;
const int YELLOW_PIN = 32;
const int GREEN_PIN = 33;
const int LEFT_GREEN_PIN = 25;
const int RIGHT_GREEN_PIN = 26;

Counter counter(CLK, DIO);
TrafficLights trafficLights(RED_PIN, YELLOW_PIN, GREEN_PIN, LEFT_GREEN_PIN, RIGHT_GREEN_PIN);
Controller controller(&counter, &trafficLights);

void setup()
{
  Serial.begin(9600);
  Serial.println("RostiKTawer");
}

void loop()
{
  controller.loop();
}