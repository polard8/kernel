/*
 * File: kernel.h 
 *   
 * Descrição:
 *    Header externo do kernel base. Esse é o header público para o ambiente 
 * Kernel Base. Cada módulo interno tem seu header, mas esse é visível para 
 * todos os módulos dentro do Kernel Base.
 *
 *     Obs: A inicial 'Ki' deve ser usado para funções de módulos internos.
 *          Incluidos em tempo de compilação.
 *
 *     Obs: A inicial 'Ke' deve ser usado para funções de módulos externos.
 *          Incluidos na hora do carregamento do sistema.
 *          *** Também é usado para chamar os Servidores em user mode.
 *          como os subsistemas ou drivers em user mode. 
 *
 * Partes do Kernel:
 * ================
 *     São basicamente 3 partes: HAL, MICROKERNEL e EXECUTIVE.
 *
 * HAL: 
 *     O kernel deve ser independente do hardware. Então deve existir 
 * uma camada de abstração onde as operações envolvendo handware são chamadas, 
 * sem levar em conta o tipo específico de hardware presente na máquina.
 * HAL oferece os parâmetros dos elementos principais do hardware, como:
 * placa mãe, processador, memória ram, pci, bios.
 *
 * MICROKERNEL:
 *     Contém o básico envolvendo tarefas.
 *
 * EXECUTIVE:
 *     Contém os drivers VIP em kernel mode.
 *
 * Project info:
 * =============
 *     4Nora 32bit Research OS Kernel.
 *
 * Histórico:
 *     Versão: 1.0, 2013 - Esse arquivo foi criado por Fred Nora.
 *     Versão: 1.0, 2014 - Aprimoramento geral das rotians básicas.
 *     Versão: 1.0, 2015 - Aprimoramento geral das rotians básicas.
 *     Versão: 1.0, 2016 - Aprimoramento geral das rotians básicas.
 *
 * Copyright (c) frednora 2013~2017.
 */ 
 
/******************************************
 *                                        *  
 * Abaixo, a estrutura em kernel mode.    *
 * (hybrid)                               * 
 *                                        *
 *  ;----------------------------------;  *
 *  ;                                  ;  *
 *  ;             Gramado (GUI)        ;  *
 *  ;                                  ;  *  
 *  ;----------------------------------;  *
 *  ;----------------------------------;  *
 *  ;                                  ;  *
 *  ;             Executive            ;  *  
 *  ;                                  ;  *
 *  ;----------------------------------;  *
 *                                        *
 *  ;----------------------------------;  *
 *  ;            Microkernel           ;  *
 *  ;----------------------------------;  *
 *                                        *
 *  ;----------------------------------;  *
 *  ;              Hal                 ;  *
 *  ;----------------------------------;  *
 *                                        *
 *                                        *
 ******************************************/
 
 
// flag para mostrar ou não as mensagens de debug.
//#define KERNEL_VERBOSE 1 
 
 
/*
 * Definições globais.
 *     (Isso deve ficar no topo). 
 */
#include <gdef.h>      //Variáveis globais mais importantes. 
#include <gdevice.h>   //Informações globais sobre o host device.



/*
 * Verbose support.
 */
 
//#define EXECUTIVE_VERBOSE    
//#define HAL_VERBOSE          
//#define MICROKERNEL_VERBOSE  

 
/*
 * Kernel version.
 */
 
/*

  Sobre versoes:
       Para o kernel usarei números grandes para versões maiores e menores.
       para trocar a versão quando quiser. ex: 1234.4321.1.23
       Para o sistema operacional as versões maiores e menores mudarão com pouca 
frequencia. Ex: Os Version 1.0.1234.4321.

*/ 
 
#define KERNEL_VERSION "1.0"



/*
 * Kernel arquitecture support.
 *  
 *  Kernel híbrido.
 *
 * Kernel parts:
 * ============
 * EXECUTIVE, HAL, MICROKERNEL.
 *
 */

 
#define KERNEL      0
#define EXECUTIVE   1 
#define HAL         2 
#define MICROKERNEL 3


/*
 diretorios
/boot
/usr
*/

//
//metafile support
// 
//#define META_




/*
 * IOPL constants.
 */
 
#define KernelMode 0
#define UserMode   3
#define RING0 0 
#define RING1 1
#define RING2 2
#define RING3 3


/* 
// Segments @todo: Include this constants.
#define GDT_KCODE   0x08
#define GDT_KDATA   0x10
#define GDT_UCODE   (0x18 | 3)
#define GDT_UDATA   (0x20 | 3)
*/ 


/*
 * Kernel status constants.
 */
 
#define  KERNEL_NULL          0 
#define  KERNEL_INITIALIZED   1
#define  KERNEL_ABORTED       2
#define  KERNEL_INICIALIZADO  KERNEL_INITIALIZED
#define  KERNEL_ABORTADO      KERNEL_ABORTED
//#define  KE_ (-1)
//#define  KE_ (-2)
//#define  KE_ (-3)
//#define  KE_ (-4)


//#define LOBYTE(w) ((char)(((unsigned long )(w)) & 0xff))
//#define HIBYTE(w) ((char)((((unsigned long)(w)) >> 8) & 0xff))






/*
 * Externs.
 */
   
 
 
//outros. 
extern unsigned long task0_stack;
extern unsigned long task1_stack;
extern unsigned long task2_stack;
extern unsigned long task3_stack;
extern unsigned long stack0_krn_ptr;


//functions
extern void dispatch_context();
extern void do_executa_new_task();




 
/*
 *  Lib C. 
 */
 
// Cada arquivo deve incluir a clib que precisar ?!
// Pois existem definições repetidas na linguagem C.

//++
#include <stddef.h>
#include <types.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iso646.h>
#include <signal.h>  //Signal support.
//...
//--




/*
 * HAL
 */
//++ 
// Global first.
#include <microkernel/pc/mm/memmap.h>      //Memory Map - address. 
#include <hal/diskmap.h>     //Disk Map - sectors.
#include <hal/screen.h> 
#include <hal/video.h>       //video.
#include <hal/memory.h>      //ram  (controlado pelo cpu nas placas modernas).    
#include <hal/cpu.h>         //cpu 
#include <hal/disk.h>        //disk.
#include <hal/volume.h>      //volume partição.
#include <hal/serial.h>        
#include <hal/mac.h>         //mac address info. (hw)
#include <executive/dd/sm/network/host.h>         //host info.   
//...
//Unblocked.
#include <executive/dd/unblocked/ports.h>       //Portas para dispositivos
#include <executive/dd/unblocked/ps2.h>       //ps/2 
#include <executive/dd/unblocked/timer.h>       //PIT. irq0.
#include <executive/dd/unblocked/pic.h>         //PIC.
#include <executive/dd/unblocked/apic.h>        //APIC - Advanced Programmable Interrupt Controller.
#include <executive/dd/unblocked/rtc.h>         //clock    ( South bridge).
#include <executive/dd/unblocked/floppy.h>      //floppy   ( South bridge).
#include <executive/dd/unblocked/keyboard.h>    //irq1     ( South bridge). //keyboard
#include <executive/dd/unblocked/ldisc.h>    //irq1     ( South bridge).   //ldisc
#include <executive/dd/unblocked/ide.h>         //irq14/15 ( South bridge).
//...
//Blocked.

#include <executive/dd/blocked/sata.h>        //(PCI BUS).
#include <executive/dd/blocked/usb.h>         //usb.      
#include <executive/dd/blocked/pci.h>         //pci.  
//#include                   //pcie (controlado pelo cpu nas plcas modernas). 
//...
//Last stuffs. (precisam dos anteriores.)     
#include <hal/device.h>      //device manager.
#include <hal/hal.h>         //*****
//--



/*
 * MICROKERNEL
 */
 //++
#include <microkernel/cpu/context.h> 
         
#include <microkernel/pc/taskswitch.h>          
#include <microkernel/pc/tasks.h>  
#include <microkernel/pc/process.h> 
#include <microkernel/pc/thread.h>
#include <microkernel/pc/scheduler/scheduler.h>
#include <microkernel/pc/ipc/ipc.h> 
#include <microkernel/pc/ipc/semaphore.h> 
#include <microkernel/pc/queue.h>
#include <microkernel/pc/realtime.h>
#include <microkernel/pc/dispatch.h>
#include <microkernel/pc/event.h>
#include <microkernel/microkernel.h>
//--



/*
 * EXECUTIVE
 */
//++
    //Ordem: uigm, uitm, sm.
	//Porque o modo texto é dependente do modo gráfico e
	//gerenciamento do sistema é dependente das duas interfaces.

//tty - Gerenciado de fluxo de caracteres.
#include <executive/dd/tty/tty.h>	


//
// @todo: ( *** IMPORTANTE ***) 
// Testar se é possível colocar esses includes abaixo dos includes do executive.
//

//gramado - GUI. (presentation layer)
#include <gramado/gui/usession.h>
#include <gramado/gui/wstation.h>
#include <gramado/gui/desktop.h>
#include <gramado/gui/window.h>     //windows stuffs: pixel, line, rect, colors, video, windows...
#include <gramado/gui/menu.h>
#include <gramado/gui/grid.h> 
#include <gramado/gui/bmp.h>
// gramado/user
#include <gramado/user/user.h>
//gramado/logon
#include <gramado/logon/logon.h>
//gramado/logoff
#include <gramado/logoff/logoff.h>	
//principal
#include <gramado/gramado.h>   //principal.

//uigm - User Interface Graphic Mode.
//nothing for now.

//uitm - User Interface Text Mode.
#include <executive/dd/uitm/line.h>          //Gerência de linhas.
#include <executive/dd/uitm/terminal.h>      //configurações de terminal(o shel usa um terminal.) 
#include <executive/dd/uitm/console.h>            //Console ??

//sm - System Management.  
#include <executive/dd/sm/install.h>  
#include <executive/dd/sm/init.h>
#include <executive/dd/sm/network/nic.h>         //nic - network interface controller, adaptador de rede.
#include <executive/dd/sm/network/nports.h>  //(network) Network Ports  (sw)
#include <executive/dd/sm/network/socket.h>       //(network) Sockets info. (sw)
#include <executive/dd/sm/network/ip.h>            //(network) IP info.      (sw)
#include <executive/dd/sm/network/channel.h>       //(network) Channel       (sw)
#include <executive/dd/sm/network/client.h>        //(network) Client process support. 
#include <executive/dd/sm/network/server.h>        //(network) Server process support.
#include <executive/dd/sm/network/network.h>       //(network) Gerenciamento de rede. 

#include <executive/fs/fs.h>            //fs.

#include <executive/dd/sm/io.h>            //io

#include <executive/sci/systemcall.h>    //as chamadas ao sistema.

#include <executive/dd/sm/modules.h>       //gerenciamento de modulos.  
#include <executive/dd/sm/debug.h>
#include <executive/dd/sm/sys.h>           //*intefaces de gerenciamento do sistema.
#include <executive/dd/sm/system.h>        //*intefaces de gerenciamento do sistema.

//ram
#include <microkernel/pc/mm/mmglobal.h>	
#include <microkernel/pc/mm/heap.h>          //Heap pointer support.
#include <microkernel/pc/mm/aspace.h>        //Address Space (conta de banco de dados)
#include <microkernel/pc/mm/dspace.h>        //Disk Space (conta de banco de dados) 
#include <microkernel/pc/mm/bank.h>          //bancos de dados. 
#include <microkernel/pc/mm/mm.h>            //mm memory manager support.

//Esse fica em /executive..
#include <executive/executive.h>     // principal.
//--



//Cursor support.
#include <cursor.h>

//Prompt support.
#include <prompt.h>

/*
 * Kernel request support.
 */
 
#include <request.h>
 
/*
 * Kernel messages support.
 */
 
#include <messages.h>

   
/*
 * Object Manager support.
 */
 
#include <object.h>

//Suporte à sinais do sistema que vão além dos padrões da libC.
#include <ss.h>




/*
 * Globals.
 */
 
 
//keyboard suppport 
//Se o teclado é do tipo abnt2.
int abnt2;
 
//
// Product type.
//
typedef enum {
   PT_THINGS,        // Things.
   PT_EDGEDEVICES,   // Edge Devices.
   //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;

//Tipo de produto. (Qual é o destino desse sistema operacional.)
int g_product_type; 
 
 
//
// Platform type.
//
typedef enum {
   PFT_16BIT,   // 16 bit processor.
   PFT_32BIT,   // 32 bit processor.
   PFT_64BIT,   // 64 bit processor.
   //PFT_128BIT,  // 128 bit processor. (haha)	
}PlatformType_t;
 
//tamanho da palavra do processador.
int g_platform_type; 
 

/*
 * Current group:
 *     Grupo que o usuário atual pertence.
 */
int current_group; 

/*
 * current_user:
 *     Current User ID,
 */
int current_user; 
 
/*
 * current_session:
 *     Current user session.
 */
int current_usersession; 

/*
 * current_windowstation:
 *     Window station atual.
 */
int current_windowstation; 

/*
 * current_desktop:
 *     Desktop atual.
 */
int current_desktop; 

/*
 * current_window:
 *     Janela atual. 
 */
int current_window;  

/*
 * current_menu:
 *     menu atual. 
 */
int current_menu;  
  
/*
 * current_process:
 *     Processo atual. 
 */
int current_process;
 
/*
 * current_thread:
 *     Thread atual. 
 */
int current_thread;


unsigned long current_process_pagedirectory_address;

//Lista para armazenas os ponteiros das estruturas de todos os processadores.
//unsigned long processorsList[32];

//Quais processadores estão no estado IDLE.
//int idleprocessorList[8];

//Quais processadores estão no estado ACTIVE.
//int activeprocessorList[8];


//Tempo absoluto em que o sistema iniciou.
//unsigned long BootTime;

//Conta o número de processadores.
//int processors_count;

//A arquitetura do processador.(marca)
//int processor_architecture;

//Lista os serviços oferecidos pelo kernel atravéz da systemcall int 200.
//endereço da função. talvez seja uma chamada à um módulo esterno ou server.
//unsigned long SystemServices[256];


//Contador de thread switch.
//unsigned long thread_switch_count;

//Armazena o endereço da rotina de debug do sistema.
//unsigned long system_debugger_address;


//Armazena qual será o número de identificação
//do próximo processo ou thread criados.
// se for '0', tem que procurar um novo.
//se usar o número contido aqui, deve atualizar para 0.
//int NewPID;
//int NewTID;




//Continua current...



//
// Logon.
//

int g_logged;

//
// GUI
// 

int g_useGUI; //modo gráfico ou texto

/*
 * Procedure.
 */
unsigned long g_next_proc;      // Procedure adreess.


/*
 * Keyboard message.
 *     @todo: Mudar para g_new_message;
 *
 */
unsigned long g_nova_mensagem;  // Se há uma nova mensagem. (kb?)
unsigned long g_new_message;


unsigned long g_next_app;       // Procedure adreess. 
unsigned long g_proc_status;    // Procedure status. 



/*
 * Drivers support.
 *     Sinaliza se eles estão inicializados.
 *     @todo: issso sera usado por estruturas.
 */
int g_driver_video_initialized;
int g_driver_apic_initialized;
int g_driver_hdd_initialized;
int g_driver_keyboard_initialized;
int g_driver_pci_initialized;
int g_driver_rtc_initialized;
int g_driver_timer_initialized;
//...
 
 
/*
 * Executive modules support.
 *
 * Flags de inicialização dos módulos.
 */ 
int g_module_shell_initialized; 
int g_module_debug_initialized; 
int g_module_disk_initialized; 
int g_module_volume_initialized; 
int g_module_fs_initialized; 
int g_module_gui_initialized; 
int g_module_logoff_initialized; 
int g_module_logon_initialized; 
int g_module_mm_initialized; 
int g_module_objectmanager_initialized; 
int g_module_runtime_initialized; 
int g_module_uem_initialized;    //user_environment_manager


 
 

/*
 * Kernel variables.
 */



/*
 * Kernel information variables.
 */
 
unsigned long KernelSize;         //Tamanho do kernel.
unsigned long KernelHeapSize;     //Tamanho do heap do kernel.
unsigned long KernelStackSize;    //Tamanho da pilha do kernel.
unsigned long KernelPages;
unsigned long KeInitPhase;        //Fase da inicialização. 
unsigned long KernelStatus;       //Status do kernel: (inicializado,abortado).


/*
 * Task support variables. 
 */ 
 
unsigned long kernel_request;    //O que fazer com a tarefa atual.
unsigned long kernel_switch;     //Ativa o kernel switch do scheduler.


/*
 * Count support variables.
 */
 
unsigned long kernel_tick;          //Contagem de tempo de funcionamento do sistema.
unsigned long kernel_tick_total;    //Tempo total de funcionamento do sistema.



/*
 * Kernel error variables.
 */ 
unsigned long errno;            //error number (global usada em abort).






/*
 * File system arrays.
 * @todo: isso deve ir para fs.h
 */
 
// Lista de clusters, para manipular arquivos. 
unsigned long file_cluster_list[1024];    //@todo rever tamanho.

// Buffer para salvar uma entrada de diretório.
char buffer_dir_entry[512];     //@todo rever tamanho. 


//Um buffer para logs do kernel.
char KernelLogBuffer[512];
 

//
// Plataform support.
//

//OBS: Não são diretórios.
#define PLATFORM_PATH  "/Platform"
#define HARDWARE_PATH  "/Platform/Hardware"
#define FIRMWARE_PATH  "/Platform/Firmware"
#define SYSTEM_PATH    "/Platform/System"
//#define USERS_PATH     "/Platform/Users"
//...



/*
 * ring0_exported_d:
 *     Ponteiros para tabelas de funções exportadas pelos
 *     programas do sistema em ring 0.
 *     são 3 programas. BM.BIN, BL.BIN. KERNEL.BIN.
 *
 */
typedef struct ring0_exported_d ring0_exported_t; 
struct ring0_exported_d
{
    unsigned long bm_exported; // Boot Manager exported functions.
    unsigned long bl_exported; // Boot Loader exported functions.
    unsigned long bk_exported; // Kernel exported functions.
};
ring0_exported_t *ring0_exported;



typedef struct node_d node_t;
struct node_d
{
    void *data;
	
	//struct window_d *window;
    //int msg;	
    //unsigned long long1;
    //unsigned long long2;
    
	struct node_d *flink;
    struct node_d *blink;    
};


/*
 * Linked list support.
 */ 
typedef struct linkedlist_d linkedlist_t;
struct linkedlist_d
{
    struct node_d *head;
    struct node_d *tail;    
};




/*
 * Structures used for Kernel.
 */
 
 
 
 
typedef struct kernel_args_d kernel_args_t; 
struct kernel_args_d
{
    unsigned long arg1;
	unsigned long arg2;
	unsigned long arg3;
	unsigned long arg4;
}; 
kernel_args_t KernelArgs; 
 


typedef struct system_classes_d system_classes_t;
struct system_classes_d
{
    unsigned long Executive;
    unsigned long Microkernel;	
    unsigned long Hal;	
};
system_classes_t SystemClasses;


typedef struct kernel_classes_d kernel_classes_t;
struct kernel_classes_d
{
    struct system_classes_d *System; 	
	//..
};
kernel_classes_t KernelClasses;
//...



//Kernel Manager.
typedef struct kernel_d kernel_t;
struct kernel_d
{
    //
    // Kernel info.
    //
	
	char *name;               //File name.(KERNEL.BIN)
	unsigned long address;    //endereço.
	
	//struct kernel_block_d *KernelBlock;  //Ponteiro para bloco de informações
	
	
	//struct process_d *process;
	
    //
    // Structs.
    //	

	struct bootmanager_d  *BootManagerBlock;    //Boot Manager.	
	struct bootloader_d   *BootLoaderBlock;     //Boot Loader.
	struct system_d       *SystemBlock;         //System. (Kernel + Módulos)
    struct ProcessorBlock_d    *ProcessorBlock;      //Processor info. (processador atual)
    
	
	//
	// CPUs.
	//
	
	int processorCount;  //Número de processadores.
	struct processor_descriptor_t *processorListHead;   //Lista de processadores..
	
	//kernel_args_t
	//kernel_classes_t
	
	//...
};
kernel_t *KernelInfo; 
//...
 
 
 
 
/*
 * plataform_d:
 *     Os componentes básicos da máquina.     
 *     As estruturas de Hardware e Software.
 *     * IMPORTANTE Essa é a estrutura BASE do kernel.
 */
typedef struct platform_d platform_t;
struct platform_d 
{
    //Name.
	char *name;
	
	//Type.
	
	
	
	//  *Hardware - Componentes do hardware.
	//  *Firmware - Componentes se software embarcados. BIOS, UEFI ...
    //  *Software - Componentes do Sistema operacional.
    
    struct hardware_d *Hardware;	// hal\hal.h
	struct firmware_d *Firmware;	// hal\hal.h
	struct system_d   *System;      // executive\system.h
	
	
	//kernel struct ...
	struct kernel_d *Kernel;
};
platform_t *Platform; 




 
/*
 * Prototypes: -------------------------------------------
 *
 * @todo: Interfaces que o kernel usa para chamar as rotinas
 * de inicialização oferecidas pelos modulos.
 *
 * O kernel chama os modulos atraves das interfaces(funções)
 * começadas por 'Ke'. ja os modulos inicializam as rotinas
 * com funções começadas por 'Ki'. (KernelInitializations)
 *
 */
 

	
int kMain(int argc, char* argv[]); 
 
 
 
//
// Initializations support.  
//


int init_runtime();         //RunTime.
void boot();                //??
void save_kernel_args();    //salva os argumentos do kernel em estrutura.


//
// Linked list support.
// 
void* newLinkedlist();
void* newNode();
void Removing_from_the_beginning(struct linkedlist_d *list);
void Removing_from_the_middle(struct linkedlist_d *list);
void Removing_from_the_end(struct linkedlist_d *list);

 
 

 
 
//
// Count support.
//
 
unsigned long get_tick_count();



/*
 * Sincroniza o retraço vertical. para directdraw usando lfb.
 * @todo: 
 *     Essa função pode ser arte do hal, 
 * ficando aqui apenas uma interface.
 *Obs: Isso é coisa de hardware. vídeo. (HAL)
 */
//void vsync(); 


//
// Delay support.
//
 
void sleep(unsigned long ms);    
  
  
//
// Finalizations support.
//
 
void faults(unsigned long number); 

void shutdown();

//
// error support
//  
void abort();    //abort.c *erros de níveis diferentes. 
void die();      //system.c * erro fatal. 

/*
 * ke - Kernel External.
 * ki - Kernel Internal.
 *      (Isso deve ficar aqui embaixo, pois usa os recursos definidos acima.).
 */
#include <ke.h> 
#include <ki.h> 

 
//
// Fim.
//

