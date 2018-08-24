/*
 * File: x86.c 
 *
 * Descrição:
 *     Acesso ao hardware na arquitetura x86.
 *
 * Ambiente:
 *    Boot Loader. RING0.
 *
 * Revison history:
 *     2005, Created.
 *     2016, Adaptação para o boot loader dos nomes das funções.
 */


#include <bootloader.h>


/*
 * enable:
 *     Habilita as interrupções. @todo: isso pode ser void.
 */ 
int enable()
{ 
    asm(" sti ");	
    return (int) 0;
};

/*
 * disable:
 *     Desabilita as interrupções.  @todo: isso pode ser void.
 */ 
int disable()
{ 
    asm(" cli ");   
	return (int) 0;
};

int stopCpu()
{      
    __asm(" cli \n\t" 
	      " hlt ");		  
};

int intReturn()
{ 
    __asm(" iret ");
};

int farReturn()
{
    __asm(" lret ");
};

int getFlags(int variable) 
{
    __asm("pushfl \n\t"     
          "popl %0"         
          : "=r" (variable));
};

int setFlags(int variable)
{
    __asm("pushl %0 \n\t"   
          "popfl"           
          : : "r" (variable));
};

int BlProcessorInPort8( int port, int data)
{
    asm("inb %%dx, %%al" : "=a" (data) : "d" (port));
};
        
int BlProcessorOutPort8(int port, int data) 
{
    __asm("outb %%al, %%dx" : : "a" (data), "d" (port));
};

int BlProcessorInPort16(int port,int data)
{ 
    __asm("inw %%dx, %%ax" : "=a" (data) : "d" (port));
};

int BlProcessorOutPort16(int port, int data) 
{
    __asm("outw %%ax, %%dx"  : : "a" (data), "d" (port));
};

int BlProcessorInPort32(int port, int data) 
{
    __asm("inl %%dx, %%eax" : "=a" (data) : "d" (port));
};

int BlProcessorOutPort32(int port,int data)
{ 
    __asm("outl %%eax, %%dx" : : "a" (data), "d" (port));
};

int Push(int value)
{
    __asm("pushl %0" : : "r" (value) : "%esp");
};

int Pop(int variable)
{
    __asm("popl %0" : "=r" (variable) : : "%esp");
};

int pushRegs()
{ 
    __asm("pushal" : : : "%esp");
};

int popRegs()
{ 
    __asm("popal" : : : "%esp");
};

int pushFlags()
{ 
    __asm("pushfl" : : : "%esp");
};

int popFlags()
{ 
    __asm("popfl" : : : "%esp");
};

int getStackPointer(int addr) 
{
    __asm("movl %%esp, %0" : "=r" (addr));
};

int setStackPointer(int addr) 
{
    __asm("movl %0, %%esp" : : "r" (addr) : "%esp");
};  


//
//End.
//


