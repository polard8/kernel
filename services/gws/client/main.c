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


char __buffer[512];

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


//message support
int gwst_loop(int fd);
int gwst_getmessage_request(int fd);
int gwst_getmessage_response(int fd);


int gwst_getmessage_request(int fd)
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    //char *name = "Window name 1";

   

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
        message_buffer[1] = 369;    //get message request  //1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
 
        //message_buffer[4] = left; //120;   //x
        //message_buffer[5] = top; //120;   //y
        //message_buffer[6] = width; //480;   //w
        //message_buffer[7] = height; //320;   //h
        
        //message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, __buffer, sizeof(__buffer), 0);
       
        if(n_writes>0)
           break;
    }


    return 0; 
}

int gwst_getmessage_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.

    //
    // Waiting for response. ==================
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

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );
    
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

    int window          = (int) message_buffer[0];
    int msg             = (int) message_buffer[1];
    unsigned long long1 = (unsigned long) message_buffer[2];
    unsigned long long2 = (unsigned long) message_buffer[3];
    
    //#debug
    //if(msg!=0)
        //printf ("%c",long1); //printf ("{%d%c} ",msg,long1);
        
        
        
    switch (msg){

         //OK isso funcionou.
        //case MSG_KEYDOWN:
          case 20:  
            //gws_debug_print ("MSG_KEYDOWN\n");
            printf ("%c",long1);
            fflush(stdout);
            goto process_event;
            break;

        //case MSG_KEYUP:
          case 21:  
            //gws_debug_print ("MSG_KEYUP\n");
            goto process_event;
            break;

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
            gws_debug_print ("@");
            goto process_event;
            //goto response_loop;
            break; 
    };





//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    gws_debug_print ("gwst: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("gwst: bye\n"); 
    printf ("gwst: Window ID %d \n", message_buffer[0] );
    //printf ("gwst: Bye\n");
    
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


//loop
int gwst_loop(int fd)
{
	//while(___running){
    while(1){
    gwst_getmessage_request(fd);
    gwst_getmessage_response(fd);
    }
    return 0; 
}



int 
gwst_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color );
    
int gwst_createwindow_response(int fd);



int 
gwst_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    char *name = "Window name 1";

   

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
        
        message_buffer[4] = left; //120;   //x
        message_buffer[5] = top; //120;   //y
        message_buffer[6] = width; //480;   //w
        message_buffer[7] = height; //320;   //h
        
        message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

         
        //...

        // Write!
        // Se foi possível enviar, então saimos do loop.  

        // n_writes = write (fd, __buffer, sizeof(__buffer));
        n_writes = send (fd, __buffer, sizeof(__buffer), 0);
       
        if(n_writes>0)
           break;
    }


    return 0; 
}



//response
int gwst_createwindow_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.

    //
    // Waiting for response. ==================
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

    //n_reads = read ( fd, __buffer, sizeof(__buffer) );
    n_reads = recv ( fd, __buffer, sizeof(__buffer), 0 );
    
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
    //close (fd);

    //gws_debug_print ("gwst: bye\n"); 
    printf ("gwst: Window ID %d \n", message_buffer[0] );
    //printf ("gwst: Bye\n");
    
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

    int client_fd = -1;

    gws_debug_print ("--------------------------\n"); 
    gws_debug_print ("gwst.bin: Initializing ...\n");
    //gws_debug_print ("gwst: Starting ...\n");
    
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
        close(client_fd);
        return (int) (-1); 
    } 
    
    
    //
    // === Create Window ===
    //
    
    gwst_createwindow_request(client_fd, 40, 40, 320, 280, COLOR_GRAY);
    gwst_createwindow_response(client_fd);     
    
    
    //
    // === Event loop ===
    //
    
    gwst_loop(client_fd);    
    
    
    //
    //  === Create Window ===
    //

    /*
    int i=0;
    int l=80;
    int t=80;
    int c=100;
    
    for (i=0; i<16;i++){
    //request
    gwst_createwindow_request(client_fd, l, t, 200, 200, COLOR_BLUE+c);
    l += 10; t += 10; c += 100;
    
    //response
    gwst_createwindow_response(client_fd);
    }
    */
    
    
    gws_debug_print ("gwst: bye :) \n");
    return 0;
}


//
// End.
//




