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
#include <kernel/config/gramado.h>    // product. 
#include <kernel/config/config.h>     // compiling.

// globals
#include <kernel/globals/gpa.h>
#include <kernel/globals/gva.h>
#include <kernel/globals/gentry.h>
#include <kernel/globals/gdef.h>
#include <kernel/globals/gdevice.h>
#include <kernel/globals/gobject.h>
#include <kernel/globals/gspin.h>
#include <kernel/globals/gwd.h>   //whatch dogs

// libcore
#include <kernel/syslib/libcore/sys/cdefs.h>
#include <kernel/syslib/libcore/stddef.h>
#include <kernel/syslib/libcore/types.h>
#include <kernel/syslib/libcore/sys/types.h>
#include <kernel/syslib/libcore/limits.h>


// libcore
#include <kernel/syslib/libcore/kstdio.h>

// kdrivers
#include <kernel/sysio/kdrivers/tty/console.h>


// libcore
#include <kernel/syslib/libcore/stdlib.h>
#include <kernel/syslib/libcore/string.h>
#include <kernel/syslib/libcore/ctype.h>
#include <kernel/syslib/libcore/iso646.h>
#include <kernel/syslib/libcore/signal.h>
#include <kernel/syslib/libcore/unistd.h>
#include <kernel/syslib/libcore/fcntl.h>


//#net
#include <kernel/net/socket.h>


#include <kernel/syslib/libcore/sys/ioctl.h>
#include <kernel/syslib/libcore/sys/ioctls.h>
#include <kernel/syslib/libcore/termios.h> 
#include <kernel/syslib/libcore/ttydef.h> 
//...


#include <kernel/sysmk/ps/mm/mm.h>

// sysmk
#include <kernel/sysmk/ps/mm/x86/memmap.h> 
#include <kernel/sysmk/ps/mm/x86/intelmm.h>


// kdrivers
#include <kernel/sysio/kdrivers/x/display.h>
#include <kernel/sysio/kdrivers/x/video/screen.h>
#include <kernel/sysio/kdrivers/x/video/video.h>
#include <kernel/sysio/kdrivers/x/video/virtcon.h>

// kservers
#include <kernel/sysio/kservers/kgws/kgws/fonts.h>
#include <kernel/sysio/kservers/ascii.h>   
#include <kernel/sysio/kservers/fs/path.h>                // path.
#include <kernel/sysio/kservers/fs/fat.h>                 // fat.


// sci/fs
#include <kernel/sci/fs/pipe.h> 
#include <kernel/sci/fs/fs.h> 
#include <kernel/sci/fs/vfs.h>  


#include <kernel/sysio/kservers/kgws/kgws/prompt.h>
#include <kernel/sysio/kservers/kgws/kgws/bmp2.h>


// hal
#include <kernel/sysio/hal/screen.h> 
#include <kernel/sysio/hal/video.h>
#include <kernel/sysio/hal/memory.h>
#include <kernel/sysio/hal/cpu.h>  
#include <kernel/sysio/hal/arch/i386/pte.h> 
#include <kernel/sysio/hal/arch/i386/tss.h> 
#include <kernel/sysio/hal/arch/x86/cputypes.h> 
#include <kernel/sysio/hal/arch/x86/pte.h> 
#include <kernel/sysio/hal/arch/x86/x86.h> 
#include <kernel/sysio/hal/arch/x86/x86iv.h> 
#include <kernel/sysio/hal/arch/x86/x86gdt.h>
#include <kernel/sysio/hal/arch/amd/cpuamd.h>  
#include <kernel/sysio/hal/arch/detect.h>  
#include <kernel/sysio/hal/serial.h>        
#include <kernel/sysio/hal/mac.h>                             
#include <kernel/sysio/hal/arch/x86/portsx86.h>

// kdrivers
#include <kernel/sysio/kdrivers/ide/ata.h>


// syssm
#include <kernel/syssm/storage/volume.h>
#include <kernel/syssm/storage/disk.h>          
#include <kernel/syssm/storage/storage.h>          



// kdrivers serial
#include <kernel/sysio/kdrivers/serial/serial.h>

// kdrivers ps2
#include <kernel/sysio/kdrivers/ps2/ps2.h>

// kdrivers x86
#include <kernel/sysio/kdrivers/arch/x86/pit.h>
#include <kernel/sysio/kdrivers/arch/x86/pic.h>
#include <kernel/sysio/kdrivers/arch/x86/apic.h>
#include <kernel/sysio/kdrivers/arch/x86/cpuid.h>

// kdrivers rtc
#include <kernel/sysio/kdrivers/rtc/rtc.h>

//floppy
#include <kernel/sysio/kdrivers/floppy/floppy.h>

//x
#include <kernel/sysio/kdrivers/x/xproc.h>
#include <kernel/sysio/kdrivers/x/i8042/keyboard.h>
#include <kernel/sysio/kdrivers/x/i8042/vk.h>
#include <kernel/sysio/kdrivers/x/i8042/kbdabnt2.h>
#include <kernel/sysio/kdrivers/x/i8042/ldisc.h>
#include <kernel/sysio/kdrivers/ide/ide.h>
#include <kernel/sysio/kdrivers/pci/pci.h>
#include <kernel/sysio/kdrivers/ahci/ahci.h>
#include <kernel/sysio/kdrivers/ahci/sata.h>
#include <kernel/sysio/kdrivers/usb/usb.h>



// hal (^)
#include <kernel/sysio/hal/up.h>
#include <kernel/sysio/hal/mp.h>
#include <kernel/sysio/hal/breaker.h>
#include <kernel/sysio/hal/hal.h>




// sysmk (^)
#include <kernel/sysmk/ps/arch/x86/x86cont.h>
#include <kernel/sysmk/ps/ts.h>
#include <kernel/sysmk/ps/tasks.h>
#include <kernel/sysmk/ps/image.h>

#include <kernel/sysmk/ps/clone.h>
#include <kernel/sysmk/ps/process.h>
#include <kernel/sysmk/ps/thread.h>

#include <kernel/sysmk/ps/sched/sched.h>
#include <kernel/sysmk/ps/ipc/ipc.h>
#include <kernel/sysmk/ps/ipc/ipccore.h>
#include <kernel/sysmk/ps/ipc/sem.h>
#include <kernel/sysmk/ps/queue.h>
#include <kernel/sysmk/ps/realtime.h>
#include <kernel/sysmk/ps/dispatch.h>
#include <kernel/sysmk/ps/event.h>
#include <kernel/sysmk/ps/ps.h>
#include <kernel/sysmk/mk.h>


// kservers (v)
#include <kernel/sysio/kservers/kgwm/kgwm.h>
#include <kernel/sysio/kservers/kgws/kgws/ws.h>




#include <kernel/sysio/kservers/kgws/kgws/window.h>
#include <kernel/sysio/kservers/kgws/kgws/menu.h>
#include <kernel/sysio/kservers/kgws/kgws/grid.h>
#include <kernel/sysio/kservers/kgws/kgws/bmp.h>
#include <kernel/sysio/kservers/kgws/terminal/line.h>
#include <kernel/sysio/kservers/kgws/terminal/terminal.h>
#include <kernel/sysio/kservers/kgws/kgws/guiconf.h>


//
// Security
//

#include <kernel/security/usession.h>
#include <kernel/security/room.h>
#include <kernel/security/desktop.h>
#include <kernel/security/user.h>


#include <kernel/sysio/kservers/kgws/logon/logon.h>
#include <kernel/sysio/kservers/kgws/logoff/logoff.h>
#include <kernel/sysio/kservers/kgws/kgws.h>


// kdrivers (^)
#include <kernel/sysio/kdrivers/tty/ttyldisc.h>
#include <kernel/sysio/kdrivers/tty/ttydrv.h>
#include <kernel/sysio/kdrivers/tty/tty.h>
#include <kernel/sysio/kdrivers/tty/pty.h>


#include <kernel/sysio/kdrivers/tty/vt.h>

#include <kernel/sysio/kdrivers/x/i8042/i8042.h>
#include <kernel/sysio/kdrivers/x/i8042/ps2mouse.h>
#include <kernel/sysio/kdrivers/x/i8042/ps2kbd.h>

//#net
#include <kernel/net/network/connect.h> 
#include <kernel/net/host/host.h>    
#include <kernel/net/ethernet/ethernet.h>


#include <kernel/net/ipv4/arp.h>
#include <kernel/net/ipv4/udp.h>
#include <kernel/net/ipv4/tcp.h>


// #kserver - nic intel
//intel nic - network interface controller.
#include <kernel/sysio/kdrivers/network/intel.h>       


// #net
#include <kernel/net/netinet/in.h>
#include <kernel/net/sys/un.h>
#include <kernel/net/network/nports.h>      //(network) Network Ports  (sw)
#include <kernel/net/ipv4/ip.h>          //(network) IP info.      (sw)
#include <kernel/net/ipv4/ipv4.h> 
//#include <kernel/net/ipv6.h> 
#include <kernel/net/ipv4/mac.h> 
#include <kernel/net/ipv4/icmp.h> 
#include <kernel/net/network/channel.h>     //(network) Channel       (sw)
#include <kernel/net/network/client.h>      //(network) Client process support. 
#include <kernel/net/network/ns.h>          //(network) Network Server.
#include <kernel/net/network/network.h>     //(network) Gerenciamento de rede.  



// devices
#include <kernel/sysio/devices.h>
#include <kernel/sysio/devmgr.h>        


// execve (v)
#include <kernel/syssm/execve/sm/install.h>


// io
#include <kernel/sysio/io.h>                  //io.



// execve
#include <kernel/syssm/execve/sm/modules.h>             //module manager.


// debug
#include <kernel/syssm/debug/debug.h>


#include <kernel/syssm/execve/sm/system.h>              //system manager.
#include <kernel/syssm/execve/sm/init.h>
#include <kernel/syssm/execve/execve.h>    


// sysmk (^)
#include <kernel/sysmk/ps/mm/x86/mmglobal.h>  // Deve ficar mais acima.
#include <kernel/sysmk/ps/mm/x86/heap.h>      // Heap pointer support.
#include <kernel/sysmk/ps/mm/x86/aspace.h>    // Address Space, (data base account).
#include <kernel/sysmk/ps/mm/x86/dspace.h>    // Disk Space, (data base account).
#include <kernel/sysmk/ps/mm/x86/bank.h>      // Bank. database
#include <kernel/sysmk/ps/mm/x86/x86mm.h>     // mm, memory manager support.



// kservers
#include <kernel/sysio/kservers/cursor.h>
#include <kernel/sysio/kservers/messages.h>
#include <kernel/sysio/kservers/events.h>


// ob
#include <kernel/syssm/ob/object.h>

// execve
#include <kernel/syssm/execve/ss.h>


// profiler
#include <kernel/profiler/pints.h>






// kernel
#include <kernel/ke.h>
#include <kernel/ki.h>
#include <kernel/info.h>
#include <kernel/request.h>
#include <kernel/panic.h>
#include <kernel/reboot.h>
#include <kernel/sub.h>       // gramado sub systems



//
// sci - system call interface
//

#include <kernel/sci/syscall.h>            //system calls.


// HERE !
#include <kernel/sci/sys/sys.h> 
#include <kernel/sysio/sysio.h> 
#include <kernel/syslib/syslib.h> 
#include <kernel/sysmk/sysmk.h> 
#include <kernel/syssm/syssm.h> 




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
int current_process;
int current_thread;
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




#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

//#define CURRENT_ARCH_ARM      2000
//...



// inicialização do kernel, independente da arquitetura.
// See: kernel/main.c
int kernel_main (int arch_type);

//inicialização da arquitetura x86.
void x86main (void);
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



//
// End.
//


