/*
 * File: gdeio.h
 * 
 * 2019 - Created by Fred Nora.
 */


// Retorna o valor.
unsigned char  gde_inport8  (unsigned int port);
unsigned short gde_inport16 (unsigned int port);
unsigned long  gde_inport32 (unsigned int port);

void gde_outport8  ( unsigned int port, unsigned char  value);
void gde_outport16 ( unsigned int port, unsigned short value);
void gde_outport32 ( unsigned int port, unsigned long  value);


