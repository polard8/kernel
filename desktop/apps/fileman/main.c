/*
 * File: main.c
 * File manager. (Gramado Shell)
 * 2020 - Created by Fred Nora.
 */

// rtl
#include <rtl/gramado.h>
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
// The client-side library
#include <gws.h>
// Local
#include <packet.h>
#include <fileman.h>

// Ports
#define PORTS_WS  4040
#define PORTS_NS  4041
#define PORTS_FS  4042
// ...
#define IP(a, b, c, d)  (a << 24 | b << 16 | c << 8 | d)

/*
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/
//char *hello = "Hello there!\n";

unsigned long gScreenWidth=0;
unsigned long gScreenHeight=0;

// ==================================================
// Windows

// :: main window
static int Main_window = 0;

// :: Header window
// The top window has two windows: The address bar and the button.
static int Header_window = 0;
static int addressbar_window = 0;
static int button = 0;
// :: The menu window
// That one at the left side.
static int Menu_window = 0;
// :: The logo window
static int Logo_window = 0;
static int lw_button1 = 0;
// :: The navigation window
//static int Navigation_window = 0;
//static int nw_button1 = 0;
//static int nw_button2 = 0;
//static int nw_button3 = 0;
// :: Client window
static int Client_window = 0;
// ============================================

//#bugbug: Cuidado, isso varia com a resolução.
#define NUMBER_OF_WINDOWS  4
int gMaxIndex = NUMBER_OF_WINDOWS;
int windows[NUMBER_OF_WINDOWS];

// JAIL,P1 ...
static int current_mode=0;


// ================

static int 
filemanProcedure(
    int fd,
    int wid,
    int msg,
    unsigned long long1,
    unsigned long long2 );

static void barPrompt(void);
static int fileman_init_globals(void);
static int fileman_init_windows(void);
static int barInputChar(int c);
static int barCompareStrings(void);

static int do_event_loop(int fd);

// ================

static int fileman_init_globals(void)
{
    gws_debug_print("fileman_init_globals:\n");
    gScreenWidth  = gws_get_system_metrics(1);
    gScreenHeight = gws_get_system_metrics(2);
    //...
    return 0;
}

static int fileman_init_windows(void)
{
    register int i=0;
    for (i=0; i<WINDOW_COUNT_MAX; i++){
        windowList[i] = 0;
    };
    return 0;
}

static int barCompareStrings(void)
{
    char c=0;
    c = (char) prompt[0];

    //debug_print("barCompareStrings: \n");

// =============================
// Emergency 

// reboot
    if(c=='q'){
        rtl_reboot();
        //gws_reboot(fd);
    }
// 
    if(c=='1')
        rtl_clone_and_execute("browser.bin");
//
    if(c=='2')
        rtl_clone_and_execute("editor.bin");
//
    if(c=='3')
        rtl_clone_and_execute("logon.bin");
//
    if(c=='4')
        rtl_clone_and_execute("terminal.bin");

/*
// reboot
// #bugbug: It is not working
    //if( strcmp(prompt,"reboot") == 0 )
    if ( strncmp( prompt, "reboot", 6 ) == 0 )
    {
        printf("reboot:\n");
        gws_reboot();
        goto exit_cmp;
    }
*/

    printf("Typed String:{%s}\n",prompt);

// #test
    //gws_clone_and_execute( (char*) &prompt[0] );

exit_cmp:
   //nothing
done:
    barPrompt();
    return 0;
}

static void barPrompt (void)
{
    register int i=0;

// Clean prompt[] buffer.
// This is a buffer inside the libc.
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
        prompt[i] = (char) '\0';
    };
    prompt[0] = (char) '\0';
    prompt_pos    = 0;
    prompt_status = 0;
    prompt_max    = PROMPT_MAX_DEFAULT;  

// #todo
// We need to change the cursor position inside the 
// editbox.

    // Prompt
    //printf("\n");
    //printf("$ ");

    //invalidate_screen();
    //refresh_screen();

    //gws_refresh_screen();
}

// Coloca no prompt[] para ser comarado.
// Talvez o prompt também seja o buffer de stdin
static int barInputChar(int c)
{
    unsigned long ascii=0;
    ascii = (unsigned long) (c & 0xFF);

    return (int) input(ascii);
}

static int 
filemanProcedure(
    int fd,
    int wid,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{
    if (fd<0){
        return (int) -1;
    }
    if (msg<0){
        return (int) -1;
    }

    switch (msg)
    {
        // keydown
        case MSG_KEYDOWN:
            switch(long1)
            {
                // [ENTER]
                case VK_RETURN: 
                    input('\n');
                    barCompareStrings();
                    return 0;
                    break;

                case 0x4B: 
                    printf ("LEFT\n"); 
                    return 0;
                    break;

                case 0x4D: 
                    printf ("RIGHT\n"); 
                    return 0;
                    break;

                // Teclas de digitação.
                default:
                    barInputChar( (int) long1 );
                    return 0;
                    break;
            };
            break;

        // syskeydown
        // It works because the fileman is getting input from
        // the control thread not from the file.
        case MSG_SYSKEYDOWN:
            switch (long1)
            {
                case VK_F1: 
                    rtl_clone_and_execute("cmdline.bin");
                    return 0;
                    break;

                case VK_F2: 
                    rtl_clone_and_execute("editor.bin");
                    return 0;
                    break;

               // main window
               case VK_F3: 
                    gws_resize_window(fd,Main_window,320,200);
                    gws_redraw_window(fd,Main_window,TRUE);
                    //gws_refresh_window(fd,Main_window);
                    return 0;
                    break;

               // menu window
               case VK_F4: 
                    gws_resize_window(fd,Menu_window,400,400);
                    gws_redraw_window(fd,Menu_window,TRUE); // redraw and show
                    //gws_refresh_window(fd,Menu_window);
                    return 0;
                    break;
            };
            break;

        case MSG_CLOSE:
            printf ("fileman.bin: MSG_CLOSE\n");
            gws_destroy_window(fd,Main_window);
            exit(0);
            break;

        default:
            break;
    };

    return 0;
}


static int do_event_loop(int fd)
{
    if(fd<0)
        return -1;

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
        //if (isTimeToQuit == TRUE)
            //break;

        e = (struct gws_event_d *) gws_get_next_event(
                fd, 
                Main_window,
                (struct gws_event_d *) &lEvent );

        if ( (void *) e != NULL )
        {
            //if( e->used == TRUE && e->magic == 1234 )
            if (e->magic == 1234)
            {
                //browserProcedure( 
                //    fd, e->window, e->type, e->long1, e->long2 );

                filemanProcedure ( 
                    (int) fd,
                    (int) e->window, 
                    (int) e->type, 
                    (unsigned long) e->long1, 
                    (unsigned long) e->long2 );
            }
        }
    };

// Exit application withou error.
    return 0;
}


//
// Main
//

int main ( int argc, char *argv[] )
{
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = PORTS_WS;
    addr_in.sin_addr.s_addr = IP(127,0,0,1);

    int client_fd = -1;

    debug_print ("fileman: Initializing ...\n");

//
// Testing parameters
//

    int fA = FALSE;  //FAKE FLAG
    int i=0;
    // percorre todos os argumentos
    for (i=0; i<argc; i++)
    {
       // Se em algum momento a flag for '-a'.
        if ( strncmp( argv[i], "-a", 2 ) == 0 ){
            fA = TRUE;
        }
    };
    if(fA==TRUE){
        printf("fileman: #test flag '-a'\n");
        //exit(0);
    }

// dc
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);
// Gramado mode.
    current_mode = rtl_get_system_metrics(130);
// #debug
    //printf ("The current mode is %d\n",current_mode);
    //exit(0);

// socket
    client_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if (client_fd<0){
        printf ("fileman: Couldn't create socket\n");
        exit(1);
    }

// connect
// Nessa hora colocamos no accept um fd.
// então o servidor escreverá em nosso arquivo.
    while (1){
        if (connect(client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){
            gws_debug_print("fileman: Connection Failed \n");
            printf         ("fileman: Connection Failed \n");
        }else{ break; }; 
    };

//
// == Main window ==============
//

    unsigned long wWidth  = (w >> 1);
    // #hack
    if (w == 800)
        wWidth = 640;
    // #hack
    if (w == 640)
        wWidth = 480;
    unsigned long wHeight = (h - 100);
    unsigned long wLeft   = (w - wWidth)  >> 1;
    unsigned long wTop    = (h - wHeight) >> 1;
    // #hackhack
    unsigned long titlebarHeight = 32;

// Small screen
    if (current_mode == GRAMADO_JAIL)
    {
        wLeft = 0;
        wTop  = 0;
        wWidth  = w;
        wHeight = (h-40);
    }

// Main window
// style: 
// See: window.h
// WS_FULLSCREEN WS_MAXIMIZED WS_STATUSBAR
    Main_window = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_OVERLAPPED, 1, 1, "GRAMADO SHELL",
                  wLeft, wTop, wWidth, wHeight,
                  0,
                  WS_STATUSBAR,//(WS_TRANSPARENT | WS_STATUSBAR),
                  COLOR_GRAY, 
                  COLOR_GRAY );

    if (Main_window < 0){
        debug_print("fileman: Main_window fail\n");
        printf     ("fileman: Main_window fail\n");
        exit(1);
    }

//
// == Header_window ======================
//

// Como nossa janela mãe é overlapped,
// então estamos relativos a sua área de cliente.
    //unsigned long header_w_width = wWidth -2 -2;
    //unsigned long header_w_height = 2 +24 +2;

    unsigned long header_w_left = 0;
    unsigned long header_w_top = 0;
    // #bugbug
    // Para a largura devemos considerar a largura da área de cliente
    // nesse caso, onde a janela mãe é overlapped.
    // Uma flag no style pode indicar que devemos fazer clipping
    // na área de cliente.
    unsigned long header_w_width = (wWidth - 50);
    unsigned long header_w_height = 2 +24 +2;

// Container for editbox and button.
// #bugbug
// A janela não pode ser maior que a área de cliente.
// Quando a janela mãe é overlapped,
// a janela é relativa à área de cliente da
// janela mãe.
    Header_window = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_SIMPLE, 1, 1,"HeaderWin",
                  header_w_left,  //l
                  header_w_left,  //t
                  header_w_width,  //w
                  header_w_height,  //h
                  Main_window, // >>> Main_window é overlapped.
                  0, 
                  xCOLOR_GRAY7, 
                  xCOLOR_GRAY7 );

    if (Header_window<0){
        debug_print("fileman: Header_window fail\n"); 
        printf     ("fileman: Header_window fail\n"); 
        exit(1);
    }

    //#debug
    //gws_refresh_window (client_fd, Main_window);
    //while(1){}


//
// == Address bar =========================
//

// Editbox.
    addressbar_window = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_EDITBOX, 1, 1,"AddressBar",
                  2, 
                  2, 
                  (header_w_width -2 -2 -2 -24 -2), 
                  24,
                  Header_window, 
                  0, 
                  COLOR_EDITBOX, 
                  COLOR_EDITBOX );

    if (addressbar_window < 0){
        debug_print("fileman: addressbar_window fail\n"); 
        printf     ("fileman: addressbar_window fail\n"); 
        exit(1);
    }

//
// == Button =========================================
//

// [>]
// button
    button = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_BUTTON, BS_DEFAULT, 1, ">",
                  (header_w_width -2 -2 -24),  //l
                  2,                           //t 
                  24, 
                  24,
                  Header_window, 
                  0, 
                  COLOR_GRAY, 
                  COLOR_GRAY );

    if (button < 0){
        debug_print("fileman: button fail\n"); 
        printf     ("fileman: button fail\n"); 
        exit(1);
    }

//
// == Menu_window ============================
//

// Se a janela mãe é overlapped, 
// então estamos relativos à area de cliente dela.

    unsigned long mwLeft   = 2;
    unsigned long mwTop    = header_w_height +2 +2;  // depois da address bar e seus pads.
    unsigned long mwWidth  = (wWidth/4) -4;
    
    //#bugbug: 
    // Wrong. 
    // Precisamos pegar as dimensões da área de cliente.
    // Tem uma função pra isso, que é válida
    // pra janelas registradas.
    unsigned long mwHeight = 
        (wHeight - mwTop -4 -titlebarHeight);

    // #hack
    // I wanna see the status bar for now.
    mwHeight = mwHeight - 40;
    
    Menu_window = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_SIMPLE, 1, 1,"MenuWin",
                  mwLeft, mwTop, mwWidth, mwHeight, 
                  Main_window, 
                  0, 
                  COLOR_BLUE2CYAN, 
                  COLOR_BLUE2CYAN );

    if (Menu_window<0){
        debug_print("fileman: Menu_window fail\n"); 
        printf     ("fileman: Menu_window fail\n"); 
        exit(1);
    }

//
// == Logo_window ============================
//

    unsigned long lwLeft = 0;
    unsigned long lwTop = 0;
    unsigned long lwWidth = mwWidth;
    unsigned long lwHeight = 40;

    Logo_window = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_SIMPLE, 1, 1,"LogoWin",
                  lwLeft, lwTop, lwWidth, lwHeight, 
                  Menu_window, 
                  0, 
                  COLOR_BLUE, 
                  COLOR_BLUE );

    if (Logo_window<0){
        debug_print("fileman: Logo_window fail\n"); 
        printf     ("fileman: Logo_window fail\n"); 
        exit(1);
    }

// [/] button
    if (Logo_window>0)
    {
        lw_button1 = 
            (int) gws_create_window ( 
                      client_fd,
                      WT_BUTTON, BS_DEFAULT, 1, "/",
                      8, 8, 50, 24,
                      Logo_window, 
                      0, 
                      COLOR_WHITE, 
                      COLOR_WHITE );
    }
    if (lw_button1<0){
        debug_print("fileman: lw_button1 fail\n"); 
    }

    /*
    gws_draw_text (
        (int) client_fd,      // fd,
        (int) Logo_window,    // window id,
        (unsigned long) 8,    // left,
        (unsigned long) 8,    // top,
        (unsigned long) COLOR_BLACK,
        " -- Gramado OS  -- ");
    */

//
// == Navigation_window ===============
//

/*
    unsigned long nwLeft   = 0;
    unsigned long nwTop    = (mwHeight -40);  // altura da menuwindow - 40
    unsigned long nwWidth  = mwWidth;         // largura da menuwindow
    unsigned long nwHeight = 40;

    Navigation_window = gws_create_window ( 
                            client_fd,
                            WT_SIMPLE, 1, 1,"NaviWin",
                            nwLeft, nwTop, nwWidth, nwHeight, 
                            Menu_window, 0, COLOR_YELLOW, COLOR_YELLOW );

    if ( Navigation_window < 0 ){
        debug_print("fileman: Navigation_window fail\n"); 
        printf     ("fileman: Navigation_window fail\n"); 
        exit(1);
    }
*/

/*
// [<] button
    if ( Navigation_window > 0 ){
    nw_button1 = gws_create_window ( 
                                   client_fd,
                                   WT_BUTTON, BS_DEFAULT, 1, "<",
                                   (nwWidth/5)*1, 
                                   8,
                                   ((nwWidth/5) -4), 
                                   24,
                                   Navigation_window, 
                                   0, 
                                   COLOR_WHITE, COLOR_WHITE );
    }
    if ( nw_button1 < 0 ){
        debug_print("fileman: nw_button1 fail\n"); 
    }
*/

/*
// [?] button
    if ( Navigation_window > 0 ){
    nw_button2 = gws_create_window ( 
                                   client_fd,
                                   WT_BUTTON, BS_DEFAULT, 1, "?",
                                   (nwWidth/5)*2, 
                                   8,
                                   ((nwWidth/5) -4), 
                                   24,
                                   Navigation_window, 
                                   0, 
                                   COLOR_WHITE, COLOR_WHITE );
    }
    if ( nw_button2 < 0 ){
        debug_print("fileman: nw_button2 fail\n"); 
    }
*/

/*
// [!] button
    if ( Navigation_window > 0 ){
    nw_button3 = gws_create_window ( 
                                   client_fd,
                                   WT_BUTTON, BS_DEFAULT, 1, "!",
                                   (nwWidth/5)*3, 
                                   8,
                                   ((nwWidth/5) -4), 
                                   24,
                                   Navigation_window, 
                                   0, 
                                   COLOR_WHITE, COLOR_WHITE );
    }
    if ( nw_button3 < 0 ){
        debug_print("fileman: nw_button3 fail\n"); 
    }
*/

//
// == Client window =====================================
//

// This is a container for the menu ítens.
// metade direita da tela.
// #todo: precisamos pegar as dimensões da área de cliente.
// Estamos relativos á area de cliente da janela mãe.

    unsigned long cwLeft   = (wWidth/4);
    unsigned long cwTop    = mwTop; //40;
    unsigned long cwWidth  = (wWidth - cwLeft -4);
    unsigned long cwHeight = mwHeight; //(wHeight - cwTop -4 -titlebarHeight);

// client window (White)
    Client_window = 
        (int) gws_create_window ( 
                  client_fd,
                  WT_SIMPLE, 1, 1, "ClientWin",
                  cwLeft, cwTop, cwWidth, cwHeight,
                  Main_window, 
                  0,
                  COLOR_WHITE, 
                  COLOR_WHITE );

    if (Client_window<0){
        debug_print("fileman: Client_window fail\n"); 
    }
//
// =============================================================
//

// Items
    register int index=0;
    gMaxIndex = NUMBER_OF_WINDOWS;

    //if (current_mode==GRAMADO_JAIL){
    //    gMaxIndex=3;
    //}

    gMaxIndex = (cwHeight/24);

    if (cwHeight <= 24){
        printf ("cwHeight is too small\n");
        exit(1);
    }

    if (cwHeight < (3*24)){
        //printf ("cwHeight is too small\n");
        //exit(1);
        gMaxIndex = 1;
    }

    unsigned long iLeft   = 0;
    unsigned long iTop    = 0;
    unsigned long iWidth  = cwWidth;  // mesma largura da client window.
    //unsigned long iHeight = (cwHeight/gMaxIndex);
    unsigned long iHeight = 24;
    
    unsigned int ItemColor=COLOR_WHITE;

    for (index=0; index<gMaxIndex; index++)
    {
        ItemColor=COLOR_WHITE;
        if ( (index % 2) != 0 ){
            ItemColor = COLOR_GRAY;
        }

        windows[index] = 
            (int) gws_create_window ( 
                      client_fd,
                      WT_SIMPLE, 1, 1,"itemWin",
                      iLeft, iTop, iWidth, iHeight, 
                      Client_window, 
                      0,
                      ItemColor, 
                      ItemColor );

        if ( windows[index] < 0 )
        {
            debug_print("fileman: windows[index] fail\n"); 
            printf     ("fileman: windows[index] fail\n"); 
            exit(1);
        }
        
        gws_draw_text ( 
            (int) client_fd, 
            (int) windows[index], 
            8, 8, xCOLOR_GRAY2, "Item");
        
        // Atualiza o top do próximo item.
        iTop = (iTop + iHeight);
    };

//
// =============================================================
//

// dir entries

    int e=0;
    int max=22;
    if (current_mode==GRAMADO_JAIL){
        max=5;
    }

    /*
    for (e=3; e<max; e++){
    // fd, window_id, left, top, color, name.
    gws_draw_text ( (int) client_fd, (int) Client_window,
        8, (e*16), COLOR_BLACK, "FAKEFILE.TXT");
    }
    */

// ============================================
// focus
// It needs to be an EDITBOX window.
// We need a wrapper for that thing.

    //gws_async_command(
    //     client_fd,
    //     9,             // set focus
    //     addressbar_window,
    //     addressbar_window );

// set active window.
    //gws_async_command(
    //     client_fd,
    //     15, 
    //     Main_window,
    //     Main_window );

    gws_set_focus( client_fd, addressbar_window );
    gws_set_active( client_fd, Main_window );


//
// Events
//

// #test
// Let's include the typed byte into the buffer
// and using the string for calling a child process.

/*
    struct gws_event_d lEvent;
    lEvent.used=0;
    lEvent.magic=0;
    lEvent.msg=0;
    lEvent.long1=0;
    lEvent.long2=0;

    struct gws_event_d *ev;

    while(TRUE){
        ev = (struct gws_event_d *) gws_get_next_event(client_fd,(struct gws_event_d *) &lEvent);
        filemanProcedure(
            (int) client_fd,
            (int) lEvent.wid,
            (int) lEvent.msg,
            (unsigned long) lEvent.long1,
            (unsigned long) lEvent.long2 );

        lEvent.msg = 0;
    };
*/

// use the thread's queue
    rtl_focus_on_this_thread();

// Call the event loop.
    return (int) do_event_loop(client_fd);

/*
    while (1){
        if ( rtl_get_event() == TRUE )
        {
            // #debug on real machine
            //printf("Event:"); fflush(stdout);
            
            //if( RTLEventBuffer[1] == MSG_QUIT ){ break; }

            filemanProcedure ( 
                (int) client_fd,
                (int) RTLEventBuffer[0], 
                (int) RTLEventBuffer[1], 
                (unsigned long) RTLEventBuffer[2], 
                (unsigned long) RTLEventBuffer[3] );

            RTLEventBuffer[1] = 0;
        }
    };
*/



// force hang
    while(1){
    };

    debug_print ("fileman: bye\n"); 
    printf      ("fileman: bye\n");
    return 0;
}

//
// End
//

