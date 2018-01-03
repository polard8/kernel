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


/*
 * cpu_falts:
 *     Tratamento de faults do Boot Loader.
 *     Trata a fault de acordo com o número.
 * Obs: Isso pertence ao Boot Loader. Não há threads para serem fechadas.
 * @todo: Exibir as falhas de inicialização.
 * 2015 - Created.
 */
void cpu_falts(unsigned long fault_number)
{	
	//Cursor.	
    g_cursor_x = 0;
	g_cursor_y = 0;
	
	//Message.
	printf("CPU FAULT: Number=[%d]\n",fault_number);
	
	// Mostra o erro de acordo com o número.	 
    switch(fault_number)
	{
	    //EXCEPTION
		case 1:
		case 3:
		    printf("EXCEPTION \n");
			mostra_reg(current_task);
			break;
		
		//DOUBLE FAULT
	    case 8:
			printf("DOUBLE FAULT \n");
			mostra_reg(current_task);
		    break;

	    //STACK
	    case 12:
			printf("STACK FAULT \n");
			mostra_reg(current_task);
		    break;

	    //GP
	    case 13:
		    printf("GP \n");
			mostra_reg(current_task);
		    break;
		
		//PAGE FAULT
	    case 14:
		    printf("PAGE FAULT \n");
			mostra_reg(current_task);
		    break;
	    
	    default:			
			printf("Default number.\n");
            mostra_reg(current_task);			
			break;
	};
	
	//
	// More ?! Tratamento, informações.
	//
  
//
// Done. " ... e então o veremos face à face ... "
//

done:
    die();
	
    // Final message !
    //printf("* System Halted!\n");    // Bullet, Message.
	
	//refresh_screen();
	//asm("hlt");                      // Halt system.
    //while(1){};                      // Wait forever.  
    
	//
    //  No return.
    //	     
};



/*
 * mostra_reg:
 *     Mostra os valores dos registradores.
 * @todo: Isso deve ir para outro arquivo. ???!!!
 *        Se ficar aqui. mudar o nome para faultShowRegisters();.
 */
//void faultShowRegisters(int tid) ??

void mostra_reg(unsigned long id){
	return;    //suspensa. 
};

//
// End.
//
