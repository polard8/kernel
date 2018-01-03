/*
 * File: ports.c 
 *
 * Descrição:
 *     Permite ao Boot Loader acessar as portas.
 */


#include <bootloader.h>


/*
 * bloutportb: 
 *     Escreve um byte em uma determina porta.
 */
inline void bloutportb(unsigned int port,unsigned int value)
{
    asm volatile(" outb %%al, %%dx " : :"d" (port), "a" (value) );
};

int outb(int port, int data) 
{
    asm(" outb %%al, %%dx " : : "a" (data), "d" (port) );
};

inline unsigned char inportb(int port)
{
    unsigned char ret; 
    asm(" inb %%dx, %%al " : "=a"(ret): "d"(port) );
	return ret;
};

int outportb(int port, int data) 
{
    asm(" outb %%al, %%dx " : : "a" (data), "d" (port) );
};

int inport8(int port, int data) 
{
    __asm("inb %%dx, %%al" : "=a" (data) : "d" (port));
};

int outport8(int port, int data) 
{
    __asm("outb %%al, %%dx"  : : "a" (data), "d" (port));
};

int inport16(int port,int data)
{ 
    __asm("inw %%dx, %%ax" : "=a" (data) : "d" (port));
};

int outport16(int port, int data) 
{
    __asm("outw %%ax, %%dx"  : : "a" (data), "d" (port));
};

int inport32(int port, int data) 
{
    __asm("inl %%dx, %%eax"  : "=a" (data) : "d" (port));
};

int outport32(int port,int data)
{ 
    __asm("outl %%eax, %%dx"  : : "a" (data), "d" (port));
};

/*
 * inb:
 *    Pega byte na porta. É usada na sincronização do monitor.
 */
char inb(int port)
{
    char value = 0;
	
    value = inportb(port);
	
	asm(" nop \n");
	asm(" nop \n");
	asm(" nop \n");
	asm(" nop \n");
	return value;
};

/*
 * inportl:
 *     Lê um dword de uma determina porta.
 */
inline unsigned long inportl(unsigned long port)
{
	unsigned long Ret;
	asm volatile ("inl %%dx,%%eax" : "=a" (Ret) : "d"(port));
	return Ret;
};

/*
 * outportl:
 *     Escreve um dword em uma determinada porta.
 */
inline void outportl(unsigned long port, unsigned long value)
{
	asm volatile ("outl %%eax,%%dx" :: "d" (port), "a" (value));
};

//
//End.
//

