#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __ACTION_TABLE__
#define __ACTION_TABLE__

struct _Action // define action in Assembly 
{
    char * actionName;
    char actionType;
    int funct;
    int opcode;
    int numOfop;
};
typedef struct _Action Action;

int * convDectoBin(int decimalNumber, int  * binaryNumber); // converts a Decimal number to binary
Action  * getAction(char * actionName); // get string and return Avrion object

int * codeAction(Action  * action, int rs, int rt, int rd ); // truining action into binary

#endif

