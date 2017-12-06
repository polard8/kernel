/*
 * File: cpux86.c 
 * 
 * Descrição:
 *     Rotinas de gerenciamento da cpu x86.
 *
 * Atribuições:
 *  + Pegar os parametros da cpu.
 *  + Inicializar a cpu presente.
 *  + ...
 *
 * In this file:
 *  + cpu_get_parameters
 *  + KeTestCPU
 *
 */

/*
 * @todo: cria a função init_cpu.
 */
 

#include <kernel.h>



/*
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
 *
 */
void get_cpu_intel_parameters()
{
    int MASK_LSB_8 = 0xFF;  
	unsigned long eax, ebx, ecx, edx;
	unsigned long name[32];	
		
	//debug.
	//printf("Scaning x86 CPU ...\n");
		
    //Vendor.
	//eax = Maximum meaningful value for the InfoType parameter. @todo:
    //ebx = Identification String (part 1)
	//ecx = Identification String (part 3)
	//edx = Identification String (part 2)
	cpuid( 0, eax, ebx, ecx, edx ); 
	name[0] = ebx;
	name[1] = edx;
	name[2] = ecx;
	name[3] = 0;	
	//salva na estrutura.
	processor->Vendor[0] = ebx;
	processor->Vendor[1] = edx;
	processor->Vendor[2] = ecx;
	processor->Vendor[3] = 0;	
	
	//
	// Confere se é Intel.
	//
	
	if( ebx == CPUID_VENDOR_INTEL_1 && 
	    edx == CPUID_VENDOR_INTEL_2 && 
		ecx == CPUID_VENDOR_INTEL_3 )
	{
	    hal_set_machine_type(1);    //Intel.
	};
	
	
	//
	//Output para argumento 1. 
	//
	
	//eax:
    //0-3 Stepping ID
    //4-7 Model
	//8-11 Family
	//12-13 Processor Type
	//14-15 Reserved
	//16-19 Extended model
	//20-27 Extended family
	//28-31 Reserved

    //ebx:
	//0-7 Brand Index
	//8-15 CLFLUSH cache line size / 8
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
	//5 MSR RDMSR and WRMSR Support
	//6 PAE Physical Address Extensions
	//7 MCE Machine Check Exception
	//8 CX8 CMPXCHG8B Inst.
	//9 APIC APIC on Chip ***
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
	
	
	
	cpuid( 1, eax, ebx, ecx, edx );
	
	//eax:
	//processor->xx = (unsigned long)( eax & 0xF);       //stepping
	//processor->xx = (unsigned long)((eax >> 4) & 0xf); //model
	//processor->xx = (unsigned long)((eax >> 8) & 0xf); //family
	//processor->xx = (unsigned long)((eax >> 12) & 0x3); //processor type
	//processor->xx = (unsigned long)((eax >> 16) & 0xf); //extended model
	//processor->xx = (unsigned long)((eax >> 20) & 0xff); //extended family
	//...
	
	//ebx:
	//processor->xx = (unsigned long)((ebx >> 9) & 0x0001);
    //... 
	
	//ecx:
	//processor->xx = (unsigned long)((ebx >> 9) & 0x0001);
	//...
	
	//edx:
	//processor->isApic = (unsigned long)((edx >> 9) & 0x0001);
	processor->isApic = (unsigned long) edx;
	//...
	
	//Serial number ???
	//cpuid( 3, eax, ebx, ecx, edx );
	
	//Check number of cores.
	//cpuid( 4, eax, ebx, ecx, edx );
	
   /*name part 1*/
    cpuid( 0x80000002, eax, ebx, ecx, edx);
	name[0] = eax; //Processor Brand String
	name[1] = ebx; //Processor Brand String
	name[2] = ecx; //Processor Brand String
	name[3] = edx; //Processor Brand String
    name[4] = 0;	    
	//salva na estrutura.
	processor->BrandName[0] = eax;	
	processor->BrandName[1] = ebx;
	processor->BrandName[2] = ecx;
	processor->BrandName[3] = edx;
	//printf("CPU={%s", &name[0]);
	//printf("%s",&name[0]);		

   /*name part 2*/
    cpuid( 0x80000003, eax, ebx, ecx, edx);
	name[0] = eax; //Processor Brand String, continued
	name[1] = ebx; //Processor Brand String, continued
	name[2] = ecx; //Processor Brand String, continued
	name[3] = edx; //Processor Brand String, continued
    name[4] = 0;	
	//salva na estrutura.	
	processor->BrandName[4] = eax;	
	processor->BrandName[5] = ebx;
	processor->BrandName[6] = ecx;
	processor->BrandName[7] = edx;
	//printf("%s",&name[0]);	

   /*name part 3*/
    cpuid( 0x80000004, eax, ebx, ecx, edx);
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
	
	
	//Max feature id.
    cpuid( 0x80000000, eax, ebx, ecx, edx);
	name[0] = eax; //Maximum meaningful value of InfoType for extended function CPUID information.
	name[1] = ebx; //reserved
	name[2] = ecx; //reserved
	name[3] = edx; //reserved
    name[4] = 0;   
	processor->MaxFeatureId = (unsigned long)(eax & MASK_LSB_8);
	//printf("Max feature id ={%d}\n", (unsigned long) processor->MaxFeatureId);
	
    if(	processor->MaxFeatureId < 6){  	
		printf("Cache Extended Feature not supported.\n");
		goto done;
	};
	
	
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
    cpuid( 0x80000006, eax, ebx, ecx, edx );
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
		
    //EAX=80000007h: Advanced Power Management Information
	
	/*
	 * Virtual and physical memory sizes.
	 */
	
    //EAX=80000008h: Virtual and Physical address Sizes	
    cpuid( 0x80000008, eax, ebx, ecx, edx );
	name[0] = eax;    //Virtual and physical memory sizes.
	name[1] = ebx;    //reserved
	name[2] = ecx;    //reserved
	name[3] = edx;    //reserved
    name[4] = 0;	
	processor->Physical_Address_Size = (unsigned long) ( eax       & 0x00FF); //7-0
	processor->Virtual_Address_Size  = (unsigned long) ((eax >> 8) & 0x00FF); //15-8	
	//printf("Physical_Address_Size={%d}\n",(unsigned long) processor->Physical_Address_Size);
	//printf("Virtual_Address_Size={%d}\n", (unsigned long) processor->Virtual_Address_Size);
	
	
//
// Done.
//	

done:
    //printf("done\n");
    return;
};



/*
 * cpu_get_parameters:
 *   Sonda a CPU pra saber seus parâmetros.
 *   (OEM)
 *
 */ 
int cpu_get_parameters()
{
    // @todo: Copiar a função KeTestCPU aqui.
	// @todo: Mudar nome para KeProbeCPU(
	
    return (int) KeTestCPU(); 
};
 

/*
 * KeTestCPU:
 *     Pega os parametros do CPU.
 * 
 * (bugbug) Problemas ao utilizar a estrutura 
 *          para registrar as informações.
 * 
 * @todo: 
 *     Mudar para scanCPUx86()
 *
 */
int KeTestCPU()
{
    //
	// Get info.
	//
	
	get_cpu_intel_parameters();
	
	
//
// Done.
//
	
done:	
	return (int) 0;
};



/*
 * show_cpu_intel_parameters:
 *     Mostra os parametros da CPU intel.
 *
 * @todo: 
 *     Colocar em janela. 
 *     Criar funções: TerminalShowCPUIntelParameters()
 *                    ShowCPUIntelParameters()
 */
void show_cpu_intel_parameters()
{
    //Title.
    printf("\nx86 CPU Info:\n\n");
	//printf("=============\n");
	
	//
    // Vendor, Name, is apic supported ?, Max feature id,
    // L2 Line size, L2 cache size,
    //
	
	printf("          Vendor: {%s}\n", &processor->Vendor[0]);
	printf("             Cpu: {%s}\n", &processor->BrandName[0]);	
	//printf("ApicSupport={%x}\n", processor->isApic);
	printf("  Max feature id: {%d}\n",(unsigned long) processor->MaxFeatureId);
	printf("    L2 line size: {%d Byte}\n",(unsigned long) processor->L2LineSize); //Bits 0-7: Cache Line Size.	
	
	//
	// L2 Associativity. 	
	//
	
	switch(processor->L2Associativity)
	{
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

	printf("   L2 cache size: {%d KB}\n",(unsigned long) processor->L2Cachesize); //Bits 16-31: Cache size in 1K units.	

	//
	// Physical and Virtual Address.
	//
	
	//Provavelmente é o número máximo de bits na arquitetura.
	//tanto em memória física como virtual.
	//36 ou 39 indica memória extendida. normal é 32=(4GB).
	// maximum physical address bits  
	//maximum linear (virtual) address bits 
	printf("         PA Lim.: {%d}\n",(unsigned long) processor->Physical_Address_Size);
	printf("         VA Lim.: {%d}\n",(unsigned long) processor->Virtual_Address_Size);
	
	//printf("     Memory Size: {%d}\n",(unsigned long) processor->MemorySize);
	
	//Continua...
	
//
// Done.
//	

done:
	return;
};


/*
 * init_intel:
 *     Inicializa processador Intel.
 *
 */
int init_intel()
{
	// Get info.
	get_cpu_intel_parameters();
	return (int) 0;
};

//
//fim.
//

