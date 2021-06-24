

#include <kernel.h>    

extern void asm_reboot (void);



void hal_set_machine_type ( unsigned long type )
{
    g_machine_type = (unsigned long) type;
}

unsigned long hal_get_machine_type (void)
{
    return (unsigned long) g_machine_type;
}



/*
 * hal_reboot:
 *     O hal é a camada mis próxima do hardware, não há tratamento nenhum
 * para fazer, somente chamar o reboot via teclado. 
 * em headlib.s 
 */

void hal_reboot(void)
{
    debug_print("hal_reboot:\n");

    asm_reboot(); 
    x_panic ("hal_reboot:\n");
}    

/*
 ********************************
 * hal_shutdown: 
 *     Interface usada pelos outros módulos
 *     #todo: Todos os possiveis métodos ficarão nessa rotina.
 *     máquina real e máquina virtual.
 *     #importante: Essa será a única função em hal para chamar shutdown.
 * quanquer outra interfce deve ficar fora do módulo hal.
 
 APM:
 ===
 This is the basic sequence of APM commands that must be given in 
 order to shut down a computer.
 +Perform an installation check.
 +Disconnect any existing APM interface.
 +Connect the Real Mode interface.
 +Enable power management for all devices.
 +Set the power state for all devices to "Off" (03h).
 
 ACPI:
 ====
  The ACPI shutdown is technically a really simple thing all 
  that is needed is a 
  
  outw(PM1a_CNT, SLP_TYPa | SLP_EN ); 
 
 and the computer is powered off. 
 
 The problem lies in the gathering of these values 
 especialy since the SLP_TYPa is in the \_S5 object 
 which is in the DSDT and therefore AML encoded.
 
 */

void hal_shutdown (void){

    const char *shutdown_str;

    debug_print ("hal_shutdown:\n");

    /*
    if (qemu____){
        //Bochs/QEMU poweroff
        shutdown_str = "Shutdown";
        while (*shutdown_str) out8 (0x8900, *(shutdown_str++));
    }
    */

    x_panic ("hal_shutdown");
}

// Monitor vertical sync.
void hal_vsync (void)
{
    // See: vsync.c
    vsync();
}


/*
 * Beep support
 * #bugbug: 
 * Não quero comprometer a programação do PIT. 
 */

/*
void ____Beep_tone (int freq){

    if (freq == 0) {
        int i = io_in8(0x61);
        io_out8(0x61, i & 0x0d);
    
    } else {
        int i = 1193180000 / freq;
        io_out8(0x43, 0xb6);
        io_out8(0x42, i & 0xff);
        io_out8(0x42, i >> 8);
        i = io_in8(0x61);
        io_out8(0x61, (i | 0x03) & 0x0f);
    }
}
*/ 



// Speaker ON. 
// OUT 
// Play sound using built in speaker

void hal_speaker_on (void){

    uint8_t tmp=0;

    //And play the sound using the PC speaker

    tmp = in8 (0x61);

    if (tmp != (tmp | 3))
    {
        out8 (0x61, tmp | 3);
    }
}


// Speaker OFF
// IN
// make it shutup
void hal_speaker_off (void)
{
    uint8_t tmp = in8(0x61) & 0xFC;

    out8 (0x61, tmp);
}
 

// Beep.
void hal_test_speaker (void){

    int i=0;

    debug_print ("Testing speaker ...\n");

    //++
    hal_speaker_on ();
    
    for( i=0; i<49000; i++)
    {
        // Nothing
    }

    hal_speaker_off ();
    //--
} 




/*
 ********************************************************
 * init_hal:
 * Initialize kernel base hal.
 *     Archtecture independent inicialization ...
 */

// Called by ?

int init_hal (void)
{
    int Status = 0;

    //Initialization.hal = FALSE;


    //init_cpu();

    
    // #todo:
    // Chamaremos essa inicialização básica nesse momento.
    // A inicialização completa será chamada pelo processo init.
    
    //early_timer_init ();
    
    
	// Detecta fabricantes específicos suportados pelo núcleo.  

    //hal_hardware_detect();

    //Initialization.hal = TRUE;

    return 0;
}





















