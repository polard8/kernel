
// debug.h

#ifndef __DEBUG_H 
#define __DEBUG_H    1

// Serial debug support.
int is_using_serial_debug(void);
void enable_serial_debug(void);
void disable_serial_debug(void);

void debug_print ( char *data );
void PROGRESS( char *string );
int debug(void);
void debug_breakpoint (void);
unsigned long 
debug_compute_checksum ( 
    unsigned char *buffer, 
    unsigned long lenght );

#endif    

