/*
 * File: main.c
 * 
 *     Client application for gwssrv.
 * 
 * 2020 - Created by Fred Nora.
 */


// #todo
// #important
// You select an item by releasing the button over the menu item.


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
#include <rtl/gramado.h>


// libgws - The client-side library.
#include <gws.h>


// gwm - internal.
#include <gwm.h>


// Topbar
int topbarList[8];

// Taskbar
int taskbarList[8];

// Menu
struct gws_menu_d *menu0;
unsigned long menu0Itens[8];


//
// == Gramado Network Protocol ===============================
//

// Standard. (First version)
#define GNP_WID        0
#define GNP_MESSAGE    1
#define GNP_LONG1      2
#define GNP_LONG2      3
// #extension
#define GNP_LONG3      4
#define GNP_LONG4      5
#define GNP_LONG5      6
#define GNP_LONG6      7
//#body
#define GNP_BODY_OFFSET    16
// ...



int MOUSE_WINDOW = -1;

// i8042 mouse status bit.
#define MOUSE_LEFT_BTN    0x01
#define MOUSE_RIGHT_BTN   0x02
#define MOUSE_MIDDLE_BTN  0x04
#define MOUSE_X_SIGN      0x10
#define MOUSE_Y_SIGN      0x20
#define MOUSE_X_OVERFLOW  0x40
#define MOUSE_Y_OVERFLOW  0x80

long mouse_x = 0;
long mouse_y = 0;

char mouse_packet_data = 0;
char mouse_packet_x = 0;
char mouse_packet_y = 0;
char mouse_packet_scroll = 0;

char saved_mouse_x =0;
char saved_mouse_y =0;


//
// == ports ====================================
//

#define PORTS_WS 4040
#define PORTS_NS 4041
#define PORTS_FS 4042
// ...


// #test
#define MSG_OFFSET_SHORTSTRING  64
#define SHORTSTRING_SIZE        64
#define MSG_OFFSET_LONGSTRING  128
#define LONGSTRING_SIZE        256
// ...

// O buffer para  as mensagens recebidas via socket.
#define MSG_BUFFER_SIZE 512
char __buffer[MSG_BUFFER_SIZE];   


#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)



unsigned long savedW;
unsigned long savedH;



//
// == prototypes ======
//

int fullscreen_client (int fd, struct wm_client_d *c);
int center_client (int fd, struct wm_client_d *c);

int gwm_init_globals(void);
int gwm_init_windows(void);

// Clients
int create_bg_client(int fd);
int create_topbar_client(int fd);
int create_taskbar_client(int fd);
int create_tester_client(int fd);
void test_create_menu ( int fd, int window );
int update(int fd);



// Window dialog
// called by the event loop.
int 
gwmProcedure ( 
    int fd,
    int window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );



//
// ====================================================
//


// #test
// Create a enu given a window
void test_create_menu ( int fd, int window )
{

    int MenuOnTop = TRUE;

    struct gws_menu_d *menu;
    struct gws_menu_item_d *menu_item;
    unsigned long menuX=0;
    unsigned long menuY=0;


    if (fd<0){
        return;
    }

    if (window<0){
        return;
    }


    menuX = 0;
    menuY = (savedH -32 -300);   // altura, menos a taskbar, altura do menu

    if (MenuOnTop == TRUE)
    {
        menuX = 0;
        menuY = 32; // Depois da topbar
    }


    //#testing (NEW)
    menu = gws_create_menu (
                (int) fd,
                (int) window,
                (int) 0,                // highlight
                (int) 4,                // count
                (unsigned long) menuX,  // x
                (unsigned long) menuY,  // y
                (unsigned long) 280,
                (unsigned long) 280,
                (unsigned long) COLOR_WINDOW );

    if ((void*) menu == NULL)
    {
        return;
    }

    // save menu pointer
    menu0 = menu;
 
    // #todo
    // Check in the lib if the function returns something.
    // It is good to return some pointer to menuitem struct.
 
    //====================================
    //menu item
    menu_item = gws_create_menu_item (
        (int) fd,
        (char *) "F1",
        (int) 0,
        (struct gws_menu_d *) menu );
    menu0Itens[0] = (unsigned long) menu_item;

    //====================================
    //menu item
    menu_item = gws_create_menu_item (
        (int) fd,
        (char *) "F2",
        (int) 1,
        (struct gws_menu_d *) menu );
    menu0Itens[1] = (unsigned long) menu_item;

    //====================================
    //menu item
    menu_item = gws_create_menu_item (
        (int) fd,
        (char *) "F3",
        (int) 2,
        (struct gws_menu_d *) menu );
    menu0Itens[2] = (unsigned long) menu_item;

    //====================================
    //menu item
    menu_item = gws_create_menu_item (
        (int) fd,
        (char *) "F4",
        (int) 3,
        (struct gws_menu_d *) menu );
    menu0Itens[3] = (unsigned long) menu_item;
}


// Window procedure.
int 
gwmProcedure (
    int fd, 
    int window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    //printf ("gwmProcedure:\n");


    switch (msg){

        case MSG_SYSKEYDOWN:
            switch(long1)
            {
                case VK_F1:
                    printf ("F1\n");
                    break;

                case VK_F2:
                    printf ("F2\n");
                    //create_tester_client(fd);
                    //test_create_menu (fd,c_tester->window);
                    test_create_menu (fd,c_bg->window);
                    //gws_refresh_window(fd,c_topbar->window);
                    break;
                
                case VK_F3: 
                    update(fd); 
                    //gws_redraw_window (fd, c_bg->window, 1);
                    //gws_redraw_window (fd, c_topbar->window, 1);
                    //gws_redraw_window (fd, c_taskbar->window, 1);
                    //gws_refresh_window(fd,c_topbar->window);
                    
                    //gws_draw_text(
                    //    fd, c_bg->window,
                    //    80, 80, COLOR_YELLOW, "DUCK");
                        
                    break;
            };
            break;

        case MSG_SYSKEYUP:
            //printf ("MSG_SYSKEYUP:\n");
            break;
    };

    return 0;
}


/*
 * =====================================================
 * update_mouse:
 *     Updates the mouse position.
 */

void update_mouse (void){

//======== X ==========
// Testando o sinal de x.
// Do the x pos first.

//pega o delta x
//testa o sinal para x
do_x:

    if ( mouse_packet_data & MOUSE_X_SIGN ) 
    {
        goto x_neg;
    }


//Caso x seja positivo.
x_pos:

    mouse_x += mouse_packet_x;
    goto do_y;


//Caso x seja negativo.
x_neg:

    mouse_x -= ( ~mouse_packet_x + 1 );

    if (mouse_x > 0)
    {
        goto do_y;
    }
    mouse_x = 0;
 
 
//======== Y ==========
// Testando o sinal de x. 
// Do the same for y position.

//Pega o delta y.
//Testa o sinal para y.
do_y:

    if ( mouse_packet_data & MOUSE_Y_SIGN )
    {
        goto y_neg;
    }


//Caso y seja positivo.
y_pos:

    mouse_y -= mouse_packet_y;

    if ( mouse_y > 0 )
    {
        goto quit;
    }

    mouse_y = 0;
    goto quit;


//Caso y seja negativo. 
y_neg:

    mouse_y += ( ~mouse_packet_y + 1 );

// Quit
quit:
    return;
}



void parse_data_packet (int fd, char data, char x, char y)
{

    if (fd<0) 
        return;

	// A partir de agora já temos os três chars.
	// Colocando os três chars em variáveis globais.
	// Isso ficará assim caso não haja overflow.
    // acho que isso sera usado na rotina de update.
    
    mouse_packet_data = (char) data;    // Primeiro char
    mouse_packet_x    = (char) x;    // Segundo char.
    mouse_packet_y    = (char) y;    // Terceiro char.

	// Salvando o antigo antes de atualizar.
	// Para poder apagar daqui a pouco.
	// Atualizando.
    saved_mouse_x = mouse_x;
    saved_mouse_y = mouse_y;
    
    //
    // == Update mouse position ====================
    //
    
    update_mouse (); 
    
    // Agora vamos manipular os valores obtidos através da 
    // função de atualização dos valores.
    // A função de atualização atualizou os valores de
    // mouse_x e mouse_y.
    mouse_x = (mouse_x & 0x000003FF );
    mouse_y = (mouse_y & 0x000003FF );



        if ( MOUSE_WINDOW > 0 ){

            gws_change_window_position(fd,MOUSE_WINDOW, mouse_x, mouse_y);
            //gws_change_window_position(fd,c_tester->title_window, i*10, i*10);

            gws_redraw_window(fd,MOUSE_WINDOW,1); 
            //gws_redraw_window(fd,c_tester->title_window,1); 
        }
}



int fullscreen_client (int fd, struct wm_client_d *c)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);
    
    if ( (void *) c != NULL )
    {
        if(c->used == 1)
        {
            gws_change_window_position(fd,c->window, 0, 0);  // x,y
            gws_resize_window(fd,c->window, w, h);           // w,h
            gws_redraw_window(fd,c->window,1); 
        }  
    }

    return 0;
}




int center_client (int fd, struct wm_client_d *c)
{
    //screen
    unsigned long sw = gws_get_system_metrics(1);
    unsigned long sh = gws_get_system_metrics(2);
    
    //window
    unsigned long ww= sw/3;
    unsigned long wh= sh/3;
 
 
    if ( (void *) c != NULL )
    {
        if(c->used == 1)
        {

            //resize
            gws_resize_window(fd,c->window, ww, wh );     //w,h
            
            //position
            gws_change_window_position(fd,c->window, 
                ((sw-ww)/2), 
                ((sh-wh)/2) );  
            
            //redraw and show
            gws_redraw_window(fd,c->window,1); 
        }  
    }

    return 0;
}




int gwm_init_globals(void)
{
    gws_debug_print("gwm_init_globals:\n");
    
    gScreenWidth  = gws_get_system_metrics(1);
    gScreenHeight = gws_get_system_metrics(2);
    
    
    if (gScreenWidth==0 || gScreenHeight==0)
        gws_debug_print("gwm_init_globals: w h fail\n");
    
    //...
    
    
    return 0;
}


// Init windows.

int gwm_init_windows(void)
{
    int i=0;

    gws_debug_print("gwm_init_windows:\n");


    // Init window list.

    for (i=0; i<WINDOW_COUNT_MAX; i++)
    {
        windowList[i] = 0;
    };
    
 
    // Not selected yet.
    active_window = -1;
    window_with_focus = -1;
    // ...   

    //gws_debug_print("gwm_init_windows: done\n");
    return 0;
}


/*
void
update_all_windows(int fd);
void
update_all_windows(int fd);
{
    struct wm_client_d  *c;
    int i=0;
    
    for (i=0; i<9; i++)
    {    
        c = (struct wm_client_d  *) wmclientList[i];
            
        if ( (void*) c != NULL )
        {
            if(c->used == 1)
            {
                if(c->focus == 1)
                {
                    gws_redraw_window(fd,c->window,1); 
                }else{
                    gws_redraw_window(fd,c->window,1);
                };
            }
        }
    };
}
*/


// ...



//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/


/*
//internal
void scan_windows(int fd)
{
    int max=0;  //how many windows.
    int wList[1024];
    int wid=0;
    int tail=0;
    
    max = gws_window_list(fd);
    
    for(i=0; i<max; i++){

        //get the window id of a given index.
        wid = gws_is_window(fd,i);    
        if ( wid >= 0 && wid < 1024 ){
            wList[tail] = wid;
            tail++;
            if(tail > 1024){
                gws_debug_print("fail\n");
                return;
            }
        }
    };
}
*/

/*
void draw_client( struct wm_client_d *c);
void draw_client( struct wm_client_d *c)
{
    if ( (void*) c == NULL ) return;
    
    if ( c == c_topbar )
    {
        //todo
        return;
    }

    if ( c == c_taskbar )
    {
        //todo
        return;
    }

    // draw title window
    // draw title
}
*/



/*
int draw_frame ( int fd, struct wm_client_d * client, int type );
int draw_frame ( int fd, struct wm_client_d * client, int type )
{
    if( (void*) client == NULL)
        return -1;

    if (client->window < 0)
        return -1;
        
    // #todo
    // We need the window's metrics.
    // Ask the window server.
    
    //title window
    client->title_window = gws_create_window (fd,
                               WT_SIMPLE,1,1,"title",
                               100, 100-32, 480, 32,     //#todo
                               0, 0, 0x2d89ef, 0x2d89ef);


    if(client->title_window<0)
        return -1;

    return 0;
}
*/



int create_bg_client(int fd)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);


    savedW = w;
    savedH = h;
    
    //if (fd<0)
        //return -1;


    //Setup hot spot.
    hot_spot.x = (w/2);
    hot_spot.y = (h/2);


    //
    // == bg (Client) ==================================
    // 
    
    gws_debug_print ("gwm: Create c_bg client\n");

    c_bg = (struct wm_client_d *) malloc ( sizeof(struct wm_client_d) );

    if( (void *) c_bg == NULL){
        printf ("gwm: c_bg fail\n");
        exit(1);
    }else{

        c_bg->used  = TRUE;
        c_bg->magic = 1234;
        c_bg->dirty = FALSE;
        c_bg->focus = FALSE;

        sprintf( c_bg->name, "name");

        //c_bg
        c_bg->window = gws_create_window (fd,
            WT_SIMPLE,1,1,"BG",
            0, 0, w, h,
            0,0, 0xD5D5D5, 0xD5D5D5); 
        
        if (c_bg->window < 0){
            printf ("gwm: c_bg->window fail\n");
            exit(1);
        }
        //printf ("w={%x}\n",c_bg->window);
        gws_refresh_window(fd,c_bg->window);

        wmclientList[0] = (unsigned long) c_bg;
    };

    //
    // == Mouse window ==================
    //

    // Window.
    MOUSE_WINDOW = gws_create_window (
                       fd,
                       WT_SIMPLE,1,1,"Mouse",
                       hot_spot.x, hot_spot.y, 4, 4,
                       0, 0, COLOR_BLACK, COLOR_BLACK );

    if ( MOUSE_WINDOW < 0){
        printf ("gwm: MOUSE_WINDOW fail\n");
        exit(1);
    }

    return 0;
}


// internal
// Create the top bar and one button.

int create_topbar_client(int fd)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    int button1_window = -1;

    //if (fd<0)
        //return -1;

    //
    // == Topbar (Client) ==================================
    // 
    
    // Topbar
    gws_debug_print ("gwm: Create c_topbar client\n");
    c_topbar = (struct wm_client_d *) malloc ( sizeof(struct wm_client_d) );

    if( (void *)c_topbar == NULL){
        printf ("gwm: c_topbar fail\n");
        exit(1);
    }else{

        c_topbar->used  = TRUE;
        c_topbar->magic = 1234;
        c_topbar->dirty = FALSE;
        c_topbar->focus = FALSE;

        sprintf( c_topbar->name, "name");
        
        // topbar widnow.
        c_topbar->window = gws_create_window (fd,
                             WT_SIMPLE, 1, 1, "Topbar",
                             0, 0, w, 32,
                             0, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );

        // #todo
        // We need to register this window.
        
        if(c_topbar->window < 0){
            printf ("gwm: c_topbar->window fail\n");
            exit(1);
        }
        //printf ("w={%x}\n",c_topbar->window);
        gws_refresh_window(fd,c_topbar->window);

        // button1 (system menu)
        button1_window = gws_create_window (fd,
                             WT_BUTTON,1,1,"=",
                             2, 2, 32, 28,
                             c_topbar->window, 0,COLOR_GRAY, COLOR_GRAY);
        
        // #todo
        // We need to register this window.
        
        topbarList[0] = button1_window;
        
        c_topbar->title_window = -1;  //todo;
        wmclientList[1] = (unsigned long) c_topbar;
    };

    return 0;
}


// interna
int create_taskbar_client(int fd)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    //
    // == Taskbar (Client) ==================================
    //
    
    int button1_window = -1;
    int button2_window = -1;


    //if (fd<0)
        //return -1;


    // Taskbar
    gws_debug_print ("gwm: Create c_taskbar client\n");
    c_taskbar = (struct wm_client_d *) malloc ( sizeof(struct wm_client_d) );
    if( (void *)c_taskbar == NULL ){
        printf ("gwm: c_taskbar fail\n");
        exit(1); 
    }else{

        c_taskbar->used  = TRUE;
        c_taskbar->magic = 1234;
        c_taskbar->dirty = FALSE;
        c_taskbar->focus = FALSE;

        sprintf( c_taskbar->name, "name");

        c_taskbar->window = gws_create_window (
                                fd,
                                WT_SIMPLE,1,1,"Taskbar",
                                0, (h-32), w, 32,
                                0,0,COLOR_GRAY, COLOR_GRAY);

        // #todo
        // We need to register this window.

        if( c_taskbar->window < 0){
            printf ("gwm: c_taskbar->window fail\n");
            exit(1);
        }
        
        //printf ("w={%x}\n",c_taskbar->window);
        gws_refresh_window(fd,c_taskbar->window);
         
        c_taskbar->title_window = -1;  //todo 

        // ================================
        // button1
        button1_window = gws_create_window (fd,
                              WT_BUTTON,1,1,"App1",
                              2, 2, 120, 28,
                              c_taskbar->window, 0,COLOR_GRAY, COLOR_GRAY);

        taskbarList[0] = button1_window;

        // ================================
         // button2
        button2_window = gws_create_window (fd,
                              WT_BUTTON,1,1,"App2",
                              2 + 120 + 2, 2, 120, 28,
                              c_taskbar->window, 0,COLOR_GRAY, COLOR_GRAY);

        taskbarList[1] = button2_window;

        wmclientList[2] = (unsigned long) c_taskbar;
    };

    return 0;
}


//interna
int create_tester_client(int fd)
{
    int CreateMenu=FALSE;

    struct gws_menu_d *menu;

    //
    // == Tester (Client) ==================================
    // 

    int tester_button=-1;
    
    
    //if (fd<0)
        //return -1;

    
    //gws_enter_critical_section();
    gws_debug_print ("gwm: Create c_tester client\n");


    c_tester = (struct wm_client_d *) malloc( sizeof(struct wm_client_d ) );

    if( (void *) c_tester == NULL){
         printf ("gwm: c_tester fail\n");
         exit(1);
    }

    if ( (void *) c_tester != NULL )
    {
        c_tester->used  = TRUE;
        c_tester->magic = 1234;
        c_tester->dirty = FALSE;
        c_tester->focus = FALSE;

        sprintf( c_tester->name, "name");

        // Window
        c_tester->window = gws_create_window ( 
                               fd,
                               WT_SIMPLE, 1, 1,"Tester",
                               8, 100, 320, 200,
                               0, 0, COLOR_GRAY, COLOR_GRAY );
        
        if ( c_tester->window < 0){
            printf ("gwm: c_tester->window fail\n");
            exit(1);
        }
        //printf ("tester window = {%d}\n",c_tester->window);
        gws_refresh_window(fd,c_tester->window);
        
        // Title window.
        c_tester->title_window = gws_create_window ( fd,
                                     WT_SIMPLE,1,1,"Tester Title",
                                     8, 100-32, 320, 32,
                                     0,0,0x2d89ef,0x2d89ef);

        if ( c_tester->title_window < 0 ){
            printf ("gwm: c_tester->title_window fail\n");
            exit(1);
        }

        // Tester title window
        // #bugbug: 
        // pagefault. The size of the string overflows the button size.
        tester_button = gws_create_window (fd,
             WT_BUTTON,1,1,"X", 
             (320-36-2), 2, 36, 28, 
             c_tester->title_window, 0, COLOR_RED, COLOR_RED);
             
        
        // save
        wmclientList[3] = (unsigned long) c_tester;
    } 
    //gws_exit_critical_section();


//
//  menu ==========
//


    if ( (void*) c_tester == NULL ){
        return -1;
    }

    if ( (void*) c_tester->window == NULL ){
        return -1;
    }

    if ( CreateMenu == FALSE ){
        return 0;
    }


    // Create menu.

    menu = gws_create_menu (
               (int) fd,
               (int) c_tester->window,
               (int) 0,            //highlight
               (int) 4,            //count
               (unsigned long) 1,  //x
               (unsigned long) 1,
               (unsigned long) 200,
               (unsigned long) 200,
               (unsigned long) COLOR_WHITE );

    // Create itens.

    if ((void*) menu != NULL)
    {
        gws_create_menu_item (
           (int) fd,
           (char *) "Item0",
           (int) 0,
           (struct gws_menu_d *) menu );

        gws_create_menu_item (
            (int) fd,
            (char *) "Item1",
            (int) 1,
            (struct gws_menu_d *) menu );

        gws_create_menu_item (
            (int) fd,
            (char *) "Item2",
            (int) 2,
            (struct gws_menu_d *) menu );

        gws_create_menu_item (
            (int) fd,
            (char *) "Item3",
            (int) 3,
            (struct gws_menu_d *) menu );
    }


    /*
    //
    // == Sprite =================================
    //
    int thechar = 1;
    int thecharx = 10;
    int thechary = 10;
    while(1){
 
        //redrawtitle window and button.
        gws_redraw_window(fd,c_tester->title_window,1); 
        //gws_redraw_window(fd,tester_button,1); 

        gws_draw_char (
            (int) fd,             // fd,
            (int) c_tester->title_window,              // window id,
            (unsigned long) thecharx,    // left,
            (unsigned long) thechary,    // top,
            (unsigned long) COLOR_RED,
            (unsigned long) thechar );  //CHAR
    
        thechar++;
        if( thechar>4 )
        {
            thechar=1;

            thecharx = (thecharx + 8);
            if ( thecharx > 400 )
                thecharx = 10;
        }
        
        gws_yield();
        gws_yield();
        gws_yield();
        gws_yield();
    };
    */
    


    // Testing more things ....
    
    /*
    // Ok. Not bad!
    // Need to fix the button's labal redraw!
    int i=0;
    for(i=0; i<16; i++){

        // #bugbug
        // We can't change it in buttons.
        
        gws_change_window_position(fd,c_tester->window, i*10, i*10);
        gws_change_window_position(fd,c_tester->title_window, i*10, i*10);
        gws_change_window_position(fd,tester_button, 1, 1);
        
        //gws_resize_window(fd,c_tester->window, i*20, i*20);
        
        gws_redraw_window(fd,c_tester->window,1); 
        gws_redraw_window(fd,c_tester->title_window,1); 
        gws_redraw_window(fd,tester_button,1); 
        //...
    };
    */
    
    // #test
    // button
    // Ok, but the label fails.
    //gws_change_window_position(fd,tester_button, (480-36-2), 2); //1, 1);
    //gws_redraw_window(fd,tester_button,1); 


    // full screen
    // ok
    //fullscreen_client (fd,c_tester);


    //put in the center.
    //center_client (fd, c_tester);

    return 0;
}


// Update all
int update(int fd)
{
    struct wm_client_d  *c;
    int i=0;


    debug_print ("update: [FIXME]\n");

    // bg, topbar, taskbar

    if ( (void*) c_bg != NULL ){
        gws_redraw_window(fd,c_bg->window,TRUE);
        if ( (void*) c_topbar != NULL ){
            gws_redraw_window(fd,c_topbar->window,TRUE);
            if ( (void*) c_taskbar != NULL ){
                gws_redraw_window(fd,c_taskbar->window,TRUE);
                //goto _more;
            }
        }
    }

    //return -1;
/*
_more:
    
    //0=bg 1=topbar 2=taskbar
    for ( i=3; i<32; i++ )
    {
        c = (struct wm_client_d *) wmclientList[i];
        if ( (void*) c != NULL ){
            gws_redraw_window(fd,c->window,1);
        }
    };
*/

    return 0;
}



// Testing new main.
int main ( int argc, char *argv[] ){

    int fd = -1;

    // Porta para o Window Server 'ws' em gramado_ports[]
    // Connecting to the window server in this machine.
    struct sockaddr_in  addr_in;

    addr_in.sin_family      = AF_INET;
    addr_in.sin_port        = PORTS_WS;
    addr_in.sin_addr.s_addr = IP(127,0,0,1); 


    debug_print ("---------------------\n");
    debug_print ("gwm: Initializing ...\n");


    //
    // socket
    // 

    // #debug
    //printf ("gwm: Creating socket\n");

    // cria o soquete.
    // AF_GRAMADO
    //fd = socket ( 8000, SOCK_STREAM, 0 );
    //fd = socket ( AF_INET, SOCK_RAW, 0 );
    fd = socket ( AF_INET, SOCK_STREAM, 0 );
        
    if ( fd < 0 ){
       printf ("gwm: Couldn't create socket\n");
       exit(1);
    }

    //
    // connect
    // 

    // Nessa hora colocamos no accept um fd.
    // então o servidor escreverá em nosso arquivo.

    // #debug
    //printf ("gnst: Connecting to the address 'ws' ...\n");      
    printf ("gwm: Connecting to ws via inet  ...\n");   

    while (1){
        if (connect (fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
            gws_debug_print ("gwm: Connection Failed \n");
            printf          ("gwm: Connection Failed \n"); 
            //return -1;
            //try again 
        }else{ break; }; 
    };

    //
    // Draw
    //

    printf ("gwm: DRAW\n");



    //
    // Create clients.
    //
    
    create_bg_client(fd);
    create_topbar_client(fd);
    create_taskbar_client(fd);
    // ...

    
    gws_debug_print ("gwm: draw done!\n");
    //printf          ("gwm: draw done!\n");

    //gws_show_background();
    //while(1){}

    //
    // == Loop ==============================
    //

    //=================================
    //get current thread
    //set foreground thread

    //int cThread = (int) sc82 (10010,0,0,0);
    //sc82 (10011,cThread,cThread,cThread);

    rtl_focus_on_this_thread();

    while (1){
        if ( rtl_get_event() == TRUE ){  
            gwmProcedure ( 
                fd,
                RTLEventBuffer[0], 
                RTLEventBuffer[1], 
                RTLEventBuffer[2], 
                RTLEventBuffer[3] );
        }
    };
    //=================================


    // #debug
    // while(1){}



    // #importante
    // Se não usarmos o loop acima, então podemos pegar
    // as mensagens do sistema....
    // O ws pode mandar mensagens de sistema para o
    // wm registrado.


    /*
    struct gws_event_d *Event;
     
    for(;;){
        
        Event = (struct gws_event_d *) gws_next_event();
        
        if (Event.type == 0){
           gws_debug_print("gwm: event 0\n");
        
        }else if (Event.type == 1){
           gws_debug_print("gwm: event 1\n");
        
        }else if (Event.type == 2){
           gws_debug_print("gwm: event 2\n");
        
        }else{
           gws_debug_print("gwm: Not valid event!\n");
        };
    };
    */



// exit
    debug_print ("gwm: bye\n"); 
    printf      ("gwm: bye\n");

    return 0;
}


//
// End.
//








