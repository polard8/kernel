

// #importante
// As system calls precisam usar os números do systema operacional alvo.
// Na verdade pode variar de acordo com a arquitetura no mesmo sistema operacional.

#ifndef _SYS_SYSCALL_H
#define _SYS_SYSCALL_H

#ifdef __GRAMADO
#include <sysdeps/gramado/syscall.h>
#endif


#ifdef __LINUX
#include <sysdeps/linux/syscall.h>
#endif

#endif /* _SYS_SYSCALL_H */


//...


