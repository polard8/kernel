

#include <kernel.h>

// rotinas para atender as syscalls desse grupo



// Helper function to initialize system's component
// after kernel initialization.
int syssm_initialize_component( int n )
{

    if(n<0)
        return -1;


    switch(n)
    {
        case 1:
            ps2();
            break;

        //case 2:
            //break;

        //case 3:
            //break;

        //case 4:
            //break;


        // ...
        

        default:
            return -1;
            break;
    };
    
    return (int) 0;
}


// 250
unsigned long syssm_get_system_metrics ( int n )
{
    return (unsigned long) systemGetSystemMetrics ( (int) n );
}
