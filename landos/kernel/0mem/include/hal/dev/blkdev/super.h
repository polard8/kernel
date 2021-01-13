/*
 * File: blkdev/super.h
 */


#ifndef  __SUPER_H
#define  __SUPER_H    1


// Superbloco de um disco.
// tera uma estrutura de volume;
struct superblock_d
{
    int id;
    int used;
    int magic;
    
    // ...
    
    struct superblock_d *next;
};

#endif    


