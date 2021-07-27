

#include <kernel.h>    



// Host name
// pegando host name
// faremos igual fizemos com usuário.
// suporte a rotina da libc.
int __gethostname (char *buffer){

    char *hostname_buffer = (char *) buffer;

	//Estrutura default para informações sobre o host.
	//host.h

    if ( (void *) HostInfo == NULL ){
        printf ("__gethostname: HostInfo\n");
        //refresh_screen();
        return (int) -1;
 
    }else{

        //64 bytes
        strcpy ( hostname_buffer, (const char *) HostInfo->__hostname );
        
        return (int) HostInfo->hostName_len;
    };

    //fail
    return (int) -1;
}

// Host name
// #todo
// configurando o hostname.
// do mesmo jeito que configuramos o username,
// só que em estruturas diferentes
int __sethostname (const char *new_hostname){

    //
    // Estrtutura HostInfo em host.h (network)
    //

    if ( (void *) HostInfo == NULL ){
        printf ("__sethostname: HostInfo\n");
        return (int) -1;
    }else{

        HostInfo->hostName_len = (size_t) strlen (new_hostname) + 1;
        
        //64 bytes
        strcpy ( HostInfo->__hostname, (const char *) new_hostname);

        return 0;
    };

    //fail
    return (int) -1;
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
// OUT: ??
off_t sys_lseek (int fd, off_t offset, int whence)
{
    file *f;    
    struct process_d *p;


    debug_print("sys_lseek: [WORK IN PROGRESS]\n");


    if (fd<0 || fd >= 32){
        debug_print("sys_lseek: fd\n");
        return -1; 
    }
    
    //process
    
    p = (struct process_d *) processList[current_process];
    
    if ( (void *) p == NULL ){
        debug_print("sys_lseek: p\n");
        return -1;
    }

    //#todo
    //validation
    
    
    f = (file *) p->Objects[fd];
    
    if ( (void *) f == NULL ){
        debug_print("sys_lseek: f\n");
        return -1; 
    }
    
    // See: kstdio.c
    k_fseek ( (file *) f, (long) offset, (int) whence );

    return (off_t) ( f->_p - f->_base ); 
}



//
// End.
//










