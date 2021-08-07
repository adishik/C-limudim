#include "instructions.h"

#define byte 1
#define true 1
#define false 0


int  ** freeDInstructions(char instructionType,int * intstructionParms, int parmsSize)
{
    int ** instructionpPointer;
    int * tempBin;
    int i = 0, k = 0, w = 0;
    instructionpPointer = malloc(sizeof(int *) * parmsSize);

    for(k = 0; k < parmsSize ; k++)
        {
            instructionpPointer[k] = (int*)malloc(32 * sizeof(int));
            tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);

            w = 31;
            for (i = 0; i < 32; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
                w--;
            }
            free(tempBin);
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

