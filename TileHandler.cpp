#include "TileHandler.h"

TileHandler::TileHandler() {};

void TileHandler::initTiles(GBState* state){
    int loc = 0;
    for(int i = 0; i < 20; i++){
        for(int n = 0; n < 18; n++){
            TilePos pos;
            pos.tile = state->tiles[loc];
            pos.x = i;
            pos.y = n;
            this->positions[loc] = pos;
            loc++;
        }
    }
}

