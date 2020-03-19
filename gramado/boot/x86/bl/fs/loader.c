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
 *     + load_files: 
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



/* 
 ******************************************** 
 * load_kernel: 
 *     Carrega o KERNEL.BIN na memória. 
 */
 
int load_kernel (){

    int Status = -1;

    // Address.
    // pa = 0x00100000.
    // va = 0xC0000000.
    
    unsigned long kernel_pa = KERNEL_ADDRESS;  
    unsigned long kernel_va = KERNEL_VA;      

    // Buffer.
    // 0x00100000.
    
    unsigned char *kernel = (unsigned char *) KERNEL_ADDRESS;      


	// Name.
    char *kernel_name = "KERNEL.BIN";

	//Message.

#ifdef BL_VERBOSE	
    printf ("load_kernel: Loading %s .. PA=%x | VA=%x \n", 
        kernel_name, kernel_pa, kernel_va );
#endif


    // Carregando KERNEL.BIN no endereço físico.

    //isso funciona.
    //Status = (int) fsLoadFile ("KERNEL  BIN", kernel_pa, FAT16_ROOTDIR_ADDRESS );

    // #test
    // Carregador usando path.
    // Isso só suporta dois níveis por enquanto.
    // Caso não for encontrado no subdiretório, tenta no diretório raiz.
        
    //#importante: Esse funciona.    
    //Status = (int) load_path ( "BOOT       /KERNEL  BIN", 
                       //(unsigned long) kernel_pa );
     
    //#importante: Esse funciona.                 
    Status = (int) load_path ( "/BOOT/KERNEL.BIN", 
                       (unsigned long) kernel_pa );
    
    if ( Status != 0 ){
		
		printf("load_kernel: FAIL *hang breakpoint \n");
		refresh_screen();
		while(1){}  

        //PLANO B;
        //Status = (int) fsLoadFile ( "KERNEL  BIN", 
        //                   kernel_pa, FAT16_ROOTDIR_ADDRESS );
    }


    if (Status != 0 ){
        printf("load_kernel fail: Load\n");  
        goto fail;    
    }




	// Check for .ELF file. 0x7f 0x45 0x4c 0x46 (.ELF)	

    if ( kernel[0] != 0x7F || 
         kernel[1] != 'E' || 
         kernel[2] != 'L' || 
         kernel[3] != 'F' )
    {
        printf ("load_kernel fail: %s Validation\n", kernel_name );  
        goto fail;
    }


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
        
		//#debug
		printf ("0x1BADB002 found!\n");
		//refresh_screen();
		//while(1){}
    }



	//Continua ...

//Done.
//Kernel carregado.

#ifdef BL_VERBOSE
	printf("Done\n");
	refresh_screen();
#endif

    //Status.

    return 0; 


// Fail 
// O Kernel não pôde ser carregado.	

fail:
    printf ("load_kernel: Fail\n");
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
