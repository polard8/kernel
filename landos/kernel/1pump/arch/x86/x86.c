/*
 * File: 1pump/arch/x86/x86.c
 *
 *    x86 misc support.
 *    #todo: Review all this thing.
 * 
 *    2005 - Created by Fred Nora.
 */


#include <kernel.h>


/*
#define NSLOTS(sz)	\
	(((sz) - DYNSEL_START) / sizeof(union descriptor))
#define NDYNSLOTS	NSLOTS(MAXGDTSIZ)
*/

#define NDYNSLOTS 8


typedef struct {

    int busy[NDYNSLOTS];
    //bool busy[NDYNSLOTS];

    size_t nslots;

} gdt_bitmap_t;

/* bitmap of busy slots */
static gdt_bitmap_t gdt_bitmap;



/*
//pega
static int
gdt_get_slot(void);
static int
gdt_get_slot(void)
{
	size_t i;

	//KASSERT(mutex_owned(&cpu_lock));

	for (i = 0; i < gdt_bitmap.nslots; i++) 
	{
		if (!gdt_bitmap.busy[i]) 
		{
			gdt_bitmap.busy[i] = true;
			return (int)i;
		}
	}
	
	panic ("gdt_get_slot: out of memory");

	// NOT REACHED
	return 0;
}
*/




/*
//libera
static void
gdt_put_slot(int slot);
static void
gdt_put_slot(int slot)
{
	//KASSERT(mutex_owned(&cpu_lock));
	//KASSERT(slot < gdt_bitmap.nslots);
	gdt_bitmap.busy[slot] = false;
}
*/




/*
int
tss_alloc(const struct i386tss *tss);
int
tss_alloc(const struct i386tss *tss)
{
	int slot;

	//mutex_enter(&cpu_lock);
	slot = gdt_get_slot();
	setgdt(slot, tss, sizeof(struct i386tss) + IOMAPSIZE - 1,
	    SDT_SYS386TSS, SEL_KPL, 0, 0);
	//mutex_exit(&cpu_lock);

	return GDYNSEL(slot, SEL_KPL);
}
*/




/*
void
tss_free(int sel);	
void
tss_free(int sel)
{

	//mutex_enter(&cpu_lock);
	gdt_put_slot(IDXDYNSEL(sel));
	//mutex_exit(&cpu_lock);
}
*/




/*
static unsigned short
get_cs(void)
{
	unsigned short _v;

	__asm__ ("movw %%cs,%0": "=r" ((unsigned short) _v));
	return _v;
}
*/



void x86_init_fpu (void) 
{
    asm volatile ("fninit");
}

// x86 disable interrupts.
void x86_disable_interrupts (void)
{
    asm ("cli"); 
}


// x86 enable interrupts.
void x86_enable_interrupts (void)
{
    asm ("sti");
}


void x86_iret (void)
{
    asm ("iret");
}


void x86_lret (void)
{
    asm ("lret");
}


void x86_cli_hlt(void)
{
    asm (" cli \n \t "); 
    asm (" hlt \n \t ");
}


void x86_stop_cpu (void)
{
    x86_cli_hlt();
}



int x86_get_eflags (unsigned long value)
{
    asm (" pushfl \n \t " 
         " popl %0      "  
       : "=r" (value) );
}

int x86_set_eflags (unsigned long value)
{
    asm (" pushl %0 \n\t "   
         " popfl         "   
           : : "r" (value) );
}


// Enable cache.
// credits: barrelfish.
// #todo: Test it on my real machine.

void x86_enable_cache (void)
{
    uint32_t cr0 = 0;

    asm volatile ("mov %%cr0, %[cr0]" : [cr0] "=r" (cr0) );

    cr0 &= ~CPUX86_CR0_CD;
    cr0 &= ~CPUX86_CR0_NW;
    
    asm volatile ("mov %[cr0], %%cr0" :: [cr0] "r" (cr0) );
}
 


/*
 ******************* 
 * setgate:
 * 
 */

// Set gate.
// Probably stolen from minix or netbsd.
// See: x86gdt.h

void
setgate ( 
    struct gate_descriptor_d *gd, 
    void *func, 
    int args, 
    int type, 
    int dpl,
    int sel )
{

    gd->gd_looffset = (int)func;
    gd->gd_selector = sel;
    gd->gd_stkcpy = args;
    gd->gd_xx = 0;
    gd->gd_type = type;
    gd->gd_dpl = dpl;
    gd->gd_p = 1;
    gd->gd_hioffset = (int)func >> 16;
}


// Unset gate.
// Probably stolen from minix or netbsd.
// See: sysio/hal/arch/x86/x86gdt.h

void unsetgate (struct gate_descriptor_d *gd)
{
	gd->gd_p = 0;
	gd->gd_hioffset = 0;
	gd->gd_looffset = 0;
	gd->gd_selector = 0;
	gd->gd_xx = 0;
	gd->gd_stkcpy = 0;
	gd->gd_type = 0;
	gd->gd_dpl = 0;
}


// Set region.
// Probably stolen from minix or netbsd.
// See: x86gdt.h
 
void
setregion ( 
    struct region_descriptor_d *rd, 
    void *base, 
    size_t limit )
{
    rd->rd_limit = (int) limit;
    rd->rd_base = (int) base;
}



// Set segment.
// Probably stolen from minix or netbsd.
// See: x86gdt.h

void
setsegment ( 
    struct segment_descriptor_d *sd, 
    const void *base, 
    size_t limit,
    int type, 
    int dpl, 
    int def32, 
    int gran )
{
    sd->sd_lolimit = (int) limit;
    sd->sd_lobase = (int) base;
    sd->sd_type = type;
    sd->sd_dpl = dpl;
    sd->sd_p = 1;
    sd->sd_hilimit = (int) limit >> 16;
    sd->sd_xx = 0;
    sd->sd_def32 = def32;
    sd->sd_gran = gran;
    sd->sd_hibase = (int) base >> 24;
}


// Set segment nr.
// Probably stolen from minix or netbsd.
// See: sysio/hal/arch/x86/x86gdt.h

void
setsegmentNR ( 
    int number, 
    const void *base, 
    size_t limit,
    int type, 
    int dpl, 
    int def32, 
    int gran )
{

    setsegment ( (struct segment_descriptor_d *) &xxx_gdt[number], 
        base, limit, type, dpl, def32, gran );
}


/*
 ***********************************
 * init_gdt:
 * 
 *     It creates a TSS and sets up some entries in the GDT.
 *     See: x86gdt.h
 */

int x86_init_gdt (void)
{
    struct i386tss_d *tss;


    debug_print ("[x86] x86_init_gdt: Danger!\n");


    // Creating a TSS and initializing it.

    tss = (void *) kmalloc ( sizeof(struct i386tss_d) );

    if ( (void *) tss == NULL ){
        debug_print ("[x86] x86_init_gdt: \n");
              panic ("[x86] x86_init_gdt: \n");

    }else{
 
        // Init TSS. 
        tss_init ( 
            (struct i386tss_d *) tss, 
            (void *) 0x003FFFF0, 
            (void *) 0x401000 );


         // Setup current.
         // ps: All threads are using the same tss.

         current_tss = tss;
         
         // #bugbug
         // #todo: Validation
         
         //if ( (void *) current_tss == NULL )
             //panic( ...
    };


	//
	// Initializing the GDT.
	//


    // NULL
    setsegment ( &xxx_gdt[GNULL_SEL], 0, 0, 0, 0, 0, 0 );


    // ring 0
    // SDT_MEMERA = 27 = 0x1B
    // SDT_MEMRWA = 19 = 0x13
    // SEL_KPL = 0
    setsegment ( &xxx_gdt[GCODE_SEL], 
        0, 0xfffff, SDT_MEMERA, SEL_KPL, 1, 1);
    setsegment ( &xxx_gdt[GDATA_SEL], 
        0, 0xfffff, SDT_MEMRWA, SEL_KPL, 1, 1);


    // ring 3
    // SDT_MEMERA = 27 = 0x1B
    // SDT_MEMRWA = 19 = 0x13
    // SEL_UPL = 3
    setsegment ( &xxx_gdt[GUCODE_SEL], 
        0, 0xfffff, SDT_MEMERA, SEL_UPL, 1, 1);
    setsegment ( &xxx_gdt[GUDATA_SEL], 
        0, 0xfffff, SDT_MEMRWA, SEL_UPL, 1, 1);


    // TSS selector.
    // (SDT_SYS386TSS=9=not busy) 
    // (11 = busy)
    setsegment ( &xxx_gdt[GTSS_SEL], 
        &tss, sizeof( struct i386tss_d ) - 1, 
        SDT_SYS386TSS,  SEL_KPL, 0, 0);

    //setsegment ( &xxx_gdt[GTSS_SEL], 
    //    &tss, sizeof ( struct i386tss_d ) - 1, 11,  SEL_KPL, 0, 0);



    // LDT selector.
    // #bugbug: 
    // #todo LDT size;
    setsegment ( &xxx_gdt[GLDT_SEL], 
        0, 0xff, SDT_SYSLDT,  SEL_KPL, 0, 0);

	//...


	//
	// Load GDT.
	//

    // Limit and base.
    xxx_gdt_ptr.limit = (unsigned short) ((32 * sizeof(struct segment_descriptor_d) ) -1);
    xxx_gdt_ptr.base  = (unsigned int) &xxx_gdt[GNULL_SEL];

    //register.
    load_gdt (&xxx_gdt_ptr);


    // Done!
    
    return 0;
}


/*
 * tss_init: 
 *     ?? internal ??
 */

static void
tss_init ( 
    struct i386tss_d *tss, 
    void *stack, 
    void *func )
{
	
	//KASSERT(curcpu()->ci_pmap == pmap_kernel());


    if ( (void *) tss == NULL ){
        panic ("[x86] tss_init:\n");
    }



    // Clean.
    memset ( tss, 0, sizeof *tss );


	//ring 0 stack
    tss->tss_esp0 = 0x003FFFF0;    // (int)((char *)stack + USPACE - 16);   //0x003FFFF0
    tss->tss_ss0 = GSEL(GDATA_SEL, SEL_KPL);	
	//tss->tss_ss0 = 0x10; //GSEL(GDATA_SEL, SEL_KPL);
	


	/* %cr3 contains the value associated to pmap_kernel */
    tss->tss_cr3 = 0x9C000;             //rcr3();   // 0x9C000   Thread->Directory ??
    tss->__tss_eip = (int) 0x401000;    //(int) func;
	/* XXX not needed? */
    tss->__tss_eflags = 0x3200;   //PSL_MBO | PSL_NT;	  // PSL_IOPL PSL_I

    tss->tss_esp = 0x0044FFF0; //(int)((char *)stack + USPACE - 16);  //0x0044FFF0


    tss->__tss_es = GSEL(GUDATA_SEL, SEL_UPL); 
    tss->__tss_cs = GSEL(GUCODE_SEL, SEL_UPL);  //0x1B 
    tss->__tss_ss = GSEL(GUDATA_SEL, SEL_UPL); 
    tss->__tss_ds = GSEL(GUDATA_SEL, SEL_UPL);  //0x23
    tss->tss_fs = GSEL(GUDATA_SEL, SEL_UPL); 
    tss->tss_gs = GSEL(GUDATA_SEL, SEL_UPL); 
    tss->tss_ldt = GSEL(GLDT_SEL, SEL_KPL);
    

	/*
	tss->__tss_es = 0x23; // GSEL(GUDATA_SEL, SEL_UPL); //GSEL(GDATA_SEL, SEL_KPL);	
	tss->__tss_cs = 0x1B; //GSEL(GUCODE_SEL, SEL_UPL); //GSEL(GCODE_SEL, SEL_KPL);
	tss->__tss_ss = 0x23; //GSEL(GUDATA_SEL, SEL_UPL); //GSEL(GCODE_SEL, SEL_KPL);
	tss->__tss_ds = 0x23; //GSEL(GUDATA_SEL, SEL_UPL); //GSEL(GCODE_SEL, SEL_KPL);

    //for fs
    ////GSEL(GDATA_SEL, SEL_KPL);
    //tss->tss_fs = GSEL(GCPU_SEL, SEL_KPL);
	tss->tss_fs =  0x23; //GSEL(GUDATA_SEL, SEL_UPL);
  
	tss->tss_gs = 0x23;  // GSEL(GUDATA_SEL, SEL_UPL); //GSEL(GDATA_SEL, SEL_KPL);
	tss->tss_ldt = 0x30; ////GSEL ( GLDT_SEL, SEL_KPL );
	*/

    tss->tss_iobase = IOMAP_VALIDOFF << 16;
}



/*
// ??
// Atualizando a pilha de ring 0 na tss atual.
void tss_set_kernel_stack (unsigned long stack_address );
void tss_set_kernel_stack (unsigned long stack_address )
{
    if ( (void *) current_tss == NULL )
	    return;
		
	current_tss->tss_esp0 = stack_address;
}
*/



/*
 *********************************************************************
 * get_cpu_intel_parameters:
 *     Pega os parâmetros da cpu x86 através da instrução cpuid.
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


/*
 ***********************************************
 * init_intel:
 *     
 *     Enable caches.
 *     Get system info using cpuid instruction.
 *     // ...
 *  
 *     See: x86.h
 */


// Called by init_architecture_dependent() on core/init.c

int x86_init_intel (void)
{
    debug_print ("[x86] x86_init_intel:");


    x86fault_initialize();

    // #bugbug
    // Suspended.
    // We need to teste the effects os this routine in the real machine.
    // See: sysio/hal/arch/x86/x86.h
    // See: sysio/hal/arch/x86/x86.c
    
    x86_enable_cache();

    // Get info.
    // See: x86.c
    get_cpu_intel_parameters();

    // ...

    return 0;
}


// Initializes sse support.
// Credits: Serenity OS.

void x86_sse_init (void)
{
    debug_print("x86_sse_init: [TEST]\n");

    asm volatile (
        "mov %cr0, %eax\n"
        "andl $0xfffffffb, %eax\n"
        "orl $0x2, %eax\n"
        "mov %eax, %cr0\n"
        "mov %cr4, %eax\n"
        "orl $0x600, %eax\n"
        "mov %eax, %cr4\n" );
}



/*
 #todo
void x86_firmware_dialog( int routine_number );
void x86_firmware_dialog( int routine_number )
{
    switch(routine_number){
    
        //reboot
        case 1:
            hal_reboot();
            break;
        
        //shutdown
        case 2:
            hal_shutdown();
            break;
        
        // ...
        
        default:
            break;

    };
}
*/



//
// End.
//
