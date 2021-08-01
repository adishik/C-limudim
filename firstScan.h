#include "parser.h"
#include "symbolTable.h"
#include "actionTable.h"
#include "instructions.h"
#include "intNode.h"

#ifndef __FIRST_SCAN__
#define __FIRST_SCAN__

struct _FirstScan
{
    SymbolNode * firstSymbol;
    IntNode * firstLine;
    IntNode * currentLine;
    int IC;
    int DC;
    int lineCounter;
};
typedef struct _FirstScan FirstScan;
int checkEmpty(char * line);
int isAlphabet(char firstChar);
int isLabel(char * label);
FirstScan * doScan(char * asFile, int strLen);

#endif
