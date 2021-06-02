/*
 * File: cpux86.c 
 * 
 * Descrição:
 *
 * Atribuições:
 *  + Pegar os parametros da cpu.
 *  + Inicializar a cpu presente.
 *  + ...
 *
 * In this file:
 *  + cpu_get_parameters
 */


/*
 * todo: 
 * cria a função init_cpu.
 */


#include <kernel.h>


int detect_IsQEMU(void)
{

    if ( (void *) processor == NULL ){
        panic ("detect_IsQEMU: FAIL\n");
    }

    if ( processor->hvName[0] == CPUID_HV_QEMU_1 &&
         processor->hvName[1] == CPUID_HV_QEMU_2 &&
         processor->hvName[2] == CPUID_HV_QEMU_3 )
    {
         g_is_qemu = TRUE;
         return TRUE;
    }

    g_is_qemu = FALSE;

    return FALSE;
}



/*
 * cpu_get_parameters:
 *   Sonda a CPU pra saber seus parâmetros. (OEM)
 *   ??header 
 */ 

	// @todo: Mudar nome para KeProbeCPU(

int cpu_get_parameters (void)
{

    // #bugbug: 
    // O prefixo Ke está errada nessa situação.

    return (int) KeTestCPU (); 
}
 


/*
 **************************************
 * KeTestCPU:
 *     Pega os parametros do CPU.
 * 
 * (bugbug) Problemas ao utilizar a estrutura 
 *          para registrar as informações.
 * 
 * @todo: 
 *     Mudar para scanCPUx86()
 *     Get info.
 *     ??header
 */

int KeTestCPU (void)
{

    int i=0;

    debug_print("KeTestCPU: \n");
    
    
    // Initializing the CPUs support. (#MP)
    // Maybe it's not the better place for that.
    // See: cpu.h
    
    // UP
    // We have at least one.
    processors_count = 1;
    
    // Clenning th list.
    for (i=0; i<PROCESSORS_MAX_COUNT; i++){
        processorsList[i] = 0;
    };

   
    // If we are in a UP system, so we're gonna use
    // the structure UPProcessorBlock.
    // This structure was initialized in another place I guess.
    
    // ...

    // See: x86.c
    
    get_cpu_intel_parameters();
 
    return 0;
}


/*
 **********************************************************
 * hal_probe_cpu:
 *     Detectar qual é o tipo de processador. 
 *     Salva o tipo na estrutura.
 *
 * @todo: Estamos usando cpuid para testar os 2 tipos de arquitetura.
 * nao sei qual ha instruções diferentes para arquiteturas diferentes.
 */

int hal_probe_cpu (void)
{
    unsigned long eax=0;
    unsigned long ebx=0;
    unsigned long ecx=0;
    unsigned long edx=0;


    debug_print ("hal_probe_cpu:\n");

#ifdef HAL_VERBOSE
    printf ("hal_probe_cpu:\n");
#endif

    // Check processor structure.
    if ( (void *) processor == NULL ){
        panic ("hal_probe_cpu: [FAIL] processor\n");
    }


    // Check vendor.
    cpuid ( 0, eax, ebx, ecx, edx ); 

    //=======================
    // Confere se é intel.
    // TestIntel:

    if ( ebx == CPUID_VENDOR_INTEL_1 && 
         edx == CPUID_VENDOR_INTEL_2 && 
         ecx == CPUID_VENDOR_INTEL_3 )
    {
        processor->Type = Processor_INTEL;
        return 0;
    }

    //=======================
    // Confere se é Amd.
    // TestAmd:

    if ( ebx == CPUID_VENDOR_AMD_1 && 
         edx == CPUID_VENDOR_AMD_2 && 
         ecx == CPUID_VENDOR_AMD_3 )
    {
        processor->Type = Processor_AMD;
        return 0;
    }

    // Desconhecido.
    // todo: Aqui é um erro fatal.
    // Fail:

    processor->Type = Processor_NULL;

    panic ("hal_probe_cpu: [FAIL] Processor not supported\n");

    //return (int) (-1);
}


/*
 ********************************************************
 * hal_probe_processor_type:
 *     Sonda pra ver apenas qual é a empresa do processador.
 */

// Called by init_architecture_dependent() in core/init.c

int hal_probe_processor_type (void){

    unsigned long eax=0;
    unsigned long ebx=0;
    unsigned long ecx=0;
    unsigned long edx=0;

    unsigned long name[32];

    int MASK_LSB_8 = 0xFF;  


    //debug.
    debug_print ("hal_probe_processor_type:\n");
    //printf("Scaning x86 CPU ...\n");

    // vendor
    // This is the same for intel and amd processors.
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

	// Continua...

    return (int) Processor_NULL;
}




// MSR
// Accessing Model Specific Registers 
//Each MSR that is accessed by the RDMSR and WRMSR group of instructions 
//is identified by a 32-bit integer. MSRs are 64-bit wide. 
//The presence of MSRs on your processor is 
//indicated by CPUID.01h:EDX[bit 5].


const unsigned long CPUID_FLAG_MSR = (1 << 5);
 
int cpuHasMSR (void)
{
    unsigned long a=0;
    unsigned long b=0;
    unsigned long c=0;
    unsigned long d=0;

    cpuid(1, a, b, c, d);
    return (int) (d & CPUID_FLAG_MSR);
}


void 
cpuGetMSR ( 
    unsigned long msr, 
    unsigned long *lo, 
    unsigned long *hi )
{
    asm volatile ("rdmsr" : "=a"(*lo), "=d"(*hi) : "c"(msr));
}


void 
cpuSetMSR ( 
    unsigned long msr, 
    unsigned long lo, 
    unsigned long hi )
{
    asm volatile ("wrmsr" : : "a"(lo), "d"(hi), "c"(msr));
}



void show_cpu_info(void)
{
    //#todo
    //Ver a flag que indica qual processado encontramos.

    // #bugbug
    // Essa mesma função é usada pra
    // mostrar as informações do cpu AMD.

    //See: x86info.c
    //if intel
    show_cpu_intel_parameters();
}





// pega alguma informação da estrutura processor_d
unsigned long get_processor_feature(int i)
{
    int Index = 0;
    
    Index = i;


    if( (void*) processor == NULL ){
        panic("get_processor_feature: [FAIL] processor\n");
    }else{
        if( processor->used != TRUE || processor->magic != 1234 )
        {
            panic("get_processor_feature: [FAIL] validation\n");
        }

        switch (Index){

            //max feature id.
            case 1:
                return (unsigned long) processor->MaxFeatureId;
                break;
        
            //l2 line size
            case 2:
                return (unsigned long) processor->L2LineSize;
                break;        
        
            //ls associativity
            case 3:
                return (unsigned long) processor->L2Associativity;
                break;
                
            //l2 cache size
            case 4:
                return (unsigned long) processor->L2Cachesize;
                break;
                
            //physical address size
            case 5:
                return (unsigned long) processor->Physical_Address_Size;
                break;

            //virtual address size
            case 6:
                return (unsigned long) processor->Virtual_Address_Size;
                break;
                
            case 7:
                return (unsigned long) 0;
                break;
                
            //case 8:
                //return (unsigned long) 0;
                //break;
            
            //...
            
            default:
                debug_print("get_processor_feature: default\n");
                break;        
        };
        
    };
    
    return 0;
}


//
// End.
//

