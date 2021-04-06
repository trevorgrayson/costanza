//
// Created by Trevor Grayson on 2/21/21.
//

#include "DinoRun/dinorun.h"

int CACTUS_LEFT_MARGIN = 30;

void progress(DinoRunState *state) {
    for(int x=0; x < 4; x++) {
        if( state->frame % 10 == 0 ) {
            state->cacti[x] = state->cacti[x] - state->cactusSpeed;
        }
        if ( state->cacti[x] < -CACTUS_LEFT_MARGIN) {
            state->cacti[x] = 200 + x*5;
        }
    }
}

bool isStanding(DinoRunState state) {
    return state.dinoTop == 0;
}

bool isJumping(DinoRunState state) {
    return !isStanding(state);
}

// check if the dino is colliding with a cactus.
bool isDead(DinoRunState *state) {
    state->fin = 0;
    if(isStanding(*state)) {
        for(int x=0; x < 4; x++) {
            state->fin = \
                state->cacti[x] < 20 &&
                state->cacti[x] > -10;

            if(state->fin) return state->fin;
        }
    }

    return state->fin;
}

void dinoRunTick(DinoRunState *state) {
    state->frame++;
    // update state
    if(!isDead(state)) {
        if(state->frame % 100 == 0) {
            state->score++;
        }
        progress(state);
    } 

    // render
    hiscore(state->score);
    dinosaur(*state);
    cactus(*state);
    viewRender();
    delay(10);
}

// NOTE: Having a previous state would make
// erasing sprites easy.
