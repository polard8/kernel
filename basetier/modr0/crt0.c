
// crt0 file for a ring 0 kernel module.

extern int module_main( int reason );

void module_crt0(void)
{
    int ret_val=0;
    int reason=0;

    //IN: reason
    ret_val = 
        (int) module_main(reason);


    while(1){
    };
}



