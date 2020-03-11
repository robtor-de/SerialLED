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
  float scale[3], dur_step;
  diff[0] = r - leds[0].r;
  diff[1] = r - leds[0].r;
  diff[2] = r - leds[0].r;

  scale[0] = scale8(1, diff[0]);
  scale[1] = scale8(1, diff[1]);
  scale[2] = scale8(1, diff[2]);

  dur_step = duration*1000/256.0;

  for(int i = 0; i < 256; i++) {
    leds[0].r += scale[0];
    leds[0].g += scale[1];
    leds[0].b += scale[2];
    FastLED.show();
    delay(dur_step);
  }

}
