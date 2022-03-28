#ifndef ____USESSION_H
#define ____USESSION_H    1

//user session start
//No caso de termos apenas uma user session, esse será o endereço dela.
unsigned long usersession_start; 

// The persistent window server.
// This is a window server embedded into the base kernel.
// It is used for the setup/installation environment and
// for some raw environment.
// kgws
struct raw_graphics_d
{
    // We can't use some routines if this window server is unavailable.
    int blocked;
    char name[32];
    // ...
};
struct raw_graphics_d    *RawGraphics;


// The loadable window server.
// It is a ring 3 application.
struct window_server_d
{
    int used;
    int magic;
    int id;
    int pid;
    int blocked;
    char name[32];
    // ...
};
struct window_server_d *WindowServer;

// The loadable window manager.
// It is a ring 3 application.
struct window_manager_d
{
    int used;
    int magic;
    int id;
    int pid;
    int blocked;
    char name[32];
    // ...
};
struct window_manager_d *WindowManager;



// This is a set of application used as
// components of a GUI.
struct desktop_environment_d
{
    int used;
    int magic;
    int id;
    int blocked;
    char name[32];

    // Maybe the current desktop environment has
    // a folder for all its components.
    // char *path;

    // Main components
    struct window_server_d   *window_server;
    struct window_manager_d  *window_manager;

    // #todo
    // List here more standard components.

    // ...
};
struct desktop_environment_d *DesktopEnvironment;




/*
 * **********************************************
 * usession_d:
 *     The user section structure. 
 *     (u.session)
 */ 

struct usession_d
{
    object_type_t   objectType;
    object_class_t  objectClass;

    struct object_d  *object;


    // SID - Session ID.
    int id;

    int used;
    int magic;

 
     // The user in this session.
    uid_t uid;

    // Initial process for this session.
    pid_t initial_pid;

    // The session leader.
    // The leader process for this process.
    // The leader has some privileges in its session.
    pid_t leader_pid;

    // #todo
    // All the process in this group will be killed when the
    // session ends.
    
    // gid_t gid;

    int initialized;

    // ??
    // What is the virtual terminal used by this session?
    // What is the virtual console used by this session?
    // This session has a terminal or console?
    
    //int tty;

    //
    //  main info
    //

    // =========================================================
    // Raw graphics system.
    // Persistent graphics system.
    // It belong to the base kernel.
    // This is all we have when the system has no
    // loadable window server installed on it.
    struct raw_graphics_d  *raw_graphics;

    // =========================================================

    // The loadable window server.
    // We will use the only the raw graphics when it is NULL.
    struct window_server_d       *window_server;

    // The loadable window manager.
    // We will use the only the raw graphics when it is NULL.
    struct window_manager_d      *window_manager;

    // The current desktop environment.
    struct desktop_environment_d *desktop_environment;

    // =========================================================


    unsigned long BeginTime;
    unsigned long EndTime;

	//
	//Lintas encadeadas de ponteiros para pool.
	//ou vetores de ponteiros para pools.
	//

    // Início da lista encadeada de ponteiros para pools.

    //unsigned long *dpHead;     //Desktop Pools.(wstations).
    //unsigned long *opHead;     //Object Pools.

    //unsigned long *pdpHead;    //Page Directory Pools. (page directory lists) 

    struct usession_d *next;
};

struct usession_d *usession0;
struct usession_d *CurrentUserSession;

// List
unsigned long usessionList[USER_SESSION_COUNT_MAX];

// Um mesmo usuário pode usar sessoes diferentes para atividades diferentes.
// -Qual é a user session do usuário logado? Sabendo a user session que o usuário está
// podemos determinar quais os pools que que estão disponíveis para ele, como pools de desktop
// pools de pagedirectory, pool de objetos...


//
// == prototypes ===============================
//


#endif    



