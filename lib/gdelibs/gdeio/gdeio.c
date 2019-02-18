
//# todo
//+ usar system_call para acessar o kernel
//+ criar lá no kernel as rotinas que atendem essa system call.

//retorna o valor.
unsigned char gde_inport8 (unsigned short port)
{
	//#todo
	//ainda não implementada.
    return (unsigned char) 0; 
}		
		
//retorna o valor.		
unsigned short gde_inport16 (unsigned short port)
{
	//#todo
	//ainda não implementada.	
    return (unsigned short) 0; 
}			
		
//retorna o valor.		
unsigned long gde_inport32 (unsigned short port)
{
	//#todo
	//ainda não implementada.	
    return (unsigned long) 0; 
}			
		
		
//o retorno é status.
//0=funcionou. 1=falhou;
int gde_outport8 ( unsigned short port, unsigned char value)
{
	//#todo
	//ainda não implementada.		
    return -1;
}	
		
//o retorno é status.
//0=funcionou. 1=falhou;
int gde_outport16 ( unsigned short port, unsigned short value)
{
	//#todo
	//ainda não implementada.		
    return -1;
}		
		
//o retorno é status.
//0=funcionou. 1=falhou;
int gde_outport32 ( unsigned short port, unsigned long value)
{
	//#todo
	//ainda não implementada.		
    return -1;
}	


