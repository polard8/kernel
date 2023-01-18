
// u.h

#ifndef __CONFIG_GRAMADO_U_H 
#define __CONFIG_GRAMADO_U_H   1

//
// utsname
// 

/* Operating system name (e.g., "Linux") */
#define OS_NAME       "Gramado"
#define OS_LONGNAME    PRODUCT_NAME
/* Operating system version */
#define VERSION_NAME  VERSION_STRING
// See: version.h
/* Operating system release (e.g., "2.6.28") */
#define RELEASE_NAME  RELEASE_STRING 
/* Hardware identifier */
#define MACHINE_NAME  "hardware-name"
/* Name within "some implementation-defined network" */
#define NODE_NAME     "gramado-node"

//#todo: domain name
#define DOMAIN_NAME     "domain-name"

// system
#define SYSTEM_VERSION_MAJOR  VERSION_MAJOR
#define SYSTEM_VERSION_MINOR  VERSION_MINOR
#define SYSTEM_VERSION_BUILD  VERSION_BUILD

// User
#define DEFAULT_USERNAME  "anon"

#endif    


