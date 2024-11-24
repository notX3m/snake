#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // If you completed Lesson #3 you would have seen that the snake goes from left to right then moves up one LED and starts going the opposite direction. After that it goes up on LED again and it repeats.
// TODO: We need to write a function to light diodes by coordinates specifing X, Y, and color.
// Here is an example with a 6 by 6 matrix:
/*
35 34 33 32 31 30
24 25 26 27 28 29
23 22 21 20 19 18
12 13 14 15 16 17
11 10  9  8  7  6
 0  1  2  3  4  5
*/
void set(int xcoor, int ycoor, CRGB color) {
  if (xcoor < 0 || xcoor > 15 || ycoor < 0 || ycoor > 15) return;
  
  int i;
  if ((ycoor%2)==0) {
    i = ycoor * 16 + xcoor;
  }
  else {
    i = ycoor * 16 + (15-xcoor);
  }

  /*
  Functions in programming are tools that allow you to group specific tasks into reusable blocks of code, making your program more organized and efficient.
  They work by taking inputs (called parameters), performing a set of actions, and sometimes providing an output. 
  A great example of this is the set() function, which I wrote to control individual LEDs on a 16x16 LED matrix. 
  The definition void set(int xcoor, int ycoor, CRGB color) tells us a lot about the function: it doesn’t return any value (as indicated by void), and it requires three inputs—xcoor (the x-coordinate), ycoor (the y-coordinate), and color (the desired LED color). 
  For instance, calling set(2, 3, CRGB::Red) will turn the LED at column 2, row 3 red. 
  Within the function, the first task is to check if the coordinates are within the valid range using if (xcoor < 0 || xcoor > 15 || ycoor < 0 || ycoor > 15) return;. 
  If the coordinates are invalid, the function stops immediately. 
  If the coordinates are valid, the function calculates the index of the LED in the leds array, which stores the colors of all LEDs in the matrix. 
  Since the LEDs are wired in a zigzag pattern, the calculation changes depending on whether the row number (ycoor) is even or odd.
  For even rows, the index is ycoor * 16 + xcoor, and for odd rows, it’s ycoor * 16 + (15 - xcoor). 
  Once the index is calculated, the function updates the corresponding LED’s color in the leds array with leds[i] = color;. 
  In this function, xcoor, ycoor, color, and i are local variables that exist only while the function is running, while leds is a global variable accessible throughout the program. 
  Writing your own functions, like set(), is a powerful way to simplify tasks in your code. 
  Instead of repeatedly writing out the logic for controlling LEDs, you can now just call set() whenever needed, making your program cleaner, more efficient, and easier to understand.
  */
}