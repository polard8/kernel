 
//glogon gramado logon

/*	$NetBSD: tty.c,v 1.8 2011/09/06 18:34:57 joerg Exp $	*/

/*
 * Copyright (c) 1988, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


 

int main (int argc, char **argv){

    printf ("gwinmgr:  \n");    
   

    // >> pegar pid do ws do desktop atual
    // >> enviar mensagem para o ws.


    unsigned long message_buffer[5];


    //
    // Desktop
    //

    // 519
    // get current dsktop;
    struct desktop_d *__desktop;
    
    //current desktop.
    __desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);


    //
    // Setup wm
    //
    
    int __ws_pid;
    char buffer[20];
    
    // 714 - get ws PID for a given desktop
    __ws_pid = (int) gramado_system_call ( 714,
                         (unsigned long) __desktop,
                         (unsigned long) __desktop,
                         (unsigned long) __desktop );
    
    if (__ws_pid >= 0)
    {
        gde_message_box ( 3, 
            "gws", 
            "Another ws is already running!" ); 
            exit(1);
 
    }else{
		
		gde_clone_and_execute ("gws.bin");
    
        // tem que esperar
        // pra poder enviar a mensagem ...
        // Por isso vamos mandar várias mensagens. Só um teste;

          

        // itoa(__ws_pid,buffer);  

         while(1)
         {
            //714 - get ws PID for a given desktop
            //__ws_pid = (int) gramado_system_call ( 714,
              //             (unsigned long) __desktop,
                //           (unsigned long) __desktop,
                  //         (unsigned long) __desktop );
 
             //gde_message_box (3,"xxx",buffer);
            //printf ("gwinmgr: ws_pid=%d \n", __ws_pid );
         }
       // while(1)
       // {
              //printf ("gwinmgr: ws_pid=%d \n", __ws_pid );

             // message_buffer[0] = (unsigned long) 0;
             // message_buffer[1] = (unsigned long) 1000;
             // message_buffer[2] = (unsigned long) 0;
             // message_buffer[3] = (unsigned long) 0;
    
             // system_call ( 112 , 
                //    (unsigned long) &message_buffer[0], 
                  //  (unsigned long) __ws_pid, 
                  //  (unsigned long) __ws_pid );
    
            //gde_send_message_to_process ( __ws_pid, 
              //                   NULL,    //window
                //                 1000,    //msg
                  //               0,       //long1
                    //             0 );     //long2    
       // }
    };   
    
 
    //gde_clone_and_execute ("gdeshell.bin");  
    while(1){}
    
    
    
    
    
    
    
    //
    // ============= cut ================
    //
    printf ("Testing fork() \n"); 
        
    int pidFORK = (int) fork ();

		// Erro.
		if ( pidFORK < 0 )
		{
		    printf ("gwinmgr: fork() falhou\n");
			printf ("getpid=%d ", getpid());
			printf ("pidFORK=%d \n", pidFORK);
            while(1){}
            //exit (1);
		}
		
		// Pai.
		if ( pidFORK > 0 )
		{
			printf("\n");
		    printf ("gwinmgr: Estamos no >>>>> PAI\n");
			printf ("getpid=%d ", getpid());
			printf ("pidFORK=%d \n", pidFORK);
			printf ("gwinmgr: *hang Parando no pai.\n");
			while(1){}
			//exit (0);
		}
		
		// Filho.
		if ( pidFORK == 0 )
		{
			printf("\n");
		    printf ("gwinmgr: estamos no >>>> FILHO\n");
			printf ("getpid=%d ", getpid());
			printf ("pidFORK=%d \n", pidFORK);
			
			execve ("launcher.bin", NULL, NULL );
			
			printf ("gwinmgr: *hang Parando no filho.\n");
			while(1){}
			
			//exit (1);
		}

    return 0; 
}
 


