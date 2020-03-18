#include <FastLED.h>

#define DATA_PIN 3
#define CLK_PIN 2
#define FADETIME_MULTIPLIER_MS 100
#define STROBETIME_MULTIPLIER_MS 10

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

  (diff[0] != 0)? scale[0] = 255/diff[0] : scale[0] = 0;
  (diff[1] != 0)? scale[1] = 255/diff[0] : scale[1] = 0;
  (diff[2] != 0)? scale[2] = 255/diff[0] : scale[2] = 0;


  dur_step = (duration*FADETIME_MULTIPLIER_MS)/256;

  for(int i = 0; i < 255; i++) {
    //if is necessary to prevent overflow
    if((i%scale[0])==0) {if(scale[0] > 0 && leds[0].r < 255) leds[0].r += 1; if(scale[0] < 0 && leds[0].r > 0) leds[0].r -= 1;}
    if((i%scale[1])==0) {if(scale[1] > 0 && leds[0].g < 255) leds[0].g += 1; if(scale[1] < 0 && leds[0].g > 0) leds[0].g -= 1;}
    if((i%scale[2])==0) {if(scale[2] > 0 && leds[0].b < 255) leds[0].b += 1; if(scale[2] < 0 && leds[0].b > 0) leds[0].b -= 1;}
    FastLED.show();
    delay(dur_step);
  }
}

//Save current state and strobe quickly in another color
void strobe(short r, short g, short b, int duration) {
  duration *= STROBETIME_MULTIPLIER_MS;
  CRGB old_color = leds[0];
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(duration);
  leds[0].setRGB(r, g, b);
  FastLED.show();
  delay(duration);
  leds[0] = CRGB::Black;
  FastLED.show();
  delay(duration);
  leds[0] = old_color;
  FastLED.show();
}

//Save current state and pulse in another Color
void pulse(short r, short g, short b, int duration) {
  CRGB old_color = leds[0];
  fadeTo(r, g, b, duration);
  fadeTo(old_color.r, old_color.g, old_color.b, duration);
}
