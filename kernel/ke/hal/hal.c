

#include <kernel.h>    


//
// import
//

//extern unsigned long gdt;
//extern unsigned long idt;
//extern unsigned long tss;


extern void asm_reboot (void);


/*
// Called by the idle handler for up.
void hal_up_idle(void);
void hal_up_idle(void)
{
    asm ("sti");
    asm ("hlt");
    return;
}
*/


/*
// Called by the idle handler for mp.
void hal_mp_idle(void);
void hal_mp_idle(void)
{
    asm ("sti");
    return;
}
*/




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

    switch (system_state ){

    // Normal situations
    case SYSTEM_BOOTING:
    case SYSTEM_REBOOT:
        debug_print("...\n");
        break;
    default:
        debug_print("Booting on an unexpected situation\n");
        break;
    };

    debug_print("Calling asm_reboot\n");
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


    // Something is wrong.
    if ( system_state != SYSTEM_POWEROFF )
        panic ("hal_shutdown: system_state\n");

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

// Called by init() in init.c

int init_hal (void)
{
    int Status = 0;

    Initialization.hal = FALSE;

    // nothing
    init_cpu();

    // #todo:
    // Chamaremos essa inicialização básica nesse momento.
    // A inicialização completa será chamada pelo processo init.
    
    early_timer_init();
    
    
	// Detecta fabricantes específicos suportados pelo núcleo.  

    // nothing
    hal_hardware_detect();

    Initialization.hal = TRUE;

    return 0;
}

/*
 * hal_hardware_detect:
 *     Detecta fabricantes específicos suportados pelo núcleo.
 *
 * 8086, 1237  //PCI & Memory.
 * 8086, 7000  //PIIX3 PCI-to-ISA Bridge (Triton II).
 * 1022, 2000  //Advanced Micro Devices, PCnet LANCE PCI Ethernet Controller.
 * 8086, 7113  //PIIX4/4E/4M Power Management Controller.
 * 8086, 2829  //Intel(R) ICH8M SATA AHCI Controller.
 * //...
 *
 */

// Consumer Chipsets (Z87, H87, H81) Haswell LGA1150. 
// Business Chipsets (Q87, Q85, B85) Haswell LGA1150.

int hal_hardware_detect (void)
{
    debug_print ("hal_hardware_detect: [TODO]\n");
    return 0;    //#todo
}

/*
 * init_cpu:
 *     Inicializa a estrutura do processador e as coisas associadas a ele.
 *     Inicializa apenas o que for independente da arquitetura.
 *     @todo: Essa rotina pode ir para outro modulo do /hal. como cpu.c
 */

// #todo 
// O retorno deve ser int, para refletir o status.
    
void init_cpu (void)
{
    debug_print("init_cpu: deprecated\n");
    // See:
    // init() on init.c
    // hal_probe_processor_type() on detect.c
}



























