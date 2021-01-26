/*
 * File: host.h
 * 
 *     This header should be included by including "gws.h".
 */


#ifndef __LIBGWS_HOST_H
#define __LIBGWS_HOST_H  1


struct gws_host_d
{

    int id;
    int used;
    int magic;
    
    char name[256];
    // ...
};

#endif    



