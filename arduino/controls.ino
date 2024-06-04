#include "controls.h"
#include "communications.h"

Servo servo;
const float servoMidPoint = 90;
float servoSidePointOffset = 90;
float motorSpeed = 255;

#define motorPinRightDir 0   // D2
#define motorPinRightSpeed 5 // D1

// Set up the motor and servo pins
void setupHardware()
{
  pinMode(motorPinRightDir, OUTPUT);
  pinMode(motorPinRightSpeed, OUTPUT);
  servo.attach(servoPin);
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
  digitalWrite(motorPinRightDir, 1);
  analogWrite(motorPinRightSpeed, motorSpeed); // Speed motor
  servo.write(servoMidPoint); // set servo to mid-point
  Serial.println("Forward");
}

void backward()
{
  digitalWrite(motorPinRightDir, 0);
  analogWrite(motorPinRightSpeed, motorSpeed); // Speed motor
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