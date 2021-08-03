


#ifndef ____USER_H
#define ____USER_H    1

/*
 Um usuário só pode rodar o servidor de recursos gráficos se ele estiver no modo terminal.
 No Gramado o modo terminal utiliza o servidor de recursos gráficos kgws, que é um servidor
 dentro do base kernel.
 No Gramado, o modo terminal terá o kgws como seu servidor de recursos gráficos para a exibição do 
 terminal em full screen.
 O segundo servidor de recursos gráficos é o gws que está dentro do programa shell.bin.
 Isso significa que para um usuário inicializar os recursos gráficos do servidor gws ele
 precisa estar em modo terminal usando o kgws.
 */


#define USER_COUNT_MAX     16    //User count.
#define GROUP_COUNT_MAX    4     //Group count.


//
// Standard user names.
//

// Interactive
// Used by special real users.
#define USER_NAME_ROOT    "root" 

// Non interactive
// Used by some system services.
#define USER_NAME_SYSTEM  "system" 


//User types.  
typedef enum {
    USER_TYPE_NULL,            // 0
    USER_TYPE_INTERACTIVE,     // 1 ex: 'root'
    USER_TYPE_NONINTERACTIVE,  // 2 ex: 'system'
    // ...
}user_type_t;


/*
    #importante:  
	User Display Modes:
    Modos de display para interação com o usuário.
	>>> NÃO se refere aos modos de display da placa de vídeo.
	Pois aqui, tanto o modo terminal, quanto graphical estão usando
	o modo gráfico da placa de vídeo.
	O modo texto da placa de vídeo só é usado no boot.
 */

typedef enum {
    USER_DISPLAY_MODE_NULL,
    USER_DISPLAY_MODE_TERMINAL,     // Modo gráfico com um terminal em full screen.
    USER_DISPLAY_MODE_GRAPHICAL    // Modo gráfico usando um servidor de recursos gráficos.
    // ...
}user_display_mode_t;

//
// == js-like events. ==============
//

// window events
// #todo: move to another place.
typedef enum {
    WINDOW_EVENTS_NULL, 
    WINDOW_EVENTS_ONAFTERPRINT,
    WINDOW_EVENTS_ONBEFOREPRINT,
    WINDOW_EVENTS_ONDEBOREUNLOAD,
    WINDOW_EVENTS_ONERROR,
    WINDOW_EVENTS_ONHASCHANGE,
    WINDOW_EVENTS_ONLOAD,
    WINDOW_EVENTS_ONMESSAGE,
    WINDOW_EVENTS_ONOFFLINE,
    WINDOW_EVENTS_ONPAGEHIDE,
    WINDOW_EVENTS_ONPAGESHOW,
    WINDOW_EVENTS_ONPOPSTATE,
    WINDOW_EVENTS_ONREDO,
    WINDOW_EVENTS_ONRESIZE,
    WINDOW_EVENTS_ONSTORAGE,
    WINDOW_EVENTS_ONUNDO,
    WINDOW_EVENTS_ONUNLOAD,
    // ...    
}window_events_t; 

// form events 
// #todo: move to another place.
typedef enum { 
    FORM_EVENTS_NULL,
    FORM_EVENTS_ONBLUR,
    FORM_EVENTS_ONCHANGE,
    FORM_EVENTS_ONCONTEXTMENU,
    FORM_EVENTS_ONFOCUS,
    FORM_EVENTS_ONFORMCHANGE,
    FORM_EVENTS_ONFORMINPUT,
    FORM_EVENTS_ONINPUT,
    FORM_EVENTS_ONINVALID,
    FORM_EVENTS_ONRESET,
    FORM_EVENTS_ONSELECT,
    FORM_EVENTS_ONSUBMIT
    //...
}form_events_t;  
 


// keybaord events. 
// #todo: move to another place.
typedef enum {
    KEYBOARD_EVENTS_NULL,
    KEYBOARD_EVENTS_ONKEYDOWN,
    KEYBOARD_EVENTS_ONKEYPRESS,
    KEYBOARD_EVENTS_ONKEYUP
    //...
}keyboard_events_t;  
 
 
// mouse eventes 
// #todo: move to another place.
typedef enum {
    MOUSE_EVENTS_NULL,
    MOUSE_EVENTS_ONCLICK,
    MOUSE_EVENTS_ONDBLCLICK,
    MOUSE_EVENTS_ONDRAG,
    MOUSE_EVENTS_ONDRAGEND,
    MOUSE_EVENTS_ONDRAGENTER,
    MOUSE_EVENTS_ONDRAGLEAVE,
    MOUSE_EVENTS_ONDRAGOVER,
    MOUSE_EVENTS_ONDRAGSTART,
    MOUSE_EVENTS_ONDROP,
    MOUSE_EVENTS_ONMOUSEDOWN,
    MOUSE_EVENTS_ONMOUSEMOVE,
    MOUSE_EVENTS_ONMOUSEOUT,
    MOUSE_EVENTS_ONMOUSEOVER,
    MOUSE_EVENTS_ONMOUSEUP,
    MOUSE_EVENTS_ONMOUSEWHEEL,
    MOUSE_EVENTS_ONSCROLL
    //...
}mouse_events_t; 




// mouse stuff
// #todo: move to another place.

// protótipos para métodos que gerenciam eventos de janela.
//...

// protótipos para métodos que gerenciam eventos de form.
//...

// protótipos para métodos que gerenciam eventos de keyboard.
//int onKeyDown();
//int onKeyPress();
//int onKeyUp();

// protótipos para métodos que gerenciam eventos de mouse.
//int onClick();
//int onDblClick();
//int onDrag();
//int onDragEnd();
//int onDragEnter();
//int onDragLeave();
//int onDragOver();
//int onDragStart();
//int onDrop();
//int onMouseDown();
//int onMouseMove();
//int onMouseOut();
//int onMouseOver();
//int onMouseUp();
//int onMouseWhell();
//int onScroll();



/*
 * ?? Se há um usuário configurado conforme registrado em arquivo de configuração.
 */ 
int userconfig_Status;
 
 

/*
 ***************************************************
 * user_info_d:
 *     Estrutura para perfil de usuário do computador.
 */ 

// #test
// This is used in the terminal structure to handle user sessions.
// logon stuff.

struct user_info_d
{
    object_type_t  objectType;
    object_class_t objectClass;

    int userId;
    int used;
    int magic;

    //
    // == Security ============================================
    //

    // Section, window station and desktop.    
    struct usession_d *usession;
    int usessionId;
    
    struct room_d     *room;
    int roomId;
    
    struct desktop_d  *desktop;
    int desktopId;
    // ===================================================

    //??
    char *path;             // '/root/user/(name)'
    
    char __username[64];    // HOSTNAME_BUFFER_SIZE
    size_t userName_len;    // len 
    
    
    
    // Indica quais os tipos de objetos permitidos para esse usuário.
    // See: globals/gobject.h
    int permissions[128];

	//
	// Bancos de Dados 
	//

	//struct bank_d *kdb;         //O banco de dados do processo kernel.	
	//struct bank_d *gdbListHead; //Lista de bancos de contas conjuntas.
	//struct bank_d *ldbListHead; //Lista de bancos de contas particulares.

	
	//Tempo da sessão de uso.
	//start time.
	//unsigned long StartTime;
	//end time.
    //unsigned long EndTime;

    
    // em qual console virtual iniciamos a sessão.
    int virtualconsoleId;

    
	// Em qual console virtual iniciamos a sessão?
	// F1 ~ F7 ...
	//struct virtual_console_d *virtual_console;
 
    //=========================


    // user type.
    user_type_t userType;


	//#importante:
	//Olhe as explicações logo acima.
	//user_display_mode_t display_mode;
	
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
		
    // Continua...
    
    // navigation.
    struct user_info_d  *Next;
}; 

struct user_info_d *RootUser;       // Super user
struct user_info_d *CurrentUser;    // Current user

// user list:
// root user is the user '0'.
unsigned long userList[USER_COUNT_MAX];



//
// == prototypes ====================
//

int GetCurrentGroupId (void);
int GetCurrentUserId (void);
void SetCurrentUserId (int user_id);
int is_superuser(void);
int __getusername (char *buffer);
int __setusername ( const char *new_username );
void *CreateUser ( char *name, int type );

int User_initialize(void);


#endif    




