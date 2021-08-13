#include "parser.h"
#include "symbolTable.h"
#include "actionTable.h"
#include "instructions.h"
#include "intNode.h"

#ifndef __FIRST_SCAN__
#define __FIRST_SCAN__

/* this moudle will be used in order to make the first scan*/

struct _FirstScan /*this what will be returned and given to the second scan*/
{
    SymbolNode * firstSymbol;
    SymbolNode * currentSymbol;
    IntNode * firstLine;
    IntNode * currentLine;
    int IC;
    int DC;
    int lineCounter;
};
typedef struct _FirstScan FirstScan;
int checkEmpty(char * line); /*gets a line, checks if it's empty*/
int isAlphabet(char firstChar); /*gets a char and return if it's alphbet char*/
int isLabel(char * label); /* gets a line and checks whether there is a label in it*/
int isSavedWord(char * label); /* gets a label and cheks if it's a saved word*/
FirstScan * doScan(char * asFile, int strLen); /*scan it self*/

#endif
