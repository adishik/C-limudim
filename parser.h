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
};

typedef struct _TextNode TextNode;
TextNode * createNode();

TextNode * lineParser(char * txt);
TextNode * wordParser(char * line);


#endif
