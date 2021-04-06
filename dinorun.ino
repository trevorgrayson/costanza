#include "DinoRun/dinorun.h"

#define UPDATE_INTERVAL 100
#define FLASH_BTN 0

DinoRunState previous;
DinoRunState state;

int HANG_TIME = 50;
int buttonFrame = 999999;  // Bug
bool GROUNDED = false;

bool JUMPING = true;
bool RUNNING = false;

void setup() {
    pinMode(FLASH_BTN, INPUT);
    dinoSetup();
}

bool mustFall() {
    return state.frame - buttonFrame > HANG_TIME;
}

void readHardware() {
    state.flash = digitalRead(FLASH_BTN);
    if(state.flash == 1) {
        GROUNDED = false;
        buttonFrame = 999999;
    }
    if (state.dinoTop != !state.flash) {
        state.dirty = true;
        buttonFrame = state.frame;
    }
    state.dinoTop = !state.flash; // 0 or 1

    if(mustFall() | GROUNDED) {
        state.dinoTop = RUNNING;
        GROUNDED = true;
    }
}

void loop() {
    readHardware();
    dinoRunTick(&state);
}
