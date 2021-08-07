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
    firstScan->lineCounter = 1;

    return firstScan;
}



int checkEmpty(char * line)
{
    int i = 0, counter = 0;
    for (i = 0; i < strlen(line); i++)
    {
        if(line[i] == ' ' || line[i] == '\t' || line[i] == '\0')
        {
            counter ++;
        }
    }

    if(counter == i)
    {
        return true;
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
    int symbolFlag = 0;
    int ** doublePointer;
    int instructionFlag = 0;
    int z = 0, i = 0, y = 0;
    TextNode * firstNode;
    TextNode * curNode;
    TextNode * curWord;
    TextNode * tempNode;
    Action * tempAction;
    int intTemp[MAX_LABEL_LEN];

    SymbolNode * lastSymbol = NULL;
    SymbolNode * firstSymbol = NULL;
    SymbolNode * curSymbol = NULL;
    char ** doubleCharP;
    int ** tempInt;
    FirstScan * firstScan;


    firstScan = initScan();
    firstNode = createNode(MAX_LABEL_LEN);
    firstNode = lineParser(asFile, strLen);
    curNode = firstNode;
    curWord = createNode(MAX_LABEL_LEN);
    tempNode = createNode(MAX_LABEL_LEN);
    tempAction = (Action*)malloc(sizeof(Action));

    while(curNode->val != NULL)
    {
       
        while(checkEmpty(curNode->val) == 1)
        {
            if(curNode->nextNode->val != NULL)
            {
                curNode = curNode->nextNode;
            }

            else
            {
                break;
            }
        }
        temp = (char*)malloc(sizeof(MAX_LABEL_LEN));
        strcpy(temp, curNode->val);
        curWord = wordParser(temp);

        if(isLabel(curNode->val))
        {
            symbolFlag = 1;
        }


        
        
        
        if(strchr(temp,'.') != NULL)
        {
            
            temp = strchr(curNode->val,'.');
            //add syntax check********************
        
            if(temp[2] == 'b')
            {         
                tempNode = wordParser(temp);
                tempNode = tempNode->nextNode;
                while(tempNode->val != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                firstScan->DC = firstScan->DC + (z);

                doublePointer = malloc(z + 1 * sizeof(int*));
                
                doublePointer = freeDInstructions('b', intTemp, z);


                for (i = 0; i < z ; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine->nextNode = createIntNode();
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                    
                free(doublePointer);
                free(tempNode);
                instructionFlag ++;

            }

            if(temp[2] == 'w')
            {
                
                
                tempNode = wordParser(temp);
                tempNode = tempNode->nextNode;
                while(tempNode->val != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                firstScan->DC = firstScan->DC + (4 * (z));

                doublePointer = malloc(z + 1 * sizeof(int*));
                
                doublePointer = freeDInstructions('w', intTemp, z);


                for (i = 0; i < z ; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine->nextNode = createIntNode();
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                    
                free(doublePointer);
                free(tempNode);
                instructionFlag ++;

            }

            if(temp[2] == 'h')
            {
                
                
                tempNode = wordParser(temp);

                tempNode = tempNode->nextNode;
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;

                    z++;
                }

                firstScan->DC = firstScan->DC + (2 * (z));

                doublePointer = malloc(z + 1 * sizeof(int*));
                
                doublePointer = freeDInstructions('h', intTemp, z);


                for (i = 1; i < z ; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine->nextNode = createIntNode();
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->IC++;
                }
                    
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
        }

        else
        {
            if(isLabel(curNode->val))
            {
                symbolFlag = 1;
            }

            strcpy(temp, curNode->val);
        
            tempNode = wordParser(temp);

            if(symbolFlag == 1)
            {
                strcpy(temp, tempNode->nextNode->val);
                tempAction = getAction(temp);
            }

            else
            {
                strcpy(temp, tempNode->val);
                tempAction = getAction(temp);
            }

            
            if(tempAction == NULL)
            {
                printf("There is no %s action, in row %d\n", tempNode->val, firstScan->lineCounter); // checks action validity 
                firstScan->currentLine = createIntNode();
                firstScan->currentLine = firstScan->currentLine->nextNode;
                firstScan->lineCounter++;
                firstScan->IC += 4;
            }

            else if(tempNode != NULL)
            {
                if(symbolFlag == 1)
                {
                    if(firstSymbol == NULL)
                    {
                        firstSymbol = createSymbol();
                        addSymbole(tempNode->val, firstScan->IC, "data", firstSymbol);
                        lastSymbol = firstSymbol;
                        curSymbol = lastSymbol;
                    }
                        
                    else
                    {
                        curSymbol = createSymbol();
                        addSymbole(tempNode->val, firstScan->IC, "data", curSymbol);
                        lastSymbol->nextNode = curSymbol;
                        lastSymbol = curSymbol;
                        firstScan->DC = firstScan->DC + (curNode->nodeSize - 2);
                    }   

                }
                doubleCharP = malloc(sizeof(char*)  * curNode->nodeSize);

                if(doubleCharP == NULL)
                {
                    printf("Memory problem in line %d", firstScan->lineCounter);
                }


                i = 0;
                while (tempNode->val != NULL)
                {
                    doubleCharP[i] = (char*)malloc(sizeof(char) * MAX_INT);
                    doubleCharP[i] = tempNode->val;
                    tempNode = tempNode->nextNode;
                    i++;
                }
                                
                if(tempAction->actionType == 'R')
                {
                    // verify all are names of rgs ***********************
                    if(tempAction->numOfop == 3)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 2]), atoi(doubleCharP[symbolFlag + 3]), 0, 0 , 0);
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }



                    if(tempAction->numOfop == 2)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), 0, atoi(doubleCharP[symbolFlag + 2]), 0, 0 , 0);
                        firstScan->currentLine->nextNode = createIntNode();
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
                        firstScan->currentLine->nextNode = createIntNode();
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
                        firstScan->currentLine->nextNode = createIntNode();
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
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                    }

                    else
                    {
                        if(tempAction->opcode == 30) // jmp
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0, 0, atoi(doubleCharP[symbolFlag + 1]));
                            firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->IC += 4;
                        }

                        else if(tempAction->opcode == 63)
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0, 0, 0);
                            firstScan->currentLine->nextNode = createIntNode();
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->IC += 4;
                        }
                    }  
                }
            }

            else
            {
                printf("unexcpected error\n");
                exit(1);
            }
        }

        curNode = curNode->nextNode;
        symbolFlag = 0;

    }
    
    return firstScan;
}

