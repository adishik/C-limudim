#include "parser.h"
#include "symbolTable.h"
#include "actionTable.h"
#include "instructions.h"
#include "intNode.h"

#ifndef __FIRST_SCAN__
#define __FIRST_SCAN__

struct _FirstScan // define action in Assembly 
{
    SymbolNode * firstSymbol;
    IntNode * firstLine;
    IntNode * currentLine;
    int IC;
    int DC;
};
typedef struct _FirstScan FirstScan;
bool checkEmpty(char * line);
bool isAlphabet(char firstChar);
bool isLabel(char * label);
FirstScan * doScan(char * asFile);

#endif
