#ifndef GBBASE_H
#define GBBASE_H

#include <stdint.h>

typedef struct {
    uint8_t pixels[64];
} GBTile;

typedef struct {
    GBTile spaces[2];
    uint8_t isLarge;
    uint16_t loc;
} GBSprite;

typedef struct {
    uint8_t z;
    uint8_t c;
    uint8_t h;
    uint8_t n;
} GBFlags;

typedef struct {
    uint8_t a;
    uint8_t f;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t h;
    uint8_t l;
    GBFlags flags;
    uint8_t memory[0x7FFF]; // This is not a pointer for segfault reasons
    GBTile tiles[512]; /* about 360 are shown on the screen, the rest is 
    not drawn */
    GBSprite sprites[40];
    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;
    uint16_t pc;
    uint16_t sp;
} GBState;


#endif 