/*
 * File: link.ld
 *    This file is used by ld.
 *    It's a common file for all the commands in this folder.
 *    
 *    2019 - Created by Fred Nora.
 */



OUTPUT_FORMAT("elf32-i386")
ENTRY(main)
SECTIONS
{ 

    /* The entry point. It's not the base of the image. */	
	.text 0x00401000: 
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