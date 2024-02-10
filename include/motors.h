#ifndef _MOTORS_H
#define _MOTORS_H

#include <Arduino.h>

#define ENABLE_MOTORS 1


class Motors
{
public:
  explicit Motors(uint8_t leftEnable = -1, uint8_t leftPin1 = -1, uint8_t leftPin2 = -1,
    uint8_t rightEnable = -1, uint8_t rightPin1 = -1, uint8_t rightPin2 = -1);
  virtual ~Motors();

  void setup(uint8_t leftEnable, uint8_t leftPin1, uint8_t leftPin2, uint8_t rightEnable, uint8_t rightPin1, uint8_t rightPin2);

  void leftForward();
  void leftBackward();
  void leftOff();
  void leftPower(byte power);
  void rightForward();
  void rightBackward();
  void rightOff();
  void rightPower(byte power);
  
  void forward();
  void backward();
  void rotateLeft();
  void rotateRight();
  void stop();

private:
  uint8_t _leftEnable;
  uint8_t _leftPin1;
  uint8_t _leftPin2;
  uint8_t _rightEnable;
  uint8_t _rightPin1;
  uint8_t _rightPin2;

/*
void leftTest() {
  leftPower(255);
  leftForward();
  //delay(5000);
  //leftOff();
  //delay(500);
  //leftBackward();
  //delay(5000);
  //leftOff();
  //delay(500);
}

void rightTest() {
  rightPower(255);
  rightForward();
   delay(5000);
  //rightOff();
  //delay(500);
  //rightBackward();
  //delay(5000);
  //rightOff();
  //delay(500);
}

void moveTest() {
  leftPower(255);
  rightPower(255);
  forward();
  delay(5000);
  stop();
  delay(500);
  backward();
  delay(5000);
  stop();
  delay(500);
}

void potTest() {
  while(1) {
    Serial.print(map(analogRead(SPEED_PIN), 0, 1023, 0, 255));
    Serial.print("  ");
    Serial.println(map(analogRead(BAT_PIN), 767, 1023, 0, 100));
    delay(50);
  }
}
*/
};
#endif // _MOTORS_H