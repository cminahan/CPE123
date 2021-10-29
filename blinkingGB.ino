#include "CPutil.h"

// Define your hardware pins
const int led1 = 38;
const int led2 = 7;
const int abutton = 9;

// Create your hardware
Led greenLed(led1);
Led blueLed(led2);
Button button(abutton);

void setup() {
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Press the button...");
  delay(500);
  blueLed.off();
  greenLed.off();
    
}

void loop() {
 
  // Control code to turn on/off LED based on button
   ledControl();
 
}

void ledControl()
{
  static int state = 1;
  if(state == 1)              // state 1 is blue blinking
  {
    if(button.wasPushed())
    {
      blueBlink();
      state = 2;
    }
  }
  else if(state == 2)       // state 2 is green blinking
  {
    if(button.wasPushed())
    {
      blueLed.off();
      greenBlink();
      state = 3;
    }
    else
    {
      blueBlink();
    }
  }
  else if(state == 3)
  {
    if(button.wasPushed())
    {
      greenLed.off();
      blueBlink();
      state = 2;
    }
    else
    {
      greenBlink();
    }
  }
}

void greenBlink()
{
  static int state = 1;
  static MSTimer aTimer;
  if(state == 1)
  {
    if(aTimer.done())
    {
      aTimer.set(1000);
      greenLed.on();
      state = 2;
    }
  }
  else if(state == 2)
  {
    if(aTimer.done())
    {
      aTimer.set(1000);
      greenLed.off();
      state = 1;
    }
  }
}

void blueBlink()
{
  static int state = 1;
  static MSTimer aTimer;
  if(state == 1)
  {
    if(aTimer.done())
    {
      aTimer.set(500);
      blueLed.on();
      state = 2;
    }
  }
  else if(state == 2)
  {
    if(aTimer.done())
    {
      aTimer.set(500);
      blueLed.off();
      state = 1;
    }
  }
}
