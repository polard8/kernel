
//gpa.h 
//Endereços físicos usados pelo kernel base.


#ifndef ____GPA_H
#define ____GPA_H 1



// Primeiros 4 MB.
#define SMALLSYSTEM_ORIGIN_ADDRESS   0
#define MEDIUMSYSTEM_ORIGIN_ADDRESS  0
#define LARGESYSTEM_ORIGIN_ADDRESS   0




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
// See: mm/x86/pages.c

#define  ____DANGER_TABLE_POINTER_HEAP_BASE    0x1000

//#todo
// Define min and max
// Quantos diretórios podemos alocar aqui?


// ===================================================



// Podemos alocar memória para isso, liberando esse espaço?
#define MBR_ADDRESS            0x00020000  


//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_VBR_ADDRESS   (0x00020000 + 0x200) 
#define VOLUME2_VBR_ADDRESS   (0x00020000 + 0x200) 

// #todo
// Tem muito espaço sobrando aqui.

// size ?
//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_FAT_ADDRESS   0x00030000 
#define VOLUME2_FAT_ADDRESS   0x00030000

// #todo
// Tem espaço sobrando aqui ??

// ?? 512 * 32 = 16KB.
//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_ROOTDIR_ADDRESS 0x00070000 
#define VOLUME2_ROOTDIR_ADDRESS 0x00070000 


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
//#define PAGETABLE_RES7  0x00080000
#define PAGETABLE_RES6    0x00081000
#define PAGETABLE_RES5    0x00082000


// Tentando mapear alguma coisa para ahci.
// AHCI 1
#define PAGETABLE_AHCI1  0x00083000   


// Extra heaps.
#define PAGETABLE_EXTRAHEAP3  0x00084000
#define PAGETABLE_EXTRAHEAP2  0x00085000
#define PAGETABLE_EXTRAHEAP1  0x00086000


// pagetable para mapear um pool de heaps.
#define PAGETABLE_HEAPPOOL     0x00087000 

// Page table para mapear um NIC.
#define PAGETABLE_NIC1  0x00088000


// Pagetable para mapear um pool.
// Possivelmente usado por um alocador de memoria compartilhada.
#define PAGETABLE_PAGEDPOOL  0x00089000

// Pagetable para o backbuffer.
// Esse eh o backbuffer que copiamos para o lfb.
#define PAGETABLE_BACKBUFFER  0x0008A000

// pagetable para o lfb.
#define PAGETABLE_FRONTBUFFER  0x0008B000

// Pagetable para o CGA em user mode.
// Aquele memoria de modo texto colorido.
#define PAGETABLE_CGA  0x0008C000

// Pagetable para mapear uma area de memoria 
// que sera usada pelos aplicativos em user mode.
#define PAGETABLE_USERBASE  0x0008D000

// Pagetable para mapear o endereço onde a imagem do kernel
// sera carregada na memoria fisica.
#define PAGETABLE_KERNELBASE  0x0008E000

// Pagetable para mapear os primeiros 4MB de memoria fisica.
// ring0. 1:1
#define PAGETABLE_KERNELAREA 0x0008F000


// Endereço do diretorio de paginas do kernel.
// O endereço físico e virtual são iguais.
// size ? 4KB ? 1024*4 ?
#define XXXKERNEL_PAGEDIRECTORY 0x0009C000

// #bugbug
// Temos uma pilha aqui ??
// eh possivel, temos espaço.
// 0x0009FFF0 ??


// vga
// The address of the VGA buffer.
#define VGA_PA  0x000A0000


// mda
// The address of the MDA buffer.
// Monocrome.
#define MDA_PA  0x000B0000

// cga
// The address of the CGA buffer.
// colors.
#define CGA_PA            0x000B8000
#define SMALLSYSTEM_CGA   0x000B8000
#define MEDIUMSYSTEM_CGA  0x000B8000
#define LARGESYSTEM_CGA   0x000B8000


//
// == 1 MB =========================================================
//

#define KERNEL_BASE              0x00100000  // 1MB físico.
#define SMALLSYSTEM_KERNELBASE   0x00100000  // KERNEL_BASE
#define MEDIUMSYSTEM_KERNELBASE  0x00100000  // KERNEL_BASE
#define LARGESYSTEM_KERNELBASE   0x00100000  // KERNEL_BASE



//
// == 4 MB =========================================================
//

// Nothing
// Aqui estava a area de user mode, 
// mas mudamos para a marca de 32 MB.
// lembrando que o kernel base foi carregado na marca de 1MB
// e tem 2 MB de heap e stack.
// A ideia eh aproveitar todos os 4MB mapeados para 
// o kernel base. Por enquanto o quarto mega
// esta desperdiçado.



//
// == 8 MB =========================================================
//

//16-8 = 8
#define SMALLSYSTEM_BACKBUFFER   0x800000  //(0x01000000 - 0x800000)  
#define MEDIUMSYSTEM_BACKBUFFER  0x800000  //(0x01000000 - 0x800000) 
#define LARGESYSTEM_BACKBUFFER   0x800000  //(0x01000000 - 0x800000)  

//16-4 = 12
#define SMALLSYSTEM_PAGEDPOLL_START   0xC00000  //(0x01000000 - 0x400000) 
#define MEDIUMSYSTEM_PAGEDPOLL_START  0xC00000  //(0x01000000 - 0x400000) 
#define LARGESYSTEM_PAGEDPOLL_START   0xC00000  //(0x01000000 - 0x400000) 


//
// == 16 MB =========================================================
//

#define SMALLSYSTEM_HEAPPOLL_START   (0x01000000) 
#define MEDIUMSYSTEM_HEAPPOLL_START  (0x01000000)
#define LARGESYSTEM_HEAPPOLL_START   (0x01000000)

//16+4 = 20
#define SMALLSYSTEM_EXTRAHEAP1_START     (0x01000000 + 0x400000) //20mb
#define MEDIUMSYSTEM_EXTRAHEAP1_START    (0x01000000 + 0x400000) 
#define LARGESYSTEM_EXTRAHEAP1_START     (0x01000000 + 0x400000) 

//16+8 = 24
#define SMALLSYSTEM_EXTRAHEAP2_START    (0x01000000 + 0x800000) //24mb 
#define MEDIUMSYSTEM_EXTRAHEAP2_START   (0x01000000 + 0x800000) 
#define LARGESYSTEM_EXTRAHEAP2_START    (0x01000000 + 0x800000) 

//16+12 = 28
#define SMALLSYSTEM_EXTRAHEAP3_START  (0x01000000 + 0xC00000) //28mb 
#define MEDIUMSYSTEM_EXTRAHEAP3_START (0x01000000 + 0xC00000) 
#define LARGESYSTEM_EXTRAHEAP3_START  (0x01000000 + 0xC00000) 


//##################################################################


//
// == 32 MB =========================================================
//


// Essa eh uma area em user mode.
// migrou de marca de 4mb para ca, para das mais espaço para
// o kernel base.

#define USER_BASE              0x02000000    // 32 MB mark
#define SMALLSYSTEM_USERBASE   0x02000000
#define MEDIUMSYSTEM_USERBASE  0x02000000
#define LARGESYSTEM_USERBASE   0x02000000 



//
// == 64 MB =========================================================
//


#define FRAME_TABLE_START_PA (0x04000000)   // 64 mb mark. 



//
// == 128 MB =========================================================
//



//
// == 256 MB =========================================================
//


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



