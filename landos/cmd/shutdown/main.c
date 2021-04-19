// 'reboot' command for Gramado.

// rtl
#include <rtl/gramado.h>
#include <stddef.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// libio
#include <libio.h>


// isso eh uma rotina de test
// Vai escrever em uma porta ja inicializada pelo kernel.
void serial_write_char (char data) 
{
    while (( libio_inport8(0x3F8 + 5) & 0x20 ) == 0);

    libio_outport8 (0x3F8, data);
}


//
// main
//

    // #test
    // Testing shutdown in virtual machines.
    // #todo:
    // We can ask the system if we are in qemu or not.
    // See: https://wiki.osdev.org/Shutdown

int main ( int argc, char *argv[] )
{

    // Na verdade essa rotina precisa ser em ring0.
    // Pois tem que checar a permissão de superuser,
    // acionar os locks, sincronizar os sistemas de arquivo
    // montados, etc ...


    int isQEMU       = FALSE;
    //int isVirtualBox = FALSE;
    //int isBochs      = FALSE;
    
    isQEMU       = rtl_get_system_metrics(300);
    //isVirtualBox = rtl_get_system_metrics(?);
    //isBochs      = rtl_get_system_metrics(?);





    // qemu
    // In newer versions of QEMU, you can do shutdown with:
    if (isQEMU == TRUE){
        //serial_write_char('1');
        //serial_write_char('2');
        //serial_write_char('3');
        //serial_write_char(' ');
        debug_print ("SHUTDOWN.BIN: [QEMU] Shutting down \n");
        libio_outport16 (0x604, 0x2000);
    }


    // virtualbox
    // In Virtualbox, you can do shutdown with:
    //if (isVirtualBox == TRUE){
    //    libio_outport16(0x4004, 0x3400);
    //}

    // bochs
    // In Bochs, and older versions of QEMU(than 2.0), you can do the following:
    //if (isBochs == TRUE){
    //    libio_outport16(0xB004, 0x2000);
    //}


fail:
    printf ("shutdown: [FAIL] Not running on qemu.\n");
    exit(0);



    return (int) (-1);
}


