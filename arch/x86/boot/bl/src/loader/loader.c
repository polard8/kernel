/*
 * File: loader.c
 *
 * Descrição:
 *     Rotinas para carregar o Kernel, os programas do sistema e os arquivos 
 * de inicialização.
 *
 * Obs: Por enquanto o módulo loader somente carrega imagens do tipo PE. (M$)
 * @todo: Incluir suporte a imgens do tipo ELF.
 * 
 * In this file:
 *     + load_kernel: Carrega o KERNEL.BIN.
 *     + load_files: Carrega IDLE.BIN, SHELL.BIN, TASKMAN.BIN.
 *
 * Históry:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     ...
 */


#include <bootloader.h>


// PE file header support.
//#define IMAGE_FILE_MACHINE_I386   0x014C  // x86
//#define IMAGE_FILE_MACHINE_IA64   0x0200  // Intel Itanium
//#define IMAGE_FILE_MACHINE_AMD64  0x8664  // x64
//Continua...



/*
//
// Progress bara support.
//

int total = 1000;
int step = 0;

//protótipos de funções locais.
size_t blstrlen(const char *s);
void DoProgress( char label[], int step, int total );
void updateProgressBar();
//...
*/


/* load_kernel: 
 * Carrega o KERNEL.BIN na memória. */
 
int load_kernel (){
	
    int Status;

	//Address.
	unsigned long kernel_pa = KERNEL_ADDRESS;                    //0x00100000.
	unsigned long kernel_va = KERNEL_VA;                         //0xC0000000.
	unsigned char *kernel = (unsigned char *) KERNEL_ADDRESS;    //0x00100000.  
	
	//Name.
	char *kernel_name = "KERNEL.BIN";
	
	//Message.
	
#ifdef BL_VERBOSE	
	printf ("load_kernel: Loading %s .. PA=%x | VA=%x \n", 
	    kernel_name, kernel_pa, kernel_va );
#endif
														
    //Carregando KERNEL.BIN no endereço físico.
	
	Status = (int) fsLoadFile ("KERNEL  BIN", kernel_pa );
    
	if (Status != 0 )
	{
        printf("load_kernel fail: Load\n");  		
        goto fail;    
	};
	
    // Update progress bar
	// updateProgressBar();
	
	/*
	 * Checando arquivo na memória. 
	 * Validação. 
	 * (Portable Executable - PE)
	 *
	 * @todo: 
	 *     Checar mais elementos do header PE.
	 */
	 
	/* 
	 * 0x14c Intel I386 (same ID used for 486 and 586).
	 * 0x14d Intel i860. ( Intel i860 (aka 80860) (32-bit) was a RISC ) 
	 * 0x1C0 ARM. ARM little endian (32-bit), ARM Holdings, later versions 
	 * 6+ used in iPhone, Microsoft Nokia N900
	 * 0x1C4. ARMv7 or IMAGE_FILE_MACHINE_ARMNT (or higher) 
	 * Thumb mode only (32 bit).
	 * 0xAA64. ARM8+ (64-bit)
     * 0x162 MIPS R3000.
     * 0x166 MIPS R4000.
	 * 0x183 DEC Alpha AXP.
	 * 0x184 Digital Equipment Corporation (DEC) Alpha (32-bit).
	 */ 
	 
	// Check for .ELF file. 0x7f 0x45 0x4c 0x46 (.ELF)	
	if ( kernel[0] != 0x7F || kernel[1] != 'E' || kernel[2] != 'L' || kernel[3] != 'F' )
	{	
	    printf ("load_kernel fail: %s Validation\n", kernel_name );  
		goto fail;	
	}


	// Check for intel i386. 0x014C.
	//if ( kernel[0] != 0x4C || kernel[1] != 0x01 )
	//{	
	//    printf ("load_kernel fail: %s Validation\n", kernel_name );  
	//	goto fail;	
	//};
	
	
	//WORD Machine.
	//WORD NumberOfSections.
	
	
	// #importante:
	// Checando se o kernel base contém o header 
	// do multiboot.
	// Obs: Para o Gramado Boot isso significa apenas
	// mais um ítem de segurança, pois o Gramado Boot
	// fará a inicialização do mesmo modo de sempre e enviará 
	// os mesmos argumentos de sempre.
	// Porém se um multiboot carregar o kernel, certamente 
	// não passará os mesmos argumentos que o Gramado Boot,
	// então o kernel inicializará de forma diferente,
	// provavelmente apenas em modo texto.

	
	// Multiboot magic signature.
    // O header está em 0xC0001000.	
	// 0x1BADB002
	// tem um jmp antes do header.
	
	if ( kernel[0x1008] != 0x02 ||
         kernel[0x1009] != 0xB0 ||
         kernel[0x100A] != 0xAD ||  		
	     kernel[0x100B] != 0x1B )
	{	    
        //
	};	
	
	//Continua ...

//Done.	
//Kernel carregado.	

#ifdef BL_VERBOSE
	printf("Done\n");
	refresh_screen();
#endif

    //Status.
	
    return (int) 0;  
	

// Fail 
// O Kernel não pôde ser carregado.	

fail:
    printf("load_kernel: Fail\n");
    abort ();
	//die();	
};


 

/*
 *************************************************************
 * load_files:
 *     Carrega os arquivos IDLE.BIN, SHELL.BIN e TASKMAN.BIN.
 *
 * In this function:
 *     + Carrega tarefas do sistema, (idle, shell ...).
 *     + ...
 *
 * @todo:
 *     Deve existir uma lista de arquivos. 
 *     Essa função carregará os arquivos da lista.
 *
 *     Mudar para loaderLoadFiles()
 */ 
 
int load_files (){
	
    int Status;   
	
    //Names.
	
    char *init_name = "INIT.BIN";
    char *shell_name = "SHELL.BIN";
	char *taskmanager_name = "TASKMAN.BIN";
	//...
	

	// @todo: Carregar mais arquivos. Especialmente os arquivos 
	// de configuração e os arquivos de componentes da interface gráfica.
	
	//@todo: Path.
	//char *root_path = "root:";
	//char *slash = "/";

	
	/*
	 * Address:
	 *     Endereços físicos para carregar os aplicativos.
	 * @todo: 
	 *     Os endereços lógicos dos aplicativos deverão ser o mesmo. 
	 * Todos terão o endereço lógico 0x00400000. Para isso, cada processo 
	 * deverá ter seu próprio diretório de páginas. Isso ainda está em fase de
	 * implementação.         
	 *
	 * Por enquanto todos processos estão usando o mesmo diretório de páginas
	 * e cada um é carregado em um endereço lógico diferente, definido à seguir.
	 */
	 
	
	// #todo:
	// Todos eles deverão ter o mesmo endereço virtual.
	// Então eles serão carregados em endereços físicos 
	// mas serão mapedos depois pelo kernel.
	
	// 0x00400000, 0x00450000, 0x004A0000; 
	
	unsigned char *init = (unsigned char *) INIT_ADDRESS;                   	 
	unsigned char *shell = (unsigned char *) SHELL_ADDRESS;                 	 
	unsigned char *taskmanager = (unsigned char *) TASKMANAGER_ADDRESS;     	 	
	//...
	
	
	// Limites: 
	// O endereço base deve estar acima do limite mínimo estabelecido 
	// para um processo de usuário.
	
	if ( INIT_ADDRESS < USER_BASE || 
	     SHELL_ADDRESS < USER_BASE || 
	     TASKMANAGER_ADDRESS < USER_BASE )
	{
	    printf("load_files fail: Address\n");
		goto fail;
	}
	
	
	// @todo: Limpar a tela.
	// Mas isso demora muito.
	
	//==================
	//0, IDLE.BIN. 
#ifdef BL_VERBOSE
	printf("load_files: Loading %s..\n", init_name );
#endif
	
	Status = (int) fsLoadFile ("INIT    BIN", INIT_ADDRESS );
	
	if (Status != 0)
    {	
	    printf("load_files: Error loading file: %s\n", init_name );
	    goto fail;
	}

    // Update progress bar
	// updateProgressBar();
	
    //==================		
	//1, SHELL.BIN.
#ifdef BL_VERBOSE
	printf ("load_files: Loading %s..\n", shell_name );
#endif

	Status = (int) fsLoadFile ("SHELL   BIN", SHELL_ADDRESS );
	
	if (Status != 0){
	    
		printf("load_files: Error loading file: %s\n",shell_name);
	    goto fail;
	};
	
    // Update progress bar
	//updateProgressBar();

    //================== 
	//2, TASKMAN.BIN.
#ifdef BL_VERBOSE
	printf("load_files: Loading %s..\n", taskmanager_name );
#endif

	Status = (int) fsLoadFile ("TASKMAN BIN", TASKMANAGER_ADDRESS );
	
	if (Status != 0){
		
	    printf("load_files: Error loading file: %s\n", taskmanager_name );
	    goto fail;
	};
	
    // Update progress bar
	//updateProgressBar();


	// Continua? 
	//     O Boot Loader pode carregar vários arquivos. Principalmete 
	// arquivos de configuração e módulos do kernel com endereço definido.
	// Pode também carregar imagens para a interface gráfica. Além de fontes e
	// drivers. 
	
	
	// #importante
	// Check for elf signature.
	// Check for .ELF file. 0x7f 0x45 0x4c 0x46 (.ELF)	
    
	// Init. 
	// Shell.
	// TaskManager.
	
    
	if ( init[0] != 0x7F || init[1] != 'E' || init[2] != 'L' || init[3] != 'F' )
	{	
	    printf ("load_files fail: %s Validation\n", init_name );  
		goto fail;	
	}
    
	if ( shell[0] != 0x7F || shell[1] != 'E' || shell[2] != 'L' || shell[3] != 'F' )
	{	
	    printf ("load_files fail: %s Validation\n", shell_name );  
		goto fail;	
	}
    
	if ( taskmanager[0] != 0x7F || taskmanager[1] != 'E' || taskmanager[2] != 'L' || taskmanager[3] != 'F' )
	{	
	    printf ("load_files fail: %s Validation\n", taskmanager_name );  
		goto fail;	
	}
    

	// Continua ...
	
    // Done!

#ifdef BL_VERBOSE
	printf("Done\n");
	refresh_screen();
#endif
    return (int) 0;  //Status.   
	
    // Fail!
	
fail:
	printf(" Fail\n");    
	abort ();
}


/*
// local
// strlen:
//     Tamanho de uma string.
// 
size_t blstrlen(const char *s)
{	
    size_t i = 0;
	
	for(i = 0; s[i] != '\0'; ++i){ 
	; 
	};
	return ( (size_t) i );
};
*/


/*
// local
// DoProgress:
//     Credits: Progress bar source code found on 
//     codeproject.com/Tips/537904/Console-simple-progress 
//
void DoProgress( char label[], int step, int total )
{
    //progress width
    const int pwidth = 72;

    //minus label len
    int width = pwidth - blstrlen( label );
    int pos = ( step * width ) / total ;
   
    int percent = ( step * 100 ) / total;

    //set green text color, only on Windows
    //SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), FOREGROUND_GREEN );
    printf("%s[", label);

    //fill progress bar with =
	int i;
    for( i = 0; i < pos; i++ ){
		printf("%c", '=');
    };
	
    //fill progress bar with spaces
    printf("% *c", width - pos + 1);
    printf("] %3d%%\r", percent);

    //reset text color, only on Windows
    //SetConsoleTextAttribute(  GetStdHandle( STD_OUTPUT_HANDLE ), 0x08 );
	
    return;	
};
*/


/*
void updateProgressBar(){
	step+=1;    
	DoProgress("Loading: ",step,total);	
	refresh_screen();	
}
*/

//
// End.
//
