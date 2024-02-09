#include <Arduino.h>

#define ENABLE_MOTORS 1

// Motor control
#define LEFT_ENABLE 3
#define LEFT_PIN_1 6
#define LEFT_PIN_2 5
#define RIGHT_ENABLE 9
#define RIGHT_PIN_1 7
#define RIGHT_PIN_2 8 

void motorSetup() {
  pinMode(LEFT_PIN_1, OUTPUT);
  pinMode(LEFT_PIN_2, OUTPUT);
  pinMode(RIGHT_ENABLE, OUTPUT);
  pinMode(RIGHT_PIN_1, OUTPUT);
  pinMode(RIGHT_PIN_2, OUTPUT);
  digitalWrite(LEFT_PIN_1, LOW);
  digitalWrite(LEFT_PIN_2, LOW);
  digitalWrite(RIGHT_PIN_1, LOW);
  digitalWrite(RIGHT_PIN_2, LOW);
}

void leftForward() {
  digitalWrite(LEFT_PIN_1, HIGH & ENABLE_MOTORS );
  digitalWrite(LEFT_PIN_2, LOW);
}

void leftBackward() {
  digitalWrite(LEFT_PIN_1, LOW);
  digitalWrite(LEFT_PIN_2, HIGH & ENABLE_MOTORS);
}

void leftOff() {
  digitalWrite(LEFT_PIN_1, LOW);
  digitalWrite(LEFT_PIN_2, LOW);
}

void leftPower(byte power) {
  analogWrite(LEFT_ENABLE, power);
}

void rightPower(byte power) {
  analogWrite(RIGHT_ENABLE, power);
}

void rightForward() {
  digitalWrite(RIGHT_PIN_1, HIGH & ENABLE_MOTORS);
  digitalWrite(RIGHT_PIN_2, LOW);
}

void rightBackward() {
  digitalWrite(RIGHT_PIN_1, LOW);
  digitalWrite(RIGHT_PIN_2, HIGH & ENABLE_MOTORS);
}

void rightOff() {
  digitalWrite(RIGHT_PIN_1, LOW);
  digitalWrite(RIGHT_PIN_2, LOW);
}

void forward() {
  leftForward();
  rightForward();
}

void backward() {
  leftBackward();
  rightBackward();
}

void rotateLeft() {
  leftBackward();
  rightForward();
}

void rotateRight() {
  leftForward();
  rightBackward();
}

void stop() {
  leftOff();
  rightOff();
}

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

/*
void potTest() {
  while(1) {
    Serial.print(map(analogRead(SPEED_PIN), 0, 1023, 0, 255));
    Serial.print("  ");
    Serial.println(map(analogRead(BAT_PIN), 767, 1023, 0, 100));
    delay(50);
  }
}
*/
