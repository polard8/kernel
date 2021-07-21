

#ifndef ____PINTS_H
#define ____PINTS_H


//
// File: pints.h
//

// Variáveis globais para contagem de interrupções.


//
// System interrupt
//

//See:  gramado/kernel/execve/sci/gde/gde_serv.c 
unsigned long g_profiler_ints_gde_services;


//
// Legacy hardware interrupts (irqs) (legacy pic)
//

unsigned long g_profiler_ints_irq0;  // kdrivers/timer.c
unsigned long g_profiler_ints_irq1;  // x/i8042/keyboard.c
unsigned long g_profiler_ints_irq2;  // cascade.
unsigned long g_profiler_ints_irq3;  //
unsigned long g_profiler_ints_irq4;  //
unsigned long g_profiler_ints_irq5;  //
unsigned long g_profiler_ints_irq6;  //
unsigned long g_profiler_ints_irq7;  //

unsigned long g_profiler_ints_irq8;   // kdrivers/rtc.c
unsigned long g_profiler_ints_irq9;   // kdrivers/network/nicintel.c
unsigned long g_profiler_ints_irq10;  //
unsigned long g_profiler_ints_irq11;  //
unsigned long g_profiler_ints_irq12;  // x/i8042/mouse.c
unsigned long g_profiler_ints_irq13;  //
unsigned long g_profiler_ints_irq14;  // kdrivers/kdrivers/ide/atairq.c
unsigned long g_profiler_ints_irq15;  // kdrivers/kdrivers/ide/atairq.c


// continua ...


#endif   


