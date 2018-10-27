/**********************************************************************

  File: gramado.h

  History:
  2018 - Created by Fred Nora.

  Copyright (C) 2005-2018 Fred Nora

**********************************************************************/

#ifndef GRAMADO_H
#define GRAMADO_H 1

//
// Set up what kind of debug message we wanna see.
//

//Esse é usado para exibir somente os marcadores pprincipais,
//que são mesnagens escritas em maiúculas.
//fnciona como uma visão panorâmica, usa espinha dorsal, um esqueleto.
//#define KERNEL_VERBOSE 1

//Esse é usado para trabalhar a rotina de entrypoint da arquitetura alvo.
//#define ENTRY_VERBOSE 1


//Esses quatro são as camadas principais.
//#define HAL_VERBOSE 1
//#define MK_VERBOSE 1
//#define EXECVE_VERBOSE 1
//#define GWS_VERBOSE 1


//
// ## breack points ##
// Set up what what is the breakpoint.
//

//Seriam inicializações parciais programadas. 
 
//#define BREAKPOINT_TARGET_AFTER_ENTRY 1
//#define BREAKPOINT_TARGET_AFTER_VIDEO 1
//#define BREAKPOINT_TARGET_AFTER_SYSTEM 1
//#define BREAKPOINT_TARGET_AFTER_RUNTIME 1
//#define BREAKPOINT_TARGET_AFTER_INIT 1
//#define BREAKPOINT_TARGET_AFTER_LOGON 1
//#define BREAKPOINT_TARGET_AFTER_LOGOFF 1
//#define BREAKPOINT_TARGET_AFTER_HAL 1
//#define BREAKPOINT_TARGET_AFTER_MK 1

//
// ## targets ##
//

//Também pretendo fazer a inicialização mudar de direção dependendo do alvo programado.

//Isso inicializa os três aplicativos do gramado core.
//#define TARGET_GRAMADOCORE_APPS 1

//Isso inicializa apenas o app init do gramado core.
//#define TARGET_GRAMADOCORE_INIT 1

// CONTINUA
//...


// ## Kernel version. ##
#define KERNEL_VERSION "0.4"
#define KERNEL_VERSION_NAME "Love and Forgiveness"

#endif

