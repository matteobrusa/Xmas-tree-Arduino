#include <Adafruit_NeoPixel.h>
#include "effects.h"


#define PIN 0

#define LEN 50

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(LEN, PIN, NEO_RGB);

#define BRIGHTNESS 255
#define TEMPO 4

union rgb_t {
  uint32_t word;
  uint8_t  byte[3];
  struct {
    uint8_t  b;
    uint8_t  g;
    uint8_t  r;
  };
};


uint32_t tictoctac = 0;

Fx *fx1, *fx2;

uint8_t mix;


void setup() {
  pixels.begin();
  pixels.setBrightness(BRIGHTNESS);
}

uint32_t fxCount = sizeof(fxs) / sizeof(fxs[0]);

Fx* randomFx(Fx* diff) {
  Fx* fx;
  do {
    fx = &fxs[ random(fxCount) ];
  }
  while ( fx == diff );

  return fx;
}

void doPixels() {

  fx1->iterate();
  fx2->iterate();

  for (uint8_t pos = 0; pos < LEN; pos++) {
    doPixel(pos);
  }

  pixels.show();
  delay(TEMPO);

  tictoctac++;
}

rgb_t c1, c2, c;
void doPixel(uint8_t pos) {

  c1.word = fx1->pixel(pos);
  c2.word = fx2->pixel(pos);

  uint16_t n = mix, m = 255 - n;

  for (int i = 0; i < 3; i++) {
    c.byte[i] = (c1.byte[i] * n + c2.byte[i] * m) >> 8;
  }

  pixels.setPixelColor(pos, c.word);
}


void loop() {

  fx1 = &flash;
  fx1->init();

  fx2 = &plasma;
  fx2->init();

  mix = 128;
//  while (true) {
//    doPixels();
//  }


  while (true) {

    // fade to f2
    for (; mix > 0; mix--) {
      doPixels();
    }

    // get new fx
    fx1 = fx2;
    mix = 255;
    fx2 = randomFx(fx1);

    // fade to mix
    uint8_t n = 64 + random(128);
    for (; mix > n; mix--) {
      doPixels();
    }

    // enjoy
    for (uint8_t i; i < 100; i++) {
      doPixels();
    }

  }
}



