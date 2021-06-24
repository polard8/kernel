// debug.h

#ifndef __DEBUG_H 
#define __DEBUG_H    1

unsigned long 
debug_compute_checksum ( 
    unsigned char *buffer, 
    unsigned long lenght );

void debug_print ( char *data );
void PROGRESS( char *string );

int debug_check_inicialization (void);
int debug_check_drivers (void);
int debug (void);

void debug_breakpoint (void);

#endif    

