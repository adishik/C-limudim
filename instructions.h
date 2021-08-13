#include "actionTable.h"
#include "parser.h"

#define byte 1

#ifndef __INSTRUCTION_TABLE__
#define __INSTRUCTION_TABLE__

/* this modoule will be used for instructions coding*/

int ** freeDInstructions(char instructionType, int * intstructionParms, int parmsSize); /* clear spce for .d instructions*/
int ** freeAsInstruction(char * parm); /* clear spce for .asciz instructions*/
int checkInstructionSyntax(char * node, int strLen);

#endif
