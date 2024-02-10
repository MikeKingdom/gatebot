#include "motors.h"

Motors::Motors(uint8_t leftEnable, uint8_t leftPin1, uint8_t leftPin2, uint8_t rightEnable, uint8_t rightPin1, uint8_t rightPin2)
  : _leftEnable(0)
  , _leftPin1(0)
  , _leftPin2(0)
  , _rightEnable(0)
  , _rightPin1(0)
  , _rightPin2(0)
{
  setup(leftEnable, leftPin1, leftPin2, rightEnable, rightPin1, rightPin2);
}

Motors::~Motors()
{}

void Motors::setup(uint8_t leftEnable, uint8_t leftPin1, uint8_t leftPin2, uint8_t rightEnable, uint8_t rightPin1, uint8_t rightPin2)
{
  if (leftEnable >= 0) {
    _leftEnable = leftEnable;
    _leftPin1 = leftPin1;
    _leftPin2 = leftPin2;
    _rightEnable = rightEnable;
    _rightPin1 = rightPin1;
    _rightPin2 = rightPin2;

    pinMode(_leftEnable, OUTPUT);
    pinMode(_leftPin1, OUTPUT);
    pinMode(_leftPin2, OUTPUT);
    pinMode(_rightEnable, OUTPUT);
    pinMode(_rightPin1, OUTPUT);
    pinMode(_rightPin2, OUTPUT);
    digitalWrite(_leftPin1, LOW);
    digitalWrite(_leftPin2, LOW);
    digitalWrite(_rightPin1, LOW);
    digitalWrite(_rightPin2, LOW);
  }
}

void Motors::leftForward() {
  digitalWrite(_leftPin1, HIGH & ENABLE_MOTORS );
  digitalWrite(_leftPin2, LOW);
}

void Motors::leftBackward() {
  digitalWrite(_leftPin1, LOW);
  digitalWrite(_leftPin2, HIGH & ENABLE_MOTORS);
}

void Motors::leftOff() {
  digitalWrite(_leftPin1, LOW);
  digitalWrite(_leftPin2, LOW);
}

void Motors::leftPower(byte power) {
  analogWrite(_leftEnable, power);
}

void Motors::rightPower(byte power) {
  analogWrite(_rightEnable, power);
}

void Motors::rightForward() {
  digitalWrite(_rightPin1, HIGH & ENABLE_MOTORS);
  digitalWrite(_rightPin2, LOW);
}

void Motors::rightBackward() {
  digitalWrite(_rightPin1, LOW);
  digitalWrite(_rightPin2, HIGH & ENABLE_MOTORS);
}

void Motors::rightOff() {
  digitalWrite(_rightPin1, LOW);
  digitalWrite(_rightPin2, LOW);
}

void Motors::forward() {
  leftForward();
  rightForward();
}

void Motors::backward() {
  leftBackward();
  rightBackward();
}

void Motors::rotateLeft() {
  leftBackward();
  rightForward();
}

void Motors::rotateRight() {
  leftForward();
  rightBackward();
}

void Motors::stop() {
  leftOff();
  rightOff();
}