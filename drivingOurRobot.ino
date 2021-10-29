#include <CPutil.h>

// Simple sketch to just test a motor

// MAKE THIS MATCHES YOUR MOTOR PINS
// The mega pins that go to the motor controller

const int leftMotorPin1 = 4; //left forward
const int leftMotorPin2 = 5; //left backwards
const int rightMotorPin1 = 6; //right forward
const int rightMotorPin2 = 7; //right backwards
const int button1 = 8;

Button button(button1);


void setup() 
{
  motorsSetup();
}


void loop()
{
  drivingControl();
}

void drivingControl()
{
  static MSTimer aTimer;
  enum {START, BUTTON_WAIT, FORWARD3, RIGHT_TURN, FORWARD5, LEFT_TURN, BACKWARDS, SPIN};
  static int state = START;
  int aSpeed = 200;

  switch (state)
  {
    case START:
     if(button.wasPushed())
     {
      state = BUTTON_WAIT;
     }
    break;

    case BUTTON_WAIT:
     if(robotForwardTimed(aSpeed, 3000) == 1)
     {
      state = FORWARD3;
     }
    break;

    case FORWARD3:
     if(robotTurnRightTimed(aSpeed, 2000) == 1)
     {
      state = RIGHT_TURN;
     }
    break;

    case RIGHT_TURN:
     if(robotForwardTimed(aSpeed, 5000) == 1)
     {
      state = FORWARD5;
     }
    break;

    case FORWARD5:
     if(robotTurnLeftTimed(aSpeed, 3000) == 1)
     {
      state = LEFT_TURN;
     }
    break;

    case LEFT_TURN:
     if(robotBackwardsTimed(aSpeed, 1000) == 1)
     {
      state = BACKWARDS;
     }
    break;

    case BACKWARDS:
     if(robotSpin(aSpeed, 500) == 1)
     {
      state = SPIN;
     }
    break;

    case SPIN:
     robotStop();
     state = START;
    break;
  }
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

int robotTurnRightTimed(int aSpeed, int driveTime)
{
  static MSTimer aTimer;
  enum {START, TURN_RIGHT, DONE};
  static int state = START;

  switch (state)
  {
    case START:
     aTimer.set(driveTime);
     robotStop();
     state = TURN_RIGHT;
     return 0;
    break;

    case TURN_RIGHT:
     rightTurn(aSpeed);
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

int robotTurnLeftTimed(int aSpeed, int driveTime)
{
  static MSTimer aTimer;
  enum {START, TURN_LEFT, DONE};
  static int state = START;

  switch (state)
  {
    case START:
     aTimer.set(driveTime);
     robotStop();
     state = TURN_LEFT;
     return 0;
    break;

    case TURN_LEFT:
     leftTurn(aSpeed);
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

int robotBackwardsTimed(int aSpeed, int driveTime)
{
  static MSTimer aTimer;
  enum {START, BACKWARDS, DONE};
  static int state = START;

  switch(state)
  {
    case START:
     aTimer.set(driveTime);
     robotStop();
     state = BACKWARDS;
     return 0;
    break;

    case BACKWARDS:
     robotBackwards(aSpeed);
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

int robotForwardTimed(int aSpeed, int driveTime)
{
  static MSTimer aTimer;
  enum {START, FORWARD, DONE};
  static int state = START;

  switch(state)
  {
    case START:
     aTimer.set(driveTime);
     robotStop();
     state = FORWARD;
     return 0;
    break;

    case FORWARD:
     robotForward(aSpeed);
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

void motorsSetup()
{
   // put your setup code here, to run once:
  Serial.begin(9600);
  
  setupMessage(__FILE__, "Simple Motor Test sketch");
  delay(500);

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
