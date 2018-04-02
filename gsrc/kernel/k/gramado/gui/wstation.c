/*
 * File: wstation.c
 *
 * Descrição:
 *     Window Station Manager. (WSM).
 *     Desktop Pool Manager. (DPM). 
 *     Rotinas para gerenciamento de window stations.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Obs:
 *     Os aplicativos poderão acessar esses serviços em user mode.
 *     Atraves de um subsistema em user mode que gerencia janelas.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


/*
 * get_current_windowstation:
 *
 */
void *get_current_windowstation()
{
    if( current_windowstation < 0){
	    return NULL;
	};
	
    return (void *) windowstationList[current_windowstation];
};


/*
 * set_current_windowstation:
 *
 */
void set_current_windowstation(struct wstation_d *ws)
{
    //Check.
	if( (void*) ws == NULL){
	    return;
    };  
    
	current_windowstation = (int) ws->wsId;
    return;
};


/*
 * CreateWindowStation:
 *     Cria uma window station em uma seção de usuário.
 */
void *CreateWindowStation(struct usession_d *s)
{
	int Offset = 0;
	struct wstation_d *Current;    
    struct wstation_d *Empty;	
	
	//User Session Struct.
    if( (void*) s == NULL){
	    return NULL;
	};
	
	//Window Station Struct.
    Current = malloc(sizeof(struct wstation_d));
	if( (void*) Current == NULL)
	{
	    printf("CreateWindowStation:");
		refresh_screen();
		while(1){}	
	}
	else
	{
	    //session.
	    Current->usession = s;
		//continua...
	};
	
	while(Offset <= WINDOW_STATION_COUNT_MAX)
	{	
        Empty = (void *) windowstationList[Offset]; 			
        if( (void*) Empty == NULL){
		    windowstationList[Offset] = (unsigned long) Current;
		    Current->wsId = Offset;    //window station id.		
		    goto done;
		};	
		Offset++;
	};
	
fail:
    return NULL;
	
done:
    //@todo: Set Current.?
	//set_current_windowstation(Current);	
    return (void*) Current;
};


/*
 * RegisterWindowStation:
 *     Registrando uma windowstation numa lista de window stations.
 *
 */
int RegisterWindowStation(struct wstation_d *ws)
{
    int Offset = 0;
		
	//Struct.
    if( (void*) ws == NULL ){
        return (int) 1;    //Erro.
    };
	
	while(Offset < WINDOW_STATION_COUNT_MAX)
	{
        if( (void*) windowstationList[Offset] == NULL ){
       	    windowstationList[Offset] = (unsigned long) ws; 
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
 * init_windowstation_list:
 */
void init_windowstation_list()
{
    int i = 0;
	
    while(i < WINDOW_STATION_COUNT_MAX){
        windowstationList[i] = 0;
		++i; 
	};
	
	return;
};


/*
 * init_window_station:
 *     Inicializa o gerenciamento de window stations.
 */
void init_window_station()
{
    //printf("init_window_station: Initializing ...\n");
	windowstations_count = 0;
	
	//List.
	init_windowstation_list();
	
	// Struct 'ws0' 
    ws0 = malloc(sizeof(struct wstation_d));
	if( (void*) ws0 == NULL){
	    printf("init_window_station fail: ws0 Struct.");
		refresh_screen();
		while(1){}	
	};
	
	
	/*
    UpdateUserInfo( 0, 
                    CurrentUser, 
					 0, 
					 0, 
					 NewUserSession->id, 
					 0,
					 0 );	
	*/
	
	//...

done:
    RegisterWindowStation(ws0);
	set_current_windowstation(ws0);    //Set current.	
	//printf("done\n");
    return;
};


/*
int windowstationInit()
{}
*/

//
// End.
//

