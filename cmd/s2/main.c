

// s2.c - socket test 2
 
// tutorial example taken from. 
// https://www.tutorialspoint.com/unix_sockets/socket_server_example.htm
 
/*
 
To make a process a TCP server, you need to follow the steps given below −

    Create a socket with the socket() system call.

    Bind the socket to an address using the bind() system call. 
    * For a server socket on the Internet, an address consists of a 
    * port number on the host machine.

    Listen for connections with the listen() system call.

    Accept a connection with the accept() system call. 
    * This call typically blocks until a client connects with the server.

    Send and receive data using the read() and write() system calls.
 



*/ 
 
 
#include <types.h>

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <netdb.h>
#include <netinet/in.h>

#include <arpa/inet.h>

#include <sys/socket.h>





int main ( int argc, char *argv[] )
{
    int client_fd;
    
    // cria o soquete.
    // AF_GRAMADO
    client_fd = socket ( 8000, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("s2: Couldn't create socket\n");
    }
    
    struct sockaddr addr;
    addr.sa_family = 8000; //AF_GRAMADO
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';    
    
 
    if (connect (client_fd, (struct sockaddr *) &addr, sizeof(addr)) < 0) 
    { 
        printf("s2: Connection Failed \n"); 
        return -1; 
    }    
    
    //send(client_fd , hello , strlen(hello) , 0 ); 

    char __buffer[512];
    
   // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n=-1;

    while   (1){

        //read test. 
        //n = read(client_fd, __buffer, sizeof(__buffer));
        //if(n>0){
            //printf ("s2: Received: %s \n",__buffer);            
        //}

        //create window
        
        message_buffer[0] = 0; //window. 
        message_buffer[1] = 1001; //1000;  //msg = hello friend.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        message_buffer[4] = 100;   //x
        message_buffer[5] = 100;   //y
        message_buffer[6] = 320;  //w
        message_buffer[7] = 280;  //h

        message_buffer[8] = 0x00FF00;   //color


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
       write(client_fd, __buffer, sizeof(__buffer));
       //break;
    }

    //printf ("s2: Received: %s \n",__buffer);
    
    return 0;

}

