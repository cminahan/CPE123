// LCD example that uses the CPLcd library
// HMS - Oct. 2019

#include <CPutil.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CPLcd.h>

CPLcd myLcd;
const int buttonPin = 8;
Button myButton(buttonPin);

void setup() {
  
	// Set up serial monitor and print out program info
	Serial.begin(9600);
	setupMessage(__FILE__, "Using the CPLcd library");
	
	myLcd.init();
	
	delay(500);  

//  redLed.off();
	
}

void loop()
{
  affirmation();
}

int affirmation()
{
  int returnValue = 0;
  static MSTimer aTimer;
  enum{ONE, TWO, THREE, FOUR, FIVE};
  static int state = ONE;
  switch(state)
  {
    case ONE:
     if(aTimer.done())
      {
        myLcd.clear();
      }
     if(myButton.wasPushed())
     {
      returnValue = 5;
      myLcd.home();
      myLcd.print("Ur not an ugly shit");
      aTimer.set(10000);
      state = TWO;
     }
    break;

    case TWO:
     if(aTimer.done())
      {
        myLcd.clear();
      }
     if(myButton.wasPushed())
     {
      returnValue = 5;
      myLcd.home();
      myLcd.print("your time is almost up");
      aTimer.set(10000);
      state = THREE;
     }
    break;

    case THREE:
     if(aTimer.done())
      {
        myLcd.clear();
      }
     if(myButton.wasPushed())
     {
      returnValue = 5;
      myLcd.home();
      myLcd.print("100 is not that old!");
      aTimer.set(10000);
      state = FOUR;
     }
    break;

    case FOUR:
     if(aTimer.done())
      {
        myLcd.clear();
      }
     if(myButton.wasPushed())
     {
      returnValue = 5;
      myLcd.home();
      myLcd.print("somebody will love you?");
      aTimer.set(10000);
      state = FIVE;
     }
    break;

    case FIVE:
     if(aTimer.done())
      {
        myLcd.clear();
      }
     if(myButton.wasPushed())
     {
      returnValue = 5;
      myLcd.home();
      myLcd.print("get ready to die");
      aTimer.set(10000);
      state = ONE;
     }
    break;
  }
  return returnValue;
}
