#include "Arduino.h"

#ifndef STATE_H
#define STATE_H
typedef struct {
  long frame = 0;
  int score  = 0;
  char msg;
  bool dirty = false;
  bool flash = false;
  bool fin = false;

  int dinoTop = 0;
  int cacti[5] = {200, 250, 330, 380, 430};
  int cactusSpeed = 10;
} DinoRunState;
#endif

void tick(DinoRunState state);
