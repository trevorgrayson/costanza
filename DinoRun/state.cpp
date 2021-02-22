#include "DinoRun/state.h"

void tick(DinoRunState state) {
  state.frame++;
  if(state.frame%1000) state.dirty = true;
}

