#ifndef _LEDS_H
#define _LEDS_H

#include <FastLED.h>
// ledfDecl
#define LED_PIN 2
#define NUM_LEDS 100
#define INIT_BRIGHTNESS 63
#define LED_TYPE          WS2811
#define COLOR_ORDER       GRB
#define FRAMES_PER_SECOND  360

class LEDs {
public:
  explicit LEDs();
  virtual ~LEDs();
  void setup();
  void process();
  void nextPattern();
  void setPatternNumber(uint8_t index);
  uint8_t getPatternNumber();

private:
  CRGB leds[NUM_LEDS];
 
  uint8_t _currentPatternNumber = 0; // Index number of which pattern is current
  uint8_t _gHue = 0; // rotating "base color" used by many of the patterns

};
#endif // _LEDS_H
