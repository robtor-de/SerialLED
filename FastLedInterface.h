#include <FastLED.h>

#define DATA_PIN 3
#define CLK_PIN 13
#define FADETIME_MULTIPLIER_MS 100

CRGB leds[1];

void hardwareSetup() {
  FastLED.addLeds<P9813, DATA_PIN, CLK_PIN, RGB>(leds, 1);
  //turn off LED's on startup
  leds[0] = CRGB::Black;
  FastLED.show();
}

//Instantly set the Color
void setColor(short r, short g, short b) {
  leds[0].r = r;
  leds[0].g = g;
  leds[0].b = b;
  FastLED.show();
}

//Fade to other color within duration
void fadeTo(short r, short g, short b, int duration) {
  short diff[3];
  short scale[3];
  int dur_step;
  diff[0] = r - leds[0].r;
  diff[1] = g - leds[0].g;
  diff[2] = b - leds[0].b;

  scale[0] = 256/diff[0];
  scale[1] = 256/diff[1];
  scale[2] = 256/diff[2];

  dur_step = (duration*FADETIME_MULTIPLIER_MS)/256;

  for(int i = 0; i < 255; i++) {
    //if is necessary to prevent overflow
    if((i%scale[0])==0) (scale[0] > 0)? leds[0].r += 1 : leds[0].r -= 1;
    if((i%scale[1])==0) (scale[1] > 0)? leds[0].g += 1 : leds[0].g -= 1;
    if((i%scale[2])==0) (scale[2] > 0)? leds[0].b += 1 : leds[0].b -= 1;
    FastLED.show();
    delay(dur_step);
  }

}
