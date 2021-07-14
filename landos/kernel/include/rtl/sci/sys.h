
// sys.h

#ifndef ____SYS_H
#define ____SYS_H  1


int sys_read (unsigned int fd, char *ubuf, int count);
int sys_write (unsigned int fd, char *ubuf, int count);

int file_read_buffer ( file *f, char *buffer, int len );
int file_write_buffer ( file *f, char *string, int len );
int sys_close (int fd);
void sys_exit_thread (int tid);
int sys_fcntl ( int fd, int cmd, unsigned long arg );
unsigned long sys_get_file_size ( char *path );


int sys_get_file_sync (int fd, int request);
void sys_set_file_sync(int fd, int request, int data);


int sys_getpid (void);
int sys_getppid (void);

int sys_initialize_component (int n);

int 
sys_open (
    const char *pathname, 
    int flags, 
    mode_t mode );

void sys_reboot (void);
int sys_serial_debug_printk ( char *s );

void sys_show_system_info ( int n );

void sys_vsync(void);

#endif   


















