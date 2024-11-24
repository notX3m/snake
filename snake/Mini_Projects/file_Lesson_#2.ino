#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  /*
  TODO: Change the function to light up all 256 diode in a row.
  You can also play around with the speed of the moving LED and practice
  using while loops as learned in the guide by having the program do the
  same thing but replacing the for loop with the while loop.
  */
  
  for (int i=0; i<16; i++) {
    light(i, CRGB::Green);
    delay(500);
    light(i, CRGB::Black);
  }
}

void light(int index, CRGB color) {
  leds[index] = color;
  FastLED.show();
}