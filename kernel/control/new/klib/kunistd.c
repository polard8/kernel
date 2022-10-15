
// kunistd.c

#include <kernel.h>    


// Host name
// pegando host name
// faremos igual fizemos com usuário.
// suporte a rotina da libc.
// #todo: How many bytes we can copy into the buffer.
// We need a parameter for that.
int __gethostname (char *buffer){

    char *hostname_buffer = (char *) buffer;

// Invalid buffer
    if( (void*) buffer == NULL )
        return -1;


//Estrutura default para informações sobre o host.
//host.h

    if ( (void *) HostInfo == NULL ){
        printf ("__gethostname: HostInfo\n");
        //refresh_screen();
        return (int) -1;
    }

// Copy 64 bytes.
    strcpy ( 
        hostname_buffer, 
        (const char *) HostInfo->__hostname );

    return (int) HostInfo->hostName_len;
}


// Host name
// #todo
// configurando o hostname.
// do mesmo jeito que configuramos o username,
// só que em estruturas diferentes
int __sethostname (const char *new_hostname)
{
    size_t StringLen=0;


    if( (void*) new_hostname == NULL )
        return -1;

    if( *new_hostname == 0 )
        return -1;

    StringLen = (size_t) strlen (new_hostname);
    StringLen = (size_t) (StringLen + 1);


//
// Estrutura HostInfo em host.h (network)
//

    if ( (void *) HostInfo == NULL ){
        printf ("__sethostname: HostInfo\n");
        return (int) -1;
    }


    HostInfo->hostName_len = (size_t) StringLen;
    // ...

// Copy 64 bytes.

        strcpy ( 
            HostInfo->__hostname, 
            (const char *) new_hostname );

    return 0;
}


long fpathconf (int fildes, int name)
{
    debug_print("fpathconf: [TODO]\n");
    return -1;
}


long pathconf (const char *pathname, int name)
{
    debug_print("pathconf: [TODO]\n");    
    return -1;
} 


// #todo:
// IN: ??
// OUT: ??
off_t sys_lseek (int fd, off_t offset, int whence)
{
    file *f;
    struct process_d *p;

    debug_print("sys_lseek: [WORK IN PROGRESS]\n");


    if (fd<0 || fd >= 32)
    {
        return (off_t) (-EBADF);
    }

//#todo
    //if(offset<0)
        //return (off_t) (-EINVAL);

// Process

    pid_t current_process = (pid_t) get_current_process();
    
    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_lseek: p\n");
        return -1;
    }

//#todo
//validation
    

// File

    f = (file *) p->Objects[fd];
    
    if ( (void *) f == NULL ){
        debug_print("sys_lseek: f\n");
        return -1; 
    }

//#todo
//validation

// fseek
// See: kstdio.c
    k_fseek ( (file *) f, (long) offset, (int) whence );

    return (off_t) ( f->_p - f->_base ); 
}



//
// End.
//

