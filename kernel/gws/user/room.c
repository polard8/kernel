/*
 * File: kernel\gws\user\room.c
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
void *get_current_room (){
	
    if ( current_room < 0 )
	{
	    return NULL;
	};
	
    return (void *) roomList[current_room];
};


/*
 * set_current_windowstation:
 *
 */
void set_current_room (struct room_d *room){
	
    //Check.
	
	if ( (void *) room == NULL )
	{
	    return;
    };  
    
	current_room = (int) room->id;
};


/*
 * CreateWindowStation:
 *     Cria uma window station em uma seção de usuário.
 */
void *CreateRoom (struct room_d *room){
	
	int i=0;
	
	struct room_d *Current;    
    struct room_d *Empty;	
	
	//User Session Struct.
    
	if ( (void *) room == NULL )
	{
	    return NULL;
	};
	
	//Window Station Struct.
    
	Current = (void *) malloc ( sizeof(struct room_d) );
	
	if ( (void *) Current == NULL )
	{
	    printf("CreateWindowStation: Current");
		die ();
		
		//refresh_screen();
		//while(1){}
		
	} else {
		
	    //room.
	    Current->room = (struct room_d *) room;
		
		//continua...
	};
	
	
	while ( i < ROOM_COUNT_MAX )
	{	
        Empty = (void *) roomList[i]; 			
        
		if ( (void *) Empty == NULL )
		{
		    roomList[i] = (unsigned long) Current;
		    Current->id = i;    	
		    
			//set_current_room(Current);	
			
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
int RegisterRoom (struct room_d *room){
	
    int i=0;
		
	//Struct.
    
	if ( (void *) room == NULL )
	{
        return (int) 1;    
    };
	
	while (i < ROOM_COUNT_MAX)
	{
        if ( (void *) roomList[i] == NULL )
		{
       	    roomList[i] = (unsigned long) room; 
            
			return (int) 0;			
	    };
		
	    i++;
    };		

    return (int) 1;
};


/*
 * init_windowstation_list:
 */
void init_room_list (){
	
    int i=0;
	
    while ( i < ROOM_COUNT_MAX )
	{
        roomList[i] = 0;
		
		i++; 
	};
};


/*
 * init_window_station:
 *     Inicializa o gerenciamento de window stations.
 */
void init_room_manager (){
	
    //printf("init_window_station: Initializing ...\n");
	
	windowstations_count = 0;
	
	//List.
	init_room_list();
	
	// Struct 'room0' 
    
	room0 = (void *) malloc ( sizeof(struct room_d) );
	
	if ( (void *) room0 == NULL )
	{
	    printf("init_window_station fail: room0 Struct");
		die ();
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

    RegisterRoom (room0);
	set_current_room (room0);   
	
	//printf("done\n");
};


/*
int windowstationInit()
{}
*/

//
// End.
//

