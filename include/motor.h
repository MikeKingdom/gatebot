#ifndef _MOTOR_H
#define _MOTOR_H

#include <Arduino.h>

#define ENABLE_MOTORS 1

class Motor {
public:
  explicit Motor(uint8_t enablePin, uint8_t pin1, uint8_t pin2);
  virtual ~Motor();

  void setup();
  void forward();
  void backward();
  void off();
  void power(byte power);

private:
  uint8_t _enablePin;
  uint8_t _pin1;
  uint8_t _pin2;
};

#endif // _MOTOR_H