/*
 * File: tty.c
 * 
 * Arquivo principal do Gerenciador de fluxo de caractere.
 * Driver para interagir com os processos.
 * O kernel recebeu o caractere de um dispositivo fisico
 * e enviou esse caractere para o driver tty, então o driver tty deve 
 * enviar esse caractere para o processo adequado...
 *o inverso também, o processo envia o caractere para o driver tty e 
 * o driver tty deve enviar o caractere para o dispositivo de saíta adequado 
 * atravéz do kernel.
 *
 * #obs: 
 * Vamos montar dispositivos de terminal virtual em /DEV
 */


#include <kernel.h> 



// Ponteiros para os dispositivos
// que a tty atua.
// sendo que o primeiro dispositivo (canal) é o console.

unsigned long tty_table[4];  //os 4 consoles virtuais.



/*
int 
tty_read_from_of ( unsigned int fd, 
           char *buffer, 
           int nr );

int 
tty_read_from_of ( unsigned int fd, 
           char *buffer, 
           int nr )
{
    // pega o objeto tty na lista de arquivos abertos.
    // chama read
    //__tty_read( ... );
    
    return -1;
}
*/



/*
int 
tty_write_from_of ( unsigned int fd, 
           char *buffer, 
           int nr );

int 
tty_write_from_of ( unsigned int fd, 
           char *buffer, 
           int nr )
{
    // pega o objeto tty na lista de arquivos abertos.
    // chama read
    //__tty_write( ... );
    
    return -1;
}
*/




// reads into ttyList[] descriptor.
int 
tty_read_ttyList ( 
    unsigned int channel, 
    char *buffer, 
    int nr )
{
    struct tty_d *__tty;
    
    // Não leremos os Consoles virtuais 
    if ( channel < 4 ){
        printf ("tty_read_ttyList: invalid channel\n");
        refresh_screen();
        return -1;
    }
    
     __tty = (struct tty_d *) ttyList[channel];

     return (int) __tty_read ( (struct tty_d *) __tty, 
                      (char *) buffer, 
                      (int) nr );
}


int 
tty_write_ttyList ( 
    unsigned int channel, 
    char *buffer, 
    int nr )
{

    struct tty_d *__tty;
    
    // Não leremos os Consoles virtuais 
    if ( channel < 4 ){
        printf ("tty_write_ttyList: invalid channel\n");
        refresh_screen();
        return -1;
    }
    
    __tty = (struct tty_d *) ttyList[channel];

    return (int) __tty_write ( (struct tty_d *) __tty, 
                     (char *) buffer, 
                     (int) nr );
}

            

int 
__tty_read ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr )
{

    if ( (void *) tty == NULL ){
        debug_print ("__tty_read: tty\n");
        return -1;
    }
   
    
    if ( nr <= 0 ){
        printf ("__tty_read: nr \n");
        refresh_screen();
        return -1;
    }

    
    //
    // Limits
    //

   
    //
    // Buffer NULL
    //
    
    
    if ( (char *) buffer == NULL ){
         panic ("__tty_read: invalid buffer \n");
    }
    
 
    //
    // File   (stdin)
    //
    
    // Arquivo de leitura.
 
    // #importante
    // Não usaremos mais o termo stream no kernel.
    // Isso então é um arquivo apontando pela tty.
    // Podemos usar o buffer da tty.   
            
    if ( (void *) tty->_buffer == NULL ){
         printf ("__tty_read: Invalid tty _buffer\n");
         refresh_screen();
         return -1;
    }


    //
    // _base. 
    //
    
    // A base do arquivo que serve de buffer.
    

    if ( (void *) tty->_buffer->_base == NULL ){
         printf ("__tty_read: invalid _base \n");
         refresh_screen();
         return -1;
    }


    // #todo
    // temos dois modos de leitura a serem considerados.
    // O raw e o canonical.
    
    
    //
    // Copy
    //

    // Copia da tty de leitura para o buffer indicado pelo aplicativo.
           
    printf ("__tty_read: Copiando para o buffer. \n");
    refresh_screen ();
 
    memcpy ( (void *) buffer, (const void *) tty->_buffer->_base, nr ); 
    
    
    //#debug
    printf ( "debug_read >>>%s \n", buffer );
    refresh_screen ();
           
    return nr; 
}



// writes into ttyList[] descriptor.
// Escrever no buffer de uma tty qualquer da ttyList
// o descritor seleciona uma tty em ttyList[] e 
// escreve em tty->stdout->_base

int 
__tty_write ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr )
{

    if ( (void *) tty == NULL ){
        debug_print ("__tty_write: tty\n");
        return -1;
    }


    if ( nr <= 0 ){
        printf ("__tty_write: nr \n");
        refresh_screen();
        return -1;
    }



    //
    // Limits
    //



    //
    // Buffer NULL
    //
    
    
    if ( (char *) buffer == NULL ){
         panic ("__tty_write: invalid buf \n");
    }


   
        
    //
    //  File (stdout) 
    //        
    
    // Checando a validade do arquivo.
    // O arquivo da tty de origem da transferência.

    if ( (void *) tty->_buffer == NULL ){
        printf ("__tty_write: Invalid tty _buffer\n");
        refresh_screen();
        return -1;
    }


    //
    // _base
    //
    
    // Essa é a base do arquivo da tty de origem.

    if ( (void *) tty->_buffer->_base == NULL ){
        printf ("__tty_write: * invalid _base \n");
        refresh_screen();
        return -1;
    }


    //
    // Copy 1.
    //

    // Copiando do buffer para o arquivo da tty de origem.

    printf ("__tty_write: Copiando para tty->_buffer->_base \n");
    refresh_screen();

    memcpy ( (void *) tty->_buffer->_base, (const void *) buffer, nr ); 
    
    

    //#debug
    printf ( "debug_write >>>%s \n", tty->_buffer->_base );
    refresh_screen ();
    
    
    //
    // Send message to parent.
    //
    
    //Envia um alerta para o pai
    //indicando a tty pra ele ler.
    
    // current process. quem escreveu;
    struct process_d * __p;
    
    __p = (struct process_d *) processList[current_process];
    

    if ( (void *) __p == NULL )
        panic("__tty_write: __p\n");


    if ( __p->used != 1 || __p->magic != 1234 )
        panic("__tty_write: validation\n");
    
    
    // #bugbug
    // Atenção. O mecanismo de clonagem
    // pode gerar um ppid errado ?
    
    // o parent 
    int PPID = (int) __p->ppid;


    if (PPID<0)
        panic("__tty_write: PPID\n");


    printf ("__tty_write: PID  %d\n", __p->pid);
    printf ("__tty_write: PPID %d\n", __p->ppid);
    refresh_screen();

    
    //
    // alert!!
    //
    
    
    // #importante
    // Ok, nesse momento o sender pode enviar vários
    // tipos de mensagem, essa mensagem deve ser indicada
    // no argumento dessa função.
    // 444 - ler a mensagem de string que está no buffer.
    // 445 - O buffer contém vários argumentos.
    // 446 - o buffer é um buffer com algum protocolo de network.
    // ??? - Muitas mensagens podem ser criadas nesse caso,
    // transformando essa rotina numa poderosa ferramenta de comunicação
    // entre processos.
    // Os soquetes da libc podem tirar proveito desse mecanismo.
    // ??? nesse caso o processo filho está mandando mensagem
    // para o processo pai, Mas podemos criar rotinas que
    // enviem mensagem pra quanquer processo, inclusive para ws e wm.
    // ??? - #importante: O próprio kernel pode usar uma rotina 
    // como essa para enviar mensagens para processos servidores 
    // ou drivers.
    
    
    
    unsigned long message_address[8];
 
     message_address[0] = (unsigned long) 0; //w
     message_address[1] = (unsigned long) 444;   // alerta que tem que ler na ttyList[] do processo indicado.
     //message_address[2] = (unsigned long) __p->pid;
     //message_address[3] = (unsigned long) __p->pid;   

     message_address[2] = (unsigned long) 0;
     message_address[3] = (unsigned long) 0;   

    
    //send
    ipc_send_message_to_process ( (unsigned long) &message_address[0], 
               (int) PPID );
    

    
    // #bugbug
    // Não devemos copiar aqui, pois assim damos a chance
    // do processo pai escrever diretamente na tty do filho
    // caso ele obtenha sua identificação.
    

    //printf( "DONE\n");
    //refresh_screen();        
 
    return nr;
}


// Escreve na tty de um processo alvo e envia uma mensagem pra
// ele saber o que fazer com o que ele ler no buffer.
// Talvez seja possível fazer o mesmo
// em outros modulos, esses mesmos argumentos mais outros.
// Essa rotina dentro do kernel copia os dados que estão num buffer 
// para dentro do buffer da tty e em seguida envia um alerta para um 
// processo alvo, dizendo que ele tem dados no buffer de sua tty. 
// Os últimos argumentos são enviados para o processo na hora do alerta 
// pra dizer pra ele que tipo de dados tem no buffer e o que deve 
// fazer com eles.
// ---
// Da pra enviar todo tipo de coisa, pois o buffer é do tamanho que 
// você quizer. Inclusive da pra enviar protocolos de rede.

// #importante
// É possível criar muitas variações dessa rotina.
// E implementá-las em outros módulos.

int 
tty_send_message ( 
    int target_pid, 
    char *buffer, 
    int nr,
    int msg,
    unsigned long long1,
    unsigned long long2 )
{

    struct process_d * __p;
    struct tty_d *tty;

    
    if ( target_pid<0 )
        return -1;

   
    __p = (struct process_d *) processList[target_pid];
    
    if ( (void *) __p == NULL )
        panic("__tty_write: __p\n");


    if ( __p->used != 1 || __p->magic != 1234 )
        panic("__tty_write: validation\n");


    if (__p->pid < 0)
        panic("__tty_write: PID\n");         


    //pega a tty do processo alvo.
    tty = __p->tty;


    if ( (void *) tty == NULL )
        panic("__tty_write: tty\n");         


    //#todo check validation.
    

    if ( nr <= 0 ){
        printf ("__tty_write: nr \n");
        refresh_screen();
        return -1;
    }



    //
    // Limits
    //



    //
    // Buffer NULL
    //
    
    
    if ( (char *) buffer == NULL ){
         panic ("__tty_write: invalid buf \n");
    }


   
        
    //
    //  File (stdout) 
    //        
    
    // Checando a validade do arquivo.
    // O arquivo da tty de origem da transferência.

    if ( (void *) tty->_buffer == NULL ){
        printf ("__tty_write: Invalid tty _buffer\n");
        refresh_screen();
        return -1;
    }


    //
    // _base
    //
    
    // Essa é a base do arquivo da tty de origem.

    if ( (void *) tty->_buffer->_base == NULL ){
        printf ("__tty_write: * invalid _base \n");
        refresh_screen();
        return -1;
    }


    //
    // Copy 1.
    //

    // Copiando do buffer para o arquivo da tty de origem.

    printf ("__tty_write: Copiando para tty->_buffer->_base \n");
    refresh_screen();

    memcpy ( (void *) tty->_buffer->_base, (const void *) buffer, nr ); 
    
    

    //#debug
    printf ( "debug_write >>>%s \n", tty->_buffer->_base );
    refresh_screen ();


    //
    // alert!!
    //
    
    
    // #importante
    // Ok, nesse momento o sender pode enviar vários
    // tipos de mensagem, essa mensagem deve ser indicada
    // no argumento dessa função.
    // 444 - ler a mensagem de string que está no buffer.
    // 445 - O buffer contém vários argumentos.
    // 446 - o buffer é um buffer com algum protocolo de network.
    // ??? - Muitas mensagens podem ser criadas nesse caso,
    // transformando essa rotina numa poderosa ferramenta de comunicação
    // entre processos.
    // Os soquetes da libc podem tirar proveito desse mecanismo.
    // ??? nesse caso o processo filho está mandando mensagem
    // para o processo pai, Mas podemos criar rotinas que
    // enviem mensagem pra quanquer processo, inclusive para ws e wm.
    // ??? - #importante: O próprio kernel pode usar uma rotina 
    // como essa para enviar mensagens para processos servidores 
    // ou drivers.
    
    
    
    unsigned long message_address[8];
 
    message_address[0] = (unsigned long) 0; //w
    message_address[1] = (unsigned long) msg;   // alerta que tem que ler na ttyList[] do processo indicado.
    message_address[2] = (unsigned long) long1;
    message_address[3] = (unsigned long) long2;   

    
    //send
    ipc_send_message_to_process ( (unsigned long) &message_address[0], 
               (int) __p->pid );
    

    
    // #bugbug
    // Não devemos copiar aqui, pois assim damos a chance
    // do processo pai escrever diretamente na tty do filho
    // caso ele obtenha sua identificação.
    

    //printf( "DONE\n");
    //refresh_screen();        
 
    return nr;
}






// copia a estrutura de termios.
// para o aplicativo em ring3 poder ler.
int tty_gets ( struct tty_d *tty, struct termios *termiosp ){


    if ( (void *) tty == NULL )
        return -1;
         
    
    if ( (void *) termiosp == NULL )
        return -1;


    // Copia a estrutura term da tty na estrutura de termios 
    // que está em ring3.
    memcpy ( termiosp, &tty->termios, sizeof(struct termios));

    return 0;
}


// channel is a fd in the file list of a process.
int 
tty_read ( 
    unsigned int channel, 
    char *buffer, 
    int nr )
{
    debug_print ("tty_read: [TODO]\n");
    return -1;
}


// channel is a fd in the file list of a process.
int 
tty_write ( 
    unsigned int channel, 
    char *buffer, 
    int nr )
{
    debug_print ("tty_write: [TODO]\n");
    return -1;
}



//copia de ring3 para o kernel.
int 
tty_sets ( 
    struct tty_d *tty, 
    int options, 
    struct termios *termiosp )
{
    int ret = -1;


    if ( (void *) tty == NULL )
        return -1;
        
    
    if (options < 0)
        return -1;
        
    
    if ( (void *) termiosp == NULL )
        return -1;

    //
    // Options.
    //

    switch (options)
    {

        // Now. The change occurs immediately. 
        case TCSANOW:
            memcpy ( &tty->termios, termiosp, sizeof(struct termios) );
            break;

        // ...

		default:
			//ret = -EINVAL;
			ret = -1;
			break;
    };


    return (ret);
}
 
 
 
// #todo
// See: 
// syslib/libcore/termios.h
// syslib/libcore/sys/ioctls.h
int tty_ioctl ( int fd, unsigned long request, char *arg ){

    debug_print ("tty_ioctl: TODO\n");
    
    switch (request)
    {
        case TCGETS:
            debug_print ("TCGETS\n");
            //ret = tty_gets(&tty, (struct termios *)arg);
            return -1;
            break;


        case TCSETS:
            debug_print ("TCSETS\n");
            //ret = tty_sets(&tty, IOCTL_MINOR(cmd), (struct termios *)arg);
            return -1;
            break;


        case TCFLSH:
            debug_print ("TCFLSH\n");
            return -1;
            break;
            
        //case ?:
            //break;
        
      
        default:
            return -1;
            break;
    };
	    //cases:
	    
	    
	    //ret = tty_clear(&tty);
	
    return -1;
}


/*
int tty_rewind_buffer ( struct tty_d *tty );
int tty_rewind_buffer ( struct tty_d *tty )
{

    if ( (void *) tty == NULL )
        return -1;
       
    if ( (void *) tty->_buffer == NULL )
        return -1;
        
    if ( (void *) tty->_buffer->_base == NULL )
        return -1;

    if ( (void *) tty->_buffer->_p == NULL )
        return -1;
        
    if ( tty->_buffer->_p < tty->_buffer->_base )
        return -1;

    tty->_buffer->_p = tty->_buffer->_base;
    
    return 0; 
}
*/






/*
int init_dev(int dev);
int init_dev(int dev)
{}
*/


/*
void release_dev (int dev, file *f);
void release_dev (int dev, file *f)
{}
*/





/*
void 
tty_struct_init ( struct tty_d *tty, dev_t dev);
void 
tty_struct_init ( struct tty_d *tty, dev_t dev)
{}
*/


/*
//#todo
struct tty_d *get_tty (int tty_id);
struct tty_d *get_tty (int tty_id)
{
	//#todo filtros.
	
	if ( tty_id < 0)
	    return NULL;
	    
    
    return (struct tty_d *) ptsList[tty_id];
}
*/



/*
FILE *tty_get_file (struct tty_d *tty);
FILE *tty_get_file (struct tty_d *tty)
{}
*/


//#todo
//sinalizar todas os processos que pertençam ao mesmo grupo.
/*
void tty_intr (struct tty_d *tty, int signal);
void tty_intr (struct tty_d *tty, int signal)
{
    int i;

    if ( (void *) tty == NULL )
        return;

    // o grupo ao qual a tty pertence.
	//if (tty->pgrp <= 0)
		//return;

    //sinalizar todos os processos em p->signal[x] = ?; ou t->signal[x] = ?;
	//for (i=0;i<NR_TASKS;i++)
		//if (task[i] && task[i]->pgrp==tty->pgrp)
			//task[i]->signal |= 1<<(signal-1);
}
*/




void tty_stop (struct tty_d *tty)
{

    if ( (void *) tty == NULL )
        return;

    //se ela já está parada.
    if (tty->stopped == 1)
        return;

    tty->stopped = 1;
}


void tty_start (struct tty_d *tty)
{
    if ( (void *) tty == NULL )
        return;

    //Se não está parada.
    if (tty->stopped == 0)
        return;

    tty->stopped = 0;
}



void tty_reset_termios ( struct tty_d *tty )
{
    //#todo: Limits messages
    if ( (void *) tty == NULL )
        return;



    // See: ttydef.h
     
    tty->termios.c_iflag = BRKINT | ICRNL | IXON;
    tty->termios.c_oflag = OPOST;
    tty->termios.c_cflag = CREAD | CS8;
    tty->termios.c_lflag = ECHO | ECHOE | ECHOK | ICANON | ISIG;

    tty->termios.c_ispeed = B9600;
    tty->termios.c_ospeed = B9600;

    // ^d
    // 4 - (CEOF: <Ctrl>d or ASCII EOT)
    tty->termios.c_cc[VEOF] = CEOF;
    
    // Bugbug overflow ??
    // ? - 0xff  
    // 2;  //BS
    //tty->termios.c_cc[VEOL]   = CEOL;    
    
    
    // ^h
    // (CERASE: <Ctrl>h or ASCII BS)
    // 0x7f ??
    // 8;  //BS
    tty->termios.c_cc[VERASE] = CERASE;
      

    // ^c
    // (CINTR: rubout or ASCII DEL)   
    //3;  //EOI  
    tty->termios.c_cc[VINTR]  = CINTR;   
    
    // ^u
    // (CKILL: <Ctrl>u or ASCII NAK)
    // ? - 1;  //BS
    tty->termios.c_cc[VKILL]  = CKILL;   
    

    // ^\
    // (CQUIT: <Ctrl>\ or ASCII FS) 
    // ? - 0x1C
    //28; //FS
    tty->termios.c_cc[VQUIT]  = CQUIT;   
    

    // ^z 
    // (CSUSP: <Ctrl>z or ASCII SUB) 
    //26; //BS
    tty->termios.c_cc[VSUSP]  = CSUSP;   



    // #todo
	//tty->win_size.ws_col = 80;
	//tty->win_size.ws_row = 25;
}




/*
//#cancelado. Deletar isso.
// Checar no tty atual se tem que atualizar a tela,
// a linha ou o char.
// mostrar o conteúdo do arquivo stdout.
void check_CurrentTTY (void);
void check_CurrentTTY (void){

	int refresh = 0;
	
	int i;
	int len = 0;
	
	//se devemos pintar alguma coisa ou não.
	if ( CurrentTTY->stdout_status == 1 )
	{
		// stdout
		// Não há o que pintar para stdout
		if (CurrentTTY->stdout_last_ptr == stdout->_p )
		{
			//printf ("check_CurrentTTY: ptr error nada pra pintar\n");
			//refresh_screen ();			
		    goto done;
		}
		
		//#debug
		//printf ("last = %x ", CurrentTTY->stdout_last_ptr);
		//printf ("ptr = %x  \n", stdout->_ptr);
		
		//pintar de que jeito?
	    switch (CurrentTTY->stdout_update_what)
		{
			// update char	
			//case 1:	
			//	printf ("%c", *CurrentTTY->stdout_last_ptr);
			//	CurrentTTY->stdout_last_ptr++;
			//	CurrentTTY->stdout_last_ptr = stdout->_ptr;
				//printf ("%c", stdout->_ptr);
				//refresh_rectangle ( g_cursor_x, g_cursor_y, 20, 20 ); 
			//	refresh = 1;
			//	break;
				
			// update line	
			//case 2:	
			//	break;
				
			// update window. file	
			default:
			//case 3:
				//calcula quantos chars devemos pintar.
				len = (stdout->_p - CurrentTTY->stdout_last_ptr);
				//pintamos todos os chars.
				for (i=0; i<len; i++)
				{
					//Isso funciona.
				    printf ("%c", *CurrentTTY->stdout_last_ptr);
				    CurrentTTY->stdout_last_ptr++;				
				}
				CurrentTTY->stdout_last_ptr = stdout->_p;
				CurrentTTY->print_pending = 0; //não temos mais print pendente
				
				refresh = 1;
				break;
				
			// nothing
			//default:
			    //break;	
		}
		
		int status = 0;
		// refresh tty window
		if (refresh == 1)
		{
		    status = show_window_rect (CurrentTTY->window);
			
			if (status == 1)
			{
				printf ("check_CurrentTTY: invalid tty window\n");
				refresh_screen ();
			}
		}
	}

//#todo: delete label.	
done:

	//reset
    CurrentTTY->stdout_status = 0;
    CurrentTTY->stdout_update_what = 0;
}
*/



/*
int set_current_tty (int tty_id);
int set_current_tty (int tty_id){
	
	struct tty_d *tty;
	
	if ( tty_id < 0 || tty_id > 7 )
	{
	    panic ("set_current_tty: tty_id");
		//return -1;
	}
	
	tty = (struct tty_d *)  ptsList[tty_id];
	
	if ( (void *) tty == NULL )
	{
		panic ("set_current_tty: tty");
		//return -1;
	}else{
	
	    if ( tty->used != 1 || tty->magic != 1234 )
		{
			panic ("set_current_tty: validation");
			//return -1;
		}
		
		//OK
		CurrentTTY = tty;
	}
	
	return 0;
}
*/


/*
void reset_tty ( struct tty_d *tty );
void reset_tty ( struct tty_d *tty ){
   //#todo resetar os elementos da estrutura.
}
*/


/*
//procura um slot livre na lista de ttys
int tty_find_empty_slot ();
int tty_find_empty_slot (){
 //#todo
}
*/


//#todo criar uma tty ldisc. 
struct ttyldisc_d *ttyldisc_create (void) 
{
    struct ttyldisc_d *__ttyldisc;


    __ttyldisc = (struct ttyldisc_d *) kmalloc ( sizeof(struct ttyldisc_d) );
    
    if ( (void *) __ttyldisc == NULL ){
        //debug_print("...");
        return NULL;
        
    }else{
        __ttyldisc->used = 1;
        __ttyldisc->magic = 1234;
    };


    return (struct ttyldisc_d *) __ttyldisc;
}



//#todo: deletar uma tty ldisc
int ttyldisc_delete ( struct ttyldisc_d *tty_ldisc ){


    // Nothing to do.
    if ( (void *) tty_ldisc == NULL ){
        //debug_print("...");
        return -1;

    }else{
         
         //#bugbug: fast way
         //free (tty_ldisc);
         
         //reusar
         tty_ldisc->magic = 216;
    };
    
    return 0;
}




//#todo criar uma tty driver.  
struct ttydrv_d *ttydrv_create (void) {

    struct ttydrv_d *__ttydrv;
    
    __ttydrv = (struct ttydrv_d *) kmalloc ( sizeof(struct ttydrv_d) );
    
    if ( (void *) __ttydrv == NULL ){
        //debug_print("...");
        return NULL;

    }else{

        __ttydrv->used = 1;
        __ttydrv->magic = 1234;
    };


    return (struct ttydrv_d *) __ttydrv;
}



//#todo: deletar uma tty driver
int ttydrv_delete ( struct ttydrv_d *tty_driver ){

    // Nothing to do.
    if ( (void *) tty_driver == NULL ){
        //debug_print("...");
        return -1;

    }else{
         
         //#bugbug: fast way
         //free (tty_driver);
         
         //reusar
         tty_driver->magic = 216;
    };
    
    return 0;
}



 
//#todo criar uma tty. 
struct tty_d *tty_create (void) {

    struct tty_d *__tty;
    int i=0;

    // Encontra slot um vazio.
    // Mas começando em 10.
    // Porque os primeiros 4 dispositivos são reservados para console virtual
    // podemos reservar os 10 primeiros.
    
    // Lista de tty e não de console.
    for (i=4; i<256; i++)
    {
        __tty = (struct tty_d *) ttyList[i];
        
        if ( (void *) __tty == NULL )
            goto _ok;
    };


_fail: 
    panic ("tty_create: No more slots!\n");   
    //return NULL;


_ok:

    __tty = (struct tty_d *) kmalloc ( sizeof(struct tty_d) );
    
    if ( (void *) __tty == NULL ){
        panic ("tty_create: __tty kmalloc fail \n");   
        //return NULL;
 
    }else{

        // Object control;
        __tty->objectType = ObjectTypeTTY;
        __tty->objectClass = ObjectClassKernelObjects;

        __tty->index = i;
        
        __tty->used = 1;
        __tty->magic = 1234;
        
        //
        // files
        //
        
        __tty->_buffer = (file *) newPage();
        __tty->stdin  = (file *) newPage (); 
        __tty->stdout = (file *) newPage (); 
        __tty->stderr = (file *) newPage (); 
        
        
        if ( (void *) __tty->_buffer == NULL ||
             (void *) __tty->stdin == NULL   ||
             (void *) __tty->stdout == NULL  ||
             (void *) __tty->stderr == NULL  )
        {
            panic ("tty_create: streams fail\n");
        }

        //precisa validar
        __tty->_buffer->used = 1;
        __tty->_buffer->magic = 1234;         
        __tty->stdin->used = 1;
        __tty->stdin->magic = 1234;
        __tty->stdout->used = 1;
        __tty->stdout->magic = 1234;
        __tty->stderr->used = 1;
        __tty->stderr->magic = 1234;
        

        //
        // o buffer do arquivo. (_base)
        //
        
        __tty->_buffer->_base  = (char *) newPage (); 
        __tty->stdin->_base  = (char *) newPage (); 
        __tty->stdout->_base = (char *) newPage (); 
        __tty->stderr->_base = (char *) newPage (); 

        //#todo checar, e inicializar os outros elementos.
        
        // register
        
        // ??
        // #debug
        if ( i >= 64){
            panic ("tty_create: Overflow\n");
        }
        
        ttyList[i] = (unsigned long) __tty;
        
        
        return (struct tty_d *) __tty;
    };


    panic ("tty_create: Crazy error!\n");   
    //return NULL;
}




//#todo: 
int tty_delete ( struct tty_d *tty ){

    // Nothing to do.
    if ( (void *) tty == NULL ){
        debug_print ("tty_delete: tty\n");
        //debug_print("...");
        return -1;
 
    }else{
         
         //#bugbug: fast way
         //free (tty);
         
         //reusar
         tty->magic = 216;
         
         tty_stop(tty);
         
         //...
    };
    
    return 0;
}

 
/*
 ***********************************
 * ttyInit:
 *     Inicialização do módulo.
 */

// #bugbug
// Essa rotina está inicializando a tty CurrentTTY e atribuindo
// o id tty_id para ela.

// #importante
// No momento estamos apenas inicializando o primeiro tty
// e usando o mesmo fluxo padrão que o teclado usa.

// #obs
// Isso é chamado por create_logon na inicialização do sistema.

int ttyInit (int tty_id){

    int i=0;

    debug_print ("ttyInit:\n");


    // #todo
    // Rever esse limite.
    // Todos os drivers de dispositivos precisarão de tty.
    // todos os terminais virtuais.
    // O linux usa terminais virtuais que vão até ctl+al+f7. 
    // Mas ttys tem muitas.

    // #importante
    // O sistema terá 8 terminais
    // e terá vários pseudo terminais. pts. - Stands for pseudo terminal slave.


    if ( tty_id < 0 || tty_id > 32 )
    {
        panic ("ttyInit: tty_id");
    }


	//
	// CurrentTTY
	//

    CurrentTTY = (struct tty_d *) kmalloc ( sizeof(struct tty_d) );

    if ( (void *) CurrentTTY == NULL ){
        panic ("ttyInit:");

    }else{

        CurrentTTY->index = tty_id;
        CurrentTTY->used = 1;
        CurrentTTY->magic = 1234;
        
        CurrentTTY->user_session = usession0;
        CurrentTTY->room = room0;
        CurrentTTY->desktop = desktop0;

        //
        // Window.
        //
        
        // Configurando uma janela básica, pra não ficar null.
        //CurrentTTY->window = gui->main;
        CurrentTTY->window = NULL;

        CurrentTTY->left = 0; 
        CurrentTTY->top = 0;
        //CurrentTTY->width = 0;
        //CurrentTTY->height = 0;	

        // Standard stream. 



        CurrentTTY->stdin = current_stdin;
        CurrentTTY->stdout = current_stdout;
        CurrentTTY->stderr = current_stderr;


        CurrentTTY->stdout_status = 0;
        CurrentTTY->stdout_update_what = 0;	




	    //
	    // buffer circular.
	    //

	    //base
	    CurrentTTY->stdout_last_ptr = CurrentTTY->stdout->_p;
	
	    //limite
	    CurrentTTY->stdout_limit = (CurrentTTY->stdout->_p + CurrentTTY->stdout->_lbfsize);
	
	    //fazer o mesmo para os outros dois arquivos.
	    //...	    
	    
	   //
	   // Limpando a lista!
	   //
	   
	   //isso ja foi inicializado em logo.c
        //for (i=0; i<256; i++)
	    //{ ttyList[i] = 0;}
	
	    ttyList[tty_id] = (unsigned long) CurrentTTY;
	       
	       
	    // More ?    
    };
    
    
    
    //


    return 0;
}



int tty_init_module (void){

    int i=0;


    for (i=0; i<256; i++)
    {
        ttyList[i] = 0;
    };


    //...
    
    return 0;
}


//
// End.
//




