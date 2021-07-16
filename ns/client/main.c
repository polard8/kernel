/*
 * File: main.c
 *
 *    Client side application for Gramado Network Server.
 *    Using socket to connect with gns.
 *    AF_GRAMADO family.
 * 
 * 
 *       O propósito é testar o servidor gns.
 *
 * 2020 - Created by Fred Nora.
 */


// Connecting via AF_INET.

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


#include <rtl/gramado.h>

// gns
#include <packet.h>



//
// == ports ====================================
//

#define PORTS_WS  4040
#define PORTS_NS  4041
#define PORTS_FS  4042
// ...



// #test
// Tentando deixar o buffer aqui e aproveitar em mais funções.
char __buffer[512];

#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)


// tipos de pacotes.
//#define SERVER_PACKET_TYPE_REQUEST    1000 
//#define SERVER_PACKET_TYPE_REPLY      1001 
//#define SERVER_PACKET_TYPE_EVENT      1002
//#define SERVER_PACKET_TYPE_ERROR      1003


void gnst_yield(void);


// Hello!
// Podemos isso na lib.
int gnst_hello_request(int fd);
int gnst_hello_response(int fd);


//...



/*
// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}
*/




void gnst_yield(void)
{
    gramado_system_call (265,0,0,0); //yield thread.
}




//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/




int gnst_hello_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.


    //
    // waiting
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    debug_print ("gnst: Waiting ...\n");      

    int y;
    for(y=0; y<15; y++)
        gnst_yield();



    //
    // read
    //

    // #debug
    debug_print ("gnst: reading ...\n");      


       //#caution
       //we can stay here for ever.
       //it's a test yet.
__again:
    n_reads = read ( fd, __buffer, sizeof(__buffer) );
    
    if (n_reads <= 0)
    {
        printf ("gnst: recv fail\n");
        gnst_yield ();
        return -1;
    }
        
    // Get the message sended by the server.
    int msg = (int) message_buffer[1];
    
    switch (msg)
    {
        case SERVER_PACKET_TYPE_REQUEST:
            gnst_yield ();
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_REPLY:
            debug_print ("gnst: SERVER_PACKET_TYPE_REPLY received\n"); 
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            //todo: call procedure.
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            debug_print ("gnst: SERVER_PACKET_TYPE_ERROR\n");
            goto __again;
            //exit (-1);
            break;
        
        default:
            goto __again;
            break; 
    };


    //
    // done:
    //

    char response_buffer[64];

process_reply:

    sprintf( response_buffer, (__buffer+16) );
    response_buffer[63] = 0;  //finaliza
    printf("RESPONSE: {%s} \n", response_buffer );

    return TRUE;
}


int gnst_hello_request (int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.

    //unsigned long ____color = 0x00FF00;
    int i=0;

// loop:
// Loop for new message.

new_message:

    //
    // Write
    //

    // #debug
    debug_print ("gns.bin: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??

    // Write!
    // Se foi possível enviar, então saimos do loop.        
    // obs: podemos usar send();

    while (1){

        // messae: Solicita um hello!      
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        // ...

        n_writes = write (fd, __buffer, sizeof(__buffer));
        if (n_writes>0)
           break;
        
        for (i=0; i<9; i++){
            gramado_system_call (265,0,0,0); //yield thread.
            //gnst_yield();
        }
    }

    return 0;
}


// internal
// #todo: 
// Move these routine to the client-side library.
int gnst_hello (int fd)
{
    
    if (fd<0){
        debug_print("gnst_hello: fd\n");
    }

    gnst_hello_request(fd);
    
    // Avisamos que um request foi enviado.
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );

    // Waiting to read the response.
    int value=0;
    while (1){
        value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
        if (value == ACTION_REPLY ) { break; }
        if (value == ACTION_ERROR ) { return -1; }
        gnst_yield();
    };

    return (int) gnst_hello_response(fd);
}



/*
 * main:
 * 
 * 
 */

int main ( int argc, char *argv[] ){


    //========================
    struct sockaddr_in server_address;
    int addrlen;
    
    server_address.sin_family = AF_INET;
    
    // Connecting to the network server in this machine.
    server_address.sin_port        = PORTS_NS;       // htons(PORTS_NS);
    server_address.sin_addr.s_addr = IP(127,0,0,1);  // inet_addr("192.168.0.101");

    addrlen = sizeof(server_address);
    //========================
 

    int client_fd = -1;

    debug_print ("-------------------------\n");
    debug_print ("gns.bin: Initializing ...\n");


//
// Socket
// 

    // #debug
    printf ("gns.bin: Creating socket\n");


    // cria o soquete.
    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );

    if ( client_fd < 0 )
    {
       //gws_debug_print ("gnst: Couldn't create socket\n");
       printf ("gns.bin: [FAIL] Couldn't create socket\n");
       exit(1);
    }


//
// Connect
// 

    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.
    
    // #debug
    //gws_debug_print ("gnst: Connecting to ns via inet  ...\n");      
    printf ("gns.bin: Connecting to ns via inet  ...\n");      
        
    while (1){

        if (connect (client_fd, (void *) &server_address, addrlen ) < 0)
        { 
            //gws_debug_print ("gnst: Connection Failed\n");
            printf ("gns.bin: Connection Failed \n"); 
            //close(client_fd);
            //exit(1);
            //return (int) (-1);
         }else{break;}; 
    };


    if (client_fd<0){
        printf("gns.bin: fd fail\n");
        exit(1);
    }

    // no loop.
    //gnst_hello (client_fd);
    //gnst_hello (client_fd);
    //gnst_hello (client_fd);
    //gnst_hello (client_fd);
    
    //int i=0;
    //for(i=0; i<50; i++)
    //    gnst_yield();

    while(1){

        printf("gns.bin: Send message\n");
        gnst_hello (client_fd);

        printf("gns.bin: Sleep\n");
        gnst_yield();
    };
    

    close(client_fd);
    
    debug_print ("gns.bin: bye\n"); 
    printf      ("gns.bin: bye\n");
    return 0;
}




