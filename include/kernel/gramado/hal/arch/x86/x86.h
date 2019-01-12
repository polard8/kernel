
//x86.h 

#define CPUX86_CR0_CD  (1 << 30)
#define CPUX86_CR0_NW  (1 << 29)
#define CPUX86_CR0_PG  (1 << 31)
#define CPUX86_CR4_MPE (1 << 11)
#define CPUX86_CR4_PCE (1 << 8)
#define CPUX86_CR4_PGE (1 << 7)
#define CPUX86_CR4_PAE (1 << 5)
#define CPUX86_CR4_PSE (1 << 4)

//instructions.
int enable();
int disable();
int stopCpu();      
int intReturn();
int farReturn();
int getFlags(int variable);
int setFlags(int variable);
int Push(int value);
int Pop(int variable);
int pushRegs();
int popRegs();
int pushFlags();
int popFlags();
int getStackPointer(int addr);
int setStackPointer(int addr);


//habilita cache.
void cpux86_enable_caches();

int init_intel();

void show_cpu_intel_parameters();



