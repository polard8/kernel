/*
 * File: x86.c 
 *
 * Descrição:
 *     Acesso ao hardware na arquitetura x86.
 *
 * Ambiente:
 *    Boot Loader. BL.BIN. Ring 0.
 *
 * Revision history:
 *
 *     2005 - Created by Fred Nora.
 *     2016 - Revision.
 */


#include <bootloader.h>


/*
 * enable:
 *     Habilita as interrupções. 
 * @todo: isso pode ser void.
 */ 
void enable (){
	
    asm (" sti ");
	
    //return (int) 0;
};


/*
 * disable:
 *     Desabilita as interrupções.  
 * @todo: isso pode ser void.
 */ 
void disable (){
	
    asm (" cli ");   
};


void stopCpu (){
	
    __asm ( " cli \n\t" 
	        " hlt ");		  
};


void intReturn (){
	
    __asm (" iret ");
};


void farReturn (){
	
    __asm (" lret ");
};


//#todo: Rever isso.
int getFlags(int variable) 
{
    __asm("pushfl \n\t"     
          "popl %0"         
          : "=r" (variable));
};


//#todo: Rever isso.
int setFlags(int variable)
{
    __asm("pushl %0 \n\t"   
          "popfl"           
          : : "r" (variable));
};


int BlProcessorInPort8 ( int port, int data ){
	
    asm ("inb %%dx, %%al" : "=a" (data) : "d" (port) );
};


int BlProcessorOutPort8 ( int port, int data ){
	
    __asm ("outb %%al, %%dx" : : "a" (data), "d" (port) );
};


int BlProcessorInPort16 (int port,int data){
	
    __asm ("inw %%dx, %%ax" : "=a" (data) : "d" (port) );
};


int BlProcessorOutPort16 ( int port, int data ){
	
    __asm ("outw %%ax, %%dx" :: "a" (data), "d" (port) );
};


int BlProcessorInPort32 ( int port, int data ){
	
    __asm ("inl %%dx, %%eax" : "=a" (data) : "d" (port) );
};


int BlProcessorOutPort32 ( int port,int data ){
	
    __asm ("outl %%eax, %%dx" : : "a" (data), "d" (port) );
};


int Push (int value){
	
    __asm ("pushl %0" : : "r" (value) : "%esp" );
};


int Pop (int variable){
	
    __asm ("popl %0" : "=r" (variable) : : "%esp" );
};


void pushRegs (){
	
    __asm ("pushal" : : : "%esp");
};


void popRegs (){
	
    __asm ("popal" : : : "%esp");
};


void pushFlags (){
	
    __asm ("pushfl" : : : "%esp" );
};


void popFlags (){
	
    __asm ("popfl" : : : "%esp" );
};


int getStackPointer (int addr){
	
    __asm ("movl %%esp, %0" : "=r" (addr) );
};


int setStackPointer (int addr){
	
    __asm ("movl %0, %%esp" : : "r" (addr) : "%esp" );
};  


//
//End.
//

