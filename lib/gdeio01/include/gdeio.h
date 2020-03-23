/*
 * File: gdeio.h
 * 
 * 2019 - Created by Fred Nora.
 */


//retorna o valor.
unsigned char gde_inport8 (unsigned short port);
unsigned short gde_inport16 (unsigned short port);
unsigned long gde_inport32 (unsigned short port);

void gde_outport8 ( unsigned short port, unsigned char value);
void gde_outport16 ( unsigned short port, unsigned short value);
void gde_outport32 ( unsigned short port, unsigned long value);


