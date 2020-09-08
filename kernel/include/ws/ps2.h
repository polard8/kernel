/*
 * File: ps2.h
 *
 * Descrição:
 *     Header para gerenciamento da porta ps/2.
 *     
 * Obs: Encontramos mais informações nos headers de teclado e de mouse.
 *
 */


#ifndef ____PS2_H
#define ____PS2_H


/*
 Wikipedia
 O conector PS/2 é um conector mini-DIN de 6 pinos usado para conectar alguns 
 teclados e mouses a um sistema de computador compatível com PC. 
 Seu nome vem da série de computadores pessoais IBM Personal System/2, 
 com o qual ele foi introduzido em 1987. O conector de mouse PS/2 geralmente 
 substitui antigos conectores de "mouses seriais" DE-9 RS-232, 
 enquanto o conector de teclado PS/2 substituiu o conector DIN mais largo de 5 pinos/180º 
 usado no desenho do IBM PC/AT. Os desenhos PS/2 nas interfaces de teclados e 
 mouses são eletricamente similares e empregam o mesmo protocolo de comunicação. 
 Entretanto, a porta de teclado ou mouse de um determinado sistema pode não ser 
 intercambiável uma vez que os dois dispositivos usam um conjunto de comandos diferentes.
 
A comunicação é serial, síncrona e bidirecional.[1] 
O dispositivo conectado gera o sinal de relógio. O hospedeiro controla a comunicação usando a 
linha de relógio. Quando o hospedeiro puxa o relógio para baixo, a comunicação do dispositivo é inibida.
*/

//
// Definições.
//

#define  PS2_PORT    0x60
#define  PS2_CTRL    0x64
#define  PS2_ACK     0xFA 
//...

 


#endif  


//
// End.
//

