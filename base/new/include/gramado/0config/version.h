/**********************************************************************

  File: version.h

        Product configuration.
 
  History:
      2018 - Created by Fred Nora.

**********************************************************************/



#ifndef ____VERSION_H
#define ____VERSION_H 1


//
//  == Product name ==========================================
//


#define PRODUCT_NAME    "Gramado Operating System"


//
//  == Product type ==========================================
//

// The business server.
#define PT_GRAMADO_SERVER         1000

// Enterprise machines to access the business server.
#define PT_GRAMADO_WORKSTATION    2000

// Regular desktop machine.
#define PT_GRAMADO_DESKTOP        3000 

// iot machine
#define PT_GRAMADO_IOT            4000 

// static
#define PRODUCT_TYPE    PT_GRAMADO_DESKTOP


//
//  == Product version ==========================================
//

// #todo
// Now we are generating some files in the build time.
// We can read these files to get all that info.
// Maybe we will delete all these defines here.

#define VERSION_MAJOR     2
#define VERSION_MINOR     0
#define VERSION_BUILD     0
#define VERSION_STRING    "2.0"


//
// Version macro
//

#define VER10    0x0100
#define VER11    0x0101
#define VER20    0x0200


#endif





