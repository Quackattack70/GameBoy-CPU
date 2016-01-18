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

void TileHandler::getTilesFromFile(GBState* state){
    if (mainGraphics == GB_GRAPHICS){
        uint16_t tileadd;
        uint16_t tileend;

        if (LCDCONT::tileadd == 1){
            tileadd = 0x9C00;
            tileend = 0x9FFF;
        } else {
            tileadd = 0x9800;
            tileend = 0x9BFF;
        }

        int currentT = 0;
        int currentP = 0;
        uint8_t tilepal[4] = {0, 0, 0, 0};
        for (tileadd; tileadd < tileend; tileadd += 16){
            for (int i = 0; i < 16; i++){
                tilepal[0] = (state->memory[tileadd+i] & 0b11000000) >> 6;
                tilepal[1] = (state->memory[tileadd+i] & 0b00110000) >> 4;
                tilepal[2] = (state->memory[tileadd+i] & 0b00001100) >> 2;
                tilepal[3] = (state->memory[tileadd+i] & 0b00000011);
                
                for (int t = 0; t < 4; t++){
                    switch(tilepal[t]){
                        case 0x00:
                           state->tiles[currentT].pixels[currentP+t].oldC =
                                   GB_BLACK;
                           break;
                        case 0x01:
                            state->tiles[currentT].pixels[currentP+t].oldC =
                                    GB_DARKGRAY;
                            break;
                        case 0x02:
                            state->tiles[currentT].pixels[currentP+t].oldC =
                                    GB_LIGHTGRAY;
                            break;
                        case 0x03:
                            state->tiles[currentT].pixels[currentP+t].oldC =
                                    GB_WHITE;
                            break;
                    }
                }
                
                currentP += 4;
            }
            currentT++;
        }
    }
}

