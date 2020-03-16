

//#define __LINUX

#include <sys/types.h>  

#include <sysdeps/linux/syscall.h>

//system calls.
//#include <stubs/syscalls_1.h>
#include <stubs/syscalls_2.h>

void test1(){}


_syscall0 ( int, xxxtest0 );
_syscall1 ( int, xxxtest1, int, argxxx1 );
_syscall2 ( int, xxxtest2, int, argxxx1, int, argxxx2 );
_syscall3 ( int, xxxtest3, int, argxxx1, int, argxxx2, int, argxxx3 );

