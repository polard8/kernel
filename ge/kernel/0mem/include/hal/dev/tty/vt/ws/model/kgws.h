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




// Send message.
// Pega um scancode, transforma em caractere e envia na forma de mensagem
// para a thread de controle associada com a janela que tem o foco de entrada.

int KGWS_SEND_KEYBOARD_MESSAGE ( unsigned char raw_byte );


// Aqui o servidor de janelas escaneia as janelas para saber 
// se o mouse está sobre alguma ... durante a rotina
// são solicitadas informações diretamente no driver de mouse ps2.
int kgws_mouse_scan_windows (void);


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


int init_gramado (void);



int KGWS_initialize(void);


#endif    



//
// End.
//

