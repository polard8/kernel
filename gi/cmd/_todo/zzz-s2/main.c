

// s2.c - socket test 2
 
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
#include <gws.h>


// tipos de pacotes.
#define SERVER_PACKET_TYPE_REQUEST    1000 
#define SERVER_PACKET_TYPE_REPLY      1001 
#define SERVER_PACKET_TYPE_EVENT      1002
#define SERVER_PACKET_TYPE_ERROR      1003





int main ( int argc, char *argv[] ){

    char __buffer[512];

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.
    int n_reads = 0;    // For receiving responses.

    int client_fd;


    debug_print ("---------------------------\n");    
    debug_print ("s2.bin: Initializing ...\n");



    //
    // socket
    // 

    // #debug
    printf ("s2: Creating socket\n");

    // cria o soquete.
    // AF_GRAMADO
    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("s2: Couldn't create socket\n");
       exit(1);
    }
    

    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'

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
    printf ("s2: connecting ...\n");      

    if (connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) { 
        printf("s2: Connection Failed \n"); 
        return -1; 
    } 


     //
     // Loop for new message.
     //

    unsigned long ____color;
      ____color = 0x00FF00;

new_message:

    //
    // write
    //

    // #debug
    debug_print ("s2: * writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??

    while   (1){

        //create window        
        message_buffer[0] = 0; //window. 
        message_buffer[1] = 1001; //1000;  //msg = hello friend.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = 450;   //x
        message_buffer[5] = 100;   //y
        message_buffer[6] = 200;   //w
        message_buffer[7] = 200;   //h
        
        message_buffer[8] = ____color; //0x00FF00;   //color


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

        // write test.
        //sprintf(__buffer,"s2: Magic message!\n");
        n_writes = write (client_fd, __buffer, sizeof(__buffer));
            //send(client_fd , hello , strlen(hello) , 0 ); 
       
        // Se foi possível enviar, então não tentaos novamente.
        if(n_writes>0)
           break;
    }


    //
    // waiting
    //

    // #debug
    debug_print ("s2: wating ...\n");      

    int y;
    for(y=0; y<10; y++)
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

    // #debug
    debug_print ("s2: reading ...\n");      


       //#caution
       //we cam stay here for ever.
       //it's a test yet.
    __again:
    n_reads = read ( client_fd, __buffer, sizeof(__buffer) );
    // Não vamos insistir num arquivo vazio.
    if (n_reads<=0){
         gws_yield();        
        goto __again;
    }
    
    // Get the message sended by the server.
    int msg = (int) message_buffer[1];
    
    switch (msg)
    {
        case SERVER_PACKET_TYPE_REQUEST:
            gws_yield ();
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
            debug_print ("gws: SERVER_PACKET_TYPE_ERROR\n");
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
    
    debug_print ("s2: new message\n");
    goto new_message;
    
    
    debug_print ("s2: bye\n"); 
    printf ("s2: bye\n");

    return 0;
}

