#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 2

CRGB leds[NUM_LEDS];


int BodyX[256] = {8,8,8};
int BodyY[256] = {8,7,6};
int BodyL = 3;

int X = 8;
int Y = 8;

int gameStatus = 0;
// 0 - not started
// 1 - game in progress
// 2 - game over
int Xpin=A0;
int Ypin=A1;
int Spin=3;
int Sval;
float Xval;
float Yval;
int Xm = 0;
int Ym = 0;
unsigned long time = 0;

long Mvdelay = 100;

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

  // check if we are out leds bounds
  if (i>=0 && i<=255) {
    leds[i] = color;
  }
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
  
  
  // calculate joystick
  Xval=analogRead(Xpin);
  Yval=analogRead(Ypin);
  Sval=digitalRead(Spin);
  Xval = (Xval - 511.0) / 512.0;
  Yval = (Yval - 511.0) / 512.0;
  if (abs(Xval)>0.5 || abs(Yval)>0.5) {
    if (abs(Xval)>abs(Yval)) {
      Xm = sign(Xval);
      Ym = 0;
      gameStatus = 1;
    }
    else
    {
      Ym = sign(Yval);
      Xm = 0;
    }
  }


  // calculations
  if (time<millis()) {

    // calculations
    // we do calculations only in game in progress mode
    if (gameStatus==1) {
      X = X + Xm;
      Y = Y - Ym;
      time = Mvdelay + millis();

      // border check   
      if (X>15 || Y>15 || X<0 || Y<0) {
        game++;
        gameStatus = 2;
      }

      // move body
      for (int i = BodyL;i>0;i--) {
        BodyX[i] = BodyX[i-1];
        BodyY[i] = BodyY[i-1];
      }

      // asign head
      BodyX[0] = X;
      BodyY[0] = Y;
    }

    // clear matrix
    clear(CRGB::Black);

    // draw body
    for (int i = 0; i<BodyL; i++) {
      set(BodyX[i], BodyY[i], CRGB::Green);
    }
    set(BodyX[0], BodyY[0], CRGB::Red);

    // show leds
    FastLED.show();
  }



  

}
