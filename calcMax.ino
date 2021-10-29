#include "CPutil.h"

// Define your hardware pins


// Create your hardware


void setup() {
  
  // Set up serial monitor and print out program info
  Serial.begin(9600);
  setupMessage(__FILE__, "Reads from Serial and outputs its ASCII value (computer value)");
  delay(500);
  
  Serial.println("\nThis program outputs your letter in the value stored by the computer");
  Serial.println("This is called is ASCII value and is standard across all computers");
  Serial.println("e.g. C = 67 and a = 97... type any letter and see");
  
  // Initialize your hardware
    
}

void loop() {
 
  // Read/Write to serial connection
   negNumCount();
 
}

void negNumCount()
{
	
	int count = 0;
  int someNum = 1;

  while(someNum != 0)
  {
    if(Serial.available())
    {
      someNum = Serial.parseInt();
      if(someNum < 0)
      {
        count ++;
      }
    }
  }
  Serial.println(count);
}
