
//gpa.h 
//Endereços físicos usados pelo kernel base.


#ifndef ____GPA_H
#define ____GPA_H 1


// primeiros 4 mb.
#define SMALLSYSTEM_ORIGIN_ADDRESS   0
#define MEDIUMSYSTEM_ORIGIN_ADDRESS  0
#define LARGESYSTEM_ORIGIN_ADDRESS   0



// #importante: PERIGO !!!
// >>>> 0x1000
// O sistema está usando esse endereço como início de um heap
// onde pegamos páginas de memória para criarmos diretórios de páginas.
// Isso porque precisamos de endereços que terminem com pelo menos 
// 12bits zerados.
// #todo: 
// Precisamos encontrar outro lugar para esse heap, tendo em vista que
// o número de diretórios criados será grande e o heap invadirá 
// outras áreas.
// me parece que o próximo endereço usado é o MBR em 0x00020000. 
// #todo: Possivelmente podemos mudar o MBR de lugar usando o alocador.
// #OBS: Os endereços físico e virtual são iguais.
// See: mm/x86/pages.c

// #define CREATE_DIRECTORY_HEAP_BASE 0x1000



#define VM_BASE                0x000B8000  //Físico.
#define KERNEL_TEXT_MODE_BASE  0x000B8000
#define SMALLSYSTEM_VGA        0x000B8000  //VM_BASE
#define MEDIUMSYSTEM_VGA       0x000B8000  //VM_BASE
#define LARGESYSTEM_VGA        0x000B8000  //VM_BASE


#define KERNEL_GRAPHIC_MODE_BASE  0x000A0000
#define MEM_BASE                  0x000A0000  //KERNEL_GRAPHIC_MODE_BASE


//Podemos alocar memória para isso, liberando esse espaço?
#define MBR_ADDRESS            0x00020000  

//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_VBR_ADDRESS   (0x00020000 + 0x200) 
#define VOLUME2_VBR_ADDRESS   (0x00020000 + 0x200) 

//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_FAT_ADDRESS   0x00030000 
#define VOLUME2_FAT_ADDRESS   0x00030000

//Podemos alocar memória para isso, liberando esse espaço?
#define VOLUME1_ROOTDIR_ADDRESS 0x00070000 
#define VOLUME2_ROOTDIR_ADDRESS 0x00070000 



//
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

//#define PAGETABLE_RES7         0x00080000
#define PAGETABLE_RES6         0x00081000
#define PAGETABLE_RES5         0x00082000

//#test
//tantando mapear alguma coisa para ahci
#define PAGETABLE_AHCI1         0x00083000   //AHCI 1


#define PAGETABLE_EXTRAHEAP3  0x00084000
#define PAGETABLE_EXTRAHEAP2    0x00085000
#define PAGETABLE_EXTRAHEAP1     0x00086000



#define PAGETABLE_HEAPPOOL     0x00087000  //POOL DE HEAPS;

#define PAGETABLE_NIC1         0x00088000  //NIC 1

#define PAGETABLE_PAGEDPOOL    0x00089000

#define PAGETABLE_BACKBUFFER   0x0008A000
#define BUFFER_PAGETABLE       0x0008A000  // BackBuffer. BACKBUFFER_PAGETABLE

#define PAGETABLE_FRONTBUFFER  0x0008B000
#define LFB_PAGETABLE          0x0008B000  // LFB.        FRONTBUFFER_PAGETABLE

#define PAGETABLE_VGA          0x0008C000
#define VGA_PAGETABLE          0x0008C000  // Pagetable para o VGA em user mode.

#define PAGETABLE_USERBASE     0x0008D000
#define UM_PAGETABLE           0x0008D000  // Pagetable para o aplicativos em user mode.

#define PAGETABLE_KERNELBASE   0x0008E000
#define KM2_PAGETABLE          0x0008E000  // Pagetable para 'O Kernel'. A 'imagem'.

#define PAGETABLE_KERNELAREA   0x0008F000
#define KM1_PAGETABLE          0x0008F000 // Pagetable para o kernel mode stuff.


//O endereço físico e virtual são iguais.
#define XXXKERNEL_PAGEDIRECTORY 0x0009C000



// ??
// Temos uma pilha aqui ??
// 0x0009FFF0 ??


//
// #### 1 MB ####
//


#define KERNEL_BASE              0x00100000  // 1MB físico.
#define SMALLSYSTEM_KERNELBASE   0x00100000  // KERNEL_BASE
#define MEDIUMSYSTEM_KERNELBASE  0x00100000  // KERNEL_BASE
#define LARGESYSTEM_KERNELBASE   0x00100000  // KERNEL_BASE



//
// #### 4 MB ####
//


//#todo
//change this address to give to kernel more space.
//maybe we can load in this extra mg a library
#define USER_BASE              0x00400000  // 4MB físico.
#define SMALLSYSTEM_USERBASE   0x00400000  // USER_BASE
#define MEDIUMSYSTEM_USERBASE  0x00400000  // USER_BASE
#define LARGESYSTEM_USERBASE   0x00400000  // USER_BASE 



//
// #### 8 MB ####
//


//16-8 = 8
#define SMALLSYSTEM_BACKBUFFER       0x800000  //(0x01000000 - 0x800000)  
#define MEDIUMSYSTEM_BACKBUFFER      0x800000  //(0x01000000 - 0x800000) 
#define LARGESYSTEM_BACKBUFFER       0x800000  //(0x01000000 - 0x800000)  


//16-4 = 12
#define SMALLSYSTEM_PAGEDPOLL_START   0xC00000  //(0x01000000 - 0x400000) 
#define MEDIUMSYSTEM_PAGEDPOLL_START  0xC00000  //(0x01000000 - 0x400000) 
#define LARGESYSTEM_PAGEDPOLL_START   0xC00000  //(0x01000000 - 0x400000) 


//
// #### 16 MB ####
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
// #### 32 MB ####
//

#define FRAME_TABLE_START (0x02000000)   // 32mb mark. 


//
// #### 64 MB ####
//


//
// #### 128 MB ####
//


//
// #### 256 MB ####
//

// Área de memória para uma frame table grande.
// De onde pegaremos os frames para mapearmos.
// É um heap grande de frames.
// #perigo: Cuidado com a colisão com as próximas
// entradas indicadas nessa lista.

// A frame table começa aqui e vai até o fim da memória ram
// disponível ou até um limite.





//
// #### 512 MB ####
//

/*
    0x01000000 (16MB)
    0x02000000 (32MB)
    0x04000000 (64MB)
    0x08000000 (128MB)
    0x10000000   = 256 MB 
    0x20000000   = 512 MB
    0x40000000   = 1 GB
    0x50000000   = 1.24 GB
    0x60000000   = 1.5 GB
    0x70000000   = 1.75 GB
    0x80000000   = 2 GB
*/



#endif    



