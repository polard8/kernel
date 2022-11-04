/*
 * File: ws/sbar.c
 *
 * Descrição:
 *     Cria uma status bar em uma janela.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2017 - Small changes.
 *     //...
 */

 
#include <kernel.h>




int 
UpdateStatusBar ( 
    struct window_d *window, 
    unsigned char *string1, 
    unsigned char *string2 )
{

    struct window_d *w;

	// parent
    if ( (void *) window == NULL )
    {
		printf ("window\n");
		refresh_screen();
	    return -1;

	}else{
		
	    if ( window->used != 1 || window->magic != 1234 ){
		    printf ("window validation\n");
		    refresh_screen();			
			return -1;
		}	
		
	    // the status bar
	    w = window->statusbar;
	    	
	    if ( (void *) w == NULL ){
		    printf ("w\n");
		    refresh_screen();
		    return -1;	
		}else{
			
	        if ( w->used != 1 || w->magic != 1234 ){
		        printf ("w validation\n");
		        refresh_screen();
			    return -1;
		    }	
			
			//clean.
		    drawDataRectangle ( w->left, w->top, 
			    w->width, w->height, w->bg_color ); 
			
			//write.
            draw_text ( w, 0* ( w->width/2), 1* (w->height/3), 
                COLOR_WINDOWTEXT, string1 );

            draw_text ( w, 1* (w->width/2), 1* (w->height/3), 
                COLOR_WINDOWTEXT, string2 );
		
		
		    show_window_rect ( (struct window_d *) w );
		};
	};

    return 0;
}


/*
 ************************************************
 * StatusBar:
 *
 * Desenha uma statusbar.
 * O tamanho da statusbar deve ser to tamanho da largura da janela. 
 * A scrollbar não deve invadir o espaço da statusbar.
 */
 
// #bugbug
// Essa rotina não é usada por CreateWindow. 

struct window_d *StatusBar ( 
    struct window_d *window, 
    unsigned char *string1, 
    unsigned char *string2 )
{

	int desktopID;
	unsigned long StatusBarColor;

	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;

	// Parent window.
	struct window_d *pWnd = (struct window_d *) window;

    // A janela da status bar.
    struct window_d *hWnd;



	// Parent window.

    if ( (void *) pWnd == NULL ){
        printf ("StatusBar: pWnd\n");
        goto fail;

    }else{

		// #obs:
		// #Aviso: Estamos retornando se não existir área de cliente.
	    // A Statusbar é um elemento dentro da janela.
	    // Não podemos considerar as bordas e a barra de títulos.
	    
		if ( (void *) pWnd->rcClient == NULL ){
			printf ("StatusBar: rcClient\n");
		    goto fail;
	    }

		// validation.
		
	    if ( pWnd->rcClient->used != 1 || 
	         pWnd->rcClient->magic != 1234 )
	    {
			printf ("StatusBar: validation\n");
		    goto fail;
	    }		
		
	    // Set Up Sizes.
	    // Começa 32pixels antes do fim.
	    // Mesma largura da janela.
	    
		x = (unsigned long) pWnd->rcClient->left;        
	    y = (unsigned long) pWnd->rcClient->bottom -32;  
	    
		width  = (unsigned long) pWnd->rcClient->width;       
	    height = (unsigned long) 32; 

		// Nothing.
	};  

	// #todo: 
	// Checar limites.


	//
	// Draw.
	//


	// #Importante: 
	// Checando se o esquema de cores está funcionando.

//ColorSchemeSupport:

    // #todo:
	// Podemos ter uma rotina de automação dessa checagem.

	if ( (void *) CurrentColorScheme == NULL )
	{
		//Erro fatal:
		//Precisamos de um esquema de cores válido.
		
		panic ("StatusBar: CurrentColorScheme");

	}else{
		
		// validation.
		
		if ( CurrentColorScheme->used != 1 || 
		     CurrentColorScheme->magic != 1234 )
		{
		    //Erro fatal:
		    //Precisamos de um esquema de cores válido.
		    
			panic ("StatusBar: CurrentColorScheme validation");
		};
		
		// Como o esquema de cores foi aprovado, vamos usa-lo.
	    // Configurando as cores usadas na status bar.
	    
		StatusBarColor = (unsigned long) CurrentColorScheme->elements[csiStatusBar];  
	
		//Nothing.
	};
	
	//Desktop.
	desktopID = (int) get_current_desktop_id ();
	
	//
	// Window
    //
	
    hWnd = (void *) CreateWindow ( WT_STATUSBAR, 0, 0, "statusbar", 
                       x, y, width, height, 
                       pWnd, desktopID, StatusBarColor, StatusBarColor ); 

	if ( (void *) hWnd == NULL )
	{
		printf ("StatusBar: hWnd\n");
        goto fail;

    }else{

        RegisterWindow (hWnd);

        draw_text ( hWnd, 0* (width/2), 1* (height/3), 
            COLOR_WINDOWTEXT, string1 );

        draw_text ( hWnd, 1* (width/2), 1* (height/3), 
            COLOR_WINDOWTEXT, string2 );

		
		//
		// Parent 
		//
		
		// Seleciona a statusbar da parent window.

		pWnd->statusbar = hWnd;

		// ... ?
		
	    goto done;
	};	 
	
	goto fail;
	
	// More ?!
	
done:

	return (struct window_d *) hWnd;

fail:

    //printf ("fail\n");
	return NULL;
}



//
// End.
//


