
// Talvez todas as rotinas de tratamento ter�o seus wrappers 
// em sci/sys/.

/*
 * File: sci/gde_serv.c 
 *
 * 
 *       (SCI) = SYSTEM CALL INTERFACE
 *
 * Esse � o arquivo principal da sci.
 *
 *       GERENCIA OS SERVI�OS OFERECIDOS PELAS INTERFACES /sys.h E /system.h.   
 *
 * Obs: Todas as rotinas chmadas por esse m�dulo devem vir apenas das interfaces
 * /sys.h e /system.h.
 *
 *
 * In this file:
 *   + services (main function)
 *   + servicesPutChar
 *   + pty_send_message_to_thread
 *   + serviceCreateWindow
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     2016 - Revision.
 *     2017 - Revision.
 *     //...
 */


#include <kernel.h>


//
// Constantes internas.
//

//#BUGBUG
// Esse m�ximo de servi�os para a interrup��o 200 n�o existir� mais.
// um n�mero grande de servi�os poder� ser atendido por essa interup��o,
// esses 255 servi�os s�o os servi�os que ser�o atendidos em kernel mode
// aqui no kernel base.
#define SERVICE_NUMBER_MAX 255


//
// Vari�veis internas.
//

//int servicesStatus;
//int servicesError;
//...

// Create Window support.
int cwFlag;                //flag (alerta que os argumentos est�o dispon�veis)
unsigned long cwArg1;      //WindowType
unsigned long cwArg2;      //WindowStatus
unsigned long cwArg3;      //WindowView
char *cwArg4;              //WindowName
unsigned long cwArg5;      //WindowX
unsigned long cwArg6;      //WindowY
unsigned long cwArg7;      //WindowWidth
unsigned long cwArg8;      //WindowHeight
struct window_d * cwArg9;  //gui->screen Parent window
int  cwArg10;               // desktopID 
unsigned long cwArg11;     // WindowClientAreaColor
unsigned long cwArg12;     // WindowColor



//
// ====
//

void *
gde_extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


// Services abouve 256.
void *
gde_extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    // #todo
    // Talvez precisaremos disso e do argumento
    // que passe o endere�o do buffer.
    // unsigned long *msg = (unsigned long *) buffer;


	//generic file pointer
    file *__fp;

	//bmp file pointer.
    file *__bmfp;


    //Deprecated.
    //Outro n�mero fará esse trabalhao.
    if ( number == 260 ){
        return (void *) sys_read ( (unsigned int) arg2, 
                            (char *) arg3, (int) arg4 );
    }
     
    //Deprecated.
    //Outro n�mero fará esse trabalhao.
    if ( number == 261 ){
        return (void *) sys_write ( (unsigned int) arg2, 
                            (char *) arg3, (int) arg4 );
    }



    // read on virtual console!
    // range: 0 ~ 3
    // chamado por read_VC em ring3.
    // IN: fd, buf, count

    if ( number == 262 ){
        return (void *) console_read ( (int) arg2, 
                            (const void *) arg3, (size_t) arg4 );
    }


    // write on virtual console!
    // range: 0 ~ 3
    // chamado por write_VC em ring3.
    // IN: fd, buf, count
    
    if ( number == 263 ){
        return (void *) console_write ( (int) arg2, 
                            (const void *) arg3, (size_t) arg4 );
    }



    // yield the current thread.
    // O seu tempo rodando vai para perto do fim.
    if (number == 265){
        //todo: debug_print
        yield (current_thread);
        return NULL;
    }


    // Pega o n�mero da tty de um processo, dado o pid.
    // ps/action/process.c
    // IN: PID.
    // OUT: tty id.
    if (number == 266){
        return (void *) process_get_tty ( (int) arg2 );
    }


    // Ligar duas tty, dados os pids dos processos que possuem as tty.
    // tty/pty.c
    // IN: master pid, slave pid.
    if (number == 267){
        return (void *) pty_link_by_pid ( (int) arg2, (int) arg3 );
    }
    

    // deprecated
    if (number == 268){ return NULL; }
    // deprecated
    if (number == 269){ return NULL; }



    // Create a terminal given the window.
    // IN: window, father's pid.
    if ( number == 270 ){
         return (void *) vt_create ( (struct window_d *) arg2, 
                             (int) arg3 );
    }
    
    
    // Set child pid given in a vt structure.
    // Only the father will configurate this thing.
    // IN: window, child's pid
    if ( number == 271 ){
         return (void *) vt_set_child ( (struct window_d *) arg2, 
                             (int) arg3 );
    }


    // Channel is a file descriptor in the file list 
    // of the current process.
    // IN: fd, buf, count.         
    if (number == 272){
           return (void *) tty_read ( (unsigned int) arg2,   //channel 
                               (char *) arg3,                //buf
                               (int) arg4 );                 //nr
    }


    // Channel is a file descriptor in the file list 
    // of the current process.
    // IN: fd, buf, count.         
    if (number == 273){
        return (void *) tty_write ( (unsigned int) arg2,  //channel 
                            (char *) arg3,                //buf
                            (int) arg4 );                 //nr
    }


    // Get current virtual console.
    if (number == 277 ){
        return (void *) console_get_current_virtual_console ();
    }

    // Set current cirtual console.
    // #todo: precisa de privilégio. 
    if (number == 278 ){
        console_set_current_virtual_console ( (int) arg2 );
        return NULL;
    }
    

    // Update window.
    // Atualiza a �rea de cliente enviando uma mensage MSG_PAINT.
    // Isso funcionou.
    if ( number == 279 ){
        windowUpdateWindow ( (struct window_d *) arg2 );
        return NULL;
    }


    // Returns the current runlevel.
    if ( number == 288 ){
        return (void *) current_runlevel;
    }
    

    // Serial debug print.
    // See: sci/sys/sys.c
    if ( number == 289 ){
        return (void *) sys_serial_debug_printk ( (char *) arg2 );
    }


    /*    
    // memory size
    // baseado no valor passado pelo bl.bin
    unsigned long __mm_size_mb = 0;
    if ( number == 292 )
    {
		//see gdef.h
		// ( (adress/1024)/1024) MB
        __mm_size_mb = ( (blSavedLastValidAddress/0x400) / 0x400 );
   
        return (void *) __mm_size_mb;
    }
    */

    unsigned long __mm_size_mb = 0;
    if ( number == 292 ){
        __mm_size_mb = ( memorysizeTotal/0x400);
        return (void *) __mm_size_mb;
    }
    
    
    // #bugbug: cuidado.
    // get boot info.
    // See: info.c
    // IN: index to select the info.
    
    if ( number == 293 ){
        return (void *) info_get_boot_info ( (int) arg2 );
    }


    // Updates a status bar of a given window.
    // #deprecated. Delete!
    if ( number == 300 )
    {
        return (void *) UpdateStatusBar ( (struct window_d *) arg2, 
                            (unsigned char *) arg3, 
                            (unsigned char *) arg4 );
    }
    
    
    /*
    // Close a process, given it's pid and the exit code.
    if ( number == 333 )
    {
        //#todo: Criar um request que chamar� exit_process(...)
        return NULL;
    }
    */
    
    
    // Inicializar ou reinicializar componentes do sistema
    // depois da inicialização completa do kernel.
    // Isso poderá ser chamado pelo init.bin, pelo shell
    // ou qualquer outro.
    if ( number == 350 ){
        return (void *) sys_initialize_component ((int) arg2);
    }
    
    
    // 377 - todo: implement uname() libc support.
    if ( number == 377 ){
        printf ("service 377: uname. [todo] \n");
        sys_uname ( (struct utsname *) arg2 );        
        refresh_screen();
    }
    
    
    struct window_d *__window;
    
    //veja se essa � overlapped.
    if (number == 400)
    {
		//#bugbug todo: fazer checks
        
        __window = (struct window_d *) windowList[arg2];
        
        if ( __window->type == WT_OVERLAPPED )
        {
			return (void *) 1;
        }
        return (void *) 0;		
    }

    //pega o ponteiro de um janela.
    if (number == 401)
    {
		//#bugbug todo: fazer checks
        return (void *) windowList[arg2];
    }


    //usado por 4 fun��es logo abaixo.
    struct desktop_d *__desktop;
    
	// 512 - get ws PID for a given desktop
    if ( number == SYS_GET_WS_PID )
    {
        // pega o wm de um dado desktop.
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                return (void *) __desktop->ws; 
            }
        }
        return NULL; //#bugbug: Isso pode significar pid 0.
    }


	// 513 - set ws PID for a given desktop
	// Register a window server.
	// gramado_ports[11] = ws_pid

    if ( number == SYS_SET_WS_PID )
    {
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                __desktop->ws = (int) arg3;
                
                
                // What is the process listen to the port 11.
                gramado_ports[GRAMADO_WS_PORT] = (int) current_process;
                
                // returning ok.
                // But, we could return the port number.
                return (void *) 1;  //ok 
            }
        }
        return NULL; //fail
    }    
    
	// 514 - get wm PID for a given desktop
	// IN: desktop
    if ( number == SYS_GET_WM_PID )
    {
        // pega o wm de um dado desktop.
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                return (void *) __desktop->wm; 
            }
        }
        return NULL; //#bugbug: Isso pode significar pid 0.
    }


	// 515 - set wm PID for a given desktop
	// IN: desktop, pid
    if ( number == SYS_SET_WM_PID )
    {
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                 __desktop->wm = (int) arg3;
                return (void *) 1;  //ok 
            }
        }
        return NULL; //fail
    }



    // 516 - show x server info
    // ws para o desktop atual
    if ( number == SYS_SHOW_X_SERVER_INFO )
    {
        kprintf ("516: ws PID=%d \n", CurrentDesktop->ws );
        refresh_screen ();
        return NULL;
    }



    // 517 - show wm info
    // wm para o desktop atual
    if ( number == SYS_SHOW_WM_INFO ){
        kprintf ("window manager info: PID=%d \n", CurrentDesktop->wm);
        refresh_screen ();
        return NULL;
    }


    // Repinta todas as janelas que foram invalidadas.
    // Isso ser� usado pelo compositor do window server. 
    // Ou pelo window manager.
    if ( number == 518 ){
        redraw_screen();
        return NULL;
    }

    // get current desktop
    if (number == 519){
        return (void *) CurrentDesktop;
    }

    // network server
	// 520 - get ns PID for a given desktop
    if ( number == 520 )
    {
        // pega o wm de um dado desktop.
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                return (void *) __desktop->ns; 
            }
        }
        return NULL; //#bugbug: Isso pode significar pid 0.
    }

    // network server
	// 521 - set ns PID for a given desktop
	// Register a window server.
	// gramado_ports[11] = ws_pid

    if ( number == 521 )
    {
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->desktopUsed == 1 && 
                 __desktop->desktopMagic == 1234 )
            {
                __desktop->ns = (int) arg3;
                
                
                // What is the process listen to the port 11.
                gramado_ports[GRAMADO_NS_PORT] = (int) current_process;
                
                // returning ok.
                // But, we could return the port number.
                return (void *) 1;  //ok 
            }
        }
        return NULL; //fail
    }    


    // ??
    // setup net buffer for a process.
    struct process_d *__net_process;
    if (number == 550)
    {
        __net_process = (struct process_d *) processList[arg2];
        if ( (void *) __net_process != NULL )
        {
             if ( __net_process->used == 1 && 
                  __net_process->magic == 1234 )
             {
                 __net_process->net_buffer = (char *) arg3;
                 return (void *) 0;
             }
        }
        //?? fail
        return (void *) -1;
    }



    // 600 - dup
    if ( number == 600 ){
        return (void *) sys_dup ( (int) arg2 );
    }

    // 601 - dup2
    if ( number == 601 ){
        return (void *) sys_dup2 ( (int) arg2, (int) arg3 );
    }

    // 602 - dup3
    if ( number == 602 ){
        return (void *) sys_dup3 ( (int) arg2, (int) arg3, (int) arg4 );
    }
    
    
    // 603 - lseek support.
    // See: unistd.c
    // IN: fd, offset, whence.
    if ( number == 603 ){
        return (void *) sys_lseek ( (int) arg2, 
                            (off_t) arg3, (int) arg4 );
    }
 

    // 620
    // process_execve.
    // Uma implementação de execve que roda um novo programa
    // usando o processo atual e o endereço físico atual
    // da imagem.
    // IN: name, argv, envp.
    if (number == 620){
        return (void *) process_execve ( (const char *) arg2,  // pathname 
                            (const char *) arg3,               // argv
                            (const char *) arg4 );             // envp
    }

    
    
    struct desktop_d *_Desktop;
    
	// 714 - get ws PID
	// IN: desktop
    if ( number == 714 )
    {
        // pega o ws de um dado desktop.
        _Desktop = ( struct desktop_d *) arg2;
        if ( (void *) _Desktop != NULL )
        {
            if ( _Desktop->desktopUsed == 1 && 
                 _Desktop->desktopMagic == 1234 )
            {
                return (void *) _Desktop->ws; 
            }
        }
        return NULL; //#bugbug: Isso pode significar pid 0.
    }


	// 715 - set ws PID
	// IN: desktop, pid
    if ( number == 715 )
    {
        _Desktop = ( struct desktop_d *) arg2;
        if ( (void *) _Desktop != NULL )
        {
            if ( _Desktop->desktopUsed == 1 && 
                 _Desktop->desktopMagic == 1234 )
            {
                 _Desktop->ws = (int) arg3;
                return (void *) 1;  //ok 
            }
        }
        return NULL; //fail
    }

 
    // Show device list.
    if (number == 770){
        systemShowDevicesInfo ();
        return NULL;
    }
    
    // cpu usage for idle thread.
    if (number == 777){
        return (void *) profiler_percentage_idle_thread;
    }
    
 
    /*
    //arp request test.
    if ( number == 800 )
    {   
		return (void *) 0;
    }
    */

    
    //get host name
    if ( number == 801 ){
        return (void *) __gethostname ( (char *) arg2);
    }

    //set host name
    if ( number == 802 ){
        return (void *) __sethostname ( (const char *) arg2); 
    }

    //get user name
    if ( number == 803 ){
        return (void *) __getusername ( (char *) arg2);
    }

    //set user name
    if ( number == 804 ){
        return (void *) __setusername ( (const char *) arg2); 
    }


    // #todo
    // supporting ptsname libc function
    // get_ptsname
    // IN: fd do master, buffer em ring3 para o nome, buflen
    //
    if ( number == 808 ){
        return (void *) __ptsname ( (int) arg2, 
                            (char *) arg3, (size_t) arg4  ); 
    }
    
    //#todo
    //supporting ptsname_r libc function
    //IN: fd do master, buffer e buflen.
    if ( number == 809 ){
        return (void *) __ptsname ( (int) arg2, 
                            (char *) arg3, (size_t) arg4  ); 
    } 

    // Deprecated!
    if ( number == 810 )
    {
        debug_print ("gde_serv.c: [810] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if ( number == 811 )
    {
        debug_print ("gde_serv.c: [811] Deprecated\n");
        return NULL;
    }


    // Get process stats given pid
    // IN: pid, number
    if ( number == 880 )
    {
       return (void *) __GetProcessStats ( (int) arg2, (int) arg3 );
    }

    // get thread stats given tid
    // IN: tid, number
    if ( number == 881 ){
        return (void *) __GetThreadStats ( (int) arg2, (int) arg3 );
    }


    // Get process name
    if ( number == 882 ){
        return (void *) getprocessname ( (int) arg2, (char *) arg3);
    }


    // Get thread name
    if ( number == 883 ){
        return (void *) getthreadname ( (int) arg2, (char *) arg3);
    }

 
     //890 ~ 899 network stuff 
    
    // 890 - get network buffer
    // O usuário recebe um buffer com um pacote.
    if ( number == 890 ){
        //ubuf,len
        return (void *) sys_network_receive ( (void *) arg2,(int) arg3);
    }

    //891 - set network buffer
    // o usuário envia um buffer com um pacote.
    if ( number == 891 ){
        //ubuf,len
        return (void *) sys_network_send ( (void *) arg2,(int) arg3);
    }

    //...

	// 900
	// Clona e executa o filho dado o nome do filho.
	// O filho inicia sua execução do início da imagem.
	// #bugbug: Isso às vezes falha na máquina real.
	// #todo: Use more arguments.
	// See: See: ps/action/clone.c

    // IN: name, dir address.
    if ( number == 900 ){

        return (void *) clone_and_execute_process( 
                            (char *) arg2 );
    }


    // 901
    // Trying another fork() implementation. 
    // Nothing for now.
    if ( number == 901 ){ return NULL; }
    
    // get screen window.
    // #todo. checar validade
    if ( number == 955 ){
        return (void *) gui->screen;
    }    

    if ( number == 956 ){
        return (void *) gui->background;
    } 
    
    // get main window.
    // #todo. checar validade
    if ( number == 957 ){
        return (void *) gui->main;
    }    


    // O processo está se comunicando com o driver de rede.
    // Um descritor de soquete é enviado via argumento.
    if ( number == 967 )
    {
        return (void *) network_procedure ( NULL,
                            (int) 2000, //envie dados para o processo.
                            (unsigned long) arg2,   //fd
                            (unsigned long) arg3 );  //fd
    }
    

    // 968 - Testing network.
    if (number == 968){
        network_test();
        return NULL;
    }


    // 970 - Create request.
    // A interrupção n�o conseguir� retornar para a mesma thread.
    // Chamar� o scheduler por conta pr�pria;
    // IN: reson, reason
    if ( number == 970 )
    {
            create_request ( (unsigned long) 15, // number 
                (int) 1,                             // status 
                (int) 0,                             // timeout. 0=imediatamente.
                (int) current_process,               // target_pid
                (int) current_thread,                // target_tid
                NULL,                                // window 
                (int) 0,                             // msg  
                (unsigned long) arg2,                // long1  
                (unsigned long) arg3 );              // long2
                
		//wait_for_a_reason ( current_thread, (int) arg2 );
        return NULL;
    }


    // Deprecated!
    if ( number == 1000 ){
        debug_print ("gde_serv.c: [1000] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if ( number == 1002 ){
        debug_print ("gde_serv.c: [1002] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if ( number == 1003 ){
        debug_print ("gde_serv.c: [1003] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if ( number == 1004 ){
        debug_print ("gde_serv.c: [1004] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if ( number == 1005 ){
        debug_print ("gde_serv.c: [1005] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if ( number == 1006 ){
        debug_print ("gde_serv.c: [1006] Deprecated\n");
        return NULL;
    }

    // Deprecated!
    if (number == 1008){
        debug_print ("gde_serv.c: [1008] Deprecated\n");
        return NULL;
    }
    
    
    
    /*
    // retorna o id da tty do processo atualatual.
    // todo criar uma função para isso.
    struct process_d * __P;
    if (number == 1009)
    {
        __P = (struct process_d *)processList[current_process];

        return (void *) __P->tty->index;
    }
    */


     // api - load file (string ???)
     // #todo: Tem que retornar algum identificador para a api.
     // poderia ser um indice na tabela de arquivos abertos pelo processo.
     // #todo: rever.
     // See: kstdio.c
    if ( number == 4002 ){
        return (void *) k_fopen ( (const char *) arg2, "r+" );
    }


    //api - load file (string ??)
    //#todo: Tem que retornar algum identificador para a api.
    //#bugbug: Podemos retornar o endere�o base. Isso pode dar problemas?
    if ( number == 4003 ){
        panic ("service 4003: bugbug\n");
        //__fp = kernel_fopen ( (const char *) arg2, "r+" );
        //return (void *) __fp->_base;
    }
    
    //#test ok
    //Load path. ex: "/BOOT/BM.BIN"
    //See: fs.c
    if ( number == 4004 )
    {
        debug_print ("service 4004:\n");
        sys_load_path ( (unsigned char *) arg2, (unsigned long) arg3 );
        refresh_screen();
        return NULL;
    }
    
    // fstat support.
    // 
    if ( number == 4005 )
    {
        debug_print ("service 4005: [TODO]\n");
        
        //#todo
        //IN: fd, stat struct pointer.
        //xxx?( (int) arg2, (struct stat *) arg3 );
        return NULL;
    }
    
    // Show root files system info.
    if ( number == 4444 ){
        fs_show_root_fs_info();
        return NULL;
    }
    


    //7000 ~ 7020 for network sockets
    
        
    // socket() 
    // See: socket.c
    // family, type, protocol
    if ( number == 7000 ){
        return (void *) sys_socket ( (int) arg2, (int) arg3, (int) arg4 );
    }

    
    // connect()
    // fd, sockaddr struct pointer, addr len.
    if ( number == 7001 ){
        return (void *) sys_connect ( (int) arg2, 
                            (const struct sockaddr *) arg3,
                            (socklen_t) arg4 );

    }
    
    
    // accept()
    // fd, sockaddr struct pointer, addr len pointer.
    if ( number == 7002 ){
        return (void *) sys_accept ( (int) arg2, 
                            (struct sockaddr *) arg3, 
                            (socklen_t *) arg4 ); 
    }

    // bind()
    // fd, sockaddr struct pointer, addr len.
    if ( number == 7003 ){
        return (void *) sys_bind ( (int) arg2, 
                            (const struct sockaddr *) arg3,
                            (socklen_t) arg4 );

     }
    
    
    // listen()
    // fd, backlog
    if ( number == 7004 ){
        return (void *) sys_listen ( (int) arg2, (int) arg3 );  
    }
    

    // See: net/socket.c
    // IN: índice em p->accept[i].
    if (number == 7005){
        return (void *) sys_accept_sender ( (int) arg2 );  
    }
    
    
    // Salvar um pid em uma das portas.
    // IN: gramado port, PID
    if (number == 7006){
        return (void *) socket_set_gramado_port( (int) arg2, (int) arg3 );
    }

    // sys_getsockname()
    // fd, sockaddr struct pointer, addr len.
    if ( number == 7007 ){
        return (void *) sys_getsockname ( (int) arg2, 
                            (struct sockaddr *) arg3,
                            (socklen_t *) arg4 );

     }
    
    
    //socket info
    //IN: pid
    if ( number == 7008 ){
        show_socket_for_a_process( (int) arg2 );
        return NULL;
    }
    
    // libc: shutdown() IN: fd, how
    if ( number == 7009 ){
        sys_socket_shutdown( (int) arg2, (int) arg3 );
        return NULL;
    }
    
    //...
    
        

    // ioctl ()
    // IN: fd, request, arg
    // See: sci/sys/sys.c    
    
    if ( number == 8000 ){
        return (void *) sys_ioctl ( (int) arg2, 
                            (unsigned long) arg3, 
                            (unsigned long) arg4 );
    }

    // fcntl()
    // See: sci/sys/sys.c    
    if ( number == 8001 ){
        return (void *) sys_fcntl ((int) arg2, 
                            (int) arg3, 
                            (unsigned long) arg4 );
    }
    
    
    // Mostra a lista de volumes montados.
    if (number == 8500){
        fs_show_mounted_list();
        return NULL;
    }


    
    // #test
    // [FAIL]
    //Special loader to load a file into a shared memory;
    //this way we load a bmp in an address that ring3 apps can read.
    //ex: See: bg_load_image: at ws/bg.c
    //void *buf_to_r3;
    /*
    if(number == 9000)
    {
         
         buf_to_r3 = (void*) allocPages (50); //50*4 = 200KB
 
         //OUT: status
         fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                      VOLUME1_ROOTDIR_ADDRESS, 
                      (unsigned char*) arg2, //name 
                       (unsigned long) buf_to_r3 ); //shared address.
        
        //return the shared address
        return (void *) buf_to_r3;
    }
    */



    //test
    //raise window.
    if ( number == 9700 ){
        return (void *) raise_window ( (struct window_d *) arg2 );
    }

    //ps2 mouse controller dialog
    // msg, long1, long2
    if ( number == 9800 ){
        return (void *) ps2_mouse_dialog ( (int) arg2, 
                            (unsigned long) arg3, 
                            (unsigned long) arg4 );
    }
 
    //button down
    //quando um bot�o � clicado ou pressionado,
    //ele ser� repintado com a apar�ncia de bot�o apertado.
    if ( number == 9900 ){
        return (void *) button_down ( (struct window_d *) arg2 );
    }

    //#todo button_up
    if ( number == 9901 ){
        return (void *) button_up ( (struct window_d *) arg2 );
    }
 
    // chamado por gde_get_pid na api.
    // See: system.c
    if ( number == 9999 ){
        return (void *) system_get_pid ( (int) arg2 );
    }


//fail
    return NULL;  
}



/*
 ****************************************
 * gde_services:
 *     Rotina que atende os pedidos feitos pelos aplicativos em user mode 
 *     via int 200. Ou ainda o kernel pode chamar essa rotina diretamente.
 *     S�o v�rios servi�os.
 *
 *
 * Obs: 
 * TODOS OS SERVI�OS DESSA ROTINA PODEM CHAMAR ROTINAS DE CLASSES 'system.x.x'.
 *
 * @todo: 
 *    Pode haver algum tipo de autoriza��o para essa rotina.
 *    Ou ainda, autoriza��o por grupo de servi�os. Sendo os servi�os
 *    de i/o os de maior privil�gio.
 *
 *    +Identificar o processo que fez a chamada e i/o e
 *    configurar a vari�vel que identifica esse processo.
 *    'caller_process_id' � uma vari�vem encapsulada em process.c
 *    'set_caller_process_id(int pid)' configura a vari�vel.
 *
 *    Uma chamada como OpenDevice pode liberar o acesso
 *    para um determinado processo e CloseDevice cancela o acesso.  
 * 
 *    @todo: O Nome da fun��o, para pertencer � essa pasta, deveria ser:
 *           servicesSystemServices(....).
 *
 *@todo: *importante: Essa rotina deve identificar quem est� chamando, PID TID.
 *
 *
 * *IMPORTANTE:
 *  DEPENDEND DO N�MERO DO SERVI�O ELE PODER� SER TRATADO EM OUTRO ARQUIVO
 *  E N�O NO KERNEL BASE.
 */


void *
gde_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    // Para strings
    char *aa2 = (char *) arg2;
    char *aa3 = (char *) arg3;
    char *aa4 = (char *) arg4;

    // Array de longs.
    unsigned long *a2 = (unsigned long*) arg2;
    unsigned long *a3 = (unsigned long*) arg3;
    unsigned long *a4 = (unsigned long*) arg4;



    int desktopID=0;

	// Window stuffs:
    struct window_d *hWnd;
    struct window_d *focusWnd;   //Janela com foco de entrada.
    unsigned long WindowColor = COLOR_WINDOW;  
    unsigned long WindowClientAreaColor = COLOR_WINDOW;  


	//Window.
    hWnd = (void *) arg2;


	//
	// Message
	//

	//o endere�o do array passado pelo aplicativo
	//usaremos para enviar uma mensagem com 4 elementos.
    unsigned long *message_address = (unsigned long *) arg2;


    // Counter and size.
    
    int __len;  //usado para strings.
    int __i;    //usado na string


    // Profiler
    // Counting interrupt of this type. 
    // system interrupt. (0x80)

    g_profiler_ints_gde_services++;



	// ================================
	// Color scheme.

    if ( (void *) CurrentColorScheme == NULL ){
        panic ("gde_services: CurrentColorScheme");
 
    }else{

        if ( CurrentColorScheme->used != 1 || 
             CurrentColorScheme->magic != 1234 )
        {
            debug_print ("gde_services: CurrentColorScheme \n");
            panic ("gde_services: CurrentColorScheme");
        }
        
        WindowColor = CurrentColorScheme->elements[csiWindowBackground]; 
        WindowClientAreaColor = CurrentColorScheme->elements[csiWindow]; 
    };

	// ================================
	// Desktop ID.

    desktopID = (int) get_current_desktop_id ();


	// ================================
	// main window

    if (gui->main == NULL){
        debug_print ("gde_services: gui->main\n");
        panic ("gde_services: gui->main");
    }



    //
    // =====================================
    // ===============  Special ============
    // =====================================
    //

    if ( number > 256 ){
        return (void *) gde_extra_services ( number, 
                            arg2, arg3, arg4 );
    }



	// Normal services.
	// 0~256

    switch (number)
    {
        // 0 - Null, O processo pode ser malicioso.
        case SYS_NULL: 
            return NULL;
            break; 

        // 1 (i/o) Essa rotina pode ser usada por 
        // um driver em user mode.
        case SYS_READ_LBA: 
            my_read_hd_sector ( (unsigned long) arg2, 
               (unsigned long) arg3, 0 , 0 ); 
            break;


        // 2 (i/o) Essa rotina pode ser usada por 
        // um driver em user mode.
        case SYS_WRITE_LBA: 
            my_write_hd_sector ( (unsigned long) arg2, 
                (unsigned long) arg3, 0 , 0 ); 
            break;


        // 3 
        // Carregar um arquivo do disco para a mem�ria.
        // See: fs/fs.c

        // IN: name, flags, mode
        case SYS_READ_FILE:
            return (void *) sys_read_file ( (char *) a2, 
                                (int) arg3, (mode_t) arg4 ); 
            break;



        // 4 
        // Save file.
        // See: fs/fs.c
        // IN: name, size in sectors, size in bytes, adress, flag.
        case SYS_WRITE_FILE:
            sys_write_file ( (char *) message_address[0],  
                (unsigned long) message_address[1],   
                (unsigned long) message_address[2],  
                (char *) message_address[3],  
                (char) message_address[4] );  
            break;


        // 5
        // See: sci/sys/sys.c 
        case SYS_VSYNC:
            sys_vsync (); 
            return NULL;
            break;

        // 6 - Put pixel. 
        // Coloca um pixel no backbuffer.
        // Isso pode ser usado por um servidor. 
        // cor, x, y, 0.
        // todo: chamar kgws_backbuffer_putpixel
        case SYS_BUFFER_PUTPIXEL:
            backbuffer_putpixel ( (unsigned long) a2, 
                (unsigned long) a3, (unsigned long) a4, 0 ); 
            break;

		// 7
		// desenha um char no backbuffer.
		// Obs: Esse funciona, n�o deletar. :)
		// (x,y,color,char)
		// (left+x, top+y,color,char)
		// devemos usar o left e o top da janela com foco de entrada.
        //
		// Obs: A biblioteca c99 em user mode usa essa chamada para pintar um caractere
		// quando implementa a fun��o printf(.). Por�m esse caractere � pintado
		// na janela com o foco de entrada. A inten��o � que o carctere seja pintado 
		// na pr�pria janela do aplicativo.
		// Outro caso � a digita��o de caractere. Quando um caractere �
		// digitado desejamos que ele seja pintado na janela com o foco de entrada.
		//
		// ?? Quando um caractere � pintado em uma janela que n�o est� com o foco 
		//    de entrada ?? ex: shells, logs ...
		//
		// Supondo que os aplicativos escrever�o mais em terminal por enquanto 
		// a cor padr�o de fonte ser� a cor de terminal.
		
		// #importante
		// Aqui est� pintando o caractere na janela com o foco de entrada.

        case SYS_BUFFER_DRAWCHAR:
            focusWnd = (void *) windowList[window_with_focus];
            if ( (void *) focusWnd == NULL ){ 
                break; 
            }

            // IN: x, y, color, char.
            my_buffer_char_blt ( (unsigned long) (focusWnd->left + arg2),             
                (unsigned long) (focusWnd->top + arg3),  
                CurrentColorScheme->elements[csiTerminalFontColor],   
                (unsigned long) arg4 ); 
            break;


        // 8 @todo: BugBug, aqui precisamos de 4 par�metros.
        case SYS_BUFFER_DRAWLINE:
            my_buffer_horizontal_line ( (unsigned long) a2, 
                (unsigned long) a3, (unsigned long) a4, COLOR_WHITE ); 
            break;

        // 9 @todo: BugBug, aqui precisamos de 5 par�metros.
        case SYS_BUFFER_DRAWRECT:
            drawDataRectangle ( 0, (unsigned long) a2, (unsigned long) a3, 
                (unsigned long) a4, COLOR_WHITE );  
            break;


        // 10 - livre.


        //11, Coloca o conte�do do backbuffer no LFB.
        case SYS_REFRESHSCREEN: 
            refresh_screen ();
            return NULL;
            break;

        //rede: 12,13,14,15	


        // 16 - open()
        //See: sys.c
        // IN: pathname, flags, mode
        //OUT: fd
        case SYS_OPEN:
            debug_print ("gde_serv: SYS_OPEN\n");
            return (void *) sys_open ( (const char *) arg2, 
                                (int) arg3, (mode_t) arg4 ); 
            break;

        // 17 - close()
        // See: sys.c
        // IN: fd
        case SYS_CLOSE:
            debug_print ("gde_serv: SYS_CLOSE\n");
            return (void *) sys_close( (int) arg2 );
            break;


        // 18 - read() 
        case SYS_READ:
            return (void *) sys_read( (unsigned int) arg2, 
                                (char *) arg3, (int) arg4 );  
            break;


        // 19 - write()
        case SYS_WRITE:
            return (void *) sys_write ( (unsigned int) arg2, 
                                (char *) arg3, (int) arg4 );  
            break;


        // BUFFERS  20 21 22 23        

        // 24
        // show window rect.
        // See: window.c
        case 24:
            return (void *) show_window_rect ( (struct window_d *) arg2 );
            break;

        //livre
        //case 33:
            //break;


        // 34 - Setup cursor.
        case SYS_VIDEO_SETCURSOR: 
            set_up_cursor ( (unsigned long) arg2, 
                (unsigned long) arg3 );
            return NULL;
            break; 


        // #todo: 
        // 35 - Getting message from the thread's queue. 
        // Vamos pegar uma mensagem na fila de mesagens da thread
        // e colocarmos nos elementos de single message para o aplicativo pegar.
        // See: ps2kbd.c
        case 35:
            return (void *) __do_35 ( (unsigned long) &message_address[0] );
            break;


        // 36 - livre


        // 37 - Chama o procedimento procedimento default. 
        case SYS_CALLSYSTEMPROCEDURE:
            
            return (void *) system_procedure ( 
                                (struct window_d *) message_address[0], 
                                (int) message_address[1], 
                                (unsigned long) message_address[2], 
                                (unsigned long) message_address[3] );
            break; 
            
            
        //38 39 40 41
             
             
        //38
        //get host name  
        case SYS_GETHOSTNAME:
            return (void *) __gethostname ( (char *) arg2);
            break;


        //39
        //set host name 
        case SYS_SETHOSTNAME:
            return (void *) __sethostname ( (const char *) arg2); 
            break;

        //40
        //get user name 
        case SYS_GETUSERNAME:
           return (void *) __getusername ( (char *) arg2);
            break;
            
        //41
        //set user name 
        case SYS_SETUSERNAME:
            return (void *) __setusername ( (const char *) arg2); 
            break;
           

        // 42 - livre
        // usar para manipulação de arquivo

        // Create an empty file.
        case 43:
            return (void *) sys_create_empty_file ( (char *) arg2 );
            break;

        // 44 -Create an empty directory.
        case 44:
            return (void *) sys_create_empty_directory ( (char *) arg2 );
            break;


        // 45 - livre
        // usar para manipulação de arquivo ou diretório.
        
        
        // 46 ~ 49 (usar para cpu support)
        
        // 46 - livre
        //see: detect.c
        case 46:
            return (void*) get_processor_feature((int)arg2);
            break;
            
        // 47 - livre
        // Show cpu info.
        case 47:
            show_cpu_info();
            return NULL;
            break;

        // 48 - livre
        case 48:
            break;

        // 49 - livre
        // Show system info
        // See: sys.c
        case 49:
            sys_show_system_info ((int) arg2);
            return NULL;
            break;


        // 50 resize window (handle,x,y)
        case SYS_BUFFER_RESIZEWINDOW:
            return (void *) resize_window ( (struct window_d *) arg2, 
                                arg3, arg4 );
            break;

        // 51 redraw window. (handle)
        case SYS_BUFFER_REDRAWWINDOW:
            return (void *) redraw_window ( (struct window_d *) arg2, arg3 );
            break;

        // 52 - IN: (handle,x,y)
        case SYS_BUFFER_REPLACEWINDOW:
            return (void *) replace_window ( (struct window_d *) arg2, 
                                arg3, arg4);
            break;

		//53 maximize window 
		//(handle)
		case SYS_BUFFER_MAXIMIZEWINDOW:
		    MaximizeWindow ((struct window_d*) arg2);
		    break;
		
		//54 minimize window
		//(handle)
		case SYS_BUFFER_MINIMIZEWINDOW:
		    MinimizeWindow ( (struct window_d *) arg2);
		    break;
		
		//55 Get foreground window.
		case SYS_BUFFER_GETFOREGROUNDWINDOW:
		    return (void *) windowGetForegroundWindow ();
		    break;
		
		//56 set foreground window.
		case SYS_BUFFER_SETFOREGROUNDWINDOW:
		    return (void *) windowSetForegroundWindow ( (struct window_d *) arg2 );
		    break;
		
		
		//57.	
		case SYS_REGISTERWINDOW: 
			return (void *) RegisterWindow ( (struct window_d *) hWnd );
			break;
			
		//58.	
		case SYS_CLOSEWINDOW: 
			CloseWindow ( (struct window_d *) hWnd ); 
			break;

        //59 - nothing
        
        // 60
        case SYS_SETACTIVEWINDOW:
            set_active_window (hWnd);
            break;

        // 61 - Id. (int).
        case SYS_GETACTIVEWINDOW:
            return (void *) get_active_window (); 
            break;

        // 62
        case SYS_SETFOCUS: 
            SetFocus ( (struct window_d *) hWnd ); 
            break;

        // 63 id
        case SYS_GETFOCUS: 
            return (void *) window_with_focus;  
            break;

        // 64
        case SYS_KILLFOCUS:
            KillFocus ( (struct window_d *) hWnd ); 
            break;


        // 65
        // Put a char in the current virtual console.
        // see: tty/console.c
        // IN: ch, console id.
        case SYS_KGWS_PUTCHAR:
            console_putchar ( (int) arg2, (int) arg3 ); 
            return NULL;
            break;


		// 66
		// Isso funcionou.
		// � usado pelas rotinas de prompt em libc03 do atacama.
		// n�o deletar :)
		// IN: string, len 
        case 66:
            // Imprime uma string no console atual.
            // IN: string
            //printf ("%s", (char *) arg2); //funciona, mas falta refresh.
            
            //pega o tamanho da string.
            __len = strlen( (const char *) arg2 );
            
            //compara com o len enviado.
            if( __len > arg4){ __len = arg4; }
            if( __len > 128){ __len = 128; }   //tamanho da linha.
                           
            for ( __i=0; __i<__len; __i++ )
            {
				//IN: ch, console id.
                console_putchar ( (int) aa2[__i], (int) arg3 );
                //console_putchar ( (int) arg2[i], (int) arg3 );
            }
            //pular linha depois de imprimir a string do buffer.
            console_putchar ( '\n', (int) arg3);
            return NULL;
            break;


		//67- reservado pra input de usu�rio.
		//case 67:
		//	break;

		//68- Reservado pra input de mouse.
		//case 68:
		//	break;


        //#usando para debug 
		// 69 - Reservado pra input de teclado.
        case 69:
            printf ("Service 69: #todo\n");

            // #obs: Isso � bem pesado. Mas funciona.
            //refresh_rectangle ( 0, 0, 20, 20 );
            //bmpDisplayMousePointerBMP (terminalIconBuffer, 0, 0 ); 		
            break;

        //
        // ## EXIT ##
        //

		// 70 - Exit.
		// Atende a fun��o exit() da libc. 
		// Criaremos um 'request' que ser� atendido somente quando 
		// houver uma interrup��o de timer. 
		// Enquanto isso a thread deve esperar em um loop.
		// IN: ??
        //#todo: criar um wrapper em sci/sys.c ou kernel/exit.c
       
        case SYS_EXIT:
            create_request ( (unsigned long) 12,  // number 
                (int) 1,                          // status 
                (int) 0,                          // timeout. 0=imediatamente.
                (int) current_process,            // target_pid
                (int) current_thread,             // target_tid
                NULL,                             // window 
                (int) 0,                          // msg  
                (unsigned long) arg2,             // long1  
                (unsigned long) arg3 );           // long2
            break;


        // 71
        // Implementação padrão de fork para a libc
        // obs: Não teremos fork na libcore. 
        // Talvez alguma variante.
        // A libcore porde virar algum tipo de api.
        // See: action/fork.c
        case SYS_FORK: 
            return (void *) sys_fork_process();
            break;



        // 72
        // See: sci/sys/sys.c
        // Cria uma thread e coloca ela pra rodar.
        case SYS_CREATETHREAD:
            return (void *) sys_create_thread ( NULL,  NULL, NULL, 
                                arg2,             // init eip
                                arg3,             // init stack
                                current_process,  // pid
                                (char *) a4 );    // name
            break; 



        // 73
        // See: sci/sys/sys.c
        // Cria um processo e coloca a thread primária pra rodar.
        case SYS_CREATEPROCESS:
            return (void *) sys_create_process ( NULL, NULL, NULL, 
                                arg2, arg3, 
                                0, (char *) a4, 
                                RING3, 
                                (unsigned long ) CloneKernelPageDirectory() ); 
            break;



		//80 Show current process info.
		//#todo: Mostrar em uma janela pr�pria.
		//#todo: Devemos chamar uma fun��o que mostre informa��es 
		//apenas do processo atual. 
        case SYS_CURRENTPROCESSINFO:
            show_currentprocess_info();
            break;

        // 81
        // See: sci/sys/sys.c
        case SYS_GETPPID: 
            return (void *) sys_getppid ();
            break;


        // 82 - Mostra informações sobre todos os processos.
        case 82:
            show_process_information();
            break;

		// 83
		// Suporte � chamada da libc waitpid(...).
		// schedi.c
		// #todo.
		// TID, PID 
		// TID � a thread atual.
		// PID veio via argumento.
        // IN: pid, status, option
        case SYS_WAIT4PID: 
            return (void *) do_waitpid ( (pid_t) arg2, 
                                (int *) arg3, (int) arg4 );
                
            //block_for_a_reason ( (int) current_thread, (int) arg2 ); //suspenso
            break;


        // 84 - livre.


        // 85
        // See: sci/sys/sys.c
        case SYS_GETPID: 
            return (void *) sys_getpid ();
            break;


        // 86 - livre.


        // 87 Down.
        case SYS_SEMAPHORE_DOWN:
            return (void *) Down ( (struct semaphore_d *) arg2);
            break;

        //Testa se o processo � v�lido
        //se for v�lido retorna 1234
        //testando ...
        case SYS_88:   
            return (void *) processTesting (arg2);
            break;

        // 89 Up. 
        case SYS_SEMAPHORE_UP:
            return (void *) Up ( (struct semaphore_d *) arg2 );
            break;

 
        // 90
        // See: sci/sys/sys.c 
        case SYS_DEADTHREADCOLLECTOR: 
            sys_dead_thread_collector ();
            break;


        // 91 92 93


        // 94
        //REAL (coloca a thread em standby para executar pela primeira vez.)
        // * MOVEMENT 1 (Initialized --> Standby).
        case SYS_STARTTHREAD:
            //t = (struct thread_d *) arg2;
            //sys_SelectForExecution (t);
            SelectForExecution ( (struct thread_d *) arg2 );
            return NULL;
            break;

 
        //99: #todo: usar para manipulação de processos.

        // #importante:
        // 100 ~ 109: Usar para rotinas de ipc.
        
        // 100, 101, 102 (Livres)  

 
		//103, SYS_RECEIVEMESSAGE	
        //Um processo consumidor solicita mensagem deixada em seu PCB.
        //Argumentos: servi�o, produtor, consumidor, mensagem.		
        //@todo: 
		case SYS_RECEIVEMESSAGE:
			break;


		//104, SYS_SENDMESSAGE
		//Um processo produtor envia uma mensagem para o PCB de outr processo.
		//Argumentos: servi�o, produtor, consumidor, mensagem.
		//@todo:		
		case SYS_SENDMESSAGE:	
			break;



        // 110
        // See: sci/sys/sys.c
        // The higher level routine for reboot.
        // It's a wrapper, an interface.
        case SYS_REBOOT: 
            sys_reboot();
            panic("gde_serv: SYS_REBOOT!");
            break;


        // 111 - Getting single message.
        // No queue. See: thread structure.
        // rotina interna, veja nesse documento.
        // IN: buffer para mensagens.
        // // See: ps2kbd.c
        case 111:
            return (void *) __do_111 ( (unsigned long) &message_address[0] );
            break;



		// 112
		// Enviar uma mensagem para a thread de controle de um processo.
		// arg2 = endere�o do buffer da mensagem, pid
		// arg3 = pid
		// #importante: 
		// O kernel l� o buffer e dentro do buffer tem uma mensagem 
		// que ser� colocada na thread de cotrole do processo;
        case SYS_SENDMESSAGETOPROCESS:
            //printf ("112: PID=%d\n", arg3 );
            ipc_send_message_to_process ( (unsigned long) &message_address[0], 
               (int) arg3 );
            //printf ("112: done\n");
            break;


        // 113 - Update window.
        // Envia uma mensagem PAINT para o aplicativo atualizar a 
        // área de cliente.
        case 113:
            windowUpdateWindow ( (struct window_d *) arg2 );
            break;


		// 114
		// Envia uma mensagem para a thread atual.
		// endereço do buffer da mensagem, tid.
        case SYS_SENDMESSAGETOCURRENTTHREAD:
            ipc_send_message_to_thread ( (unsigned long) &message_address[0], 
                (int) current_thread );
            break;



        // 115 - free slot.
        // 116 - free slot.


        // 117.
        // Envia uma mensagem para uma thread, dado o tid.
        // #todo: poderíamos retornar o retorno da função.
        case 117:
            ipc_send_message_to_thread ( (unsigned long) &message_address[0], 
                 (int) arg3 );
            return NULL;
            break;


        // CREATE WINDOW
        // Cria uma janela usando os recursos do kgws.
        // Chamamos uma fun��o nesse documento.
        case SYS_118:
            return (void *) serviceCreateWindow ( (char *)  arg2 );
            break;


        // 119 - Color scheme.
        case SYS_SELECTCOLORSCHEME:
            return (void *) windowSelectColorScheme ( (int) arg2 );
            break;



        // 120 ~ 123 (livre)


		// 124	 (teste)
		// Defered system procedure call.
		// #todo: 
		// Precisamos armazenasr os argumentos em algum lugar.
		// #bugbug: Precisamos criar um request.
        case 124:
            kernel_request = KR_DEFERED_SYSTEMPROCEDURE;
            return NULL;
            break;


        // 125 - system procedure call.
        case 125:
            return (void *) system_procedure ( NULL, 
                                arg2, arg3, arg4 );
            break;


		// 126
		// Permitindo que drivers e servidores em usermode acessem
		// as portas.
        case SYS_USERMODE_PORT_IN:
			// #bugbug
			// #todo: 
			// Tem que resolver as quest�es de privil�gios.
			//bits, port
            return (void *) portsx86_IN ( (int) arg2, 
                                (unsigned long) arg3 );
            break;


		// 127
		// Permitindo que drivers e servidores em usermode acessem
		// as portas.
        case SYS_USERMODE_PORT_OUT:
			//#bugbug
			//#todo: 
			// Tem que resolver as quest�es de privil�gios.
			//bits, port, value
            portsx86_OUT ( (int) arg2, 
                (unsigned long) arg3, (unsigned long) arg4 );
            return NULL;
            break;

       //128 nothing

		// #especial
		// 129
		// Um driver confirmando que foi inicializado.
		// Efetuaremos a rotina de liga��o do driver com o sistema.
		// O sistema linka o driver com o sistema operacional.
	    //@todo: Essa rotina precisa ser aprimorada. Mas a chamada deve ser 
		// essa mesma.
        case SYS_DRIVERINITIALIZED: 
            return (void *) systemLinkDriver (arg2,arg3,arg4); 
            break;


		// 130
		// Pinta um texto em uma dada janela.
		// #todo: 
		// Se n�o for expecificado a janela, 
		// ent�o � pra pintar na janela principal. gui->main.
		// Repensar se qualquer um pode pintar na janela principal.	
		// IN: window, x, y, color, string.

        case SYS_DRAWTEXT:
            draw_text ( (struct window_d *) message_address[0], 
                (unsigned long) message_address[1],  
                (unsigned long) message_address[2],  
                (unsigned long) message_address[3],   
                (unsigned char *) message_address[4] ); 
            break;


        // 131
        // Pintar o caractere especificamente na janela com o 
        // foco de entrada.          
        case SYS_BUFFER_DRAWCHAR_WWF: 
            focusWnd = (void *) windowList[window_with_focus];
            if ( (void *) focusWnd == NULL ){
                break;
            }
            // x,y,color,char.
            my_buffer_char_blt ( (unsigned long) (arg2 + focusWnd->left),
                (unsigned long) (arg3 + focusWnd->top),
                COLOR_BLACK,     
                (unsigned long) arg4);  
            break;


        // 133 - ??

		// 134
		// Pegar informa��es sobre a �rea de cliente de uma janela;
		// #bugbug: temos que checar mais validade de estrutura.
		// obs: No come�o dessa fun��o, colocamos o arg3 como 
		// ponteiro para a3. um buffer de longs.
        // #bugbug: Ja podemos deletar esse trem ?!
        case 134:
            hWnd = (struct window_d *) arg3;
            if ( (void *) hWnd != NULL ){
                a3[0] = (unsigned long) hWnd->rcClient->left;
                a3[1] = (unsigned long) hWnd->rcClient->top;     
                a3[2] = (unsigned long) hWnd->rcClient->width;
                a3[3] = (unsigned long) hWnd->rcClient->height;
                a3[4] = (unsigned long) hWnd->rcClient->bg_color;
            }
            break;


		// 135 - livre.
		// 136 - livre.


		// 137
		// Isso � usado pela biblioteca stdio em user mode
		// na fun��o 'getchar()'
		// Pega caractere no stdin do teclado.
		// Isso funciona.
		// #bugbug: Rever isso.
        case SYS_GETCH:  
            return (void *) thread_getchar();
            break;


		//138 - get key state.
		// #importante: 
		// #todo: isso precisa ir para a API.
        case 138:
            return (void *) keyboardGetKeyState ( (unsigned char) arg2 );
            break;

        // 139
        case SYS_GETSCANCODE:
            return (void *) get_scancode ();
            break;

        // 140
        case SYS_SET_CURRENT_KEYBOARD_RESPONDER:
            set_current_keyboard_responder (arg2);
            break;

        // 141
        case SYS_GET_CURRENT_KEYBOARD_RESPONDER:
            return (void *) get_current_keyboard_responder();
            break;

        // 142
        case SYS_SET_CURRENT_MOUSE_RESPONDER:
            return NULL;
            //set_current_mouse_responder(arg2);
            break;

        // 143
        case SYS_GET_CURRENT_MOUSE_RESPONDER:
            return NULL;
            //return (void *) get_current_mouse_responder ();
            break;


		// 144
		// Pega o ponteiro da client area.
		// #bugbug: pegamos o ponteiro mas n�o temos permiss�o 
		// para acessar a estrutura.
        case SYS_GETCLIENTAREARECT:
            return (void *) getClientAreaRect ();
            break;


        // 145
        // configura a client area	
        // @todo: 
        // O ponteiro para estrutura de ret�ngulo � passado 
        // via argumento.
        case SYS_SETCLIENTAREARECT:
            setClientAreaRect ( arg2, arg3, arg4, 0);
            break;

        // 146
        // #bugbug: 
        // isso n�o parece seguro, precismos checar a validade 
        // da estrutura antes, mas vai ficar assim por enquanto.
        // Perigo!
        case 146:
            return (void *) gui->screen;
            break;


        // 147
        // #bugbug: 
        // isso n�o parece seguro, precismos checar a validade da 
        // estrutura antes, mas vai ficar assim por enquanto.
        // Perigo!
        case 147:
            return (void *) gui->main;
            break;


		// 148 
		// Create grid and itens.
		// window, n, view. 
        case 148:
           return (void *) grid ( (struct window_d *) arg2, 
                               (int) arg3, (int) arg4 );
            break;



        // 149 - Testing system menu.
        // Essa � uma rotina de teste, qua chama v�rias fun��es.
        case 149:
            MainMenu ( (struct window_d *) arg2 );
            break;


        // 152 - get uid
        case SYS_GETCURRENTUSERID: 
            return (void *) current_user; 
            break;

        // 154 - get gid
        case SYS_GETCURRENTGROUPID: 
            return (void *) current_group; 
            break;
  
        // 156 - SYS_SHOWUSERINFO
        case 156:
            ShowUserInfo (current_user);
            return NULL;
            break;

        // 157 - get user session id
        case SYS_GETCURRENTUSERSESSION:
            return (void *) current_usersession; 
            break;

        // 158 - get room id (window station)
        case SYS_GETCURRENTWINDOWSTATION:
            return (void *) current_room;  
            break;

        // 159 - get desktop id
        case SYS_GETCURRENTDESKTOP:
            return (void *) current_desktop; 
            break;

		// 160
		// Criar um socket e retornar o ponteiro para a estrutura.
		// Gramado API socket support. (not libc)
		// See:
        case 160:
            return (void *) create_socket ( (unsigned long) arg2, 
                                (unsigned short) arg3 );
            break;


        // 161
        // get socket IP
        // Gramado API socket support. (not libc)
        case 161:
            return (void *) getSocketIP ( (struct socket_d *) arg2 );
            break;

        // 162
        // get socket port
        // Gramado API socket support. (not libc)
        case 162:
            return (void *) getSocketPort( (struct socket_d *) arg2 );
            break;


        // 163
        // update socket  
        // retorno 0=ok 1=fail		
        // Gramado API socket support. (not libc)
        case 163:
            return (void *) update_socket ( (struct socket_d *) arg2, 
                                (unsigned long) arg3, 
                                (unsigned short) arg4 );
            break;


        // 164 - livre. 

        // socket stuff
        case 165:
            break;

        // socket stuff
        case 166:
            break;

 
       // 167 - livre.
 
 
       // livre
       // IN: filename, argv, envp
       case 168:
           return (void *) __execute_new_process ( (const char *) arg2, 
                               (char **) arg3, 
                               (char **) arg4 );
           break;



       // write
       // See: unistd.c em garden/lib/libcore.
       case 169:
           //essa rotina mudou de n�mero.
           return NULL;
           // IN: fd, buf, count.         
           //return (void *) tty_write ( (unsigned int) arg2,  //channel 
             //                  (char *) arg3,                //buf
               //                (int) arg4 );                 //nr
           break;


        //170
        //pwd ...
        //Cada processo tem seu pr�prio pwd.
        //Essa rotina mostra o pathname usado pelo processo.	
        case SYS_PWD:
            debug_print ("175:\n");
            fs_print_process_pwd (current_process);
            return NULL;
            break;


        // 171 - retorna o id do volume atual.
        case SYS_GETCURRENTVOLUMEID:
            return (void *) current_volume;
            break;

		//172 - configura o id do volume atual.
		//#bugbug: Estamos modificando, sem aplicar nenhum filtro.
        case SYS_SETCURRENTVOLUMEID:
            current_volume = (int) arg2;
            break;

        // 173
        // Lista arquivos de um diret�rio, dado o n�mero do disco,
        //o n�mero do volume e o n�mero do diret�rio,
        //args in: disk id, volume id, directory id
        case SYS_LISTFILES:
            fsListFiles ( arg2, arg3, arg4 );  
            return NULL;
            break;


        // 174
        case SYS_SEARCHFILE:
            return (void *) KiSearchFile ( (unsigned char *) arg2, 
                                (unsigned long) arg3 );
            break;


        // 175 - 'cd' command support.
        // +Atualiza o pathname na estrutura do processo atual.
        // +Atualiza o pathname na string global.
        // +Carrega o arquivo referente ao diretório atual.
        case 175:
            debug_print ("175:\n");
            fsUpdateWorkingDiretoryString ( (char *) arg2 );
            fsLoadFileFromCurrentTargetDir ();
            return NULL;
            break;


        // 176
        // Remove n nomes de diret�rio do pathname do processo 
        // indicado no argumento.
        // Copia o nome para a string global.
        case 176:
            fs_pathname_backup ( current_process, (int) arg3 );
            break;


        // 177 -  'dir' command.
        // Comando dir no shell.
        // Listando arquivos em um diretório dado seu nome.
        case 177:
            debug_print ("177:\n");
            fsList ( (const char *) arg2 );
            return NULL;
            break;


        // 178
        // See: sci/sys/sys.c
        case 178:
            return (void *) sys_get_file_size ( (unsigned char *) arg2 );
            break;


        // 179 - livre


        // 184
        // pega o endere�o do heap do processo dado seu id.	
        case SYS_GETPROCESSHEAPPOINTER:
            return (void *) GetProcessHeapStart ( (int) arg2 );
            break;



       // 193 - livre.
       // 194 - livre.
       // 195 - livre.
       // 196 - livre.


        //197
		//scroll de �rea de cliente de uma janela;
        case 197:
		    //essa � uma boa rotina, mas precisamos tabalhar nisso,
			//est� dando page fault.
			//scroll_client_window ( (struct window_d *) arg2 );
            break; 


        // 199 - Kernel Garbage Collector.
        // The kernel cleans some memory marked as unused.
        // #bugbug: We don't need a syscall for this operation.
        case SYS_GC:
            kernel_gc();
            return NULL;
            break;


        // 200 - Envia um sinal para um processo.
        // argumentos (process handle, signal number).
        case SYS_SENDSIGNAL:
            signalSend ( (void *) a2, (int) arg3 );
            return NULL;
            break;
            
        //#todo: precismos criar o suporte a chamada signal()
        // maybe sys_signal
        //


        // ...

        // 205
        // block for a reason.
        //bloqueamos uma thead por um dos motivos indicados em argumento.
        case SYS_GENERICWAIT:
		    //TID, reason.
            //block_for_a_reason ( (int) arg2, (int) arg3 );
			break;		

		//210
		case SYS_CREATETERMINAL: 
            break;
			
		//211
        case SYS_GETCURRENTTERMINAL:
            return (void *) current_terminal;
			break;
			
	    //212
        case SYS_SETCURRENTTERMINAL:
            current_terminal = (int) arg2;
			break;
			
		//213
        case SYS_GETTERMINALINPUTBUFFER:	
            return NULL;
			break;
			
		//214
        case SYS_SETTERMINALINPUTBUFFER:
		    break;

		// 215
		// Get terminal window.	
		// retorna o ID.
		// O ID fica em terminal_window.
		case SYS_GETTERMINALWINDOW: 
			return (void *) systemGetTerminalWindow (); 
			break;

		// 216
		// Set terminal window	
		// Configura qual vai ser a janela do terminal virtual. 
		// #obs: O refresh de stdout podera' ocorrer em ts.c
		// O ID fica em terminal_window.	
		case SYS_SETTERMINALWINDOW:	
		   systemSetTerminalWindow ( (struct window_d *) arg2 );	
		   break;
		   
		//217
		case SYS_GETTERMINALRECT:
			return NULL; 
			break;

		//218
        //configura na estrutura do terminal corrente,
        //qual vai ser o ret�ngulo a ser usado. 		
		case SYS_SETTERMINALRECT:
		
		   //#bugbug: Pagefault.
		   
		    // Estamos usando default por falta de argumento.
            //systemSetTerminalRectangle( DEFAULT_TERMINAL_LEFT, 
			//                            DEFAULT_TERMINAL_TOP, 
			//							arg3, 
			//							arg4 );		
		    break;


		//219
        case SYS_DESTROYTERMINAL:
            break; 
 
       //220 - reboot             #todo
       //221 - execute a program. #todo


        // 222 - Create timer.
        // IN: window, ms e tipo
        case 222:
            return (void *) create_timer ( (struct window_d *) arg2, 
                                (unsigned long) arg3, (int) arg4 );
            break;



        //223 - get sys time info.
        // informa��es variadas sobre o sys time.
        case 223:
            return (void *) get_systime_info ( (int) arg2 );
            break;


        // 224 - get time
        case SYS_GETTIME:  return (void *) get_time();  break;
        // 225 - get date
        case SYS_GETDATE:  return (void *) get_date();  break;


        // Obs: 
        // #todo: 
        // Poderia ser uma chamada para configurar o posicionamento 
        // e outra para configurar as dimens�es.
        //226 - get
        case SYS_GET_KERNELSEMAPHORE:
            return (void *) __spinlock_ipc;
            break;


        // 227 - close critical section	
        case SYS_CLOSE_KERNELSEMAPHORE:
            //__spinlock_ipc = 0;
            //criticalsection_pid = (pid_t) 0;
            process_exit_criticalsection(current_process);
            return NULL;
            break;


        // 228 - open critical section
        // #todo: Quando um processo fechar e estiver
        // em sua sessão crítica, então devemos liberar
        // essa flag. Isso fica mais fácil de lembrar se
        // existir uma flag na estrutura de processo.
        case SYS_OPEN_KERNELSEMAPHORE:
            //__spinlock_ipc = 1;
            //criticalsection_pid = (pid_t) current_process;
            process_enter_criticalsection(current_process);
            return NULL;
            break;


		// 232 - livre
		// 233 - livre
		// 234 - livre 
		// 235 - livre



		// tty ... 236 237 238 239.

        // 236 - get tty id
        case 236:
            return (void *) current_tty;
            break;

        //240
        case SYS_GETCURSORX:  return (void *) get_cursor_x();  break;
        //241
        case SYS_GETCURSORY:  return (void *) get_cursor_y();  break;


		//244 enable text cursor.	
		case 244:
		    timerEnableTextCursor ();
		    //timerShowTextCursor = 1;
		    //gwsEnableTextCursor ();
            break;		

        //245 disable text cursor.
        case 245:
            timerDisableTextCursor ();
            //timerShowTextCursor = 0;
            //gwsDisableTextCursor ();
            break;

        // =====================================
        // 246 ~ 249 reservado para libc support.

        // 246
        // openat - open a file relative to a directory file descriptor 
        // IN: dirfd, pathname, flags.
        case 246:
            return (void *) k_openat ( (int) arg2, 
                                (const char *) arg3, (int) arg4 ); 
            break;

        // 247 - pipe() support.
        // IN: array, flags.
        case 247:
            return (void *) sys_pipe ( (int *) arg2, (int) arg3 ); 
            break;


        // 248 - execve() support.
        // Executa um programa usando o processo atual.
        // #bugbug: 
        // A intenção é carregar a imagem num novo endereço físico
        // e continuar usando o processo clone criado pelo fork().
        // #todo: 
        // Implementar com base em outro execve existente.
        // IN: pathname, argv, envp.
        case 248:
            return (void *) sys_execve ( (const char *) arg2, 
                                (char **) arg3, (char **) arg4 ); 
            break;


        // 249 - livre.
        // #todo: Usar para algum tipo de exec, igual ao número acima.


        // =====================================
        // (250 ~ 255) - Info support.

        // 250
        // See: syssm/syssm.c
        case SYS_GETSYSTEMMETRICS:
            return (void *) sys_get_system_metrics ( (int) arg2 );
            break;

        // 251
        // See: sci/sys/sys.c
        case SYS_SHOWDISKINFO:  sys_show_system_info(1);  break;

        // 252
        // See: sci/sys/sys.c
        case SYS_SHOWVOLUMEINFO: sys_show_system_info(2);  break;

        // 253
        // See: sci/sys/sys.c
        case SYS_MEMORYINFO:  sys_show_system_info(3);  break;


        // 254
        // See: sci/sys/sys.c
        case SYS_SHOWPCIINFO:  sys_show_system_info(4);  break;

        // 255
        // See: sci/sys/sys.c
        case SYS_SHOWKERNELINFO: sys_show_system_info(5);  break;


		// #todo:
		// Need to check the system call ID to ensure it's valid 
		// If it s invalid, return ENOSYS Function not implemented error

        default:
            printf ("services: Default {%d}\n", number );
            refresh_screen ();
            return NULL;
            break;
    };


	//Debug.
	//printf("SystemService={%d}\n",number);
   

	// * importante:
	//   Depois de esgotados os 'cases', vamos para a sa�da da fun��o.
	//    No caso de um aplicativo ter chamado essa rotina, 
	// o retorno ser� para o ISR da int 0x80, feito em assembly.
	//    No caso do kernel ter chamado essa rotina, apenas retorna.


done:
    //Debug.
    //printf("Done\n",number);
    //refresh_screen();
    return NULL;
}



/*
 ******************************************************
 * serviceCreateWindow:
 *     Cria uma janela com base nos argumentos passados no buffer.
 *     Essa rotina � o servi�o 118.
 */

// #todo
// Esse servi�o deve ir para o m�dulo /kgws

unsigned long serviceCreateWindow ( char *message_buffer ){

    unsigned long *message_address = (unsigned long *) message_buffer;

	//Ponteiro para a janela criada pelo servi�o.
    struct window_d *NewWindow;  
    struct window_d *ParentWindow;  

    cwArg1 = message_address[0];             // Type. 
    cwArg2 = message_address[1];             // WindowStatus 
    cwArg3 = message_address[2];             // view
    cwArg4 = (char *) message_address[3];    // a4 Window name.
    cwArg5 = message_address[4];             // x
    cwArg6 = message_address[5];             // y
    cwArg7 = message_address[6];             // width
    cwArg8 = message_address[7];             // height

	//parent window.
	//message_address[8];
	//cwArg9 = gui->screen;  //@todo: O argumento arg4 est� enviando parent window. 
    cwArg9 = (struct window_d *) message_address[8];    //parent
    ParentWindow = (struct window_d *) message_address[8];    //parent

	//onde?
	//message_address[9];
	//cwArg10 = arg4;  //desktop ID 

    cwArg11 = message_address[10];    //cor da area de cliente.
    cwArg12 = message_address[11];    //cor da janela.

    //==========

	//Window.
    unsigned long WindowType;      //Tipo de janela.
    unsigned long WindowStatus;    //Status, ativa ou n�o.
	//unsigned long WindowRect;
    unsigned long WindowView;      //Min, max.
    char *WindowName;  

    unsigned long WindowX = (2*(800/20));    //100;   >          
    unsigned long WindowWidth  = 320;               
    unsigned long WindowY = (2*(600/20));    //100;   V                
    unsigned long WindowHeight = 480;  

    unsigned long WindowClientAreaColor = COLOR_WINDOW;  
    unsigned long WindowColor = COLOR_WINDOW;  


	//#todo: Checar a validade da esturtura,
	//WindowClientAreaColor = CurrentColorScheme->elements[csiWindow];  
	//WindowColor = CurrentColorScheme->elements[csiWindowBackground];  


    WindowType = cwArg1; 
    WindowStatus = cwArg2; 
    WindowView = cwArg3; 
    WindowName = (char *) cwArg4; 

    WindowX = cwArg5; 
    WindowY = cwArg6; 
    WindowWidth = cwArg7; 
    WindowHeight = cwArg8;


	//#todo
	//gui->screen  = cwArg9; 
	//desktopID = cwArg10; 

	//Obs: 11 - A cor da �rea de cliente ser� escolhida pelo app.   
    WindowClientAreaColor = (unsigned long) cwArg11;  
    WindowColor = (unsigned long) cwArg12;     


    struct thread_d *t;
    int desktopID;


    desktopID = (int) get_current_desktop_id ();


    //
    // Create.
    //
    
    
    // #test
    // Ok isso funcionou.
    if ( (void *) ParentWindow != NULL )
    {
        WindowX = ParentWindow->left + WindowX;
        WindowY = ParentWindow->top + WindowY;
    }

    // Importante:
	// Nesse momento � fundamental saber qual � a parent window da janela que 
	// vamos criar pois a parent window ter� as margens que nos guiam.
	// Essa parent window pode ser uma aba de navegador por exemplo.
	// >> O aplicativo deve enviar o ponteiro da janela m�e.
	
	//Criando uma janela, mas desconsiderando a estrutura rect_d passada por argumento.
	//@todo: #bugbug a estrutura rect_d apresenta problema quando passada por argumento
	//com um endere�o da �rea de mem�ria do app.
	
	
	//#test
	// testando novo m�todo de pintura.

    NewWindow = (void *) kgws_create_window ( WindowType, WindowStatus, 
                             WindowView, WindowName, 
                             WindowX, WindowY, WindowWidth, WindowHeight,
                             cwArg9, desktopID, 
                             (unsigned long) WindowClientAreaColor, 
                             (unsigned long) WindowColor );


    if ( (void *) NewWindow == NULL )
    { 
        //?? Mensagem. 
        return 0;

    }else{

		//se a janela foi criada com sucesso, podemos desativar a flag.
		//*importante, nesse momento precisamos desativar a flag.

		cwFlag = 0;                  
		
        // Obs: 
		// Quem solicitou a cria��o da janela pode estar em user mode
        // por�m a estrutura da janela est� em kernel mode. #bugbug
		// Obs:
		// Para preencher as informa��es da estrutura, a aplica��o
		// pode enviar diversas chamadas, Se n�o enviar, ser�o considerados
		// os valores padr�o referentes ao tipo de janela criada.
		// Cada tipo tem suas caracter�sticas e mesmo que o solicitante
		// n�o seja espec�fico nos detalhes ele ter� a janela do tipo que deseja.
		
        //  
        //@todo: Pode-se refinar os par�metros da janela na estrutura.
		//NewWindow->
		//...
		
		//@todo: N�o registrar, quem criou que registre a janela.
		//RegisterWindow(NewWindow);
		
		// #importante
		// Se a tarefa atual est� pintando, vamos melhorar a sua prioridade.
		// Possivelmente a thread de controle da janela � a thread atual.
		
		t = (void *) threadList[current_thread];
		
		set_thread_priority ( t, PRIORITY_MAX );
		
		NewWindow->control = t;


        return (unsigned long) NewWindow;
    };
}



/*
 ***********************
 * servicesPutChar:
 *     Movendo para terminal/output.c 
 *     Coloca um char usando o 'terminal mode' de stdio selecionado 
 * em _outbyte.
 * stdio_terminalmode_flag = n�o transparente.
 */

void servicesPutChar ( int c )
{
    console_putchar ( (int) c, current_vc );
}



/*
 ***************************************
 * gde_133:
 *
 *     This routine was called by the interrupt 133.
 *     See the handler at: x86/entry/head/sw.inc.
 *     At function: _int133.
 */

void *gde_133 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    void *ret;


	//Salva contexto dos registradores.
    save_current_context ();


   // ret = (void *) ?????();

	//Restaura os registradores e o cr3.
    restore_current_context ();

    return (void *) ret; 
}



//
// End.
//

