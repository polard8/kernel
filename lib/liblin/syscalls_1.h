
// chamada ao gramado
// até 4 argumentos

void *syscalls_1_system_call ( unsigned long ax, 
                               unsigned long bx, 
                               unsigned long cx, 
                               unsigned long dx )
{
    int Ret = 0;

    //System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(Ret)	
                 : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    return (void *) Ret; 
}


// #importante
// Não pode ser do tipo void.

#undef _syscall0
#define _syscall0(type,name) \
type name(void) \
{ \
	return (type) syscalls_1_system_call ( (unsigned long) SYS_##name, 0, 0, 0 ); \
}\


