/*
 * File: sm.c  
 *
 *     Server Manager 
 *
 *  
 */


/*
A basic set of servers for a general-purpose microkernel includes 
file system servers, 
device driver servers, 
networking servers, 
display servers, 
and user interface device servers.

The necessary servers are started at system startup and provide services, 
such as file, network, and device access, to ordinary application programs.

display server
timer server
int fs_server();
int mm_server();
int xx_server();
*/


#include <kernel.h>



//
// == register ws =====================
//

/*
//See: gde_serv: 513
int sm_register_ws(int pid);
int sm_register_ws(int pid)
{
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                __desktop->ws = (int) arg3;
                
                
                // What is the process listen to the port 11.
                gramado_ports[GRAMADO_WS_PORT] = (int) current_process;
                
                // returning ok.
                // But, we could return the port number.
                return (void *) 1;  //ok 
            }
        }
        return NULL; //fail
}
*/



//
// == unregister ws =====================
//

/*
int sm_unregister_ws(void);
int sm_unregister_ws(void)
{
}
*/

//
// == register ns =====================
//
//See: gde_serv: 521
/*
int sm_register_ns(int pid);
int sm_register_ns(int pid)
{
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                __desktop->ns = (int) arg3;
                
                
                // What is the process listen to the port 11.
                gramado_ports[GRAMADO_NS_PORT] = (int) current_process;
                
                // returning ok.
                // But, we could return the port number.
                return (void *) 1;  //ok 
            }
        }
        return NULL; //fail
}
*/

//
// == unregister ns =====================
//
/*
int sm_unregister_ns(void);
int sm_unregister_ns(void)
{
}
*/



/*
 * init_systemserver:
 *     System server supprt.
 */

int init_systemserver (void)
{
    debug_print ("init_systemserver: [TODO] Not used yet\n");
    return 0;  //Ainda não implementada.
}




//
// End.
//

