
#ifndef ____U_H
#define ____U_H  1


//
// name
//

#define OS_LONGNAME    PRODUCT_NAME


//
// user
//
 
#define DEFAULT_USERNAME "default-[USER]"


//
// utsname
// 

/* Operating system name (e.g., "Linux") */
#define OS_NAME       "Gramado Operating System"

/* Name within "some implementation-defined network" */
#define NODE_NAME     "gramado-node"

// See:
// gramado/0config/version.h

/* Operating system release (e.g., "2.6.28") */
#define RELEASE_NAME  VERSION_STRING

/* Operating system version */
#define VERSION_NAME  RELEASE_STRING

 /* Hardware identifier */
#define MACHINE_NAME  "hardware-name"


//
// system
//

#define SYSTEM_VERSION_MAJOR    VERSION_MAJOR
#define SYSTEM_VERSION_MINOR    VERSION_MINOR
#define SYSTEM_VERSION_BUILD    VERSION_BUILD


#endif    


