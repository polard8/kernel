/*
 * File: main.c
 *    Client side application for Gramado Network Server.
 *    Using socket to connect with gns.
 *    AF_GRAMADO family.
 *    O propósito é testar o servidor gns.
 * History:
 *     2020 - Created by Fred Nora.
 */
// See:
// https://wiki.osdev.org/Message_Passing_Tutorial
// https://wiki.osdev.org/Synchronization_Primitives
// ...
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

#include <gnsint.h>

// Ports.
#define PORTS_WS  4040
#define PORTS_NS  4041
#define PORTS_FS  4042
// ...

#define IP(a, b, c, d) \
    (a << 24 | b << 16 | c << 8 | d)

// ----------------------

static void InitializeGlobals(void);
static void ShutdownApplication(int socket_fd);

// ----------------------

/*
// #test
// gerar número aleatório dentro de uma faixa.
int gerar_numero(int lim_inf, int lim_sup)
{
    return (lim_inf + (rand() % lim_sup));
}
*/

/*
#define IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)
struct sockaddr_in addr = {
    .sin_family = AF_INET,
    .sin_port   = 7548, 
    .sin_addr   = IP(192, 168, 1, 79),
};
*/


static void InitializeGlobals(void)
{
    register int i=0;

// Clear the buffer.
    for (i=0; i<__BUFFER_SIZE; i++){
        buffer[i] = 0;
    };
}

static void ShutdownApplication(int socket_fd)
{
    debug_print("net.bin: ShutdownApplication\n"); 
    printf     ("net.bin: ShutdownApplication\n");
// Close the given socket.
    close(socket_fd);
}

// ========
// main:

int main(int argc, char *argv[])
{

//========================
    struct sockaddr_in  server_address;
    int addrlen=0;
    server_address.sin_family = AF_INET;
    // Connecting to the network server in this machine.
    server_address.sin_port = PORTS_NS;       // htons(PORTS_NS);
    server_address.sin_addr.s_addr = IP(127,0,0,1);  // inet_addr("192.168.0.101");

    addrlen = sizeof(server_address);
//========================

    int client_fd = -1;

    debug_print ("net.bin: Initializing ...\n");
    InitializeGlobals();

// Socket
    client_fd = (int) socket( AF_INET, SOCK_STREAM, 0 );
    if (client_fd < 0){
       //gws_debug_print ("gnst: Couldn't create socket\n");
       printf ("net.bin: [FAIL] Couldn't create socket\n");
       exit(1);
    }

// Connect
// Nessa hora colocamos no accept um fd.
// Então o servidor escreverá em nosso arquivo.

    while (1){
        if (connect (client_fd, (void *) &server_address, addrlen ) < 0)
        { 
            //gws_debug_print ("gnst: Connection Failed\n");
            printf ("net.bin: Connection Failed \n"); 
            //close(client_fd);
            //exit(1);
        }else{ break; }; 
    };

    if (client_fd<0){
        printf("net.bin: fd fail\n");
        exit(1);
    }


// ------------------
// Send request and wait for response.
// Ok. Its working :)

    printf("NET.BIN: Sending hello!\n");

    int hello_status = (int) gns_hello(client_fd);
    if (hello_status <= 0){
        printf("net.bin: Service failed\n");
    }

// Loop
// See: 
// libgns/

    int data_status=-1;
    int service_status = -1;
    while (1)
    {
        //if( isTimeToQuit == TRUE )
            //break;

        // ------------------
        // Get data from kernel.
        data_status = (int) gns_get_packet( buffer, __BUFFER_SIZE );
        if (data_status > 0)
        {
           //#debug
           // We got data from kernel.
           printf("net.bin: Data={%s}\n",buffer);
           //exit(0);
        }

        // ------------------
        // Send request and wait for response.
        // Ok. Its working :)
        //service_status = (int) gns_hello(client_fd);
        //if (service_status <= 0){
        //    printf("net.bin: Service failed\n");
        //}

        // Sleep
        gns_yield();
    };

// Not reached.

    ShutdownApplication(client_fd);
    return 0;
}

