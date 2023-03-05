
// gns.c
// This is a client-side library for the GNSSRV.

#include <types.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <heap.h>
#include <sys/socket.h>
#include <rtl/gramado.h>

#include "include/gns.h"

#define SIZE_DONT_CHANGE  512
char __gns_buffer[SIZE_DONT_CHANGE];

//=================================
static int __gns_hello_request(int fd);
static int __gns_hello_response(int fd);
//=================================

// System call.
// 0x80 System interrupt.
void *gns_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    unsigned long __Ret=0;

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}

// Debug vai serial port. (COM1)
void gns_debug_print (char *string)
{
    if ( (void*) string == NULL ){
        return;
    }
    gns_system_call ( 
        289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}

// Yield this thread.
void gns_yield(void)
{
    gns_system_call (265,0,0,0);
}

// hello request
static int __gns_hello_request (int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gns_buffer[0];   
    int n_writes = 0;   // For sending requests.
    int i=0;

//
// Write
//

    // #debug
    // debug_print ("__gns_hello_request: Writing ...\n");      

// Enviamos um request para o servidor.
// ?? Precisamos mesmo de um loop para isso. ??
// Write!
// Se foi possível enviar, então saimos do loop.        
// obs: podemos usar send();

// Message: Solicita um hello!      
    message_buffer[0] = 0;       // window. 
    message_buffer[1] = GNS_Hello;  //1000;    // msg=hello.
    message_buffer[2] = 0;
    message_buffer[3] = 0;
    // ...

    while (1){
        n_writes = 
            (int) write (
                      fd, 
                      __gns_buffer, 
                      sizeof(__gns_buffer) );

        if (n_writes>0){
           break;
        }

        for (i=0; i<11; i++)
        {
            //gramado_system_call (265,0,0,0); //yield thread.
            //gnst_yield();
            rtl_yield();
        }
    };

    if (n_writes <= 0){
        return -1;
    }

    return (int) n_writes;
}

static int __gns_hello_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gns_buffer[0];   
    int n_reads = 0;    // For receiving responses.
    int i=0;
    char response_buffer[128];

    if (fd<0){
        return -1;
    }

//
// Read
//
    // #debug
    //debug_print ("__gns_hello_response: reading ...\n");      

    n_reads = 
        (int) read ( 
                  fd, 
                  __gns_buffer, 
                  sizeof(__gns_buffer) );

// #bugbug
// If we do not read the file, so the flag will not switch
// and we will not be able to write into the socket.

    if (n_reads <= 0){
        printf ("__gns_hello_response: recv fail\n");
        return -1;
    }

// Get the message sended by the server.
    int msg = (int) message_buffer[1];

    switch (msg){
 
    // reply (ok)
    case GNS_SERVER_PACKET_TYPE_REPLY:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_REPLY received\n"); 
        goto process_reply;
        break;

    // error
    case GNS_SERVER_PACKET_TYPE_ERROR:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_ERROR\n");
        return -1;
        break;

    // request
    case GNS_SERVER_PACKET_TYPE_REQUEST:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_REQUEST\n");
        return -1;
        break;

    // event
    case GNS_SERVER_PACKET_TYPE_EVENT:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_EVENT\n");
        return -1;
        break;

    default:
        return -1;
        break;
    };

process_reply:

// Clear the buffer.
// #bugbug: Overflow. We need a limit here.
// #todo: Get the size of the message
// and then put the message into the tmp buffer.
// Se tem alguma coisa no buffer, mostra

    for (i=0; i<128; i++){
        response_buffer[i]=0;
    };

// Get the payload.
// The message is in the offset 128?
    sprintf( response_buffer, (__gns_buffer+128) );
    response_buffer[127] = 0;  //finaliza

    if ( *response_buffer != 0 ){
        printf("RESPONSE: { %s } \n", response_buffer );
    }

    return (int) n_reads;
}


void
gns_async_command ( 
    int fd, 
    unsigned long request,
    unsigned long sub_request,
    unsigned long data )
{
    // #todo
    // Post asynchonous request to the server.
}

// =============================================
int gns_hello (int fd)
{
    int status=-1;

    if (fd<0){
        debug_print("gns_hello: fd\n");
        return FALSE;
    }

// Reset flags.
// Configuramos a flag para que possamos escrever.
   debug_print ("gns_hello: reset flags\n");      
    
   rtl_set_file_sync( 
       fd,   // 
       216,  // request. (We can write)
       0 );  // data

//=============================
// Request.
// Avisamos que um request foi enviado.
   debug_print ("gns_hello: Send request\n");      

    int req_status=-1;
    req_status = (int) __gns_hello_request(fd);
    if(req_status<0){
        return -1;
    }

// Set a request.
    rtl_set_file_sync( 
        fd, 
        SYNC_REQUEST_SET_ACTION, 
        ACTION_REQUEST );

//=============================
// Response.
// Waiting to read the response.
   debug_print ("gns_hello: Read response\n");      

    int value=0;
    while (1)
    {
        value = 
            (int) rtl_get_file_sync( 
                      fd, 
                      SYNC_REQUEST_GET_ACTION );
        
        if (value == ACTION_REQUEST){ rtl_yield(); }
        if (value == ACTION_REPLY ) { break; }
        if (value == ACTION_ERROR ) { return -1; }
        if (value == ACTION_NULL )  { return -1; }  // no reply
    };

// A sicronização nos diz que ja temos um reply,
// então não precisamos esperar.

// ??
// Se não conseguimos ler a resposta.
// Então vamos reconfigurar as flags do arquivo
// dizendo que queremos autorização para escrever.
// Na verdade esse erro na hora de ler a resposta
// ja é motivo pra fechar a conexão.

    status = (int) __gns_hello_response(fd);
    if ( status <= 0 ){
        return -1;
    }
    
    return TRUE;
}

