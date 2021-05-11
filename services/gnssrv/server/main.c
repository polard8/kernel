/*
 * File: main.c
 * 
 *    ??
 *    Main file for the Gramado Network Server.
 * 
 *
 *    History:
 *        2020 - Created by Fred Nora. 
 */


#include <gns.h>


//
// == Gramado Network Protocol ===============================
//

// Standard. (First version)
// This is the standard header.
#define GNP_WID        0
#define GNP_MESSAGE    1
#define GNP_LONG1      2
#define GNP_LONG2      3
// #extension
// extended data.
#define GNP_LONG3      4
#define GNP_LONG4      5
#define GNP_LONG5      6
#define GNP_LONG6      7
// #body
// Here starts the data section.
// It goes untill the end of the socket. 
// Maybe 512-(16*4).
#define GNP_BODY_OFFSET    16
// ...

int NoReply = FALSE;

//
// Buffer
//

// Buffer for the messages.

#define GNS_BUFFER_SIZE  512

char __buffer[GNS_BUFFER_SIZE];

//
// Status
//

int running = FALSE;


//
// Server fd
//

int ____saved_server_fd = -1;

//
// Current client fd
//

int ____saved_current_client_fd = -1;


//
// Buffer
//

// This is the buffer ussed for the next response.
// Marsheling ...

// Esses valores serão enviados como 
// resposta ao serviço atual.
// Eles são configurados pelo dialogo na hora da 
// prestação do serviço.
// No início desse array fica o header.

unsigned long next_response[32];




//
// == Prototypes =========================
//

int serviceInitializeNetwork(void);

void gnssrv_yield(void);

// dialog
int 
gnsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

void xxxHandleNextRequest (int fd);


void gns_send_error_response (int fd, int code, char *error_message);


//
// ===============================
//

void gns_send_error_response (int fd, int code, char *error_message)
{
    // 500: internal server error!!
    //#todo
    debug_print ("gnssrv: [TODO] gns_send_error_response\n");
}



// internal.
// Messages sended via socket.
// obs: read and write use the buffer '__buffer'
// in the top of this file.
// Called by main.

void xxxHandleNextRequest(int fd){

    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__buffer[0];   

    int n_reads = 0;     // For requests.
    int n_writes = 0;    // For responses.


    // Fail. Cleaning

    if (fd<0){
        debug_print ("gnssrv: xxxHandleNextRequest fd\n");
        message_buffer[0] = 0;
        message_buffer[1] = 0;
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        gnssrv_yield(); 
        return;
    }


    // Check if we heave a new request.
    
    int value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );

    if ( value != ACTION_REQUEST )
    {
        gnssrv_yield();
        return;           // drop it!
    }


//__loop:

    // #todo
    // Devemos escrever em nosso próprio
    // socket e o kernel copia??
    // o kernel copia para aquele arquivo ao qual esse estivere conectado.
    // olhando em accept[0]

    n_reads = read ( fd, __buffer, sizeof(__buffer) );

    if (n_reads <= 0)
    { 
        debug_print ("gnssrv: xxxHandleNextRequest n_reads\n");
        // Cleaning
        message_buffer[0] = 0;
        message_buffer[1] = 0;
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        gnssrv_yield(); 
        return; 
    }
  
    // Nesse momento lemos alguma coisa.   
 
    //debug_print ("gws: request found on its own socket \n");  
       
    //  mensagem invalida  
    if (message_buffer[1] == 0)
    { 
        debug_print ("gnssrv: xxxHandleNextRequest Unknown message\n");
        // Cleaning
        message_buffer[0] = 0;
        message_buffer[1] = 0;
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        gnssrv_yield(); 
        return;
    }

    //
    // == Message OK =====================
    //

    debug_print ("gnssrv: Got a request!\n");
    debug_print ("gnssrv: Calling window procedure \n");
                
    //#debug: para a máquina real.
    //printf ("gws: got a message!\n");
    //printf ("gws: __socket_messages: calling window procedure \n");
 
                
    // realiza o serviço.
    gnsProcedure ( 
        (void *)        message_buffer[0], 
        (int)           message_buffer[1], 
        (unsigned long) message_buffer[2], 
        (unsigned long) message_buffer[3] );


    // #todo
    // Se o request foi um request de evento,
    // significa que o cliente deseja receber o próximo evento da 
    // lista de eventos.
    // podemos passar mensagens recebidas pelo gws para o cliente.

    // ??
    // espera ate conseguir enviar a resposta.
    // o kernel precisa copiar para aquele conectado em accept[]

    if (NoReply == TRUE)
    {
        rtl_set_file_sync( 
            fd, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
        return;
    }


//
// Sending reply.
// 
 
    //debug_print ("Sending response ...\n");  

    //# it works.
    char *m = (char *) (&__buffer[0] + 16);
    sprintf( m, "GRAMADO 501 Not Implemented\n\n");
    //sprintf( m, "HTTP/1.1 501 Not Implemented\n\n");
    //sprintf( m, "HTTP/1.1 400 Bad Request\n Content-Type: text/html\n Content-Length: 0\n");



    // Primeiros longs do buffer.
    message_buffer[0] = next_response[0];         // Window ID.
    message_buffer[1] = SERVER_PACKET_TYPE_REPLY; // next_response[1] 
    message_buffer[2] = next_response[2];         // Return value (long1)
    message_buffer[3] = next_response[3];         // Return value (long2)

    // #todo:
    // Talvez aqui possamos usar alguma função chamada post_message().

//__again:

    // #todo:
    // while(1){...}
    
    debug_print ("gnssrv: Sending response ...\n");


//
// == Response =============================== 
//

    // set response
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REPLY );
    
    //
    // Send
    //

    n_writes = write ( fd, __buffer, sizeof(__buffer) );
    if (n_writes<=0){
        debug_print ("gnssrv: xxxHandleNextRequest Response fail\n");
    }


    // Cleaning
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;

    // Cleaning
    int c=0;
    for(c=0; c<32; c++){
        next_response[c] = 0;
    };


    debug_print ("gnssrv: Response sent\n"); 
    
    gnssrv_yield(); 
}


/*
 **********************************
 * gnsProcedure:
 *     Main dialog.
 */

int 
gnsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    int my_pid = -1;


    debug_print ("gnssrv: gnsProcedure\n");

    if (msg<0)
        return -1;

    switch (msg){

        // Com essa mensagem o cliente solicita input.
        // então devemos drenar input usado loop de mensagens e
        // repassar para o cliente via socket.
        case 8080:
            debug_print ("gnssrv: [TODO] 8080. drain messages ...\n");
            break;

        case MSG_SYSKEYUP:
            switch ( long1)
            {
                // #debug
                case VK_F1:
                    //reboot();
                    break;
                    
                // #debug
                // mostrar informações sobre o socket 
                // do gws.    
                case VK_F2:
                    my_pid = (int) getpid();
                    gramado_system_call (7008,my_pid,0,0);
                    break; 
             
                // Enviar a mensagem para o processo associado
                // com a janela que tem o foco de entrada.
                default:
                    debug_print ("gnssrv: MSG_SYSKEYUP\n");
                    break;
            }    
            break;

        // #test
        // Tentando receber uma mensagem de digitação.
        case MSG_KEYDOWN:
            
            //#bugbug: Isso está falhando.
            //mas o f1 funciona.
            //printf ("%c", (char) long1); 
            //gws_show_backbuffer ();
            
            debug_print ("gnssrv: MSG_KEYDOWN\n");
            break;


        //MSG_GNS_HELLO
        case 1000:
            printf ("\n");
            printf ("gnssrv: [1000] Hello from Gramado Network Server!\n");
            printf ("\n");
            NoReply = FALSE;
            return 0;
            break;


        //MSG_GNS_INITIALIZENETWORK
        case 1001:
            printf ("\n");
            printf ("gnssrv: [1001]\n");
            // serviceInitializeNetwork();
            //printf ("\n");
            return 0;
            break; 

        //case 1002:  break;
        //case 1003:  break;

        //case 2000:  break;
        //case 2001:  break;
        //case 2002:  break;
        //case 2003:  break;

        //MSG_GNS_SHUTDOWN
        case 2010:
            debug_print ("gnssrv: [2010] Disconnect\n");
            break;

        case 2020:
             break;

        // Refresh rectangle ... 
        case 2021:
            break;
            
        //MSG_GNS_PROTOCOL
        case 3000:
            break;

        // ...
             
                
        default:
            //printf ("msg=%d ",msg);
            break;
    }


    // #todo: 
    // Call the system's window procedure.    
    // Rever esse retorno.
    //return (int) xxxxxx_system_procedure (window,msg,long1,long2);
    return 0;
}


//char *
//eth_broadcast_addr = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };
//char *
//eth_null_addr = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

/*
void gnssrv_print_mac (char *string);
void gnssrv_print_mac (char *string)
{
    char *ptr = (char *) string;
    printf("MAC { %x:%x:%x:%x:%x:%x } \n", 
        ptr[0], 
        ptr[1], 
        ptr[2], 
        ptr[3], 
        ptr[4],
        ptr[5] );
}
*/


/*
int gnssrv_maccmp(char *a, char *b);
int gnssrv_maccmp(char *a, char *b)
{
    char *__a = a;
    char *__b = b;
    int i=0;

    for ( i=0; i<6; i++ )
    {
        if (__a[i] != __b[i]){ return (int) 1; }
    };

    return 0;
}
*/

/*
void
gnssrv_print_ip_addr(uint32_t ip);
void
gnssrv_print_ip_addr(uint32_t ip)
{
    char *__ip = (char *) &ip;
    print ("%d.%d.%d.%d \n", 
        (uint8_t) __ip[0], 
        (uint8_t) __ip[1], 
        (uint8_t) __ip[2], 
        (uint8_t) __ip[3]);
}
*/

/*
void
gnssrv_print_le_ip_addr(uint32_t ip);
void
gnssrv_print_le_ip_addr(uint32_t ip)
{
    char *__ip = (char *) &ip;
    print ("%d.%d.%d.%d \n", 
        (uint8_t) __ip[3], 
        (uint8_t) __ip[2], 
        (uint8_t) __ip[1], 
        (uint8_t) __ip[0]);
}
*/


/*
uint16_t
ip_calculate_checksum(void *ip);
uint16_t
ip_calculate_checksum(void *ip)
{
    uint16_t *buffer = (uint16_t *) ip;
    uint32_t sum = 0;
    int i;
    int len = 20; //FIXME: get it from ip_ihl 

    for (i = 0; i < len / sizeof(uint16_t); i ++)
        sum += (buffer[i]);

    while (sum > 0xffff) {
        uint16_t val = (sum & 0xffff0000) >> 16;
        sum &= 0x0000ffff;
        sum += val;
    }

    sum = ~sum;

    return (sum);
}
*/


// yield thread.
void gnssrv_yield(void)
{
    // #todo
    // Use the sc 82. 
    gramado_system_call (265,0,0,0); 
    //  sc82 (265,0,0,0);
}


int serviceInitializeNetwork(void)
{
    // Ring0 routine to initialize network infrastructure.
    gramado_system_call (968,0,0,0);
    return 0;
}





/*
 ******************************
 * main: 
 *     gns main routine.
 */

int main (int argc, char **argv){


    //=======================
    struct sockaddr server_address;
    socklen_t addrlen;
    
    server_address.sa_family = AF_GRAMADO;
    server_address.sa_data[0] = 'n';
    server_address.sa_data[1] = 's';

    addrlen = sizeof(server_address);


    int server_fd = -1; 
    int bind_status = -1;


    int i=0;
    int _status = -1;
     
    //unsigned long w=0;
    //unsigned long h=0;


    // Global flag for the loop.
    running = TRUE;


    // Serial debug.
    debug_print ("-----------------------\n");
    debug_print ("gnssrv: Initializing...\n");
    printf      ("gnssrv: Initializing...\n");


    //
    // Register.
    //

    // Register this process as the network server.
    // See: connect.c
    _status = (int) register_ns();

    if (_status<0){
        debug_print ("gnssrv: Couldn't register the server \n");
             printf ("gnssrv: Couldn't register the server \n");
        exit(1);
    }
    debug_print ("gnssrv: Registration ok \n");


    //
    // socket
    //
    
    // #debug
    printf ("gnssrv: Creating socket\n");

    server_fd = (int) socket (AF_GRAMADO, SOCK_STREAM, 0);
    
    if (server_fd<0){
        printf("gnssrv: [FAIL] Couldn't create the server socket\n");
        exit(1);
    }
    ____saved_server_fd = server_fd;



//
// bind
// 
 
    // #debug
    printf ("gnssrv: bind\n");
 
    bind_status = bind ( 
                      server_fd, 
                      (struct sockaddr *) &server_address, 
                      addrlen );

    if (bind_status<0){
        printf("gnssrv: Couldn't bind to the socket\n");
        exit(1);
    }


    //
    // =======================================
    //


    //
    // Calling child.
    //
    
    // #obs
    // Suspended ...
    // We are launching the server in background
    // and calling the child via command interpreter.


    //printf ("gnssrv: Calling child \n");

    rtl_clone_and_execute ("gns.bin"); 


    //
    // Wait
    //

    printf ("gnssrv: [FIXME] yield \n");

    for (i=0; i<11; i++){
        gnssrv_yield();
    };


//
// == Accept =====================================
//

// loop:
    debug_print ("gnssrv: Entering main loop.\n");


    // Messages sended via sockets.
    // Mensagens enviadas pelos clientes via socket.
    // Inclusive a mensagem que pede para drenar input e 
    // via mensagens e repassar via socket. 
    

    // clients.
    int newconn = -1;
    int curconn = ____saved_server_fd;


    // Accept connection from a client. 
    
    while (1){
        newconn = accept ( 
                      ____saved_server_fd, 
                      (struct sockaddr *) &server_address, 
                      (socklen_t *) addrlen );

        if (newconn < 0){
            debug_print ("gnssrv: [FAIL] Error on accept\n");
            gnssrv_yield(); 
        }else{
            xxxHandleNextRequest (newconn);
        };
    };



    //
    // =======================================
    //

    // Done.
    
    debug_print ("gnssrv: Bye\n");
         printf ("gnssrv: Bye\n");

    return 0; 
}

//
// End
//




