
// File: iliinit.c
// Inicializar o ambiente ILI.
// No momento usado para testar a comunicação com o Window Server.
// Created by Fred Nora.

#include <sys/cdefs.h>
#include <stdlib.h>
//#include <stdio.h>
//#include <unistd.h>
#include <api.h>


#include <sys/types.h>
#include <sys/socket.h>


//#bugbug: temos que usar o id.
struct desktop_d *__desktop;


int __ws_pid;   



/*
 * main: 
 * 
 * 
 */
 
int main (int argc, char **argv){

    // #debug
    // printf ("iliinit:   \n");
    // gde_message_box ( 3, "iliinit", "hola!" );            
    // while(1){}
    
    
 
    //
    // Desktop
    //


    // get current desktop;
    
    // #bugbug: isso é um id.

    __desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);
   
    
   //
   // get ws pid
   //

    // Get ws PID for a given desktop
    __ws_pid = (int) gramado_system_call ( 512,
                         (unsigned long) __desktop,
                         (unsigned long) __desktop,
                         (unsigned long) __desktop );
    
    if (__ws_pid < 0){
        gde_message_box ( 3, "iliinit", "ws fail" ); 
        gde_exit (1);
        
    }else{


        // Send message.
        // Envia uma mensagem pedindo para o ws emitir um hello!
        // msg = 1000;

        // IN: PID, window, msg, long1, long2
        gde_send_message_to_process ( __ws_pid, 
            NULL, 1000, getpid(), getpid() );  
            

        // enviando mais vezes pra testar a fila de mensagens
        // ok, funcionou no qemu.
        //gde_send_message_to_process ( __ws_pid, 
            //NULL, 1000, 0, 0 );  
        //gde_send_message_to_process ( __ws_pid, 
            //NULL, 1000, 0, 0 );  
        //gde_send_message_to_process ( __ws_pid, 
            //NULL, 1000, 0, 0 );  
            

        // Testing the Window Server.
 
        // put some pixel in this position.
        gde_send_message_to_process ( __ws_pid, 
            NULL, 2000, 40, 40 );  

        // refresh screen
        gde_send_message_to_process ( __ws_pid, 
            NULL, 2020, 0, 0 );  
    };


    return 0; 
}
 


