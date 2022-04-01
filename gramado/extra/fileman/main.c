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
#include <packet.h>

// The client-side library
#include <gws.h>

// Local
#include <fileman.h>


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

#define NUMBER_OF_WINDOWS  8
int gMaxIndex=NUMBER_OF_WINDOWS;
int windows[NUMBER_OF_WINDOWS];


//
// == ports ====================================
//

#define PORTS_WS 4040
#define PORTS_NS 4041
#define PORTS_FS 4042
// ...

// JAIL,P1 ...
int current_mode;



#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)


int fileman_init_globals(void)
{
    gws_debug_print("fileman_init_globals:\n");
    
    gScreenWidth  = gws_get_system_metrics(1);
    gScreenHeight = gws_get_system_metrics(2);

    
    //...
    
    return 0;
}


int fileman_init_windows(void)
{
    int i=0;


    gws_debug_print("fileman_init_windows:\n");
    for(i=0;i<WINDOW_COUNT_MAX;i++)
    {
        windowList[i] = 0;
    };
    return 0;
}


//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/


int barCompareStrings(void)
{
    debug_print("barCompareStrings: \n");


    char c=0;
    
    c = (char) prompt[0];

// =============================
// Emergency 


// reboot
    if(c=='q')
        gws_reboot();

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



void barPrompt (void)
{
    int i=0;

// Clean prompt[] buffer.
// This is a buffer inside the libc.

    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){ prompt[i] = (char) '\0'; };

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
int barInputChar( int c )
{
    unsigned long ascii=0;
    
    ascii = (unsigned long) (c & 0xFF);

    return (int) input(ascii);
}



int filemanProcedure(
    int fd,
    int wid,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    if(msg<0)
        return -1;

    switch(msg)
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
    };

    return 0;
}


//
// Main
//

int main ( int argc, char *argv[] )
{
    int client_fd = -1;
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port   = PORTS_WS;
    addr_in.sin_addr.s_addr = IP(127,0,0,1);


    debug_print ("fileman: Initializing ...\n");
    
// dc
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

// Gramado mode.
    current_mode = rtl_get_system_metrics(130);

// #debug
    //printf ("The current mode is %d\n",current_mode);
    //exit(0);

//
// socket
// 

// #debug
    //printf ("fileman: Creating socket\n");

    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    if ( client_fd < 0 ){
        printf ("fileman: Couldn't create socket\n");
        exit(1);
    }

//
// connect
// 

// Nessa hora colocamos no accept um fd.
// então o servidor escreverá em nosso arquivo.

    //printf ("fileman: Connecting to ws via inet ...\n");

    while (1){
        if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){
            gws_debug_print("fileman: Connection Failed \n");
            printf         ("fileman: Connection Failed \n");
        }else{ break; }; 
    };



//
// == Main window ==============
//

    unsigned long wWidth  = (w >> 1);
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


// main window
// Locked and maximized.
// style: 0x0001=maximized | 0x0002=minimized | 0x0004=fullscreen | 0x0008=statusbar?
// style: 0x8000=locked

    Main_window = gws_create_window ( 
                      client_fd,
                      WT_OVERLAPPED, 1, 1, "Gramado Shell",
                      wLeft, wTop, wWidth, wHeight,
                      0,
                      0x8008,
                      COLOR_GRAY, COLOR_GRAY );

    if ( Main_window < 0 ){
        debug_print("fileman: Main_window fail\n");
        printf     ("fileman: Main_window fail\n");
        exit(1);
    }


//
// == Header_window ======================
//

    Header_window = gws_create_window ( 
                        client_fd,
                        WT_SIMPLE, 1, 1,"HeaderWin",
                        2,                  //left 
                        titlebarHeight +2,  //top 
                        wWidth -2 -2,       //width 
                        32 +2 +2,           //height
                        Main_window, 0, xCOLOR_GRAY7, xCOLOR_GRAY7 );

    if ( Header_window < 0 ){
        debug_print("fileman: Header_window fail\n"); 
        printf     ("fileman: Header_window fail\n"); 
        exit(1);
    }


//
// == Address bar =========================
//

// #bugbug
// The window server needs to fix the client area.
// So 0,0 needs to mean the top/left of the client area.

// address bar
    addressbar_window = gws_create_window ( 
                            client_fd,
                            WT_EDITBOX, 1, 1,"AddressBar",
                            4, titlebarHeight +4, 
                            (wWidth-40), 32,
                            Main_window, 0, COLOR_WHITE, COLOR_WHITE );

    if ( addressbar_window < 0 ){
        debug_print("fileman: addressbar_window fail\n"); 
        printf     ("fileman: addressbar_window fail\n"); 
        exit(1);
    }


//
// == Button =========================================
//

    // [>]
    // button
    button = gws_create_window ( 
                 client_fd,
                 WT_BUTTON, BS_DEFAULT, 1, ">",
                 (wWidth-32-4), titlebarHeight +4, 32, 32,
                 Main_window, 0, COLOR_GRAY, COLOR_GRAY );

    if ( button < 0 ){
        debug_print("fileman: button fail\n"); 
        printf     ("fileman: button fail\n"); 
        exit(1);
    }


//
// == Menu_window ============================
//

    unsigned long mwLeft   = 2;
    unsigned long mwTop    = (titlebarHeight +40);
    unsigned long mwWidth  = (wWidth/4) -4;
    unsigned long mwHeight = (wHeight - mwTop -4 -titlebarHeight);

    Menu_window = gws_create_window ( 
                        client_fd,
                        WT_SIMPLE, 1, 1,"MenuWin",
                        mwLeft, mwTop, mwWidth, mwHeight, 
                        Main_window, 0, COLOR_BLUE, COLOR_BLUE );

    if ( Menu_window < 0 ){
        debug_print("fileman: Menu_window fail\n"); 
        printf     ("fileman: Menu_window fail\n"); 
        exit(1);
    }


//
// == Logo_window ============================
//

    unsigned long lwLeft   = 0;
    unsigned long lwTop    = 0;
    unsigned long lwWidth  = mwWidth;
    unsigned long lwHeight = 40;

    Logo_window = gws_create_window ( 
                        client_fd,
                        WT_SIMPLE, 1, 1,"LogoWin",
                        lwLeft, lwTop, lwWidth, lwHeight, 
                        Menu_window, 0, COLOR_BLUE2CYAN, COLOR_BLUE2CYAN );

    if ( Logo_window < 0 ){
        debug_print("fileman: Logo_window fail\n"); 
        printf     ("fileman: Logo_window fail\n"); 
        exit(1);
    }


// [/] button
    if ( Logo_window > 0 ){
    lw_button1 = gws_create_window ( 
                                   client_fd,
                                   WT_BUTTON, BS_DEFAULT, 1, "/",
                                   8, 8, 50, 24,
                                   Logo_window, 
                                   0, 
                                   COLOR_WHITE, COLOR_WHITE );
    }
    if ( lw_button1 < 0 ){
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

    unsigned long cwLeft   = (wWidth/4);
    unsigned long cwTop    = titlebarHeight +40;
    unsigned long cwWidth  = (wWidth - cwLeft -4);
    unsigned long cwHeight = (wHeight - cwTop -4 -titlebarHeight);

    // client window (White)
    Client_window = gws_create_window ( 
                        client_fd,
                        WT_SIMPLE, 1, 1, "ClientWin",
                        cwLeft, cwTop, cwWidth, cwHeight,
                        Main_window, 
                        0,  // style: 0x0001=maximized | 0x0002=minimized | 0x0004=fullscreen 
                        COLOR_WHITE, 
                        COLOR_WHITE );

    if ( Client_window < 0 ){
        debug_print("fileman: Client_window fail\n"); 
    }

//
// =============================================================
//

// Items

    int index=0;
    gMaxIndex=NUMBER_OF_WINDOWS;

    if (current_mode==GRAMADO_JAIL)
    {
        gMaxIndex=3;
    }

    unsigned long iLeft   = 0;
    unsigned long iTop    = 0;
    unsigned long iWidth  = cwWidth;  // mesma largura da client window.
    unsigned long iHeight = (cwHeight/gMaxIndex);

    unsigned int ItemColor=COLOR_WHITE;

    for (index=0; index<gMaxIndex; index++)
    {
        ItemColor=COLOR_WHITE;
        if( (index % 2) != 0 )
            ItemColor = COLOR_GRAY;
        
        windows[index] = 
            (int) gws_create_window ( 
                      client_fd,
                      WT_SIMPLE, 1, 1,"itemWin",
                      iLeft, iTop, iWidth, iHeight, 
                      Client_window, 
                      0,
                      ItemColor, ItemColor );

        if ( windows[index] < 0 )
        {
            debug_print("fileman: windows[index] fail\n"); 
            printf     ("fileman: windows[index] fail\n"); 
            exit(1);
        }
        
        gws_draw_text ( 
            (int) client_fd, 
            (int) windows[index], 
            8, 8, COLOR_BLACK, "Item");
        
        // atualiza o top do próximo item.
        iTop = (iTop + iHeight);
    };

//
// =============================================================
//


// dir entries

    int e=0;
    int max=22;
    if (current_mode==GRAMADO_JAIL){max=5;}

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

    gws_async_command(
         client_fd,
         9,             // set focus
         addressbar_window,
         addressbar_window );

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


    while(1){}

    debug_print ("fileman: bye\n"); 
    printf      ("fileman: bye\n");
    return 0;
}


//
// End.
//








