/*
 * Arquivo: cpuamd.c
 *
 * Descrição:
 *     Rotinas para a cpu AMD.
 */


#include <kernel.h>



/*
 * get_cpu_amd_parameters:
 *     Pega os parametros da cpu AMD.
 *
 */

// #todo: Not implemented yet!

// See:
// https://www.amd.com/system/files/TechDocs/25481.pdf

// There are differences between AMD and Intel. 

void get_cpu_amd_parameters (void)
{
    unsigned long eax=0; 
    unsigned long ebx=0; 
    unsigned long ecx=0;
    unsigned long edx=0;

    unsigned long name[32];

    int MASK_LSB_8 = 0xFF;



    // #todo
    // We need to build this routine to get the amd cpu info.




    debug_print ("get_cpu_amd_parameters: [TODO]\n");

    // Vendor.
    //eax = Maximum meaningful value for the InfoType parameter. @todo:
    //ebx = Identification String (part 1)
    //ecx = Identification String (part 3)
    //edx = Identification String (part 2)

    // 0
    cpuid ( 0, eax, ebx, ecx, edx ); 
    name[0] = ebx;
    name[1] = edx;
    name[2] = ecx;
    name[3] = 0;

    processor->Vendor[0] = ebx;
    processor->Vendor[1] = edx;
    processor->Vendor[2] = ecx;
    processor->Vendor[3] = 0;

    /*
    // amd ?
    if ( ebx == CPUID_VENDOR_AMD_1 && 
         edx == CPUID_VENDOR_AMDL_2 && 
         ecx == CPUID_VENDOR_AMD_3 )
    {
        // #BUGBUG: CHECAR 
        // definir Intel como 2.
        hal_set_machine_type(2);    
    }
    */

    //========================================
    //1
    //cpuid ( 1, eax, ebx, ecx, edx );
    //ebx tem apic
   
   
    //========================================
    //cpuid ( 0x80000000, eax, ebx, ecx, edx);
    // eax: largest extended function number.

    //========================================
    // L1 cache info
    //cpuid ( 0x80000005, eax, ebx, ecx, edx );

    //========================================
    // L2 and L3 cache info
    //cpuid ( 0x80000006, eax, ebx, ecx, edx );

    //========================================
    // APM info. (power)
    //cpuid ( 0x80000007, eax, ebx, ecx, edx );


    //========================================
    // EAX=8FFFFFFFh: AMD Easter Egg


    //return; //Não implementada ainda.
}


/*
 ************************************************
 * init_amd
 * 
 */
 
// Called by init_architecture_dependent() on core/init.c

int init_amd (void)
{

    //todo:
    //trazer as rotinas da amd para esse arquivo.

    debug_print ("[x86] init_amd:");
    
    get_cpu_amd_parameters();

    return 0;
}


//
// End.
//

