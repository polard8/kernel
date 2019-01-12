/*
 * File: cpu.h 
 *
 * Descrição:
 *     Header para gerenciamento de cpus.
 *
 *     CPUs em Desktops:
 *         Intel, AMD.
 *
 *     CPUs para dispositivos embarcados:
 *         Intel Quark.
 *
 * @todo: boa parte do que está aqui pode ir 
 * para /hardware/intel.h e hardware/amd.h
 *
 * 2015 - Fred Nora.
 */
 
	
 
/* 
 * System Modes support.
 */
 
#define SI_RM 0    //Real Mode.
#define SI_PM 1    //Protected Mode.
#define SI_LM 2    //Long Mode.
//#define SI_SM 3    //SMM.


//values for cpu mode
//#define	CPU16	1
//#define	CPU32	2
//#define	CPU64	3



/*
 * Processors support.
 */

#define Processor_NULL  0 
#define Processor_INTEL 1
#define Processor_AMD   2
//#define Processor_xxxx   3
//...

 
/*
 * Globais.
 */ 
  
  
/*
 * Structures.
 */  
  
  
//Informações sobre um processador.  
typedef struct tagProcessor processor_descriptor_t;
struct tagProcessor   
{
	object_type_t objectType;
	object_class_t objectClass;	
	
	//
	// @todo: Uma das primeiras coisas deve ser as threads 
	//        de cada processador.
	//        
	//
	
    //struct _KTHREAD *CurrentThread;
    //struct _KTHREAD *NextThread;
    //struct _KTHREAD *IdleThread;	
	
	//@todo: Processor State ???
	
	
	//@todo: Reservar espaço ???
	//ULONG   KernelReserved[16];         // For use by the kernel
    //ULONG   HalReserved[16];            // For use by Hal
	
	//@todo: quantas vezes um processador foi interrompido.
	// ULONG   InterruptCount;             // per precessor counts
	
	
	//
	// Processor information:
	//
	
    unsigned char Id;	
	unsigned char Type;
	
	//@todo: ULONG MHz;
	
	
	//0x0.
	//cpuid vars.
	unsigned long Vendor[4];


	//0x1(eax)
	//unsigned long stepping;
	//model
	//family
	//processor type
	//extended model
	//extended family
	
	//0x1(ebx)
	//Brand Index
	//CLFLUSH cache line size / 8
	//APIC Physical ID
	//...
	
	//0x1(ecx)
	//0 SSE3 New Instructions
	//1-2 Reserved
	//3 MONITOR/MWAIT
	//4 CPL Qualified Debug Store
	//5-7 Reserved
	//8 Thermal Monitor 2
	//9 Reserved
	//10 L1 Context ID
	//11-31 Reserved
	
	//0x1(edx)
    //0 FPU x87 FPU on Chip
	//1 VME Virtual-8086 Mode Enhancement
	//2 DE Debugging Extensions
	//3 PSE Page Size Extensions
	//4 TSC Time Stamp Counter
	//5 MSR RDMSR and WRMSR Support
	//6 PAE Physical Address Extensions
	//7 MCE Machine Check Exception
	//8 CX8 CMPXCHG8B Inst.
	unsigned long isApic;    //O processador suporta APIC.	
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
	//...
	
	
	//0x80000000 (eax) (Max feature id.).
	//Maximum meaningful value of InfoType for extended function CPUID information.
    unsigned long MaxFeatureId;
	
    //0x80000002,0x80000003,0x80000004 (Brand name)	
	unsigned long BrandName[4*3];
	
	//0x80000006(ecx) (L2 cache information (Intel)).
	unsigned long L2LineSize;
	unsigned long L2Associativity;
	unsigned long L2Cachesize;
	
	unsigned long L1LineSize; 	
	unsigned long L3LineSize;
	
	unsigned long L1Associativity;
	unsigned long L3Associativity;
	
	unsigned long L1Cachesize;
	unsigned long L3Cachesize;
	
	
	//0x80000008(eax??) (Virtual and physical memory sizes.)
	unsigned long Physical_Address_Size;
	unsigned long Virtual_Address_Size;
	//...
	
	
	//unsigned long MemorySize; 
	
	//
	//
	//
	
	//cada processador tem sua gdt, idt, tss.
	unsigned long Gdt;
	unsigned long Idt;
	unsigned long Tss;	
	
	
	
    //Threads presentes no processador.
	int currentId;    //id.
    int idleId;       //id.
    int nextId;       //id.
	
	//Threads.
	struct thread_d *IdleThread;       //ponteiro para estrutura.
	//struct thread_d *ShellThread;       //ponteiro para estrutura. isso nao interessa para o processador
	//struct thread_d *TaskManThread;       //ponteiro para estrutura. isso nao interessa para o processador	
	struct thread_d *CurrentThread;    //ponteiro para estrutura.
	struct thread_d *NextThread;       //ponteiro para estrutura.

	
	//processos
	struct process_d *IdleProcess;       //ponteiro para estrutura.
	struct process_d *CurrentProcess;    //ponteiro para estrutura.
	struct process_d *NextProcess;       //ponteiro para estrutura.

	
	//...
};
processor_descriptor_t *processor; 
 

//@todo: liberar essa lista. 
//unsigned long processorList[32]; 
 

/*
 * Prototypes.
 */
 




//Rotines.
void init_cpu();
int cpu_get_parameters();
int KeTestCPU();   //@todo: Isso deve isr para include/ke.h.


//
//fim.
//

