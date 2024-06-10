// main.c
// netd.bin
// Gramado Network Server
// This is the main server whe Gramado is acting like
// a server. When the 'product' is the 'Gramado Server'.
// And a client can use this service to connect
// with a Gramado Server for sharing resources
// as well as identifying it self.

// Servidor de configuração de rede local.
// Segurança/credenciais e inicialização de sessões.
// Através desse servidor, duas máquinas rodando Gramado
// podem sincronizar suas ações gerando certificados
// próprios para máquinas rodando Gramado.
// Gramado Tokens.
// Podemos gerar estatísticas sobre o uso da rede
// e descrições sobre os componentes.
// 2020 - Created by Fred Nora.

/*
 Network server costuma ser um termo genérico que identifica
 um computador como sendo servidor em uma rede. 
 Esses servidores costumam ser das seguintes classes:
 + File servers -  files in the local network.
 + Database servers - files inside the server.
 + Application servers.
 */


#include <gnsint.h>

// static int __saved_sync_id = -1;

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

// Status
static int running = FALSE;
// Server fd
static int ____saved_server_fd = -1;
// Current client fd
static int ____saved_current_client_fd = -1;
// Flag: Send or not a reoply.
static int NoReply = FALSE;

//
// == Prototypes =========================
//

static int ServerInitialization(void);
static int ServerShutdown(void);

static void __initialize_globals(void);

static void dispatch(int fd);
static int serviceInitializeNetwork(void);
static void serviceHello(void);

// dialog
static int 
gnsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

static void 
gns_send_error_response (int fd, int code, char *error_message);

static void gnssrv_yield(void);

//
// ===============================
//

static void 
gns_send_error_response (int fd, int code, char *error_message)
{
    // 500: internal server error!!
    //#todo
    debug_print("netd: [TODO] gns_send_error_response\n");
}

static void serviceHello(void)
{
    printf("\n");
    printf("netd: [1000] Hello from Gramado Network Server!\n");
    next_response[0] = 0;  //wid
    next_response[1] = SERVER_PACKET_TYPE_REPLY; // The response is a reply. 
    next_response[2] = 0;
    next_response[3] = 0;
    NoReply = FALSE;
    rtl_yield();
}

// internal.
// Messages sended via socket.
// obs: read and write use the buffer '__buffer'
// in the top of this file.
// Called by main.

static void dispatch(int fd)
{
    unsigned long *message_buffer = 
        (unsigned long *) &__buffer[0];
    int n_reads = 0;     // For requests.
    int n_writes = 0;    // For responses.

// Fail. Cleaning
    if (fd<0){
        debug_print("netd: dispatch fd\n");
        message_buffer[0] = 0;
        message_buffer[1] = 0;
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        gnssrv_yield(); 
        return;
    }

// Check if we have a new request.
    int value = rtl_get_file_sync( fd, SYNC_REQUEST_GET_ACTION );
// Not a request.
    if (value != ACTION_REQUEST){
        gnssrv_yield();
        return;
    }

// =====================
// Read the request.
    n_reads = (int) read( fd, __buffer, sizeof(__buffer) );
    if (n_reads <= 0)
    {
        debug_print("netd: dispatch n_reads\n");
        // No reply
        rtl_set_file_sync( 
            fd, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
        // Cleaning
        message_buffer[0] = 0;
        message_buffer[1] = 0;
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        gnssrv_yield(); 
        return; 
    }

// Nesse momento já lemos alguma coisa.

// Invalid message code.
    if (message_buffer[1] == 0)
    { 
        debug_print("netd: dispatch Unknown message\n");
        // No reply
        rtl_set_file_sync( 
            fd, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
        // Cleaning
        message_buffer[0] = 0;
        message_buffer[1] = 0;
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        gnssrv_yield();
        return;
    }

// OK:
// Valid message
// Call the service!

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

    if (NoReply == TRUE){
        rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
        return;
    }

// ==============================================

//
// Send reply!
//


// Insert message string int to the response buffer.
    char *m = (char *) (__buffer + 128);
    sprintf( m, "GRAMADO 501 Not Implemented!");
    //sprintf( m, "HTTP/1.1 501 Not Implemented\n\n");
    //sprintf( m, "HTTP/1.1 400 Bad Request\n Content-Type: text/html\n Content-Length: 0\n");

// Standard message fields.
// Primeiros longs do buffer.
// #bugbug: Invalid values for next_response[i];
    message_buffer[0] = next_response[0];         // Window ID.
    message_buffer[1] = SERVER_PACKET_TYPE_REPLY; // next_response[1] 
    message_buffer[2] = next_response[2];         // Return value (long1)
    message_buffer[3] = next_response[3];         // Return value (long2)

// #todo:
// Talvez aqui possamos usar alguma função chamada post_message().

// Sending the reply.
    n_writes = (int) write( fd, __buffer, sizeof(__buffer) );
    if (n_writes<=0)
    {
        debug_print("netd: dispatch Response fail\n");
        // No response. It fails.
        rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_NULL );
        return;
    }

// Cleaning
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[2] = 0;
    message_buffer[3] = 0;

// Cleaning the buffer for the response.
    register int c=0;
    for (c=0; c<32; c++){
        next_response[c] = 0;
    };

// Set response.
    rtl_set_file_sync( fd, SYNC_REQUEST_SET_ACTION, ACTION_REPLY );
}

static int 
gnsProcedure ( 
    void *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
// Do a service. 
// Called by dispath();

    int my_pid = -1;

    if (msg<0){
        return -1;
    }

    switch (msg){

        // Com essa mensagem o cliente solicita input.
        // então devemos drenar input usado loop de mensagens e
        // repassar para o cliente via socket.
        case 8080:
            //debug_print("netd: [TODO] 8080. drain messages ...\n");
            break;

        case MSG_SYSKEYUP:
            switch (long1)
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
                    gramado_system_call(7008,my_pid,0,0);
                    break; 
             
                // Enviar a mensagem para o processo associado
                // com a janela que tem o foco de entrada.
                default:
                    debug_print("netd: MSG_SYSKEYUP\n");
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

            debug_print("netd: MSG_KEYDOWN\n");
            break;

        // MSG_GNS_HELLO
        // case 1000:
        case GNS_Hello:
            serviceHello();           
            NoReply = FALSE;
            return 0;
            break;

        // MSG_GNS_INITIALIZENETWORK
        case 1001:
            printf("\n");
            printf("netd: [1001]\n");
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
            debug_print("netd: [2010] Disconnect\n");
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

static void gnssrv_yield(void)
{
    gramado_system_call(265,0,0,0); 
    //  sc82 (265,0,0,0);
}

static int serviceInitializeNetwork(void)
{
    // Ring0 routine to initialize network infrastructure.
    // #remember: At this moment we are in the user app memory space.
    gramado_system_call(968,0,0,0);
    return 0;
}

static void __initialize_globals(void)
{
    register int i=0;

// Global flag for the loop.
    running = FALSE;

    ____saved_server_fd = -1;
    ____saved_current_client_fd = -1;

// Clear the buffer for the messages.
// see: globals.c
    for (i=0; i<GNS_BUFFER_SIZE; i++){
        __buffer[i] = 0;
    };

// Clear the tmp buffer for next response metadata.
// see: globals.c
    for (i=0; i<32; i++){
        next_response[i] = 0;
    };
}

static int ServerShutdown(void)
{
    //#todo
    printf("netd: [todo] ServerShutdown\n");
}

// Called by main().
static int ServerInitialization(void)
{

//=======================
    struct sockaddr server_address;
    socklen_t addrlen=0;
    server_address.sa_family = AF_GRAMADO;
    server_address.sa_data[0] = 'n';
    server_address.sa_data[1] = 's';
    addrlen = sizeof(server_address);
//=======================

    int server_fd = -1; 
    int bind_status = -1;
    register int i=0;
    int _status = -1;
    //int InitializeFirstClient = TRUE;
    int InitializeFirstClient = FALSE;
     
    //unsigned long w=0;
    //unsigned long h=0;

// debug
    printf("NETD.BIN: Initializing\n");

// Initialize global variables.
    __initialize_globals();


// Sincronizaçao provisoria
// vamos precisar disso antes de tudo;
// vamos pegar a que foi criada pelo primeiro cliente.
// ele cria no começo da rotina.
// Dai usaremos essa id por enquanto, pois o sistema so tem ela ainda.

/*
    while(1){
        __saved_sync_id = sc82 (10005,0,0,0);
        if( __saved_sync_id > 0 && __saved_sync_id < 1024 )
            break;
    };
 */

// -------------------
// Register
// Register this process as the network server.
// See: connect.c
    _status = (int) register_ns();
    if (_status<0){
        printf("netd: Couldn't register the server\n");
        goto fail;
    }
    debug_print("netd: Registration ok\n");

// -------------------
// socket
// Create socket and save the into a global variable.
    server_fd = (int) socket(AF_GRAMADO, SOCK_STREAM, 0);
    if (server_fd < 0){
        printf("netd: on socket()\n");
        goto fail;
    }
    ____saved_server_fd = (int) server_fd;

// -------------------
// bind
    bind_status = 
        (int) bind (
                  server_fd, 
                  (struct sockaddr *) &server_address, 
                  addrlen );

    if (bind_status < 0){
        printf("netd: on bind()\n");
        goto fail;
    }

// Calling child and wait.
// Just for fun, not for profit.
    if (InitializeFirstClient == TRUE){
        rtl_clone_and_execute("gns.bin");
    }

// Wait
    for (i=0; i<11; i++){
        gnssrv_yield();
    };

//
// == Accept =====================================
//

// Messages sent via sockets.
// Mensagens enviadas pelos clientes via socket.
// Inclusive a mensagem que pede para drenar input e 
// via mensagens e repassar via socket. 

// Clients
    register int newconn = -1;
    int curconn = ____saved_server_fd;

// Accept connection from a client. 

    running = TRUE;

    while (1)
    {
        newconn = 
            (int) accept ( 
                      ____saved_server_fd, 
                      (struct sockaddr *) &server_address, 
                      (socklen_t *) addrlen );

        if (newconn < 0){
            debug_print("netd: on accept()\n");
            gnssrv_yield(); 
        }else{
            // Valid fd.
            if (newconn == 31){
                dispatch(newconn);
            }
        };
    };

// =======================================
    debug_print("netd: Bye\n");
         printf("netd: Bye\n");
    return 0;
fail:
    exit(1);
    return -1;
}

// -------------------
// Main:
int main (int argc, char **argv)
{
    int Status=-1;
    register int i=0;

// #test: Flags
    int f1= FALSE;
    int f2= FALSE;
    int f3= FALSE;
    int f4= FALSE;

    if (argc>0)
    {
        for (i=0; i<argc; i++)
        {
            //printf("%d: {%s}\n",i,argv[i]);

            if ( strncmp( argv[i], "-1", 2 ) == 0 )
                f1=TRUE;
            if ( strncmp( argv[i], "-2", 2 ) == 0 )
                f2=TRUE;
            if ( strncmp( argv[i], "-3", 2 ) == 0 )
                f3=TRUE;
            if ( strncmp( argv[i], "-4", 2 ) == 0 )
                f4=TRUE;
        };
    }
     
    Status = (int) ServerInitialization();
    if (Status == 0){
        ServerShutdown();
        exit(0);
    }
    
    return 0;
}

//
// End
//

