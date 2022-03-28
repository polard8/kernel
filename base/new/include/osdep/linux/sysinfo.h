
// #todo
// Include this file in kernel.h

// sysinfo.h
// Information about the host system used during the compiling time.
//


struct linux_sysinfo_d
{
    int used;
    int magic;

    // ...
};

struct linux_sysinfo_d *linux_sysinfo;


