#include "communications.h"
#include "controls.h"

const char *ssid = "ABB_Gym_IOT";
const char *password = "Welcome2abb";
const char *mqtt_server = "3.121.8.173"; // hiveMQ
const String directionTopic = "simon.svoboda@hitachigymnasiet.se/direction";
const String dataTopic = "simon.svoboda@hitachigymnasiet.se/data";
const String offlineTopic = "simon.svoboda@hitachigymnasiet.se/offline";
const String motorSpeedTopic = "simon.svoboda@hitachigymnasiet.se/motorSpeed";
const String servoAngleTopic = "simon.svoboda@hitachigymnasiet.se/servoAngle";

unsigned int ticks = 0;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void setupCommunications()
{
    // Connect to WiFi
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }

    randomSeed(micros());

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    // MQTT setup
    mqttClient.setServer(mqtt_server, 1883);
    mqttClient.setCallback(receiveMessage);

    Serial.println("Setup complete");
}

// Reconnect to MQTT server if disconnected
void communicationsLifeCycleLoop()
{
    if (!mqttClient.connected())
    {
        Serial.println("MQTT Disconnected");
        reconnect();
    }
    mqttClient.loop();

    ticks++;
}

void receiveMessage(char *topic, byte *payload, unsigned int length)
{
    // Check if the message is an offline message
    Serial.println(topic);
    if (String(topic) == offlineTopic)
    {
        Serial.println("Publisher Offline");
        stop();
    }

    // Parse the message
    String message;
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.println(message);

    // Check if the message is a motor speed, servo angle message or a direction message
    if (String(topic) == motorSpeedTopic)
    {
        setMotorSpeed(message.toFloat());
    }
    else if (String(topic) == servoAngleTopic)
    {
        setServoAngle(message.toFloat());
    }
    else
    {
        determineMovement(message);
    }
}

void reconnect()
{
    // Loop until mqtt client is connected
    while (!mqttClient.connected())
    {
        Serial.print("Attempting MQTT connection...");
        // Create a random Client ID
        String mqttClientId = "ESP8266Client-";
        mqttClientId += String(random(0xffff), HEX);
        // Attempt to connect
        if (mqttClient.connect(mqttClientId.c_str()))
        {
            Serial.println("connected");
            // ... and resubscribe
            mqttClient.subscribe(directionTopic.c_str());
            mqttClient.subscribe(offlineTopic.c_str());
            mqttClient.subscribe(motorSpeedTopic.c_str());
            mqttClient.subscribe(servoAngleTopic.c_str());
        }
        else
        {
            Serial.print("failed, rc=");
            Serial.print(mqttClient.state());
            Serial.println(" try again in 5 seconds");
            // Wait 5 seconds before retrying
            delay(5000);
        }
    }
}