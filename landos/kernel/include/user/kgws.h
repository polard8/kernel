/*
 * File: kgws.h
 * 
 *     header for the kGWS.
 * 
 *    kGWS - Kernel Gramado Window Server
 *
 * 
 * History:
 *     2017 - Created by Fred Nora.
 */


/*

    KGWS
    The KGWS subsystem handles all the kernel input and output.
    kgws_keyboard for keyboard input
    kgws_mouse for mouse input.

 */



#ifndef __KGWS_H
#define __KGWS_H    1


/*
#define KGWS_MAGIC 1234
#define KGWS_KEYBOARD    1000
#define KGWS_MOUSE       2000
#define KGWS_DISPLAY     3000
*/

//
// == prototypes ==========================================
//

void kgws_enable(void);
void kgws_disable(void);




// ========================================

// Sent data to keyboard tty.
// Called by UserInput_SendKeyboardMessage.
int 
sendto_tty ( 
    struct tty_d *target_tty,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte );


// Send data to event queue in a given thread structure.
// Called by UserInput_SendKeyboardMessage.
int 
sendto_eventqueue ( 
    int tid,
    struct window_d *window, 
    int message,
    unsigned long ascii_code,
    unsigned long raw_byte );



// Send message.
// Pega um scancode, transforma em caractere e envia na forma de mensagem
// para a thread de controle associada com a janela que tem o foco de entrada.

int 
UserInput_SendKeyboardMessage( 
    int tid, 
    unsigned char raw_byte );


// ==============================================




int kgwsRegisterWindowServer(int pid);


// Abrir o servidor de janelas. 
int gwsOpen (void);


//fechar o servidor de janelas
int gwsClose (void);



// Send a message to the thread associated with the
// window with focus.
// See: top/ws/kgws.c
int
kgws_send_to_controlthread_of_currentwindow ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );

int
kgws_send_to_tid ( 
    int tid, 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


int
kgws_send_to_foreground_thread ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 );


int init_gramado (void);


int KGWS_initialize(void);


#endif    



//
// End.
//

