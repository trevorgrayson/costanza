#include "ssd1306.h"
#include "nano_gfx.h"

#include "DinoRun/state.h"
#include "DinoRun/images.h"

#include <TFT_eSPI.h>                 // Include the graphics library (this includes the sprite functions)

TFT_eSPI    tft = TFT_eSPI();         // Declare object "tft"
TFT_eSprite dino = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object

// Set delay after plotting the sprite
#define DELAY 1000

// Width and height of sprite
#define WIDTH  240
#define HEIGHT 135

int top;
int dinoTop=0;

int CACTI_COUNT=1;
int SPEED=1;
TFT_eSprite cact = TFT_eSprite(&tft);

int SPRITE_HEIGHT = 14;
int SPRITE_WIDTH  = 14;

void viewSetup() {
    tft.init();
    // tft.begin(); tft.width(); tft.height();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    dino.createSprite(WIDTH, HEIGHT);
//    for (int x=0; x<CACTI_COUNT; x++) {
    cact.createSprite(WIDTH, HEIGHT);
//    }
}

void clear() { ssd1306_clearScreen(); }

void dinosaur(DinoRunState state) {
    dinoTop = HEIGHT - (1 + state.dinoTop) * SPRITE_HEIGHT;
    dino.fillSprite(TFT_BLACK); // clear last frame
    dino.drawXBitmap(0, dinoTop, dinosaur_bits,
                    SPRITE_HEIGHT, SPRITE_HEIGHT,
                    TFT_GREEN);
    //dino.drawRect(0, 0, WIDTH, HEIGHT, TFT_BLACK);
}

void cactus(int16_t offset) {
    cact.drawXBitmap(
            offset*SPRITE_WIDTH,
            HEIGHT - SPRITE_HEIGHT, cactus_bits,
            SPRITE_HEIGHT, SPRITE_WIDTH,
            TFT_GREEN);
    for (int x=0; x<CACTI_COUNT; x++) {
    }
}

void viewRender() {
    dino.pushSprite(0, 0);
    cact.pushSprite(0, 0);
}

// spr.setTextDatum(MC_DATUM);
// spr.drawString("it's a boy", 0, HEIGHT / 2, 4);