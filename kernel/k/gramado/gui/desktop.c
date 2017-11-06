/*
 * File: desktop.c
 *
 * Descrição:
 *     Gerência a criação de desktops.
 *     Cada desktop pertence à uma window station. Cada desktop contém várias 
 * janelas e menus. Cada desktop tem um propósito, as vezes genérico, as vezes 
 * específico. 
 *     Define como as janelas estão empilhadas, qual está em foregroud (Por cima).
 *     Define uma lista encadeada de janelas, trocando a janela ativa e o 
 * foco de entrada. Etc...  
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Obs:
 *     Os aplicativos poderão acessar esses serviços em user mode. Através de 
 * um subsistema em user mode que gerencia janelas.
 *     O desktop abarca vários componentes como janelas especiais, 
 * janelas normais, áreas de memória para usos diversos, permissoes, 
 * características diversas ... etc ...
 *    Obs: *IMPORTANTE: Um desktop tem um heap de memória. A gerente de
 * memória alocará memória para os processos pertencentes à um desktop
 * específico no próprio heap do desktop ao qual o processo pertence. 
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */

 
#include <kernel.h>


/*
    Buffer creation:
	===============
    
	//Supposing the display is 800x600 with 32 bpp (meaning 32/8 = 4 bytes per pixel).
    uint8_t *BackBuffer = ((uint8_t *) (malloc(800 * 600 * 4)));
	
	//24bpp.
	unsigned char *BackBuffer = ( (unsigned char *) (malloc(800 * 600 * 3))); 
*/

/*
 * RegisterDesktop:
 *     Registrando um desktop numa lista de desktops.
 *     @todo: Mudar para desktopRegisterDesktop(.). 
 */
int RegisterDesktop(struct desktop_d *d)
{
    int Offset = 0;
	
    if( (void*) d == NULL ){
        return (int) 1;    //Erro.
    };
	
	//
	// @todo: Pode aparacer um loop infinito aqui.
	//
	
	while(Offset < DESKTOP_COUNT_MAX)
	{
       if( (void*) desktopList[Offset] == NULL ){
       	    desktopList[Offset] = (unsigned long) d; 
            goto done;			
	   };
	   Offset++;
    };		
	
fail:
    return (int) 1;
done:
    return (int) 0;
};


/*
 * set_current_desktop:
 *     Seta o desktop atual.
 *     @todo: Mudar para desktopSetCurrentDesktop(.).
 */
void set_current_desktop(struct desktop_d *desktop)
{
	//Check.
	if( (void*) desktop == NULL ){ return; }
	
	//Configura a variável global.
	current_desktop = (int) desktop->desktopId;
	return;
};

/*
 * get_current_desktop:
 *     Pega o endereço da estrutura do desktop atual.
 *     @todo: Mudar para desktopGetCurrentDesktop().
 */
void *get_current_desktop()
{
    //Check limits.
    if( current_desktop < 0 || current_desktop >= DESKTOP_COUNT_MAX ){
	    return NULL;
	};
    return (void *) desktopList[current_desktop];
};


int get_current_desktop_id(){
	return (int) current_desktop;
};


/*
 * init_desktop_list:
 *     Inicializa o array de ponteiros de desktop.
 */
void init_desktop_list()
{
    int i = 0;		
    while( i < DESKTOP_COUNT_MAX){
        desktopList[i] = 0;
		++i; 
	};
	return;
};



/*
 * CreateDesktop:
 *     Cria um desktop em uma window station.
 *
 */
void *CreateDesktop(struct wstation_d *ws)
{
	int Offset = 0;
	struct desktop_d *Current;
    struct desktop_d *Empty;	
    //... 
	
	//Check.
    if( (void*) ws == NULL ){ return NULL; };
	
	//
	// @todo: O usuário precisa de permissão pra criar desktops.
	//
	
	
	// Struct.
    Current = (void*) malloc( sizeof(struct desktop_d) );
	if( (void*) Current == NULL){
	    printf("CreateDesktop:");
		refresh_screen();
		while(1){}	
	}
	else
	{
	    //section.
	    Current->wstation = (void*) ws;
		//continua...
	};
	
	
	while(Offset < DESKTOP_COUNT_MAX)
	{	
        Empty = (void *) desktopList[Offset]; 			
        if( (void*) Empty == NULL){
		    desktopList[Offset] = (unsigned long) Current;
		    Current->desktopId = Offset;    //Window Station id.		
		    goto done;
		};	
		Offset++;
	};
	//Nothing.
fail:
    return NULL;
done:	
    return (void*) Current;
};



/*
 * set_current_menuwindow:
 *     Configura a menu window atual.
 *
 */
void set_current_menuwindow(struct desktop_d *desktop, struct window_d *window)
{
    //Check.
	if( (void*) desktop == NULL || (void*) window == NULL ){ return; };  
    
	desktop->menuWindow = (void*) window;  //Current foreground window.
    return;
};

/*
 * set_current_foreground:
 *     Configura a foreground window atual.
 *
 */
void set_current_foreground(struct desktop_d *desktop, struct window_d *window)
{
    //Check.
	if( (void*) desktop == NULL || (void*) window == NULL ){ return; };  
    
	desktop->foregroundWindow = (void*) window;    //Current foreground window.
    return;
};


/*
 * set_current_messagewindow:
 *     Configura a message window atual.
 *
 */
void set_current_messagewindow(struct desktop_d *desktop, struct window_d *window)
{
    //Check.
	if( (void*) desktop == NULL || (void*) window == NULL ){ return; };  
	
	desktop->messageWindow = (void*) window;    //Current message window.
    return;
};


/*
 * set_current_traywindow:
 *     Configura a tray window atual.
 */
void set_current_traywindow(struct desktop_d *desktop, struct window_d *window)
{
    //Check.
	if( (void*) desktop == NULL || (void*) window == NULL ){ return; };  
	
	desktop->trayWindow = (void*) window;  //Current tray window.
    return;
};

/*
 * set_current_tooltipwindow:
 *     Configura a tooltip window atual.
 */
void set_current_tooltipwindow(struct desktop_d *desktop, struct window_d *window)
{
    //Check.
	if( (void*) desktop == NULL || (void*) window == NULL ){ return; };  
	
	desktop->tooltipWindow = (void*) window;  //Current tooltip window.
    return;
};

/*
 * change_foreground:
 *    Change foreground window for a desktop.
 */
void change_foreground(struct desktop_d *desktop)
{
    struct window_d *fw;
	
    //Check Desktop.
	if( (void*) desktop == NULL ){ return; };  

	//Foreground window.
	fw = (void*) desktop->foregroundWindow;
	if( (void*) fw == NULL ){
	    return;
    };  

	//Use a próxima janela indicada na estrutura da atual.
	if( (void*) fw->next == NULL ){
		//Deixa a mesma que estava.
   	    desktop->foregroundWindow = (void*) fw;
    }else{
		//Muda para a próxima.
		desktop->foregroundWindow = (void*) fw->next;
	    return;		
	};  
	//Nothing.
done:
    return;
};


/*
 * set_current_sysMenu:
 *     Configura o sysMenu atual.
 */
void set_current_sysMenu(struct desktop_d *desktop, struct menu_d *menu)
{
    //Check.
	if( (void*) desktop == NULL || (void*) menu == NULL ){ return; };
	
	desktop->sysMenu = (void*) menu;    //Current.
    return;
};


/*
 * set_current_dialogsysMenu:
 *     Configura o dialogsysMenu atual.
 *
 */
void set_current_dialogsysMenu(struct desktop_d *desktop, struct menu_d *menu)
{
    //Check.
	if( (void*) desktop == NULL || (void*) menu == NULL ){ return; };
	
	desktop->dialogsysMenu = (void*) menu;    //Current. 
    return;
};


/*
 * set_current_menuHScroll:
 *     Configura o menuHScroll atual.
 *
 */
void set_current_menuHScroll(struct desktop_d *desktop, struct menu_d *menu)
{
    //Check.
	if( (void*) desktop == NULL || (void*) menu == NULL ){ return; };
	
	desktop->menuHScroll = (void*) menu;    //Current. 
    return;
};


/*
 * set_current_menuVScroll:
 *     Configura o menuVScroll atual.
 *
 */
void set_current_menuVScroll(struct desktop_d *desktop, struct menu_d *menu)
{
    //Check.
	if( (void*) desktop == NULL || (void*) menu == NULL ){ return; };
	
	desktop->menuVScroll = (void*) menu;    //Current. 
    return;
};


/*
 * init_desktop:
 *     Inicializa o desktop 0.
 *     @todo: Mudar para: desktopInit().
 */
void init_desktop()
{
    //printf("init_desktop: Initializing..\n");
	
	desktops_count = 0;
	
	//inicializa a lista.
	init_desktop_list();

	//Struct.
	desktop0 = (void*) malloc( sizeof(struct desktop_d) );
	if( (void*) desktop0 == NULL ){
	    printf("init_desktop error: desktop0");
		refresh_screen();
		while(1){}	
	};
	
	//
	// Configura o desktop atual.
	//
	
    set_current_menuwindow(desktop0, NULL); 
    set_current_foreground(desktop0, NULL); 
    set_current_messagewindow(desktop0, NULL); 
    set_current_traywindow(desktop0, NULL); 
    set_current_tooltipwindow(desktop0, NULL); 
	
    set_current_sysMenu(desktop0, NULL);
    set_current_dialogsysMenu(desktop0, NULL);
    set_current_menuHScroll(desktop0, NULL);
    set_current_menuVScroll(desktop0, NULL);

	
	//registra na lista
	RegisterDesktop(desktop0); 
		
	//esse desktop pertence à window station 0.
	//desktop0->windowstation = (void*) ws0;
	
	
	//...
		
done:
	//printf("Done.\n");
	//Set Current.
	set_current_desktop(desktop0);
    return;
};

/*
int desktopInit()
{}
*/

//
// Fim.
//
