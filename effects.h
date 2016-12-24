
#ifndef _EFFECTS_H
#define _EFFECTS_H

typedef struct {
  void (*init) ();
  void (*iterate) ();
  uint32_t (*pixel) (uint8_t pos);

} Fx;

extern Fx flash, glow, runner, plasma, wave, counter, rainbow;

Fx fxs[]= {flash, rainbow, plasma, wave, rainbow};

#endif
