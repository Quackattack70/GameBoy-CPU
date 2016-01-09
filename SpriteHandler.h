#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include "GBBase.h"

class SpriteHandler {
    GBSprite* sprites[40];
    void initSprites(GBState*);
};

#endif

