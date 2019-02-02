/*
 * File: memmap.h
 *
 * Descrição:
 *     Header para informações sobre a memória. 
 *     Referência para localização de VBR, FAT, ROOT, DATAAREA e outros.
 *
 * ATENÇÃO: 
 *     Kernel base = 0x00100000.
 *     vbr  =  
 *     fat  =  ;
 *     root =  ;
 *
 *     Cuidado na escolha dos endereços para fat, root.
 *     @todo Deixar espaço o bastante para um kernel grande. 
 *           Começando em 0x00100000
 *
 * Versão 1.0, 2015 - Created.
 * Versão 1.0, Oct 2016 - Revision. 
 */
 

/*
    Memory map.
	Para o processo do kernel.
	Obs: Algumas áreas serão comuns entre processos
	     Como o LFB, o BackBuffer, o Kernel. 
	
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
             |  Stack =    | Pilha do Kernel. 
	         |  Heap  =     |	Obs: O Heap do kernel precisa ser maior.
             |                                    | 			 
			 |  Kernel Entry point = 0xC0001000   |      Entry point do kernel.
	         |  Kernel Base = 0xC0000000          |	     Início da imágem do processo kernel. 
	C0000000 |         Kernel Mode access         |	 	   
	         +------------------------------------+
             |           User Land                |	 
	         |                                    |
             |      | @todo  Início da pilha em user mode do proesso.
	         |      | @todo: Início do heap em user mode do processo.
             |                                    | ### Por enquando cada processo tem sua própria
             |                                    |     pilha e heap no fim da imagem do processo.   			 
             |  .           | ??
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
			 
 
 
*/


// 
// Bug Bug !! 
// @todo: 
//     Endereços não implementados, usando VBR ?? por enquanto.
//
//


#define MBR_ADDRESS     0x7C00              
#define FS_MBR_ADDRESS  0x7C00              
#define FS_VBR_ADDRESS  (0x7C00 + 0x200)    

#define FS_FAT_ADDRESS      (0x1000000 - 0x400000)  
#define FS_ROOTDIR_ADDRESS  (0x1000000 - 0x100000)  


//
// Fat support.  fat16, fat12.
//

#define FAT12_VBR_ADDRESS     FS_VBR_ADDRESS
#define FAT12_FAT_ADDRESS     FS_FAT_ADDRESS
#define FAT12_ROOTDIR_ADDRESS FS_ROOTDIR_ADDRESS

#define FAT16_VBR_ADDRESS     FS_VBR_ADDRESS
#define FAT16_FAT_ADDRESS     FS_FAT_ADDRESS
#define FAT16_ROOTDIR_ADDRESS FS_ROOTDIR_ADDRESS

//#define FAT32_VBR_ADDRESS     FS_VBR_ADDRESS
//#define FAT32_FAT_ADDRESS     FS_FAT_ADDRESS
//#define FAT32_ROOTDIR_ADDRESS FS_ROOTDIR_ADDRESS


/*
 * Referências para memória de vídeo.
 */
#define BL_TEXT_MODE_BASE    0x000B8000
#define BL_GRAPHIC_MODE_BASE 0x000A0000

//
// End.
//

