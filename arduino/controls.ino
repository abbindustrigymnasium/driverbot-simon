#include "controls.h"


Servo servo;
const float servoMidPoint = 90;
const float servoSidePointOffset = 45;

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
void determineDirection(String message)
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
  digitalWrite(motorPinRightDir, HIGH);
  analogWrite(motorPinRightSpeed, 255); // Speed motor
  servo.write(servoMidPoint); // set servo to mid-point
  Serial.println("Forward");
}

void backward()
{
  digitalWrite(motorPinRightDir, LOW);
  analogWrite(motorPinRightSpeed, 255); // Speed motor
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
  digitalWrite(motorPinRightDir, LOW);
  analogWrite(motorPinRightSpeed, 0); // Stop motor
  servo.write(servoMidPoint);
  Serial.println("Stop");
}