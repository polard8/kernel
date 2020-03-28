/*
 * File: socket.c
 *     SOCKET. network access protocol.
 * 
 */


#include <kernel.h>




void show_socket_for_a_process(int pid){

    struct process_d *p;
    struct socket_d *s;


    printf ("Socket info for pid %d: \n", pid);

    //#todo: max
    if (pid<0){
        printf ("pid limits\n");
        refresh_screen();
        return;
    }


    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        printf("p\n");
        refresh_screen();
        return;

    }else{

        if ( p->used != 1 || p->magic != 1234 ){
            printf("Process validation\n");
            refresh_screen();
            return;
        }

        //ok
    };
    
    
    //Pega o ponteiro para a estrutura privada de soquete.
    s = (struct socket_d *) p->priv;
    
    if ( (void *) s == NULL ){
        printf("s\n");
        refresh_screen();
        return;
    }else{

        if ( s->used != 1 || s->magic != 1234 ){
            printf("socket validation\n");
            refresh_screen();
            return;
        }

    };
    
    
    //
    // Show !!
    //
      
    // sockaddr structure.  
    printf ("family %d \n",s->addr.sa_family);
    printf ("data %s   \n",s->addr.sa_data);
    //printf ("",s->);
    //printf ("",s->);
    //printf ("",s->);
    
    refresh_screen();
}




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
    
    sock->ip = 0;
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
    
    sock->ip = 0;
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



int socket_init(void)
{
    int i;
    for(i=0; i<32; i++)
        socketList[i] = (unsigned long)0;
        
        
    return 0;
}



// #todo:
// Vai retornar o descritor de um arquivo.
int 
socket_gramado ( 
    struct socket_d *sock, 
    int family, 
    const struct sockaddr *addr,
    socklen_t addrlen, 
    int type, 
    int protocol )
{

    file *_file;
    
    struct process_d *Process;

    //struct socket_d *__socket;


    // Procurar slot livres.
    int __slot = -1;
    int i=0;


    //#todo
    //check sock arg.



    //
    // Process
    //


    Process = (void *) processList[current_process];

    if ( (void *) Process == NULL ){
        printf("Process\n");
        refresh_screen();
        return -1;

    }else{

        if ( Process->used != 1 || Process->magic != 1234 ){
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



	// #improvisando
	// 0, 1, 2 são reservados para o fluxo padrão.
	// Como ainda não temos rotinas par ao fluxo padrão,
	// pode ser que peguemos os índices reservados.
	// Para evitar, começaremos depois deles.

    __slot = -1; //fail
    
    for ( i=3; i< NUMBER_OF_FILES; i++ )
    {
        if ( Process->Objects[i] == 0 ){
            __slot = i;
            break;
        }
    };


    // Fail.
    if ( __slot == -1 ){
        Process->Objects[i] = (unsigned long) 0;
        printf ("socket_gramado: No free slots\n");
        refresh_screen();
        return -1;
    }


	// buffer

    char *buff = (char *) kmalloc (BUFSIZ);
	//char *buff = (char *) newPage ();

    if ( (void *) buff == NULL ){
        Process->Objects[__slot] = (unsigned long) 0;
        printf ("socket_gramado: Buffer allocation fail\n");
        refresh_screen();
        return -1;
    }


	//
	// File.
	//

    _file = (void *) kmalloc ( sizeof(file) );

    if ( (void *) _file == NULL  ){
        Process->Objects[__slot] = (unsigned long) 0;
        printf ("socket_gramado: _file fail\n");
        refresh_screen();
        return -1;

    }else{
        
        // This file represents a object of type socket.
        _file->____object = ObjectTypeSocket;


        _file->used = 1;
        _file->magic = 1234;
        
        _file->_file = __slot;
        
        _file->_tmpfname = NULL;
        //socket_file->_tmpfname = "socket";       


        // O buffer.
        _file->_base = buff;
        _file->_p = buff;
        _file->_r = 0;
        _file->_w = 0;
        _file->_lbfsize = BUFSIZ; 
        //quanto falta é igual ao tamanho.
        _file->_cnt = _file->_lbfsize;
        
        _file->socket_buffer_full = 0;  

        _file->socket = sock;
        
        // O arquivo do soquete, o buffer ?
        sock->private_file = (file *) _file; 

        // Salvamos o ponteira para estrutura de soquete
        // na estrutura de processo do processo atual.
        Process->priv = (void *) sock;
        
        //Colocando na lista de arquivos abertos no processo.
        Process->Objects[__slot] = (unsigned long) _file;

        // Retornamos o fd na lista de arquivos abertos pelo processo.
        return (int) __slot;
    };


    return -1;      
}


int 
socket_unix ( 
    struct socket_d *sock, 
    int family, 
    const struct sockaddr *addr,
    socklen_t addrlen, 
    int type, 
    int protocol )
{
    debug_print("socket_unix: [TODO]\n");
    return -1;
}                
                


int 
socket_inet ( 
    struct socket_d *sock, 
    int family, 
    const struct sockaddr *addr,
    socklen_t addrlen, 
    int type, 
    int protocol )
{
    debug_print("socket_inet: [TODO]\n");
    return -1;
}


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

// OUT: ?

int sys_socket ( int family, int type, int protocol ){

    struct socket_d *__socket;
    struct sockaddr addr;
    
    addr.sa_family = family;
    addr.sa_data[0] = 'x'; 
    addr.sa_data[1] = 'x';
    
    unsigned long ip = 0x00000000;
    unsigned short port = 0x0000;

    struct process_d *p;  //current


    // #debug
    printf ("\n======================================\n");
    printf ("sys_socket: PID %d | family %d | type %d | protocol %d \n",
        current_process, family, type, protocol );
    refresh_screen();


	//
	// Filtros
	//

    if (family < 0)
        return -1;

    //if (type < 0)
        //return -1;

    //if (protocol < 0)
       //return -1;


     p = (struct process_d *) processList[current_process];
     
     if ( (void*) p == NULL ){
        printf ("sys_socket: p fail\n");
        refresh_screen();
        return -1;
     }

    
    //
    // Socket structure.
    //
    
    // Criamos um socket vazio.
    // IN: ip and port.

    __socket = (struct socket_d *) create_socket ( ip, port );
  
    if ( (void *) __socket == NULL ){
        printf ("sys_socket: __socket fail\n");
        refresh_screen();
        return -1;
 
 
    }else{


       __socket->addr = addr;
       
       p->priv = __socket;


       // family

       switch(family)
       {
           case AF_GRAMADO:
               return (int) socket_gramado ( __socket, 
                                AF_GRAMADO, 
                                (const struct sockaddr *) &addr, 
                                14,
                                type,
                                protocol );
               break;
               
           case AF_UNIX:
               return (int) socket_unix ( __socket, 
                                AF_UNIX, 
                                (const struct sockaddr *) &addr, 
                                14, 
                                type, 
                                protocol );
               break;

           //#bugbug: 
           //talvez precisamos rever sockaddr 
           //para essa função, e usarmos outra estrutura.               
           case AF_INET:
               return (int) socket_inet ( __socket, 
                                AF_INET, 
                                (const struct sockaddr *) &addr, 
                                14,
                                type,
                                protocol );
               break;
           
           
               
           //...
           
           
           default:
               return -1;
               break;
       }


        //...
    };
    


    return -1;
}



struct socket_d *get_socket_from_fd (int fd){

    struct process_d *p;

    file *_file;
    
    
    if(fd<0 || fd>=32)
        return (struct socket_d *) 0;


    p = (struct process_d *) processList[current_process];
    if( (void*) p == NULL)
        return (struct socket_d *) 0;
 
        
    _file = (file *) p->Objects[fd];    
    if( (void*) _file == NULL)
        return (struct socket_d *) 0;

    
    return (struct socket_d *) _file->socket;
}





// os dois são arquivos no mesmo processo.
// o processo atual.
int
sock_socketpair ( 
    int family, 
    int type, 
    int protocol, 
    int usockvec[2] )
{

    int fd1, fd2;
    struct socket_d *sock1;
    struct socket_d *sock2;


    fd1 = sys_socket(family,type,protocol);
    sock1 = get_socket_from_fd(fd1);
    if( (void*) sock1 == NULL)
        return -1;
    
    fd2 = sys_socket(family,type,protocol);
    sock2 = get_socket_from_fd(fd2);    
    if( (void*) sock2 == NULL)
        return -1;

    
    // #todo
    // Antes é preciso verificar a área de memória.
    
    usockvec[0] = fd1; 
    usockvec[1] = fd2;    
    
    //ok
    return 0;
}


/*
// Sinalizamos que estamos esperando uma conexão de determinal servidor.
// lembrando que estamos falando de peer to peer
// o servidor terá que validar a conexão que estamos preparando aqui.
int socket_connection_waiting_for_validation (struct socket_d *mysock, struct socket_d *servsock);
int socket_connection_waiting_for_validation (struct socket_d *mysock, struct socket_d *servsock)
{
    if( (void*) mysock == NULL)
        return -1;
        
    if( (void*) servsock == NULL)
        return -1;

    mysock->state   = SOCKET_CONNECTING;
    servsock->state = SOCKET_CONNECTING;

    mysock->conn = servsock;
    servsock->conn = mysock

    return 0;
}
*/



// serviços de soquetes da klibc
// #todo: rever os números.
// OUT: ?
unsigned long 
socket_ioctl ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    printf ("socket_ioctl: number=%d \n", number);

    if ( number < 7000 || number >= 8000 )
        return 0;


	// número do serviço.

    switch (number)
    {
		//socket(...)	
		//family, type, protocol
		//vai retornar o descritor de uma stream.	
        case 7000:
            return (unsigned long) sys_socket ( (int) arg2, 
                                       (int) arg3, (int) arg4 );
            break;

		//send
		//case 7001:
		//	return (unsigned long) 1; 
		//	break;

		//...
			
        default:
            printf ("socket_ioctl: Default\n");
            refresh_screen();
            break;
    };


    // Fail.
    return 0;
}


// connect.
// Em nosso exemplo o cliente quer se conectar com o servidor.
// IN: client fd, address, address len
// OUT: 0=ok <0=fail

int 
sys_connect ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{

    struct process_d *p;   // Current process.
    struct process_d *tp;  // Target process.

    struct file_d *f;
    
    struct socket_d *my_socket;
    struct socket_d *server_socket; 

    int target_pid = -1;
    

    
    printf ("sys_connect: PID %d | fd %d | \n",
        current_process, sockfd );
    

    //sockfd é um soquete de quem quer se conecta
    //o addr indica o alvo.

    if ( sockfd < 0 || sockfd >= 32 ){
        printf ("sys_connect: sockfd fail\n");
        refresh_screen();
        return -1;
    }

    // Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL ){
        printf ("sys_connect: addr fail\n");
        refresh_screen();
        return -1;
    }

    // Getting the target PID.
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

            // network server
            if ( addr->sa_data[0] == 'n' && addr->sa_data[1] == 's' ){   
                target_pid = (int) gramado_ports[GRAMADO_NS_PORT]; 
            }

            // ...

            printf (">>>> target pid %d \n", target_pid);
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
    
    // Vamos obter o arquivo do tipo soquete
    // que pertence ao sender.
    
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
        printf ("sys_connect: *** f fail\n");
        refresh_screen();
        return -1;
    }

    //is socket??
    
    int __is = -1;
    
    __is = is_socket ((file *)f);
    if(__is != 1){
        printf ("sys_connect: f is not a socket\n");
        refresh_screen();
        return -1;
    }

    

    //pega a estrutura de socket associada ao arquivo.
    // socket structure in the senders file.
    //s = (struct socket_d *) p->priv; 
    my_socket = (struct socket_d *) f->socket;   
    
    if ( (void *) my_socket == NULL ){
        printf ("sys_connect: my_socket fail\n");
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


    server_socket = (struct socket_d *) tp->priv;
    
    
    //connecting ;;;
    
    my_socket->conn = server_socket;
    server_socket->conn = my_socket;    
     
    my_socket->state = SOCKET_CONNECTED;
    server_socket->state = SOCKET_CONNECTED; 
     
    debug_print("sys_connect: connect ok\n");
    printf ("sys_connect: *done.\n");
    refresh_screen();

    return 0;
}   



// #test
// ??
// Checar o accept[].
// Vamos pegar um descritor que aponta para um arquivo do tipo soquete 
// que deseja se concetar.
// #todo: mudar o tipo do retorno para pid_t

int sys_accept_sender (int n){

    int __pid = -1;
    struct process_d *p;
 
 
    if(n<0 || n>4)
        return -1;

    p = (struct process_d *) processList[current_process];
    if( (void *) p == NULL)
        return -1;

    //todo: validation.

    //todo: tem 5 possíveis conexões.

    __pid = (int) p->accept[n];

    p->accept[n] = 0;


    return (int) __pid;
}


// #todo: OUT: ???
int 
sys_accept (
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{
    struct process_d *p;

    struct file_d *f;

    struct socket_d *s;


    // fd
    if ( sockfd < 0 || sockfd >= 32 ){
        printf ("sys_accept: sockfd fail\n");
        refresh_screen();
        return -1;
    }
    
    // process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL ){
        printf ("sys_accept: p fail\n");
        refresh_screen();
        return -1;
    }
 
 
    // file
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL ){
        printf ("sys_accept: f fail\n");
        refresh_screen();
        return -1;
    }
    
 
    // socket
    s = (struct socket_d *) p->priv;

    if ( (void *) s == NULL ){
        printf ("sys_accept: s fail\n");
        refresh_screen();
        return -1;
    }
 
    //
    // Socket ok.
    //
   
    // Check addr structure.
    if ( (void *) addr == NULL ){
        printf ("sys_accept: addr fail\n");
        refresh_screen();
        return -1;
    }

    // #debug
    printf ("process %d | family %d | len %d \n", 
        current_process, addr->sa_family, addrlen  );

 
    printf ("sys_accept: [FIXME] TODO ...\n");
    refresh_screen();

    // More ??

    return -1;
}   


/*
  When a socket is created with socket(2), it exists in a 
  name space (address family) but has no address assigned to it. 
  bind() assigns the address specified by addr to the socket 
  referred to by the file descriptor sockfd.
 */

int 
sys_bind ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{
    struct process_d *p;
    
    struct file_d *f;
    
    struct socket_d *s;



    printf ("sys_bind: PID %d | fd %d | \n",
        current_process, sockfd );


    // fd
    if ( sockfd < 0 || sockfd >= 32 ){
        printf ("sys_bind: sockfd fail\n");
        goto fail;
    }


    // Check addr structure.
    if ( (void *) addr == NULL ){
        printf ("sys_bind: addr fail\n");
        goto fail;
    }



    // process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL ){
        printf ("sys_bind: p fail\n");
        goto fail;
    }
 
 
    // file
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL ){
        printf ("sys_bind: f fail\n");
        goto fail;
    }
    
 
    // socket
    s = (struct socket_d *) f->socket;

    if ( (void *) s == NULL ){
        printf ("sys_bind: s fail\n");
        goto fail; 
    }


    //
    // family
    //
    
    // Everything is ok.
    // So now we need to include the 'name' into the socket structure
    // respecting the socket's family.
    int n = 0;

    // AF_GRAMADO
    if (s->addr.sa_family == AF_GRAMADO){
        // Binding the name to the socket.
        printf ("~Binding the name to the socket.\n");
        
        // Always 14.
        for(n=0; n<14; n++)
            s->addr.sa_data[n] = addr->sa_data[n];


        printf ("process %d ; family %d ; len %d \n", 
            current_process, addr->sa_family, addrlen  );
        
        debug_print ("sys_bind: bind ok\n");
        return 0;
    }

    // AF_UNIX
    if (s->addr.sa_family == AF_UNIX){
        debug_print ("sys_bind: AF_UNIX not supported yet\n");
        return -1;
    }    

    // AF_INET
    if (s->addr.sa_family == AF_INET){
        debug_print ("sys_bind: AF_INET not supported yet\n");
        return -1;    
    } 
  
    // DEFAULT:
    printf ("sys_bind: fail. family not valid\n");

fail:    
    printf ("sys_bind: fail\n");
    refresh_screen();
    
    debug_print ("sys_bind: fail\n");
    return -1;
}   



int 
sys_getsockname ( 
    int sockfd, 
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
    s = (struct socket_d *) p->priv;

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
    
    // #todo
    // More families.
    //if ( ...
    //if ( ...
    //if ( ...
    // ...
    
    printf ("process %d ; family %d ; len %d \n", 
        current_process, addr->sa_family, addrlen  );
 
     
    printf ("sys_getsockname: fail\n");
    refresh_screen();
    return -1;
}



int sys_listen (int sockfd, int backlog)      
{
    printf ("sys_listen: [TODO]\n");
    refresh_screen();
    return -1;
}


/*
 ******************************************
 * create_socket: 
 *     Cria um socket. 
 *     Retorna o ponteiro para a estrutura.
 */


struct socket_d *
create_socket ( 
    unsigned long ip, 
    unsigned short port )
{

    struct socket_d *s;


    s = (void *) kmalloc ( sizeof( struct socket_d ) );

    if ( (void *) s ==  NULL ){
        printf ( "create_socket: allocation fail \n");
        refresh_screen();
        return NULL;

    }else{

        //s->objectType =
        //s->objectClass =

        s->used = 1;
        s->magic = 1234;
        
        s->state = SOCKET_NOT_CONNECTED;
        
        s->private_file = (file *) 0;
        
        //s->addr = (struct sockaddr) 0;
        
        s->owner = current_process;
        
        s->ip = ip;
        s->port = port;
        
        
        // Initializing pointers.
        // We don't want this kinda crash in the real machine.
        
        s->conn = (struct socket_d *) 0;
        // ...
        
        
        //...
        
    };


    return (struct socket_d *) s;
}


unsigned long getSocketIP ( struct socket_d *socket ){

    if ( (void *) socket ==  NULL ){
        return 0;

    }else{

        return (unsigned long) socket->ip;
    };
}


unsigned long getSocketPort ( struct socket_d *socket ){

    if ( (void *) socket ==  NULL ){
        return 0;

    }else{

        return (unsigned long) socket->port;
    };
}



int 
update_socket ( 
    struct socket_d *socket, 
    unsigned long ip, 
    unsigned short port )
{

    if ( (void *) socket ==  NULL ){
        return (int) 1;

    }else{

        socket->ip = (unsigned long) ip;
        socket->port = (unsigned short) port;
        return 0;
    };
}



int socket_read (unsigned int fd, char *buf, int count)
{
    debug_print("socket_read:[TODO]\n");
    return -1;
}



int socket_write (unsigned int fd,char *buf,int count)
{
    debug_print("socket_write:[TODO]\n");
    return -1;
}


// Conjunto especiais de portas.
// Usados apenas na famíla AF_GRAMADO.
int socket_set_gramado_port (int port, int pid)
{
 
    if( port<0 || port >31)
        return -1;


    //todo: max
    if(pid<0)
        return -1;       
    
    gramado_ports[port] = (int) pid;

    return 0;
}



int is_socket (file *f){

    if( (void*) f == NULL )
        return -1;

    if ( f->____object == ObjectTypeSocket )
        return 1; // Yes.
        
    // No
    return 0;
}


int is_virtual_console (file *f){

    if( (void*) f == NULL )
        return -1;

    if ( f->____object == ObjectTypeVirtualConsole )
        return 1; // Yes.
        
    // No
    return 0;
}



//...


//
// End.
//



