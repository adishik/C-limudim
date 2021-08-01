#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __PARSER__
#define __PARSER__

struct _TextNode  
{
    char * val;
    struct _TextNode * nextNode;
    int nodeSize;
};

typedef struct _TextNode TextNode;
TextNode * createNode(int strLen);

TextNode * lineParser(char * txt, int strLen);
TextNode * wordParser(char * line);


#endif
