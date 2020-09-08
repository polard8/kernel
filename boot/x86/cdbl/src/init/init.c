/*
 * File: init.c
 *
 * Descrição:
 *     Rotinas de inicialização do Boot Loader.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 */


#include <bootloader.h>


// Funções importadas.

extern unsigned long SavedBootMode;


/*
 *****************************************
 * set_up_color:
 *     Configura cor padrão para o sistema.
 */
void set_up_color (unsigned long color){   
	
	g_system_color = (unsigned long) color;	
};


/*
 ***************************************************************
 * set_up_text_color:
 *     Atribui o primeiro plano e o fundo.
 *
 *     Top 4 bytes are the background, 
 *     bottom 4 bytes are the foreground color.
 *     @todo: Acho que eu quiz dizer bits.
 *
 *     @todo: Checar o tamanho da variável g_char_attrib. 
 */
void set_up_text_color ( unsigned char forecolor, unsigned char backcolor ){
	
    g_char_attrib = (backcolor << 4) | (forecolor & 0x0F);
};


/*
 *****************************************
 * init_globals:
 *     Inicia variáveis globais.
 *     @Mudar para BlInitGlobals();
 *     o retorno por ser int.
 */
//void BlInitGlobals() 
void init_globals (){
	
	// Próximo procedimento, status and file system type.
	// 1=fat16.
		
	g_next_proc = (unsigned long) bl_procedure;
	g_proc_status = 0;
	g_file_system_type = 1;	
	//Continua...
	
	//
	// Procedure structure. @todo Check.
	//
	
	procedure_info.next = (unsigned long) bl_procedure;
	procedure_info.status = 0;		
    //Continua...
    
	//?? @todo: Deletar.
	proximo = 0;
};


/*
 ***************************************************
 * init:
 *     Função principal do arquivo init.c.
 */
 
int init (){
	
	g_cursor_x = 0;
	g_cursor_y = 0;		
	
	// Inicializando o vídeo.
	
	//@todo: Inicializar estruturas de vídeo.
	
    //Selecionando modo de vídeo.	
	
	if (SavedBootMode == 1)
	{
	    VideoBlock.useGui = 1;	
	}else{
		VideoBlock.useGui = 0;
	};

#ifdef BL_VERBOSE	
	//Debug Message.
    //Se estivermos usando modo gráfico (GUI.)	
	if (VideoBlock.useGui == 1)
	{
        printf("init: Using GUI\n");
	};
#endif

	//Se não estivermos usando GUI.(text mode).
	//Limpa a tela.
	//Branco em preto.
	
	if (VideoBlock.useGui != 1)
	{	
        bl_clear (0);	                      
	    set_up_text_color (0x0F, 0x00);
		
		printf("init: Text Mode\n");
	};
	
	//
	// Inicializando o Boot Loader.
	//
		
	//Título.
#ifdef BL_VERBOSE
	printf ("init: Boot Loader Version %s \n", BL_VERSION );	
#endif

    //globais.	
#ifdef BL_VERBOSE	
	printf("init: Globals..\n");
#endif	
    init_globals();
	
    //sistema de arquivos.
#ifdef BL_VERBOSE	
	printf("init: file system..\n");
#endif
    fsInit();
	
	
	//inicia o shell do bootloader.
#ifdef BL_VERBOSE	
	printf("init: BL-Shell..\n");	
#endif
	shellInit();    //Inicializando variáveis.
	
#ifdef BL_VERBOSE
	printf("init: Timer..\n");		
#endif
	BltimerInit();	
	
	//
	// Type:
	//     CD, HD, PXE, FLASH, FAT16 ...
    //
	
/*	
	switch(BootType)
	{
	    case BOOT_TYPE1:
            break; 		

		case BOOT_TYPE1:
            break; 		

	    case BOOT_TYPE1:
            break;

        //...			

		default:
		    //printf("init: Boot type unknow!\n");
            //BlAbort();			
            break;			
	};
	
*/


    //
	// @todo:
	//     Check VESA configuration.
	//     Porque vesa foi configurado pelo Mass Storage Manager.(MSM)(BootManager)
	//
	//BlCheckVESA();


	
	//@todo:
	//Pega o valor herdado do Boot Manager.
	//LegacyCR3 = (unsigned long) GetCR3();
	
	
	//Enable a20? não parece necesário. já foi feito.
	
	//Inicializar os segmentos do sistema.(GDT).(data e code)
	
	//
	// Continua ...
	//
	
// Done 
done:
    //printf("habilitando as interrupcoes\n");
	//refresh_screen();
	
    //Habilita as interrupções. #CUIDADO!
	//?? Isso é realmente necessário ??
	asm ("sti");
	
	//debug
	//printf("#DEBUG");
	//refresh_screen();
	//while(1){}		
	
    g_initialized = (int) 1;    
    return (int) 0;  
};


//
// End.
//

