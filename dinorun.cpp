//
// Created by Trevor Grayson on 2/21/21.
//

#include "DinoRun/dinorun.h"

int CACTUS_LEFT_MARGIN = 15;

void progress(DinoRunState *state) {
    for(int x=0; x < 1; x++) {
        if( state->frame % 10 == 0 ) {
            state->cacti[0]--;
        }
        if ( state->cacti[x] < -CACTUS_LEFT_MARGIN) {
            state->cacti[x] = 200 + x*5;
        }
    }
}

// check if the dino is colliding with a cactus.
void isDead(DinoRunState *state) {
    state->fin = state->dinoTop == 0 && \
        state->cacti[0] < 20 &&
        state->cacti[0] > -10;
}

void dinoRunTick(DinoRunState *state) {
    state->frame++;
    if(state->frame % 100 == 0) {
        state->score++;
    }
    hiscore(state->score);
    isDead(state);
    dinosaur(*state);
    cactus(*state);
    viewRender();
    progress(state);
}

// NOTE: Having a previous state would make
// erasing sprites easy.