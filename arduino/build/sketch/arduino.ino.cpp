#include <Arduino.h>
#line 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino"
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include "controls.h"
#include "communications.h"

#line 7 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino"
void setup();
#line 15 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino"
void loop();
#line 16 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
void setupCommunications();
#line 45 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
void communicationsLifeCycleLoop();
#line 58 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
void receiveMessage(char *topic, byte *payload, unsigned int length);
#line 76 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
void reconnect();
#line 104 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
void publishData(float motorSpeed);
#line 13 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void setupHardware();
#line 26 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void determineMovement(String message);
#line 74 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void forward();
#line 83 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void backward();
#line 92 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void turnLeft();
#line 99 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void turnRight();
#line 106 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
void stop();
#line 7 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino"
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

// #define motorPinRightDir  0//D2
// #define motorPinRightSpeed 5//D1

// void setup() {
//   // put your setup code here, to run once:
//   pinMode(motorPinRightDir, OUTPUT);
//   pinMode(motorPinRightSpeed, OUTPUT);

//   Serial.begin(115200);
// }

// void loop() {
//   int speed = 1024;
//   int dir = 0;

//   delay(2200);
//   digitalWrite(motorPinRightDir, dir);
//   analogWrite(motorPinRightSpeed, speed);
//       delay(2200);      
//   digitalWrite(motorPinRightDir, 1);
//   analogWrite(motorPinRightSpeed, speed);
// }
#line 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
#include "communications.h"
#include "controls.h"

const char *ssid = "ABB_Gym_IOT";
const char *password = "Welcome2abb";
const char *mqtt_server = "3.121.8.173"; // hiveMQ
const String directionTopic = "simon.svoboda@hitachigymnasiet.se/direction";
const String dataTopic = "simon.svoboda@hitachigymnasiet.se/data";
const String offlineTopic = "simon.svoboda@hitachigymnasiet.se/offline";

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
    if (String(topic) == offlineTopic)
    {
        Serial.println("Publisher Offline");
        stop();
    }

    // Parse the payload
    String message;
    for (int i = 0; i < length; i++)
    {
        message += (char)payload[i];
    }
    Serial.println(message);
    determineMovement(message);
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

void publishData(float motorSpeed)
{
    float rpm = motorSpeed / 100;
    mqttClient.publish(dataTopic.c_str(), String(rpm).c_str());
}
#line 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
#include "controls.h"
#include "communications.h"

Servo servo;
const float servoMidPoint = 90;
const float servoSidePointOffset = 90;
const float motorSpeed = 255;

#define motorPinRightDir 0   // D2
#define motorPinRightSpeed 5 // D1

// Set up the motor and servo pins
void setupHardware()
{
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  servo.attach(servoPin);
}

// Determine the direction based on the mqtt payload
// n = north/forward
// s = south/backwards
// w = west/left
// e = east/right
// stop = stop
void determineMovement(String message)
{
  if (message == "n")
  {
    forward();
  }
  else if (message == "s")
  {
    backward();
  }
  else if (message == "w")
  {
    turnLeft();
  }
  else if (message == "e")
  {
    turnRight();
  }
  else if (message == "ne")
  {
    forward();
    turnRight();
  }
  else if (message == "nw")
  {
    forward();
    turnLeft();
  }
  else if (message == "se")
  {
    backward();
    turnRight();
  }
  else if (message == "sw")
  {
    backward();
    turnLeft();
  }
  else if (message == "stop")
  {
    stop();
  }
  else
  {
    Serial.println("Invalid direction");
  }
}

void forward()
{
  digitalWrite(motorPinRightDir, 1);
  analogWrite(motorPinRightSpeed, motorSpeed); // Speed motor
  publishData(motorSpeed);
  servo.write(servoMidPoint); // set servo to mid-point
  Serial.println("Forward");
}

void backward()
{
  digitalWrite(motorPinRightDir, 0);
  analogWrite(motorPinRightSpeed, motorSpeed); // Speed motor
  publishData(motorSpeed);
  servo.write(servoMidPoint); // set servo to mid-point
  Serial.println("Backward");
}

void turnLeft()
{
  servo.write(servoMidPoint - servoSidePointOffset); // set servo to turn left
  publishData(motorSpeed);
  Serial.println("Left");
}

void turnRight()
{
  servo.write(servoMidPoint + servoSidePointOffset); // set servo to turn right
  publishData(motorSpeed);
  Serial.println("Right");
}

void stop()
{
  digitalWrite(motorPinRightDir, LOW);
  analogWrite(motorPinRightSpeed, 0); // Stop motor
  publishData(0);
  servo.write(servoMidPoint);
  Serial.println("Stop");
}
