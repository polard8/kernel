/*
 * File: cpuamd.c
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

    // Used by cpuid.
    unsigned long eax=0;
    unsigned long ebx=0;
    unsigned long ecx=0;
    unsigned long edx=0;

    // name.
    unsigned long name[32];

    int MASK_LSB_8 = 0xFF;



    // #todo
    // We need to build this routine to get the amd cpu info.


    // #todo
    // Check processor structure pointer validation.


    debug_print ("get_cpu_amd_parameters: [TODO]\n");

    //========================================
    //0 CPUID Fn0000_0000_EAX Processor Vendor and Largest Standard Function Number

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

    hal_set_machine_type(Processor_NULL);

    // amd ?
    if ( ebx == CPUID_VENDOR_AMD_1 && 
         edx == CPUID_VENDOR_AMD_2 && 
         ecx == CPUID_VENDOR_AMD_3 )
    {
        hal_set_machine_type(Processor_AMD);
    }

    //========================================
    //1
    // CPUID Fn0000_0001_EAX Family, Model, Stepping Identifiers
    // CPUID Fn0000_0001_EBX LocalApicId, LogicalProcessorCount, CLFlush
    // CPUID Fn0000_0001_ECX Feature Identifiers
    // CPUID Fn0000_0001_EDX Feature Identifiers
     
    cpuid ( 1, eax, ebx, ecx, edx );

    // See: https://en.wikichip.org/wiki/amd/cpuid
    processor->Stepping_ID        = (unsigned long)( eax        & 0xF);  // Stepping
    processor->Model              = (unsigned long)((eax >> 4)  & 0xf);  // Base model
    processor->Family_ID          = (unsigned long)((eax >> 8)  & 0xf);  // Base family
    processor->Processor_Type     = (unsigned long)((eax >> 12) & 0x3);  // Reserved.
    processor->Extended_Model_ID  = (unsigned long)((eax >> 16) & 0xf);  // Extended model
    processor->Extended_Family_ID = (unsigned long)((eax >> 20) & 0xff); // Extended family
    // 31 ~ 28 Reserved.


    //========================================
    // CPUID Fn0000_000[4,3,2] Reserved
    

    //========================================
    //CPUID Fn0000_0005_EAX Monitor/MWait
    //CPUID Fn0000_0005_EBX Monitor/MWait
    //CPUID Fn0000_0005_ECX Monitor/MWait
    //CPUID Fn0000_0005_EDX Monitor/MWait

    //========================================
    //CPUID Fn0000_0006_EAX Thermal and Power Management
    //CPUID Fn0000_0006_EBX Thermal and Power Management
    //CPUID Fn0000_0006_ECX Thermal and Power Management
    //CPUID Fn0000_0006_EDX Thermal and Power Management
    
    //========================================
    //CPUID Fn0000_0007_EAX_x0 Structured Extended Feature Identifiers (ECX=0)
    //CPUID Fn0000_0007_EBX_x0 Structured Extended Feature Identifiers (ECX=0)
    //CPUID Fn0000_0007_ECX_x0 Structured Extended Feature Identifiers (ECX=0)
    //CPUID Fn0000_0007_EDX_x0 Structured Extended Feature Identifiers (ECX=0)

    //========================================
    //CPUID Fn0000_000[C:8] Reserved


    //========================================
    
    //CPUID Fn0000_000D_EAX_x0 Processor Extended State Enumeration (ECX=0)
    //CPUID Fn0000_000D_EBX_x0 Processor Extended State Enumeration (ECX=0)
    //CPUID Fn0000_000D_ECX_x0 Processor Extended State Enumeration (ECX=0)
    //CPUID Fn0000_000D_EDX_x0 Processor Extended State Enumeration (ECX=0)
    
    //CPUID Fn0000_000D_EAX_x2 Processor Extended State Enumeration (ECX=2)
    //CPUID Fn0000_000D_EBX_x2 Processor Extended State Enumeration (ECX=2)
    //CPUID Fn0000_000D_ECX_x2 Processor Extended State Enumeration (ECX=2)
    //CPUID Fn0000_000D_EDX_x2 Processor Extended State Enumeration (ECX=2)
    
    //CPUID Fn0000_000D_EAX_x3E Processor Extended State Enumeration (ECX=62)
    //CPUID Fn0000_000D_EBX_x3E Processor Extended State Enumeration (ECX=62)
    //CPUID Fn0000_000D_ECX_x3E Processor Extended State Enumeration (ECX=62)
    //CPUID Fn0000_000D_EDX_x3E Processor Extended State Enumeration (ECX=62)



    // ==========================================================
    // hypervisor level 4000_0000h
    cpuid ( 0x40000000, eax, ebx, ecx, edx );
    processor->hvName[0] = ebx;
    processor->hvName[1] = ecx;
    processor->hvName[2] = edx;
    processor->hvName[3] = 0;


    //========================================
    //cpuid ( 0x80000000, eax, ebx, ecx, edx);
    // eax: largest extended function number.
    // CPUID Fn8000_0000_EAX Largest Extended Function Number
    // CPUID Fn8000_0000_E[D,C,B]X Processor Vendor
    cpuid ( 0x80000000, eax, ebx, ecx, edx);
    processor->MaxFeatureId = (unsigned long)(eax & MASK_LSB_8);
    
        
    //========================================
    // CPUID Fn8000_0001_EAX Family, Model, Stepping Identifiers
    // CPUID Fn8000_0001_EBX BrandId Identifier
    // CPUID Fn8000_0001_ECX Feature Identifiers
    // CPUID Fn8000_0001_EDX Feature Identifiers
    
    //========================================
    // CPUID Fn8000_000[4:2]_E[D,C,B,A]X Processor Name String Identifier




    /*name part 1*/
    cpuid ( 0x80000002, eax, ebx, ecx, edx);
    name[0] = eax;  //Processor Brand String
    name[1] = ebx;  //Processor Brand String
    name[2] = ecx;  //Processor Brand String
    name[3] = edx;  //Processor Brand String
    name[4] = 0;
    //salva na estrutura.
    processor->BrandName[0] = eax;
    processor->BrandName[1] = ebx;
    processor->BrandName[2] = ecx;
    processor->BrandName[3] = edx;
	//printf("CPU={%s", &name[0]);
	//printf("%s",&name[0]);

   /*name part 2*/
    cpuid ( 0x80000003, eax, ebx, ecx, edx);
    name[0] = eax;  //Processor Brand String, continued
    name[1] = ebx;  //Processor Brand String, continued
    name[2] = ecx;  //Processor Brand String, continued
    name[3] = edx;  //Processor Brand String, continued
    name[4] = 0;
	//salva na estrutura.	
    processor->BrandName[4] = eax;
    processor->BrandName[5] = ebx;
    processor->BrandName[6] = ecx;
    processor->BrandName[7] = edx;
	//printf("%s",&name[0]);

   /*name part 3*/
    cpuid ( 0x80000004, eax, ebx, ecx, edx);
    name[0] = eax; //Processor Brand String, continued
    name[1] = ebx; //Processor Brand String, continued
    name[2] = ecx; //Processor Brand String, continued
    name[3] = edx; //Processor Brand String, continued
    name[4] = 0;
	//salva na estrutura.	
    processor->BrandName[8]  = eax;
    processor->BrandName[9]  = ebx;
    processor->BrandName[10] = ecx;
    processor->BrandName[11] = edx;
	//printf("%s}\n",&name[0]);	


    
    

    //========================================
    // L1 cache info
    //cpuid ( 0x80000005, eax, ebx, ecx, edx );
    // CPUID Fn8000_0005_EAX L1 TLB 2M/4M Identifiers
    // CPUID Fn8000_0005_EBX L1 TLB 4K Identifiers
    // CPUID Fn8000_0005_ECX L1 Data Cache Identifiers
    // CPUID Fn8000_0005_EDX L1 Instruction Cache Identifiers
    

    // pegamos logo acima.
    if ( processor->MaxFeatureId < 6)
    {
        debug_print ("get_cpu_amd_parameters: Cache Extended Feature not supported\n");
        //printf("Cache Extended Feature not supported\n");
        //goto done;
        return;
    }


    //========================================
    // L2 and L3 cache info
    //cpuid ( 0x80000006, eax, ebx, ecx, edx );
    // CPUID Fn8000_0006_EAX L2 TLB 2M/4M Identifiers
    // CPUID Fn8000_0006_EBX L2 TLB 4K Identifiers
    // CPUID Fn8000_0006_ECX L2 Cache Identifiers
    // CPUID Fn8000_0006_EDX L3 Cache Identifiers

    cpuid ( 0x80000006, eax, ebx, ecx, edx );
    name[0] = eax;
    name[1] = ebx;
    name[2] = ecx;
    name[3] = edx;
    name[4] = 0;
    processor->L2LineSize      = (unsigned long)( ecx        & 0x00FF); //Bits 0-7: Cache Line Size.
    processor->L2Associativity = (unsigned long)((ecx >> 12) & 0x000F);	//Bits 12-15: L2 Associativity.
    processor->L2Cachesize     = (unsigned long)((ecx >> 16) & 0xFFFF); //Bits 16-31: Cache size in 1K units.
	//printf("L2LineSize={%d Byte}\n",(unsigned long) processor->L2LineSize);	
	//printf("L2Cachesize={%d KB}\n",(unsigned long) processor->L2Cachesize);



    //========================================
    // APM info. (power)
    //cpuid ( 0x80000007, eax, ebx, ecx, edx );
    // CPUID Fn8000_0007_E[C,B,A]X Advanced Power Management Information
    // CPUID Fn8000_0007_EDX Advanced Power Management Information

    //========================================
    // CPUID Fn8000_0008_EAX Long Mode Address Size Identifiers
    // CPUID Fn8000_0008_EBX Reserved
    // CPUID Fn8000_0008_ECX APIC ID Size and Core Count
    // CPUID Fn8000_0008_EDX Reserved
    
    cpuid ( 0x80000008, eax, ebx, ecx, edx );
    name[0] = eax;    //Virtual and physical memory sizes.
    name[1] = ebx;    //reserved
    name[2] = ecx;    //reserved
    name[3] = edx;    //reserved
    name[4] = 0;
    processor->Physical_Address_Size = (unsigned long) ( eax       & 0x00FF); //7-0
    processor->Virtual_Address_Size  = (unsigned long) ((eax >> 8) & 0x00FF); //15-8	
    //printf("Physical_Address_Size={%d}\n",(unsigned long) processor->Physical_Address_Size);
    //printf("Virtual_Address_Size={%d}\n", (unsigned long) processor->Virtual_Address_Size);

    
    //========================================
    // CPUID Fn8000_0009 Reserved
    
    //========================================
    //CPUID Fn8000_000A_EAX SVM Revision
    //CPUID Fn8000_000A_EBX SVM Revision and Feature Identification
    //CPUID Fn8000_000A_ECX Reserved
    //CPUID Fn8000_000A_EDX SVM Feature Identification
    

    //========================================
    // CPUID Fn8000_00[18:0B] Reserved
    

    //========================================
    //CPUID Fn8000_0019_EAX L1 TLB 1G Identifiers
    //CPUID Fn8000_0019_EBX L2 TLB 1G Identifiers
    //CPUID Fn8000_0019_E[D,C]X Reserved
    

    //========================================
    //CPUID Fn8000_001A_EAX Performance Optimization Identifiers
    //CPUID Fn8000_001A_E[D,C,B]X Reserved
    
    //========================================
    //CPUID Fn8000_001B_EAX Instruction Based Sampling Identifiers
    //CPUID Fn8000_001B_E[D,C,B]X Instruction Based Sampling Identifiers
    
    //========================================
    //CPUID Fn8000_001C_EAX Lightweight Profiling Capabilities 0
    //CPUID Fn8000_001C_EBX Lightweight Profiling Capabilities 0
    //CPUID Fn8000_001C_ECX Lightweight Profiling Capabilities 0
    //CPUID Fn8000_001C_EDX Lightweight Profiling Capabilities 0
    
    //========================================
    //CPUID Fn8000_001D_EAX_x0 Cache Properties
    //CPUID Fn8000_001D_EAX_x1 Cache Properties
    //CPUID Fn8000_001D_EAX_x2 Cache Properties
    //CPUID Fn8000_001D_EAX_x3 Cache Properties
    //CPUID Fn8000_001D_EAX_x4 Cache Properties
    //CPUID Fn8000_001D_EBX_x0 Cache Properties
    //CPUID Fn8000_001D_EBX_x1 Cache Properties
    //CPUID Fn8000_001D_EBX_x2 Cache Properties
    //CPUID Fn8000_001D_EBX_x3 Cache Properties
    //CPUID Fn8000_001D_EBX_x4 Cache Properties
    //CPUID Fn8000_001D_ECX_x0 Cache Properties
    //CPUID Fn8000_001D_ECX_x1 Cache Properties
    //CPUID Fn8000_001D_ECX_x2 Cache Properties
    //CPUID Fn8000_001D_ECX_x3 Cache Properties
    //CPUID Fn8000_001D_ECX_x4 Cache Properties
    //CPUID Fn8000_001D_EDX_x0 Cache Properties
    //CPUID Fn8000_001D_EDX_x1 Cache Properties
    //CPUID Fn8000_001D_EDX_x2 Cache Properties
    //CPUID Fn8000_001D_EDX_x3 Cache Properties
    //CPUID Fn8000_001D_EDX_x4 Cache Properties
    
    //========================================
    //CPUID Fn8000_001E_EAX Extended APIC ID
    //CPUID Fn8000_001E_EBX Compute Unit Identifiers
    //CPUID Fn8000_001E_ECX Node Identifiers
    //CPUID Fn8000_001E_EDX Reserved
        
    
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

    // ?? The same from intel?
    x86fault_initialize();

    //todo:
    //trazer as rotinas da amd para esse arquivo.

    debug_print ("[x86] init_amd:");
    
    get_cpu_amd_parameters();

    return 0;
}


//
// End.
//

