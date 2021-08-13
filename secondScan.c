#include "secondScan.h"
#define MAX_LEN_LINE 60 
#define INT_SIZE 32

/* second scan, gets the result of the first*/

FirstScan * doSecondScan(FirstScan * firstScan, char * asFile, int strLen)
{  
    TextNode * tempNode;
    char ** doubleCharP;
    SymbolNode  * curSym;
    TextNode * curWord;
    TextNode * firstLine;
    Action * tempAction;
    int foundEntery = 0;
    int errorCounter = 0;
    int i = 0;
    int symbolFlag = 0;
    char  * temp;
    int lineCounter = 0;
    int labelLoc = 0;
    int labelFound = 0;
    tempNode = createNode(strLen);
    firstScan->currentLine = firstScan->firstLine;
    curSym = createSymbol();
    curWord = createNode(MAX_LEN_LINE);
    temp = (char*)malloc((strLen + 1) *  sizeof(char));
    tempAction = (Action*)malloc(sizeof(Action));
    




    firstLine = createNode(strLen);


    tempNode = lineParser(asFile, strLen);
    firstLine = tempNode;

    firstScan->currentSymbol = firstScan->firstSymbol;


    if(firstScan->currentLine == NULL || tempNode == NULL)
    {
        return 0;
    }
    
    while(firstScan->currentLine != NULL)
    {
        while(checkEmpty(tempNode->val) == 1)
        {
            if(firstScan->currentLine->nextNode == NULL)
            {
                break;
            }

            else
            {
                firstScan->currentLine = firstScan->currentLine->nextNode;
            }
        }
       

        if(firstScan->currentLine->labelIsOp != 0) /* this was set by the first scan*/
                                                    /* it informs that we have a label as oparnd in this line*/
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

            
            while(firstScan->currentSymbol != NULL)
            {
                if(tempAction->actionType == 'J')
                {
                    labelLoc = symbolFlag + 1; /* label location*/
                }

                else
                {
                    labelLoc = symbolFlag + 3;/* label location*/
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
                        errorCounter++;
                    }
                }

                firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
            }
            
            if(labelFound == 0)
            {
                printf("error in line %d, Symbool %s is not defined\n", lineCounter, doubleCharP[labelLoc]);
                errorCounter++;
            }
        }

        firstScan->currentLine = firstScan->currentLine->nextNode;
        symbolFlag = 0;
        lineCounter++;
        tempNode = firstLine;
        labelLoc = 0;
        labelFound = 0;
    }
    

    tempNode = firstLine;

    firstScan->currentSymbol = firstScan->firstSymbol;
    lineCounter = 0;

    while (tempNode->nextNode != NULL)
    {
        if(strchr(tempNode->val, '.') != NULL) /* instruction*/
        {
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


            if(strcmp(doubleCharP[symbolFlag], ".entery") == 0)
            {

                firstScan->currentSymbol = firstScan->firstSymbol;

                while(firstScan->currentSymbol->nextNode != NULL)
                {


                    if(strcmp(doubleCharP[symbolFlag + 1], firstScan->currentSymbol->symbole) == 0)
                    {
                        strcat(firstScan->currentSymbol->att, "entry");
                        foundEntery = 1;
                    }

                    firstScan->currentSymbol = firstScan->currentSymbol->nextNode;

                }

                if(foundEntery == 0)
                {
                    printf("error in line %d symbol %s doesn't exsist and assign to entry\n ", lineCounter, doubleCharP[symbolFlag + 1]);
                    errorCounter++;
                }
            }

            foundEntery = 0;
        }

        tempNode = tempNode->nextNode;
        lineCounter++;
    }
    



    free(temp);
    free(firstLine);
    free(curWord);
    free(tempAction);



    if(errorCounter > 0)
    {
        printf("exit with %d erros\n", errorCounter);
        exit(2);
    }
    
    return firstScan;


}
