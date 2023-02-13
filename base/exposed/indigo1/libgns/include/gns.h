
// gns.h
// This a client-side library for GNS, Gramado Network Server.

#define LIBGNS_VERSION_STRING  "0.1"

#include "gns_pack.h"
#include "protocol.h"


//
// prototypes
//

void *gns_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d );

void
gns_async_command ( 
    int fd, 
    unsigned long request,
    unsigned long sub_request,
    unsigned long data );


int gns_hello(int fd);
void gns_yield(void);
void gns_debug_print (char *string);

