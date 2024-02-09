#include <FastLED.h>


// ledfDecl
#define LED_PIN 2
#define NUM_LEDS 100
#define INIT_BRIGHTNESS 63
#define LED_TYPE          WS2811
#define COLOR_ORDER       GRB
#define FRAMES_PER_SECOND  360
CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette(CRGB::Black);
// Many different possibilities here. These are accessible in colorpalettes.h in the FastLED library.
// Available: CloudColors_p, LavaColors_p, OceanColors_p, ForestColors_p, RainbowColors_p, RainbowStripeColors_p, PartyColors_p, and HeatColors_p
CRGBPalette16 targetPalette(PartyColors_p);

// Pattern Variables
// List of patterns to cycle through.  Each is defined as a separate function below.
void rainbow();
void rainbowWithGlitter();
void confetti();
void sinelon();
void juggle();
void juggle();
void bpm();

typedef void (*SimplePatternList[])();
SimplePatternList gPatterns = { rainbow, rainbowWithGlitter, confetti, sinelon, juggle, bpm };
 
uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current
uint8_t gHue = 0; // rotating "base color" used by many of the patterns
int lastBrightness = 127;
int actBrightness = 127;


void ledSetup() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);

  // Set the maximum power allowed for the string - (volts, milliamps)
  // For now, limit to 1.5A
  FastLED.setMaxPowerInVoltsAndMilliamps(5,1500);
  FastLED.setBrightness(INIT_BRIGHTNESS);

  rainbow();
  FastLED.show();
}

void ledProcess() {
  EVERY_N_MILLISECONDS( 20 ) {
    gHue++;  // slowly cycle the "base color" through the rainbow
    //Serial.print("gHue ");
    //Serial.println(gHue);
    gPatterns[gCurrentPatternNumber]();
    FastLED.show();
  }
}
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))

void nextPattern()
{
  // add one to the current pattern number, and wrap around at the end
  gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE( gPatterns);
}

void rainbow()
{
  // FastLED's built-in rainbow generator
  fill_rainbow( leds, NUM_LEDS, gHue, 7);
}

void addGlitter( fract8 chanceOfGlitter) 
{
  if( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}
 
void rainbowWithGlitter() 
{
  // built-in FastLED rainbow, plus some random sparkly glitter
  rainbow();
  addGlitter(80);
}
 
void confetti() 
{
  // random colored speckles that blink in and fade smoothly
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}
 
void sinelon()
{
  // a colored dot sweeping back and forth, with fading trails
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16( 13, 0, NUM_LEDS-1 );
  leds[pos] += CHSV( gHue, 255, 192);
}
 
void bpm()
{
  // colored stripes pulsing at a defined Beats-Per-Minute (BPM)
  uint8_t BeatsPerMinute = 62;
  CRGBPalette16 palette = PartyColors_p;
  uint8_t beat = beatsin8( BeatsPerMinute, 64, 255);
  for( int i = 0; i < NUM_LEDS; i++) { //9948
    leds[i] = ColorFromPalette(palette, gHue+(i*2), beat-gHue+(i*10));
  }
}
 
void juggle() {
  // eight colored dots, weaving in and out of sync with each other
  fadeToBlackBy( leds, NUM_LEDS, 20);
  uint8_t dothue = 0;
  for( int i = 0; i < 8; i++) {
    leds[beatsin16( i+7, 0, NUM_LEDS-1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}
