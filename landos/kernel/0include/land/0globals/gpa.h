
// gpa.h 
// Endereços físicos usados pelo kernel base.


#ifndef ____GPA_H
#define ____GPA_H  1


//
// == 0 KB ==================================================
//

// Primeiros 2 MB.
#define SYSTEM_ORIGIN  0
#define SMALLSYSTEM_ORIGIN_ADDRESS   SYSTEM_ORIGIN
#define MEDIUMSYSTEM_ORIGIN_ADDRESS  SYSTEM_ORIGIN
#define LARGESYSTEM_ORIGIN_ADDRESS   SYSTEM_ORIGIN

// Size = 1KB
#define REALMODE_IVT  SYSTEM_ORIGIN

// Size?
#define REALMODE_BIOSDATAAREA  0x400

// Size?
#define REALMODE_FREEAREA  0x500


// ...

//
// == 4 KB ==================================================
//

// ===================================================

// #importante: PERIGO !!!
// >>>> 0x1000
// O sistema está usando esse endereço como início de um heap
// onde pegamos páginas de memória para criarmos diretórios de páginas.
// Isso porque precisamos de endereços que terminem com pelo menos 
// 12bits zerados.
// #todo: 
// Podemos fazer uma contagem de alocaçao possivel nesse heap
// #todo: 
// Precisamos encontrar outro lugar para esse heap, tendo em vista que
// o número de diretórios criados será grande e o heap invadirá 
// outras áreas.
// me parece que o próximo endereço usado é o MBR em 0x00020000. 
// #todo: Possivelmente podemos mudar o MBR de lugar usando o alocador.
// #OBS: Os endereços físico e virtual são iguais.
// See: mm/pages.c

//#todo
// Define min and max
// Quantos diretórios podemos alocar aqui?

#define  ____DANGER_TABLE_POINTER_HEAP_BASE  0x1000


// Essa tabela é bem longa
// Vai até o MBR.


//
// == 128 KB ==================================================
//


// 128 KB mark.
#define MBR_ADDRESS  0x00020000  


#define VOLUME1_VBR_ADDRESS   (MBR_ADDRESS + 0x200) 
#define VOLUME2_VBR_ADDRESS   (MBR_ADDRESS + 0x200) 
// ...


//
// == 192 KB ==================================================
//

// Size?
#define VOLUME1_FAT_ADDRESS   0x00030000 
#define VOLUME2_FAT_ADDRESS   0x00030000


//
// == 448 KB ==================================================
//

// Rootdir size = (512*32) = 16 KB.
#define VOLUME1_ROOTDIR_ADDRESS  0x00070000 
#define VOLUME2_ROOTDIR_ADDRESS  0x00070000 


//
// == 512 KB ==================================================
//

// #todo
// Tem espaço sobrando aqui ??

// #todo
// Deveria ter uma área de memória de onde pegaríamos 
// as pagetables que precisamos, em ordem,
// podendo contar um numero mínimo e máximo de pagetables
// no sistema.


// 0x0008F000 Tabela para mapear a parte mais baixa da memória física. Começa em 0.
// 0x0008E000 Tabela para mapear a memória usada pela imagem do kernel. Começa em 0x100000.
// 0x0008D000 Tabela para mapear uma área em user mode onde rodam códigos. Começa em 0x400000.
// 0x0008C000 Tabela para mapear a vga. Começa em 0xb8000.
// 0x0008B000 Tabela para mapear o frontbuffer, O começo é passado pelo Boot.
// 0x0008A000 Tabela para mapear o backbuffer, o começo é em (0x01000000 - 0x400000) no small system.
// // 0x00089000 Tabela de páginas para o pagedpool.
// //...
//?? Obs: Não sei o quanto podemos ir escolhendo endereços nessa região sem sobrepor o boot loader.
//

// System page tables:
// Essas são as pagetables mais importantes,
// por isso ficarão aqui isoladas.
// Já as outras pagetables ficarão concatenadas 
// numa lista grande em um outro lugar de fácil acesso. 
// #importante 
// Essas pagetable possuem endereço físico e lógico iguais.
// Page tables.
// ?? estao sendo usadas no momento ou nao?
//0x00083000 - AHCI 1 - Tentando mapear alguma coisa para ahci.
// Extra heaps.
//0x00087000 - pagetable para mapear um pool de heaps.
//0x00088000 - Page table para mapear um NIC.
// 0x00089000 - Pagetable para mapear um pool.
// Possivelmente usado por um alocador de memoria compartilhada.
// 0x0008A000 - Pagetable para o backbuffer.
// Esse eh o backbuffer que copiamos para o lfb.
// 0x0008B000 - pagetable para o lfb.
// 0x0008C000 - Pagetable para o CGA em user mode.
// Aquele memoria de modo texto colorido.
// 0x0008D000 - Pagetable para mapear uma area de memoria 
// que sera usada pelos aplicativos em user mode.
// 0x0008E000 - Pagetable para mapear o endereço onde a imagem do kernel
// sera carregada na memoria fisica.
// 0x0008F000 - Pagetable para mapear os primeiros 4MB de memoria fisica.
// ring0. 1:1


// Pagetables.
// Static 
//#define PAGETABLE_RES7       0x00080000
#define PAGETABLE_RES6         0x00081000
#define PAGETABLE_RES5         0x00082000
#define PAGETABLE_AHCI1        0x00083000   
#define PAGETABLE_EXTRAHEAP3   0x00084000
#define PAGETABLE_EXTRAHEAP2   0x00085000
#define PAGETABLE_EXTRAHEAP1   0x00086000
#define PAGETABLE_HEAPPOOL     0x00087000 
#define PAGETABLE_NIC1         0x00088000
#define PAGETABLE_PAGEDPOOL    0x00089000
#define PAGETABLE_BACKBUFFER   0x0008A000
#define PAGETABLE_FRONTBUFFER  0x0008B000
#define PAGETABLE_CGA          0x0008C000
#define PAGETABLE_RING3AREA    0x0008D000
#define PAGETABLE_KERNELIMAGE  0x0008E000
#define PAGETABLE_RING0AREA    0x0008F000


//
// == 576 KB ==================================================
//

// #bugbug
//  Em 0x00090000 costumava ter uma pilha.

// O endereço físico e virtual do boot block são o mesmo.
// Boot block size?
#define BOOTBLOCK_PA  0x0000000000090000

// pml4, pdpt, pd for kernel process.
// Lembrando que a parte das flags precisa ser '000'

#define KERNEL_PD_PA    0x000000000009A000
#define KERNEL_PDPT_PA  0x000000000009B000
#define KERNEL_PML4_PA  0x000000000009C000


// #bugbug
// Temos uma pilha aqui ??
// eh possivel, temos espaço.
// 0x0009FFF0 ??



//
// == 640 KB ==================================================
//

//==============
// vga
// The address of the VGA buffer.
//EGA	A0000 for 128K byte *
//VGA	A0000 for 128K byte *

#define VGA_PA  0x000A0000
#define EGA_PA  0x000A0000

//
// == 704 KB ==================================================
//

//==============
// mda
// The address of the MDA buffer.
// Monocrome.
//MDA	B0000 for 4K byte
//HGC (Hercules)	B0000 for 64K byte

#define MDA_PA  0x000B0000
#define HGC_PA  0x000B0000


//
// == 736 KB ==================================================
//


//==============
// cga
// The address of the CGA buffer.
// colors.
//CGA	B8000 for 16K byte

#define CGA_PA            0x000B8000
#define SMALLSYSTEM_CGA   CGA_PA
#define MEDIUMSYSTEM_CGA  CGA_PA
#define LARGESYSTEM_CGA   CGA_PA


//
// == 768 KB ==================================================
//

// 16-bit devices, expansion ROMs  
#define BIOS_STUFF  0x000C0000


//
// == 960 KB ==================================================
//

// BIOS ROM  
#define BIOS_STUFF2  0x000F0000
#define BIOS_ROM  BIOS_STUFF2

//
// == 1 MB ==================================================
//

// eXTENDED MEMORY

// 1MB físico.
// #importante: 
// Foram mapeados 2MB para a imagem do kernel e
// para o heap e a stack.

// 1
#define KERNEL_BASE  0x00100000
#define SMALLSYSTEM_KERNELBASE   KERNEL_BASE
#define MEDIUMSYSTEM_KERNELBASE  KERNEL_BASE
#define LARGESYSTEM_KERNELBASE   KERNEL_BASE


//
// == 2 MB ==================================================
//

// ...

//
// == 4 MB ==================================================
//

// ...

//
// == 8 MB ==================================================
//

// Segue 8MB de Backbuffer.
// Esse backbuffer será usado principalmente para
// sistemas 'Small'.

// 8
#define BACKBUFFER  0x800000
#define BACKBUFFER_PART1  BACKBUFFER
#define SMALLSYSTEM_BACKBUFFER   BACKBUFFER
#define MEDIUMSYSTEM_BACKBUFFER  BACKBUFFER
#define LARGESYSTEM_BACKBUFFER   BACKBUFFER

// 10
// Reservado para backbuffer
//#define BACKBUFFER_PART2  0xA00000

// 12
// Reservado para backbuffer
//#define BACKBUFFER_PART3  0xC00000

// 14
// Reservado para backbuffer
//#define BACKBUFFER_PART4  0xE00000

//
// == 16 MB =========================================================
//
// 0x01000000

// 16
#define HEAPPOOL  0x01000000
#define SMALLSYSTEM_HEAPPOLL_START   HEAPPOOL
#define MEDIUMSYSTEM_HEAPPOLL_START  HEAPPOOL
#define LARGESYSTEM_HEAPPOLL_START   HEAPPOOL

//16+2 = 18 MB
#define EXTRAHEAP1  (0x01000000 + 0x200000)
#define SMALLSYSTEM_EXTRAHEAP1_START     EXTRAHEAP1
#define MEDIUMSYSTEM_EXTRAHEAP1_START    EXTRAHEAP1 
#define LARGESYSTEM_EXTRAHEAP1_START     EXTRAHEAP1 

//16+4 = 20 MB
#define EXTRAHEAP2  (0x01000000 + 0x400000)
#define SMALLSYSTEM_EXTRAHEAP2_START    EXTRAHEAP2
#define MEDIUMSYSTEM_EXTRAHEAP2_START   EXTRAHEAP2 
#define LARGESYSTEM_EXTRAHEAP2_START    EXTRAHEAP2 

//16+6 = 22 MB
#define EXTRAHEAP3  (0x01000000 + 0x600000)
#define SMALLSYSTEM_EXTRAHEAP3_START     EXTRAHEAP3
#define MEDIUMSYSTEM_EXTRAHEAP3_START    EXTRAHEAP3 
#define LARGESYSTEM_EXTRAHEAP3_START     EXTRAHEAP3 

// 24
#define PAGEDPOOL1  (0x01000000 + 0x800000) 
#define PAGEDPOOL  PAGEDPOOL1
#define SMALLSYSTEM_PAGEDPOLL_START   PAGEDPOOL
#define MEDIUMSYSTEM_PAGEDPOLL_START  PAGEDPOOL
#define LARGESYSTEM_PAGEDPOLL_START   PAGEDPOOL

// 26
#define PAGEDPOOL2  (0x01000000 + 0xA00000) 

// 28
#define PAGEDPOOL3  (0x01000000 + 0xC00000) 

// 30
#define PAGEDPOOL4  (0x01000000 + 0xE00000) 


//
// == 32 MB =========================================================
//

// Um sistema maior que 32MB já é considerado Small.

// #atenção:
// Essa é uma area em user mode.

// 32 MB mark
#define USER_BASE  0x02000000 
#define SMALLSYSTEM_USERBASE     USER_BASE
#define MEDIUMSYSTEM_USERBASE    USER_BASE
#define LARGESYSTEM_USERBASE     USER_BASE 


// #important: 
// Segue-se bastaste espaço livre.
// 
// ...



//
// == 64 MB =========================================================
//

// Um sistema maior que 64MB já é considerado Medium.
// Portando não pode mais ter definições de Small.

#define FRAME_TABLE_START_PA  (0x04000000)   // 64 mb mark. 


// #important: Segue-se bastaste espaço livre.
// ...


//
// == 128 MB =========================================================
//

// Um sistema maior que 128MB já é considerado Large.
// Portando não pode mais ter definições de Medium ou Small.

// 0x08000000
// #available



//
// == 256 MB =========================================================
//

// 0x10000000
// #available

// Área de memória para uma frame table grande.
// De onde pegaremos os frames para mapearmos.
// É um heap grande de frames.
// #perigo: Cuidado com a colisão com as próximas
// entradas indicadas nessa lista.

// A frame table começa aqui e vai até o fim da memória ram
// disponível ou até um limite.


//
// == 512 MB =========================================================
//

// 0x20000000
// #available


//
// == 1GB =========================================================
//

// 0x40000000
// #available

// #todo
// Quando o sistema tiver memória o suficiente
// Então colocaremos um backbuffer bem grande aqui.
// Provavelmente no limite de 1gb de tamanho.
// #todo: 
// Já podemos tentar isso na máquina real.

#define BACKBUFFER_1GB  0x40000000


//
// == 2GB =========================================================
//

// 0x80000000
// #available

//
// == 3GB =========================================================
//

// 0xC0000000
// #available



// =================================================================

/*
    // endereços comuns
    
    0x01000000 =  16 MB
    0x02000000 =  32 MB
    0x04000000 =  64 MB
    0x08000000 = 128 MB
    
    0x10000000 = 256 MB 
    0x20000000 = 512 MB
    0x40000000 = 1    GB
    0x50000000 = 1.24 GB
    0x60000000 = 1.5  GB
    0x70000000 = 1.75 GB
    0x80000000 = 2    GB
*/


#endif    





















