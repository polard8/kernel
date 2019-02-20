// gdeio.c 
// acesso a portas para processos em user mdoe.
// será usado pelos servidores e drivers.
// o privilégio será baseado em 'usuário' e 'desktop'.


void *gdeio_system_call ( unsigned long ax, 
                          unsigned long bx, 
				          unsigned long cx, 
				          unsigned long dx );
	

//# todo
//+ usar system_call para acessar o kernel
//+ criar lá no kernel as rotinas que atendem essa system call.

//retorna o valor.
unsigned char gde_inport8 (unsigned short port)
{
	
	gde_system_call ( 126, (unsigned long) 8, (unsigned long) port, (unsigned long) port );	
	
	//#todo
	//ainda não implementada.
    return (unsigned char) 0; 
}		
		
//retorna o valor.		
unsigned short gde_inport16 (unsigned short port)
{
	gde_system_call ( 126, (unsigned long) 16, (unsigned long) port, (unsigned long) port );	
	
	//#todo
	//ainda não implementada.	
    return (unsigned short) 0; 
}			
		
//retorna o valor.		
unsigned long gde_inport32 (unsigned short port)
{
	gde_system_call ( 126, (unsigned long) 32, (unsigned long) port, (unsigned long) port );	
	
	//#todo
	//ainda não implementada.	
    return (unsigned long) 0; 
}			
		
		

void gde_outport8 ( unsigned short port, unsigned char value)
{
	gde_system_call ( 127, (unsigned long) 8, (unsigned long) port, (unsigned long) value );	
}	
		

void gde_outport16 ( unsigned short port, unsigned short value)
{
	gde_system_call ( 127, (unsigned long) 16, (unsigned long) port, (unsigned long) value );	
}		
		

void gde_outport32 ( unsigned short port, unsigned long value)
{
	gde_system_call ( 127, (unsigned long) 32, (unsigned long) port, (unsigned long) value );	
}	


void *gdeio_system_call ( unsigned long ax, 
                          unsigned long bx, 
				          unsigned long cx, 
				          unsigned long dx )
{
    int Ret = 0;	
	
    //System interrupt.
 	
	asm volatile ( " int %1 \n"
		           : "=a"(Ret)	
		           : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

	return (void *) Ret; 
};