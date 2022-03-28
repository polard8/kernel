/*
 * File: main.c
 *
 *    Browser application. UI.
 *
 * 2020 - Created by Fred Nora.
 */


// rtl 
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <packet.h>

// The client-side library.
#include <gws.h>


//
// == ports ====================================
//

#define PORTS_WS 4040
#define PORTS_NS 4041
#define PORTS_FS 4042
// ...


#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)


//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/


static int __main_window = -1;
static int __addressbar_window = -1;
static int __button_window = -1;
static int __client_window = -1;


//prototype
static int 
browserProcedure(
    int fd, 
    int event_window, 
    int event_type, 
    unsigned long long1, 
    unsigned long long2 );

// local
static int 
browserProcedure(
    int fd, 
    int event_window, 
    int event_type, 
    unsigned long long1, 
    unsigned long long2 )
{
    if(fd<0)
        return -1;
    if(event_window<0)
        return -1;
    if(event_type<0)
        return -1;


    switch(event_type){

    // Evento de teste.
    case 1000:
        // If the event window is the main window, so
        // redraw client window
        if( event_window == __main_window ){
            gws_redraw_window(fd,__client_window,TRUE);
            return 0;
        }
        break;

    //case ?:
        //break;

    //...
    
    default:
        return -1;
        break;
    };

    return -1;
}



int main ( int argc, char *argv[] )
{
    int client_fd = -1;

    // Porta para o Window Server 'ws' em gramado_ports[]
    struct sockaddr_in addr_in;

    addr_in.sin_family      = AF_INET;
    addr_in.sin_port        = PORTS_WS;   
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 112); 


    //debug_print ("-------------------------\n");
    debug_print ("browser: Initializing ...\n");


// Device info.
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    if ( w == 0 || h == 0 ){
        printf ("browser: w h \n");
        exit(1);
    }


//
// socket
// 

    // #debug
    printf ("browser: Creating socket\n");

    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( client_fd < 0 ){
       printf ("browser: Couldn't create socket\n");
       exit(1);
    }


//
// connect
// 

// Nessa hora colocamos no accept um fd.
// Então o servidor escreverá em nosso arquivo.

// #debug
    printf ("browser: Connecting to the address via inet  ...\n");    

    while (TRUE){
        if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
            debug_print("browser: Connection Failed \n"); 
            printf     ("browser: Connection Failed \n"); 
        }else{ break; }; 
    };


// ==============================================

// #todo: 
// Salvar em global.
// Por enquanto aqui.

    int main_window=0;
    int addressbar_window=0;    
    int client_window=0;
    int button=0;

// A janela é a metade da tela.
    unsigned long w_width  = (w/2);
    unsigned long w_height = (h/2); 

    unsigned long viewwindowx = ( ( w - w_width ) >> 1 );
    unsigned long viewwindowy = ( ( h - w_height) >> 1 );


    if ( w == 320 )
    {
        // dimensoes
        w_width  = w;
        w_height = h;
        
        // posicionamento
        viewwindowx = 0;
        viewwindowy = 0;
    }


// ===================
// main window
// style: 
// 0x0001=maximized | 0x0002=minimized | 0x0004=fullscreen | 0x0008 statusbar

    main_window = gws_create_window ( 
                      client_fd,
                      WT_OVERLAPPED, 1, 1, "Browser",
                      viewwindowx, viewwindowy, w_width, w_height,
                      0, 
                      0x0000,  
                      COLOR_GRAY, COLOR_GRAY );

    if ( main_window < 0 ){
        debug_print("browser: main_window fail\n"); 
        exit(1);
    }
    
    if ( main_window > 0 ){
        // Save globally.
        __main_window = main_window;
    }

// ===================
// address bar
    addressbar_window = gws_create_window (
                            client_fd,
                            WT_EDITBOX,1,1,"AddressBar",
                            4, 32 +4, 
                            (w_width-32-4-4-4), 32,
                            main_window, 0, COLOR_WHITE, COLOR_WHITE );

    if ( addressbar_window < 0 ){
        debug_print("browser: addressbar_window fail\n"); 
    }

// IN: 
// fd, window id, left, top, color, string
    if( addressbar_window > 0 ){
        __addressbar_window = addressbar_window;
        gws_draw_text (
            (int) client_fd,
            (int) addressbar_window,
             8, 8, (unsigned long) COLOR_BLACK,
            "https://github.com/frednora");
    }

// ===================
// button
    button = gws_create_window (client_fd,
        WT_BUTTON,1,1,">",
        (w_width-32-4), 32 +4, 
        32, 32,
        main_window, 0, COLOR_GRAY, COLOR_GRAY );

    if ( button < 0 ) 
        debug_print("browser: button fail\n"); 

    if(button>0)
        __button_window=button;

// ===================
// client window (White)
    client_window = gws_create_window (client_fd,
        WT_SIMPLE,1,1,"client",
        4, 32 +40, 
        w_width-8, w_height - 40 - 4 -32,
        main_window, 0, COLOR_WHITE, COLOR_WHITE );

    if ( client_window < 0 )             
        debug_print("browser: client_window fail\n"); 

    if ( client_window > 0 )
    {
        // Save globally.
        __client_window = client_window;
        
        gws_draw_text (
            (int) client_fd,        // fd,
            (int) client_window,    // window id,
            (unsigned long) 40,     // left,
            (unsigned long) 40,     // top,
            (unsigned long) COLOR_BLACK,
            "Hello there!");
    }

//
// Refresh
//
    gws_refresh_window( client_fd, main_window );


// ============================================
// focus
// Editbox!

    gws_async_command(
         client_fd,
         9,             // set focus
         addressbar_window,
         addressbar_window );

// =======================================================

//
// Loop
//


//HANG:
    //while(1){}

    // This event routine is working fine.

// #test
// pegando um evento com o ws.
// See: libgws/

    struct gws_event_d lEvent;
    lEvent.used = FALSE;
    lEvent.magic = 0;
    lEvent.type = 0;
    lEvent.long1 = 0;
    lEvent.long2 = 0;

    struct gws_event_d *e;

// loop
// Call the local window procedure 
// if a valid event was found.

    while (1)
    {
        e = (struct gws_event_d *) gws_get_next_event(
                client_fd, 
                (struct gws_event_d *) &lEvent );
        
        if( (void *) e != NULL )
        {
            if( e->used == TRUE && e->magic == 1234 )
            {
                browserProcedure(
                    client_fd, e->window, e->type, e->long1, e->long2 );
            }
        }
    };


//HANG:
    while(1){}

    debug_print ("browser: bye\n"); 
    printf      ("browser: bye\n");

    return 0;
}


//
// End.
//








