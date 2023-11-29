
// mi.h
// Maskable interrupts
// see:
// sci.c
// ...

#ifndef __X86_64__X64MI_H
#define __X86_64__X64MI_H    1

void *mi80h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );

void *mi81h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );

void *mi82h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );

void *mi83h ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );

#endif   


