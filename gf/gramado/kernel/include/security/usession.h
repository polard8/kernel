/*
 * File: usession.h
 *
 * Descrição:
 *     Header do gerenciador de user sections.
 *     
 *     WINDOW -> DESKTOP -> WINDOW STATION -> USER SECTION.
 *
 *
 * Obs: Uma estrutura de user session pode armazenas ponteiros para
 *      +Desktop Pool. (Window Station). 
 *      +Object Pool.
 *      +Page Directory Pool. 
 *
 *
 *  Tipos de usuários: 
 *     Interactive e non_interactive.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão do header.
 *     ...
 */


#ifndef ____USESSION_H
#define ____USESSION_H

 
 
//user session start
//No caso de termos apenas uma user session, esse será o endereço dela.
unsigned long usersession_start; 
 
 
/*
 * User section structure (u.session)
 */ 

struct usession_d
{

    // object control

    object_type_t objectType;
    object_class_t objectClass;

    struct object_d *object;

    // SID - Session ID.
    int id;

    int used;
    int magic;
 
    int uid; // *IMPORTANTE , ID do usuário da secção.


    int initialized;

    unsigned long BeginTime;
    unsigned long EndTime;

	//
	//Lintas encadeadas de ponteiros para pool.
	//ou vetores de ponteiros para pools.
	//
	
	//Início da lista encadeada de ponteiros para pools.
	unsigned long *dpHead;     //Desktop Pools.(wstations).
	unsigned long *opHead;     //Object Pools.
	unsigned long *pdpHead;    //Page Directory Pools. (page directory lists) 
	
	
	//Ponteiros para 8 desktop pools. (window stations).
	//pools de desktop.
	unsigned long listDesktopPool[8];
	
	//ponteiros para 8 object pools.
	//pools de objetos.
	unsigned long listObjectPool[8];
	
	//Ponteiros para 8 Page Directory Pools.
	//pools de diretório de páginas.
	unsigned long listPageDirectoryPool[8];
	
	//struct wstation_d *arrayWindowStation; //ponteiro para um array de estruturas de window station.
	
	//linked list. (a linked list da window station)
	//struct linkedlist_d *linkedlist;
	
    struct usession_d *next;	
};

struct usession_d *usession0;
struct usession_d *CurrentUserSession;


//
// Um mesmo usuário pode usar sessoes diferentes para atividades diferentes.
// -Qual é a user session do usuário logado? Sabendo a user session que o usuário está
// podemos determinar quais os pools que que estão disponíveis para ele, como pools de desktop
// pools de pagedirectory, pool de objetos...
//



unsigned long usessionList[USER_SESSION_COUNT_MAX];



//
// Protótipos das funções.
//

void init_user_session (void); 

void *CreateUserSession(int userID); 

void *get_current_user_session (void);

void open_user_session (void);

void close_user_session (void);



#endif   


//
// End.
//


