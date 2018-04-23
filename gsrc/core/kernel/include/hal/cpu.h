/*
 * Arquivo: cpu.h 
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
 * Versão 1.0, 2015.
 */
 
 
//cpuid.
#define cpuid( in, a, b, c, d)\
        asm("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));
		
 
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
 * Vendor Strings. 
 */
 
#define CPUID_VENDOR_INTEL   "GenuineIntel"        //Intel.     
#define CPUID_VENDOR_AMD     "AuthenticAMD"        //AMD.
#define CPUID_VENDOR_OLDAMD  "AMDisbetter!"        //AMD.   
#define CPUID_VENDOR_VIA     "CentaurHauls"        //VIA.
#define CPUID_VENDOR_SIS     "SiS SiS SiS "        //SIS.
#define CPUID_VENDOR_OLDTRANSMETA  "TransmetaCPU"
#define CPUID_VENDOR_TRANSMETA     "GenuineTMx86"
#define CPUID_VENDOR_CYRIX         "CyrixInstead"
#define CPUID_VENDOR_CENTAUR       "CentaurHauls"
#define CPUID_VENDOR_NEXGEN        "NexGenDriven"
#define CPUID_VENDOR_UMC           "UMC UMC UMC "
#define CPUID_VENDOR_NSC           "Geode by NSC"
#define CPUID_VENDOR_RISE          "RiseRiseRise"
//...

//Intel.
#define CPUID_VENDOR_INTEL_1  0x756e6547    //"Genu" 
#define CPUID_VENDOR_INTEL_2  0x49656e69    //"ineI" 
#define CPUID_VENDOR_INTEL_3  0x6c65746e    //"ntel" 

//AMD.
#define CPUID_VENDOR_AMD_1    0x68747541    //"Auth" 
#define CPUID_VENDOR_AMD_2    0x69746e65    //"enti" 
#define CPUID_VENDOR_AMD_3    0x444d4163    //"cAMD"

 
//
// CPU Features
// When called with EAX = 1 (CPUID_GETFEATURES), CPUID returns a bit field 
// in EDX containing the following values. (osdev)
//

/*

enum {
    CPUID_FEAT_ECX_SSE3         = 1 << 0, 
    CPUID_FEAT_ECX_PCLMUL       = 1 << 1,
    CPUID_FEAT_ECX_DTES64       = 1 << 2,
    CPUID_FEAT_ECX_MONITOR      = 1 << 3,  
    CPUID_FEAT_ECX_DS_CPL       = 1 << 4,  
    CPUID_FEAT_ECX_VMX          = 1 << 5,  
    CPUID_FEAT_ECX_SMX          = 1 << 6,  
    CPUID_FEAT_ECX_EST          = 1 << 7,  
    CPUID_FEAT_ECX_TM2          = 1 << 8,  
    CPUID_FEAT_ECX_SSSE3        = 1 << 9,  
    CPUID_FEAT_ECX_CID          = 1 << 10,
    CPUID_FEAT_ECX_FMA          = 1 << 12,
    CPUID_FEAT_ECX_CX16         = 1 << 13, 
    CPUID_FEAT_ECX_ETPRD        = 1 << 14, 
    CPUID_FEAT_ECX_PDCM         = 1 << 15, 
    CPUID_FEAT_ECX_DCA          = 1 << 18, 
    CPUID_FEAT_ECX_SSE4_1       = 1 << 19, 
    CPUID_FEAT_ECX_SSE4_2       = 1 << 20, 
    CPUID_FEAT_ECX_x2APIC       = 1 << 21, 
    CPUID_FEAT_ECX_MOVBE        = 1 << 22, 
    CPUID_FEAT_ECX_POPCNT       = 1 << 23, 
    CPUID_FEAT_ECX_AES          = 1 << 25, 
    CPUID_FEAT_ECX_XSAVE        = 1 << 26, 
    CPUID_FEAT_ECX_OSXSAVE      = 1 << 27, 
    CPUID_FEAT_ECX_AVX          = 1 << 28,
 
    CPUID_FEAT_EDX_FPU          = 1 << 0,  
    CPUID_FEAT_EDX_VME          = 1 << 1,  
    CPUID_FEAT_EDX_DE           = 1 << 2,  
    CPUID_FEAT_EDX_PSE          = 1 << 3,  
    CPUID_FEAT_EDX_TSC          = 1 << 4,  
    CPUID_FEAT_EDX_MSR          = 1 << 5,  
    CPUID_FEAT_EDX_PAE          = 1 << 6,  
    CPUID_FEAT_EDX_MCE          = 1 << 7,  
    CPUID_FEAT_EDX_CX8          = 1 << 8,  
    CPUID_FEAT_EDX_APIC         = 1 << 9,  
    CPUID_FEAT_EDX_SEP          = 1 << 11, 
    CPUID_FEAT_EDX_MTRR         = 1 << 12, 
    CPUID_FEAT_EDX_PGE          = 1 << 13, 
    CPUID_FEAT_EDX_MCA          = 1 << 14, 
    CPUID_FEAT_EDX_CMOV         = 1 << 15, 
    CPUID_FEAT_EDX_PAT          = 1 << 16, 
    CPUID_FEAT_EDX_PSE36        = 1 << 17, 
    CPUID_FEAT_EDX_PSN          = 1 << 18, 
    CPUID_FEAT_EDX_CLF          = 1 << 19, 
    CPUID_FEAT_EDX_DTES         = 1 << 21, 
    CPUID_FEAT_EDX_ACPI         = 1 << 22, 
    CPUID_FEAT_EDX_MMX          = 1 << 23, 
    CPUID_FEAT_EDX_FXSR         = 1 << 24, 
    CPUID_FEAT_EDX_SSE          = 1 << 25, 
    CPUID_FEAT_EDX_SSE2         = 1 << 26, 
    CPUID_FEAT_EDX_SS           = 1 << 27, 
    CPUID_FEAT_EDX_HTT          = 1 << 28, 
    CPUID_FEAT_EDX_TM1          = 1 << 29, 
    CPUID_FEAT_EDX_IA64         = 1 << 30,
    CPUID_FEAT_EDX_PBE          = 1 << 31
};
*/

 
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
 

//Ports and instructions.
int enable();
int disable();
int stopCpu();      
int intReturn();
int farReturn();
int getFlags(int variable);
int setFlags(int variable);
int kernelProcessorInPort8(int port,int data);
int kernelProcessorOutPort8(int port,int data);
int kernelProcessorInPort16(int port,int data);
int kernelProcessorOutPort16(int port,int data);
int kernelProcessorInPort32(int port,int data); 
int kernelProcessorOutPort32(int port,int data);
int Push(int value);
int Pop(int variable);
int pushRegs();
int popRegs();
int pushFlags();
int popFlags();
int getStackPointer(int addr);
int setStackPointer(int addr);


//Rotines.
void init_cpu();
int cpu_get_parameters();
void get_cpu_intel_parameters();
void get_cpu_amd_parameters();
int KeTestCPU();   //@todo: Isso deve isr para include/ke.h.
void show_cpu_intel_parameters();

//
//fim.
//

