#ifndef STATE_H
#define STATE_H
typedef struct {
  long frame = 0;
  int score  = 0;
  char msg;
  bool dirty = false;
  bool flash = false;

  int dinoTop = 0;
} DinoRunState;
#endif

void tick(DinoRunState state);
