/*
 *  File: mm\memmap.h 
 *
 * Descrição: 
 *     Memory map support.
 *     Referência para localização de VBR, FAT, ROOT, DATAAREA ...
 *
 * ATENÇÃO: 
 *     kernel base = 0x00100000pa
 *   
 * #bugbug: 
 *     Ao usar 0x00020000, 0x00060000, 0x00080000 a memória de video 
 * é afetada.
 *     Tem mapeamento sobreposto nessa região.
 *
 * History:
 *     2015 - Created by Fred Nora.
 */
 
 
 /*
  #importante:
  Basicamente existem 2 mapeamentos de memória:
  
  + Um usado pelo kernel e seus módulos, mesmo que esses 
    módulos estejam em user mode ou em outro processo e 
	
  + Outro mapeamento padrão para todos os processos.
  
  + ?? Não sei quanto ao mapeamento para servidores em user mode 
    ou para bibliotecas em user mode
  ...
 
  */

/*    
  Memory map. 
	
 " Cada processo tem seu diretório de páginas e uma configuração 
   de 4GB de memória virtual. "

   Mapeamento de memória para o processo kernel.
  
 " Note que no início da memória virtual temos 4MB em kernel mode. 
   Isso é usado pelo Kernel para acessar os endereços mais baixos,
   inclusive a memória de video VGA, mas a memória de vídeo VGA 
   foi novamente mapeada no endereço virtual 0x800000. "
   
			 +====================================+
             |           Kernel land              |
	         |                                    | 
             |  Stack = 0xC02F7FF0 ~ 0xC02FFFF0   | Total 32KB. 
	         |  Heap  = 0xC0100000 ~ 0xC02F7FF0   |	Total 2015 KB.
             |                                    | 			 
			 |  Kernel Entry point = 0xC0001000   | Entry point do kernel.
	         |  Kernel Base = 0xC0000000          |	Início da imagem do 
             |                                    |	processo kernel. 		 
	C0000000 |        ( Kernel Mode access )      |	 	   
	         +------------------------------------+
			 
*/

/*   

    Mapeamento padrão de memória virtual para todos os processos:
    ============================================================	


		     +------------------------------------+
	FFFFFFFF |             FIM                    |
		     +------------------------------------+
		     +------------------------------------+
		     +------------------------------------+ 
		     +------------------------------------+
	         |         User Mode access           | @todo: Mudar de lugar.  
		     |                                    |        Seder espaço para lfb.  
		     |                                    |
    C0800000 |           Back Buffer              |  			 
		     +------------------------------------+	
	         |        User Mode access            |	 Memória da placa de vídeo.
		     |             (4MB)                  |  @todo Ampliar (PRECISA SER MAIOR)
			 |             ...                    |  obs: Tamanho do monitor.
	C0400000 |             LFB                    |
		     +------------------------------------+
			 +====================================+
             |           Kernel land              |
	         |                                    | 
             |  Stack = 0xC02F7FF0 ~ 0xC02FFFF0   | Total 32KB. 
	         |  Heap  = 0xC0100000 ~ 0xC02F7FF0   |	Total 2015 KB.
             |                                    | 			 
			 |  Kernel Entry point = 0xC0001000   | Entry point do kernel.
	         |  Kernel Base = 0xC0000000          |	Início da imagem do 
             |                                    |	processo kernel. 		 
	C0000000 |        ( Kernel Mode access )      |	 	   
	         +------------------------------------+
             |           User Land                |	 
	         |                                    |
             |                                    | @todo  Início da pilha em user mode do proesso.
	         |                                    | @todo: Início do heap em user mode do processo.
             |                                    | ### Por enquando cada processo tem sua própria
             |                                    |     pilha e heap no fim da imagem do processo.   			 
             |                                    | ??
			 |                                    |
			 | 00041000 = Process entry point     | Entrypoint da imagem.
			 | 00040000 = Process image base      | Onde se carrega uma imagem de processo.
             |                                    |  			 
             | 00000000 = Dinamic Library Base    |
			 | 00000000 = Dinamic Library image   |
			 |                                    |
             |              ...                   | @todo: ampliar heap.   			 
	00000000 |       User Mode access             |	 
			 +====================================+			 
			    
  

    ***	 

			 
    ***
	
	Obs: O layout da memória virtual está em fase de desenvolvimento.	   
	
*/ 
 

//
// Referências para memória de video.
//
 
#define KERNEL_TEXT_MODE_BASE     0x000B8000
#define KERNEL_GRAPHIC_MODE_BASE  0x000A0000

#define MEM_BASE  KERNEL_GRAPHIC_MODE_BASE

#define VM_BASE      0x000B8000    //Físico.

#define KERNEL_BASE  0x00100000    //1MB físico.
#define USER_BASE    0x00400000    //4MB físico.

//Endereço virtual padrão para o Linear Frame Buffer. (LFB).
#define DEFAULT_LFB_VIRTUALADDRESS  0xC0400000 

//Endereço virtual padrão para o BackBuffer. (buffer1)
#define DEFAULT_BACKBUFFER_VIRTUALADDRESS 0xC0800000


//MEDIDAS.
//0x01000000 (16Mb)	
//0x02000000 (32Mb)
//0x04000000 (64Mb)	
//0x08000000 (128Mb)
//...	

//Onde começa a área onde alocaremos frames para os processos.
//físico ??
//Esse início será o mesmo tanto para sistemas com 32mb quanto para sistemas maiores.

//definindo o início do paged pool para sustemas pequenos. Com 32MB.

//
// SMALL SYSTEM (MÍNIMO 32MB)
#define SMALLSYSTEM_KERNELADDRESS    0
#define SMALLSYSTEM_KERNELBASE       KERNEL_BASE
#define SMALLSYSTEM_USERBASE         USER_BASE
#define SMALLSYSTEM_VGA              VM_BASE
//#define SMALLSYSTEM_FRONTBUFFER      ?? 
#define SMALLSYSTEM_BACKBUFFER       (0x01000000 - 0x400000)   
#define SMALLSYSTEM_PAGEDPOLL_START  0x01000000   //Começa em 16MB.
//...

//
// MEDIUM SYSTEM  (MÍNIMO 64MB) 
#define MEDIUMSYSTEM_KERNELADDRESS    0
#define MEDIUMSYSTEM_KERNELBASE       KERNEL_BASE
#define MEDIUMSYSTEM_USERBASE         USER_BASE
#define MEDIUMSYSTEM_VGA              VM_BASE
//#define MEDIUMSYSTEM_FRONTBUFFER      ?? 
#define MEDIUMSYSTEM_BACKBUFFER       0x01000000   
#define MEDIUMSYSTEM_PAGEDPOLL_START  0x02000000   //Começa em 32MB.
//...

//
// LARGE SYSTEM (MÍNIMO 128MB)
#define LARGESYSTEM_KERNELADDRESS    0
#define LARGESYSTEM_KERNELBASE       KERNEL_BASE
#define LARGESYSTEM_USERBASE         USER_BASE
#define LARGESYSTEM_VGA              VM_BASE
//#define LARGESYSTEM_FRONTBUFFER      ?? 
#define LARGESYSTEM_BACKBUFFER       0x01000000   
#define LARGESYSTEM_PAGEDPOLL_START  0x04000000   //Começa em 64MB.
//...


//
// Endereços físicos de algumas pagetables.
//

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
#define PAGETABLE_KERNELAREA   0x0008F000
#define PAGETABLE_KERNELBASE   0x0008E000
#define PAGETABLE_USERBASE     0x0008D000
#define PAGETABLE_VGA          0x0008C000
#define PAGETABLE_FRONTBUFFER  0x0008B000
#define PAGETABLE_BACKBUFFER   0x0008A000
#define PAGETABLE_PAGEDPOOL    0x00089000  //?? isso é um teste ... Cuidado. #bugbug
//?? Obs: Não sei o quanto podemos ir escolhendo endereços nessa região sem sobrepor o boot loader.

//
// @todo: Com as informações de backbuffer e lfb pode-se
//        fazer rotinas de pintura rápida de partes da tela, 
//        e não a tela inteira.
// 

/*
unsigned long memmapBaseMemoryStart;
unsigned long memmapBaseMemoryEnd;
unsigned long memmapOtherMemoryStart;
unsigned long memmapOtherMemoryEnd;
unsigned long memmapExtendedMemoryStart;
unsigned long memmapExtendedMemoryEnd;
*/

//
//fim.
//

