/*
 * Gramado Hal - The main file for the Hal module in the kernel base. 
 * (c) Copyright 2015-2016 Fred Nora.
 *
 *  File: k\hal\hal.c 
 *  
 * Classes:
 *     system.unblockeddevices (K2)
 *     system.blockeddevices   (K1)
 *     system.things           (K0)
 *
 * HAL:
 *     O HAL lida especialmente com dispositivos externos.
 * Seu trabalho é permitir que as camadas superiores não se preocupem
 * com detalhes específicos dos dispositivos e encarem todos de forma genérica.
 *     O ambiente do hal é ideal para realizar proteção de variáveis estruturas e 
 * funções
 *     É aceitável a inclusão de código em assembly nessa camada do sistema. 
 *
 *
 *  Descrição:
 *      Hardware Abstraction Layer.
 *      MB - Módulos incluídos no Kernel Base.
 *      I/O Manager.
 *
 *  Objetivo: 
 *      Interface comum para identificar e acessar arquiteturas diferentes.
 *      Principalmente placa mãe e processador.   
 *      ( cpu, context, mmu, trap, clock, interrupt )
 *
 * Obs: É esperado que a sondagem de sispositivos aconteça nesse módulo.
 *
 * @todo:
 *     +Os serviços oferecidos por esse módulo aparecerão aqui começando 
 *     por 'sys_'. ??
 *     Na verdade as rotinas aqui devem começar por hal_, o módulo system,
 *     fará interfaces começando por sys_.
 *     + halHal(); é o construtor.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Aprimoramento geral das rotinas básicas.
 *     //...
 */
 
 
#include <kernel.h>
//#include "hidata.h"  //Hal Internal Data.

//unsigned char  HalName[] = "HAL LAYER";

//
// Variáveis importadas.
//

extern unsigned long gdt;
extern unsigned long idt;

extern void gui_buffer_putpixel();

//
//@todo: criar rotina hal_get_page_dir();
//extern unsigned long _get_page_dir();
//

//
// Protótipo de funções internas.
//

unsigned long getGdt();
unsigned long getIdt();



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
 *
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
 
 
/*
void halMain();
void halMain(){
	return;
};
*/


//@todo: criar. halGetBootInfo()








/*
 * hal_backbuffer_putpixel:
 *     Coloca um pixel no backbuffer.
 *
 */
void hal_backbuffer_putpixel( unsigned long ax, 
                              unsigned long bx, 
						      unsigned long cx, 
						      unsigned long dx )
{
	
	
	 //cor,x,y,0
	asm volatile(" \n " : : "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
		
	/*
	 * Chama a rotina em assembly depois de enviar os valores para os 
	 * registradores.
	 */
	 
	//Coloca um pixel no backbuffer. 
	// ?? De onde vem essa rotina ??
	// @todo: Devemos chamar o módulo hal.
	gui_buffer_putpixel(); 	
	return;
};



/*
 * sys_vsync:
 * 
 */
void sys_vsync(){
    hal_vsync();	
    return;
};


int sys_showpciinfo(){
    return (int) hal_showpciinfo();
};


/*
 * sys_reboot:
 *     Reboot, Serviço do sistema.
 */
void sys_reboot(){
    KiReboot();
    while(1){}	
};


/*
 * sys_shutdown:
 * ShutDown. Serviço do sistema.
 */
void sys_shutdown(){
    KiShutDown();
    while(1){}
};


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
int hal_hardware_detect()
{		
    //int Status;
	
	//
	// Check system struct.	
    //
	
	if((void*) System == NULL){
	    return (int) 1;    //Fail.	
	}else{
		
		//
		// @todo: Talvez essa estrutura deva ser inicializada em outra rotina.
		//        Checar a validade da estrutura system. 
		//
		
		//Initialize.
		System->NorthBridge = (unsigned long) 0;
	    System->SouthBridge = (unsigned long) 0;
		//...
	};
	
	
	//
	// 
	// Consumer Chipsets (Z87, H87, H81) Haswell LGA1150. 
	// Business Chipsets (Q87, Q85, B85) Haswell LGA1150.
	//
	//
	
	
	//
	// Check North Bridge. (@todo)
	//
	
	
	//
	// OBS: As CPUs modernas fazem o papel da north bridge.
	//
	
	
	
	//
	// Check South Bridge.
	//

    //Continua...
	
done:
    return (int) 0;	
};


int hal_showpciinfo(){
	return (int) pciInfo();
};


/*
 * hal_probe_processor_type:
 *     Sonda pra ver apenas qual é a empresa do processador.
 */
int hal_probe_processor_type()
{
    int MASK_LSB_8 = 0xFF;  
	unsigned long eax, ebx, ecx, edx;
	unsigned long name[32];	
		
	//debug.
	//printf("Scaning x86 CPU ...\n");
		
    //vendor
    cpuid( 0, eax, ebx, ecx, edx ); 
	name[0] = ebx;
	name[1] = edx;
	name[2] = ecx;
	name[3] = 0;	
	//salva na estrutura.
	processor->Vendor[0] = ebx;
	processor->Vendor[1] = edx;
	processor->Vendor[2] = ecx;
	processor->Vendor[3] = 0;	
	
	// Confere se é Intel.
	if( ebx == CPUID_VENDOR_INTEL_1 && 
	    edx == CPUID_VENDOR_INTEL_2 && 
		ecx == CPUID_VENDOR_INTEL_3 )
	{
	    return (int) Processor_INTEL;    //Intel.
	};
	
	// Confere se é AMD
	if( ebx == CPUID_VENDOR_AMD_1 && 
	    edx == CPUID_VENDOR_AMD_2 && 
		ecx == CPUID_VENDOR_AMD_3 )
	{
	    return (int) Processor_AMD;    //AMD.
	};		
	
	//Continua...
	
fail:		
	return (int) Processor_NULL;	
};


/*
 * init_cpu:
 *     Inicializa a estrutura do processador e as coisas associadas a ele.
 *     Inicializa apenas o que for independente da arquitetura.
 *     @todo: Essa rotina pode ir para outro modulo do /hal. como cpu.c
 */
void init_cpu()
{
    int Status = 0;
	
	processor = (void*) malloc( sizeof(struct tagProcessor) );
	if((void*) processor == NULL){
	    printf("init_cpu:");
	    die();
		//refresh_screen();
		//while(1){};
		//return;
	}else{
	    
		//@todo: set processor id: escolhe o processador atual. ??
	
	    //Inicializa alguns valores da estrurura.
	    processor->Gdt = (unsigned long) getGdt();
	    processor->Idt = (unsigned long) getIdt();
	    processor->Tss = 0;  //processor->Id=getTss();
        
		//...
        
		if( (void*) Hardware != NULL ){
			Hardware->Processor = processor;
		};
        //Nothing.		
    };	
	
	//Checa qual cpu é e inicializa mais variaveis.
	Status = (int) hal_probe_cpu(); //sonda.
	if(Status != 0){
	    printf("init_hal fail: Probe cpu.");
        die();
		//refresh_screen();
        //while(1){};
        //return;   		
	};
	
    //More?!	
	
done:

#ifdef KERNEL_VERBOSE
    printf("Done\n");
#endif	
    return;
};


void hal_set_machine_type(unsigned long type)
{
    g_machine_type = (unsigned long) type;
	return;
};


unsigned long hal_get_machine_type(){
    return (unsigned long) g_machine_type;
};


/*
 *  hal_init_machine:
 *      Faz inicializações dado o tipo de máquina.
 *      @todo: Trocar o nome para hal_init_current_machine. 
 */
int hal_init_machine()
{	
	// Limits for machine type.
	if( g_machine_type < 0 || g_machine_type > 4)
	{
	    //#bugbug: Devemos parar aqui.
		printf("hal_init_machine:\n");
        return (int) 0;    
	};
	
	// Type.
	switch(g_machine_type)    
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
	        printf("hal_init_machine error: default type.\n");
            return (int) 0; 			
		    break;
	};

	//More?!
	
done:
    return (int) 0;
};



/*
 * hal_probe_cpu:
 *     Detectar qual é o tipo de processador. 
 *     Salva o tipo na estrutura.
 *
 * @todo: Estamos usando cpuid para testar os 2 tipos de arquitetura.
 * nao sei qual ha instruções diferentes para arquiteturas diferentes.
 */
int hal_probe_cpu()
{
	unsigned long eax, ebx, ecx, edx;
	
#ifdef KERNEL_VERBOSE
    printf("hal_probe_cpu:\n");	
#endif
	
	//
	// Check structure.
	//
	
	if((void*) processor == NULL )
	{
	    printf("hal_probe_cpu fail: Struct.\n");
		//@todo: Aqui não deveria parar.
		return (int) 1;    //Fail.
	};
	
    //Check vendor.
    cpuid( 0, eax, ebx, ecx, edx); 

//Confere se é intel.	
TestIntel:
	if( ebx == CPUID_VENDOR_INTEL_1 && 
	    edx == CPUID_VENDOR_INTEL_2 && 
		ecx == CPUID_VENDOR_INTEL_3 )
	{
	    processor->Type = Processor_INTEL;
		return (int) 0;
	};

//Confere se é Amd.	
TestAmd:
	if( ebx == CPUID_VENDOR_AMD_1 && 
	    edx == CPUID_VENDOR_AMD_2 && 
		ecx == CPUID_VENDOR_AMD_3 )
	{
	    processor->Type = Processor_AMD;
		return (int) 0;
	};

//Desconhecido.	
//@todo: Aqui é um erro fatal.
Fail:
	processor->Type = Processor_NULL;	
    return (int) 1;
};


unsigned long getGdt(){
    return (unsigned long) &gdt; 
};

unsigned long getIdt(){
    return (unsigned long) &idt; 
};

void hal_vsync(){
    vsync();
    return;	
};


/*
 * hal_shutdown:    
 */
void hal_shutdown(){
    shutdown();
    die();
};


/*
 * shutdown:
 *     Desligar a máquina.
 *     @todo: APM, ACPI.
 *
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
void shutdown()
{
	//
	// @todo: Background.
	//
	
    MessageBox(gui->screen ,1 ,"shutdown:" ,"@todo:");
	
	//
	// @todo: switch APM, ACPI. modo smm	
	//        Obs: Aqui, temporariamente, poderia desabilitar todo o
	//             sistema e permitir que o usuário desligue a energia
	//             manualmente. 
	//            (Ex: O computador pode ser desligado com segurança).  
	//
	
fail:	
    die();
};




/*
 * KiReboot:
 *     Inicialização da parte de hardware do processo de reboot.   
 */
void KiReboot()
{
	//
	// @todo: fechar as coisas aqui antes de chamar hal_reboot()
	// pois hal fica responsavel pela parte de hardware.
    // As rotinas de desligamento do sistema foram para syste.c systemReboot().
	// ficará aqui somente o que prescede o shamamento de hal.
	// em hal ficarão as rotinas de reiniamento de hardware.
    //

    //
    // hal	
    // Reboot via keyboard.	
	//
	
do_reboot:
    StatusBar( gui->screen, "StatusBar:", "Rebooting...");	
	refresh_screen();
	hal_reboot();
    die();	 
};



/*
 * KiShutDown:
 *    @todo: Isso será uma interface para chamar o deligamanto.
 *
 *
 */
void KiShutDown()
{
    hal_shutdown();
    die();
};


/*
 * hal_reboot:
 *     O hal é a camada mis próxima do hardware, não há tratamento nenhum
 * para fazer, somente chamar o reboot via teclado. 
 */
void hal_reboot()
{
    asm_reboot(); 
	die();
};


/*
 * init_hal:
 * Initialize kernel base hal.
 *     Archtecture independent inicialization ...
 *     (Inicialização de estruturas.)
 *
 *     Faz inicializações do hardware básico.
 *
 *     obs: Segue a ordem de importância.
 *          Cpu, Pci (bustype), Timer, Cmos/Rtc, Keyboard ...
 */
int init_hal()
{	
    int Status = 0;
	
#ifdef KERNEL_VERBOSE	
	printf("HAL:\n");
#endif	
	
	// CPU - Cria e inicializa a estrutura de cpu.
#ifdef KERNEL_VERBOSE	
	printf("init_hal: cpu..\n");
#endif	
	init_cpu();

	
	//
	// Bug Bug - PCI Initialization.
	//
	
	// PCI - Cria e inicializa estrutura de pci.
#ifdef KERNEL_VERBOSE	
	printf("init_hal: pci..(BUG) \n");
#endif	
	init_pci();    //bugbug (a rotina esta incompleta.)	

	//@todo: Isso é um teste de inicialização de pci.
	//printf("* init_hal: Debug!");
    //refresh_screen();
    //while(1){}		
	
	
	// TIMER - Cria e inicializa estrutura do timer.
#ifdef KERNEL_VERBOSE	
	printf("init_hal: Timer..\n");
#endif    
	timerInit();	

	// RTC - Cria e inicializa estrutura de rtc.
#ifdef KERNEL_VERBOSE	
	printf("init_hal: rtc..\n");
#endif	
	init_clock();
	get_cmos_info();
		
		
	//
    //@todo 8042 ... teclado e mouse.
    //
    //P8042_install();	
		
    //keyboard.
#ifdef KERNEL_VERBOSE	
	printf("init_hal: kd..\n");
#endif	
	init_keyboard();
	
	//mouse
	//printf("init_hal: mouse..\n");
	//init_mouse();  //isso está em keyboard.c
	
	//printf("init_hal: init machine (bug)\n");	
	//hal_init_machine();	
	

	//Ports components.
	
	//
	// bios date. (detect)
	//
	
	//Collecting Disk Geometry
	//Floppy Component 
	

	//Video Display Adapter.
	 //init_screen();
	
	//Mouse components

	//
	// Detecta fabricantes específicos suportados pelo núcleo.  
	//
	
	hal_hardware_detect();
	
	//
	// Continua ...
	//

Done:
    Initialization.hal = 1;	
	
#ifdef KERNEL_VERBOSE
	printf("Done!\n");
#endif
	
	return (int) Status;
};


/*
int halInit()
{
	
};
*/


//
// End.
//
