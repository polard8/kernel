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

