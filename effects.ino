

Fx rainbow  = {
  .init = &dummy,
  .iterate = &iterateRainbow,
  .pixel = pixelRainbow
};

Fx flash  = {
  .init = initFlash,
  .iterate = &dummy,
  .pixel = pixelFlash
};

Fx runner  = {
  .init = &dummy,
  .iterate = &dummy,
  .pixel = pixelRunner
};

Fx plasma  = {
  .init = initPlasma,
  .iterate = iteratePlasma,
  .pixel = pixelPlasma
};

Fx wave  = {
  .init = initWave,
  .iterate = &iterateWave,
  .pixel = pixelWave
};

void dummy() {
}


/*
    Glow
*/
#define GLOW_LEN 50;

void iterateRainbow() {
}

uint32_t pixelRainbow(uint8_t pos) {

  rgb_t res;

  uint16_t offset = pos * 3 + tictoctac;
  uint8_t wavelen = 14 + (pos << 3) % GLOW_LEN;

  res.r = (255 + ramp(offset , wavelen)) >> 1;

  wavelen = 14 + ((pos + 7) << 3) % GLOW_LEN;
  res.g = (60 + ramp(offset + 1, wavelen)) >> 1;

  wavelen = 14 + ((pos + 13) << 3) % GLOW_LEN;
  res.b = (0 + ramp(offset + 2, wavelen)) >> 1;
  return res.word;
}




/*
   Flash
*/

uint8_t flashiness;

void initFlash() {
  flashiness = random(0, 3);
}
uint32_t pixelFlash(uint8_t pos) {

  if ( random(flashiness) == 0) {
    if ( pos == random(LEN))
      return   0xaa6622 ;
  }
  return 0;
}

/*
   Runner
*/
uint32_t pixelRunner(uint8_t pos) {
  if (pos % (LEN / 2) == (tictoctac / 4) %  ( LEN / 2))
    return 0xffddaa ;
  return 0;
}

/*
   Plasma
*/

uint8_t plasmaSpeed;
rgb_t plasmaFrom, plasmaTo;
uint32_t plasmaProgress;
rgb_t plasmaColor;

void initPlasma() {
  plasmaSpeed = 40 + random(40);
}
void iteratePlasma() {

  plasmaProgress = tictoctac % plasmaSpeed;

  if (plasmaProgress == 0) {
    plasmaFrom = plasmaTo;
    plasmaTo.word = adjustBrightness(getRandomColor(20), 64);

    plasmaTo.r += 30;
  }

  for (uint8_t i = 0; i < 3; i++) {
    plasmaColor.byte[i] = plasmaFrom.byte[i] * (plasmaSpeed - plasmaProgress) / plasmaSpeed +
                          plasmaTo.byte[i] * plasmaProgress / plasmaSpeed;
  }
}

uint32_t pixelPlasma(uint8_t pos) {
  return plasmaColor.word;
}

/*
   Wave of colors
*/

uint32_t waveOffset;
uint8_t waveSpeed;
uint16_t waveLen;

void initWave() {
  waveSpeed =  random(2, 4);
  waveLen = waveSpeed * LEN;
}
void iterateWave() {

  waveOffset++;
  waveOffset = waveOffset % waveLen;
}

uint32_t pixelWave(uint8_t pos) {

  uint32_t p = pos * waveSpeed + waveOffset;
  p = p % waveLen;
  uint8_t n = r3(p, waveLen);


  return adjustBrightness( 0xFFaa11, n);
}




