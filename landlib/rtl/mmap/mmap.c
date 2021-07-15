
/*
 * File: mmap.c 
 * 
 *     mmap, munmap - map or unmap files or devices into memory
 *     Created by Fred Nora.
 */

#include  <types.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <ctype.h>
#include  <stdarg.h>
#include  <sys/mman.h>

// #todo
void *mmap ( 
    void *addr, 
    size_t length, 
    int prot, 
    int flags,
    int fd, 
    off_t offset )
{
    debug_print ("mmap: [TODO]\n");
    
    //if (fd<0){}
    
    return NULL; 
}

//#todo
int munmap (void *addr, size_t length)
{
    debug_print ("munmap: [TODO]\n");
    return -1;
}

