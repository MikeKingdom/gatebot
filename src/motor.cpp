#include "motor.h"

Motor::Motor(uint8_t enablePin, uint8_t pin1, uint8_t pin2)
  : _enablePin(enablePin)
  , _pin1(pin1)
  , _pin2(pin2)
{
}

Motor::~Motor()
{}

void Motor::setup()
{
  pinMode(_enablePin, OUTPUT);
  pinMode(_pin1, OUTPUT);
  pinMode(_pin2, OUTPUT);
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

void Motor::forward() {
  digitalWrite(_pin1, HIGH & ENABLE_MOTORS );
  digitalWrite(_pin2, LOW);
}

void Motor::backward() {
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, HIGH & ENABLE_MOTORS);
}

void Motor::off() {
  digitalWrite(_pin1, LOW);
  digitalWrite(_pin2, LOW);
}

void Motor::power(byte power) {
  analogWrite(_enablePin, power);
}
