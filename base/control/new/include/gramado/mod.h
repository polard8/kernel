
// mod.h

#ifndef __GRAMADO_MOD_H
#define __GRAMADO_MOD_H    1

#define KMODULE_MOD0  0   // first of the list.
#define KMODULE_MAX   8

// Informações compartilhadas 
// entre o kernel e um dado módulo.
struct km_shared_info_d
{
// The entry point
    unsigned long entry_point;
// Procedure.
    unsigned long dialog_address;
// The pointer for a table of symbols exported
// by this module.
    unsigned long function_table_address;
};

struct kernel_module_d
{
    int used;
    int magic;
    int id;

    int initialized;

    char name[64];
    size_t name_size;

// Shared info
    struct km_shared_info_d info;
    struct thread_d  *thread;

// Navigation
    struct kernel_module_d  *next;
};

// see: mod.c, x64init.c
extern struct kernel_module_d  *kernel_mod0;

// see: mod.c
extern unsigned long kmList[KMODULE_MAX];

//----------------------------------------------


void test_mod0(void);

#endif   


