#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

int X = 8; // Starting position X
int Y = 8; // Starting position Y
int Xpin = A1; // Joystick X-axis pin
int Ypin = A0; // Joystick Y-axis pin
float Xval;
float Yval;
int Xm = 0;
int Ym = 0;
unsigned long time = 0;
long Mvdelay = 200;

// Function to calculate the LED index in the array
void set(int xcoor, int ycoor, CRGB color) {
  if (xcoor < 0 || xcoor > 15 || ycoor < 0 || ycoor > 15) return;
  
  int i;
  if ((ycoor % 2) == 0) {
    i = ycoor * 16 + xcoor;
  } else {
    i = ycoor * 16 + (15 - xcoor);
  }

  if (i >= 0 && i <= 255) {
    leds[i] = color;
  }
}

// Function to clear the matrix
void clear(CRGB color) {
  for (int j = 0; j < 256; j++) {
    leds[j] = color;
  }
}

// Determines the sign of a number (-1 or 1)
int sign(float f) {
  if (f > 0) {
    return 1;
  } else {
    return -1;
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(Xpin, INPUT);
  pinMode(Ypin, INPUT);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // Read joystick input
  Xval = analogRead(Xpin);
  Yval = analogRead(Ypin);
  Xval = ((Xval - 511.0) / 512.0) * -1;
  Yval = ((Yval - 511.0) / 512.0);

  if (abs(Xval) > 0.5 || abs(Yval) > 0.5) {
    if (abs(Xval) > abs(Yval)) {
      Xm = sign(Xval);
      Ym = 0;
    } else {
      Ym = sign(Yval);
      Xm = 0;
    }
  }

  if (time < millis()) {
    // Update the dot's position
    X = X + Xm;
    Y = Y - Ym;
    time = Mvdelay + millis();

    // Prevent going out of bounds
    if (X > 15) X = 15;
    if (Y > 15) Y = 15;
    if (X < 0) X = 0;
    if (Y < 0) Y = 0;

    // Clear the matrix and draw the dot
    clear(CRGB::Black);
    set(X, Y, CRGB::Blue);
    FastLED.show();
  }
}

/*This code uses input values from the joystick to move this blue dot 
across the screen. Remember if you are having trouble understanding the
joystick go back to the tutorial where there is a video on it. As always
You can look through the code and make sense of what it is doing. If you
don't understand something then just ask chatgpt. And no, it's not cheating if 
you use AI in the correct way as in don't have AI do everything for you.
*/