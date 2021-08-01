#include "firstScan.h"
#define MAX_LABEL_LEN 60

#define true 1
#define false 0

#define MAX_INT 31


FirstScan * initScan()
{
    FirstScan * firstScan = (FirstScan*)malloc(sizeof(FirstScan));
    firstScan->firstSymbol = createSymbol();
    firstScan->firstLine = createIntNode();
    firstScan->currentLine = firstScan->firstLine;
    firstScan->DC = 0;
    firstScan->IC = 100;
    firstScan->lineCounter = 0;

    return firstScan;
}

int checkEmpty(char * line)
{
    int i = 0;
    for (i = 0; i < strlen(line); i++)
    {
        if(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')
        {
            return true;
        }
    }

    return false;
    
}

int isAlphabet(char firstChar)
{
    if(((int)firstChar <= 90 && (int)firstChar >= 65) || ((int)firstChar <= 122 && (int)firstChar >= 97) )
    {
        return true;
    }

    return false;
}

int isLabel(char * label)
{
    int i = 0;
    for (i = 0; i < strlen(label); i++)
    {
        if(label[i] == ':')
        {
            return true;
        }
    }


    return false;
    
}

FirstScan * doScan(char * asFile, int strLen)
{
    
    char * temp;
    int * intTemp;
    int symbolFlag = 0;
    int ** doublePointer;
    int instructionFlag = 0;
    int z = 0, i = 0;
    TextNode * firstNode;
    TextNode * curNode;
    TextNode * curWord;
    TextNode * tempNode;
    Action * tempAction;

    SymbolNode * lastSymbol = NULL;
    SymbolNode * firstSymbol = NULL;
    SymbolNode * curSymbol = NULL;
    char ** doubleCharP;
    int ** tempInt;
    FirstScan * firstScan;


    firstScan = initScan();
    firstNode = createNode(MAX_LABEL_LEN);
    firstNode = lineParser(asFile, strLen);
    curNode = createNode(MAX_LABEL_LEN);
    curNode = firstNode;
    curWord = createNode(MAX_LABEL_LEN);
    tempNode = createNode(MAX_LABEL_LEN);
    tempAction = (Action*)malloc(sizeof(Action));

    while(curNode != NULL)
    {
        printf("this is already a problem line 107\n");
        printf("the size of val is %d\n", curNode->nodeSize);
        while(checkEmpty(curNode->val))
        {
            if(curNode->nextNode != NULL)
            {
                curNode = curNode->nextNode;
            }

            else
            {
                break;
            }
        }


        curWord = wordParser(curNode->val);
        printf("this is already a problem line 123\n");
        if(isLabel(curNode->val))
        {
            symbolFlag = 1;
        }
        
        printf("this is already a problem line 115\n");
        printf("%p\n", (void *)curNode->val);
        printf("%s\n", curNode->val);
        temp = strchr(curNode->val,'.');

        if(temp != NULL)
        {
            printf("Sucess creating temp with lenght %lu\n", strlen(temp));
            //add syntax check********************
        
            if(temp[2] == 'b')
            {
                firstScan->DC = firstScan->DC + (curNode->nodeSize - 2);
                tempNode = wordParser(temp);
                tempNode = tempNode->nextNode;
                intTemp = (int*)malloc((tempNode->nodeSize - 1) * sizeof(int));
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                doublePointer = freeDInstructions('b', intTemp, tempNode->nodeSize - 1);

                for (i = 0; i < tempNode->nodeSize - 1; i++)
                {
                    printf("problem is here at line 138 becaseu i is : %d\n", i);
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                    
                free(intTemp);
                free(doublePointer);
                free(tempNode);
                instructionFlag ++;

            }

            if(temp[2] == 'w')
            {

                firstScan->DC = firstScan->DC + (4 * (curNode->nodeSize - 2));
                tempNode = wordParser(temp);
                tempNode = tempNode->nextNode;
                intTemp = (int*)malloc((tempNode->nodeSize - 1) * sizeof(int));
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                doublePointer = freeDInstructions('w', intTemp, tempNode->nodeSize - 1);

                for (i = 0; i < tempNode->nodeSize - 1; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                    
                free(intTemp);
                free(doublePointer);
                free(tempNode);
                instructionFlag ++;
            }

            if(temp[2] == 'h')
            {
                firstScan->DC = firstScan->DC + (2 * (curNode->nodeSize - 2));
                tempNode = wordParser(temp);
                tempNode = tempNode->nextNode;
                intTemp = (int*)malloc((tempNode->nodeSize - 1) * sizeof(int));
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                doublePointer = freeDInstructions('h', intTemp, tempNode->nodeSize - 1);

                for (i = 0; i < tempNode->nodeSize - 1; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                    
                free(intTemp);
                free(doublePointer);
                free(tempNode);
                instructionFlag ++;
            }

            if(temp[2] == 's')
            {
                tempNode = wordParser(temp);
                firstScan->DC = firstScan->DC + (strlen(tempNode->val) + 1);
                tempInt = malloc(tempNode->nodeSize *  sizeof(int*));
                tempInt = freeAsInstruction(temp);
                for (i = 0; i < tempNode->nodeSize; i++)
                {
                    firstScan->currentLine->val = tempInt[i];
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                instructionFlag++;
            }

            if(symbolFlag == 1)
            {
                // verify symbol doesn't exsists *******************************************
                if(instructionFlag == 1)
                {
                    if(firstSymbol == NULL)
                    {
                        firstSymbol = createSymbol();
                        addSymbole(curWord->val, firstScan->IC, "data", firstSymbol);
                        lastSymbol = firstSymbol;
                        curSymbol = lastSymbol;
                    }
                        
                    else
                    {
                        curSymbol = createSymbol();
                        addSymbole(curWord->val, firstScan->IC, "data", curSymbol);
                        lastSymbol->nextNode = curSymbol;
                        lastSymbol = curSymbol;
                        firstScan->DC = firstScan->DC + (curNode->nodeSize - 2);
                    }
                }

                else
                {
                    if(firstSymbol == NULL)
                    {
                        firstSymbol = createSymbol();
                        addSymbole(curWord->val, 0, "external", firstSymbol);
                        lastSymbol = firstSymbol;
                        curSymbol = lastSymbol;
                    }
                        
                    else
                    {
                        curSymbol = createSymbol();
                        addSymbole(curWord->val, 0, "external", curSymbol);
                        lastSymbol->nextNode = curSymbol;
                        lastSymbol = curSymbol;
                        firstScan->DC = firstScan->DC + (curNode->nodeSize - 2);
                    }
                }
            }
            free(temp);
        }

        else
        {
            if(isLabel(curNode->val))
            {
                symbolFlag = 1;
            }
        
            tempNode = wordParser(curNode->val);
            tempAction = getAction(tempNode->val);
            if(temp == 0)
            {
                printf("There is no %s action, in row %d", tempNode->val, firstScan->lineCounter);// checks action validity 
                firstScan->currentLine = firstScan->currentLine->nextNode;
                firstScan->lineCounter++;
                firstScan->IC += 4;

            }

            else
            {
                if(symbolFlag == 1)
                {
                    if(firstSymbol == NULL)
                    {
                        firstSymbol = createSymbol();
                        addSymbole(curWord->val, firstScan->IC, "data", firstSymbol);
                        lastSymbol = firstSymbol;
                        curSymbol = lastSymbol;
                    }
                        
                    else
                    {
                        curSymbol = createSymbol();
                        addSymbole(curWord->val, firstScan->IC, "data", curSymbol);
                        lastSymbol->nextNode = curSymbol;
                        lastSymbol = curSymbol;
                        firstScan->DC = firstScan->DC + (curNode->nodeSize - 2);
                    }       
                }

                doubleCharP = malloc(sizeof(char*)  * curNode->nodeSize);
                for (i = 0; i < tempNode->nodeSize; i++)
                {
                    printf("this is the problem, line 316 because i: %d\n", i);
                    doubleCharP[i] = (char*)malloc(sizeof(char) * MAX_INT);
                    doubleCharP[i] = tempNode->val;
                    tempNode = tempNode->nextNode;
                }
                
                
                if(tempAction->actionType == 'R')
                {
                    // verify all are names of rgs ***********************
                    if(tempAction->numOfop == 3)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 2]), atoi(doubleCharP[symbolFlag + 3]), 0, 0 , 0);
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }

                    if(tempAction->numOfop == 2)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), 0, atoi(doubleCharP[symbolFlag + 2]), 0, 0 , 0);
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }
                }

                if(tempAction->actionType == 'I')
                {
                    if(tempAction->opcode < 15 && tempAction->opcode > 9)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 3]), 0,atoi(doubleCharP[symbolFlag + 2]), 0, 0);
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }

                    if(tempAction->opcode < 19 && tempAction->opcode > 14)
                    {
                        if(isAlphabet(doubleCharP[symbolFlag + 3][0]) == 1)
                        {
                            firstScan->currentLine->labelIsOp = true;
                        }
                    }

                    else
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 3]), 0,atoi(doubleCharP[symbolFlag + 2]), 0, 0);
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }
                }

                else
                {
                    if(isAlphabet(doubleCharP[symbolFlag + 1][0]) == 1)
                    {
                        firstScan->currentLine->labelIsOp = true;
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }

                    else
                    {
                        //int * codeAction(Action * action, int rs, int rt, int rd, int imme, int reg, int add)
                        if(tempAction->opcode == 30) // jmp
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0, 0, atoi(doubleCharP[symbolFlag + 1]));
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->IC += 4;
                        }

                        else if(tempAction->opcode == 63)
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0, 0, 0);
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->IC += 4;
                        }
                    }  
                }
            }
        }
    }

    return firstScan;
}

