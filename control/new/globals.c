
// globals.c

#include <kernel.h>


// see: gdef.h
struct boot_block_d  BootBlock;

// This status flag is setted when
// the callouts to GWSSRV.BIN are installed.
int gUseWMCallbacks=FALSE;


int system_state = SYSTEM_NULL;

// GRAMADO_JAIL, GRAMADO_P1 ...
int current_mode=0;

// INPUT_MODE_SETUP, INPUT_MODE_WS ...
//int current_input_mode=0;

// x86 ...
int current_arch = CURRENT_ARCH_X86_64;

// Organização de usuários.
int current_user=0;
int current_group=0; 

// Current runlevel. Used in init process.
int current_runlevel=0;

// Organização dos discos.
int current_disk=0;
int current_volume=0;

// Organização dos arquivos.
int current_directory=0;
int current_file=0;

// Organização dos terminais
int current_tty=0;
int current_terminal=0;
//int current_pty=0;
//int current_pts=0;

int abnt2=FALSE;

// Type of product.
int g_product_type = PT_UNDEFINED;
// Size of processor word.
int g_platform_type = PFT_64BIT;
// System type.
int g_system_type = SYSTEM_TYPE_NULL;


// Logon.
int g_logged=FALSE;

// GUI
// flag.
// If the kernel is in graphics mode.
int g_useGUI=FALSE;


// Kernel information variables.
unsigned long KernelSize=0;
unsigned long KernelHeapSize=0;
unsigned long KernelStackSize=0;
unsigned long KernelPages=0;
//...


int g_kernel_symbols_available=FALSE;

//#bugbug
//move this to kernel (ring 0) crt support.
//error support.
unsigned long errno=0;





















