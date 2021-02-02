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

#include <rtl/gramado.h>


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
    
    addr.sa_family = AF_GRAMADO; 
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


// local
int 
gwsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    switch (msg){

        // 20 = MSG_KEYDOWN
        case MSG_KEYDOWN:
            printf("%c",long1); fflush(stdout);
            break;
            
        // 22 = MSG_SYSKEYDOWN
        case MSG_SYSKEYDOWN:
            printf ("MSG_SYSKEYDOWN\n");

            switch (long1){

                // #test: Chamando um demo.
                // gws_async_command(client_fd,4,9); //cat

                case VK_F1: gws_clone_and_execute("editor.bin");   break;
                case VK_F2: gws_clone_and_execute("gwm.bin");      break;
                case VK_F3: gws_clone_and_execute("fileman.bin");  break;
                case VK_F4: gws_clone_and_execute("terminal.bin"); break;

                case VK_F5: gws_clone_and_execute("browser.bin"); break;
                case VK_F6: gws_clone_and_execute("browser.bin"); break;
                case VK_F7: gws_clone_and_execute("browser.bin"); break;
                case VK_F8: gws_clone_and_execute("browser.bin"); break;
                
                case VK_F9 : gws_clone_and_execute("browser.bin"); break;
                case VK_F10: gws_clone_and_execute("browser.bin"); break;
                case VK_F11: gws_clone_and_execute("browser.bin"); break;
                case VK_F12: gws_clone_and_execute("browser.bin"); break;
                // ...
            };
            break;
    };

    // ok
    // retorna TRUE quando o diálogo chamado 
    // consumiu o evento passado à ele.
    
    return TRUE;
}


//==========================================
// Main

int main ( int argc, char *argv[] )
{

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
    rtl_set_file_sync( client_fd, SYNC_REQUEST_SET_ACTION, ACTION_ERROR );
    int value = rtl_get_file_sync( client_fd, SYNC_REQUEST_GET_ACTION );
    
    printf ("VALUE {%d} \n", value);
    
    if( value == ACTION_ERROR )
        printf("OK\n");

    rtl_set_file_sync( client_fd, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
    //close(client_fd);
    //exit(0);
    //while(1){}
    */ 
        
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

    //while(1){
    // Hello
    //gws_async_command(client_fd,3,0);
    //}


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


    /*
    gws_debug_print ("gws.bin: 3 Testing Plot0 4x\n");
    printf          ("gws.bin: 3 Testing Plot0 4x\n");

    //test: plot point;
    //um ponto em cada quadrante.
    gws_plot0 ( client_fd, -50,  50, 0, COLOR_RED );
    gws_plot0 ( client_fd,  50,  50, 0, COLOR_GREEN );
    gws_plot0 ( client_fd,  50, -50, 0, COLOR_BLUE );
    gws_plot0 ( client_fd, -50, -50, 0, COLOR_YELLOW );
    */

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

    /*
    gws_debug_print ("gws.bin: 5 Testing Plot rect \n");
    printf          ("gws.bin: 5 Testing Plot rect \n");

    
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
    */
   
   
    printf ("LOOP:\n");
   
    // #debug
    //while (1){

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
    //}


    // #test: Chamando um demo.
    // gws_async_command(client_fd,4,9); //cat

    // Loop



    //=================================
    
    //get current thread
    int cThread = (int) sc82 (10010,0,0,0);
    //set foreground thread.
    sc82 (10011,cThread,cThread,cThread);
    
    while(1){
        if ( rtl_get_event() == TRUE )
        {  
            // Podemos chamar mais de um diálogo
            // Retorna TRUE quando o diálogo chamado 
            // consumiu o evento passado à ele.
            // Nesse caso chamados 'continue;'
            // Caso contrário podemos chamar outros diálogos.

            gwsProcedure ( 
                (void*) RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };
    //=================================


    // Isso ehestranho ... um cliente remoto nao deve poder fazer isso.
    //gws_debug_print ("gws: Sending command to close the server. \n");
    gws_async_command(client_fd,1,0);
    //exit(0);

    // Asking to server to send me an notification
    // telling me to close myself
    
    //gws_debug_print ("gws: Pinging\n");
    //gws_async_command(client_fd,2,0);


    while(1){}
    // ...

    /*
    unsigned long event_buffer[8];
    // Event loop
    while (TRUE)
    {
        // Get next event.
        read ( client_fd, event_buffer, sizeof(event_buffer) );
        
        //event: Close my self
        //if ( event_buffer[1] == 12344321 )
        //{
        //    gws_debug_print ("gws: [EVENT] We got the event 12344321\n \n");
        //    break;
        //}
        
        if ( event_buffer[0] == 'p' &&
             event_buffer[1] == 'o' &&
             event_buffer[2] == 'n' &&
             event_buffer[3] == 'g' )
        {
            printf("PONG\n");
            gws_async_command(client_fd,1,0);
        }
    };
    */
 
    // exit
    gws_debug_print ("gws: bye :) \n");
    exit(0);
    
    return 0;
}



//
// End.
//




