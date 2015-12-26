#include "GameRender.h"

int main(int argc, char** argv) {
    GameRender* render = new GameRender(argv[1]);
    render->loop();
    return 0;
}

