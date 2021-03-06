#include "actionTable.h"
#include "parser.h"

#define true 1
#define false 0
#define MAX_LABEL_LEN 60

int * convDectoBin(int decimalNumber, int  * binaryNumber, int size) /*Convert decimal number to Binary*/
{
    long int quotient;
    int i = 0,j = 0;
    int isNegative = false;

    quotient = decimalNumber;
    
    if(decimalNumber < 0)
    {
        isNegative = true;
        decimalNumber =  abs(decimalNumber);
    }

    while(quotient!=0 && i < size){
        binaryNumber[i++]= quotient % 2;

        quotient = quotient / 2;

    }

    if(isNegative == true) /* this will turn the number in to משלים ל2*/
    {
        for (i = 0; i < size; i++)
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

        for (j = 0; j < size; j++)
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

/*this is the action table*/

static struct _Action actionTable[27] = 
                                {
                                    {"add", 'R', 1, 0, 3},
                                    {"sub", 'R', 2, 0, 3},
                                    {"and", 'R', 3, 0, 3},
                                    {"or", 'R', 4, 0, 3},
                                    {"nor", 'R', 5, 0, 3},
                                    {"move", 'R', 1, 1, 2},
                                    {"mvhi", 'R', 2, 1, 2},
                                    {"mvlo", 'R', 3, 1, 2},
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
                                    {"jmp", 'J', 0, 30, 1},
                                    {"la", 'J', 0, 31, 1},
                                    {"call", 'J', 0, 32, 1},
                                    {"stop", 'J', 0, 63, 0}
                                };                          


Action  * getAction(char * actionName)/* Gets the name of an action and return it's attribiutes*/
{
    int k;
    for(k = 0; k < 27; k++)
    {
        if(strcmp(actionName, actionTable[k].actionName) == 0)
        {
            
            
            Action  * returnAdrees = (Action*)malloc(sizeof(Action));
            returnAdrees->actionName = actionTable[k].actionName;
            returnAdrees->actionType = actionTable[k].actionType;
            returnAdrees->funct = actionTable[k].funct;
            returnAdrees->numOfop= actionTable[k].numOfop;
            returnAdrees->opcode = actionTable[k].opcode;


            return returnAdrees;
        }
    }

    return NULL;

}
int * codeAction(Action * action, int rs, int rt, int rd, int imme, int reg, int add)
{
    int  * binLine = (int*)malloc(32 * sizeof(int));
    int * tempOP;
    int * tempRS;
    int * tempRD;
    int * tempFunct;
    int * tempRT;
    int * tempAdd;
    int * tempImme;
    int y = 0;
    if(binLine == NULL)
    {
        printf("out of memory!");
        return 0;
    }

    else
    {
        if(action->actionType == 'R')/*Codind according to R type*/
        {
            
            tempOP = (int*)malloc(6 * sizeof(int)); /* OP */
            tempOP = convDectoBin(action->opcode, tempOP, 6);
            binLine[31] = tempOP[5];
            binLine[30] = tempOP[4];
            binLine[29] = tempOP[3];
            binLine[28] = tempOP[2];
            binLine[27] = tempOP[1];
            binLine[26] = tempOP[0];
            free(tempOP);

            
            tempRS = (int*)malloc(5 * sizeof(int));/* RS */
            tempRS = convDectoBin(rs,tempRS, 5);
            binLine[25] = tempRS[4];
            binLine[24] = tempRS[3];
            binLine[23] = tempRS[2];
            binLine[22] = tempRS[1];
            binLine[21] = tempRS[0];
            free(tempRS);

            
            tempRD = (int*)malloc(5 * sizeof(int));/* RD */
            tempRD = convDectoBin(rt, tempRD, 5);
            binLine[15] = tempRS[4];
            binLine[14] = tempRS[3];
            binLine[13] = tempRS[2];
            binLine[12] = tempRS[1];
            binLine[11] = tempRS[0];
            free(tempRD);

            
            tempFunct = (int*)malloc(5 * sizeof(int));/* FuncT */
            tempFunct = convDectoBin(action->funct, tempFunct, 5);
            binLine[10] = tempFunct[4];
            binLine[9] = tempFunct[3];
            binLine[8] = tempFunct[2];
            binLine[7] = tempFunct[1];
            binLine[6] = tempFunct[0];
            free(tempFunct);

            if(action->numOfop == 3)/* If needed we will code RT, altought some of the actions doesn't really need it no we will keep it 0 */
            {
                
                tempRT = (int*)malloc(5 * sizeof(int));
                tempRT = convDectoBin(rt,tempRT, 5);
                binLine[20] = tempRT[4];
                binLine[19] = tempRT[3];
                binLine[18] = tempRT[2];
                binLine[17] = tempRT[1];
                binLine[16] = tempRT[0];
                free(tempRT);
            }
        }

        if(action->actionType == 'I') /*Codind according to I type*/
        {
            tempOP = (int*)malloc(6 * sizeof(int));
            tempOP = convDectoBin(action->opcode, tempOP, 6);/* OP */
            binLine[31] = tempOP[5];
            binLine[30] = tempOP[4];
            binLine[29] = tempOP[3];
            binLine[28] = tempOP[2];
            binLine[27] = tempOP[1];
            binLine[26] = tempOP[0];
            free(tempOP);

            tempRS = (int*)malloc(5 * sizeof(int)); /* RS */
            tempRS = convDectoBin(rs,tempRS, 5);
            binLine[25] = tempRS[4];
            binLine[24] = tempRS[3];
            binLine[23] = tempRS[2];
            binLine[22] = tempRS[1];
            binLine[21] = tempRS[0];
            free(tempRS);

            tempRT = (int*)malloc(5 * sizeof(int)); /* RT */
            tempRT = convDectoBin(rt,tempRT, 5);
            binLine[20] = tempRT[4];
            binLine[19] = tempRT[3];
            binLine[18] = tempRT[2];
            binLine[17] = tempRT[1];
            binLine[16] = tempRT[0];
            free(tempRT);

            tempImme = (int*)malloc(16 * sizeof(int)); /* Immedtiet */
            tempImme = convDectoBin(imme, tempImme, 16);
            binLine[15] = tempImme[15];
            binLine[14] = tempImme[14];
            binLine[13] = tempImme[13];
            binLine[12] = tempImme[12];
            binLine[11] = tempImme[11];
            binLine[10] = tempImme[10];
            binLine[9] = tempImme[9];
            binLine[8] = tempImme[8];
            binLine[7] = tempImme[7];
            binLine[6] = tempImme[6];
            binLine[5] = tempImme[5];
            binLine[4] = tempImme[4];
            binLine[3] = tempImme[3];
            binLine[2] = tempImme[2];
            binLine[1] = tempImme[1];
            binLine[0] = tempImme[0];
            free(tempImme);
        }


        if(action->actionType == 'J') /*Codind according to J type*/
        {

            tempOP = (int*)malloc(6 * sizeof(int));
            tempOP = convDectoBin(action->opcode, tempOP, 6); /* OP */
            binLine[31] = tempOP[5];
            binLine[30] = tempOP[4];
            binLine[29] = tempOP[3];
            binLine[28] = tempOP[2];
            binLine[27] = tempOP[1];
            binLine[26] = tempOP[0];
            free(tempOP);


            binLine[25] = reg;



            tempAdd = (int*)malloc(24 * sizeof(int));
            tempAdd = convDectoBin(add, tempAdd, 24);
            for(y = 24; y >= 0; y--)
            {
                binLine[y] = tempAdd[y];
            }
        }
        
        return binLine;
    }


}

int checkActionSyntax(Action * tempAction, char * line, int strLine) /* Checking for syntax errors */
{
    char  * temp;
    char  * temp2;
    char ** doubleCharP;
    int i = 0, z = 0;


    TextNode  * nextNode;
    TextNode * par;
    TextNode * firstNode;
    firstNode = (TextNode*)malloc(sizeof(TextNode));
    par = firstNode;

    temp = (char*)malloc(strLine);
    temp2 = (char*)malloc(strLine);

    
    for (i = 0; i < strLine - 1 ; i++) /* removing spaces */
    {
        if(line[i] != ' ')
        {
            temp[i] = line[i];
        }
    }

    z = i;

    for (i = 0; i < z ; i++)
    {
        if(temp[i] == temp[i + 1] && (temp[i] == ',')) /* Means there is a comma right after a comma */
        {
            return 1; /* too many commas*/
        }
    }

    if(strLine > 60)
    {
        return 2; /*line was too long*/
    }

    doubleCharP = malloc(strLine * sizeof(char*));

    i = 0;
    par->val = strtok(line, " :,");
    doubleCharP[i] = (char*)malloc(strLine);
    doubleCharP[i] = par->val;
    

    if(par->val == NULL)
    {
        printf("NULL\n");
       

        return 0;
    }


   
    while(par->val != NULL)
    {
        i++;
        nextNode = createNode(MAX_LABEL_LEN);
        par->nodeSize++;
        par->nextNode = nextNode;
        par = par->nextNode;
        par->val = strtok(NULL, " :,");
        doubleCharP[i] = (char*)malloc(strLine);
        doubleCharP[i] = par->val;
        
    }


    
  
    free(tempAction);
    free(temp);
    free(temp2);
    return 0;

}
