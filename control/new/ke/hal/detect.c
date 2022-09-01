
// detect.c


//
// FRED
//

/*
FRED:

== Enumeration:
CPUID.(EAX=7,ECX=1):EAX[bit 17] is a new feature flag 
that enumerates support for the new FRED transitions. 
It also enumerates support for the new architectural state
(MSRs) defined by FRED.
CPUID.(EAX=7,ECX=1):EAX[bit 18] is another new CPUID feature flag 
that enumerates support for the LKGS instruction.

== Enabling in CR4:
When FRED transitions are enabled (CR4.FRED = IA32_EFER.LMA = 1), 
IDT event delivery of exceptions and interrupts is replaced 
with FRED event delivery.
Setting CR4.FRED enables FRED event delivery. CR4[32].

== New MSRs for Configuration of FRED Transitions:
+IA32_FRED_CONFIG (MSR index 1D4H).
+IA32_FRED_RSP0, IA32_FRED_RSP1, IA32_FRED_RSP2, and IA32_FRED_RSP3
(MSR indices 1CCH–1CFH).
+IA32_FRED_SSP1, IA32_FRED_SSP2, and IA32_FRED_SSP3 (MSR indices 1D1H–
1D3H).

-------------
far CALL, far JMP, far RET, and IRET. Enabling FRED
transitions modifies the operation of these instructions. 
A FRED-enabled operating system cannot use them for ring transitions.

*/

#include <kernel.h>

//see: hv.h
int g_is_qemu=FALSE;
int g_is_kvm=FALSE;
int g_is_bhyve=FALSE;
int g_is_qnx=FALSE;
int g_is_acrn=FALSE;
// ...

// see: hv.h
struct hv_d  HVInfo;

// ===================================

// #todo: Used during the initialization.
// called by I_init() in x64init.c
int detect_hv(void)
{
    HVInfo.initialized = FALSE;
    HVInfo.type = HV_TYPE_UNDEFINED;

    g_is_qemu = FALSE;
    g_is_kvm = FALSE;
    g_is_bhyve = FALSE;
    g_is_qnx = FALSE;
    g_is_acrn = FALSE;
    // ...

// #todo #bugbug
// This structure is for the current processor?
// oIntel onely?

    if ( (void *) processor == NULL ){
        x_panic ("detect_hv: processor struct\n");
    }

// qemu?
    if ( processor->hvName[0] == HV_STRING_QEMU_PART1 &&
         processor->hvName[1] == HV_STRING_QEMU_PART2 &&
         processor->hvName[2] == HV_STRING_QEMU_PART3 )
    {
         HVInfo.type = HV_TYPE_QEMU;
         g_is_qemu = TRUE;
         goto done;
    }

// bhyve?
    if ( processor->hvName[0] == HV_STRING_BHYVE_PART1 &&
         processor->hvName[1] == HV_STRING_BHYVE_PART2 &&
         processor->hvName[2] == HV_STRING_BHYVE_PART3 )
    {
         HVInfo.type = HV_TYPE_BHYVE;
         g_is_bhyve = TRUE;
         goto done;
    }

// qnx?
    if ( processor->hvName[0] == HV_STRING_QNX_PART1 &&
         processor->hvName[1] == HV_STRING_QNX_PART2 &&
         processor->hvName[2] == HV_STRING_QNX_PART3 )
    {
         HVInfo.type = HV_TYPE_QNX;
         g_is_qnx = TRUE;
         goto done;
    }

// acrn?
    if ( processor->hvName[0] == HV_STRING_ACRN_PART1 &&
         processor->hvName[1] == HV_STRING_ACRN_PART2 &&
         processor->hvName[2] == HV_STRING_ACRN_PART3 )
    {
         HVInfo.type = HV_TYPE_ACRN;
         g_is_acrn = TRUE;
         goto done;
    }


fail:
    HVInfo.initialized = FALSE;
    return FALSE;
done:
    HVInfo.initialized = TRUE;
    return TRUE;
}


// #todo: Used by system metrics.
int isQEMU(void)
{
    return (int) g_is_qemu;
}


/*
 * hal_probe_cpu:
 *     Detectar qual é o tipo de processador. 
 *     Salva o tipo na estrutura.
 * #todo: Estamos usando cpuid para testar os 2 tipos de arquitetura.
 * nao sei qual ha instruções diferentes para arquiteturas diferentes.
 */

int hal_probe_cpu (void)
{
    unsigned int eax=0;
    unsigned int ebx=0;
    unsigned int ecx=0;
    unsigned int edx=0;

    debug_print ("hal_probe_cpu:\n");

// Check processor structure.
    if ( (void *) processor == NULL ){
        x_panic ("hal_probe_cpu: [FAIL] processor\n");
    }

// Unknown processor type.
    processor->Type = Processor_NULL;

//
// Check vendor
//

    cpuid ( 0, eax, ebx, ecx, edx ); 

// TestIntel: Confere se é intel.
    if ( ebx == CPUID_VENDOR_INTEL_1 && 
         edx == CPUID_VENDOR_INTEL_2 && 
         ecx == CPUID_VENDOR_INTEL_3 )
    {
        processor->Type = Processor_INTEL;
        return 0;
    }

// TestAmd: Confere se é AMD.
    if ( ebx == CPUID_VENDOR_AMD_1 && 
         edx == CPUID_VENDOR_AMD_2 && 
         ecx == CPUID_VENDOR_AMD_3 )
    {
        processor->Type = Processor_AMD;
        return 0;
    }
    
// fail:
    x_panic ("hal_probe_cpu: [FAIL] Processor not supported\n");
    return (int) (-1);
}


/*
 * hal_probe_processor_type:
 *     Sonda pra ver apenas qual é a empresa do processador.
 */

// Called by init_architecture_dependent() in core/init.c

int hal_probe_processor_type (void)
{
    unsigned int eax=0;
    unsigned int ebx=0;
    unsigned int ecx=0;
    unsigned int edx=0;
    unsigned int name[32];
    int MASK_LSB_8 = 0xFF;  


    //debug.
    debug_print ("hal_probe_processor_type:\n");
    //printf("Scaning x86 CPU ...\n");


// Check processor structure.
    if ( (void *) processor == NULL ){
        x_panic ("hal_probe_processor_type: [FAIL] processor\n");
    }


// Unknown processor type.
    // processor->Type = Processor_NULL;

// vendor
// This is the same for intel and amd processors.
    cpuid( 0, eax, ebx, ecx, edx ); 
    name[0] = ebx;
    name[1] = edx;
    name[2] = ecx;
    name[3] = 0;

// Salva na estrutura.
    processor->Vendor[0] = ebx;
    processor->Vendor[1] = edx;
    processor->Vendor[2] = ecx;
    processor->Vendor[3] = 0;


// #hackhack
// #fixme
// Na verdade quando estamos rodando no qemu, é amd.
// #todo: Precisamos do nome certo usado pelo qemu.

    return Processor_AMD;


    /*
    // Confere se é Intel.
    if ( ebx == CPUID_VENDOR_INTEL_1 && 
         edx == CPUID_VENDOR_INTEL_2 && 
         ecx == CPUID_VENDOR_INTEL_3 )
    {
        return (int) Processor_INTEL; 
    }

    // Confere se é AMD
    if ( ebx == CPUID_VENDOR_AMD_1 && 
         edx == CPUID_VENDOR_AMD_2 && 
         ecx == CPUID_VENDOR_AMD_3 )
    {
        return (int) Processor_AMD; 
    }
    */

	// Continua...

    return (int) Processor_NULL;
}


// ====================================
// MSR
// Accessing 'Model Specific Registers'
// Each MSR that is accessed by the 
// RDMSR and WRMSR group of instructions 
// is identified by a 32-bit integer. 
// MSRs are 64-bit wide. 
// The presence of MSRs on your processor is indicated 
// by CPUID.01h:EDX[bit 5].
// See: cpu.h

const unsigned int CPUID_FLAG_MSR = (1 << 5);
 
int cpuHasMSR (void)
{
    unsigned int a=0;
    unsigned int b=0;
    unsigned int c=0;
    unsigned int d=0;

    cpuid(1,a,b,c,d);
    return (int) (d & CPUID_FLAG_MSR);
}


void 
cpuGetMSR ( 
    unsigned int msr, 
    unsigned int *lo, 
    unsigned int *hi )
{
    asm volatile ("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}


void 
cpuSetMSR ( 
    unsigned int msr, 
    unsigned int lo, 
    unsigned int hi )
{
    asm volatile ("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}




/* Example: Get CPU's model number */
/*
static int get_model(void);
static int get_model(void)
{
    int ebx, unused;
    cpuid(0, unused, ebx, unused, unused);
    return ebx;
}
*/


/* Example: Check for builtin local APIC. */
/*
//  CPUID_FEAT_EDX_APIC = 1 << 9,  
static int check_apic(void);
static int check_apic(void)
{
    unsigned int eax, unused, edx;
    cpuid(1, &eax, &unused, &unused, %edx);
    return edx & CPUID_FEAT_EDX_APIC;
}
*/

