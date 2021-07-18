#include "assemmText.h"
textNode * readText()
{
    int index = -1;
    struct textNode *firstNode = createNode(); // we want to keep the first node address becaseu each one will point tot the next 
    struct textNode *curNode = firstNode;
    char newInput; // input from the user 

    do
    {
        index ++;

        if(index > 1)
        {
            firstInLine = false;
        }

        if(index == MAX__LINE_LEN)
        {
            struct textNode *nextNode = createNode();
            curNode->next = nextNode;
            curNode = nextNode;
            index = -1;
            bool firstInLine = true;
        }

        newInput = getchar();

        if(newInput == '\t' || newInput == ' ')
        {
            index --;
        }

        if(newInput == '\n')
        {
            struct textNode *nextNode = createNode();
            curNode->next = nextNode;
            curNode = nextNode;
            index = -1;
            bool firstInLine = true;
        }

    } while (curNode->val[index] != EOF);

        curNode->val[index] = '\0';

        return firstNode;

    }
}
