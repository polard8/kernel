/*
 * File: x86.c
 *
 * Descrição:
 *     Suporte às portas na arquitetura x86.
 *
 *     O acesso as portas também será oferecido na forma de serviços, para
 * que processos servidores também possam configurar o hardware diretamente.
 * Logicamente algum tipo de filtro será criado, para conferir a permissão.
 *
 *  @todo: Muita função aqui deveria ter o retorno do tipo void.
 *
 */

 
#include <kernel.h>


/*
#define NSLOTS(sz)	\
	(((sz) - DYNSEL_START) / sizeof(union descriptor))
#define NDYNSLOTS	NSLOTS(MAXGDTSIZ)
*/

#define NDYNSLOTS 8

typedef struct {
	
	//bool busy[NDYNSLOTS];
	int busy[NDYNSLOTS];
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


// habilita as interrupções
int enable (){
	
    asm ("sti");

    //@todo: Porque habilitar as interrupções deveria mudar o valor do registrador eax.
    //talvez deveria ser void o tipo da função.	
    
	return (int) 0;
}


// desabilita as interrupções
int disable (){
	
    asm ("cli"); 

    //@todo: Porque desabilitar as interrupções deveria mudar o valor do registrador eax.
    //talvez deveria ser void o tipo da função.		
    
	return (int) 0;
}


int stopCpu (){
	
    __asm (" cli \n \t " 
		   " hlt ");
}


int intReturn (){
	
    __asm ("iret");
}


int farReturn (){
	
    __asm ("lret");
}


int getFlags (int variable){
	
    __asm (" pushfl \n \t "     
           " popl %0 "         
           : "=r" (variable) );
}


int setFlags (int variable){
	
    __asm ("pushl %0 \n\t"   
           "popfl"           
           : : "r" (variable) );
}



int Push (int value){
	
    __asm ("pushl %0" : : "r" (value) : "%esp");
};


int Pop (int variable){
	
    __asm ("popl %0" : "=r" (variable) : : "%esp");
};


int pushRegs (){
	
    __asm ("pushal" : : : "%esp");
};


int popRegs (){
	
    __asm ("popal" : : : "%esp");
};


int pushFlags (){
	
    __asm ("pushfl" : : : "%esp");
};


int popFlags (){
	
    __asm ("popfl" : : : "%esp");
};


int getStackPointer (int addr){
	
    __asm ("movl %%esp, %0" : "=r" (addr) );
};


int setStackPointer (int addr){
	
    __asm ("movl %0, %%esp" : : "r" (addr) : "%esp");
};



//habilita cache.
//credits: barrelfish

void cpux86_enable_caches (){
	
    uint32_t cr0;

    __asm volatile ("mov %%cr0, %[cr0]" : [cr0] "=r" (cr0) );
	
    cr0 &= ~CPUX86_CR0_CD;
    cr0 &= ~CPUX86_CR0_NW;
    
	__asm volatile ("mov %[cr0], %%cr0" :: [cr0] "r" (cr0) );
}
 


void
setgate(struct gate_descriptor_d *gd, void *func, int args, int type, int dpl,
    int sel)
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

void
unsetgate(struct gate_descriptor_d *gd)
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
 
 
void
setregion(struct region_descriptor_d *rd, void *base, size_t limit)
{

	rd->rd_limit = (int)limit;
	rd->rd_base = (int)base;
}

void
setsegment(struct segment_descriptor_d *sd, const void *base, size_t limit,
    int type, int dpl, int def32, int gran)
{

	sd->sd_lolimit = (int)limit;
	sd->sd_lobase = (int)base;
	sd->sd_type = type;
	sd->sd_dpl = dpl;
	sd->sd_p = 1;
	sd->sd_hilimit = (int)limit >> 16;
	sd->sd_xx = 0;
	sd->sd_def32 = def32;
	sd->sd_gran = gran;
	sd->sd_hibase = (int)base >> 24;
}



/*
 ***********************************************
 * init_intel:
 *     Inicializa processador Intel.
 */
 
int init_intel (){
	
	cpux86_enable_caches ();
	
	// Get info.
	get_cpu_intel_parameters ();
	
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

void show_cpu_intel_parameters (){
	
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
            printf("L2 Associativity: {Disabled}\n");
		    break; 
	    case 0x01:
	        printf("L2 Associativity: {Direct mapped}\n");
		    break; 
	    case 0x02:
	        printf("L2 Associativit: {2-way associative}\n");
		    break; 
	    case 0x04:
	        printf("L2 Associativity: {4-way associative}\n");
		    break; 
	    case 0x06:
	        printf("L2 Associativity: {8-way associative}\n");
		    break; 
	    case 0x08:
	        printf("L2 Associativity: {16-way associative}\n");
		    break; 
	    case 0x0F:
	        printf("L2 Associativity: {Fully associative}\n");
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
};




//
// End.
//
