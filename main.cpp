#include "GameRender.h"

int main(int argc, char** argv) {
    GameRender* render = new GameRender("pokesilver.gbc");
    render->loop();
    return 0;
}

