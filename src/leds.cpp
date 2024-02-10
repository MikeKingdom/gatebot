#include "leds.h"

#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

typedef void (*SimplePatternList[])(CRGB *leds, uint8_t hue);
void rainbow(CRGB *leds, uint8_t hue);
void rainbowWithGlitter(CRGB *leds, uint8_t hue);
void confetti(CRGB *leds, uint8_t hue);
void sinelon(CRGB *leds, uint8_t hue);
void juggle(CRGB *leds, uint8_t hue);
void juggle(CRGB *leds, uint8_t hue);
void bpm(CRGB *leds, uint8_t hue);

SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };

LEDs::LEDs()
{
}

LEDs::~LEDs() {

}

void LEDs::process()
{
  EVERY_N_MILLISECONDS( 20 ) {
    _gHue++;  // slowly cycle the "base color" through the rainbow
    //Serial.print("gHue ");
    //Serial.println(_gHue);
    gPatterns[gCurrentPatternNumber](leds, _gHue);
    FastLED.show();
  }

  // EVERY_N_SECONDS( 10 ) { nextPattern(); } // change patterns periodically

}

void LEDs::setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // Set the maximum power allowed for the string - (volts, milliamps)
  // For now, limit to 1.5A
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1500);
  FastLED.setBrightness(INIT_BRIGHTNESS);

  rainbow(leds, _gHue);
  FastLED.show();
}

void LEDs::nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow(CRGB *leds, uint8_t hue)
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, hue, 7);
}

void addGlitter( CRGB *leds, fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
 
void rainbowWithGlitter(CRGB *leds, uint8_t hue) 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow(leds, hue);
  addGlitter(leds, 80);
}
 
void confetti(CRGB *leds, uint8_t hue) 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( hue + random8(64), 200, 255);
}
 
void sinelon(CRGB *leds, uint8_t hue)
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( hue, 255, 192);
}
 
void bpm(CRGB *leds, uint8_t hue)
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, hue+(i*2), beat-hue+(i*10));
  }
}
 
void juggle(CRGB *leds, uint8_t hue) {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
