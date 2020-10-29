/*
 * File: kernel.h
 * 
 *     This is the main header for the bse kernel.
 * 
 * History:
 *     2013 - Created by Fred Nora.
 *     2014~2018 - Resision.
 */


// Modes.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...



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
 
 
//#test 
//typedef int (*fn_ptr)();


// =========================================================



// config
#include "config/version.h"    // Product. 
#include "config/u.h"          // User
#include "config/config.h"     // Compiling.


// gramado
#include "gramado/limits.h"

// globals
#include "globals/gpa.h"
#include "globals/gva.h"
#include "globals/gentry.h"
#include "globals/gdef.h"
#include "globals/gdevice.h"
#include "globals/gobject.h"
#include "globals/gspin.h"
#include "globals/gwd.h"   //whatch dogs


// klibc
#include "klibc/cdefs.h"
#include "klibc/stddef.h"
#include "klibc/types.h"
#include "klibc/types2.h"
#include "klibc/limits.h"
#include "klibc/kstdio.h"
#include "klibc/stdlib.h"
#include "klibc/string.h"
#include "klibc/ctype.h"
#include "klibc/iso646.h"
#include "klibc/signal.h"
#include "klibc/unistd.h"
#include "klibc/fcntl.h"
#include "klibc/ioctl.h"
#include "klibc/ioctls.h"
#include "klibc/termios.h"
#include "klibc/ttydef.h"



// memory management support.
#include "mm/mm.h"
#include "mm/memmap.h" 
#include "mm/intelmm.h"



// ws -
// #view presentation output.
#include "ws/view/display.h"
#include "ws/view/screen.h"
#include "ws/view/video.h"


//
// Render
//

#include "render/r_render.h"



// #model. data model.
#include "ws/model/fonts.h"
#include "ws/model/ascii.h" 


//tty
#include "tty/virtcon.h"


// fs
#include "fs/path.h"         // path.
#include "fs/fat.h"          // fat16.
#include "fs/inode.h"
#include "fs/exec_elf.h"
#include "fs/pipe.h" 
#include "fs/fs.h"
#include "fs/vfs.h"


// ws - 
// view - input and presentation
#include "ws/view/prompt.h"

// view - showing the data.
#include "ws/view/bmp2.h"



// hal
#include "hal/portsx86.h"
#include "hal/halvid.h"
#include "hal/halmm.h"
#include "hal/cpu.h"
#include "hal/pte.h"
#include "hal/tss.h" 
#include "hal/cputypes.h"
#include "hal/x86pte.h"
#include "hal/x86.h"
#include "hal/x86iv.h"
#include "hal/x86gdt.h"
#include "hal/cpuamd.h"
#include "hal/detect.h"


// drivers
#include "serial.h"


//todo: podemos mover isso de lugar para perto de net/
#include "net/mac.h"



// storage
#include "storage/floppy.h"
#include "storage/ata.h"
#include "storage/super.h"
#include "storage/volume.h"
#include "storage/disk.h"  
#include "storage/storage.h" 



// ws - window server, and beyond
// ps2 controller.
#include "ws/view/ps2.h"



// hal
#include "hal/pit.h"
#include "hal/pic.h"
#include "hal/apic.h"
#include "hal/cpuid.h"
#include "hal/rtc.h"



// ws - window server
// inputs
#include "ws/view/xproc.h"
#include "ws/view/keyboard.h"
#include "ws/view/mouse.h"
#include "ws/view/vk.h"
#include "ws/view/kbdabnt2.h"
// #view. drawing routines.
#include "ws/view/ldisc.h"


//storage (^)
#include "storage/ide.h"



//pci
#include "hal/pci.h"


//storage (^)
#include "storage/ahci.h"
#include "storage/sata.h"


//usb bus.
#include "usb.h"


// hal (^)
#include "hal/up.h"
#include "hal/mp.h"
#include "hal/breaker.h"
#include "hal/hal.h"



// ps
#include "ps/x86cont.h"
#include "ps/ts.h"
#include "ps/tasks.h"
#include "ps/image.h"
#include "ps/clone.h"
#include "ps/process.h"
#include "ps/thread.h"
#include "ps/sched.h"
#include "ps/ipc.h"
#include "ps/ipccore.h"
#include "ps/sem.h"
#include "ps/queue.h"
#include "ps/realtime.h"
#include "ps/dispatch.h"
#include "ps/event.h"
#include "ps/ps.h"
#include "ps/mk.h"



// ws - 
// model business logic
#include "ws/model/kgwm.h"
#include "ws/model/ws.h"

// #view - designers
#include "ws/view/window.h"
#include "ws/view/menu.h"
#include "ws/view/pbar.h"
#include "ws/view/bmp.h"
#include "ws/view/line.h"

// #view. presentation
#include "ws/view/terminal.h"
#include "ws/view/guiconf.h"


//
// == Security ===============================
//

#include "security/usession.h"
#include "security/room.h"
#include "security/desktop.h"
#include "security/user.h"
#include "security/security.h"



// ws - window server, and beyond
#include "ws/logon.h"
#include "ws/logoff.h"

// model. business logic
#include "ws/model/kgws.h"




// tty
#include "tty/ttyldisc.h"
#include "tty/ttydrv.h"
#include "tty/tty.h"
#include "tty/pty.h"
#include "tty/vt.h"
#include "tty/console.h"


// ws - 
// view - input support.
#include "ws/view/i8042.h"
#include "ws/view/ps2mouse.h"
#include "ws/view/ps2kbd.h"



//
//  ==== NETWORK ====
//

#include "net/connect.h" 
#include "net/host.h"
#include "net/ethernet.h"
#include "net/arp.h"
#include "net/udp.h"
#include "net/tcp.h"
#include "net/nicintel.h"    //intel nic - network interface controller.
#include "net/in.h"
#include "net/un.h"
#include "net/nports.h"     //(network) Network Ports  (sw)
#include "net/ip.h"         //(network) IP info.      (sw)
#include "net/ipv4.h" 
//#include "net/ipv6.h" 
#include "net/ipv4mac.h" 
#include "net/icmp.h" 
#include "net/packet.h"      // network packets.
#include "net/channel.h"     //(network) Channel       (sw)
#include "net/client.h"      //(network) Client process support. 
#include "net/ns.h"          //(network) Network Server.
#include "net/network.h"     //(network) Gerenciamento de rede.  
#include "net/socket.h"      //last always



//
// ==== DEVICES ====
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


// mm
#include "mm/mmglobal.h"  // Deve ficar mais acima.
#include "mm/heap.h"      // Heap pointer support.
#include "mm/aspace.h"    // Address Space, (data base account).

// storage ?
#include "dspace.h"    // Disk Space, (data base account). storage stuff

// mm
#include "mm/bank.h"      // Bank. database
#include "mm/x86mm.h"     // mm, memory manager support.



// ws - 
// view. input support.
#include "ws/view/cursor.h"


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
#include "reboot.h"
#include "sub.h"       // gramado sub systems


#include "utsname.h"


// Globals. PIDs support.

#include "gpid.h"


//
// sci - system call interface
//

// All the functions in this folder can be called
// by the ring3 apps via system call.
// This is the last #include. :^)

#include "sci/syscall.h"        
#include "sci/sys.h"



//
// si - services interfce
//

#include "si/sifs.h"
#include "si/sins.h"
#include "si/siws.h"



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

int current_mode;

int current_arch;


// Organização de usuários.
int current_user; 
int current_group; 



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

// panic without clean
void panic ( const char *format, ... );   //panic.c

// clean and panic.
void panic2 ( const char *format, ... );   //panic.c

void abort (void);    //abort.c
void die (void);      //system.c



//
// End.
//







