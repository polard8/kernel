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
 

#include <kernel.h>


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

static inline void imcr_pic_to_apic (void){

	//Select IMCR register.
    outb (0x70, 0x22);
	
	//NMI and 8259 INTR go through APIC. 
    outb (0x01, 0x23);
	
	//Nothing.
}

 
static inline void imcr_apic_to_pic (void){

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
#define IA32_APIC_BASE_MSR 0x1B
#define IA32_APIC_BASE_MSR_BSP 0x100 // Processor is a BSP
#define IA32_APIC_BASE_MSR_ENABLE 0x800
*/ 
 
/** returns a 'true' value if the CPU supports APIC
 *  and if the local APIC hasn't been disabled in MSRs
 *  note that this requires CPUID to be supported.
 */
 
/* 
bool check_apic(); 
bool check_apic() {
   uint32_t eax, edx;
   cpuid(1, &eax, &edx);
   return edx & CPUID_FEAT_EDX_APIC;
}
*/



/* Set the physical address for local APIC registers */

/*
void cpu_set_apic_base(uintptr_t apic);
void cpu_set_apic_base(uintptr_t apic) {
   uint32_t edx = 0;
   uint32_t eax = (apic & 0xfffff000) | IA32_APIC_BASE_MSR_ENABLE;
 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
   edx = (apic >> 32) & 0x0f;
#endif
 
   cpuSetMSR(IA32_APIC_BASE_MSR, eax, edx);
}
*/
 
 
 
/**
 * Get the physical address of the APIC registers page
 * make sure you map it to virtual memory ;)
 */
 
/*
uintptr_t cpu_get_apic_base();
uintptr_t cpu_get_apic_base() {
	
   uint32_t eax, edx;
   cpuGetMSR(IA32_APIC_BASE_MSR, &eax, &edx);
 
#ifdef __PHYSICAL_MEMORY_EXTENSION__
   return (eax & 0xfffff000) | ((edx & 0x0f) << 32);
#else
   return (eax & 0xfffff000);
#endif
}
*/
 
 
/* 
void enable_apic(); 
void enable_apic (){

    //Hardware enable the Local APIC if it wasn't enabled.
    cpu_set_apic_base(cpu_get_apic_base());
 
    //Set the Spurious Interrupt Vector Register bit 8 to start receiving interrupts.
    write_reg(0xF0, ReadRegister(0xF0) | 0x100);
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
int init_apic();
int init_apic()
{
    
 
done:
    g_driver_apic_initialized = 0;
    return (int) 0;
};
*/



/*
 * Constructor.
int apicApic()
{};
*/



/*
int apicInit()
{};
*/



//
// End.
//
