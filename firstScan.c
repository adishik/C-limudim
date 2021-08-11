#include "firstScan.h"
#define MAX_LABEL_LEN 60

#define true 1
#define false 0

#define MAX_INT 31


FirstScan * initScan()
{
    FirstScan * firstScan = (FirstScan*)malloc(sizeof(FirstScan));
    firstScan->firstSymbol = NULL;
    firstScan->currentSymbol = firstScan->firstSymbol;
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

    if(line[0] == ';')
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
    TextNode * tempNodeCopy;
    Action * tempAction;
    int intTemp[MAX_LABEL_LEN];

    SymbolNode * lastSymbol = NULL;
    SymbolNode * firstSymbol = NULL;
    SymbolNode * curSymbol = NULL;
    char ** doubleCharP;
    int ** tempInt;
    FirstScan * firstScan;
    int lineCounter = 0;


    firstScan = initScan();
    firstNode = createNode(MAX_LABEL_LEN);
    firstNode = lineParser(asFile, strLen);
    curNode = firstNode;
    curWord = createNode(MAX_LABEL_LEN);
    tempNode = createNode(MAX_LABEL_LEN);
    tempNodeCopy = createNode(MAX_LABEL_LEN);
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
        temp = (char*)malloc(sizeof(strLen));
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
                    firstScan->currentLine->lineIC = firstScan->IC;
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


                for (i = 1; i < z ; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine->nextNode = createIntNode();
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->currentLine->lineIC = firstScan->IC;
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
                while(tempNode->val != NULL)
                {
                    intTemp[z] = atoi(tempNode->val);
                    tempNode = tempNode->nextNode;
                    z++;
                }

                firstScan->DC = firstScan->DC + (4 * (z));

                doublePointer = malloc(z + 1 * sizeof(int*));
                
                doublePointer = freeDInstructions('h', intTemp, z);


                for (i = 1; i < z ; i++)
                {
                    firstScan->currentLine->val = doublePointer[i];
                    firstScan->currentLine->nextNode = createIntNode();
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->currentLine->lineIC = firstScan->IC;
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
                tempInt = malloc(MAX_LABEL_LEN *  sizeof(int*));
                tempInt = freeAsInstruction(temp);
                for (i = 1; i < strlen(tempNode->nextNode->val); i++)
                {
                    firstScan->currentLine->val = tempInt[i];
                    firstScan->currentLine = firstScan->currentLine->nextNode;
                    firstScan->lineCounter++;
                    firstScan->currentLine->lineIC = firstScan->IC;
                    firstScan->IC++;
                }
                instructionFlag++;

                z  = strlen(tempNode->nextNode->val) - 1;
            }

            if(symbolFlag == 1)
            {
                // verify symbol doesn't exsists *******************************************
                if(instructionFlag == 1)
                {
                    if(firstScan->firstSymbol == NULL)
                    {
                        
                        firstScan->firstSymbol = createSymbol();
                        strcpy(firstScan->firstSymbol->symbole,curWord->val);
                        firstScan->firstSymbol->val = firstScan->IC;
                        strcat(firstScan->firstSymbol->att,"data");
                        firstScan->currentSymbol = firstScan->firstSymbol;
                    }
                        
                    else
                    {
                        firstScan->currentSymbol->nextNode = createSymbol();
                        firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
                        strcpy(firstScan->currentSymbol->symbole,curWord->val);
                        firstScan->currentSymbol->val = firstScan->IC;
                        strcat(firstScan->currentSymbol->att,"data");
                        firstScan->DC = firstScan->DC + (z);
                    }   
                }

                else
                {
                    if(firstScan->firstSymbol == NULL)
                    {
                        
                        firstScan->firstSymbol = createSymbol();
                        strcpy(firstScan->firstSymbol->symbole,curWord->val);
                        firstScan->firstSymbol->val = 0;
                        strcat(firstScan->firstSymbol->att,"external");
                        firstScan->currentSymbol = firstScan->firstSymbol;
                    }
                        
                    else
                    {
                        firstScan->currentSymbol->nextNode = createSymbol();
                        firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
                        strcpy(firstScan->currentSymbol->symbole,curWord->val);
                        firstScan->currentSymbol->val = 0;
                        strcat(firstScan->currentSymbol->att,"external");
                        firstScan->DC = firstScan->DC + (z);
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

            //temp = (char*)malloc(sizeof(strLen));
            strcpy(temp, curNode->val);
        
            tempNode = wordParser(temp);
            
            if(tempAction == NULL)
            {
                printf("There is no %s action, in row %d\n", tempNode->val, lineCounter); // checks action validity 
                firstScan->currentLine = createIntNode();
                firstScan->currentLine = firstScan->currentLine->nextNode;
                firstScan->lineCounter++;
                firstScan->currentLine->lineIC = firstScan->IC;
                firstScan->IC += 4;
            }

            else if(tempNode != NULL)
            {
                doubleCharP = malloc(sizeof(char*)  * 32);

                if(doubleCharP == NULL)
                {
                    printf("Memory problem in line %d", lineCounter);
                }


                i = 0;
                while (tempNode->val != NULL)
                {
                    doubleCharP[i] = (char*)malloc(sizeof(char) * MAX_INT);
                    doubleCharP[i] = tempNode->val;
                    tempNode = tempNode->nextNode;
                    i++;
                }

                if(symbolFlag == 1)
                {
                    

                    if(firstScan->firstSymbol == NULL)
                    {
                        
                        firstScan->firstSymbol = createSymbol();
                        strcpy(firstScan->firstSymbol->symbole,doubleCharP[0]);
                        firstScan->firstSymbol->val = firstScan->IC;
                        strcat(firstScan->firstSymbol->att,"data");
                        firstScan->currentSymbol = firstScan->firstSymbol;
                    }
                        
                    else
                    {
                        firstScan->currentSymbol->nextNode = createSymbol();
                        firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
                        strcpy(firstScan->currentSymbol->symbole,doubleCharP[0]);
                        firstScan->currentSymbol->val = firstScan->IC;
                        strcat(firstScan->currentSymbol->att,"data");
                        firstScan->DC = firstScan->DC + (i - 2);
                    }   

                }

                tempAction = getAction(doubleCharP[symbolFlag]);

                
                
                if(tempAction->actionType == 'R')
                {
                    // verify all are names of rgs ***********************
                    if(tempAction->numOfop == 3)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 2]), atoi(doubleCharP[symbolFlag + 3]), 0, 0 , 0);
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->currentLine->lineIC = firstScan->IC;
                        firstScan->IC += 4;
                    }



                    else if(tempAction->numOfop == 2)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), 0, atoi(doubleCharP[symbolFlag + 2]), 0, 0 , 0);
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->currentLine->lineIC = firstScan->IC;
                        firstScan->IC += 4;
                    }

                    else
                    {
                        printf("Unexpected error");
                    }

                }

                else if(tempAction->actionType == 'I')
                {
                    if(tempAction->opcode < 15 && tempAction->opcode > 9)
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 3]), 0,atoi(doubleCharP[symbolFlag + 2]), 0, 0);
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->currentLine->lineIC = firstScan->IC;
                        firstScan->IC += 4;
                    }

                    else if(tempAction->opcode < 19 && tempAction->opcode > 14)
                    {
                        if(isAlphabet(doubleCharP[symbolFlag + 3][0]) == 1)
                        {
                            firstScan->currentLine->labelIsOp = lineCounter;
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0 , 0, 0);;
                            firstScan->currentLine->nextNode = createIntNode();
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->currentLine->lineIC = firstScan->IC;
                            firstScan->IC += 4;
                        }
                    }

                    else
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 3]), 0,atoi(doubleCharP[symbolFlag + 2]), 0, 0);
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->currentLine->lineIC = firstScan->IC;
                        firstScan->IC += 4;
                    }
                }

                else if(tempAction->actionType == 'J')
                {
                    if(isAlphabet(doubleCharP[symbolFlag + 1][0]) == 1)
                    {

                        firstScan->currentLine->labelIsOp = lineCounter;
                        firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0 , 0, 0);
                        firstScan->currentLine->nextNode = createIntNode();
                        firstScan->currentLine = firstScan->currentLine->nextNode;
                        firstScan->lineCounter++;
                        firstScan->currentLine->lineIC = firstScan->IC;
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
                        firstScan->currentLine->lineIC = firstScan->IC;
                        firstScan->IC += 4;

                        }

                        else if(tempAction->opcode == 63)
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0, 0, 0);
                            firstScan->currentLine->nextNode = createIntNode();
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->currentLine->lineIC = firstScan->IC;
                            firstScan->IC += 4;
                        }
                    }  
                }

                else
                {
                    printf("Problem Occured\n");
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
        lineCounter++;
    }

    return firstScan;
}

