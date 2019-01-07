/*
 * Arquivo: debug.h
 *
 * Descrição:
 *     Header do debug interno do kernel.
 */

  
int debug();
int debug_check_inicialization();
int debug_check_drivers();

//retorna um checksum dado um buffer e um tamanho.
unsigned long debug_compute_checksum( unsigned char *Buffer, unsigned long Lenght);

//escreve na porta seria.
void debug_print ( char *data );

//
//fim.
//

