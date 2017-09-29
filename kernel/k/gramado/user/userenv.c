/*
 * File: userenv.c 
 *
 * Descrição:
 * User Environment Manager, (UEM).
 * Cria o ambiente do usuário, Área de trabalho, onde o usuário interaje 
 * com a máquina logo após o logon. 
 *
 * MB - Módulos incluídos no Kernel Base.
 *    
 * Tem usuários do tipo interactive e do tipo non_interactive.
 * * O ambiente gráfico é criado para usuário tipo interactive.
 *
 * Rotinas de criação, inicialização, finalização e configuração 
 * do ambiente do usuário.
 * Inicia programas, troca backgrounds, cor padrão de janelas ... etc.
 * Criar session, window stations, desktops. 
 * (usando as rotinas que estão em outros módulos.)
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 */

 
#include <kernel.h>


//User Environment Manager (UEM)

//
// Segue uma lista de operações que poderão ser realizadas para configuração
// do ambiente gráfico do usuário. Obs: Nesse módulo, apenas chamaremos
// algumas funções primitivas. Todo o trabalho maior deve ficar para os
// servidores em user mode.
//

#define UEM_NULL 0
#define UEM_CHANGE_BACKGROUND 1
#define UEM_CHANGE_LOGO       2
#define UEM_CHANGE_COLORS     3
//...


//Variáveis internas.
//int userenvironmentStatus;
//int userenvironmentError;
//...


//Internas.
void config_user();



/*
 * startUserEnvironment:
 *     Cria um ambiente com janelas para usuário do tipo interativo.
 *     @todo: Todo esse trabalho gráfico não deve ser feito pelo kernel.
 *            Futuramente isso irá para um serviço de inicialização.
 *            Mudar o nome para userenvironmentStart(int argc, char* argv[]).
 */
int startUserEnvironment(int argc, char* argv[])
{
	int Status = 0;
	int UserId;
		
    //
	// GUI ~ Ítens básicos.
	//
   
    //Cria. (background e navigation bar).
    create_gui();
	
	//Inicializa.
	init_gui(); 
	
	
	//More?!
	
	if(gui->screen != NULL){
	    StatusBar( gui->screen, "GUI", "User Environment");	
    };

done:
	//
	// Barra no topo, estilo Mac/Linux.
	// Aqui vamos usar o procedimento da menubar.
	//
	
	//menubarX();

    SetProcedure( (unsigned long) &system_procedure);	 
    return (int) Status;
};


/*
 * ShowUserInfo:
 *     Mostra informações sobre o usuário atual.
 *
 * #bugbug: Aqui aparece alguma pagefault, provavelmente alguma 
 *          estrutura não foi inicializada(alocada) corretamente.
 */
void ShowUserInfo(int user_id)
{
	struct user_info_d *User;
	
	if(user_id < 0 || user_id >= USER_COUNT_MAX){
	    return;
	};  
	
	User = (void *) userList[user_id];
	if( (void*) User == NULL ){
	    printf("Invalid user ID!");
        return;		
	}else{
	    
		printf("Name={%s} Id={%d} Type={%d} \n",User->name_address
		                                       ,User->userId
											   ,User->userType );		
	    return;
	};
	
	//...
	
// Done.
done:
    return;
};


/*
 * config_user:
 *     Abre o arquivo de configuração de usuário. 
 *     No arquivo ou metafile, terão todas as informações
 * sobre o usuário e serão colocanas nas estruturas.
 *
 */
void config_user()
{
    userconfig_Status = 0;	
	
	//...
	
done:
    return;    //Ainda não implementada.
};


/*
 * CreateUser:
 *     Cria um usuário do computador.
 */
void *CreateUser(char *name, int type)
{
	int Index = 0;	
   	struct user_info_d *New;

	// New User struct.
	New = (void*) malloc( sizeof(struct user_info_d) ); 
	if( (void*) New == NULL ){
	    printf("CreateUser:");
	    refresh_screen();
	    while(1){}
	}else{
	    
		New->name = (char *) name;      //Name.
	    New->name_address = (unsigned long) name;
	    New->userType = type;    //Type.
	
	    New->sessionId       = current_usersession;      //Session. 
	    New->windowstationId = current_windowstation;    //Window Station. (Desktop pool). 
	    New->desktopId       = current_desktop;          //Desktop.

	    //Inicializa tokens. (rever)
	    //New->k_token = KERNEL_TOKEN_NULL;
	    //New->e_token = EXECUTIVE_TOKEN_NULL;
	    //New->m_token = MICROKERNEL_TOKEN_NULL;
	    //New->h_token = HAL_TOKEN_NULL;
		
	    //...
	};		
	

	//Procurando uma entrada livre na lista.
	while(Index < USER_COUNT_MAX)
	{	
        if( (void *) userList[Index] == NULL )
		{
		    userList[Index] = (unsigned long) New;
	        New->userId = Index;    //User Id.     
		    goto done;
		};
        ++Index;
	};
//Fail: 
//Fim do loop. 
//Não encontramos uma entrada livre.
fail:
    return NULL;
done:
    //printf("CreateUser: Done.\n"); 
	return (void *) New;			
};


/*
 * SetCurrentUserId:
 *     Configura o ID do usuário atual.  
 */
void SetCurrentUserId(int user_id)
{
	//Limits.
	if(user_id < 0 || user_id > USER_COUNT_MAX){
		printf("SetCurrentUserId:\n");
		return;
	};
    current_user = (int) user_id;
	return;
};


/*
 * GetCurrentUserId: 
 *     Pega o ID do usuário atual.
 */
int GetCurrentUserId(){
   return (int) current_user;
};


void SetCurrentGroupId(int group_id)
{
	//Limits.
	if(group_id < 0 || group_id > GROUP_COUNT_MAX){
		printf("SetCurrentGroupId:\n");
		return;
	};
    current_group = (int) group_id;
	return;
};


/*
 * GetCurrentGroupId: 
 *     Pega o GID do usuário atual.
 */
int GetCurrentGroupId(){
    return (int) current_group;
};


/*
 * UpdateUserInfo:
 *    Atualiza todas as informações de usuário.
 */					 
void UpdateUserInfo( struct user_info_d *user, 
                     int id, 
					 char *name, 
					 int type, 
					 int user_session_id, 
					 int window_station_id,
					 int desktop_id )
{  
	if( (void*) user == NULL){
        return;
	}else{	
	    
		user->userId = (int) id;                      //Id.     
		user->name = (char *) name;                   //Name.
	    user->name_address = (unsigned long) name;    //Name.
		user->userType = type;                        //Type.
	    user->sessionId = user_session_id;            //Session.
	    user->windowstationId = window_station_id;    //Window Station.
        user->desktopId = desktop_id;                 //Desktop.
		//...
	};
	//Nothing.
done:
    return;
};


/*
 * init_user_info:
 *     Configurar informações sobre o usuário default.
 *
 * Obs: 
 *     Deve ser possível configurar usuários independente se 
 *     a interface gráfica está habilitada ou não.
 *
 * Obs:
 *     Utiliza as informações do usuário ativo. 
 *     O usuário ativo pode ser trocado.
 *     pode ser criar e deletar usuários.
 */
void init_user_info()
{	 
	int Id = 0;
    int Index = 0;	
	
	//Name. (static)
	//char *defaultName = "default-[USER]";     //@todo: Usar uma constante em system.h. 
	//char defaultName[] = "default-[USER]"; //@todo: Usar esse.
	

	//Initialize list.
	while(Index < USER_COUNT_MAX){
	    userList[Index] = (unsigned long) 0;
        ++Index;
	};	
	
	//Configurando a estrutura global.
	// Create default user. (default,interactive)
	DefaultUser = (void*) CreateUser(default_user_name, USER_TYPE_INTERACTIVE);
	if( (void*) DefaultUser == NULL){
	    printf("init_user_info:");
	    refresh_screen();
	    while(1){}
	}else{
		
		//Coloca no início da lista.
		//userList[0] = (unsigned long) SystemUser;    //System.
		userList[1] = (unsigned long) DefaultUser;     //Default.
		userList[2] = (unsigned long) 0;               //0.
		//userList[3] = (unsigned long) 0;               //0.
		//...
		
		//Configura o usuário atual.
		Id = (int) DefaultUser->userId;
		SetCurrentUserId(Id);
		CurrentUser = (void *) DefaultUser;
		
		//Configura o grupo atual ao qual o usuário pertence.
		SetCurrentGroupId(0);
		
		//...
		
		//g_logged = (int) 1;
	};
	
    // Continua...??!!

done:
    printf("init_user_info: Done.\n"); 
    return;
};


/*
 * init_user_environment_manager:
 *    Inicializa o User Environment Manager. (UEM). 
 */
int init_user_environment_manager(int argc, char *argv[]) 
{
	//...
	
    //g_module_uem_initialized = 1;
    userenvironmentStatus = 1;
	return (int) 0;
};


/*
 * Construtor
void userenvironmentUserEnvironment()
{}
*/

/*
int userenvironmentInit()
{}
*/

//
// End.
//

