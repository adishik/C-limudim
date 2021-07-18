#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


struct _textNode * createNode()
{
    struct textNode* node = (struct textNode*)calloc(MAX__LINE_LEN, sizeof(struct textNode*));
    node->val = (char *)calloc(MAX__LINE_LEN,sizeof(char));
    node->next = (struct textNode*)calloc(MAX__LINE_LEN, sizeof(char));;
    node->size = 1;

    return node;
};

typedef struct _textNode textNode;
textNode * readText();

