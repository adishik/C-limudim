#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __ACTION_TABLE__
#define __ACTION_TABLE__
/* this moudle is for hanlding actions, I used an array of structers in order to keep all of the action attribuites*/

struct _Action
{
    char * actionName;
    char actionType;
    int funct;
    int opcode;
    int numOfop;
};
typedef struct _Action Action;

int * convDectoBin(int decimalNumber, int  * binaryNumber, int); /*convert Decimal number to binary*/
Action  * getAction(char * actionName); /* Return action pointer according ot the action name*/

int * codeAction(Action  * action, int rs, int rt, int rd, int imme, int reg, int add ); /*coding the action according tot he specification*/
int checkActionSyntax(Action * tempAction, char * line, int strLine); /*checks action validity*/
#endif

