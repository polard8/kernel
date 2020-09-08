/**********************************************************************

  File: gramado.h

        Product configuration.
 
  History:
  2018 - Created by Fred Nora.

  Copyright (C) 2005-2018 Fred Nora

**********************************************************************/



#ifndef ____GRAMADO_H
#define ____GRAMADO_H 1


//
// utsname
// 

/* Operating system name (e.g., "Linux") */
#define OS_NAME      "Gramado"

/* Name within "some implementation-defined network" */
#define NODE_NAME    "GRAMADO"

/* Operating system release (e.g., "2.6.28") */
#define RELEASE_NAME "1.0"

/* Operating system version */
#define VERSION_NAME "1.0"

 /* Hardware identifier */
#define MACHINE_NAME "gigabyte-intel"




//
// #### Name ####
//


#define OS_LONGNAME "Animal Operating System"


//
// #### Version ####
//


//Kernel version
//Esse é padrão de versão. 
//Não mudar, apenas fazer as atualizações.

//#bugbug. 
//Isso na verdade deve ser feito no makefile.
//mas o makefiles faz isso de um jeito que
//utiliza recursos que o gramado ainda nao tem
//quando formos compilar ele com o pr'oprio compilador.



#define SYSTEM_VERSION_MAJOR 0 
#define SYSTEM_VERSION_MINOR 0
#define SYSTEM_VERSION_REVISION 0   

//Kernel version strings.
#define SYSTEM_VERSION_STRING "0.0"
#define SYSTEM_VERSION_NAME_STRING "?"


//
// #### User ####
//
 
#define DEFAULT_USERNAME "default-[USER]"


#endif

