/*
 * File: s2.c
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


// tipos de pacotes.
//#define SERVER_PACKET_TYPE_REQUEST    1000 
//#define SERVER_PACKET_TYPE_REPLY      1001 
//#define SERVER_PACKET_TYPE_EVENT      1002
//#define SERVER_PACKET_TYPE_ERROR      1003
void gnst_yield(void);









void gnst_yield(void){
	
    gramado_system_call (265,0,0,0); //yield thread.
}


// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}


int main ( int argc, char *argv[] ){

    char __buffer[512];

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.
    int n_reads = 0;    // For receiving responses.

    int client_fd;


    debug_print ("---------------------------\n");    
    debug_print ("gnst.bin: Initializing ...\n");



    //
    // socket
    // 

    // #debug
    printf ("gnst: Creating socket\n");

    // cria o soquete.
    // AF_GRAMADO
    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("gnst: Couldn't create socket\n");
       exit(1);
    }
    

    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'

    // The port name is 'port:/ws'

    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'n';
    addr.sa_data[1] = 's';  
    
    
    
    //
    // connect
    // 


    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.
    
    // #debug
    printf ("gnst: connecting ...\n");      

    if (connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0){ 
        printf("gnst: Connection Failed \n"); 
        return -1; 
    } 


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

    while (1)
    {
        // Create window        
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = 450;   //x
        message_buffer[5] = 100;   //y
        message_buffer[6] = 200;   //w
        message_buffer[7] = 200;   //h
        
        message_buffer[8] = ____color + ( rand() ); 


        /*
        //line
        message_buffer[0] = 0; //window. 
        message_buffer[1] = 1003; //1000;  //msg = hello friend.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        message_buffer[4] = 100;   //x1
        message_buffer[5] = 100;   //y
        message_buffer[6] = 200;       //x2
        message_buffer[7] = 0x00FF00;   //color
        */

        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.        
        // obs: podemos usar send();

        n_writes = write (client_fd, __buffer, sizeof(__buffer));
       
        if(n_writes>0)
           break;
    }


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


    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.


    //
    // read
    //

    // #debug
    debug_print ("gnst: reading ...\n");      


       //#caution
       //we cam stay here for ever.
       //it's a test yet.
    __again:
    n_reads = read ( client_fd, __buffer, sizeof(__buffer) );
    // Não vamos insistir num arquivo vazio.
    if (n_reads<=0){
         gnst_yield();        
        goto __again;
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
    //printf("RESPONSE: {%s} \n",__buffer+16);
    
    // A resposta tras o window id no inpicio do buffer.
    // printf ("s2: Window ID %d \n", message_buffer[0] );

    ____color = rand();
    
    debug_print ("gnst: new message\n");
    goto new_message;
    
    
    debug_print ("gnst: bye\n"); 
    printf ("gnst: bye\n");

    return 0;
}

