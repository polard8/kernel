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
