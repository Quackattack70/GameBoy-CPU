#include <stdint.h>

#ifndef GBBASE_H
#define GBBASE_H

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
    uint8_t* memory;
    uint16_t af;
    uint16_t bc;
    uint16_t de;
    uint16_t hl;
    uint16_t pc;
    uint16_t sp;
} GBState;


#endif 

