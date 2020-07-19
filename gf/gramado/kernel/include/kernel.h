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
 * * ;              kgws                ;  *
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


//#ifndef ____KERNEL_H
//#define ____KERNEL_H    


 
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
extern void dispatch_context (void);
extern void do_executa_new_task (void);
 
 

// =========================================================

// config
//#include "gramado.h"    // product. 
#include "animal.h"    // product. 
#include "config.h"     // compiling.

// globals
#include "gpa.h"
#include "gva.h"
#include "gentry.h"
#include "gdef.h"
#include "gdevice.h"
#include "gobject.h"
#include "gspin.h"
#include "gwd.h"   //whatch dogs






// libcore
#include "cdefs.h"
#include "stddef.h"
#include "types.h"


#include "types2.h"

// libcore
#include "limits.h"


// libcore
#include "kstdio.h"

// kdrivers
#include "console.h"


// libcore
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "iso646.h"
#include "signal.h"
#include "unistd.h"
#include "fcntl.h"


//#net
//#include "socket.h" //test ... tentando mudar para baixo logo apos os headers de network


#include "ioctl.h"
#include "ioctls.h"

#include "termios.h"
#include "ttydef.h"
//...


#include "mm.h"

// sysmk
#include "memmap.h" 
#include "intelmm.h"


// kdrivers
#include "display.h"


//video
#include "screen.h"
#include "video.h"
#include "virtcon.h"


// kservers
#include "fonts.h"

#include "ascii.h" 


#include "path.h"         // path.
#include "fat.h"          // fat.



// elf
#include "exec_elf.h"


// sci/fs
#include "pipe.h" 
#include "fs.h"
#include "vfs.h"


#include "prompt.h"
#include "bmp2.h"


// hal
#include "halvid.h"
#include "halmm.h"
#include "cpu.h"



#include "pte.h"
#include "tss.h" 

//hal
#include "cputypes.h"
#include "x86pte.h"
#include "x86.h"
#include "x86iv.h"
#include "x86gdt.h"
#include "cpuamd.h"
#include "detect.h"


#include "serial.h"
#include "mac.h"

#include "portsx86.h"

// kdrivers
#include "ata.h"


// syssm
#include "volume.h"
#include "disk.h"       
#include "storage.h"          


// kdrivers serial
#include "serial2.h"

// kdrivers ps2
#include "ps2.h"



// kdrivers x86
#include "pit.h"
#include "pic.h"
#include "apic.h"
#include "cpuid.h"


#include "rtc.h"
#include "floppy.h"


//x
#include "xproc.h"

//x
#include "keyboard.h"
#include "vk.h"
#include "kbdabnt2.h"
#include "ldisc.h"

#include "ide.h"
#include "pci.h"

#include "ahci.h"
#include "sata.h"


#include "usb.h"



// hal (^)
#include "up.h"
#include "mp.h"
#include "breaker.h"
#include "hal.h"




// sysmk (^)
#include "x86cont.h"


#include "ts.h"
#include "tasks.h"
#include "image.h"
#include "clone.h"
#include "process.h"
#include "thread.h"


#include "sched.h"
#include "ipc.h"
#include "ipccore.h"
#include "sem.h"



#include "queue.h"
#include "realtime.h"
#include "dispatch.h"
#include "event.h"
#include "ps.h"
#include "mk.h"



#include "kgwm.h"
#include "ws.h"
#include "window.h"
#include "menu.h"
#include "grid.h"
#include "bmp.h"
#include "line.h"
#include "terminal.h"
#include "guiconf.h"


//
// Security
//

#include "usession.h"
#include "room.h"
#include "desktop.h"
#include "user.h"


#include "logon.h"
#include "logoff.h"
#include "kgws.h"


// kdrivers (^)
#include "ttyldisc.h"
#include "ttydrv.h"
#include "tty.h"
#include "pty.h"
#include "vt.h"


#include "i8042.h"
#include "ps2mouse.h"
#include "ps2kbd.h"


//
//    ==== NETWORK ====
//

#include "connect.h" 
#include "host.h"

#include "ethernet.h"
#include "arp.h"
#include "udp.h"
#include "tcp.h"

//intel nic - network interface controller.
#include "nicintel.h"      

#include "in.h"
#include "un.h"
#include "nports.h"     //(network) Network Ports  (sw)
#include "ip.h"       //(network) IP info.      (sw)
#include "ipv4.h" 
//#include "ipv6.h" 
#include "ipv4mac.h" 
#include "icmp.h" 
//...

#include "packet.h"      // network packets.

#include "channel.h"     //(network) Channel       (sw)
#include "client.h"      //(network) Client process support. 
#include "ns.h"          //(network) Network Server.
#include "network.h"     //(network) Gerenciamento de rede.  

#include "socket.h"


//
//    ==== DEVICES ====
//


// devices
#include "devices.h"
#include "devmgr.h"       
#include "io.h"               //io.



#include "modules.h"     //module manager.
#include "debug.h"
#include "system.h"    //system manager.
#include "init.h"

#include "execve.h"  

// sysmk (^)
#include "mmglobal.h"  // Deve ficar mais acima.
#include "heap.h"      // Heap pointer support.
#include "aspace.h"    // Address Space, (data base account).
#include "dspace.h"    // Disk Space, (data base account).
#include "bank.h"      // Bank. database
#include "x86mm.h"     // mm, memory manager support.

// kservers
#include "cursor.h"
#include "messages.h"
#include "events.h"

#include "object.h"
#include "ss.h"

// profiler
#include "pints.h"


// kernel
#include "ke.h"
#include "ki.h"
#include "info.h"
#include "request.h"
#include "panic.h"
#include "reboot.h"
#include "sub.h"       // gramado sub systems



//
// sci - system call interface
//

#include "syscall.h"         //system calls.

#include "sys.h"
#include "sysio.h"
#include "syslib.h" 
#include "sysmk.h"
#include "syssm.h" 


#include "utsname.h"


//
// Globals.
//


// This is the last #include. :^)

#include "gpid.h"




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


// UP ou MP
typedef enum {

    SYSTEM_TYPE_NULL,
    SYSTEM_TYPE_UNIPROCESSOR,
    SYSTEM_TYPE_MULTIPROCESSOR

} SystemType_t;




//
// ==== current ====
//

int current_arch;


// Organização de usuários.
int current_user; 
int current_group; 

// Organização dos ambientes.
//int current_user_session;
//int current_room;
//int current_desktop;



// Organização dos processos


// [Processing time]
// Only these can read the keyboard input.
// Sometime it's the terminal.
// It's child will read into a file.
int current_process;   // Currently having the processing time.
int current_thread;    // Currently having the processing time.

int criticalsection_pid;

// [Focus]
int active_process;    // This is the process with the active thread.
int active_thread;     // This thread will receive the input.

//[Scheduler]
int next_thread;     //next user mode thread.


// Current runlevel. Used in init process.
int current_runlevel;


// Organização dos discos.
int current_disk;
int current_volume;

// Organização dos arquivos.
int current_directory;
int current_file;
int current_dead_process;
int current_dead_thread;

// Organização dos terminais
int current_tty;
int current_terminal;
//int current_pty;
//int current_pts;


//...

// ==== ====


//size of processor word.
int g_platform_type;






//se ele est'a inicializado ou nao
int dead_thread_collector_status;

// se 'e para usalo ou nao
int dead_thread_collector_flag;

//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address;



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
    //struct processor_d *processor;
    
	
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
    
    // UP or MP;
    SystemType_t system_type;

    struct hardware_d *Hardware;    // hal/hal.h
    struct firmware_d *Firmware;    // hal/hal.h
    struct system_d   *System;      // execve/sm/system.h

    //kernel struct ...
    //struct kernel_d *Kernel;
};
struct platform_d *Platform; 




#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

//#define CURRENT_ARCH_ARM      2000
//...



// inicialização do kernel, independente da arquitetura.
// See: kernel/main.c
int kernel_main (int arch_type);

//inicialização da arquitetura x86.
int x86main (void);
//...


//
// Initializations support.  
//


//RunTime.
int init_runtime (void);         


//Save args in the structure.
void save_kernel_args (void);    


// Linked list support.

void* newLinkedlist (void);
void* newNode (void);

void Removing_from_the_beginning(struct linkedlist_d *list);
void Removing_from_the_middle(struct linkedlist_d *list);
void Removing_from_the_end(struct linkedlist_d *list);


//
// Count support.
//

//?? somente o protótipo. deletar.
//unsigned long get_tick_count ();


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
 
void abort (void);    //abort.c
void die (void);      //system.c



//#endif   

//
// End.
//







