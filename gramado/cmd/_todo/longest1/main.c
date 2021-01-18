/*
 * longest1 - Um aplicativo de teste para o sistema operacional Gramado.
 * 2018 - Fred Nora.
 */


#include <types.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 32


int getlinelength( char *s );
void copy(char *to, char *from);



/*
 *******************************************
 *  ## MAIN ##
 */
int app_test()
{
    int i;
	int len, max = 0;
    char line[MAXLINE], longest[MAXLINE];
  
    sprintf(line, "Initializing\n" );
    sprintf(longest, "Initializing LONGEST1.BIN ...\n" );
	

    libcInitRT();
    stdioInitialize();		
	
	
	for( i=0; i<4; i++ )
    {
		len = (int) getlinelength( (char*) line );  
		
		//só copia se for maior.
        if(len > max)
	    {
            max = len;
            copy( (char*) longest, (char*) line);
        }
    };
	
	
    if( max > 0 ){
        printf("longest: %s\n", longest);
    };

done:
    printf("LONGEST1.BIN: done.\n");
    
	while(1){
        asm("pause");
    };		
    return 0;
};


//pega quantidade de chars.
int getlinelength( char *s )
{
    int ch;
    int i;
  
    printf("\n");
    printf("getlinelength:\n");  

	while(1)
	{
	    ch = (int) getchar();
	    if(ch != -1)
	    {
	        printf("%c",ch);
	    
	        switch(ch)
            {
			   //quit
			    case 'q':
			    case '\n':
			       goto done;
				   break;
				   
				default:
				    //page fault por escrita em lugar inválido.
                    s[i] = (char) ch;
                    i++;	
		    };		   
		};
		asm("pause");
	};

done:  	
    if(ch == '\n')
	{
        s[i] = ch;
        ++i;
    }

    s[i] = '\0';

    return (int) i;
};

void copy(char *to, char *from)
{
    int i;

    //printf("copy:\n");
	
    i = 0;

    while( (to[i] = from[i]) != '\0' )
	{
        ++i;
    };
};

/*
// do a getc, but give error message if EOF encountered 
int safegetc(f)
    FILE *f;
{
    register int c = getc(f);
    if (c == EOF)
        fatal("Unexpected end of file");
    return c;
}
*/


