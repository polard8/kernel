/*
 * Gramado HAL - The main file for the hal module in the kernel base. 
 * (c) Copyright 2015-2016 Fred Nora.
 *
 *  File: hal/hal.c 
 *
 *      HAL - Hardware Abstraction Layer
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     //...
 */
 
 
#include <kernel.h>
//#include "hidata.h"  //Hal Internal Data.

//unsigned char  HalName[] = "HAL LAYER";

//
// inport.
//

extern unsigned long gdt;
extern unsigned long idt;
//extern unsigned long tss;


extern void gui_buffer_putpixel (void);
extern void swlib_backbuffer_putpixel (void);
extern void swlib_lfb_putpixel (void);
extern void asm_reboot (void);

//
// ## IDT SUPPORT ##
//


// 256 interrupções
// 8 extras para handlers default.
//unsigned long HANDLERS[256+8];


//Esse handler será instalando em todas as entradas
//da tabela antes da configuração.

void hal_default_handler (void)
{
    //return;
}


void hal_init_handlers_table (void)
{
    int i=0;
	int max = (256+8);
	
	for ( i=0; i<max; i++ )
	{
	    HANDLERS[i] = (unsigned long) &hal_default_handler;
	}
}


void hal_setup_new_handler ( int number, unsigned long callback )
{
    HANDLERS[number] = (unsigned long) callback;    
}


void hal_invalidate_handler (int number)
{
    HANDLERS[number] = (unsigned long) 0;    
}


//
//  ## Interrupt vectors support ##
//

//Esses endereços foram configurados pelo assembler na inicialização.
//Vamos salvá los na tabela em seus respectivos slots.

extern unsigned long fault_N0;
extern unsigned long fault_N1;
extern unsigned long fault_N2;
extern unsigned long fault_N3;
extern unsigned long fault_N4;
extern unsigned long fault_N5;
extern unsigned long fault_INTRUCAO_INVALIDA;
extern unsigned long fault_N7;
extern unsigned long fault_DOUBLE;
extern unsigned long fault_N9;
extern unsigned long fault_N10;
extern unsigned long fault_N11;
extern unsigned long fault_STACK;
extern unsigned long fault_GP;
extern unsigned long fault_N14;
extern unsigned long fault_N15;
extern unsigned long fault_N16;
extern unsigned long fault_N17;
extern unsigned long fault_N18;
extern unsigned long fault_N19;
extern unsigned long fault_N20;
extern unsigned long fault_N21;
extern unsigned long fault_N22;
extern unsigned long fault_N23;
extern unsigned long fault_N24;
extern unsigned long fault_N25;
extern unsigned long fault_N26;
extern unsigned long fault_N27;
extern unsigned long fault_N28;
extern unsigned long fault_N29;
extern unsigned long fault_N30;
extern unsigned long fault_N31;


extern unsigned long timer_test;  //32
extern unsigned long irq1;
extern unsigned long irq8;
extern unsigned long irq12;
extern unsigned long irq14;
extern unsigned long irq15;
extern unsigned long int128;  // 0x80, system interrupt
extern unsigned long int213;
extern unsigned long int216;




void hal_setup_new_vectors_table_entry ( int number, unsigned long address )
{
    VECTORS[number] = (unsigned long) address;    
}


//Esses endereços foram configurados pelo assembler na inicialização.
//Vamos salvá los na tabela em seus respectivos slots.

void hal_init_vectors_table (void)
{
	
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N0 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N1 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N2 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N3 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N4 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N5 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_INTRUCAO_INVALIDA );	
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N7 );	
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_DOUBLE );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N9 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N10 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N11 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_STACK );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_GP );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N14 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N15 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N16 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N17 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N18 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N19 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N20 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N21 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N22 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N23 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N24 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N25 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N26 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N27 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N28 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N29 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N30 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &fault_N31 );
	
	
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &timer_test );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &irq1 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &irq8 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &irq12 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &irq14 );
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &irq15 );
	
	//interrupts
	
	//128 - 0x80 system interrupt
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &int128 );
	
	//213 - Executa nova tarefa.
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &int213 );
	
	//216 - fast create window.
	hal_setup_new_vectors_table_entry ( (int) 0, (unsigned long) &int216 );
	
	//...
}



 /* 
    Exemplo:
     checa alguns chipes especificos
 
    //...

		        // Procura por Am79C970, vendor 0x1022, device 0x2000.
                // 82371AB		
		        if( Vendor == 0x1022 &&    //AMD - (Advanced Micro Devices)   
		        Device == 0x2000 )         //Am79C970/1/2/3/5/6.
		        {
			        //System->SouthBridge = (unsigned long) 0;
		            printf("hal_hardware_detect: PCnet LANCE PCI Ethernet Controller Found.\n");
		        };
	
		        // Procura por PIIX4, vendor 8086, device 7113.
                // 82371AB		
		        if( Vendor == 0x8086 &&    //Intel.   
		        Device == 0x7113 )     //82371AB.
		        {
			        //System->SouthBridge = (unsigned long) 0x7113;
		            printf("hal_hardware_detect: Intel 82371AB PIIX4 Found.\n");
		        };

		        // Procura por vendor 8086, device 27B8. 
		        // Intel 82801GB ICH7.
		        // Name: 82801GB/GR (ICH7 Family) LPC Interface Bridge
		        // Name: I/O Controller Hub LPC
		        if( Vendor == 0x8086 &&    //Intel. 
		        Device == 0x27B8 )     //82801GB.
		        {
			        //System->SouthBridge = (unsigned long) 0x27B8;
		            printf("hal_hardware_detect: Intel 82801GB ICH7 Found.\n");
		        };
		
		        // Procura por vendor 8086, device 2448.
		        // Intel 82801 Mobile PCI Bridge.
		        if( Vendor == 0x8086 &&    //Intel.
                 Device == 0x2448 )     //82801.
		         {
			      //System->xxx = (unsigned long) 0x2448;
		           printf("hal_hardware_detect: Intel 82801 Mobile PCI Bridge Found.\n");
		         };		
		
		         // Procura por vendor 8086, device 27B9.
		         // Intel 82801GBM (ICH7-M) LPC Interface Bridge.
		        if( Vendor == 0x8086 &&    //Intel. 
		         Device == 0x27B9 )     //82801GBM.
		        {
			       //System->xxx = (unsigned long) 0x27B9;
		             printf("hal_hardware_detect: Intel 82801GBM (ICH7-M) LPC Interface Bridge Found.\n");
		          };

		        // Procura por vendor 8086, device 2829.
		        // Intel(R) ICH8M SATA AHCI Controller.
		        if( Vendor == 0x8086 &&    //Intel. 
		        Device == 0x2829 )     //Intel(R) ICH8M SATA AHCI Controller.
		       {
		     	//System->xxx = (unsigned long) 0x2829;
		        printf("hal_hardware_detect: Intel(R) ICH8M SATA AHCI Controller. Found.\n");
		       };
		
		       // vendor 0x10EC Realtek Semiconductor Corp.
		       //if( Vendor == 0x10EC && Device == 0 ){};
		
		// Continua...	
				
				//...
 
 */

 
/*
 * Beep support
 * #bugbug: Não quero comprometer a programação do PIT.
void Beep::tone(int freq) {
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
 
 
//OUT 
//Play sound using built in speaker
void hal_speaker_on (void){

    uint8_t tmp;

    //And play the sound using the PC speaker

    tmp = in8 (0x61);

    if (tmp != (tmp | 3))
    {
        out8 (0x61, tmp | 3);
    }
}


//IN
//make it shutup
void hal_speaker_off (void)
{
    uint8_t tmp = in8(0x61) & 0xFC;

    out8 (0x61, tmp);
}
 
 

//testando o beep;
void hal_test_speaker (void)
{
	int i;

    printf ("testing speaker ...\n");
    refresh_screen();

    hal_speaker_on ();
    
    for( i=0; i<49000; i++){};

    hal_speaker_off ();
} 
 


//@todo: criar. halGetBootInfo()



/*
 ************************************************
 * hal_backbuffer_putpixel:
 *     Coloca um pixel no backbuffer.
 */

// Chama a rotina em assembly depois de enviar os valores para os 
// registradores.
// IN: cor, x, y, 0

void 
hal_backbuffer_putpixel ( unsigned long ax, 
                          unsigned long bx, 
                          unsigned long cx, 
                          unsigned long dx )
{
    asm volatile ( "\n" : : "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    swlib_backbuffer_putpixel ();	
}


/*
 ************************************************
 * hal_lfb_putpixel:
 *     Coloca um pixel no LFB.
 */

// Chama a rotina em assembly depois de enviar os valores para os 
// registradores.
// IN: cor, x, y, 0

void 
hal_lfb_putpixel ( unsigned long ax, 
                   unsigned long bx, 
                   unsigned long cx, 
                   unsigned long dx )
{
    asm volatile ( "\n" : : "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    swlib_lfb_putpixel ();
}




/*
 *********************************************************
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
    return 0;    //#todo	
}


//#bugbug: tem algo errado aqui nos nomes das funções.
//hal_showpciinfo deveria ser a rotina que pci.c chama 
//para obter acesso as informações em baixo nível.
//@todo: rever os nomes das funções.

int hal_showpciinfo (void)
{	
	return (int) pciInfo ();
}


/*
 ******************************************
 * init_cpu:
 *     Inicializa a estrutura do processador e as coisas associadas a ele.
 *     Inicializa apenas o que for independente da arquitetura.
 *     @todo: Essa rotina pode ir para outro modulo do /hal. como cpu.c
 */
 
void init_cpu (void){
	
    int Status = 0;
	
	// #bugbug
	// Precisamos dar suporte à vários processadores,
	// e nessa rotina estamos usando uma estrutura para 
	// um processador específico.
	// Podemos atribuílo como Current ao fim da rotina.
	
	//
	// Processor struct
	//
	
	processor = (void *) kmalloc ( sizeof(struct tagProcessor) );
	
	if ( (void *) processor == NULL )
	{
	    panic ("hal-init_cpu: processor");
		
	} else {
	    
		//@todo: set processor id: escolhe o processador atual. ??
	
	    //Inicializa alguns valores da estrurura.
		
	    processor->Gdt = (unsigned long) getGdt ();
	    processor->Idt = (unsigned long) getIdt ();
	    processor->Tss = 0;  //getTss();
        
		//...
        
		if ( (void *) Hardware != NULL )
		{
			Hardware->Processor = processor;
		}
		
        //Nothing.		
    };	
	
	//sonda.
	//Checa qual cpu é, e inicializa mais variáveis.
	
	Status = (int) hal_probe_cpu (); 
	
	if( Status != 0 )
	{
	    panic ("init_cpu: hal_probe_cpu Status \n");  		
	};
	
    //More?!	


#ifdef HAL_VERBOSE
    printf("Done\n");
#endif	

    //#todo, o retorno deve ser int, para refletir o status.
    return;
};


void hal_set_machine_type ( unsigned long type ){
	
    g_machine_type = (unsigned long) type;
};


unsigned long hal_get_machine_type (void)
{	
    return (unsigned long) g_machine_type;
}


/*
 *****************************************************
 *  hal_init_machine:
 *      Faz inicializações dado o tipo de máquina.
 *      @todo: Trocar o nome para hal_init_current_machine. 
 */
 
int hal_init_machine (void){
	
	// Limits for machine type.
	
	if ( g_machine_type < 0 || g_machine_type > 4)
	{   
		panic ("hal-hal_init_machine:");  
	};
	
	
	// Type.
	
	switch (g_machine_type)    
	{
		//Unknow.
	    case 0:
		    //processor->Type = (unsigned char) 0;
		    break;
        
		//Intel.
	    case 1:
		    //processor->Type = (unsigned char) 1;
		    break;

	    //Amd.
		case 2:
		    //processor->Type = (unsigned char) 2;
		    break;

		//...	
	    case 3:
		    //processor->Type = (unsigned char) 3;
		    break;
        
		//Unknow.
		default:
		    //processor->Type = (unsigned char) 0;
	        printf("hal_init_machine: default type\n");
            return (int) 0; 		
			
		    break;
	};

	//More?!

    return 0;
}


unsigned long getGdt (void)
{	
    return (unsigned long) &gdt; 
}


unsigned long getIdt (void)
{	
    return (unsigned long) &idt; 
}


/*
unsigned long getTss (){
	
    return (unsigned long) &tss; 
}
*/
	
	
//credits: levex		
void hal_idt_register_interrupt ( unsigned long idt_location, unsigned char i, unsigned long callback )
{
	// Editando uma entrada na idt.
	
	//if(!__idt_setup) panic("Invalid IDT!");
	
	*(unsigned short*)(idt_location + 8*i + 0) = (unsigned short) (callback & 0x0000ffff);
	*(unsigned short*)(idt_location + 8*i + 2) = (unsigned short) 0x8;
	*(unsigned char*) (idt_location + 8*i + 4) = 0x00;
	*(unsigned char*) (idt_location + 8*i + 5) = 0x8e;    //0 | IDT_32BIT_INTERRUPT_GATE | IDT_PRESENT;
	*(unsigned short*)(idt_location + 8*i + 6) = (unsigned short)((callback & 0xffff0000) >> 16);
	
	//if(test_success) mprint("Registered INT#%d\n", i);
	//return;
}	
	

// Monitor vertical sync.
void hal_vsync (void)
{	
    vsync ();
}


/*
 * hal_reboot:
 *     O hal é a camada mis próxima do hardware, não há tratamento nenhum
 * para fazer, somente chamar o reboot via teclado. 
 * em headlib.s 
 */

void hal_reboot (void)
{	
    asm_reboot (); 
	
	panic ("hal_reboot");
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
 This is the basic sequence of APM commands that must be given in order to shut down a computer.
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
	
void hal_shutdown (void)
{	
	const char *shutdown_str;
	
    /* Bochs/QEMU poweroff */
	shutdown_str = "Shutdown";
    while (*shutdown_str) out8 (0x8900, *(shutdown_str++));
	
    panic ("hal_shutdown");
}


/*
 ********************************************************
 * init_hal:
 * Initialize kernel base hal.
 *     Archtecture independent inicialization ...
 */

int init_hal (void){
	
    int Status = 0;
	
#ifdef KERNEL_VERBOSE	
	printf("HAL:\n");
#endif	
	
	// CPU - Cria e inicializa a estrutura de cpu.
#ifdef HAL_VERBOSE
	printf("init_hal: cpu\n");
#endif	
	init_cpu();

		
	// TIMER - Cria e inicializa estrutura do timer.
#ifdef HAL_VERBOSE	
	printf("init_hal: Timer\n");
#endif


    // #todo: 
    // Essa inicialização deve ser adiada.
    // deixando para o processo init fazer isso.

    //timerInit ();

    
    // #todo:
    // Chamaremos essa inicialização básica nesse momento.
    // A inicialização completa será chamada pelo processo init.
    
    early_timer_init ();
    
    

	//
	// Detecta fabricantes específicos suportados pelo núcleo.  
	//
	
	hal_hardware_detect();
	
	//
	// Continua ...
	//

//Done:

    Initialization.hal = 1;	
	
#ifdef HAL_VERBOSE
	printf("Done\n");
#endif


#ifdef BREAKPOINT_TARGET_AFTER_HAL
    //#debug 
	//a primeira mensagem só aparece após a inicialização da runtime.
	//por isso não deu pra limpar a tela antes.
	printf(">>>debug hang: after init");
	refresh_screen(); 
	while (1){ asm ("hlt"); }
#endif	
	
	return (int) Status;
}


//
// End.
//
