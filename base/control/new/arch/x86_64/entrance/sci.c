
// sci.c
// system call interface.
// Handlers for the system interrupts.
// #todo: 
// There is another point:
// The 'event delivery' and 'return' support.

#include <kernel.h>  

//#define SERVICE_NUMBER_MAX  255

static unsigned long __default_syscall_counter=0;


//globals
//see:sw.asm
unsigned long sci0_cpl=0;
unsigned long sci1_cpl=0;
unsigned long sci2_cpl=0;


//
// == private functions: prototypes =============
//

static void *__extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );

static void __service897(void);
static void __servicePutChar( int c );
static void __invalidate_surface_rectangle(void);


static void __setup_surface_rectangle(
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height );

static void __initialize_ws_info(pid_t pid);
static void __maximize_ws_priority(pid_t pid);

// =============================

// Setup WindowServerInfo global structure.
static void __initialize_ws_info(pid_t pid)
{
    struct process_d *p;
    struct thread_d *t;

    pid_t current_process = (pid_t) get_current_process();

    debug_print ("__initialize_ws_info:\n");

    if (pid != current_process){
        panic("__initialize_ws_info: pid != current_process\n");
    }

// #todo
// Maybe we can just emit an error message and return.

    if( WindowServerInfo.initialized == TRUE ){
        panic("__initialize_ws_info: The ws is already running\n");
    }

    WindowServerInfo.initialized = FALSE;
    
    if (pid < 0 || pid >= PROCESS_COUNT_MAX)
    {
        return;
    }

// process
    p = (struct process_d *) processList[pid];
    if( (void*) p == NULL )
        return;
    if(p->magic!=1234)
        return;
    // Changing personality.
    // The childs will have the same personality
    p->personality = (int) PERSONALITY_GWS;
    WindowServerInfo.pid_personality = (int) PERSONALITY_GWS;
 
// thread
    t = (struct thread_d *) p->control;
    if( (void*) t == NULL )
        return;
    if(t->magic!=1234)
        return;
    // Changing personality.
    // The childs will have the same personality
    t->personality = (int) PERSONALITY_GWS;
    WindowServerInfo.tid_personality = (int) PERSONALITY_GWS;

    WindowServerInfo.pid = (pid_t) pid;
    WindowServerInfo.tid = (tid_t) t->tid;

    WindowServerInfo.initialized = TRUE;
}


static void __service897(void)
{
    struct thread_d *myThread; 
    struct rect_d r;
    unsigned int _Color=0;


// Current thread
// This routine only can be called by the 
// init process. Its tid is INIT_TID.
    if ( current_thread < 0 || current_thread >= THREAD_COUNT_MAX ){
        return;
    }
    if (current_thread != INIT_TID){
        return;
    }

    _Color = (unsigned int) (COLOR_GREEN + 0);

// Setup rectangle
    r.left = 0;
    r.top = 0;
    r.width = 24;
    r.height = 24;
    r.dirty = FALSE; 
    r.used = TRUE;
    r.magic = 1234;

// Paint
// Invalidate means that the rectangle need to be flushed
// into the framebuffer.
// If the rectangle is dirty, so it needs to be flushed into 
// the framebuffer.
// When we draw a window it needs to be invalidated.

    backbuffer_draw_rectangle( 
        r.left, r.top, r.width, r.height, 
        _Color, 
        0 );      // #todo: rop flags.

    r.dirty = TRUE;

// Setup surface rectangle.

//  Thread
    myThread = (struct thread_d *) threadList[current_thread];
// Valid thread
    if ( (void*) myThread != NULL )
    {
        if ( myThread->used == TRUE && myThread->magic == 1234 ){
            myThread->surface_rect = (struct rect_d *) &r;
            return;
        }
    }
}

static void __setup_surface_rectangle(
    unsigned long left,
    unsigned long top,
    unsigned long width,
    unsigned long height )
{
    struct thread_d *t;
    struct rect_d *r;

/*
// dc: Clippint
    unsigned long deviceWidth  = (unsigned long) screenGetWidth();
    unsigned long deviceHeight = (unsigned long) screenGetHeight();
    if ( deviceWidth == 0 || deviceHeight == 0 ){
        debug_print ("__setup_surface_rectangle: [PANIC] w h\n");
        panic       ("__setup_surface_rectangle: [PANIC] w h\n");
    }
*/

    if ( current_thread<0 || current_thread >= THREAD_COUNT_MAX ){
        return;
    }

// structure
    t = (struct thread_d *) threadList[current_thread];
    if ( (void*) t == NULL ){ return; }
    if ( t->magic != 1234 ) { return; }

    r = t->surface_rect;
    if ( (void*) r == NULL ){ return; }
    if ( r->magic != 1234 ) { return; }
    
    r->left   = (left   & 0xFFFF);
    r->top    = (top    & 0xFFFF);
    r->width  = (width  & 0xFFFF);
    r->height = (height & 0xFFFF);

    r->dirty = FALSE;
}


static void __invalidate_surface_rectangle(void)
{
    struct thread_d *t;
    struct rect_d *r;

    if ( current_thread<0 || current_thread >= THREAD_COUNT_MAX ){
        return;
    }

    t = (struct thread_d *) threadList[current_thread];
    if ( (void*) t == NULL ){ return; }
    if ( t->magic != 1234 ) { return; }

    r = t->surface_rect;
    if ( (void*) r == NULL ){ return; }
    if ( r->magic != 1234 ) { return; }

    r->dirty = TRUE;
}


// #test
// Changing the window server's quantum. 
// The purpose here is boosting it when it is trying to register itself.
// class 1: Normal threads.
static void __maximize_ws_priority(pid_t pid)
{
    struct process_d *p;
    struct thread_d *t;

    unsigned long ProcessType         = PROCESS_TYPE_SYSTEM;
    unsigned long ProcessBasePriority = PRIORITY_SYSTEM;
    unsigned long ProcessPriority     = PRIORITY_SYSTEM;

    unsigned long ThreadType         = ProcessType;
    unsigned long ThreadBasePriority = ProcessBasePriority;
    unsigned long ThreadPriority     = ProcessPriority;

    pid_t current_process = (pid_t) get_current_process();

    if (pid<=0 || pid >= PROCESS_COUNT_MAX){
        return;
    }
    if (pid != current_process){
        debug_print ("__maximize_ws_priority: pid != current_process\n");
        panic       ("__maximize_ws_priority: pid != current_process\n");
    }

// process
    p = (struct process_d *) processList[pid];
    if ((void*)p==NULL)
        return;
    if (p->used!=TRUE)
        return;
    if (p->magic!=1234)
        return;

    p->type = ProcessType;

    p->base_priority = ProcessBasePriority;
    p->priority      = ProcessPriority;

// thread
    t = (struct thread_d *) p->control;
    if ( (void*) t == NULL ){ return; }
    if ( t->magic != 1234 ) { return; }

    t->type = ThreadType;

    t->base_priority = ThreadBasePriority;
    t->priority      = ThreadPriority;

// see: ps/sched.h
    t->quantum = QUANTUM_MAX;
}


// Services abouve 256.
// Helper function called by sci0().
static void *__extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    struct process_d *__p;
    struct process_d *__net_process;
    struct desktop_d *__desktop;
    //struct desktop_d *_Desktop;
    struct window_d  *__window;
//generic file pointer
    file *__fp;
//bmp file pointer.
    file *__bmfp;
    unsigned long *message_address = (unsigned long *) arg2;

    pid_t current_process = (pid_t) get_current_process();

//Deprecated.
//Outro n�mero fará esse trabalhao.
    if ( number == 260 ){
        return (void *) sys_read ( 
                            (unsigned int) arg2, 
                            (char *)       arg3, 
                            (int)          arg4 );
    }

//Deprecated.
//Outro numero fará esse trabalho.
    if ( number == 261 ){
        return (void *) sys_write ( 
                            (unsigned int) arg2, 
                            (char *)       arg3, 
                            (int)          arg4 );
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

// 266
// Pega o número da tty de um processo, dado o pid.
// process.c
// IN: PID.
// OUT: tty id.
    if (number == 266){
        return (void *) process_get_tty ( (int) arg2 );
    }

// Ligar duas tty, dados os pids dos processos que possuem as tty.
// tty/pty.c
// IN: master pid, slave pid.
    //if (number == 267){
    //    return (void *) pty_link_by_pid ( (int) arg2, (int) arg3 );
    //}

// Channel is a file descriptor in the file list 
// of the current process.
// IN: fd, buf, count.
    if (number == 272)
    {
           return (void *) tty_read ( 
                               (unsigned int) arg2,    // channel 
                               (char *)       arg3,    // buf
                               (int)          arg4 );  // nr
    }

// Channel is a file descriptor in the file list 
// of the current process.
// IN: fd, buf, count.
    if (number == 273)
    {
        return (void *) tty_write ( 
                            (unsigned int) arg2,    // channel 
                            (char *)       arg3,    // buf
                            (int)          arg4 );  // nr
    }

// Get current virtual console.
    if (number == 277 ){
        return (void *) console_get_current_virtual_console();
    }

// Set current cirtual console.
// #todo: precisa de privilégio. 
    if (number == 278 ){
        console_set_current_virtual_console ( (int) arg2 );
        return NULL;
    }

// Returns the current runlevel.
    if ( number == 288 ){
        return (void *) newos_get_current_runlevel();
    }

// Serial debug print string.
// See: sys.c
    if ( number == 289 ){
        return (void *) sys_serial_debug_printk( (char *) arg2 );
    }

    if ( number == 292 ){
        return (void *) newos_get_memory_size_mb();
    }

// #bugbug: cuidado.
// get boot info.
// See: info.c
// IN: index to select the info.
    if ( number == 293 ){
        return (void *) info_get_boot_info ( (int) arg2 );
    }

// Inicializar ou reinicializar componentes do sistema
// depois da inicialização completa do kernel.
// Isso poderá ser chamado pelo init.bin, pelo shell
// ou qualquer outro.
// see: 
    if ( number == 350 ){
        printf("350:\n"); refresh_screen();
        return (void *) sys_initialize_component ((int) arg2);
    }

// 377 
// todo: implement uname() libc support.
// See: sys.c
    if ( number == 377 )
    {
        //printf ("__extra_services: [377] uname. [todo] \n");
        //invalidate_screen();
        //refresh_screen();
        sys_uname ( (struct utsname *) arg2 );        
        return NULL;
    }

// #bugbug
// It crashes the system.
// Clear the screen.
    if (number==390)
    {
        debug_print ("__extra_services: [390] :)\n");
        //Background_initialize();
        return NULL;
    }

// #bugbug
// Falha se tentamos pintar a tela toda.
    if (number==391)
    {
        //debug_print("__extra_services: [391]\n");
        backbuffer_draw_rectangle ( 
            (unsigned long) message_address[0],    //x 
            (unsigned long) message_address[1],    //y
            (unsigned long) message_address[2],    //width
            (unsigned long) message_address[3],    //height
            (unsigned int)  message_address[4],    //color
            (unsigned long) message_address[5] );  //rop_flags
        return NULL;
    }

// 512 - Get ws PID for a given desktop.
// Pega o wm de um dado desktop.
// IN: Desktop structure pointer.
// OUT: pid
    if ( number == SYS_GET_WS_PID )
    {
        debug_print("__extra_services: SYS_GET_WS_PID\n");
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->used  == TRUE && 
                 __desktop->magic == 1234 )
            {
                return (void *) __desktop->ws; 
            }
        }
        // It means pid=0.
        return NULL;
    }

// 513
// Register the ring3 window server.
// Set ws PID for a given desktop
// Register a window server.
// gramado_ports[11] = ws_pid
// Called by the window server.
// arg2 = desktop structure pointer.
// arg3 = The window server PID.
// #todo: 
// We need a helper function for this.

    if ( number == SYS_SET_WS_PID )
    {
        debug_print("__extra_services: SYS_SET_WS_PID\n");
        
        __desktop = ( struct desktop_d *) arg2;

        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->used  == TRUE && 
                 __desktop->magic == 1234 )
            {
                if(arg3 != current_process){
                    panic("sci.c: [SYS_SET_WS_PID] arg3 != current_process\n");
                }
                //register_ws_process(current_process);
                __desktop->ws = (pid_t) current_process;
                
                socket_set_gramado_port(
                    GRAMADO_WS_PORT,
                    (pid_t) current_process );

                __initialize_ws_info(current_process);
                __maximize_ws_priority(current_process);
                
                //#todo
                //WindowServer.desktop = (struct desktop_d *) __desktop;
                //WindowServer.type = WindowServerTypeRing3Process;
                //WindowServer.pid = (pid_t) current_process;
                
                // #test
                // Eleva a prioridade da thread de controle para alem dos limites.
                // #bugbug: Cancelado.
                // Isso melhorou a performance somente no qemu.
                // Todo o resto piorou. Piorou a conexao entre os processos e
                // principalmente piorou em resoluçoes maiores e na maquina real.
                //power_pid(current_process,4);
                //power_pid(current_process,8);
                
                
                // Changing the kernel input mode.
                // #bugbug: Maybe we need to wait a little bit. hahaha
                // The window server is still initializing ...
                // but there is no problem to sent messages to its control thread.
                // os am i wrong?
                
                //#importante
                // Nao mudaremos mais o modo de input.
                // Esse modo de input nao vai mais existir.
                // o cliente pegara o input.
                // current_input_mode = INPUT_MODE_WS; 
                
                // returning ok.
                // But, we could return the port number.
                
                //#debug
                //printf("513: done\n");
                //refresh_screen();
                //while(1){}
                
                return (void *) TRUE;  //ok 
            }
        }

        //#debug
        //printf("513: fail\n");
        //refresh_screen();
        //while(1){}
        
        return NULL; //fail
    }    

// 514 - get wm PID for a given desktop
// IN: desktop
    if ( number == SYS_GET_WM_PID )
    {
       debug_print("__extra_services: SYS_GET_WM_PID\n");
        // pega o wm de um dado desktop.
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->used  == TRUE && 
                 __desktop->magic == 1234 )
            {
                return (void *) __desktop->wm; 
            }
        }
        return NULL; //#bugbug: Isso pode significar pid 0.
    }

// 515 - set wm PID for a given desktop
// Register a ring3 wm.
// IN: desktop, pid
    if ( number == SYS_SET_WM_PID )
    {
       debug_print("__extra_services: SYS_SET_WM_PID\n");
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->used  == TRUE && 
                 __desktop->magic == 1234 )
            {
                //register_wm_process(arg3);
                 __desktop->wm = (pid_t) arg3;

                socket_set_gramado_port(
                    GRAMADO_WM_PORT,
                    (pid_t) current_process );

                return (void *) TRUE;  //ok 
            }
        }
        return NULL; //fail
    }

// #bugbug
// This is a ring0 pointer.
// A ring3 process can't handle this thing.
// Get current desktop
    if (number == 519){
        return (void *) CurrentDesktop;
    }

// network server
// 521 - set ns PID for a given desktop
// Register a network server.
// gramado_ports[11] = ws_pid

    if ( number == 521 )
    {
        __desktop = ( struct desktop_d *) arg2;
        if ( (void *) __desktop != NULL )
        {
            if ( __desktop->used == TRUE && 
                 __desktop->magic == 1234 )
            {
                __desktop->ns = (int) arg3;
                
                socket_set_gramado_port(
                    GRAMADO_NS_PORT,
                    (pid_t) current_process );

                return (void *) TRUE;  //ok 
            }
        }
        return NULL; //fail
    }    

// 600 - dup
    if ( number == 600 ){
        return (void *) sys_dup( (int) arg2 );  
    }

// 601 - dup2
    if ( number == 601 ){
        return (void *) sys_dup2( (int) arg2, (int) arg3 );
    }

// 602 - dup3
    if ( number == 602 ){
        return (void *) sys_dup3( (int) arg2, (int) arg3, (int) arg4 );
    }



// 603 - lseek support.
// See: klib/kunistd.c
// IN: fd, offset, whence.
    if ( number == 603 ){
        return (void *) sys_lseek ( 
                            (int)   arg2, 
                            (off_t) arg3, 
                            (int)   arg4 );
    }



    if (number == 640)
    {
        if(current_thread != INIT_TID){return NULL;}
        taskswitch_lock();
        return NULL;
    }

// 641
// Unlock taskswitching 
    if (number == 641)
    {
        if(current_thread != INIT_TID){return NULL;}
        taskswitch_unlock();
        return NULL;
    }

    if (number == 642)
    {
        if(current_thread != INIT_TID){return NULL;}
        scheduler_lock();
        return NULL;
    }

// 643
// Unlock scheduler
    if (number == 643)
    {
        if(current_thread != INIT_TID){return NULL;}
        scheduler_unlock();
        return NULL;
    }

// Show device list.
    if (number == 770)
    {
        // #bugbug
        // Showing only one type of object,
        devmgr_show_device_list(ObjectTypeTTY);
        return NULL;
    }

// cpu usage for idle thread.
    if (number == 777){
        return (void *) profiler_percentage_idle_thread;
    }

// get host name
    if ( number == 801 ){
        return (void *) __gethostname ( (char *) arg2);
    }

// set host name
    if ( number == 802 ){
        return (void *) __sethostname ( (const char *) arg2); 
    }

// get user name
    if ( number == 803 ){
        return (void *) __getusername ( (char *) arg2);
    }

// set user name
    if ( number == 804 ){
        return (void *) __setusername ( (const char *) arg2); 
    }

// #todo
// supporting ptsname libc function
// get_ptsname
// #todo: Change the name to sys_ptsname()
// IN: fd do master, buffer em ring3 para o nome, buflen.
    if ( number == 808 ){
        return (void *) __ptsname ( (int) arg2, 
                            (char *) arg3, (size_t) arg4  ); 
    }

//#todo
//supporting ptsname_r libc function
// #todo: Change the name to sys_ptsname()
//IN: fd do master, buffer e buflen.
    if ( number == 809 ){
        return (void *) __ptsname ( (int) arg2, 
                            (char *) arg3, (size_t) arg4  ); 
    } 

// Get process stats given pid
// IN: pid, index
    if ( number == 880 ){
       return (void *) get_process_stats ( (pid_t) arg2, (int) arg3 );
    }

// get thread stats given tid
// IN: tid, number
    if ( number == 881 ){
        return (void *) GetThreadStats ( (int) arg2, (int) arg3 );
    }

// Get process name
// IN: PID, ubuffer.
    if ( number == 882 ){
        return (void *) getprocessname( (pid_t) arg2, (char *) arg3 );
    }

// Get thread name
    if ( number == 883 ){
        return (void *) getthreadname ( (int) arg2, (char *) arg3 );
    }

// alarm()
// See: sys.c
    if ( number == 884 ){
        return (unsigned long) sys_alarm( (unsigned long) arg2 );
    }

// 891
// Allocate shared ring3 pages.
    if ( number == 891 ){
        debug_print("__extra_services: 891, Allocate shared ring3 pages\n");
        return (void *) newos_alloc_shared_ring3_pages( (pid_t) current_process, (int) arg2 );
    }

// Setup the thread's surface rectangle.
    if ( number == 892 )
    {
        __setup_surface_rectangle( 
            (unsigned long) message_address[0],  //l 
            (unsigned long) message_address[1],  //t
            (unsigned long) message_address[2],  //w
            (unsigned long) message_address[3]); //h
        return NULL;
    }

// Invalidate the thread's surface rectangle.
    if ( number == 893 )
    {
        __invalidate_surface_rectangle();
        return NULL;
    }

    // 896,895 ... window stuff.

// Invalidate the whole screen
    if ( number == 896 )
    {
        invalidate_screen();
        //screen_is_dirty = TRUE;
        return NULL;
    }

// Create a rectangle.
// Testing compositor
    if (number == 897)
    {
        __service897();
        return NULL;
    }

// Enable prompt
    if ( number == 898 )
    {
        printf ("Prompt ON: Type something\n");
        printf("\n");
        ShellFlag = TRUE;
        return NULL;
    }

// Desable prompt
    if ( number == 899 )
    {
        printf ("Prompt OFF: Bye\n");
        printf("\n");
        ShellFlag = FALSE;
        return NULL;
    }

// is it full ?
// See: sys.c
// IN: fd
// OUT: -1= error; FALSE= nao pode ler; TRUE= pode ler.
    if ( number == 913 ){
        return (void *) sys_sleep_if_socket_is_empty(arg2);
    }

// get screen window.
// #todo. checar validade
    //if ( number == 955 ){  return (void *) gui->screen;  } 
    
    //if ( number == 956 ){  return (void *) gui->background; } 

// get main window.
// #todo. checar validade
    //if ( number == 957 ){ return (void *) gui->main; }  

// 970 - Create request.
// A interrupção n�o conseguir� retornar para a mesma thread.
// Chamar� o scheduler por conta pr�pria;
// IN: reason, reason
    if ( number == 970 )
    {
            create_request ( 
                (unsigned long) 15,      // number 
                (int) 1,                 // status 
                (int) 0,                 // timeout. 0=imediatamente.
                (int) current_process,   // target_pid
                (int) current_thread,    // target_tid
                NULL,                    // window 
                (int) 0,                 // msg  
                (unsigned long) arg2,    // long1  
                (unsigned long) arg3 );  // long2

        //wait_for_a_reason ( current_thread, (int) arg2 );
        return NULL;
    }

// api - load file (string ???)
// #todo: Tem que retornar algum identificador para a api.
// poderia ser um indice na tabela de arquivos abertos pelo processo.
// #todo: rever.
// See: kstdio.c
    //if ( number == 4002 ){
    //    return (void *) k_fopen ( (const char *) arg2, "r+" );
    //}

// Show root files system info.
    if ( number == 4444 )
    {
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
        return (void *) sys_connect ( 
                            (int) arg2, 
                            (const struct sockaddr *) arg3,
                            (socklen_t) arg4 );
    }

// accept()
// This is the unix standard method.
// Our major goal is to return the fd for the client socket file.
// #bugbug: Work in progress.
// fd, sockaddr struct pointer, addr len pointer.
    if ( number == 7002 ){
        return (void *) sys_accept ( 
                            (int) arg2, 
                            (struct sockaddr *) arg3, 
                            (socklen_t *) arg4 ); 
    }

// bind()
// fd, sockaddr struct pointer, addr len.
    if ( number == 7003 ){
        return (void *) sys_bind ( 
                            (int) arg2, 
                            (const struct sockaddr *) arg3,
                            (socklen_t) arg4 );
     }

// listen()
// fd, backlog
    if ( number == 7004 ){
        return (void *) sys_listen ( (int) arg2, (int) arg3 );  
    }

// Salvar um pid em uma das portas.
// IN: gramado port, PID
    if (number == 7006){
        return (void *) socket_set_gramado_port( (int) arg2, (int) arg3 );
    }

// sys_getsockname()
// fd, sockaddr struct pointer, addr len.
    if ( number == 7007 ){
        return (void *) sys_getsockname ( 
                            (int) arg2, 
                            (struct sockaddr *) arg3,
                            (socklen_t *) arg4 );
     }

// socket info
// IN: pid
    if ( number == 7008 ){
        show_socket_for_a_process( (int) arg2 );
        return NULL;
    }

// libc: shutdown() IN: fd, how
    if ( number == 7009 ){
        sys_socket_shutdown( (int) arg2, (int) arg3 );
        return NULL;
    }

// ioctl ()
// IN: fd, request, arg
// See: sys.c
    if ( number == 8000 ){
        return (void *) sys_ioctl ( 
                            (int) arg2, 
                            (unsigned long) arg3, 
                            (unsigned long) arg4 );
    }

// fcntl()
// See: sys.c    
    if ( number == 8001 ){
        return (void *) sys_fcntl ( 
                            (int) arg2, 
                            (int) arg3, 
                            (unsigned long) arg4 );
    }

// Setup stdin pointer
// See: kstdio
    if (number == 8002 )
    {
        // IN: fd
        return (void *) sys_setup_stdin((int) arg2);
    }

// test: pegando o endereço de um buffer de icone..
// queremos saber se ele eh compartilhado.
// shared_buffer_terminal_icon
// See: wm.c
    if (number == 9100){
        return (void *) ui_get_system_icon ( (int) arg2 );
    }

    // ...

// #deprecated
    if ( number == 9999 ){
        panic("__extra_services: [9999] #deprecated\n");
    }

// 
// ======================================
//

// Register callbacks sent by gwssrv.bin
    if ( number == 101234 )
    {
        return (void*) newos_register_ws_callbacks(
            (pid_t) current_process,
            (unsigned long) arg2,
            (unsigned long) arg3,
            (unsigned long) arg4 );
    }

// fail
    return NULL;
}


// Handler for the interrupt 0x80.
void *sci0 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    struct process_d  *p;
    struct thread_d  *t;

    unsigned long *message_address = (unsigned long *) arg2;

    unsigned long *a2 = (unsigned long*) arg2;
    unsigned long *a3 = (unsigned long*) arg3;
    unsigned long *a4 = (unsigned long*) arg4;

    char *aa2 = (char *) arg2;
    char *aa3 = (char *) arg3;
    char *aa4 = (char *) arg4;

    int desktopID=0;

    pid_t current_process = (pid_t) get_current_process();

//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci0_cpl;
    int cpl=-1;
    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("sci0: cpl");
    }

    if(cpl == 0){
        printf("number=%d\n",number);
        printf("pid=%d\n",current_process);
        //if(current_process != 0){
            panic("sci0: cpl 0\n");
        //}
    }
    if(cpl == 1){
        panic("sci0: cpl 1\n");
    }
    if(cpl == 2){
        panic("sci0: cpl 2\n");
    }
    if(cpl == 3){
        // ok
    }




    // #debug
    //debug_print("sc0:\n");
    //printf("sc0:\n");
    //refresh_screen();

    g_profiler_ints_gde_services++;

// Profiling in the process structure.

// Permission

    if (current_process<0 || current_process >= PROCESS_COUNT_MAX){
        panic("sci0: current_process\n");
    }

    p = (struct process_d *) processList[current_process];
    if ( (void*) p == NULL ){
        debug_print("sci0: p\n");
        panic("sci0: p\n");
    }
    if ( p->used != TRUE || p->magic != 1234 ){
        debug_print("sci0: p validation\n");
        panic("sci0: p validation\n");
    }

    if (p->personality != PERSONALITY_GRAMADO &&
        p->personality != PERSONALITY_GWS)
    {
        debug_print("sci0: Personality\n");
        panic      ("sci0: Personality\n");
    }

// Counting ...
    p->syscalls_counter++;

// exit
// Marcamos no processo nossa intenção de fechar.
// Marcamos na thread de controle nossa intenção de fechar.
// #todo: as outras threads do processo.
    if (number == SYS_EXIT)
    {
        debug_print("sci0: SYS_EXIT\n");
        p->exit_in_progress = TRUE;
        // Quando o scheduler passar por ela,
        // vai pular ela e marca-la como zombie.
        if( (void*) p->control != NULL ){
            if(p->control->magic==1234)
                p->control->exit_in_progress = TRUE;
        }
        return NULL;
    }

    // #debug
    // #todo: Explain it better.
    if (number == 4321)
    {
        printf ("4321: arg2 %x | arg3 %x | arg4 %x \n",arg2,arg3,arg4);
        invalidate_screen();
        //refresh_screen();
        return NULL;
    }


    // ================================
    // Color scheme.

    /*
    if ( (void *) CurrentColorScheme == NULL ){
        panic ("sci0: CurrentColorScheme\n");
    }else{
        if ( CurrentColorScheme->used  != TRUE || 
             CurrentColorScheme->magic != 1234 )
        {
            debug_print ("sci0: CurrentColorScheme\n");
            panic       ("sci0: CurrentColorScheme\n");
        }
        WindowColor           = CurrentColorScheme->elements[csiWindowBackground]; 
        WindowClientAreaColor = CurrentColorScheme->elements[csiWindow]; 
    };
    */

	// ================================
	// Desktop ID.

    // desktopID = (int) get_current_desktop_id ();


// Extra services

    if (number>256){
        return (void *) __extra_services(number,arg2,arg3,arg4);
    }

// Switch

    switch (number){

        case SYS_NULL:  
            return NULL;  
            break;

        // 1 (i/o) Essa rotina pode ser usada por 
        // um driver em user mode.
        // #todo: This operation needs permition.
        case SYS_READ_LBA: 
            ataReadSector ( 
                (unsigned long) arg2, (unsigned long) arg3, 0 , 0 ); 
            break;


        // 2 (i/o) Essa rotina pode ser usada por 
        // um driver em user mode.
        // #todo: This operation needs permition.
        case SYS_WRITE_LBA: 
            ataWriteSector ( 
                (unsigned long) arg2, (unsigned long) arg3, 0 , 0 ); 
            break;

        // 3 
        // Carregar um arquivo do disco para a mem�ria.
        // See: fs/fs.c
        // IN: name, flags, mode
        case SYS_READ_FILE:
            return (void *) sys_read_file_from_disk ( 
                                (char *) a2, 
                                (int)    arg3, 
                                (mode_t) arg4 ); 
            break;

        // 4 
        // Save file.
        // See: fs/fs.c
        // IN: name, size in sectors, size in bytes, adress, flag.
        case SYS_WRITE_FILE:
            sys_write_file_to_disk ( 
                (char *)        message_address[0],
                (unsigned long) message_address[1],
                (unsigned long) message_address[2],
                (char *)        message_address[3],
                (char)          message_address[4] ); 
            return NULL;
            break;

        // 5
        // See: sys.c 
        case SYS_VSYNC:
            sys_vsync();
            return NULL;
            break;

        // 6 - Put pixel. 
        // Coloca um pixel no backbuffer.
        // Isso pode ser usado por um servidor. 
        // cor, x, y, rop_flags.
        // todo: chamar kgws_backbuffer_putpixel
        case SYS_BUFFER_PUTPIXEL:
            backbuffer_putpixel ( 
                (unsigned long) a2,  // color
                (unsigned long) a3,  // x
                (unsigned long) a4,  // y
                0 );                 // rop_flags
            return NULL; 
            break;

        // 8 @todo: BugBug, aqui precisamos de 4 par�metros.
        case SYS_BUFFER_DRAWLINE:
            backbuffer_draw_horizontal_line ( 
                (unsigned long) a2, 
                (unsigned long) a3, 
                (unsigned long) a4, 
                COLOR_WHITE,
                0 );   // rop_flags 
            return NULL;
            break;

        // 9 - Draw a rectangle into the backbuffer.
        // see: _int128 in sw.asm.
        // see: rect.c
        //case SYS_BUFFER_DRAWRECT:
        case 9:
            //debug_print("sci0: [9]\n");
            backbuffer_draw_rectangle ( 
                (unsigned long) message_address[0],    //x 
                (unsigned long) message_address[1],    //y
                (unsigned long) message_address[2],    //width
                (unsigned long) message_address[3],    //height
                (unsigned int)  message_address[4],    //color
                (unsigned long) message_address[5] );  //rop_flags
            return NULL;
            break;

        // 10 - Refresh rectangle.
        case 10:
            //debug_print("sci0: [10]\n");
            refresh_rectangle ( 
                (unsigned long) message_address[0],    //x 
                (unsigned long) message_address[1],    //y
                (unsigned long) message_address[2],    //width
                (unsigned long) message_address[3] );  //height 
            return NULL;
            break;


        //11, Coloca o conte�do do backbuffer no LFB.
        case SYS_REFRESHSCREEN: 
            invalidate_screen();
            //refresh_screen();
            return NULL;
            break;


        //rede: 12,13,14,15

        // 16 - open()
        // In ring3, see: fcntl.c
        // In ring0, see: fs.c
        // IN: pathname, flags, mode
        // OUT: fd

        case SYS_OPEN:
            debug_print ("sci0: SYS_OPEN\n");
            return (void *) sys_open ( 
                                (const char *) arg2, 
                                (int)          arg3, 
                                (mode_t)       arg4 ); 
            break;


        // 17 - close()
        // See: sys.c
        // IN: fd
        case SYS_CLOSE:
            debug_print ("sci0: SYS_CLOSE\n");
            return (void *) sys_close( (int) arg2 );
            break;


        // 18 - read() 
        // See: sys.c
        case SYS_READ:
            return (void *) sys_read ( 
                                (unsigned int) arg2, 
                                (char *)       arg3, 
                                (int)          arg4 ); 
            break;

        // 19 - write()
        // See: sys.c
        case SYS_WRITE:
            return (void *) sys_write ( 
                                (unsigned int) arg2, 
                                (char *)       arg3, 
                                (int)          arg4 );  
            break;

        // Buffers support: 20~23 
        // Windows support: 24~28
 
        // 33 - free number.

        // 34
        // Setup cursor position for the current virtual console.
        case SYS_VIDEO_SETCURSOR: 
            newos_set_cursor ( 
                (unsigned long) arg2, 
                (unsigned long) arg3 );
            return NULL;
            break;

        // 35 - free number.
        // ...

        // 38 - get host name  
        case SYS_GETHOSTNAME:
            return (void *) __gethostname ( (char *) arg2 );
            break;

        // 39 - set host name 
        // #todo: This operation needs permition?
        case SYS_SETHOSTNAME:
            return (void *) __sethostname ( (const char *) arg2 ); 
            break;

        // 40 - get user name 
        case SYS_GETUSERNAME:
            return (void *) __getusername ( (char *) arg2 );
            break;
            
        // 41 - set user name 
        // #todo: This operation needs permition?
        case SYS_SETUSERNAME:
            return (void *) __setusername ( (const char *) arg2 ); 
            break;

        // 42 - livre
        // usar para manipulação de arquivo

        // 43 - Create an empty file.
        // See: fs.c
        case 43:
            return (void *) sys_create_empty_file( (char *) arg2 );
            break;

        // 44 - Create an empty directory.
        // See: fs.c
        case 44:
            return (void *) sys_create_empty_directory ( (char *) arg2 );
            break;

        // 45 - livre
        // usar para manipulação de arquivo ou diretório.

        // 46 ~ 48 (usar para cpu support)


        // 47 - livre
        // Show cpu info.
        case 47:
            //show_cpu_info();
            return NULL;
            break;

        // 48 - livre

        // 49 - livre
        // Show system info
        // See: sys.c
        case 49:
            sys_show_system_info((int) arg2);
            return NULL;
            break;

        // ...
        
        // 65
        // Put a char in the current virtual console.
        // see: console.c
        // IN: ch, console id.
        case SYS_KGWS_PUTCHAR:
            console_putchar ( (int) arg2, (int) arg3 ); 
            return NULL;
            break;


        //
        // ## EXIT ##
        //

        // 70 - Exit.
        // Atende a funcao exit() da libc. 
        // Criaremos um 'request' que sera atendido somente quando 
        // houver uma interrupcao de timer. 
        // Enquanto isso a thread deve esperar em um loop.
        // #bugbug: Pode haver sobreposicao de requests?
        // Assincrono.
        // IN: ??
        // #todo: 
        // Criar um wrapper em sys.c ou exit.c
        // See: request.c
        // Request number 12. (Exit thread)
  
        case SYS_EXIT:
            // #bugbug: Não podemos fechar a thread atual e
            // retornarmos de uma systemcall.
            // tem que agendar o exit através de um request.
            // Mas os requests estão desabilitados no momento.
            debug_print ("sci0: [TODO] SYS_EXIT\n");
            
            //create_request ( 
            //    (unsigned long) 12,      // number 
            //    (int) 1,                 // status 
            //    (int) 0,                 // timeout. 0=imediatamente.
            //    (int) current_process,   // target_pid
            //    (int) current_thread,    // target_tid
            //    NULL,                    // window 
            //    (int) 0,                 // msg  ??
            //    (unsigned long) arg2,    // long1  
            //    (unsigned long) arg3 );  // long2

            return NULL;
            break;
   

        // 72
        // See: ke/sys.c
        // Cria uma thread que fica no estado INITIALIZED.
        // Outra syscall tem que colocar ela em STANDBY.
        case SYS_CREATETHREAD:
            debug_print("sci0: [FIXME] SYS_CREATETHREAD\n");
            return (void *) sys_create_thread ( NULL,  NULL, NULL, 
                                arg2,             // init eip
                                arg3,             // init stack
                                current_process,  // pid
                                (char *) a4 );    // name
            break; 



        // 73
        // See: ke/sys.c
        // Cria um processo e coloca a thread primária pra rodar.
        // #bugbug: 
        // Na inicializacao do kernel, nos criamos um processo
        // usando create_process. Mas nesse momento estavamos usando
        // o diretorio de paginas do kernel e os registradores de segmento
        // pertenciam ao kernel.
        // Nessa tentativa de criarmos um processo usando create_process
        // as coisas estao um pouco diferentes ... provavelmente
        // estamos usando o diretorio de paginas do processo e os
        // registradores de segmento podem estar em ring3.
        // ?? Talvez poderiamos criar um request, da mesma maneira 
        // que fazemos com a criaçao de threads e o spawn.

        // #todo
        // Aqui no kernel, precisamos criar mais rotinas de suporte
        // a criacao de processos.
        // Temos poucas opçoes e tudo esta meio fora de ordem ainda.

        // syscall: 
        // arg2 = name
        // arg3 = process priority
        // arg4 = nothing
        
        case SYS_CREATEPROCESS:
            debug_print("sci0: [FIXME] SYS_CREATEPROCESS\n");
            return (void *) sys_create_process ( 
                                NULL,             // room
                                NULL,             // desktop
                                NULL,             // window
                                0,                // Reserved
                                arg3,             // priority
                                current_process,  // ppid
                                (char *) a2,      // name
                                RING3 );          // iopl 
            break;


        // 80 - Show current process info.
        // #todo: Mostrar em uma janela própria.
        // #todo: Devemos chamar uma função que 
        // mostre informações apenas do processo atual. 
        case SYS_CURRENTPROCESSINFO:
            show_currentprocess_info();
            return NULL;
            break;

        // 81
        // Get parent process id.
        // See: sys.c
        case SYS_GETPPID: 
            return (void *) sys_getppid();
            break;

        // 82 - Mostra informações sobre todos os processos.
        case 82:
            show_process_information();
            return NULL;
            break;

        // 83
        // Suporte a chamada da libc waitpid(...).
        // schedi.c
        // #todo.
        // TID, PID 
        // TID eh a thread atual.
        // PID veio via argumento.
        // IN: pid, status, option
        // #todo: Change the name to sys_xxxx
 
        case SYS_WAIT4PID: 
            debug_print("sci0: [FIXME] SYS_WAIT4PID\n");
            return (void *) do_waitpid( 
                                (pid_t) arg2, 
                                (int *) arg3, 
                                (int)   arg4 );
                
            //block_for_a_reason ( (int) current_thread, (int) arg2 ); //suspenso
            break;


        // 84 - livre.

        case 85:
        //case SYS_GETPID: 
            //return (void *) newos_getpid();
            return (void *) get_current_process();
            break;

        // 86 - livre.
        //case 86:
            //return (void*) 
            //break;

        // Testa se o processo é válido
        // se for valido retorna 1234
        // testando ...
        case SYS_88:   
            return (void *) processTesting (arg2);
            break;

        // ------------------
        // 90~99 Reservado para thread support

        // 94
        case SYS_STARTTHREAD:
            debug_print("sci0: SYS_STARTTHREAD\n");
            return (void *) newos_start_thread ( (struct thread_d *) arg2 );
            break;

        // ------------------

        // 100~109: free

        // 110
        // Use 'int'
        // # We need to return when a non-superuser process call this
        // service. We don't wanna hang the system in this case.
        // see: ke/sys.c
        int reb_ret=-1;
        case SYS_REBOOT: 
            debug_print("sci0: SYS_REBOOT\n");
            reb_ret = (int) sys_reboot();
            return (void *) (reb_ret & 0xFFFFFFFF);
            break;

        // 111
        // See: tlib.c
        // Get the next system message.
        // IN: buffer for message elements.
        case 111:
            //debug_print("sci0: 111\n");
            return (void *) sys_get_message( (unsigned long) &message_address[0] );
            break;

        // tlib.c
        // Post message to tid.
        // Asynchronous.
        // IN: tid, message buffer address.
        case 112:
            return (void *) sys_post_message_to_tid( (int) arg2, (unsigned long) arg3 );
            break;

        // 113~119: free

        // 120
        // Get a message given the index.
        // With restart support.
        case 120:
            //debug_print("sci0: \n");
            return (void *) sys_get_message2( 
                (unsigned long) &message_address[0], arg3, arg4 );
            break;

        // 124 (teste)
        // Defered system procedure call.
        // #todo: 
        // Precisamos armazenasr os argumentos em algum lugar.
        // #bugbug: Precisamos criar um request.
        case 124:
            kernel_request = KR_DEFERED_SYSTEMPROCEDURE;
            return NULL;
            break;


        // 126
        // Permitindo que drivers e servidores em usermode acessem
        // as portas.
        // #todo: This operation needs permition?
        // #bugbug
        // #todo: 
        // Tem que resolver as quest�es de privil�gios.
        // IN: bits, port

        case SYS_USERMODE_PORT_IN:
            return (void *) portsx86_IN ( 
                                (int) (arg2 & 0xFFFFFFFF), 
                                (unsigned short) (arg3 & 0xFFFF) );
            break;

        // 127
        // Permitindo que drivers e servidores em usermode acessem
        // as portas.
        // #todo: This operation needs permition?
        // #bugbug
        // #todo: 
        // Tem que resolver as quest�es de privil�gios.
        // IN: bits, port, value

        case SYS_USERMODE_PORT_OUT:
            portsx86_OUT ( 
                (int) arg2, 
                (unsigned short) (arg3 & 0xFFFF), 
                (unsigned int)   (arg4 & 0xFFFFFFFF) );
            return NULL;
            break;

        // 128~131: free

        // 132 - d_draw_char
        // Desenha um caractere e pinta o pano de fundo.
        // #todo: We do not have an api routine yet.
        // IN: x, y, c, fg color, bg color
        case 132: 
            d_draw_char(
                (unsigned long)  message_address[0],  //x
                (unsigned long)  message_address[1],  //y 
                (unsigned long)  message_address[2],  //c
                (unsigned long)  message_address[3],  //fg
                (unsigned long)  message_address[4] ); //bg
            return NULL;
            break;

        // 133 - d_drawchar_transparent
        // Desenha um caractere sem alterar o pano de fundo.
        // IN: x, y, color, c
        case 133:
            d_drawchar_transparent(
                (unsigned long)  message_address[0],   // x
                (unsigned long)  message_address[1],   // y 
                (unsigned long)  message_address[2],   // color
                (unsigned long)  message_address[3] ); // c
            return NULL;
            break;

        // 134~136: free

        // 137 - #deprecated.
        case SYS_GETCH:
            panic("SYS_GETCH: #deprecated\n"); 
            return NULL;
            break;

        // 138 - Get key state.
        // IN: vk.
        case 138:
            return (void *) keyboardGetKeyState( (unsigned char) arg2 );
            break;


        // 150~156 User and group support.

        // 152 - get uid
        case SYS_GETCURRENTUSERID:  
            return (void *) current_user; 
            break;
        // 154 - get gid
        case SYS_GETCURRENTGROUPID: 
            return (void *) current_group; 
            break;

        // 157~159: Security

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

        // ----------------
        // 160~169: Reserved to network support.

        // 161
        // get socket IP
        // Gramado API socket support. (not libc)
        case 161:
            return (void *) getSocketIPV4 ( (struct socket_d *) arg2 );
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
            return (void *) update_socket ( 
                                (struct socket_d *) arg2, 
                                (unsigned int)      (arg3 & 0xFFFFFFFF), 
                                (unsigned short)    (arg4 & 0xFFFF) );
            break;


        // ----------------

        // 170 - command 'pwd'.
        // Cada processo tem seu proprio pwd.
        // Essa rotina mostra o pathname usado pelo processo.
        // See: fs.c
        case SYS_PWD:
            // #test
            // Isso é um teste. Essa chamada não precisa disso.
            if (is_superuser() == TRUE )
            {
                debug_print("sci0: [SYS_PWD] Yes, I'm the super user.\n");
                printf     ("sci0: [SYS_PWD] Yes, I'm the super user.\n");
                refresh_screen();
            }
            sys_pwd();
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
            return NULL;
            break;

        // 173
        // Lista arquivos de um diretório, dado o número do disco,
        // o numero do volume e o número do diretório,
        // args in: disk id, volume id, directory id
        // See: fs.c
        case SYS_LISTFILES:
            fsListFiles ( arg2, arg3, arg4 );  
            return NULL;
            break;

        // 174
        case SYS_SEARCHFILE:
            debug_print ("sci0: SYS_SEARCHFILE\n");
            return (void *) search_in_dir ( 
                                (const char *) arg2, 
                                (unsigned long)   arg3 );
            break;


        // 175 - 'cd' command support.
        // +Atualiza o pathname na estrutura do processo atual.
        // +Atualiza o pathname na string global.
        // +Carrega o arquivo referente ao diretório atual.
        // See: fs.c
        case 175:
            debug_print ("sci0: 175\n");
            sys_cd_command ( (char *) arg2 );
            return NULL;
            break;

        // 176
        // Remove n nomes de diretório do pathname do processo 
        // indicado no argumento.
        // Copia o nome para a string global.
        case 176:
            debug_print ("sci0: 176\n");
            fs_pathname_backup ( current_process, (int) arg3 );
            return NULL;
            break;


        // 177 -  'dir' command.
        // Comando dir no shell.
        // Listando arquivos em um diretório dado seu nome.
        // #bugbug: Talvez tenhamos que usr a sci2.
        // See: fs.c
        case 177:
            debug_print ("sci0: [177]\n");
            fsList ( (const char *) arg2 );
            return NULL;
            break;

        // 178
        // See: sys.c
        case 178:
            return (void *) sys_get_file_size ( (unsigned char *) arg2 );
            break;

        //----------
        // 180~189: memory support.

        // 184
        // Pega o endereço do heap do processo dado seu id.
        // See: process.c
        case SYS_GETPROCESSHEAPPOINTER:
            debug_print("sci0: [184]\n");
            return (void *) GetProcessHeapStart ( (int) arg2 );
            break;

        //----------
        
        // 190~199: free
        // 200~209: free

        //----------

        // 210~219: terminal/virtual console support.

        //211
        case SYS_GETCURRENTTERMINAL:
            return (void *) current_terminal;
            break;

        //212
        case SYS_SETCURRENTTERMINAL:
            current_terminal = (int) arg2;
            break;

        //----------

        // 223 - Get sys time info.
        // informaçoes variadas sobre o sys time.
        case 223:
            return (void *) get_systime_info ( (int) arg2 );
            break;

        // 224, 225
        case SYS_GETTIME:  return (void *) get_time();  break;
        case SYS_GETDATE:  return (void *) get_date();  break;

// 226 - get
// Obs: 
// #todo: 
// Poderia ser uma chamada para configurar o posicionamento 
// e outra para configurar as dimens�es.
        case SYS_GET_KERNELSEMAPHORE:
            return (void *) __spinlock_ipc;
            break;

// 227 - close gate
// Entering critical section.
// See: process.c
        case SYS_CLOSE_KERNELSEMAPHORE:
            process_close_gate(current_process);
            return NULL;
            break;

// 228 - open gate
// Exiting critical section.
// #todo: Quando um processo fechar e estiver
// em sua sessão crítica, então devemos liberar
// essa flag. Isso fica mais fácil de lembrar se
// existir uma flag na estrutura de processo.
// See: process.c
        case SYS_OPEN_KERNELSEMAPHORE:
            process_open_gate(current_process);
            return NULL;
            break;

        //---------------------
        // 230~239: Reserved for tty support.

        // 236 - get tty id
        case 236:
            return (void *) current_tty;
            break;

        //---------------------
        
        // 240~249: Reserved for text editing support.
        
        // 240, 241
        case SYS_GETCURSORX:  return (void *) get_cursor_x(); break;
        case SYS_GETCURSORY:  return (void *) get_cursor_y(); break;
        // ...

        // =====================================
        // (250 ~ 255) - Info support.

        // 250
        case SYS_GETSYSTEMMETRICS:
            return (void *) sys_get_system_metrics ( (int) arg2 );
            break;

        default:
            __default_syscall_counter++;
            debug_print ("sci0: [FIXME] Default\n");
            printf      ("sci0: [FIXME] Default SYSCALL {%d}\n", number );
            invalidate_screen();
            //refresh_screen ();
            return NULL;
            break;
    };

done:
    return NULL;
}


// Handler for the interrupt 0x81.
void *sci1 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    debug_print ("sci1: [TODO]\n");

    pid_t current_process = (pid_t) get_current_process();

//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci1_cpl;
    int cpl=-1;
    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("sci1: cpl");
    }

    if(cpl == 0){
        panic("sci1: cpl 0\n");
    }
    if(cpl == 1){
        panic("sci1: cpl 1\n");
    }
    if(cpl == 2){
        panic("sci1: cpl 2\n");
    }
    if(cpl == 3){
        // ok
    }

// permission
    if (current_process<0 || current_process >= PROCESS_COUNT_MAX){
        panic("sci1: current_process\n");
    }

    switch (number){

    case 1:
        return NULL;
        break;  

    // ...

    default:
        __default_syscall_counter++;
        return NULL;
        break;
    };

    // #todo
    // Maybe kill the caller.

    panic ("sci1: [FIXME] default syscall\n");
    return NULL;
}


// Handler for the interrupt 0x82.
void *sci2 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    struct process_d  *p;
    struct thread_d  *t;

    // Array de longs.
    unsigned long *a2 = (unsigned long*) arg2;
    unsigned long *a3 = (unsigned long*) arg3;
    unsigned long *a4 = (unsigned long*) arg4;

    pid_t current_process = (pid_t) get_current_process();

//cpl
    unsigned long *cpl_buffer = (unsigned long *) &sci2_cpl;
    int cpl=-1;
    unsigned long tmp_cpl = (unsigned long) cpl_buffer[0];
    cpl = (int) (tmp_cpl & 3);

    if( cpl != 0 && cpl != 1 && cpl != 2 && cpl != 3 )
    {
        panic("sci2: cpl");
    }

    if(cpl == 0){
        panic("sci2: cpl 0\n");
    }
    if(cpl == 1){
        panic("sci2: cpl 1\n");
    }
    if(cpl == 2){
        panic("sci2: cpl 2\n");
    }
    if(cpl == 3){
        // ok
    }

    // debug_print("sci2: [TODO]\n");

// Profiling in the process structure.

// Permission

    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        panic("sci2: current_process\n");
    }

    p = (struct process_d *) processList[current_process];
    if ( (void*) p == NULL ){
        debug_print("sci2: p\n");
        panic("sci2: p\n");
    }
    if ( p->used != TRUE || p->magic != 1234 ){
        debug_print("sci2: p validation\n");
        panic("sci2: p validation\n");
    }

// Personality
    if (p->personality != PERSONALITY_GRAMADO &&
        p->personality != PERSONALITY_GWS)
    {
        debug_print("sci2: Personality\n");
        panic      ("sci2: Personality\n");
    }

// Counting syscalls ...
    p->syscalls_counter++;

//
// switch
//

//set magic
// #todo: This operation needs permition?
    if (number == 1){
        //CONSOLE_TTYS[fg_console].magic = arg2;
        return NULL;
    }

// Get magic
    if (number == 2){
        return (void*) CONSOLE_TTYS[fg_console].magic;
    }

// Get system metrics
    if (number == 3){
        return (void*) sys_get_system_metrics(arg2);
    }

    if (number == 4){
        debug_print("sci2: [4] ioctl\n");
        //return (void*) sys_ioctl ( (int) arg2, (unsigned long) arg3, (unsigned long) arg4 );
        return NULL;
    }

    if (number == 5){
        debug_print("sci2: [5] fcntl\n");
        return (void*) sys_fcntl ( (int) arg2, (int) arg3, (unsigned long) arg4 );
    }

// read() implementation.
// See: fs.c
    if (number == 18){
        //debug_print("sci2: [18] read\n");
        return (void *) sys_read ( 
                            (unsigned int) arg2, 
                            (char *)       arg3, 
                            (int)          arg4 );
    }

// write() implementation.
// See: fs.c
    if (number == 19){
        //debug_print("sci2: [19] write\n");
        return (void *) sys_write ( 
                            (unsigned int) arg2, 
                            (char *)       arg3, 
                            (int)          arg4 );
    }

    // ...    

// yield 
// See: ps/sched/schedi.c
// Set a flag that this thread will be preempted.

    if (number == 265){
        debug_print("sci2: [265] Yield\n");   
        yield(current_thread); 
        return NULL; 
    }

// 900
// Clona e executa o filho dado o nome do filho.
// O filho inicia sua execução do início da imagem.
// #bugbug: Isso às vezes falha na máquina real.
// #todo: Use more arguments.
// See: clone.c

    // IN: file name, parent pid, clone flags.
    // OUT: Child's PID.
    if ( number == 900 )
    {
        debug_print("sci2: [900] clone and execute\n");
        
        // #debug
        //printf("sci2: copy_process called by pid{%d}\n",current_process);
        //refresh_screen();
        
        return (void *) copy_process( 
                            (const char *) arg2, 
                            (pid_t) current_process, 
                            (unsigned long) arg3 );
    }

    // ioctl()
    // See: ke/sys.c
    // #bugbug: fd versus console number,
    if ( number == 8000 ){
        debug_print("sci2: [8000] ioctl\n");
        return (void *) sys_ioctl ( 
                            (int) arg2, 
                            (unsigned long) arg3, 
                            (unsigned long) arg4 );
    }

    // fcntl()
    // See: ke/sys.c
    if ( number == 8001 ){
        debug_print("sci2: [8001] fcntl\n");
        return (void *) sys_fcntl (
                            (int) arg2, 
                            (int) arg3, 
                            (unsigned long) arg4 );
    }

    // Clear the fg console background with a given color.
    // Do not change the colors.
    if (number == 8003)
    { 
        if(fg_console<0 || fg_console > 3){
            return NULL;
        }

        /*
        //#bugbug; cant change the color of the kernel consoles.
        //IN: bg color, fg color, console number.
        clear_console(
            (unsigned int) arg2,
            (unsigned int) CONSOLE_TTYS[fg_console].fg_color,
            fg_console );
        */

        //IN: bg color, fg color, console number.
        clear_console(
            (unsigned int) CONSOLE_TTYS[fg_console].bg_color,
            (unsigned int) CONSOLE_TTYS[fg_console].fg_color,
            fg_console );

        refresh_screen();
        return NULL;
    }
    
    // Change the foreground color of the current console.
    if (number == 8004)
    {
        if (fg_console<0 || fg_console > 3){
            return NULL;
        }
        
        // #bugbug
        // #deprecated
        // Cant change the kernel consoles.
        // Only the other ttys.
        // CONSOLE_TTYS[fg_console].fg_color = (unsigned int) arg2;
        
        return NULL;
    }

    // Configurando sincronização de leitura e escrita em arquivo.
    // principalmente socket.
    // A estrutura de arquivo contém uma estrutura de sincronização de leitura e escrita.
    // #ok: podemos usar ioctl
    // See: sys.c
    if ( number == 10000 )
    {
        debug_print("sci2: [10000] sys_set_file_sync\n");
        // IN: fd, request, data
        sys_set_file_sync( (int) arg2, (int) arg3, (int) arg4 );
        return NULL;
    }

// Pegando informação sobre sincronização de leitura e escrita de arquivos.
// principalmente para socket.
// A estrutura de arquivo contém uma estrutura de sincronização de leitura e escrita.
// #ok: podemos usar ioctl
// See: sys.c
// IN: fd, request

    if ( number == 10001 ){
        //debug_print("sci2: [10000] sys_get_file_sync\n");
        return (void*) sys_get_file_sync( (int) arg2, (int) arg3 );
    }



//=====
// See: sys.c
    // Set action.
    if ( number == 10002 ){
        sys_set_global_sync( (int) arg2, (int) arg3, (int) arg4 );
        return NULL;
    }
    // Get action.
    if ( number == 10003 ){
        return (void*) sys_get_global_sync( (int) arg2, (int) arg3 );
    }
    // Create sync.
    // OUT: sync id.
    if (number == 10004){
        return (void*) sys_create_new_sync();
    }
    // Get sync id.
    // Provisorio para teste
    if(number == 10005){
        return (void*) get_saved_sync();
    }
//=====

    // Set file sync action
    // IN: fd, request, data
    // see; fs.c
    if ( number == 10006 ){
        sys_set_file_sync( (int) arg2, (int) arg3, (int) arg4 );
        return NULL;
    }
    // Get file sync action
    // IN: fd, request
    // see; fs.c
    if ( number == 10007 ){
        return (void*) sys_get_file_sync( (int) arg2, (int) arg3 );
    }





// Get the tid of the current thread.
    if ( number == 10010 ){
        //debug_print("sci2: [10010] GetCurrentTID\n");
        return (void*) GetCurrentTID();
    }

// foreground thread
// Set the foreground thread tid.
// #todo: We need a method for that.
// IN: arg2=tid.
    if ( number == 10011 )
    {
        debug_print("sci2: [10011] set foreground thread tid\n");
        //Change the priority of the old foreground thread?
        //set_thread_priority( threadList[foreground_thread], PRIORITY_NORMAL);
        if (arg2<0 || arg2>=THREAD_COUNT_MAX){ return NULL; }  //fail
        t = (struct thread_d *) threadList[arg2];
        if( (void*) t == NULL ){ return NULL; }; //fail
        if(t->used != TRUE) { return NULL; }; //fail
        if(t->magic != 1234){ return NULL; }; //fail
        //Giving more credits. But the scheduler will balance
        //it at the and of the round.
        //t->quantum  = QUANTUM_FIRST_PLANE;
        t->quantum  = (QUANTUM_MAX + 88);
        t->priority = PRIORITY_MAX;
        
        //#test
        //t->signal |= 1<<(SIGALRM-1);
        //t->signal |= 1<<(SIGKILL-1);
        
        foreground_thread = (int) arg2;
        
        // #deprecated
        // it will select the next input reponder.
        // set_input_responder_tid(foreground_thread);
        return NULL;
    }

    // Get Init PID
    if(number == 10020){ return (void*) GRAMADO_PID_INIT; }
    // Get Init TID
    if(number == 10021){ return (void*) INIT_TID; }

// #test
// shared memory 2mb surface.
// ring 3.
    if (number == 22777)
    {
        if (g_extraheap3_initialized==TRUE)
            return (void*) g_extraheap3_va;
        return NULL;
    }

// Callback support.
// see: ts.c
// see: pit.c
// arg2 = address
// arg3 = pid
// arg4 = signature
    pid_t ws_pid = -1;
    unsigned long r3_handler=0;
    if(number == 44000)
    {
        // Somente o window server pode chamar esse serviço.
        ws_pid = (pid_t) socket_get_gramado_port(GRAMADO_WS_PORT);
        // Checando se caller foi o window server.
        if (current_process != ws_pid){
            panic("sci2: [44000] current_process!=ws_pid\n");
        }
        // Check signature
        if (arg4 != 1234){
            panic("sci2: [44000] Signature\n");
        }
        // PID
        if (arg3 != ws_pid){
            panic("sci2: [44000] Invalid PID\n");
        }
        // nao foi inicializado pela inicialização do kenrel.
        if ( ws_callback_info.initialized != TRUE ){
            panic("sci2: [44000] callback support Not initialized\n");
        }
        // Se ele ja esta pronto para efetuarmos o iretq
        // é porque tem alguma coisa errada.
        if ( ws_callback_info.ready == TRUE ){
            panic("sci2: [44000] called again\n");
        }
        // Enable for the first time.
        // Configuramos o callback em ts.c.
        r3_handler = (unsigned long) arg2;
        setup_callback( (unsigned long) r3_handler );
        return NULL;
    }


// Counter

    __default_syscall_counter++;

// #todo
// Maybe kill the caller. 
// Maybe return.

    panic ("sci2: [FIXME] default syscall \n");
    return NULL;
}


/*
 * __servicePutChar:
 *     Movendo para terminal/output.c 
 *     Coloca um char usando o 'terminal mode' de stdio selecionado 
 * em _outbyte.
 * stdio_terminalmode_flag = n�o transparente.
 */

// #bugbug
// Where is the prototype?

static void __servicePutChar(int c)
{
// Put char into the fg console.

    if (fg_console < 0){
        return;
    }
    console_putchar ( (int) c, fg_console );
}

void newos_reboot(unsigned long reboot_flags)
{
    sys_reboot();
    //hal_reboot();
}


// See: kgwm.c
int 
newos_register_ws_callbacks(
    pid_t pid,
    unsigned long callback0,
    unsigned long callback1,
    unsigned long callback2 )
{

// Who can do this?
// Only the gwssrv.bin.

    if(pid != KernelProcess->pid){
        panic("newos_register_ws_callbacks: pid");
    }

    //#todo: filter parameters
    wmRegisterWSCallbacks(
        (unsigned long) callback0,
        (unsigned long) callback1,
        (unsigned long) callback2 );

    return 0;
}


unsigned long newos_get_system_metrics(int index)
{
    if (index<0){
        return 0;
    }
    return (unsigned long) doGetSystemMetrics ( (int) index );
}

pid_t newos_getpid(void)
{
    return (pid_t) sys_getpid();
}


// REAL (coloca a thread em standby para executar pela primeira vez.)
// MOVEMENT 1 (Initialized --> Standby).
int newos_start_thread( struct thread_d *thread )
{

// structure
    if( (void*) thread == NULL )
        return (-1);
    if(thread->used != TRUE)
        return (-1);
    if(thread->magic != 1234)
        return (-1);

    SelectForExecution ( (struct thread_d *) thread );
    return 0;
}

int newos_get_current_runlevel(void)
{
    return (int) current_runlevel;
}

unsigned long newos_get_memory_size_mb(void)
{
    unsigned long __mm_size_mb = 
        (unsigned long) (memorysizeTotal/0x400);

    return (unsigned long) __mm_size_mb;
}

// Usado pelo malloc em ring3.
void *newos_alloc_shared_ring3_pages(pid_t pid, int number_of_bytes)
{
    int number_of_pages=0;

// #todo
// pid premission

// #todo
// Check max limit

    if ( number_of_bytes < 0 )
        number_of_bytes = 4096;

    if ( number_of_bytes <= 4096 ){
        return (void *) allocPages(1);
    }

// Alinhando para cima.
    number_of_pages = (int) ((number_of_bytes/4096) + 1);

    return (void *) allocPages(number_of_pages);
}


// 34 - Setup cursor for the current virtual console.
// See: core/system.c
// IN: x,y
// #todo: Essa rotina dever pertencer ao user/

void newos_set_cursor( unsigned long x, unsigned long y )
{

// #todo
// Maybe check some limits.

    set_up_cursor ( 
        (unsigned long) x, 
        (unsigned long) y );
}



//
// End
//


