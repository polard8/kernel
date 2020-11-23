/*
 * File: io.c
 *
 * Descrição:
 *     Arquivo principal do I/O Manager.
 *     I/O control. 
 *     Obs: Note que o I/O Manager está fora do executive, mas faz parte 
 *          do Kernel Base.
 *
 * Todo gerenciamento de dispositivos, toda concessão de acesso passará por 
 * esse gerenciador, que faz parte da camada de abstração de hardware 
 * oferecida pelo kernel base.
 * Essa parte do gerenciamento de i/o está no kernel base em kernel mode. 
 * Porem haverá outras partes. Haverá um subsistema em user mode, e talvez 
 * um módulo externo do kernel em kernel mode.
 *
 * I/O system: Inclui I/O manager
 *
 *  @todo: Cria funções para gerenciar ioBuffers.
 * The actual fileList modules lives in kernel space on Unix, and are 
 * installed (pushed) and removed (popped) by the ioctl system call.
 * 
 *    2016 - Created by Fred Nora.
 */


#include <kernel.h> 


//==========================================
// This is called by ioctl() in ring3.

// OK Isso é um wrapper.
// Chamaremos tty_ioctl() ou outros ...  
// ...

// See:
// http://man7.org/linux/man-pages/man2/ioctl.2.html
// https://en.wikipedia.org/wiki/Ioctl

// The ioctl() system call manipulates the 
// underlying device parameters of special files.
// In particular, many operating characteristics of
// character special files (e.g., terminals) may be controlled with
// ioctl() requests.  The argument fd must be an open file descriptor.

// return:
// On error, -1 is returned, and errno is set appropriately.
// EBADF  fd is not a valid file descriptor.
// EFAULT argp references an inaccessible memory area.
// EINVAL request or argp is not valid.
// ENOTTY fd is not associated with a character special device.
// ENOTTY 
// The specified request does not apply to the kind of object
// that the file descriptor fd references

       
// Called by sys_ioctl().
// But this routine can be called by the routines inside the kernel.

int io_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    struct process_d *p;
    file *f;


    debug_print ("io_ioctl: [TODO]\n");

    // fd must to be on open file descriptor.
    if ( fd<0 || fd>31 ){
       debug_print("io_ioctl: [FAIL] Invalid fd\n");
       return -1;  //EBADF
    }

    // #todo
    // Check the arg pointer validation
    // EFAULT
    // But we will not use this argument in all the cases.

    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("io_ioctl: [FAIL] p fail\n");
        return -1;
    }
        
    if ( p->used != 1 || p->magic != 1234 ){
        debug_print("io_ioctl: [FAIL] validation fail\n");
        return -1;
    }
  
    // pega o arquivo.
    // checa o tipo de objeto.
    // Isso deve ser usado principalmente com dispositivos 
    // de caracteres como o terminal.
    // #todo
    // check file structure validation.
    // The TIOCSTI (terminal I/O control, 
    // simulate terminal input) ioctl 
    // function can push a character into a device stream
    // ENOTTY -  "Not a typewriter"
    // #todo
    // Now we can use a swit to call different
    // functions, as tty_ioctl etc.

    f = (file *) p->Objects[fd];

    if ( (void *) f == NULL ){
        debug_print("io_ioctl: [FAIL] f\n");
        return -1;
    }

    switch (f->____object){

        // Pode isso ??
        // Normal file ???
        // See: kstdio.c
        case ObjectTypeFile:
            debug_print ("io_ioctl: ObjectTypeFile [TEST]\n");
            return (int) regularfile_ioctl ( (int) fd, 
                            (unsigned long) request, 
                            (unsigned long) arg );
            break;

        // tty object
        case ObjectTypeTTY:
        //case ObjectTypeTerminal: 
            debug_print ("io_ioctl: ObjectTypeTTY\n"); 
            return (int) tty_ioctl ( (int) fd, 
                            (unsigned long) request, 
                            (unsigned long) arg );
            break;
        
        // socket object
        case ObjectTypeSocket:
            debug_print ("io_ioctl: ObjectTypeSocket\n");
            return (int) socket_ioctl ( (int) fd, 
                            (unsigned long) request, 
                            (unsigned long) arg );
            break;
        
        // Console object
        // See: console.c
        case ObjectTypeVirtualConsole: 
            debug_print ("io_ioctl: ObjectTypeVirtualConsole\n");
            return (int) console_ioctl ( (int) fd, 
                            (unsigned long) request, 
                            (unsigned long) arg );
            break; 


        //...    
            
        default:
            debug_print ("io_ioctl: [FAIL] default object\n");
            return -1;  //ENOTTY maybe
            break;
    }

    //fail
    debug_print ("io_ioctl: Fail\n");
    return -1;
}




/*
 ********************************
 * ioInit:
 *     Initialize i/o manager.
 */

int ioInit(void){

    int Status = 0;


    debug_print ("ioInit: [TODO]\n");
    
    // ...

    return (int) Status;
}


//
// End.
//

