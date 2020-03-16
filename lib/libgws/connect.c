


   // Os cpodigos da libgws vão precisar disso 
   // pra se conectarem com o Window Server. gws
   
   
   
// libcore 
// #todo: tem coisa que tem que implementar na libcore.
// #atenção: não usaremos a libc03.
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>


//#bugbug
//#include <netdb.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>





// OUT: 1 = Ok.  0 = fail.
int connect_with_ws (void)
{
	return -1;
	

    int client_fd = -1;
    
    // cria o soquete.
    // AF_GRAMADO
    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("libgws-connect_init: Couldn't create socket\n");
    }

       
    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';    
    
     
    int connect_status = -1;
    
    
    connect_status = connect ( client_fd, (struct sockaddr *) &addr, sizeof(addr) );
    
    if ( connect_status < 0 ){ 
        printf ("libgws-connect_init: Connection Failed \n"); 
        return -1; 
    }    
    
    return (int) connect_status;
    
    
    // read: suspenso.
    /*

    char __buffer[32];
    int n=-1;

    while(1){

        n = read (client_fd, __buffer, sizeof(__buffer));

        if(n>0)
        {
            //break;
            printf ("libgws-connect_init: Received: %s \n",__buffer);            
        }
    }

    printf ("libgws-connect_init: Received: %s \n",__buffer);
    
    //send(client_fd , hello , strlen(hello) , 0 ); 
    
    return (int) -1;
    
    */
}







