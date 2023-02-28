
// product.h

#ifndef __PRODUCT_PRODUCT_H
#define __PRODUCT_PRODUCT_H    1

//
//  == Product name ==========================================
//

#define PRODUCT_NAME    "Gramado OS"

//
//  == Product type ==========================================
//

// The business server.
#define PT_GRAMADO_SERVER         1000
#define PT_GRAMADO_SERVER_STRING  "Server"
// Enterprise machines to access the business server.
#define PT_GRAMADO_WORKSTATION         2000
#define PT_GRAMADO_WORKSTATION_STRING  "Workstation"
// Regular desktop machine.
#define PT_GRAMADO_DESKTOP         3000
#define PT_GRAMADO_DESKTOP_STRING  "Desktop" 
// IOT devices
#define PT_GRAMADO_IOT         4000
#define PT_GRAMADO_IOT_STRING  "IOT" 

// Current product type
// Updated by the builder.
#define PRODUCT_TYPE         PT_GRAMADO_DESKTOP
#define PRODUCT_TYPE_STRING  PT_GRAMADO_DESKTOP_STRING

#define MACHINE_TYPE_STRING  "x86_64"

#endif    

