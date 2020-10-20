/*
 * File: main.c
 *
 *    Client side application for Gramado Window Server.
 *    Using socket to connect with gws.
 *    AF_GRAMADO family.
 *
 * History:
 *     2020 - Created by Fred Nora.
 */



// tutorial example taken from. 
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
 
/*
    To make a process a TCP server, you need to follow the steps given below −

    Create a socket with the socket() system call.

    Bind the socket to an address using the bind() system call. 
    For a server socket on the Internet, an address consists of a 
    port number on the host machine.

    Listen for connections with the listen() system call.

    Accept a connection with the accept() system call. 
    This call typically blocks until a client connects with the server.

    Send and receive data using the read() and write() system calls.
*/ 

// See:
// https://wiki.osdev.org/Message_Passing_Tutorial
// https://wiki.osdev.org/Synchronization_Primitives
// ...
 

// rtl
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>



// libgws - The client-side library.
#include <gws.h>



// initialize via AF_GRAMADO.
// Ainda nao podemos mudar isso para a lib, pois precisamos
// do suporte as rotinas de socket e as definiçoes.
// tem que incluir mais coisa na lib.

int gws (void);
int gws(void)
{
    int client_fd = -1;

    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'
    // The port name is 'port:/ws'

    struct sockaddr addr; 
    
    addr.sa_family = AF_GRAMADO;  //8000
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';  
    
    gws_debug_print ("-------------------------\n"); 
    printf          ("-------------------------\n"); 
    gws_debug_print ("gws.bin: Initializing ...\n");
    printf          ("gws.bin: Initializing ...\n");


    //
    // Socket
    // 

    // #debug
    printf ("gws: Creating socket\n");

    // Create a socket. 
    // AF_GRAMADO = 8000
    client_fd = socket ( AF_GRAMADO, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       gws_debug_print ("gws: [FAIL] Couldn't create socket\n");
       printf          ("gws: [FAIL] Couldn't create socket\n");
       exit(1);  //#bugbug Cuidado.
    }

    //
    // Connect
    //

    // Nessa hora colocamos no accept um fd.
    // então o servidor escreverá em nosso arquivo.
    // Tentando nos conectar ao endereço indicado na estrutura
    // Como o domínio é AF_GRAMADO, então o endereço é "w","s".

    printf ("gws: Trying to connect to the address 'ws' ...\n");      
        
    while (1){

        if ( connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0 )
        { 
            gws_debug_print ("gws: Connection Failed\n");
            printf          ("gws: Connection Failed \n"); 
            //exit(1);
            
        }else{ break; };
    };


    return (int) client_fd;
}


// Main

int main ( int argc, char *argv[] ){

    int client_fd = -1;



    client_fd = gws();

    if ( client_fd < 0 )
    {
         gws_debug_print ("gws.bin: gws initialization fail \n");
         printf          ("gws.bin: gws initialization fail \n");
         exit(1);
    }


    // #test: 
    // Create a lil window in the top left corner.
    
    gws_create_window (client_fd,
        WT_SIMPLE,1,1,"gws-client",
        2, 2, 8, 8,
        0, 0, COLOR_RED, COLOR_RED);

    // #test: 
    // Draw a char.
    gws_draw_char (
        client_fd, 
        0,          // window
        10,         // x
        10,         // y
        COLOR_RED,  // COLOR
        'C');


    // #debug
    while(1){}

    // exit
    gws_debug_print ("gws: bye :) \n");
    return 0;
}


//
// End.
//




