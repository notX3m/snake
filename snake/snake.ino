#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
CRGB leds[NUM_LEDS];
#define DATA_PIN 2


int X = 8;
int Y = 8;


int Xpin=A0;
int Ypin=A1;
int Spin=3;
float Xval;
float Yval;
int Sval;
int Dt=200;
int Xm = 0;
int Ym = 0;
unsigned long time = 0;

long Mvdelay = 500;
int i;
int game = 0;
CRGB colors[] = {
  CRGB::Red,        // Red
  CRGB::Green,      // Green
  CRGB::Blue,       // Blue
  CRGB::White,      // White
  CRGB::Yellow,     // Yellow
  CRGB::Cyan,       // Cyan
  CRGB::Magenta,    // Magenta
  CRGB::Orange,     // Orange
  CRGB::Purple,     // Purple
  CRGB::Pink,       // Pink
  CRGB::Lime,       // Lime
  CRGB::Aqua,       // Aqua
  CRGB::Teal,       // Teal
  CRGB::Violet,     // Violet
  CRGB::Gold,       // Gold
  CRGB::Silver      // Silver
};


int sign(float f) {
  if (f>0) {
    return 1;
  }
  else {
    return -1;
  }
}

void set(int xcoor, int ycoor, CRGB color) {
  int i;
  if ((ycoor%2)==0) {
    i = ycoor * 16 + xcoor;
  }
  else {
    i = ycoor * 16 + (15-xcoor);
  }
  leds[i] = color;
}

void clear(CRGB color) {
  for (int j=0;j<256;j++) {
    leds[j]=color;
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Xpin,INPUT);
  pinMode(Ypin,INPUT);
  pinMode(Spin,INPUT);
  digitalWrite(Spin,HIGH);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop() {
  // put your main code here, to run repeatedly:
  Xval=analogRead(Xpin);
  Yval=analogRead(Ypin);
  Sval=digitalRead(Spin);
  Xval = (Xval - 511.0) / 512.0;
  Yval = (Yval - 511.0) / 512.0;
  if (abs(Xval)>0.5 || abs(Yval)>0.5) {
    if (abs(Xval)>abs(Yval)) {
      Xm = sign(Xval);
      Ym = 0;
    }
    else {
      Ym = sign(Yval);
      Xm = 0;
    }
  }

  if (time<millis()) {
    X = X + Xm;
    Y = Y - Ym;
    time = Mvdelay + millis();
    // Serial.print("Xm value = ");
    // Serial.print(Xm);
    // Serial.print(" ");
    // Serial.print("Ym value = ");
    // Serial.println(Ym);
   
    if (X>15 || Y>15 || X<0 || Y<0) {
      X = 8;
      Y = 8;
      // Xm = 0;
      // Ym = 0;
      game++;
    }

    clear(CRGB::Black);
    int colori = game%16;
    CRGB color = colors[colori];
    set(X, Y, color);
    FastLED.show();
  }



  

  /*
  delay(Dt);
  Serial.print("X value = ");
  Serial.print(Xm);
  Serial.print(" ");
  Serial.print("Y value = ");
  Serial.print(Ym);
  Serial.print(" ");
  Serial.print("Switch state is ");
  Serial.println(Sval);
  */

}
