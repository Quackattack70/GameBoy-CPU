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
        for (tileadd; tileadd < tileend; tileadd += 16){
            for (int i = 0; i < 16; i++){
                uint8_t bitp1 = (state->memory[tileadd+i] & 0b11000000) >> 6;
                uint8_t bitp2 = (state->memory[tileadd+i] & 0b00110000) >> 4;
                uint8_t bitp3 = (state->memory[tileadd+i] & 0b00001100) >> 2;
                uint8_t bitp4 = (state->memory[tileadd+i] & 0b00000011);

                state->tiles[currentT].pixels[currentP].oldC = (GBOldColor)bitp1;
                state->tiles[currentT].pixels[currentP+1].oldC = (GBOldColor)bitp2;
                state->tiles[currentT].pixels[currentP+2].oldC = (GBOldColor)bitp3;
                state->tiles[currentT].pixels[currentP+3].oldC = (GBOldColor)bitp4;

                currentP += 4;
            }
            currentT++;
        }
    }
}

