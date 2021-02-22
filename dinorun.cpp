//
// Created by Trevor Grayson on 2/21/21.
//

#include "DinoRun/dinorun.h"

void bootstrapDinoRun(DinoRunState state) {
    dinosaur(state);
    cactus(2);
    viewRender();
}
