
// un.h
// socket support for the base kernel.
// ring0
// 2020 - Created by Fred Nora.


#ifndef ____UN_H
#define ____UN_H



#define UNIX_PATH_MAX 108
struct sockaddr_un {
    uint16_t sun_family;
    char sun_path[UNIX_PATH_MAX];
};



#endif   

