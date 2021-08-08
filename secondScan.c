#include "secondScan.h"
#def MAX_LEN_LINE 60 
#def INT_SIZE 32

void * doSecondScan(FirstScan firstScan)
{  
    TextNode * tempNode;
    char ** doubleCharP;
    SymbolNode curSym;
    TextNode * curWord;
    Action * tempAction;
    int symbolFlag = 0;
    char  * temp;
    tempNode = createNode();
    firstScan->currentLine = firstScan->firstLine;
    curSym = createSymbol();
    curWord = createNode();
    temp = (char*)malloc(MAX_LEN_LINE *  sizeof(char));
    tempAction = (Action*)malloc(sizeof(Action));
    firstScan->lineCounter = 0;
    
    while(firstScan->currentLine != NULL)
    {
        while(checkEmpty(firstScan->currentLine) == 1)
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

        tempNode = lineParser(firstScan->currentLine->val, strlen(firstScan->currentLine->val));
        if(isLabel(curNode->val) == 1)
        {
            symbolFlag = 1;
        }

        doubleCharP = malloc(sizeof(char*)  * MAX_LEN_LINE);

       

        strcpy(temp, tempNode->val);
        curWord = wordParser(temp);

         while (curWord->val != NULL)
        {
            doubleCharP[i] = (char*)malloc(sizeof(char) * INT_SIZE);
            doubleCharP[i] = curWord->val;
            curWord = curWord->nextNode;
            i++;
        }
        
        if(firstScan->currentLine->labelIsOp == 1)
        {
            curSym = firstScan->firstSymbol;
            strcpy(temp, doubleCharP[symbolFlag]);
            tempAction = getAction(temp);
            
            while(curSym->nextNode != NULL)
            {
                if(strcmp(doubleCharP[symbolFlag], curSym->symbole) == 0)
                {
                    if(tempAction->actionType == 'I')
                    {
                        codeAction(tempAction,doubleCharP[symbolFlag + 1], doubleCharP[symbolFlag + 2], 0, curSym->val - firstScan->IC , 0 , 0 );
                    }

                    if(tempAction->actionType == 'J')
                    {
                        if(tempAction->opcode = 30)
                        {
                            codeAction(tempAction, 0, 0, 0, 0 , 1, curSym->val);
                        }

                        if(tempAction->opcode == 31 || tempAction->opcode == 32)
                        {
                            codeAction(tempAction, 0, 0, 0, 0 , 0, curSym->val);
                        }

                        else
                        {
                            codeAction(tempAction, 0, 0, 0, 0 , 0, 0);
                        }
                    }
                }

                else
                {
                    printf("error in line %d, Symbool %s is not defined", firstScan->lineCounter, doubleCharP[symbolFlag]);
                }
            }
        }
    }


}
