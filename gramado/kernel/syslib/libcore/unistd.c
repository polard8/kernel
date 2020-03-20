/*
 * File: unistd.c  
 * 
 */


#include <kernel.h>



long fpathconf (int fildes, int name){
    return -1;
}

long pathconf (const char *pathname, int name){
    return -1;
} 


//pegando host name
//faremos igual fizemos com usuário.
//suporte a rotina da libc.
int __gethostname (char *buffer){


    char *hostname_buffer = (char *) buffer;
 

	//Estrutura default para informações sobre o host.
	//host.h

    if ( (void *) HostInfo == NULL )
    {
        printf ("__gethostname: HostInfo\n");
        return (int) -1;
    }else{

                 //64 bytes
        strcpy ( hostname_buffer, (const char *) HostInfo->__hostname );
        
        return (int) HostInfo->hostName_len;
    };


    return (int) -1;
}


//#todo
// configurando o hostname.
//do mesmo jeito que configuramos o username,
//só que em estruturas diferentes
int __sethostname (const char *new_hostname){

    //
    // Estrtutura HostInfo em host.h (network)
    //


    if ( (void *) HostInfo == NULL )
    {
        printf ("__sethostname: HostInfo\n");
        return (int) -1;
    }else{

        HostInfo->hostName_len = (size_t) strlen (new_hostname) + 1;
        
        //64 bytes
        strcpy ( HostInfo->__hostname, (const char *) new_hostname);

		return 0;
	};


    return (int) -1;
}










