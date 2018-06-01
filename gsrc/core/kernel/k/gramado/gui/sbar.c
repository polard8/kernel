/*
 * File: gui\statusbar.c
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


/*
int UpdateStatusBar( struct window_d *window, 
                     unsigned char *string1, 
		             unsigned char *string2 );

int UpdateStatusBar( struct window_d *window, 
                     unsigned char *string1, 
		             unsigned char *string2 )
{
	//@todo:
	//atualizar as strings de uma status bar caso
	//a janela tenha uma status bar.
};
*/


/*
 ************************************************
 * StatusBar:
 *     Desenha uma status bar, dada a janela, 
 * encontramos o retângula da área de cliente.
 *     @todo: Acrescentar uma borda delicada, 
 * usar outra cor, próximo do branco.
 *
 * O tamanho da status bar deve ser to tamanho da 
 * largura da janela. A scroll bar não deve invadir 
 * o espaço da status bar.
 */
struct window_d*
StatusBar( struct window_d *window, 
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
	
	//
	//  ## Parent Window ##
	//
	
	if( (void*) pWnd == NULL )
	{
		printf("StatusBar: pWnd\n");
        goto fail;

    }else{
				
	    // A Status bar é um elemento dentro da janela.
	    // não podemos considerar as bordas e a barra de títulos.
	    if( (void*) pWnd->rcClient == NULL )
		{
			printf("StatusBar: pWnd->rcClient\n");
		    goto fail;
	    }
		
		//magic
	    if( pWnd->rcClient->used != 1 || 
	        pWnd->rcClient->magic != 1234 )
	    {
			printf("StatusBar: used magic\n");
		    goto fail;
	    }		
		
		
	    // Set Up Sizes.
	    // Começa 32pixels antes do fim.
	    // Mesma largura da janela.
	    x = (unsigned long) pWnd->rcClient->left;        
	    y = (unsigned long) pWnd->rcClient->bottom -32;  
	    
		width = (unsigned long) pWnd->rcClient->width;       
	    height = (unsigned long) 32;  		
		
		// Nothing.
	};  
	
	//
	// @todo: Checar limites.
	//
	
    //Desenha a barra.
//draw_bar:

	//
	// #Importante: 
	// Checando se o esquema de cores está funcionando.
	//
	
ColorSchemeSupport:

    //@todo:
	//Podemos ter uma rotina de automação dessa checagem.

	if( (void*) CurrentColorScheme == NULL )
	{
		//Erro fatal:
		//Precisamos de um esquema de cores válido.
		printf("StatusBar: CurrentColorScheme");
		die();
	}else{
		
		if( CurrentColorScheme->used != 1 || 
		    CurrentColorScheme->magic != 1234 )
		{
		    //Erro fatal:
		    //Precisamos de um esquema de cores válido.			
		    printf("StatusBar: CurrentColorScheme validation");
		    die();			
		};
		
		
		// Como o esquema de cores foi aprovado, vamos usa-lo.
	    // Configurando as cores usadas na status bar.
	    StatusBarColor = (unsigned long) CurrentColorScheme->elements[csiStatusBar];  
		
		
		//Nothing.
	};
	
	
	//Desktop.
	desktopID = (int) get_current_desktop_id();	
	
	
	//
	// ## Window  ##
	//

 
	hWnd = (void*) CreateWindow( WT_STATUSBAR, 0, 0, "statusbar", 
	                   x, y, width, height, 
					   pWnd, desktopID, StatusBarColor, StatusBarColor); 
	
	if( (void*) hWnd == NULL )
	{
		printf("StatusBar: hWnd\n");
        goto fail;
    }else{
		
	    // @todo: Registrar! 
	    // (Sabendo quem é janela mãe pode-se liberar memória depois).
	
	    RegisterWindow(hWnd);
        //set_active_window(hWnd);
	    //SetFocus(hWnd);	
		
	    //  ## Draw ##
		
		//Escreve as strings.
		
	    draw_text( hWnd, 
		           0* (width/2), 
				   1* (height/3), 
				   COLOR_WINDOWTEXT, 
				   string1 );
				   
	    draw_text( hWnd, 
		           1* (width/2), 
				   1* (height/3), 
				   COLOR_WINDOWTEXT, 
				   string2 );
				   
				   
		// Seleciona a statusbar da parent window.
		pWnd->statusbar = hWnd;		   
      
	  
	    // O que mais ??
	    goto done;
	};	 
	
	goto fail;
	
	//More?!
	
done:     
    //return (int) 0;
	return (struct window_d*) hWnd;
fail:
    printf("fail\n");
	return NULL;
    //return (int) 1;	
};



/*
int statusbarInit()
{}
*/

//
//fim
//

