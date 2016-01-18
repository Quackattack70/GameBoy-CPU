#include "debug.h"

void printLCDCONT(){
    printf("Tile Location(0x9C00): %02x\n", LCDCONT::tileadd);
    printf("Sprite Size(128 pix): %02x\n", LCDCONT::spritesize);
}

void printRegs(GBState* s){
    printf("A: %02x\n", s->a);
    printf("F: %02x\n", s->f);
    printf("B: %02x\n", s->b);
    printf("C: %02x\n", s->c);
    printf("D: %02x\n", s->d);
    printf("E: %02x\n", s->e);
    printf("H: %02x\n", s->h);
    printf("L: %02x\n", s->l);
    printf("PC: %04x\n", s->pc);
    printf("SP: %04x\n", s->sp);
}
