
// gentry.h
// Números de entradas em diretórios de páginas. PD_ENTRY_XXX.
// Talvez possamos fazer o mesmo para page tables. PT_ENTRY_XXXX

// Número das entradas no diretório principal.
// Usado para mapear as regiões principais de memória virtual.
// Por enquanto só temos um diretório de páginas no kernel.
// Os aplicativos estão clonando o diretorio do kernel,
// depois modificando a parte referente a imagem do processo e pilha.
// See: pages.c

#ifndef ____GENTRY_H
#define ____GENTRY_H  1


// Os primeiros 2 MB de memoria virtual
//#define PD_ENTRY_RING0AREA    0

// Os segundos 2 MB de memória virtual
// Used in copy_process() in clone.c
// Pois eles clonam o pd do kernel e modificam essa entrada
// para as pts dela apontarem para o endereço físico da imagem
// do processo sendo clone.

// #bugbug
// We are still using it in clone.c
//#define PD_ENTRY_RING3AREA    1

// ...

// The kernel image goes here.
//#define PD_ENTRY_KERNELIMAGE  384

//#define PD_ENTRY_FRONTBUFFER  385
//#define PD_ENTRY_BACKBUFFER   386

// paged pool:
// Com apenas uma entrada no diretorio, então teremos
// apenas uma tabela e conseguiremos mapear
// apenas 2mb, que dá 512 páginas.
// Isso é muito pouco.
// #todo: Precisamos de várias entradas consecutivas e
// várias pt.
//#define PD_ENTRY_PAGEDPOOL    387

// Um pool usado para pegarmos pequenos heaps.
// 0x0000000030800000
//#define PD_ENTRY_HEAPPOOL     388

// Aqui foi mapeado o primeo módulo carregável do kernel.
// Esse módulo não é uma thread. Ele é chamado diretamente
// pelo kernel.
// 0x0000000030A00000
//#define PD_ENTRY_EXTRAHEAP1   389

// Mapeamos essa região mas não usamos ainda.
// 0x0000000030C00000
//#define PD_ENTRY_EXTRAHEAP2   390 

// Mapeamos essa região mas não usamos ainda.
// 0x0000000030E00000
//#define PD_ENTRY_EXTRAHEAP3   391 

// Mapeamos os registradores da lapic.
// 0x0000000031000000
//#define PD_ENTRY_LAPIC  392

// Usado pelo nic intel e1000.
// 0x0000000031200000
//#define PD_ENTRY_NIC1   393

//  ...

// #todo
// Vamos usar algumas entradas em sequência 
// para mapearmos um pagedpool maior que o ja temos.
// 400~500
// 100 * 2MB = 200MB
// 100 * 512 = 51200 páginas.
// Com 100 entradas poderemos mapear um pool de 200 MB.
// Para isso precisamos detectar memória ram o suficiente e
// e nosso pool de frames tem que ser grande o bastante
// pra todas essas páginas.
//#define PD_ENTRY_PAGEDPOOL_FIRST_ENTRY   400

//
// #importante:
// In x86_64 as tabelas possuem apenas 512 entradas.
//

#endif    


