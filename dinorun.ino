#include "DinoRun/dinorun.h"

#define UPDATE_INTERVAL 100
#define FLASH_BTN 0

DinoRunState previous;
DinoRunState state;

void setup() {
    pinMode(FLASH_BTN, INPUT);
    dinoSetup();
}

void readHardware() {
    state.flash = digitalRead(FLASH_BTN);
    if (state.dinoTop != !state.flash) {
        state.dirty = 1;
    }
    state.dinoTop = !state.flash; // 0 or 1
}

void loop() {
    readHardware();
    dinoRunTick(&state);
}
