/*
 * File: socket.c
 * 
 *     unix-like socket support.
 *
 * 
 * History:
 *     2020 - Created by Fred Nora. 
 */


#include <kernel.h>


//internal
#define SYS_SOCKET_IP(a, b, c, d) (a << 24 | b << 16 | c << 8 | d)



void show_socket_for_a_process(int pid){

    struct process_d  *p;
    struct socket_d   *s;

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



int socket_init (void)
{
    int i=0;

    for (i=0; i<32; i++)
        socketList[i] = (unsigned long) 0;
        
        
    return 0;
}



// #todo:
// Configura a estrutura de socket para um socket da
// família AF_GRAMADO.
// Vai retornar o descritor de um arquivo.

int 
socket_gramado ( 
    struct socket_d *sock, 
    int family, 
    int type, 
    int protocol )
{

    // Esse é o arquivo usado pelos aplicativos.
    // Retornaremos seu fd.
    file *_file;
    struct process_d *Process;

    // Procurar slot livres.
    int i=0;
    int __slot = -1;



    debug_print ("socket_gramado:\n");


   
    if ( (void*) sock == NULL )
    {
        debug_print ("socket_gramado: [FAIL] sock\n");
        goto fail;
    }
    
    if (family != AF_GRAMADO)
    {
        debug_print ("socket_gramado: [FAIL] bad family\n");
        goto fail;
    }


    // Process.

    Process = (void *) processList[current_process];

    if ( (void *) Process == NULL ){
        printf("socket_gramado: [FAIL] Process\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);

    }else{

        if ( Process->used != 1 || Process->magic != 1234 ){
            printf("socket_gramado: [FAIL] Process validation\n");
            goto fail;
            //refresh_screen();
            //return (int) (-1);
        }
        //ok
    };


	//#todo
	//temos que criar uma rotina que procure slots em Process->Objects[]
	//e colocarmos em process.c
	//essa é afunção que estamos criando.
	// process_find_empty_stream_slot ( struct process_d *process );



	// #improvisando
	// 0, 1, 2 são reservados para o fluxo padrão.
	// Como ainda não temos rotinas par ao fluxo padrão,
	// pode ser que peguemos os índices reservados.
	// Para evitar, começaremos depois deles.


    // Reserva um slot.
    for ( i=3; i< NUMBER_OF_FILES; i++ )
    {
        if ( Process->Objects[i] == 0 ){ __slot = i; break; }
    };

    // Check slot validation. 
    if ( __slot == -1 )
    {
        printf ("socket_gramado: [FAIL] No free slots\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);
    }

    //
    // == Buffer ========================
    //
    
    //char *buff = (char *) newPage ();
    char *buff = (char *) kmalloc(BUFSIZ);

    if ( (void *) buff == NULL )
    {
        Process->Objects[__slot] = (unsigned long) 0;

        debug_print ("socket_gramado: [FAIL] Buffer allocation fail\n");
        printf      ("socket_gramado: [FAIL] Buffer allocation fail\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);
    }


	//
	// File.
	//

    _file = (void *) kmalloc ( sizeof(file) );

    if ( (void *) _file == NULL  )
    {
        Process->Objects[__slot] = (unsigned long) 0;
        
        debug_print ("socket_gramado: [FAIL] _file fail\n");
        printf      ("socket_gramado: [FAIL] _file fail\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);

    }else{
        _file->used = 1;
        _file->magic = 1234;
        _file->pid = (pid_t) current_process;
        _file->uid = (uid_t) current_user;
        _file->gid = (gid_t) current_group;
        _file->____object = ObjectTypeSocket;

        // No name for now.
        _file->_tmpfname = NULL;
        //_file->_tmpfname = "socket";       
        

        // Buffer.
        _file->_base    = buff;
        _file->_p       = buff;
        _file->_lbfsize = BUFSIZ;          
      
        // Quanto falta.
        _file->_cnt = _file->_lbfsize;         
        
        _file->_r = 0;
        _file->_w = 0;
        
        // Status do buffer do socket.   
        _file->socket_buffer_full = 0;  

        // Socket pointer.
        _file->socket = sock;

        // O arquivo do soquete, o buffer ?
        sock->private_file = (file *) _file; 

        // Socket pointer.
        // Salvamos o ponteira para estrutura de soquete
        // na estrutura de processo do processo atual.
        Process->priv = (void *) sock;

        // fd.
        _file->_file = __slot;
        
        //Colocando na lista de arquivos abertos no processo.
        Process->Objects[__slot] = (unsigned long) _file;
        
        
        debug_print ("socket_gramado: done\n");

        // ok.
        // Retornamos o fd na lista de arquivos abertos pelo processo.
        return (int) __slot;
    };

fail:
    debug_print ("socket_gramado: [FAIL]\n");
    refresh_screen();
    return (int) (-1);      
}


// Configura a estrutura de socket para um socket da
// família AF_UNIX or AF_LOCAL.
// Precisa ser uma rotina parecida com a do outro tipo criado.

int 
socket_unix ( 
    struct socket_d *sock, 
    int family, 
    int type, 
    int protocol )
{

    file *_file;
    struct process_d *Process;

    // Procurar slot livres.
    int i=0;
    int __slot = -1;


    //#todo
    //check sock arg.


    debug_print ("socket_unix:\n");


    if ( (void*) sock == NULL )
    {
        debug_print ("socket_unix: [FAIL] sock\n");
        goto fail;
    }


    if (family != AF_UNIX)
    {
        debug_print ("socket_unix: [FAIL] bad family\n");
        goto fail;
    }


    // Process.

    Process = (void *) processList[current_process];

    if ( (void *) Process == NULL )
    {
        printf("socket_unix: Process\n");
        goto fail;
        //refresh_screen();
        //return (int)(-1);

    }else{

        if ( Process->used != 1 || Process->magic != 1234 ){
            printf("socket_unix: validation\n");
            goto fail;
            //refresh_screen();
            //return (int)(-1);
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

    // Reserva um slot.
    for ( i=3; i< NUMBER_OF_FILES; i++ )
    {
        if ( Process->Objects[i] == 0 ){ __slot = i; break; }
    };


    // Check slot validation. 
    if ( __slot == -1 )
    {
        printf ("socket_unix: No free slots\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);
    }


    //
    // == Buffer ================
    //

    char *buff = (char *) kmalloc(BUFSIZ);
    //char *buff = (char *) newPage ();

    if ( (void *) buff == NULL )
    {
        Process->Objects[__slot] = (unsigned long) 0;
        
        debug_print ("socket_unix: [FAIL] Buffer allocation fail\n");
        printf      ("socket_unix: [FAIL] Buffer allocation fail\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);
    }


	//
	// File.
	//

    _file = (void *) kmalloc( sizeof(file) );

    if ( (void *) _file == NULL  )
    {
        Process->Objects[__slot] = (unsigned long) 0;
        
        printf ("socket_unix: _file fail\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);

    }else{
        _file->used = 1;
        _file->magic = 1234;
        _file->pid = (pid_t) current_process;
        _file->uid = (uid_t) current_user;
        _file->gid = (gid_t) current_group;
        _file->____object = ObjectTypeSocket;


        // No name for now.
        // #bugbug: 
        // unix sockets has names.
        // it's like a normal fs pathname.

        _file->_tmpfname = NULL;
        //_file->_tmpfname = "/tmp/socketXXX";    


        // Buffer.
        _file->_base = buff;
        _file->_p    = buff;
        _file->_lbfsize = BUFSIZ; 

        // Quanto falta.
        _file->_cnt = _file->_lbfsize;

        _file->_r = 0;
        _file->_w = 0;


        _file->socket_buffer_full = 0;  

        _file->socket = sock;
        
        // O arquivo do soquete, o buffer ?
        sock->private_file = (file *) _file; 

        // Salvamos o ponteira para estrutura de soquete
        // na estrutura de processo do processo atual.
        Process->priv = (void *) sock;


        // fd.
        _file->_file = __slot;

        //Colocando na lista de arquivos abertos no processo.
        Process->Objects[__slot] = (unsigned long) _file;

         debug_print ("socket_unix: done\n");
         
        //ok.
        // Retornamos o fd na lista de arquivos abertos pelo processo.
        return (int) __slot;
    };


fail:
    debug_print ("socket_unix: fail\n");
    refresh_screen();
    return (int) (-1);  
}


// Configura a estrutura de socket para um socket da
// família AF_INET.
// Precisa ser uma rotina parecida com a do outro tipo criado.
// Esse domínio lida com tcp/ip ?

int 
socket_inet ( 
    struct socket_d *sock, 
    int family,
    int type, 
    int protocol )
{

    file *_file;
    struct process_d *Process;

    // Procurar slot livres.
    int i=0;
    int __slot = -1;


    if ( (void*) sock == NULL )
    {
        debug_print ("socket_unix: [FAIL] sock\n");
        goto fail;
    }

    if (family != AF_INET)
    {
        debug_print ("socket_unix: [FAIL] bad family\n");
        goto fail;
    }


    // Process

    Process = (void *) processList[current_process];

    if ( (void *) Process == NULL )
    {
        printf("socket_inet: Process\n");
        goto fail;

    }else{

        if ( Process->used != 1 || Process->magic != 1234 ){
            printf("socket_inet: validation\n");
            goto fail;
            //refresh_screen();
            //return (int) (-1);
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
    
    for ( i=3; i< NUMBER_OF_FILES; i++ )
    {
        if ( Process->Objects[i] == 0 ){ __slot = i; break; }
    };


    // Fail.
    if ( __slot == -1 )
    {
        printf ("socket_inet: No free slots\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);
    }


    //
    // == Buffer ==========================
    //
    
    char *buff = (char *) kmalloc(BUFSIZ);
    //char *buff = (char *) newPage ();

    if ( (void *) buff == NULL )
    {
        Process->Objects[__slot] = (unsigned long) 0;

        debug_print ("socket_inet: [FAIL] Buffer allocation fail\n");
        printf      ("socket_inet: [FAIL] Buffer allocation fail\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);
    }

	//
	// File.
	//

    _file = (void *) kmalloc( sizeof(file) );

    if ( (void *) _file == NULL  )
    {
        Process->Objects[__slot] = (unsigned long) 0;
        
        printf ("socket_inet: _file fail\n");
        goto fail;
        //refresh_screen();
        //return (int) (-1);

    }else{
        _file->used = 1;
        _file->magic = 1234;
        _file->pid = (pid_t) current_process;
        _file->uid = (uid_t) current_user;
        _file->gid = (gid_t) current_group;
        _file->____object = ObjectTypeSocket;


        // No name for now.
        _file->_tmpfname = NULL;
        //_file->_tmpfname = "socket";       

        // Buffer.
        _file->_base    = buff;
        _file->_p       = buff;
        _file->_lbfsize = BUFSIZ; 
        
        // Quanto falta.
        _file->_cnt = _file->_lbfsize;        
        
        _file->_r = 0;
        _file->_w = 0;
        
        
        _file->socket_buffer_full = 0;  

        _file->socket = sock;
        
        // O arquivo do soquete, o buffer ?
        sock->private_file = (file *) _file; 

        // Salvamos o ponteira para estrutura de soquete
        // na estrutura de processo do processo atual.
        Process->priv = (void *) sock;

        // fd.
        _file->_file = __slot;
        
        //Colocando na lista de arquivos abertos no processo.
        Process->Objects[__slot] = (unsigned long) _file;
        
        debug_print ("socket_inet: done\n");

        // ok
        // Retornamos o fd na lista de arquivos abertos pelo processo.
        return (int) __slot;
    };


fail:
    debug_print ("socket_inet: [FAIL]\n");
    refresh_screen();
    return (int) (-1);
}




/*
struct socket_d *create_socket ( 
    int family, 
    int type, 
    int protocol );
struct socket_d *create_socket ( 
    int family, 
    int type, 
    int protocol )
{

    struct socket_d *new_socket;
  
  
    // Socket address structure.
    // Usado em AF_GRAMADO
    struct sockaddr addr;
    addr.sa_family  = family;
    addr.sa_data[0] = 'x'; 
    addr.sa_data[1] = 'x';


    // Internet style for inet.
    // Usado em AF_INET
    struct sockaddr_in addr_in;
    addr_in.sin_family      = AF_INET;
    addr_in.sin_port        = 11369;  //??
    addr_in.sin_addr.s_addr = SYS_SOCKET_IP(127,0,0,1);
    //addr_in.sin_addr      = SYS_SOCKET_IP(192, 168, 1, 112); //errado
    //addr_in->sin_addr.s_addr = inet_addr("127.0.0.1");  //todo: inet_addr see netbsd
 
    // Current process.
    struct process_d *p;  
    
    int fd = -1; 
    
	//
	// Filtros
	//

    if (family < 0){
        debug_print ("sys_socket: [FAIL] family not supported\n");
        goto fail;
        //return -1;
    }

    // Check if this is a valid type.
    //if (type < 0){
    if ( type != SOCK_STREAM &&
         type != SOCK_DGRAM  &&
         type != SOCK_RAW)
    {
        debug_print ("sys_socket: [FAIL] type not supported\n");
        goto fail;
        //return -1;
    }

    if (protocol < 0){
        debug_print ("sys_socket: [FAIL] protocol not supported\n");
        goto fail;
        //return -1;
    }


    // Current process.
    
    p = (struct process_d *) processList[current_process];
     
    if ( (void *) p == NULL )
    {
        debug_print ("sys_socket: p fail\n");
        printf      ("sys_socket: p fail\n");
        goto fail;
        //refresh_screen();
        //return -1;
    }

    new_socket = (struct socket_d *) create_socket_object();

    if ( (void *) new_socket == NULL )
    {
        debug_print ("create_socket: [FAIL] __socket fail\n");
        printf      ("create_socket: [FAIL] __socket fail\n");
        goto fail;

    }else{

        // The private socket of a process.
        //p->priv = __socket;

        // family, type and protocol.
        new_socket->family   = family;
        new_socket->type     = type;      // DATAGRAM or STREAM 
        new_socket->protocol = protocol;

        // #Initialized with '0'.
        new_socket->ip   = 0;
        new_socket->port = 0;

        new_socket->pid = (pid_t) current_process;
        new_socket->uid = (uid_t) current_user;
        new_socket->gid = (gid_t) current_group;


       //
       // Create file!
       //

       // family
       // Setup the addr.

       // #importante
       // As rotinas logo abaixo criarão o arquivo
       // e retornarão o fd.

       switch (family)
       {
           case AF_GRAMADO:
               debug_print ("sys_socket: AF_GRAMADO\n");
               new_socket->addr = addr;
               fd = socket_gramado ( new_socket, 
                                AF_GRAMADO, type, protocol );
               
               return (struct socket_d *) new_socket;
               break;

           //case AF_LOCAL:
           case AF_UNIX:
               debug_print ("sys_socket: AF_UNIX\n");
               new_socket->addr =  addr;
               fd = socket_unix ( new_socket, 
                                AF_UNIX, type, protocol );
               return (struct socket_d *) new_socket;
               break;

           //#bugbug: 
           //talvez precisamos rever sockaddr 
           //para essa função, e usarmos outra estrutura.               
           case AF_INET:
               debug_print ("sys_socket: AF_INET\n");
               new_socket->addr_in = addr_in;
               
               
               
               fd = socket_inet ( new_socket, 
                                AF_INET, type, protocol );
               
      
               return (struct socket_d *) new_socket;
               break;

           // ...
           
           default:
               debug_print ("sys_socket: [FAIL] default family\n");
               debug_print ("sys_socket: Couldn't create the file\n");
               goto fail;
               //return (int) (-1);
               break;
        };

        // ...
    };

    //fail.
    
fail:
    debug_print ("sys_socket: [FAIL] Something is wrong!\n");
    refresh_screen();
    return NULL;
}
*/



/*
 ********************** 
 *  sys_socket:
 *       Essa é função oferece suporte à função socket da libc.
 *       Estamos na klibc dentro do kernel base.
 */
 
//libc socket interface.
//See: https://www.gnu.org/software/libc/manual/html_node/Sockets.html

// #example:
// tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
// udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
// raw_socket = socket(AF_INET, SOCK_RAW, protocol);

// #todo
// Fazer um switch para tratar os vários tipos.
// Se o protocolo for '0', então precisamos encontrar o 
// protocolo adequado.

// OUT: ?

int sys_socket ( int family, int type, int protocol ){


    //#todo
    // call create_socket(...)
    // it will return a pointer.


    // Socket structure.
    struct socket_d *__socket;


    // Socket address structure.
    // Usado em AF_GRAMADO
    struct sockaddr addr;
    addr.sa_family  = family;
    addr.sa_data[0] = 'x'; 
    addr.sa_data[1] = 'x';


    // Internet style for inet.
    // Usado em AF_INET
    struct sockaddr_in addr_in;
    addr_in.sin_family      = AF_INET;
    addr_in.sin_port        = 11369;  //??
    addr_in.sin_addr.s_addr = SYS_SOCKET_IP(127,0,0,1);
    //addr_in.sin_addr      = SYS_SOCKET_IP(192, 168, 1, 112); //errado
    //addr_in->sin_addr.s_addr = inet_addr("127.0.0.1");  //todo: inet_addr see netbsd

    
    // Current process.
    struct process_d *p;  

    // ip:port used in the socket struture.
    unsigned long ip    = 0x00000000;
    unsigned short port = 0x0000;


    // #debug
    printf ("\n======================================\n");
    printf ("sys_socket: PID %d | family %d | type %d | protocol %d \n",
        current_process, family, type, protocol );
    refresh_screen();


	//
	// Filtros
	//

    if (family < 0){
        debug_print ("sys_socket: [FAIL] family not supported\n");
        goto fail;
        //return -1;
    }

    // Check if this is a valid type.
    //if (type < 0){
    if ( type != SOCK_STREAM &&
         type != SOCK_DGRAM  &&
         type != SOCK_RAW)
    {
        debug_print ("sys_socket: [FAIL] type not supported\n");
        goto fail;
        //return -1;
    }

    if (protocol < 0){
        debug_print ("sys_socket: [FAIL] protocol not supported\n");
        goto fail;
        //return -1;
    }


    // Current process.
    
    p = (struct process_d *) processList[current_process];
     
    if ( (void *) p == NULL )
    {
        debug_print ("sys_socket: p fail\n");
        printf      ("sys_socket: p fail\n");
        goto fail;
        //refresh_screen();
        //return -1;
    }


    //
    // Socket structure.
    //
    
    // #todo:
    // Create a helper function to do this job.
    // This functions need to create the object and need to have this switch
    // for different families. create_socket( family, type, protocol)
    // it returns the socket structure pointer.
    
    // Criamos um socket vazio.
    // IN: ip and port.

    __socket = (struct socket_d *) create_socket_object();
  
    if ( (void *) __socket == NULL )
    {
        debug_print ("sys_socket: [FAIL] __socket fail\n");
        printf      ("sys_socket: [FAIL] __socket fail\n");
        goto fail;

    }else{

        // #bugbug
        // The private socket of a process.
        p->priv = __socket;

        // family, type and protocol.
        __socket->family   = family;
        __socket->type     = type;      // DATAGRAM or STREAM 
        __socket->protocol = protocol;

        // #Initialized with '0'.
        __socket->ip   = ip;
        __socket->port = port;

        __socket->pid = (pid_t) current_process;
        __socket->uid = (uid_t) current_user;
        __socket->gid = (gid_t) current_group;


       //
       // Create file!
       //

       // family
       // Setup the addr.

       // #importante
       // As rotinas logo abaixo criarão o arquivo
       // e retornarão o fd.

       switch (family)
       {
           case AF_GRAMADO:
               debug_print ("sys_socket: AF_GRAMADO\n");
               __socket->addr = addr;
               return (int) socket_gramado ( __socket, 
                                AF_GRAMADO, type, protocol );
               break;

           //case AF_LOCAL:
           case AF_UNIX:
               debug_print ("sys_socket: AF_UNIX\n");
               __socket->addr =  addr;
               return (int) socket_unix ( __socket, 
                                AF_UNIX, type, protocol );
               break;

           //#bugbug: 
           //talvez precisamos rever sockaddr 
           //para essa função, e usarmos outra estrutura.               
           case AF_INET:
               debug_print ("sys_socket: AF_INET\n");
               __socket->addr_in = addr_in;
               return (int) socket_inet ( __socket, 
                                AF_INET, type, protocol );
               break;

           // ...
           
           default:
               debug_print ("sys_socket: [FAIL] bad family\n");
               debug_print ("sys_socket: Couldn't create the file\n");
               goto fail;
               break;
        };

        // ...
    };

    //fail.
    
fail:
    debug_print ("sys_socket: [FAIL] Something is wrong!\n");
    refresh_screen();
    return (int) (-1);
}


// Get the pointer for the socket structure of the current process
// given the fd.
struct socket_d *get_socket_from_fd (int fd){

    struct process_d *p;
    file *_file;
    
    
    if (fd<0 || fd>=32)
        return (struct socket_d *) 0;


    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL)
        return (struct socket_d *) 0;
 
        
    _file = (file *) p->Objects[fd];    
    if ( (void *) _file == NULL)
        return (struct socket_d *) 0;


    // Get the pointer for the socket structure of the current process
    // given the fd.
    return (struct socket_d *) _file->socket;
}


// Os dois são arquivos no mesmo processo. O processo atual.
int
sock_socketpair ( 
    int family, 
    int type, 
    int protocol, 
    int usockvec[2] )
{

    int fd1 = -1; 
    int fd2 = -1;
    struct socket_d *sock1;
    struct socket_d *sock2;


    fd1 = sys_socket(family,type,protocol);
    sock1 = get_socket_from_fd(fd1);
    if( (void*) sock1 == NULL){
        debug_print("sock_socketpair: sock1\n");
        return -1;
    }

    fd2 = sys_socket(family,type,protocol);
    sock2 = get_socket_from_fd(fd2);    
    if( (void*) sock2 == NULL){
        debug_print("sock_socketpair: sock2\n");
        return -1;
    }

    // #todo
    // Antes é preciso verificar a área de memória.

    usockvec[0] = fd1;
    usockvec[1] = fd2;

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

    mysock->state   = SS_CONNECTING;
    servsock->state = SS_CONNECTING;

    mysock->conn = servsock;
    servsock->conn = mysock

    return 0;
}
*/


int socket_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    debug_print ("socket_ioctl: TODO\n");
    return -1;
}


// socket_dialog
// Serviços de soquetes da klibc
// #todo: rever os números.
// #todo: devemos mudar os argumentos 
// para ficar no padrão da libc.
// OUT: ?
unsigned long 
socket_dialog ( 
    unsigned long number, 
    unsigned long arg2, 
    unsigned long arg3, 
    unsigned long arg4 )
{

    printf ("socket_dialog: number=%d \n", number);

    if ( number < 7000 || number >= 8000 ){
        //message
        return 0;
    }


	// número do serviço.

    switch (number)
    {
		//socket(...)	
		//family, type, protocol
		//vai retornar o descritor de uma stream.	
        case 7000:
            debug_print ("socket_dialog: 7000. sys_socket\n");
            return (unsigned long) sys_socket ( (int) arg2, 
                                       (int) arg3, (int) arg4 );
            break;

		//send
		//case 7001:
		//	return (unsigned long) 1; 
		//	break;

		//...

        default:
            debug_print ("socket_dialog: default\n");
            printf      ("socket_dialog: default\n");
            refresh_screen();
            break;
    };

    // Fail.
    return 0;
}



/*
 ************************************** 
 * sys_connect:
 *     Connecting to a server given an address.
 */

// connect.
// Em nosso exemplo o cliente quer se conectar com o servidor.
// Conectando a um servidor dado um endereço.
// O endereço pode vir em formatos diferentes dependendo
// do domínio indicado na estrutura.

// #atenção
// O servidor poderá estar conectado a vários clientes,
// mas estará ouvindo a apenas um por vez. Ou precisaremos 
// de instâncias.


// #todo
// O socket do cliente precisa ter um fd no processo servidor.

// IN: client fd, address, address len
// OUT: 0=ok <0=fail

int 
sys_connect ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{
    
    // #??
    // connect() eh chamado uma vez pelo cliente quando
    // ele inicializa. Essa chamada fornece o fd do cliente.
    // O servidor quando chama accept() seleciona um dos
    // clientes conectados. 
    // O servidor nao pode simplesmente aceitar
    // o ultimo que se conectou.
    // #bugbug: lembrando que nosso write copia de um socket para outro.
    // Entao podemoriamos deixar as conexoes pendentes e selecionarmos
    // somete uma a cada accept. 
    // O write ira falhar se nao estiver conectado?


    // #todo
    // O socket do cliente precisa de um arquivo aberto no
    // processo alvo.
    // #bugbug:
    // Se nao fecharmos o arquivo ao fim da conexao, entao
    // a lista de arquivos abertos se esgotara rapidamente.

    struct process_d *cProcess;  // Client process.
    struct process_d *sProcess;  // Server process.
    
    int target_pid = -1;
    
    struct socket_d *client_socket;
    struct socket_d *server_socket;
    
    int client_socket_fd = -1;

    struct file_d *f;


    //#importante
    //no caso de endereços no estilo inet
    //vamos precisar de outra estrututura.
    struct sockaddr_in *addr_in;


    client_socket_fd = sockfd;


    printf ("sys_connect: PID %d | Client socket fd %d | \n",
        current_process, client_socket_fd );
    

    // ?? the address.
    // #todo: type.
    // da um problema na compilação.
    //addr_in = (?) addr;
    
    addr_in = addr;


    //client_socket_fd é um soquete de quem quer se conecta
    //o addr indica o alvo.
    if ( client_socket_fd < 0 || client_socket_fd >= 32 )
    {
        printf ("sys_connect: client_socket_fd fail\n");
        goto fail;
    }

    // Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL )
    {
        printf ("sys_connect: addr fail\n");
        goto fail;
    }


    // Getting the target PID.
    // #todo:
    // Devemos obter o número do processo alvo dado um endereço.
    // O tipo de endereço depende do tipo de domínio (família).
 
    // Tente inet, ao menos que mudemos de planos por 
    // encontrarmos af_gramado, af_unix ou af_local.
    int ____in = 1;  


    // #importante
    // opções de domínio se o endereço é no estilo unix. 
    // >>> sockaddr
    switch (addr->sa_family)
    {
        // AF_GRAMADO = 8000
        // Vamos obter o número do processo alvo dado o endereço.
        // 32 ports only.
        case AF_GRAMADO:
            debug_print ("sys_connect: AF_GRAMADO ok\n");
            
            // window server
            if ( addr->sa_data[0] == 'w' && addr->sa_data[1] == 's' ){   
                target_pid = (int) gramado_ports[GRAMADO_WS_PORT]; 
            }

            // network server
            if ( addr->sa_data[0] == 'n' && addr->sa_data[1] == 's' ){   
                target_pid = (int) gramado_ports[GRAMADO_NS_PORT]; 
            }

            // file system server
            if ( addr->sa_data[0] == 'f' && addr->sa_data[1] == 's' ){   
                target_pid = (int) gramado_ports[GRAMADO_FS_PORT]; 
            }

            // ...
            
            if ( target_pid < 0 )
            {
                debug_print ("sys_connect: target_pid fail\n");
                goto fail;
            }

            printf ("sys_connect: target pid %d \n", target_pid);
            
            // não tente inet, somos af_gramado
            ____in = 0;
            break;
        
        // #todo
        // Podemos usar isso no caso do  window server.
        // Pois se trata de uma conexão local.
        //case AF_LOCAL:
        case AF_UNIX:
            // Essa conexão local usa endereços no sistema de arquivos.
            // #todo: Implementar isso.
            debug_print ("sys_connect: [TODO] AF_UNIX \n");
            //target_pid = -1;
            // não tente inet, somos af_unix
            ____in = 0;

            goto fail;
            break;
    };

    // >>> sockaddr_in
    if ( ____in == 1 )
    {
      // opções de domínio se o endereço é no estilo internet.
      switch (addr_in->sin_family)
      {
        // Estamos usando inet em conexão local.
        // Então precisamos usar localhost como ip.
            
        case AF_INET:
            debug_print ("sys_connect: AF_INET\n");
            printf      ("sys_connect: AF_INET port %d \n", 
                addr_in->sin_port);
            
            // WS
            // Se a porta for , então usaremos o pid do WS.
            // 4040
            if (addr_in->sin_port == PORTS_WS){
                printf ("sys_connect: Connecting to the Window Server on port %d ...\n",
                    addr_in->sin_port);
                printf("sys_connect: IP {%x}\n",
                    addr_in->sin_addr.s_addr );
                refresh_screen();
                target_pid = (int) gramado_ports[GRAMADO_WS_PORT]; 
                break;
            }
     
            // NS
            // Se a porta for , então usaremos o pid do NS.
            // 4041
            if (addr_in->sin_port == PORTS_NS){
                printf ("sys_connect: Connecting to the Network Server on port %d...\n",
                    addr_in->sin_port);
                printf("sys_connect: IP {%x}\n",
                    addr_in->sin_addr.s_addr );
                refresh_screen();
                //while(1){}
                target_pid = (int) gramado_ports[GRAMADO_NS_PORT]; 
                break;
            }
            
            //PORTS_FS

            // FTP
            if (addr_in->sin_port == 21){
                printf("$$$$ FTP $$$$\n");
                refresh_screen();
                goto fail;
            }

            // Telnet
            if (addr_in->sin_port == 23){
                printf("$$$$ Telnet $$$$\n");
                refresh_screen();
                goto fail;
            }

            // DHCP
            if (addr_in->sin_port == 67){
                printf("$$$$ DHCP $$$$\n");
                refresh_screen();
                goto fail;
            }
            
            // HTTP
            if (addr_in->sin_port == 80){
                printf("$$$$ HTTP $$$$\n");
                refresh_screen();
                goto fail;
            }

            // Drop!
            
            printf("sys_connect: [FAIL] Port not valid {%d}\n",
                addr_in->sin_port);
            goto fail;
            break;
             
        //... 
        
        default:
            debug_print ("sys_connect: domain not supported\n");
            printf      ("sys_connect: [FAIL] Family not supported! %d \n",
                addr_in->sin_family);
            goto fail;
            break;
      };
    }


//__go:

    //
    // == Client process =============================
    //
    
    // Vamos obter o arquivo do tipo soquete
    // que pertence ao sender.
    
    // sender's process
    cProcess = (struct process_d *) processList[current_process];
 
    if ( (void *) cProcess == NULL ){
        debug_print ("sys_connect: cProcess fail\n");
        printf      ("sys_connect: cProcess fail\n");
        goto fail;
    }

    // sender's file
    // Objeto do tipo socket.
    // O cliente criou esse socket antes de chamar o connect().
    f = (file *) cProcess->Objects[client_socket_fd];

    if ( (void *) f == NULL )
    {
        printf ("sys_connect: f fail\n");
        goto fail;
    }

    //is socket??
    
    int __is = -1;
    
    __is = is_socket ((file *)f);
    if (__is != 1)
    {
        printf ("sys_connect: [FAIL] f is not a socket\n");
        goto fail;
    }


    // Pega a estrutura de socket associada ao arquivo.
    // socket structure in the senders file.
    //s = (struct socket_d *) p->priv; 
    client_socket = (struct socket_d *) f->socket;   
    
    if ( (void *) client_socket == NULL )
    {
        printf ("sys_connect: [FAIL] client_socket fail\n");
        goto fail;
    }

    if (client_socket->state != SS_UNCONNECTED) {
        printf ("sys_connect: socket not SS_UNCONNECTED\n");
        goto fail;
    }

    //
    // == Server process ===============================
    //

    // #todo
    // O socket do cliente precisa ter um fd no processo servidor.
 
    // target pid.
    if (target_pid<0)
    {
        debug_print ("sys_connect: [FAIL] target_pid\n");
        printf      ("sys_connect: [FAIL] target_pid\n");
        goto fail;
    }


    // process
    // O processo cliente chamou essa função e
    // então pegaremos agora o processo alvo,
    // que é um servidor.
     
    sProcess = (struct process_d *) processList[target_pid];
 
    if ( (void *) sProcess == NULL ){
        debug_print ("sys_connect: sProcess fail\n");
        printf      ("sys_connect: sProcess fail\n");
        goto fail;
    }


    
    // Procurando um slot livre.
    int __slot=0;
    for (__slot=0; __slot<32; __slot++)
    {
         if ( sProcess->Objects[__slot] == 0 ){ goto __OK_new_slot; }
    };
    panic ("sys_connect: [FIXME] We need a slot in the server\n");
__OK_new_slot:
    client_socket->clientfd_on_server = __slot;



    // Esse é o socket do processo servidor.
    // Sim, porque é o cliente que está tentando se conectar.
    // Dessa forma o alvo é o servidor.

    server_socket = (struct socket_d *) sProcess->priv;
    
    //
    // == Connecting! ======================================
    //
    
    // #bugbug
    // connect() eh chamado somente uma vez pelo cliente.
    // a conexao deve ficar pendente e o accept
    // seleciona uma delas.
    // #test: Pra começar vamos deixar apenas uma pendente
    // e o accept() selecionara ela.
 
 
    // #todo
    // Temos que colocar os pedidos de conexão em uma fila.
    // O tamanho dessa fila foi determinado pelo servidor
    // com a chamada listen. Mas podemos ter um tamanho padrão.
    // Talvez tamanho 1 para começar.
    // Conectando o socket do processo alvo ao ponto de
    // conecção do processo cliente.
    // Conectando o socket do cliente ao ponto de conecção do
    // processo servidor.
    // Acionando as flags que indicam a conecção.
    // Nesse momento poderíamos usar a flag SS_CONNECTING
    // e a rotina accept() mudaria para SS_CONNECTED. 
    
    client_socket->conn = server_socket;
    server_socket->conn = client_socket;

    client_socket->state = SS_CONNECTING;
    server_socket->state = SS_CONNECTING;
    debug_print("sys_connect: Pending connection\n");
    printf     ("sys_connect: Pending connection\n");
 
    
    // #todo
    // Precisamos de uma lista de conexoes pendentes.
    // O cliente invocou a conexao apenas uma vez
    // e precisa uasr o servidor varias vezes
    // #obs: Isso funcionou. Vamos tentar com lista.
    // #ps: algumas implementacoes usam lista encadeada
    // de conexoes incompletas. 'server_socket->iconn'
    // #bugbug: essa lista deve ficar na estrutura de socket
    // e nao na estrutura de processo, dessa forma
    // o servidor pode ter mais de uma socket.
    
    sProcess->socket_pending_list[0] = (unsigned long) client_socket;
    
 
    //ok.
    refresh_screen();
    return 0;

//fail

fail:
    refresh_screen();
    return -1;
}   


// libc shutdown() function.
// See: https://linux.die.net/man/3/shutdown
int sys_socket_shutdown (int socket, int how)
{
    // #todo
    // desconectar dois sockets.
    // mas nao destruir o socket ...


    debug_print ("sys_socket_shutdown: [TODO]\n");
    printf      ("sys_socket_shutdown: [TODO] fd=%d how=%d\n",
        socket, how );


    if ( socket < 0 )
    {
        debug_print ("sys_socket_shutdown: [FAIL] fd\n");
        printf      ("sys_socket_shutdown: [FAIL] fd\n");
        goto fail;
    }
    

    struct process_d *p;
    file *f;
    struct socket_d *s;
    
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL )
    {
        debug_print ("sys_socket_shutdown: p fail\n");
        printf      ("sys_socket_shutdown: p fail\n");
        goto fail;
    }
 
    // sender's file
    // Objeto do tipo socket.
    f = (file *) p->Objects[socket];

    if ( (void *) f == NULL )
    {
        debug_print ("sys_socket_shutdown: f fail\n");
        printf      ("sys_socket_shutdown: f fail\n");
        goto fail;
    }

    //is socket??
    
    int __is = -1;
    
    __is = is_socket ((file *)f);
    if(__is != 1)
    {
        debug_print ("sys_socket_shutdown: f is not a socket\n");
        printf      ("sys_socket_shutdown: f is not a socket\n");
        goto fail;
    }

    //
    // == socket =====================
    //

    // Pega a estrutura de socket associada ao arquivo.
    // socket structure in the senders file.
    //s = (struct socket_d *) p->priv; 
    s = (struct socket_d *) f->socket;   
    
    if ( (void *) s == NULL )
    {
        debug_print ("sys_socket_shutdown: s fail\n");
        printf      ("sys_socket_shutdown: s fail\n");
        goto fail;
        
    }else{

        s->conn->state = SS_UNCONNECTED;
        s->conn->conn = (struct socket_d *) 0;
        
        s->state = SS_UNCONNECTED;
        s->conn = (struct socket_d *) 0;

        //ok
        return 0;

    };


    // ...

fail:
    debug_print ("sys_socket_shutdown: [FAIL]\n");
    printf      ("sys_socket_shutdown: [FAIL]\n");
    return -1;
}



// Deprecated!
int sys_accept_sender (int n)
{
    debug_print ("sys_accept_sender: [DEPRECATED]\n");
    printf      ("sys_accept_sender: [DEPRECATED]\n");
    return -1;
}




/*
 ***************** 
 * sys_accept:
 * 
 */

// The accept() system call causes the process to block 
// until a client connects to the server. 
//  It returns a new file descriptor.

// #todo:
// Aceitar uma conecção.
// Essa função é chamada dentro do loop, então
// será chamada várias vezes ...
// #importante:
// A intenção é aceitar várias conecções mas ouvir apenas
// uma por vez.

// IN: ??
// OUT: ?? Retornamos o fd do socket aceito.
// provavelmente o que iremos ouvir.

// Alternative way.
// It returns the fd of the server and write() will copy the data.  

// #todo
// Pega um socket da lista de conexoes incompletas.

int 
sys_accept2 (
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{

    //
    // == todo =========================
    //

    // #solution
    // We create a new socket and connect this 
    // new socket with the client.
    // This way we can return the fd of the socket.
    // When the write() writes in the new socket, the data
    // will be copied to the client socket.
    
    /*
     * From Linux 0.98.1:
     * 
     * For accept, 
     * we attempt to create a new socket, 
     * set up the link with the client, 
     * wake up the client, then 
     * return the new connected fd.
     */
     
     // #todo
     // We need to create a new socket. Only this way the process
     // will have a new file in p->Objects[].


    struct process_d  *sProcess; //server process
    file              *f;

    struct socket_d   *sSocket;  //server socket
    struct socket_d   *cSocket;  //client socket
    
    // #todo
    // O argumento dá o descritor para o socket do servidor.
    // A função accept seleciona um dos sockets da lista
    // de conexões pendentes criadas por listen() e conecta
    // com o socket do servidor.
    // Ao fim devemos retornar o descritor do socket selecionado
    // na lista de conexões pendentes.

    // #debug
    //debug_print ("sys_accept:\n");

    // fd
    // ?? Esse é o socket do servidor.
    if ( sockfd < 0 || sockfd >= 32 )
    {
        debug_print ("sys_accept2: [FAIL] sockfd\n");
        printf      ("sys_accept2: [FAIL] sockfd\n");
        goto fail;
    }

    // Check addr structure.
    // #bugbug: Ainda não sabemos qual é a estrutura de
    // endereços usada.
    // #bugbug: Ainda não estamos usando isso.
    if ( (void *) addr == NULL )
    {
        debug_print ("sys_accept2: [FAIL] addr\n");
        printf      ("sys_accept2: [FAIL] addr\n");
        goto fail;
    }

    //
    // Current process. (The server)
    //
    
    sProcess = (struct process_d *) processList[current_process];
 
    if ( (void *) sProcess == NULL )
    {
        debug_print ("sys_accept2: [FAIL] sProcess\n");
        printf      ("sys_accept2: [FAIL] sProcess\n");
        goto fail;
    }


    // O objeto que se refere ao socket do servidor.

    // file
    // The socket is a file and belongs to the process.
    f = (file *) sProcess->Objects[sockfd];

    if ( (void *) f == NULL )
    {
        debug_print ("sys_accept2: f fail\n");
        printf      ("sys_accept2: f fail\n");
        goto fail;
    }

    // #todo
    // Poderiamos chamar uma 'helper function' logo apos
    // pegarmos os dois ponteiros para estruturas de socket.
    
    // O socket privado do Servidor.

    // socket
    // Socket structure that belongs to the process.
    // s = (struct socket_d *) p->priv;
    
    sSocket = f->socket;
    
    if ( (void *) sSocket == NULL )
    {
        debug_print ("sys_accept2: [FAIL] sSocket\n");
        printf      ("sys_accept2: [FAIL] sSocket\n");
        goto fail;
    }

    // Isso significa que o cliente chamou connect antes mesmo 
    // do servidor chamar accept ??
    /*
    if (sSocket->state == SS_CONNECTED) 
    {
        printf("sys_accept: [FAIL] socket is already SS_CONNECTED\n");
        refresh_screen();
        return -1;
    }
    */


    /*
    // #test
    // The indicated socket need to be the same of the privete socket.
    if( f->socket != s )
    {
        //#debug Testing ...
        panic("sys_accept: [FIXME] Check the original socket in the process %d!",
            current_process);
    }
    */

    //
    // Socket ok!
    //
    
    
    // #todo
    // Essa funcao nos enviou o fd do socket do servidor.
    // Agora vamos olhar na lista de conexoes existentes nesse
    // socket e pegarmos um dos fd da lista. Em ordem round robing

    /*
    // get next!
    int i=0;
    int max=1;
    //max = s->backlog_max;
    return (int) s->pending_connections[ s->backlog_pos ];
    */
    

    // O que segue abaixo eh um improviso,
    // ja que listen ainda nao funciona
    


    // #debug
    //printf ("sys_accept: process %d | family %d | len %d \n", 
        //current_process, addr->sa_family, addrlen  );


    // #bugbug
    // Wrong, wrong, wrong !!!
    // Se retornarmos o fd do cliente vai falhar,
    // porque nosso write copia de um socket para outro,
    // entao copiaria do cliente para o servidor.
    // Estamos retornando o fd do servidor,
    // entao o write esta copiando no socket do cliente.
    // sys_accept deve apenas pegar um fd da lista de conexoes
    // pending_connections[].
    // Lembre-se que o fd do cliente estah numa lista em outro processo.

 
    // #test
    // Se o socket do servidor já está conectado.
    // Se ele jah esta conectado, entao o seu slave tem um arquivo e esse
    // arquivo deve ir para a lista de arquivos abertos pelo processo?
    // Estamos retornando o fd do proprio servidor porque o write() 
    // copia de um socket para o outro. Mas a intençao nao eh essa.
    
    // #bugbug
    // O socket do servidor precisa estar desconectado.
    // Pois cada accept eh cria uma nova conexao.
    
    if ( sSocket->state == SS_CONNECTED )
    {
        //debug_print ("sys_accept2: Already connected!\n");
        //printf      ("sys_accept2: Already connected!\n");
        //refresh_screen();
        //return -1;
        
        return (int) sockfd;
    }


    // #todo
    // Na verdade precisamos pegar um da fila.
    
    // #test
    // Se a conexão do socket do servidor está pendente.
    // #bugbug
    // Devemos retornar o descritor do socket cliente e
    // não do socket do servidor.
    // Mas como existe cópia durante o write,
    // quando o servidor escrever em seu próprio socket
    // a mensagem vai ser copiada no cliente.
    // #todo: Para devolver um descritor para o servidor,
    // então o socket do cliente deveria estar na lista de
    // arquivos abertos pelo servidor.
    // obs: Por enquanto fica assim. Devolvemos o
    // descritor do proprio servidor. Mas ele está conectado e
    // o cliente receberá a mensagem.
    
    // #ok
    // Pega um socket da lista de conexoes incompletas.
 
    if ( sSocket->state == SS_CONNECTING )
    {
        debug_print ("sys_accept2: CONNECTING !!\n");

        //Server socket. Pre-connect.
        //precisamos mudar no caso de erro no cliente.
        sSocket->state = SS_CONNECTED;
             
        // Se existe outro socket linkado ao socket do servidor.
        cSocket = (struct socket_d *) sProcess->socket_pending_list[0];
        
        // Not valid Client socket
        if ( (void*) cSocket == NULL )
        {
            debug_print ("sys_accept2: [FAIL] cSocket\n");
            sSocket->state = SS_CONNECTING;  //anula.
            goto fail;
        }

        // Valid Client socket
        if ( (void *) cSocket != NULL )
        {
            //ok: usar isso só para debug
            //debug_print ("sys_accept: done\n");

            cSocket->state = SS_CONNECTED;
            
            //retornamos o fd do proprio servidor, pois nosso write copia
            //entre os buffers dos sockets conectados.
            return (int) sockfd;
        }

        //fail
        debug_print ("sys_accept2: [FAIL] Pending connection\n");
        sSocket->state = SS_CONNECTING;  //anula.
        goto fail;
    }


// fail
// #todo:
// Are we already connected?
// So we need a flag to indicate this status.

fail:
    debug_print ("sys_accept2: [FAIL] Something is wrong!\n");
    //printf    ("sys_accept2: [FAIL] Something is wrong!\n");
    refresh_screen();
    return -1;
}


// #todo
// Pega um socket da lista de conexoes incompletas.

// Essa eh uma implementacao tradicional
// Nosso maior objetivo aqui eh retornar o fd arquivo de socket do cliente.

int 
sys_accept (
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{

    //
    // == todo =========================
    //

    // #solution
    // We create a new socket and connect this 
    // new socket with the client.
    // This way we can return the fd of the socket.
    // When the write() writes in the new socket, the data
    // will be copied to the client socket.
    
    /*
     * From Linux 0.98.1:
     * 
     * For accept, 
     * we attempt to create a new socket, 
     * set up the link with the client, 
     * wake up the client, then 
     * return the new connected fd.
     */
     
     // #todo
     // We need to create a new socket. Only this way the process
     // will have a new file in p->Objects[].


    struct process_d  *sProcess; //server process
    file              *f;

    struct socket_d   *sSocket;  //server socket
    struct socket_d   *cSocket;  //client socket
    
    // #todo
    // O argumento dá o descritor para o socket do servidor.
    // A função accept seleciona um dos sockets da lista
    // de conexões pendentes criadas por listen() e conecta
    // com o socket do servidor.
    // Ao fim devemos retornar o descritor do socket selecionado
    // na lista de conexões pendentes.

    // #debug
    //debug_print ("sys_accept:\n");

    // fd
    // ?? Esse é o socket do servidor.
    if ( sockfd < 0 || sockfd >= 32 )
    {
        debug_print ("sys_accept: [FAIL] sockfd\n");
        printf      ("sys_accept: [FAIL] sockfd\n");
        goto fail;
    }

    // Check addr structure.
    // #bugbug: Ainda não sabemos qual é a estrutura de
    // endereços usada.
    // #bugbug: Ainda não estamos usando isso.
    if ( (void *) addr == NULL )
    {
        debug_print ("sys_accept: [FAIL] addr\n");
        printf      ("sys_accept: [FAIL] addr\n");
        goto fail;
    }

    //
    // Current process. (The server)
    //
    
    sProcess = (struct process_d *) processList[current_process];
 
    if ( (void *) sProcess == NULL )
    {
        debug_print ("sys_accept: [FAIL] sProcess\n");
        printf      ("sys_accept: [FAIL] sProcess\n");
        goto fail;
    }


    // O objeto que se refere ao socket do servidor.

    // file
    // The socket is a file and belongs to the process.
    f = (file *) sProcess->Objects[sockfd];

    if ( (void *) f == NULL )
    {
        debug_print ("sys_accept: f fail\n");
        printf      ("sys_accept: f fail\n");
        goto fail;
    }

    // #todo
    // Poderiamos chamar uma 'helper function' logo apos
    // pegarmos os dois ponteiros para estruturas de socket.
    
    // O socket privado do Servidor.

    // socket
    // Socket structure that belongs to the process.
    // s = (struct socket_d *) p->priv;
    
    sSocket = f->socket;
    
    if ( (void *) sSocket == NULL )
    {
        debug_print ("sys_accept: [FAIL] sSocket\n");
        printf      ("sys_accept: [FAIL] sSocket\n");
        goto fail;
    }

    // Isso significa que o cliente chamou connect antes mesmo 
    // do servidor chamar accept ??
    /*
    if (sSocket->state == SS_CONNECTED) 
    {
        printf("sys_accept: [FAIL] socket is already SS_CONNECTED\n");
        refresh_screen();
        return -1;
    }
    */


    /*
    // #test
    // The indicated socket need to be the same of the privete socket.
    if( f->socket != s )
    {
        //#debug Testing ...
        panic("sys_accept: [FIXME] Check the original socket in the process %d!",
            current_process);
    }
    */

    //
    // Socket ok!
    //
    
    
    // #todo
    // Essa funcao nos enviou o fd do socket do servidor.
    // Agora vamos olhar na lista de conexoes existentes nesse
    // socket e pegarmos um dos fd da lista. Em ordem round robing

    /*
    // get next!
    int i=0;
    int max=1;
    //max = s->backlog_max;
    return (int) s->pending_connections[ s->backlog_pos ];
    */
    

    // O que segue abaixo eh um improviso,
    // ja que listen ainda nao funciona
    


    // #debug
    //printf ("sys_accept: process %d | family %d | len %d \n", 
        //current_process, addr->sa_family, addrlen  );


    // #bugbug
    // Wrong, wrong, wrong !!!
    // Se retornarmos o fd do cliente vai falhar,
    // porque nosso write copia de um socket para outro,
    // entao copiaria do cliente para o servidor.
    // Estamos retornando o fd do servidor,
    // entao o write esta copiando no socket do cliente.
    // sys_accept deve apenas pegar um fd da lista de conexoes
    // pending_connections[].
    // Lembre-se que o fd do cliente estah numa lista em outro processo.

 
    // #test
    // Se o socket do servidor já está conectado.
    // Se ele jah esta conectado, entao o seu slave tem um arquivo e esse
    // arquivo deve ir para a lista de arquivos abertos pelo processo?
    // Estamos retornando o fd do proprio servidor porque o write() 
    // copia de um socket para o outro. Mas a intençao nao eh essa.
    
    // #bugbug
    // O socket do servidor precisa estar desconectado.
    // Pois cada accept eh cria uma nova conexao.
    
    if ( sSocket->state == SS_CONNECTED )
    {
        //debug_print ("sys_accept2: Already connected!\n");
        //printf      ("sys_accept2: Already connected!\n");
        //refresh_screen();
        //return -1;
        
        return (int) sockfd;
    }


    // #todo
    // Na verdade precisamos pegar um da fila.
    
    // #test
    // Se a conexão do socket do servidor está pendente.
    // #bugbug
    // Devemos retornar o descritor do socket cliente e
    // não do socket do servidor.
    // Mas como existe cópia durante o write,
    // quando o servidor escrever em seu próprio socket
    // a mensagem vai ser copiada no cliente.
    // #todo: Para devolver um descritor para o servidor,
    // então o socket do cliente deveria estar na lista de
    // arquivos abertos pelo servidor.
    // obs: Por enquanto fica assim. Devolvemos o
    // descritor do proprio servidor. Mas ele está conectado e
    // o cliente receberá a mensagem.
    
    // #ok
    // Pega um socket da lista de conexoes incompletas.
 
    if ( sSocket->state == SS_CONNECTING )
    {
        debug_print ("sys_accept: CONNECTING !!\n");

        //Server socket. Pre-connect.
        //precisamos mudar no caso de erro no cliente.
        sSocket->state = SS_CONNECTED;
             
        // Se existe outro socket linkado ao socket do servidor.
        cSocket = (struct socket_d *) sProcess->socket_pending_list[0];
        
        // Not valid Client socket
        if ( (void*) cSocket == NULL )
        {
            debug_print ("sys_accept: [FAIL] cSocket\n");
            sSocket->state = SS_CONNECTING;  //anula.
            goto fail;
        }

        // Valid Client socket
        if ( (void *) cSocket != NULL )
        {
            //ok: usar isso só para debug
            //debug_print ("sys_accept: done\n");

            cSocket->state = SS_CONNECTED;
            
            //retornamos o fd do proprio servidor, pois nosso write copia
            //entre os buffers dos sockets conectados.
            return (int) sockfd;
        }

        //fail
        debug_print ("sys_accept: [FAIL] Pending connection\n");
        sSocket->state = SS_CONNECTING;  //anula.
        goto fail;
    }


// fail
// #todo:
// Are we already connected?
// So we need a flag to indicate this status.

fail:
    debug_print ("sys_accept: [FAIL] Something is wrong!\n");
    //printf    ("sys_accept: [FAIL] Something is wrong!\n");
    refresh_screen();
    return -1;
}


/*
 ********************************
 * sys_bind:
 *    When a socket is created with socket(), it exists in a 
 *    name space (address family) but has no address assigned to it. 
 *    bind() assigns the address specified by addr to the socket 
 *    referred to by the file descriptor sockfd.
 */

// See:
// https://man7.org/linux/man-pages/man2/bind.2.html

int 
sys_bind ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{

    struct process_d  *p;   // Process
    struct file_d     *f;   // File
    struct socket_d   *s;   // Socket

    int i=0;


    // #debug
    debug_print ("sys_bind:\n");
    printf      ("sys_bind: PID %d | fd %d | \n",
        current_process, sockfd );


    // fd
    if ( sockfd < 0 || sockfd >= 32 )
    {
        debug_print ("sys_bind: sockfd fail\n");
        printf      ("sys_bind: sockfd fail\n");
        goto fail;
    }

    // Check addr structure.
    if ( (void *) addr == NULL )
    {
        debug_print ("sys_bind: addr fail\n");
        printf      ("sys_bind: addr fail\n");
        goto fail;
    }


    // process
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL )
    {
        debug_print ("sys_bind: p fail\n");
        printf      ("sys_bind: p fail\n");
        goto fail;
    }
 
 
    // file
    // O objeto do tipo socket.
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL )
    {
        debug_print ("sys_bind: f fail\n");
        printf      ("sys_bind: f fail\n");
        goto fail;
    }
    
 
    // socket
    // A estrutura de socket associada ao
    // objeto do tipo socket.
    s = (struct socket_d *) f->socket;

    if ( (void *) s == NULL )
    {
        debug_print ("sys_bind: s fail\n");
        printf      ("sys_bind: s fail\n");
        goto fail; 
    }


    //
    // family
    //
    
    // Everything is ok.
    // Binding the name to the socket.
    // So now we need to include the 'name' into the socket structure
    // respecting the socket's family.
    // Each family has a different size?

    //++
    // AF_GRAMADO
    if (s->addr.sa_family == AF_GRAMADO){
        printf ("sys_bind: Binding the name to the socket.\n");

        // Always 14.
        for (i=0; i<14; i++){ s->addr.sa_data[i] = addr->sa_data[i]; }; 

        printf ("sys_bind: process %d ; family %d ; len %d \n", 
            current_process, addr->sa_family, addrlen  );

        debug_print ("sys_bind: bind ok\n");
        return 0;
    }
    //--


    //++
    // AF_UNIX ou AF_LOCAL
    // See: http://man7.org/linux/man-pages/man7/unix.7.html
    if (s->addr.sa_family == AF_UNIX){
        debug_print ("sys_bind: AF_UNIX not supported yet\n");
        //for (i=0; i<14; i++){ s->addr.sa_data[i] = addr->sa_data[i]; }; 
        return -1;
    }
    //--    


    //++
    // AF_INET
    if (s->addr.sa_family == AF_INET){
        debug_print ("sys_bind: AF_INET not supported yet\n");
        //for (i=0; i<14; i++){ s->addr.sa_data[i] = addr->sa_data[i]; }; 
        return -1;    
    } 
    //--


    // #fail
    // A família é de um tipo não suportado.
  
    // DEFAULT:
    debug_print ("sys_bind: [FAIL] family not valid\n");
    printf      ("sys_bind: [FAIL] family not valid\n");

   // fail

fail:

    debug_print ("sys_bind: [FAIL] Something is wrong!\n");
    printf      ("sys_bind: [FAIL] Something is wrong!\n");
    refresh_screen();
    return (int) (-1);
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
        printf ("sys_getsockname: Getting the name and the size\n");
        
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
    
    printf ("sys_getsockname: process %d ; family %d ; len %d \n", 
        current_process, addr->sa_family, addrlen  );
 
     
    printf ("sys_getsockname: fail\n");
    refresh_screen();
    return -1;
}



/*
 ************************** 
 * sys_listen:
 * 
 */

/*
 The backlog argument defines the maximum length to which the queue of
 pending connections for sockfd may grow.  If a connection request
 arrives when the queue is full, the client may receive an error with
 an indication of ECONNREFUSED or, if the underlying protocol supports
 retransmission, the request may be ignored so that a later reattempt
 at connection succeed
*/

// See:
// https://man7.org/linux/man-pages/man2/listen.2.html

// IN:
// sockfd  = The fd of the server's socket.
// backlog = The server tell us the the 'size of the list'.

int sys_listen (int sockfd, int backlog) 
{
    int n=0;


    debug_print ("sys_listen: [TODO]\n");
    printf      ("sys_listen: [TODO] fd=%d backlog=%d\n",sockfd,backlog);


    if ( sockfd < 0 )
    {
        debug_print ("sys_listen: [FAIL] fd\n");
        printf      ("sys_listen: [FAIL] fd\n");
        goto fail;
    }

    // Wrong n. Ajusting to default.
    if( backlog <= 0 )
    { 
        debug_print ("sys_listen: [FIXME] backlog fail\n");
        n=1; 
    }

    // #hackhack
    // We need to do something
    if( backlog > 8 )
    { 
        debug_print ("sys_listen: [FIXME] backlog too long\n");
        n=1; 
    }


    //
    // TODO !!!
    //

//
// ==============================================
//

   
    /*
    // We need to get the socket structure in the process structure.
    // We need to clean the list. Not here. when creating the socket.
    //int i=0;
    //for(i=0; i<32; i++) { s->pending_connections[i] = 0;};
    // Updating the list support.
    //s->backlog_max = backlog;  //max
    //s->backlog_pos = 0;        //current 
    */

    struct process_d *p;
    file *f;
    struct socket_d *s;
    
    p = (struct process_d *) processList[current_process];
 
    if ( (void *) p == NULL )
    {
        debug_print ("sys_listen: p fail\n");
        printf      ("sys_listen: p fail\n");
        goto fail;
    }
 
    // sender's file
    // Objeto do tipo socket.
    f = (file *) p->Objects[sockfd];

    if ( (void *) f == NULL )
    {
        debug_print ("sys_listen: f fail\n");
        printf      ("sys_listen: f fail\n");
        goto fail;
    }

    //is socket??
    
    int __is = -1;
    
    __is = is_socket ((file *)f);
    if(__is != 1)
    {
        debug_print ("sys_listen: f is not a socket\n");
        printf      ("sys_listen: f is not a socket\n");
        goto fail;
    }


    // Pega a estrutura de socket associada ao arquivo.
    // socket structure in the senders file.
    //s = (struct socket_d *) p->priv; 
    s = (struct socket_d *) f->socket;   
    
    if ( (void *) s == NULL )
    {
        debug_print ("sys_listen: s fail\n");
        printf      ("sys_listen: s fail\n");
        goto fail;
        
    }else{

        s->backlog_max = backlog;
    };

    // ...

    debug_print ("sys_listen: [TODO] continue...\n");
    printf      ("sys_listen: [TODO] continue...\n");


//
// ==============================================
//


fail:
    debug_print ("sys_listen: [FAIL]\n");
    printf      ("sys_listen: [FAIL]\n");
    refresh_screen();
    //while(1){}
    
    return -1;
}



/*
 ******************************************
 * create_socket_object: 
 *     It creates a socket structure.
 *     Every process has its own socket structure.
 *     The status is: NOT CONNECTED.
 */

// IN: ip and port.

struct socket_d *create_socket_object (void){

    struct socket_d *s;
    int i=0;


    s = (void *) kmalloc ( sizeof( struct socket_d ) );

    if ( (void *) s ==  NULL ){
        printf ( "create_socket_object: allocation fail \n");
        refresh_screen();
        return NULL;

    }else{

        //s->objectType =
        //s->objectClass =

        s->used = 1;
        s->magic = 1234;
        
        //#test
        s->family = 0;
        s->type = 0;
        s->protocol = 0;
        
        //s->ip = ip;
        //s->port = port;
        
        s->state = SS_UNCONNECTED;
        
        s->private_file = (file *) 0;
        
        //s->addr = (struct sockaddr) 0;
        
        
        s->pid = (pid_t) current_process;
        s->uid = (uid_t) current_user;
        s->gid = (gid_t) current_group;
        
        
        s->conn_copy = 1;  //YES, copy!
        
        // Initializing pointers.
        // We don't want this kinda crash in the real machine.
        
        // Connection ponter.
        // Its a pointer to another socket. Is it?
        s->conn = (struct socket_d *) 0;
        
       // The server finds a place in the server_process->Objects[i].
        s->clientfd_on_server = -1;
        
        // ...
        
        s->backlog_max=1;
        s->backlog_pos=0;
        for(i=0; i<32; i++){
            s->pending_connections[i]=0;
        }
          
        //...
        
    };


    return (struct socket_d *) s;
}


unsigned long getSocketIP ( struct socket_d *socket ){

    if ( (void *) socket ==  NULL ){
        return 0;

    }else{ return (unsigned long) socket->ip; };
}


unsigned long getSocketPort ( struct socket_d *socket ){

    if ( (void *) socket ==  NULL ){
        return 0;

    }else{ return (unsigned long) socket->port; };
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
        socket->ip   = (unsigned long)  ip;
        socket->port = (unsigned short) port;
        return 0;
    };
}



int socket_read ( unsigned int fd, char *buf, int count ){

    debug_print ("socket_read:[TODO]\n");
    return -1;
}


int socket_write ( unsigned int fd, char *buf, int count ){

    debug_print ("socket_write:[TODO]\n");
    return -1;
}


// Conjunto especiais de portas.
// Usados apenas na famíla AF_GRAMADO.
int socket_set_gramado_port (int port, int pid){

    //port
    if ( port<0 || port >31){
        debug_print ("socket_set_gramado_port: port fail\n");
        return -1;
    }

    //pid
    //todo: max
    if (pid<0){
        debug_print ("socket_set_gramado_port: port fail\n");
        return -1;
    }       
    
    gramado_ports[port] = (int) pid;

    return 0;
}



int is_socket (file *f){

    // Fail
    if ( (void *) f == NULL ){ return (int) (-1); }

    // Yes
    if ( f->____object == ObjectTypeSocket ){ return (int) 1; } 
        
    // No
    return 0;
}


int is_virtual_console (file *f){

    // Fail
    if ( (void *) f == NULL ){ return (int) (-1); }

    // Yes
    if ( f->____object == ObjectTypeVirtualConsole ){ return (int) 1; } 
   
    // No
    return 0;
}


/*
// #todo
// shutdown the socket. 
// shutdown some socket for the current process.
// this is a fd for a list of objects of the current process.
// 'fd' file descriptor.
// 'how' indicates if we shutdown for read or for write.

int sys_socket_shutdown (int fd, int how);
int sys_socket_shutdown (int fd, int how)
{
    // #todo: 
    debug_print ("sys_socket_shutdown: [TODO] \n");
    return -1;
}
*/



// ...


//
// End.
//



