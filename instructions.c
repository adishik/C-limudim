#include "instructions.h"

#define byte 1
#define true 1
#define false 0


int  ** freeDInstructions(char instructionType,int * intstructionParms, int parmsSize)
{
    int ** instructionpPointer;
    int * tempBin;
    int i = 0, k = 0;
    instructionpPointer = malloc(sizeof(int *) * parmsSize);

    if(instructionType == 'b')
    {
        int k = 0, i = 0;
        for(k = 0; k < parmsSize; k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(byte));
            tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);
            for (i = 0; i < 32; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }

            free(tempBin);
        }
    }

    if(instructionType == 'w')
    {
        for(k = 0; k < parmsSize; k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(4 * byte));
            tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);
            for (i = 0; i < 32; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }

            free(tempBin);
        }
        
    }

    if(instructionType == 'h')
    {
        for(k = 0; k < parmsSize; k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(2 * byte));
            tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);
            for (i = 0; i < 32; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }

            free(tempBin);
        }
        
    }

    return instructionpPointer;
}

int ** freeAsInstruction(char * parm)
{
    int * tempBin;
    int ** instructionpPointer = malloc(sizeof(int *) * (int)strlen(parm));
    int i = 0, k = 0;
    for(k = 0; k < strlen(parm); k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(byte));
            tempBin = (int*)malloc(sizeof(byte));
            tempBin = convDectoBin((int)parm[k],tempBin);
            for (i = 0; i < 8; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }
            free(tempBin);
        }

    instructionpPointer[strlen(parm)] = 0;  

    return instructionpPointer;

}

