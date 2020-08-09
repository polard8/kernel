

 
 
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>


//#test
#include <gws.h>

int main ( int argc, char *argv[] )
{
    int pid=getpid();
    int ppid=getppid();
    
    
    while(1){
    gws_debug_print("s1: Sending message to terminal\n");
    gws_send_message_to_process(ppid,0,7000,0,0);

    }
    return 0;
}

