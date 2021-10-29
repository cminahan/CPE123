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

const int irPin1 = A11;   // right side of robot
const int irPin2 = A12;
const int irPin3 = A13;   // middle of robot
const int irPin4 = A14;
const int irPin5 = A15;   // left side of robot

const int irSensorPins[] = {A11, A12, A13, A14, A15};
Led irSensorLeds[] = {35, 37, 39, 41, 43};


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
 sharpTurn(150);
}

void sharpTurn(int aSpeed)
{
  enum{FOLLOW, RIGHT, LEFT};
  static int state = FOLLOW;

  switch(state)
  {
    case FOLLOW:
     if(determineBWValue() & 16)
     {
      state = RIGHT;
     }
     else if(determineBWValue() & 1)
     {
      state = LEFT;
     }
     else
     {
      curveyLine(aSpeed);
     }
    break;

    case RIGHT:
     if(rightFollow(aSpeed) == true)
     {
      state = FOLLOW;
     }
    break;

    case LEFT:
     if(leftFollow(aSpeed) == true)
     {
      state = FOLLOW;
     }
    break;

    default:
    break;
  }
}


int leftFollow(int aSpeed)
{
  enum{FORWARD, LEFT, FOLLOW};
  static int state = FORWARD;
  int returnValue = false;

  switch(state)
  {
    case FORWARD:
     robotForward(aSpeed);
     state = LEFT;
     returnValue = false;
    break;
    
    case LEFT:
     if(determineBWValue() == 0)
     {
      robotSpinRight(aSpeed);
      state = FOLLOW;
      returnValue = false;
     }
    break;

    case FOLLOW:
     if(determineBWValue() == 4)
     {
      robotStop();
      state = FORWARD;
      returnValue = true;
     }
    break;

    default:
    break;
  }
 return returnValue;
}

int rightFollow(int aSpeed)
{
  enum{FORWARD, RIGHT, FOLLOW};
  static int state = FORWARD;
  int returnValue = false;

  switch(state)
  {
    case FORWARD:
     robotForward(aSpeed);
     state = RIGHT;
     returnValue = false;
    break;
    
    case RIGHT:
     if(determineBWValue() == 0)
     {
      robotSpinLeft(aSpeed);
      state = FOLLOW;
      returnValue = false;
     }
    break;

    case FOLLOW:
     if(determineBWValue() == 4)
     {
      robotStop();
      state = FORWARD;
      returnValue = true;
     }
    break;

    default:
    break;
  }
 return returnValue;
}

void curveyLine(int aSpeed)
{
  
  if(determineBWValue() == 4)
  {
    robotForward(aSpeed);
  }
  else if(determineBWValue() == 2)
  {
    rightTurn(aSpeed);
  }
  else if(determineBWValue() == 6)
  {
    rightTurn(aSpeed);
  }
  else if(determineBWValue() == 8)
  {
    leftTurn(aSpeed);
  }
  else if(determineBWValue() == 12)
  {
    leftTurn(aSpeed);
  }
}

int determineBWValue()
{
  int value[] = {1, 2, 4, 8, 16};
  int BWValue = 0;
  int i = 0;

  for(i = 0; i < 5; i++)
  {
    if(analogRead(irSensorPins[i]) >= 146)
    {
      irSensorLeds[i].on();
      BWValue = BWValue + value[i];
    }
    else
    {
      irSensorLeds[i].off();
    }
  }
  return BWValue;
}
     
void printIR(int aIRPin) 
{
  int irValue = analogRead(aIRPin);   
  
  print4("Mega Pin #: ", aIRPin, " IR sensor value: ", irValue);

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

int robotSpinLeft(int aSpeed)
{
 rightMotorForward(aSpeed);
 leftMotorBackwards(aSpeed);
}

int robotSpinRight(int aSpeed)
{
  rightMotorBackwards(aSpeed);
  leftMotorForward(aSpeed);
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
