#ifndef _CHASSIS_H
#define _CHASSIS_H

#include "motor.h"

class Chassis {
public:
  explicit Chassis(Motor &leftMotor, Motor &rightMotor);
  virtual ~Chassis();

  void setup();
  void forward(); 
  void backward();
  void rotateLeft();
  void rotateRight();
  void stop();
  void power(byte power);

private:
  Motor &_leftMotor;
  Motor &_rightMotor;
};

#endif // _CHASSIS_H