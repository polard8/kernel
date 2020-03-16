
/*
 * File: mmap.c 
 * 
 *     mmap, munmap - map or unmap files or devices into memory
 * 
 * Created by Fred Nora.
 */



#include  <types.h>

#include	<stdio.h>
#include	<stdlib.h>
#include	<ctype.h>
#include	<stdarg.h>

#include  <sys/mman.h>



//#todo
void *mmap ( void *addr, 
             size_t length, 
             int prot, 
             int flags,
             int fd, 
             off_t offset )
{
    return NULL; 
}

//#todo
int munmap (void *addr, size_t length)
{
    return -1;
}






