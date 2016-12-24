/*      _
   fn: / \
*/
uint32_t hut(uint8_t n) {
  if (n < 86)
    return n * 3;
  if (n < 170)
    return 255;
  return (255 - (n - 170) * 3);
}

/* fn:
     /\
    /  \
*/
uint32_t ramp(uint8_t n) {
  return n < 128 ? n : 255 - n ;
}
uint8_t ramp(uint16_t n, uint16_t len) {
  n = n % len;
  if (n > len / 2)
    n =  len - n;

  //n = n * 2 * 255 / len;
  n = ((n << 9) - n - n ) / len;

  return n;
}

uint32_t r3(uint16_t n, uint16_t len) {
  if (n > len / 3)
    if (n < len * 2 / 3)
      n =  len - n;
    else
      n = 0;

  n = n * 3 * 255 / len;
  return n;
}

/*      _
   fn: / \_
*/
uint32_t trig(uint8_t n) {
  if (n < 64)
    return n * 4;
  if (n < 128)
    return 255;
  if (n < 192)
    return (255 - (n - 128) * 4);
  return 0;
}



/*
   fn: /\__
*/
uint32_t tooth(uint8_t n) {
  if (n < 64)
    return n * 4;
  if (n < 128)
    return (255 - (n - 64) * 4);
  return 0;
}

uint32_t adjustBrightness(uint32_t color, uint8_t b) {

  rgb_t res;
  res.word = color;

  for (uint8_t i = 0; i < 3; i++)
    res.byte[i] = (res.byte[i] * b) >> 8;

  return res.word;
}


#

uint32_t getRandomColor(uint8_t minBrightness) {

  rgb_t res;
  uint8_t mb3 = minBrightness + minBrightness + minBrightness;

  do {
    res.r = random (255);
    res.g = random (255);
    res.b = random (255);
  } while ( (res.r + res.g + res.b) < mb3);

  return res.word;
}


// this one seems broken
#define HUE_SEG 255/6

uint32_t hueToColor(uint8_t hue, uint8_t bri) {
  uint32_t p = hue % HUE_SEG;
  uint8_t q = hue / HUE_SEG;

  uint32_t n = p * bri / HUE_SEG;
  uint32_t m = bri - n;

  if (q == 0)
    return m << 16 | n << 8;
  if (q == 1)
    return n << 16 | m << 8;
  if (q == 2)
    return m << 8 | n;
  if (q == 3)
    return n << 8 | m;
  if (q == 4)
    return m | n << 16;
  if (q == 5)
    return n | m << 16;

  return 0x0;
}



