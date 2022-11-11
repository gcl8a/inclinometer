#ifndef __COMP_FILTER_H
#define __COMP_FILTER_H

#include <Wire.h>
#include <Romi32U4.h>

class ComplementaryFilter
{
 private:
  const float EPSILON = 0.001;
  

  float fusedAngle = 0;
  float accAngle = 0;
  float gyroBias = 0;

public: 
  static LSM6 imu;
  void init(void);
  bool calcAngle(float&);
  bool calcAngle(float&, float&, float&);

  float KAPPA;
};

#endif
