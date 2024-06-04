#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "controls.h"
#include "communications.h"

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting up");
  setupCommunications();
  setupHardware();
}

void loop()
{
  communicationsLifeCycleLoop();
}