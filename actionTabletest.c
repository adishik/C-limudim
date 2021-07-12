#include "actionTable.h"

struct _Action // define action in Assembly 
{
    char * actionName;
    char actionType;
    int funct;
    int opcode;
    int numOfop;
};

int * convDectoBin(int decimalNumber) 
{
    long int quotient;

    int binaryNumber[5],i = 0, j;

    quotient = decimalNumber;


    while(quotient!=0){

        binaryNumber[i++]= quotient % 2;

        quotient = quotient / 2;

    }

    return binaryNumber;
}

static struct _Action actionTable[27] = 
                                {
                                    {"add", 'R', 1, 0, 3},
                                    {"sub", 'R', 2, 0, 3},
                                    {"and", 'R', 3, 0, 3},
                                    {"or", 'R', 4, 0, 3},
                                    {"nor", 'R', 5, 0, 3},
                                    {"move", 'R', 1, 1, 2},
                                    {"mvhi", 'R', 2, 1, 2},
                                    {"mvlw", 'R', 3, 1, 2},
                                    {"addi", 'I', 0, 10, 3},
                                    {"subi", 'I', 0, 11, 3},
                                    {"andi", 'I', 0, 12, 3},
                                    {"ori", 'I', 0, 13, 3},
                                    {"nori", 'I', 0, 14, 3},
                                    {"bne", 'I', 0, 15, 3},
                                    {"beq", 'I', 0, 16, 3},
                                    {"blt", 'I', 0, 17, 3},
                                    {"bgt", 'I', 0, 18, 3},
                                    {"lb", 'I', 0, 19, 3},
                                    {"sb", 'I', 0, 20, 3},
                                    {"lw", 'I', 0, 21, 3},
                                    {"sw", 'I', 0, 22, 3},
                                    {"lh", 'I', 0, 23, 3},
                                    {"sh", 'I', 0, 24, 3},
                                    {"jmp", 'J', 0, 30, 3},
                                    {"la", 'J', 0, 31, 3},
                                    {"call", 'J', 0, 32, 3},
                                    {"stop", 'J', 0, 63, 3}
                                };


Action getAction(char * actionName)
{
    for(int i = 0, i < 27, i++)
    {
        if(strcmp(actionName, actionTable[i]) == 0)
        {
            return actionTable[i];
        }
    }

    return 0;
}
int * codeAction(Action action, int rs, int rt, int rd )
{
    int  * binLine = (int*)malloc(sizeof(32 * int));


    if(action.actionType == 'R')
    {
        if(action.numOfop == 3)
        int * tempOP = convDectoBin(action.opcode);
        binLine[31] = tempOP[0];
        binLine[30] = tempOP[1];
        binLine[29] = tempOP[2];
        binLine[28] = tempOP[3];
        binLine[27] = tempOP[4];
        binLine[26] = tempOP[5];


        int * tempRS = convDectoBin(rs);
        binLine[25] = tempRS[0];
        binLine[24] = tempRS[1];
        binLine[23] = tempRS[2];
        binLine[22] = tempRS[3];
        binLine[21] = tempRS[4];

        int * tempRT = convDectoBin(rt);
        binLine[20] = tempRT[0];
        binLine[19] = tempRT[1];
        binLine[18] = tempRT[2];
        binLine[17] = tempRT[3];
        binLine[16] = tempRT[4];

        int * tempRT = convDectoBin(rt);
        binLine[20] = tempRT[0];
        binLine[19] = tempRT[1];
        binLine[18] = tempRT[2];
        binLine[17] = tempRT[3];
        binLine[16] = tempRT[4];

        int * tempRD = convDectoBin(rt);
        binLine[15] = tempRS[0];
        binLine[14] = tempRS[1];
        binLine[13] = tempRS[2];
        binLine[12] = tempRS[3];
        binLine[11] = tempRS[4];

        int * temoFunct = convDectoBin(action.funct);
        binLine[10] = temoFunct[0];
        binLine[9] = temoFunct[1];
        binLine[8] = temoFunct[2];
        binLine[7] = temoFunct[3];
        binLine[6] = temoFunct[4];

    }


}




