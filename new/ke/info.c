
#include <kernel.h>


// ================================================
// The data comes from boot block and beyond.

// #test
// Lets use the info that omes from the BootBlock structure.
// This structure was initialized for kernel_main() in main.c

unsigned long info_get_boot_info ( int i )
{

    if (i<0){  return 0;  }

    switch (i){

        // #bugbug
        // If we use the BootBlock structure, maybe the info
        // will be accessible only using the sci2. int 0x82.

        case 1:
           return (unsigned long) BootBlock.last_valid_address;
           break;

        case 2:
           return (unsigned long) BootBlock.metafile_address;
           break;

        case 3:
           return (unsigned long) BootBlock.disk_number;
           break;

        case 4:
           return (unsigned long) BootBlock.heads;
           break;

        case 5:
           return (unsigned long) BootBlock.spt;
           break;

        case 6:
           return (unsigned long) BootBlock.cylinders;
           break;

        case 7:
           //return (unsigned long) 
           break;

        case 9:
           //return (unsigned long) 
           break;
    };
    
   //fail 
   return 0;
}


