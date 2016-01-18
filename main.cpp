#include "GameRender.h"

int main(int argc, char** argv) {
    GameRender* render = new GameRender(argv[1]);
    PrintLCDCONT();
    return 0;
}