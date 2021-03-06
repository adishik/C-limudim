#include "symbolTable.h"
#define MAX_LABEL_LEN 31 


SymbolNode * createSymbol() /* Creating Symbol Node */
{
    SymbolNode * node = (SymbolNode*)malloc(sizeof(SymbolNode));
    node->symbole = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->val = -1;
    node->att = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->nextNode = NULL;


    return node;
}

SymbolNode * addSymbole(char * symbolName, int val, char * att, SymbolNode * node) /* Addign symbol to the table */
{
    SymbolNode * node2 = createSymbol();
    node2->symbole = symbolName;
    node2->val = val;
    strcat(node2->att,att);

    return node2;
}

int checkIfSymbolExsits(SymbolNode * node, char * symbol) /* checks if the symbol exsists in the symbol table already */
{
    while(node!= NULL)
    {
        if(strcmp(node->symbole, symbol) == 0)
        {
         
            return 1;
        }

        node = node->nextNode;
    }

    return 0;
}

