#ifndef TILEHANDLER_H
#define TILEHANDLER_H

#include "GBBase.h"

typedef struct {
    int x, y;
    GBTile tile;
} TilePos;

class TileHandler {
public:
    TilePos positions[360];
    void initTiles(GBState*);
    TileHandler();
};

#endif

