#include <CPutil.h>

#define NUM_LEDS 5

// Create your hardware
// Change the next statement to use the pins you have
// attached to your Leds (the array below are my led pins)
Led leds[] = {43, 41, 39, 37,35};

void setup() 
{
  Serial.begin(9600);
  setupMessage(__FILE__, "Blinks an LED");
  delay(500);
  
  // intially set LED to off
  ledsOff();
 
}

void loop() 
{ 
   blinkLeds();
}



void blinkLeds()
{
  // note this is not a state machine
  // it uses a toggle flag.
  static MSTimer ledTimer;
  static int ledOnFlag = false;

  if (ledTimer.done() == true)
  {
    // reset the timer to 1 second
    ledTimer.set(1000);

    // turn on/off the led
    if (ledOnFlag == false)
    {
      ledsOn();
      ledOnFlag = true;
    }
    else
    {
      ledsOff();;
      ledOnFlag = false;
    }
  }
}


void ledsOn()
{
	int i = 0;
	
	for (i = 0; i < NUM_LEDS; i++)
	{
		leds[i].on();
	}
}

void ledsOff()
{
	int i = 0;
	
	for (i = 0; i < NUM_LEDS; i++)
	{
		leds[i].off();
	}
}
