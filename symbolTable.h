#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct _SymbolNode 
{
    char * symbole;
    int val;
    char * att;
    struct _SymbolNode * nextNode;

};
typedef struct _SymbolNode SymbolNode;

SymbolNode * createSymbol();
SymbolNode * addSymbole(char * symbolName, int val, char * att, SymbolNode * node);
