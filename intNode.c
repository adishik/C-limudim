#include "intNode.h"
#define MAX_LABEL_LEN 32

#define true 1
#define false 0

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
