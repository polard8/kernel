// tentando chamar o gramado.


#include <errno.h>

#undef __syscall_return
#define __syscall_return(type, res) \
do { \
	if ((unsigned long)(res) >= (unsigned long)(-125)) { \
		errno = -(res); \
		res = -1; \
	} \
	return (type) (res); \
} while (0)


// Não pode ser void.
#undef _syscall0
#define _syscall0(type,name) \
type name(void) \
{ \
long __res; \
__asm__ volatile ("int %1 \n" \
	: "=a" (__res) \
	: "i" (0x80), "a"(SYS_##name), "b"(0), "c"(0), "d"(0) ); \
__syscall_return(type,__res); \
}


#undef _syscall1
#define _syscall1(type,name, type1, arg1) \
type name(type1 arg1) \
{ \
long __res; \
__asm__ volatile ("int %1 \n" \
	: "=a" (__res) \
	: "i" (0x80), "a"(SYS_##name), "b"(arg1), "c"(0), "d"(0) ); \
__syscall_return(type,__res); \
}


#undef _syscall2
#define _syscall2(type,name, type1, arg1, type2, arg2) \
type name(type1 arg1, type2 arg2) \
{ \
long __res; \
__asm__ volatile ("int %1 \n" \
	: "=a" (__res) \
	: "i" (0x80), "a"(SYS_##name), "b"(arg1), "c"(arg2), "d"(0) ); \
__syscall_return(type,__res); \
}



#undef _syscall3
#define _syscall3(type,name, type1, arg1, type2, arg2, type3, arg3) \
type name(type1 arg1, type2 arg2, type3 arg3) \
{ \
long __res; \
__asm__ volatile ("int %1 \n" \
	: "=a" (__res) \
	: "i" (0x80), "a"(SYS_##name), "b"(arg1), "c"(arg2), "d"(arg3) ); \
__syscall_return(type,__res); \
}






//
// exemplo.
//

/*
#undef __syscall_return
#define __syscall_return(type, res) \
do { \
	if ((unsigned long)(res) >= (unsigned long)(-125)) { \
		errno = -(res); \
		res = -1; \
	} \
	return (type) (res); \
} while (0)
*/

/*
#undef _syscall0
#define _syscall0(type,name) \
type name(void) \
{ \
long __res; \
__asm__ volatile ("int $0x80" \
	: "=a" (__res) \
	: "0" (__NR_##name)); \
__syscall_return(type,__res); \
}
*/

 

 
