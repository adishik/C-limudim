#include "parser.h"
#define MAX_LABEL_LEN 80


#define true 1
#define false 0


TextNode * createNode(int strLen)
{
    TextNode * node = (TextNode*)malloc(sizeof(TextNode));
    node->val = NULL;
    node->nextNode = NULL;
    node->nodeSize = 0;

    return node;
}

TextNode * lineParser(char * txt, int strLen) /* parser according to \n */
{
    TextNode * par; /* will be used as temp node for parsing */
    TextNode * firstNode; /* Will keep the first parsed node to return */
    par = createNode(strLen);
    firstNode = par;
    par->val = strtok(txt, "\n"); /* parsing accordign to lines */
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

TextNode * wordParser(char * line) /* parser according to :, $ */
{
    TextNode * par; /* will be used as temp node for parsing */
    TextNode * firstNode; /* Will keep the first parsed node to return */
    firstNode = (TextNode*)malloc(sizeof(TextNode));
    par = firstNode;
    par->val = strtok(line, " :,$"); /* parsing accordign to words */

    if(par->val == NULL)
    {
        printf("NULL\n");
       

        return 0;
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


