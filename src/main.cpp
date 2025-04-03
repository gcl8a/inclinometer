#include <Arduino.h>
#include <comp_filter.h>

ComplementaryFilter filter;
ComplementaryFilter filter_gyro;
ComplementaryFilter filter_accel;

LSM6 ComplementaryFilter::imu;

void setup() 
{
  Serial.begin(115200);
  filter.init(0.02, 0.001);
  filter_gyro.init(0, 0);
  filter_accel.init(1);
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
  
    Serial.print('>');
    Serial.print("accel:");
    Serial.print(newAccelAngle * 180 / 3.1416);
    Serial.print('\n');
    Serial.print('>');
    Serial.print("gyro:");
    Serial.print(newGyroAngle * 180 / 3.1416);
    Serial.print('\n');
    Serial.print('>');
    Serial.print("fused:");
    Serial.print(newAngle * 180 / 3.1416);
    Serial.print('\n');
  }
}