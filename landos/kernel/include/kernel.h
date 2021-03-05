/*
 * File: kernel.h
 * 
 *     This is the main header for the bse kernel.
 * 
 * History:
 *     2013 - Created by Fred Nora.
 *     2014~2018 - Resision.
 */


//
// == gramado modes =================================================
//

// See: 'current_mode'.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...

//
// == input modes ==================================================
//

// See: 'current_input_mode'.


// ================
// fred:
// Talvez o bom mesmo seja usarmos apenas o input mode tty.
// Nesse caso para todos os tipos de aplicativo eles precisaram ler
// a tty para pegar o input no seu modo raw.
// Todo esse trabalho so existe porque o kernel esta construindo
// o evento de input ao inves de mandar o input no formato raw.
// ================


// Setup input mode.
// This is the mode used when we do not have a 
// loadble ring3 window server.
// Send the input event to the thread associated with the
// window with focus in the window server embedded inside the kernel.
#define INPUT_MODE_SETUP  1000

// tty input mode.
// In this mode we're gonna send the input to the tty buffer.
// This way a virtual terminal can share the input with its client.
#define INPUT_MODE_TTY    2000

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
// ...


//#test 
//typedef int (*fn_ptr)();


// =========================================================


// (NT)
// Land OS headers.

// oh boy
#include "land/0boy/0boy.h"

// config
#include "land/0config/version.h"    // Product. 
#include "land/0config/u.h"          // User
#include "land/0config/config.h"     // Compiling.

// globals
#include "land/0globals/limits.h"
#include "land/0globals/gpa.h"
#include "land/0globals/gva.h"
#include "land/0globals/gentry.h"
#include "land/0globals/gdef.h"
#include "land/0globals/gdevice.h"
#include "land/0globals/gobject.h"
#include "land/0globals/gspin.h"
#include "land/0globals/ginput.h"   // input manager support.
#include "land/0globals/gwd.h"   //whatch dogs


// rtl 
// Inside the base kernel
#include "rtl/cdefs.h"
#include "rtl/stddef.h"
#include "rtl/types.h"
#include "rtl/types2.h"
#include "rtl/limits.h"
#include "rtl/kstdio.h"
#include "rtl/stdlib.h"
#include "rtl/string.h"
#include "rtl/ctype.h"
#include "rtl/iso646.h"
#include "rtl/signal.h"
#include "rtl/unistd.h"
#include "rtl/fcntl.h"
#include "rtl/ioctl.h"
#include "rtl/ioctls.h"
#include "rtl/termios.h"
#include "rtl/ttydef.h"



// memory management support.
#include "land/mm/mm.h"
#include "land/mm/memmap.h" 
#include "land/mm/intelmm.h"


// rawgr -
// #view presentation output.
#include "hal/dev/tty/vt/rawgr/view/display.h"
#include "hal/dev/tty/vt/rawgr/view/screen.h"
#include "hal/dev/tty/vt/rawgr/view/video.h"


// Render
#include "hal/dev/tty/vt/render/r_render.h"


// #model. data model.
#include "hal/dev/tty/vt/rawgr/model/fonts.h"
#include "hal/dev/tty/vt/rawgr/model/ascii.h" 


// fs
#include "rtl/fs/path.h"       // path.
#include "rtl/fs/fat.h"        // fat16.
#include "rtl/fs/fat_lfn.h"    // fat16 lfn.
#include "rtl/fs/inode.h"
#include "rtl/fs/exec_elf.h"
#include "rtl/fs/pipe.h" 
#include "rtl/fs/fs.h"
#include "rtl/fs/vfs.h"


// rawgr - 
// view - input and presentation
#include "hal/dev/tty/vt/rawgr/view/prompt.h"

// view - showing the data.
#include "hal/dev/tty/vt/rawgr/view/bmp2.h"



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
#include "hal/dmi.h"
#include "hal/detect.h"


#include "hal/dev/tty/serial.h"


//todo: podemos mover isso de lugar para perto de net/
#include "rtl/net/mac.h"



// hal/dev/blkdev
#include "hal/dev/blkdev/floppy.h"
#include "hal/dev/blkdev/ata.h"
#include "hal/dev/blkdev/super.h"
#include "hal/dev/blkdev/volume.h"
#include "hal/dev/blkdev/disk.h"  
#include "hal/dev/blkdev/storage.h" 

// hal
#include "hal/pit.h"
#include "hal/pic.h"
#include "hal/apic.h"
#include "hal/cpuid.h"
#include "hal/rtc.h"



// rawgr - window server
// inputs
#include "hal/dev/tty/vt/rawgr/view/xproc.h"
#include "hal/dev/tty/vt/rawgr/view/keyboard.h"
#include "hal/dev/tty/vt/rawgr/view/mouse.h"
#include "hal/dev/tty/vt/rawgr/view/vk.h"
#include "hal/dev/tty/vt/rawgr/view/kbdabnt2.h"

// #view. drawing routines.
#include "hal/dev/tty/vt/rawgr/view/ldisc.h"

//storage (^)
#include "hal/dev/blkdev/ide.h"


//pci
//#include "hal/bus/isa.h"   //#todo
#include "hal/bus/pci.h"

//storage (^)
#include "hal/dev/blkdev/ahci.h"
#include "hal/dev/blkdev/sata.h"

#include "hal/bus/usb.h"


#include "hal/up.h"
#include "hal/mp.h"
#include "hal/breaker.h"
#include "hal/hal.h"


// ps
#include "land/ps/x86cont.h"
#include "land/ps/ts.h"
#include "land/ps/tasks.h"
#include "land/ps/image.h"
#include "land/ps/clone.h"
#include "land/ps/process.h"
#include "land/ps/thread.h"
#include "land/ps/sched.h"
#include "land/ps/ipc.h"
#include "land/ps/ipccore.h"
#include "land/ps/sem.h"
#include "land/ps/queue.h"
#include "land/ps/realtime.h"
#include "land/ps/dispatch.h"
#include "land/ps/event.h"
#include "land/ps/ps.h"
#include "land/ps/mk.h"



// rawgr - 
// model business logic
#include "hal/dev/tty/vt/rawgr/model/kgwm.h"
#include "hal/dev/tty/vt/rawgr/model/ws.h"

// #view - designers
#include "hal/dev/tty/vt/rawgr/view/window.h"
#include "hal/dev/tty/vt/rawgr/view/menu.h"
#include "hal/dev/tty/vt/rawgr/view/pbar.h"
#include "hal/dev/tty/vt/rawgr/view/bmp.h"
#include "hal/dev/tty/vt/rawgr/view/line.h"

// #view. presentation
#include "hal/dev/tty/vt/rawgr/view/terminal.h"
#include "hal/dev/tty/vt/rawgr/view/guiconf.h"


//
// == Security ===============================
//

#include "land/security/usession.h"
#include "land/security/room.h"
#include "land/security/desktop.h"
#include "land/security/user.h"
#include "land/security/security.h"


// rawgr - window server, and beyond
#include "hal/dev/tty/vt/rawgr/logon.h"
#include "hal/dev/tty/vt/rawgr/logoff.h"

// model. business logic
#include "hal/dev/tty/vt/rawgr/model/kgws.h"


// tty
#include "hal/dev/tty/ttyldisc.h"
#include "hal/dev/tty/ttydrv.h"
#include "hal/dev/tty/tty.h"
#include "hal/dev/tty/pty.h"


#include "hal/dev/tty/vt/vt.h"
#include "hal/dev/tty/vt/console.h"


// =============================
// rawgr - i8042 ps2 controller.
#include "hal/dev/tty/vt/rawgr/view/i8042/i8042.h"
#include "hal/dev/tty/vt/rawgr/view/i8042/ps2mouse.h"
#include "hal/dev/tty/vt/rawgr/view/i8042/ps2kbd.h"
#include "hal/dev/tty/vt/rawgr/view/i8042/ps2.h"




//
//  ==== NETWORK ====
//

#include "rtl/net/connect.h" 
#include "rtl/net/host.h"
#include "rtl/net/ethernet.h"
#include "rtl/net/arp.h"
#include "rtl/net/udp.h"
#include "rtl/net/tcp.h"
#include "rtl/net/nicintel.h"    //intel nic - network interface controller.
#include "rtl/net/in.h"
#include "rtl/net/un.h"
#include "rtl/net/nports.h"     //(network) Network Ports  (sw)
#include "rtl/net/ip.h"         //(network) IP info.      (sw)
#include "rtl/net/ipv4.h" 
//#include "rtl/net/ipv6.h" 
#include "rtl/net/ipv4mac.h" 
#include "rtl/net/icmp.h" 
#include "rtl/net/packet.h"      // network packets.
#include "rtl/net/channel.h"     //(network) Channel       (sw)
#include "rtl/net/client.h"      //(network) Client process support. 
#include "rtl/net/ns.h"          //(network) Network Server.
#include "rtl/net/network.h"     //(network) Gerenciamento de rede.  
#include "rtl/net/socket.h"      //last always


//
// ==== DEVICES ====
//


// devices
#include "hal/dev/devices.h"
#include "hal/dev/devmgr.h"      
 
#include "hal/io.h"               //io.


#include "land/modules.h"     //module manager.
#include "land/debug.h"
#include "land/system.h"    //system manager.
#include "land/init.h"
#include "land/execve.h"  
// mm
#include "land/mm/mmglobal.h"  // Deve ficar mais acima.
#include "land/mm/heap.h"      // Heap pointer support.
#include "land/mm/aspace.h"    // Address Space, (data base account).

// dspace
#include "hal/dev/blkdev/dspace.h"    // Disk Space, (data base account). storage stuff

// mm
#include "land/mm/bank.h"      // Bank. database
#include "land/mm/x86mm.h"     // mm, memory manager support.



// rawgr - 
// view. input support.
#include "hal/dev/tty/vt/rawgr/view/cursor.h"


#include "land/messages.h"
#include "land/events.h"
#include "land/object.h"
#include "land/ss.h"


// profiler
#include "land/pints.h"


#include "rtl/runtime.h"


// kernel
#include "land/ke.h"
#include "land/ki.h"
#include "land/info.h"
#include "land/request.h"
#include "land/reboot.h"
#include "land/sub.h"       // gramado sub systems
#include "land/utsname.h"
#include "land/gpid.h"      // Globals. PIDs support.


// sci - system call interface
// All the functions in this folder can be called
// by the ring3 apps via system call.
// This is the last #include. :^)

#include "rtl/sci/syscall.h"        
#include "rtl/sci/sys.h"

// si - services interfce
#include "rtl/si/sifs.h"
#include "rtl/si/sins.h"
#include "rtl/si/siws.h"


// ==============================

//keyboard suppport 
//abnt2 flag.
//#todo: Move this to another file.
//maybe gdef.h
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
// == current ======================================================
//

// GRAMADO_JAIL, GRAMADO_P1 ...
int current_mode;

// INPUT_MODE_SETUP, INPUT_MODE_WS ...
int current_input_mode;

// x86 ...
int current_arch;


// Organização de usuários.
int current_user; 
int current_group; 



// Organização dos processos


// Process used by the console during the job control.
// #hackhack: 
// For now we are using the control thread associated with the
// window with focus.
// #todo
// But we need to use the control thread of the foreground process
// associated with the console TTY.
int foreground_process;

int foreground_thread;


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
int g_driver_ps2keyboard_initialized;   //ps2 keyboard
int g_driver_ps2mouse_initialized;      //ps2 mouse

int g_driver_video_initialized;
int g_driver_apic_initialized;
int g_driver_hdd_initialized;

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


//
// symbol table
//

int g_kernel_symbols_available;


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







