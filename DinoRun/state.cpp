#include "DinoRun/state.h"

void tick(State state) {
  state.frame++;
  if(state.frame%1000) state.dirty = true;
}

