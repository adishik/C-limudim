#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __ACTION_TABLE__
#define __ACTION_TABLE__

struct _Action
{
    char * actionName;
    char actionType;
    int funct;
    int opcode;
    int numOfop;
};
typedef struct _Action Action;

int * convDectoBin(int decimalNumber, int  * binaryNumber); 
Action  * getAction(char * actionName); 

int * codeAction(Action  * action, int rs, int rt, int rd, int imme, int reg, int add ); 

#endif

