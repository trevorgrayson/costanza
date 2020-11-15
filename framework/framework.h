#include "cron.h"

void (*frameworkSetups[]) () = {
  cronSetup
};

bool shouldRender();

void setup() {
  size_t n = sizeof(setups) / sizeof(setups[0]);
  for(int x=0; x<n; x++) {
    setups[x]();
  }
  n = sizeof(frameworkSetups) / sizeof(frameworkSetups[0]);
  for(int x=0; x<n; x++) {
    frameworkSetups[x]();
  }
}

void runBefores() {
  size_t n = sizeof(befores) / sizeof(befores[0]);
  for(int x=0; x<n; x++) {
    befores[x]();
  }
}

void runAfters() {
  size_t n = sizeof(afters) / sizeof(afters[0]);
  for(int x=0; x<n; x++) {
    afters[x]();
  }
}

void loop() {
  runBefores();
  tick();  // runs every cycle
  //// update: heavy requests, web polling => cron schedule
  if (shouldRender()) render(); // should update display
  runAfters();
}
