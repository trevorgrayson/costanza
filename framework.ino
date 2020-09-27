#define UPDATE_INTERVAL 5000
// async - non blocking
// multiple concerns
// CQRS MVP patterns

struct State {
  long frame = 0;
  int score  = 0;
  String msg = "loading...";
  bool dirty = false;
  bool flash = false;
} state;

void start() {
  Serial.begin(115200);
}

void tick() {
  print("hello");
}

void update() { // rename to poll
}

void render() {
}

#include "framework/framework.h"
