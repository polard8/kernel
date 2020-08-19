


// libc03
#include <types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

//#bugbug
//#include <netdb.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>

// libgws
#include "include/connect.h"  
#include "include/gws.h"  


// get next event.
// the window server return the next event
// from the queue of a client.
struct gws_event_d *gws_next_event(int fd)
{
    return (struct gws_event_d *) 0;
}


// Send event.
// It is gonna be used by the window manager to send 
// events to the window server.
// Remember: The window manager gets the system messages
// end sends window events to the window server.
void 
gws_send_event ( 
    int fd, 
    int window, 
    struct gws_event_d *event )
{
}



