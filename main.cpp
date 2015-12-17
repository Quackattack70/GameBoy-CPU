#include <stdio.h>
#include "GameRender.h"

int main(int argc, char** argv) {
    GameRender* render = new GameRender();
    render->init();
    render->loop();
    return 0;
}

