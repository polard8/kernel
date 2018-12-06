OUTPUT_FORMAT("pe-i386")
ENTRY(fmain)
SECTIONS
{ 
	
	.text 0x1000: 
    {
        code = .; 
		_code = .; 
		__code = .;
           
	  *(.head_x86)    
	  *(.text)	 
	  
       . = ALIGN(4096);
    }

    .data :
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