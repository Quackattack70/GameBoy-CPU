#include "TileHandler.h"

TileHandler::TileHandler() {};

void TileHandler::initTiles(GBState* state){
    int loc = 0;
    for(loc = 0; loc < 20; loc++){
         GBTile pos = state->tiles[loc];
         this->positions[loc] = pos;
         loc++;
    }
}

