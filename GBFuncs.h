#ifndef GBFUNCS_H
#define GBFUNCS_H

#include "GBBase.h"
#include <stdio.h>
#include <fstream>
#include <string>
using namespace std;

void setColorCompatible(GBState*);
void combineRegs(GBState*);
void setFlagsInF(GBState*);

void EmulateInstruct(GBState*);
void initMemory(GBState*, char*);

#endif

