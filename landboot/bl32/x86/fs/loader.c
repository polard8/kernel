/*
 * File: fs/loader.c
 *
 * Descri��o:
 *     Rotinas para carregar o Kernel, os programas do sistema e os 
 * arquivos de inicializa��o.
 *
 * Obs: Por enquanto o m�dulo loader somente carrega imagens do tipo PE. (M$)
 * @todo: Incluir suporte a imgens do tipo ELF.
 * 
 * In this file:
 *     + elfLoadKernelImage: Carrega o KERNEL.BIN.
 *     + load_files: 
 *
 * History:
 *     2015 - Created by Fred Nora.
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

//prot�tipos de fun��es locais.
size_t blstrlen(const char *s);
void DoProgress( char label[], int step, int total );
void updateProgressBar();
//...
*/



/* 
 ******************************************** 
 * elfLoadKernelImage: 
 *     Carrega o KERNEL.BIN na mem�ria. 
 */

// Address.
// pa = 0x00100000.
// va = 0xC0000000.

// Called by LandOSLoadKernelImage()

int elfLoadKernelImage (const char *file_name)
{
    int Status = -1;

    unsigned long kernel_pa = KERNEL_ADDRESS;
    unsigned long kernel_va = KERNEL_VA;

    // Buffer.
    // 0x00100000.

    unsigned char *kernel = (unsigned char *) KERNEL_ADDRESS;      


    // Path
    char Path[64];
    char DefaultPath[64];

    // Name.

    char *kernel_name;
    kernel_name = file_name;


    // Message.

#ifdef BL_VERBOSE
    printf ("elfLoadKernelImage: Loading %s .. PA=%x | VA=%x \n", 
        kernel_name, kernel_pa, kernel_va );
#endif


    //
    // Load kernel image
    //


    // The name given by function parameter.
    strcpy (Path, "/GRAMADO");
    strcat (Path, "/");
    strcat (Path, kernel_name );

    // Default
    strcpy (DefaultPath, "/GRAMADO/KERNEL.BIN");


    // Load KERNEL.BIN on a physical address.
    // Search the file in the /LANDOS/ and /BOOT/ subdirectories
    // of the boot partition.
    // See: fs.c

    Status = (int) load_path( Path, (unsigned long) kernel_pa );

    // Fail
    // Try default name.

    if ( Status != 0 ){
        // Try again
        Status = (int) load_path( DefaultPath,(unsigned long) kernel_pa );
    }

    // Fail.
    if (Status != 0 ){
        printf("elfLoadKernelImage: [FAIL] Couldn't load the kernel image\n");
        goto fail;    
    }


    //
    // Check signature.
    //

    // Check for .ELF file signature. 
    // 0x7f 0x45 0x4c 0x46 (.ELF)

    if ( kernel[0] != 0x7F || 
         kernel[1] != 'E' || kernel[2] != 'L' || kernel[3] != 'F' )
    {
        printf ("elfLoadKernelImage: [FAIL] %s ELF image validation\n", 
            kernel_name ); 
        goto fail;
    }


	//WORD Machine.
	//WORD NumberOfSections.
	
	
	// #importante:
	// Checando se o kernel base cont�m o header 
	// do multiboot.
	// Obs: Para o Gramado Boot isso significa apenas
	// mais um �tem de seguran�a, pois o Gramado Boot
	// far� a inicializa��o do mesmo modo de sempre e enviar� 
	// os mesmos argumentos de sempre.
	// Por�m se um multiboot carregar o kernel, certamente 
	// n�o passar� os mesmos argumentos que o Gramado Boot,
	// ent�o o kernel inicializar� de forma diferente,
	// provavelmente apenas em modo texto.

	
    // Multiboot magic signature.
    // O header est� em 0xC0001000.
    // 0x1BADB002
    // tem um jmp antes do header.

    if ( kernel[0x1008] != 0x02 ||
         kernel[0x1009] != 0xB0 ||
         kernel[0x100A] != 0xAD || 
         kernel[0x100B] != 0x1B )
    {

		//#debug
		printf ("elfLoadKernelImage: [FAIL] 0x1BADB002 found!\n");
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


    // =================================

// Fail 
// O Kernel n�o p�de ser carregado.

fail:

    printf ("elfLoadKernelImage: Fail\n");
    refresh_screen();

    // #test
    // Vamos retornar para dar a chace ao rescue shell.
    // abort();
    
    return (int) (-1);
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
