// ws.h
// Window system support.
// Colors and color scheme.
// Created by Fred Nora.

#ifndef __DISPLAY_WS_H
#define __DISPLAY_WS_H    1


// ===============================================================

struct ws_info_d
{
    int initialized;

// Process info
    pid_t pid;
    int pid_personality;

// Thread indo
    tid_t tid;
};
// see: graphics.c
extern struct ws_info_d  WindowServerInfo;

// ===============================================================

// # Principais variáveis globais #
// This is not the right place for them.

// see: graphics.c
extern int current_display; 
extern int current_screen;
extern int guiStatus;
// Status de ambientes gráficos.
extern int logonStatus;              //Logon status.
extern int logoffStatus;             //Logoff status.
extern int userenvironmentStatus;    //User environment status.

extern unsigned long g_system_color;
extern unsigned long g_char_attrib;
// LFB - address for kernel graphic mode
extern unsigned long g_kernel_lfb; 
//video mode
extern unsigned long g_current_vm;          //video memory
extern unsigned long g_current_video_mode;  //video mode
//status do cursor.
//se ele deve aparecer e piscar ou não.
extern int g_show_text_cursor;
//status: aceso ou apagado.
//0=apaga 1=acende.
extern int textcursorStatus;      
extern unsigned long g_mousepointer_x;
extern unsigned long g_mousepointer_y;

//
// == window server ==================================================
//

// #todo:
// Change this term to display server.
// types of window server.
typedef enum {
    WindowServerTypeNull,
    WindowServerTypeEmbedded,       // Embedded inside the base kernel.
    WindowServerTypeRing0Process,
    WindowServerTypeRing3Process
    // ...
    // #todo
    //DisplayServerTypeNull,
    //DisplayServerTypeEmbedded,       // Embedded inside the base kernel.
    //DisplayServerTypeRing0Process,
    //DisplayServerTypeRing3Process
    // ...
} window_server_t;
//} display_server_t;

// The window server struct.
// Here we will find all the info we need about the window server
// that the system is using in the moment. Things like, name, pid ... 
// The system is able to run only one window server.
// We can select one window server per cgroup.
// The window server is a ring3 process.
// The system also have an embedded window server inside the base kernel.
// Maybe we will create different kinds of window server in the future,
// but this is gonna be the struct for then all. Only one structure.


// #todo:
// maybe the window server can be an kind of device
// and we can use the file dev/ws to setup the properties.
// and use ioctl.


// #bugbug
// Estamos com problemas na hora dos aplicativos pegarem 
// informaçoes que estao dentro de estruturas do kernel.
// Por isso suspendemos essa estrutura por enquanto.
// Leia as notas de design.

//struct window_server_d
//{
    // #bugbug
    // It works fine on qemu.
    // But we lost all these values when testing on my real machine. 
    // Why?
    // ps: We are using the embedded command, 'metrics' on gdeshell.
    // Maybe the problem is in the gdeshell application.

    int WindowServer_initialized;
    
    window_server_t WindowServer_type;  // tipo de window server.
    
    // the pid for loadable window servers.
    // When the window server is the embedded so this pid needs to be
    // the pid of the kernel process.
    
    pid_t WindowServer_pid; 
    //struct cgroup_d *cgroup;  // The cgroup associated with the ws. (display server)

    // Limiting the nale to 64.
    char WindowServer_name[64];

    //file *ws_file;
    
    // the virtual console used by this window server.
    int WindowServer_virtual_console;
    
    //no navigation.
//};
//static struct window_server_d WindowServer;


//
// == prototypes ==============================================
//

int ws_init (void);

int 
ws_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg );

void ws_show_info(void);

#endif    
















