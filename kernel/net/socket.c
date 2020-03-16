/*
 * File: socket.c
 *     SOCKET network access protocol.
 */


#include <kernel.h>



/*
int socket_create (struct file_d *f, int domain, int type, int protocol);
int socket_create (struct file_d *f, int domain, int type, int protocol)
{
    return -1;
}
*/


/*
int socket_udp_initialize (struct socket_d *sock);
int socket_udp_initialize (struct socket_d *sock)
{
    if( (void*) sock == NULL )
        return -1;
        

    sock->objectType
    sock->objectClass


    sock->type = SOCK_DGRAM;
    
        
    sock->_file = -1;
    
    sock->ip_long = 0;
    sock->port = 0;

    //...
    
    return 0;
}
*/


/*
int socket_tcp_initialize (struct socket_d *sock);
int socket_tcp_initialize (struct socket_d *sock)
{
    if( (void*) sock == NULL )
        return -1;
        

    sock->objectType
    sock->objectClass


    sock->type = SOCK_STREAM;
    
        
    sock->_file = -1;
    
    sock->ip_long = 0;
    sock->port = 0;

    //...
    
    return 0;
}
*/


/*
int socket_inet_create (struct socket_d *sock, int type);
int socket_inet_create (struct socket_d *sock, int type)
{
    if( (void*) sock == NULL )
        return -1;


    sock->sock_domain = AF_INET;

    switch(type) {

        case SOCK_DGRAM:
            return socket_udp_create(sock);

        case SOCK_STREAM:
            return socket_tcp_create(sock);

        default:
            return -1;
    }
    
    return -1;
}
*/




/*
struct socket_d* socket_open (int type);
struct socket_d* socket_open (int type){


    struct socket_d *sock = (struct socket_d *) kmalloc ( sizeof(struct socket_d) );

    memset ( sock, 0, sizeof(struct socket_d) );

    sock->type = type;

    return sock;
}
*/



/*
file *file_from_socket (struct socket_d *sock);
file *file_from_socket (struct socket_d *sock)
{
    
    file *filp = (file *) kmalloc ( sizeof(file) );
    
    if (!filp)
        return NULL;

    //filp->type = FILE_TYPE_SOCKET;
    //filp->isdir = 0;
    //filp->fpos = 0;
    //filp->respath = NULL;
    filp->priv = sock;
    //filp->fops = &socket_fops;
    //filp->refc = 1;

    return filp;
}
*/

/*
 ********************** 
 *  socket:
 *       Essa é função oferece suporte à função socket da libc.
 *       Estamos na klibc dentro do kernel base.
 */
 
//libc socket interface.
//See: https://www.gnu.org/software/libc/manual/html_node/Sockets.html

// #todo
// Fazer um switch para tratar os vários tipos.
// Se o protocolo for '0', então precisamos encontrar o 
// protocolo adequado.

    
int sys_socket ( int family, int type, int protocol ){

	//#todo:
	//vai retornar o descritor de uma stream.

    //#debug
    printf ("sys_socket:\n");
    refresh_screen();


    file *socket_file;
    
    // See: nsocket.h
    struct socket_d *__socket;

    struct process_d *Process;


	//
	// Filtros
	//
	
	//if (family < 0)
	   //return -1;
	
	//if (type < 0)
	   //return -1;
	
	//if (protocol < 0)
	   //return -1;


    //switch (family)
    //{}

    //switch (type)
    //{}

    //switch (protocol)
    //{}
    
    
    // Criamos um socket vazio.
    
    // IN: ip and port.
    __socket = (struct socket_d *) create_socket ( (unsigned long) 0, (unsigned short) 0 );
  
    if ( (void *) __socket == NULL ){
        printf ("sys_socket: __socket fail\n");
        refresh_screen();
        return -1;
    }
    
    // salva o domínio na estrutura de socket.
    __socket->addr.sa_family = family;




    Process = (void *) processList[current_process];

    if ( (void *) Process == NULL ){

        printf("Process\n");
        refresh_screen();
        return -1;

    }else{

        if ( Process->used != 1 || Process->magic != 1234 )
        {
            printf("Process validation\n");
            refresh_screen();
            return -1;
        }

        //ok
    };


	//#todo
	//temos que criar uma rotina que procure slots em Process->Streams[]
	//e colocarmos em process.c
	//essa é afunção que estamos criando.
	// process_find_empty_stream_slot ( struct process_d *process );

    // procurar slot livres.
    int i;
    int __slot = -1;


	// #improvisando
	// 0, 1, 2 são reservados para o fluxo padrão.
	// Como ainda não temos rotinas par ao fluxo padrão,
	// pode ser que peguemos os índices reservados.
	// Para evitar, começaremos depois deles.

	for ( i=3; i< NUMBER_OF_FILES; i++ )
	{
	    if ( Process->Objects[i] == 0 )
		{
			//reserva.
			Process->Objects[i] = 216; 
			
		    __slot = i;
			break;
		}
	}

    //se falhar.
	if ( __slot == -1 ) 
	{
		printf ("no free slots\n");
		Process->Objects[i] = (unsigned long) 0;
	    return -1;
	}


	
	// buffer
	
	char *buff = (char *) kmalloc (BUFSIZ);
	//char *buff = (char *) newPage ();
	
    if ( (void *) buff == NULL )
	{
		 Process->Objects[i] = (unsigned long) 0;
	     return -1;
	}

	//
	// File.
	//

    socket_file = (void *) kmalloc ( sizeof(file) );

    if ( (void *) socket_file == NULL  ){

        Process->Objects[i] = (unsigned long) 0;
        return -1;

    }else{

        // As duas estruturas compartilham o mesmo buffer.

        socket_file->used = 1;
        socket_file->magic = 1234;
        
        socket_file->_file = __slot;
        
        // This file represents a object of type socket.
        socket_file->____object = ObjectTypeSocket;

        socket_file->_base = buff;
        socket_file->_p = buff;

        socket_file->_tmpfname = NULL;

        socket_file->_lbfsize = BUFSIZ; 


        //quanto falta é igual ao tamanho.
        socket_file->_cnt = socket_file->_lbfsize;  
        
        //
        // socket
        //
        
        // Salvamos o ponteiro privado de estrutura de socket.
        socket_file->priv = (void *) __socket; 
        
        __socket->_file = socket_file->_file;

        //Colocando na lista de arquivos abertos no processo.
        Process->Objects[i] = (unsigned long) socket_file;


		// #importante
		// Esse é o retorno esperado.

		//printf ("slot1 = %d\n", slot1);
        return (int) __slot;
    };


    return -1;
}


// serviços de soquetes da klibc
// #todo: rever os números.

unsigned long 
socket_ioctl ( unsigned long number, 
               unsigned long arg2, 
               unsigned long arg3, 
               unsigned long arg4 )
{

	printf ("socket_ioctl: number=%d \n", number);
	
	if ( number < 7000 || number >= 8000 )
		return 0;
	
	// nu'mero do serviço.
	switch (number)
	{
		//socket(...)	
		//family, type, protocol
		//vai retornar o descritor de uma stream.	
		case 7000:
			return (unsigned long) sys_socket ( (int) arg2, (int) arg3, (int) arg4 );
			break;
			
		//send	
		//case 7001:
		//	return (unsigned long) 1; 
		//	break;
			
		//...
			
	    default:
			printf ("socket_ioctl: Default\n");
			break;
	}
	
    return 1;
}




int 
sys_connect ( int sockfd, 
              const struct sockaddr *addr,
              socklen_t addrlen )
{

    struct process_d *p;
    struct process_d *tp;  //target process.
    
    struct file_d *f;
    struct socket_d *s;


    //sockfd é um soquete de quem quer se conecta
    //o addr indica o alvo.

    if ( sockfd < 0 || sockfd >= 32 ){
        printf ("sys_connect: sockfd fail\n");
        refresh_screen();
        return -1;
    }
    
    //target.
   // Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL )
    {
        printf ("sys_connect: addr fail\n");
        refresh_screen();
        return -1;
    }

    
    
    int target_pid = -1;
     
    
    switch (addr->sa_family)
    {
        // AF_GRAMADO
        // Vamos obter o número do processo alvo.
        case 8000:

            // shell
            if ( addr->sa_data[0] == 's' && addr->sa_data[1] == 'h' ){   
                target_pid = (int) gramado_ports[GRAMADO_SH_PORT]; 
            }
            
            // window server
            if ( addr->sa_data[0] == 'w' && addr->sa_data[1] == 's' ){   
                target_pid = (int) gramado_ports[GRAMADO_WS_PORT]; 
            }

            // window manager
            if ( addr->sa_data[0] == 'w' && addr->sa_data[1] == 'm' ){   
                target_pid = (int) gramado_ports[GRAMADO_WM_PORT]; 
            }
            
            // ...

            printf ("target pid %d \n", target_pid);
            break;

        //... 
        
        default:
            printf ("Family not supported! %d \n",addr->sa_family);
            refresh_screen();
            return -1;
            break;
    }
    

    //
    // Sender process.
    //
    
    
    // sender's process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL ){
        printf ("sys_connect: p fail\n");
        refresh_screen();
        return -1;
    }
 
 
    // sender's file
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL ){
        printf ("sys_connect: f fail\n");
        refresh_screen();
        return -1;
    }
    
 
    // socket structure in the senders file.
    s = (struct socket_d *) f->priv;

    if ( (void *) s == NULL ){
        printf ("sys_connect: s fail\n");
        refresh_screen();
        return -1;
    }
 
 
     //
     // target process
     //
 
     // target pid.
     if (target_pid<0){
        printf ("sys_connect: target_pid.\n");
        refresh_screen();
        return -1;
     }

 
     // process
     tp = (struct process_d *) processList[target_pid];
 
     if ( (void *) tp == NULL ){
         printf ("sys_connect: tp fail\n");
         refresh_screen();
         return -1;
     }

     //share file
     int freefd = -1;
     freefd = fs_get_free_fd ( target_pid );
 
     if(freefd<0){
        printf ("sys_connect: freefd fail\n");
        refresh_screen();
        return -1;
     }

         
         
     // Now the target has a file to read.
     tp->Objects[freefd] = p->Objects[sockfd];
 
 
     // O accept decide se quer esse arquivo.
     // no máximo 5.
     tp->accept[0] = freefd;
     
    debug_print("sys_connect: connect ok\n");
    printf ("sys_connect: *done.\n");
    refresh_screen();
    return 0;
     
     //
     // socket ok.
     //
   
     /*
     // Usando a estrutura que nos foi passada.
     if ( (void *) addr == NULL )
     {
         printf ("sys_connect: addr fail\n");
         refresh_screen();
         return -1;
     }


    
    
     printf ("process %d ; family %d ; len %d \n", 
         current_process, addr->sa_family, addrlen  );
 
     
    printf ("sys_connect: #todo\n");
    refresh_screen();
    return -1; 
    */   
}   


// #test
// vamos pegar um descritor que aponta para
// um arquivo do tipo soquete que deseja se concetar 
// em o processo
int sys_accept_sender(int n)
{
    struct process_d *p;

    int __value = -1;
    
    if(n<0 || n>4)
        return -1;

    p = (struct process_d *) processList[current_process];
    if( (void *) p == NULL)
        return -1;

    //todo: validation.

    //todo: tem 5 possíveis conexões.

    __value = (int) p->accept[n];

    p->accept[n] = 0;

    return (int) __value;
}




int sys_accept (int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    struct process_d *p;
    struct file_d *f;
    struct socket_d *s;



    if ( sockfd < 0 || sockfd >= 32 )
    {
        printf ("sys_accept: sockfd fail\n");
        refresh_screen();
        return -1;
    }
   
    //
    // 
    //
    
    
    // process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL )
    {
        printf ("sys_accept: p fail\n");
        refresh_screen();
        return -1;
    }
 
 
    //file
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL )
    {
        printf ("sys_accept: f fail\n");
        refresh_screen();
        return -1;
    }
    
 
    //socket
    s = (struct socket_d *) f->priv;

    if ( (void *) s == NULL )
    {
        printf ("sys_accept: s fail\n");
        refresh_screen();
        return -1;
    }
 
    //
    // socket ok.
    //
   
    // Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL )
    {
        printf ("sys_accept: addr fail\n");
        refresh_screen();
        return -1;
    }


    
    
     printf ("process %d ; family %d ; len %d \n", 
         current_process, addr->sa_family, addrlen  );
 
     
    
 
    printf ("sys_accept: #todo\n");
    refresh_screen();
    return -1;
}   


/*
  When a socket is created with socket(2), it exists in a 
  name space (address family) but has no address assigned to it. 
  bind() assigns the address specified by addr to the socket 
  referred to by the file descriptor sockfd.
 */

int 
sys_bind ( int sockfd, 
           const struct sockaddr *addr,
           socklen_t addrlen )
{
    struct process_d *p;
    struct file_d *f;
    struct socket_d *s;



    if ( sockfd < 0 || sockfd >= 32 ){
        printf ("sys_bind: sockfd fail\n");
        refresh_screen();
        return -1;
    }

    // process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL ){
        printf ("sys_bind: p fail\n");
        refresh_screen();
        return -1;
    }
 
 
    // file
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL ){
        printf ("sys_bind: f fail\n");
        refresh_screen();
        return -1;
    }
    
 
    //socket
    s = (struct socket_d *) f->priv;

    if ( (void *) s == NULL ){
        printf ("sys_bind: s fail\n");
        refresh_screen();
        return -1;
    }
   
    //addr 
    
    // Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL ){
        printf ("sys_bind: addr fail\n");
        refresh_screen();
        return -1;
    }


    // Everything is ok.
    // So now we need to include the 'name' into the socket structure
    // respecting the socket's family.
    int n = 0;
    if (s->addr.sa_family == AF_GRAMADO)
    {
        // Binding the name to the socket.
        printf ("~Binding the name to the socket.\n");
        
        // Always 14.
        for(n=0; n<14; n++)
            s->addr.sa_data[n] = addr->sa_data[n];

        
        debug_print ("sys_bind: bind ok\n");
        return 0;
    }
    
    printf ("process %d ; family %d ; len %d \n", 
        current_process, addr->sa_family, addrlen  );
 
     
    printf ("sys_bind: fail\n");
    refresh_screen();
    return -1;
}   



int 
sys_getsockname ( int sockfd, 
                  struct sockaddr *addr, 
                  socklen_t *addrlen )
{
    struct process_d *p;
    struct file_d *f;
    struct socket_d *s;



    if ( sockfd < 0 || sockfd >= 32 ){
        printf ("sys_getsockname: sockfd fail\n");
        refresh_screen();
        return -1;
    }

    // process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL ){
        printf ("sys_getsockname: p fail\n");
        refresh_screen();
        return -1;
    }


    // file
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL ){
        printf ("sys_getsockname: f fail\n");
        refresh_screen();
        return -1;
    }
    
 
    //socket
    s = (struct socket_d *) f->priv;

    if ( (void *) s == NULL ){
        printf ("sys_getsockname: s fail\n");
        refresh_screen();
        return -1;
    }


    //addr 
    
    // Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL ){
        printf ("sys_getsockname: addr fail\n");
        refresh_screen();
        return -1;
    }


    // Everything is ok.
    // So now we need to include the 'name' into the socket structure
    // respecting the socket's family.
    int n = 0;
    if (s->addr.sa_family == AF_GRAMADO)
    {
        // Binding the name to the socket.
        printf ("~Getting the name and the size\n");
        
        addrlen[0] = n;
        
        // Always 14.
        for(n=0; n<14; n++)
            addr->sa_data[n] = s->addr.sa_data[n];


        debug_print ("sys_getsockname: copy ok\n");
        return 0;
    }
    
    printf ("process %d ; family %d ; len %d \n", 
        current_process, addr->sa_family, addrlen  );
 
     
    printf ("sys_getsockname: fail\n");
    refresh_screen();
    return -1;
}
      
      
        

int sys_listen (int sockfd, int backlog)      
{
    printf ("sys_listen: todo\n");
    refresh_screen();
    return -1;
}

/*
 **********************************************
 * create_socket: 
 *     Cria um socket. 
 *     Retorna o ponteiro para a estrutura.
 */

struct socket_d *create_socket ( unsigned long ip, unsigned short port ){

    struct socket_d *s;


    s = (void *) kmalloc ( sizeof( struct socket_d ) );

    if ( (void *) s ==  NULL ){
        printf ( "create_socket: allocation fail \n");
        refresh_screen();
        return NULL;

    }else{

        s->ip_long = ip;
        s->port = port;
    };


    return (struct socket_d *) s;
}


unsigned long getSocketIP ( struct socket_d *socket ){

    if ( (void *) socket ==  NULL )
    {
        return 0;
    }else{

        return (unsigned long) socket->ip_long;
    };
}

unsigned long getSocketPort ( struct socket_d *socket ){

    if ( (void *) socket ==  NULL )
    {
        return 0;
    }else{

        return (unsigned long) socket->port;
    };
}



int 
update_socket ( struct socket_d *socket, 
                unsigned long ip, 
                unsigned short port )
{

    if ( (void *) socket ==  NULL )
    {
        return (int) 1;

    }else{

        socket->ip_long = (unsigned long) ip;
        socket->port = (unsigned short) port;
        return 0;
    };
}




int socket_read (unsigned int fd, char *buf, int count)
{
    struct process_d *__P;
    
    file *__file;
    
    int len;
    
    
    
    // linux 0.01 style.
	//if (fd>=NR_OPEN || count <0 || !(file=current->filp[fd]))
		//return -EINVAL;
	//if (!count)
		//return 0;



    
    // fd?
    // Não pode ser maior que o número de arquivos abertos 
    // pelo processo atual.
    
    
    if (fd<0)
        return -1;
        
    if (fd >= 32)
        return -1;
        
        
        
     //if (count<=0)
         //return -1;


    //
    // Size of the buffer.
    //

    // len
    len = strlen( (const char *) buf );
    
    if (len > count )
        len = count;
    
    // #bugbug: 
    // Precisamos da opção de salvarmos vários setores em
    // dispositivos de bloco.
    if (len > 64 )
        len = 64;
    
    
    //
    // Process pointer.
    //
    
    
    
    __P = (struct process_d *) processList[current_process];

    if ( (void *) __P == NULL ){
        printf ("socket_read: __P\n");
        refresh_screen ();
        return -1; 
    }


    //
    // file.
    //

    // #importante
    // Arquivo. Mas significa objeto.

    __file = ( file * ) __P->Objects[fd];  
    
    
    if ( (void *) __file == NULL ){
		printf ("socket_read: __file\n");
		refresh_screen();
        return -1; 
    }



    //#todo:
    //tipo socket.

    //switch
    // is_char_dev?     read_char(...)
    // is_block_dev?    read_block(...)
    // is_
    
    
    //if ( __file->____object == ObjectTypeFile )
        //return (int) unistd_file_read ( (file *) __file, (char *) buf, (int) count );


    //if ( __file->____object == ObjectTypeDisk )
        // todo disk_read(...)


    //if ( __file->____object == ObjectTypeTTY )
        // tty_read (...) #todo criar função se não existe.



    //See: unistd.c
    // #todo
    // Tem que retornar a quantidade de bytes lido.
    
    return (int) unistd_file_read ( (file *) __file, (char *) buf, (int) count );
}



int socket_write (unsigned int fd,char *buf,int count)
{
    struct process_d *__P;
    
    file *__file;
    
    int len;
    
    
    
    // linux 0.01 style.
	//if (fd>=NR_OPEN || count <0 || !(file=current->filp[fd]))
		//return -EINVAL;
	//if (!count)
		//return 0;



    
    // fd?
    // Não pode ser maior que o número de arquivos abertos 
    // pelo processo atual.
    
    
    if (fd<0)
        return -1;
        
    if (fd >= 32)
        return -1;
        
        
    //if(count<=0)
        //return -1;


    //
    // Size of the buffer.
    //

    // len
    len = strlen( (const char *) buf );
    
    if (len > count )
        len = count;
    
    // #bugbug: 
    // Precisamos da opção de salvarmos vários setores em
    // dispositivos de bloco.
    if (len > 64 )
        len = 64;
    
    
    //
    // Process pointer.
    //
    
    
    
    __P = (struct process_d *) processList[current_process];

    if ( (void *) __P == NULL ){
        printf ("socket_write: __P\n");
        refresh_screen ();
        return -1; 
    }


    //
    // file.
    //

    // #importante
    // Arquivo. Mas significa objeto.

    __file = ( file * ) __P->Objects[fd];   //#todo: Use this one!
    
    if ( (void *) __file == NULL ){
		printf ("socket_write: __file\n");
		refresh_screen();
        return -1; 
    }
    
    // #todo:
    // tipo socket.
    
    //switch
    // is_char_dev?     read_char(...)
    // is_block_dev?    read_block(...)
    // is_


    // Se o descritor usado por write() for de um arquivo
    // do tipo console, escreveremos no console 0.
    /*
    if ( __file->____object == ObjectTypeVirtualConsole )
    {
       // console number, buffer, size.
       return (int) console_write ( 
                        (int) 0,       // Console 0 
                        (const void *) buf, 
                        (size_t) count );
    }
    */
    

    //tem que retonar o tanto de bytes escritos.
    //See: unistd.c
    // Escreve em uma stream uma certa quantidade de chars.
    return (int) unistd_file_write ( (file *) __file, (char *) buf, (int) count );
}



int socket_set_gramado_port(int port, int pid)
{
 
    if( port<0 || port >31)
        return -1;
          
    //todo: max
    if(pid<0)
        return -1;       
    
    gramado_ports[port] = (int) pid;
    
    return 0;
}






          
