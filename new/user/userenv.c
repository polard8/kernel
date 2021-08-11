

#include <kernel.h>



// User Environment Manager (UEM)
// Segue uma lista de operações que poderão ser realizadas para configuração
// do ambiente gráfico do usuário. Obs: Nesse módulo, apenas chamaremos
// algumas funções primitivas. Todo o trabalho maior deve ficar para os
// servidores em user mode.

#define UEM_NULL 0
#define UEM_CHANGE_BACKGROUND  1
#define UEM_CHANGE_LOGO        2
#define UEM_CHANGE_COLORS      3
// ...


int GetCurrentGroupId (void)
{
    return (int) current_group;
}

int GetCurrentUserId (void)
{
    return (int) current_user;
}

void SetCurrentUserId (int user_id)
{
    if ( user_id < 0 || user_id >= USER_COUNT_MAX )
    {
        printf ("SetCurrentUserId: [FAIL]\n");
        return;
    }

    current_user = (int) user_id;
}

int is_superuser(void)
{
    uid_t uid = -1;
    
    uid = GetCurrentUserId();

    // Is 'root' ?

    if ( uid == 0 ){  return TRUE;  }
    
    return FALSE;
}

int __getusername (char *buffer)
{
    char *login_buffer = (char *) buffer;

    if ( (void*) buffer == NULL ){
        debug_print ("__getusername: [FAIL] buffer\n");
        return -1;
    }

	//Estrutura default para informações sobre o host.
	//host.h

    if ( (void *) CurrentUser== NULL ){
        printf ("__getusername: CurrentUser\n");
        return (int) -1; 
    }else{
        
        //64 bytes
        strcpy ( login_buffer, (const char *) CurrentUser->__username );
                
        return (int) CurrentUser->userName_len;
    };

    return (int) -1;
}

/*
 * __setusername: 
 *
 */

// O novo nome está no buffer passado via argumento.
// Ele tem o limite de 64 bytes.
// Vamos colocar ele na estrutura de usuário.

int __setusername ( const char *new_username )
{
    if ( (void*) new_username == NULL ){
        debug_print ("__setusername: [FAIL] new_username\n");
        return -1;
    }

    // Estrutura de usuário.
     
    // #todo
    // Where is this structure defined?

    if ( (void *) CurrentUser == NULL ){
        printf ("__setusername: CurrentUser\n");
        return (int) -1;
    }else{

        CurrentUser->userName_len = (size_t) strlen (new_username) + 1;

        //64 bytes
        strcpy ( CurrentUser->__username, (const char *) new_username);
        
        return 0;
    };

    return (int) -1;
}

/*
 * CreateUser:
 *     Cria um usuário do computador.
 *     #importante: Quando criar um usuário tem que 
 * montar uma pasta para ele em /root/user/(name)
 * Se utilizar um usuário válido é só pegar os arquivos de 
 * configuração dentro da pasta.
 */

void *CreateUser ( char *name, int type ){

    struct user_info_d  *New;

    int Index = 0;
    int i=0;


    // #bugbug
    // We don't wanna kill the initialization 
    // only for a wrong name.

    // #alert
    if ( (void*) name == NULL ){
        debug_print ("CreateUser: [FAIL] name\n");
        panic ("CreateUser: [FIXME] name is not valid\n");
    }

    // #alert
    if (*name == 0){
        debug_print ("CreateUser: [FAIL] *name\n");
        panic ("CreateUser: [FIXME] *name is not valid\n");
    }


    // #todo
    // We need to check the limits for the name size.
    // Maybe copy the name into a local buffer.
    // strlen(name);


    // Structure.

    New = (void *) kmalloc ( sizeof(struct user_info_d) ); 

    if ( (void *) New == NULL ){
        panic ("CreateUser: New\n");
    } else {

        New->used  = TRUE;
        New->magic = 1234;
        New->userType = type; 
        New->path = NULL;
        
        // The name.
        // The name size.

        if ( (void*) name != NULL )
        {
            strcpy( New->__username, (const char *) name);
            New->userName_len = strlen(name);
            
            // #todo
            // Check limits for this size.
            // There is a standard definition for that size.
            //if ( New->userName_len >= ???? ){}
        }
 
        //Session.
        //room. Window Station. (Desktop pool).
        //Desktop.

        New->usessionId = current_usersession;
        New->roomId     = current_room;
        New->desktopId  = current_desktop;
    
        // Inicializando a lista de objetos permitidos.
        // Proibindo tudo.
        for (i=0; i<128; i++){ New->permissions[i]=0; };

	    //Inicializa tokens. (rever)
	    //New->k_token = KERNEL_TOKEN_NULL;
	    //New->e_token = EXECUTIVE_TOKEN_NULL;
	    //New->m_token = MICROKERNEL_TOKEN_NULL;
	    //New->h_token = HAL_TOKEN_NULL;
		
	    //...
    };


    // Procurando uma entrada livre na lista.
    while ( Index < USER_COUNT_MAX )
    {
        if ( (void *) userList[Index] == NULL )
        {
            // User Id. 
            New->userId = Index; 

            userList[Index] = (unsigned long) New;

            // printf("CreateUser: Done.\n"); 
            return (void *) New;
        }

        Index++;
    };

//Fail: 
//Fim do loop. 
//Não encontramos uma entrada livre.

fail:
    return NULL;
}



int User_initialize(void)
{

    debug_print("User_initialize:\n");

    current_user = 0;

    // User session, room (Window Station), desktop, 
    current_usersession  = 0;
    current_room         = 0;
    current_desktop      = 0;

    // Initialize user info structure
    printf ("User_initialize: init_user_info\n");
    //init_user_info ();   


//
// Security
//

    // Initialize User Session, room and Desktop.
    // user section
    //printf ("User_initialize: initializing user session\n");
    //init_user_session();

    // room
    // initialize window station default.
    //printf ("User_initialize: initializing room\n");   
    //init_room_manager();

    // desktop
    printf ("User_initialize: initializing desktop\n");   
    init_desktop();



    debug_print("User_initialize: done\n");
    return 0;
}




















