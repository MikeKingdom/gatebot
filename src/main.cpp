#include <Arduino.h>
#include <EEPROM.h>

#include "config.h"
#include "InputDebounce.h"
#include "leds.h"
#include "chassis.h"
#include "battery.h"

#define STATE_OFF 0
#define STATE_STOP 1
#define STATE_FORWARD 2
#define STATE_BACKWARD 3
#define STATE_ROTATE 4

int state = STATE_STOP;

static InputDebounce btn;
static Motor leftMotor(LEFT_ENABLE, LEFT_PIN_1, LEFT_PIN_2);
static Motor rightMotor(RIGHT_ENABLE, RIGHT_PIN_1, RIGHT_PIN_2);
static Chassis chassis(leftMotor, rightMotor);
static Battery battery;
static LEDs leds;

// EEPROM Setup
#define EP_ADDRESS         0
struct ep_contents
{
  byte saved = 0;
  byte pattern = 0;
};
typedef struct ep_contents ep_contents;
ep_contents epData;

void handleBtnPressed(uint8_t pinIn) {
  // Serial.println("Button Pressed");
}

void handleBtnReleased(uint8_t pinIn) {
  leds.nextPattern();
  // save the current pattern index in EEPROM
  epData.saved = 1;
  epData.pattern = leds.getPatternNumber();
  EEPROM.put(EP_ADDRESS, epData);
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
      chassis.stop();
      break;
    case STATE_STOP:
      state = newState;
      Serial.println("Stop");
      chassis.stop();
      break;
    case STATE_FORWARD:
      state = newState;
      Serial.println("Forward");
      chassis.forward();
      break;
    case STATE_BACKWARD:
      state = newState;
      Serial.println("Backward");
      chassis.backward();
      break;
    case STATE_ROTATE:
      state = newState;
      Serial.println("Rotate");
      chassis.rotateLeft();
      break;
  }
}

void updatePower() {
  int power = map(analogRead(SPEED_PIN), 0, 1023, 0, 255);
  chassis.power(power);
}

void onBatteryLow(int value, int percent) {
  setState(STATE_OFF);
  FastLED.clear(true);
  FastLED.show();
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  chassis.setup();
  battery.setup(BAT_PIN, onBatteryLow);
  pinMode(FRONT_IR_PIN, INPUT);
  pinMode(BACK_IR_PIN, INPUT);
  pinMode(SPEED_PIN, INPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  Serial.begin(9600);

  EEPROM.get(EP_ADDRESS, epData);
  Serial.print("epData saved=");
  Serial.print(epData.saved);
  Serial.print(" pattern=");
  Serial.println(epData.pattern);
  if (epData.saved == 1) {
    // 255 is erased state. no settings saved)
    // If any other value is written, it is not erased and therefore settings are saved.
    leds.setPatternNumber(epData.pattern);
  }

  btn.registerCallbacks(handleBtnPressed, handleBtnReleased, handleBtnPressedDuration, handleBtnReleasedDuration);
  btn.setup(BTN_PIN, BUTTON_DEBOUNCE_DELAY, InputDebounce::PIM_INT_PULL_UP_RES);

  leds.setup();
  
  delay(500);
  updatePower();
  setState(STATE_FORWARD);
  // moveTest();
  // rightTest();
  // leftTest();
  // potTest();
}

void loop() {
  unsigned long now = millis();

  EVERY_N_SECONDS(10) {
    battery.process();
  }

  btn.process(now);

  if (state != STATE_OFF) {
    EVERY_N_SECONDS(1) {
      updatePower();
    }

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

    leds.process();
  }
}
