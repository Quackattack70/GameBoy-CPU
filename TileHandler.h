#ifndef TILEHANDLER_H
#define TILEHANDLER_H

#include "GBBase.h"

class TileHandler {
public:
    GBTile positions[360];
    void initTiles(GBState*);
    void getTilesFromFile(GBState*);
    TileHandler();
};

#endif

