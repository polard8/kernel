


void *gramado_system_call ( unsigned long ax, 
                            unsigned long bx, 
				            unsigned long cx, 
				            unsigned long dx );



void crt0()
{
	unsigned long ch = 'g';
	
    //gramado_system_call ( 7, 8* 4,  8* 4, (unsigned long) 66 );
	gramado_system_call ( 65, (unsigned long) ch, (unsigned long) ch, 
		(unsigned long) ch );
	while(1){}
}


void *gramado_system_call ( unsigned long ax, 
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
}



