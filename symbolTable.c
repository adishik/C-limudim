#include "symbolTable.h"
#define MAX_LABEL_LEN 31 //maximum lenght of a lable in assembly


struct SymbolNode * createSymbol()
{
    struct SymbolNode * node = (SymbolNode*)malloc(sizeof(SymbolNode));
    node->symbole = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->val = (int*)calloc(sizeof(int));;
    node->att = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->nextNode = (SymbolNode*)malloc(sizeof(SymbolNode));


    return node;
};

void addSymbole(char * symbolName, int val, char * att, SymbolNode * node)
{
    strcpy(node->symbole, symbolName);
    node->val = val;
    strcat(node->att,att);
}

