// see: 
//http://man7.org/linux/man-pages/man7/pty.7.html
//https://en.wikipedia.org/wiki/Pseudoterminal
//https://lwn.net/Articles/688809/

// See: ptmx.


#ifndef ____PTY_H
#define ____PTY_H  1


/*
#important
window server >> terminal >> shell

    The terminal communicates with the window server via socket.
    To create an instance of a terminal, you need to open a ptmx, 
    that is a multiplexer and has its own file system, and 
    the ptmx will give you two TTYs, one for master and one for slave. 
    These tty given by the ptmx is called pty. 
    So the shell will use the pty slave and the terminal will 
    use the pty master.
*/    

// A pseudoterminal (sometimes abbreviated "pty") is a pair of virtual
// character devices that provide a bidirectional communication channel.
// The slave end of the pseudoterminal provides an interface
// that behaves exactly like a classical terminal.
// A process that expects to be connected to a terminal, 
// can open the slave end of a pseudoterminal and then be driven 
// by a program that has opened the master end.   
   
   
            
// In some operating systems, including Unix, a pseudoterminal, 
// pseudotty, or PTY is a pair of pseudo-devices, ...

// The multiplexer and the pts fili system.
// This design for PTYs created two related singletons: 
// the master multiplexer /dev/ptmx and the slave virtual filesystem /dev/pts. 

//pty é um canal de comunicação com duas pontas.
// é semelhante ao canal com dois soquetes, um em cada ponta.
// enquando os canais usam os termos server/client os pty
// usam os termos master/slave.

// #importante
// não existe estrutura de pty. 
// pty usa a estrutura de tty.

//ex: terminal=slave  shell=master.

// UNIX 98 pseudoterminals
// BSD pseudoterminals


//pty BSD master devices
//tty BSD slave devices

/*
The role of the terminal emulator process is:

    to interact with the user.
    
    to feed text input to the master pseudo-device for use by 
    the shell (such as bash), which is connected to the slave 
    pseudo-device (virtual terminal).
    
    to read text output from the master pseudo-device (shell) and show 
    it to the user.
*/


//credits: linux
// pty subtypes;
// lembrando que pty usa a mesma estrutura do tty.

#define  PTY_TYPE_MASTER  0x0001
#define  PTY_TYPE_SLAVE   0x0002

 


//Ligar duas tty dados os pids dos processos que possuem as tty.
// isso será usado pelo terminal se ele tiver o pid do filho.
int pty_link_by_pid ( int master_pid, int slave_pid );

int pty_link ( struct tty_d *master, struct tty_d *slave );
int pty_unlink ( struct tty_d *tty );

int ptmx_open (void);
 

#endif    


