

#include <kernel.h>  


/*
 *******************************************
 * ataDialog:
 *     Rotina de diálogo com o driver ATA. 
 */

int 
ataDialog ( 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    int Status = 1;    //Error.


    switch (msg)
    {
		//ATAMSG_INITIALIZE
		//Initialize driver.
		//ata.c

        case 1:
            debug_print ("ataDialog: Initialize ata\n");
            ata_initialize ( (int) long1 );
            Status = 0;
            return (int) Status;
            break;

		//ATAMSG_REGISTER
		//registra o driver. 
		//case 2:
		//    break;

        default:
            debug_print ("ataDialog: default\n");
            printf      ("ataDialog: default\n");
            break;
    };


    return (int) Status;
}



