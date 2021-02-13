/*
 * C program to Display the Function Names
 * defined in C Source File
 */

#include <types.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void check (char *c,int p1, int p2);
void display (char *c, int p1);


int main (int argc, char **argv)
{
    FILE *fp;
    char ch[100];
    char *pos1, *pos2, *pos3;

    printf("showfun:\n");

    fp = fopen(argv[1], "r");

    if (fp == NULL){
       printf("\nFile unable to open");
       return -1;
    }else{
       printf("\nFile Opened to display function names :\n");
    };


    while (TRUE){

        if ((fgets(ch, 100, fp)) != NULL)
        {
            if ((strstr(ch, "/*")) == NULL)
            {
                pos1 = strchr(ch, '(');          /* check opening brace */
                
                if (pos1)
                {
                    pos2 = strchr(ch,')');   /* check oclosing brace */
                    
                    if (pos2)
                    {
                        pos3 = strchr(ch,';');   /* check for semicolon */

                        if ((pos1 < pos2) && (pos3 == NULL) || (pos3 < pos1))
                        {
                            check (ch, pos1 - ch, pos2 - ch);
                        }else{ continue; }
                    }else{ continue; }
                }else{  continue; }
            }else{ continue; }
        }else{ break; }
    };

    fclose(fp);

    return 0;
}


/* To check if it is a function */

void check (char *c, int p1, int p2)
{
    int i, flag = 0, temp = p1;


    if ((c[p1 + 1] == ')'))
    {
         display(c, p1);  return;
    }

    for (i = p1 + 1; i < p2; i++)
    {
        if (c[i] != ' ') {  flag = 1; }
        if (c[i] == ')') {  flag = 1; }
        
        if (flag == 0){  display(c, p1);  return;  }

        flag = 0;

        while (c[--temp] != ' '){  };

        for (i = 0; i < temp; i++)
        {
            if (c[i]==' '){  flag = 1;  }
        };

        if (flag == 0){  display(c, p1);  return;  } 
        
        return; 
    };
}


/* To display function name */
void display (char *c, int p1)
{
    int temp = p1, i;

    while (c[--temp] != ' '){  };

    /* Print name of function character by character */
    for (i = temp + 1; i < p1; i++)
    {
        printf ("%c", c[i]);
    };

    printf("\n");
    return;
}

