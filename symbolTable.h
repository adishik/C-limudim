#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct _SymbolNode // define action in Assembly 
{
    char * symbole;
    int val;
    char * att;
    struct _SymbolNode nextNode;

};
typedef struct _SymbolNode SymbolNode;

struct SymbolNode * createSymbol();
void addSymbole(char * symbolName, int val, char * att, SymbolNode * node);
