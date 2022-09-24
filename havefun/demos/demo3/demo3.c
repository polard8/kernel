

#include "../../eng3/gws.h"

char *args[] = { "nothing", NULL };


// include inside the engine.
void gr_setup(void)
{
    //printf("gr_setup:\n");
    __setupCatModel(TRUE,TRUE,TRUE);
}

// include inside the engine.
void gr_draw(void)
{
    //printf("gr_draw:\n");
    demoCat();
}

int main(int argc, char **argv)
{
    // chama o main() da engine
    //eng1_main();
    
    printf("DEMO3.BIN: Initializing ...\n");
    eng3_main(1,args);
    
    return 0;
}



