
// main file for the ring 0 kernel module.
// called by ./crt0.c


int module_main( int reason )
{

    if(reason==1)
        return 0;

    while(1){
    };

    return 0;
}



