#include "instructions.h"
#define byte 1


int  * freeInstructions(char instructionType,int * intstructionParms, int parmsSize)
{
    if(instructionType == 'b')
    {
        int * instructionpPointer = (int*)malloc(parmsSize * byte);
    }

    if(instructionType == 'w')
    {
        int * instructionpPointer = (int*)malloc(parmsSize * (4 * byte));
    }

    if(instructionType == 'h')
    {
        int * instructionpPointer = (int*)malloc(parmsSize * (2 * byte));
    }

    for(i = 0; i < parmsSize; i++)
        {
            instructionpPointer[i] = intstructionParms;
        }


    return instructionpPointer;
}
