/*
 * File: user/usession.c
 *
 * Descrição:
 *     User Session.
 *     Faz parte do módulo Window Manager do tipo MB.
 *     Arquivo principal do gerenciador de user session. 
 *     Secões usuário.
 *
 * *importante:
 *     Quando um usuário loga, ele cria uma 'seção', que conterá uma 
 * 'window station', que conterá um 'desktop', que conterá 'janelas'.
 *
 * Versão 1.0, 2015, 2016.
 */
 
 
#include <kernel.h>


/*
 * get_current_user_session:
 *     Get yhe current user session handle.
 */

void *get_current_user_session (void){
	
    //return (void*) CurrentUserSession;
	
	if ( current_usersession < 0 || 
	     current_usersession >= USER_SESSION_COUNT_MAX )
    {
	    return NULL;
	};
	
    return (void *) usessionList[current_usersession];
}



/*
 *********************************
 * CreateUserSection:
 *     Cria uma user section para um usuário válido.
 */

void *CreateUserSession (int userID){
	
	int i=0;
	
	struct usession_d *NewUserSession;
	

	// Check limits.
    if ( userID < 0 || userID >= USER_COUNT_MAX )
    {
        return NULL;
    };


	// Create a new user section struct.
    
	NewUserSession = (void *) kmalloc ( sizeof(struct usession_d) );
	
    if ( (void *) NewUserSession == NULL )
    {
        panic ("CreateUserSection:");
    } else {

		NewUserSession->usUsed  = (int) 1;         //flag, está em uso.
		NewUserSession->usMagic = (int) 1234;      //magic
	    
		NewUserSession->userID  = (int) userID;    //*IMPORTANTE id do usuário da seção.
		//@todo: group.
		NewUserSession->initialized = 0;           //Apenas criada, não inicializada.
		
		//@todo: Setar ponteiro.
		//CurrentUserSession = (void *) NewUserSession;
		
		//continua...
	};
			
	//Procura uma entrada vazia na lista.
	
	while ( i < USER_SESSION_COUNT_MAX )
	{		
        //Coloca na lista em um lugar vazio.
        
		if ( (void *) usessionList[i] == NULL )
		{
			usessionList[i] = (unsigned long) NewUserSession; 
		    NewUserSession->usId = i;    //User session id.		
		    
			return (void *) NewUserSession;
		};	
		
		i++;
	};
    
    // ?? debug ??
	printf ("CreateUserSession error: Can't create!\n");
    die ();
	
	//refresh_screen();
	//while(1){};
	
	//#bugbug: Talvez devamos retornar.
	return NULL;
}



//Open User Session.
void open_user_session (void){
	
	if ( (void *) CurrentUserSession == NULL )
	{
		printf ("open_user_session: fail \n");
		return;
	};
	
	//@todo: Criar tempo de início de sessão.
	//tempo de inicio de sessão
	
	CurrentUserSession->BeginTime = (unsigned long) 0;	
	CurrentUserSession->initialized = 1; 
}

//Close User Session.

void close_user_session (void){
	
	if ( (void *) CurrentUserSession == NULL )
	{
		printf("close_user_session: fail \n");
		return;
	};
	
	//@todo: Criar tempo de fim de sessão.
	//tempo de fim de sessão
	
	CurrentUserSession->EndTime = (unsigned long) 0;
	
	
	CurrentUserSession->usId = 0; 
	
	CurrentUserSession->usUsed = 0; 
	CurrentUserSession->usMagic = 0; 
	
	CurrentUserSession->userID = 0; 
	
	CurrentUserSession->initialized = 0; 
	
	//...
}



/*
 *****************************
 * init_user_session:
 *     Inicializa user session. 
 */

void init_user_session (void){

    int i = 0;
    int CurrentUser_ID = 0;


    debug_print ("init_user_session:\n");


	//Init list

    while ( i < USER_SESSION_COUNT_MAX )
    {
        usessionList[i] = 0;
        i++;
    };


	//
	// User.
	//

    CurrentUser_ID = (int) GetCurrentUserId ();

    if ( CurrentUser_ID < 0 || CurrentUser_ID >= USER_COUNT_MAX )
    {
		CurrentUserSession = NULL;
		//panic ("init_user_session: CurrentUser_ID");
		return;
    }

	
	//
	// User Session.
	//
	
	//Struct.
	
    usession0 = (void *) CreateUserSession (CurrentUser_ID);
	
    if ( (void *) usession0 == NULL )
	{
	    panic ("init_user_session: DefaultUserSession");
	}
	
	
	CurrentUserSession = (void *) usession0;
	
	//Open.
	open_user_session ();
	
	//...
	
    CurrentUserSession->initialized = 1;
}


/*
int usersessionInit()
{}
*/


//
// End.
//

