/*
 * File: security/usession.c
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
 * 2015 - Created by Fred Nora.
 */


#include <kernel.h>


/*
 * get_current_user_session:
 *     Get the current user session handle.
 */

void *get_current_user_session (void)
{

    //return (void*) CurrentUserSession;

    if ( current_usersession < 0 || 
         current_usersession >= USER_SESSION_COUNT_MAX )
    {
        return NULL;
    }

    return (void *) usessionList[current_usersession];
}



void 
set_current_user_session ( 
    struct usession_d *usession )
{

    if ( (void *) usession == NULL ){ 
        debug_print ("set_current_user_session: [FAIL] usession \n");
        return; 
    }

    if ( usession->id < 0 ){
        debug_print ("set_current_user_session: [FAIL] id \n");
        return; 
    }

    current_usersession = (int) usession->id;

    CurrentUserSession = usession;
}


/*
 *********************************
 * CreateUserSection:
 *     Cria uma user section para um usuário válido.
 */

void *CreateUserSession (int user_id)
{

    struct usession_d *NewUserSession;
    int i=0;


	// Check limits.
    if ( user_id < 0 || user_id >= USER_COUNT_MAX )
    {
        debug_print ("CreateUserSession: [FAIL] user_id\n");
        return NULL;
    }


    //
    // User session structure.
    //

    // Create a new user section struct.

    NewUserSession = (void *) kmalloc ( sizeof(struct usession_d) );

    if ( (void *) NewUserSession == NULL ){
        panic ("CreateUserSection: [FAIL] NewUserSession\n");
    } else {

        NewUserSession->used  = (int) TRUE;
        NewUserSession->magic = (int) 1234;

        // user for this session.
        NewUserSession->uid  = (int) user_id;

        // Not initialized yet.
        NewUserSession->initialized = FALSE;

        // ...

        // #todo
        // CurrentUserSession = (void *) NewUserSession;
    };


    // We need an empty slot in the list usessionList[].
    // Coloca na lista em um lugar vazio.

    while ( i < USER_SESSION_COUNT_MAX )
    {
        if ( (void *) usessionList[i] == NULL )
        {
            // The structure pointer.
            usessionList[i] = (unsigned long) NewUserSession; 

            // User session id.
            NewUserSession->id = i;

            return (void *) NewUserSession;
        }

        i++;
    };
    
    // #debug
    // hanging for debug.

    panic ("CreateUserSession: [DEBUG] Can't create!\n");
    return NULL;
}


// ??
// Open current user session.
void open_user_session (void){

    if ( (void *) CurrentUserSession == NULL )
    {
        printf ("open_user_session: [FAIL] CurrentUserSession\n");
        return;
    }

	// #todo: 
	// Criar tempo de início de sessão.
	// tempo de inicio de sessão

    CurrentUserSession->BeginTime = (unsigned long) 0;

    // ...

    CurrentUserSession->initialized = TRUE; 
}


// ??
// Close current user session.
void close_user_session (void)
{

    if ( (void *) CurrentUserSession == NULL )
    {
        printf ("close_user_session: [FAIL] CurrentUserSession \n");
        return;
    }

	// #todo: 
	// Criar tempo de fim de sessão.
	// tempo de fim de sessão

    CurrentUserSession->EndTime = (unsigned long) 0;


    CurrentUserSession->id = 0; 

    CurrentUserSession->used  = FALSE; 
    CurrentUserSession->magic = 0; 

    CurrentUserSession->uid = 0; 

    // ...

    CurrentUserSession->initialized = FALSE; 
}



/*
 *****************************
 * init_user_session:
 * 
 *     Inicializa user session support.
 */

void init_user_session (void){

    int i = 0;
    int CurrentUser_ID = 0;


    debug_print ("init_user_session:\n");


    //  Clear the list of user sessions.

    for (i=0; i<USER_SESSION_COUNT_MAX; i++)
    {
        usessionList[i] = (unsigned long) 0;
    };

	//
	// User.
	//

    CurrentUser_ID = (int) GetCurrentUserId();

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
        panic ("init_user_session: [FAIL] usession0\n");
    }

    
    //CurrentUserSession = (void *) usession0;
    set_current_user_session(usession0);

	//Open.
    open_user_session ();

	//...

    CurrentUserSession->initialized = TRUE;
}


//
// End.
//

