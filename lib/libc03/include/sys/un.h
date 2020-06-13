
// sys/un.h
// Socket support for libc03.
// ring3
// 2020 - Created by Fred Nora.


#ifndef ____UN_H
#define ____UN_H


//#test
#include <sys/ansi.h>
#include <netinet/in.h>


#define UNIX_PATH_MAX 108
struct sockaddr_un {

    //#bugbug
    //ps: It needs to be 16 bit.
    // See: netinet/in.h
    sa_family_t sun_family; 
    //uint16_t sun_family;
    
    char sun_path[UNIX_PATH_MAX];
};


#endif    



