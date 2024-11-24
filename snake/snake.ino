#include <FastLED.h>
#define NUM_LEDS 256 // 16x16 matrix
#define DATA_PIN 2

CRGB leds[NUM_LEDS];

/*
Notice that the the array below has only 64 numbers which limits the length of the snake to 64. You might be asking, "but doesn't our matrix have 256 LEDS" to which I wouuld say yes, you are correct.
But here's the thing, if you are creating the portable box then this would be the best way to do it because the Arduino NANO just isn't as powerful than say the Arduino UNO. If you are not doing the 
portable box then you can go ahead and change it to 256. By the way one way to open up some storage and make the body be bigger is making the int's with small numbers being stored in them into a thing
called, "byte." Byte's do the same task as int's but store smaller numbers. Using byte helps save storage.
*/
int BodyX[64] = {8,8,8};
int BodyY[64] = {8,7,6};
int BodyL = 3;

int X = 8;
int Y = 8;

int NOT_STARTED = 0;
int GAME_IN_PROGRESS = 1;
int GAME_OVER = 2;

// game status
int gameStatus = NOT_STARTED;

int appleX;
int appleY;
int Xpin=A1;
int Ypin=A0;
int Spin=3;
int Sval;
float Xval;
float Yval;
int Xm = 0;
int Ym = 0;
unsigned long time = 0;
int Buzzpin = 4;

long Mvdelay = 200;

int game = 0;
CRGB colors[] = {
  CRGB::Red,        // Red
  CRGB::Green,      // Green
  CRGB::Blue       // Blue
};


int sign(float f) {
  if (f>0) {
    return 1;
  }
  else {
    return -1;
  }
}
//This function that we wrote gets coordinates from the joystick and turns them into the correct number LED to light up.
void set(int xcoor, int ycoor, CRGB color) {
  if (xcoor < 0 || xcoor > 15 || ycoor < 0 || ycoor > 15) return;
  
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

//This function that we wrote clears the matrix so the new position of the snake can be drawn.
void clear(CRGB color) {
  for (int j=0;j<256;j++) {
    leds[j]=color;
  }
}

//This function that we wrote commences when the player clicks a button. It returns everything to a homeostasis so the player can play again.
void reset() {
  BodyL = 3;
  X = 8;
  Y = 8;
  BodyX[0] = 8;
  BodyX[1] = 8;
  BodyX[2] = 8;
  BodyY[0] = 8;
  BodyY[1] = 7;
  BodyY[2] = 6;
}

//This randomizes the apple position
void castApple() {
  appleX = random(0,16);
  appleY = random(0,16);
}

//This checks if the head has knocked into the body. If it has, the buzzer tells us that it's game over and the function, "return;" just returns back to the beggining of, "void loop() {}"
void check() {
  for (int i=0;i<BodyL;i++) {
     if (X==BodyX[i] && Y==BodyY[i]) {
      gameStatus = GAME_OVER;    
      tone(Buzzpin,100, 500);
      return;
     }
  }
}

//Just if you don't know, "void setup() {}" runs only once when starting the program unlike "void loop() {}" which runs forever.
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Xpin,INPUT);
  pinMode(Ypin,INPUT);
  pinMode(Spin,INPUT);
  digitalWrite(Spin,HIGH);
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  pinMode(Buzzpin,OUTPUT);
}

void loop() {
  
  
  // calculate joystick
  Xval=analogRead(Xpin);
  Yval=analogRead(Ypin);
  Sval=digitalRead(Spin);
  Xval = ((Xval - 511.0) / 512.0)*-1;
  Yval = ((Yval - 511.0) / 512.0);

  // Checks the game status. If it is, "GAME_IN_PROGRESS"  It checks only if the joystick is past half of what it can go to the sides. If true, then it checks the closest direction were the joystick is pointing.
  if (gameStatus == NOT_STARTED || gameStatus == GAME_IN_PROGRESS)  {
    if (abs(Xval)>0.5 || abs(Yval)>0.5) {
      if (abs(Xval)>abs(Yval)) {
        Xm = sign(Xval);
        Ym = 0;
      }
      else
      {
        Ym = sign(Yval);
        Xm = 0;
      }
      if (gameStatus==NOT_STARTED) {
        castApple();
      }
      gameStatus = GAME_IN_PROGRESS;
    }
  }

  //Checks if you lost, if true then it wait's for the player to click on the joystick. When he does the function, "reset()" a function that we wrote, resets the game to a homeostasis.
  if (gameStatus == GAME_OVER && Sval == 0) {
    gameStatus = NOT_STARTED;
    reset();
  }

  // calculations
  if (time<millis()) {

    // calculations
    // we do calculations only in game in progress mode.
    if (gameStatus==GAME_IN_PROGRESS) {
      X = X + Xm;
      Y = Y - Ym;
      check();
      time = Mvdelay + millis();

      // border check   
      if (X>15 || Y>15 || X<0 || Y<0) {
        game++;
        gameStatus = 2;
        tone(Buzzpin,100, 500);
      }

      // move body
      for (int i = BodyL;i>0;i--) {
        BodyX[i] = BodyX[i-1];
        BodyY[i] = BodyY[i-1];
      }

      // assign head
      BodyX[0] = X;
      BodyY[0] = Y;
      if (X==appleX && Y==appleY) {
        BodyL++;
        castApple();
        tone(Buzzpin,1000, 100);
      }
    }

    // clear matrix
    clear(CRGB::Black);

    // draw body
    for (int i = 0; i<BodyL; i++) {
      set(BodyX[i], BodyY[i], CRGB::Green);
    }

    set(BodyX[0], BodyY[0], CRGB::Blue);
    set(appleX, appleY, CRGB::Red);
    // show leds
    FastLED.show();
  }



  

}