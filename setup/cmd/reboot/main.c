// 'reboot' command for Gramado.

// rtl
#include <rtl/gramado.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main ( int argc, char *argv[] ){

	int code=0;
	char *env_string;

	puts ("\n");
	printf ("reboot\n");

	env_string = (char *) getenv ("USER");
	printf (">>> Bye %s! :) \n", env_string);

	rtl_reboot();

	return -1;
}



