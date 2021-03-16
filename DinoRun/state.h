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
  int cacti[5] = {200, 0, 0, 0, 0};
  int cactusSpeed = 5;
} DinoRunState;
#endif

void tick(DinoRunState state);
