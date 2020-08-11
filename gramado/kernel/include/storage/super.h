/*
 * File: storage/super.h
 */



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





