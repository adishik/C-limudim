#include "actionTable.h"
#define byte 1

#ifndef __INSTRUCTION_TABLE__
#define __INSTRUCTION_TABLE__

int ** freeDInstructions(char instructionType, int * intstructionParms, int parmsSize);
int ** freeAsInstruction(char * parm);

#endif
