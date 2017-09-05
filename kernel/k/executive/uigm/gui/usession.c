/*
 * File: usession.c
 *
 * Descrição:
 *     User Session.
 *     Faz parte do módulo Window Manager do tipo MB.
 *     Arquivo principal do gerenciador de user session. 
 *     Secões usuário.
 *     Quando um usuário loga, ele cria uma seção, que conterá uma 
 * window station, que conterá um desktop, que conterá janelas.
 *
 * Versão 1.0, 2015, 2016.
 */
 
 
#include <kernel.h>


/*
 * get_current_user_session:
 *     Get yhe current user session handle.
 */
void *get_current_user_session()
{
    //return (void*) CurrentUserSession;
	
	if(current_usersession < 0 || current_usersession >= USER_SESSION_COUNT_MAX){
	    return NULL;
	};
	
    return (void *) usessionList[current_usersession];
};


/*
 * CreateUserSection:
 *     Cria uma user section para um usuário válido.
 */
void *CreateUserSession(int userID)
{
	struct usession_d *NewUserSession;
	int Offset = 0;

	// Check limits.
    if( userID < 0 || userID >= USER_COUNT_MAX ){
	    return NULL;
	};
	
	// Create a new user section struct.
    NewUserSession = malloc(sizeof(struct usession_d));
	if( (void*) NewUserSession == NULL ){
	    printf("CreateUserSection:");
		refresh_screen();
		while(1){}	
	}
	else
	{
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
	while(Offset < USER_SESSION_COUNT_MAX)
	{		
        //Coloca na lista em um lugar vazio.
        if( (void *) usessionList[Offset] == NULL)
		{
			usessionList[Offset] = (unsigned long) NewUserSession; 
		    NewUserSession->usId = Offset;    //User session id.		
		    goto done;
		};	
		Offset++;
	};
	//Nothing.
fail:
    printf("CreateUserSession error: Cant create!\n");
    refresh_screen();
	while(1){};
	return NULL;	
done:	
    return (void*) NewUserSession;
};


//Close User Session.
void close_user_session()
{
	if((void*) CurrentUserSession == NULL){
		printf("close_user_session:");
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
	
	return;
};


//Open User Session.
void open_user_session()
{
	if((void*) CurrentUserSession == NULL){
		printf("open_user_session:");
		return;
	};
	
	//@todo: Criar tempo de início de sessão.
	//tempo de inicio de sessão
	CurrentUserSession->BeginTime = (unsigned long) 0;	
	CurrentUserSession->initialized = 1; 
	return;
};


/*
 * init_user_session:
 *     Inicializa user session.
 */
void init_user_session()
{	
    int CurrentUser = 0;
 	int Offset = 0;
	
	//Init list	
	while(Offset < USER_SESSION_COUNT_MAX){		
        usessionList[Offset] = 0;
		Offset++;
	};
	
	//
	// User.
	//
	
	CurrentUser = (int) GetCurrentUserId();
	
	//Limits.
	if(CurrentUser < 0 || CurrentUser >= USER_COUNT_MAX ){
		return;
	};
	
	
	//
	// User Session.
	//
	
	//Struct.
    DefaultUserSession = (void *) CreateUserSession(CurrentUser);
	if( (void*) DefaultUserSession == NULL){
	    printf("init_user_session:");
	    refresh_screen();
	    while(1){}
	}; 
	
	CurrentUserSession = (void*) DefaultUserSession;
	
	//Open.
	open_user_session();
	
	//...
	
done:
    DefaultUserSession->initialized = 1;
    return;
};


/*
int usersessionInit()
{}
*/

//
// End.
//

