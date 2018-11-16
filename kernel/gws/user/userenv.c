/*
 * File: gws\user\userenv.c 
 *
 * Descrição:
 *
 * User Environment Manager, (UEM).
 *
 * Cria o ambiente do usuário, Área de trabalho, onde o usuário interage 
 * com a máquina (logo após o logon). 
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
 *********************************************************************
 * startUserEnvironment:
 *     ?? Quem chamaou essa função ??
 *     Talvez ele nem seja usado ...#importante  
 *     os aplicativos podem esta rodando no ambiente de logon. 
 *     O procedimento do logon.c pode chama-lá apertando F1.  
 *     Cria um ambiente com janelas para usuário do tipo interativo.
 *     Obs: Isso não é realmente o ambiente que o usuário vai usar, mas sim 
 * as janelas principais onde o aplicativo 'file manager' (explorer e taskbar) 
 * vão criar juas janelas.
 * 
 * Mudar o nome para userenvironmentStart(int argc, char* argv[]).
 */
int startUserEnvironment ( int argc, char* argv[] ){
	
    int Status = 0;
	
	//
	// GUI support.
	//

    //Cria as principais janelas que servirão de base para 
    //a interface gráfica.
    create_gui();

    //Inicializa.
    init_gui(); 
	
	//
	// Keyboard support.
	//
	
	ldisc_init_modifier_keys();
	ldisc_init_lock_keys();
	
	
	// #importante
	// Obs: Precisamos inicializar todos os elementos 
	// de interação que o usuário vai precisar.
	
	//
	// ...
	//

//done:

    SetProcedure ( (unsigned long) &system_procedure);
    
	return (int) Status;
};


/*
 * ShowUserInfo:
 *     Mostra informações sobre o usuário atual.
 */
void ShowUserInfo (int user_id){
	
	struct user_info_d *User;
	
	if ( user_id < 0 || user_id >= USER_COUNT_MAX )
	{
	    return;
	};  
	
	User = (void *) userList[user_id];
	
	if ( (void *) User == NULL )
	{
	    printf("ShowUserInfo: Error\n");
        return;		
	
	}else{
	    
		printf ("Name={%s} Id={%d} Type={%d} \n", User->name_address,
		    User->userId, User->userType );		
	    return;
	};
	
	//...
};


/*
 * config_user:
 *     Abre o arquivo de configuração de usuário. 
 *     No arquivo ou metafile, terão todas as informações
 * sobre o usuário e serão colocanas nas estruturas.
 *
 */
void config_user (){
	
    userconfig_Status = 0;	
	
	//...
	
//done:
    //return;    //Ainda não implementada.
};


/*
 * CreateUser:
 *     Cria um usuário do computador.
 *     #importante: Quando criar um usuário tem que 
 * montar uma pasta para ele em /root/user/(name)
 * Se utilizar um usuário válido é só pegar os arquivos de 
 * configuração dentro da pasta.
 * 
 */
 
void *CreateUser ( char *name, int type ){
	
	int Index = 0;	
	
   	struct user_info_d *New;

	New = (void *) malloc ( sizeof(struct user_info_d) ); 
	
	if ( (void *) New == NULL )
	{
	    printf("user-userenv-CreateUser:");
	    die();
		
	} else {
	    
		New->used = 1;
		New->magic = 1234;
		
		//New->path = ?
		
		New->name = (char *) name;      
	    New->name_address = (unsigned long) name;
	    New->userType = type;  

 		//Session.
        //Window Station. (Desktop pool).
        //Desktop.		 
	
	    New->sessionId = current_usersession;           
	    New->windowstationId = current_room;  //->roomID  
	    New->desktopId = current_desktop;          

	    //Inicializa tokens. (rever)
	    //New->k_token = KERNEL_TOKEN_NULL;
	    //New->e_token = EXECUTIVE_TOKEN_NULL;
	    //New->m_token = MICROKERNEL_TOKEN_NULL;
	    //New->h_token = HAL_TOKEN_NULL;
		
	    //...
	};		
	

	//Procurando uma entrada livre na lista.
	while ( Index < USER_COUNT_MAX )
	{	
        if ( (void *) userList[Index] == NULL )
		{
		    //User Id. 
			New->userId = Index;     
						
		    userList[Index] = (unsigned long) New;

            //printf("CreateUser: Done.\n"); 
	        return (void *) New;			
		};
        
		Index++;
	};
	
//Fail: 
//Fim do loop. 
//Não encontramos uma entrada livre.

fail:
    return NULL;
};


/*
 * SetCurrentUserId:
 *     Configura o ID do usuário atual.  
 */
void SetCurrentUserId (int user_id){
	
	if ( user_id < 0 || user_id >= USER_COUNT_MAX )
	{
		printf("user-userenv-SetCurrentUserId:\n");
		return;
	};
	
    current_user = (int) user_id;
	
	//return;
};


/*
 * GetCurrentUserId: 
 *     Pega o ID do usuário atual.
 */
int GetCurrentUserId (){
	
   return (int) current_user;
};


void SetCurrentGroupId (int group_id){
	
	if ( group_id < 0 || group_id >= GROUP_COUNT_MAX )
	{
		printf("SetCurrentGroupId:\n");
		return;
	};
	
    current_group = (int) group_id;
	
	//return;
};


/*
 * GetCurrentGroupId: 
 *     Pega o GID do usuário atual.
 */
int GetCurrentGroupId (){
	
    return (int) current_group;
};


/*
 * UpdateUserInfo:
 *    Atualiza todas as informações de usuário.
 */					 
void UpdateUserInfo ( struct user_info_d *user, 
                      int id, 
					  char *name, 
					  int type, 
					  int user_session_id, 
					  int window_station_id,
					  int desktop_id )
{  
	if ( (void *) user == NULL )
	{
        return;
	
	} else {
		
		//Estamos tentando atualizar uma estrutura válida.

        if ( user->used != 1 || user->magic != 1234 )
		{
			//fail;
			//return;
		}  	
	    
		user->userId = (int) id;                      //Id.     
		
		user->name = (char *) name;                   //Name.
	    user->name_address = (unsigned long) name;    //Name.
		
		user->userType = type;                        //Type.
	    
		user->sessionId = user_session_id;            //Session.
	    user->windowstationId = window_station_id;    //Window Station.
        user->desktopId = desktop_id;                 //Desktop.
		//...
	};
};


/*
 * init_user_info:
 *     Configurar informações sobre o usuário default.
 *
 *     #bugbug: Na verdade o que queremos é que seja feita a 
 * inicialização do ambiente de usuário com as configurações 
 * do usuário atual e não o default.
 *
 * #importante:
 *      Esse é o momento certo para inicializar todas as preferências 
 * salvas no perfil do usuário.
 *  
 * Configurar o ambiente do usuário significa:
 *     Selecionar suas preferências de fonte e cores.
 *     Selecionar suas preferências de estilos de elementos gráficos.
 *     etc ...
 *
 * Obs: 
 *     Deve ser possível configurar usuários independente se 
 *     a interface gráfica está habilitada ou não.
 *
 * Obs:
 *     Utiliza as informações do usuário ativo. 
 *     O usuário ativo pode ser trocado.
 *     pode ser criar e deletar usuários.
 *
 * #importante: As informações de usuário ficam 
 * em /root/user/(name)
 * 
 * Obs: Nessa hora o VFS ja deve estar montado
 * então pegaremos informações sobre qual é o usuário atual.
 * /root/user/password.txt
 * /root/user/username.txt
 * /root/user/config.txt
 * ...
 */
 
void init_user_info (){
	
	int Id = 0;
    int Index = 0;	
	
	//Initialize list.
	while (Index < USER_COUNT_MAX){
		
	    userList[Index] = (unsigned long) 0;
        Index++;
	};	
	
	//Configurando a estrutura global.
	// Create default user. (default,interactive)
	DefaultUser = (void *) CreateUser(default_user_name, USER_TYPE_INTERACTIVE);
	
	if ( (void *) DefaultUser == NULL )
	{
	    printf("init_user_info:");
	    die();
		
	} else {
		
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
};


/*
 * init_user_environment_manager:
 *    Inicializa o User Environment Manager. (UEM). 
 */
int init_user_environment_manager ( int argc, char *argv[] ){
	
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

