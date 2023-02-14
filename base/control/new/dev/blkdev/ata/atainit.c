
// atainit.c
// 2021 - Created by Fred Nora.

#include <kernel.h>  

// ataDialog:
// Rotina de diálogo com o driver ATA. 
// Called by init_executive() in system.c
// #importante
// Nessa hora ja temos as estruturas de disk e volume inicializadas.
// entao as estruturas usadas pelo driver ata, pode
// se registrar em disk ou volume.
// msg:
// 1 = Initialize the driver.
// 2 = Register the driver.
// ...

// IN: ???
int 
ataDialog ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
// Do some ata routine given the operation number.

    int Status = 1;  // Error.

    debug_print ("ataDialog:\n");

    switch (msg)
    {

        // ATAMSG_INITIALIZE
        // Initialize driver.
        // ata.c
        case 1:
            debug_print("ataDialog: Initialize ata support\n");
            // IN: ?? forcepio.
            Status = (int) ata_initialize( (int) long1 );
            // We can't live without this at the moment.
            if(Status<0){
                panic("ataDialog: ata_initialize failed\n");
            }
            return (int) Status;
            break;

        //ATAMSG_REGISTER
        //registra o driver. 
        //case 2:
        //    break;

        default:
            panic("ataDialog: Unsupported service.\n");
            break;
    };

    return (int) Status;
}

