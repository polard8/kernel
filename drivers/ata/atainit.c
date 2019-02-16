

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
		case 1:
		    diskATAInitialize ( (int) long1 );
		    Status = 0;
			goto done;
			break;
			
		//ATAMSG_REGISTER
        //registra o driver. 		
		//case 2:
		//    break;
			
		default:
		    goto fail;
			break;
	};

//
// Done:
//	
fail:
    printf("diskATADialog: fail\n");
done:
    return (int) Status;	
};


