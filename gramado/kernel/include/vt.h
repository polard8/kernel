

#ifndef ____VT_H
#define ____VT_H



// This struct is an element of window_d struct.
struct vt_d
{
    //Object
    
    int id;
    
    int used;
    int magic;
    
    
    // The PID of the father that owns the terminal window.
    int father_pid;
    
    // The PID of the command running inside the window that is
    // a terminal.
    int child_pid;
    
    // what is the state of this terminal ?
    int state;
    
    
    //
    // pty channel.
    //
    
    struct tty_d *master;
    struct tty_d *slave;
     
    // Continue
    // ...
};


// Listar os terminais virtuais.
// Isso vai ajudar a mandar as mensagens;
unsigned long vtList[32];


int 
vt_ioctl ( 
    int fd, 
    unsigned long request, 
    char *arg );

void _vt_outbyte ( int c, struct tty_d *tty );
void vt_outbyte ( int c, struct tty_d *tty );
void vt_scroll (struct tty_d *tty);



// Create a terminal for a window.
// The father is creating a terminal in one of its windows.
int vt_create (struct window_d *window, int father_pid);

// Set child pid given in a window structure.
int vt_set_child ( struct window_d *window, int child_pid );

//init module.
int vt_init_module (void);


#endif    


