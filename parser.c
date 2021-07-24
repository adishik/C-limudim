#include "parser.h"
#define MAX_LABEL_LEN 60



TextNode * createNode()
{
    TextNode * node = (TextNode*)malloc(sizeof(TextNode));
    node->val = (char*)malloc(MAX_LABEL_LEN * sizeof(char));
    node->nextNode = (TextNode*)malloc(sizeof(TextNode));

    return node;
};

TextNode * lineParser(char * txt)
{
    TextNode * par = createNode();
    TextNode * firstNode = par;
    par->val = strtok(txt, "\n");

    while(par->val != NULL)
    {
        TextNode  * nextNode = createNode();
        par->nextNode = nextNode;
        nextNode->val = strtok(NULL, "\n");
        par = nextNode;
    }

    return firstNode;
}

TextNode * wordParser(char * line)
{
    TextNode * par = createNode();
    TextNode * firstNode = par;
    par->val = strtok(line, " :,$");

    while(par->val != NULL)
    {
        TextNode  * nextNode = createNode();
        par->nextNode = nextNode;
        nextNode->val = strtok(NULL, " :,$");
        par = nextNode;
    }

    return firstNode;
}


