#include <Arduino.h>
#include "leds.h"
#include "motors.h"
#include "InputDebounce.h"

#define FRONT_IR_PIN A0
#define BACK_IR_PIN A1
#define SPEED_PIN A6
#define BAT_PIN A7
#define LED_PIN 2
#define BTN_PIN 4

#define BAT_3VPERCELL_READING 782
#define BAT_42VPERCELL_READING 1023
#define BAT_MIN_PERCENT 40

#define STATE_OFF 0
#define STATE_STOP 1
#define STATE_FORWARD 2
#define STATE_BACKWARD 3
#define STATE_ROTATE 4

#define BUTTON_DEBOUNCE_DELAY   20   // [ms]

int state = STATE_STOP;

static InputDebounce btn;

void handleBtnPressed(uint8_t pinIn) {
  // Serial.println("Button Pressed");
}

void handleBtnReleased(uint8_t pinIn) {
  nextPattern();
}

void handleBtnPressedDuration(uint8_t pinIn, unsigned long duration) {
  /*
  Serial.print("Button pressed duration ");
  Serial.print(duration);
  Serial.println("ms");
  */
}

void handleBtnReleasedDuration(uint8_t pinIn, unsigned long duration) {
  /*
  Serial.print("Button released duration ");
  Serial.print(duration);
  Serial.println("ms");
  */
}

void setState(int newState) {
  switch (newState) {
    case STATE_OFF:
      state = newState;
      Serial.println("OFF");
      stop();
      break;
    case STATE_STOP:
      state = newState;
      Serial.println("Stop");
      stop();
      break;
    case STATE_FORWARD:
      state = newState;
      Serial.println("Forward");
      forward();
      break;
    case STATE_BACKWARD:
      state = newState;
      Serial.println("Backward");
      backward();
      break;
    case STATE_ROTATE:
      state = newState;
      Serial.println("Rotate");
      rotateLeft();
      break;
  }
}

void updatePower() {
  int power = map(analogRead(SPEED_PIN), 0, 1023, 0, 255);
  leftPower(power);
  rightPower(power);
}

void checkBattery() {
  int battery = analogRead(BAT_PIN);
  int batteryPercent = map(battery, 
    BAT_3VPERCELL_READING, BAT_42VPERCELL_READING,
    0, 100);
  Serial.print("Battery ");
  Serial.print(batteryPercent);
  Serial.print("% (");
  Serial.print(battery);
  Serial.println(")");
  if (batteryPercent < BAT_MIN_PERCENT) {
    Serial.print("Battery is too low ");
    Serial.print(batteryPercent);
    Serial.println("%. Turning off.");
    setState(STATE_OFF);
    FastLED.clear(true);
    FastLED.show();
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LEFT_ENABLE, OUTPUT);
  motorSetup();
  pinMode(FRONT_IR_PIN, INPUT);
  pinMode(BACK_IR_PIN, INPUT);
  pinMode(SPEED_PIN, INPUT);
  pinMode(BAT_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  Serial.begin(9600);

  btn.registerCallbacks(handleBtnPressed, handleBtnReleased, handleBtnPressedDuration, handleBtnReleasedDuration);
  btn.setup(BTN_PIN, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);

  ledSetup();
  
  delay(500);
  updatePower();
  setState(STATE_FORWARD);
  // moveTest();
  // rightTest();
  // leftTest();
  // potTest();
}

uint8_t lastBtn = LOW;

void loop() {
  unsigned long now = millis();

  /*
  EVERY_N_SECONDS(10) {
    checkBattery();
  }
*/
  btn.process(now);

  if (state != STATE_OFF) {
  /*
    updatePower();
    switch (state) {
      case STATE_FORWARD:
        if (digitalRead(FRONT_IR_PIN) == LOW) {
          setState(STATE_STOP);
          delay(300);
          setState(STATE_BACKWARD);
        }
        break;
      case STATE_BACKWARD:
        if (digitalRead(BACK_IR_PIN) == LOW) {
          setState(STATE_STOP);
          delay(300);
          setState(STATE_FORWARD);
        }
    }
  */
  
    ledProcess();

    // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically

  }
}
