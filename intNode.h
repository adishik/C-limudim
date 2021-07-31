#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __INT_NODE__
#define __INT_NODE__

struct _IntNode  
{
    int * val;
    struct _IntNode * nextNode;
    int nodeSize;
    bool labelIsOp;
};

typedef struct _IntNode IntNode;
IntNode * createIntNode();



#endif
