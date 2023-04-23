
// host.h

#ifndef __OS_HOST_H
#define __OS_HOST_H    1

struct gws_host_d
{
    int id;
    int used;
    int magic;

    char name[256];
    // ...
};

#endif    



