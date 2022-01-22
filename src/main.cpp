#include <Arduino.h>
#include "comp_filter.h"
#include "Romi32u4lcd.h"

ComplementaryFilter filter;
Romi32U4LCD lcd;

void setup() 
{
  filter.init();
  
}

void loop() 
{
  static float newAngle = 0;
  bool newReading = filter.calcAngle(newAngle);
  if(newReading)
  {
    Serial.println(newAngle);
      // Clear the screen.
    lcd.clear();

    // Go to the next line.
    lcd.gotoXY(0, 0);

    // Print a number.
    lcd.print(newAngle * 180 / 3.1416);
  }
}



// void loop()
// {
//   // Clear the screen.
//   lcd.clear();

//   // Print a string.
//   lcd.print("hi");

//   // Go to the next line.
//   lcd.gotoXY(0, 1);

//   // Print a number.
//   lcd.print(1234);

//   delay(1000);
// }
