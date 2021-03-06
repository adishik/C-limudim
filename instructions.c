#include "instructions.h"
#include "parser.h"

#define byte 1
#define true 1
#define false 0
#define MAX_LABLE_LEN 80


int  ** freeDInstructions(char instructionType,int * intstructionParms, int parmsSize) /* clear spce for .d instructions*/
{
    int ** instructionpPointer;
    int * tempBin;
    int i = 0, k = 0, w = 0;
    instructionpPointer = malloc(sizeof(int *) * parmsSize);

    for(k = 0; k < parmsSize ; k++)
        {
            instructionpPointer[k] = (int*)malloc(32 * sizeof(int));
            tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin, 32);

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

int ** freeAsInstruction(char * parm) /* clear spce for .asciz instructions*/
{
    int * tempBin;
    int ** instructionpPointer = malloc(sizeof(int *) * (int)strlen(parm));
    int i = 0, k = 0;
    for(k = 0; k < strlen(parm); k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(int));
            tempBin = (int*)malloc(8 * sizeof(int));
            tempBin = convDectoBin((int)parm[k],tempBin, 8);
            for (i = 0; i < 8; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }
            free(tempBin);
        }

    instructionpPointer[strlen(parm)] = 0;  

    return instructionpPointer;

}

int checkInstructionSyntax(char * node, int strLen) /* checks fo syntax errors */
{
    char  * temp;
    int i = 0, z = 0;


    temp = (char*)malloc(strLen * sizeof(char));        
    for (i = 0; i < strLen ; i++)
    {
        if(node[i] != ' ') /* Clear Spaces */
        {
            temp[i] = node[i];
        }
    }

    z = i;

    for (i = 0; i < z ; i++)
    {
        if(temp[i] == temp[i + 1] && (temp[i] == ',')) /* Checking if thee is ,, on the line */
        {
            return 1;
        }
    }

    if(strLen > 80) /* check if the line's length is valid */
    {
        return 2;
    }

    return 0;
  
    
}

