/*
 * File: terminal.c 
 * 
 *     Terminal interface.
 *     Interface to handle all the virtual terminal management.
 *     See: chardev/tty/ in 2io/
 */


//   This is the kserver part for the virtual terminal support.
//   Initialization routines needs to call this file to setup 
//   the virtual terminal functionalities.

#include <kernel.h>


extern unsigned long SavedX;
extern unsigned long SavedY;



int 
terminal_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    if ( fd<0 ){
        debug_print("terminal_ioctl:\n");
        return -1;
    }
    
    // ?? more
    return (int) tty_ioctl(fd,request,arg);
}


/*
 ****************************************************
 * systemSetTerminalWindow:
 * 
 * #importante
 * Configura qual vai ser a janela do terminal virtual.
 * Configurar as variáveis de terminal presentes dentro da janela, pois cada 
 * janela pode ter um terminal. 
 *
 * #importante:
 * >>>> Essa e' a janela que o kernel precisa efetuar o refresh do stdout 
 * associado a ela. Dessa forma, as rotinas da libc precisa apenas escrever
 * em stdout, ficando por conta do kernel efetuar o refresh do arquivo 
 * para dentro da janela. 
 * >>>> Mas esse arquivo deve conter as caracteri'ticas de cada caractere. 
 * 
 */


// #importante
// Configuramos qual será a janela do terminal atual.
// +poderíamos configurar a estrutura do terminal atual.
// +podemos usar as variáveis globais como representação
// do terminal atual.
// >>> Avaliaremos isso. Provavelmente teremos que usar a
// estrutura do terminal atual para efetuatmos qualquer tipo 
// de pintura.
// O sistema poderá ter 8 terminais virtuais tty e 8
// usuários diferentes poderão logar ao mesmo tempo.


// #bugbug
// There is something wrong here.
// The purpose of this routine is to setup the
// window for the virtual terminal, not
// for the virtual console.
// So, we need two routines, 
// one for the virtual consoles and
// another one for the virtual terminals.
// Both will use the tty structure,
// but the console is not able to use
// all the tty features (there is a bug)


// #todo
// Podemos melhorar esse nome.
//int terminal_set_vt_window( int console_number, struct window_d *window ){

void systemSetTerminalWindow ( struct window_d *window )
{

    //#todo
    /*
    unsigned long deviceWidth=0; 
    unsigned long deviceHeight=0; 
    deviceWidth  = systemGetSystemMetrics(1);
    deviceHeight = systemGetSystemMetrics(2);
    if ( deviceWidth == 0 || deviceHeight == 0 )
    {
        panic("systemSetTerminalWindow: deviceWidth deviceHeight\n");
    }
    */


	// Obs: ?? Como faremos para pintar dentro da janela do terminal.
	// Obs: a rotina de configuração do terminal deverá ajustar as margens 
	// usadas pela rotina de impressão de caracteres.

	// obs:
	// essa modificação de margens obriga o aplicativo a 
	// configurar o terminal somente na hora que for usa-lo,
	// para não correr o risco de imprimir no lugar errado.

//check_window:

    if ( (void *) window == NULL )
        return;

    if ( window->used != 1 || window->magic != 1234 )
        return;
		
       
    // #bugbug
	// De que janela estamos falando, de qual dos terminais virtuais?
	// Pode ser da que esta em primeiro plano.
	// Configurando a variável global que diz qual é 
	// o ID da janela que tem o terminal virtual ativo.

    terminal_window = (int) window->id;

	//configura o status do terminal dentro da janela
	//validade e reusabilidade das variáveis de terminal 
	//dentro da estrutura de janela.

    window->terminal_used = 1;
    window->terminal_magic = 1234; 

	//tab
	//número da tab.
	//indica qual tab o terminal está usando.
	//@todo:
	// Criar uma forma de contar as tabs de terminal 
	// dentro do gerenciador de terminais.
    window->terminal_tab = 0; 


	//rect
	//configura por último
    //window->terminal_left = 0;
    //window->terminal_top = 0;
    //window->terminal_width = 0;
    //window->terminal_height = 0;
	//..

    window->terminal_left   = window->left;
    window->terminal_top    = window->top;
    window->terminal_width  = window->width;
    window->terminal_height = window->height;


    // #bugbug
    // Qual eh o current no momento dessa inicializaçao
    // so temos 4.
    // eles ja estao inicializados.
    // #todo: podeia ter uma flag que diz se ja inicializamos os consoles.
 
 
// #bugbug
// There is something wrong here.
// The purpose of this routine is to setup the
// window for the virtual terminal, not
// for the virtual console.
// So, we need two routines, 
// one for the virtual consoles and
// another one for the virtual terminals.
// Both will use the tty structure,
// but the console is not able to use
// all the tty features (there is a bug)


    if (fg_console < 0 || fg_console >= CONSOLE_COUNT_MAX )
    {
        panic("systemSetTerminalWindow: fg_console\n");
    }

    //position
    vc_cons[fg_console].tty->cursor_x = (window->left / 8);
    vc_cons[fg_console].tty->cursor_y = (window->top  / 8);

    //margin
    vc_cons[fg_console].tty->cursor_left = vc_cons[fg_console].tty->cursor_x; 
    vc_cons[fg_console].tty->cursor_top  = vc_cons[fg_console].tty->cursor_y;

    //limits
    vc_cons[fg_console].tty->cursor_right  = 0+(SavedX/8) -1;  // (screen width / char width)
    vc_cons[fg_console].tty->cursor_bottom = 0+(SavedY/8) -1;  // (screen height/ char height)


	//
	// rcClient  (retângulo)
    //
	
	// test:
	// tentando ajustar as margens para as rotinas de impressão.
	// para que as rotinas de impressão imprimam dentro das 
	// dimensões do terminal. 
	// obs: @todo: Essas margens deverão ser reconfiguradas 
	// quando o terminal é fechado.

	// #bugbug:
	// #importante		
	// Esse ajuste pode significar problemas.


    /*
    if ( (void *) window->rcClient !=  NULL )
    {
		//x inicial
        if ( window->rcClient->left > 0 )
        {
            g_cursor_x = (window->rcClient->left/8 ); 
            g_cursor_left = g_cursor_x;

            window->terminal_left = window->rcClient->left; 
        }

		//y inicial
        if ( window->rcClient->top > 0 )
        {
            g_cursor_y = (window->rcClient->top/8 ); 
            g_cursor_top = g_cursor_y;

            window->terminal_top = window->rcClient->top; 
        }
    }
    */

    /*
    if ( window->rcClient->width > 0 )
    {
        window->terminal_width = window->rcClient->width; 
    }

    if ( window->rcClient->height > 0 )
    {
        window->terminal_height = window->rcClient->height;
    }

    if ( window->rcClient->right > 0 )
    {
	    // margem direita dada em linhas
        g_cursor_right = window->rcClient->right /8;

        window->terminal_right = window->rcClient->right; 
    }

    if ( window->rcClient->bottom > 0 )
    {
	    // margem inferior dada em linhas
        g_cursor_bottom = window->rcClient->bottom /8;

        window->terminal_bottom = window->rcClient->bottom; 
    }
    */

    // #bugbug
    // This is very ugly, i know!
    // We need to fix it.

    if ( vc_cons[fg_console].tty->cursor_left > 800 )
    {
        vc_cons[fg_console].tty->cursor_left = 795;
    }

    if ( vc_cons[fg_console].tty->cursor_top > 600 )
    {
         vc_cons[fg_console].tty->cursor_top = 595;
    }

    if ( vc_cons[fg_console].tty->cursor_right > 800 )
    {
         vc_cons[fg_console].tty->cursor_right = 795;
    }

    if ( vc_cons[fg_console].tty->cursor_bottom > 600 )
    {
         vc_cons[fg_console].tty->cursor_bottom = 595;
    }


    // Cursor

    vc_cons[fg_console].tty->cursor_width_in_pixels  = 8;
    vc_cons[fg_console].tty->cursor_height_in_pixels = 8;
    vc_cons[fg_console].tty->cursor_color  = COLOR_WHITE;

    // ...
}



// o ID da janela que tem o terminal virtual ativo.
// isso deve ir para kgws
// int terminal_get_vt_window_id(int console_number)

int systemGetTerminalWindow (void)
{
    return (int) terminal_window;
}


//@todo: precisamos de argumentos.
//configuramos o retângulo do terminal virtual corrente.. 
void 
systemSetTerminalRectangle ( 
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height )
{
	// current terminal
}


// initialize terminal support.

int terminalInit (void)
{
    // ??
    // seleciona o primeiro terminal

    current_terminal = 0;

    // ...
    
    return 0;
}



