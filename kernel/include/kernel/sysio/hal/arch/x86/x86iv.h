/*
 * File: x86iv.h
 *
 *     x86 interrupt vectors
 *
 * 2018 - Created by Fred Nora.
 */



//Linux vectors 
// *  Vectors   0 ...  31 : system traps and exceptions - hardcoded events
// *  Vectors  32 ... 127 : device interrupts
// *  Vector  128         : legacy int80 syscall interface
// *  Vectors 129 ... INVALIDATE_TLB_VECTOR_START-1 except 204 : device interrupts
// *  Vectors INVALIDATE_TLB_VECTOR_START ... 255 : special interrupts
 

//linux 
//0–19 (0x0-0x13) Nonmaskable interrupts and exceptions
//20–31 (0x14-0x1f) Intel-reserved
//32–127 (0x20-0x7f)  External interrupts (IRQs)
//128 (0x80)Programmed exception for system calls 
//129–238 (0x81-0xee) External interrupts (IRQs)
 
// 0-18 ?? Nonmaskable interrupts and exceptions 
// 0-19 ???
//19-31 reservado pela intel. 
 


// system call
// Gramado, Linux and many others. 
#define IA32_SYSCALL_VECTOR  0x80 

// #todo  
// number of vectors?? 
//#define NR_VECTORS  256


// #todo
// 2 - non maskable interrupt.
#define NMI_VECTOR  0x02



// #todo
// fazer a número 3. int 3.
// O handler vai mostrar o contexto.


//18 - machine check.
//https://en.wikipedia.org/wiki/Machine-check_exception
#define MCE_VECTOR  0x12


//32 - onde começam as IRQs
#define FIRST_EXTERNAL_VECTOR  0x20


// #todo
// podemos criar funções expeciais 
// como reboot e shutdown 
// essas funções especiais poderiam começar em 0xF0
// 0xF0-0xFF
// reboot 
// shutdown 
// ...



//
// End.
//


