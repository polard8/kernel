
// Ok. This is the system's API. 
// It uses the kgws window server for the gui stuff.
// kgws is a window server embedded inside the base kernel.
// But now we are creating a ring3 loadable window server 
// called gwssrv.bin, codename aurora and we will use a 
// client-side library called libgws for this window server.

/*
 * File: api.c 
 *
 * Description:
 *     Application Programming Interface - (API).
 *
 *
 * History: 
 *     2014 - Created by Fred Nora.
 */


// rtl
#include <types.h> 
//#include <sys/types.h>    //#todo    
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <heap.h>   
#include <rtl/gramado.h>   //#test

#include "include/api.h"  



// Buttons
struct window_d  *first_responder;
struct window_d  *messagebox_button1;
struct window_d  *messagebox_button2;
struct window_d  *dialogbox_button1;
struct window_d  *dialogbox_button2;
// ...


//
// Protótipos de funções internas.
//


unsigned long 
mbProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


unsigned long 
dbProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


/*
 ***************************************************
 * system_call:  
 *
 *    The system interrupt.
 *    Interrupt number 0x80.
 *
 * IN:
 *    eax = arg1, The number of the system service.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */

// #define  IA32_SYSCALL_VECTOR    0x80 

// #todo
// We can create gde_sc80, gde_sc81, gde_sc82
// just like in the rtl.

void *system_call ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{
    unsigned long __RET = 0;

    asm volatile ( 
        "int %1 \n"
        : "=a"(__RET)
        : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    return (void *) __RET;
}



/*
 ***********************************
 * gde_system:
 *  
 *     #todo: 
 *     It runs a command using fork/execve or something else.
 */

int gde_system (const char *command)
{
    gde_debug_print ("gde_system: [TODO]\n");
    
    //if ( (void*) command == NULL )
        // ...
    
    //if ( *command == 0 )
         // ...
         
    return -1;
}




//=====================================
// #obs
// some other functions.


/*
 **********************************************
 * gde_refresh_buffer:
 * 
 *     int 0x80, serviços de 1 à 9.
 *     Refresh buffer.
 *     Atualiza um buffer dado seu número.  (rever) 
 */

void gde_refresh_buffer (unsigned long n)
{
    //n=0;
    gde_debug_print ("gde_refresh_buffer: [FIXME]\n");
    //return;
}



/*
 * gde_print_string:
 *     int 0x80, serviço 10.
 *     Print string no buffer.  (rever) 
 */

void 
gde_print_string ( 
    unsigned long x,  
    unsigned long y,  
    unsigned long color, 
    unsigned char *string )
{
    gde_debug_print ("gde_print_string: [TODO]\n");
}


/*
 **********************
 * gde_vsync:
 *     Int 0x80, serviço 15.
 *     Call the kernel to make a vertical retrace synchronization.
 *     Is this an old crt thing? hahaha
 */

int gde_vsync (void)
{
    return (int) gramado_system_call ( SYSTEMCALL_VSYNC, 0, 0, 0 );
}


/*
 ******************************************************
 * gde_system_procedure:
 *
 *    It calls a window procedure inside the base kernel.
 */

void *gde_system_procedure ( 
    struct window_d *window,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    unsigned long message_buffer[5]; 
    message_buffer[0] = (unsigned long) window; 
    message_buffer[1] = (unsigned long) msg;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;
    
    if ( (void *) window == NULL ){ return NULL; }
    if ( msg <= 0 )               { return NULL; }

    return (void *) system_call ( SYSTEMCALL_CALL_SYSTEMPROCEDURE, 
                        (unsigned long) &message_buffer[0], 
                        (unsigned long) &message_buffer[0], 
                        (unsigned long) &message_buffer[0] );
}




/*
 **********************************
 * __gde_set_cursor:
 *
 */

int __gde_set_cursor (unsigned long x, unsigned long y)
{
    return (int) gramado_system_call ( SYSTEMCALL_SETCURSOR, x, y, 0 );
}


/*
 *************************************************
 * __gde_put_char:
 *     Put char.
 */

void 
__gde_put_char ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned char *ch )
{
    gde_debug_print ("__gde_put_char: [TODO]\n");
}


/*
 ************************************************************
 *  gde_load_bitmap_16x16:
 * 
 *     Coloca um bitmap no buffer.
 *     interrupção 200, serviço SYSTEMCALL_LOAD_BITMAP_16x16, 
 *     pôe um bitmap no buffer.
 *
 *     ?? @todo: Rever, onde pega e pra onde vai.
 *
 * a - endreço da imagem. 
 * b - x
 * c - y 
 * d - null
 *
 * Obs: 
 *     Lembrar que estamos usando endereços lógicos.  (rever)
 */

void 
gde_load_bitmap_16x16 ( 
    unsigned long img_address, 
    unsigned long x, 
    unsigned long y )
{
    
    // NULL pointer
    if ( img_address == 0 )
    {
        // msg
        return;
    }

    system_call ( SYSTEMCALL_LOAD_BITMAP_16x16, img_address, x, y ); 
}


/*
 *************************
 * gde_load_path 
 * 
 */

// IN: 
// pathname, ring3 buffer, ring3 buffer limit.

int 
gde_load_path ( 
    const char *path, 
    unsigned long buffer, 
    unsigned long buffer_len )
{
    int status = -1;
    size_t Size=0;

    if ( (void*) path == NULL ){
        printf ("gde_load_path: [FAIL] path\n");
        return (int) -1;
    }

    if (*path != '/'){
        printf ("gde_load_path: [FAIL] It's not an absolute pathname\n");
        return (int) -1;
    }

    if (*path == 0){
        printf ("gde_load_path: [FAIL] *path\n");
        return (int) -1;
    }

    Size = strlen(path);
    
    if (Size == 0){
        printf ("gde_load_path: [FAIL] Size\n");
        return (int) -1;
    }

    if (buffer == 0){
        printf ("gde_load_path: [FAIL] buffer\n");
        return (int) -1;
    }

    if (buffer_len == 0){
        printf ("gde_load_path: [FAIL] buffer_len\n");
        return (int) -1;
    }

    status = (int) gramado_system_call ( 4004, 
                       (unsigned long) path, 
                       (unsigned long) buffer, 
                       (unsigned long) buffer_len );

    return (int) status;
}


/*
 **********************
 * gde_shutdown:
 *     Shutdown the machine.
 */

void gde_shutdown (void)
{
    gde_debug_print ("gde_shutdown: [TODO]\n");
    //gramado_system_call ( ??, 0, 0, 0 );

    while (1){ asm ("pause"); };
}



/*
 * gde_init_background:
 *     Initialize default background configuration. 
 */

void gde_init_background (void)
{
    // todo: Implementar.	
    // Não há uma chamada para isso ainda.

    gde_debug_print ("gde_init_background: [TODO]\n");
}



/*
 ***************************************************
 * gde_message_box:
 *     Message box on gui->screen.
 *     Types=[1~5]
 *     @todo: Devemos considerar o retorno? E se a chamada falhar?
 */

// #todo
// It can be usefull in the setup environment.
// #todo: 
// usar get system metrics

int __mb_current_button; 

int 
gde_message_box ( 
    int type, 
    char *string1, 
    char *string2 )
{

    struct window_d *hWnd;    // Window.
    int Response = 0;

    int running = 1;          // Loop.


    unsigned long deviceWidth  = gde_get_system_metrics(1); 
    unsigned long deviceHeight = gde_get_system_metrics(2);

    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        printf ("gde_message_box: device size\n");
        return -1;
    }

    // dimensoes
    unsigned long cx = (unsigned long) (deviceWidth/3);   // largura 
    unsigned long cy = (unsigned long) (deviceHeight/3);  // altura

    // posicionamento.
    unsigned long x  = (unsigned long) ( ( deviceWidth  - cx ) >> 1 ); 
    unsigned long y  = (unsigned long) ( ( deviceHeight - cy ) >> 1 ); 
    
    
    int current_mode = rtl_get_system_metrics(130);
    if (current_mode == GRAMADO_JAIL ){
        x=0;  y=0;  cx=deviceWidth;  cy=deviceHeight;
    }
    
    // check

    if ( cx == 0 || cy == 0 )
    {
        printf ("gde_message_box: cx cy\n");
        return -1;
    }

    
    int Button = 0;

    // Colors;
    unsigned long WindowClientAreaColor=0;
    unsigned long WindowColor=0;


    // Colors.
    WindowClientAreaColor = xCOLOR_GRAY3;
    WindowColor           = COLOR_TERMINAL2;

    // Seleciona o botão 1. first responder;
    __mb_current_button = 1;
    first_responder = messagebox_button1;



    if ( (void*) string1 == NULL ){
        gde_debug_print ("gde_message_box: string1\n");
        return -1;
     }

    if ( (void*) string2 == NULL ){
        gde_debug_print ("gde_message_box: string2\n");
        return -1;
    }

    if (*string1 == 0){
        gde_debug_print ("gde_message_box: *string1\n");
        return -1;
    }

    if (*string2 == 0){
        gde_debug_print ("gde_message_box: *string2\n");
        return -1;
    }



	// Obs: 
	// Por enquanto para todos os tipos de messagebox 
	// estamos usando o mesmo tipo de janela.


	//if (type <0)
		//return -1;


    // ??
    // Qual eh o tipo de message box.
    switch (type){

        // fail
        case 1:
        case 2:
            printf ("message box type not supported\n");
            return (int) -1;
            break;

        // ok
        case 3:
            goto do_create_messagebox_3;
            break;

        // fail
        case 4:
        default:
            printf ("message box type not supported\n");
            return (int) -1;
            break;
    };

// == Create Window ==============================================

do_create_messagebox_3:

    // Características.
    Button = 1;
    //...
    

    //++
    gde_enter_critical_section ();
    
    hWnd = (void *) gde_create_window ( 
                        WT_OVERLAPPED, 1, 1, string1, 
                        x, y, cx, cy, 
                        NULL, 0, 
                        WindowClientAreaColor, WindowColor );


    if ( (void *) hWnd == NULL ){
        printf ("gde_message_box: hWnd\n");
        return (int) -1;
    }else{

        gde_register_window (hWnd);
        //APISetActiveWindow (hWnd);
        //gde_set_focus (hWnd);
        
        gde_draw_text ( 
            (struct window_d *) hWnd,
            1*(cx/16), 1*(cy/3), COLOR_WHITE, string2 );

        gde_show_window (hWnd);
    };

    gde_exit_critical_section ();
    //--

	//======================================
	// button support
	//
	
	//obs: o procedure vai precisar dos botões então tem que declarar global.
	
	//unsigned long app1Left = ((ScreenWidth/8) * 2);
	//unsigned long app2Left = ((ScreenWidth/8) * 3);
	
	//unsigned long app1Top = ( (ScreenHeight/10) * 8); 
	//unsigned long app2Top = app1Top; 



    //++
	// button 1
    gde_enter_critical_section ();

    messagebox_button1 = (void *) gde_create_window ( 
                                      WT_BUTTON, 1, 1, "[F1] OK", 
                                      ((cx/2)*0), ((cy/8)*6), (cx/2), 24,
                                      hWnd, 0, 
                                      xCOLOR_GRAY1, xCOLOR_GRAY1 );

    if ( (void *) messagebox_button1 == NULL ){
        printf ("OK button fail\n");
        return (int) -1;
    }else{
        gde_register_window (messagebox_button1); 
        gde_show_window (messagebox_button1);
    };

    gde_exit_critical_section ();
    //--


    //++
	// button 2
	gde_enter_critical_section ();

	messagebox_button2 = (void *) gde_create_window ( 
	                                  WT_BUTTON, 1, 1, "[F2] CANCEL",     
                                      ((cx/2)*1), ((cy/8)*6), (cx/2), 24,    
                                      hWnd, 0, 
                                      xCOLOR_GRAY1, xCOLOR_GRAY1 );

    if ( (void *) messagebox_button2 == NULL ){
        printf (" CANCEL button fail \n");
        return (int) -1;
    }else{
        gde_register_window (messagebox_button2); 
        gde_show_window (hWnd);
    };
    
    gde_exit_critical_section();
    //--

    // string
    // apiDrawText ( (struct window_d *) hWnd,
    //    1*(cx/16), 1*(cy/3), COLOR_WINDOWTEXT, string1 );	

    // #sustenso:
    // Show window.
    // apiShowWindow (hWnd);

// == Message loop ===============================================

    // buffer.
    unsigned long message_buffer[5];
    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[3] = 0;
    message_buffer[4] = 0;

Mainloop:

    while (running){

        //++
        gde_enter_critical_section();
        system_call ( 111, 
            (unsigned long) &message_buffer[0],
            (unsigned long) &message_buffer[0], 
            (unsigned long) &message_buffer[0] );
        gde_exit_critical_section();
        //--

        if ( message_buffer[1] != 0 )
        {
            Response = (int) mbProcedure ( 
                                 (struct window_d *) message_buffer[0], 
                                 (int)               message_buffer[1], 
                                 (unsigned long)     message_buffer[2], 
                                 (unsigned long)     message_buffer[3] );

            // Temos uma resposta.
            if (Response > 100){
                printf ("Response = %d \n", Response );
                goto exit_messagebox;
            }

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;
        };
    };

// Exit message box.

exit_messagebox:

    // #debug
    //printf ("Exiting Message Box \n");

    return (int) Response;
}


/*
 **************************************************
 * mbProcedure:
 *     O procedimento padrão de message box. 
 *     #interna
 */

unsigned long 
mbProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    switch (msg)
    {
        // MSG_MOUSEKEYDOWN
        case 30:
            switch (long1)
            {
                case 1:
                    if ( window == messagebox_button1 )
                    {
                        gramado_system_call ( 
                            9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        return (unsigned long) 0;
                        break;
                    }
                    if ( window == messagebox_button2 )
                    {
                        gramado_system_call ( 
                            9900,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        return (unsigned long) 0;
                        break;
                    }
                break;
            };
            break;

        //mouse keyup    
        case 31:
            switch (long1)
            {
                case 1:
                    if ( window == messagebox_button1 )
                    {
                        gramado_system_call ( 
                            9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        // Response [YES]
                        return (unsigned long) 102;
                        break;
                    }
                    if ( window == messagebox_button2 )
                    {
                        gramado_system_call ( 
                            9901,   
                            (unsigned long) window, 
                            (unsigned long) window, 
                            (unsigned long) window );
                        // Response [NO]
                        return (unsigned long) 101; 
                        break;
                    }
                    break;
            };
            break;

        case MSG_KEYUP:
            switch(long1)
            {
                case VK_RETURN:
                    return (unsigned long) 0;
                    break;

                default:
                    return (unsigned long) 0;
                    break; 
            };
            break;


        case MSG_KEYDOWN:
            switch(long1)
            {
                // Response [NO]
                case VK_ESCAPE:
                    return (unsigned long) 101; 
                    break;

                // Response [YES]
                case VK_RETURN:
                    return (unsigned long) 102;
                    break;

                default:
                    return (unsigned long) 0;
                    break; 
            };
            break;


        case MSG_SYSKEYDOWN: 
            switch (long1)
            {
                // Response [OK].
                case VK_F1:
                    printf ("F1: YES\n");
                    return (unsigned long) 102;
                    break;

                // Response [NO]
                case VK_F2:
                    printf ("F2: NO\n");
                    return (unsigned long) 101;
                    break;

                default:
                    return (unsigned long) 0;
                    break;
            };
            break;

        default:
            return (unsigned long) 0;
            break;
    };

    printf ("done\n");
    return (unsigned long) 0;
}


/*
 ******************************
 * gde_dialog_box:
 *     
 *     Types=[1~5]
 *     @todo: Devemos considerar o retorno? E se a chamada falhar? 
 */

int gde_dialog_box ( int type, char *string1, char *string2 )
{
    int Response = 0;
    int running = 1;

    struct window_d *hWnd;    //Window.
    struct window_d *pWnd;    //Parent.
    struct window_d *bWnd;    //Button.

    unsigned long deviceWidth  = gde_get_system_metrics(1); 
    unsigned long deviceHeight = gde_get_system_metrics(2);

    if ( deviceWidth == 0 || deviceHeight == 0 ){
        printf ("gde_dialog_box: [FAIL] device size\n");
        return -1;
    }

    // dimensoes
    unsigned long cx = (unsigned long) (deviceWidth/3);   // largura 
    unsigned long cy = (unsigned long) (deviceHeight/3);  // altura

    // posicionamento.
    unsigned long x  = (unsigned long) ( ( deviceWidth - cx ) >> 1 ); 
    unsigned long y  = (unsigned long) ( ( deviceHeight - cy) >> 1 ); 


    int current_mode = rtl_get_system_metrics(130);
    if (current_mode == GRAMADO_JAIL ){
        x=0;  y=0;  cx=deviceWidth;  cy=deviceHeight;
    }
    
    // check

    if ( cx == 0 || cy == 0 )
    {
        printf ("gde_dialog_box: cx cy\n");
        return -1;
    }

    int Button = 0;

    // Color
    unsigned long WindowClientAreaColor=0;
    unsigned long WindowColor=0;

    WindowClientAreaColor = COLOR_YELLOW;
    WindowColor           = COLOR_PINK;

    gde_debug_print ("gde_dialog_box:\n");


    if ( (void*) string1 == NULL ){
        gde_debug_print ("gde_dialog_box: string1\n");
        return -1;
     }

    if ( (void*) string2 == NULL ){
        gde_debug_print ("gde_dialog_box: string2\n");
        return -1;
    }

    if (*string1 == 0){
        gde_debug_print ("gde_dialog_box: *string1\n");
        return -1;
    }

    if (*string2 == 0){
        gde_debug_print ("gde_dialog_box: *string2\n");
        return -1;
    }


    // Obs: 
    // Por enquanto para todos os tipos de messagebox 
    // estamos usando o mesmo tipo de janela.
    
    switch (type){

	    // Com botão, considera o título.
        case 1:

            gde_begin_paint();
            Button = 1;
            //janela tipo simples.
            hWnd = (void *) gde_create_window (  
                               WT_SIMPLE, 1, 1, string1, 
                               x, y, cx, cy, NULL, 0, 
                               WindowClientAreaColor, WindowColor); 
            if ( (void *) hWnd == NULL )
            {  
                gde_end_paint ();
                printf("gde_dialog_box: hWnd fail\n");
                break;
            }
            gde_end_paint ();

            gde_register_window(hWnd);
            gde_set_active_window(hWnd);
            gde_set_focus(hWnd);
            break;

		// Sem botão, considera o título.	
	    case 2:
            Button = 0;
            hWnd = (void*) gde_create_window ( 
                               WT_POPUP, 1, 1, string1, 
                               x, y, cx, cy, NULL, 0, 
                               WindowClientAreaColor, WindowColor); 
            break;


        // Com botão, Título de alerta.
        // Criamos agora a janela de aplicativo.
        case 3:
            Button = 1;
            hWnd = (void*) gde_create_window ( 
                               WT_OVERLAPPED, 1, 1, "Alert", 
                               x, y, cx, cy, NULL, 0, 
                               WindowClientAreaColor, WindowColor ); 
            break;


        // Com botão, título de mensagem do sistema.	
        case 4:
		    Button = 1;
	        hWnd = (void*) gde_create_window ( WT_OVERLAPPED, 1, 1, "System Message", 
			                x, y, cx, cy, NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;


		//Tipo negligenciado. Usamos o formato padrão.	
		default:
		    Button = 1;
	        hWnd = (void*) gde_create_window ( WT_OVERLAPPED, 1, 1, "Error", 
			                x, y, cx, cy, NULL, 0, 
							WindowClientAreaColor, WindowColor); 
		    break;
    };


	//
	// button
	//
	
	//obs: o procedure vai precisar dos botões então tem que declarar global.
	
	//unsigned long app1Left = ((ScreenWidth/8) * 2);
	//unsigned long app2Left = ((ScreenWidth/8) * 3);
	
	//unsigned long app1Top = ( (ScreenHeight/10) * 8); 
	//unsigned long app2Top = app1Top; 


    // =========
    // button 1 
    dialogbox_button1 = (void *) gde_create_window ( 
                                     WT_BUTTON, 1, 1, "OK", 
                                     (cx/3), ((cy/8)*5), 80, 24,
                                     hWnd, 0, 
                                     xCOLOR_GRAY1, xCOLOR_GRAY1 );

    if ( (void *) dialogbox_button1 == NULL ){
        printf("gde_dialog_box: dialogbox_button1 fail\n");
        return -1;
    }else{
        gde_register_window (dialogbox_button1);
    };


    // ============
    // button 2
    dialogbox_button2 = (void *) gde_create_window ( 
                                     WT_BUTTON, 1, 1, "CANCEL",     
                                     ((cx/3)*2), ((cy/8)*5), 80, 24,    
                                     hWnd, 0, 
                                     xCOLOR_GRAY1, xCOLOR_GRAY1 );

    if ( (void *) dialogbox_button2 == NULL ){
        printf("gde_dialog_box: dialogbox_button2 fail\n");
        return -1;
    }else{
        gde_register_window (dialogbox_button2);
    };


    // Draw and show a string.

    gde_draw_text ( 
        (struct window_d *) hWnd,
        1*(cx/16), 1*(cy/3), 
        COLOR_WHITE, string1 );

    gde_show_window (hWnd);

// ================================
// event loop

    unsigned long message_buffer[5];

    message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[3] = 0;
    message_buffer[4] = 0;

EventLoop:

    while (running){

        gde_enter_critical_section ();
        system_call ( 111, 
            (unsigned long)&message_buffer[0],
            (unsigned long)&message_buffer[0], 
            (unsigned long)&message_buffer[0] );
        gde_exit_critical_section();

        if ( message_buffer[1] != 0 )
        {
            Response = (int) dbProcedure ( 
                               (struct window_d *) message_buffer[0], 
                               (int)               message_buffer[1], 
                               (unsigned long)     message_buffer[2], 
                               (unsigned long)     message_buffer[3] );

            if (Response > 100)
            {
                printf ("Response=%d \n", Response );
                goto exit_dialogbox;
            }

            message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;
        }
    };


//
// Exit.
//

exit_dialogbox:

	//#debug
	printf ("Exiting dialog Box \n");

    return (int) Response;
}



/*
 **************************************************
 * dbProcedure:
 *     O procedimento padrão de dialog box. 
 */

unsigned long 
dbProcedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

    switch (msg)
    {

        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:
                    return (unsigned long) 101; 
                    break;

                default:
                    return (unsigned long) 0;
                    break; 
            };
            break;


        case MSG_SYSKEYDOWN: 
            switch (long1)
            {
                case VK_F1:
                    printf ("F1: YES\n");
                    return (unsigned long) 102;
                    break;

                case VK_F2:
                    printf ("F2: NO\n");
                    return (unsigned long) 101;
                    break;

                default:
                    return (unsigned long) 0;
                    break;
            };
            break;


        default:
            return (unsigned long) 0;
            break;
    };

    printf ("done\n");
    return (unsigned long) 0;
}



/*
 *******************************************************************
 * gde_create_window: 
 * 
 *     Cria uma janela com base em uma struct.
 *     Retorna o endereço da estrutura da janela criada. 
 *     Para que possa ser registrada na lista windowList[].
 *     Essa lista tambem fica em kgws no kernel.
 * 
 * Cria a janela dependendo do tipo:                              
 * =================================
 * 1 - POP-UP.
 * 2 - EDIT-BOX.
 * 3 - NORMAL ( bg + client area ).
 * 4 - NORMAL_EDIT ( bg + editbox).
 * 5 - MENUBAR.
 * 6 - TOOLBAR.
 * 7 - STATUSBAR.
 * 8 - TASKBAR.
 * 9 - ? 
 * CONTINUA ...
 *
 */

void *gde_create_window ( 
    unsigned long type,        //1, Tipo de janela (popup,normal,...)
    unsigned long status,      //2, Estado da janela (ativa ou nao)
    unsigned long view,        //3, (min, max ...)
    char *windowname,          //4, Título.                          
    unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
    unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
    unsigned long width,       //7, Largura da janela.
    unsigned long height,      //8, Altura da janela.
    struct window_d *pWindow,  //9, Endereço da estrutura da janela mãe.
    unsigned long onde,        //10, Ambiente.( Est� no desktop, barra, cliente ...)
    unsigned long clientcolor, //11, Cor da área de cliente
    unsigned long color )      //12, Color (bg) (para janela simples).
{ 

    struct window_d *Window;

	// Enviando tudo via argumento.
	// Esse método dá a possibilidade de enviarmos ainda 
	// mais argumentos. 
	// #importante: Isso está funcionado, Vamos fazer assim e 
	// não do jeito antigo.


	unsigned long message_buffer[12];
	message_buffer[0]  = (unsigned long) type;
	message_buffer[1]  = (unsigned long) status;
	message_buffer[2]  = (unsigned long) view;
	message_buffer[3]  = (unsigned long) windowname;
	message_buffer[4]  = (unsigned long) x;
	message_buffer[5]  = (unsigned long) y;
	message_buffer[6]  = (unsigned long) width;
	message_buffer[7]  = (unsigned long) height;
	message_buffer[8]  = (unsigned long) pWindow;
	message_buffer[9]  = (unsigned long) onde;
	message_buffer[10] = (unsigned long) clientcolor;
	message_buffer[11] = (unsigned long) color;


    // #bugbug
    // Now we need to use the window server to create windows.
    // maybe this function can call the window server clint side
    // functions.
    gde_debug_print ("gde_create_window: [DEPRECATED]\n");

    Window = (void *) system_call ( 
                          118 , 
                          (unsigned long) &message_buffer[0], 
                          (unsigned long) &message_buffer[0], 
                          (unsigned long) &message_buffer[0] );

    if ( (void *) Window == NULL )
    {
        gde_debug_print ("gde_create_window: fail\n");
        return NULL;  
    }


    // ??
    // #teste
    // Vamos enviar a mensagem MSG_CREATE para o procedimento de janela.
    // Assim ele pode terminar de pintar nessa mesma janela.


    return (void *) Window;    
}


/*
 *****************************
 * gde_register_window:
 *     Register Window. 
 */

int gde_register_window (struct window_d *window)
{
    if ( (void *) window == NULL ){
        gde_debug_print ("gde_register_window: fail\n");
        return 1;
    }else{
        return (int) system_call ( SYSTEMCALL_REGISTERWINDOW, 
                        (unsigned long) window, 
                        (unsigned long) window, 
                        (unsigned long) window);
    };

    //#todo: Maybe '-1'
    return 2;
}


/*
 *****************************
 * gde_close_window:
 *     Close Window. 
 */

int gde_close_window (struct window_d *window)
{

    gde_debug_print ("gde_close_window: [DEPRECATED]\n");
        
    if ( (void *) window == NULL ){
        gde_debug_print ("gde_close_window: fail\n");
        return (int) 1;
    }else{
        return (int) system_call ( SYSTEMCALL_CLOSEWINDOW, 
                         (unsigned long) window, 
                         (unsigned long) window, 
                         (unsigned long) window );
    };

    //#todo: Maybe '-1'
    return 2;
}


/*
 * gde_set_focus:
 *     Set Focus. 
 */

int gde_set_focus (struct window_d *window)
{

    if ( (void *) window == NULL ){
        gde_debug_print ("gde_set_focus: fail\n");
        return (int) 1;
    }else{
        return (int) system_call ( SYSTEMCALL_SETFOCUS, 
                        (unsigned long) window, 
                        (unsigned long) window, 
                        (unsigned long) window );
    };

    //#todo: Maybe '-1'
    return 2;
}


/*
 * gde_get_focus:
 *     Get Focus. 
 */

// ??

int gde_get_focus (void)
{
    return (int) system_call ( SYSTEMCALL_GETFOCUS, 0, 0, 0 );
}


/*
 ******************************
 * gde_kill_focus:
 *     Kill Focus. 
 */

// deprecated

int gde_kill_focus (struct window_d *window)
{

    if ( (void *) window == NULL ){
        gde_debug_print ("gde_kill_focus: fail\n");
        return (int) 1;
    }else{

        return (int) system_call ( SYSTEMCALL_KILLFOCUS, 
                         (unsigned long) window, 
                         (unsigned long) window, 
                         (unsigned long) window );
    };

    //#todo: Maybe '-1'
    return (int) 2;
}


/*
 * gde_set_active_window:
 *     Set Active Window.
 *     @todo: Esse retorno pode ser void??. 
 */

// deprecated.

int gde_set_active_window (struct window_d *window)
{
    if ( (void *) window == NULL ){
        gde_debug_print ("gde_set_active_window: fail\n");
        return (int) 1;
    }else{
        return (int) system_call ( SYSTEMCALL_SETACTIVEWINDOW, 
                         (unsigned long) window, 
                         (unsigned long) window, 
                         (unsigned long) window );
    };

    //#todo: Maybe '-1'
    return 2;
}


/*
 * gde_get_active_window:
 *     Get Active Window Id.
 */

// deprecated

int gde_get_active_window (void)
{
    return (int) system_call ( SYSTEMCALL_GETACTIVEWINDOW, 0, 0, 0 );
}


/*
 * gde_show_current_process_info:
 *     Mostra informações sobre o processo atual.
 */

	// #todo: 
	// Essa rotina deveria apenas pegar os valores via system call
	// e imprimir os valores obtidos usando rotinas em user mode.

void gde_show_current_process_info (void)
{
    system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
}


void 
gde_resize_window ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y )
{

    gramado_system_call ( 
        SYSTEMCALL_RESIZEWINDOW, (unsigned long) window, x, y );
}


/*
 * gde_redraw_window:
 */

//deprecated

void 
gde_redraw_window ( 
    struct window_d *window, 
    unsigned long flags )
{

    if ( (void*) window == NULL )
        return;

    gramado_system_call ( 
        SYSTEMCALL_REDRAWWINDOW, 
        (unsigned long) window, 
        (unsigned long) flags, 
        (unsigned long) flags );
}


void 
gde_replace_window ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y )
{
    if ( (void*) window == NULL )
        return;

    system_call ( 
        SYSTEMCALL_REPLACEWINDOW, (unsigned long) window, x, y );
}


void gde_maximize_window (struct window_d *window)
{

    if ( (void*) window == NULL )
        return;

    gramado_system_call ( 
        SYSTEMCALL_MAXIMIZEWINDOW, 
        (unsigned long) window, 
        (unsigned long) window, 
        (unsigned long) window);
}


void gde_minimize_window (struct window_d *window)
{

    if ( (void*) window == NULL )
        return;

    gramado_system_call ( 
        SYSTEMCALL_MINIMIZEWINDOW, 
        (unsigned long) window, 
        (unsigned long) window, 
        (unsigned long) window);
}



// Envia uma mensagem PAINT para o aplicativo atualizar 
// a área de trabalho.

void gde_update_window (struct window_d *window)
{

    if ( (void*) window == NULL )
        return;

    gramado_system_call ( 
        279, 
        (unsigned long) window, 
        (unsigned long) window, 
        (unsigned long) window );
}


void *gde_get_foregroung_window (void)
{
    system_call ( SYSTEMCALL_GETFOREGROUNDWINDOW, 0, 0, 0 );
}


void gde_set_foregroung_window (struct window_d *window)
{

    if ( (void*) window == NULL )
        return;

    system_call ( 
        SYSTEMCALL_SETFOREGROUNDWINDOW, 
        (unsigned long) window, 
        (unsigned long) window, 
        (unsigned long) window );
}


/*
 ************************
 * gde_exit:
 *     Torna zombie a thread atual.
 *     Mas o propósito é terminar sair do 
 *     programa, terminando o processo e
 *     liberar os recursos que o processo estava usando.
 */

void gde_exit (int exit_code)
{

    gde_debug_print ("gde_exit:\n");

    // #todo:
    // exit(exit_code);

    system_call ( 
        SYSTEMCALL_EXIT, 
        (unsigned long) exit_code, 
        (unsigned long) exit_code, 
        (unsigned long) exit_code );


    while (1){ asm ("pause"); };
}


/*
 *****************************************
 * kill:
 *
 */

void gde_kill (int exit_code)
{
    gde_debug_print ("gde_kill: [TODO]\n");
    gde_exit(exit_code);
}



/*
 ****************************
 * gde_dead_thread_collector:
 * 
 *     Aciona o coletor de threads zumbis.
 *     Procura em todos os slots por threads no estado ZOMBIE e 
 * fecha elas.
 *     @todo: Talvez essa rotina possa ser implemetada em user mode 
 * por um server, ficando à cargo do kernel apenas fazer a realocação 
 * dos recursos de destruição das estruturas. 
 */

// What a cool thing !

void gde_dead_thread_collector (void)
{
    system_call ( 
        SYSTEMCALL_DEAD_THREAD_COLLECTOR, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0 );
}


// Compare two strings.

int gde_strncmp (char *s1, char *s2, int len)
{
    int n = len;


	//if ( len < 0 )
		//return 3;


    while (n > 0)
    {
         n--;
        
        if (*s1 != *s2)
        { 
            return (int) 1; 
        }

        *s1++;
        *s2++;
    };

    if ( *s1 != '\0' || *s2 != '\0' )
    {
        return (int) 2;
    }

    return 0;
}


/*
 *************************************
 * gde_show_backbuffer:
 *     Refresh Screen.
 *     Passa o conteúdo do backbuffer para o lfb. 
 */

void gde_show_backbuffer (void)
{
    // #todo
    // trocar o nome dessa systemcall.
    // refresh screen será associado à refresh all windows.
    
    system_call ( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0 );
}





/*
 *************************
 * gde_reboot:
 *     Reboot the O.S and then reboot the machine. 
 */

	// #todo: 
	// Fazer outras chamadas para
	// as camadas de software de mais alto nível antes
	// de efetuar o reboot de hardware propriamente dito. 

void gde_reboot (void)
{
    gramado_system_call ( SYSTEMCALL_REBOOT, 0, 0, 0 );

    gde_debug_print ("gde_reboot: unexpected return\n");
    while (1){ asm("pause"); };
}


/*
 *******************************
 * gde_set_cursor: 
 *     Set cursor. 
 */

void gde_set_cursor ( unsigned long x, unsigned long y )
{
    gramado_system_call ( SYSTEMCALL_SETCURSOR, x, y, 0 );
}


// #todo
void gde_get_cursor ( unsigned long *x, unsigned long *y )
{
    gde_debug_print ("gde_get_cursor: [TODO]\n");
}



/*
 * gde_get_cursor_x:
 *     Get cursor x. 
 */
unsigned long gde_get_cursor_x (void)
{
    return (unsigned long) gramado_system_call ( 
                               SYSTEMCALL_GETCURSORX, 0, 0, 0 );
}

/*
 * gde_get_cursor_y:
 *     Get cursor y.
 */
unsigned long gde_get_cursor_y (void)
{
    return (unsigned long) gramado_system_call (
                               SYSTEMCALL_GETCURSORY, 0, 0, 0 );
}


/*
 * gde_get_client_area_rect:
 *     Get client area rect.
 */

void *gde_get_client_area_rect (void)
{
    return (void *) system_call ( SYSTEMCALL_GETCLIENTAREARECT, 0, 0, 0 );
}


/*
 * gde_set_client_area_rect:
 *     Enviar uma estrutura de retângulo criada em user mode para o kernel.
 */

void gde_set_client_area_rect (struct rect_d *r)
{
    system_call ( SYSTEMCALL_SETCLIENTAREARECT, 
        (unsigned long) r, (unsigned long) r, (unsigned long) r );
}


/*
 ***********************************
 * gde_create_process:
 *     Create a process.
 */

void *gde_create_process ( 
    char *name,
    unsigned long process_priority )
{

    gde_debug_print ("gde_create_process:\n");


    if ( (void*) name == NULL ){
        gde_debug_print ("gde_create_process: [ERROR] no name provided\n");
        return NULL;
    }

    if ( *name == 0 ){
        gde_debug_print ("gde_create_process: [ERROR] invalid name\n");
        return NULL;
    }

    //return (void *) system_call ( 
    //                    SYSTEMCALL_CREATEPROCESS, 
    //                    (unsigned long) name, 
    //                    (unsigned long) process_priority, 
    //                    (unsigned long) 0 );

    return (void *) sc82 ( 
                        SYSTEMCALL_CREATEPROCESS, 
                        (unsigned long) name, 
                        (unsigned long) process_priority, 
                        (unsigned long) 0 );
}


/*
 **************************
 * gde_create_thread:
 *     Create a thread.
 *     #todo: 
 *     Precisamos uma função que envie mais argumentos.
 *     Essa será uma rotina de baixo nível para pthreads.
 */

void *gde_create_thread ( 
    unsigned long init_eip, 
    unsigned long init_stack, 
    char *name )
{
    gde_debug_print ("gde_create_thread:\n");


    if (init_eip == 0){
        gde_debug_print ("gde_create_thread: [ERROR] init_eip\n");
        return NULL;
    }

    if (init_stack == 0){
        gde_debug_print ("gde_create_thread: [ERROR] init_stack\n");
        return NULL;
    }

    if ( (void*) name == NULL ){
        gde_debug_print ("gde_create_thread: [ERROR] no name provided\n");
        return NULL;
    }

    if ( *name == 0 ){
        gde_debug_print ("gde_create_thread: [ERROR] invalid name\n");
        return NULL;
    }

    //return (void *) system_call ( 
    //                    SYSTEMCALL_CREATETHREAD, 
    //                    init_eip, 
    //                    init_stack, 
    //                    (unsigned long) name );

    return (void *) sc82 ( 
                        SYSTEMCALL_CREATETHREAD, 
                        init_eip, 
                        init_stack, 
                        (unsigned long) name );
}


/*
 ****************************************************************
 * gde_start_thread:
 *     Coloca no estado standby para executar pela primeira vez
 */

void gde_start_thread (void *thread)
{

    if ( (void*) thread == NULL )
    {
        gde_debug_print ("gde_start_thread: [ERROR] thread pointer\n");
        return;
    }

    system_call ( SYSTEMCALL_STARTTHREAD, 
        (unsigned long) thread, 
        (unsigned long) thread, 
        (unsigned long) thread );
}


/*
 * apiFOpen:
 *     Carrega na memória um arquivo.
 *     Usa um serviço do kernel para carregar um arquivo na memória.
 *     Obs: Devemos passar um endereço válido, previamente alocado. 
 */

// #bugbug
// Cuidado estamos entrando na sessão crítica.
// O aplicativo pode desejar fazer o mesmo.

void *gde_fopen (const char *filename, const char *mode){
	
    void *Ret;


    gde_debug_print ("gde_fopen:\n");

    if ( (void*) filename == NULL )
    {
        gde_debug_print ("gde_fopen: [ERROR] no filename provided\n");
        return NULL;
    }

    Ret = (void *) system_call ( 
                       SYSTEMCALL_READ_FILE, 
                       (unsigned long) filename, 
                       (unsigned long) mode, 
                       0 );
    
    return (void *) Ret;
}


/*
 *************************************************************
 * gde_save_file:
 *     Salva um arquivo no diretório raiz do volume de boot.
 *     Obs: Talvez possamos ter mais argumentos.
 *     #bugbug: 
 *     Essa rotina seria mais fácil se todas as informações sobre
 * o arquivo fossem gerenciadas pelo kernel. Mas não é o que estamos 
 * fazendo agora.
 */
 
//file_size = size in sectors

int
gde_save_file ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )
{

    int Ret = 0;


	// Enviando tudo via argumento.
	// Esse método dá a possibilidade de enviarmos ainda 
	// mais argumentos. 
	// #importante: Isso está funcionado, Vamos fazer assim e 
	// não do jeito antigo.

    unsigned long message_buffer[12];
    message_buffer[0] = (unsigned long) file_name;
    message_buffer[1] = (unsigned long) file_size;
    message_buffer[2] = (unsigned long) size_in_bytes;
    message_buffer[3] = (unsigned long) file_address;
    message_buffer[4] = (unsigned long) flag;
    //message_buffer[5] = (unsigned long) x;
    //message_buffer[6] = (unsigned long) x;
    // ...

    if ( (void*) file_name == NULL )
    {
        gde_debug_print ("gde_save_file: [ERROR] no filename provided\n");
        return -1;
    }

    if ( (void*) file_address == NULL )
    {
        gde_debug_print ("gde_save_file: [ERROR] file_address\n");
        return -1;
    }

    gde_enter_critical_section();
    Ret = (int) gramado_system_call ( 
                    SYSTEMCALL_WRITE_FILE,
                    (unsigned long) &message_buffer[0], 
                    (unsigned long) &message_buffer[0],  
                    (unsigned long) &message_buffer[0] ); 
    gde_exit_critical_section();


    return (int) Ret;
}


//testando a rotina de salvar um arquivo.
//estamos usando a API.
	//
	// #importante:
	// N�o podemos chamar a API sem que todos os argumentos estejam corretos.
	//
	
	// #obs:
	// Vamos impor o limite de 4 setores por enquanto. 
	// 512*4 = 2048  (4 setores) 2KB
	// Se a quantidade de bytes for '0'. ???


int gde_test_save_file (char *file_name)
{
    int Ret=0;

    char *file_1_name;
    char file_1[] = "gde_test_save_file: Arquivo \n escrito \n em \n user mode. \n";
    
    unsigned long number_of_sectors = 0;
    size_t len = 0;
    


    printf ("gde_test_save_file: Saving a file ...\n");
    
    file_1_name = file_name;

    if ( (void*) file_name == NULL )
    {
        gde_debug_print ("gde_test_save_file: [ERROR] no filename provided\n");
        return -1;
    }


    // Lenght in bytes.
    
    len = (size_t) strlen (file_1);

    if (len <= 0){
        printf ("gde_test_save_file:  Fail. Empty file.\n");
        return (int) 1;
        //return (int) -1;
    }

    if (len > 2048){
        printf ("gde_test_save_file:  Limit Fail. The  file is too long.\n");
        return (int) 1;
        //return (int) -1;
    }

    //
    // Number os sectors.
    //

    number_of_sectors = (unsigned long) ( len / 512 );

    if ( len > 0 && len < 512 )
    {
        number_of_sectors = 1; 
    }

    if ( number_of_sectors == 0 )
    {
        printf ("gde_test_save_file:  Limit Fail. (0) sectors so save.\n");
        return (int) 1;
        //return (int) -1;
    }

	//limite de teste.
	//Se tivermos que salvar mais que 4 setores.
    if ( number_of_sectors > 4 )
    {
        printf ("gde_test_save_file:  Limit Fail. (%d) sectors so save.\n",
            number_of_sectors );
        return (int) 1;
        //return (int) -1;
    }

    // Save!

    Ret = (int) gde_save_file ( 
                    file_1_name,        // name 
                    number_of_sectors,  // number of sectors.
                    len,                // size in bytes
                    file_1,             // address
                    0x20 );             // flag ??


    //if (Ret == 0)
    //    printf ("gde_test_save_file: fail\n");


    printf ("gde_test_save_file: done\n");

    return (int) Ret;
}



int gde_create_empty_file ( char *file_name )
{
    int __ret = 0;


    if ( (void*) file_name == NULL )
    {
        gde_debug_print ("gde_create_empty_file: [ERROR] no filename provided\n");
        return -1;
    }
  
    
    gde_enter_critical_section();
    __ret = (int) gramado_system_call ( 
                      43, 
                      (unsigned long) file_name, 
                      0, 
                      0);
    gde_exit_critical_section();    
    
    return __ret;
}


// (fs)
int gde_create_empty_directory ( char *dir_name )
{
    int __ret=0;

    if ( (void*) dir_name == NULL )
    {
        gde_debug_print ("gde_create_empty_directory: [ERROR] no dir_name provided\n");
        return -1;
    }

    gde_enter_critical_section();
    
    __ret = (int) gramado_system_call ( 44, 
                      (unsigned long) dir_name, 0, 0);

    gde_exit_critical_section();    


    return (int) __ret;
}



// gde_down:
// Operação down em um semáforo indicado no argumento.

void gde_down (struct semaphore_d *s)
{
    int Status = 1;    //fail.


    // Semáforo inválido, 
    // Bloquear a thread, não adianta fazer a system call.
    // todo: Chamar rotina que bloqueia a thread.
    if ( (void *) s == NULL  ){

        printf ("gde_down: *fail");
        while (1){ asm ("pause"); };
        //return;
    }

tryAgain:
    
	//0 = deu certo, entrada liberada na sessão crítica.
    //1 = algo deu errado espere tentando novamente.

    Status = (int) system_call ( SYSTEMCALL_SEMAPHORE_DOWN, 
                       (unsigned long) s, 
                       (unsigned long) s, 
                       (unsigned long) s );

	// Podemos entrar na região crítica.

    if (Status == 0){
        return;
    }


	// Devemos esperar, monitorando a flag ou bloquando a thread.
	
    if (Status == 1)
    {
		// Opções:
		// + Bloqueamos a thread e quando ela acordar tentaremos novamente.
		// + Fazemos um loop monitorando a flag.
		
		//Opção 1.
		//Exemplo: apiBlockThread(...)
		
		//Opção 2.
		goto tryAgain;
    }

fail:
    goto tryAgain;
}


// gde_up:
// Operação up em um semáforo indicado no argumento.

void gde_up (struct semaphore_d *s)
{
    int Status = 1; 

       //Semáforo inválido, 
        //Bloquear a thread, não adianta fazer a system call.
        //@todo: Chamar rotina que bloqueia a thread.

    if ( (void *) s == NULL  )
    {
        printf ("gde_up: *fail");
        while (1){ asm ("pause"); }
    }


    //0 = deu certo, podemos asir da sessão crítica.
    //1 = algo deu errado, não conseguimos sair da sessão crítica.	

tryAgain:

    Status = (int) system_call ( SYSTEMCALL_SEMAPHORE_UP, 
                       (unsigned long) s, 
                       (unsigned long) s, 
                       (unsigned long) s );

	//Ok , podemos sair sa sessão crítica.
	if (Status == 0)
	{
		return;
	}

	//Deu errado a nossa tentativa d sair da sessão crítica.
	if (Status == 1)
	{
		//
		// Opções:
		// + Bloqueamos a thread e quando ela acordar tentaremos novamente.
		// + Fazemos um loop monitorando a flag.
		//
		
		//Opção 1.
		//Exemplo: apiBlockThread(...)
		
		//Opção 2.
		goto tryAgain;
	}

fail:
    goto tryAgain;
}


//P (Proberen) testar.
void gde_enter_critical_section (void)
{
    int S=0;

    // Pega o valor do spinlock rpincipal.
    while (1){

        S = (int) system_call ( 
                      SYSTEMCALL_GET_KERNELSEMAPHORE, 0, 0, 0 );
                      
		// Se deixou de ser 0 então posso entrar.
		// Se ainda for 0, continuo no while.
        if ( S == 1 ){ goto done; }
        
        //#wait
        // gramado_system_call (265,0,0,0); //yield thread.
        sc82(265,0,0,0);
    };

    //Nothing

done:
    //Muda para zero para que ninguém entre.
    system_call ( SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 0, 0, 0 );
    return;
}


//V (Verhogen)incrementar.
void gde_exit_critical_section (void)
{
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    system_call ( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0 );
}




// P (Proberen) testar.
void gde_p (void)
{
    gde_debug_print ("gde_p: [TODO]\n");
    //gde_enter_critical_section ();         
}

// V (Verhogen) incrementar.
void gde_v (void)
{
    gde_debug_print ("gde_v: [TODO]\n");
    //gde_exit_critical_section ();          
}


//
//Inicializa em 1 o semáforo do kernel para que 
//o primeiro possa usar.

void gde_initialize_critical_section (void)
{
    system_call ( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0 );
}


void gde_begin_paint(void)
{
    gde_enter_critical_section ();
}


void gde_end_paint(void)
{
    gde_exit_critical_section ();
}


/*
 *******************************************
 * gde_put_char:
 *     Imprime um caractere usando o cursor do sistema.
 *     #todo; falar mais sobre isso.
 */

void gde_put_char (int c)
{
    system_call ( SYSTEMCALL_SYS_PUTCHAR, c, c, c );
}



/*
 * gde_def_dialog:
 *     Defered dialog.
 *     Procedimento de janela adiado. 
 *     Usado pelos aplicativos ao fim dos seus procedimentos de janela.
 */

unsigned long 
gde_def_dialog ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{
    gde_debug_print ("gde_def_dialog: [TODO]\n");
    return (unsigned long) 1;
}


/*
 **********************************
 * gde_get_system_metrics:
 *     Obtem informações sobre dimensões e posicionamentos. 
 *     #importante
 */
 
unsigned long gde_get_system_metrics (int index)
{
    // #todo
    
    //if (index<0){
        //gde_debug_print ("gde_get_system_metrics: fail\n");
        //return 0;
    //}

    return (unsigned long) system_call ( 
                               SYSTEMCALL_GETSYSTEMMETRICS, 
                               (unsigned long) index, 
                               (unsigned long) index, 
                               (unsigned long) index );
}




/*
 // ??
//enviamos um ponteiro par ao kernel carregar elementos na estrutura.
void api_receive_message( struct api_receive_message_d *m );
void api_receive_message( struct api_receive_message_d *m )
{
	//Enviamos para o kernel o ponteiro da estrutura que desejamos que ele 
	//coloque os valores.
	//o kernel deve atualizar a flag dizendo que tem alguma mensagems na estrutura.
    system_call( SYSTEMCALL_138, (unsigned long) m, (unsigned long) m, (unsigned long) m );
				 
};
*/



/*
 *******************************
 * gde_dialog:
 *     Diálogo de yes ou no. 
 */

// #??
// Ninguem esta usando essa rotina no momento. hahaha
// precisamos testar rotinas de input.

int gde_dialog ( const char *string )
{
    int Status = 1; // Yes!
    int ch = 0;


    //if ( (void *) string == NULL ){ return -1; }   

    printf (string);

    //
    // == loop =====================================
    //

    while (1){

        // #todo:
        // Check this input method.
        // It can be useful for some other aplications running
        // with no window server.
        
        ch = (int) gde_getchar();

        if ( ch != -1 )
        {
            switch (ch)
            {
                case VK_RETURN:  return (int) Status;  break;

			    case 'Y': case 'y':
				    printf ("Yes\n");
			        Status = 1;
				    break;
				   
			    case 'N': case 'n':
			        printf ("No\n");
					Status = 0;
				    break;

				//default:
				//    break;
		    };		   
		};

        // ?? rever isso.
        asm ("pause");
    };

    return (int) Status;
}



/*
 ******************************** 
 * gde_getchar:
 *     Metodo alternativo de pegar input.
 *     #todo: Checar.
 */

// #todo
// Descrever o método usado por essa rotina.
// O que pegamos aqui?
// Como pegamos?

int gde_getchar (void)
{
    return (int) gramado_system_call ( 137, 0, 0, 0 );
}



/*
 ************************************
 * gde_display_bmp:
 *     Mostra na tela uma imagem bmp carregada na memória.
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *     @todo: deletar w h 
 *
 *	// @todo: Criar defines para esses deslocamentos.
 */

// #atenção
// Me parece que essa rotina funcinna bem,
// o problema é a rotina que carrega o arquivo.

static int nibble_count_16colors = 0;
 
int 
gde_display_bmp ( 
    char *address, 
    unsigned long x, 
    unsigned long y )
{
    int i, j, base, offset;

    unsigned long left, top, bottom;

    unsigned long color, color2;
    unsigned long pal_address;

    unsigned long Width;
    unsigned long Height;

    unsigned long xLimit, yLimit;

    struct bmp_header_d *bh;
    struct bmp_infoheader_d *bi;

	// Endereço base do BMP que foi carregado na memória
    unsigned char *bmp = (unsigned char *) address;
	
	// Variável para salvar rgba.
    unsigned char *c  = (unsigned char *) &color;
    unsigned char *c2 = (unsigned char *) &color2;

    unsigned long *palette = (unsigned long *) (address + 0x36);
    unsigned char *palette_index = (unsigned char *) &pal_address;	


	// Limits
	
	xLimit = 800;
	yLimit = 600;
	
	
	//@todo: Refazer isso
	if ( x > xLimit || y > yLimit )
	{ 
        return (int) 1; 
	}
	

	// @todo:
	// Testar validade do endereço.
	
	
	if ( address == 0 )
	{
		//goto fail;
	}
	
	
	//
	// struct for Info header
	//
	
	bh = (struct bmp_header_d *) malloc ( sizeof(struct bmp_header_d) );
	
    if ( (void *) bh == NULL )
	{
		//goto fail;
	}	
	

	//
	// Signature.
	//
	
    unsigned short sig;
	
	sig = *( unsigned short * ) &bmp[0];
	
	bh->bmpType = sig;
	
	
	//
	// Size. ( 2 bytes )
	//
	
	unsigned short Size = *( unsigned short* ) &bmp[2];
	
	bh->bmpSize = Size;
	
	
	//
	// struct for Info header
	//
	
	//Windows bmp.
	bi = (struct bmp_infoheader_d *) malloc ( sizeof(struct bmp_infoheader_d) );
	
    if ( (void *) bi == NULL )
    {
		//goto fail;
    }	

	//The size of this header.
	bi->bmpSize = *( unsigned long * ) &bmp[14];
	
	// Width and height.
    Width  = *( unsigned long * ) &bmp[18];
    Height = *( unsigned long * ) &bmp[22];
	
	//@todo: checar validade da altura e da largura encontrada.
	
	// Salvar.
	bi->bmpWidth  = (unsigned long) Width;
	bi->bmpHeight = (unsigned long) Height;
	
	
	/* Number of bits per pixel */
	//1, 4, 8, 16, 24 and 32.
	bi->bmpBitCount = *( unsigned short * ) &bmp[28];
	
	// Único suportado ainda.
	if ( bi->bmpBitCount != 24 )
	{
		//fail
	}
	
	
	// 0 = Nenhuma compressão.
	if ( bi->bmpCompression != 0 )
	{
		//fail
	}
	
	
	//
	// Draw !
	//
	
	left = x;    
	top = y; 
	
	
	//bottom = top + height;
	bottom = (top + bi->bmpHeight );

	// Início da área de dados do BMP.
	
	//#importante:
	//a base é diferente para os tipos.
	 

	switch (bi->bmpBitCount){
		
		//case 1:
		//    base = (0x36 + 0x40);
		//    break;
		    
		//case 2:
		//    base = (0x36 + 0x40);
		//    break;
			
		case 4:
		    //4bytes pra cada cor, 16 cores, 64bytes.
		    base = (0x36 + 0x40);
		    break; 
			
		case 8:
		    //4bytes pra cada cor, 256 cores, 1024bytes.
		    base = (0x36 + 0x400);
		    break; 
			
		default:
		    base = 0x36;
			break;
	};	
	

//1 - 1 bpp (Mono)
//4 - 4 bpp (Indexed)
//8 - 8 bpp (Indexed) bbgggrrr
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24 - 24 bpp (True color)
//32 - 32 bpp (True color, RGB)
//320 - 32 bpp (True color, RGBA)	


  
	// ## ABGR8888 ##
	// Little-endian
	// pegando os caracteres
	//
	// 0 = A (MSByte)(left byte) 
	// 1 = B 
	// 2 = G 
	// 3 = R
	//
	// Output long = 0xRRGGBBAA
    //	
	// Exemplo: gramado GUI
    //#define COLOR_RED   0xFF000000 
    //#define COLOR_GREEN 0x00FF0000
    //#define COLOR_BLUE  0x0000FF00

	
	for ( i=0; i < bi->bmpHeight; i++ )	
	{		
		for ( j=0; j < bi->bmpWidth; j++ )	
		{	
	        // 16 cores
            // Um pixel por nibble.
	        if ( bi->bmpBitCount == 4 )
	        {				
				offset = base;
							    
				palette_index[0] = bmp[offset];
												
                //segundo nibble.
				if( nibble_count_16colors == 2222 )
				{
					palette_index[0] = ( palette_index[0] & 0x0F);  
					color = (unsigned long) palette[  palette_index[0]  ];
					
					nibble_count_16colors = 0;
					base = base + 1;
					
				//primeiro nibble.	
				}else{

			        palette_index[0] =  ( (  palette_index[0] >> 4 ) & 0x0F);
					color = (unsigned long) palette[  palette_index[0] ];
				    
					nibble_count_16colors = 2222;
					base = base;
				};
	        };	

			// 256 cores
			// Próximo pixel para 8bpp
	        if( bi->bmpBitCount == 8 )
	        {   
				offset = base;
				color = (unsigned long) palette[  bmp[offset] ];
				
				base = base + 1;     
	        };			
			
			// 16bpp high color BMP
			// Próximo pixel para 16bpp
			// apenas 565 por enquanto.  
	        if ( bi->bmpBitCount == 16 )
	        {

			    //565
                //if(565 )
                //{
				    offset = base;					
					
				    //A
			        c[0] = 0;	

			        //b				
			        c[1] = bmp[offset];
			        c[1] = (c[1] & 0xF8);  // '1111 1000' 0000 0000  
				
				    //g
			        c2[0] = bmp[offset];
			        c2[0] = c2[0] &  0x07;    // '0000 0111' 0000 0000 
			        c2[1] = bmp[offset+1];
			        c2[1] = c2[1] &  0xE0;    //  0000 0000 '1110 0000' 
					c[2] = ( c2[0] | c2[1]  );
					
			        //r
			        c[3] = bmp[offset+1];
			        c[3] = c[3] & 0x1F;     // 0000 0000 '0001 1111' 
		        
				    base = base + 2;    
				//};
	        };
			

			// Próximo pixel para 24bpp
	        if ( bi->bmpBitCount == 24 )
	        {
				offset = base;
			    
			    c[0] = 0; //A
				
				c[1] = bmp[offset];
			    
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];

		        base = base + 3;    
	        };
			
			
			// Próximo pixel para 32bpp
	        if ( bi->bmpBitCount == 32 )
	        { 
				//A
				//offset = base+3;
			    c[0] = 0;
				
				offset = base;
			    c[1] = bmp[offset];
			
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
				
		        base = base + 4;    
	        };
			
			//todo: o window server tem rotina pra pintar no backbuffer
			//que está em ring3.
			system_call ( SYSTEMCALL_BUFFER_PUTPIXEL, (unsigned long) color, 
				(unsigned long) left, (unsigned long) bottom );
			
			// Próximo pixel.
			left++; 
		};
		
		// Vamos para a linha anterior.
		bottom = bottom-1;
		
		// Reiniciamos o x.
		left = x;    
	};	
	
	// ## test palette 
	//int p;
	
	//if(bi->bmpBitCount == 8 )
	//{
	//    printf("\n");
	//    for( p=0; p<16; ++p )
	//    {
	//	   printf("%x\n",palette[p]);
	//    }
	//    printf("\n");
	//};
	
fail:	
    //printf("fail");	
	
done:
	
	//Debug
	//printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
	
	return 0;
}



/*
 **********************************************************
 * gde_send_message_to_process:
 *     Envia uma mensagem para a thread de controle de um dado processo.
 *     Dado o PID.
 */

// #obs
// Dá pra criar uma função semelhante, que use estrutura ao invés 
// de buffer.

int
gde_send_message_to_process ( 
    int pid, 
    struct window_d *window, 
    int message,
    unsigned long long1,
    unsigned long long2 )
{

    unsigned long message_buffer[5];


    if ( pid<0 ){
        gde_debug_print ("gde_send_message_to_process: fail\n");
        return -1;
    }

    message_buffer[0] = (unsigned long) window;
    message_buffer[1] = (unsigned long) message;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;
    //...

    return (int) system_call ( 112 , 
                    (unsigned long) &message_buffer[0], 
                    (unsigned long) pid, 
                    (unsigned long) pid );
}


/*
 *************************************
 * gde_send_message_to_thread:
 *     Envia uma mensagem para uma thread.
 */

int 
gde_send_message_to_thread ( 
    int tid, 
    struct window_d *window, 
    int message,
    unsigned long long1,
    unsigned long long2 )
{

    unsigned long message_buffer[5];

    if (tid < 0){
        gde_debug_print ("gde_send_message_to_thread: fail\n");
        return -1;
    }


    message_buffer[0] = (unsigned long) window;
    message_buffer[1] = (unsigned long) message;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2;
    //...


    return (int) system_call ( 117 , 
                     (unsigned long) &message_buffer[0], 
                     (unsigned long) tid, 
                     (unsigned long) tid );
}



/*
 **********
 * gde_send_message:
 *     Envia uma mensagem para a thread atual.
 *     Isso funcionou.
 */

unsigned long 
gde_send_message ( 
    struct window_d *window, 
    int message,
    unsigned long long1,
    unsigned long long2 )
{

    unsigned long message_buffer[5];
    
    message_buffer[0] = (unsigned long) window;
    message_buffer[1] = (unsigned long) message;
    message_buffer[2] = (unsigned long) long1;
    message_buffer[3] = (unsigned long) long2; 

    return (unsigned long) system_call ( 114 , 
                               (unsigned long) &message_buffer[0], 
                               (unsigned long) &message_buffer[0], 
                               (unsigned long) &message_buffer[0] );
}


// Draw text.
// deprecated.
int 
gde_draw_text ( 
    struct window_d *window, 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    char *string )
{

    unsigned long msg[8];
    
    msg[0] = (unsigned long) window;
    msg[1] = (unsigned long) x;
    msg[2] = (unsigned long) y;
    msg[3] = (unsigned long) color;
    msg[4] = (unsigned long) string;
    // ...

    return (int) system_call ( SYSTEMCALL_DRAWTEXT, 
                    (unsigned long) &msg[0], 
                    (unsigned long) &msg[0], 
                    (unsigned long) &msg[0] );
}


// ?
struct window_d *gde_get_ws_screen_window (void)
{
    return (struct window_d *) system_call ( 146 , 0, 0, 0 );
}

// ?
struct window_d *gde_get_ws_main_window (void)
{
    return (struct window_d *) system_call ( 147 , 0, 0, 0 );
}



/*
 ****************************** 
 * gde_create_timer:
 *     
 *     Create timer.
 */

// IN: pid, ms, type

struct timer_d *gde_create_timer ( 
    int pid, 
    unsigned long ms, 
    int type )
{
    gde_debug_print ("gde_create_timer:\n");

    if ( pid<0 ){
        gde_debug_print ("gde_create_timer: [FAIL] pid \n");
        return -1;
    }

    return (struct timer_d *) gramado_system_call ( 
                                  222, 
                                  (unsigned long) pid, 
                                  (unsigned long) ms, 
                                  (unsigned long) type );
}


// pega informações varidas sobre o sys time.
unsigned long gde_get_systime_info (int n){

    return (unsigned long) gramado_system_call ( 223, 
                               (unsigned long) n, 
                               (unsigned long) n, 
                               (unsigned long) n );
}


/*
 * gde_show_window 
 * 
 */
 
//deprecated
//mostra uma janela na tela. backbuffer ---> frontbuffer

void gde_show_window (struct window_d *window){

    gramado_system_call ( 24, 
        (unsigned long) window, 
        (unsigned long) window, 
        (unsigned long) window );
}



/* 
 * gde_start_terminal:
 *     
 */

// 'Clona' e executa o noraterm como processo filho. 
// registra o terminal noraterm como terminal atual.
// pega o pid do terminal atual
// manda uma mensagem pedindo para o terminal dizer hello.

// #bugbug
// Deprecated.
 
int gde_start_terminal (void){

    int PID = -1;
    
    
    gde_debug_print("gde_start_terminal: [DEPRECATED]\n");

    // Clona e executa o noraterm como processo filho. 

    PID = (int) system_call ( 900, (unsigned long) "noraterm.bin", 0, 0 );

	// Exibe o PID para debug.
	//printf ("PID = %d \n", PID);

    //registra o terminal como terminal atual.
    system_call ( 1003, PID, 0, 0 ); 

	//invalida a variável.
    PID = -1;
		
	//pega o pid do terminal atual
    PID = (int) system_call ( 1004, 0, 0, 0 ); 

    if ( PID <= 0 ){
        printf ("PID fail. We can't send the message\n");
        return -1;
    }


	//manda uma mensagem pedindo para o terminal dizer hello.
	//__SendMessageToProcess ( PID, NULL, MSG_TERMINALCOMMAND, 2001, 2001 );

	return (int) PID;
}


int 
gde_update_statusbar ( 
    struct window_d *window, 
    unsigned char *string1, 
    unsigned char *string2 )
{
    return (int) system_call ( 300, 
                     (unsigned long) window, 
                     (unsigned long) string1, 
                     (unsigned long) string2 );
}


// Usada para obter o pid de alguns drivers e servidores
// do sistema. Aqueles servidores que só podem ter um do tipo 
// rodando ao mesmo tempo.
int gde_get_pid (int index){

    if ( index < 0 ){
        return (int) -1;
    }

    // #todo
    // Lá no kernel tem que checar os limites.

    return gramado_system_call ( 9999, index, index, index );
}


struct window_d *gde_get_screen_window (void)
{
    return (struct window_d *) gramado_system_call ( 955, 0, 0, 0 );
}


struct window_d *gde_get_background_window (void)
{
    return (struct window_d *) gramado_system_call ( 956, 0, 0, 0 );
}


struct window_d *gde_get_main_window (void)
{
    return (struct window_d *) gramado_system_call ( 957, 0, 0, 0 );
}



// Pega o nome do processo dado o pid.
// OUT: name len ?
int gde_getprocessname (int pid, char *name, size_t len){

    int __len_ret = 0;


    //HOST_NAME_MAX
    if ( len < 0 || len > 64 ){
        printf ("gde_getprocessname: len\n");
        return -1;
    }


    // Coloca no buffer interno
    __len_ret = (int) gramado_system_call ( 882, 
                        (unsigned long) pid,
                        (unsigned long) name,
                        (unsigned long) name );

    // HOST_NAME_MAX
    // Isso nao significa erro de medida do nome, 
    // pois se chamarmos com um pid invalido
    // vai retornar -1.

    if ( __len_ret < 0 || __len_ret > 64 ) 
    {
        debug_print ("gde_getprocessname: __len_ret \n");
        return -1;
    }

    // Se o nome do processo eh maior que o buffer em ring3.
    if ( __len_ret > len ){ __len_ret = len; }

    return __len_ret;
}


//pega o nome do thread dado o tid.
int gde_getthreadname (int tid, char *name, size_t len){

    int __len_ret = 0;


    //HOST_NAME_MAX
    if ( len < 0 || len > 64 ){
        printf ("gde_getthreadname: len\n");
        return -1;
    }


    //coloca no buffer interno
    __len_ret = (int) gramado_system_call ( 883, 
                        (unsigned long) tid,
                        (unsigned long) name,
                        (unsigned long) name );

    //HOST_NAME_MAX
    if ( __len_ret < 0 || __len_ret > 64 ){
        printf ("gde_getthreadname: __len_ret\n");
        return -1;
    }

    if ( __len_ret > len )
    {
        __len_ret = len;
    }


    return 0;
}



unsigned long gde_get_process_stats (int pid, int index)
{
    return (unsigned long) system_call ( 880, 
                               (unsigned long) pid, 
                               (unsigned long) index, 
                               (unsigned long) index );
}

unsigned long gde_get_thread_stats (int tid, int index){

    return (unsigned long) system_call ( 881, 
                               (unsigned long) tid, 
                               (unsigned long) index, 
                               (unsigned long) index );
}


/*
 **********************************************
 * gde_debug_print:
 *     Envia uma string para a porta serial COM1.
 */

void gde_debug_print (char *string)
{
    // #todo
    // Check pointer validation.
    
    gramado_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}


/*
 **************************************
 * gde_clone_and_execute:
 *     Clone and execute a process.
 */

int gde_clone_and_execute ( char *name )
{
    if ( (void *) name == NULL ){
        printf ("gde_clone_and_execute: [TEST] Name pointer\n");
        return -1;
    }

    if ( *name == 0 ){
        printf ("gde_clone_and_execute: [TEST] Invalid name\n");
        return -1;
    }

    //return (int) gramado_system_call ( 900, (unsigned long) name, 0, 0 );
    return (int) sc82 ( 900, (unsigned long) name, 0, 0 );
}


// Enviamos para o kernel um buffer que está no app.
// Associando esse buffer ao pid do app.
// Desse modo o driver de rede pode colocar conteúdo no buffer
// do aplicativo que está ouvindo determinada porta.
// Depois mandar uma mensagem para o app dizendo, pode ler seu buffer.
//

// O kernel poderá guardar esse ponteiro para o net_buffer
// na estrutura do processo cujo pid foi passado por essa função.
// Também pode salvar o tamanho do buffer pou ele pode ter
// tamanho padrçao. 4KB.

// IN: pid, ponteiro para o buffer, comprimento do buffer;
// OUT: 0=Ok -1=fail
int gde_setup_net_buffer (int pid, char *buffer, size_t len){

    int len_ret = 0;
    
    len_ret = (int) gramado_system_call ( 550, 
                        (unsigned long) pid,
                        (unsigned long) buffer,
                        (unsigned long) buffer );

     return len_ret;
}


// cria um novo process, uma thread e carrega a imagem.
int 
execute_new_process ( 
    const char *filename, 
    char *argv[], 
    char *envp[] )
{
    return (int) gramado_system_call ( 168, 
                     (unsigned long) filename,    // Nome
                     (unsigned long) argv,        // arg (endereço da linha de comando)
                     (unsigned long) envp );      // env
}



// Get an event from the thread's event queue.
// That old 'get system message'
// Using a buffer
int libcore_get_event (void)
{
    // clear
    LibCoreEventBuffer[0] = 0;
    LibCoreEventBuffer[1] = 0;
    LibCoreEventBuffer[2] = 0;
    LibCoreEventBuffer[3] = 0;
    //...

    // Get event from the thread's event queue.
    gde_enter_critical_section(); 
    gramado_system_call ( 111,
        (unsigned long) &LibCoreEventBuffer[0],
        (unsigned long) &LibCoreEventBuffer[0],
        (unsigned long) &LibCoreEventBuffer[0] );
    gde_exit_critical_section(); 

    // Check if it is a valid event.

    // No, we do not have an event. Yield.
    if ( LibCoreEventBuffer[1] == 0 )
    {
        //gramado_system_call (265,0,0,0); 
        //debug_print("*\n");
        sc82 (265,0,0,0);
        
        // clear
        LibCoreEventBuffer[0] = 0;
        LibCoreEventBuffer[1] = 0;
        LibCoreEventBuffer[2] = 0;
        LibCoreEventBuffer[3] = 0;
        //...

        return FALSE; 
    }

    // Yes, we have an event.
    return TRUE;
}


//
// End.
//

