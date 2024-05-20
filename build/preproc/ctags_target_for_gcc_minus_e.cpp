# 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\motorTest\\motorTest.ino"
# 2 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\motorTest\\motorTest.ino" 2
# 3 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\motorTest\\motorTest.ino" 2
# 4 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\motorTest\\motorTest.ino" 2





const char *ssid = "ABB_Gym_IOT";
const char *password = "Welcome2abb";
const char *mqtt_server = "3.121.8.173"; // test.mosquitto.org
const String directionTopic = "simon.svoboda@hitachigymnasiet.se/direction";

WiFiClient espClient;
PubSubClient client(espClient);
Servo servo;

unsigned long lastMsg = 0;

char msg[(50)];
int value = 0;

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
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
}

void callback(char *topic, byte *payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  String message;
  for (int i = 0; i < length; i++)
  {
    message += (char)payload[i];
  }
  Serial.println(message);
  determineDirection(message);
}

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), 16);
    // Attempt to connect
    if (client.connect(clientId.c_str()))
    {
      Serial.println("connected");
      // ... and resubscribe
      client.subscribe(directionTopic.c_str());
    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(BUILTIN_LED, 0x01); // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pinMode(0 /* D2*/, 0x01);
  pinMode(5 /* D1*/, 0x01);
  servo.attach(2 /* D4*/);
}

void loop()
{

  if (!client.connected())
  {
    reconnect();
  }
  client.loop();
}

void determineDirection(String message)
{
  if (message == "n")
  {
    forward();
  }
  else if (message == "s")
  {
    backwards();
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
    backwards();
    turnRight();
  }
  else if (message == "sw")
  {
    backwards();
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
  digitalWrite(0 /* D2*/, 0x1);
  analogWrite(5 /* D1*/, 255); // Speed motor
  servo.write(90); // set servo to mid-point
  Serial.println("Forward");
}

void backwards()
{
  digitalWrite(0 /* D2*/, 0x0);
  analogWrite(5 /* D1*/, 255); // Speed motor
  servo.write(90); // set servo to mid-point
  Serial.println("Backward");
}

void turnLeft()
{
  servo.write(0); // set servo to minimum
  Serial.println("Left");
}

void turnRight()
{
  servo.write(180); // set servo to maximum
  Serial.println("Right");
}

void stop()
{
  digitalWrite(0 /* D2*/, 0x0);
  analogWrite(5 /* D1*/, 0); // Stop motor
  servo.write(90); // set servo to mid-point
  Serial.println("Stop");
}
