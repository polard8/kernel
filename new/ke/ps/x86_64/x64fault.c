
#include <kernel.h>


unsigned long xxx_fault_number;

void faults ( unsigned long number )
{

    debug_print ("~faults:\n");


    // #debug

    // number = 9;  //test de switch
    // #debug: Isso é so um teste.
    // o assembly vai inpurtar essa variável.
    // number = xxx_fault_number;

     // #bugbug
     // ??
     // Quando podemos usar panic() ??
     // x_panic pode ser usado antes de panic() ?

    // provisório
    switch ( number ){

        // Divisão por zero, ou resultado muito longo?
        // Se a falta ocoreu em ring 0, então precisamos
        // encerrar o sistema, mas se a falta aconteceu em ring3,
        // podemos simplesmente fechar o aplicativo.
        case 0: 
            x_panic("faults() 0"); 
            break;
        
        case 1: x_panic("faults() 1"); break;
        case 2: x_panic("faults() 2"); break;


        case 3: 
            //printf ("== 3 ==\n");  
            //show_slots();
            //refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            
            x_panic("faults() 3"); 
            
            break;


        
        case 4: x_panic("faults() 4"); break;
        case 5: x_panic("faults() 5"); break;
        case 6: x_panic("faults() 6"); break;
        case 7: x_panic("faults() 7"); break;
        case 8: x_panic("faults() 8"); break;
        case 9: x_panic("faults() 9"); break;
        case 10: x_panic("faults() 10"); break;
        case 11: x_panic("faults() 11"); break;
        case 12: x_panic("faults() 12"); break;


        //General Protection Fault
        case 13: 
            printf ("== GP ==\n");  
            //show_slots();
            refresh_screen();
            // Esse tipo funciona mesmo antes do console
            // ter sido inicializado.
            x_panic("faults() 13"); 
            break;
        
        //Page Fault
        case 14: 
            printf ("== PF ==\n");  
            show_slots();
            refresh_screen();
            x_panic("faults() 14"); 
            break;
        
        case 15: x_panic("faults() 15"); break;
        case 16: x_panic("faults() 16"); break;
        case 17: x_panic("faults() 17"); break;
        case 18: x_panic("faults() 18"); break;
        case 19: x_panic("faults() 19"); break;
        case 20: x_panic("faults() 20"); break;
        case 21: x_panic("faults() 21"); break;
        case 22: x_panic("faults() 22"); break;
        case 23: x_panic("faults() 23"); break;
        case 24: x_panic("faults() 24"); break;
        case 25: x_panic("faults() 25"); break;
        case 26: x_panic("faults() 26"); break;
        case 27: x_panic("faults() 27"); break;
        case 28: x_panic("faults() 28"); break;
        case 29: x_panic("faults() 29"); break;
        case 30: x_panic("faults() 30"); break;
        case 31: x_panic("faults() 31"); break;

        default:
            x_panic("faults() default"); 
            break;
    };
    
    x_panic("faults() fail");
}



