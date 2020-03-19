
//ipccore.h

//para se conetar com os servidores do mo'dulo gramado core.


//registra um dos servidores do gramado core.
int ipccore_register ( int server_index, struct process_d *process, struct thread_d *thread );

unsigned long ipcore_services ( unsigned long number, unsigned long arg2, unsigned long arg3, unsigned long arg4 );

int ipccore_open ( int pid, int server_index );
int ipccore_close ( int pid, int server_index );


