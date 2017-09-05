OUTPUT_FORMAT("pe-i386")    /* let the linker use its 'native' format (ELF/COFF/PE) */
ENTRY(_kernel_begin)
SECTIONS
{ 
	.text 0xC0001000:       /* kernel text segment */
    {
	    _code_begin = .;            
	    *(.head_x86)     
	    *(.text)	
	    _code_end = .; 
		. = ALIGN(4096);
    }
    .data :                /* kernel data segment */
    { 
		_data_begin = .; 
        *(.data)
		*(.rdata) /*test*/
		_data_end = .; 
        . = ALIGN(4096);
    }
    .bss :                /* kernel bss segment */  
    { 
		_bss_begin = .; 
        *(.bss)
		*(COMMON)
		_bss_end = .; 	
        . = ALIGN(4096);
    }
    /* EOF - Fim do kernel */
	_kernel_end	= .; 
}

