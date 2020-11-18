// 'cat' command for Gramado.

// rtl
#include <rtl/gramado.h>
#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>


int main ( int argc, char *argv[] ){

	FILE *fp;
	register int c=0;
	char buffer[1024];
	int nreads = 0;
	int nwrites = 0;

	fp = fopen ( (char *) argv[1], "r+" );
	if ( (void *) fp == NULL ){
		printf ("cat: fopen fail\n");
		//perror ("cat: fopen fail  ... testing perror\n");
		exit (-1);
	}

	nreads = read( fileno(fp), buffer, sizeof(buffer) );
	if ( nreads <= 0 ){
		printf ("cat: read fail\n");
		exit (-1);
	}

	// Get file size.
	fseek (fp, 0, SEEK_END);
	size_t size = ftell (fp);
	fseek (fp, 0, SEEK_SET);
	printf (">> size %d \n",size);

	// Write.
	nwrites = write ( 1, buffer, sizeof(buffer) );
	if ( nwrites <= 0 ){
		printf ("cat: write fail\n");
		exit(-1);
	}

	return 0;
}


