# 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino"
# 2 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino" 2
# 3 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino" 2

# 5 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino" 2
# 6 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\arduino.ino" 2

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
# 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino"
# 2 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino" 2
# 3 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\communications.ino" 2

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
        mqttClientId += String(random(0xffff), 16);
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
# 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino"
# 2 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino" 2
# 3 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.ino" 2

Servo servo;
const float servoMidPoint = 90;
float servoSidePointOffset = 90;
float motorSpeed = 255;




// Set up the motor and servo pins
void setupHardware()
{
  pinMode(0 /* D2*/, 0x01);
  pinMode(5 /* D1*/, 0x01);
  servo.attach(2 /* D4*/);
}

void setMotorSpeed(float newMotorSpeed)
{
  motorSpeed = newMotorSpeed;
}

void setServoAngle(float newServoAngle)
{
  servoSidePointOffset = newServoAngle;
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
  digitalWrite(0 /* D2*/, 1);
  analogWrite(5 /* D1*/, motorSpeed); // Speed motor
  servo.write(servoMidPoint); // set servo to mid-point
  Serial.println("Forward");
}

void backward()
{
  digitalWrite(0 /* D2*/, 0);
  analogWrite(5 /* D1*/, motorSpeed); // Speed motor
  servo.write(servoMidPoint); // set servo to mid-point
  Serial.println("Backward");
}

void turnLeft()
{
  servo.write(servoMidPoint - servoSidePointOffset); // set servo to turn left
  Serial.println("Left");
}

void turnRight()
{
  servo.write(servoMidPoint + servoSidePointOffset); // set servo to turn right
  Serial.println("Right");
}

void stop()
{
  digitalWrite(0 /* D2*/, 0x0);
  analogWrite(5 /* D1*/, 0); // Stop motor
  servo.write(servoMidPoint);
  Serial.println("Stop");
}
