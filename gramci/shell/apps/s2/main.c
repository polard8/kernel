/*
 * File: s2.c
 *
 *    Small shell.
 *    This is client of gwssrv.
 *    Calling the server directly. With no virtual terminal
 * 
 *    Using socket to connect with gws.
 *    AF_GRAMADO family.
 *
 * 2020 - Created by Fred Nora.
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


/*
// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}
*/

char __buffer[512];

//
// main:
//

//    Small shell.
//    This is client of gwssrv.
//    Calling the server directly. With no virtual terminal

int main ( int argc, char *argv[] ){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.
    int n_reads = 0;    // For receiving responses.

    int client_fd=0;


    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'

    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';  


    debug_print ("---------------------------\n");    
    debug_print ("s2.bin: Small shell for gwssrv.\n");

    //
    // socket
    // 

    // #debug
    printf ("s2.bin: Small shell for gwssrv.\n");
    printf ("s2: Creating socket\n");


    //
    // Socket
    //

    client_fd = socket ( AF_GRAMADO, SOCK_STREAM, 0 );

    if ( client_fd < 0 ){
       printf ("s2: Couldn't create socket\n");
       exit(1);
    }


    //
    // Connect
    // 

    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.
    
    while(1){
        // #debug
        printf ("s2: connecting ...\n");      

        if ( connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0 )
        { 
            debug_print ("s2: Connection Failed \n");
            printf      ("s2: Connection Failed \n");
            // Try again forever.

        }else{break;}; 
    };


    //
    // Loop.
    //

    // Green
    //unsigned long ____color = 0x00FF00;
    
    // Black (fake terminal)
    unsigned long ____color = 0x000000;
 
 
// loop:
new_message:

    // #todo
    // Small shell.
    // This is client of gwssrv.
    // Calling the server directly. With no virtual terminal.


    //
    // Write
    //

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??

    while (1)
    {
        // #debug
        debug_print ("s2: Sending request ...\n");      
        
        // Create window        
        message_buffer[0] = 0;     // window. ?? 
        message_buffer[1] = 1001;  // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        message_buffer[4] = 0;   //x
        message_buffer[5] = 0;   //y
        message_buffer[6] = 640;  //w
        message_buffer[7] = 480;  //h
        message_buffer[8] = ____color; //____color + ( rand() ); 
        message_buffer[9] = WT_SIMPLE;
        // #bugbug: Arg missing!
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.        
        // obs: podemos usar send();

        n_writes = write (client_fd, __buffer, sizeof(__buffer));
       
        if(n_writes>0){ break; }
    }


    //
    // Waiting
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    //debug_print ("s2: Waiting ...\n");      

    int y=0;
    for(y=0; y<15; y++)
        gws_yield();


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // read
    //

   //#caution
   //we cam stay here forever.
   //it's a test yet.

    // #debug
    debug_print ("s2: Reading response ...\n");      


__again:

    n_reads = read ( client_fd, __buffer, sizeof(__buffer) );
    
    if (n_reads<=0)
    {
        gws_yield();        
        goto __again;
    }
    
    // Now we got a message!    
    // Get the message sended by the server.
    int msg = (int) message_buffer[1];


    switch (msg)
    {
        case SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_REPLY:
            goto do_exit;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            //todo: call procedure.
            gws_yield ();
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            debug_print ("gws: SERVER_PACKET_TYPE_ERROR\n");
            gws_yield ();
            goto __again;
            //exit (-1);
            break;
        
        default:
            ____color = rand();
            goto __again;
            break; 
    };


    //
    // done:
    //
    
do_exit:

    printf("%d bytes readed\n",n_reads);
    printf("RESPONSE: {%s} \n",__buffer+16);
    
    // A resposta tras o window id no inpicio do buffer.
    printf ("s2: Window ID %d \n", message_buffer[0] );


    debug_print ("s2: bye\n"); 
    printf      ("s2: bye\n");

    return 0;
}



