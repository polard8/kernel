/*
 * File: s3.c
 *
 *    Using socket to connect with gws.
 *    AF_GRAMADO family.
 *
 * 2020 - Created by Fred Nora.
 */
 
// #todo: 
// Tentar fazer um programa bem pequeno e simples.


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


#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <gws.h>



// tipos de pacotes.
#define SERVER_PACKET_TYPE_REQUEST    1000 
#define SERVER_PACKET_TYPE_REPLY      1001 
#define SERVER_PACKET_TYPE_EVENT      1002
#define SERVER_PACKET_TYPE_ERROR      1003


char __buffer[512];

//char *hello = "s3: Hello!\n";


struct sockaddr addr = {

    .sa_family = AF_GRAMADO,  // 8000
    .sa_data[0] = 'w',
    .sa_data[1] = 's',
};




// main
// Programa para testar conexão.
// deve ser simples e pequeno.

int main ( int argc, char *argv[] ){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.
    int n_reads = 0;    // For receiving responses.

    int client_fd=0;

    int s=-1;


    // Socket

    client_fd = socket ( AF_GRAMADO, SOCK_STREAM, 0 );

    if ( client_fd < 0 )
    {
       printf ("s3: Couldn't create socket\n");
       exit(1);
    }

    // Connect
    
    while (1){
        
        s = connect (client_fd, (struct sockaddr *) &addr, sizeof(addr));
   
        if (s<0){ 
            debug_print ("s3: Connection Failed \n");
            printf      ("s3: Connection Failed \n"); 
            // #bugbug: Try agin forever. 
            
        }else{break;}; 
    };


    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??

round:

    debug_print("s3: Sending request...\n");
    
    while (1)
    {
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello!
        message_buffer[2] = 40;
        message_buffer[3] = 40;

        n_writes = write (client_fd, __buffer, sizeof(__buffer));
       
        if(n_writes>0){ break; }
    };

    //
    // Get response.
    //
 
__again:

    n_reads = read ( client_fd, __buffer, sizeof(__buffer) );

    if (n_reads<=0)
    {
        gws_yield();        
        goto __again;
    }

    
    // Get the message sended by the server.
    int msg = (int) message_buffer[1];
    
    switch (msg){
            
        case SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;
        
        default:
            debug_print ("s3: default reply\n");
            goto __again;
            break; 
    };


   // process reply.

process_reply:
    printf ("s3: We got a respose!\n");
    printf ("s3: bye\n");
    return 0;
}






