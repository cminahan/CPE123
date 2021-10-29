#include <CPutil.h>
#include <CPE123_EncoderLib.h>

// This program tests out the encoders using the encoder library
// This library uses interrupts

// Encoder Pins for Mega board
const int rightEncoderPin1 = 20;
const int rightEncoderPin2 = 21;
const int leftEncoderPin1 = 2;
const int leftEncoderPin2 = 3;

void setup() {
  // put your setup code here, to run once:
   
  // Setup serial monitor
  Serial.begin(9600);
  setupMessage(__FILE__, "Encoder Interupt Test");

  encoderSetup(rightEncoderPin1, rightEncoderPin2, leftEncoderPin1, leftEncoderPin2);
  
   // wait for the board to settle down 
   delay(1000);  

   print2("count for 45: ", calcAngle(90));
   print2("count for 90cm: ", calcDistance(20));
}

void loop() 
{
  outputCounts();
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

void outputCounts()
{
    static MSTimer mainTimer(1000);
  
    if (mainTimer.done() == true)
    {
      mainTimer.set(1000);
      Serial.print(" Left encoder count: ");
      Serial.print(leftEncoderCount());
      Serial.print(" Right encoder count: ");
      Serial.println(rightEncoderCount());
    }
}
