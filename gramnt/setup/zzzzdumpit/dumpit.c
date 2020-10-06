

// rtl
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>




/* 16 chars per line in dump */
#define BUFLEN 16


void dumpfile (const char * fname, int mode, FILE *path)
{
	int i,numread=BUFLEN;
	unsigned char buf[BUFLEN];    
	FILE * fd = fopen(fname, "rb");
	FILE * OUTPUT = mode ? path : stdout;

	if(NULL == fd)
	{
		printf ("dumpfile: fd\n");
		fprintf (stderr, "Unable to open file %s\n\n", fname);
		return;
	}

    /* print the line w/ the filename */
	fprintf(OUTPUT,"%s\n", fname);   
	
	for(i=0; i<64; i++ )            /* dividing line */
		fprintf(OUTPUT,"-");
	fprintf(OUTPUT,"\n");
        
	while( numread == BUFLEN )     /* while there is unread input in file*/
	{
		for(i = 0; i < BUFLEN; ++i)
		{
			/* clean the buf array with terminators... */
			buf[i] = 0;
		}
		numread = fread ( buf, sizeof(char), BUFLEN, fd);  /* read 16 bytes */
		int cursor = 0;

		for( i=0; i < BUFLEN; ++i )
		{	
			fprintf (OUTPUT,"%02x ",  buf[i]);
		}

		for( i=0; i < BUFLEN; ++i )
		{
			isprint ( buf[i]) ?  fprintf(OUTPUT,"%c", buf[i]) : fprintf(OUTPUT,"." );
		}

		fprintf(OUTPUT,"\n");
	}
	fclose(fd);
	fprintf(OUTPUT,"\n");
	
	//
	// Show OUTPUT file.
	//
	
	//#test
	int c;
	while ( (c = fgetc(OUTPUT)) >= 0 )
		printf ("%c", c);		
	
}
