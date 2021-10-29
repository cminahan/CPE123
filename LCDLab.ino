//#include <CPLcd.h>


// LCD example that uses the CPLcd library
// HMS - Oct. 2019


#include <CPutil.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <CPLcd.h>

CPLcd myLcd;
const int redLedPin = 7;
Led redLed(redLedPin);
const int buttonPin = 8;
Button myButton(buttonPin);

void setup() {
  
	// Set up serial monitor and print out program info
	Serial.begin(9600);
	setupMessage(__FILE__, "Using the CPLcd library");
	
	myLcd.init();
	
	delay(500);  

  redLed.off();
	
}

void loop()
{
  affirmation();
}

void countButton() 
{
  int buttonCount = 0;
	lcdExamples();
	blinkLed();
  buttonCount = buttonToSerial();
  showNum(buttonCount);
}

void test()
{
  static MSTimer aTimer;
  myLcd.home();
  myLcd.print("hey");
  aTimer.set(10000);
  if(aTimer.done())
  {
    myLcd.clear();
  }
}

void showNum(int num)
{
  static MSTimer LCDTimer;
  CPLcd myLCD;
  if(LCDTimer.done())
  {
    myLCD.home();
    myLCD.print(num);
    LCDTimer.set(300);
  }
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

void blinkLed()
{
  static MSTimer ledTimer;
  static int ledOnFlag = false;

  if (ledTimer.done() == true)
  {
    // reset the timer to 1 second
    ledTimer.set(1000);

    // turn on/off the led
    if (ledOnFlag == false)
    {
      redLed.on();
      ledOnFlag = true;
    }
    else
    {
      redLed.off();
      ledOnFlag = false;
    }
  }
   
}

void lcdExamples()
{
	
	// using the writeRow methods (note writeRow clears to end of line)
	// delays() is used so you can see it work)

  static MSTimer aTimer;
  if(aTimer.done())
  {
   aTimer.set(500);
  }
	

}

int buttonToSerial()
{
  static int buttonCount = 0;

  // Will only recognize its been pushed once per second
  if (myButton.wasPushed() == true)
  {
    buttonCount = buttonCount + 1;
    Serial.print(1);
  
    // The % gives you the reminder of a division, so if the number is divisable by 5 we get 0
    if (buttonCount % 5 == 0)
    {
      print2("\nButton Count is: ", buttonCount);
    }
  }
  
  return buttonCount;
   
}

  
