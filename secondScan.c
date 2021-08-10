#include "secondScan.h"
#define MAX_LEN_LINE 60 
#define INT_SIZE 32

FirstScan * doSecondScan(FirstScan * firstScan, char * asFile, int strLen)
{  
    TextNode * tempNode;
    char ** doubleCharP;
    SymbolNode  * curSym;
    TextNode * curWord;
    TextNode * firstLine;
    Action * tempAction;
    int i = 0;
    int symbolFlag = 0;
    char  * temp;
    tempNode = createNode(strLen);
    firstScan->currentLine = firstScan->firstLine;
    curSym = createSymbol();
    curWord = createNode(MAX_LEN_LINE);
    temp = (char*)malloc(strLen *  sizeof(char));
    tempAction = (Action*)malloc(sizeof(Action));
    int lineCounter = 0;
    int labelLoc = 0;
    int labelFound = 0;

    firstLine = createNode(strLen);
    tempNode = lineParser(asFile, strLen);
    firstLine = tempNode;

    firstScan->currentSymbol = firstScan->firstSymbol;


    if(firstScan->currentLine == NULL || tempNode == NULL)
    {
        return 0;
    }
    
    while(firstScan->currentLine->nextNode != NULL)
    {
        while(checkEmpty(tempNode->val) == 1)
        {
            if(firstScan->currentLine->nextNode == NULL)
            {
                break;
                //FILEOUTPUT>>>>>>>>
            }

            else
            {
                firstScan->currentLine = firstScan->currentLine->nextNode;
            }
        }
       

        if(firstScan->currentLine->labelIsOp != 0)
        {
            i = 0;

            while(i < firstScan->currentLine->labelIsOp)
            {
                tempNode = tempNode->nextNode;
                i++;
            }

            if(isLabel(tempNode->val) == 1)
            {
                symbolFlag = 1;
            }

            doubleCharP = malloc(sizeof(char*) * MAX_LEN_LINE);

            strcpy(temp, tempNode->val);
            curWord = wordParser(temp);

            i = 0;

            while (curWord->val != NULL)
            {
                doubleCharP[i] = (char*)malloc(sizeof(char) * INT_SIZE);
                doubleCharP[i] = curWord->val;
                curWord = curWord->nextNode;
                i++;
            }



            firstScan->currentSymbol = firstScan->firstSymbol;
            tempAction = getAction(doubleCharP[symbolFlag]);

            
            while(firstScan->currentSymbol->nextNode != NULL)
            {
                if(tempAction->actionType == 'J')
                {
                    labelLoc = symbolFlag + 1;
                }

                else
                {
                    labelLoc = symbolFlag + 3;
                }
                
                if(strcmp(doubleCharP[labelLoc], firstScan->currentSymbol->symbole) == 0)
                {
                    labelFound = 1;
                    if(tempAction->actionType == 'I')
                    {
                        firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 2]), 0, firstScan->currentSymbol->val - firstScan->IC , 0 , 0 );
                    }

                    else if(tempAction->actionType == 'J')
                    {
                        if(tempAction->opcode == 30)
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0 ,1, firstScan->currentSymbol->val);
                        }

                        else if(tempAction->opcode == 31 || tempAction->opcode == 32)
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0 , 0, firstScan->currentSymbol->val);
                        }

                        else
                        {
                            firstScan->currentLine->val = codeAction(tempAction, 0, 0, 0, 0 , 0, 0);
                        }
                    }

                    else
                    {
                        printf("Unexpected Error");
                    }
                }

                firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
            }
            
            if(labelFound == 0)
            {
                printf("error in line %d, Symbool %s is not defined\n", lineCounter, doubleCharP[labelLoc]);
            }
        }


        firstScan->currentLine = firstScan->currentLine->nextNode;
        symbolFlag = 0;
        lineCounter++;
        tempNode = firstLine;
        labelLoc = 0;
        labelFound = 0;
    }

    free(temp);
    free(firstLine);
    free(curWord);
    free(tempAction);






    return firstScan;


}
