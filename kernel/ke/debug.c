
// debug.c

#include <kernel.h>


extern unsigned long InitializationPhase;


// debug_compute_checksum: 
// retorna um checksum dado um buffer e um tamanho.

unsigned long 
debug_compute_checksum ( 
    unsigned char *buffer, 
    unsigned long lenght )
{
    unsigned long CheckSum = 0;


    while (lenght > 0){
        CheckSum = ( CheckSum + (unsigned long) *buffer++ );
        lenght--;
    };

    return (unsigned long) CheckSum;
}


void debug_print ( char *data )
{
    register int i=0;

    if ( (void *) data == NULL ){ return; }
    if (*data == 0)             { return; }

    for ( i=0; data[i] != '\0'; i++ )
    {
        serial_write_char ( COM1_PORT, data[i] );
    };
}


// We will use this function to track 
// the main kernel initialization progress.
// It will print into the serial port for now.

void PROGRESS( char *string )
{
    if( (void*) string == NULL ){
        return;
    }

    if(*string == 0){
        return;
    }

    // #todo
    // Select the available method.
    // switch(...

    debug_print("\n");
    debug_print(string);
}


// debug_check_inicialization:
//     Checar se o kernel e os módulos foram inicializados.
//     Checa o valor das flags.
//     Checar todos contextos de tarefas válidas.

// #todo
// Rever esses nomes e etapas.

int debug_check_inicialization (void){

    int Status = 0;

    // Check phase.

    if ( InitializationPhase != 3 ){
       Status = 1;
       printf ("debug_check_inicialization: InitializationPhase = {%d}\n",
           InitializationPhase );
       goto fail;
    }


    // Executive.
    if ( Initialization.executive != 1 ){
        Status = 1;
        printf ("debug_check_inicialization: executive\n");
        goto fail;
    }


    // Microkernel.
    if ( Initialization.microkernel != 1 ){
       Status = 1;
       printf ("debug_check_inicialization: microkernel\n");
       goto fail;
    }


    // Hal.
    if ( Initialization.hal != 1 ){
        Status = 1;
        printf ("debug_check_inicialization: hal\n");
        goto fail;
    }

    // More?!

//done:
    return (int) Status;
fail:
    die(); 
    return -1;
}

/*
 * debug_check_drivers:
 *    Checar se os drivers estão inicializados.
 */
 
int debug_check_drivers (void)
{
    int Status = 0;


    // #todo
    // This routine is very cool.

    debug_print("debug_check_drivers: TODO\n");

    /*
     
	if (g_driver_ps2keyboard_initialized != 1){
	    //erro
	}

	if (g_driver_ps2mouse_initialized != 1){
	    //erro
	}


	if (g_driver_hdd_initialized != 1){
	    //erro
	}

    if (g_driver_pci_initialized != 1){
	    //erro
	}
	
    if (g_driver_rtc_initialized != 1){
	    //erro
	}
	
    if (g_driver_timer_initialized != 1){
	    //erro
	}

    */

    return (int) Status;
}


/*
 ****************************************
 * debug:
 *     Checa por falhas depois de cumpridas as 
 *     três fases de inicialização.
 */

// #bugbug
// Será que o output está realmente disponível nesse momento ?!

int debug (void){

    int Status = -1; 

    // Checa inicialização. 
    // Fases, variáveis e estruturas.

    Status = (int) debug_check_inicialization();

    if (Status == 1){
        panic ("debug: debug_check_inicialization fail\n");
    }

    // 'processor' struct.

    if ( (void *) processor == NULL ){
        panic ("debug: processor struct fail\n");
    }

    // Check drivers status. 
    // ( Ver se os principais drivers estão inicializados )

    debug_check_drivers();

	/*
	 * @todo: 
	 *     Checar se existe componentes do sistema como mbr, root, fat 
	 * e arquivos e programas básicos do sistema.
	 */
	 
	 
	/* 
	 * @todo: 
	 *     Checar por falhas no sistema de arquivos.
	 */
	 
	 
	/*
     * @todo:	
	 *     Checar por falhas nas estruturas de tarefas.
	 */

	//...


    // printf ("debug: Done.\n");

    return 0; 
}

// debug_breakpoint:
//     Para a execução do sistema.
//     @todo: isso pode ir para o arquivo debug.c.

void debug_breakpoint (void)
{
    printf ("debug_breakpoint:\n");
    die();
}


/*
void 
bug_check( 
    int number, 
    unsigned long parameter1,
    unsigned long parameter2,
    unsigned long parameter3,
    unsigned long parameter4 )
{
    switch (number){
    case 1:
       
    };

    if( WeHavePanic == TRUE ){
        panic("bug_check: panic\n");
    }

    if( WeHaveXPanic == TRUE ){
        panic("bug_check: xpanic\n");
    }

    // We have nothing.
    while(1){
        asm (" cli ");
        asm (" hlt ");
    };
}
*/



