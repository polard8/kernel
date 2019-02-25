

//   sm\sys.h (System Management)

// classe de interfaces para rotinas de sistema.
// INTERFACES PARA ROTINAS QUE AUXILIAM O GERENCIAMENTO DO SISTEMA.
// ex: ligamentos, desligamentos, criação, destruição ...


//
// PROCESSES
//

int sys_getpid();     //Get process Identification.
int sys_getppid();    //Get parent process Identification.


int sys_fork();
void sys_exit_process(int pid, int code);

void *sys_create_process ( struct room_d *room,
                           struct desktop_d  *desktop,
                           struct window_d *window,
                           unsigned long init_eip, 
                           unsigned long priority, 
					       int ppid, 
					       char *name, 
						   unsigned long iopl,
                           unsigned long directory_address );
						  
//
// THREADS
//

void sys_dead_thread_collector();
void sys_exit_thread(int tid);

void *sys_create_thread( struct room_d *room,
                         struct desktop_d  *desktop,
                         struct window_d *window,
                         unsigned long init_eip, 
                         unsigned long priority, 
					     int ppid, 
					     char *name );
						 

//Sincronização do retraço vertical.
void sys_vsync();

//Show kernel info.
void sys_showkernelinfo();

//Show pci info.
int sys_showpciinfo();

//reboot.
void sys_reboot();
		
//shutdown.		
void sys_shutdown();

//
//fim.
//

