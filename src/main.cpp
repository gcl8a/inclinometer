#include <Arduino.h>
#include "comp_filter.h"
#include "Romi32u4lcd.h"

ComplementaryFilter filter;
ComplementaryFilter filter_gyro;
ComplementaryFilter filter_accel;

Romi32U4LCD lcd;

LSM6 ComplementaryFilter::imu;

void setup() 
{
  filter.init(0.5);
  filter_gyro.init(0.97);
  filter_accel.init(0);
}

void loop() 
{

  if(filter.imu.getStatus() & 0x01)
  {
    filter.imu.read();

    static float newAngle = 0;
    filter.calcAngle(newAngle);

    static float newAccelAngle = 0;
    filter_accel.calcAngle(newAccelAngle);

    static float newGyroAngle = 0;
    filter_gyro.calcAngle(newGyroAngle);
  
    Serial.print(newAccelAngle * 180 / 3.1416);
    Serial.print('\t');
    Serial.print(newAngle * 180 / 3.1416);
    Serial.print('\t');
    Serial.print(newGyroAngle * 180 / 3.1416);
    Serial.print('\n');
    // Clear the screen
    lcd.clear();

    // Set to first line
    lcd.gotoXY(0, 0);

    // Print the angle
    int printAngle = newAngle * 180.0 / 3.1416;
    lcd.print(printAngle);
    lcd.print(" deg");
  }
}
