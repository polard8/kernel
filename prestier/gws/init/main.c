

// init process

int main( int argc, char **argv)
{
    //#todo
    //printf()

//
// Interrupts
//

// The taskswithing will not work without this.

    asm ("int $199 \n");


// interrupts
// Unlock the taskswitching support.
// Unlock the scheduler embedded into the base kernel.
// Only the init process is able to do this.

    //gws_debug_print ("gws.bin: Unlock taskswitching and scheduler \n");
    //printf          ("gws.bin: Unlock taskswitching and scheduler \n");
    gramado_system_call (641,0,0,0);
    gramado_system_call (643,0,0,0);


    printf("Init process: press [control + f9] to open the console\n");

    while(1){}
    return 0;
}

