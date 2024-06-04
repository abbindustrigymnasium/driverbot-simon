#line 1 "C:\\Users\\23simsvo\\OneDrive - ABB Gymnasiet\\teknik1\\driverbot-simon\\arduino\\controls.h"
#include <Servo.h>

#define servoPin 2           // D4

extern Servo servo;

// Define servo degree variables
extern const float servoMidPoint;
extern float servoSidePointOffset;

// Define controls.ino functions
void setupHardware();
void setMotorSpeed(float newMotorSpeed);
void setServoAngle(float newServoAngle);
void turnRight();
void determineMovement(String message);
void forward();
void backward();
void turnLeft();
void turnRight();
void stop();