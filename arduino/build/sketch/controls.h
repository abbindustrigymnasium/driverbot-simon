#line 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.h"
#include <Servo.h>

#define motorPinRightDir 0   // D2
#define motorPinRightSpeed 5 // D1
#define servoPin 2           // D4

extern Servo servo;

// Define servo degree variables
extern const float servoMidPoint;
extern const float servoSidePointOffset;

// Define controls.ino functions
void setupHardware();
void turnRight();
void determineDirection(String message);
void forward();
void backward();
void turnLeft();
void turnRight();
void stop();