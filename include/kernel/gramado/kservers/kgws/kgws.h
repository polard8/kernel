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
int gwsOpen();

//fechar o servidor de janelas
int gwsClose();

// Registrar um window manager.
int gwsRegisterWindowManager( int pid );

int init_gui ();


//diálogo para suportar eventos de mouse.
unsigned long
kgws_mouse_dialog ( struct window_d *window, 
				    int msg, 
				    unsigned long long1, 
				    unsigned long long2 );

void gramado();
int init_gramado();

//
// End.
//

