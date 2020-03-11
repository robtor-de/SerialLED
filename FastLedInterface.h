#include <FastLED.h>

#define DATA_PIN 3
#define CLK_PIN 13

CRGB leds[1];

void hardwareSetup() {
  FastLED.addLeds<P9813, DATA_PIN, CLK_PIN, RGB>(leds, 1);
  //turn off LED's on startup
  leds[0] = CRGB::Black;
  FastLED.show();
}

void setColor(short r, short g, short b) {
  leds[0].r = r;
  leds[0].g = g;
  leds[0].b = b;
  FastLED.show();
}
