
// x64info.c
// handle x64 cpu informations.

#include <kernel.h>


void x64_info(void)
{
    printf("\n");
    printf("x64 CPU Info:\n");
    printf("\n");
    printf("Number of processors: {%d}\n", g_processor_count);

    show_cpu_intel_parameters();
}

/*
 * show_cpu_intel_parameters:
 *     Mostra os parametros da CPU intel.
 * #todo: 
 *     Colocar em janela. 
 *     Criar funções: TerminalShowCPUIntelParameters()
 *                    ShowCPUIntelParameters()
 */

void show_cpu_intel_parameters(void)
{

    printf("\n");

// #todo
// Check the pointer validation?

    if ( (void*) processor == NULL )
        panic("show_cpu_intel_parameters: processor\n");

// Vendor and brand.
    printf("        Vendor: {%s}\n", &processor->Vendor[0] );
    printf("           Cpu: {%s}\n", &processor->BrandName[0] );

// HV - Hypervisor
// #todo: pegamos o vhName apenas para AMD, precisamos
// fazer o mesmo para intel.

    printf("             HV: {%s}\n", &processor->hvName[0] );

    printf("       Stepping: {%d}\n", 
        (unsigned long) processor->Stepping_ID );
    printf("          Model: {%d}\n", 
        (unsigned long) processor->Model );
    printf("         Family: {%d}\n", 
        (unsigned long) processor->Family_ID );
    printf(" Processor Type: {%d}\n", 
        (unsigned long) processor->Processor_Type );
    printf(" Extended Model: {%d}\n", 
        (unsigned long) processor->Extended_Model_ID );
    printf("Extended Family: {%d}\n", 
        (unsigned long) processor->Extended_Family_ID );
    //printf("ApicSupport={%x}\n", processor->isApic);
    printf("    Max feature: {%d}\n", 
        (unsigned long) processor->MaxFeatureId );
    //Bits 0-7: Cache Line Size.
    printf("   L2 line size: {%d Byte}\n", 
        (unsigned long) processor->L2LineSize ); 

// L2 Associativity. 
// Bits 12-15: L2 Associativity.
   
    unsigned long L2Associativity = processor->L2Associativity;

    switch (L2Associativity){
    case 0x00:  printf ("L2 Associativity: {Disabled}\n");           break; 
    case 0x01:  printf ("L2 Associativity: {Direct mapped}\n");      break; 
    case 0x02:  printf ("L2 Associativity: {2-way associative}\n");  break; 
    case 0x04:  printf ("L2 Associativity: {4-way associative}\n");  break; 
    case 0x06:  printf ("L2 Associativity: {8-way associative}\n");  break; 
    case 0x08:  printf ("L2 Associativity: {16-way associative}\n"); break; 
    case 0x0F:  printf ("L2 Associativity: {Fully associative}\n");  break; 
    };

//
// Cache
//

//Bits 16-31: Cache size in 1K units.
    printf("    L2 cache size: {%d KB}\n", 
        (unsigned long) processor->L2Cachesize ); 

//
// Physical and Virtual Address.
//

// Provavelmente é o número máximo de bits na arquitetura.
// tanto em memória física como virtual.
// 36 ou 39 indica memória extendida. normal é 32=(4GB).
// maximum physical address bits  
//maximum linear (virtual) address bits 

    printf("          PA Lim: {%d}\n", 
        (unsigned long) processor->Physical_Address_Size );
    printf("          VA Lim: {%d}\n", 
        (unsigned long) processor->Virtual_Address_Size );

    
    //printf("     Memory Size: {%d}\n",(unsigned long) processor->MemorySize);

// apic
    if (processor->hasAPIC == TRUE){
        printf("It has APIC\n");
    }
    if (processor->hasAPIC != TRUE){
        printf("No APIC!\n");
    }

// x87
    if (processor->hasX87FPU == TRUE){
        printf("It has a x87 FPU\n");
    }
    if (processor->hasX87FPU != TRUE){
        printf("No x87 FPU!\n");
    }

// HTT
    if (processor->hasHTT == TRUE){
        printf("It has a HTT\n");
    }
    if (processor->hasHTT != TRUE){
        printf("No HTT!\n");
    }


// LAPIC
    if(LAPIC.initialized == TRUE){
        printf("LAPIC.lapic_pa %x \n",LAPIC.lapic_pa);
        printf("LAPIC.lapic_va %x \n",LAPIC.lapic_va);
        printf("LAPIC.entry    %d \n",LAPIC.entry);
    }else{
        printf("[ERROR] LAPIC not initialized\n");
    };

    // Continua ...

// Show
// #obs:
// Como não usamos janelas no kernel, 
// então devemos dar refresh na tela todo por enquanto.

    refresh_screen();
}

//
// End
//
