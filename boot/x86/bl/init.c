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


// Variaveis herdadas do boot manager

// O modo de boot. gui or cli.
extern unsigned long SavedBootMode;

// Endereço do boot block
extern unsigned long SavedBootBlock;   

// device info
//extern unsigned long SavedLFB;
//extern unsigned long SavedX;
//extern unsigned long SavedY;
//extern unsigned long SavedBPP;





/*
 *****************************************
 * set_up_color:
 *     Configura cor padrão para o sistema. */

void set_up_color (unsigned long color)
{   
    g_system_color = (unsigned long) color;
}


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

void 
set_up_text_color ( 
    unsigned char forecolor, 
    unsigned char backcolor )
{
    g_char_attrib = (backcolor << 4) | (forecolor & 0x0F);
}


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

	// Procedure structure. 
	// @todo Check.

	procedure_info.next = (unsigned long) bl_procedure;
	procedure_info.status = 0;
    //Continua...
}


/*
 ***************************************************
 * init:
 *     Função principal do arquivo init.c.
 */
 
//int init (int ?){ 

int init (){

    g_cursor_x = 0;
    g_cursor_y = 0;

	// Inicializando o vídeo.


	// #todo: 
	// Inicializar estruturas de vídeo.

    //Selecionando modo de vídeo.	

    if (SavedBootMode == 1){
        VideoBlock.useGui = 1;
    }else{
        VideoBlock.useGui = 0;
    };


#ifdef BL_VERBOSE	
    //Debug Message.
    //Se estivermos usando modo gráfico (GUI.)	
    if (VideoBlock.useGui == 1)
    {
        // #importante
        // Essa é a primeira mensagem, ela aparece nos modos 0x115 e 0x118
        printf("init: Using GUI\n");
    }
#endif


	// Se não estivermos usando GUI.(text mode).
	// Limpa a tela.
	// Branco em preto.

    if (VideoBlock.useGui != 1)
    {
        bl_clear (0);
        set_up_text_color (0x0F, 0x00);

        printf ("init: Text Mode\n");
    }



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
    init_globals ();



    //
    // == boot block ===========================
    //
    
    // Vamos pegar as informaçoes no boot block passado pelo
    // BM e salvarmos na estrutura no BL.
    // Eh melhor copiar do que simplesmente fazer referencia.
    // Vamos copiar em ordem.
    // See: gdef.h
    
    unsigned long *base = (unsigned long *) SavedBootBlock;
    
    BootBlock.lfb                = (unsigned long) base[0]; // 0
    BootBlock.x                  = (unsigned long) base[1]; // 4
    BootBlock.y                  = (unsigned long) base[2]; // 8
    BootBlock.bpp                = (unsigned long) base[3]; // 12
    BootBlock.last_valid_address = (unsigned long) base[4]; // 16
    BootBlock.metafile_address   = (unsigned long) base[5]; // 20
    BootBlock.disk_number        = (unsigned long) base[6]; // 24
    BootBlock.heads              = (unsigned long) base[7]; // 28
    BootBlock.spt                = (unsigned long) base[8]; // 32 
    BootBlock.cylinders          = (unsigned long) base[9]; // 36
    BootBlock.boot_mode          = (unsigned long) base[10]; // 40
    BootBlock.gramado_mode       = (unsigned long) base[11]; //  44

    // #debug
    // vamos mostrar as informaçoes do boot block
    
    // OK
    //printf ("Gramado mode %d\n",BootBlock.gramado_mode);
    //refresh_screen();
    //while(1){}



    //sistema de arquivos.
#ifdef BL_VERBOSE	
	printf("init: file system..\n");
#endif
    fsInit();



    //inicia o shell do bootloader.
    //Inicializando variáveis.
#ifdef BL_VERBOSE	
	printf("init: BL-Shell..\n");
#endif
	shellInit();    



#ifdef BL_VERBOSE
	printf("init: Timer..\n");
#endif
	BltimerInit();




	// Type:
	//     CD, HD, PXE, FLASH, FAT16 ...
	
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



	// Inicializar os segmentos do sistema.(GDT).
	// (data e code)

	// #todo:
	// Pega o valor herdado do Boot Manager.
	// LegacyCR3 = (unsigned long) GetCR3();	



	//
	// Continua ?
	//

    g_initialized = (int) 1; 
    return 0;  
}


//
// End.
//

