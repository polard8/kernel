
// desktop.h
// 'Virtual desktops'
// This separation is for security reason, and
// load balance reason. Its not the same definition found 
// in the window server. The kernel is not responsable
// for whatever is happening in ring3.

#ifndef __VEM_DESKTOP_H
#define __VEM_DESKTOP_H    1

struct desktop_d
{
    object_type_t   objectType;
    object_class_t  objectClass;
// DID - Desktop ID.
    int id;
    int used;
    int magic;

    uid_t uid;

// usando o mesmo esquema do usuário.
    char __name[64];
    int name_lenght;

// The window server and the window manager for this desktop.
    pid_t ws;   // window server
    pid_t wm;   // window manager
    pid_t ns;   // network server
    //pid_t fs;   // file system
    // ...

// #importante
// #quantidades
// Isso limita as quantidades que podem ser criadas em um desktop.
// permitindo o fácil gerenciamento de drivers em desktops específicos.
// Pois alguns desktops podem ter seus próprios gerenciadores de servidores.
// Como o caso do gramado core. Que fica a cargo apenas do kernel 
// gerenciar esses servidores especiais.

	unsigned int drivers_max;
	unsigned int servers_max;
	unsigned int apps_max;

// Heap do desktop.
    //struct heap_d  *heap;

//
// List of overlapped windows.
//

// Only application windows,
// that one with a frame.
    int lTail;
    int lHead;
    unsigned long list[8];

    struct room_d *room;

// Navigation
    struct desktop_d *next;
};
// #todo
// Use external reference here.
struct desktop_d  *desktop0;
struct desktop_d  *CurrentDesktop;

// List
unsigned long desktopList[DESKTOP_COUNT_MAX];


//
// == prototypes ===========================
//

// Initialization
void init_desktop_list (void);
void init_desktop (void);

void set_current_desktop ( struct desktop_d *desktop );
void *get_current_desktop (void);

int get_current_desktop_id (void);

int RegisterDesktop (struct desktop_d *d);

void *CreateDesktop (struct room_d *room);

int desktop_setup_ws ( struct desktop_d *desktop, int ws_pid );
int desktop_setup_wm ( struct desktop_d *desktop, int wm_pid );

#endif    





