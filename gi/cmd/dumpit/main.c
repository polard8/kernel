


#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dumpit.h"



/* help function if parameters not ok */
void usage()
{
	printf ("usage:\n"); 
	//fprintf (stderr, "usage: dumpit file1 file2 ...\n");
	//fprintf (stderr, "\n");
	exit (1);
}


/*parses arguments*/
void handle_args (int num_args, char **args){
	
	int i;
	int isP = 0;
	FILE *f;

	if (num_args < 2)
	{
        usage ();
    }


	/*look for -p and -o command-line switches first*/

    printf ("handle_args: Step1\n"); 
	for (i=1; i<num_args; ++i)
	{
		if (args[i][0] == '-' && args[i][1] == 'p')  
		    ++isP;

		if (args[i][0] == '-' && args[i][1] == 'o')
		{
			if ( 0 == isprint(args[i][2]) ) usage();
			else{
				
				/*create filename from remaining characters*/
				char fname[256];
				/*null-terminate the fname array to prevent filenaming errors*/
				int j;
				for(j=0; j<256; ++j) fname[j] = 0;
				int k = 0;
				for(j=2; j<strlen(args[i]); ++j)
				{
					fname[k] = args[i][j];
					++k;
				}
				
				printf ("handle_args: FileName={%s}\n",fname);
				
				/*create file object*/
				f = fopen (fname, "wb");				
				
				/*parse all files*/
				for (i=1; i<num_args; ++i)
				{
					if (args[i][0] != '-')
					{
						dumpfile (args[i], 1, f);
					}
				}
				printf ("handle_args: fclose\n");
				fclose(f);
			}
			
			printf ("handle_args: return\n"); 
			return; /*prevents the -p option from doing evil*/
		}
		/*fail if invalid command switch*/
		if(args[i][0] == '-' && (args[i][1] != 'p' && args[i][1] != 'o')) usage();
	}


    printf ("handle_args: Step2\n"); 
	for(i=1; i<num_args; ++i)
	{
		if(args[i][0] != '-')
		{
			dumpfile(args[i], 0, NULL);
			if (isP && i < num_args-1)
			{
				printf ("Press enter to continue\n");
				getc (stdin);
			}		
		}
	}

}


/*
 * main:
 */
 
int main ( int argc, char **argv ){
	
	printf ("DUMPIT: Initializing ...\n");
	
	handle_args (argc, argv);
	
	printf ("DUMPIT: done\n");
	exit (0);
}


