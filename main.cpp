#include "GameRender.h"

int main(int argc, char** argv) {
    GameRender* render = new GameRender();
    render->loop();
    return 0;
}

