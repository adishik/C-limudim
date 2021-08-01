#include "symbolTable.h"
#define MAX_LABEL_LEN 31 


SymbolNode * createSymbol()
{
    SymbolNode * node = (SymbolNode*)malloc(sizeof(SymbolNode));
    node->symbole = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->val = 0;
    node->att = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->nextNode = (SymbolNode*)malloc(sizeof(SymbolNode));


    return node;
}

void addSymbole(char * symbolName, int val, char * att, SymbolNode * node)
{
    strcpy(node->symbole, symbolName);
    node->val = val;
    strcat(node->att,att);
}

