#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {

  // 1. This program Blinks one LED

  leds[136] = CRGB::Red;
  FastLED.show();
  delay(500);

  leds[136] = CRGB::Black;
  FastLED.show();
  delay(500);


  //TODO: add code to blink multiple LEDS in different colors.


}