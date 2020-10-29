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


//
// End.
//

