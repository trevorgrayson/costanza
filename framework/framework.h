#include "cron.h"

// void (*setups[]) ();

void (*setups[]) () = {
  start,
  viewSetup,
  cronSetup,
  viewRender
};


void before() {
  clear();
}

void after() {
  state.frame++;
  viewRender();
}

bool shouldRender(State state) {
  bool changed = state.dirty;
  state.dirty = false;
  return changed;
}

void setup() {
  size_t n = sizeof(setups) / sizeof(setups[0]);
  for(int x=0; x<n; x++) {
    setups[x]();
  }
}

void loop() {
  before();
  tick();
  after();
}
