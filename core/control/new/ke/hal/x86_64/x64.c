
// x64.c

#include <kernel.h>    

// See: unit1hw.asm
extern void DisableSSE(void);
extern void EnableSSE(void);

// see: mp.h
struct mp_floating_pointer_structure_d *MPTable;
// see: mp.h
struct mp_configuration_table_d *MPConfigurationTable;
// see: mp.h
struct smp_info_d smp_info;



/*
 // 8259 isa irqs
unsigned char isa_irqs[16] = {
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F  
};
*/

/*
 * x64_init_gdt:
 *     It creates a TSS and sets up some entries in the GDT.
 *     See: x86gdt.h
 */
// Called by I_x64main in init.c.
// See: head_64.asm

extern void rsp0Stack(void);
extern void gdt_flush(unsigned long gdtr_address);

int x64_init_gdt(void)
{
    struct tss_d  *tss;

    // debug_print ("[x64] x64_init_gdt: [DANGER] \n");

// Clean the GDT. #danger
    unsigned long GDT_Base = (unsigned long) &xxx_gdt[GNULL_SEL];
    size_t        GDT_NumberOfEntries = DESCRIPTOR_COUNT_MAX;  //32 
    size_t        GDT_Size = 
        (size_t) (sizeof(struct segment_descriptor_d) * GDT_NumberOfEntries);
    memset( GDT_Base, 0, GDT_Size );

// IN: 
// (entry address, limit, base, type, s, dpl, p, avl, l, db, g)

// null
    set_gdt_entry ( 
        &xxx_gdt[GNULL_SEL], 
        0,0,0,0,0,0,0,0,0,0);

// ring 0
// dpl 0
// (n, limit, base, type, s, dpl, p, avl, l, db, g)
    set_gdt_entry ( 
        &xxx_gdt[GCODE_SEL], 
        0,    // limit
        0x0,  // base
        SEG_CODE_EXRD, //0xA,  // type
        1,    // s
        RING0, //0,    // dpl
        1,    // p
        0,    // avl
        1,    // l
        0,    // db
        0);   // g
    set_gdt_entry ( 
        &xxx_gdt[GDATA_SEL], 
        0,    // limit
        0x0,  // base
        SEG_DATA_RDWR, //0x2,  // type
        1,    // s
        RING0, //0,    // dpl
        1,    // p
        0,    // avl
        1,    // l
        0,    // db
        0);   // g

// ring 3
// dpl 3
// (n, limit, base, type, s, dpl, p, avl, l, db, g)
    set_gdt_entry ( 
        &xxx_gdt[GUCODE_SEL], 
        0,    // limit
        0x0,  // base
        SEG_CODE_EXRD, //0xA,  // type
        1,    // s
        RING3, //3,    // dpl ??
        1,    // p
        0,    // avl
        1,    // l
        0,    // db
        0);   // g
    set_gdt_entry ( 
        &xxx_gdt[GUDATA_SEL], 
        0,      // limit   
        0x0,    // base
        SEG_DATA_RDWR, //0x2,    // type
        1,      // s
        RING3, //3,      // dpl ??
        1,      // p
        0,      // avl
        1,      // l
        0,      // db
        0);     // g

//
// tss
//

// Creating a TSS and initializing it.
// Save current tss.
// Create gdt entry for the tss. (two entries)

    tss = (void *) kmalloc( sizeof(struct tss_d) );
    if ( (void *) tss == NULL ){
        debug_print ("[x64] x64_init_gdt:\n");
              panic ("[x64] x64_init_gdt:\n");
    }

// Initializing the tss structure,
// given the ring0 stack pointer.
    tss_init ( 
        (struct tss_d *) tss,  // tss 
        (void *) &rsp0Stack    // ring 0 stack address
        );

    // tss, dpl 3
    // Two entries.
    set_gdt_entry( 
        &xxx_gdt[GTSS_SEL], 
        sizeof(struct tss_d) - 1, 
        (unsigned long) tss, 
        0x9,0,3,1,0,0,0,1);
    set_gdt_entry( 
        &xxx_gdt[GTSS_CONT_SEL], 
        (unsigned long) tss >> 32,
        (unsigned long) tss >> 48,
        0,0,0,0,0,0,0,0);

    CurrentTSS = tss;
    //CurrentTSS = (struct tss_d *) tss;

//
// Load GDT
//

// Limit and base.

    xxx_gdt_ptr.limit = 
        (unsigned short) ((DESCRIPTOR_COUNT_MAX * sizeof(struct segment_descriptor_d) ) -1);
    xxx_gdt_ptr.base = 
        (unsigned long) &xxx_gdt[GNULL_SEL];


// register.
    gdt_flush( (unsigned long) &xxx_gdt_ptr );

    // See: x64gdt.h
    //load_gdt (&xxx_gdt_ptr);

// #todo
// print gdt entries.


// Load TR. #danger
// 0x2B = (0x28+3).
    x64_load_ltr(0x2B);

    return 0;
}

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
    if ( (void*) sd == NULL ){
        debug_print ("[x64] set_gdt_entry: sd\n");
        panic       ("[x64] set_gdt_entry: sd\n");
    }

// limit
    sd->limit_15_0  = (limit & 0xFFFF);       // (16) segment extent (lsw) 
    sd->limit_19_16 = ((limit >> 16) & 0xF);  // (4)

// base
    sd->base_15_0   = (base & 0xFFFF);         // (16) lsw
    sd->base_23_16  = ((base >> 16) & 0xFF);   // (8)
    sd->base_31_24  = ((base  >> 24) & 0xFF);  // (8)

// access byte
    sd->type  = ( type & 0xF );  // (4)
    sd->s     = ( s    & 0x1 );  // (1)
    sd->dpl   = ( dpl  & 0x3 );  // (2)
    sd->p     = ( p    & 0x1 );  // (1)

//
    sd->avl  = (avl & 1);  // (1)  
    sd->l    = (l   & 1);  // (1)
    sd->db   = (db  & 1);  // (1)
    sd->g    = (g   & 1);  // (1)
}

// ======================

void
tss_init ( 
    struct tss_d *tss, 
    void *stack_address )
{
    if ( (void *) tss == NULL ){
        debug_print ("[x64] tss_init:\n");
        panic       ("[x64] tss_init:\n");
    }

// Clean
    memset ( tss, 0, sizeof *tss );
    //memset ( tss, 0, sizeof(struct tts_d) ); //#todo

// ring 0 stack
    //#todo
    //if ( stack_address == 0 )
    //    panic("tss_init: stack_address\n");
    tss->rsp0 = (unsigned long) stack_address;  // va?? 

    //#debug
    //printf ("Stack %x\n", stack_address);
    //refresh_screen();
    //while(1){}
}

// # not tested yet
void x64_load_ltr(int tr)
{
    asm volatile ( \
        " movw %w0, %%ax; \
          ltrw %%ax;     "\
        :: "a"(tr) );
}

// ==========================

/*
 * get_cpu_intel_parameters:
 *     Pega os parâmetros da cpu x64 através da instrução cpuid.
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

void get_cpu_intel_parameters(void)
{
    unsigned long eax=0;
    unsigned long ebx=0;
    unsigned long ecx=0;
    unsigned long edx=0;
    unsigned long buffer[8];
    int MASK_LSB_8 = 0xFF;

    //debug_print ("get_cpu_intel_parameters: [FIXME]\n");

//========================================
// EAX=0: Highest Function Parameter and Manufacturer ID
// #todo: eax
// eax = Maximum meaningful value for the InfoType parameter. 
// Vendor.
// ebx = Identification String (part 1)
// ecx = Identification String (part 3)
// edx = Identification String (part 2)

    cpuid ( 0, eax, ebx, ecx, edx ); 
    buffer[0] = ebx;
    buffer[1] = edx;
    buffer[2] = ecx;
    buffer[3] = 0;

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
        g_processor_count = 1;
    }

//========================================
// EAX=1: Processor Info and Feature Bits

//
// Output para argumento 1. 
//

// eax:
//  0- 3 Stepping ID
//  4- 7 Model
//  8-11 Family
// 12-13 Processor Type
// 14-15 Reserved
// 16-19 Extended model
// 20-27 Extended family
// 28-31 Reserved

// ebx:
//  0- 7 Brand Index
//  8-15 CLFLUSH cache line size / 8.
// 16-23 Reserved
// 24-31 APIC Physical ID.

// ecx:
//     0 SSE3 New Instructions
// 1-  2 Reserved
//     3 MONITOR/MWAIT
//     4 CPL Qualified Debug Store
// 5-  7 Reserved
//     8 Thermal Monitor 2
//     9 Reserved
//    10 L1 Context ID
// 11-31 Reserved

// edx: 
//  0 FPU x87 FPU on Chip.
//  1 VME Virtual-8086 Mode Enhancement
//  2 DE Debugging Extensions
//  3 PSE Page Size Extensions
//  4 TSC Time Stamp Counter
//  5 MSR RDMSR and WRMSR Support.
//  6 PAE Physical Address Extensions
//  7 MCE Machine Check Exception
//  8 CX8 CMPXCHG8B Inst.
//  9 APIC APIC on Chip.
// 10 n/a Reserved
// 11 SEP SYSENTER and SYSEXIT
// 12 MTRR Memory Type Range Registers
// 13 PGE PTE Global Bit
// 14 MCA Machine Check Architecture
// 15 CMOV Conditional Move/Compare Instruction
// 16 PAT Page Attribute Table
// 17 PSE Page Size Extension (PSE36)
// 18 PSN Processor Serial Number
// 19 CLFSH CFLUSH Instruction
// 20 n/a Reserved
// 21 DS Debug Store
// 22 ACPI Thermal Monitor and Clock Ctrl
// 23 MMX MMX Technology
// 24 FXSR FXSAVE/FXRSTOR
// 25 SSE SSE Extensions
// 26 SSE2 SSE2 Extensions
// 27 SS Self Snoop
// 28 HTT Hyper-threading technology.
// 29 TM Thermal Monitor
// 30 n/a Reserved
// 31 PBE Pend. Brk. En.

    cpuid ( 1, eax, ebx, ecx, edx );

// eax:
// Processor Version Information 
    processor->Stepping_ID = 
        (unsigned long)( eax        & 0xF);  //stepping
    processor->Model = 
        (unsigned long)((eax >> 4)  & 0xf);  //model
    processor->Family_ID = 
        (unsigned long)((eax >> 8)  & 0xf);  //family
    processor->Processor_Type = 
        (unsigned long)((eax >> 12) & 0x3);  //processor type
    processor->Extended_Model_ID = 
        (unsigned long)((eax >> 16) & 0xf);  //extended model
    processor->Extended_Family_ID = 
        (unsigned long)((eax >> 20) & 0xff); //extended family
    // 31 ~ 28 Reserved??

// ebx:
// Additional Information 

    //processor->xx = (unsigned long)((ebx >> 9) & 0x0001);
    //... 

// ecx e edx:
// Feature Information 

// ecx

// SSE3 - bit 0.
    processor->hasSSE3 = 
        (unsigned long)( ecx & 0x0001);

// edx:

// The CPUID.01h:EDX[bit 0] flag.
// Specifies whether a CPU has a built-in local x87 FPU. 
    processor->hasX87FPU = 
        (unsigned long)( edx & 0x0001);

// PSE - bit 3.
    processor->hasPSE = 
        (unsigned long)((edx >> 3) & 0x0001);

// TSC - bit 4.
    processor->hasTSC = 
        (unsigned long)((edx >> 4) & 0x0001);

//The presence of MSRs on your processor is 
//indicated by CPUID.01h:EDX[bit 5].
    processor->hasMSR = 
        (unsigned long)((edx >> 5) & 0x0001);

// PAE - bit 6.
    processor->hasPAE = 
        (unsigned long)((edx >> 6) & 0x0001);

// The CPUID.01h:EDX[bit 9] flag 
// Specifies whether a CPU has a built-in local APIC. 
    processor->hasAPIC = 
        (unsigned long)((edx >> 9) & 0x0001);

// MTRR Memory Type Range Registers
    processor->hasMTRR = 
        (unsigned long)((edx >> 12) & 0x0001);

// PAT - Page Attribute Table
    processor->hasPAT = 
        (unsigned long)((edx >> 16) & 0x0001);

// PSE - Page Size Extension (PSE36)
    processor->hasPSE36 = 
        (unsigned long)((edx >> 17) & 0x0001);

// PSN - Processor Serial Number
    processor->hasPSN = 
        (unsigned long)((edx >> 18) & 0x0001);

//---

// MMX
    processor->hasMMX = 
        (unsigned long)((edx >> 23) & 0x0001);

// SSE
    processor->hasSSE = 
        (unsigned long)((edx >> 25) & 0x0001);

// SSE2
    processor->hasSSE2 = 
        (unsigned long)((edx >> 26) & 0x0001);

// HTT - hyper-threading technology
    processor->hasHTT = 
        (unsigned long)((edx >> 28) & 0x0001);

    // ...

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

// ============================================
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
    buffer[0] = eax;  //Maximum meaningful value of InfoType for extended function CPUID information.
    buffer[1] = ebx;  //reserved
    buffer[2] = ecx;  //reserved
    buffer[3] = edx;  //reserved
    buffer[4] = 0; 
    processor->MaxFeatureId = (unsigned long)(eax & MASK_LSB_8);
    //printf("Max feature id ={%d}\n", (unsigned long) processor->MaxFeatureId);

//========================================
// EAX=80000001h: Extended Processor Info and Feature Bits

//========================================
// EAX=80000002h,80000003h,80000004h: Processor Brand String

/*name part 1*/
    cpuid ( 0x80000002, eax, ebx, ecx, edx);
    buffer[0] = eax;  //Processor Brand String
    buffer[1] = ebx;  //Processor Brand String
    buffer[2] = ecx;  //Processor Brand String
    buffer[3] = edx;  //Processor Brand String
    buffer[4] = 0;
    //salva na estrutura.
    processor->BrandName[0] = eax;
    processor->BrandName[1] = ebx;
    processor->BrandName[2] = ecx;
    processor->BrandName[3] = edx;
    //printf("CPU={%s", &buffer[0]);
    //printf("%s",&buffer[0]);

/*name part 2*/
    cpuid ( 0x80000003, eax, ebx, ecx, edx);
    buffer[0] = eax;  //Processor Brand String, continued
    buffer[1] = ebx;  //Processor Brand String, continued
    buffer[2] = ecx;  //Processor Brand String, continued
    buffer[3] = edx;  //Processor Brand String, continued
    buffer[4] = 0;
    //salva na estrutura.
    processor->BrandName[4] = eax;
    processor->BrandName[5] = ebx;
    processor->BrandName[6] = ecx;
    processor->BrandName[7] = edx;
    //printf("%s",&buffer[0]);

/*name part 3*/
    cpuid ( 0x80000004, eax, ebx, ecx, edx);
    buffer[0] = eax; //Processor Brand String, continued
    buffer[1] = ebx; //Processor Brand String, continued
    buffer[2] = ecx; //Processor Brand String, continued
    buffer[3] = edx; //Processor Brand String, continued
    buffer[4] = 0;
    // Salva na estrutura.
    processor->BrandName[8]  = eax;
    processor->BrandName[9]  = ebx;
    processor->BrandName[10] = ecx;
    processor->BrandName[11] = edx;
    //printf("%s}\n",&buffer[0]);

//========================================
// EAX=80000005h: L1 Cache and TLB Identifiers

//========================================
// EAX=80000006h: Extended L2 Cache Features

// Pegamos logo acima.
    if (processor->MaxFeatureId < 6){
        debug_print ("get_cpu_intel_parameters: Cache Extended Feature not supported\n");
        //printf("Cache Extended Feature not supported\n");
        //goto done;
        return;  // Why?
    }

/*
 * L2 cache information (Intel)
 * EAX Reserved
 * EBX Reserved
 * ECX Bits:
 *     Bits 0-7: Cache Line Size.
 *     Bits 12-15: L2 Associativity.
 *     Bits 16-31: Cache size in 1K units.
 * EDX Reserved
 */

    cpuid ( 0x80000006, eax, ebx, ecx, edx );
    buffer[0] = eax;
    buffer[1] = ebx;
    buffer[2] = ecx;
    buffer[3] = edx;
    buffer[4] = 0;

// Bits 0-7: Cache Line Size.
    processor->L2LineSize = 
        (unsigned long)(ecx & 0x00FF);

// Bits 12-15: L2 Associativity.
    processor->L2Associativity = 
        (unsigned long)((ecx >> 12) & 0x000F);

// Bits 16-31: Cache size in 1K units.
    processor->L2Cachesize = 
        (unsigned long)((ecx >> 16) & 0xFFFF);

    //printf("L2LineSize={%d Byte}\n",(unsigned long) processor->L2LineSize);
    //printf("L2Cachesize={%d KB} \n",(unsigned long) processor->L2Cachesize);

//========================================
// EAX=80000007h: Advanced Power Management Information

//========================================
// EAX=80000008h: 
// Virtual and Physical address Sizes
// Returns largest virtual and physical address sizes.

/*
 * Virtual and physical memory sizes.
 */

    cpuid ( 0x80000008, eax, ebx, ecx, edx );
    buffer[0] = eax;    //Virtual and physical memory sizes.
    buffer[1] = ebx;    //reserved
    buffer[2] = ecx;    //reserved
    buffer[3] = edx;    //reserved
    buffer[4] = 0;

// 7-0
    processor->Physical_Address_Size = 
        (unsigned long) ( eax & 0x00FF);

// 15-8
    processor->Virtual_Address_Size = 
        (unsigned long) ((eax >> 8) & 0x00FF);

    //printf("Physical_Address_Size={%d}\n",(unsigned long) processor->Physical_Address_Size);
    //printf("Virtual_Address_Size={%d}\n", (unsigned long) processor->Virtual_Address_Size);

    //...
}

// FPU state
// When the FPU is configured, 
// the only thing left to do is to initialize its registers 
// to their proper states. FNINIT will reset 
// the user-visible part of the FPU stack. 
// see:
// https://wiki.osdev.org/FPU
void x64_init_fpu (void) 
{
    asm volatile ("fninit");
}

// Initialize fpu support and enable SSE.
// Long mode demands that SSE and SSE2 are available, and 
// compilers are free to use the SSE registers instead of 
// the old FPU registers for floating point operations. 
// This means that your kernel will need to have SSE enabled 
// before using any floating point operations.
// see:
// https://wiki.osdev.org/FPU
int x64_init_fpu_support(void)
{
// + Enable SSE support.
// + Initialize fpu support.

// Structure validation
    if ( (void*) processor == NULL ){
        printf("x64_init_fpu_support: processor\n");
        return -1;
    }

// has SSE
    if (processor->hasSSE != TRUE){
        printf("x64_init_fpu_support: hasSSE\n");
        return -1;
    }

// has SSE2
    if (processor->hasSSE2 != TRUE){
        printf("x64_init_fpu_support: hasSSE2\n");
        return -1;
    }

// has SSE3
    if (processor->hasSSE3 != TRUE){
        printf("x64_init_fpu_support: hasSSE3\n");
        return -1;
    }

// has x87fpu
// Check the FPU bit in CPUID.
    if (processor->hasX87FPU != TRUE){
        printf("x64_init_fpu_support: hasX87FPU\n");
        return -1;
    }

// Enable SSE.
// Clear TS bit in cr0.
// see: arch/x86_64/entrance/hw/hw1.asm
    EnableSSE();

// ??
// Enable
// Set OSFXSR and OSXMMEXCPT in cr4.
// Clear EM and Set MP in cr0.

    asm volatile (
        " movq %%cr4, %%rax;  "
        " orl $0x600, %%eax;  "    /*Set OSFXSR and OSXMMEXCPT*/
        " movq %%rax, %%cr4;  "
        
        " movq %%cr0, %%rax;  "
        " andw $0xFFFB, %%ax; "    /*Clear EM*/
        " orw $0x2, %%ax;     "    /*Set MP*/
        " movq %%rax, %%cr0;  " :: );

// Initialize fpu support.
// simply call 'fninit' instruction.
    x64_init_fpu();
 
    return 0;
}

// Set the FPU control word:
// These functions can be used with GCC (or TCC) 
// to perform some FPU operations without 
// resorting to dedicated assembly.
void fpu_load_control_word(const uint16_t control)
{
    asm volatile ("fldcw %0;"::"m"(control)); 
}

// x64 disable interrupts.
// maybe inline.
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

/*
inline void __invalidate_cache_flush(void);
inline void __invalidate_cache_flush(void)
{
    asm ("wbinvd");
}
*/

// Enable cache.
// credits: barrelfish.
// #todo: Test it on my real machine.

void x64_enable_cache (void)
{
    // #danger

/*
    uint32_t cr0 = 0; 
    unsigned long cr0 = 0; //use this one ??

    asm volatile ("mov %%cr0, %[cr0]" : [cr0] "=r" (cr0) );

    cr0 &= ~CPUX64_CR0_CD;
    cr0 &= ~CPUX64_CR0_NW;
    
    asm volatile ("mov %[cr0], %%cr0" :: [cr0] "r" (cr0) );
 */
}

// Called by init_architecture_dependent() on init.c
int x64_init_intel (void)
{
    //debug_print ("[x64] x64_init_intel:");

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
    //debug_print("x64_load_pml4_table: DANGER\n");

    asm volatile ("movq %0, %%cr3"::"r"(phy_addr));
}


// MP Floating Point Structure:
// To use these tables, the MP Floating Point Structure 
// must first be found. As the name suggests, 
// it is a Floating Point Structure and must be searched for.
// can't be found in this area, 
// then the area between 0xF0000 and 0xFFFFF should be searched. 
// To find the table, the following areas must be searched in:
// :: a) In the first kilobyte of Extended BIOS Data Area (EBDA), or
// :: b) Within the last kilobyte of system base memory 
// (e.g., 639K-640K for systems with 640KB of base memory 
// or 511K-512K for systems with 512 KB of base memory) 
// if the EBDA segment is undefined, or
// :: c) In the BIOS ROM address space between 0xF0000 and 0xFFFFF.
// See:
// https://wiki.osdev.org/Symmetric_Multiprocessing
// OUT:
// TRUE = OK.
// FALSE = FAIL.
int smp_probe(void)
{
// Probe the MP Floating Point structure.
// Called by I_init() in x64init.c.

// 0x040E - The base address.
// Get a short value.
    unsigned short *bda = (unsigned short*) BDA_BASE;
    unsigned long ebda_address=0;
    register int i=0;
    unsigned char *p;
// Signature elements.
    unsigned char c1=0;
    unsigned char c2=0;
    unsigned char c3=0;
    unsigned char c4=0;

    printf("smp_probe:\n");

// #todo
// We can use a structure and put all these variable together,
    g_smp_initialized = FALSE;
    smp_info.initialized = FALSE;

// At this point we gotta have a lot of information
// in the structure 'processor'.
    if ( (void*) processor == NULL ){
        panic("smp_probe: processor\n");
    }
// Is APIC supported?
    if (processor->hasAPIC != TRUE){
        panic("smp_probe: No APIC\n");
    }

//
// Probe ebda address at bda base.
//

    printf("EBDA short Address: %x\n", bda[0] ); 
    ebda_address = (unsigned long) ( bda[0] << 4 );
    ebda_address = (unsigned long) ( ebda_address & 0xFFFFFFFF);
    printf("EBDA Address: %x\n", ebda_address ); 

    // #debug
    // refresh_screen();

//
// Probe 0x5F504D5F signature. 
// "_MP_".
//


// base
// between 0xF0000 and 0xFFFFF.
// #todo: filter

    p = ebda_address;

// The signature was found?
    static int mp_found = FALSE;

// Probe for the signature."_MP_"
// This signature is the first element of the table.
// MP Floating Pointer Structure
    int max = (int) (0xFFFFF - ebda_address);
    for (i=0; i<max; i++){
        c1 = p[i+0];
        c2 = p[i+1];
        c3 = p[i+2];
        c4 = p[i+3];
        if ( c1 == '_' && c2 == 'M' && c3 == 'P' && c4 == '_' )
        {
            printf (":: Found _MP_ at index %d. :)\n",i);
            mp_found=TRUE;
            break;
        }
    };

// Signature not found.
// #todo: Try APIC instead.
    if (mp_found != TRUE)
    {
        printf("smp_probe: MP table wasn't found!\n");
        printf ("Try APIC table instead\n");
        goto fail;
    }


//mp_table_found:

// ==============================================
// MPTable
// MP Floating Point Structure
// base + offset.
// This is the base of the structure.
// See:
// https://wiki.osdev.org/User:Shikhin/Tutorial_SMP
// hal/mp.h

    unsigned long table_address = 
        (unsigned long) (ebda_address + i);
    MPTable = 
        (struct mp_floating_pointer_structure_d *) table_address;

// Saving
    smp_info.mp_floating_point = 
        (struct mp_floating_pointer_structure_d *) MPTable;
// ---------------------------------------------
// Print table info

// Signature
// "_MP_" 
// + OK on qemu.
// + OK on kvm.
// + FAIL on Virtualbox. #todo: try APIC.
    printf("Signature: %c %c %c %c\n",
        MPTable->signature[0],
        MPTable->signature[1],
        MPTable->signature[2],
        MPTable->signature[3] );

    //#debug
    //refresh_screen();
    //while(1){}

// ------------------------------------------
// Getting the address of the MP Configuration Table. 
// Pointed by th MP Floating point structure.
// 32bit address.
    unsigned long configurationtable_address = 
        (unsigned long) (MPTable->configuration_table & 0xFFFFFFFF);

// Pointer for the configuration table.
    printf("Configuration table address: {%x}\n",
        configurationtable_address);
// Lenght: n*16 bytes
// The length of the floating point structure table, 
// in 16 byte units. 
// This field *should* contain 0x01, meaning 16-bytes.
    printf("Lenght: {%d}\n", MPTable->length);
// Revision: 1.x
// The version number of the MP Specification. 
// A value of 1 indicates 1.1, 4 indicates 1.4, and so on.
    printf("Revision: {%d}\n", MPTable->mp_specification_revision);
// Checksum
// The checksum of the Floating Point Structure. 
    printf("Checksum: {%d}\n", MPTable->checksum);
// Default configuration flag.
// If this is not zero then configuration_table should be 
// ignored and a default configuration should be loaded instead.
    printf("Default configuration flag: {%d}\n",
        MPTable->default_configuration );

    if ( MPTable->default_configuration != 0 ){
        printf("todo: The configuration table should be ignored\n");
    }

// Features
// Few feature bytes.
// If bit 7 is set 
// then the IMCR is present and PIC mode is being used, 
// otherwise virtual wire mode is. 
// All other bits are reserved.
    printf("Features: {%d}\n", MPTable->features);
// Se o bit 7 está ligado.
    if ( MPTable->features & (1 << 7) ){
         printf("The IMCR is present and PIC mode is being used.\n");
    }
// Se o bit 7 está desligado.
    if ( (MPTable->features & (1 << 7)) == 0 ){
         printf("Using the virtual wire mode.\n");
    }

    //#debug
    //refresh_screen();
    //while(1){}

// ==============================================
// MPConfigurationTable structure.
// Pointed by th MP Floating point structure.

// Struture pointer.
// MP Configuration table.
    MPConfigurationTable = 
        (struct mp_configuration_table_d *) configurationtable_address;

    if ((void*) MPConfigurationTable == NULL ){
        printf("smp_probe: Invalid Configuration table address\n");
        goto fail;
    }
// Saving
    smp_info.mp_configuration_table = 
        (struct mp_configuration_table_d *) MPConfigurationTable;


// Signature
// "PCMP"
    printf("Signature: %c %c %c %c\n",
        MPConfigurationTable->signature[0],
        MPConfigurationTable->signature[1],
        MPConfigurationTable->signature[2],
        MPConfigurationTable->signature[3] );


// Intel strings: 
// "OEM00000" "PROD00000000"

// OEM ID STRING
    char oemid_string[8+1];
    for (i=0; i<8; i++){
        oemid_string[i] = MPConfigurationTable->oem_id[i];
    };
    oemid_string[8]=0;  // finish
    printf("OEM ID STRING: {%s}\n",oemid_string);

// PRODUCT ID STRING
    char productid_string[12+1];
    for (i=0; i<12; i++){
        productid_string[i] = MPConfigurationTable->product_id[i];
    };
    productid_string[12]=0;  // finish
    printf("PRODUCT ID STRING: {%s}\n",productid_string);

// Lapic address
    printf("lapic address: {%x}\n",
        MPConfigurationTable->lapic_address );

// Is this the standard lapic address?
    if ( MPConfigurationTable->lapic_address != LAPIC_BASE )
    {
        printf("fail: Not standard lapic address\n");
        printf("Found={%x} Standard{%x}\n",
            MPConfigurationTable->lapic_address,
            LAPIC_BASE );
    }

// --------------------------------
// Initialize lapic.
// See:
// apic.c
// Check the local apic table for the current processor.
// That one we are using right now.
// The BSP.
    printf("smp_probe: Initialize lapic for BSP\n");
    // Setup BSP's local APIC.
    lapic_initializing( 
        (unsigned long) MPConfigurationTable->lapic_address );

    if (LAPIC.initialized != TRUE){
        printf("smp_probe: lapic initialization fail\n");
    }
    //#debug
    //refresh_screen();
    //while(1){}


//
// Entries
//

// Probing the entries right below the MPConfigurationTable.

// -------------------------------
// Max number of entries.

    register int EntryCount = 
        (int) MPConfigurationTable->entry_count;

    printf("Entry count: {%d}\n",
        MPConfigurationTable->entry_count);

    //#debug
    //refresh_screen();
    //while(1){};


// #bugbug
// Talvez essas entradas estão erradas.
// Talvez não haja entrada alguma nesse endereço aqui.


// =======================================================
// Entries
// ACPI processor, Local APIC.

// Logo abaixo da configuration table.
// começa uma sequência de entradas de tamanhos diferentes.
// Se a entrada for para descrever um processador, então 
// a entrada tem 20 bytes, caso contrario tem 8 bytes.
// see: mp.h

// The address of the first entry.
    unsigned long entry_base = 
    (unsigned long) ( configurationtable_address + 
                      sizeof( struct mp_configuration_table_d ) );


/*
entry info:
Description | Type | Length | Comments
Processor  |     0 |     20 | One entry per processor.
Bus        |     1 |      8 | One entry per bus.
I/O APIC   |     2 |      8 | One entry per I/O APIC.
I/O 
Interrupt 
Assignment |     3 |      8 | One entry per bus interrupt source.
Local 
Interrupt 
Assignment |     4 |      8 | One entry per system interrupt source.
*/


// Estrutura para entradas que descrevem um processador.
// Processor = type 0.

    struct entry_processor_d *e;

// This routine gets the number of processors.
// #todo:
// We can create a method for that routine.
// Register this number into the global data.
    unsigned int NumberOfProcessors=0;
    g_processor_count = NumberOfProcessors;

// EntryCount has the max number of entries.
// #bugbug
// #test

    if ( EntryCount > 32 )
    {
        printf("#bugbug: EntryCount > 32\n");
        EntryCount = 32;
    }


// Clean the list.
    for (i=0; i<32; i++){
        smp_info.processors[i] = 0;
    };
    smp_info.number_of_processors = 0;

// loop:
// Check all the n entries indicated in the table above.
    for (i=0; i<EntryCount; i++)
    {
        // Tracing
        //printf("\n");
        //printf(":::: Entry %d:\n",i);
        
        // Looking for processors.
        e = (struct entry_processor_d *) entry_base;

        // It is a processor entry.
        if (e->type == 0){

            smp_info.processors[NumberOfProcessors] = (unsigned long) e;
            NumberOfProcessors += 1;

            // #todo
            // We neet a worker function for this job.
            printf ("PROCESSOR found! in entry %d\n",i);
            // apic id.
            printf("local_apic_id %d\n", e->local_apic_id);
            // apic version
            printf("local_apic_version %d\n", e->local_apic_version);
            // Flags:
            // If bit 0 is clear then the processor must be ignored.
            // If bit 1 is set then the processor is the bootstrap processor.
            // Ignore the processor.
            if( (e->flags & (1<<0)) == 0 ){
                printf("Processor must be ignored\n");
            }
            // BSP processor.
            if( e->flags & (1<<1) ){
                printf("smp_probe: The processor is a BSP\n");
            }
            printf ("stepping: %d\n", (e->signature & 0x00F));
            printf ("   model: %d\n",((e->signature & 0x0F0) >> 4) );
            printf ("  family: %d\n",((e->signature & 0xF00) >> 8) );

            entry_base = (unsigned long) (entry_base + 20);

        // Not a processor.
        } else if (e->type != 0){
            //printf ("Device type %d in entry %d\n", e->type, i );
            entry_base = (unsigned long) (entry_base + 8);
        }
    };

done:

    g_processor_count = 
        (unsigned int) NumberOfProcessors;
    smp_info.number_of_processors = (unsigned int) NumberOfProcessors;
    printf("Processor count: {%d}\n",g_processor_count);
    printf("smp_probe: done\n");

    smp_info.initialized = TRUE;

    // #debug
    //refresh_screen();
    //while(1){
    //};

    // g_smp_initialized = TRUE;
    return TRUE;
fail:
    //refresh_screen();
    g_smp_initialized = FALSE;
    smp_info.initialized = FALSE;
    return FALSE;
}

void smp_probe_via_acpi(void)
{
// After you've gathered the information, 
// you'll need to disable the PIC and prepare for I/O APIC. 
// You also need to setup BSP's local APIC. 
// Then, startup the APs using SIPIs.
}




