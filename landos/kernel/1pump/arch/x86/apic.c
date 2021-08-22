/*
 * File: apic.c
 *
 *    Controlador APIC.
 *    Arquivo principal do módulo interno do kernel de 32bit. 
 *
 *    APIC - Advanced Programmable Interrupt Controller.
 *
 *   Stuffs:
 *       +Discrete APIC.
 *       +Integrated local APICs.
 *       +APIC timer.
 *       +I/O APICs.
 *
 * Versão 1.0, 2015.
 */


// See:
// hwi/dd/nhid/arch/x86/apic.c



#include <kernel.h>



/* Flush caches */
/*
void flush_cashes(void)
{
	__asm__("wbinvd");
}
*/


//@todo: definir porta 70h usada nesse arquivo.




//
// Variáveis internas.
//

//int apicStatus;
//int apicError;
//...



/*
 * imcr_pic_to_apic:
 *
 * Handle interrupt mode configuration register (IMCR).
 *
 * This register controls whether the interrupt signals that reach 
 * the BSP come from the master PIC or from the local APIC. 
 *
 * Before entering Symmetric I/O Mode, either the BIOS or 
 * the operating system must switch out of PIC Mode by changing the IMCR.
 *
 */

static inline void imcr_pic_to_apic (void)
{

	//Select IMCR register.
    outb (0x70, 0x22);
	
	//NMI and 8259 INTR go through APIC. 
    outb (0x01, 0x23);
	
	//Nothing.
}

 
static inline void imcr_apic_to_pic (void)
{

	//Select IMCR register.
    outb (0x70, 0x22);
     
	//NMI and 8259 INTR go directly to BSP.
    outb (0x00, 0x23);
	
	//Nothing.
}




//
// begin ======================================================
//

// #todo
// Testando um código encontrado em https://wiki.osdev.org/APIC.
// setting up the APIC: 


 
 
/* 
 * check_apic:
 *     returns a 'true' value if the CPU supports APIC
 *  and if the local APIC hasn't been disabled in MSRs
 *  note that this requires CPUID to be supported.
 */

int check_apic (void)
{
   unsigned long eax=0; 
   unsigned long ebx=0; 
   unsigned long ecx=0;
   unsigned long edx=0;


   cpuid (1, eax, ebx, ecx, edx );
   
   return (int) (edx & CPUID_FEAT_EDX_APIC);
}




/* Set the physical address for local APIC registers */
// ??
// Is it possible to change the base?
// But we have a default adddress, it is 0xFEE00000.

void cpu_set_apic_base(unsigned long apic) 
{
   unsigned long edx = 0;
   unsigned long eax = (apic & 0xfffff000) | IA32_APIC_BASE_MSR_ENABLE;
 
//#ifdef __PHYSICAL_MEMORY_EXTENSION__
//   edx = (apic >> 32) & 0x0f;
//#endif
 
   cpuSetMSR (IA32_APIC_BASE_MSR, eax, edx);
}

 
 
 
 
/**
 * Get the physical address of the APIC registers page
 * make sure you map it to virtual memory ;)
 */
unsigned long cpu_get_apic_base (void) 
{
   
   unsigned long eax=0; 
   unsigned long edx=0;


   cpuGetMSR (IA32_APIC_BASE_MSR, &eax, &edx);
 
/* 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
   return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
#else
   return (eax & 0xfffff000);
#endif
*/

    return (eax & 0xfffff000);
}

 
 
// #todo: 
/* 
void enable_apic(void); 
void enable_apic (void){

    //Hardware enable the Local APIC if it wasn't enabled.
    cpu_set_apic_base ( cpu_get_apic_base() );
 
    // ??
    //Set the Spurious Interrupt Vector Register bit 8 to start receiving interrupts.
    write_reg (0xF0, ReadRegister(0xF0) | 0x100);
}
*/


//
// IO APIC Configuration 
//


/*
uint32_t cpuReadIoApic(void *ioapicaddr, uint32_t reg);
uint32_t cpuReadIoApic(void *ioapicaddr, uint32_t reg)
{
   uint32_t volatile *ioapic = (uint32_t volatile *)ioapicaddr;
   ioapic[0] = (reg & 0xff);
   return ioapic[4];
}
*/
 
/* 
void cpuWriteIoApic(void *ioapicaddr, uint32_t reg, uint32_t value); 
void cpuWriteIoApic(void *ioapicaddr, uint32_t reg, uint32_t value)
{
   uint32_t volatile *ioapic = (uint32_t volatile *)ioapicaddr;
   ioapic[0] = (reg & 0xff);
   ioapic[4] = value;
}
*/


/*
 # SIPI Sequence 
 
void APIC::wakeupSequence(U32 apicId, U8 pvect);
void APIC::wakeupSequence(U32 apicId, U8 pvect)
{
                ICRHigh hreg = {
				.destField = apicId
		};
 
		ICRLow lreg(DeliveryMode::INIT, Level::Deassert, TriggerMode::Edge);
 
		xAPICDriver::write(APIC_REGISTER_ICR_HIGH, hreg.value);
		xAPICDriver::write(APIC_REGISTER_ICR_LOW, lreg.value);
 
		lreg.vectorNo = pvect;
		lreg.delvMode = DeliveryMode::StartUp;
 
		Dbg("APBoot: Wakeup sequence following...");
 
		xAPICDriver::write(APIC_REGISTER_ICR_HIGH, hreg.value);
		xAPICDriver::write(APIC_REGISTER_ICR_LOW, lreg.value);
}
*/ 
 
// NOTE: ICRLow and ICRHigh are types in the Silcos kernel. If your code uses direct bit
// manipulations you must replace some code with bit operations.


//
// end ======================================================
//





/*
uint32_t apic_read(void* apic_base, uint32_t register);
uint32_t apic_read(void* apic_base, uint32_t register) 
{
    return *((volatile uint32_t*)(apic_base + register));
}
*/


/*
void apic_write(void* apic_base, uint32_t register, uint32_t data);
void apic_write(void* apic_base, uint32_t register, uint32_t data) 
{
    *((volatile uint32_t*)(apic_base + register)) = data;
}
*/




//
// End.
//
