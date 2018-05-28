/*
 * File: x86.c
 *
 * Descrição:
 *     Suporte às portas na arquitetura x86.
 *
 *     O acesso as portas também será oferecido na forma de serviços, para
 * que processos servidores também possam configurar o hardware diretamente.
 * Logicamente algum tipo de filtro será criado, para conferir a permissão.
 *
 *  @todo: Muita função aqui deveria ter o retorno do tipo void.
 *
 */

 
#include <kernel.h>


// habilita as interrupções
int enable()
{ 
    asm("sti");

done:
    //@todo: Porque habilitar as interrupções deveria mudar o valor do registrador eax.
    //talvez deveria ser void o tipo da função.	
    return (int) 0;
};


// desabilita as interrupções
int disable()
{ 
    asm("cli"); 
	
done:
    //@todo: Porque desabilitar as interrupções deveria mudar o valor do registrador eax.
    //talvez deveria ser void o tipo da função.		
    return (int) 0;
};


int stopCpu()
{      
    __asm(" cli \n \t " 
		  " hlt ");
};


int intReturn(){ 
    __asm("iret");
};


int farReturn(){
    __asm("lret");
};


int getFlags(int variable) 
{
    __asm(" pushfl \n \t "     
          " popl %0 "         
          : "=r" (variable));
};


int setFlags(int variable)
{
    __asm("pushl %0 \n\t"   
          "popfl"           
          : : "r" (variable));
};


int kernelProcessorInPort8( int port, int data){
    asm("inb %%dx, %%al" : "=a" (data) : "d" (port));
};
    

int kernelProcessorOutPort8(int port, int data){
    __asm("outb %%al, %%dx" : : "a" (data), "d" (port));
};


int kernelProcessorInPort16(int port,int data){ 
    __asm("inw %%dx, %%ax" : "=a" (data) : "d" (port));
};


int kernelProcessorOutPort16(int port, int data){
    __asm("outw %%ax, %%dx" : : "a" (data), "d" (port));
};


int kernelProcessorInPort32(int port, int data){
    __asm("inl %%dx, %%eax" : "=a" (data) : "d" (port));
};


int kernelProcessorOutPort32(int port,int data){ 
    __asm("outl %%eax, %%dx" : : "a" (data), "d" (port));
};


int Push(int value){
    __asm("pushl %0" : : "r" (value) : "%esp");
};


int Pop(int variable){
    __asm("popl %0" : "=r" (variable) : : "%esp");
};


int pushRegs(){ 
    __asm("pushal" : : : "%esp");
};


int popRegs(){ 
    __asm("popal" : : : "%esp");
};


int pushFlags(){ 
    __asm("pushfl" : : : "%esp");
};


int popFlags(){ 
    __asm("popfl" : : : "%esp");
};


int getStackPointer(int addr){
    __asm("movl %%esp, %0" : "=r" (addr));
};


int setStackPointer(int addr){
    __asm("movl %0, %%esp" : : "r" (addr) : "%esp");
};

//
// End.
//

