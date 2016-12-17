// Low power NeoPixel earrings example.  Makes a nice blinky display
// with just a few LEDs on at any time...uses MUCH less juice than
// rainbow display!

#include <Adafruit_NeoPixel.h>
#include "effects.h"


#define PIN 0

#define LEN 50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEN, PIN, NEO_RGB);

#define BRIGHTNESS 255
#define TEMPO 10

#define FLASHINESS 4

union rgb_t {
  uint32_t word;
  uint8_t  byte[3];
  struct {
    uint8_t  b;
    uint8_t  g;
    uint8_t  r;
  } ;
} ;

uint8_t tic = 0, // every round this increments up to LEN
        toc = 0, // every LEN rounds
        tac = 0;
uint32_t tictoctac = 0;






void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
}







void doPixel(Fx fx1, Fx fx2, uint8_t pos) {

  rgb_t c1, c2, c;
  c1.word = fx1.pixel(pos);
  c2.word = fx2.pixel(pos);

  uint16_t n = MIX, m = 255 - n;
  uint32_t ch;

  for (int i = 0; i < 3; i++) {
    ch = (c1.byte[i] * n + c2.byte[i] * m) >> 8;
    if (ch > 255) ch = 255;
    c.byte[i] = ch ;
  }

  pixels.setPixelColor(pos, c.word);
}


void loop() {

  // keyframer

  Fx fx1 = wave;
  fx1.init();

  Fx fx2 = plasma;
  fx2.init();


  fx1.iterate();
  fx2.iterate();



  for (uint8_t pos = 0; pos < LEN; pos++) {
    doPixel(fx1, fx2, pos);
  }

  pixels.show();
  delay(TEMPO);

  tictoctac++;

  if (++tic == LEN) {
    tic = 0;

    if (++toc == LEN) {
      toc = 0;

      if (++tac == LEN) {
        tac = 0;
      }
    }
  }

  /*
    switch (mode) {

     // candle
     case 1:
       l = 0x0f0c04 * (5 + random(6));
       m = 0x0f0c04 * random(6);

       for (i = 0; i < 16; i++)
         pixels.setPixelColor(i, l); // 0xffcc44
       pixels.show();
       delay(100 + random(400));

       for (i = 0; i < 16; i++)
         pixels.setPixelColor(i, (m + l) / 2);
       pixels.show();
       delay(10);

       for (i = 0; i < 16; i++)
         pixels.setPixelColor(i, m);
       pixels.show();
       delay(random(16)*random(6));

       wait = 0;
       duration = 1;
       offset += 7;
       break;

     // random
     case 4:
       l = random(16 * 16 * 16);

       x = l & 15;
       l = l >> 4;
       y = l & 15;
       l = l >> 4;
       z = l & 15;

       pixels.setPixelColor(x, 0xffddaa);
       pixels.setPixelColor(y, 0xffddaa);
       pixels.setPixelColor(z, 0xffddaa);

       pixels.show();
       delay(20);
       pixels.setPixelColor(x, 0);
       pixels.setPixelColor(y, 0);
       pixels.setPixelColor(z, 0);

       wait = 0;
       duration = 3;
       break;

     // plasma
     case 2:
       doPlasma();
       break;

     // glow
     case 3:
       doGlow();
       break;

     // alpha-omega
     case 5:
       for (i = 0; i < 16; i++) {
         pixels.setPixelColor((i + (offset / 16)) % 16, hueToColor(i < 8 ? offset : offset + 128, 255));
       }
       wait = 1;
       duration = 4;
       break;

    // rainbow
     case 6:
       for (i = 0; i < 16; i++) {
         pixels.setPixelColor(i, hueToColor(offset, 255));
       }
       wait = 2;
       duration = 5;
       break;
    }
  */


}



