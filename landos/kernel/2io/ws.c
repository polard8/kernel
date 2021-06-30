

#include <kernel.h>

// This is called at the kernel initialization to initialize
// the window server struct with the embedded window server info.
int ws_init (void)
{

    debug_print ("ws_init: \n");

    //#todo
    //WindowServer.desktop = (struct desktop_d *) __desktop;

    // The system starts with the embedded window server.
    WindowServer_type = WindowServerTypeEmbedded;
    
    // #todo
    // Use the pid of the kernel process.
    //WindowServer.pid = (pid_t) current_process;

    // name.
    WindowServer_name[0] = 'k';
    WindowServer_name[1] = 'g';
    WindowServer_name[2] = 'w';
    WindowServer_name[3] = 's';
    WindowServer_name[4] = 0;
    
    WindowServer_virtual_console = 0;

    // ...

    WindowServer_initialized = TRUE;
    return 0;
}

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

void ws_show_info(void)
{
    printf("name %s\n",WindowServer_name);
    printf("initialized     %d\n", WindowServer_initialized);
    printf("type            %d\n", WindowServer_type);
    printf("pid             %d\n", WindowServer_pid);
    printf("virtual console %d\n", WindowServer_virtual_console);
    refresh_screen();
}


//
// End.
//














