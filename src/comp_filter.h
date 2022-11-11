#ifndef __COMP_FILTER_H
#define __COMP_FILTER_H

#include <Wire.h>
#include <Romi32U4.h>

class ComplementaryFilter
{
 private:
  float EPSILON = 0.001;
  float KAPPA = 0.95;

  float fusedAngle = 0;
  float accAngle = 0;
  float gyroBias = 0;

public: 
  static LSM6 imu; //static to allow multiple filters for comparison

  void init(float kappa, float eps = 0.001);
  bool calcAngle(float&);
  bool calcAngle(float&, float&, float&);
};

#endif
