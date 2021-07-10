#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#ifndef __ACTION_TABLE__
#define __ACTION_TABLE__

struct _Action;
typedef struct _Action Action;

int * doRType(char * actionName,int * rs, int * rt, int * rd);

#endif
