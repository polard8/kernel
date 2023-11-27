
// kctl.h

#ifndef __KCTL_KCTL_H
#define __KCTL_KCTL_H    1

// ---------------------------------
// process group
// When a process belongs to a group,
// these are the resources that this processes is allowed to use.
// #todo:
// Some of these information can be saved into the file system.
// #importante:
struct process_group_d
{
    int used;
    int magic;

// The index of this structure into the list of structures of the same type.
    int id;
// The group id associated with this structure.
    gid_t gid;
//------------------------
// Resources

// Kernel consoles.
// What are the kernel consoles that this group of process are
// allowed to use?
// We only have 4 kernel consoles.
    int consoles[4];

// ...
};

// ---------------------------------
// Namespaces
struct namespaces_d 
{
    int used;
    int magic;
    
    // #todo
    //char name[64];

// The index of this structure into the list of structures of the same type.
    int id;
// The group id associated with this structure.
    gid_t gid;
//------------------------

};

#endif   


