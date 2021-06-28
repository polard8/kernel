


#include <kernel.h> 


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
 * file_write_buffer: 
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

// Exit thread.
void sys_exit_thread (int tid)
{
    if ( tid < 0 ){
        //todo: message
        return;
    }

    exit_thread (tid);
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

// 178
unsigned long sys_get_file_size ( char *path )
{
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

// 85 
// Get PID of the current process.
int sys_getpid (void)
{
    return (int) current_process;
}

// 81
// Get the PID of the father.
int sys_getppid (void)
{
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
    hal_reboot();

    panic("sys_reboot:");
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

// Usada por vários serviços de debug.
// Usada para debug.

void sys_show_system_info ( int n ){

    if (n<0){
        debug_print("sys_show_system_info: [FAIL] n\n");
        return;
    }

    switch (n){

        case 1:  
            disk_show_info();        
            break;
        case 2:  
            volume_show_info();      
            break;
        case 3:  
            //memoryShowMemoryInfo();  
            break;
        
        case 4:
            //systemShowDevicesInfo();
            //pciInfo();
            break;
            
        case 5:  
            //KiInformation(); 
            break;
        
        // See: detect.c
        case 6:
            //show_cpu_info();
            break;
            
        // ...
    };

    refresh_screen();
}

/*
 * sys_vsync:
 *     Sincroniza o retraço vertical do monitor.
 */

void sys_vsync(void)
{
    hal_vsync();
}






























































 

