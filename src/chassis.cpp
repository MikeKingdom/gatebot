#include "chassis.h"

Chassis::Chassis(Motor &leftMotor, Motor &rightMotor)
  : _leftMotor(leftMotor)
  , _rightMotor(rightMotor)
  {

  }

Chassis::~Chassis()
{}

void Chassis::setup()
{
  _leftMotor.setup();
  _rightMotor.setup();
}

void Chassis::forward() {
  _leftMotor.forward();
  _rightMotor.forward();
}

void Chassis::backward() {
  _leftMotor.backward();
  _rightMotor.backward();
}

void Chassis::rotateLeft() {
  _leftMotor.backward();
  _rightMotor.forward();
}

void Chassis::rotateRight() {
  _leftMotor.forward();
  _rightMotor.backward();
}

void Chassis::stop() {
  _leftMotor.off();
  _rightMotor.off();
}

void Chassis::power(byte power) {
  _leftMotor.power(power);
  _rightMotor.power(power);
}
