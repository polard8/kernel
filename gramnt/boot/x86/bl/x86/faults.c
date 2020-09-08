/*
 * File: faults.c 
 *
 * Description: 
 *     Rotinas de tratamento de faults e exception para o Boot Loader em 
 * sistema 32bit para desktop.
 * Obs: Essa rotina pertence ao Boot Loader, que está em ring 0.
 *
 * Versão: 1.0, 2015.
 */
 
 
#include <bootloader.h>


void faultsShowRegisters ();






/*
 **************************************************
 * cpu_faults:
 *     Tratamento de faults do Boot Loader.
 *     Trata a fault de acordo com o número.
 * Obs: Isso pertence ao Boot Loader. Não há threads para serem fechadas.
 * @todo: Exibir as falhas de inicialização.
 *
 * 2015 - Created.
 */

void cpu_faults (unsigned long fault_number){
	
    g_cursor_x = 0;
	g_cursor_y = 0;
	
	printf("faults-cpu_faults: %d\n", fault_number );
	
	
	//se estamos testando a memória.
    if ( ____testing_memory_size_flag == 1 )
    {
		// global. See: gdef.h
        printf ("cpu_faults: Testing memory size\n");
        printf ("cpu_faults: Out of range with exception %d\n", fault_number );
        printf ("cpu_faults: address = %x \n", __last_valid_address);
        refresh_screen();
            while(1)
            {
                asm ("cli");
                asm ("hlt");
            }
    }


	// Mostra o erro de acordo com o número.
	
    switch (fault_number)
	{
	    //EXCEPTION
		case 1:
		case 3:
		    printf ("EXCEPTION \n");
			break;
		
		//DOUBLE FAULT
	    case 8:
			printf ("DOUBLE FAULT \n");
		    break;

	    //STACK
	    case 12:
			printf ("STACK FAULT \n");
		    break;

	    //GP
	    case 13:
		    printf ("GP \n");
		    break;
		
		//PAGE FAULT
	    case 14:
		    printf ("PAGE FAULT \n");
		    break;
	    
	    default:
			printf ("Default number\n");
			break;
	};
	
	// More ?! 
	// Tratamento, informações.


//done:

    faultsShowRegisters ();
    die ();

	//
	//  No return.
	//

}


void faultsShowRegisters ()
{
    //#todo
}




//
// End.
//
