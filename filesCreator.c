#include "filesCreator.h"

    
    
    
    
void creatFiles(int argc, char *argv[])
{

    FirstScan * gg;
    int i = 0, z = 0, y=0;
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

    



    
    for (y = 1; y < argc; y++)
    {

        saveName = (char*)malloc(strlen(argv[1]));

        i = 0;
        while(argv[1][i] != '.')
        {
            saveName[i] = argv[1][i];
            i++;
        }
        

        fp = fopen(argv[y], "r");    
        // checking if the file exist or not
        if (fp == NULL) 
        {
            printf("File Not Found!\n");
            return;
        }
    
        fseek(fp, 0L, SEEK_END);
    
        // calculating the size of the file
        res = ftell(fp);
    
        rewind(fp);
        
        buffer = (char*)malloc(res + 1);
        // closing the file

        fread(buffer, res, 1, fp);
        buffer[res] = '\0';

        buffer2 = (char*)malloc(res + 1);

        strcpy(buffer2, buffer);



        res2 = res;

        gg = (FirstScan*)malloc(sizeof(FirstScan));


        gg = doScan(buffer, res);
        gg = doSecondScan(gg, buffer2, res2);
        

        strcpy(tempFileName, saveName);
        strcat(tempFileName, ".ob");
        fp = fopen(tempFileName, "w");

        if (fp == NULL)
        {
            printf("File does not exist.\n");
            return;
        }
       
        
        gg->currentLine = gg->firstLine;

        t = 100;

        while(gg->currentLine != NULL)
        {
            if(gg->currentLine->nextNode == NULL)
            {
                break;
            }

            if(t < 1000)
            {
                fprintf(fp, "0%d ", t);
            }

            else
            {
                fprintf(fp, "%d ", t);
            }

            for(i = 0; i < 32; i+=8)
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

               sprintf(tempString, "%x", tempInt);

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


               
               tempInt = (int)strtol(tempString, NULL, 2);

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



        
        free(buffer2);
        free(buffer);

        res = 0;
        res2 = 0;

    }
    

    free(gg);
}
