
// gns.h
// This a client-side library for GNS, Gramado Network Server.

#include "gns_pack.h"

#define LIBGNS_VERSION_STRING  "0.1"

//
// prototypes
//

void *gns_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d );

int gns_hello(int fd);
void gns_yield(void);
void gns_debug_print (char *string);

