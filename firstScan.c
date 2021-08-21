#include "firstScan.h"
#define MAX_LABEL_LEN 80

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



int checkEmpty(char * line) /* This chekcs if the line is empty or a note */
{
    int i = 0, counter = 0;
    for (i = 0; i < strlen(line); i++)
    {
        if(line[i] == ' ' || line[i] == '\t' || line[i] == '\0') /* Empty */
        {
            counter ++;
        }
    }

    if(counter == i)
    {
        return true;
    }

    if(line[0] == ';') /* Note */
    {
        return true;
    }

    return false;
    
}

int isAlphabet(char firstChar) /* Gets char return if it's alphabet or not */
{
    if(((int)firstChar <= 90 && (int)firstChar >= 65) || ((int)firstChar <= 122 && (int)firstChar >= 97) )
    {
        return true;
    }


    return false;
}

int isLabel(char * label) /* Checks if there is a legal label is this line */
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

int isSavedWord(char * label) /* Retrun whether a lable is saved word */
{
    if(strcmp(label, "add") == 0 ||
        strcmp(label, "sub") == 0  ||
        strcmp(label, "and") ==  0||
        strcmp(label, "or") ==  0||
        strcmp(label, "nor") ==  0||
        strcmp(label, "move") ==  0||
        strcmp(label, "mvhi") ==  0||
        strcmp(label, "mvlo") ==  0||
        strcmp(label, "addi") ==  0||
        strcmp(label, "subi") ==  0||
        strcmp(label, "andi") ==  0||
        strcmp(label, "ori") ==  0||
        strcmp(label, "nori") ==  0||
        strcmp(label, "bne") ==  0||
        strcmp(label, "beq") ==  0||
        strcmp(label, "blt") ==  0||
        strcmp(label, "bgt") ==  0||
        strcmp(label, "lb") ==  0||
        strcmp(label, "sb") ==  0||
        strcmp(label, "lw") ==  0||
        strcmp(label, "sw") ==  0||
        strcmp(label, "lh") ==  0||
        strcmp(label, "sh") ==  0||
        strcmp(label, "jmp") ==  0||
        strcmp(label, "la") ==  0||
        strcmp(label, "call") ==  0||
        strcmp(label, "stop") ==  0||
        strcmp(label, "dh") ==  0||
        strcmp(label, "dw") ==  0||
        strcmp(label, "db") ==  0||
        strcmp(label, "asciz") == 0 ||
        strcmp(label, "extern") == 0 ||
        strcmp(label, "entery") ==  0)
        {
            return 1;
        }

        return 0;
}

FirstScan * doScan(char * asFile, int strLen) /* First Scan */
{
    
    char * temp;
    int symbolFlag = 0;
    int ** doublePointer;
    int instructionFlag = 0;
    int z = 0, i = 0;
    TextNode * firstNode;
    TextNode * curNode;
    TextNode * curWord;
    TextNode * tempNode;
    Action * tempAction;


    int intTemp[MAX_LABEL_LEN];
    int errorCounter = 0;
    SymbolNode * lastSymbol = NULL;
    char ** doubleCharP;
    int ** tempInt;
    FirstScan * firstScan;
    int lineCounter = 0;


    firstScan = initScan();
    firstNode = createNode(MAX_LABEL_LEN);
    firstNode = lineParser(asFile, strLen); /*split the main text to lines*/
    curNode = firstNode;
    curWord = createNode(MAX_LABEL_LEN);
    tempNode = createNode(MAX_LABEL_LEN);
    tempAction = (Action*)malloc(sizeof(Action));


    while(curNode->val != NULL) /* as long as thei are white labels we skip them*/
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
        temp = (char*)malloc(strLen*sizeof(char));
        strcpy(temp, curNode->val);

       
        curWord = wordParser(temp); /*split the line to word*/

        if(isLabel(curNode->val)) 
        {
            symbolFlag = 1;
        }


        
        
        
        if(strchr(temp,'.') != NULL) /*meaing there is an instruction here*/
        {
            /* the way i handle instructions, is first checking it's kind, than according to the spec I code it */
           
            temp = strchr(curNode->val,'.');

            i = checkInstructionSyntax(temp, strlen(temp));
	    

            if(i != 0)
            {
                if(i == 1)
                {
                    printf("Syntax error in %d, to many commas\n", lineCounter);
		    curNode = curNode->nextNode;
        	    symbolFlag = 0;
                    lineCounter++;
                    errorCounter++;
                }

                else
                {
                    printf("Error in line %d, Line is too long\n", lineCounter);
                    errorCounter++;
                }
            }
            i = 0;

            if(temp[2] == 'b') /* .db */
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


                for (i = 0; i < z ; i++) /* for each number we need to assign memory */
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

            else if(temp[2] == 'w') /* .dw */
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


                for (i = 1; i < z ; i++) /* for each number we need to assign memory */
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

            else if(temp[2] == 'h') /* .dh */
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


                for (i = 1; i < z ; i++) /* for each number we need to assign memory */
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

            else if(temp[2] == 's') /* asicz */
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

            else if(temp[2]  == 'x') /* external */
            {
                doubleCharP = malloc(sizeof(char*)  * 32);

                if(doubleCharP == NULL)
                {
                    printf("Memory problem in line %d", lineCounter);
                }

                tempNode = wordParser(temp);
                i = 0;
                while (tempNode->val != NULL)
                {
                    doubleCharP[i] = (char*)malloc(sizeof(char) * MAX_INT);
                    doubleCharP[i] = tempNode->val;
                    tempNode = tempNode->nextNode;
                    i++;
                }

                if(firstScan->firstSymbol == NULL) /*Checks label valididty */
                {
                    
                    firstScan->firstSymbol = createSymbol();
                    if(isAlphabet( doubleCharP[1][0]) == 0)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }

                    if(isSavedWord(doubleCharP[0]) == 1)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }
                    strcpy(firstScan->firstSymbol->symbole,doubleCharP[1]);
                    firstScan->firstSymbol->val = 0;
                    strcat(firstScan->firstSymbol->att,"external");
                    firstScan->currentSymbol = firstScan->firstSymbol;
                }
                    
                else
                {
                    if(isAlphabet( doubleCharP[1][0]) == 0)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }


                    if(isSavedWord(doubleCharP[1]) == 1)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }

                    firstScan->currentSymbol->nextNode = createSymbol();
                    firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
                    strcpy(firstScan->currentSymbol->symbole,doubleCharP[1]);
                    firstScan->currentSymbol->val = 0;
                    strcat(firstScan->currentSymbol->att,"external");
                    firstScan->DC = firstScan->DC + (z);
                }

                firstScan->lineCounter++; 
            }

           

            else if(temp[2]  == 'n') /* .entery */
            {
                firstScan->lineCounter++;
            }

            else /* if we didin;t find any of the above it means there is a problem with the instruction*/
            {
          
                tempNode = wordParser(temp);
                printf("Error in line %d, %s is not an instruction\n", lineCounter, tempNode->val);
                errorCounter++;
            }

            if(symbolFlag == 1)
            {

                lastSymbol = createSymbol();
                lastSymbol = firstScan->firstSymbol;

                if(checkIfSymbolExsits(lastSymbol, curWord->val) == 1) /*validates that the symbol doesn't exsits in the symbol table*/
                {
                    printf("Error in line %d Symbol %s already exsists\n", lineCounter, curWord->val);
                    errorCounter++;
                }
                
                if(instructionFlag == 1) /* if it's an instruction */
                {
                    if(firstScan->firstSymbol == NULL)
                    {
                        if(isAlphabet( curWord->val[0]) == 0)
                        {
                            printf("Error in line %d, illegal Label\n", lineCounter);
                            errorCounter++;
                        }

                        if(isSavedWord(curWord->val) == 1)
                        {
                            printf("Error in line %d, illegal Label\n", lineCounter);
                            errorCounter++;
                        }

                        firstScan->firstSymbol = createSymbol();
                        strcpy(firstScan->firstSymbol->symbole,curWord->val);
                        firstScan->firstSymbol->val = firstScan->IC;
                        strcat(firstScan->firstSymbol->att,"data");
                        firstScan->currentSymbol = firstScan->firstSymbol;
                    }
                        
                    else
                    {
                        if(isAlphabet( curWord->val[0]) == 0)
                        {
                            printf("Error in line %d, illegal Label\n", lineCounter);
                            errorCounter++;
                        }

                        if(isSavedWord(curWord->val) == 1)
                        {
                            printf("Error in line %d, illegal Label\n", lineCounter);
                            errorCounter++;
                        }

                        firstScan->currentSymbol->nextNode = createSymbol();
                        firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
                        strcpy(firstScan->currentSymbol->symbole,curWord->val);
                        firstScan->currentSymbol->val = firstScan->IC;
                        strcat(firstScan->currentSymbol->att,"data");
                        firstScan->DC = firstScan->DC + (z);
                    }   
                }
            }            
        }

        else /*  Meaning this line is action and not instruction*/
        {
            if(isLabel(curNode->val))
            {
                symbolFlag = 1;
            }

            strcpy(temp, curNode->val);
        
            tempNode = wordParser(temp); /* Parsing line to Words */
            
            if(tempAction == NULL)
            {
                printf("There is no %s action, in row %d\n", tempNode->val, lineCounter);
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
                    printf("Memory problem in line %d\n", lineCounter);
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
                    
                    lastSymbol = createSymbol();
                    lastSymbol = firstScan->firstSymbol;

                    if(checkIfSymbolExsits(lastSymbol, doubleCharP[0]) == 1) /* Checks if the symbol already exsists in the symbol table */
                    {
                        printf("Error in line %d Symbol %s already exsists\n", lineCounter, doubleCharP[0]);
                        errorCounter++;
                    }

                    if(firstScan->firstSymbol == NULL)
                    {
                        if(isAlphabet( doubleCharP[0][0]) == 0)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }

                    if(isSavedWord(doubleCharP[0]) == 1) /* Checks if the symbol is saved word */
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }
                        
                        firstScan->firstSymbol = createSymbol();
                        strcpy(firstScan->firstSymbol->symbole,doubleCharP[0]);
                        firstScan->firstSymbol->val = firstScan->IC;
                        strcat(firstScan->firstSymbol->att,"data");
                        firstScan->currentSymbol = firstScan->firstSymbol;
                    }
                        
                    else
                    {

                    if(isAlphabet( doubleCharP[0][0]) == 0)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }

                    if(isSavedWord(doubleCharP[0]) == 1)
                    {
                        printf("Error in line %d, illegal Label\n", lineCounter);
                        errorCounter++;
                    }
                        firstScan->currentSymbol->nextNode = createSymbol();
                        firstScan->currentSymbol = firstScan->currentSymbol->nextNode;
                        strcpy(firstScan->currentSymbol->symbole,doubleCharP[0]);
                        firstScan->currentSymbol->val = firstScan->IC;
                        strcat(firstScan->currentSymbol->att,"data");
                        firstScan->DC = firstScan->DC + (i - 2);
                    }   

                }

                tempAction = getAction(doubleCharP[symbolFlag]); /* Getts current action */

                if(tempAction == NULL) /* meaning action not found */
                {
                    printf("Error in line %d, %s is not an action\n", lineCounter, doubleCharP[symbolFlag]);
                    errorCounter++;
                }

                
                else
                {   
                    
                    if(tempAction->actionType == 'R') /* Coding R type actions */
                    {
                        if(tempAction->numOfop == 3) /* Case the number of operands is 3 */
                        {
                            firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 2]), atoi(doubleCharP[symbolFlag + 3]), 0, 0 , 0);
                            firstScan->currentLine->nextNode = createIntNode();
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->currentLine->lineIC = firstScan->IC;
                            firstScan->IC += 4;
                        }



                        else if(tempAction->numOfop == 2) /* Case the number of operands is 2 */
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
                            errorCounter++;
                        }

                    }

                    else if(tempAction->actionType == 'I') /* Coding I type actions */
                    {
                        if(tempAction->opcode < 15 && tempAction->opcode > 9) /* nori, andi, ori, subi, addi */
                        {
                            firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 3]), 0,atoi(doubleCharP[symbolFlag + 2]), 0, 0);
                            firstScan->currentLine->nextNode = createIntNode();
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->currentLine->lineIC = firstScan->IC;
                            firstScan->IC += 4;
                        }

                        else if(tempAction->opcode < 19 && tempAction->opcode > 14) /* bgt, blt, bne, beq */
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

                        else /* all of the rest */
                        {
                            firstScan->currentLine->val = codeAction(tempAction,atoi(doubleCharP[symbolFlag + 1]), atoi(doubleCharP[symbolFlag + 3]), 0,atoi(doubleCharP[symbolFlag + 2]), 0, 0);
                            firstScan->currentLine->nextNode = createIntNode();
                            firstScan->currentLine = firstScan->currentLine->nextNode;
                            firstScan->lineCounter++;
                            firstScan->currentLine->lineIC = firstScan->IC;
                            firstScan->IC += 4;
                        }
                    }

                    else if(tempAction->actionType == 'J') /* we can't really do anything with J type action on the first scan so we are keeping them an empty line, wit only OP Coded, wil be treated in the Second scan */
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
                            if(tempAction->opcode == 30) 
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
                }
            }

            else
            {
                printf("unexcpected error\n");
                errorCounter++;
                exit(1);
            }
        }

        curNode = curNode->nextNode;
        symbolFlag = 0;
        lineCounter++;
    }

    if(errorCounter > 0)
    {
        printf("exit with %d erros\n", errorCounter);
        return 0;
    }

    return firstScan;
}

