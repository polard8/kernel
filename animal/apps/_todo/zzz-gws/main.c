// main.c
// Arquivo principal do gws.
// As funções começam com o nome do módulo
// para que em client side começem com gws_


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


#include <gws.h>

#include <api.h>


// Our desktop;
struct desktop_d *__desktop;

// Our PID.
int __ws_pid;



//window.
struct window_d *__mywindow; 
  
  

  
  
// #bugbug
// existe um outro procedimento em gws.c
// mas queremos apenas um , esse aqui.!!
// deletar o outro.       

int 
gwsProcedure ( struct window_d *window, 
               int msg, 
               unsigned long long1, 
               unsigned long long2 );
                   
int 
gwsProcedure ( struct window_d *window, 
               int msg, 
               unsigned long long1, 
               unsigned long long2 )
{
    switch(msg)
    {

        case MSG_SYSKEYUP:
            switch ( long1)
            {
                case VK_F1:
                    gde_reboot ();
                    break;
            }    
            break;

        // #test
        // Tentando receber uma mensagem de digitação.
        case MSG_KEYDOWN:
            
            //#bugbug: Isso está falhando.
            //mas o f1 funciona.
            printf ("%c", (char) long1); 
            //gde_show_backbuffer ();
            break;

        case 1000:
        
            //draw text inside a window.
            dtextDrawText ( (struct window_d *) __mywindow,
                40, 60,
                COLOR_RED,
                "Hello friend. This is the Window Server!" );
                
             printf ("Hello friend! %d %d \r \n", long1, long2 );
            
             //#todo: send response.
            
             gde_show_backbuffer ();
             break;
                
         //
         // Testing some drawing routines.
         //
         
         // put pixel
         // IN: Color, x, y
         case 2000:
             pixelBackBufferPutpixel ( (unsigned long) COLOR_PINK,   
                 (unsigned long) long1, (unsigned long) long2 );
             break;
 
 
         case 2001:
             break;
             
         case 2002:
             break;
             
             
         case 2003:
             break;

         // Refresh screen 
         // refresh screen using kgws service. 
         case 2020:
             gde_show_backbuffer ();
             break;
             

         // Refresh rectangle ... 
         case 2021:
             break;

         // ...
             
                
         default:
             //printf ("msg=%d ",msg);
             break;
    }

    return (0);
}



/*
 * main: 
 *     
 * 
 */
 
int main (int argc, char **argv){
    
    // #todo
    // Use the debug funcion via serial port.
    
    // #debug
    printf ("gws: gws is alive !  \n");

    
    // Init gws infrastructure.
    
    gwsInit ();

    
    // #tests
    // Isso funciona.
    //pixelBackBufferPutpixel ( COLOR_RED,   100, 250 );
    //pixelBackBufferPutpixel ( COLOR_GREEN, 105, 250 );
    //pixelBackBufferPutpixel ( COLOR_BLUE,  110, 250 );
    //charBackbufferDrawcharTransparent ( 250,       250, COLOR_RED,   (unsigned long) 'R');
    //charBackbufferDrawcharTransparent ( 250 +8,    250, COLOR_GREEN, (unsigned long) 'G');
    //charBackbufferDrawcharTransparent ( 250 +8 +8, 250, COLOR_BLUE,  (unsigned long) 'B');
    //charBackbufferDrawchar ( 300, 300, (unsigned long) 'X', COLOR_YELLOW, COLOR_RED );
    //lineBackbufferDrawHorizontalLine ( 400, 88, 500, COLOR_PINK );
    //rectBackbufferDrawRectangle ( 200, 400, 100, 60, COLOR_YELLOW );


    //createwCreateWindow ( WT_SIMPLE, 1, 1, "FIRST-WINDOW",  
        //10, 60, 
        //(800/3), (600/3),   
        //gui->screen, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );
    

    //createwCreateWindow ( WT_EDITBOX, 1, 1, "FIRST-WINDOW",  
      //  80, 80, 
      //  300, 40,   
      // gui->screen, 0, xCOLOR_GRAY3, xCOLOR_GRAY3 );


    
    __mywindow = (struct window_d *) createwCreateWindow ( WT_OVERLAPPED, 
                                         1, 1, "overlapped",  
                                         20, 20, 
                                         480, 320,   
                                         gui->screen, 0, 
                                         xCOLOR_GRAY3, xCOLOR_GRAY3 );

 
    //
    // Calling child.
    //


    // Draw text inside a window.
    dtextDrawText ( (struct window_d *) __mywindow,
        40, 40, 
        COLOR_RED, "gws: Calling child" );
      

    // fail !!!
    // Não está rodando o aplicativo que chamamos.     
    gde_clone_and_execute ("iliinit.bin");        
    //gde_clone_and_execute ("gdeshell.bin");        
    //gde_clone_and_execute ("iliinit.bin");        
    // ...


    //
    // Refresh screen.
    //

    gde_show_backbuffer ();
   
   
    //
    // Desktop
    //

    // Getting current desktop;

    __desktop = (struct desktop_d *) gramado_system_call (519,0,0,0);


     //draw text inside a window.
     //draw_text ( (struct window_d *) __mywindow,
       // 40, 40,
        //COLOR_RED,
         //"Drawing some text inside a window!" );


    __ws_pid = (int) getpid();

    // Set ws PID
    // Setar esse processo como o ws do sistema.
    gramado_system_call ( 513, 
        __desktop, __ws_pid, __ws_pid);



    //
    // Event loop
    //

    // Message loop and compositor loop.

    unsigned long message_buffer[5];   
    
event_loop:

    while (1)
    {
        gde_enter_critical_section ();
        gramado_system_call ( 111,
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section ();

        if ( message_buffer[1] != 0 )
        {
            gwsProcedure ( (struct window_d *) message_buffer[0], 
                (int) message_buffer[1], 
                (unsigned long) message_buffer[2], 
                (unsigned long) message_buffer[3] );

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;
            
            //compositor_loop ();
        };
    };



// Error

    return 1; 
}
 





