#include "battery.h"

Battery::Battery() : _batteryPin(-1)
{

}

Battery::~Battery()
{

}

void Battery::setup(uint8_t batteryPin, battery_low_cb callback)
{
  _batteryPin = batteryPin;
  _callback = callback;
  pinMode(_batteryPin, INPUT);
}

void Battery::process()
{
  int battery = analogRead(_batteryPin);
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
    if (_callback) {
      _callback(battery, batteryPercent);
    }
    // setState(STATE_OFF);
    // FastLED.clear(true);
    // FastLED.show();
  }
}
