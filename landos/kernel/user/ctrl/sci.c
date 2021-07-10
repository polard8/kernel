

#include <kernel.h>  

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




void *sci0 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    struct process_d *p;

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
    printf("sc0:\n");
    refresh_screen();

    g_profiler_ints_gde_services++;

    // Profiling in the process structure.

    if (current_process<0)
        panic("sci0: current_process\n");

    p = (struct process_d *) processList[current_process];

    if ( (void*) p == NULL )
        panic("sci0: p\n");

    // Counting ...
    p->syscalls_counter++;


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

        // ...

        //11, Coloca o conte�do do backbuffer no LFB.
        case SYS_REFRESHSCREEN: 
            refresh_screen();
            return NULL;
            break;


        //rede: 12,13,14,15

        
        // 18 - read() 
        // See: sys.c
        case SYS_READ:
            return NULL;
            //return (void *) sys_read ( 
            //                    (unsigned int) arg2, 
            //                    (char *)       arg3, 
            //                    (int)          arg4 );  
            break;


        // 19 - write()
        // See: sys.c
        case SYS_WRITE:
            return NULL;
            //return (void *) sys_write ( 
            //                    (unsigned int) arg2, 
            //                    (char *)       arg3, 
            //                    (int)          arg4 );  
            break;

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


        // 65
        // Put a char in the current virtual console.
        // see: tty/console.c
        // IN: ch, console id.
        case SYS_KGWS_PUTCHAR:
            console_putchar ( (int) arg2, (int) arg3 ); 
            return NULL;
            break;



        // 81
        // See: sci/sys/sys.c
        case SYS_GETPPID: 
            return (void *) sys_getppid();
            break;



        // 84 - livre.

        // 85
        // See: sci/sys/sys.c
        case 85:
        //case SYS_GETPID: 
            return (void *) sys_getpid();
            break;

        // 86 - livre.

        // 110 - Reboot.
        // See: sci/sys/sys.c
        case SYS_REBOOT: 
            debug_print("sci0: SYS_REBOOT\n");
            sys_reboot();
            panic("sci0: SYS_REBOOT!");
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


        // 152 - get uid
        case SYS_GETCURRENTUSERID:  
            return (void *) current_user; 
            break;
 
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

        // 224 - get time
        case SYS_GETTIME:  return (void *) get_time();  break;
        // 225 - get date
        case SYS_GETDATE:  return (void *) get_date();  break;


		// 232 - livre
		// 233 - livre
		// 234 - livre 
		// 235 - livre

        // tty ... 236 237 238 239.

        // 236 - get tty id
        case 236:  return (void *) current_tty;  break;
        
        // 240
        case SYS_GETCURSORX:  return (void *) get_cursor_x();  break;
        
        // 241
        case SYS_GETCURSORY:  return (void *) get_cursor_y();  break;


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



void *sci1 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
	//nothing
	return NULL;
}

void *sci2 ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{
	//nothing
	return NULL;
}




void nothing4(void){}
void nothing5(void){}
void nothing6(void){}
void nothing7(void){}
void nothing41(void){}
void nothing51(void){}
void nothing61(void){}
void nothing71(void){}



















