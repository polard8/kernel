/*
 * File: libio.h
 * 
 * 2019 - Created by Fred Nora.
 */


// Retorna o valor.
unsigned char  libio_inport8  (unsigned int port);
unsigned short libio_inport16 (unsigned int port);
unsigned long  libio_inport32 (unsigned int port);

void libio_outport8  ( unsigned int port, unsigned char  value);
void libio_outport16 ( unsigned int port, unsigned short value);
void libio_outport32 ( unsigned int port, unsigned long  value);


