/*
 * File: wstation.c
 *
 * Descrição:
 *     Window Station Manager. (WSM).
 *     "Desktop Pool" Manager. (DPM). 
 *     Rotinas para gerenciamento de window stations.
 *     Faz parte do módulo Window Manager do tipo MB.
 *
 * Obs:
 *     Os aplicativos poderão acessar esses serviços em user mode.
 *     Atraves de um subsistema em user mode que gerencia janelas.
 *
 *    2015 - Created by Fred Nora.
 */

 
#include <kernel.h>


/*
 * get_current_windowstation:
 *
 */
void *get_current_windowstation (){
	
    if ( current_windowstation < 0 )
	{
	    return NULL;
	};
	
    return (void *) windowstationList[current_windowstation];
};


/*
 * set_current_windowstation:
 *
 */
void set_current_windowstation (struct wstation_d *ws){
	
    //Check.
	
	if ( (void *) ws == NULL )
	{
	    return;
    };  
    
	current_windowstation = (int) ws->wsId;
};


/*
 * CreateWindowStation:
 *     Cria uma window station em uma seção de usuário.
 */
void *CreateWindowStation (struct usession_d *s){
	
	int i=0;
	
	struct wstation_d *Current;    
    struct wstation_d *Empty;	
	
	//User Session Struct.
    
	if ( (void *) s == NULL )
	{
	    return NULL;
	};
	
	//Window Station Struct.
    
	Current = (void *) malloc ( sizeof(struct wstation_d) );
	
	if ( (void *) Current == NULL )
	{
	    printf("CreateWindowStation: Current");
		die ();
		
		//refresh_screen();
		//while(1){}
		
	} else {
		
	    //session.
	    Current->usession = s;
		
		//continua...
	};
	
	
	while ( i < WINDOW_STATION_COUNT_MAX )
	{	
        Empty = (void *) windowstationList[i]; 			
        
		if ( (void *) Empty == NULL )
		{
		    windowstationList[i] = (unsigned long) Current;
		    Current->wsId = i;    	
		    
			//set_current_windowstation(Current);	
			
			return (void *) Current;
		};	
		
		i++;
	};
	
    return NULL;    
};


/*
 * RegisterWindowStation:
 *     Registrando uma windowstation numa lista de window stations.
 */
int RegisterWindowStation (struct wstation_d *ws){
	
    int i=0;
		
	//Struct.
    
	if ( (void *) ws == NULL )
	{
        return (int) 1;    
    };
	
	while (i < WINDOW_STATION_COUNT_MAX)
	{
        if ( (void *) windowstationList[i] == NULL )
		{
       	    windowstationList[i] = (unsigned long) ws; 
            
			return (int) 0;			
	    };
		
	    i++;
    };		

    return (int) 1;
};


/*
 * init_windowstation_list:
 */
void init_windowstation_list (){
	
    int i=0;
	
    while ( i < WINDOW_STATION_COUNT_MAX )
	{
        windowstationList[i] = 0;
		
		i++; 
	};
};


/*
 * init_window_station:
 *     Inicializa o gerenciamento de window stations.
 */
void init_window_station (){
	
    //printf("init_window_station: Initializing ...\n");
	
	windowstations_count = 0;
	
	//List.
	init_windowstation_list();
	
	// Struct 'ws0' 
    
	ws0 = (void *) malloc ( sizeof(struct wstation_d) );
	
	if ( (void *) ws0 == NULL )
	{
	    printf("init_window_station fail: ws0 Struct");
		die ();
		
		//refresh_screen();
		//while(1){}	
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

    RegisterWindowStation (ws0);
	set_current_windowstation (ws0);   
	
	//printf("done\n");
};


/*
int windowstationInit()
{}
*/

//
// End.
//

