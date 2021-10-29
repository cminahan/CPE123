#include <CPutil.h>
#include <CPE123_EncoderLib.h>

//Claire Minahan
//Team #1

// This program tests out the encoders using the encoder library
// This library uses interrupts

// Encoder Pins for Mega board
const int rightEncoderPin1 = 3;
const int rightEncoderPin2 = 2;
const int leftEncoderPin1 = 20;
const int leftEncoderPin2 = 21;

const int leftMotorPin1 = 4; //left forward
const int leftMotorPin2 = 5; //left backwards
const int rightMotorPin1 = 6; //right forward
const int rightMotorPin2 = 7; //right backwards
const int button1 = 9;

Button button(button1);

void motorsSetup()
{
 
   // Initalize the pins for output 
   pinMode(leftMotorPin1, OUTPUT);
   pinMode(leftMotorPin2, OUTPUT); 
   pinMode(rightMotorPin1, OUTPUT); 
   pinMode(rightMotorPin2, OUTPUT); 

    // Stop the motor
   analogWrite(leftMotorPin1, 0);
   analogWrite(leftMotorPin2, 0);
   analogWrite(rightMotorPin1, 0);
   analogWrite(rightMotorPin2, 0);

   robotStop();
    
}

void setup() 
{
    // put your setup code here, to run once:
  Serial.begin(9600);
  
  setupMessage(__FILE__, "Simple Motor Test sketch");
  delay(500);

  motorsSetup();
  encoderSetup(rightEncoderPin1, rightEncoderPin2, leftEncoderPin1, leftEncoderPin2); 
}

void loop()
{
 driveRobot();
}

void driveRobot()
{
  int aSpeed = 200;
  enum{START, BUTTON_WAIT, STRAIGHT_100, LEFT_45, STRAIGHT_40, RIGHT_90, STRAIGHT_50, RIGHT_45, STRAIGHT_502, STOP};
  static int state = START;
  switch(state)
  {
    case START:
     waitOnButton(button);
     state = BUTTON_WAIT;
    break;

    case BUTTON_WAIT:
     if(button.wasPushed())
     {
      state = STRAIGHT_100;
     }

    case STRAIGHT_100:
     if(robotForwardAtDistance(100, aSpeed) == 1)
     {
      state = LEFT_45;
     }
    break;

    case LEFT_45:
     if(robotLeftAtAngle(45, aSpeed) == 1)
     {
      state = STRAIGHT_40;
     }
    break;

    case STRAIGHT_40:
     if(robotForwardAtDistance(40, aSpeed) == 1)
     {
      state = RIGHT_90;
     }
     break;

    case RIGHT_90:
     if(robotRightAtAngle(90, aSpeed) == 1)
     {
      state = STRAIGHT_50;
     }
    break;

    case STRAIGHT_50:
     if(robotForwardAtDistance(50,aSpeed) == 1)
     {
      state = RIGHT_45;
     }
    break;

    case RIGHT_45:
     if(robotRightAtAngle(45, aSpeed) == 1)
     {
      state = STOP;
     }
    break;

    case STOP:
     robotStop();
     state = START;
    break;
  }
}

void waitOnButton(Button & aButton)
{
  Serial.println("Waiting on button push");
  while(aButton.wasPushed() == false)
  {}
}

int robotBackwardsAtDistance(int distanceInCM, int aSpeed)
{
  unsigned long distance = 0;
  static unsigned long thouEnd = 0;
  int returnValue = false;
  enum{START, STOP, MOVE};
  static int state = START;
  switch(state)
  {
    case START:
     robotStop();
     distance = calcDistance(distanceInCM);
     thouEnd = distance + rightEncoderCount();
     state = STOP;
     returnValue = false;
    break;

    case STOP:
     robotBackwards(aSpeed);
     state = MOVE;
     returnValue = false;
    break;

    case MOVE:
     if(rightEncoderCount() >= thouEnd)
     {
      state = START;
      robotStop();
      returnValue = true;
     }
    break;
  }
  return returnValue;
}

int robotForwardAtDistance(int distanceInCM, int aSpeed)
{
  unsigned long distance = 0;
  static unsigned long thouEnd = 0;
  int returnValue = false;
  enum{START, STOP, MOVE};
  static int state = START;
  switch(state)
  {
    case START:
     robotStop();
     distance = calcDistance(distanceInCM);
     thouEnd = distance + rightEncoderCount();
     state = STOP;
     returnValue = false;
    break;

    case STOP:
     robotForward(aSpeed);
     state = MOVE;
     returnValue = false;
    break;

    case MOVE:
     if(rightEncoderCount() >= thouEnd)
     {
      state = START;
      robotStop();
      returnValue = true;
     }
    break;
  }
  return returnValue;
}

int robotRightAtAngle(int aAngle, int aSpeed)
{
  unsigned long angle = 0;
  static unsigned long thouEnd = 0;
  int returnValue = false;
  enum{START, STOP, RIGHT};
  static int state = START;
  
  switch(state)
  {
    case START:
     robotStop();
     angle = calcAngle(aAngle);
     state = STOP;
     thouEnd = angle + leftEncoderCount();
     returnValue = false;
    break;

    case STOP:
     rightTurn(aSpeed);
     state = RIGHT;
     returnValue = false;
    break;

    case RIGHT:
     if(leftEncoderCount() >= thouEnd)
     {
      state = START;
      robotStop();
      returnValue = true;
     }
    break;

    default:
    break;
  }
  return returnValue;
}

int robotLeftAtAngle(int aAngle, int aSpeed)
{
  unsigned long angle = 0;
  static unsigned long thouEnd = 0;
  int returnValue = false;
  enum{START, STOP, LEFT};
  static int state = START;
  
  switch(state)
  {
    case START:
     robotStop();
     angle = calcAngle(aAngle);
     state = STOP;
     thouEnd = angle + rightEncoderCount();
     returnValue = false;
    break;

    case STOP:
     leftTurn(aSpeed);
     state = LEFT;
     returnValue = false;
    break;

    case LEFT:
     if(rightEncoderCount() >= thouEnd)
     {
      state = START;
      robotStop();
      returnValue = true;
     }
    break;

    default:
    break;
  }
  return returnValue;
}

unsigned long calcAngle(int aAngle)
{
  unsigned long clicks = 0;
  clicks = aAngle*44;
  return clicks;
}

unsigned long calcDistance (int aDistance)
{
  unsigned long clicks = 0;
  clicks = aDistance*112;
  return clicks;
}

int robotSpin(int spinTime, int aSpeed)
{
  static MSTimer aTimer;
  enum {START, SPIN, DONE};
  static int state = START;

  switch (state)
  {
    case START:
     aTimer.set(spinTime);
     robotStop();
     state = SPIN;
     return 0;
    break;

    case SPIN:
     rightMotorForward(aSpeed);
     leftMotorBackwards(aSpeed);
     if(aTimer.done())
     {
      state = DONE;
     }
     return 0;
    break;

    case DONE:
     robotStop();
     return 1;
    break;
     
  }
}

void robotStop()
{
  leftMotorStop();
  rightMotorStop();
}

void leftTurn(int aSpeed)
{
  leftMotorStop();
  rightMotorForward(aSpeed);
}

void rightTurn(int aSpeed)
{
  rightMotorStop();
  leftMotorForward(aSpeed);
}

void robotBackwards(int aSpeed)
{
  rightMotorBackwards(aSpeed);
  leftMotorBackwards(aSpeed);
}

void robotForward(int aSpeed)
{
  rightMotorForward(aSpeed);
  leftMotorForward(aSpeed);
}

void rightMotorBackwards(int aSpeed)
{
  motorControl(rightMotorPin2, rightMotorPin1, aSpeed);
}

void leftMotorBackwards(int aSpeed)
{
  motorControl(leftMotorPin2, leftMotorPin1, aSpeed);
}

void rightMotorForward(int aSpeed)
{
  motorControl(rightMotorPin1, rightMotorPin2, aSpeed);
}

void leftMotorForward(int aSpeed)
{
  motorControl(leftMotorPin1, leftMotorPin2, aSpeed);
}

void rightMotorStop()
{
  motorControl(rightMotorPin1, rightMotorPin2, 0);
}

void leftMotorStop()
{
  motorControl(leftMotorPin1, leftMotorPin2, 0);
}

void motorControl(int pin1, int pin2, int aSpeed)
{
  analogWrite(pin1, aSpeed);
  analogWrite(pin2, 0);
}

void motorTest()
{
   analogWrite(leftMotorPin1, 250);
   analogWrite(leftMotorPin2, 0);
   analogWrite(rightMotorPin1, 250);
   analogWrite(rightMotorPin2, 0);
  
   delay(5000);
 
    // Stop the motor
   analogWrite(leftMotorPin1, 0);
   analogWrite(leftMotorPin2, 0);
   analogWrite(rightMotorPin1, 0);
   analogWrite(rightMotorPin2, 0);
 
  delay(2000);
}
