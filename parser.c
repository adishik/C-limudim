#include "parser.h"
#define MAX_LABEL_LEN 60


#define true 1
#define false 0


TextNode * createNode(int strLen)
{
    TextNode * node = (TextNode*)malloc(sizeof(TextNode));
    node->val = NULL;//(char*)malloc(strLen * sizeof(char));
    node->nextNode = (TextNode*)malloc(sizeof(TextNode));
    node->nodeSize = 0;

    return node;
}

TextNode * lineParser(char * txt, int strLen)
{
    TextNode * par;
    TextNode * firstNode;
    par = createNode(strLen);
    firstNode = par;
    par->val = strtok(txt, "\n");
    par->nodeSize++;
   
    while(par->val != NULL)
    {
        
        TextNode  * nextNode = createNode(MAX_LABEL_LEN);
        par->nodeSize++;
        par->nextNode = nextNode;
        par = par->nextNode;
        par->val = strtok(NULL, "\n");
    }



    return firstNode;
}

TextNode * wordParser(char * line)
{
    TextNode * par;
    TextNode * firstNode;
    par = createNode(MAX_LABEL_LEN);
    firstNode = par;
    par->val = strtok(line, " :,$");
    if(par->val == NULL)
    {
        printf("NULL\n");
    }
    par->nodeSize++;
   
    while(par->val != NULL)
    {
        
        TextNode  * nextNode = createNode(MAX_LABEL_LEN);
        par->nodeSize++;
        par->nextNode = nextNode;
        par = par->nextNode;
        par->val = strtok(NULL, " :,$");
    }



    return firstNode;
}


