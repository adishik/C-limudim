#include "intNode.h"

IntNode * createIntNode()
{
    IntNode * node = (IntNode*)malloc(sizeof(IntNode));
    node->val = (int*)malloc(MAX_LABEL_LEN * sizeof(int));
    node->nextNode = (IntNode*)malloc(sizeof(IntNode));
    node->nodeSize = 0;
    labelIsOp = false; // this field will be turned on when a label is part of the action operands, we will know no to code it

    return node;
}
