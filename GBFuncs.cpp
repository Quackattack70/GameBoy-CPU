#include "GBFuncs.h"

void setColorCompatible(GBState* state){
    if (state->memory[0x143] == 0x80){
        mainGraphics = GBC_GRAPHICS;
    } 
    else if (state->memory[0x143] == 0x00){
        mainGraphics = GB_GRAPHICS;
    }
}

void PrintLCDCONT(){
    printf("Tile Location(0x9C00): %02x\n", LCDCONT::tileadd);
    printf("Sprite Size(128 pix): %02x\n", LCDCONT::spritesize);
}

void combineRegs(GBState* state){
    state->bc = (state->b << 8) | state->c;
    state->af = (state->a << 8) | state->f;
    state->de = (state->d << 8) | state->e;
}

void setFlagsInF(GBState* state){
    state->f = (state->flags.z << 7) | (state->flags.n << 6);
    state->f = state->f | (state->flags.h << 5) | (state->flags.c << 4);
}

void INC_rr(uint8_t* a1, uint8_t* a2){
    uint16_t a = (a1[0] << 8) | a2[0] + 1;
    a1[0] = (a & 0xF0) >> 8;
    a2[0] = (a & 0x0F);
}

void DEC_rr(uint8_t* a1, uint8_t* a2){
    uint16_t a = (a1[0] << 8) | a2[0] - 1;
    a1[0] = (a & 0xF0) >> 8;
    a2[0] = (a & 0xF);
}


void EmulateInstruct(GBState* state){
    uint8_t* opcode = &state->memory[state->pc];
    
    switch(opcode[0]){
        case 0x00: break; // NOP
        
        // 8 bit loads
        case 0x06: // LD B,b8
            state->b = opcode[1];
            state->pc++;
            break;
            
        case 0x0E: // LD C,b8
            state->c = opcode[1];
            state->pc++;
            break;
            
        case 0x16: // LD D,b8
            state->d = opcode[1];
            state->pc++;
            break;
            
        case 0x1E: // LD E,b8
            state->e = opcode[1];
            state->pc++;
            break;
            
        case 0x26: // LD H,b8
            state->h = opcode[1];
            state->pc++;
            break;
            
        case 0x2E: // LD L,b8
            state->l = opcode[1];
            state->pc++;
            break;
            
        case 0x36: // LD (HL),b8
            state->memory[state->hl] = opcode[1];
            state->pc++;
            break;
            
        case 0x3E: // LD A,b8
            state->a = opcode[1];
            state->pc++;
            break;
            
        // 16 bit loads yaaaaaay!!!! :)
        case 0x01: // LD BC,b16
            state->b = opcode[1];
            state->c = opcode[2];
            state->pc += 2;
            break;
            
        case 0x11: // LD DE,b16
            state->d = opcode[1];
            state->e = opcode[2];
            state->pc += 2;
            break;
            
        case 0x21: // LD HL,b16
            state->h = opcode[1];
            state->l = opcode[2];
            state->pc += 2;
            break;
            
        case 0x31: // LD SP,b16
            state->sp = (opcode[2] << 8) | opcode[1];
            state->pc += 2;
            break;
        
        // back to 8 bit loads :( :P
        case 0x41: state->b = state->c; break; // LD B,C
        case 0x42: state->b = state->d; break; // LD B,D
        case 0x43: state->b = state->e; break; // LD B,E 
        case 0x44: state->b = state->h; break; // LD B,H
        case 0x45: state->b = state->l; break; // LD B,L
        case 0x46: state->b = state->memory[state->hl]; break; // LD B,(HL)
        case 0x47: state->b = state->a; break; // LD B,A
        case 0x48: state->c = state->b; break; // LD C,B
        case 0x4a: state->c = state->d; break; // LD C,D
        case 0x4b: state->c = state->e; break; // LD C,E
        case 0x4c: state->c = state->h; break; // LD C,H
        case 0x4d: state->c = state->l; break; // LD C,L
        case 0x4e: state->c = state->memory[state->hl]; break; // LD C,(HL)
        case 0x4f: state->c = state->a; break; // LD C,A
        case 0x50: state->d = state->b; break; // LD D,B
        case 0x51: state->d = state->c; break; // LD D,C
        case 0x53: state->d = state->e; break; // LD D,E
        case 0x54: state->d = state->h; break; // LD D,H
        case 0x55: state->d = state->l; break; // LD D,L
        case 0x56: state->d = state->memory[state->hl]; break; // LD D,(HL)
        case 0x57: state->d = state->a; break; // LD D,A
        case 0x58: state->e = state->b; break; // LD E,B
        case 0x59: state->e = state->c; break; // LD E,C
        case 0x5a: state->e = state->d; break; // LD E,D
        case 0x5c: state->e = state->h; break; // LD E,H
        case 0x5d: state->e = state->l; break; // LD E,L
        case 0x5e: state->e = state->memory[state->hl]; break; // LD E,(HL)
        case 0x5f: state->e = state->a; break; // LD E,A
        case 0x60: state->h = state->b; break; // LD H,B
        case 0x61: state->h = state->c; break; // LD H,C
        case 0x62: state->h = state->d; break; // LD H,D
        case 0x63: state->h = state->e; break; // LD H,E
        case 0x65: state->h = state->l; break; // LD H,L
        case 0x66: state->h = state->memory[state->hl]; break; // LD H,(HL)
        case 0x67: state->h = state->a; break; // LD H,A
        case 0x68: state->l = state->b; break; // LD L,B
        case 0x69: state->l = state->c; break; // LD L,C
        case 0x6a: state->l = state->d; break; // LD L,D
        case 0x6b: state->l = state->e; break; // LD L,E
        case 0x6c: state->l = state->h; break; // LD L,H
        case 0x6e: state->l = state->memory[state->hl]; break; // LD L,(HL)
        case 0x6f: state->l = state->a; break; // LD L,A
        case 0x70: state->memory[state->hl] = state->b; break; // LD (HL),B
        case 0x71: state->memory[state->hl] = state->c; break; // LD (HL),C
        case 0x72: state->memory[state->hl] = state->d; break; // LD (HL),D
        case 0x73: state->memory[state->hl] = state->e; break; // LD (HL),E
        case 0x74: state->memory[state->hl] = state->h; break; // LD (HL),H
        case 0x75: state->memory[state->hl] = state->l; break; // LD (HL),L
        case 0x77: state->memory[state->hl] = state->a; break; // LD (HL),A
        case 0x78: state->a = state->b; break; // LD A,B
        case 0x79: state->a = state->c; break; // LD A,C
        case 0x7a: state->a = state->d; break; // LD A,D
        case 0x7b: state->a = state->e; break; // LD A,E
        case 0x7c: state->a = state->h; break; // LD A,H
        case 0x7d: state->a = state->l; break; // LD A,L
        case 0x7e: state->a = state->memory[state->hl]; break; // LD A,(HL)
        
        case 0x04: state->b++; state->flags.n = 0; break; // INC B
        case 0x14: state->d++; state->flags.n = 0; break; // INC D
        case 0x24: state->h++; state->flags.n = 0; break; // INC H
        case 0x34: state->memory[state->hl]++; state->flags.n = 0; break; // INC (HL)
        case 0x0C: state->c++; state->flags.n = 0; break; // INC C
        case 0x1C: state->e++; state->flags.n = 0; break; // INC E
        case 0x2C: state->l++; state->flags.n = 0; break; // INC L
        case 0x3C: state->a++; state->flags.n = 0; break; // INC A
        case 0x33: state->sp++; break; // INC SP
        case 0x03: INC_rr(&state->b, &state->c); break; // INC BC
        case 0x13: INC_rr(&state->d, &state->e); break; // INC DE
        case 0x23: INC_rr(&state->h, &state->l); break; // INC HL
        
        case 0x0B: DEC_rr(&state->b, &state->c); break; // DEC BC
        case 0x1B: DEC_rr(&state->d, &state->e); break; // DEC DE
        case 0x2B: DEC_rr(&state->h, &state->l); break; // DEC HL
        case 0x3B: state->sp--; break; // DEC SP
        case 0x05: state->b--; state->flags.n = 1; break; // DEC B
        case 0x15: state->d--; state->flags.n = 1; break; // DEC D
        case 0x25: state->h--; state->flags.n = 1; break; // DEC H
        case 0x35: state->memory[state->hl]--; state->flags.n = 1; break; // DEC (HL)
        case 0xC3: state->pc = (opcode[2] << 8) | opcode[1]; break; // JP b16
        case 0x76: running = 0; break; // HALT
        case 0xCD: // CALL b12
        {
            uint16_t ret = state->sp + 2;
            state->memory[state->sp-1] = (ret >> 8) & 0xff;
            state->memory[state->sp-2] = (ret & 0xff);
            state->sp -= 2;
            state->pc = (opcode[2] >> 8) | opcode[1];
            break;
        }
        case 0xC9:
            state->pc = state->memory[state->sp] | (state->memory[state->sp+1] << 8);
            state->sp += 2;
            break;
        
        default: fprintf(stderr, "Unimplemented Instruction\n"); break;
    }
    
    state->pc++;
    
    combineRegs(state);
    setFlagsInF(state);
}

void initMemory(GBState* state, char *filename){
    running = true;
    fstream ss(filename);
    string save = "";
    int memloc = 0;
    while (getline(ss, save) && memloc < 0xFFFF){
        for (int i = 0; i < save.size(); i++){
            state->memory[memloc] = save[i];
            memloc++;
        }
    }
}

void initLCDCONT(GBState* state){
    uint8_t lcdcont = state->memory[0xFF40];
    LCDCONT::operation = (lcdcont & 0b10000000) >> 7;
    LCDCONT::tileadd = (lcdcont & 0b01000000) >> 6;
    LCDCONT::windowdis = (lcdcont & 0b00100000) >> 5;
    LCDCONT::tilepadd = (lcdcont & 0b00010000) >> 4;
    LCDCONT::backtileadd = (lcdcont & 0b00001000) >> 3;
    LCDCONT::spritesize = (lcdcont & 0b00000100) >> 2;
    LCDCONT::color0dis = (lcdcont & 0b00000010) >> 1;
    LCDCONT::backdis = (lcdcont & 0b00000001);
}