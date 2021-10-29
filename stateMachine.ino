#include <CPutil.h>

// Define your pins

const int LedPin1 = 38;
const int LedPin2 = 7;
const int button1 = 9;

// Create your hardware

Led led1(LedPin1);
Led led2(LedPin2);
Button button(button1);

void setup() 
{
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Blinks an LED");
  delay(500);
  
  // Initialize your hardware
  led1.off();
  led2.off();
  

}

void loop() 
{
  // put your main code here, to run repeatedly:

   stateMachine();
 
}

void stateMachine()
{
 static int state = 1;
 if(state == 1)                   // state 1 has led 1 on and led 2 off
 {
  if(button.wasPushed())
  {
    led1.on();
    state = 2;
  }
 }
 
 else if(state == 2)              // state 2 has led 1 off and led 2 on
 {
  if(button.wasPushed())
  {
    led1.off();
    led2.on();
    state = 3;
  }
 }
 
 else if(state == 3)              // state 3 has led 1 on and led 2 on
 {
  if(button.wasPushed())
  {
    led1.on();
    state = 4;
  }
 }

 else if(state == 4)              // state 4 has led 1 on and led 2 off
 {
  if(button.wasPushed())
  {
    led2.off();
    state = 2;
  }
 }
}
