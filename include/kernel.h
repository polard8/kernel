/*
 * Gramado Operating System - The main header for the kernel base. 
 * (c) Coppyright 2018 - Fred Nora.
 *
 * File: kernel.h 
 *
 * This is the header file kernel base.
 * This is a hybrid kernel. 
 * The kernel base has 4 layers: 
 *     HAL, MICROKERNEL, EXECUTIVE and GRAMADO.
 *
 * *****************************************
 * *                                       *  
 * * ;----------------------------------;  *
 * * ;                                  ;  *
 * * ;               GWS                ;  *
 * * ;                                  ;  *  
 * * ;----------------------------------;  *
 * * ;----------------------------------;  *
 * * ;                                  ;  *
 * * ;             Execve               ;  *  
 * * ;                                  ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * * ;----------------------------------;  *
 * * ;               MK                 ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * * ;----------------------------------;  *
 * * ;              Hal                 ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * *****************************************
 *
 *
 * History:
 *     2013 - Created by Fred Nora.
 *     2014~2018 - Resision.
 */
 

//
// ## Config section ##
// 
 

/* Configuração de produto */ 
#include <kernel/config/gramado.h> 
 
/* Configuração de compilação */ 
#include <kernel/config/config.h> 


//
// ## Globals section ##
// 

// Global definitions.
// This must be on top.

#include <kernel/globals/gpa.h>
#include <kernel/globals/gva.h>
#include <kernel/globals/gentry.h>
#include <kernel/globals/gdef.h>
#include <kernel/globals/gdevice.h>
//...

//spinlocks
#include <kernel/gramado/mk/pc/spinlock.h>

//layer.

#define HAL         4   //4
#define MICROKERNEL 3   //3
#define EXECUTIVE   2   //2
#define GRAMADO     1   //1 gws

#define KERNEL      0




//IOPL constants.
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


//Kernel status constants.
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


//
//  ## JOB CONTROL SUPPORT ##
//

#define PROCESS 10
#define THREAD  20
#define BACKGROUND 100 
#define FOREGROUND 200



//
// Externs.
//


//Stack for fome threads in kernel mode. 
extern unsigned long task0_stack;
extern unsigned long task1_stack;
extern unsigned long task2_stack;
extern unsigned long task3_stack;
extern unsigned long stack0_krn_ptr;
//...


//functions
extern void dispatch_context();
extern void do_executa_new_task();






// kernel libC support.
//++
#include <kernel/stddef.h>
#include <kernel/types.h>
#include <kernel/limits.h>
#include <kernel/stdio.h>
#include <kernel/stdlib.h>
#include <kernel/string.h>
#include <kernel/ctype.h>
#include <kernel/iso646.h>
#include <kernel/signal.h>
#include <kernel/unistd.h>
//...
//--





// ## hardware ## 

#include <kernel/gramado/intel.h>
#include <kernel/gramado/memory.h>

#include <kernel/gramado/cpuid.h>
#include <kernel/gramado/screen.h>
#include <kernel/gramado/video.h>
#include <kernel/gramado/rtc.h>
//...

// ## shared ## 
#include <kernel/gramado/fonts.h>
#include <kernel/gramado/ascii.h>     //ascii table 
#include <kernel/gramado/fs.h> 
#include <kernel/gramado/prompt.h>
#include <kernel/gramado/bmp.h>
//...


//
// MICROKERNEL (3)
//


// Global first.
#include <kernel/gramado/mk/pc/mm/memmap.h>            //Memory Map - address.



//execve
#include <kernel/gramado/execve/sm/disk/diskmap.h>        //Disk Map - sectors.


//
// HAL (4)
//

#include <kernel/gramado/hal/screen.h> 
#include <kernel/gramado/hal/video.h>                        //video.
#include <kernel/gramado/hal/memory.h>                       //ram (hardware).
#include <kernel/gramado/hal/cpu.h>  
#include <kernel/gramado/hal/arch/x86/x86.h> 
#include <kernel/gramado/hal/arch/amd/cpuamd.h>  

#include <kernel/gramado/hal/arch/detect.h>  


//disk1 - nelson
//#include <kernel/gramado/3rdparty/sirius.h>
#include <kernel/gramado/execve/dd/ide/disk1.h>

//execve
#include <kernel/gramado/execve/sm/disk/disk.h>           //disk.

#include <kernel/gramado/execve/sm/disk/volume.h>         //volume.
#include <kernel/gramado/hal/serial.h>        
#include <kernel/gramado/hal/mac.h>                             //mac address info. (hw)
//...

//
// EXECUTIVE (2)
//

//não mecher na ordem, pode dar problemas;
 //Portas para dispositivos
#include <kernel/gramado/hal/arch/x86/portsx86.h>       

#include <kernel/gramado/execve/dd/serial.h>  
#include <kernel/gramado/execve/dd/ps2.h>          //ps/2 
#include <kernel/gramado/execve/dd/timer.h>        //PIT. irq0.
#include <kernel/gramado/execve/dd/pic.h>          //PIC.
#include <kernel/gramado/execve/dd/apic.h>         //APIC - Advanced Programmable Interrupt Controller.
#include <kernel/gramado/execve/dd/rtc.h>          //clock.
#include <kernel/gramado/execve/dd/floppy.h>       //floppy.
#include <kernel/gramado/execve/dd/keyboard.h>     //irq1     //keyboard
#include <kernel/gramado/execve/dd/vk.h>         //virtual keys
#include <kernel/gramado/execve/dd/abnt2.h> 
#include <kernel/gramado/execve/dd/ldisc/ldisc.h>        //ldisc

#include <kernel/gramado/execve/dd/ide/ide.h>          //irq14/15 


#include <kernel/gramado/execve/dd/pci/pci.h>            //pci.

//#Test
#include <kernel/gramado/execve/dd/ahci/ahci.h>          
#include <kernel/gramado/execve/dd/ahci/sata.h>          


#include <kernel/gramado/execve/dd/usb.h>            //usb.

//#include                                       //pcie.
//...

//
// HAL (4)
//

//This must to be on the bottom of HAL part.    
#include <kernel/gramado/hal/device.h>      //device manager.
#include <kernel/gramado/hal/hal.h>         //*****
//--


/*
 * MICROKERNEL (3)
 */
 //++

#include <kernel/gramado/mk/arch/x86/x86cont.h>
#include <kernel/gramado/mk/pc/ts.h>
#include <kernel/gramado/mk/pc/tasks.h>
#include <kernel/gramado/mk/pc/process.h>
#include <kernel/gramado/mk/pc/thread.h>
#include <kernel/gramado/mk/pc/sched/sched.h>
#include <kernel/gramado/mk/pc/ipc/ipc.h>
#include <kernel/gramado/mk/pc/ipc/sem.h>
#include <kernel/gramado/mk/pc/queue.h>
#include <kernel/gramado/mk/pc/realtime.h>
#include <kernel/gramado/mk/pc/dispatch.h>
#include <kernel/gramado/mk/pc/event.h>
#include <kernel/gramado/mk/pc/pc.h>
#include <kernel/gramado/mk/mk.h>
//--


//
// EXECUTIVE (2)
//

//tty
#include <kernel/gramado/execve/dd/tty/tty.h>


//
// GRAMADO (1)
// This must to be on the bottom.
//

//gramado - GUI. (presentation layer)
//Gramado Window Server
#include <kernel/gramado/gws/gws/ws.h>

//user
#include <kernel/gramado/gws/user/usession.h>
#include <kernel/gramado/gws/user/room.h>
#include <kernel/gramado/gws/user/desktop.h>

#include <kernel/gramado/gws/gws/window.h>

//tentar mudar de lugar.
#include <kernel/gramado/execve/dd/i8042/i8042.h>
#include <kernel/gramado/execve/dd/i8042/ps2mouse.h>
#include <kernel/gramado/execve/dd/i8042/ps2kbd.h>

#include <kernel/gramado/gws/gws/menu.h>
#include <kernel/gramado/gws/gws/grid.h>
#include <kernel/gramado/gws/gws/bmp.h>
#include <kernel/gramado/gws/gws/guiconf.h>  //*principal.

// user, logon, logoff
#include <kernel/gramado/gws/user/user.h>
#include <kernel/gramado/gws/logon/logon.h>
#include <kernel/gramado/gws/logoff/logoff.h>

//principal
#include <kernel/gramado/gws/gws.h>                     

//uigm - User Interface Graphic Mode.
//nothing for now.

//gws/terminal 
//suporte a terminal.
#include <kernel/gramado/gws/terminal/line.h>              //lines support.
#include <kernel/gramado/gws/terminal/terminal.h>          //terminal support. 
#include <kernel/gramado/gws/terminal/console.h>           //Console. Monitor support.

//sm - System Management.  
#include <kernel/gramado/execve/sm/install.h>  
#include <kernel/gramado/execve/sm/init.h>

#include <kernel/gramado/execve/dd/network/host.h>        //host info.

#include <kernel/gramado/execve/dd/network/ethernet.h>
#include <kernel/gramado/execve/dd/network/arp.h>

#include <kernel/gramado/execve/dd/network/intel.h>       //intel nic - network interface controller.
#include <kernel/gramado/execve/dd/network/nports.h>      //(network) Network Ports  (sw)
#include <kernel/gramado/execve/dd/network/socket.h>      //(network) Sockets info. (sw)
#include <kernel/gramado/execve/dd/network/ip.h>          //(network) IP info.      (sw)
#include <kernel/gramado/execve/dd/network/channel.h>     //(network) Channel       (sw)
#include <kernel/gramado/execve/dd/network/client.h>      //(network) Client process support. 
#include <kernel/gramado/execve/dd/network/ns.h>          //(network) Network Server.
#include <kernel/gramado/execve/dd/network/network.h>     //(network) Gerenciamento de rede. 

#include <kernel/gramado/execve/fs/fs.h>                     //fs.
#include <kernel/gramado/execve/fs/vfs.h>                     //vfs.
#include <kernel/gramado/execve/sm/io.h>                  //io.
#include <kernel/gramado/execve/sci/syscall.h>            //system calls.
#include <kernel/gramado/execve/sm/modules.h>             //module manager.
#include <kernel/gramado/execve/sm/debug.h>
#include <kernel/gramado/execve/sm/sys.h>                 //system calls 2.
#include <kernel/gramado/execve/sm/system.h>              //system manager.
#include <kernel/gramado/execve/dd/dd.h>

//
// MICROKERNEL (3)
//

//mm
#include <kernel/gramado/mk/pc/mm/mmglobal.h>
#include <kernel/gramado/mk/pc/mm/heap.h>          //Heap pointer support.
#include <kernel/gramado/mk/pc/mm/aspace.h>        //Address Space, (data base account).
#include <kernel/gramado/mk/pc/mm/dspace.h>        //Disk Space, (data base account).
#include <kernel/gramado/mk/pc/mm/bank.h>          //Bank. database
#include <kernel/gramado/mk/pc/mm/mm.h>            //mm, memory manager support.


//
// EXECUTIVE (2)
//

#include <kernel/gramado/execve/execve.h>              //main file.
//--


//
// Some other stuff.
//

//Cursor support.
#include <kernel/gramado/cursor.h>

//Kernel request support.
#include <kernel/gramado/request.h>

//Kernel messages support.
#include <kernel/gramado/messages.h>

//Object Manager support.
#include <kernel/gramado/object.h>

//system signals. (SS)
#include <kernel/gramado/ss.h>

#include <kernel/gramado/events.h>

//=============================================


//
// Globals.
//


//keyboard suppport 
//abnt2 flag.
int abnt2;
//...


// Product type.
typedef enum {
   PT_THINGS,        // Things.
   PT_EDGEDEVICES,   // Edge Devices.
   //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;


//Type of product.
int g_product_type; 


// Platform type.
typedef enum {
   PFT_16BIT,       //16bit processor.
   PFT_32BIT,       //32bit processor.
   PFT_64BIT,       //64bit processor.
   //...
}PlatformType_t;


//size of processor word.
int g_platform_type;


int current_user;    //gramado ?
int current_group;   //gramado ?

//#importante:
//isso foi movido para gws\ws.h
//int current_usersession;    //gws
//int current_windowstation;  //gws
//int current_desktop;        //gws 
//int current_window;         //gws
//int current_menu; //gws

//
// #importante
// Essa é a verdadeira idle, que está em ring 0 e trabalha 
// quando sistema está ocioso.
// ela deve ficar bloqueada quendo outras estão trabalhando. 
// Ela não pode ser destruída e nem alterada ... uma vez configurada 
// ficará sendo ela pra sempre, se ela fechar o sistema deve falhar.
int idle;   

//Próxima thread das threads em user mode.
int next_thread;   
  
int current_process;
int current_thread;
int current_disk;
int current_volume;
int current_directory;   
int current_file;        
int current_terminal;
int current_dead_process;  //qual processo acabou de morrer.
int current_dead_thread;   //qual thread acabou de morrer.
//...


//cr3. current page directoory address.
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


//
// Logon.
//

int g_logged;


//
// GUI
//

//flag.
//If the kernel is in graphics mode.
int g_useGUI; 


//Messages support.
unsigned long g_next_proc;      // Procedure address.
unsigned long g_nova_mensagem;  // ?? new message ??
unsigned long g_new_message;
unsigned long g_next_app;       // Procedure adreess.
unsigned long g_proc_status;    // Procedure status.


//Drivers support.
int g_driver_video_initialized;
int g_driver_apic_initialized;
int g_driver_hdd_initialized;
int g_driver_keyboard_initialized;
int g_driver_pci_initialized;
int g_driver_rtc_initialized;
int g_driver_timer_initialized;
//...


//internal modules support.
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
int g_module_uem_initialized;             //user environment manager.
//...

// Kernel information variables.
unsigned long KernelSize;
unsigned long KernelHeapSize;
unsigned long KernelStackSize;
unsigned long KernelPages;
unsigned long KeInitPhase;
unsigned long KernelStatus;
//...


//Task support variables.

//??
unsigned long kernel_switch;


//error support.
//isso deve ir para a libc
unsigned long errno;


//
// fs support.
//


//??
//directory entries support.
char buffer_dir_entry[512];

//??Isso pode ir para outro lugar ou podemos usar uma stream.
//log buffer
char KernelLogBuffer[512];


//
// Plataform support.
//

//environment variables.
#define PLATFORM_PATH  "/Platform"
#define HARDWARE_PATH  "/Platform/Hardware"
#define FIRMWARE_PATH  "/Platform/Firmware"
#define SYSTEM_PATH    "/Platform/System"
//#define USERS_PATH     "/Platform/Users"
//...



//node od a linked list.
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


//Linked list support.
struct linkedlist_d
{
    struct node_d *head;
    struct node_d *tail;
};


//save args support. 
struct kernel_args_d
{
    unsigned long arg1;
    unsigned long arg2;
    unsigned long arg3;
    unsigned long arg4;
}; 
struct kernel_args_d KernelArgs;


//system classes.
struct system_classes_d
{
    //unsigned long Gramado; //@todo: Include this one.
    unsigned long Executive;
    unsigned long Microkernel;
    unsigned long Hal;
};
struct system_classes_d SystemClasses;


//Kernel classes.
struct kernel_classes_d
{
    struct system_classes_d *System;
    //..
};
struct kernel_classes_d KernelClasses;
//...

/*
//Kernel Manager.
struct kernel_d
{
    //
    // Kernel info.
    //

    char *name;
    unsigned long address;

    //Kernel information block.
    //struct kernel_block_d *KernelBlock;

    //struct process_d *process;

    //
    // Structs.
    //

    //struct bootmanager_d     *BootManagerBlock;  //Boot Manager.
    //struct bootloader_d      *BootLoaderBlock;   //Boot Loader.
	
    //struct system_d          *SystemBlock;       //System.
    //struct ProcessorBlock_d  *ProcessorBlock;    //Processor info.
    //...

    //
    // CPUs.
    //

    //int processorCount;
    //struct processor_descriptor_t *processorListHead;

    //kernel_args_t
    //kernel_classes_t

    //...
};
struct kernel_d *KernelInfo; 
*/
//...


/*
 **********************************************************
 * plataform_d:
 *     Os componentes básicos da máquina.
 *     As estruturas de Hardware e Software.
 *     * IMPORTANTE Essa é a estrutura BASE do kernel.
 */
struct platform_d
{
    //Name.
    char *name;

    //Type.


    //  *Hardware - Componentes do hardware.
    //  *Firmware - Componentes se software embarcados. BIOS, UEFI ...
    //  *Software - Componentes do Sistema operacional.

    struct hardware_d *Hardware;    // hal\hal.h
    struct firmware_d *Firmware;    // hal\hal.h
    struct system_d   *System;      // executive\system.h


    //kernel struct ...
    struct kernel_d *Kernel;
};
struct platform_d *Platform; 


//
// ## MAIN ##
//

int kMain ( int argc, char **argv );


//
// Initializations support.  
//


int init_runtime();         //RunTime.
void boot();                //??
void save_kernel_args();    //Save args in the structure.


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
// Error support
// 
 
void abort();    //abort.c
void die();      //system.c


//
// ke - Kernel External.
// ki - Kernel Internal.
// PS: This must to be here in the end.
//


#include <kernel/gramado/ke.h>
#include <kernel/gramado/ki.h>


//
// End.
//


