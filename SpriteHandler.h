#ifndef SPRITEHANDLER_H
#define SPRITEHANDLER_H

#include "GBBase.h"

class SpriteHandler {
public:
    GBSprite* sprites[40];
    SpriteHandler();
    void initSprites(GBState*);
};

#endif

