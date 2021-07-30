#include "firstScan.h"

FirstScan * initScan()
{
    FirstScan * firstScan = (FirstScan*)malloc(sizeof(FirstScan));
    firstScan->firstSymbol = createSymbol();
    firstScan->firstLine = createIntNode();
    firstScan->currentLine = firstScan->firstLine;
    firstScan->DC = 0;
    firstScan->IC 100;
    firstScan->lineCounter = 0;
}

bool checkEmpty(char * line)
{
    int k = 0;
    for (int i = 0; i < strlen(line); i++)
    {
        if(line[i] == ' ' || line[i] == '\t' || line[i] == NULL)
        {
            return true;
        }
    }

    return false;
    
}

bool isAlphabet(char firstChar)
{
    if(((int)firstChar <= 90 && (int)firstChar >= 65) || ((int)firstChar <= 122 && (int)firstChar >= 97) )
    {
        return true;
    }

    return false;
}

bool isLabel(char * label)
{
    for (int i = 0; i < strlen(lable); i++)
    {
        if(label[i] == ':')
        {
            return true;
        }
    }

    else
    {
        return false;
    }
    
}

FirstScan * doScan(char * asFile)
{
    FirstScan * firstScan = initScan();
    TextNode * firsNode = createNode();
    firsNode = lineParser(asFile);
    TextNode * curNode = createNode();
    curNode = firstNode;
    TextNode * curWord = createNode()
    int symbolFlag = 0;
    SymbolNode * lastSymbol = NULL;
    SymbolNode * firstSymbol = NULL;
    SymbolNode * curSymbol = NULL;
    char * temp;
    int * intTemp;
    TextNode * tempNode = createNode();
    int ** doublePointer;
    int instructionFlag = 0;
    Action * tempAction = (Action*)malloc(sizeof(Action));
    while(curNode != NULL)
    {
        while(checkEmpty(curNode))
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


        curWord = wordParser(curNode);

        if(isLabel(curNode->val))
        {
            symbolFlag = 1;
        }

        
    
        temp = strchr(curNode->val,'.');
        if(temp[0] = '.'); // meanig it's an instruction
        {
            //add syntax check********************
        
            if(temp[2] == 'b')
            {
                firstScan->DC = firstScan->DC + (curNode->nodeSize - 2);
                tempNode = wordParser(temp);
                intTemp = (int*)malloc((tempNode->nodeSize - 1) * sizeof(int))
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val[0]);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                doublePointer = freeDInstructions('b', intTemp, tempNode->nodeSize - 1);

                for (int i = 0; i < tempNode->nodeSize - 1; i++)
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

            if(temp[2] == 'w')
            {

                firstScan->DC = firstScan->DC + (4 * (curNode->nodeSize - 2));
                tempNode = wordParser(temp);
                intTemp = (int*)malloc((tempNode->nodeSize - 1) * sizeof(int))
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val[0]);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                doublePointer = freeDInstructions('w', intTemp, tempNode->nodeSize - 1);

                for (int i = 0; i < tempNode->nodeSize - 1; i++)
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
                intTemp = (int*)malloc((tempNode->nodeSize - 1) * sizeof(int))
                while(tempNode->nextNode != NULL)
                {
                    intTemp[z] = atoi(tempNode->val[0]);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                doublePointer = freeDInstructions('h', intTemp, tempNode->nodeSize - 1);

                for (int i = 0; i < tempNode->nodeSize - 1; i++)
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
                temp = wordParser(temp);
                firstScan->DC = firstScan->DC + (strlen(temp[1] + 1));
                int ** tempInt = malloc(temp->nodeSize *  sizeof(int*));
                tempInt = freeAsInstruction(temp);
                for (int i = 0; i < temp->nodeSize; i++)
                {
                    firstScan->currentLine->val =  tempInt[i];
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
            free(temp);
        }
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
            printf("There is no %s action, in row %d", tempNode->val, FirstScan->lineCounter);

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
            //int * codeAction(Action * action, int rs, int rt, int rd, int imme, int reg, int add)
            if(tempAction->actionType == 'R')
            {
                if(tempAction->numOfop == 3)
                {
                    FirstScan->currentLine->val = codeAction(tempAction,tempNode->val[symbolFlag + 1], tempNode->val[symbolFlag + 2], tempNode->val[symbolFlag + 3], 0, 0 , 0);
                    FirstScan->currentLine = FirstScan->currentLine->nextNode;
                    FirstScan->lineCounter++;
                    FirstScan->IC += 4;
                }

                if(tempAction->numOfop == 2)
                {
                    FirstScan->currentLine->val = codeAction(tempAction,tempNode->val[symbolFlag + 1], 0, tempNode->val[symbolFlag + 2], 0, 0 , 0);
                    FirstScan->currentLine = FirstScan->currentLine->nextNode;
                    FirstScan->lineCounter++;
                    FirstScan->IC += 4;
                }
            }

        }
    
    

    }

    
    }
}
