#include "intNode.h"
#define MAX_LABEL_LEN 32

#define true 1
#define false 0
/* this modoule is used for the scan line, which are coded in araay of number(0 and 1)*/
IntNode * createIntNode()
{
    IntNode * node = (IntNode*)malloc(sizeof(IntNode));
    node->val = (int*)malloc(MAX_LABEL_LEN * sizeof(int));
    node->nextNode = NULL;
    node->nodeSize = 0;
    node->labelIsOp = false; 
    node->lineIC = 0;

    return node;
}
