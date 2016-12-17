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


uint8_t mix = 64 + random(128);
uint8_t fxCount = sizeof(fxs) / sizeof(Fx);

Fx *fx1, *fx2;

void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
}

void doPixels() {

  fx1->iterate();
  fx2->iterate();

  for (uint8_t pos = 0; pos < LEN; pos++) {
    doPixel( pos);
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
}

void doPixel(uint8_t pos) {

  rgb_t c1, c2, c;
  c1.word = fx1->pixel(pos);
  c2.word = fx2->pixel(pos);

  uint16_t n = mix, m = 255 - n;
  uint32_t ch;

  for (int i = 0; i < 3; i++) {
    ch = (c1.byte[i] * n + c2.byte[i] * m) >> 8;
    if (ch > 255) ch = 255;
    c.byte[i] = ch ;
  }

  pixels.setPixelColor(pos, c.word);
}


Fx* randomFx(Fx* diff) {
  Fx* fx;
  do {
    fx = &fxs[ random(fxCount) ];
  }
  while ( fx == diff );

  return fx;
}


void loop() {

  Fx* fx1 = &wave;
  fx1->init();

  Fx* fx2 = &plasma;
  fx2->init();

  mix = 128;

  while (true) {

    // fade to f2
    for (; mix < 255; mix++) {
      doPixels();
    }

    // get new fx
    fx1 = fx2;
    mix = 255;
    fx2 = randomFx(fx1);

    // fade to mix
    uint32_t n = 64 + random(128);
    for (; mix != n; mix--) {
      doPixels();
    }

    // enjoy
    n = 100000 + random(200);
    for (uint8_t i; i < n; i++) {
      doPixels();
    }
  }
}
