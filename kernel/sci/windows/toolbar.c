/*
 * File: kgws/comp/toolbar.c
 *
 *     Toolbar support for kgws.
 *
 * History:
 *     2019 - Created by Fred Nora.
 */

 
#include <kernel.h>


/*
 ************************************************
 * ToolBar:
 *
 * Desenha uma toolbar.
 * #obs: Só o bg por enquanto.
 */

struct window_d *ToolBar ( struct window_d *window ){
	
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
	
	if ( (void *) pWnd == NULL )
	{
		printf ("ToolBar: pWnd\n");
        goto fail;
		
    }else{
				
		// #obs:
		// #Aviso: Estamos retornando se não existir área de cliente.
	    // A Statusbar é um elemento dentro da janela.
	    // Não podemos considerar as bordas e a barra de títulos.
	    
		if ( (void *) pWnd->rcClient == NULL )
		{
			printf ("ToolBar: rcClient\n");
		    goto fail;
	    }
		
		// validation.
		
	    if ( pWnd->rcClient->used != 1 || pWnd->rcClient->magic != 1234 )
	    {
			printf ("ToolBar: validation\n");
		    goto fail;
	    }		
		
	    // Set Up Sizes.
	    // Começa 32pixels antes do fim.
	    // Mesma largura da janela.
	    
		x = (unsigned long) pWnd->rcClient->left;        
		y = (unsigned long) pWnd->rcClient->top;  
	    
		width = (unsigned long) pWnd->rcClient->width;       
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
		
		panic ("ToolBar: CurrentColorScheme");
		
	}else{
		
		// validation.
		// Erro fatal: Precisamos de um esquema de cores válido.			
		    		
		if ( CurrentColorScheme->used != 1 || 
		     CurrentColorScheme->magic != 1234 )
		{
			panic ("ToolBar: CurrentColorScheme validation");		
		}
		
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
					   pWnd, desktopID, StatusBarColor, StatusBarColor); 
	
	if ( (void *) hWnd == NULL )
	{
		printf ("ToolBar: hWnd\n");
        goto fail;
		
    }else{
			
	    RegisterWindow (hWnd);
		
		
		//#deletar.
	    //draw_text ( hWnd, 
		//    0* (width/2), 1* (height/3), 
		//    COLOR_WINDOWTEXT, string1 );	   
	    //draw_text ( hWnd, 
		//    1* (width/2), 1* (height/3), 
		//	COLOR_WINDOWTEXT, string2 );
				   
		
		// Seleciona a statusbar da parent window.
		
		pWnd->toolbar = hWnd;
      
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


