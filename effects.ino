

Fx glow  = {
  .init = &dummy,
  .iterate = &iterateGlow,
  .pixel = pixelGlow
};

Fx flash  = {
  .init = &dummy,
  .iterate = &dummy,
  .pixel = pixelFlash
};

Fx runner  = {
  .init = &dummy,
  .iterate = &dummy,
  .pixel = pixelRunner
};


Fx plasma  = {
  .init = &dummy,
  .iterate = &iteratePlasma,
  .pixel = pixelPlasma
};

Fx wave  = {
  .init = &dummy,
  .iterate = &iterateWave,
  .pixel = pixelWave
};

Fx counter  = {
  .init = &dummy,
  .iterate = &dummy,
  .pixel = pixelCounter
};

void dummy() {
}


/*
    Glow
*/
void initGlow() {
}

void iterateGlow() {
}

uint32_t pixelGlow(uint8_t pos) {

  return hueToColor(tic, 255);

  uint32_t p = tictoctac % 147;
  uint32_t q = tictoctac / 147;


  uint8_t hue = q * 37;
  return hueToColor(hue, hut(p * 256 / 147));
}

/*
   Flash
*/
uint32_t pixelFlash(uint8_t pos) {

  if ( random(FLASHINESS) == 0) {
    if ( pos == random( LEN))
      return   0xFFddaa ;
  }
  return 0;
}

/*
   Runner
*/
uint32_t pixelRunner(uint8_t pos) {
  return pos == (tictoctac / 4) %   LEN ? 0xffddaa : 0;
}

/*
   Plasma
*/

#define PLASMA_SPEED 40
rgb_t plasmaFrom, plasmaTo;
uint32_t plasmaProgress;
rgb_t plasmaColor;

void iteratePlasma() {

  plasmaProgress = tictoctac % PLASMA_SPEED;

  if (plasmaProgress == 0) {
    plasmaFrom = plasmaTo;
    plasmaTo.word = getRandomColor(20);
  }

  for (uint8_t i = 0; i < 3; i++) {
    plasmaColor.byte[i] = plasmaFrom.byte[i] * (PLASMA_SPEED - plasmaProgress) / PLASMA_SPEED +
                          plasmaTo.byte[i] * plasmaProgress / PLASMA_SPEED;
    //plasmaColor.byte[i] = c;
  }
  //  plasmaColor.byte[i] = //
  //    plasmaTo.byte[i] * plasmaProgress / PLASMA_SPEED;
}

uint32_t pixelPlasma(uint8_t pos) {
  return plasmaColor.word;
}

/*
   Wave of colors
*/

#define WAVE_SPEED 1
#define WAVE_N LEN * WAVE_SPEED

rgb_t waveColor;
uint32_t waveOffset = 0;

void iterateWave() {

  waveColor.word = 0xFFaa11;

  waveOffset++;
  //waveOffset= WAVE_N/2;

  waveOffset = waveOffset % WAVE_N;


}

uint32_t pixelWave(uint8_t pos) {

  uint32_t p = pos * WAVE_SPEED + waveOffset ;
  p = p % WAVE_N;
  uint8_t n = ramp(p, WAVE_N);


  //waveColor.b = n;
  //return waveColor.word;
  return adjustBrightness( waveColor.word, n);

}


/*
   Counter
*/

uint32_t pixelCounter(uint8_t pos) {

  uint32_t res = 0;
  if (pos == toc)
    return  0xff00;
  if (pos == tac)
    return 0xff;

  return res;
}

