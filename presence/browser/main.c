/*
 * File: main.c
 *
 *     Client side application using gwssrv.
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




// #test
// Tentando deixar o buffer aqui e aproveitar em mais funções.
char __buffer[512];

#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)


// tipos de pacotes.
//#define SERVER_PACKET_TYPE_REQUEST    1000 
//#define SERVER_PACKET_TYPE_REPLY      1001 
//#define SERVER_PACKET_TYPE_EVENT      1002
//#define SERVER_PACKET_TYPE_ERROR      1003


// Hello!
// Podemos isso na lib.
int browser_hello_request(int fd);
int browser_hello_response(int fd);



/*
int 
browser_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color );
int browser_createwindow_response(int fd);
*/




// message support
int browser_getmessage_request(int fd);
int browser_getmessage_response(int fd);
int browser_loop(int fd);



int browser_getmessage_request(int fd)
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.



    //char *name = "Window name 1";

   

    //
    // Send request.
    //

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // #debug
        gws_debug_print ("browser: Sending request ...\n");      
    
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


int browser_getmessage_response(int fd)
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
    //gws_debug_print ("browser: iting ...\n");      

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

    // #caution
    // Waiting for response.
    // We can stay here for ever.

response_loop:

    // #debug
    gws_debug_print ("browser: Getting response ...\n");      


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
        gws_debug_print ("browser: recv fail.\n");
        printf ("browser: recv fail.\n");
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
    
    //#debug
    //if(msg!=0)
        //printf ("%c",long1); //printf ("{%d%c} ",msg,long1);
        
        
        
    switch (msg){

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
            gws_debug_print ("browser: SERVER_PACKET_TYPE_ERROR\n");
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
    gws_debug_print ("browser: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("gwst: bye\n"); 
    printf ("browser: Window ID %d \n", message_buffer[0] );
    //printf ("browser: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("browser: We got an event\n"); 
    return 0;
}




/*
 ************************* 
 * browser_loop:
 * 
 */

int browser_loop(int fd)
{
	//while(___running){
    while(1){
        browser_getmessage_request(fd);
        browser_getmessage_response(fd);
    }
    return 0; 
}


//...

/*
int 
browser_createwindow_request (
    int fd,
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height,
    unsigned long bg_color )
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.

    char *name = "Window name 1";

    //
    // Send request.
    //

    // #debug
    gws_debug_print ("browser: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??
    // msg = 369 (get input event)

    while (1)
    {
        // Create window    
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1001;    // msg. Create window.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        
        message_buffer[4] = left; //120;   //x
        message_buffer[5] = top; //120;   //y
        message_buffer[6] = width; //480;   //w
        message_buffer[7] = height; //320;   //h
        
        message_buffer[8] = bg_color; //xCOLOR_GRAY2; 

         
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
*/

/*
//response
int browser_createwindow_response(int fd)
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
    gws_debug_print ("browser: Waiting ...\n");      

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
    gws_debug_print ("browser: reading ...\n");      


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
        gws_debug_print ("browser: recv fail.\n");
        printf ("browser: recv fail.\n");
        printf ("Something is wrong with the socket.\n");
        exit (1);
    }


    //
    // The msg index.
    //
    
    // Get the message sended by the server.

    int msg = (int) message_buffer[1];
    
    switch (msg){

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
            gws_debug_print ("browser: SERVER_PACKET_TYPE_ERROR\n");
            goto response_loop;
            //exit (-1);
            break;
        
        default:
            goto response_loop;
            break; 
    };

//
// Process reply.
//

// A resposta tras o window id no início do buffer.
    
process_reply:

    // #test
    gws_debug_print ("browser: Testing close() ...\n"); 
    //close (fd);

    //gws_debug_print ("gwst: bye\n"); 
    printf ("browser: Window ID %d \n", message_buffer[0] );
    //printf ("browser: Bye\n");
    
    // #todo
    // Podemos usar a biblioteca e testarmos
    // vários serviços da biblioteca nesse momento.

    return 0;

//
// Process an event.
//

process_event:
    gws_debug_print ("browser: We got an event\n"); 
    return 0;

}
*/




/*
// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}
*/



//char *hello = "Hello there!\n";
/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/




int browser_hello_response(int fd){

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
    debug_print ("browser: Waiting ...\n");      


    int y;
    for(y=0; y<15; y++)
        gws_yield();


    //
    // read
    //

    // #debug
    debug_print ("browser: Reading ...\n");      


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
        printf ("browser: recv fail.\n");
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
            debug_print ("browser: SERVER_PACKET_TYPE_REPLY received\n"); 
            goto process_reply;
            break;
            
        case SERVER_PACKET_TYPE_EVENT:
            //todo: call procedure.
            goto __again;
            break;
            
        case SERVER_PACKET_TYPE_ERROR:
            debug_print ("browser: SERVER_PACKET_TYPE_ERROR\n");
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


int browser_hello_request(int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_writes = 0;   // For sending requests.
    unsigned long ____color = 0x00FF00;


     //
     // Loop for new message.
     //



// loop:
new_message:

    
    //
    // Write
    //

    // #debug
    debug_print ("browser: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??


    // Write!
    // Se foi possível enviar, então saimos do loop.        
    // obs: podemos usar send();

    while (1){

        // solicita um hello!      
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        // ...

        n_writes = write (fd, __buffer, sizeof(__buffer));
        if(n_writes>0)
           break;
    }

    return 0;
}



/*
 ********************************* 
 * main: 
 * 
 */

int main ( int argc, char *argv[] ){

    int client_fd = -1;

    // Porta para o Window Server 'ws' em gramado_ports[]
    struct sockaddr_in addr_in;

    addr_in.sin_family      = AF_INET;
    addr_in.sin_port        = PORTS_WS;   
    addr_in.sin_addr.s_addr = IP(192, 168, 1, 112); 


    debug_print ("-------------------------\n");
    debug_print ("browser: Initializing ...\n");


    // Metrics.
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

    // cria o soquete.
    // AF_GRAMADO
    //client_fd = socket ( 8000, SOCK_STREAM, 0 );
    client_fd = socket ( AF_INET, SOCK_STREAM, 0 );
    
    if ( client_fd < 0 ){
       printf ("browser: Couldn't create socket\n");
       exit(1);
    }


    //
    // connect
    // 

    //nessa hora colocamos no accept um fd.
    //então o servidor escreverá em nosso arquivo.

    // #debug
    //printf ("gnst: Connecting to the address 'ws' ...\n");      
    printf ("browser: Connecting to the address via inet  ...\n");    

    while (TRUE){
        if (connect (client_fd, (void *) &addr_in, sizeof(addr_in)) < 0){ 
            debug_print("browser: Connection Failed \n"); 
            printf     ("browser: Connection Failed \n"); 
            //return -1; 
        // try again
        }else{ break; }; 
    };


    //
    // messages
    //
   
    // #test
    // Testing loop; ok.
    // #todo
    // Podemos checar antes se o fd 
    // representa um objeto que permite leitura.
    // Pode nem ser possível.
    // Mas como sabemos que é um soquete,
    // então sabemos que é possível ler.

   // #bugbug
   // We need this or something is gonna fail in the title bar.

    //while(1){
    //    browser_hello_request(client_fd);
    //    browser_hello_response(client_fd);
    //}

    // The main window.
    // #todo: Can gws_create_window call these two functions? 
    //browser_createwindow_request(client_fd, 80, 80, 480, 320, COLOR_PINK);
    //browser_createwindow_response(client_fd); 


    //#todo: salvar em global
    //por enquanto aqui
    int main_window=0;
    int addressbar_window=0;    
    int client_window=0;
    int button=0;



    // a janela eh a metade da tela.
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
    main_window = gws_create_window ( 
                      client_fd,
                      WT_OVERLAPPED, 1, 1, "Browser",
                      viewwindowx, viewwindowy, w_width, w_height,
                      0, 0, COLOR_GRAY, COLOR_GRAY );

    if ( main_window < 0 ){
        debug_print("browser: main_window fail\n"); 
        exit(1);
    }

    // ===================
    // address bar
    addressbar_window = gws_create_window (
                            client_fd,
                            WT_EDITBOX,1,1,"address-bar",
                            4, 32 +4, 
                            (w_width-32-4-4-4), 32,
                            main_window, 0, COLOR_WHITE, COLOR_WHITE );

    if ( addressbar_window < 0 ){
        debug_print("browser: addressbar_window fail\n"); 
    }

    // IN: fd, window id, left, top, color, string
    gws_draw_text (
        (int) client_fd,
        (int) addressbar_window,
         8, 8, (unsigned long) COLOR_BLACK,
        "http://www.google.com");


    // ===================
    // button
    button = gws_create_window (client_fd,
        WT_BUTTON,1,1,">",
        (w_width-32-4), 32 +4, 
        32, 32,
        main_window, 0, COLOR_GRAY, COLOR_GRAY );

    if ( button < 0 ) 
        debug_print("browser: button fail\n"); 


    // ===================
    // client window (White)
    client_window = gws_create_window (client_fd,
        WT_SIMPLE,1,1,"client",
        4, 32 +40, 
        w_width-8, w_height - 40 - 4 -32,
        main_window, 0, COLOR_WHITE, COLOR_WHITE );

    if ( client_window < 0 )             
        debug_print("browser: client_window fail\n"); 

     gws_draw_text (
        (int) client_fd,        // fd,
        (int) client_window,    // window id,
        (unsigned long) 40,     // left,
        (unsigned long) 40,     // top,
        (unsigned long) COLOR_BLACK,
        "Hello, from G**gle!");


    gws_refresh_window( client_fd, main_window );

    //
    // Loop.
    //
 
    while(1){}
        
    // browser_loop(client_fd);

    debug_print ("browser: bye\n"); 
    printf      ("browser: bye\n");


    return 0;
}


//
// End.
//








