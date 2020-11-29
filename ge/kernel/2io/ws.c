

#include <kernel.h>


// Let's setup the window server.
// See:
// ws/model/ws.h
int 
ws_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    
    // #todo
    // We have a structure in ws.h
    
    debug_print("ws_ioctl: [TODO]\n");
    return -1;
}


// This is called at the kernel initialization to initialize
// the window server struct with the embedded window server info.
int ws_init (void)
{

    debug_print ("ws_init: \n");

    //#todo
    //WindowServer.desktop = (struct desktop_d *) __desktop;

    // The system starts with the embedded window server.
    WindowServer.type = WindowServerTypeEmbedded;
    
    // #todo
    // Use the pid of the kernel process.
    //WindowServer.pid = (pid_t) current_process;

    // name.
    WindowServer.name[0] = 'k';
    WindowServer.name[1] = 'g';
    WindowServer.name[2] = 'w';
    WindowServer.name[3] = 's';
    WindowServer.name[4] = 0;
    
    
    WindowServer.virtual_console = 0;

    WindowServer.initialized = 1;
        
    return 0;
}



//
// End.
//


