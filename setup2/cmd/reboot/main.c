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

    char *env_string;

    puts ("\n");
    printf ("reboot\n");

    // Getting the user name.
    env_string = (char *) getenv ("USER");

    // Showing the user name.
    printf (">>> Bye %s! :) \n", env_string);

    // reboot.
    rtl_reboot();

    printf("reboot.bin: Fail\n");
    return (int) (-1);
}


