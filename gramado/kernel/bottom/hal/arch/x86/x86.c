/*
 * File: hal/arch/x86/x86.c
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





// x86 enable interrupts.

void enable (void)
{
    asm ("sti");
}

// x86 disable interrupts.

void disable (void)
{
    asm ("cli"); 
}


void farReturn (void)
{
    asm ("lret");
}


void intReturn (void)
{
    asm ("iret");
}


void stopCpu (void)
{
    asm (" cli \n \t "); 
    asm (" hlt \n \t ");
}


// ?? return value
int getFlags (int variable){

    __asm (" pushfl \n \t "     
           " popl %0 "         
           : "=r" (variable) );
}


// ?? return value
int setFlags (int variable){

    __asm ("pushl %0 \n\t"   
           "popfl"           
           : : "r" (variable) );
}






// Enable cache.
// credits: barrelfish.
// #todo: Test it on my real machine.

void cpux86_enable_caches (void){

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

int init_gdt (void){

    struct i386tss_d *tss;


    debug_print ("[x86] init_gdt: Danger!\n");


    // Creating a TSS and initializing it.

    tss = (void *) kmalloc ( sizeof(struct i386tss_d) );

    if ( (void *) tss == NULL ){
        debug_print ("[x86] init_gdt: \n");
        panic ("[x86] init_gdt: \n");

    }else{
 
        // Init TSS. 
        tss_init ( (struct i386tss_d *) tss, 
            (void *) 0x003FFFF0, (void *) 0x401000 );


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
 ***********************************************
 * init_intel:
 *     Inicializa processador Intel.
 *     See: x86.h
 */
 
int init_intel (void){

    debug_print ("[x86] init_intel:");

    // #bugbug
    // Suspended.
    // We need to teste the effects os this routine in the real machine.
    // See: sysio/hal/arch/x86/x86.h
    // See: sysio/hal/arch/x86/x86.c
    
    cpux86_enable_caches ();

    // Get info.
    get_cpu_intel_parameters ();

    // ...

    return 0;
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
	
    //Title.
    printf("\nx86 CPU Info:\n\n");
	//printf("=============\n");
	
	//
    // Vendor, Name, is apic supported ?, Max feature id,
    // L2 Line size, L2 cache size,
    //
	
	printf("          Vendor: {%s}\n", &processor->Vendor[0] );
	printf("             Cpu: {%s}\n", &processor->BrandName[0] );	
	//printf("ApicSupport={%x}\n", processor->isApic);
	printf("  Max feature id: {%d}\n", 
	    (unsigned long) processor->MaxFeatureId );
	
	//Bits 0-7: Cache Line Size.
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

	//Bits 16-31: Cache size in 1K units.
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
	
	printf("          PA Lim: {%d}\n", 
	    (unsigned long) processor->Physical_Address_Size );
		
	printf("          VA Lim: {%d}\n", 
	    (unsigned long) processor->Virtual_Address_Size );
	
	//printf("     Memory Size: {%d}\n",(unsigned long) processor->MemorySize);
	
	//Continua...

    //como não usa janelas devemos dar refresh na tela todo por enquanto.

	//#bugbug: isso é lento.
    refresh_screen();
}


// Initializes sse support.
void x86_sse_init (void)
{
    asm volatile (
        "mov %cr0, %eax\n"
        "andl $0xfffffffb, %eax\n"
        "orl $0x2, %eax\n"
        "mov %eax, %cr0\n"
        "mov %cr4, %eax\n"
        "orl $0x600, %eax\n"
        "mov %eax, %cr4\n" );
}


//
// End.
//
