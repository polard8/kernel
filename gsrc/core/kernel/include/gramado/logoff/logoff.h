/*
 * File: gramado\logoff\logoff.h
 *
 * Descrição:
 *     Kernel Mode Logoff Support Routines.
 *     Header de suporte ao logoff.
 *
 * OBS:
 *     O Logoff deve seu próprio desktop. 
 *     As rotinas de Logoff podem estar em um processo em User Mode. Ou em um 
 * módulo externo em kernel mode e poderão chamar as rotinas presentes nesse
 * módulo. 
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - revision.
 *     ...
 */
 
 
int init_logoff(int argc, char *argv[]);
int StartLogoff(int argc, char *argv[]);


//
// End.
//

