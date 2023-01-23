
// kernel.h
// Created by Fred Nora.


// This status flag is setted when
// the callouts to GWSSRV.BIN are installed.
extern int gUseWMCallbacks;


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

// Nothing
#define SYSTEM_NULL        0
// Getting info from bootloader tables.
// Setup global, and configurations.
// Starting serial debuyg support and virtual console support.
#define SYSTEM_PREINIT     1
// The system is starting ...
#define SYSTEM_BOOTING     2
// The system is scheduling ...
#define SYSTEM_SCHEDULING  3
// The system is running.
#define SYSTEM_RUNNING     4
// The system is running the reboot routine.
#define SYSTEM_REBOOT      5
// The system is running the poweroff routine.
#define SYSTEM_POWEROFF    6
// The system is running the routine to restart the kernel.
#define SYSTEM_RESTART     7
// The system was aborted ... ex: initialization fail
#define SYSTEM_ABORTED     8
// Running the panic routine.
#define SYSTEM_PANIC       9
// The initialization fail and we are
// halted for ever.
#define SYSTEM_DEAD        10
// ...

extern int system_state;

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

// Display device support.
// Imported from bl64.
// Change to gSavedLFB ...
// See: screen.c

extern unsigned long gSavedLFB;
extern unsigned long gSavedX;
extern unsigned long gSavedY;
extern unsigned long gSavedBPP;


// =========================================================

// #todo
// Reorganizar esses headers quando puder.


// (NT)
// Gramado OS headers.

// ==================================
// Gramado Configuration
#include "config/gramado/config.h"
#include "config/gramado/version.h"    // Product. 
#include "config/gramado/u.h"          // User
#include "config/gramado/system.h"

// ==================================
#include "gramado/utsname.h"

// ==================================
// Kernel configuration.
// Compiling.
#include "config/superv/config.h"
#include "config/superv/limits.h"
#include "config/superv/limits2.h"
#include "config/superv/gdef.h"
#include "config/superv/gdevice.h"
#include "config/superv/ginput.h"  // input manager support.
#include "config/superv/gspin.h"
#include "config/superv/gwd.h"     // whatch dogs.
#include "config/superv/pints.h"   // profiler
#include "config/superv/request.h"
#include "config/superv/info.h"    // last one?
#include "config/superv/kinit.h"   // kernel initialization.

#include "gramado/debug.h"


// klib: libc support.
#include "kstdarg.h"
#include "kerrno.h"
#include "kcdefs.h"
#include "kstddef.h"
#include "ktypes.h"
#include "ktypes2.h"
#include "kobject.h"
#include "klimits.h"
#include "kstdio.h"
#include "kstdlib.h"
#include "kstring.h"
#include "kctype.h"
#include "kiso646.h"
#include "ksignal.h"
#include "kunistd.h"
#include "kfcntl.h"
#include "kioctl.h"
#include "kioctls.h"
#include "ktermios.h"
#include "kttydef.h"

// Globals. PIDs support.
#include "config/superv/kpid.h"

// Memory management.
#include "mm/x64gpa.h"
#include "mm/x64gva.h"
#include "mm/gentry.h"
#include "mm/mm.h"
#include "mm/memmap.h" 
#include "mm/intelmm.h"
#include "mm/x64mm.h"
#include "mm/mmglobal.h"  // Deve ficar mais acima.
#include "mm/heap.h"      // Heap pointer support.
#include "mm/aspace.h"    // Address Space, (data base account).
#include "mm/bank.h"      // Bank. database


// memory and libc
#include "runtime.h"


// hal
#include "hal/ports64.h"
#include "hal/cpu.h"
#include "hal/tss.h"
#include "hal/x64gdt.h"
#include "hal/x64.h"
#include "hal/detect.h"
// hal pci
#include "hal/bus/pci.h"  // PCI bus.
// hv
#include "config/hyperv/hv.h"
// hal cpu
#include "hal/cpuid.h"
#include "hal/up.h"
#include "hal/mp.h"
// hal pic/apic
#include "hal/pic.h"
#include "hal/apic.h"
#include "hal/breaker.h"
// hal timers.
#include "hal/pit.h"
#include "hal/rtc.h"
// hal io
#include "hal/io.h"    //io.
// hal global
#include "hal/hal.h"     // last one.


//  primeiro char, depois block, depois network.

//
// TTY ------------------
//

// tty
#include "dev/tty/ttyldisc.h"
#include "dev/tty/ttydrv.h"
#include "dev/tty/tty.h"
#include "dev/tty/pty.h"
#include "dev/tty/vt.h"
#include "dev/tty/console.h"

//
// Serial devices ------------------
//

// fb device
#include "dev/fb/hw/halvid.h"
#include "dev/fb/hw/video.h"
#include "dev/fb/hw/screen.h"
#include "dev/fb/gr/fonts.h"
#include "dev/fb/gr/ascii.h" 
#include "dev/fb/gr/ws.h"
#include "dev/fb/gr/window.h"
#include "dev/fb/gr/bg.h"
#include "dev/fb/gr/graphics.h"
// Serial port. (COM).
#include "dev/tty/serial.h"

// ps2 - i8042
#include "dev/kbd/vk.h"
#include "dev/kbd/kbdabnt2.h"
#include "dev/kbd/kbdmap.h"
#include "dev/kbd/keyboard.h"
#include "dev/kbd/ps2kbd.h"
#include "dev/mouse/mouse.h"
#include "dev/mouse/ps2mouse.h"
#include "dev/i8042.h"
#include "dev/ps2.h"


//
// Block devices ----------------------
//

// ata, sata
#include "dev/ata/ata.h"
#include "dev/ata/ide.h"
// storage
#include "dev/super.h"
#include "dev/volume.h"
#include "dev/disk.h"  
#include "dev/storage.h" 


//
// Network devices ---------------------------
// 

// primeiro controladoras depois protocolos
// e1000 - nic intel
#include "dev/e1000/nicintel.h"
#include "net/mac.h"
#include "net/host.h"
#include "net/in.h"
#include "net/un.h"
#include "net/ethernet.h"
#include "net/arp.h"
#include "net/ip.h"
#include "net/udp.h"
#include "net/tcp.h"
#include "net/icmp.h" 
#include "net/nports.h"     //(network) Network Ports  (sw)
#include "net/network.h"     //(network) Gerenciamento de rede.  
#include "net/socket.h"      //last always

// ----------------------

// por ultimo em devices.
// device manager
#include "dev/devmgr.h"  

// ----------------------

// depois de devices.
// fs
#include "fs/path.h"       // path.
#include "fs/fat.h"        // fat16.
#include "fs/fat_lfn.h"    // fat16 lfn.
#include "fs/inode.h"
#include "fs/exec_elf.h"
#include "fs/pipe.h"
#include "fs/fs.h"


//
// Kernel --------------------------
//

// ps
#include "ps/prio.h"     // Priority
#include "ps/quantum.h"  // Quantum
#include "ps/image.h"
#include "ps/x64cont.h"
#include "ps/ts.h"
#include "ps/tasks.h"
#include "ps/callback.h"
#include "ps/process.h"
#include "ps/thread.h"
#include "ps/sched.h"
#include "ps/queue.h"
#include "ps/mk.h"
#include "ps/dispatch.h"



//
// Configurações finais
//


// Autentication
// Security
#include "user/usession.h"
#include "user/room.h"
#include "user/desktop.h"
#include "user/logon.h"
#include "user/logoff.h"
#include "user/user.h"
#include "user/security.h"

// ==============================

// sci - system call interface
// All the functions in this folder can be called
// by the ring3 apps via system call.
// This is the last #include. :^)

#include "gramado/syscalls.h"

#include "newos.h"

// ==============================
// #bugbug: O resto das coisas daqui pra 
// baixo são incluidas mais de uma vez, pois não te ifndef pra elas
// podemos colocar todas elas dentro de arquivos .h
// e mover as definições para arquivos .c.


// ------------------------------
// Product type.
typedef enum {
    PT_UNDEFINED,
    PT_THINGS,          // Things.
    PT_EDGEDEVICES,     // Edge Devices.
    //PT_COREDEVICES,   // Core Devices. (haha)
}ProductType_t;
//Type of product.
extern int g_product_type; 

// ------------------------------
// Platform type.
typedef enum {
   PFT_16BIT,       //16bit processor.
   PFT_32BIT,       //32bit processor.
   PFT_64BIT,       //64bit processor.
   //...
}PlatformType_t;
//size of processor word.
extern int g_platform_type;

// ------------------------------
// UP ou MP
typedef enum {
    SYSTEM_TYPE_NULL,
    SYSTEM_TYPE_UNIPROCESSOR,
    SYSTEM_TYPE_MULTIPROCESSOR
} SystemType_t;
extern int g_system_type;


extern unsigned int g_processor_count;
extern int g_smp_initialized;

//
// == current ======================================================
//

// GRAMADO_JAIL, GRAMADO_P1 ...
extern int current_mode;

#define CURRENT_ARCH_X86      1000
#define CURRENT_ARCH_X86_64   1001
// ...

// x86 ...
extern int current_arch;
// Organização de usuários.
extern int current_user; 
extern int current_group; 


// Organização dos processos

// ------
// see: process.c
// Process used by the console during the job control.
// #hackhack: 
// For now we are using the control thread associated with the
// window with focus.
// #todo
// But we need to use the control thread of the foreground process
// associated with the console TTY.
extern pid_t foreground_process;
// This is the process with the active thread.
extern pid_t active_process;    
// [Processing time]
// Only these can read the keyboard input.
// Sometime it's the terminal.
// It's child will read into a file.
// See: ps/process.c
extern pid_t criticalsection_pid;
// ------


// ------
// See: ps/thread.c
extern tid_t current_thread;     // Currently having the processing time.
extern tid_t foreground_thread;  // Input thread.
extern tid_t active_thread;      // This thread will receive the input.
extern tid_t next_thread;        // next user mode thread.
// ------

pid_t current_dead_process;
int current_dead_thread;


// Current runlevel. Used in init process.
extern int current_runlevel;

// Organização dos discos.
extern int current_disk;
extern int current_volume;

// Organização dos arquivos.
extern int current_directory;
extern int current_file;

// Organização dos terminais
extern int current_tty;
extern int current_terminal;
//extern int current_pty;
//extern int current_pts;


//se ele est'a inicializado ou nao
int dead_thread_collector_status;

// se 'e para usalo ou nao
int dead_thread_collector_flag;

//cr3. current page directoory address.
unsigned long current_process_pagedirectory_address;


// Logon.
extern int g_logged;

// GUI
//flag.
//If the kernel is in graphics mode.
extern int g_useGUI; 

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
extern unsigned long KernelSize;
extern unsigned long KernelHeapSize;
extern unsigned long KernelStackSize;
extern unsigned long KernelPages;
//...

// symbol table
extern int g_kernel_symbols_available;


//#bugbug
//move this to kernel (ring 0) crt support.
//error support.
extern unsigned long errno;

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
struct kernel_args_d  KernelArgs;


//system classes.
struct system_classes_d
{
    //unsigned long Gramado; //@todo: Include this one.
    unsigned long Executive;
    unsigned long Microkernel;
    unsigned long Hal;
};
struct system_classes_d  SystemClasses;


//Kernel classes.
struct kernel_classes_d
{
    struct system_classes_d *System;
    //..
};
struct kernel_classes_d  KernelClasses;
//...

// Informações compartilhadas 
// entre o kernel e um dado módulo.
struct km_shared_info_d
{
// The entry point
    unsigned long entry_point;

// Procedure.
    unsigned long dialog_address;

// The pointer for a table of symbols exported
// by this module.
    unsigned long function_table_address;
};

struct kernel_module_d
{
    int used;
    int magic;
    int id;
    char name[64];
    size_t name_size;
// Shared info
    struct km_shared_info_d info;
    int initialized;
    struct thread_d  *thread;

// navigation
    //struct kernel_module_d *next;
};


#define KMODULE_MOD0  0   // first of the list.
#define KMODULE_MAX   8

unsigned long kmList[KMODULE_MAX];


//
// == prototypes ==========================================
//

// inicialização do kernel, independente da arquitetura.
// See: init.c
int kmain(int arch_type);
void gramado_shutdown (int how);

// ================================================

//
// x86_64 Initialization. (Main routine)
//

// x64init.c
int I_x64main (void);
void I_x64ExecuteInitialProcess (void);

// ================================================

//
// Finalizations support.
//

void faults(unsigned long number);

// #debug
// usado durante a construçao dos handlers das irqs.
// See: main.c hw.asm headlib.asm
void xxxxIRQ0_DEBUG_MESSAGE(void);
void xxxxIRQ1_DEBUG_MESSAGE(void);

void panic ( const char *format, ... );
void die (void);
