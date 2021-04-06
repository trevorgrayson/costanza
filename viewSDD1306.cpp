#include "ssd1306.h"
#include "nano_gfx.h"

#include "DinoRun/state.h"
#include "DinoRun/images.h"

#include <TFT_eSPI.h>                 // Include the graphics library (this includes the sprite functions)


TFT_eSPI    tft = TFT_eSPI();         // Declare object "tft"
TFT_eSprite dino = TFT_eSprite(&tft);  // Declare Sprite object "spr" with pointer to "tft" object
TFT_eSprite score = TFT_eSprite(&tft); // Sprite object stext1
TFT_eSprite cact[] = {
    TFT_eSprite(&tft),
    TFT_eSprite(&tft),
    TFT_eSprite(&tft),
    TFT_eSprite(&tft),
    TFT_eSprite(&tft)
};
int CACTI_COUNT=4;

// Set delay after plotting the sprite
#define DELAY 1000

// Width and height of sprite
#define WIDTH  240
#define HEIGHT 135

int top;
int dinoTop=0;

int cact_x = WIDTH - cactus_width;

int SPRITE_HEIGHT = 28;
int SPRITE_WIDTH  = 28;
char scoreHUD[] = "HI 000000";
int b = 0;


void dinoSetup() {
    tft.init();
    // tft.begin(); tft.width(); tft.height();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    dino.createSprite(dinosaur_width, dinosaur_height);
    for (int x=0; x<CACTI_COUNT; x++) {
        cact[x].createSprite(cactus_width, cactus_height);
    }

    // Score HUD
    score.createSprite(WIDTH, 20);
    score.setTextColor(TFT_WHITE);
    // score.fillSprite(TFT_DARKGREY);
}

void clear() { ssd1306_clearScreen(); }

void hiscore(int value) {
    // score.setTextDatum(TR_DATUM);
    score.setTextColor(TFT_BLACK);
    score.drawString(scoreHUD, 5, 5, 2);
    score.setTextColor(TFT_WHITE);
    sprintf(scoreHUD, "HI %04d", value);
    score.drawString(scoreHUD, 5, 5, 2);
    score.pushSprite(WIDTH - 60, 0);
}

void dinosaur(DinoRunState state) {
    dino.fillSprite(TFT_BLACK); // clear last frame
    dino.pushSprite(0, dinoTop);

    dinoTop = HEIGHT - (1 + state.dinoTop) * SPRITE_HEIGHT;
    if (state.fin) {
        dino.drawXBitmap(
            0, 0, dinosaur_bits,
            dinosaur_width, dinosaur_height,
            TFT_RED);
    } else {
        dino.drawXBitmap(
            0, 0, dinosaur_bits,
            dinosaur_width, dinosaur_height,
            TFT_GREEN);
    }

    dino.pushSprite(0, dinoTop);
}

void cactus(DinoRunState state) {
    // can you do this once at startup?
    dino.fillSprite(TFT_BLACK); // clear last frame
    for (int x=0; x<CACTI_COUNT; x++) {
        cact[x].drawXBitmap(
            0, 0, cactus_bits,
            cactus_width, cactus_height,
            TFT_BLACK);
        cact[x].pushSprite(
            state.cacti[x] + state.cactusSpeed,
            HEIGHT - cactus_height);

        cact[x].drawXBitmap(
            0, 0, cactus_bits,
            cactus_width, cactus_height,
            TFT_GREEN);
        cact[x].pushSprite(
            state.cacti[x],
            HEIGHT - cactus_height);
    }
}

void viewRender() {}

// spr.setTextDatum(MC_DATUM);
// spr.drawString("it's a boy", 0, HEIGHT / 2, 4);
