


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

//libgws
#include "include/connect.h"  
#include "include/gws.h"  



int __gws__desktop__id;
int __ws__pid;
int ____gws_connected = 0;

// for read and write functions.
int ____gws_client_fd;         //socket fd
char ____gws_io_buffer[512];   //buffer


// OUT: 1 = Ok.  0 = fail.
int gws_connect (void){

    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';    
    
    //
    // socket
    //
    
    // #debug
    printf ("libgws-gws_connect: Creating socket ...\n");
    
    
    // cria o soquete.
    // AF_GRAMADO
    ____gws_client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( ____gws_client_fd < 0 ){
       gws_debug_print ("libgws-gws_connect: Couldn't create socket\n");
       return -1;
    }

       
    //
    // connect
    //   
    
    ____gws_connected = connect ( ____gws_client_fd, 
                            (struct sockaddr *) &addr, 
                            sizeof(addr) );
    
    if ( ____gws_connected < 0 ){ 
        gws_debug_print ("libgws-gws_connect: Connection Failed \n"); 
        return -1; 
    }    



    return (int) ____gws_connected;
}



int gws_get_connect_status(void){
    return ____gws_connected;
}




int gws_get_client_fd(void){

    return ____gws_client_fd;
}



int gws_get_desktop_id(void){
    return __gws__desktop__id;
}



int gws_initialize_connection(void)
{
    // Pega o id do desktop atual.
    // ?? Ou o qual o processo pertence ??
    __gws__desktop__id = (int) gws_system_call (519,0,0,0);
   
    
    // Get ws PID for a given desktop
    __ws__pid = (int) gws_system_call ( 512,
                         (unsigned long) __gws__desktop__id,
                         (unsigned long) __gws__desktop__id,
                         (unsigned long) __gws__desktop__id );    
        
        
    
    if (__ws__pid<0)
        return -1;
        
        
        // Send message.
        // Envia uma mensagem pedindo para o ws emitir um hello!
        // msg = 1000;

        //vamos criar uma chamada semelhante a essa.

        // IN: PID, window, msg, long1, long2
        gws_send_message_to_process ( __ws__pid, 
            NULL, 1000, 0, 0 );  
    

        // put some pixel in this position.
        gws_send_message_to_process ( __ws__pid, 
            NULL, 2000, 40, 40 );  

        // refresh screen
        gws_send_message_to_process ( __ws__pid, 
            NULL, 2020, 0, 0 );     
        
    return 0;
}


unsigned long gws_get_message_buffer(void){

    return (unsigned long) &____gws_io_buffer[0];   
}




