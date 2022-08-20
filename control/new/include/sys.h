
// sys.h

#ifndef ____SYS_H
#define ____SYS_H  1

unsigned long sys_get_system_metrics(int n);

void *sys_create_process ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long res1,          //nothing
    unsigned long priority, 
    int ppid, 
    char *name,
    unsigned long iopl );

void *sys_create_thread ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long init_rip, 
    unsigned long priority, 
    int ppid, 
    char *name );


void sys_exit_thread (int tid);

int sys_fork (void);

int sys_getpid (void);
int sys_getppid (void);

int sys_initialize_component(int n);

int sys_serial_debug_printk ( char *s );

void sys_show_system_info ( int n );

int sys_uname (struct utsname *ubuf);

void sys_vsync(void);

int sys_reboot(void);
void sys_shutdown (void);

#endif   


















