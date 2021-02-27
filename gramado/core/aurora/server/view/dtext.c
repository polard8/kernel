/*
 * File: dtext.c 
 * 
 *     Draw text routines.
 */


#include <gws.h>



// Draw text.
// Service 1005
int serviceDrawText (void)
{

    // Global buffer.
    unsigned long *message_address = (unsigned long *) &__buffer[0];


    struct gws_window_d  *window;
    
    int window_id = -1;      // index 4
    unsigned long x;         // index 5
    unsigned long y;         // index 6
    unsigned long color;     // index 7


    // #debug
    gwssrv_debug_print ("gwssrv: serviceDrawText\n");


    // Get

    window_id = (int) message_address[4];
    x         = (unsigned long) message_address[5];
    y         = (unsigned long) message_address[6]; 
    color     = (unsigned long) message_address[7];


    /*
    //size 256 bytes
    unsigned char *text_buffer = (unsigned char *) &message_address[MSG_OFFSET_LONGSTRING];  
   
    int s = sizeof(text_buffer);
   
    if(s<0 || s>= 256)
    {
        gwssrv_debug_print ("gwssrv: serviceDrawText [DEBUG]   SIZE \n");
        exit(1);
    }
    */


   //
   // == Draw ==========================================
   //


    //#todo
    // Get the window structure given the id.
    //window = (struct gws_window_d *) windowList[window_id];
    
    //#test
    // Usando a janela screen por enquanto.
    
    // OK. string funcionou.
        
    unsigned char buf[256+1];
    int i=0;
    int string_off=8;
    for(i=0; i<256; i++)
    {
         buf[i] = message_address[string_off];
         string_off++;
    }
    buf[i] = 0;
    
    
    //
    // == Draw ===============================================
    //
    
    //#todo
    //switch (alignment) {  ... }
    
    
    //dtextDrawText ( (struct gws_window_d *) gui->screen,
        //x, y, color, buf ); 


    if (window_id>0 && window_id < WINDOW_COUNT_MAX)
    {

        window = (struct gws_window_d *) windowList[window_id];
        
        if ((void*)window!=NULL){
            dtextDrawText ( (struct gws_window_d *) window,
                x, y, color, buf );
        
            gws_show_window_rect(window);
        }
    
    //#debug
    }else{

        if ( (void*) gui->screen_window != NULL ){
            
            dtextDrawText ( 
                (struct gws_window_d *) gui->screen_window,
                x, y, color, buf ); 
            
            // #bugbug
            //  Mostrando sempre. Isso eh lento.
            gws_show_window_rect(gui->screen_window);
         }
    };


   // #debug
   // We are refreshing the whole screen for now.
   // #todo: let's try to refresh only the window.
   // or each char maybe.
   
   //gws_show_backbuffer(); 
   
   return 0;
}




/* 
 * dtextDrawString:
 *     Draw a string on the screen. 
 */

void 
dtextDrawString ( 
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned char *string )
{

    int Index=0;

    //#bugbug:  Determinando
    int cWidth = 8;   
	//int cWidth = get_char_width ();
	//int cHeight = get_char_height ();


	//if ( cWidth == 0 || cHeight == 0 )
    if ( cWidth == 0 )
    {
        //panic ("dtext-draw_string: cWidth");
    
        //#debug
        //gde_message_box (3, "xxx","dtext-draw_string: cWidth");
        printf ("dtextDrawString: cWidth\n");
        while(1){}
    }

    //int size = sizeof(string);  
    //for ( Index=0; Index<size; Index++ )
    
    for ( Index=0; string[Index] != 0; Index++ )
    {
        charBackbufferDrawcharTransparent ( x, y, 
            color, string[Index] );

        //#todo: 
        //   Conflito de tipo no argumento 4.
        //   gcharWidth.
        //my_buffer_char_blt( x, y, color, string[Index]);
        //drawchar_transparent ( x, y, color, string[Index] );
        
		//#todo: 
		//Tamanho do char. Usar variável.

        x += cWidth;
    };
}


/* 
 * dtextDrawText:
 *     Draw text on a window.
 *
 * #test: 
 *     Como opção, se nenhuma janela for especificada, 
 *     então pintaremos na janela principal.
 */

void 
dtextDrawText ( 
    struct gws_window_d *window,
    unsigned long x,
    unsigned long y,
    unsigned long color,
    unsigned char *string )
{ 

    struct gws_window_d * __w;


    __w = (struct gws_window_d *) gui->screen_window;


    if ( (void *) window == NULL ){

        if ( (void*)__w != NULL )
        {
            dtextDrawString ( 
                (__w->left +x), 
                (__w->top  +y), 
                color, 
                string );
            return;
        }
        gwssrv_debug_print("dtextDrawText: __w\n");
        return;

    }else{
        dtextDrawString ( 
            (window->left +x), 
            (window->top  +y), 
            color, 
            string );
    };
}


