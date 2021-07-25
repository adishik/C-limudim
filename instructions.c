#include "instructions.h"
#define byte 1

int * convDectoBin(int decimalNumber, int  * binaryNumber) 
{
    long int quotient;
    int i = 0, j;

    quotient = decimalNumber;
    bool isNegative = false;
    if(decimalNumber < 0)
    {
        isNegative = true;
        decimalNumber =  abs(decimalNumber);
    }
    while(quotient!=0){

        binaryNumber[i++]= quotient % 2;

        quotient = quotient / 2;

    }


    if(isNegative)
    {
        for (int  i = 0; i < 31; i++)
        {
            if(binaryNumber[i] == 0)
            {
                binaryNumber[i] = 1;
            }  

            else
            {
                binaryNumber[i] = 0;
            }
        }

        for (int j = 0; j < 31; j++)
        {
            if(binaryNumber[j] == 0)
            {
                binaryNumber[j]++;
                return binaryNumber;
            }

            else
            {
                binaryNumber[j]--;
            }
        }
    }

    return binaryNumber;
}


int  ** freeDInstructions(char instructionType,int * intstructionParms, int parmsSize)
{
    int ** instructionpPointer = malloc(sizeof(int *) * parmsSize);

    if(instructionType == 'b')
    {
        for(int k = 0; k < parmsSize; k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(byte));
            int * tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);
            for (int i = 0; i < 32; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }

            free(tempBin);
        }
    }

    if(instructionType == 'w')
    {
        for(int k = 0; k < parmsSize; k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(4 * byte));
            int * tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);
            for (int i = 0; i < 32; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }

            free(tempBin);
        }
        
    }

    if(instructionType == 'h')
    {
        for(int k = 0; k < parmsSize; k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(2 * byte));
            int * tempBin = (int*)malloc(32 * sizeof(int));
            tempBin = convDectoBin(intstructionParms[k],tempBin);
            for (int i = 0; i < 32; i++)
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
    
    int ** instructionpPointer = malloc(sizeof(int *) * (int)strlen(parm));
    int i = 0, k = 0;
    for(int k = 0; k < strlen(parm); k++)
        {
            instructionpPointer[k] = (int*)malloc(sizeof(byte));
            int * tempBin = (int*)malloc(sizeof(byte));
            tempBin = convDectoBin((int)parm[k],tempBin);
            for (int i = 0; i < 8; i++)
            {
                instructionpPointer[k][i] = tempBin[i];
            }
            free(tempBin);
        }

    instructionpPointer[strlen(parm)] = 0;  

    return instructionpPointer;

}

