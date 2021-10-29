#include <CPutil.h>

//Claire Minahan
//Group #1

// Define your pins

const int redLedPin1 = 40;
const int redLedPin2 = 9;
const int yellowLedPin1 = 10;
const int yellowLedPin2 = 11;
const int greenLedPin1 = 12;
const int greenLedPin2 = 13;
const int button1 = 8;

// Create your hardware

Led bigRed(redLedPin1);
Led smallRed(redLedPin2);
Led bigYellow(yellowLedPin1);
Led smallYellow(yellowLedPin2);
Led bigGreen(greenLedPin1);
Led smallGreen(greenLedPin2);
Button button(button1);

void setup() 
{
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Blinks an LED");
  delay(500);
  
  // Initialize your hardware
  bigRed.off();
  smallRed.off();
  bigYellow.off();
  smallYellow.off();
  bigGreen.off();
  smallGreen.off();

}

void loop() 
{
  // put your main code here, to run repeatedly:

/*if(smallStreet() == 1)
{
  delay (500);
  smallStreet();
}
 */

 control();
}

void control()
{
  enum {START, BIG_STREET, SMALL_STREET};
  static int state = START;

  switch (state)
  {
    case START:
     smallRed.on();
     state = BIG_STREET;
    break;
    
    case BIG_STREET:
     if(bigStreet() == 1)
     {
      state = SMALL_STREET;
     }
    break;
    
    case SMALL_STREET:
     if(smallStreet() == 1)
     {
      state = BIG_STREET;
     }
    break;
  }
}

int smallStreet()
{
 enum {START, GREEN, GREEN_TIMER_WAIT, YELLOW, RED};
 static MSTimer aTimer;
 static int state = START;

 switch (state)
 {
  case START:
   aTimer.set(2000);
   state = GREEN;
   return 0;
  break;

  case GREEN:
   if(aTimer.done())
   {
    state = GREEN_TIMER_WAIT;
    smallRed.off();
    return 0;
   }
  break;

  case GREEN_TIMER_WAIT:
   if(aTimer.done())
   {
    state = YELLOW;
    smallGreen.off();
    smallYellow.on();
    smallRed.off();
    aTimer.set(1000);
    return 0;
   }
  break;

  case YELLOW:
   if(aTimer.done())
   {
    state = RED;
    smallRed.on();
    smallYellow.off();
    aTimer.set(1000);
    return 1;
   }
  break;

  case RED:
   if(aTimer.done())
   {
    smallRed.off();
    smallGreen.on();
    aTimer.set(4000);
    state = START;
    return 0;
   }
  break;

  }
}


int bigStreet()
{
  enum {START, GREEN, GREEN_BUTTON_WAIT, GREEN_TIMER_WAIT, YELLOW, RED};
  static MSTimer aTimer;
  static int state = START;
  
  switch (state)
  {
    case START:
     aTimer.set(4000);
     bigGreen.on();
     state = GREEN;
     return 0;
    break;
    
    case GREEN:
     if(aTimer.done())
     {
      state = GREEN_BUTTON_WAIT;
      return 0;
     }
     else if(button.wasPushed())
     {
       state = GREEN_TIMER_WAIT; 
       return 0;
     }
    break;

    case GREEN_BUTTON_WAIT:
     if(button.wasPushed())
     {
      state = YELLOW;
      bigGreen.off();
      bigYellow.on();
      aTimer.set(1000);
      return 0;
     }
    break;

    case GREEN_TIMER_WAIT:
     if(aTimer.done())
     {
      state = YELLOW;
      bigGreen.off();
      bigYellow.on();
      aTimer.set(1000);
      return 0;
     }
    break;

    case YELLOW:
     if(aTimer.done())
     {
      state = RED;
      bigYellow.off();
      bigRed.on();
      aTimer.set(1000);
      return 1;
     }
    break;

    case RED:
     if(aTimer.done())
     {
      state = START;
      aTimer.set(4000);
      bigRed.off();
      bigGreen.on();
      return 0;
     }
    break;
  }
 
}
