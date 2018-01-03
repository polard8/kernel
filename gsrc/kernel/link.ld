OUTPUT_FORMAT("pe-i386")   /* let the linker use its 'native' format (ELF/COFF/PE) */
ENTRY(_kernel_begin)       /* Kernel entry point. (head.s) */
SECTIONS
{ 
    
    /*Opção??: _kernel_begin	= .; */

    /* 0xc0001000 = .text = _kernel_begin =  _code_begin =  .head_x86 */
	.text 0xC0001000:      /* kernel text segment. executable code of the program */
    {
	    _code_begin = .;            
	    *(.head_x86)       /* */
	    *(.text)	
	    _code_end = .; 
		. = ALIGN(4096);
    }

    .data :                /* kernel data segment*/
    { 
		_data_begin = .;            
        *(.data)           /*contains initialized global variables which are not constants*/
		*(.rdata)          /*contains read-only data*/
		_data_end = .; 
        . = ALIGN(4096);
    }
    
    .bss :                 /* kernel bss segment, contains all the static uninitalized data */  
    { 
		_bss_begin = .; 
        *(.bss)
		*(COMMON)          /*?? Contains the un-initialized global variables (not static). ??*/
		_bss_end = .; 	
        . = ALIGN(4096);
    }
    
    /* EOF - Fim do kernel */
	_kernel_end	= .; 
}

