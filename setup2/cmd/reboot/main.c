// 'reboot' command for Gramado.

// rtl
#include <rtl/gramado.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <libio.h>


//isso eh uma rotina de test
//vai escrever em uma porta ja inicializada pelo kernel.
void serial_write_char (char data) 
{
    while (( libio_inport8(0x3F8 + 5) & 0x20 ) == 0);

    libio_outport8 (0x3F8, data);
}


int main ( int argc, char *argv[] ){

    char *env_string;

    puts ("\n");
    printf ("reboot\n");

    // Getting the user name.
    env_string = (char *) getenv ("USER");

    // Showing the user name.
    printf (">>> Bye %s! :) \n", env_string);


    //testing serial port
    //ok isso funcionou.
    serial_write_char('x');
    serial_write_char('y');
    serial_write_char('z');
    serial_write_char(' ');


    // reboot via rtl
    // printf ("reboot via rtl\n");
    // rtl_reboot();

 
    // reboot via libio.
    printf ("reboot via libio\n");
    unsigned char good = 0x02;
    while (good & 0x02)
    {
        good = libio_inport8(0x64);
    }

    debug_print("reboot.bin: Go!\n");
         printf("reboot.bin: Go!\n");
    
    libio_outport8(0x64, 0xFE);
    //halt();       
     
     
    debug_print("reboot.bin: fail\n");
         printf("reboot.bin: fail\n");
    
    return (int) (-1);
}


