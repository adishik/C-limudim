#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

/* this moudle handels the symbols*/

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
int checkIfSymbolExsits(SymbolNode * node, char * symbol);/* chwlc if the current symbol exsits in the table*/
