
// sci.c
// Handlers for the system interrupts.

#include <kernel.h>  

//#define SERVICE_NUMBER_MAX  255


// prototype
void *gde_extra_services ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 );


// Services abouve 256.
// Helper function called by sci0().
void *gde_extra_services ( 
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


    //Deprecated.
    //Outro n�mero fará esse trabalhao.
    if ( number == 260 ){
        //return (void *) sys_read ( 
        //                    (unsigned int) arg2, 
        //                    (char *)       arg3, 
        //                    (int)          arg4 );
    }
     
    //Deprecated.
    //Outro n�mero fará esse trabalhao.
    if ( number == 261 ){
        //return (void *) sys_write ( 
        //                    (unsigned int) arg2, 
        //                    (char *)       arg3, 
        //                    (int)          arg4 );
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


    // Returns the current runlevel.
    if ( number == 288 ){
        return (void *) current_runlevel;
    }


    // Serial debug print.
    // See: sci/sys/sys.c
    if ( number == 289 ){
        return (void *) sys_serial_debug_printk ( (char *) arg2 );
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
        return (void *) sys_lseek ( 
                            (int)   arg2, 
                            (off_t) arg3, 
                            (int)   arg4 );
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


    // libc: shutdown() IN: fd, how
    if ( number == 7009 ){
        sys_socket_shutdown( (int) arg2, (int) arg3 );
        return NULL;
    }


    // fcntl()
    // See: sci/sys/sys.c    
    if ( number == 8001 ){
        return (void *) sys_fcntl ( 
                            (int) arg2, 
                            (int) arg3, 
                            (unsigned long) arg4 );
    }


    // chamado por gde_get_pid na api.
    // See: system.c
    if ( number == 9999 ){
        return (void *) system_get_pid ( (int) arg2 );
    }

// fail
    return NULL;
}



// unit2: Do the job.
void *sci0 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    struct process_d  *p;
    unsigned long *message_address = (unsigned long *) arg2;

    unsigned long *a2 = (unsigned long*) arg2;
    unsigned long *a3 = (unsigned long*) arg3;
    unsigned long *a4 = (unsigned long*) arg4;

    char *aa2 = (char *) arg2;
    char *aa3 = (char *) arg3;
    char *aa4 = (char *) arg4;

    int desktopID=0;


    // #debug
    debug_print("sc0:\n");
    //printf("sc0:\n");
    //refresh_screen();

    g_profiler_ints_gde_services++;

    // Profiling in the process structure.

    if (current_process<0)
        panic("sci0: current_process\n");

    p = (struct process_d *) processList[current_process];

    if ( (void*) p == NULL )
        panic("sci0: p\n");

    // Counting ...
    p->syscalls_counter++;
    
    
    // #debug
    if (number == 4321){
        printf ("4321: arg2 %x | arg3 %x | arg4 %x \n",arg2,arg3,arg4);
        refresh_screen();
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



// extra services

    if ( number > 256 ){
        return (void *) gde_extra_services(number,arg2,arg3,arg4);
        return NULL;
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
            my_read_hd_sector ( 
                (unsigned long) arg2, (unsigned long) arg3, 0 , 0 ); 
            break;


        // 2 (i/o) Essa rotina pode ser usada por 
        // um driver em user mode.
        // #todo: This operation needs permition.
        case SYS_WRITE_LBA: 
            my_write_hd_sector ( 
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
        // See: sci/sys/sys.c 
        case SYS_VSYNC:
            sys_vsync();  
            return NULL;
            break;

        // 6 - Put pixel. 
        // Coloca um pixel no backbuffer.
        // Isso pode ser usado por um servidor. 
        // cor, x, y, 0.
        // todo: chamar kgws_backbuffer_putpixel
        case SYS_BUFFER_PUTPIXEL:
            backbuffer_putpixel ( 
                (unsigned long) a2, 
                (unsigned long) a3, 
                (unsigned long) a4, 
                0 );
            return NULL; 
            break;

        // 8 @todo: BugBug, aqui precisamos de 4 par�metros.
        case SYS_BUFFER_DRAWLINE:
            my_buffer_horizontal_line ( 
                (unsigned long) a2, 
                (unsigned long) a3, 
                (unsigned long) a4, 
                COLOR_WHITE ); 
            return NULL;
            break;

        // 9 - Draw rectangle.
        // #todo: #BugBug, aqui precisamos de 5 par�metros.
        // passe o buffer como parametro
        //case SYS_BUFFER_DRAWRECT:
        case 9:
            drawDataRectangle ( 
                (unsigned long) message_address[0],    //x 
                (unsigned long) message_address[1],    //y
                (unsigned long) message_address[2],    //width
                (unsigned long) message_address[3],    //height
                (unsigned long) message_address[4] );  //color
            return NULL;
            break;


        // 10 - Refresh rectangle.
        case 10:
            refresh_rectangle ( 
                (unsigned long) message_address[0],    //x 
                (unsigned long) message_address[1],    //y
                (unsigned long) message_address[2],    //width
                (unsigned long) message_address[3] );  //height 
            return NULL;
            break;


        //11, Coloca o conte�do do backbuffer no LFB.
        case SYS_REFRESHSCREEN: 
            refresh_screen();
            return NULL;
            break;


        //rede: 12,13,14,15

        // 16 - open()
        // In ring0, see: sci/sys/sys.c
        // In ring3, see: fcntl.c
        // IN: pathname, flags, mode
        //OUT: fd

        case SYS_OPEN:
            debug_print ("$ --------------- \n");
            debug_print ("sci0: SYS_OPEN $\n");
            return (void *) sys_open ( 
                                (const char *) arg2, 
                                (int)          arg3, 
                                (mode_t)       arg4 ); 
            break;


        // 17 - close()
        // See: sys.c
        // IN: fd
        case SYS_CLOSE:
            debug_print ("$ ------------ \n");
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

        // BUFFERS  20 21 22 23 
 
 
        // 33 - free number.


        // 34 - Setup cursor for the current virtual console.
        // See: core/system.c
        // IN: x,y
        // #todo: Essa rotina dever pertencer ao user/
        case SYS_VIDEO_SETCURSOR: 
            set_up_cursor ( 
                (unsigned long) arg2, 
                (unsigned long) arg3 );
            return NULL;
            break; 

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
            return (void *) sys_create_empty_file ( (char *) arg2 );
            break;

        // 44 -Create an empty directory.
        // See: fs.c
        case 44:
            return (void *) sys_create_empty_directory ( (char *) arg2 );
            break;


        // 45 - livre
        // usar para manipulação de arquivo ou diretório.
        
        
        // 46 ~ 49 (usar para cpu support)


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
            sys_show_system_info ((int) arg2);
            return NULL;
            break;


        // A lot of window services.
        // ...

        // 65
        // Put a char in the current virtual console.
        // see: tty/console.c
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
        //#todo: 
        // Criar um wrapper em sci/sys.c ou kernel/exit.c
        // See: request.c
        // Request number 12. (Exit thread)
  
        case SYS_EXIT:
            debug_print ("sci0: SYS_EXIT\n");
            create_request ( 
                (unsigned long) 12,      // number 
                (int) 1,                 // status 
                (int) 0,                 // timeout. 0=imediatamente.
                (int) current_process,   // target_pid
                (int) current_thread,    // target_tid
                NULL,                    // window 
                (int) 0,                 // msg  ??
                (unsigned long) arg2,    // long1  
                (unsigned long) arg3 );  // long2
            return NULL;
            break;
   

        // 72
        // See: sci/sys/sys.c
        // Cria uma thread e coloca ela pra rodar.
        case SYS_CREATETHREAD:
            debug_print("sci0: [FIXME] SYS_CREATETHREAD\n");
            return (void *) sys_create_thread ( NULL,  NULL, NULL, 
                                arg2,             // init eip
                                arg3,             // init stack
                                current_process,  // pid
                                (char *) a4 );    // name
            break; 



        // 73
        // See: sci/sys/sys.c
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
                                NULL, NULL, NULL, 
                                0, arg3,        //res, priority
                                0, (char *) a2, //ppid, name
                                RING3 ); 
            break;




		//80 Show current process info.
		//#todo: Mostrar em uma janela pr�pria.
		//#todo: Devemos chamar uma fun��o que mostre informa��es 
		//apenas do processo atual. 
        case SYS_CURRENTPROCESSINFO:
            show_currentprocess_info();
            return NULL;
            break;


        // 81
        // See: sci/sys/sys.c
        case SYS_GETPPID: 
            return (void *) sys_getppid();
            break;

        // 82 - Mostra informações sobre todos os processos.
        case 82:
            show_process_information();
            return NULL;
            break;

        // 83
        // Suporte � chamada da libc waitpid(...).
        // schedi.c
        // #todo.
        // TID, PID 
        // TID eh a thread atual.
        // PID veio via argumento.
        // IN: pid, status, option
 
        case SYS_WAIT4PID: 
            debug_print("sci0: [FIXME] SYS_WAIT4PID\n");
            return (void *) do_waitpid( 
                                (pid_t) arg2, 
                                (int *) arg3, 
                                (int)   arg4 );
                
            //block_for_a_reason ( (int) current_thread, (int) arg2 ); //suspenso
            break;


        // 84 - livre.

        // 85
        // See: sci/sys/sys.c
        case 85:
        //case SYS_GETPID: 
            return (void *) sys_getpid();
            break;

        // 86 - livre.

        // Testa se o processo é válido
        // se for valido retorna 1234
        // testando ...
        case SYS_88:   
            return (void *) processTesting (arg2);
            break;

        // free: 91 92 93


        // 94
        //REAL (coloca a thread em standby para executar pela primeira vez.)
        // * MOVEMENT 1 (Initialized --> Standby).
        case SYS_STARTTHREAD:
            debug_print("sci0: SYS_STARTTHREAD\n");
            //t = (struct thread_d *) arg2;
            //sys_SelectForExecution (t);
            SelectForExecution ( (struct thread_d *) arg2 );
            return NULL;
            break;


        // 110 - Reboot.
        // See: sci/sys/sys.c
        case SYS_REBOOT: 
            debug_print("sci0: SYS_REBOOT\n");
            sys_reboot();
            panic("sci0: SYS_REBOOT!");
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

		// 126
		// Permitindo que drivers e servidores em usermode acessem
		// as portas.
        // #todo: This operation needs permition?
        case SYS_USERMODE_PORT_IN:
			// #bugbug
			// #todo: 
			// Tem que resolver as quest�es de privil�gios.
            //bits, port
            return (void *) portsx86_IN ( 
                                (int) arg2, 
                                (unsigned long) arg3 );
            break;



		// 127
		// Permitindo que drivers e servidores em usermode acessem
		// as portas.
        // #todo: This operation needs permition?
        case SYS_USERMODE_PORT_OUT:
			//#bugbug
			//#todo: 
			// Tem que resolver as quest�es de privil�gios.
			//bits, port, value
            portsx86_OUT ( 
                (int) arg2, 
                (unsigned long) arg3, 
                (unsigned long) arg4 );
            return NULL;
            break;

        // 132 - d_draw_char
        // Desenha um caractere e pinta o pano de fundo.
        // #todo: We do not hae an api routine yet.
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

		// 135 - livre.
		// 136 - livre.

        // 137
        // Isso eh um metodo alternativo de pegar input.
        // Ainda esta sobre avaliaçao.
        // Isso eh usado pela biblioteca stdio em user mode
        // na funçao 'getchar()'
        // Isso tambem eh usado por gde_getchar em libcore/ em grass/
        // ??? Pega caractere no stdin do teclado.
        // ?? Isso funciona.
        // #bugbug: >>>> Rever isso.
        
        // See: core/ps/thread.c
        case SYS_GETCH:  
            return (void *) thread_getchar();
            break;

        // 138 - get key state.
        case 138:
            return (void *) keyboardGetKeyState ( (unsigned char) arg2 );
            break;


        // 152 - get uid
        case SYS_GETCURRENTUSERID:  
            return (void *) current_user; 
            break;

        // 153

        // 154 - get gid
        case SYS_GETCURRENTGROUPID: 
            return (void *) current_group; 
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
            return (void *) update_socket ( 
                                (struct socket_d *) arg2, 
                                (unsigned long)     arg3, 
                                (unsigned short)    arg4 );
            break;


        // 164 - livre. 
        // socket stuff
        // case 165:  break;
        // socket stuff
        // case 166:  break;
        // 167 - livre.


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
        // Lista arquivos de um diret�rio, dado o n�mero do disco,
        // o numero do volume e o n�mero do diret�rio,
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
        // Remove n nomes de diret�rio do pathname do processo 
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
        // See: sci/sys/sys.c
        case 178:
            return (void *) sys_get_file_size ( (unsigned char *) arg2 );
            break;


        // 184
        // Pega o endereço do heap do processo dado seu id.
        // See: process.c
        case SYS_GETPROCESSHEAPPOINTER:
            debug_print("sci0: [184]\n");
            return (void *) GetProcessHeapStart ( (int) arg2 );
            break;

        //211
        case SYS_GETCURRENTTERMINAL:
            return (void *) current_terminal;
            break;

        //212
        case SYS_SETCURRENTTERMINAL:
            current_terminal = (int) arg2;
            break;

        // 223 - get sys time info.
        // informaçoes variadas sobre o sys time.
        case 223:
            return (void *) get_systime_info ( (int) arg2 );
            break;

        // 224, 225
        case SYS_GETTIME:  return (void *) get_time();  break;
        case SYS_GETDATE:  return (void *) get_date();  break;

        // Obs: 
        // #todo: 
        // Poderia ser uma chamada para configurar o posicionamento 
        // e outra para configurar as dimens�es.
        //226 - get
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


		// 232 - livre
		// 233 - livre
		// 234 - livre 
		// 235 - livre

        // tty ... 236 237 238 239.

        // 236 - get tty id
        case 236:  return (void *) current_tty;  break;
        
        // 240, 241
        case SYS_GETCURSORX:  return (void *) get_cursor_x();  break;
        case SYS_GETCURSORY:  return (void *) get_cursor_y();  break;

        // ...

        default: 
            debug_print ("sci0: [FIXME] Default\n");
            printf      ("sci0: [FIXME] Default SYSCALL {%d}\n", number );
            refresh_screen ();
            return NULL;
            break;
    };

done:
    return NULL;
}


// unit2: Do the job.
void *sci1 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    debug_print ("sci1: [TODO]\n");

    switch (number){

        case 1:  return NULL;  break;  

        // ...
        
        default:
            break;
    };

    // #todo
    // Maybe kill the caller.

    panic ("sci1: [FIXME] default syscall\n");
    return NULL;
}


// unit2: Do the job.
void *sci2 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
    struct process_d  *p;

    // Array de longs.
    unsigned long *a2 = (unsigned long*) arg2;
    unsigned long *a3 = (unsigned long*) arg3;
    unsigned long *a4 = (unsigned long*) arg4;

    debug_print("sci2: [TODO]\n");

    // Profiling in the process structure.

    // #todo: limite superior
    if (current_process<0){
        panic("sci2: current_process\n");
    }

    p = (struct process_d *) processList[current_process];

    if ( (void*) p == NULL ){
        panic("sci2: p\n");
    }

    if ( p->used != TRUE || p->magic != 1234 ){
        panic("sci2: p validation\n");
    }

    // Counting syscalls ...
    p->syscalls_counter++;

//
// switch
//

    //set magic
    // #todo: This operation needs permition?
    if ( number == 1 ){
        CONSOLE_TTYS[fg_console].magic = arg2;
        return NULL;
    }

    //get magic
    if ( number == 2 ){
        return (void*) CONSOLE_TTYS[fg_console].magic;
    }

    if ( number == 3 ){
        debug_print("sci2: [3] metrics\n");
        //return (void*) systemGetSystemMetrics(arg2);
    }
        
    if ( number == 4 ){
        debug_print("sci2: [4] ioctl\n");
        //return (void*) sys_ioctl ( (int) arg2, (unsigned long) arg3, (unsigned long) arg4 );
    }

    
    if ( number == 5 ){
        debug_print("sci2: [5] fcntl\n");
        return (void*) sys_fcntl ( (int) arg2, (int) arg3, (unsigned long) arg4 );
    }

    // sys_read
    if ( number == 18 ){
        debug_print("sci2: [18] read\n");
        return (void *) sys_read ( 
                            (unsigned int) arg2, 
                            (char *)       arg3, 
                            (int)          arg4 );
    }

    // sys_write
    if ( number == 19 ){
        debug_print("sci2: [19] write\n");
        return (void *) sys_write ( 
                            (unsigned int) arg2, 
                            (char *)       arg3, 
                            (int)          arg4 );
    }

    // ...    

    if (number == 265){
        //debug_print("sci2: [FIXME] Service 265 suspended!\n");   
        yield (current_thread); 
        return NULL; 
    }

	// 900
	// Clona e executa o filho dado o nome do filho.
	// O filho inicia sua execução do início da imagem.
	// #bugbug: Isso às vezes falha na máquina real.
	// #todo: Use more arguments.
	// See: See: ps/action/clone.c
	// See: process.c

    // IN: name, dir address.
    if ( number == 900 ){
        debug_print("sci2: [900] clone and execute\n");
        return (void *) clone_and_execute_process( (const char *) arg2 );
    }

    // fcntl()
    // See: sci/sys/sys.c    
    if ( number == 8001 ){
        debug_print("sci2: [8001] fcntl\n");
        return (void *) sys_fcntl (
                            (int) arg2, 
                            (int) arg3, 
                            (unsigned long) arg4 );
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
    if ( number == 10001 )
    {
        debug_print("sci2: [10000] sys_get_file_sync\n");
        // IN: fd, request
        return (void*) sys_get_file_sync( (int) arg2, (int) arg3 );
    }

    // get the tid of the current thread.
    if ( number == 10010 )
    {
        debug_print("sci2: [10010] GetCurrentThreadId\n");
        return (void*) GetCurrentThreadId();
    }
    
    // Se the foreground thread tid.
    // #todo: We need a method for that.
    if ( number == 10011 )
    {
        debug_print("sci2: [10011] set foreground thread tid\n");
        foreground_thread = (int) arg2;
        return NULL;
    }

    // #todo
    // Maybe kill the caller.
    panic ("sci2: [FIXME] default syscall \n");
    return NULL;
}

/*
 ***********************
 * servicesPutChar:
 *     Movendo para terminal/output.c 
 *     Coloca um char usando o 'terminal mode' de stdio selecionado 
 * em _outbyte.
 * stdio_terminalmode_flag = n�o transparente.
 */

// #bugbug
// Where is the prototype?

void servicesPutChar ( int c )
{
    if ( fg_console < 0 ){
        // #todo: Message
        return;
    }

    console_putchar ( (int) c, fg_console );
}



void nothing4(void){}
void nothing5(void){}
void nothing6(void){}
void nothing7(void){}
void nothing41(void){}
void nothing51(void){}
void nothing61(void){}
void nothing71(void){}



















