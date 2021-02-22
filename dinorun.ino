#include "DinoRun/dinorun.h"
#include "DinoRun/state.h"
#include "DinoRun/view.h"

#define UPDATE_INTERVAL 100
#define FLASH_BTN 0

DinoRunState state;

void setup() {
  pinMode(FLASH_BTN, INPUT);
  viewSetup();
}

void loop() {
  state.flash = digitalRead(FLASH_BTN);
  if (state.dinoTop != !state.flash) {
      state.dirty = 1;
  }
  state.dinoTop = !state.flash; // 0 or 1
  bootstrapDinoRun(state);
}
