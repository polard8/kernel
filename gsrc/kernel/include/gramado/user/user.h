/*
 * Arquivo: user.h
 *
 * Descrição:
 *     Header para rotinas de configuração o ambiente do usuário.
 *
 *     DESKTOP -> WINDOW STATION -> USER SECTION.
 *
 *     USER -> USER SECTION.
 *     USER -> WINDOW STATION.
 *     USER -> DESKTOP. 
 *
 *     PROCESS -> WINDOW STATION. 
 *     THREAD  -> DESKTOP.
 *
 *
 * Tipos de usuários: (interactive. non_interactive).
 *
 * @todo: Criar um utilitário em user mode que mostre informações sobre o usuário.
 *
 * Versão 1.0, 2015, 2016.
 */
 

#define USER_COUNT_MAX 16  //User count.
#define GROUP_COUNT_MAX 4  //Group count.
  
 
//Strings.
#define USER_SYSTEM            "system" 
#define USER_DEFAULT           "default" 
#define USER_ADMIN             "admin" 
#define USER_ALL               "all" 
#define _4NORA_USER_DIRECTORY  "/root/user" 
//...

 
//User types.  
typedef enum {
    USER_TYPE_NULL,            //0 
    USER_TYPE_INTERACTIVE,     //1
    USER_TYPE_NONINTERACTIVE,  //2
	//...
}user_type_t;

 
/*
 * ?? Se há um usuário configurado conforme registrado em arquivo de configuração.
 */ 
int userconfig_Status;
 
 
//
// @todo: Revendo: para cada grupo pode ter 2 tipos, major e minor.
// 
 
 
/*
 * kernel_token_t:
 *     TOKEN de acesso.
 *     As rotinas mais sistemicamente importantes darão acesso somente para 
 * usuários com token do tipo KERNEL_TOKEN_MAJOR.
 * @todo: Esse era um esquema de autoridades que será revisto.
 */
/* 
typedef enum {
    KERNEL_TOKEN_NULL,	
    KERNEL_TOKEN_MAJOR,    	
    //...	
}kernel_token_t;
*/
 
 
/*
 * executive_token_t:
 *     TOKEN de acesso.
 *     A interface gráfica utiliza os tokens EXECUTIVE_TOKEN_NULL para acesso 
 * à window station e EXECUTIVE_TOKEN_TEACHER para acesso
 * à desktop.
 * Para a gerência de objetos e devices apenas o token KERNEL_TOKEN_MAJOR é aceito,
 * denotando ser sistemicamente importante. 
 * @todo: Esse era um esquema de autoridades que será revisto.
 */
/* 
typedef enum {
    EXECUTIVE_TOKEN_NULL,
    EXECUTIVE_TOKEN_PRINCIPAL,    //Acesso à window station. (School).
    EXECUTIVE_TOKEN_TEACHER,      //Acesso à desktop. (Class).	
	//...
}executive_token_t;
*/
 
 
/*
 * microkernel_token_t:
 *     TOKEN de acesso.
 *
 *     Para a gerência de processos e threads
 *     apenas o token KERNEL_TOKEN_MAJOR é aceito,
 *     denotando ser sistemicamente importante. 
 * @todo: Esse era um esquema de autoridades que será revisto.
*/
/*
typedef enum {
    MICROKERNEL_TOKEN_NULL,
	//...
}microkernel_token_t;
*/

/*
 * hal_token_t:
 *     TOKEN de acesso.
 *
 *     Para a gerência de controladores
 *     apenas o token KERNEL_TOKEN_MAJOR é aceito,
 *     denotando ser sistemicamente importante. 
 * @todo: Esse era um esquema de autoridades que será revisto.
*/
/*
typedef enum {
    HAL_TOKEN_NULL,
    //...	
}hal_token_t;
 */
 
/*
 * user_info_d:
 *     Estrutura para perfil de usuário do computador.
 *
 */ 
typedef struct user_info_d user_info_t;
struct user_info_d
{
	object_type_t objectType;
	object_class_t objectClass;
	
	//File.
	FILE userinfo;  //User info file.
	
    //Name.
	char *name;
    unsigned long name_address; 	 
	
    //Id. 
	int userId;
	
	//
	// *** Bancos de Dados ***
	//

	struct bank_d *kdb;         //O banco de dados do processo kernel.	
	struct bank_d *gdbListHead; //Lista de bancos de contas conjuntas.
	struct bank_d *ldbListHead; //Lista de bancos de contas particulares.


	
	//Tempo da sessão de uso.
	//start time.
	//unsigned long StartTime;
	//end time.
    //unsigned long EndTime;
	
	//
	// * IMPORTANTE:
	// A estrutura de user session representa uma sessão  
	// de uso. Nessa estrutura temos ponteiros para pools
    // de objetos, pools de pagedirectory e pools de desktop (wstation)	
	//
	
	//Section, window station and desktop.
	int sessionId;
    int windowstationId;
    int desktopId;	

	//user type.
    user_type_t userType;	
	
	//
	// TOKENs de acesso à recursos do kernel. @todo: Rever.
	//
	
	//kernel_token_t       k_token;    //Kernel.
	//executive_token_t    e_token;    //Executive.
	//microkernel_token_t  m_token;    //Microkenrel.
	//hal_token_t          h_token;    //Hal.
	
	//
	// todo: tipo, tamanho ... 
	//
		
    //Continua...
	struct user_info_d *Next;  //Próximo usuário.(troca.).
}; 
user_info_t *CurrentUser;    //Current user !!!
user_info_t *SystemUser;    //O sistema é o usuário '0'.
user_info_t *DefaultUser;    //O usuário padrão.
//user_info_t *UserInfo;
//user_info_t *User;
//...


//Lint.
unsigned long userList[USER_COUNT_MAX];
 
  
//
// Protótipos.
//  


//@todo: Mudar os nomes para uma forma mais organizada.


int startUserEnvironment(int argc, char* argv[]); 

int init_user_environment_manager(int argc, char *argv[]); 
void init_user_info();

void *CreateUser(char *name, int type);
//User
void SetCurrentUserId(int user_id);
int GetCurrentUserId();
//Group
void SetCurrentGroupId(int group_id);
int GetCurrentGroupId();
void UpdateUserInfo( struct user_info_d *user, 
                     int id, 
					 char *name, 
					 int type, 
					 int user_session_id, 
					 int window_station_id,
					 int desktop_id );
void ShowUserInfo(int user_id);
					 
//
// Fim.
//

