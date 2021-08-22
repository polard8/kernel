/*
 * File: debug.h
 *
 *     Header do debug interno do kernel.
 */


int debug (void);
int debug_check_inicialization (void);
int debug_check_drivers (void);
void debug_breakpoint (void);

//retorna um checksum dado um buffer e um tamanho.
unsigned long 
debug_compute_checksum( 
    unsigned char *Buffer, 
    unsigned long Lenght );

// Escreve na porta serial.
void debug_print ( char *data );

void PROGRESS( char *string );

//
// End.
//

