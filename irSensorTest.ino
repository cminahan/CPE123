//  Code to test out the analog IR sensors - HMS Fall 17

#include <CPutil.h>

// Define your pins (note the number on the pin name specifies
// the sensor number on the IR Sensor board)
const int irPin1 = A11;   // right side of robot
const int irPin2 = A12;
const int irPin3 = A13;   // middle of robot
const int irPin4 = A14;
const int irPin5 = A15;   // left side of robot

const int irSensorPins[] = {A11, A12, A13, A14, A15};
Led irSensorLeds[] = {53, 51, 49, 47, 45};

void setup() 
{
   Serial.begin(9600);
   setupMessage(__FILE__, "IR Sensor testing");
   delay(500);

   
       
}

void loop() 
{
	determineBWValue();
}
       
void testIRSensors()
{
	static MSTimer aDelay(1000);

	if (aDelay.done())
	{
		aDelay.set(1000);
		Serial.print("\n\n");
		printIR(irPin1);
		printIR(irPin2);
		printIR(irPin3);
		printIR(irPin4);
		printIR(irPin5);
	}
}

int determineBWValue()
{
  int value[] = {1, 2, 4, 8, 16};
  int BMValue = 0;
  int i = 0;

  for(i = 0; i < 5; i++)
  {
    if(analogRead(irSensorPins[i]) >= 146)
    {
      irSensorLeds[i].on();
      BMValue = BMValue + value[i];
    }
    else
    {
      irSensorLeds[i].off();
    }
  }
  return BMValue;
}
     
void printIR(int aIRPin) 
{
  int irValue = analogRead(aIRPin);   
  
  print4("Mega Pin #: ", aIRPin, " IR sensor value: ", irValue);

}          
