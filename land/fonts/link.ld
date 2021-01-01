OUTPUT_FORMAT("elf32-i386")
ENTRY(fmain)
SECTIONS
{ 
	.text 0x200: 
    {
        code = .; 
		_code = .; 
		__code = .;
           
	  *(.head_x86)    
	  *(.text)	 
	  
       . = ALIGN(4096);
    }

    /* importante - esse eh o entry point para ler os caracteres */
	
    .data 0x2000:
    {
        data = .; 
		_data = .; 
		__data = .;
		
        *(.data)
		
        . = ALIGN(4096);
    }

    .bss :
    {
        bss = .; 
		_bss = .; 
		__bss = .;
		
        *(.bss)
		
        . = ALIGN(4096);
    }

    end = .; 
	_end = .; 
	__end = .;
}