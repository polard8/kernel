/*
 * Arquivo: logoff.h
 *
 * Descrição:
 *     Header de suporte ao logoff.
 *
 *     OBS:
 *     O Logoff deve seu próprio desktop. 
 *     As rotinas de Logoff podem estar em um processo em User Mode.
 *     Ou em um módulo externo em kernel mode.     
 *
 * Versão 1.0, 2015, 2016.
 */
 
int init_logoff(int argc, char *argv[]);
int StartLogoff(int argc, char *argv[]);


//
//fim.
//

