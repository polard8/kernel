

#include <kernel.h>    



/*
 // 8259 isa irqs
unsigned char isa_irqs[16] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F  
};
*/


/*
 ***********************************
 * x64_init_gdt:
 *     It creates a TSS and sets up some entries in the GDT.
 *     See: x86gdt.h
 */

// See: head_64.asm
extern void rsp0Stack(void);
extern void gdt_flush(unsigned long gdtr_address);

int x64_init_gdt (void)
{
    struct tss_d  *tss;


    debug_print ("[x64] x64_init_gdt: [DANGER] \n");


    memset(
        &xxx_gdt[GNULL_SEL],
        0,
        sizeof(struct segment_descriptor_d)*32 );


    // Creating a TSS and initializing it.

    tss = (void *) kmalloc ( sizeof(struct tss_d) );

    if ( (void *) tss == NULL ){
        debug_print ("[x64] x64_init_gdt: \n");
              panic ("[x64] x64_init_gdt: \n");
    }else{
 
        // Init TSS. 
        tss_init ( 
            (struct tss_d *) tss,  // tss 
            (void *) &rsp0Stack    // ring 0 stack address
            );

        //tss_init ( 
        //    (struct tss_d *) tss,  // tss 
        //    (void *) 0x8000    // ring 0 stack address
        //    );


         // Setup current.
         // ps: All threads are using the same tss.

         CurrentTSS = tss;
         
         // #bugbug
         // #todo: Validation
         
         //if ( (void *) CurrentTSS == NULL )
             //panic( ...
    };


//
// Initializing the GDT.
//

    // IN: 
    // (n, limit, base, type, s, dpl, p, avl, l, db, g)

    // null
    set_gdt_entry ( &xxx_gdt[GNULL_SEL], 
        0,0,0,0,0,0,0,0,0,0);

    // ring 0
    set_gdt_entry ( &xxx_gdt[GCODE_SEL], 
        0,0x0,0xA,1,0,1,0,1,0,0); //dpl 0
    set_gdt_entry ( &xxx_gdt[GDATA_SEL], 
        0,0x0,0x2,1,0,1,0,1,0,0); //dpl 0

    // ring 3
    set_gdt_entry ( &xxx_gdt[GUCODE_SEL], 
        0,0x0,0xA,1,3,1,0,1,0,0); //dpl 3
    set_gdt_entry ( &xxx_gdt[GUDATA_SEL], 
        0,0x0,0x2,1,3,1,0,1,0,0); //dpl 3

    // tss
    set_gdt_entry ( &xxx_gdt[GTSS_SEL], 
        sizeof( struct tss_d ) - 1, (unsigned long) tss,0x9,0,3,1,0,0,0,1); //tss dpl 3
    set_gdt_entry ( &xxx_gdt[GTSS_CONT_SEL], 
        (unsigned long) tss >> 32, (unsigned long) tss >> 48,0,0,0,0,0,0,0,0);

//
// Load GDT.
//

    // Limit and base.
    xxx_gdt_ptr.limit = (unsigned short) ((32 * sizeof(struct segment_descriptor_d) ) -1);
    xxx_gdt_ptr.base  = (unsigned long) &xxx_gdt[GNULL_SEL];

    // register.
    gdt_flush((unsigned long) &xxx_gdt_ptr);

    // See: x64gdt.h
    //load_gdt (&xxx_gdt_ptr);
    
    
//
// Load tr   [DANGER]
//

    // Load TR.
    // 0x2B = (0x28+3).

    // #bugbug
    // Falha quando carregamos isso.

    x64_load_ltr(0x2B);


// Done
    return 0;
}


// ===================





// Set segment.
// Probably stolen from minix or netbsd.
// See: x64gdt.h

void
set_gdt_entry ( 
    struct segment_descriptor_d *sd, 
    unsigned int limit,
    unsigned int base,
    unsigned char type,
    unsigned char s, 
    unsigned char dpl, 
    unsigned char p, 
    unsigned char avl,
    unsigned char l,
    unsigned char db,   //Sz 
    unsigned char g )
{
    // low limit
    sd->limit_15_0 = (limit & 0xFFFF); // (16) segment extent (lsb) 

    // base low
    sd->base_15_0   = (base & 0xFFFF);        // (16)
    sd->base_23_16  = ((base >> 16) & 0xFF);  // (8)

    sd->type  = ( type & 0xF );  // (4)
    sd->s     = ( s    & 0x1 );  // (1)
    sd->dpl   = ( dpl  & 0x3 );  // (2)
    sd->p     = ( p    & 0x1 );  // (1)

    sd->limit_19_16 = ((limit >>16) & 0xF);  //(4)

    sd->avl  = (avl & 1);  // (1)  
    sd->l    = (l   & 1);  // (1)
    sd->db   = (db  & 1);  // (1)
    sd->g    = (g   & 1);  // (1)

    // base high
    sd->base_31_24  = ((base  >> 24) & 0xFF);  // (8)
}



// ======================


static void
tss_init ( 
    struct tss_d *tss, 
    void *stack_address )
{

    if ( (void *) tss == NULL ){
        debug_print ("[x64] tss_init:\n");
        panic       ("[x64] tss_init:\n");
    }

    // Clean.
    memset ( tss, 0, sizeof *tss );

    //ring 0 stack
    tss->rsp0 = (unsigned long) stack_address;  // va ?? 

    //#debug
    //printf ("Stack %x\n", stack_address);
    //refresh_screen();
    //while(1){}
}





// # not tested yet
void x64_load_ltr (int tr)
{
    asm volatile ( \
        " movw %w0, %%ax; \
          ltrw %%ax;     "\
        :: "a"(tr) );
}

// ==========================



/*
 ***************************************************
 * get_cpu_intel_parameters:
 *     Pega os parâmetros da cpu x64 através da instrução cpuid.
 *
 * Vendor               = 0.
 * Apic ??              = 1.
 * Number of cores      = 4.
 * Name                 = 0x80000002,0x80000003,0x80000004. (Processor Brand String).
 * Max feature id       = 0x80000000.
 * L2 cache information = 0x80000006.(Extended L2 Cache Features)
 * core per die         = 0x80000008.
 */

// #todo:
// apic
// The CPUID.01h:EDX[bit 9] flag 
// specifies whether a CPU has a built-in local APIC. 


// According to the Intel CPUID application note, 
// we should first check the Vendor ID String for "GenuineIntel" 
// before taking out information, such as 
// the Processor Signature, Processor Feature Flags, etc. 

void get_cpu_intel_parameters (void)
{

    unsigned long eax=0; 
    unsigned long ebx=0; 
    unsigned long ecx=0;
    unsigned long edx=0;

    unsigned long name[32];

    int MASK_LSB_8 = 0xFF;


    debug_print ("get_cpu_intel_parameters: [FIXME]\n");


    //========================================
    // EAX=0: Highest Function Parameter and Manufacturer ID
    // #todo: eax
    //eax = Maximum meaningful value for the InfoType parameter. 
    // Vendor.
    //ebx = Identification String (part 1)
    //ecx = Identification String (part 3)
    //edx = Identification String (part 2)

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
    
    // Intel?
    // #todo: definir Intel como 1.
    if ( ebx == CPUID_VENDOR_INTEL_1 && 
         edx == CPUID_VENDOR_INTEL_2 && 
         ecx == CPUID_VENDOR_INTEL_3 )
    {
        hal_set_machine_type(Processor_INTEL);
    }


    //========================================
    // EAX=1: Processor Info and Feature Bits

	//
	// Output para argumento 1. 
	//
	
    //eax:
    // 0- 3 Stepping ID
    // 4- 7 Model
    // 8-11 Family
    //12-13 Processor Type
    //14-15 Reserved
    //16-19 Extended model
    //20-27 Extended family
    //28-31 Reserved

    //ebx:
    // 0- 7 Brand Index
    // 8-15 CLFLUSH cache line size / 8
    //16-23 Reserved
    //24-31 APIC Physical ID

	//ecx:
	//0 SSE3 New Instructions
	//1-2 Reserved
	//3 MONITOR/MWAIT
	//4 CPL Qualified Debug Store
	//5-7 Reserved
	//8 Thermal Monitor 2
	//9 Reserved
	//10 L1 Context ID
	//11-31 Reserved
	
	//edx: 
	//0 FPU x87 FPU on Chip
	//1 VME Virtual-8086 Mode Enhancement
	//2 DE Debugging Extensions
	//3 PSE Page Size Extensions
	//4 TSC Time Stamp Counter
	//5 ~~> MSR RDMSR and WRMSR Support ***
	//6 PAE Physical Address Extensions
	//7 MCE Machine Check Exception
	//8 CX8 CMPXCHG8B Inst.
	//9 ~~~> APIC APIC on Chip ***
	//10 n/a Reserved
	//11 SEP SYSENTER and SYSEXIT
	//12 MTRR Memory Type Range Registers
	//13 PGE PTE Global Bit
	//14 MCA Machine Check Architecture
	//15 CMOV Conditional Move/Compare Instruction
	//16 PAT Page Attribute Table
	//17 PSE Page Size Extension
	//18 PSN Processor Serial Number
	//19 CLFSH CFLUSH Instruction
	//20 n/a Reserved
	//21 DS Debug Store
	//22 ACPI Thermal Monitor and Clock Ctrl
	//23 MMX MMX Technology
	//24 FXSR FXSAVE/FXRSTOR
	//25 SSE SSE Extensions
	//26 SSE2 SSE2 Extensions
	//27 SS Self Snoop
	//28 HTT Hyper-threading technology
	//29 TM Thermal Monitor
	//30 n/a Reserved
	//31 PBE Pend. Brk. En.
	
	

    cpuid ( 1, eax, ebx, ecx, edx );

	// eax:
	// Processor Version Information 
	processor->Stepping_ID        = (unsigned long)( eax        & 0xF);  //stepping
	processor->Model              = (unsigned long)((eax >> 4)  & 0xf);  //model
	processor->Family_ID          = (unsigned long)((eax >> 8)  & 0xf);  //family
	processor->Processor_Type     = (unsigned long)((eax >> 12) & 0x3);  //processor type
	processor->Extended_Model_ID  = (unsigned long)((eax >> 16) & 0xf);  //extended model
	processor->Extended_Family_ID = (unsigned long)((eax >> 20) & 0xff); //extended family
    // 31 ~ 28 Reserved??

	//ebx:
	// Additional Information 
	//processor->xx = (unsigned long)((ebx >> 9) & 0x0001);
    //... 



    // ecx e edx:
    // Feature Information 

	//edx:
	// The CPUID.01h:EDX[bit 9] flag 
	// specifies whether a CPU has a built-in local APIC. 
    processor->isApic = (unsigned long)((edx >> 9) & 0x0001);
	//processor->isApic = (unsigned long) edx;
	
	
	//The presence of MSRs on your processor is 
    //indicated by CPUID.01h:EDX[bit 5].
    //processor->hasMSR = (unsigned long)((edx >> 5) & 0x0001);
	//...
	
	// #todo:
	// Mostrar uma mensagem, se tem ou não apic;


    //========================================
    // EAX=2: Cache and TLB Descriptor information
    
    // ...
    
    //========================================
    // EAX=3: Processor Serial Number
    
	//Serial number ???
	//cpuid( 3, eax, ebx, ecx, edx );


    //========================================
    // EAX=4 and EAX=Bh: Intel thread/core and cache topology
    
	//Check number of cores.
	//cpuid( 4, eax, ebx, ecx, edx );



    //========================================
    // EAX=6: Thermal and power management
    

    //========================================
    // EAX=7, ECX=0: Extended Features
    // EAX=7, ECX=1: Extended Features
    

    // ==========================================================
    // hypervisor level 4000_0000h
    cpuid ( 0x40000000, eax, ebx, ecx, edx );
    processor->hvName[0] = ebx;
    processor->hvName[1] = ecx;
    processor->hvName[2] = edx;
    processor->hvName[3] = 0;



    //========================================
    // EAX=80000000h: Get Highest Extended Function Implemented

    // Max feature id.
    cpuid ( 0x80000000, eax, ebx, ecx, edx);
    name[0] = eax;  //Maximum meaningful value of InfoType for extended function CPUID information.
    name[1] = ebx;  //reserved
    name[2] = ecx;  //reserved
    name[3] = edx;  //reserved
    name[4] = 0; 
    processor->MaxFeatureId = (unsigned long)(eax & MASK_LSB_8);
    //printf("Max feature id ={%d}\n", (unsigned long) processor->MaxFeatureId);


    //========================================
    // EAX=80000001h: Extended Processor Info and Feature Bits
    
    //========================================
    // EAX=80000002h,80000003h,80000004h: Processor Brand String
    
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
    // EAX=80000005h: L1 Cache and TLB Identifiers




    //========================================
    // EAX=80000006h: Extended L2 Cache Features
 
    // pegamos logo acima.
    if ( processor->MaxFeatureId < 6)
    {
        debug_print ("get_cpu_intel_parameters: Cache Extended Feature not supported\n");
        //printf("Cache Extended Feature not supported\n");
        //goto done;
        return;
    }

    /*
     * L2 cache information (Intel)
     *
     * EAX Reserved
     * EBX Reserved
     * ECX Bits:  
     *     Bits 0-7: Cache Line Size.
     *     Bits 12-15: L2 Associativity.
     *     Bits 16-31: Cache size in 1K units.   
     * EDX Reserved
     */

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
    // EAX=80000007h: Advanced Power Management Information



    //========================================
    //EAX=80000008h: 
    //Virtual and Physical address Sizes	
    //Returns largest virtual and physical address sizes.

    /*
     * Virtual and physical memory sizes.
     */

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

    //...
}


void x64_init_fpu (void) 
{
    asm volatile ("fninit");
}


// x64 disable interrupts.
void x64_disable_interrupts (void)
{
    asm ("cli"); 
}

// x64 enable interrupts.
void x64_enable_interrupts (void)
{
    asm ("sti");
}


void x64_iretq (void)
{
    asm ("iretq");
}

void x64_iret (void)
{
    asm ("iret");
}

void x64_lret (void)
{
    asm ("lret");
}

void x64_cli_hlt(void)
{
    asm (" cli \n \t "); 
    asm (" hlt \n \t ");
}

void x64_stop_cpu (void)
{
    x64_cli_hlt();
}


// Enable cache.
// credits: barrelfish.
// #todo: Test it on my real machine.

void x64_enable_cache (void)
{
    /*
    uint32_t cr0 = 0; 
    unsigned long cr0 = 0; //use this one ??

    asm volatile ("mov %%cr0, %[cr0]" : [cr0] "=r" (cr0) );

    cr0 &= ~CPUX64_CR0_CD;
    cr0 &= ~CPUX64_CR0_NW;
    
    asm volatile ("mov %[cr0], %%cr0" :: [cr0] "r" (cr0) );
    */
}

// Called by init_architecture_dependent() on core/init.c

int x64_init_intel (void)
{
    debug_print ("[x64] x64_init_intel:");


    //x64fault_initialize();

    // #bugbug
    // Suspended.
    // We need to teste the effects os this routine in the real machine.
    // See: sysio/hal/arch/x86/x86.h
    // See: sysio/hal/arch/x86/x86.c
    
    //x64_enable_cache();

    // Get info.
    // See: x86.c
    get_cpu_intel_parameters();

    // ...

    return 0;
}


void x64_load_pml4_table(unsigned long phy_addr)
{
    asm volatile ("movq %0,%%cr3"::"r"(phy_addr));
}















