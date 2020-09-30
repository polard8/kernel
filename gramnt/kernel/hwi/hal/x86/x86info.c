/*
 * File: x86info.c
 * 
 * 
 */


#include <kernel.h>



// #test
void x86_info (void)
{
    // ...
    show_cpu_intel_parameters();
}


/*
 * show_cpu_intel_parameters:
 *     Mostra os parametros da CPU intel.
 *
 * @todo: 
 *     Colocar em janela. 
 *     Criar funções: TerminalShowCPUIntelParameters()
 *                    ShowCPUIntelParameters()
 */

void show_cpu_intel_parameters (void){

    // Title.
    // printf("=============\n");
    printf("\n x86 CPU Info: *\n\n");


    if ( (void *) processor == NULL ){
        debug_print ("show_cpu_intel_parameters: processor\n");
        return;
    }


    // Vendor, 
    // Name, 
    // is apic supported ?, 
    // Max feature id,
    // L2 Line size, 
    // L2 cache size,
    // ...

    // Vendor.
    printf("          Vendor: {%s}\n", &processor->Vendor[0] );
    
    // Brand name.
    printf("             Cpu: {%s}\n", &processor->BrandName[0] );
    
    //printf("ApicSupport={%x}\n", processor->isApic);
    
    //
    printf("  Max feature id: {%d}\n", 
        (unsigned long) processor->MaxFeatureId );

    // L2 line size.
    // Bits 0-7: Cache Line Size.
    printf("    L2 line size: {%d Byte}\n", 
        (unsigned long) processor->L2LineSize ); 


    // L2 Associativity. 

    switch (processor->L2Associativity){

        //Bits 12-15: L2 Associativity.
        case 0x00:
            printf ("L2 Associativity: {Disabled}\n");
            break; 
        case 0x01:
            printf ("L2 Associativity: {Direct mapped}\n");
            break; 
        case 0x02:
            printf ("L2 Associativit: {2-way associative}\n");
            break; 
        case 0x04:
            printf ("L2 Associativity: {4-way associative}\n");
            break; 
        case 0x06:
            printf ("L2 Associativity: {8-way associative}\n");
            break; 
        case 0x08:
            printf ("L2 Associativity: {16-way associative}\n");
            break; 
        case 0x0F:
            printf ("L2 Associativity: {Fully associative}\n");
            break; 
    };

    // L2 cache size.
    // Bits 16-31: Cache size in 1K units.
    printf("   L2 cache size: {%d KB}\n", 
        (unsigned long) processor->L2Cachesize ); 


	//
	// Physical and Virtual Address.
	//
	
	//Provavelmente é o número máximo de bits na arquitetura.
	//tanto em memória física como virtual.
	//36 ou 39 indica memória extendida. normal é 32=(4GB).
	// maximum physical address bits  
	//maximum linear (virtual) address bits 

    printf("[Largest virtual and physical address sizes]\n");

    // PA lim.
    printf("          PA Lim: {%d}\n", 
        (unsigned long) processor->Physical_Address_Size );

    // VA lim.
    printf("          VA Lim: {%d}\n", 
        (unsigned long) processor->Virtual_Address_Size );


    // Memory size.
    //printf("     Memory Size: {%d}\n",(unsigned long) processor->MemorySize);


    // ...


    refresh_screen();
}


//
// End.
//
