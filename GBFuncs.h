#ifndef GBFUNCS_H
#define GBFUNCS_H

#include "GBBase.h"
#include <stdio.h>

void setColorCompatible(GBState*);
void combineRegs(GBState*);
void setFlagsInF(GBState*);

void EmulateInstruct(GBState*);

#endif

