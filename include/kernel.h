/*
 * Gramado Operating System - The main header for the kernel base. 
 * (c) Coppyright 2019 - Fred Nora.
 *
 * File: kernel.h 
 *
 * This is the header file kernel base.
 * This is a hybrid kernel.
 *
 * The base kernel has 4 layers: 
 *     HAL, MICROKERNEL, EXECUTIVE and GRAMADO.
 *
 * *****************************************
 * *                                       *
 * * ;----------------------------------;  *
 * * ;                                  ;  *
 * * ;               kgws               ;  *
 * * ;                                  ;  *
 * * ;----------------------------------;  *
 * * ;----------------------------------;  *
 * * ;                                  ;  *
 * * ;             execve               ;  *
 * * ;                                  ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * * ;----------------------------------;  *
 * * ;              mk                  ;  *
 * * ;----------------------------------;  *
 * *                                       *
 * * ;----------------------------------;  *
 * * ;              hal                 ;  *
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
 

/* setup product */ 
#include <kernel/config/gramado.h> 
 
/* setup compiling stuff */ 
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


//layers
#define KERNEL      0
#define GRAMADO     1   //1 kgws
#define EXECUTIVE   2   //2
#define MICROKERNEL 3   //3
#define HAL         4   //4



//IOPL constants.
#define KernelMode 0
#define UserMode   3
#define RING0 0
#define RING1 1
#define RING2 2
#define RING3 3





//Kernel status constants.
#define  KERNEL_NULL          0
#define  KERNEL_INITIALIZED   1
#define  KERNEL_ABORTED       2
#define  KERNEL_INICIALIZADO  KERNEL_INITIALIZED
#define  KERNEL_ABORTADO      KERNEL_ABORTED



//#define LOBYTE(w) ((char)(((unsigned long )(w)) & 0xff))
//#define HIBYTE(w) ((char)((((unsigned long)(w)) >> 8) & 0xff))


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



// 
//  ## klibc ##
//

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
#include <kernel/fcntl.h>
#include <kernel/sys/types.h>
#include <kernel/socket.h>
//...
//--


// ## hardware ## 

#include <kernel/gramado/kdrivers/intel.h>

#include <kernel/gramado/mk/pc/mm/memory2.h>

#include <kernel/gramado/kdrivers/cpuid.h>

#include <kernel/gramado/kdrivers/screen.h>
#include <kernel/gramado/kdrivers/video.h>

#include <kernel/gramado/kdrivers/rtc2.h>
//...


#include <kernel/gramado/kservers/kgws/kgws/fonts.h>

#include <kernel/gramado/kservers/ascii.h>   

#include <kernel/gramado/kservers/fs/fs2.h> 

#include <kernel/gramado/kservers/kgws/kgws/prompt.h>
#include <kernel/gramado/kservers/kgws/kgws/bmp2.h>
//...


//
// MICROKERNEL (3)
//


// Global first.
//Memory Map - address.
#include <kernel/gramado/mk/pc/mm/x86/memmap.h>            



//execve
//Disk Map - sectors.
#include <kernel/gramado/execve/sm/disk/diskmap.h>        


//
// HAL (4)
//

#include <kernel/gramado/hal/screen.h> 
#include <kernel/gramado/hal/video.h>
#include <kernel/gramado/hal/memory.h>
#include <kernel/gramado/hal/cpu.h>  

#include <kernel/gramado/hal/arch/i386/pte.h> 
#include <kernel/gramado/hal/arch/i386/tss.h> 

#include <kernel/gramado/hal/arch/x86/cputypes.h> 
#include <kernel/gramado/hal/arch/x86/pte.h> 
#include <kernel/gramado/hal/arch/x86/x86.h> 
#include <kernel/gramado/hal/arch/x86/x86iv.h> 
#include <kernel/gramado/hal/arch/x86/x86gdt.h>

#include <kernel/gramado/hal/arch/amd/cpuamd.h>  
#include <kernel/gramado/hal/arch/detect.h>  
#include <kernel/gramado/hal/serial.h>        
#include <kernel/gramado/hal/mac.h>                             
#include <kernel/gramado/hal/arch/x86/portsx86.h>


//execve
//disk1 - nelson
//#include <kernel/3rdparty/sirius.h>

#include <kernel/gramado/kdrivers/ide/ata.h>

#include <kernel/gramado/execve/sm/disk/disk.h>          
#include <kernel/gramado/execve/sm/disk/volume.h>

#include <kernel/gramado/kdrivers/serial/serial.h>


#include <kernel/gramado/kdrivers/ps2/ps2.h>


#include <kernel/gramado/kdrivers/timer.h>


#include <kernel/gramado/kdrivers/pic.h>
#include <kernel/gramado/kdrivers/apic.h>

#include <kernel/gramado/kdrivers/rtc.h>


#include <kernel/gramado/kdrivers/floppy/floppy.h>


#include <kernel/gramado/kdrivers/i8042/keyboard.h>
#include <kernel/gramado/kdrivers/i8042/vk.h>
#include <kernel/gramado/kdrivers/i8042/kbdabnt2.h>


#include <kernel/gramado/execve/ldisc/ldisc.h>


#include <kernel/gramado/kdrivers/ide/ide.h>


#include <kernel/gramado/kdrivers/pci/pci.h>


#include <kernel/gramado/kdrivers/ahci/ahci.h>
#include <kernel/gramado/kdrivers/ahci/sata.h>


#include <kernel/gramado/kdrivers/usb/usb.h>
//...



//
// HAL (4)
//

//device manager.
#include <kernel/gramado/hal/device.h>
#include <kernel/gramado/hal/hal.h>
//--


/*
 * MICROKERNEL (3)
 */


//++
//mk
#include <kernel/gramado/mk/arch/x86/x86cont.h>
#include <kernel/gramado/mk/pc/ts.h>
#include <kernel/gramado/mk/pc/tasks.h>
#include <kernel/gramado/mk/pc/image.h>
#include <kernel/gramado/mk/pc/process.h>
#include <kernel/gramado/mk/pc/thread.h>
#include <kernel/gramado/mk/pc/sched/sched.h>
#include <kernel/gramado/mk/pc/ipc/ipc.h>

//test
#include <kernel/gramado/mk/pc/ipc/ipccore.h>

#include <kernel/gramado/mk/pc/ipc/sem.h>
#include <kernel/gramado/mk/pc/queue.h>
#include <kernel/gramado/mk/pc/realtime.h>
#include <kernel/gramado/mk/pc/dispatch.h>
#include <kernel/gramado/mk/pc/event.h>
#include <kernel/gramado/mk/pc/pc.h>
#include <kernel/gramado/mk/mk.h>
//--


//
// GRAMADO (KGWS) Kernel gramado window server
//

#include <kernel/gramado/kservers/kgws/kgws/ws.h>
#include <kernel/gramado/kservers/kgws/user/usession.h>
#include <kernel/gramado/kservers/kgws/user/room.h>
#include <kernel/gramado/kservers/kgws/user/desktop.h>
#include <kernel/gramado/kservers/kgws/kgws/window.h>
#include <kernel/gramado/kservers/kgws/kgws/menu.h>
#include <kernel/gramado/kservers/kgws/kgws/grid.h>
#include <kernel/gramado/kservers/kgws/kgws/bmp.h>
#include <kernel/gramado/kservers/kgws/terminal/line.h>
#include <kernel/gramado/kservers/kgws/terminal/terminal.h>
#include <kernel/gramado/kservers/kgws/terminal/console.h>
#include <kernel/gramado/kservers/kgws/kgws/guiconf.h>
#include <kernel/gramado/kservers/kgws/user/user.h>
#include <kernel/gramado/kservers/kgws/logon/logon.h>
#include <kernel/gramado/kservers/kgws/logoff/logoff.h>
#include <kernel/gramado/kservers/kgws/kgws.h>


//execve
#include <kernel/gramado/execve/sm/install.h>
#include <kernel/gramado/execve/sm/init.h>


#include <kernel/gramado/kdrivers/tty/tty.h>


#include <kernel/gramado/kdrivers/i8042/i8042.h>
#include <kernel/gramado/kdrivers/i8042/ps2mouse.h>
#include <kernel/gramado/kdrivers/i8042/ps2kbd.h>

#include <kernel/gramado/kdrivers/network/host.h>        //host info.
#include <kernel/gramado/kdrivers/network/ethernet.h>
#include <kernel/gramado/kdrivers/network/arp.h>
#include <kernel/gramado/kdrivers/network/intel.h>       //intel nic - network interface controller.
#include <kernel/gramado/kdrivers/network/nports.h>      //(network) Network Ports  (sw)
#include <kernel/gramado/kdrivers/network/nsocket.h>     //(network) Sockets info. (sw) (not libc)
#include <kernel/gramado/kdrivers/network/ip.h>          //(network) IP info.      (sw)
#include <kernel/gramado/kdrivers/network/channel.h>     //(network) Channel       (sw)
#include <kernel/gramado/kdrivers/network/client.h>      //(network) Client process support. 
#include <kernel/gramado/kdrivers/network/ns.h>          //(network) Network Server.
#include <kernel/gramado/kdrivers/network/network.h>     //(network) Gerenciamento de rede. 


#include <kernel/gramado/kservers/fs/fs.h>                  //fs.

#include <kernel/gramado/kservers/vfs/vfs.h>                //vfs.


#include <kernel/gramado/execve/sm/io.h>                  //io.
#include <kernel/gramado/execve/sci/syscall.h>            //system calls.
#include <kernel/gramado/execve/sm/modules.h>             //module manager.
#include <kernel/gramado/execve/sm/debug.h>
#include <kernel/gramado/execve/sm/sys.h>                 //system calls 2.
#include <kernel/gramado/execve/sm/system.h>              //system manager.


#include <kernel/gramado/kdrivers/dd.h>


#include <kernel/gramado/execve/execve.h>        

//
// MICROKERNEL (3)
//

//mm
#include <kernel/gramado/mk/pc/mm/x86/mmglobal.h>
#include <kernel/gramado/mk/pc/mm/x86/heap.h>          //Heap pointer support.
#include <kernel/gramado/mk/pc/mm/x86/aspace.h>        //Address Space, (data base account).
#include <kernel/gramado/mk/pc/mm/x86/dspace.h>        //Disk Space, (data base account).
#include <kernel/gramado/mk/pc/mm/x86/bank.h>          //Bank. database
#include <kernel/gramado/mk/pc/mm/x86/mm.h>            //mm, memory manager support.


//
// Some other stuff.
//

//Cursor support.
#include <kernel/gramado/kservers/cursor.h>

//Kernel request support.
#include <kernel/gramado/request.h>

//Kernel messages support.
#include <kernel/gramado/kservers/messages.h>

//Object Manager support.
#include <kernel/gramado/execve/object.h>

//system signals. (SS)
#include <kernel/gramado/execve/ss.h>

#include <kernel/gramado/kservers/events.h>

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


//true ring 0 idle tread id.
//can't be destroied.
//stay blocked if we have more then one thread.
int idle;

//next user mode thread.
int next_thread;

int current_process;
int current_thread;
int current_disk;
int current_volume;
int current_directory;
int current_file;
int current_terminal;
int current_dead_process;
int current_dead_thread;
//...


//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address;



//processors count
int processors_count;

//all processors's structs.
unsigned long processorsList[32];

//processors in idle state.
int idleprocessorList[32];

//processors in active state.
int activeprocessorList[32];



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


//#bugbug
//move this to kernel (ring 0) crt support.
//error support.
unsigned long errno;


//
// fs support.
//

//directory entries support.
//char buffer_dir_entry[512];

//log buffer
//char KernelLogBuffer[512];



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
    //struct tagProcessor *processor;
    
	
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
 *     Basic machine components. Hardware and Software. */

struct platform_d
{
    char *name;
	
    struct hardware_d *Hardware;    // hal/hal.h
    struct firmware_d *Firmware;    // hal/hal.h
    struct system_d   *System;      // execve/sm/system.h

    //kernel struct ...
    //struct kernel_d *Kernel;
};
struct platform_d *Platform; 


// Initializations support.  
int init_runtime();         //RunTime.
void boot();                //??
void save_kernel_args();    //Save args in the structure.


// Linked list support.
void* newLinkedlist();
void* newNode();
void Removing_from_the_beginning(struct linkedlist_d *list);
void Removing_from_the_middle(struct linkedlist_d *list);
void Removing_from_the_end(struct linkedlist_d *list);


//
// Count support.
//

unsigned long get_tick_count ();


//
// Delay support.
//

void sleep (unsigned long ms);


//
// Finalizations support.
//

void faults (unsigned long number);



//
// Error support
// 
 
void abort ();    //abort.c
void die ();      //system.c


// ke - Kernel External.
// ki - Kernel Internal.
// PS: This must to be here in the end.

#include <kernel/gramado/ke.h>
#include <kernel/gramado/ki.h>


//
// End.
//


