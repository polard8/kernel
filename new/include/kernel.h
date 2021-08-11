// kernel.h
// porting from Gramado 32bit.


//
// Gramado Alone
//


//
// == gramado modes =========================
//

// See: 'current_mode'.
#define GRAMADO_JAIL        0x00
#define GRAMADO_P1          0x01
#define GRAMADO_HOME        0x02
#define GRAMADO_P2          0x03
#define GRAMADO_CASTLE      0x04
#define GRAMADO_CALIFORNIA  0x05
// ...


// ============================

//
// System State
//

// # This is a test yet.

#define SYSTEM_NULL        0   // Nothing
#define SYSTEM_BOOTING     1   // The system is starting ...
#define SYSTEM_SCHEDULING  2   // The system is scheduling ...
#define SYSTEM_RUNNING     3   // The system is running.
#define SYSTEM_REBOOT      4   // The system is running the reboot routine.
#define SYSTEM_POWEROFF    5   // The system is running the poweroff routine.
#define SYSTEM_RESTART     6   // The system is running the routine to restart the kernel.
#define SYSTEM_ABORTED     7  // The system was aborted ... ex: initialization fail
#define SYSTEM_PANIC       8  // Running the panic routine.
// ...

int system_state;

// ============================



//
// IO Control
//

// #todo
// include/user/ is a better place for this structure.
// But it needs to a global thing.

// This is the idea:
// Instead of selecting the io model,
// we will select the components that will be used in the input system.

struct io_control_d
{
    int initialized;
    int useTTY;
    int useEventQueue;
};
struct io_control_d  IOControl;


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
// Used by applications using the kgws window server.
// This is the mode used when we do not have a 
// loadble ring3 window server.
// Send the input event to the thread associated with the
// window with focus in the window server embedded inside the kernel.
#define INPUT_MODE_EVENTS  1000
#define INPUT_MODE_SETUP   INPUT_MODE_EVENTS

// tty input mode.
// In this mode we're gonna send the input to the tty buffer.
// This way a virtual terminal can share the input with its client.
#define INPUT_MODE_TTY    2000

// ws input mode.
// Used for the applications running on an environment
// with a loadable window server. Just like gws window server.
#define INPUT_MODE_WS     3000

// ...


// Importados de bl64.
// See: main.c
unsigned long SavedLFB;
unsigned long SavedX;
unsigned long SavedY;
unsigned long SavedBPP;




// =========================================================

// (NT)
// gramado OS headers.

// oh boy
#include "gramado/0boy/0boy.h"

// config
#include "gramado/0config/version.h"    // Product. 
#include "gramado/0config/u.h"          // User
#include "gramado/0config/config.h"     // Compiling.

// globals
#include "gramado/0globals/limits.h"
#include "gramado/0globals/gpa.h"
#include "gramado/0globals/gva.h"
#include "gramado/0globals/gentry.h"
#include "gramado/0globals/gdef.h"
#include "gramado/0globals/gdevice.h"
#include "gramado/0globals/gobject.h"
#include "gramado/0globals/gspin.h"
#include "gramado/0globals/ginput.h"  // input manager support.
#include "gramado/0globals/gwd.h"     // whatch dogs.

//#test
#include "rtl/stdarg.h"

// rtl 
// Inside the base kernel
#include "rtl/errno.h"
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
#include "mm/mm.h"
#include "mm/memmap.h" 
#include "mm/intelmm.h"
#include "mm/x64mm.h"     // mm, memory manager support.

//#test
#include "user/view/video.h"

#include "user/view/screen.h"

#include "user/model/fonts.h"
#include "user/model/ascii.h" 

// fs
#include "fs/path.h"       // path.
#include "fs/fat.h"        // fat16.
#include "fs/fat_lfn.h"    // fat16 lfn.
#include "fs/inode.h"
#include "fs/exec_elf.h"
#include "fs/pipe.h"
#include "fs/fs.h"


// hal
#include "hal/ports64.h"
#include "hal/halvid.h"
#include "hal/cpu.h"
#include "hal/tss.h"
#include "hal/x64gdt.h"
#include "hal/x64.h"
#include "hal/detect.h"
#include "hal/dev/tty/serial.h"


// todo: 
// podemos mover isso de lugar para perto de net/
#include "rtl/net/mac.h"


// hal/dev/blkdev
#include "hal/dev/blkdev/ata.h"
#include "hal/dev/blkdev/ide.h"
#include "hal/dev/blkdev/super.h"
#include "hal/dev/blkdev/volume.h"
#include "hal/dev/blkdev/disk.h"  
#include "hal/dev/blkdev/storage.h" 

// hal
#include "hal/pit.h"
#include "hal/pic.h"
#include "hal/cpuid.h"
#include "hal/rtc.h"


#include "user/view/i8042/keyboard.h"
#include "user/view/i8042/mouse.h"

#include "hal/bus/pci.h"


#include "hal/up.h"
#include "hal/breaker.h"
#include "hal/hal.h"


// ps
#include "ps/image.h"
#include "ps/x64cont.h"
#include "ps/ts.h"
#include "ps/tasks.h"
#include "ps/process.h"
#include "ps/thread.h"
#include "ps/sched.h"
#include "ps/queue.h"
#include "ps/mk.h"
#include "ps/dispatch.h"


#include "user/ws.h"

#include "user/kgws.h"


// #view - designers
#include "user/view/vk.h"
#include "user/view/kbdabnt2.h"
#include "user/view/window.h"
// ...


//
// == Security ===============================
//

#include "user/security/usession.h"
#include "user/security/room.h"
#include "user/security/desktop.h"
#include "user/security/logon.h"
#include "user/security/logoff.h"
#include "user/security/user.h"
#include "user/security/security.h"


// tty
#include "hal/dev/tty/ttyldisc.h"
#include "hal/dev/tty/ttydrv.h"
#include "hal/dev/tty/tty.h"
#include "hal/dev/tty/pty.h"

#include "user/vt.h"
#include "user/console.h"


// =============================
// i8042 ps2 controller.
#include "user/view/i8042/i8042.h"
#include "user/view/i8042/ps2mouse.h"
#include "user/view/i8042/ps2kbd.h"
#include "user/view/i8042/ps2.h"



//
// == NETWORK ====
//

//#include "rtl/net/connect.h" 
#include "rtl/net/host.h"
#include "rtl/net/ethernet.h"
#include "rtl/net/arp.h"
#include "rtl/net/udp.h"
#include "rtl/net/tcp.h"

#include "rtl/net/in.h"
#include "rtl/net/un.h"
#include "rtl/net/nports.h"     //(network) Network Ports  (sw)
#include "rtl/net/icmp.h" 
#include "rtl/net/network.h"     //(network) Gerenciamento de rede.  
#include "rtl/net/socket.h"      //last always


// devices
#include "hal/dev/devmgr.h"      

#include "hal/io.h"               //io.

#include "gramado/init.h"
#include "gramado/debug.h"
#include "gramado/system.h"   // system manager

// mm
#include "mm/mmglobal.h"  // Deve ficar mais acima.
#include "mm/heap.h"      // Heap pointer support.
#include "mm/aspace.h"    // Address Space, (data base account).
#include "mm/bank.h"      // Bank. database
#include "mm/x64mm.h"     // mm, memory manager support.

#include "gramado/object.h"

// profiler
#include "gramado/pints.h"

#include "rtl/runtime.h"
#include "gramado/request.h"
#include "gramado/gpid.h"      // Globals. PIDs support.
#include "gramado/utsname.h"
#include "gramado/info.h"      // last one?


// ==============================

// sci - system call interface
// All the functions in this folder can be called
// by the ring3 apps via system call.
// This is the last #include. :^)

#include "rtl/sci/syscall.h"        
#include "rtl/sci/sys.h"


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
//int current_input_mode;

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
//...


//
// #todo
//

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

#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...



//
// == prototypes ==========================================
//


// inicialização do kernel, independente da arquitetura.
// See: kernel/main.c
int kernel_main (int arch_type);

// ================================================

//
// x86_64 Initialization. (Main routine)
//

// x64init.c
int I_x64main (void);

// sysinit.c
int I_init (void);

// x64init.c
void I_x64CreateInitialProcess (void);
void I_x64ExecuteInitialProcess (void);

// x64init.c
void I_x64CreateKernelProcess(void);
void I_x64CreateEarlyRing0IdleThread(void);



// ================================================

//
// Finalizations support.
//

void faults (unsigned long number);



// #debug
// usado durante a construçao dos handlers das irqs.
// See: main.c hw.asm headlib.asm
void xxxxIRQ0_DEBUG_MESSAGE(void);
void xxxxIRQ1_DEBUG_MESSAGE(void);
// See: main.c Sw.asm headlib.asm
void xxxxINT128_DEBUG_MESSAGE(void);




void panic ( const char *format, ... );
void die (void);
void a_soft_place_to_fall(void);


