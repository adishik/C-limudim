#include "filesCreator.h"

    
/* this moudle generates the files*/
/* I used the same algorithem the was mentiond in the maman, with one side note, for J type actions I didn't do anything in the first scan*/
/* I just cread an empty line with the action OP code, and it was handled in the second scan*/
    
    
    
void creatFiles(int argc, char *argv[])
{

    FirstScan * gg;
    int i = 0, y=0;
    char * buffer;
    char * buffer2;
    long int res;
    long int res2;
    int t;
    int tempInt;
    char tempChar;
    char tempString[12];
    char tempLine[15];
    char  * saveName;
    char tempFileName[255];
    FILE* fp;

    


    printf("Scan begins\n");
    for (y = 1; y < argc; y++) /* for each file in the command arrgs*/
    {

        saveName = (char*)malloc(strlen(argv[y]));

        i = 0;
        while(argv[y][i] != '.')
        {
            saveName[i] = argv[y][i];
            i++;
        }
        

        fp = fopen(argv[y], "r");    
        /* checking if the file exist or not */
        if (fp == NULL) 
        {
            printf("File Not Found!\n");
            return;
        }
    
        fseek(fp, 0L, SEEK_END);
    
        /* calculating the size of the file */
        res = ftell(fp);
    
        rewind(fp);
        
        buffer = (char*)malloc(res + 1);

        fread(buffer, res, 1, fp);
        buffer[res] = '\0';

        buffer2 = (char*)malloc(res + 1);

        strcpy(buffer2, buffer);



        res2 = res;

        gg = (FirstScan*)malloc(sizeof(FirstScan));

        gg = doScan(buffer, res); /* First Scan */
	
	if(gg == 0)/*Meaning there were errors*/
	{
		printf("Errors was found in the first scan, file %d, moving to the next", y);
	}
	
	else
	{
		gg = doSecondScan(gg, buffer2, res2); /* Second Scan */
		
		if(gg == 0)/* Meaning there were errors*/
		{
			printf("Errors was found in the seond scan, file %d, moving to the next", y);
		}

		else
		{

			strcpy(tempFileName, saveName); /* These three limes will be used to creat a file with the right name */
			strcat(tempFileName, ".ob");
			fp = fopen(tempFileName, "w");

			if (fp == NULL)
			{
			    printf("File does not exist.\n");
			    return;
			}
		       
		
			gg->currentLine = gg->firstLine;

			t = 100;
			fprintf(fp, "     %d %d\n", gg->DC, gg->IC);

			while(gg->currentLine != NULL) /* the next model turns the second scan Binary code to hexadecimal*/
			{
				
			    
			    if(gg->currentLine->nextNode == NULL)
			    {
				break;
			    }

			    if(t < 1000)
			    {
				fprintf(fp, "0%d ", t); /* Adding a 0 before the address*/
			    }

			    else
			    {
				fprintf(fp, "%d ", t);
			    }

			    for(i = 0; i < 32; i+=8) /* by puuting + '0' we can covert integr to char */
			    {
			       tempChar =  gg->currentLine->val[i] + '0' ;
			       strncat(tempString, &tempChar, 1);
			       tempChar =  gg->currentLine->val[i + 1] + '0';
			       strncat(tempString, &tempChar, 1);
			       tempChar =  gg->currentLine->val[i + 2] + '0';
			       strncat(tempString, &tempChar, 1);
			       tempChar =  gg->currentLine->val[i + 3] + '0';
			       strncat(tempString, &tempChar, 1);


			       tempInt = (int)strtol(tempString, NULL, 2);

			       sprintf(tempString, "%x", tempInt); /* turn Bin to Hex */

			       strcat(tempLine, tempString);


			       strcpy(tempString, "");

			       tempChar =  gg->currentLine->val[i + 4] + '0' ;
			       strncat(tempString, &tempChar, 1);
			       tempChar =  gg->currentLine->val[i + 5] + '0';
			       strncat(tempString, &tempChar, 1);
			       tempChar =  gg->currentLine->val[i + 6] + '0';
			       strncat(tempString, &tempChar, 1);
			       tempChar =  gg->currentLine->val[i + 7] + '0';
			       strncat(tempString, &tempChar, 1);


			       
			       tempInt = (int)strtol(tempString, NULL, 2); /* turn Bin to Hex */

			       sprintf(tempString, "%x", tempInt);

			       strcat(tempLine, tempString);

			       strcat(tempLine, " ");
			       strcpy(tempString, "");

			    }

			    t+=4;

			    fprintf(fp, "%s", tempLine);

			    

			    fprintf(fp, "\n");

			    strcpy(tempLine, "");

			    gg->currentLine = gg->currentLine->nextNode;



			}

			fclose(fp);
			i = 0;

			gg->currentSymbol = gg->firstSymbol; /* Create .ent files, if nescary*/

			while(gg->currentSymbol->nextNode != NULL)
			{
			    if(strstr(gg->currentSymbol->att, "entry"))
			    {
				i++;
			    }

			    gg->currentSymbol = gg->currentSymbol->nextNode;
			}

			if(i > 0)
			{
			    strcpy(tempFileName, saveName);
			    strcat(tempFileName, ".ent");
			    fp = fopen(tempFileName, "w");

			    if (fp == NULL)
			    {
				fprintf(fp, "File does not exist.\n");
				return;
			    }

			    gg->currentSymbol = gg->firstSymbol;
			    


			    while(gg->currentSymbol->nextNode != NULL)
			    {
				if(strstr(gg->currentSymbol->att, "entry"))
				{
				    fprintf(fp, "%s %d\n",gg->currentSymbol->symbole, gg->currentSymbol->val);
				}

				gg->currentSymbol = gg->currentSymbol->nextNode;
			    }

			fclose(fp);
			}

			i = 0;

			gg->currentSymbol = gg->firstSymbol; /* Create .ext files, if nescary*/

			while(gg->currentSymbol->nextNode != NULL)
			{
			    if(strstr(gg->currentSymbol->att, "external"))
			    {
				i++;
			    }

			    gg->currentSymbol = gg->currentSymbol->nextNode;
			}

			if( i > 0 )
			{
			    strcpy(tempFileName, saveName);
			    strcat(tempFileName, ".ext");
			    fp = fopen(tempFileName, "w");

			    if (fp == NULL)
			    {
				fprintf(fp, "File does not exist.\n");
				return;
			    }

			    gg->currentSymbol = gg->firstSymbol;

			    while(gg->currentSymbol->nextNode != NULL)
			    {
				if(strstr(gg->currentSymbol->att, "external"))
				{
				    fprintf(fp, "%s %d\n",gg->currentSymbol->symbole, gg->currentSymbol->val);
				}

				gg->currentSymbol = gg->currentSymbol->nextNode;
			    }
			}



		
			free(buffer2);
			free(buffer);

			res = 0;
			res2 = 0;
			free(gg);
		}
	}
	
	printf("File number %d, scanned, moving on\n", y);

    }
printf("scan finished\n");

    

    
}
