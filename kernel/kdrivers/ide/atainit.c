

#include <kernel.h>



/*
 *******************************************
 * diskATADialog:
 *     Rotina de diálogo com o driver ATA. */

int 
diskATADialog ( int msg, 
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
		    diskATAInitialize ( (int) long1 );
		    Status = 0;
			return (int) Status;	
			break;
			
		//ATAMSG_REGISTER
        //registra o driver. 		
		//case 2:
		//    break;
			
		default:
		    printf ("diskATADialog: fail\n");
			break;
	};

    return (int) Status;	
}

