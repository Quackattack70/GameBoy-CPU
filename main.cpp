#include <stdio.h>
#include "GBBase.h"
#include "GBFuncs.h"
#include "TileHandler.h"

int main(int argc, char** argv) {
    GBColor c;
    c.newC.r = 0b11111;
    c.newC.g = 0b11111;
    c.newC.b = 0b11111;
    c.defineColorInt();
    printf("%i", c.colorint);
    return 0;
}

