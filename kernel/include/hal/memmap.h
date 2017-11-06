/*
 *  File: hal\memmap.h 
 *
 * Descrição: 
 *     Memory map support.
 *     Referência para localização de VBR, FAT, ROOT, DATAAREA ...
 *
 * ATENÇÃO: 
 *     kernel base = 0x00100000
 *   
 * bug bug: 
 *     Ao usar 0x00020000, 0x00060000, 0x00080000 
 *     a memória de video está sendo afetada 
 *     quando usa esses endereços.
 *
 * Versão 1.0. 2015, 2016.
 */
 

/*
    Memory map. (Kernel directory)
	
 " Cada processo tem seu diretório e uma configuração de 4GB de 
   memória virtual. Essa é memória virtual do processo Kernel. "

 " Note que no início da memória virtual temos 4MB em kernel mode, 
   isso é usado pelo Kernel para acessar os endereços mais baixos,
   inclusive a memória de video VGA, mas a memória de vídeo VGA 
   foi novamente mapeada em no endereço virtual 0x800000. "  

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
             |  Stack = 0xC0300000 ~ 0xC03FFFF0   | Pilha do Kernel. 
	         |  Heap  = 0xC0100000 ~ 0xC02FFFF0   |	Obs: O Heap do kernel precisa ser maior.
             |                                    | 			 
			 |  Kernel Entry point = 0xC0001000   |      Entry point do kernel.
	         |  Kernel Base = 0xC0000000          |	     Início da imágem do processo kernel. 
	C0000000 |         Kernel Mode access         |	 	   
	         +------------------------------------+
             |           User Land                |	 
	         |                                    |
             |  Stack = 0x40300000 ~ 0x403FFFF0   | @todo  Início da pilha em user mode do proesso.
	         |  Heap  = 0x40100000 ~ 0x402FFFF0   | @todo: Início do heap em user mode do processo.
             |                                    | ### Por enquando cada processo tem sua própria
             |                                    |     pilha e heap no fim da imagem do processo.   			 
             | 40000000 = Process Base.           | ??
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

#define MEM_BASE    KERNEL_GRAPHIC_MODE_BASE

#define KERNEL_BASE  0x00100000    //1MB físico.
#define VM_BASE      0x000B8000    //Físico.
#define USER_BASE    0x00400000    //4MB físico.


//Endereço virtual padrão para o Linear Frame Buffer. (LFB).
#define DEFAULT_LFB_VIRTUALADDRESS  0xC0400000 

//Endereço virtual padrão para o BackBuffer. (buffer1)
#define DEFAULT_BACKBUFFER_VIRTUALADDRESS 0xC0800000

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

