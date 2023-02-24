
// vt.h

#ifndef ____VT_H
#define ____VT_H  1

struct vt_d
{
    //Object

    int id;
    int used;
    int magic;

// The PID of the father that owns the terminal window.
    pid_t father_pid;
// The PID of the command running inside the window that is a terminal.
    pid_t child_pid;

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


//
// == prototypes ==================
//


#endif    



