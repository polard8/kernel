// This is a client-side library for the GNS. 

// rtl
#include <types.h>  
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <heap.h>   

//#test: usado por gws_open_display
#include <sys/socket.h>

#include <rtl/gramado.h>   


#include "include/gns.h"


char __gns_buffer[512];


// System call.
void *gns_system_call ( 
    unsigned long a, 
    unsigned long b, 
    unsigned long c, 
    unsigned long d )
{
    unsigned long __Ret = 0;

    //System interrupt.

    asm volatile ( " int %1 \n"
                 : "=a"(__Ret)
                 : "i"(0x80), "a"(a), "b"(b), "c"(c), "d"(d) );

    return (void *) __Ret; 
}


// Debug vai serial port. (COM1)
void gns_debug_print (char *string)
{
    gns_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}

void gns_yield(void)
{
    gns_system_call (265,0,0,0); //yield thread.
}


// hello request
int __gns_hello_request (int fd)
{
    // Isso permite ler a mensagem na forma de longs.
    unsigned long *message_buffer = (unsigned long *) &__gns_buffer[0];   

    int n_writes = 0;   // For sending requests.

    //unsigned long ____color = 0x00FF00;
    int i=0;

// loop:
// Loop for new message.

new_message:

    //
    // Write
    //

    // #debug
    debug_print ("__gns_hello_request: Writing ...\n");      

    // Enviamos um request para o servidor.
    // ?? Precisamos mesmo de um loop para isso. ??

    // Write!
    // Se foi possível enviar, então saimos do loop.        
    // obs: podemos usar send();

    while (1){

        // messae: Solicita um hello!      
        message_buffer[0] = 0;       // window. 
        message_buffer[1] = 1000;    // msg=hello.
        message_buffer[2] = 0;
        message_buffer[3] = 0;
        // ...

        n_writes = write (
                       fd, 
                       __gns_buffer, 
                       sizeof(__gns_buffer) );

        if (n_writes>0)
           break;
        
        for (i=0; i<9; i++){
            gramado_system_call (265,0,0,0); //yield thread.
            //gnst_yield();
        }
    }

    return 0;
}


int __gns_hello_response(int fd)
{
    unsigned long *message_buffer = (unsigned long *) &__gns_buffer[0];   
    int n_reads = 0;    // For receiving responses.

// waiting
// Espera para ler a resposta. 
// Esperando com yield como teste.
// Isso demora, pois a resposta só será enviada depois de
// prestado o servido.
// obs: Nesse momento deveríamos estar dormindo.

    // #debug
    //debug_print ("__gns_hello_response: Waiting ...\n");      

    //int y;
    //for(y=0; y<15; y++)
        //gns_yield();

//
// read
//

    // #debug
    debug_print ("__gns_hello_response: reading ...\n");      


    n_reads = read ( 
                  fd, 
                  __gns_buffer, 
                  sizeof(__gns_buffer) );

    // #bugbug
    // If we do not read the file, so the flag will not switch
    // and we will not be able to write into the socket.

    if (n_reads <= 0)
    {
        printf ("__gns_hello_response: recv fail\n");
        
        // Tentamos ler e falhou.
        
        return -1;
    }

// Get the message sended by the server.
    int msg = (int) message_buffer[1];

    switch (msg){
 
    // reply
    case GNS_SERVER_PACKET_TYPE_REPLY:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_REPLY received\n"); 
        goto process_reply;
        break;

//
// error
//

    case GNS_SERVER_PACKET_TYPE_ERROR:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_ERROR\n");
        return -1;
        break;

    case GNS_SERVER_PACKET_TYPE_REQUEST:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_REQUEST\n");
        return -1;
        break;

    case GNS_SERVER_PACKET_TYPE_EVENT:
        debug_print ("__gns_hello_response: GNS_SERVER_PACKET_TYPE_EVENT\n");
        return -1;
        break;

    default:
        return -1;
        break;
    };

//
// done:
//

    char response_buffer[64];
    response_buffer[0]=0;

process_reply:

    //#bugbug: Overflow. We need a limit here.
    //#todo: Get the size of the message
    //and then put the message into the tmp buffer.
    sprintf( response_buffer, (__gns_buffer+128) );
    response_buffer[63] = 0;  //finaliza

// Se tem alguma coisa no buffer.
    if( *response_buffer != 0 )
        printf("RESPONSE: {%s} \n", response_buffer );

    return TRUE;
}


// =============================================

int gns_hello (int fd)
{
    int status=-1;

    int __saved_global_sync_id = sc82 (10005,0,0,0);

    if (fd<0){
        debug_print("gns_hello: fd\n");
        return FALSE;
    }


// Reset flags.
// Configuramos a flag para que possamos escrever.
   debug_print ("gns_hello: reset flags\n");      
    
   rtl_set_global_sync( 
       __saved_global_sync_id,   // 
       216,  // request. (We can write)
       0 );  // data


// Request.
// Avisamos que um request foi enviado.
   debug_print ("gns_hello: Send request\n");      

    __gns_hello_request(fd);
    rtl_set_global_sync( __saved_global_sync_id, SYNC_REQUEST_SET_ACTION, ACTION_REQUEST );


// Response.
// Waiting to read the response.
   debug_print ("gns_hello: Read response\n");      

    int value=0;
    while (1){
        value = rtl_get_global_sync( __saved_global_sync_id, SYNC_REQUEST_GET_ACTION );
        if (value == ACTION_REPLY ) { break; }
        if (value == ACTION_ERROR ) { return -1; }
        if (value == ACTION_NULL )  { return -1; }  // no reply
    };
    
    // A sicronização nos diz que ja temos um reply,
    // então não precisamos esperar.
    status = (int) __gns_hello_response(fd);

    // Se não conseguimos ler a resposta.
    // Então vamos reconfigurar as flags do arquivo
    // dizendo que queremos autorização para escrever.
    // Na verdade esse erro na hora de ler a resposta
    // ja é motivo pra fechar a conexão.
    /*
    if (status<0)
    {
        rtl_set_global_sync( 
            __saved_global_sync_id,   // fd 
            216,  // request
            0 );  // data
    }
    */
    
    return TRUE;
}




















