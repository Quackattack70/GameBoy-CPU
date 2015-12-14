
#include "GBFuncs.h"

void combineRegs(GBState* state){
    state->bc = (state->b << 8) | state->c;
    state->af = (state->a << 8) | state->f;
    state->de = (state->d << 8) | state->e;
}

void setFlagsInF(GBState* state){
    state->f = (state->flags.z << 7) | (state->flags.n << 6);
    state->f = state->f | (state->flags.h << 5) | (state->flags.c << 4);
}

void EmulateInstruct(GBState* state){
    uint8_t* opcode = &state->memory[state->currentb];
    
    switch(opcode[0]){
        case 0x00: break; // NOP
        
        // 8 bit loads
        case 0x06: // LD B,b8
            state->b = opcode[1];
            state->currentb++;
            break;
            
        case 0x0E: // LD C,b8
            state->c = opcode[1];
            state->currentb++;
            break;
            
        case 0x16: // LD D,b8
            state->d = opcode[1];
            state->currentb++;
            break;
            
        case 0x1E: // LD E,b8
            state->e = opcode[1];
            state->currentb++;
            break;
            
        case 0x26: // LD H,b8
            state->h = opcode[1];
            state->currentb++;
            break;
            
        case 0x2E: // LD L,b8
            state->l = opcode[1];
            state->currentb++;
            break;
            
        case 0x36: // LD (HL),b8
            state->memory[state->hl] = opcode[1];
            state->currentb++;
            break;
            
        case 0x3E: // LD A,b8
            state->a = opcode[1];
            state->currentb++;
            break;
            
        // 16 bit loads yaaaaaay!!!! :)
        case 0x01: // LD BC,b16
            state->b = opcode[1];
            state->c = opcode[2];
            state->currentb += 2;
            break;
            
        case 0x11: // LD DE,b16
            state->d = opcode[1];
            state->e = opcode[2];
            state->currentb += 2;
            break;
            
        case 0x21: // LD HL,b16
            state->h = opcode[1];
            state->l = opcode[2];
            state->currentb += 2;
            break;
            
        case 0x31: // LD SP,b16
            state->sp = (opcode[1] << 8) | opcode[2];
            state->currentb += 2;
            break;
        
        // back to 8 bit loads :( :P
        case 0x41: // LD B,C
            state->b = state->c;
            state->currentb++;
            break;
    }
    
    state->pc++;
    
    combineRegs(state);
    setFlagsInF(state);
}