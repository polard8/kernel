

#include <kernel.h> 


// called by init()
int init_gramado (void)
{
    debug_print ("init_gramado: [?? fixme]\n");
    return 0;
}


/*
 ***********************************
 * windowLoadGramadoIcons:
 * 
 *     Carrega alguns ícones do sistema.
 *     It's a part of the window system's initialization.
 */

int windowLoadGramadoIcons (void)
{
    unsigned long fRet=0;

	//#debug
	//printf("windowLoadGramadoIcons:\n");

	//
	//  ## Icon support ##
	//

//iconSupport:

	// Carregando alguns ícones básicos usados pelo sistema.

	// ## size ##
	// Vamos carregar ícones pequenos.
	//@todo checar a validade dos ponteiros.


    // #bugbug
    // Size determinado, mas não sabemos o tamanho dos ícones.

    // 4 pages.
    // 16 KB ? Is it enough ?
    // Sim, os ícones que estamos usam possuem no máximo 2KB.
    // See: base/

    unsigned long tmp_size = (4*4096);

    // See: window.h
    shared_buffer_app_icon       = (void *) allocPages(4);
    shared_buffer_file_icon      = (void *) allocPages(4);
    shared_buffer_folder_icon    = (void *) allocPages(4);
    shared_buffer_terminal_icon  = (void *) allocPages(4);
    shared_buffer_cursor_icon    = (void *) allocPages(4);
    // ...


    if ( (void *) shared_buffer_app_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_app_icon\n");
    }

    if ( (void *) shared_buffer_file_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_file_icon\n");
    }

    if ( (void *) shared_buffer_folder_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_folder_icon\n");
    }

    if ( (void *) shared_buffer_terminal_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_terminal_icon\n");
    }

    if ( (void *) shared_buffer_cursor_icon == NULL ){
        panic ("windowLoadGramadoIcons: shared_buffer_cursor_icon\n");
    }

	//
	// Load
	//

    // app icon
    fRet = (unsigned long) fsLoadFile ( 
                               VOLUME1_FAT_ADDRESS,
                               VOLUME1_ROOTDIR_ADDRESS, 
                               FAT16_ROOT_ENTRIES,
                               "APP     BMP", 
                               (unsigned long) shared_buffer_app_icon,
                               tmp_size );
    if ( fRet != 0 ){
        panic ("windowLoadGramadoIcons: APP.BMP\n");
    }

    // file icon
    fRet = (unsigned long) fsLoadFile ( 
                               VOLUME1_FAT_ADDRESS,
                               VOLUME1_ROOTDIR_ADDRESS, 
                               FAT16_ROOT_ENTRIES, 
                               "FILE    BMP", 
                               (unsigned long) shared_buffer_file_icon,
                               tmp_size );
    if ( fRet != 0 ){
        panic ("windowLoadGramadoIcons: FILE.BMP\n");
    }

    // folder icon
    fRet = (unsigned long) fsLoadFile ( 
                               VOLUME1_FAT_ADDRESS, 
                               VOLUME1_ROOTDIR_ADDRESS, 
                               FAT16_ROOT_ENTRIES,
                               "FOLDER  BMP", 
                               (unsigned long) shared_buffer_folder_icon,
                               tmp_size );
    if ( fRet != 0 ){
        panic ("windowLoadGramadoIcons: FOLDER.BMP\n");
    }

    // terminal icon
    fRet = (unsigned long) fsLoadFile ( 
                               VOLUME1_FAT_ADDRESS, 
                               VOLUME1_ROOTDIR_ADDRESS, 
                               FAT16_ROOT_ENTRIES, 
                               "TERMINALBMP", 
                               (unsigned long) shared_buffer_terminal_icon,
                               tmp_size );
    if ( fRet != 0 ){
        panic ("windowLoadGramadoIcons: TERMINAL.BMP\n");
    }


    // cursor icon
    fRet = (unsigned long) fsLoadFile ( 
                               VOLUME1_FAT_ADDRESS, 
                               VOLUME1_ROOTDIR_ADDRESS, 
                               FAT16_ROOT_ENTRIES,
                               "CURSOR  BMP", 
                               (unsigned long) shared_buffer_cursor_icon,
                               tmp_size );
    if ( fRet != 0 ){
        panic ("windowLoadGramadoIcons: CURSOR.BMP\n");
    }

	// More ?

    return 0;
}




// Get a shared buffer to a system icon.
// it is gonna be used by the window server.
// It is a pre allocated buffer containg an bmp icon loaded at it.
// Service 9100

void *ui_get_system_icon ( int n )
{
    if (n <= 0){ return NULL; }

    // See: window.h
    switch (n){

    case 1: return (void *) shared_buffer_app_icon;       break;
    case 2: return (void *) shared_buffer_file_icon;      break;
    case 3: return (void *) shared_buffer_folder_icon;    break;
    case 4: return (void *) shared_buffer_terminal_icon;  break;
    case 5: return (void *) shared_buffer_cursor_icon;    break;
    // ...
    };

    return NULL;
}














