
// sys.h

#ifndef ____SYS_H
#define ____SYS_H  1



unsigned long sys_get_system_metrics ( int n );

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


int sys_read (unsigned int fd, char *ubuf, int count);
int sys_write (unsigned int fd, char *ubuf, int count);

int file_read_buffer ( file *f, char *buffer, int len );
int file_write_buffer ( file *f, char *string, int len );
int sys_close (int fd);
void sys_exit_thread (int tid);

int sys_fork (void);
int sys_fcntl ( int fd, int cmd, unsigned long arg );

unsigned long sys_get_file_size ( char *path );


int sys_get_file_sync (int fd, int request);
void sys_set_file_sync(int fd, int request, int data);


int sys_getpid (void);
int sys_getppid (void);

int sys_initialize_component (int n);

int sys_ioctl ( int fd, unsigned long request, unsigned long arg );

int 
sys_open (
    const char *pathname, 
    int flags, 
    mode_t mode );

void sys_reboot (void);
int sys_serial_debug_printk ( char *s );

void sys_show_system_info ( int n );

int sys_sleep_if_socket_is_empty ( int fd );


int sys_uname (struct utsname *ubuf);

void sys_vsync(void);

void sys_shutdown (void);

#endif   


















