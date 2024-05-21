#line 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.h"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

extern const char *ssid;
extern const char *password;
extern const char *mqtt_server; // hiveMQ
extern const String directionTopic;
extern const String offlineTopic;

extern WiFiClient espClient;
extern PubSubClient mqttClient;

void setupCommunications();
void communicationsLifeCycleLoop();
void receiveMessage(char *topic, byte *payload, unsigned int length);
void reconnect();