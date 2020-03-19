/*
 * File: unistd.c  
 * 
 */


#include <kernel.h>



/*
 * file_write: 
 *     Escreve no arquivo uma certa quantidade de caracteres de uma 
 *     dada string.
 */

int file_write ( file *f, char *string, int len ){

    int i;
    char *p;

  
    p = string;

  
    if ( (void *) f == NULL ){
        printf ("file_write: file\n");
        refresh_screen();
        return EOF; 
    }

    if ( (void *) p == NULL ){
        printf ("file_write: p\n");
        refresh_screen();
        return EOF; 
    }

    //não sei se devemos
    //rewind(f);
        
        
    /*
    for (i=0; i<len; i++)
    {
        fputc ( ( int ) *p, f );
        p++;
    };
    */
    
    memcpy ( (void *) f->_base, (const void *) string, len ); 

    return len;
}


// File read.
int file_read ( file *f, char *buffer, int len ){

    int i;
    char *p;

  
    p = buffer;
  
  
    // file
    if ( (void *) f == NULL ){
        printf ("file_read: file\n");
        refresh_screen();
        return EOF; 
    }

    // buffer
    if ( (void *) p == NULL ){
        printf ("file_read: p\n");
        refresh_screen();
        return EOF; 
    }


    //rewind(f);


    //printf ("unistd_file_read: putting %d bytes into the buffer.\n",len);
    //refresh_screen();
 
    memcpy ( (void *) buffer, (const void *) f->_base, len ); 

 
    //Essa rotina falhou.
    //faltvez fgetc esta falhando.
    /*
    int ch = 0;
    for (i=0; i<len; i++)
    {
        ch = (int) fgetc (f);
        *p = (char) ch;
        p++;
    };
    */

    //printf ("file_read: >> %s \n", buffer); //não funciona.
    //printf ("file_read: >>_base %s \n", &f->_base[0]); //funciona.
    //refresh_screen();

    // retorna o número bytes lidos.

    return len;
}







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










