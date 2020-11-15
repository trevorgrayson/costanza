#include "DinoRun/state.h"
//#include "time.h"

#define UPDATE_INTERVAL 100
#define FLASH_BTN 0

State state;

void start() {
  //state.frame = millis();
  pinMode(FLASH_BTN, INPUT);
}

void (*setups[]) () = { 
  viewSetup, start, render, viewRender
};

void tick() {
  dinorun(&state);
  // state.flash = !digitalRead(FLASH_BTN); 
}

void render() {
  dinoView(state, 1);
  dinoView(state, 0);
  viewRender();
  delay(50);
}

bool shouldRender() {
  if (state.frame % UPDATE_INTERVAL == 0) {
    state.score++;
    return true;
  }
  return false;
}


void (*befores[]) () = { 
};

void (*afters[]) () = { 
};

#include "framework/framework.h"
