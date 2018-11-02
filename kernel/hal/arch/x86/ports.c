/*
 * File: ports.c
 *
 * Descrição:
 *     Interface de abstração para acesso as portas.
 *     A idéia é que um módulo do kernel base possa acessar as portas sem se 
 * preocupar com o tipo de arquitetura. Mas por enquanto estamos apenas 
 * suportando a arquitetura intel.
 *
 *     O acesso as portas também será oferecido na forma de serviços, para
 * que processos servidores também possam configurar o hardware diretamente.
 * Logicamente algum tipo de filtro será criado, para conferir a permissão.
 *
 *     @todo: As rotinas aqui, desviarão a chamada para para a rotina da 
 * arquitetura atual.
 *
 *    Obs: O HAL deve chamar essas rotinas e não os programas.
 *
 *    Obs: Por enquanto a unica arquitetura suportada aqui
 *         é a arquitetura PC x86.
 *
 *   header em /hal/arch/x86/ports.h
 *
 * Versão 1.0, 2015, 2016.
 */



#include <kernel.h>




//inport byte
inline unsigned char kinportb (int port){
	
    unsigned char ret;
 
    asm ("inb %%dx, %%al" : "=a"(ret): "d"(port) );
	
	return (unsigned char) ret;
};


/*
 * koutportb:
 * Escreve um byte em uma determina porta.
 */
inline void koutportb ( unsigned int port, unsigned int value ){
    
	asm volatile ("outb %%al, %%dx" :: "d" (port), "a" (value) );
};


//inport byte.
inline unsigned char inb (int port){
	
    unsigned char ret;
 
    asm ("inb %%dx, %%al" : "=a"(ret): "d"(port) );
	
	return (unsigned char) ret;
};


//outpot byte
void outb ( int port, int data ){
    
	asm ("outb %%al, %%dx" :: "a" (data), "d" (port) );
};


inline unsigned char inportb (int port){
	
    unsigned char ret;
 
    asm ("inb %%dx, %%al" : "=a"(ret): "d"(port) );
	
	return (unsigned char) ret;
};


void outportb ( int port, int data ){
	
    asm ("outb %%al, %%dx" :: "a" (data), "d" (port) );
};


int inport8 (int port){
	
	unsigned char ret;
	
    __asm ("inb %%dx, %%al" : "=a" (ret) : "d" (port) );
	
	return (unsigned char) ret;
};


void outport8 (int port, int data){
    
	__asm ("outb %%al, %%dx" :: "a" (data), "d" (port) );
};


int inport16 (int port){
	
    unsigned short ret;
	
    __asm ("inw %%dx, %%ax" : "=a" (ret) : "d" (port) );
	
	return (unsigned short) ret;
};


void outport16 (int port, int data){
    
	__asm ("outw %%ax, %%dx" :: "a" (data), "d" (port) );
};


int inport32 (int port){
	
	unsigned long ret;
    
	__asm("inl %%dx, %%eax" : "=a" (ret) : "d" (port) );
	
	return (unsigned long) ret;
};


void outport32 ( int port, int data ){ 

    __asm ("outl %%eax, %%dx" :: "a" (data), "d" (port) );
};


/*
 * inportl:
 *     Lê um dword de uma determina porta.
 */
inline unsigned long inportl (unsigned long port){
	
	unsigned long ret;

	asm volatile ("inl %%dx,%%eax" : "=a" (ret) : "d"(port) );
	
	return ret;
};


/*
 * outportl:
 *     Escreve um dword em uma determinada porta.
 */
inline void outportl ( unsigned long port, unsigned long value ){
	
	asm volatile ("outl %%eax,%%dx" :: "d" (port), "a" (value) );
};



// Input.
// Input a value from the keyboard controller's data port, after checking
// to make sure that there's some data there for us.
static unsigned char inPort60 (void){
	
    unsigned char data = 0;

    while (!(data & 0x01))
        kernelProcessorInPort8(0x64, data);

    kernelProcessorInPort8(0x60, data);
	
    return (data);
};


// Output.
// Output a value to the keyboard controller's data port, after checking
// to make sure it's ready for the data.
static void outPort60 (unsigned char value){
	
    unsigned char data;
  
    // Wait for the controller to be ready
    data = 0x02;
    while (data & 0x02)
        kernelProcessorInPort8(0x64, data);
  
    data = value;
    kernelProcessorOutPort8(0x60, data);
 
    return;
};


// Output.
// Output a value to the keyboard controller's command port, after checking
// to make sure it's ready for the command
static void outPort64 (unsigned char value){
	
    unsigned char data;
  
    // Wait for the controller to be ready
    data = 0x02;
	
    while (data & 0x02)
        kernelProcessorInPort8(0x64, data);

    data = value;
    kernelProcessorOutPort8(0x64, data);
	
	return;
};


inline void wait_ns(int count)
{
	count /=100;	 
	while(--count)io_delay();

}



//
//  End.
//

