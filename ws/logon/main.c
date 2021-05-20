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

// #todo
// We can have a custom status bar in this client.
// goal: Identity purpose.



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


#define __BG_COLOR    xCOLOR_GRAY1


unsigned long savedW=0;
unsigned long savedH=0;



int logon_window;
    
//
// == prototypes =============
//

int gws (void);



// area de jogo
int player_x;
int player_y;
int game_width;
int game_height;

// barra de status
int status_window;


void gameTestASCIITable(int fd,unsigned long w, unsigned long h)
{
    int i=0;
    int j=0;
    int c=0;
    
    for(i=0; i<4; i++)
    {
        for(j=0; j<64; j++)
        {
            gws_draw_char ( 
                fd, status_window, 
                (w/64) * j, (i*8), 
                COLOR_YELLOW, c );
            c++;
        };
    };
}


//
// initialize
//

int 
logonInitialize( 
    int fd,
    unsigned long w, 
    unsigned long h )
{

    player_x = 0;
    player_y = 0;

    // Test
    // #bugbug
    // O refresh da tela faz à cada letra, 
    // faz as letras aparecerem lentamente.

    // Draw two chars in the status bar.

    gws_draw_char ( fd, status_window, (w/30)  * 2, (8), COLOR_BLUE, 127 );
    gws_draw_char ( fd, status_window, (w/30)  * 3, (8), COLOR_BLUE, 127 );
    gws_draw_char ( fd, status_window, (w/30)  * 2, (8), COLOR_YELLOW, '0' );
    gws_draw_char ( fd, status_window, (w/30)  * 3, (8), COLOR_YELLOW, '0' );

    // Draw a string in the status bar
    gws_draw_text(
        fd, status_window,
        (w/30)  * 6, 8, COLOR_YELLOW, "LOGON:  F1=UI | F2=Reboot");

    //...

    return 0;
}


void 
SB_Update ( 
    int fd, 
    unsigned long w, 
    unsigned long h, 
    int first_number, 
    int second_number )
{

    gws_draw_char ( fd, status_window, (w/30)  * 2, (8), COLOR_BLUE, 127 );
    gws_draw_char ( fd, status_window, (w/30)  * 3, (8), COLOR_BLUE, 127 );
    
    gws_draw_char ( fd, status_window, (w/30)  * 2, (8), COLOR_YELLOW, first_number );
    gws_draw_char ( fd, status_window, (w/30)  * 3, (8), COLOR_YELLOW, second_number );

}

// initialize via AF_GRAMADO.
// Ainda nao podemos mudar isso para a lib, pois precisamos
// do suporte as rotinas de socket e as definiçoes.
// tem que incluir mais coisa na lib.

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

    while (TRUE){
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
logonProcedure ( 
    int fd,
    int window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    int f12Status = -1;

    switch (msg){

        // 20 = MSG_KEYDOWN
        case MSG_KEYDOWN:
            switch(long1){
                // keyboard arrows
                case 0x48: 
                    //printf ("UP   \n"); 
                    player_y = (player_y - 8);
                    if( player_y <= 0){ player_y = 0; }
                    gws_draw_char ( fd, logon_window, player_x, player_y, COLOR_YELLOW, 'G' );
                    SB_Update(fd,savedW,savedH,0, 'U');
                    goto done; 
                    break;
                case 0x4B: 
                    //printf ("LEFT \n"); 
                    player_x = (player_x - 8);
                    if ( player_x <= 0){ player_x = 0;}
                    gws_draw_char ( fd, logon_window, player_x, player_y, COLOR_YELLOW, 'G' );
                    SB_Update(fd,savedW,savedH,0, 'L');
                    goto done; 
                    break;
                case 0x4D: 
                    //printf ("RIGHT\n"); 
                    player_x = (player_x + 8);
                    if ( player_x >= game_width){ player_x = (game_width - 8);}
                    gws_draw_char ( fd, logon_window, player_x, player_y, COLOR_YELLOW, 'G' );
                    SB_Update(fd,savedW,savedH,0, 'R');
                    goto done; 
                    break;
                case 0x50: 
                    //printf ("DOWN \n"); 
                    player_y = (player_y + 8);
                    if( player_y >= game_height){ player_y = (game_height-8); }
                    gws_draw_char ( fd, logon_window, player_x, player_y, COLOR_YELLOW, 'G' );
                    SB_Update(fd,savedW,savedH,0, 'D');
                    goto done; 
                    break;
 
                // #bugbug: It does't work.
                //case '1': 
                    //gws_redraw_window(fd, logon_window, 1); 
                    //gws_refresh_window(fd, logon_window);
                    //break;

                default:
                    printf("%c",long1); fflush(stdout);
                    break;
            }
            break;

        // 22 = MSG_SYSKEYDOWN
        case MSG_SYSKEYDOWN:
            switch (long1){

                // 1~4

                // UI
                case VK_F1: 
                    gws_clone_and_execute("gwm.bin");
                    return 0;
                    break;
                
                // REBOOT
                case VK_F2: 
                    gws_clone_and_execute("reboot.bin");  
                    return 0;
                    break;
                    
                //case VK_F3: gws_clone_and_execute("fileman.bin");   break;
                //case VK_F4: gws_clone_and_execute("editor.bin");    break;

                // 4~8
                //case VK_F5: gws_clone_and_execute("browser.bin"); break;
                //case VK_F6: gws_clone_and_execute("browser.bin"); break;
                //case VK_F7: gws_clone_and_execute("browser.bin"); break;
                case VK_F8: 
                    // #test
                    // Setup the flag to show or not the fps window.
                    // Request number 6.
                    gws_async_command(fd,6,TRUE,0);
                    break;


                // 9~12
                case VK_F9: 
                    //gws_async_command(fd,1,0,0);  // Exit GWS
                    //gws_async_command(fd,4,1,0);
                    //gws_async_command(fd,1,0,0);
                    gws_async_command(fd,4,9,0);  // cat
                    //gws_async_command(fd,4,1,0);
                    //gws_async_command(fd,4,2,0);
                    //gws_clone_and_execute("browser.bin"); 
                    break;
                case VK_F10: 
                    gws_async_command(fd,4,6,0);
                    //gws_clone_and_execute("browser.bin"); 
                    break;
                case VK_F11: 
                    gws_async_command(fd,4,7,0);
                    //gws_clone_and_execute("browser.bin"); 
                    break;

                // #test
                case VK_F12: 
                    gws_async_command(fd,4,1,0);  // testando janela.
                    //gws_async_command(fd,4,10,0);   //triangle
                    //gws_async_command(fd,4,11,0); //polygon
                    //gws_async_command(fd,4,12,0); //lines
                    //gws_clone_and_execute("browser.bin"); 
                    //printf("gws.bin: Shutting down ...\n");
                    //f12Status = (int) gws_clone_and_execute("shutdown.bin");
                    //if (f12Status<0){ break; } // fail
                    //exit(0);
                    break;
 
                // ...
            };
            break;
    };

    // ok
    // retorna TRUE quando o diálogo chamado 
    // consumiu o evento passado à ele.

done:
    return (int) gws_default_procedure(fd,0,msg,long1,long2);
    //return 0;
}


//==========================================
// Main

int main ( int argc, char *argv[] )
{

    // # config
    int ShowCube = FALSE;
    // ...


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
    //         printf ("gws.bin:  \n");


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

    unsigned long SB_Width=0;
    unsigned long SB_Height=0;

    if ( w == 0 || h == 0 ){
        printf ("gws.bin: w h \n");
        exit(1);
    }

    game_width  = w;
    game_height = h;
    savedW      = w;
    savedH      = h;

    //while(1){
    // Hello
    //gws_async_command(client_fd,3,0,0);
    //}


//
// Windows
//

    // ===============================
    // Main window: Background
    gws_debug_print ("logon.bin: Creating main window \n");
    //printf          ("gws.bin: Creating main window \n");

    main_window = gws_create_window (
                      client_fd,
                      WT_SIMPLE, 1, 1, "gws-main",
                      0, 0, w, h,
                      0, 0, 
                      __BG_COLOR, __BG_COLOR);

    if (main_window < 0){
        printf ("gws.bin: main_window\n");
        exit(1);
    }
    logon_window = main_window;
    //========================


    // ===============================
    // Status bar:
    gws_debug_print ("logon.bin: Creating status window \n");
    //printf          ("gws.bin: Creating main window \n");
    SB_Width = w;
    if (h  < 200){ SB_Height = h >> 1; }
    if (h >= 200){ SB_Height = h >> 2; }
    if (h >= 600){ SB_Height = h >> 3; }

    int tmp1;
    tmp1 = gws_create_window (
               client_fd,
               WT_SIMPLE, 1, 1, "SB",
               0, h-SB_Height, 
               SB_Width, SB_Height,
               0, 0, xCOLOR_GRAY2, xCOLOR_GRAY2 );

    if (tmp1<0){
        printf ("logon.bin: tmp1\n");
        exit(1);
    }
    status_window = tmp1;
    //========================



    // Drawing a char just for fun, not for profit.

    //===================
    gws_debug_print ("logon.bin: 2 Drawing a char \n");
    //printf          ("gws.bin: Drawing a char \n");
    gws_draw_char ( 
        client_fd, main_window, 0, 0, COLOR_YELLOW, 'G' );
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

    // #maybe
    // The custon status bar?
    // Maybe the custon status bar can be a window.

    gws_debug_print ("gws.bin: 4 Testing Plot cube \n");
    //printf          ("gws.bin: 4 Testing Plot cube \n");

    
    int backLeft   = (-(w/4)); 
    int backRight  =   (w/4);
    int backTop    = (h/2);
    int backBottom = (h/2) - 32;
    
    int frontLeft   = (-(w/2)); 
    int frontRight  =   (w/2);
    int frontTop    = -((h/2) - 32);
    int frontBottom = -(h/2);
    

    /*
    int backLeft   =  -100;
    int backRight  =  -50;
    int backTop    =   0;
    int backBottom =  -50;
    int frontLeft   = -300; 
    int frontRight  = -200;
    int frontTop    = -100;
    int frontBottom = -200;
    */

    int zTest = 0;

    struct gr_cube_d *cube;
    cube = (void *) malloc( sizeof( struct gr_cube_d ) );

    //int Count=0;
    //for (Count=0; Count<100; Count = Count+10 ){
    //zTest = zTest - 10;
    if ( (void*) cube != NULL )
    {
        // =========
        // south (frente) 
        cube->p[0].x = frontLeft; //-140;
        cube->p[0].y = frontTop;  //-90;
        cube->p[0].z = zTest;
        cube->p[0].color = COLOR_YELLOW;
        
        cube->p[1].x = frontRight; //140;
        cube->p[1].y = frontTop;   //-90;
        cube->p[1].z = zTest;
        cube->p[1].color = COLOR_YELLOW;
        
        cube->p[2].x = frontRight;  //140;
        cube->p[2].y = frontBottom; //-100;
        cube->p[2].z = zTest;
        cube->p[2].color = COLOR_YELLOW;
        
        cube->p[3].x = frontLeft;   //-140;
        cube->p[3].y = frontBottom; //-100;
        cube->p[3].z = zTest;
        cube->p[3].color = COLOR_YELLOW;

        // ===========
        // north (trás)
        cube->p[4].x = backLeft; //-140;
        cube->p[4].y = backTop; //-90;
        cube->p[4].z = zTest;
        cube->p[4].color = COLOR_GREEN;
        
        cube->p[5].x = backRight; //140;
        cube->p[5].y = backTop; //-90;
        cube->p[5].z = zTest;
        cube->p[5].color = COLOR_GREEN;
        
        cube->p[6].x = backRight;  //140;
        cube->p[6].y = backBottom; //-100;
        cube->p[6].z = zTest;
        cube->p[6].color = COLOR_GREEN;
        
        cube->p[7].x = backLeft; //-140;
        cube->p[7].y = backBottom; //-100;
        cube->p[7].z = zTest;
        cube->p[7].color = COLOR_GREEN;
 
        // plot cube 
        if (ShowCube==TRUE){
            gws_plotcube ( client_fd, (struct gr_cube_d *) cube );
        }
    }
    //}; //for


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


//
// Loop
//

    gws_debug_print("LOOP:\n");
    //printf ("LOOP:\n");

    // #debug
    //while (1){

    gws_draw_char ( 
        client_fd, main_window, 8, 8, COLOR_YELLOW, 'x' );

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
    // gws_async_command(client_fd,4,9,0); //cat





/*
//============================================================

    int i=0;
    int x=0;  int y=0;  int z=0;
    int offset=0;
    int T=0;

    //no translation
    offset=0;
    for(i=0; i<50; i++){
    gws_plot0(client_fd, x+offset,        0,        0, COLOR_RED   );
    gws_plot0(client_fd,        0, y+offset,        0, COLOR_GREEN );
    gws_plot0(client_fd,        0,        0, z+offset, COLOR_BLUE  );
    offset++;
    };

    // x translation
    T=8;
    offset=0;
    for(i=0; i<50; i++){
    gws_plot0(client_fd, x+offset+T,        0,        0, COLOR_RED   );
    gws_plot0(client_fd,        0+T, y+offset,        0, COLOR_GREEN );
    gws_plot0(client_fd,        0+T,        0, z+offset, COLOR_BLUE  );
    offset++;
    };

    
    // y translation
    T=8;
    offset=0;
    for(i=0; i<50; i++){
    gws_plot0(client_fd, x+offset,        0+T,        0, COLOR_RED   );
    gws_plot0(client_fd,        0, y+offset+T,        0, COLOR_GREEN );
    gws_plot0(client_fd,        0,        0+T, z+offset, COLOR_BLUE  );
    offset++;
    };
    
    // z translation
    T=8;
    offset=0;
    for(i=0; i<50; i++){
    gws_plot0(client_fd, x+offset,        0,        0+T, COLOR_RED   );
    gws_plot0(client_fd,        0, y+offset,        0+T, COLOR_GREEN );
    gws_plot0(client_fd,        0,        0, z+offset+T, COLOR_BLUE  );
    offset++;
    };

//============================================================
    */

    //
    // Loop
    //

    // #test
    gws_refresh_window (client_fd, main_window);
        

    //
    // Logon
    //

    logonInitialize(client_fd,w,h);


    //gameTestASCIITable(client_fd,w,h);


    // #test
    // Setup the flag to show or not the fps window.
    // Request number 6.

    gws_async_command(client_fd,6,FALSE,0);


    //=================================
    
    // get current thread
    // set foreground thread.
    // #todo: We need to create a rtl function for this.
    // See: rtl.c
    //int cThread = (int) pthread_self();
    //sc82 (10011,cThread,cThread,cThread);
    // rtl_focus_on_this_thread();
    
    // Enable input method number 1.
    // Event queue in the current thread.

    gws_enable_input_method(1);

    //=================================

            // Podemos chamar mais de um diálogo
            // Retorna TRUE quando o diálogo chamado 
            // consumiu o evento passado à ele.
            // Nesse caso chamados 'continue;'
            // Caso contrário podemos chamar outros diálogos.

    while (1){
        if ( rtl_get_event() == TRUE )
        {  
            logonProcedure ( 
                client_fd,
                (int) RTLEventBuffer[0], 
                (int) RTLEventBuffer[1], 
                (unsigned long) RTLEventBuffer[2], 
                (unsigned long) RTLEventBuffer[3] );
        }
    };
    //=================================


    // Isso ehestranho ... um cliente remoto nao deve poder fazer isso.
    //gws_debug_print ("gws: Sending command to close the server. \n");
    gws_async_command(client_fd,1,0,0);
    //exit(0);

    // Asking to server to send me an notification
    // telling me to close myself
    
    //gws_debug_print ("gws: Pinging\n");
    //gws_async_command(client_fd,2,0,0);


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
            gws_async_command(client_fd,1,0,0);
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




