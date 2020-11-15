#ifndef STATE_H
#define STATE_H
typedef struct {
  long frame = 0;
  int score  = 0;
  char msg;
  bool dirty = false;
  bool flash = false;
} State;
#endif

void tick(State state);
