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

    // Vamos nos concetar com o processo identificado 
    // com o nome 'ws'
    // The port name is 'port:/ws'

    //==============================
    struct sockaddr addr; 
    int addrlen;
    
    addr.sa_family = AF_GRAMADO;  //8000
    addr.sa_data[0] = 'w';
    addr.sa_data[1] = 's';  

    addrlen = sizeof(addr);
    //==============================
    
    
    int client_fd = -1;
    
    
    
    
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

        if ( connect (client_fd, (struct sockaddr *) &addr, addrlen ) < 0 )
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
    int main_window = -1;
    

    //================================
    
    // connection.
    // Only connect. Nothing more.
    
    client_fd = gws();

    if ( client_fd < 0 ){
         gws_debug_print ("gws.bin: gws initialization fail \n");
         printf          ("gws.bin: gws initialization fail \n");
         exit(1);
    }
    
    //===============

    //========================================
    
    // Waiting ...
    // Wait for the moment where the server says: 'yes'

    gws_debug_print ("gws.bin:  \n");
             printf ("gws.bin:  \n");
    
    /*
    char buf[32];
    while (1)
    {
        read (client_fd, buf, 4);
        
        // Not yes
        if( buf[0] != 'y')
        { 
            buf[4] = 0;
            printf ("%s",buf); 
            fflush(stdout);
        }
        
        // yes!
        if( buf[0] == 'y')
        {
            printf ("YES babe!\n");
            break;
            //exit(0);
        }
        
        //gws_draw_char ( client_fd, 
        //    main_window, 
        //    w/3, 8, COLOR_RED, 'C' );
    }
    //================
    */


    //========================================
    
    // Metrics.
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    if ( w == 0 || h == 0 ){
        printf ("gws.bin: w h \n");
        exit(1);
    }


    //
    // Window
    //

    //===============================
    gws_debug_print ("gws.bin: 1 Creating window \n");
    printf          ("gws.bin: Creating window \n");

       
    main_window = gws_create_window (client_fd,
                      WT_SIMPLE, 1, 1, "gws-client",
                      0, 0, w, h,
                      0, 0, COLOR_PINK, COLOR_PINK);

    if (main_window<0){
        printf ("gws.bin: main_window\n");
        exit(1);
    }
    //========================


    //===================
    gws_debug_print ("gws.bin: 2 Drawing a char \n");
    //printf          ("gws.bin: Drawing a char \n");
    gws_draw_char ( client_fd, main_window, 
        16, 8, COLOR_RED, 'C' );
    //====================   
    
    
    
    /*
    //
    // == stdin ===================================================
    //
    char evBuf[32];
    int ev_nreads=0;
    unsigned long lMessage[8];
    //struct
    while(TRUE){
        //read from keyboard tty
        ev_nreads = read(0,evBuf,16);
        //if (ev_nreads>0){ printf ("E\n"); }  //funcionou.
        if(ev_nreads>0)
        {
            memcpy( (void*) &lMessage[0],(const void*) &evBuf[0], 16); //16 bytes 
            if( lMessage[1] != 0 )
            {
                 printf( "%c", lMessage[2] ); //long1
                 fflush(stdout);
            }
        }  
        gws_draw_char ( client_fd, main_window, 
        32, 8, COLOR_RED, 'I' );
    };
    // ============================================================
    */
    
    

    // Create a little window in the top left corner.
    //gws_create_window (client_fd,
        //WT_SIMPLE,1,1,"gws-client",
        //2, 2, 8, 8,
        //0, 0, COLOR_RED, COLOR_RED);

    // Draw a char.
    // IN: fd, window id, x, y, color, char.
    //gws_draw_char ( client_fd, 0, 
        //16, 8, COLOR_RED, 'C' );


    gws_debug_print ("gws.bin: 3 Testing Plot0 4x\n");
    printf          ("gws.bin: 3 Testing Plot0 4x\n");

    //test: plot point;
    //um ponto em cada quadrante.
    gws_plot0 ( client_fd, -50,  50, 0, COLOR_RED );
    gws_plot0 ( client_fd,  50,  50, 0, COLOR_GREEN );
    gws_plot0 ( client_fd,  50, -50, 0, COLOR_BLUE );
    gws_plot0 ( client_fd, -50, -50, 0, COLOR_YELLOW );

    //
    // == cube ==================================
    //

    
    gws_debug_print ("gws.bin: 4 Testing Plot cube \n");
    printf          ("gws.bin: 4 Testing Plot cube \n");


    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );
    if ( (void*) cube != NULL )
    {

        //south     
        cube->p[0].x = -140;
        cube->p[0].y = -90;
        cube->p[0].z = 0;
        cube->p[0].color = COLOR_WHITE;
        
        cube->p[1].x = 140;
        cube->p[1].y = -90;
        cube->p[1].z = 0;
        cube->p[1].color = COLOR_WHITE;
        
        cube->p[2].x = 140;
        cube->p[2].y = -100;
        cube->p[2].z = 0;
        cube->p[2].color = COLOR_WHITE;
        
        cube->p[3].x = -140;
        cube->p[3].y = -100;
        cube->p[3].z = 0;
        cube->p[3].color = COLOR_WHITE;

        //north
        cube->p[4].x = -140;
        cube->p[4].y = -90;
        cube->p[4].z = 20;
        cube->p[4].color = COLOR_YELLOW;
        
        cube->p[5].x = 140;
        cube->p[5].y = -90;
        cube->p[5].z = 20;
        cube->p[5].color = COLOR_YELLOW;
        
        cube->p[6].x = 140;
        cube->p[6].y = -100;
        cube->p[6].z = 20;
        cube->p[6].color = COLOR_YELLOW;
        
        cube->p[7].x = -140;
        cube->p[7].y = -100;
        cube->p[7].z = 20;
        cube->p[7].color = COLOR_YELLOW;
        
        // plot cube 
        gws_plotcube ( client_fd, (struct gr_cube_d *) cube );
    }
   


    //
    // == rectangle ==================================
    //
    
    
    struct gr_rectangle_d *rect;
    rect = (void *) malloc( sizeof( struct gr_rectangle_d ) );
    if ( (void*) rect != NULL )
    {

        rect->p[0].x = -20;
        rect->p[0].y = 20;
        rect->p[0].z = 0;
        rect->p[0].color = COLOR_BLUE;
        
        rect->p[1].x = 10;
        rect->p[1].y = 20;
        rect->p[1].z = 0;
        rect->p[1].color = COLOR_BLUE;
        
        rect->p[2].x = 10;
        rect->p[2].y = 0;
        rect->p[2].z = 0;
        rect->p[2].color = COLOR_BLUE;
        
        rect->p[3].x = -20;
        rect->p[3].y = 0;
        rect->p[3].z = 0;
        rect->p[3].color = COLOR_BLUE;
        
        
        // plot rectangle 
        gws_plotrectangle ( client_fd, (struct gr_rectangle_d *) rect );
    }
   
   
    // #debug
    while (1){

        gws_draw_char ( client_fd, main_window, 
            20, 20, COLOR_RED, 'X' );
   
        // ...

        // Saving the fd into the libgws.
        // it's gonna be used by the payment routine.
        // See: connect.c
        //gws_set_client_fd(client_fd);
        //gws_payment();
        
        //refresh background and yield.
        //gws_refresh_yield(client_fd);
        
        //gws_refresh_window (client_fd, main_window);
        //gws_yield();
    }


    // exit
    gws_debug_print ("gws: bye :) \n");
    return 0;
}



//
// End.
//




