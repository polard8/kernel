
// sched.c

#include <sys/types.h>
#include <sched.h>


int sched_yield(void)
{
    //#todo
    //rtl_yield();
    return (int) -1;
}

int sched_setparam(pid_t pid, const struct sched_param* param)
{
    return (int) -1;
}

int sched_getparam(pid_t pid, struct sched_param *param)
{
    return (int) -1;
}



