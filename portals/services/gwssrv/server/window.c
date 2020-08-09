/*
 * File: window.c 
 * 
 * 
 */


#include <api.h>
#include <gws.h>

/*
 * =====================================================
 * windowSetUpColorScheme:
 *     Isso configura os esquemas de cores utilizados 
 * pelo sistema.
 *     Essa rotina é chamada apenas uma vez na inicialização
 * do kernel.
 *     O esquema de cores a ser utilizado deve estar 
 * salvo no perfil do usuário que fez o logon.
 * Os dois esquemas padrão chamam-se: 'humility' e 'pride'.
 * + O esquema 'humility' são cores com tema cinza, 
 * lembrando interfaces antigas.
 * + O esquema 'pride' são cores modernas 
 *   ( Aquele verde e preto e cinza, das primeiras versões, 
 * com imagens publicadas. )
 * @todo: é preciso criar rotinas que selecionem entre os 
 * modo criados e habilitados.
 * É preciso criar rotinas que permitam que aplicativos 
 * em user mode criem esquemas de cores e habilite eles.
 */


void 
gwssrv_initialize_color_schemes (int selected_type)
{

    struct gws_color_scheme_d *humility;
    struct gws_color_scheme_d *pride;

	//
	// * HUMILITY
	//
	
    //Criando o esquema de cores humility. (cinza)
    humility = (void *) malloc ( sizeof(struct gws_color_scheme_d) );
    
	if( (void *) humility == NULL ){
		gde_debug_print ("gwssrv_initialize_color_schemes: humility\n");
		
	}else{
		
		//Object.
		//humility->objectType = ObjectTypeColorScheme;
		//humility->objectClass = ObjectClassGuiObjects;
		

		humility->used = 1;
		humility->magic = 1234;
		humility->name = "Humility";
		
		//Colors
		//Definidas em ws.h
		humility->elements[csiNull] = 0;                             //0
        humility->elements[csiDesktop] = HUMILITY_COLOR_BACKGROUND;  //1		
		humility->elements[csiWindow] = HUMILITY_COLOR_WINDOW;       //2
        humility->elements[csiWindowBackground] = HUMILITY_COLOR_WINDOW_BACKGROUND;	 //3	
		humility->elements[csiActiveWindowBorder] = HUMILITY_COLOR_ACTIVE_WINDOW_BORDER;  //4
        humility->elements[csiInactiveWindowBorder] = HUMILITY_COLOR_INACTIVE_WINDOW_BORDER;  //5		
		humility->elements[csiActiveWindowTitleBar] = HUMILITY_COLOR_ACTIVE_WINDOW_TITLEBAR;  //6
        humility->elements[csiInactiveWindowTitleBar] = HUMILITY_COLOR_INACTIVE_WINDOW_TITLEBAR;  //7	 	
		humility->elements[csiMenuBar] = HUMILITY_COLOR_MENUBAR;                //8
        humility->elements[csiScrollBar] = HUMILITY_COLOR_SCROLLBAR;            //9  
		humility->elements[csiStatusBar] = HUMILITY_COLOR_STATUSBAR;            //10
        humility->elements[csiMessageBox] = HUMILITY_COLOR_MESSAGEBOX;		    //11
		humility->elements[csiSystemFontColor] = HUMILITY_COLOR_SYSTEMFONT;		//12
		humility->elements[csiTerminalFontColor] = HUMILITY_COLOR_TERMINALFONT;	//13
		//...
		
		//Sanvando na estrutura padrão para o esquema humility.
		GWSHumilityColorScheme = (void*) humility;
	};	
	
	//
	// * PRIDE 
	//
	
    //Criando o esquema de cores PRIDE. (colorido)
    pride = (void *) malloc ( sizeof(struct gws_color_scheme_d) );
    
    if ( (void *) pride == NULL ){
        gde_debug_print ("gwssrv_initialize_color_schemes: pride\n");

    }else{
		
		//Object.
		//pride->objectType  = ObjectTypeColorScheme;
		//pride->objectClass = ObjectClassGuiObjects;

		pride->used = 1;
		pride->magic = 1234;
		pride->name = "Pride";
		
		//Colors
		//Definidas em ws.h
		pride->elements[csiNull] = 0;
        pride->elements[csiDesktop] = PRIDE_COLOR_BACKGROUND;  
		pride->elements[csiWindow] = PRIDE_COLOR_WINDOW;
        pride->elements[csiWindowBackground] = PRIDE_COLOR_WINDOW_BACKGROUND;
		pride->elements[csiActiveWindowBorder] = PRIDE_COLOR_ACTIVE_WINDOW_BORDER;  
        pride->elements[csiInactiveWindowBorder] = PRIDE_COLOR_INACTIVE_WINDOW_BORDER;  
		pride->elements[csiActiveWindowTitleBar] = PRIDE_COLOR_ACTIVE_WINDOW_TITLEBAR;    
        pride->elements[csiInactiveWindowTitleBar] = PRIDE_COLOR_INACTIVE_WINDOW_TITLEBAR;		
		pride->elements[csiMenuBar] = PRIDE_COLOR_MENUBAR;
        pride->elements[csiScrollBar] = PRIDE_COLOR_SCROLLBAR;  		
		pride->elements[csiStatusBar] = PRIDE_COLOR_STATUSBAR;    
        pride->elements[csiMessageBox] = PRIDE_COLOR_MESSAGEBOX;
		pride->elements[csiSystemFontColor] = PRIDE_COLOR_SYSTEMFONT;    //12
		pride->elements[csiTerminalFontColor] = PRIDE_COLOR_TERMINALFONT;  //13		
		//...
		
		//Sanvando na estrutura padrão para o esquema pride.
		GWSPrideColorScheme = (void *) pride;
	};	
		
	
	// Configurando qual será o esquema padrão.
	// @todo; Criar uma função que selecione qual dois esquemas serão usados
	//        apenas selecionando o ponteiro da estrutura.  
	
    switch (selected_type){
		
		case ColorSchemeNull:
		    GWSCurrentColorScheme = (void *) humility;
		    break;
		
		case ColorSchemeHumility:
		    GWSCurrentColorScheme = (void *) humility;
		    break;
		
		case ColorSchemePride:
	        GWSCurrentColorScheme = (void *) pride; 
		    break;
		
		default:
		    GWSCurrentColorScheme = (void *) humility;
			break;
	};	
}


//seleciona o tipo ...isso é um serviço.
int gwssrv_select_color_scheme (int type){
	//#debug
	//printf("windowSelectColorScheme: type={%d} \n", type);
	
    switch (type)
	{
		case ColorSchemeHumility:
		    goto do_humility;
		    break;
			
		case ColorSchemePride:
		    goto do_pride;
			break;
			
		default:
		    gde_debug_print("windowSelectColorScheme: Type not defined\n");
			goto fail;
			break;
	};

	
do_humility:

    if ( (void *) GWSHumilityColorScheme == NULL )
    {
		gde_debug_print("HumilityColorScheme fail\n");
        goto fail;  
           	    	
	}else{
		
	    if ( GWSHumilityColorScheme->used != 1 || 
		     GWSHumilityColorScheme->magic != 1234 )
		{
			gde_debug_print("HumilityColorScheme sig fail\n");
			goto fail;
		}
		
		gde_debug_print("Humility selected\n");
	    GWSCurrentColorScheme = GWSHumilityColorScheme;	
	    goto done;
	};		
	
	
do_pride:	

    if ( (void *) GWSPrideColorScheme == NULL )
    {
		gde_debug_print("GWSPrideColorScheme fail\n");
        goto fail; 
            	    	
	}else{
	    if( GWSPrideColorScheme->used != 1 || 
		    GWSPrideColorScheme->magic != 1234 )
		{
			gde_debug_print("PrideColorScheme sig fail\n");
			goto fail;
		}
		
	    gde_debug_print ("Pride selected\n"); 
		GWSCurrentColorScheme = GWSPrideColorScheme;	
	    goto done;
	};		

done:

    return 0;	
    
fail:

    gde_debug_print ("fail\n");
    return 1;
}









/*
 ***********************************************
 * show_window_rect:
 *     Mostra o retângulo de uma janela que está no backbuffer.
 *     Tem uma janela no backbuffer e desejamos enviar ela para o frontbuffer.
 *     A rotina de refresh rectangle tem que ter o vsync
 *     #todo: criar um define chamado refresh_window.
 */

int gws_show_window_rect (struct gws_window_d *window){


    struct gws_window_d *p;

    if ( (void *) window == NULL ){
        debug_print ("show_window_rect: window\n");
        return (int) 1;

    }else{

        if ( window->used == 1 || window->magic == 1234 )
        {

			//#shadow 
			// ?? E se a janela tiver uma sombra, 
			// então precisamos mostrar a sombra também. 
			
			//#bugbug
			//Extranhamente essa checagem atraza a pintura da janela.
			//Ou talvez o novo tamanho favoreça o refresh rectangle,
			//ja que tem rotinas diferentes para larguras diferentes
			
			//if ( window->shadowUsed == 1 )
			//{

			    //window->width = window->width +4;
				//window->height = window->height +4;
			    
				//refresh_rectangle ( window->left, window->top, 
				//    window->width +2, window->height +2 ); 
				//return (int) 0;
			//}


            
            p = window->parent;
            
            //#todo: delete
            if ((void*)p==NULL)
            {
                gde_debug_print("gws_show_window_rect: No parent");
                
                gws_refresh_rectangle ( 
                    window->left, 
                    window->top, 
                    window->width, 
                    window->height ); 

                return 0;
            }
            
            if ((void*)p!=NULL)
            {
                //gde_debug_print("gws_show_window_rect: parent ok");
                
                gws_refresh_rectangle ( 
                    window->left,
                    window->top,
                    window->width, 
                    window->height ); 

                return 0;
            }

            return 0;
        }
    };


	//fail.
    return (int) 1;
}



/*
// #todo
// Retorna o ponteiro de estrutura de janela
// dado o id da janela.
struct gws_window_d *gws_window_from_id (int id);
struct gws_window_d *gws_window_from_id (int id)
{
    struct gws_window_d *w;
    
    // ...
    
    return (struct gws_window_d *) w;
}
*/
 

int gwsDefineInitialRootWindow ( struct gws_window_d *window )
{
    if ( (void *) window == NULL )
        return -1;
    
    ROOT = window;
    
    // ...
    
    return 0;  //ok
}
   
/*
 *******************************************************
 * gwsRegisterWindow: 
 *     Register a window.
 */
 
// OUT:
// < 0 = fail.
// > 0 = Ok. (index)
 
int gwsRegisterWindow (struct gws_window_d *window){

    struct gws_window_d *tmp; 

    int __slot=0;



    if ( (void *) window == NULL ){
        //gws_debug_print ("gwsRegisterWindow: window struct\n");
        return (int) -1;    
    }


	// Contagem de janelas e limites.
	// (é diferente de id, pois id representa a posição
	// da janela na lista de janelas).

    windows_count++;

    if ( windows_count >= WINDOW_COUNT_MAX ){
        //gws_debug_print ("gwsRegisterWindow: Limits\n");
        printf ("gwsRegisterWindow: Limits\n");
        return -1;
    }


    // Search for empty slot
    for (__slot=0; __slot<1024; __slot++)
    {
        tmp = (struct gws_window_d *) windowList[__slot];

        // Found!
        if ( (void *) tmp == NULL )
        {
            windowList[__slot] = (unsigned long) window; 
            window->id = (int) __slot;
            
            return (int) __slot;
        }
    };

// fail
    //gde_debug_print("No more slots\n");
    return (int) (-1);
}

/*
 * get_active_window:
 *     Obtem o id da janela ativa.
 *     @todo: Mudar para windowGetActiveWindowId().
 */


int get_active_window ()
{
    return (int) active_window;  
}


/*
 * set_active_window:
 */

void set_active_window (int id){

	// @todo: Limits. Max.
    if (id < 0)
        return;
    

    active_window = (int) id;
}


// Pegando a z-order de uma janela.
int get_zorder ( struct window_d *window ){

    if ( (void *) window != NULL ){
        return (int) window->zIndex;
    }

    return (int) -1;
}



int get_top_window (){

    return (int) top_window;
}


//Setando a top window.
void set_top_window (int id){

    top_window = (int) id;
}



/*
 *********************************************
 * gws_resize_window:
 *     Muda as dimensões da janela.
 */
 
int 
gws_resize_window ( 
    struct gws_window_d *window, 
    unsigned long cx, 
    unsigned long cy )
{

    if ( (void *) window == NULL )
        return -1;


    // Só precisa mudar se for diferente.
    if ( window->width  != cx ||
         window->height != cy )
    {
        window->width  = (unsigned long) cx;
        window->height = (unsigned long) cy;
    }

    return 0;
}


/*
 ****************************************************
 * gws_replace_window:
 *     Muda os valores do posicionamento da janela.
 */	
 
int 
gws_replace_window ( 
    struct gws_window_d *window, 
    unsigned long x, 
    unsigned long y )
{

    if ( (void *) window == NULL )
        return -1;


    if ( window->left != x ||
         window->top  != y )
    {
        window->left = (unsigned long) x;
        window->top  = (unsigned long) y;
    }

    return 0;
}



/*
 * gwsWindowLock:
 *     Bloqueia uma janela.
 *     @todo: Quem pode realizar essa operação??
 */
 
void gwsWindowLock (struct gws_window_d *window){

    if ( (void *) window == NULL )
        return;


    window->locked = (int) WINDOW_LOCKED;  //1.
}


/*
 * gwsWindowUnlock:
 *     Desbloqueia uma janela.
 *     @todo: Quem pode realizar essa operação??
 */
 
void gwsWindowUnlock (struct gws_window_d *window){

    if ( (void *) window == NULL )
        return;


    window->locked = (int) WINDOW_UNLOCKED;  //0.
}


int gwssrv_init_windows(void)
{
    int i=0;
    
    //window.h
    windows_count      =0;
    window_with_focus  =0;
    active_window      =0;
    top_window         =0;
    //...

    for (i=0; i<1024; i++)
        windowList[WINDOW_COUNT_MAX] = 0;


    return 0;
}

//
// End.
//


