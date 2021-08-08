

#include <kernel.h> 


/*
 ******************************************************************* 
 * __kgwm_ps2kbd_procedure:
 * 
 *       Some combinations with control + F1~F12
 */

// Local function.

// Called by kgws_event_dialog in kgws.c
// Called by si_send_longmessage_to_ws and si_send_message_to_ws
// in siws.c 
// #bugbug: We don't wanna call the window server. Not now.

// #important:
// Isso garante que o usuário sempre podera alterar o foco
// entre as janelas do kgws usando o teclado, pois essa rotina
// é independente da thread que está em foreground.

// #todo
// Talvez a gente possa usar algo semelhando quando o window
// server estiver ativo. Mas possivelmente precisaremos 
// usar outra rotina e não essa. Pois lidaremos com uma estrutura
// de janela diferente, que esta localizada em ring3.

// From Windows:
// Because the mouse, like the keyboard, 
// must be shared among all the different threads, the OS 
// must not allow a single thread to monopolize the mouse cursor 
// by altering its shape or confining it to a small area of the screen.

// #todo
// This functions is the moment to check the current input model,
// and take a decision. It will help us to compose the event message.
// It is because each environment uses its own event format.

unsigned long 
__kgwm_ps2kbd_procedure ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 )
{

// #test
// Testando uma rotina de pintura que usa escape sequence.
// Queremos que ela funcione na máquina real.
// Vamos testar os ponteiros.

// #todo
// We need the structure of the current thread.
// This way we have the current input model for this thread
// and we can compose an event for this environment.

    // struct thread_d  *t;


    char buffer[128];
    sprintf (buffer,"My super \x1b[8C string!!\n"); 

    int Status = -1;


    if (msg<0){
        return 0;
    }

    switch (msg){

        case MSG_KEYDOWN:
            switch (long1){
            case VK_TAB: printf("TAB\n"); refresh_screen(); break;
            };
            break;

        // Pressionadas: teclas de funçao
        case MSG_SYSKEYDOWN: 
            switch (long1){

                case VK_F1:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(0);
                    }
                    if (alt_status == 1){
                        printf ("__kgwm_ps2kbd_procedure: alt + f1\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        //jobcontrol_switch_console(0);
                    }
                    return 0;
                    break;

                case VK_F2:
                    if (ctrl_status == TRUE){
                         //powertrio_select_client(1);
                    }
                    if (alt_status == 1){
                        printf ("__kgwm_ps2kbd_procedure: alt + f2\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        //jobcontrol_switch_console(1);
                    }
                    return 0;
                    break;

                case VK_F3:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(2);
                    }
                    if (alt_status == 1){
                        printf ("__kgwm_ps2kbd_procedure: alt + f3\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        //jobcontrol_switch_console(2);
                    }
                    return 0;
                    break;

                case VK_F4:
                    if (ctrl_status == TRUE){
                        //powertrio_next();
                    }
                    if (alt_status == 1){
                        printf ("__kgwm_ps2kbd_procedure: alt + f4\n");
                        refresh_screen();
                    }
                    if (shift_status == 1){
                        //jobcontrol_switch_console(3);
                    }
                    return 0;
                    break;


                // Reboot
                case VK_F5:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(0);
                        //reboot();
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f5\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        //kgwm_next();
                    }
                    return 0;
                    break;

                // Send a message to the Init process.
                // 9216 - Launch the redpill application
                case VK_F6:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(1);
                        // #todo: 
                        // shutdown. Only the ring3 applications
                        // can shutdown via qemu for now. 
                        //__kgwm_SendMessageToInitProcess(9216); 
                        return 0; 
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f6\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        //kgwm_next();
                    }
                    return 0;
                    break;

                // Test 1.
                case VK_F7:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(2);
                       // Send message to init process to launch gdeshell.
                        //__kgwm_SendMessageToInitProcess(9217);
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f7\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        //kgwm_next();
                    }
                    return 0;
                    break;

                // Test 2.
                case VK_F8:
                    if (ctrl_status == TRUE){
                        //powertrio_next();
                        // Send message to init process to launch the launcher.
                        //__kgwm_SendMessageToInitProcess(9216); 
                        //__kgwm_SendMessageToInitProcess(9218);  // launch sysmon
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f8\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        //kgwm_next();
                    }
                    return 0;
                    break;

                case VK_F9:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(0);
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f9\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        // #goal
                        // This is a emergency keycombination.
                        // We can't call another process and 
                        // we want to reboot the machine.
                        sys_reboot();
                        //__kgwm_SendMessageToInitProcess(9216);  //reboot
                    }
                    return 0;
                    break;

                case VK_F10:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(1);
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f10\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        Background_initialize();
                        show_slots();
                        //pages_calc_mem();
                        refresh_screen();
                        //__kgwm_SendMessageToInitProcess(9217);  //gdeshell
                    }
                    return 0;
                    break;

                case VK_F11:
                    if (ctrl_status == TRUE){
                        //powertrio_select_client(2);
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f11\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                       hal_reboot();
                       // #bugbug: Something is wrong with this routine.
                       //__kgwm_SendMessageToInitProcess(9218);  // redpill application
                    }
                    return 0;
                    break;

                case VK_F12:
                    if (ctrl_status == TRUE){
                        //powertrio_next();
                    }
                    if (alt_status == TRUE){
                        printf ("__kgwm_ps2kbd_procedure: alt + f12\n");
                        refresh_screen();
                    }
                    if (shift_status == TRUE){
                        //__kgwm_SendMessageToInitProcess(9219);  // sysmon
                    }
                    return 0;
                    break;

                default:
                    // nothing
                    return 0;
            
            }
    };


    // #debug
    refresh_screen();
    
    return 0;
}


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














