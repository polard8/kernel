/*
 * File: ws/logon.h
 *
 * Descrição:
 *     Kernel Mode Logon Support Routines.
 *     Header de suporte à criação do Logon.
 *  
 * OBS:
 *     O Logon está na WindowStation0 e no Desktop0. 
 *     Existirá um processo em user mode para gerenciamento de Logon e esse 
 * processo poderá chamar rotinas de logon presentes nesse módulo.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */
 

//
// Variáveis globais.
// 
 
//flag, usar ou naõ o default user. 
int g_use_default_user; 


//
// == Prototypes ====================================
// 


//Cria.
int init_logon_manager (void);

 
//
// End.
//

