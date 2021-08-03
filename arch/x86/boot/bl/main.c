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


//
// == Prototypes ==========================================
//

unsigned long init_testing_memory_size (int mb);

int LandOSLoadKernelImage(void);

void BlSetupPaging(void);



// Show menu.
void blShowMenu (void){

    int i=0;


    // Cursor.
    g_cursor_x = 0;
    g_cursor_y = 0;

    // Clear backbuffer.
    // Black color.
    clear_backbuffer();


    for (i=0; i<8; i++)
    {
        printf ("\n");

        if (MENU[i].used == TRUE)
        {
            if ( i == menu_highlight){
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


    while (1){

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

    // #todo
    // Podemos cair num shell de recuperaçcao
    // caso o carregamento der errado.


    int Status = (-1);

    // main flags.
    gdefLegacyBIOSBoot  = FALSE;
    gdefEFIBoot         = FALSE;
    gdefSafeBoot        = FALSE;
    gdefShowLogo        = FALSE;
    gdefShowProgressBar = FALSE;
    // ...


    // Set GUI.
    // VideoBlock.useGui = 1;
    // VideoBlock.useGui = 0;

    // Init.
    // See: init.c
    
    Status = (int) init();

    if (Status != 0 ){
        // #todo
    }


//++
// == Memory size ===============================

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
    __address = (unsigned long) init_testing_memory_size(2048);   
    
    // #todo
    // Temos que passar esses valores para o kernel,
    // juntamente com os valores que passsamos durante a inicialização
    // em assembly, através do boot buffer em 0x0000000000090000. 
    // See: head.s

    // LFB_VA:      0x00090000 + 0
    // WIDTH:       0x00090000 + 8
    // HEIGHT:      0x00090000 + 16
    // BPP:         0x00090000 + 24
    // LAST_VALID:  0x00090000 + 32
    // LAST_VALID:  0x00090000 + 40 (complement)
    // ...

    unsigned long *LastValid           = (unsigned long*) (0x00090000 + 32); 
    unsigned long *LastValidComplement = (unsigned long*) (0x00090000 + 36); 

    LastValid[0]           = (unsigned long) __address;
    LastValidComplement[0] = (unsigned long) 0;

    printf ("BlMain: Las valid PA = %x \n", __address);
    refresh_screen();
    //while(1){}

// =======================================
//--



    // #todo
    // Precisamos reconsiderar a necessidade de fazermos isso.
    // O timer ira atrazar a inicializa��o ?
    // Precisamos dessas interrup��es para alguma coisa como
    // o driver de ata ?

    // #debug
    // printf("habilitando as interrupcoes\n");
    // refresh_screen();

    // #todo:
    // Talvez devamos adiar esse sti.

//
// Interrupts
//

    // #todo
    // Podemos adiar isso. :)

    asm ("sti");


    // Initializes heap;
    // Used for malloc() and ide driver.
    
    printf ("BlMain: init_heap..\n");
    refresh_screen();
    
    init_heap();

    printf ("BlMain: init_hdd..\n");
    refresh_screen();

    // Initializes ide support.
    init_hdd();


    // #todo: 
    // Clean the screen.


    // Welcome Message.
    // banner


//#ifdef BL_VERBOSE
    //printf ("BlMain: Starting Boot Loader..\n");
    //refresh_screen();
//#endif

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
//#ifdef BL_VERBOSE
//    printf ("BlMain: Loading rootdir and fat ..\n");
//    refresh_screen();
//#endif


    // #todo
    // Maybe we need the return from these routines.


    // Load root dir.
    printf ("BlMain: Loading rootdir ..\n");
    refresh_screen();

    fs_load_rootdirEx();
    g_fat16_root_status = TRUE;


    // Load FAT.
    printf ("BlMain: Loading fat ..\n");
    refresh_screen();

    fs_load_fatEx();
    g_fat16_fat_status = TRUE;


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


    // ?? maybe.
    // BlLoadConfigFiles ();   


    // Loading the kernel image.
    // Helper function in this document.

    printf ("BlMain: Loading kernel image ..\n");
    refresh_screen();

    //Status = AnotherOSLoadKernelImage();
    Status = LandOSLoadKernelImage();

    if (Status<0){
         printf("BlMain: LandOSLoadKernelImage fail. \n");
         refresh_screen();
         while(1){}    
         //goto run_rescue_shell;
    }


    /*
     * 
     *  ok, depois de carregarmos a imagem do kernel de 64bit
     *  então devemos configurar o long mode e a paginação para
     *  64bit ... para por fim saltarmos para o kernel.
     * 
     * */


/*
  #todo:
 bl.bin é feito em 32bit e ainda em 32bit ele deve carregar
 o kernel que é um programa de 64bit. 
  Ao fim de sua rotina em C 32bit ele faz as configurações
  necessarias para entrar em 64bit. Poderá usar rotinas
 em assembly 64bit. 
 E por fim salta para o kernel de 64bit.
*/

    // Nesse momento ja carregamos a imagem do kernel.
    // No momento é uma imagem fake.
   
    //#todo
    //precisamos limpara a tela,
    //para visualizarmos essa mensagem na resolução 320x200

    // #test
    // background preto.
    g_cursor_x = 0;
    g_cursor_y = 0;
    clear_backbuffer();


    printf ("\n");
    printf ("\n");
    printf ("\n");
    printf ("Gramado X-BL.BIN: [main.c-BlMain()] \n");
    printf ("The 64bit kernel image is \n");
    printf ("already loaded. So now we will \n");
    printf ("setup the long mode, the paging and\n");
    printf ("jump to the kernel image\n");
    printf ("Good luck\n");

    printf("======================\n");

    //refresh_screen();
    //while(1){}

/*
    How do I enable Long Mode ?

    The steps for enabling long mode are:

    + Disable paging
    + Set the PAE enable bit in CR4
    + Load CR3 with the physical address of the PML4
    + Enable long mode by setting the EFER.LME flag in MSR 0xC0000080
    + Enable paging

    Now the CPU will be in compatibility mode, and 
instructions are still 32-bit. To enter long mode, 
+ the D/B bit (bit 22, 2nd 32-bit value) of the GDT code segment 
must be clear (as it would be for a 16-bit code segment), and 
the L bit (bit 21, 2nd 32-bit value) of the GDT code segment 
must be set. Once that is done, the CPU is in 64-bit long mode.

See:
    https://wiki.osdev.org/X86-64
    ...
*/


    // Verificar suport x86_64
    unsigned long a=0;
    unsigned long b=0;
    unsigned long c=0;
    unsigned long d=0;

    cpuid ( 
        0x80000001, 
        a, b, c, d );

    // Test LM-bit
    unsigned long data = (unsigned long) (d >> 29 );

    if ( (data & 1) != 0 ){
        printf("BlMain: x86_64 hardware supported\n");
        refresh_screen();
    }

    // #todo
    // Abort! There is nothing to do.
    if ( (data & 1) == 0 ){
        printf("BlMain: [ERROR] x86_64 hardware not supported\n");
        refresh_screen();
        while(1){
            asm ("cli");
            asm ("hlt");
        };
    }

    printf ("done\n");
    printf("======================\n");

    // #breakpoint
    //refresh_screen();
    //while(1){}

//
// No interrupts
//

    asm ("cli");
    
    
    // #bugbug
    // Talvez não devamos retornar da rotina
    // de configuração da paginação. Devendo
    // de lá mesmo chamar a rotina de salto
    // para o kernel. Pois algo pode atrapalhar nosso retorno
    // pois a pilha pode ter sido desconfigurada.
    
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


    // #debug
    printf ("BlMain: Initializing pages..  ******** \n");
    refresh_screen();

    // In this document.
    BlSetupPaging();

    // nao podemos chamar rotina alguma aqui,
    // somente retornar.
    // os registradores estao bagunçados.
    
    // Not reached
    while(1){}
    
    //return;
}


/*
 ************************************
 * LandOSLoadKernelImage: 
 * 
 *     It loads the kernel image at 0x00100000.
 *     The entry point is at 0x00101000.
 */ 

    // #todo
    // This way can chose the filename from a
    // configuration file.
    // This routine will try to load the default filename
    // if the provide name fail.

    // This routine will build the pathname
    // to search in the default folder.
    
    // Called by BlMain()

int LandOSLoadKernelImage(void)
{
    int Status = -1;

    // Standard name.
    // #todo: Maybe we need some options, some config file.

    char *image_name = "KERNEL.BIN";

    // #bugbug
    // Precisamos que essa rotina retorne
    // para termos a change de inicializarmos o
    // rescue shell. Mas acontece que por enquanto
    // essa função aborta ao primeiro sinal de perigo.


    Status = (int) elfLoadKernelImage(image_name);

    // Fail
    if ( Status != 0 )
    {
        printf ("LandOSLoadKernelImage: elfLoadKernelImage fail\n");
        refresh_screen();
        
        return (int) (-1);
    }
    
    // ok
    return Status;
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

void BlAbort()
{

	//@todo: 
	//    Talvez poderia ter uma interface antes de chamar a rotina abort().
	//
	//ex:
	//checks()

    abort(); 
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
    printf ("init_testing_memory_size: Looking for %d MB base...\n", mb);
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


