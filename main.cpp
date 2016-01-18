#include "GameRender.h"
#include "debug.h"

int main(int argc, char** argv) {
    GameRender* render = new GameRender(argv[1]);
    render->loop();
    printLCDCONT();
    printRegs(&render->state);
    return 0;
}