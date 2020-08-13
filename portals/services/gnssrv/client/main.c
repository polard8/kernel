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
 
 
#include <types.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <netdb.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#include <sys/socket.h>


//#test
//#include <gws.h>

#include <packet.h>


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
    
    // Não vamos insistir num arquivo vazio.
    //if (n_reads<=0){
    //     gnst_yield();        
    //    goto __again;
    //}

    if (n_reads == 0){
         gnst_yield();        
        goto __again;
    }
    
    if (n_reads < 0){
        printf ("gnst: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
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


process_reply:

    //
    // done:
    //

    //printf("%d bytes readed\n",n_reads);
    printf("RESPONSE: {%s} \n",__buffer+16);

    return 0;
}


int gnst_hello_request(int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.

     //
     // Loop for new message.
     //

    unsigned long ____color = 0x00FF00;

// loop:
new_message:

    
     
    //
    // Write
    //

    // #debug
    debug_print ("gnst: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??


    // Write!
    // Se foi possível enviar, então saimos do loop.        
    // obs: podemos usar send();

    while (1){

        // solicita um hello!      
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        // ...

        n_writes = write (fd, __buffer, sizeof(__buffer));
        if(n_writes>0)
           break;
    }

    return 0;
}


//internal
void gnst_hello (int fd)
{
    if(fd<0)
        debug_print("gnst_hello: fd\n");

    gnst_hello_request(fd);
    gnst_hello_response(fd);
}


// Testing new main.
int main ( int argc, char *argv[] ){

    int client_fd = -1;

    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port   = 7548;   //porta para o Network Server 'ns' em gramado_ports[]
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 79); 
    

    debug_print ("---------------------------\n");    
    debug_print ("gnst.bin: Initializing ...\n");


    //
    // Socket
    // 

    // #debug
    printf ("gnst: Creating socket\n");


    // cria o soquete.
    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );

    if ( client_fd < 0 ){
       //gws_debug_print ("gnst: Couldn't create socket\n");
       printf ("gnst: Couldn't create socket\n");
       exit(1);
    }


    while(1){
    
        //
        // Connect
        // 

        //nessa hora colocamos no accept um fd.
        //então o servidor escreverá em nosso arquivo.
        // #debug
        //gws_debug_print ("gnst: Connecting to ns via inet  ...\n");      
        printf ("gnst: Connecting to ns via inet  ...\n");      
        if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0)
        { 
            //gws_debug_print ("gnst: Connection Failed\n");
            printf("gnst: Connection Failed \n"); 
            //close(client_fd);
            //exit(1);
            //return (int) (-1); 
         }else{break;}; 

    };




    //
    // Loop.
    //

    while(1){

        // Hello.
        gnst_hello(client_fd);
    }


    debug_print ("gnst: bye\n"); 
    printf ("gnst: bye\n");

    return 0;
}




