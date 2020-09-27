#define UPDATE_INTERVAL 5000

struct State {
  long frame = 0;
  int score  = 0;
  String msg = "loading...";
  bool dirty = false;
  bool flash = false;
} state;

void start() {
  Serial.begin(115200);
  print(state.msg);
}

void (*setups[]) () = { 
  viewSetup, start, viewRender 
};

void tick() {
  state.dirty = true;
}

void render() {
  print("hello4");
}

void (*befores[]) () = { 
  clear
};

void (*afters[]) () = { 
  viewRender
};

#include "framework/framework.h"
