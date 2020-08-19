/*
 * File: main.c
 *
 *    Client side application for Gramado Network Server.
 *    Using socket to connect with gns.
 *    AF_GRAMADO family.
 * 
 * 
 *       O propósito é testar o servidor gns.
 *
 * 2020 - Created by Fred Nora.
 */
 
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

#include <gwm.h>




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

// tipos de pacotes.
//#define SERVER_PACKET_TYPE_REQUEST    1000 
//#define SERVER_PACKET_TYPE_REPLY      1001 
//#define SERVER_PACKET_TYPE_EVENT      1002
//#define SERVER_PACKET_TYPE_ERROR      1003



// Hello!
// Podemos isso na lib.
int _hello_request(int fd);
int _hello_response(int fd);
void hello(int fd);

//message support
int _getmessage_request(int fd);
int _getmessage_response(int fd);
int run(int fd);



int fullscreen_client (int fd, struct wm_client_d *c);
int center_client (int fd, struct wm_client_d *c);


int gwm_init_globals(void);
int gwm_init_windows(void);
int create_main_menu( int fd );





int fullscreen_client (int fd, struct wm_client_d *c)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);
    
    if ( (void *) c != NULL )
    {
        if(c->used == 1)
        {
            gws_change_window_position(fd,c->window, 0, 0);  //x,y
            gws_resize_window(fd,c->window, w, h);     //w,h
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
    
    gScreenWidth = gws_get_system_metrics(1);
    gScreenHeight = gws_get_system_metrics(2);
    
    
    //...
    
    return 0;
}

int gwm_init_windows(void)
{
    int i=0;

    gws_debug_print("gwm_init_windows:\n");
    
    for(i=0;i<WINDOW_COUNT_MAX;i++)
    {
        windowList[i] = 0;
    };
    
    
    
    return 0;
}




int _getmessage_request(int fd)
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    //char *name = "Window name 1";

   

    //
    // Send request.
    //


    // #debug
    gws_debug_print ("gwm: Writing ...\n");      

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


int _getmessage_response(int fd)
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
    gws_debug_print ("gwm: Waiting ...\n");      

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
    gws_debug_print ("gwm: reading ...\n");      


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
        gws_debug_print ("gwm: recv fail.\n");
        printf ("gwm: recv fail.\n");
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

    // #extra
    unsigned long long3 = (unsigned long) message_buffer[4];
    unsigned long long4 = (unsigned long) message_buffer[5];

    //#debug
    //if(msg!=0)
        //printf ("%c",long1); //printf ("{%d%c} ",msg,long1);
        
        
        
    switch (msg){


        // #test
        // Testando mensagem de mouse.
        // A mensagem tem um pacote com 3 valores a serem decodificados.
        // Raw mouse input!!!
        case 4567:
            printf("gwm-4567: [TEST] Mouse raw input\n");
            break;
        
        //OK isso funcionou.
        case MSG_KEYDOWN:
          //case 20:
            //gws_debug_print ("MSG_KEYDOWN\n");
            switch (long1)
            {
                //case 0:
                    //relax cpu
                    //break; 
                    
                //case VK_RETURN:
                    //goto process_event;
                    //break;
                  
                //case VK_TAB:
                //case VK_BACK:
                
                //...
                
                
                // We are in the terminal ...
                // We will not process the chars ...
                // We need to send it to the client via file.
                default:
                    //terminal_write_char(long1) #todo
                    printf ("%c",long1);
                    fflush(stdout);
                    goto process_event;
                    break;
            };
            break;


        //case MSG_KEYUP:
          case 21:  
            //gws_debug_print ("MSG_KEYUP\n");
            goto process_event;
            break;

            
        case MSG_SYSKEYDOWN:
            switch (long1)
            {
                case VK_F1:
                    printf ("gwm: VK_F1\n");
                    create_main_menu(fd);
                    break;

                case VK_F2:
                    printf ("gwm: VK_F2\n");
                    create_tester_client(fd);
                    break;

                // This sistem call is able to initialize a lot
                // of system's components.
                // IN: 1 = full initialization os ps2.
                case VK_F3:
                    printf ("gwm: VK_F3\n");
                    gramado_system_call ( 350, 1, 0, 0 );
                    break;
                    
                case VK_F4:
                    printf ("gwm: VK_F4 reboot\n");
                    gws_reboot();
                    break;
                    
                    
                default:
                    goto process_event;
                    break;
            };
            break;
            

        case MSG_SYSKEYUP:
            switch (long1)
            {
                //case VK_F1:
                default:
                    goto process_event;
                    break;
            };
            break;

        // Commands.
        case MSG_COMMAND:
            switch (long1)
            {
                //case CMD_ABOUT:
                    //printf ("terminal: CMD_ABOUT\n");
                    //goto process_event;
                    //break;
                    
                default:
                    goto process_event;
                    break;
            };

 
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
            gws_debug_print ("gwm: SERVER_PACKET_TYPE_ERROR\n");
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
    gws_debug_print ("gwm: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("gwst: bye\n"); 
    printf ("gwm: Window ID %d \n", message_buffer[0] );
    //printf ("gwm: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("gwm: We got an event\n"); 
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


// loop
// Loop de requests para o gws.
int run(int fd)
{
    //struct wm_client_d  *c;
    
    
	//while(___running){
    while(1){
        _getmessage_request(fd);
        _getmessage_response(fd);    
    };

    return 0; 
}





//...




//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/




int _hello_response(int fd){

    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   
    int n_reads = 0;    // For receiving responses.


    //
    // waiting
    //

    // Espera para ler a resposta. 
    // Esperando com yield como teste.
    // Isso demora, pois a resposta só será enviada depois de
    // prestado o servido.
    // obs: Nesse momento deveríamos estar dormindo.

    // #debug
    debug_print ("gwm: Waiting ...\n");      


    int y;
    for(y=0; y<15; y++)
        gws_yield();



    //
    // read
    //

    // #debug
    debug_print ("gwm: Reading ...\n");      


       //#caution
       //we can stay here for ever.
       //it's a test yet.
__again:
    n_reads = read ( fd, __buffer, sizeof(__buffer) );
    
    // Não vamos insistir num arquivo vazio.
    //if (n_reads<=0){
    //     gws_yield();        
    //    goto __again;
    //}

    if (n_reads == 0){
        gws_yield();        
        goto __again;
    }
    
    if (n_reads < 0){
        printf ("gwm: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
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
            debug_print ("gwm: SERVER_PACKET_TYPE_REPLY received\n"); 
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            //todo: call procedure.
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            debug_print ("gwm: SERVER_PACKET_TYPE_ERROR\n");
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
    printf("RESPONSE: {%s} \n",__buffer+16);

    return 0;
}


int _hello_request(int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.

     //
     // Loop for new message.
     //

    unsigned long ____color = 0x00FF00;

// loop:
new_message:

    
    //
    // Write
    //

    // #debug
    debug_print ("gwm: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??


    // Write!
    // Se foi possível enviar, então saimos do loop.        
    // obs: podemos usar send();

    while (1){

        // Solicita um hello na posição x,y.      
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello.
        message_buffer[2] = 10;       // x
        message_buffer[3] = 40;       // y (Depois da topbar) 
        // ...

        n_writes = write (fd, __buffer, sizeof(__buffer));
        if(n_writes>0)
           break;
    };

    return 0;
}


void hello(int fd)
{
    if(fd<0)return;
    
    //while(1){
        _hello_request(fd);
        _hello_response(fd);
    //}
}


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


//interna
int create_topbar_client(int fd)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    int button1_window=-1;   
    
    
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

        //topbar
        c_topbar->window = gws_create_window (fd,
            WT_SIMPLE,1,1,"Topbar",
            0, 0, w, 32,
            0,0,xCOLOR_GRAY3, xCOLOR_GRAY3);
        
        if( (void *) c_topbar->window < 0){
            printf ("gwm: c_topbar->window fail\n");
            exit(1);
        }
        printf ("w={%x}\n",c_topbar->window);
        gws_refresh_window(fd,c_topbar->window);

         // button1 (system menu)
         button1_window = gws_create_window (fd,
                              WT_BUTTON,1,1,"=",
                              2, 2, 32, 28,
                              c_topbar->window, 0,COLOR_GRAY, COLOR_GRAY);
        
        c_topbar->title_window = -1;  //todo;
        wmclientList[0] = (unsigned long) c_topbar;
    };
    
    return 0;
}


//interna
int create_taskbar_client(int fd)
{
    unsigned long w = gws_get_system_metrics(1);
    unsigned long h = gws_get_system_metrics(2);

    //
    // == Taskbar (Client) ==================================
    //
    
    int button1_window=-1;   
    int button2_window=-1;   
    
    
    //if (fd<0)
        //return -1;

    
    // Taskbar
    gws_debug_print ("gwm: Create c_taskbar client\n");
    c_taskbar = (struct wm_client_d *) malloc ( sizeof(struct wm_client_d) );
    if( (void *)c_taskbar == NULL){
        printf ("gwm: c_taskbar fail\n");
        exit(1);
    
    }else{

         c_taskbar->window = gws_create_window (fd,
                                 WT_SIMPLE,1,1,"Taskbar",
                                 0, (h-32), w, 32,
                                 0,0,COLOR_GRAY, COLOR_GRAY);

        if( (void *) c_taskbar->window < 0){
            printf ("gwm: c_taskbar->window fail\n");
            exit(1);
        }
        printf ("w={%x}\n",c_taskbar->window);
        gws_refresh_window(fd,c_taskbar->window);
         
         c_taskbar->title_window = -1;  //todo 

         // button1
         button1_window = gws_create_window (fd,
                              WT_BUTTON,1,1,"App1",
                              2, 2, 120, 28,
                              c_taskbar->window, 0,COLOR_GRAY, COLOR_GRAY);

         // button2
         button2_window = gws_create_window (fd,
                              WT_BUTTON,1,1,"App2",
                              2 + 120 + 2, 2, 120, 28,
                              c_taskbar->window, 0,COLOR_GRAY, COLOR_GRAY);

         wmclientList[1] = (unsigned long) c_taskbar;
    };

    return 0;
}


//interna
int create_tester_client(int fd)
{
    struct gws_menu_d *menu;

    //
    // == Tester (Client) ==================================
    // 

    int tester_button=-1;
    
    
    //if (fd<0)
        //return -1;

    
    //gws_enter_critical_section();
    gws_debug_print ("gwm: Create tester_client client\n");
    //struct wm_client_d *tester_client;
    tester_client = (struct wm_client_d *) malloc( sizeof(struct wm_client_d ) );

    if( (void *) tester_client == NULL){
         printf ("gwm: tester_client fail\n");
         exit(1);
    }

    if ( (void *) tester_client != NULL )
    {
        tester_client->used = 1;
        tester_client->magic = 1234;
        
        tester_client->window = gws_create_window (fd,
                                    WT_SIMPLE,1,1,"Tester",
                                    100, 100, 480, 320,
                                    0,0, 0xF5DEB3, 0xF5DEB3);
        
        if( (void *) tester_client->window < 0){
            printf ("gwm: tester_client->window fail\n");
            exit(1);
        }
        printf ("w={%x}\n",tester_client->window);
        gws_refresh_window(fd,tester_client->window);
        
        tester_client->title_window = gws_create_window (fd,
                                          WT_SIMPLE,1,1,"Tester Title",
                                          100, 100-32, 480, 32,
                                          0,0, 0x2d89ef, 0x2d89ef);

        if( (void *) tester_client->title_window < 0 ){
            printf ("gwm: tester_client->title_window fail\n");
            exit(1);
        }
    
    
        //Tester title window
        tester_button = gws_create_window (fd,
             WT_BUTTON,1,1,"X", //#bugbug: pagefault. the size of the string overflows the button size.
             (480-36-2), 2, 36, 28, //2, 2, 80, 28,
             tester_client->title_window, 0, COLOR_RED, COLOR_RED);
             
             
             
        //#testing (NEW)
        menu = gws_create_menu (
                (int) fd,
                (int) tester_client->window,
                (int) 0, //highlight
                (int) 4,   //count
                (unsigned long) 1, //x
                (unsigned long) 1,
                (unsigned long) 200,
                (unsigned long) 200,
                (unsigned long) COLOR_WHITE );

          if( (void*) menu != NULL )
          {
               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item0",
                  (int) 0,
                  (struct gws_menu_d *) menu );

               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item1",
                  (int) 1,
                  (struct gws_menu_d *) menu );

               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item2",
                  (int) 2,
                  (struct gws_menu_d *) menu );

               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item3",
                  (int) 3,
                  (struct gws_menu_d *) menu );

           }
             
        wmclientList[2] = (unsigned long) tester_client;
    } 
    //gws_exit_critical_section();


    // Testing more things ....
    
    
    int i=0;
    for(i=0; i<16; i++){

        gws_change_window_position(fd,tester_client->window, i*10, i*10);
        gws_change_window_position(fd,tester_client->title_window, i*10, i*10);
        
        //gws_resize_window(fd,tester_client->window, i*20, i*20);
        
        gws_redraw_window(fd,tester_client->window,1); 
        gws_redraw_window(fd,tester_client->title_window,1); 
         
    };
    
    
    //full screen
    // ok
    //fullscreen_client (fd,tester_client);
    
    //put in the center.
    //center_client (fd, tester_client);

    return 0;
}


//internal
int create_main_menu( int fd )
{
    struct gws_menu_d *menu;


    if (fd<0)
        return -1;

    if ( (void *) c_topbar == NULL )
        return -1;
    
    if ( c_topbar->window < 0 )
        return -1;


    // #testing (NEW)
    menu = gws_create_menu (
               (int) fd,
               (int) c_topbar->window,
               (int) 0, //highlight
               (int) 4,   //count
               (unsigned long) 20, //x
               (unsigned long) 20,
               (unsigned long) 200,
               (unsigned long) 200,
               (unsigned long) COLOR_WHITE );

    if ( (void*) menu != NULL )
    {
               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item0",
                  (int) 0,
                  (struct gws_menu_d *) menu );

               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item1",
                  (int) 1,
                  (struct gws_menu_d *) menu );

               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item2",
                  (int) 2,
                  (struct gws_menu_d *) menu );

               //menu item
               gws_create_menu_item (
                  (int) fd,
                  (char *) "Item3",
                  (int) 3,
                  (struct gws_menu_d *) menu );

    }


    return 0;
}

// Testing new main.
int main ( int argc, char *argv[] ){

    int client_fd = -1;

    // Porta para o Window Server 'ws' em gramado_ports[]
    struct sockaddr_in addr_in;
    addr_in.sin_family = AF_INET;
    addr_in.sin_port   = PORTS_WS;   
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 112); 



    debug_print ("---------------------------\n");    
    debug_print ("gwm: Initializing ...\n");



    //
    // socket
    // 

    // #debug
    printf ("gwm: Creating socket\n");

    // cria o soquete.
    // AF_GRAMADO
    //client_fd = socket ( 8000, SOCK_STREAM, 0 );
    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("gwm: Couldn't create socket\n");
       exit(1);
    }


    while(1){

        //
        // connect
        // 

        //nessa hora colocamos no accept um fd.
        //então o servidor escreverá em nosso arquivo.
    
        // #debug
        //printf ("gnst: Connecting to the address 'ws' ...\n");      
        printf ("gwm: Connecting to ws via inet  ...\n");   

        if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
            gws_debug_print ("gwm: Connection Failed \n");
            printf          ("gwm: Connection Failed \n"); 
            //return -1;
            //try again 
        }else{ break; }; 
    };


    // Testing server.
    hello(client_fd);

    // Create clients.
    create_topbar_client(client_fd);
    create_taskbar_client(client_fd);
    // ...
    

    // Press F2.
    //create_tester_client(client_fd);



    gws_debug_print ("gwm: draw done!\n");
    printf          ("gwm: draw done!\n");

    //gws_show_background();
    //while(1){}

    //
    // Loop
    //

    // Loop de requests para o gws.
    run (client_fd);


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
    printf ("gwm: bye\n");

    return 0;
}


//
// End.
//








