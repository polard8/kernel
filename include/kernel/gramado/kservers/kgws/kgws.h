/*
 * File: gws.h
 *     header for the GWS.
 *     ## GWS - Gramado Window Server ##
 *
 * History:
 *     2017 - Created by Fred Nora.
 */


//void gwsEnableTextCursor ();
//void gwsDisableTextCursor ();


//abrir o servidor de janelas. 
int gwsOpen (void);


//fechar o servidor de janelas
int gwsClose (void);


// Registrar um window manager.
int gwsRegisterWindowManager( int pid );


unsigned long
kgws_mouse_dialog ( struct window_d *window,
				    int msg,
				    unsigned long long1,
				    unsigned long long2 );


int init_gui (void);


int init_gramado (void);


//
// End.
//

