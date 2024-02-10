#ifndef _BATTERY_H
#define _BATTERY_H

#include <Arduino.h>

#define BAT_3VPERCELL_READING 782
#define BAT_42VPERCELL_READING 1023
#define BAT_MIN_PERCENT 40

typedef void (*battery_low_cb)(int, int);

class Battery {
public:
  explicit Battery();
  virtual ~Battery();
  void setup(uint8_t batteryPin, battery_low_cb callback);
  void process();

private:
  uint8_t _batteryPin;
  battery_low_cb _callback;
};
#endif // _BATTERY_H