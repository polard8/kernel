/*
 * Project Land Loader. "Gramado Boot Loader"
 * 
 * (c) Copyright 2015-2020 Fred Nora.
 *
 * File: main.c 
 *
 * + It loads the kernel image.
 * + ... initializes the paging.
 * + passes the command to the kernel.
 *
 * The boot loader was loaded in the address 0x00020000, and
 * has the entry point in the address 0x00021000.
 *
 * The kernel image will be loaded in the address 0x00100000
 * and  the entry point will be in the address 0x00101000.
 * The virtual addresses are 0xC0000000 for the base and
 * 0xC0001000 for the entry point.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2020 - Revision.
 *     ... 
 */
 
 
#include <bootloader.h>



//static char *codename = "Gramado Boot";
//char kernel_file_name[] = "kernel.bin";
//static char **argv = { NULL, NULL, NULL };
//static char **envp = { NULL, NULL, NULL };



// Prototypes.

unsigned long init_testing_memory_size (int mb);

void BlLoadKernel(void);

void BlSetupPaging(void);



void blShowMenu (void){

    int i=0;


    g_cursor_x = 0;
    g_cursor_y = 0;
    clear_backbuffer();  //black
    
    for (i=0; i<8; i++)
    {
        printf ("\n");
        
        if (MENU[i].used == 1)
        {
            if( i == menu_highlight){
                printf ("* %s \n",MENU[i].string);
            }else{
                printf ("  %s \n",MENU[i].string);
            };
        }
    };
    
    refresh_screen(); 
}



void
BlMenu(void)
{
    
    char Key=0;
    
    
    // prepara o menu.
    
    MENU[0].used = 1;
    MENU[1].used = 1;
    MENU[2].used = 0;
    MENU[3].used = 0;
    MENU[4].used = 0;
    MENU[5].used = 0;
    MENU[6].used = 0;
    MENU[7].used = 0;

    menu_highlight = 1;
        
    sprintf( MENU[0].string, "menu item 0");
    sprintf( MENU[1].string, "menu item 1");    
    
    
    //mostra o menu.
    //blShowMenu(); 
    
    while(1)
    {
        blShowMenu();
        
        Key = keyboard_wait_key();
    
        switch (Key)
        {
			
			case 'x': goto ____go; break;

            case '\n':
                //goto do_execute_item;
                break;    
                
            // UP
            case 'e':
                //blMenuUP();
                break;
            
            // DOWN
            case 'd':
                //blMenuDOWN();
                break;    

            default:
                // Nothing
                break;
        };
    };
    

____go:
    return;
}


/*
 ************************************************
 * BlMain:
 * 
 *     This is the entrypoint for the C part of the boot loader.
 *     Initializes, loads the kernel image and returns to head.s.
 */

void BlMain (void){

    int Status = (-1);

    // main flags.
    gdefLegacyBIOSBoot = FALSE;
    gdefEFIBoot = FALSE;
    gdefSafeBoot = FALSE;
    gdefShowLogo = FALSE;
    gdefShowProgressBar = FALSE;
    // ...


    // Set GUI.
    // VideoBlock.useGui = 1;
    // VideoBlock.useGui = 0;

    // Init.
    
    Status = (int) init();

    if (Status != 0 ){
        // #todo
    }


//
// == Memory size ===============================
//

    // #test
    // Sondando quanta mem�ria f�sica tem instalada.
    // Faremos isso antes de mapearmos qualquer coisa e
    // antes de carregarmos qualquer arquivo.
    // #todo:
    // Temos v�rias quest�es � se considerar, como o fato de sujarmos
    // a IVT no in�cio da mem�ria.


    unsigned long __address = 0;

    // ok
    //__address = (unsigned long) init_testing_memory_size (4);
    // ok
    //__address = (unsigned long) init_testing_memory_size (64);
    // ok
    //__address = (unsigned long) init_testing_memory_size (127);  
    // 511
    //__address = (unsigned long) init_testing_memory_size (1024);   

    //para testar na m�quina real com 2048 mb instalado.
    __address = (unsigned long) init_testing_memory_size (2048);   
        
    printf ("init: address = %x \n", __address);
    refresh_screen();
    //while(1){}

//
// ========================== memory ===============================
//


    // #todo
    // Precisamos reconsiderar a necessidade de fazermos isso.
    // O timer ira atrazar a inicializa��o ?
    // Precisamos dessas interrup��es para alguma coisa como
    // o driver de ata ?

    // #debug
    // printf("habilitando as interrupcoes\n");
    // refresh_screen();

    asm ("sti");



    // Initializes heap;
    // Used for malloc() and ide driver.
    init_heap();

    // Initializes ide support.
    init_hdd();


    // #todo: 
    // Clean the screen.


    // Welcome Message.
    // banner


#ifdef BL_VERBOSE
    printf ("BlMain: Starting Boot Loader..\n");
#endif

    if (g_initialized != 1){
        printf("BlMain: g_initialized\n");
        die();
    }



    // #important:
    // ===========
    //     Daqui pra frente vamos carregar os arquivos. 
    // Lembrando que o Boot Loader ainda n�o sabe carregar de 
    // outro dispositivo se n�o IDE. 


    //
    // Inicia os carregamentos.
    //


	//Carrega arquivos.
#ifdef BL_VERBOSE
    printf ("BlMain: Loading files..\n");
    refresh_screen ();
#endif


	// #importante:
	// Carregando o diret�rio raiz e a fat na mem�ria.
	// Evitando repeti��o de carregamento.


    fs_load_rootdirEx();
    fs_load_fatEx();


    g_fat16_root_status = 1;
    g_fat16_fat_status = 1;



    // #todo
    // Podemos mostrar o menu de opções
    // imediatamente antes da opção de carregarmos o kernel.
    // Dessa forma o boot loader carregará o kernel adequado
    // de acordo com o ítem selecionado no menu, que pode ser
    // uma aplicação ou modo diferente de inicialização.

    /*
     #bugbug: It hangs the system.
    BlMenu();
    printf("hang\n"); 
    refresh_screen();
    while(1){}
    */
    
    
    
    //
    // Loading files.
    //


   // Loading kernel image.
    BlLoadKernel();


    // ?? maybe.
    // BlLoadConfigFiles ();   


	// Paging:
	//     Depois carregar o kernel e os m�dulos 
	//     nos seus endere�os f�sicos, 
	//     configura a pagina��o e 
	//     volta para o assembly para 
	//     configurar os registradores e 
	//     passar o comando para o kernel.
	//
	// #obs:
	// Essa configuraçao basica nao impede
	// que o kernel faça uma reconfiguraçao completa.


#ifdef BL_VERBOSE
    printf ("BlMain: Initializing pages..\n");
    //refresh_screen();
#endif

    BlSetupPaging();


    //g_cursor_x = 0;
    //g_cursor_y = 0;
    //clear_backbuffer();  //black


	
	//@todo: Atualizar status.

// Done:
//     Ao retornar, head.s configura CR0 e CR3.


//done:

	// Debug message.

#ifdef BL_VERBOSE
    printf ("BlMain: Done\n");
    //printf ("BlMain: LFB={%x} \n",g_lbf_pa);
    //printf ("#DEBUG: *HANG\n");
    refresh_screen ();
    while(1){};
#endif

}


/*
 ***************************************************************
 * BlLoadKernel: 
 *     It loads the kernel image at 0x00100000.
 *     The entry point is at 0x00101000.
 */ 

void BlLoadKernel(void){

    int Status = -1;

    Status = (int) load_kernel();

    if ( Status != 0 ){
        printf ("BlLoadKernel:\n");
        die();
    }
}


 
/*
 ********************************************************************
 * BlSetupPaging:
 *     Configura as p�ginas.
 *
 * In this function:
 *
 * @diretorio:
 *   page_directory = 0x9C000
 *   OBS: 
 * Esse diret�rio criado ser� usado pelas primeiros processos durante
 * essa fase de constru��o do sistema.
 *        O ideal � um diret�rio por processo.
 *        Toda vez que o kernel iniciar a execu��o de um processo ele deve 
 * carregar o endere�o do diretorio do processo em CR3.
 *       Por enquanto s� tem um diret�rio criado.
 *
 * @p�ginas:
 *   km_page_table  = 0x8C000 (RING 0).
 *   um_page_table  = 0x8E000 (RING 3).
 *   vga_page_table = 0x8F000 (RING 3).
 *   lfb_page_table = ?? (RING 3).
 *
 *  @todo: 
 *      Esses endere�os precisam ser registrados em vari�veis globais ou
 * dentro de uma estrutura para se passado para o Kernel.
* 
 *      Essa deve ser uma interface que chama as rotinas de configura��o
 * da pagina��o. 
 */

// See: pages.c
void BlSetupPaging(void)
{
    SetUpPaging();
}


/*
 ********************************************
 * BlAbort:
 *     Rotina para abortar o bootloader em caso de erro grave.
 */

void BlAbort (){


	//@todo: 
	//    Talvez poderia ter uma interface antes de chamar a rotina abort().
	//
	//ex:
	//checks()

    abort (); 
}


/*
 *****************************************************************
 * BlKernelModuleMain:
 *     Se � o kernel que est� chamando o Boot Loader na forma de 
 * m�dulo do kernel em kernel mode.
 *
 */
 
void BlKernelModuleMain (){

    printf ("BlKernelModuleMain: Boot Loader\n");
    refresh_screen ();
}



//
//================================================================
// begin - Testing memory size
//================================================================
//

//interna
unsigned long init_testing_memory_size (int mb)
{
    unsigned char *BASE = (unsigned char *) 0;  
    
    int offset=0; 
    int i=0;

    // Salvando os valores durante o test.
    unsigned char ____value1 = 0;             
    unsigned char ____value2 = 0;                 
    
    
    //
    // Flag.
    //

    // Acionando flag.
    ____testing_memory_size_flag = 1;



    printf ("=========================================\n");
    printf ("__testing_memory_size: Looking for %d MB base...\n", mb);
    refresh_screen();


    // Come�amos em 4MB porque o kernel est� no primeiro mega.
    for (i=1; i< (mb+1); i++)
    {

        //printf ("i=%d \n", i);
        //refresh_screen();

        offset = 0x00100000 * i;
        
        //printf ("coloca \n");
        //refresh_screen();
         
         
         // #bugbug
         // cuidado com ponteiro nulo.
         
        //coloca.
        BASE[offset +0] = 0xAA;  //1
        BASE[offset +1] = 0x55;  //2
        
        
        //printf ("retira \n");
        //refresh_screen();

        //retira dois chars.
        ____value1 = BASE[offset +0];
        ____value2 = BASE[offset +1];
        
        
        
        
        // Se retiramos os mesmos bytes que colocamos.
        if (____value1 == 0xAA && ____value2 == 0x55)
        {
            //salvamos o �ltimo endere�o de mem�ria v�lido.
            __last_valid_address =  (unsigned long) &BASE[offset];
        
            // continua sondando.

        // Se n�o conseguimos retirar os mesmos bytes que colocamos
        // e n�o tivemos uma exce��o.
        }else{

            ____testing_memory_size_flag = 0;
            
            printf ("__testing_memory_size: out of range with no exception! \n");
            printf ("__testing_memory_size: last valid address = %x \n", 
                __last_valid_address);
            refresh_screen();
            
            
            ____testing_memory_size_flag = 0;
            return __last_valid_address;
            
            /*
            while(1)
            {
                asm ("cli");
                asm ("hlt");
            }
            */
        }
    };


     ____testing_memory_size_flag = 0;        
            
    // ok temos um endere�o de mem�ria
    // tamb�m ser� salvo em uma vari�vel global para o caso de panic.
    return __last_valid_address;
}
 
//
//================================================================
// end - Testing memory size
//================================================================
//



/*
 *******************************************
 * die:
 *     CLI HLT routine.
 *     No return!
 */

// See: bootloader.h

void die(void){

    printf ("BL.BIN: [DIE] * System Halted\n");
    refresh_screen();

    while (1){
        asm ("cli");
        asm ("hlt");
    };
}


//
// End.
//


