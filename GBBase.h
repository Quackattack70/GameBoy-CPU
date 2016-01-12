#ifndef GBBASE_H
#define GBBASE_H

#include <stdint.h>

typedef enum {
    GB_GRAPHICS, GBC_GRAPHICS
} GraphicsType;

static GraphicsType mainGraphics;
static bool running = true;

namespace LCDCONT {
    static uint8_t operation;
    static uint8_t tileadd;
    static uint8_t windowdis;
    static uint8_t tilepadd;
    static uint8_t backtileadd;
    static uint8_t spritesize;
    static uint8_t color0dis;
    static uint8_t backdis;
}

typedef enum {
    GB_WHITE = 0,
    GB_LIGHTGRAY = 1,
    GB_DARKGRAY = 2,
    GB_BLACK = 3
} GBOldColor;

typedef struct {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} GBNewColor;

struct GBColor {
#if mainGraphics == GBC_GRAPHICS
    GBNewColor color;
#elif mainGraphics == GB_GRAPHICS
    GBOldColor color;
#endif
};

typedef struct {
    GBColor pixels[64];
} GBTile;

typedef struct {
    GBColor pixels[128];
    uint8_t x;
    uint8_t y;
    bool yflip;
    bool xflip;
    bool ground;
    bool palette;
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
    uint8_t memory[0xFFFF]; // This is not a pointer for segfault reasons
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