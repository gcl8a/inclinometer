#include "comp_filter.h"

void ComplementaryFilter::init(float kappa, float eps)
{ 
   EPSILON = eps; KAPPA = kappa; 
    Wire.begin();

  if (!imu.init())
  {
    // Failed to detect the LSM6.
    ledRed(1);
    while(1)
    {
      Serial.println(F("Failed to detect the LSM6."));
      delay(100);
    }
  }

  imu.enableDefault();

  imu.setFullScaleGyro(LSM6::GYRO_FS1000);
  imu.setGyroDataOutputRate(LSM6::ODR104);

  imu.setFullScaleAcc(LSM6::ACC_FS16);
  imu.setAccDataOutputRate(LSM6::ODR104);
}

bool ComplementaryFilter::calcAngle(float& newAngle)
{
    float angVel = (imu.dps.y * 3.1416 / 180.0 - gyroBias); //radians / sec
  
    float delta = angVel * 0.0096; // in radians
    
    float predAngle = fusedAngle + delta;
    
    accAngle = atan2(-imu.a.x, imu.a.z); //radians

    fusedAngle = predAngle + KAPPA * (accAngle - predAngle);

    gyroBias -= EPSILON * (accAngle - predAngle) / 0.0096;

    newAngle = fusedAngle;

  return true;
}

bool ComplementaryFilter::calcAngle(float& accCalc, float& newAngle, float& newBias)
{
  bool retVal = false;
  
  if(imu.getStatus() & 0x01)
  {
    retVal = true;

    imu.read();

    float angVel = (imu.dps.y * 3.1416 / 180.0 - gyroBias) ; //radians / sec
    float delta = angVel * 0.0096; //radians
    
    float predAngle = fusedAngle + delta;
    
    accAngle = atan2(-imu.a.x, imu.a.z); //radians

    fusedAngle = KAPPA * predAngle + (1-KAPPA) * accAngle;

    gyroBias += EPSILON * (predAngle - accAngle) / 0.0096;

    //returns
    accCalc = accAngle;
    newAngle = fusedAngle;
    newBias = gyroBias;
  }

  return retVal;
}
