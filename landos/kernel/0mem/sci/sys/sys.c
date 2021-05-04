/*
 * File: sys.c
 *
 *
 * History:
 *     2019 - Created by Fred Nora.
 */


#include <kernel.h>


// #todo
// Comment the purpose of this routine.
// It is used on socket communication.

void sys_set_file_sync(int fd, int request, int data)
{
    struct process_d  *p;
    file *object;

    //#bugbug
    // Pensaremos nessa possibilidade.
    
    /*
    if (fd == 0 || fd == 1 || fd == 2 )
    {
        debug_print("sys_close: [FIXME] We can't close the standard stream\n");
        // WHY NOT ???!!
        return (int) (-1);
    }
    */

    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_set_file_sync: [FAIL] fd\n");
        return;
    }

    // == Process ================

    if ( current_process < 0 ){
        debug_print("sys_set_file_sync: [FAIL] current_process\n");
        return;
    }

    p = (void *) processList[current_process];

    if ( (void *) p == NULL )
    {
        debug_print("sys_set_file_sync:  [FAIL] p\n");
        return;
    }

    // #todo
    // check validation

    // object
        
    object = (file *) p->Objects[fd];

    if ( (void*) object == NULL )
    {
        debug_print("sys_set_file_sync: [FAIL] object\n");
        return;
    }

    if ( object->used != TRUE || object->magic != 1234 )
    {
        debug_print("sys_set_file_sync: validation\n");
        return;
    }
    
    switch (request){

        // set last action
        case SYNC_REQUEST_SET_ACTION:
            object->sync.action = data;
            break;
        
        //case ?:
            //break;
        
        // ...
        
        default:
            debug_print("sys_set_file_sync: [FAIL] Default request\n");
            return;
            break;
    };

    // ...
}


// #todo
// Comment the purpose of this routine.
// It is used on socket communication.

int sys_get_file_sync (int fd, int request)
{
    struct process_d  *p;
    file *object;

    //#bugbug
    // Pensaremos nessa possibilidade.
    
    /*
    if (fd == 0 || fd == 1 || fd == 2 )
    {
        debug_print("sys_close: [FIXME] We can't close the standard stream\n");
        // WHY NOT ???!!
        return (int) (-1);
    }
    */

    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_get_file_sync: [FAIL] fd\n");
        return (int) (-1);
    }

    // == Process ================

    if ( current_process < 0 ){
        debug_print("sys_get_file_sync: current_process\n");
        return (int) (-1);
    }

    p = (void *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_get_file_sync: p\n");
        return (int) (-1);
    }

    // #todo
    // check validation

    // object
        
    object = (file *) p->Objects[fd];

    if ( (void*) object == NULL ){
        debug_print("sys_get_file_sync: [FAIL] object\n");
        return (int) (-1);
    }

    if ( object->used != TRUE || object->magic != 1234 )
    {
        debug_print("sys_get_file_sync: validation\n");
        return (int) (-1);
    }


    switch (request){

        // get last action
        case SYNC_REQUEST_GET_ACTION:
            return (int) object->sync.action;
            break;
        

        //case ?:
            //break;
        
        // ...
        
        default:
            debug_print("sys_get_file_sync: [FAIL] Default request\n");
            return (int) (-1);
            break;
    };

    // ...
    return 0;
}




//credits: linux gpl
/*
int sys_alarm(long seconds)
int sys_alarm(long seconds)
{
	int old = current->alarm;

	if (old)
		old = (old - jiffies) / HZ;
	current->alarm = (seconds>0)?(jiffies+HZ*seconds):0;
	return (old);
}
*/

//credits: linux gpl
/*
int sys_signal(int signum, long handler, long restorer);
int sys_signal(int signum, long handler, long restorer)
{
	struct sigaction tmp;

	if (signum<1 || signum>32 || signum==SIGKILL)
		return -1;
	tmp.sa_handler = (void (*)(int)) handler;
	tmp.sa_mask = 0;
	tmp.sa_flags = SA_ONESHOT | SA_NOMASK;
	tmp.sa_restorer = (void (*)(void)) restorer;
	handler = (long) current->sigaction[signum-1].sa_handler;
	current->sigaction[signum-1] = tmp;
	return handler;
}
*/




// Helper function to initialize system's component
// after kernel initialization.
//  This is called by ring3 apps.

int sys_initialize_component (int n)
{

    if(n<0)
        return -1;


    switch (n)
    {
        
        case 1:
            //PS2_early_initialization();
            PS2_initialize();
            return 0;
            break;

        //case 2:
            //break;

        //case 3:
            //break;

        //case 4:
            //break;


        // ...
        

        default:
            return -1;
            break;
    };
    
    return (int) 0;
}


// 250
unsigned long sys_get_system_metrics ( int n )
{
    return (unsigned long) systemGetSystemMetrics ( (int) n );
}








/*
 *************** 
 * sys_uname:
 * 
 */

// service 377.
int sys_uname (struct utsname *ubuf){


    if ( (void *) ubuf == NULL ){
        //#todo: message.
        return -1;
    }


    memcpy ( (void *)  ubuf->sysname, 
        (const void *) OS_NAME, 
        sizeof(OS_NAME) );    

    memcpy ( (void *)  ubuf->nodename, 
        (const void *) NODE_NAME, 
        sizeof(NODE_NAME) );    
        
    memcpy ( (void *)  ubuf->release, 
        (const void *) RELEASE_NAME, 
        sizeof(RELEASE_NAME) );    
        
    memcpy ( (void *)  ubuf->version, 
        (const void *) VERSION_NAME, 
        sizeof(VERSION_NAME) );    

    memcpy ( (void *)  ubuf->machine, 
        (const void *) MACHINE_NAME, 
        sizeof(MACHINE_NAME) );    

    
    return 0;
}



// 289
// See: sm/debug/debug.c
int sys_serial_debug_printk ( char *s )
{
    
    //#todo
    //if ( (void *) s == NULL )
        //return -1;
        
    debug_print ( (char *) s );
    return 0;
}


/*
 *******************************
 * sys_ioctl:
 *     system call implementation of ioctl().
 *     Executa um dado comando em um dado dispositivo.
 */

int sys_ioctl ( int fd, unsigned long request, unsigned long arg )
{

    // fd.
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_ioctl: fd\n");
        printf     ("sys_ioctl: fd\n");
        return (int) (-EINVAL);
    }

    // Enquanto sys_ioctl eh chamada pelos applicativos,
    // io_ioctl eh chamada pelas rotinas dentro do kernel.
    // See: io.c
    
    return (int) io_ioctl (fd,request,arg);
}


// #todo: 
// Rever esses argumentos.
// SVr4, 4.3BSD, POSIX.1-2001. and more.
// See: 
// https://man7.org/linux/man-pages/man2/fcntl.2.html

int sys_fcntl ( int fd, int cmd, unsigned long arg )
{
    debug_print ("sys_fcntl:\n");


    // fd.
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_fcntl: fd\n");
        printf     ("sys_fcntl: fd\n");
        return (int) (-EINVAL);
    }

    if ( cmd < 0 ){
        debug_print ("sys_fcntl: cmd\n");
        return -1;
    }
    
    //POSIX Table 6-1.
    //See: fcntl.h
    switch (cmd)
    {
        //duplicate file descriptor
        case F_DUPFD:
            debug_print ("sys_fcntl: [TODO] F_DUPFD\n");
            return -1;
            break;

        //get file descriptor flags
        case F_GETFD:
            debug_print ("sys_fcntl: [TODO] F_GETFD\n");
            return -1;
            break;

        //set file descriptor flags
        case F_SETFD:
            debug_print ("sys_fcntl: [TODO] F_SETFD\n");
            return -1;
            break;

        //get file status flags
        case F_GETFL:
            debug_print ("sys_fcntl: [TODO] F_GETFL\n");
            return -1;
            break;

        //set file status flags
        case F_SETFL:
            debug_print ("sys_fcntl: [TODO] F_SETFL\n");
            return -1;
            break;

        //get record locking information
        case F_GETLK:
            debug_print ("sys_fcntl: [TODO] F_GETLK\n");
            return -1;
            break;

        // set record locking information
        case F_SETLK:
            debug_print ("sys_fcntl: [TODO] F_SETLK\n");
            return -1;
            break;

        //set record locking info; wait if blocked
        case F_SETLKW:
            debug_print ("sys_fcntl: [TODO] F_SETLKW\n");
            return -1;
            break;

        //free a section of a regular file
        case F_FREESP:
            debug_print ("sys_fcntl: [TODO] F_FREESP\n");
            return -1;
            break;
           
        
        // ...
            
        default:
            debug_print ("sys_fcntl: default command\n");
            break;
    };


    debug_print ("sys_fcntl: FAIL\n");

    return -1; //#todo
}


//#??? isso não pertence à fcntl.c ?
//SVr4,  4.3BSD,  POSIX.1-2001. 

// #bugbug
// Precisamos de um endereço em ring 3
// para que a libc possa manipular o buffer ?

// ou open deve ser usado somente com dispositivos ??
// #obs:
// vamos retornar o indice da tabela de arquivos abertos 
// do processo atual.

// Syscall 16.

int 
sys_open (
    const char *pathname, 
    int flags, 
    mode_t mode )
{
    int _ret=-1;
 
    // ??
    // creat chama open.
    // open tenta ler num arquivo que nao existe?


    debug_print ("sys_open: $ \n");

    // See: sci/fs/fs.c
    // OUT: fd

    _ret = (int) sys_read_file_from_disk ( 
                     (char *) pathname, 
                     flags, 
                     mode );

    if ( _ret<0){
        printf ("sys_open: fail\n");
        return -1;
    }
    
    return (int) _ret;
}


// IN: fd
// OUT: -1= error; FALSE= nao pode ler; TRUE= pode ler.
int sys_sleep_if_socket_is_empty ( int fd )
{

    struct process_d *p;
    file *object;


    if (fd<0)
        return -1;


    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_sleep_if_socket_is_empty: fd\n");
        return (int) (-1);
    }

    if ( current_process < 0 ){
        debug_print("sys_sleep_if_socket_is_empty: current_process\n");
        return (int) (-1);
    }

    // process
    
    p = (void *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_sleep_if_socket_is_empty: p\n");
        return (int) (-1);
    }else{
        
        object = (file *) p->Objects[fd];
        
        // validation
        if ( (void *) object == NULL ){
            debug_print("sys_sleep_if_socket_is_empty: object\n");
            return (int) (-1);
        }else{
            
            //validation
            if (object->used != 1 || object->magic != 1234 ){
                debug_print("sys_sleep_if_socket_is_empty: calidation\n");
                return -1;
            }
            
            if ( object->____object != ObjectTypeSocket )
            {
                debug_print ("sys_sleep_if_socket_is_empty: [ERROR] only for sockets\n");
                return -1;
            }
            
            // TRUE or FALSE
            //return (int) object->socket_buffer_full;   
        
           // sim esta vazio, nao pode ler;  retorna FALSE
           if( object->socket_buffer_full == FALSE )
           {
               debug_print("sys_sleep_if_socket_is_empty: Buffer is empty. we can not read. sleeping\n");
               object->_flags |= __SWR;                  // pode escrever
               //todo: falg que nege a leitura.
               object->tid_waiting = current_thread;     // thread atual dorme   
               do_thread_waiting (current_thread);
               return FALSE;  // nao pode ler
           }
           
           // O buffer esta cheio, pode ler. retorna TRUE
           if( object->socket_buffer_full == TRUE )
           {
               debug_print("sys_sleep_if_socket_is_empty: Buffer is empty. we can read\n");
               object->_flags |= __SRD;
               return TRUE;
           }
        };
    };  
    
    debug_print ("sys_sleep_if_socket_is_empty: [FAIL] Unexpected error \n");
    return -1;
}




/*
 **************************
 *  sys_close:
 * 
 */

// Fechar um dos objetos abertos do processo atual.
// O descritor é um índice na sua tabela de objetos abertos.

// See:
// https://man7.org/linux/man-pages/man2/close.2.html
// https://pubs.opengroup.org/onlinepubs/009695399/functions/close.html

int sys_close (int fd)
{
    struct process_d *p;
    file *object;


    // ??
    // Can we close this devices?
    
    /*
    if (fd == 0 || fd == 1 || fd == 2 )
    {
        debug_print("sys_close: [FIXME] We can't close the standard stream\n");
        // WHY NOT ???!!
        return (int) (-1);
    }
    */

    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_close: fd\n");
        return (int) (-EINVAL);
    }

    // Process.

    // #todo: Check overflow.
    if ( current_process < 0 ){
        debug_print("sys_close: current_process\n");
        goto fail;
    }

    p = (void *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_close: p\n");
        goto fail;
    }

    if ( p->used != TRUE || p->magic != 1234 )
    {
        debug_print("sys_close: p validation\n");
        goto fail;
    }

    // object
    // The object is a file structure.

    object = (file *) p->Objects[fd];
        
    if ( (void *) object == NULL )
    {
        debug_print("sys_close: object\n");
        return (int) (-1);
    }

    if ( object->used != TRUE || object->magic != 1234 )
    {
        debug_print("sys_close: object validation\n");
        goto fail;
    }


    // What type of object?
    // socket, pipe, virtual console, tty, regular file ??
 
    // ===============================================
    // socket
    if ( object->____object == ObjectTypeSocket )
    {
        debug_print("sys_close: Trying to close a socket object\n");
        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }

    // ==============================================
    // pipe
    if ( object->____object == ObjectTypePipe )
    {
        debug_print("sys_close: Trying to close a pipe object\n");
        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }


    // ====================================================
    // virtual console.
    if ( object->____object == ObjectTypeVirtualConsole ){
        debug_print("sys_close: Trying to close a virtual console object\n");
        return 0;
    }
 
    // =====================================================
    // tty
    if ( object->____object == ObjectTypeTTY )
    {
        debug_print("sys_close: Trying to close a tty object\n");
        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }

    // #bugbug
    // Poderemos ter problemas aqui com os diversos tipos
    // de arquivos.

    // #bugbug
    // ugly test

    // ===========================================
    // regular file
    if ( object->____object == ObjectTypeFile )
    {
        debug_print("sys_close: [FIXME] trying to close a regular file\n");
        debug_print("sys_close: [FIXME] fsSaveFile\n");
                
        // #fixme: buffer limit
        if (object->_lbfsize < 512)
        {  
            debug_print("sys_close: [FIXME] Ajusting file size\n");
            object->_lbfsize = 512; 
        }

        // Save file in the root dir.
        // #bugbug: Where to save?

        fsSaveFile ( 
            VOLUME1_FAT_ADDRESS, 
            VOLUME1_ROOTDIR_ADDRESS, 
            FAT16_ROOT_ENTRIES,
            (char *)         object->_tmpfname, 
            (unsigned long) (object->_lbfsize/512),  // file_size, in sectors       
            (unsigned long)  object->_lbfsize,       // size_in_bytes,  
            (char *)         object->_base,          // buffer address          
            (char)           0x20 );                 // flag ??

        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }

    //
    // Object type not supported.
    //
    
    debug_print("sys_close:[FAIL] Object type not supported yet \n");

fail:
    debug_print("sys_close: [FAIL] \n");
    return (int) (-1);
}



/*
// checar se o usuário tem permissão 
// para abrir um objeto.
// vamos checar no processo atual qual é o usuário que está
// tentando abrir o objeto.
// Se permitido então colocaremos um fd na lista de arquivos
// abertos pelo processo.
int permission (file *f);
int permission (file *f)
{
    // ...
    
    return -1;
}
*/



// File read.
// It's called by sys_read.
// Copia à partir do início do arquivo.
int file_read_buffer ( file *f, char *buffer, int len )
{

    char *p;

    p = buffer;

    // Check file
    if ( (void *) f == NULL ){
        printf ("file_read_buffer: file\n");
        goto fail;
    }

    // Check buffer
    if ( (void *) p == NULL ){
        printf ("file_read_buffer: p\n");
        goto fail;
    }
    
    
    if ( len > BUFSIZ ){
        printf ("file_read_buffer: len > BUFSIZ\n");
        goto fail;
    }
    

    //
    // Copy!
    //
    
    // #todo
    // nao podemos ler mais que o limite do arquivo.
    
    // A próxima leitura precisa ser depois dessa.
    
    // Se o arquivo é um socket, então não concatenaremos escrita ou leitura.
    if ( f->____object == ObjectTypeSocket ){    
        memcpy ( (void *) buffer, (const void *) f->_base, len ); 
        return len;
    }

    //não concatenaremos
    if ( f->____object == ObjectTypePipe ){    
        memcpy ( (void *) buffer, (const void *) f->_base, len ); 
        return len;
    }



    // nesse caso a leitura tem que respeitar os offsets e limites.
    if ( f->____object == ObjectTypeFile ||
         f->____object == ObjectTypeTTY  ||
         f->____object == ObjectTypeIoBuffer)
    {
        
        // se o tamanho do buffer for maior que o padrao.
        if ( f->_lbfsize > BUFSIZ ){
            printf ("file_read_buffer: _lbfsize\n");
            goto fail;
        }
    

        // se o offset de escrita ultrapassa os limites.
        // arquivo circular?? depende do tipo. #todo
        if( f->_r < 0 || f->_r > BUFSIZ )
        {
            //#bugbug
            printf ("file_read_buffer: _r [TEST] RESETING ...\n");
            //goto fail;
            f->_p = f->_base;
            f->_r = 0; 
            return 0;
        }
    
        // se o que desejamos escrever eh maior que o espaço que temos.
        if( len < 0 || len > f->_lbfsize )
        {
            printf ("file_read_buffer: len limits\n");
            goto fail;
        }
 
        // vamos ler daqui.
        f->_p = (f->_base + f->_r);

        // read
        
        //---
        memcpy ( (void *) buffer, (const void *) f->_p, len ); 
        
        //atualizamos o ponteiro de escrita
        f->_p = (f->_p + len);

        // atualizamos o offset de escrita.
        f->_r = (f->_r + len);
        
        return (int) len;
    }



fail:
    refresh_screen ();
    return EOF;
}


/*
 * file_write: 
 *     Escreve no arquivo uma certa quantidade de caracteres de uma 
 *     dada string.
 */
// Escreve no arquivo uma certa quantidade de caracteres de uma dada string 

// It's called by sys_write.

int file_write_buffer ( file *f, char *string, int len )
{

    char *p;

    p = string;

  
    if ( (void *) f == NULL ){
        printf ("file_write_buffer: file\n");
        goto fail;
    }

    if ( (void *) p == NULL ){
        printf ("file_write_buffer: p\n");
        goto fail;
    }

    if ( len > BUFSIZ ){
        printf ("file_write_buffer: len > BUFSIZ\n");
        goto fail;
    }


    //
    // Copy!
    //
    
    // Socket file.
    // Se o arquivo é um socket, então não concatenaremos 
    // escrita ou leitura.
    if ( f->____object == ObjectTypeSocket ){
        memcpy ( (void *) f->_base, (const void *) string, len ); 
        return len;
    }

    //não concatenaremos
    if ( f->____object == ObjectTypePipe ){
        memcpy ( (void *) f->_base, (const void *) string, len ); 
        return len;
    }
    
    // Normal file.
    // Tem que atualizar o ponteiro para que o próximo
    // write seja depois desse write.
    // Para isso o ponteiro precisa estar no base quando
    // o write for usado pela primeira vez.
    // Mas se o write for usado num arquivo aberto com 
    // open(), então o ponteiro deve estar no fim do arquivo.
    
    //#todo: Normal file object
    if ( f->____object == ObjectTypeFile ||
         f->____object == ObjectTypeTTY  ||
         f->____object == ObjectTypeIoBuffer)
    {
        // #bugbug
        // Temos que ter um limite aqui ... !!!
        // #todo
    
        // se o tamanho do buffer for maior que o padrao.
        if ( f->_lbfsize > BUFSIZ ){
            printf ("file_write_buffer: _lbfsize\n");
            goto fail;
        }
    

        // se o offset de escrita ultrapassa os limites.
        // arquivo circular?? depende do tipo. #todo
        if( f->_w < 0 || f->_w > BUFSIZ )
        {
            //#bugbug
            printf ("file_write_buffer: _w [TEST] RESETING ...\n");
            //goto fail;
            f->_p = f->_base;
            f->_w = 0; 
            f->_cnt = f->_lbfsize;
            return 0;
        }
    
        // recalculando quanto espaço temos.
        f->_cnt = (f->_lbfsize - f->_w);
    
        // se a qunatidade que temos ultrapassa os limites.
        if( f->_cnt < 0 || f->_cnt > BUFSIZ )
        {
            printf ("file_write_buffer: _cnt\n");
            //goto fail;
                f->_p = f->_base; 
                f->_w = 0;
                f->_cnt = f->_lbfsize; 
        }

        // se o que desejamos escrever eh maior que o espaço que temos.
        if( len < 0 || len > f->_cnt || len > f->_lbfsize)
        {
            printf ("file_write_buffer: len limits %d\n",len);
            //goto fail;
            
            //se o len eh maior que o espaço disponivel
            //mas o espaço disponivel eh maior que zero.
            if ( f->_cnt > 0 )
            {
                len = f->_cnt; 
            }
            
            //fim do arquivo
            if ( f->_cnt <= 0 )
            {
                f->_p = f->_base; 
                f->_w = 0;
                f->_cnt = f->_lbfsize; 
            }
        }

        // write.
        
        // vamos escrever aqui.
        f->_p = (f->_base + f->_w);
    
        //escrevemos usando o ponteiro de escrita.
        memcpy ( (void *) f->_p, (const void *) string, len ); 
    
        //atualizamos o ponteiro de escrita
        f->_p = (f->_p + len);

        // atualizamos o offset de escrita.
        f->_w = (f->_w + len);
    
        //atualizamos o quanto nos falta.
        f->_cnt = (f->_cnt - len);
    
        // retornamos a quantidade escrita no buffer.
        return len;
    }
    
    // unknown type.
    
fail:
    //printf ("file_write_buffer: fail\n");
    refresh_screen ();
    return EOF;
}




/*
 ************************************
 * sys_read;
 *     implementation os read() libc function.
 */

// Service 18.
// #todo: There's a lot to do with synchronization.

// #todo
// We need to call one subfunctions for
// each different kind of file intead of implementing
// an internal sub-routine.

// #todo
// Isso deveria ser apenas um wrapper,
// chamando as rotinas apropriadas para cada tipo 
// de arquivo.

// OUT:
// 0 = Couldn't read.
// -1 = Error.

int sys_read (unsigned int fd, char *ubuf, int count)
{

    struct process_d  *__P;
    file              *__file;
    struct socket_d   *s;
    int nbytes=0; 
    int ubuf_len=0;


    // #bugbug
    // O argumento é 'unsigned int'
    // Não precisa checar <0.
    // Deveria ser apenas int?

    // fd.
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_read: fd\n");
        printf     ("sys_read: fd\n");
        return (int) (-EINVAL);
    }

    // buf.
    // todo: Checar a validade da região de memória.
    if ( (char *) ubuf == (char *) 0 ){
        debug_print ("sys_read: invalid ubuf address\n");
        printf      ("sys_read: invalid ubuf address\n"); 
        goto fail; 
    }

    // count.
    
    if ( count < 0 ){ 
        debug_print ("sys_read: count < 0\n");
        return -1;
        // return -EINVAL; 
    }
    
    if ( count == 0 ){ 
        debug_print ("sys_read: count 0\n");
        return 0; 
    }
    

    // Size of the buffer.
    ubuf_len = strlen( (const char *) ubuf );

    //Se a quantidade desejada é maior que o buffer disponível,
    //temos um problema.
    if (count > ubuf_len){
        //debug_print ("sys_read: [FIXME] count too large\n");
    }

    //Se o buffer disponível é maior que a quantidade desejada
    //então não temos problemas, nem precisamos disso. 
    if (ubuf_len > count )
        ubuf_len = count;

    //#fixme
    if (ubuf_len > 512)
    {
        debug_print ("sys_read: [FIXME] limiting ubuf_len \n");
        //ubuf_len = 512;
    }


    // Process.
    __P = (struct process_d *) processList[current_process];

    if ( (void *) __P == NULL )
    {
        debug_print ("sys_read: __P\n");
        panic       ("sys_read: __P\n");
    }

    // File.
    
    __file = (file *) __P->Objects[fd];  

    if ( (void *) __file == NULL )
    {
        debug_print ("sys_read: __file not open\n");
        printf      ("sys_read: __file not open\n");
        goto fail; 
    }


    if ( __file->sync.can_read != TRUE )
    {
        debug_print ("sys_read: [PERMISSION] Can NOT read the file\n");
        printf      ("sys_read: [PERMISSION] Can NOT read the file\n");
        goto fail; 
    }


    /*
    // #todo
    // ainda nao inicializamos esse elemento.
    if( __file->is_readable == FALSE )
    {
        debug_print ("sys_read: Not readable\n");
        return -1;
    }
    */

    // #todo: Create thie element in the structure.
    // if( __file->is_directory == TRUE ){}
    


    //==========================================================
    // stdin
    // read keyboard tty
    if ( __file->_file == 0 )
    {
        // anda nao pode ler porque nao chegou no fim da linha.
        // isso eh um console
        if ( PS2KeyboardDeviceTTY->new_event == TRUE ){
        
            // vamos ler da fila bruta. raw
            nbytes = 0;
            nbytes = (int) file_read_buffer ( 
                               (file *) PS2KeyboardDeviceTTY->_rbuffer, 
                               (char *) ubuf, 
                               (int) count );
        
            if(nbytes>0)
                PS2KeyboardDeviceTTY->_rbuffer->_flags |= __SWR;
        
            // acabamos a leitura, pode ter sido um byte ou varios.
            return nbytes;
        }
        //nao podemos ler ainda
        return 0;  // 
        //if ( PS2KeyboardDeviceTTY->new_event == TRUE ){
        //    __tty_read( PS2KeyboardDeviceTTY, ubuf, 16 );
        //    PS2KeyboardDeviceTTY->new_event = FALSE;  //mensagem consumida.
        //    return 16;
        //}
        //PS2KeyboardDeviceTTY->new_event = FALSE; //mensagem consumida.
        //return 0;
    }
    //==========================================================




    /*
    int object = (int) __file->____object; 
    switch(object)
    {
        case ObjectTypeSocket:
            //#todo: call socket_read(...)
            break;
        case ObjectTypeFile:  //regular file
           break;

        case 1:
            break;
        
        default:
            break;
    }
    */

    // maybe.    
    // is_char_dev?     read_char(...)
    // is_block_dev?    read_block(...)
    // is_
    
    
    //if ( __file->____object == ObjectTypeFile )
        //return (int) unistd_file_read ( (file *) __file, (char *) buf, (int) count );


    //if ( __file->____object == ObjectTypeDisk )
        // todo disk_read(...)


    //if ( __file->____object == ObjectTypeTTY )
        // tty_read (...) #todo criar função se não existe.


    //if pipe
    
    
    //if socket
    // socket_read()


    // #todo
    // Maybe we ca read from console.
    // if ( __file->____object == ObjectTypeVirtualConsole ){}

    //
    // == Socket file ===========================================
    //


    // #todo: 
    // Now we can call socket_read(...)
    
    // ==== Socket =======================
    // Se o arquivo for um socket.
    if ( __file->____object == ObjectTypeSocket )
    {

        // debug_print("sys_read: [DEBUG] Trying to read a socket object\n");
            
        // not reading yet
        if ((__file->_flags & __SRD) == 0) 
        {
            debug_print("sys_read: [FAIL] flag __SRD \n");
            yield (current_thread);
            goto fail;
        }

        nbytes = 0;

        // vazio? 
        // nao podemos ler.
        // acorda escritores e dorme.
        if (__file->socket_buffer_full == FALSE)
        { 
            debug_print("sys_read: [FAIL] can't read an empty buffer\n");
            //goto fail;
            
            debug_print("sys_read: WAKEUP WRITER\n");
            __file->_flags = 0;
            __file->_flags |= __SWR;                  // pode escrever
            do_thread_ready( __file->tid_waiting );   // acorda escritores. 
            __file->tid_waiting = -1;
            
                    // #bugbug
                    // Isso pode ser ruim pela natureza da chamada sys_read()
                    // que vem de uma syscall que nao salvou o contexto.
            
            if (__file->sync.block_on_read_empty == TRUE )
            {
                debug_print("sys_read: SLEEP READER\n");
                panic("sys_read: [DEBUG] Couldn't read socket. Buffer not full\n");

                __file->tid_waiting = current_thread;
                do_thread_waiting (current_thread);
                yield (current_thread);
                goto fail;
            }
            yield (current_thread);
            goto fail;
        }

        // cheio? le e acorda escritores.
        if (__file->socket_buffer_full == TRUE)
        {
            if( __file->_flags & __SRD )
            {
                debug_print ("sys_read: >>>> READ\n");
            
            
                // read!
                nbytes = (int) file_read_buffer ( 
                                   (file *) __file, 
                                   (char *) ubuf, 
                                   (int) count );
        
            if (nbytes <= 0){
                debug_print("sys_read: [FAIL] file_read_buffer fail when reading a socket \n");
                yield (current_thread);
                goto fail;
            }

            // ok
            if (nbytes > 0)
            {
                debug_print("sys_read: [DEBUG] lemos mais que 0 bytes em um socket.\n");
                __file->socket_buffer_full = FALSE;     // buffer vazio
                __file->_flags &= ~__SRD;                 //nao posso mais LER.            
                __file->_flags |= __SWR;                // pode escrever.
                
                
                debug_print("sys_read: WAKEUP WRITER\n");
                do_thread_ready( __file->tid_waiting ); // acorda escritores.
                __file->tid_waiting = -1;
                debug_print("sys_read:done\n");
                
                return (int) nbytes;                    // bytes escritos.
            }
            }
        } 

        panic ("sys_read: [FAIL] Unexpected error when reading socket\n \n");
    } 




    //
    // == Regular file ============================================
    //


    // ==== Regular file =======================
    // Read a regular file.
    // See: unistd.c
    // #todo Tem que retornar a quantidade de bytes lido.
    // #bugbug: Nem todos arquivos criados possuem essa flag configurada
    // apropriadamente ...estamos fazendo isso.
    
    // #hackhack
    // We will open all the other kind of object
    // with this IF right here.
    // We need to fix it in the open() routines
    // to give us the correct type.
    
    if ( __file->____object == ObjectTypeFile )
    { 
        //debug_print("sys_read: [DEBUG] Trying to read a regular file object\n");
        
        //Se não pode ler.
        if ( (__file->_flags & __SRD) == 0 )
        {
            debug_print("sys_read: [FLAGS] Can't read!\n");
        
            //Não conseguimos ler.
            //nada de errado, apenas espera.
            //do_thread_waiting (current_thread);
            //__file->tid_waiting = current_thread;
            //__file->_flags |= __SWR;  //pode escrever.
            //scheduler();
            return 0;
        }
   
        // Se puder ler:
        // + Call a function to read a regular file.
        // + Sinalize that another process can write.
        // #todo: wake the one that was waiting to write.

        if ( __file->_flags & __SRD )
        {     
            nbytes = (int) file_read_buffer ( (file *) __file, 
                               (char *) ubuf, (int) count );

            // Se conseguimos ler.
            if ( nbytes>0)
            {
                // ok to write.
                __file->_flags = __SWR;
        
                // #test
                // Acordar quem esperava por esse evento
                //do_thread_ready( __file->tid_waiting );
                return (int) nbytes;        
            }
        
            //Não conseguimos ler.
            //nada de errado, apenas espera.
            //do_thread_waiting (current_thread);
            //__file->tid_waiting = current_thread;
            //__file->_flags |= __SWR;  //pode escrever.
            //scheduler();
            return 0;
        }

    } //-- regular file.

    //pseudo terminal multiplexer.
    if ( __file->____object == ObjectTypePTMX )
    {
        printk ("sys_read: [TODO] trying to read a PTMX device file\n");
        refresh_screen();
        return 0;
    }

    // pty () pseudo terminal.
    if ( __file->____object == ObjectTypePTY )
    {
        printk ("sys_read: [TODO] trying to read a PTY device file\n");
        refresh_screen();
        return 0;
    }


    // file system
    if ( __file->____object == ObjectTypeFileSystem )
    {
        printk ("sys_read: [TODO] trying to read a file system\n");
        refresh_screen();
        return 0;
    }

    // See: pipe.c
    if ( __file->____object == ObjectTypePipe )
    {
        printk ("sys_read: [TODO] trying to read a pipe\n");
        return sys_read_pipe ( (int) fd, (char *)ubuf, (int) count ); 
    }

    // ...
    
    // ======================================================
    
    debug_print ("sys_read: [FAIL] Unknown object type\n");


    //
    // Fail!
    //
    
// #bugbug
// See manual for the error:
// https://www.gnu.org/software/libc/manual/html_node/I_002fO-Primitives.html
// http://man7.org/linux/man-pages/man2/read.2.html

// A intenção é que um erro seja representado por -1 e não por 0.
// Zero representará fim de arquivo. 

fail:

    // #debug
    debug_print ("sys_read: [FAIL] something is wrong!\n");
    // printf      ("sys_read: [FAIL] something is wrong!\n");
    refresh_screen();

    //bloqueando, autorizando a escrita e reescalonando.
    //do_thread_waiting (current_thread);
    //__file->tid_waiting = current_thread;
    //__file->_flags |= __SWR;  //pode escrever      
    //scheduler();  //#bugbug: Isso é um teste  

    return (int) (-1); // fail !!! something is wrong!!!
}


/*
 ****************************
 * sys_write:
 *     Implemantation of write() for libc.
 *
 */

// service 19.
// Copiar um buffer para um arquivo dado o descritor.
// Aqui devemos selecionar o dispositivo à escrever.
// See:
// https://github.com/zavg/linux-0.01/blob/master/fs/read_write.c
// https://linux.die.net/man/2/write
// ...
// #todo
// We need to call one subfunction for each different kind of file 
// intead of implementing an internal sub-routine.

// #todo
// Isso deveria ser apenas um wrapper,
// chamando as rotinas apropriadas para cada tipo 
// de arquivo.

// OUT:
// 0 = Couldn't read.
// -1 = Error.

int sys_write (unsigned int fd, char *ubuf, int count)
{
    // #todo
    // Copiar deve ser uma opcao e nao uma regra!
    // Precisamos de uma flag para copyonwrite.
    
    // atençao
    // Podemos escrever num socket que nao eh o privado!!!
    // existe a possibilidade de o processo atual estar 
    // escrevendo em um socket que pertence a outro processo.
    // mas que por causa da conexao possui o fd dele registrado
    // em sua estrutura.
    // Entao o fd passado por argumento nao precisa ser o mesmo
    // do socket privado do processo. Pois poderemos estar
    // escrevendo em outro socket que nao o privado.

    struct process_d  *__P;
    
    file *__file;

    
    struct socket_d  *s1;
    //struct socket_d  *s2;
    
    int nbytes=0;
    int ubuf_len=0;

    size_t ncopy=0;

    // check arguments.
    // fd, ubuf, count.
    // todo: Check validation for the memory region. 

    //if (fd<0 || fd>31){
    //    debug_print ("sys_write: fd\n");  goto fail;
    //}

    // fd.
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_write: fd\n");
        printf     ("sys_write: fd\n");
        return (int) (-EINVAL);
    }

    if ( (char *) ubuf == (char *) 0 ){
        debug_print ("sys_write: invalid ubuf address\n");  goto fail;
    }

    // count.
    
    if ( count < 0 ){ 
        debug_print ("sys_read: count < 0\n");
        return -1; 
    }
    
    if ( count == 0 ){ 
        debug_print ("sys_read: count 0\n");
        return 0; 
    }


    //
    // Size of the buffer.
    //

    // len
    ubuf_len = strlen( (const char *) ubuf );
    
    //Se a quantidade desejada é maior que o buffer disponível.
    if(count > ubuf_len){
        //debug_print("sys_write: [FIXME] count too long!\n");
    }

    // se o buffer é maior que a quantidade desejada, 
    //então não temos problemas
    if (ubuf_len > count ){
        ubuf_len = count;
        //debug_print ("sys_write: [FIXME] Ajusting ubuf_len\n");
    }

    // #debug: 
    // limits
    // Um socket tem o tamanho de BUFSIZ.
    
    if (ubuf_len > 512 )
    {
        ubuf_len = 512;
        debug_print ("sys_write: [FIXME] Ajusting ubuf_len to 512\n");
    }

    //
    // Process pointer.
    //

    __P = (struct process_d *) processList[current_process];

    if ( (void *) __P == NULL )
    {
        debug_print ("sys_write: __P\n");
        panic       ("sys_write: __P\n");
    }

    //
    // __file.
    //

    __file = (file *) __P->Objects[fd]; 
    
    if ( (void *) __file == NULL )
    {
        debug_print ("sys_write: __file not open\n");
        printf      ("sys_write: __file not open\n");
        goto fail;
    }


    //while (TRUE){
    //    if ( __file->sync.lock == FALSE ){ break; }
    //     yield (current_thread); 
    //};

    if ( __file->sync.can_write != TRUE )
    {
        debug_print ("sys_write: [PERMISSION] Can NOT write the file\n");
        printf      ("sys_write: [PERMISSION] Can NOT write the file\n");
        goto fail; 
    }


    /*
    // #todo
    // ainda nao inicializamos esse elemento.
    if( __file->is_writable == FALSE )
    {
        debug_print ("sys_write: Not writable\n");
        return -1;
    }
    */

    //#todo: Create thie element in the structure.
    //if( __file->is_directory == TRUE ){}

//=======================================================

    // escrevendo no stdin
    if ( __file->_file == 0 )
    {
        nbytes = 0;
        nbytes = (int) file_write_buffer ( 
                           (file *) PS2KeyboardDeviceTTY->_rbuffer, 
                           (char *) ubuf, 
                           (int) count );
                           
        if (nbytes>0)
            PS2KeyboardDeviceTTY->_rbuffer->_flags |= __SRD;
        
        return nbytes;
    }


    // switch
    // is_char_dev?     read_char(...)
    // is_block_dev?    read_block(...)
    // is_

    //
    // == stdout ===================================
    //
    
    // Primeiro vamos checar se eh o arquivo numero um do processo atual.
    // Depois vamos checar se ele eh do tipo console virtual,
    // como deve ser.
    // Devemos escrever no console virtual atual,
    // e nao em qualquer um.

    // ==== Console ===============================
    // >> Console.
    // Se o descritor usado por write() for de um arquivo
    // do tipo console, escreveremos no console 0.
    // IN: console number, buffer, size.

    if ( __file->_file == 1 )
    {
        if ( __file->____object != ObjectTypeVirtualConsole ){
            panic("sys_write: Wrong object for stdout");
        }
        return (int) console_write ( 
                         (int) fg_console, 
                         (const void *) ubuf, 
                         (size_t) count );
    }


    //
    // == Sockets ===============================================
    //
    
    ncopy = count;
    
    // ==== Socket ===============================
    // Descobrindo o soquete que devemos copiar.
    // Se o arquivo é do tipo socket, então devemos
    // sabar onde está o buffer.
    // #todo: Talvez podemos chamar a função socket_write().
    // #todo: Lidar com a questao do copiar, pois
    // accept deve retornar o fd do cliente, para que o servidor
    // construa uma lista de clientes.
    // Entao copiar sera uma opçao, gerenciada por uma flag.
    
    // #bugbug
    // Nao podemos fazer a copia se os dois sockets 
    // estiverem com a conexao pendente.

    if ( __file->____object == ObjectTypeSocket )
    {
        //debug_print("sys_write: [DEBUG] Trying to write on a socket object \n");
        
        nbytes = 0;

        // #test
        // checking the synchronization struct
        //if( __file->sync.sender != current_process )
        //{
        //    printf("sys_write: sender %d current %d #debug\n",__file->sync.sender, current_process);
        //    refresh_screen();
        //    panic("sys_write: __file->sync.sender\n");
        //}

        // not writing yet
        if ((__file->_flags & __SWR) == 0) 
        {
            debug_print("sys_write: [FAIL] flag __SWR \n");
            yield (current_thread);
            goto fail;
        }
        
        // cheio? 
        // Nao podemos escrever.
        // Acorde os leitores para esvaziar.
        if ( __file->socket_buffer_full == TRUE )
        {
            debug_print("sys_write: [FAIL] can't write on a full buffer\n");

            debug_print("sys_write: WAKEUP READER\n");
            __file->_flags = 0;
            __file->_flags |= __SRD;                 // pode ler.
            do_thread_ready( __file->tid_waiting );  // acorda leitores
            __file->tid_waiting = -1;


            if ( __file->sync.block_on_write_full == TRUE )
            {
                 debug_print("sys_write: SLEEP WRITER\n");
                 __file->tid_waiting = current_thread;
                 do_thread_waiting(current_thread);
                 yield (current_thread);
                 goto fail;
            }
            yield (current_thread); 
            goto fail;
        }

        // vazio? escreva e acorde os leitores.
        if ( __file->socket_buffer_full == FALSE )
        {
            
            if( __file->_flags & __SWR )
            {
                debug_print ("sys_write: >>>> WRITE\n");
                __file->_flags = 0;
            
                // Write in the socket buffer.
                nbytes = (int) file_write_buffer ( 
                                   (file *) __file, 
                                   (char *) ubuf, 
                                   (int) count );

                // fail
                if (nbytes <= 0){
                    debug_print("sys_write: [FAIL] file_write_buffer couldn't write on socket \n");
                    yield (current_thread);
                    goto fail;
                }

                // ok, write funcionou.
                if (nbytes>0)
                { 
                    
                    
                    debug_print("sys_write: WAKEUP READER\n");
                    __file->socket_buffer_full = TRUE;       // buffer cheio
                    __file->_flags &= ~__SWR;                // nao posso mais ESCREVER.            
                    __file->_flags |= __SRD;                 // pode ler 
                    do_thread_ready( __file->tid_waiting );  // acorda leitores
                    __file->tid_waiting = -1;
                
                    // #bugbug
                    // Isso pode ser ruim pela natureza da chamada sys_write()
                    // que vem de uma syscall que nao salvou o contexto.
                    
                    if ( __file->sync.block_on_write == TRUE )
                    {
                        debug_print("sys_write: SLEEP WRITER\n");
                        __file->tid_waiting = current_thread;
                        do_thread_waiting(current_thread);
                    }
                    
                    // #bugbug: test ...
                    //  impedir que eu mesmo me leia.
                    yield (current_thread);
                    //yield (current_thread);
                    //yield (current_thread);
                    //yield (current_thread);
                    
                    return nbytes;                           // bytes written
                }
            }
        }
        
        panic("sys_write: [FAIL] unexpected error when writing on socket.\n");         
    }  //socket file 




    //
    // Arquivos normais (regular)
    //
    
    // == Regular file =========================================
    

    // Tem que retonar o tanto de bytes escritos.
    // Escreve em uma stream uma certa quantidade de chars.

    if ( __file->____object == ObjectTypeFile )
    {
        //debug_print("sys_write: [DEBUG] Trying to write on a regular file object \n");
        
        //can't write!
        if ( (__file->_flags & __SWR) == 0)
        {
             debug_print("sys_write: [FLAGS] Can't write!\n");
             // Não conseguimos escrever ... 
             // nada de errado, apenas esperaremos.
             //do_thread_waiting (current_thread);
             //__file->tid_waiting = current_thread;
             //__file->_flags |= __SWR;  //pode escrever.
             //scheduler();
             return 0;
        }

        //#todo: ainda não colocamos essa flag na criação do arquivo.
        if (__file->_flags & __SWR)
        {
            // Regular file.
            nbytes = (int) file_write_buffer ( (file *) __file, 
                           (char *) ubuf, (int) count );

            // Avisa que o arquivo não está mais no modo escrita,
            // que agora pode ler.

            // Adiciona o bit que permite a leitura.
            // Assim o servidor pode ler o request.
            // #todo: wait on write.
            // #bugbug:
            // A questão é que se o cliente está esperando por resposta,
            // então ele lerá também.
            // Atualizamos a flag e acordamos quem esperava pelo evento.

            if (nbytes>0)
            { 
                __file->_flags |= __SRD;
                do_thread_ready( __file->tid_waiting );
                return (int) nbytes;
            }

            //suspenso.
            // Não conseguimos escrever ... 
            // nada de errado, apenas esperaremos.
            //do_thread_waiting (current_thread);
            //__file->tid_waiting = current_thread;
            //__file->_flags |= __SWR;  //pode escrever.
            //scheduler();
        
            debug_print ("sys_write: [FAIL] file_write_buffer fail!\n");
            return 0;
        }
 
        debug_print ("sys_write: [FAIL] Something is wrong!\n");
    } //regular file.

    //======================================================

    //pseudo terminal multiplexer.
    if ( __file->____object == ObjectTypePTMX )
    {
        printk ("sys_write: [TODO] trying to write a PTMX device file\n");
        refresh_screen();
        return 0;
    }

    // pty () pseudo terminal.
    if ( __file->____object == ObjectTypePTY )
    {
        printk ("sys_write: [TODO] trying to write a PTY device file\n");
        refresh_screen();
        return 0;
    }


    // file system
    if ( __file->____object == ObjectTypeFileSystem )
    {
        printk ("sys_write: [TODO] trying to write a file system\n");
        refresh_screen();
        return 0;
    }
    
    // See: pipe.c
    if ( __file->____object == ObjectTypePipe )
    {
        printk ("sys_write: [TODO] trying to write a pipe\n");
        return sys_write_pipe ( (int) fd, (char *)ubuf, (int) count ); 
    }

    // ...

    //==============================================

    debug_print ("sys_write: [FAIL] Unknown object type!\n");

fail:

    // #debug
    debug_print ("sys_write: [FAIL] Something is wrong!\n");
    // printf      ("sys_write: [FAIL] something is wrong!\n");

fail2:
    refresh_screen();

    // Não conseguimos escrever ... 
    // Estamos com problemas 
    //do_thread_waiting (current_thread);
    //__file->tid_waiting = current_thread;
    //__file->_flags |= __SWR;  //pode escrever.
    //scheduler();
    return (int) (-1);  // fail. something is wrong!!!!
}


/*
 *****************************************************
 * sys_create_process:
 *     Create process system interface.
 */

        // 73 - Create process.
        // ??
        // #todo: enviar os argumentos via buffer.
        // #todo: Ok, nesse momento, precisamos saber qual é o 
        // processo pai do processo que iremos criar. Esse deve ser 
        // o processo atual ...  
        // PPID = 0. Nesse momento todo processo criado será filho 
        // do processo número 0. mas não é verdade. 
        // @todo: Precisamos que o aplicativo em user mode nos passe 
        // o número do processo pai, ou o proprio kernel identifica 
        // qual é o processo atual e determina que ele será o 
        // processo pai. 

// Service 73

void *sys_create_process ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long res1,          //nothing
    unsigned long priority, 
    int ppid, 
    char *name,
    unsigned long iopl ) 
{

    // #bugbug
    // Lembrando que quando entramos nesse serviço (73)
    // estavamos usando o diretorio de paginas do processo.


    // #todo: 
    // Esse ultimo argumento eh o endereço do diretorio de paginas.
    // Nao precisamos clonar novamente.
     

   //#bugbug
   // o argumento directory_address está errado.
   // deletar esse argumento. outra coisa no lugar.
   // o argumento init_eip também ta errado.

    struct process_d  *p;
    struct thread_d   *t;
    
    
   //
   // Carregar num endereço virtual temporário ..
   // converte o endereço virtual em físico, para
   // remapearmos depois.
   // Mas antes precisamos saber o tamanho da imagem.
   //
    
    unsigned long tmp_va = 0;
    unsigned long tmp_pa = 0;
        

    int fileret = -1;
    
    

    debug_print ("sys_create_process: [FIXME] It's a work in progress\n");


    //
    // == #bugbug ===============================================
    //
   
    // This is a virtual address using the kernel page directory!

    // #bugbug
    // (40 * 4096)  160KB  ??
    
    unsigned long tmp_image_size = (40 * 4096);   
    tmp_va = (unsigned long) allocPages(40);   // 40 pages;


    if ( tmp_va == 0 )
        panic ("sys_create_process: [FAIL] tmp_va");
            

    //
    // == Physical address ==============================
    //

    tmp_pa = (unsigned long) virtual_to_physical ( tmp_va, 
                                 gKernelPageDirectoryAddress ); 

    if ( tmp_pa == 0 )
        panic ("sys_create_process: [FAIL] tmp_pa");
 

    // loading image.
    // Loading the image in the virtual address of the 
    // kernel's page directory.
    // Com base no endereço fisico criaremos uma pagetable com
    // endereço virtual começando em 0x400000 como desejado.
    
    //printf ("sys_create_process: Loading the image in the address %x\n", tmp_va);
    
    
    // Loading from root dir
    // 512 entries.

    fileret = (unsigned long) fsLoadFile ( 
                                  VOLUME1_FAT_ADDRESS, 
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  FAT16_ROOT_ENTRIES, //#bugbug: Number of entries.
                                  name, 
                                  (unsigned long) tmp_va,      // virtual base address
                                  tmp_image_size );            // image size


    // Se não encontramos a imagem
    if ( fileret != 0 )
    {
        //fileret = (unsigned long) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
        //                              VOLUME1_ROOTDIR_ADDRESS, 
        //                              32, //#bugbug: Number of entries.
        //                              name, 
        //                              (unsigned long) tmp_va, tmp_size );

        
        //if ( fileret != 0 ){
            panic ("sys_create_process: [FILE] fileret. Couldn't load the image \n");
        //}
    }


    //
    // == Create process! ===================================
    //
 
    // Criamos um processo no endereço virtual 0x00400000
    // de seu proprio diretorio de paginas, que eh um clone do
    // diretorio do kernel.
    // See: ps/process.c

    p = (void *) create_process ( 
                     room, desktop, window, 
                     (unsigned long) 0x00400000, //base
                     priority, 
                     ppid, 
                     name, 
                     RING3, 
                     (unsigned long ) CloneKernelPageDirectory() );

    if ( (void *) p == NULL ){
        panic ("sys_create_process: [FAIL] p\n");
    }else{
        fs_initialize_process_cwd ( p->pid, "/" );
    };


     //
     // == page table =========================
     //
    
     // #bugbug
     // Precisa alocar um endereço físico para a nova imagem
     // mapear esse endereço em 0x400000 do diretorio do processo que
     // acabamos de criar.
     
     // Salvando o endereço fisico.
     p->ImagePA = tmp_pa;

     // Criando uma pagetable
     // #bugbug: ?? Nesse momento esse endereço virtual eh valido??
     // Estamos usando qual diretorio de paginas ... ??
     
     // #bugbug
     // Essa funcao nao sabera onde sta o diretorio de paginas
     // pois esse argumento esta errado.
     
     // Isso fara com que o endereço 0x400000 aponte para o 
     // endereço fisico de onde carregamos a imagem.
     
     CreatePageTable ( 
         (unsigned long) p->DirectoryVA, 
         ENTRY_USERMODE_PAGES, 
         p->ImagePA );
 
     // Com base no endereço físico, usamos a função acima
     // para atribuírmos um novo endereço virtual para a imagem.
     p->Image = 0x400000; // com base na entrada escolhida (ENTRY_USERMODE_PAGES)            
 

    //
    // == Thread ===================================
    //

	// Create thread.
    t = (struct thread_d *) create_thread ( 
                                room, desktop, window, 
                                0x00401000,    //entrypoint 
                                priority, 
                                p->pid, 
                                "control-thread" ); 

    if ( (void *) t == NULL ){
        debug_print ("sys_create_process: t fail\n");
        goto fail;
    }

    // Marca ela como thread de controle do processo.
    p->control = t;

    SelectForExecution ( (struct thread_d *) t );

    //ok
    debug_print ("sys_create_process: Done\n");
    printf      ("sys_create_process: Done\n");
    refresh_screen();
    return (struct process_d *) p;

fail:
    printf ("sys_create_process: [FAIL]\n");
    refresh_screen();
    return NULL;
}



// 85 
// Get PID of the current process.
int sys_getpid (void)
{
    return (int) current_process;
}


// 81
// Get the PID of the father.
int sys_getppid (void){

    struct process_d *p;
    pid_t pid = -1;


    pid = (int) current_process;

    if ( pid >= 0 && pid < PROCESS_COUNT_MAX )
    {
        p = (void *) processList[pid];

        if ( (void *) p == NULL ){ return (int) -1; }

        if ( p->used != 1 || p->magic != 1234 ){ return (int) -1; }

        return (int) p->ppid;
    }

    return (int) (-1);
}


/*
 *********************************************
 * sys_fork:
 *     
 */

// #todo 

int sys_fork (void)
{
    debug_print ("sys_fork: \n");

    // #todo
    // We need to change this name. fork() will be used only on ring3.
    // See: gramado/kernel/middle/sysmk/ps/action/threadi.c

    return (int) kfork();
}



//exit process.
//serviço do sistema.

void sys_exit_process ( int pid, int code ){

    if ( pid < 0 ){
        //todo: message
        return;
    }

    exit_process ( pid, code );
}




/*
 *********************************************************
 * sys_create_thread:
 *     Create thread system interface.
 */

    // 72 - Create thread.
    // #todo: 
    // Enviar os argumentos via buffer.


void *sys_create_thread ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long init_eip, 
    unsigned long priority, 
    int ppid, 
    char *name )
{
    struct thread_d *Thread;


    debug_print ("sys_create_thread:\n");

    // #todo:
    // Filtros, para ponteiros NULL.
    
    if ( init_eip == 0 ){
        debug_print ("sys_create_thread: [FAIL] init_eip\n");
        return NULL;
    }


    // Create thread.
    
    Thread = (struct thread_d *) create_thread ( room, desktop, window, 
                        init_eip, priority, ppid, name ); 

    if ( (void *) Thread == NULL ){
        debug_print ("sys_create_thread: [FAIL] Thread\n");
        return NULL;
    }

    SelectForExecution ( (struct thread_d *) Thread );

    return (struct thread_d *) Thread;
}



//exit thread.
void sys_exit_thread (int tid){

    if ( tid < 0 ){
        //todo: message
        return;
    }

    exit_thread (tid);
}



// 90 - Coletor de threads Zombie. 
// (a tarefa idle pode chamar isso.)
void sys_dead_thread_collector (void)
{
    dead_thread_collector ();
}


/*
 * sys_vsync:
 *     Sincroniza o retraço vertical do monitor.
 */

void sys_vsync (void)
{
    hal_vsync ();
}


/* 
 **********************************
 * sys_showkernelinfo:
 *     Show kernel info. 
 */

void sys_showkernelinfo (void)
{
    KiInformation ();
}




/*
 * sys_showpciinfo:
 *     Mostra informações encontradas na interface PCI.
 */

int sys_showpciinfo (void)
{
    return (int) hal_showpciinfo ();
}

 
/*
 ************************************
 * sys_reboot:
 *     Reboot, Serviço do sistema.
 *     Chamando uma rotina interna de reboot do sistema.
 */


// The service 110.
// It's called by gde_serv.c.
// The higher level routine for reboot.
// It's a wrapper, an interface.

void sys_reboot (void)
{
    debug_print("sys_reboot:\n");

    // FAT cache.
    // This is the FAT cache for the system disk.
    // The boot partition.
    
    // Message
    if(fat_cache_saved==CACHE_NOT_SAVED)
        debug_print("sys_reboot: CACHE_NOT_SAVED\n");

    
    debug_print("sys_reboot: Saving FAT cache\n");
    fs_save_fat(VOLUME1_FAT_ADDRESS,VOLUME1_FAT_LBA,246);


    //
    // Reboot!
    //

    debug_print("sys_reboot: Rebooting...\n");
    reboot();

    panic("sys_reboot:");
}


/*
 **********************************
 * sys_shutdown:
 *     Chama uma rotina interna para desligar a máquina.
 */

void sys_shutdown (void)
{
    debug_print("sys_shutdown: [TODO]\n");
    hal_shutdown();
}


// 178
unsigned long sys_get_file_size ( char *path ){

    unsigned long Size=0;


    if ( (void*) path == NULL ){
        debug_print("sys_get_file_size: [FAIL] path\n");
        return 0;
    }

    if ( *path == 0 ){
        debug_print("sys_get_file_size: [FAIL] *path\n");
        return 0;
    }


    //taskswitch_lock();
    //scheduler_lock();
    
    Size = (unsigned long) fsRootDirGetFileSize ( (unsigned char *) path ); 
    
    //scheduler_unlock();
    //taskswitch_unlock();
    
    return (unsigned long) Size; 
}


// Usada por vários serviços de debug.
// Usada para debug.

void sys_show_system_info ( int n ){

    if (n<0){
        debug_print("sys_show_system_info: [FAIL] n\n");
        return;
    }

    switch (n){

        case 1:  disk_show_info();        break;
        case 2:  volume_show_info();      break;
        case 3:  memoryShowMemoryInfo();  break;
        
        case 4:
            systemShowDevicesInfo();
            pciInfo();
            break;
            
        case 5:  
            KiInformation(); 
            break;
        
        // See: detect.c
        case 6:
            show_cpu_info();
            break;
            
        // ...
    };

    refresh_screen();
}


//
// End
//





