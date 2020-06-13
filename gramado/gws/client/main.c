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
 
 
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>


// libgws ?
#include <gws.h>


// Tipos de pacotes.
// #todo: Move this to gws.h
#define SERVER_PACKET_TYPE_REQUEST    1000 
#define SERVER_PACKET_TYPE_REPLY      1001 
#define SERVER_PACKET_TYPE_EVENT      1002
#define SERVER_PACKET_TYPE_ERROR      1003



// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}




int gwst_event_loop(void);


int gwst_event_loop(void){
	
    char __buffer[512];

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.
    int n_reads = 0;    // For receiving responses.

    int client_fd;


    gws_debug_print ("--------------------------\n"); 
    gws_debug_print ("gwst.bin: Initializing ...\n");

    char *name = "Window name 1";

    //
    // socket
    // 

    // #debug
    printf ("gwst: Creating socket\n");

    // Create a socket. AF_GRAMADO = 8000
    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       gws_debug_print ("gwst: Couldn't create socket\n");
       printf ("gwst: Couldn't create socket\n");
       exit(1);  //#bugbug Cuidado.
    }
    

    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'

    // The port name is 'port:/ws'

    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';  
    

    //
    // connect
    // 

    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.
    
    // #debug
    printf ("gwst: Connecting to the address 'ws' ...\n");      

    // Tentando nos conectar ao endereço indicado na estrutura
    // Como o domínio é AF_GRAMADO, então o endereço é "w","s".
    if ( connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0 )
    { 
        gws_debug_print ("gwst: Connection Failed\n");
        printf ("gwst: Connection Failed \n"); 
        return -1; 
    } 


    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gwst: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = 120;   //x
        message_buffer[5] = 120;   //y
        message_buffer[6] = 480;   //w
        message_buffer[7] = 320;   //h
        
        message_buffer[8] = xCOLOR_GRAY2; 

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (client_fd, __buffer, sizeof(__buffer));
        n_writes = send (client_fd, __buffer, sizeof(__buffer), 0);
       
        if(n_writes>0)
           break;
    }


    //
    // Waiting for response.
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    gws_debug_print ("gwst: Waiting ...\n");      

    int y;
    for(y=0; y<15; y++)
        gws_yield();   // See: libgws/


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
    gws_debug_print ("gwst: reading ...\n");      


    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    //n_reads = read ( client_fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( client_fd, __buffer, sizeof(__buffer), 0 );
    
    //if (n_reads<=0){
    //     gws_yield(); 
    //    goto response_loop;
    //}
    
    // Se retornou 0, podemos tentar novamente.
    if (n_reads == 0){
         gws_yield(); 
        goto response_loop;
    }
    
    // Se retornou -1 é porque algo está errado com o arquivo.
    if (n_reads < 0){
        gws_debug_print ("gwst: recv fail.\n");
        printf ("gwst: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }


    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

        case SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
            goto response_loop;
            break;
            
        // Reply!
        case SERVER_PACKET_TYPE_REPLY:
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            goto process_event;
            //goto response_loop;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            gws_debug_print ("gwst: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default:
            goto response_loop;
            break; 
    };





//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    gws_debug_print ("gwst: Testing close() ...\n"); 
    close (client_fd);

    gws_debug_print ("gwst: bye\n"); 
    printf ("gwst: Window ID %d \n", message_buffer[0] );
    printf ("gwst: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("gwst: We got an event\n"); 
    return 0;
}



int main ( int argc, char *argv[] ){

    gws_debug_print ("gwst: Starting ...\n");
    
    return (int) gwst_event_loop();
}


//
// End.
//




