/*
 * File: gdef.h
*
* Descrição:
*     Definições globais. 
*     Será utilizado por todos os módulos. Deve ficar no início.
*     Quando uma definição deve ser acessada por todos os módulos
*     do kernel base ela deve ficar aqui.
*
* @todo: FAZER O MÁXIMO DE COISAS SISTEMICAMENTE NÃO-IMPORTANTES PRIMEIRO.
         que não comprometam o sistema. como gui.
*/

/*
 * Sobre a GUI:
 * ============
 *     Um grid flutuante de janelas quadradas, 4 janelas.
 *     O message box pode ser um retângulo abaixo do grid.
 *     Uma janela de terminal virtual igual à um celular. 
 * Desse modo, enquanto essas 6 janelas não são flutuantes, dá pra
 * ir usando elas desenha das no backbuffer mesmo.
 *
 *
 * divisão da tela:   
 * quatro quadrantes de 10.
 * divide por vinte e multiplica pela quantidade desejada.
 *         (multiplicador*(total/20)) 
 */

/*
 Sobre o banco de dados:
 =======================
 
Tipos de contas:
    aspace e dspace, pessoais e conjuntas.
	
aspace:
    Um Address Space é uma conta de banco de dados em memória. Uma conta 
pode ser do tipo conjunta(Shared) ou  pessoal(Personal). 

dspace:
    Um Disk Space é uma conta de banco de dados em disco. Uma conta pode 
ser do tipo conjunta(Shared) ou  pessoal(Personal). 

Donos das contas:
    Os processos são os clientes dos bancos de dados e são os donos das 
contas de bancos de dados.

Tipos de bancos:
    Kernel Data Base, Global Data Base e Local Data Base.

KDB:	
    Banco de dados do tipo kernel. É o banco de maior privilégio, poucos
processos poderão usar esse banco e as contas presentes nele.

GDB:
    Bancos de dados do tipo global. É o banco das contas conjuntas, para
que os processos possam compartilhar as contas e os dados que elas acessam.

LDB:
    Bancos de dados do tipo pessoal. É o banco das contas pessoais. Um 
processo pode ser dono de uma conta dessas para proteger seus dados
e revogar qualquer tipo de acesso e somente ele terá acesso aos dados
dessa conta.
	
*/

#ifndef ____GDEF_H
#define ____GDEF_H 1



//#define BIOS_FONT8X8 0x000FFA6E

//using gui flags.
#define GUI_ON   1
#define GUI_OFF  0


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


// user
//#define SUPER_USER    0



/*
// Classes of processes queues.
#define NQ          0
#define SYSTEM_Q    1
#define SERVICES_Q  2
#define USER_Q      3
*/


//
// socket support
//

// used by listen()
// See: process.h

#define SOCKET_MAX_PENDING_CONNECTIONS 32




int g_is_qemu;


// ===================================================


// Salvando o último endereço válido de memória ram.
// usado em head.asm

unsigned long blSavedLastValidAddress;
unsigned long blSavedPhysicalMemoryInKB;

unsigned long blSavedMetafileAddress;
unsigned long blSavedDiskNumber;
unsigned long blSavedHeads;
unsigned long blSavedSPT;
unsigned long blSavedCylinders;
//...




/*
 * Os Type:
 *     O sistema operacional pode ser usado como servidor.
 * Radando em uma máquina real e acessado por um terminal
 * via rede LAN, ou porta serial. TTY.
 *     Qualquer sistema operacional em uma máquina cliente pode
 * acessar o sistema operacional na maquina servidora. Pra isso
 * tem que ter um programa na máquina cliente que envie comandos 
 * para a máquina servidora através da placa de rede ou da porta 
 * serial.
 *     O sistema pode atuar como cliente.
 */

typedef enum {
	
	OsTypeClient,
	OsTypeServer,
	OsTypeHeadlessServer,

    // ...
    
}os_type_t;


//
// The boot block structure.
//


struct boot_block_d
{
    unsigned long bootblock_address;  //pa ?? va ??
    unsigned long lfb;
    unsigned long x;
    unsigned long y;
    unsigned long bpp;
    
    unsigned long last_valid_address;
    unsigned long physical_memory_in_kb;

    unsigned long metafile_address;
    unsigned long disk_number;
    unsigned long heads; 
    unsigned long spt; 
    unsigned long cylinders; 
    unsigned long boot_mode; 
    unsigned long gramado_mode;
    //...
    int initialized;
};

struct boot_block_d BootBlock;





//
// buffer support
//

// #todo: 
// Talvez essas globais deva ir para o microkernel/pc


// frontbuffer lfb
// The framebuffer
unsigned long g_frontbuffer_va;   
unsigned long g_frontbuffer_pa; 

// backbuffer
unsigned long g_backbuffer_va;
unsigned long g_backbuffer_pa;



//
//
//

/*
struct display_info_d
{
    // The LFB. (frontbuffer)
    unsigned long framebuffer;
    unsigned long width;
    unsigned long height;
    unsigned long depth;    // bits per pixel.
};
*/



//pagedpool virtual address
unsigned long g_pagedpool_va;

// endereço virtual do pool de heaps.
// os heaps nessa área serão dados para os processos.
unsigned long g_heappool_va;
int g_heap_count;
int g_heap_count_max;
unsigned long g_heap_size;
#define G_DEFAULT_PROCESSHEAP_SIZE (1024*128)
#define G_DEFAULT_PROCESSHEAP_COUNTMAX 16     //16 PROCESSOS #BUGBUG



#define  G_DEFAULT_EXTRAHEAP_SIZE  0x400000;  //4MB

unsigned long g_extraheap1_va;
unsigned long g_extraheap1_size;
unsigned long g_extraheap2_va;
unsigned long g_extraheap2_size;
unsigned long g_extraheap3_va;
unsigned long g_extraheap3_size;


int gNextKeyboardMessage;



#endif   



//
// End.
//

