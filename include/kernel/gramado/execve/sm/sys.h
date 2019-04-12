

//   sm/sys.h (System Management)

// classe de interfaces para rotinas de sistema.
// INTERFACES PARA ROTINAS QUE AUXILIAM O GERENCIAMENTO DO SISTEMA.
// ex: ligamentos, desligamentos, criação, destruição ...


//
// PROCESSES
//

void *sys_create_process ( struct room_d *room,
                           struct desktop_d  *desktop,
                           struct window_d *window,
                           unsigned long init_eip, 
                           unsigned long priority, 
                           int ppid, 
                           char *name, 
                           unsigned long iopl,
                           unsigned long directory_address );

int sys_getpid ();
int sys_getppid ();
int sys_fork ();
void sys_exit_process (int pid, int code);



//
// THREADS
//

void *sys_create_thread ( struct room_d *room,
                          struct desktop_d  *desktop,
                          struct window_d *window,
                          unsigned long init_eip, 
                          unsigned long priority, 
                          int ppid, 
                          char *name );

void sys_exit_thread (int tid);
void sys_dead_thread_collector ();



//Sincronização do retraço vertical.
void sys_vsync();

//Show kernel info.
void sys_showkernelinfo();

//Show pci info.
int sys_showpciinfo();


//
// reboot and shutdown
//

void sys_reboot ();
void sys_shutdown ();


//
// End.
//

