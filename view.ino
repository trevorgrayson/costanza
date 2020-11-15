#include "SSD1306.h"        // legacy: #include "SSD1306.h"
#include "SSD1306Wire.h"        // legacy: #include "SSD1306.h"
#include "images.h"
#include "DinoRun/state.h"

#define CACTI_COUNT 2
SSD1306Wire display(0x3c, SDA, SCL, 
                    GEOMETRY_128_32);  
// ADDRESS, SDA, SCL, OLEDDISPLAY_GEOMETRY  -  Extra param required for 128x32 displays.

int counter = 0;

char buffer[16];
char *format = "hi %04ld";

void drawProgressBarDemo() {
  counter++;
  if (counter == 100) {
    counter = 0;
  }
  int progress = (counter / 5) % 100;
  // draw the progress bar
  display.drawProgressBar(0, 32, 120, 10, progress);

  // draw the percentage as String
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.drawString(64, 15, String(progress) + "%");
}

void viewSetup() {
  display.init();
  display.flipScreenVertically();
  display.displayOn();
  display.setFont(ArialMT_Plain_10); // 16
  display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void print(String s) {
  display.drawString(0, 0, s);
}

void printOn(String s, int line) {
  display.drawString(10*line, 0, s);
}

void showHiScore(State state) {
  //display.setTextAlignment(TEXT_ALIGN_RIGHT);
  sprintf(buffer, format, state.score);
  display.drawString(80, 0, (String)buffer);
  //display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void printFrame(int count) {
  display.drawString(0, 20, String(count));
}

void isPressed() {
  display.drawString(12, 20, "PRESSED");
}

void printWifiStatus(bool online) {
  if(online) {
    display.drawString(118, 16, "x");
  } else {
    display.drawString(118, 16, "o");
  }

}

void viewRender()      { display.display(); }
void clear()           { display.clear(); }

/*
 * dinorun
  dinorun(state);
 */
int HEIGHT = 32;
int top;

int sprites[CACTI_COUNT] = {0,0};

void dinorun(State *state) {
  state->frame++;
  if (!state->flash) state->score++;
}

void dinoView(State state, int color) {
  display.setColor((OLEDDISPLAY_COLOR)color);
  //showHiScore(state);
  dinosaur(state);
  cacti(state);
}

void dinosaur(State state) {
  bool jump = state.flash;
  if (jump) top = 0; 
  else top = HEIGHT - 14;
  display.drawXbm(0, top, 
                  14, 14, 
                  dinosaur_bits);
}

void cactus(int16_t offset) {
  display.drawXbm(offset, (HEIGHT-cactus_height), 
                  cactus_width, cactus_height, 
                  cactus_bits);
}

void cacti(State state) {
    for(int x=0; x<CACTI_COUNT; x++) {
      if(sprites[x] > 0) {
        sprites[x] = sprites[x] - 1;
        cactus(sprites[x]);
      } else {
        if(state.frame%50==0 && sprites[x+1] == 0) {
            sprites[x] = 120;
        }
      }
    }
}
