/**********************************************************************

  File: gramado.h

  History:
  2018 - Created by Fred Nora.

  Copyright (C) 2005-2018 Fred Nora

**********************************************************************/

#ifndef GRAMADO_H
#define GRAMADO_H 1


//
// #### Name ####
//

#define OS_NAME "Gramado"
#define OS_LONGNAME "Gramado Operating System"


//
// #### Version ####
//


//Kernel version
//Esse é padrão de versão. 
//Não mudar, apenas fazer as atualizações. 
#define SYSTEM_VERSION_MAJOR 0 
#define SYSTEM_VERSION_MINOR 5
#define SYSTEM_VERSION_REVISION 0   

//Kernel version strings.
#define SYSTEM_VERSION_STRING "0.5"
#define SYSTEM_VERSION_NAME_STRING "Five"


//
// #### Product ####
//


// Seleciona o tipo de produto.
// #Define a edição atuala do sistema.
// 1,2,3,4 ... 
#define SYSTEM_EDITION 1               

#define SYSTEM_DEVELOPER_EDITION    1  //Contém ferramentas do desenvolvedor.
#define SYSTEM_WORKSTATION_EDITION  2  //Contém ferramentas de escritório.
#define SYSTEM_SERVER_EDITION       3  //Contém ferramentas de comunicação em rede.
#define SYSTEM_IOT_EDITION          4  //Contém ferramentas de suporte á dispositivos externos.

#define SYSTEM_DEVELOPER_EDITION_STRING    "Gramado Developer Edition"    
#define SYSTEM_WORKSTATION_EDITION_STRING  "Gramado Workstation Edition"  
#define SYSTEM_SERVER_EDITION_STRING       "Gramado Server Edition"       
#define SYSTEM_IOT_EDITION_STRING          "Gramado IOT Edition"       


//
// #### User ####
//
 
#define DEFAULT_USERNAME "default-[USER]"


#endif

