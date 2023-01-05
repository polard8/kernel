
// socket.c
// See:
// https://en.wikipedia.org/wiki/Berkeley_sockets

#include <kernel.h>  

// Internal
#define SYS_SOCKET_IP(a, b, c, d)  (a << 24 | b << 16 | c << 8 | d)

// globals
// see: socket.h
struct socket_d  *CurrentSocket;
struct socket_d  *LocalHostHTTPSocket;
// ...
unsigned long socketList[SOCKET_COUNT_MAX];
// private:
// A small list of PIDs.
// A server can register its PID here
// telling the system that it is responsible for this kind of service.
static pid_t gramado_ports[GRAMADO_PORT_MAX];

// ====================
static int __socket_initialize_gramado_ports(void);
// ====================

/*
 * create_socket_object: 
 *     It creates a socket structure.
 *     Every process has its own socket structure.
 *     The status is: NOT CONNECTED.
 */
struct socket_d *create_socket_object(void)
{
    struct socket_d *s;
    register int i=0;

// Create and clean the structure.
    s = (void *) kmalloc ( sizeof( struct socket_d ) );
    if ( (void *) s ==  NULL ){
        printf ( "create_socket_object: s\n");
        goto fail;
    }
    memset( s, 0, sizeof(struct socket_d) );

    //s->objectType =
    //s->objectClass =

    s->pid = (pid_t) get_current_process();
    s->uid = (uid_t) current_user;
    s->gid = (gid_t) current_group;

// #todo
    //s->addr = 0;

    s->family = 0;
    s->type = 0;
    s->protocol = 0;

    s->ip_ipv4 = (unsigned int) 0;
    s->ip_ipv6 = (unsigned long) 0;
    s->port = (unsigned short) 0;

// Initializing pointers.
// We don't want this kinda crash in the real machine.

// Connection ponter.
// Its a pointer to another socket. Is it?
    s->conn = (struct socket_d *) 0;

// The counter
    s->connections_count = 0;

    for (i=0; i<32; i++){
        s->pending_connections[i]=0;
    };
    s->backlog_head = 0;   //sai
    s->backlog_tail = 0;   //entra
    s->backlog_max = 4;    //default 

// Not yet.
// listen() will set this flag.
    s->AcceptingConnections = FALSE;
// The socket needs to be initialized 
// in the disconnected state.
    s->state = SS_UNCONNECTED;
// #bugbug
// It tells us that write() will copy 
// the data to the connected socket.
    s->conn_copy = TRUE;  //YES, copy!
// The server finds a place in the server_process->Objects[i].
    s->clientfd_on_server = -1;

    s->private_file = (file *) 0;

    // ...

    s->flags = 0;
    s->used = TRUE;
    s->magic = 1234;

    return (struct socket_d *) s;

fail:
    refresh_screen();
    return NULL;
}

unsigned int getSocketIPV4(struct socket_d *socket)
{
    if ( (void *) socket ==  NULL ){
        return 0;
    }
    if (socket->magic!=1234){
        return 0;
    }
    return (unsigned int) socket->ip_ipv4; 
}

unsigned long getSocketIPV6(struct socket_d *socket)
{
    if ( (void *) socket ==  NULL ){
        return 0;
    }
    if (socket->magic!=1234){
        return 0;
    }
    return (unsigned long) socket->ip_ipv6; 
}

unsigned short getSocketPort(struct socket_d *socket)
{
    if ( (void *) socket ==  NULL ){
        return 0;
    }
    if (socket->magic!=1234){
        return 0;
    }
    return (unsigned short) socket->port; 
}

// Get the pointer for the socket structure 
// given the fd.
// OUT: Returning a pointer for a 
// ring0 socket structure.
struct socket_d *get_socket_from_fd (int fd)
{
    struct process_d *p;
    file *_file;

    if (fd<0 || fd>=OPEN_MAX){
        //msg
        return (struct socket_d *) 0;
    }

// process
    pid_t current_process = (pid_t) get_current_process();
    if (current_process<0 || current_process>=PROCESS_COUNT_MAX){
        goto fail;
    }
    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL ){
        goto fail;
    }

// The file.
    _file = (file *) p->Objects[fd];
    if ( (void *) _file == NULL){
        goto fail;
    }
    if (_file->magic!=1234){
        goto fail;
    }

// The structure.
// Get the pointer for the socket structure given the fd.
    return (struct socket_d *) _file->socket;
fail:
    return (struct socket_d *) 0;
}

// Show the private socket for a process.
void show_socket_for_a_process (pid_t pid)
{
    struct process_d  *p;
    struct socket_d   *s;

    printf ("Socket info for pid %d: \n", pid);

    if (pid<0 || pid >= PROCESS_COUNT_MAX){
        printf ("pid limits\n");
        goto fail;
    }

// process

    p = (struct process_d *) processList[pid];
    if ( (void *) p == NULL ){
        printf("p\n");
        goto fail;
    }
    if ( p->used != TRUE || p->magic != 1234 ){
        printf("p validation\n");
        goto fail;
    }

// Socket struture.
// Pega o ponteiro para a estrutura privada de soquete.
    s = (struct socket_d *) p->priv;
    if ( (void *) s == NULL ){
        printf("s\n");
        goto fail;
    }
    if ( s->used != TRUE || s->magic != 1234 ){
        printf ("s validation\n");
        goto fail;
    }

// Show
// sockaddr structure.  

    printf ("family %d \n",s->addr.sa_family);
    printf ("data %s   \n",s->addr.sa_data);
    //printf ("",s->);
    //printf ("",s->);
    //printf ("",s->);

//done:
    refresh_screen();
    return;

fail:
   refresh_screen();
   return;
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
// Uma estrutura de socket será associada à 
// essa estrutura der arquivo.
// Retornaremos seu fd.
    file *_file;
    struct process_d *Process;
    register int i=0;
    int __slot = -1;

    debug_print ("socket_gramado:\n");

    if ( (void*) sock == NULL ){
        debug_print ("socket_gramado: sock\n");
        goto fail;
    }
    if (sock->magic!=1234){
        debug_print ("socket_gramado: sock validation\n");
        goto fail;
    }
    if (family != AF_GRAMADO){
        debug_print ("socket_gramado: family\n");
        goto fail;
    }

    sock->addr.sa_family  = family;
    sock->addr.sa_data[0] = 'x'; 
    sock->addr.sa_data[1] = 'x';

// Process

    pid_t current_process = (pid_t) get_current_process();
    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        printf ("socket_gramado: current_process\n");
        goto fail;
    }

    Process = (void *) processList[current_process];
    if ( (void *) Process == NULL ){
        printf("socket_gramado: Process\n");
        goto fail;
    }
    if ( Process->used != TRUE || Process->magic != 1234 ){
        printf("socket_gramado: Process validation\n");
        goto fail;
    }

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
    __slot = -1; //fail
    //for ( i=3; i<NUMBER_OF_FILES; i++ )
    for ( i=3; i<31; i++ )
    {
        if ( Process->Objects[i] == 0 )
        { 
            __slot = i;
            break; 
        }
    };

// Check slot validation. 
    if ( __slot == -1 ){
        printf ("socket_gramado: [FAIL] No free slots\n");
        goto fail;
    }

//
// == Buffer ========================
//
    
    //char *buff = (char *) newPage ();
    char *buff = (char *) kmalloc(BUFSIZ);
    if ( (void *) buff == NULL ){
        //Process->Objects[__slot] = (unsigned long) 0;
        debug_print ("socket_gramado: [FAIL] Buffer allocation fail\n");
        printf      ("socket_gramado: [FAIL] Buffer allocation fail\n");
        goto fail;
    }

//
// File
//

    _file = (void *) kmalloc ( sizeof(file) );
    if ( (void *) _file == NULL  ){
        //Process->Objects[__slot] = (unsigned long) 0;
        debug_print ("socket_gramado: [FAIL] _file fail\n");
        printf      ("socket_gramado: [FAIL] _file fail\n");
        goto fail;
    }
    memset( _file, 0, sizeof(struct file_d) );

// Object type
    _file->____object = ObjectTypeSocket;

    _file->pid = (pid_t) current_process;
    _file->uid = (uid_t) current_user;
    _file->gid = (gid_t) current_group;

// sync

    _file->sync.sender   = -1;
    _file->sync.receiver = -1;
    _file->sync.action = ACTION_NULL;
    _file->sync.can_read    = TRUE;
    _file->sync.can_write   = TRUE;
    _file->sync.can_execute = FALSE;
    _file->sync.can_accept  = TRUE;
    _file->sync.can_connect = TRUE;

    _file->sync.block_on_read = FALSE;
    _file->sync.block_on_read_empty = TRUE;

    _file->sync.block_on_write = TRUE;
    _file->sync.block_on_write_full = TRUE;

    _file->sync.lock = FALSE;

// flags
    _file->_flags = __SWR;
// No name for now.
    _file->_tmpfname = NULL;
        //_file->_tmpfname = "socket";

//
// Buffer
//

    _file->_base = buff;
    _file->_p    = buff;
    _file->_lbfsize = BUFSIZ;
// Quanto falta
    _file->_cnt = _file->_lbfsize;
 // Offsets
    _file->_r = 0;
    _file->_w = 0;
// Status do buffer do socket.
    _file->socket_buffer_full = 0;  

// Socket pointer
// Associando a estrutura de socket à estrutura de arquivo.
    _file->socket = sock;

// O arquivo do soquete, o buffer ?
    sock->private_file = (file *) _file; 

// Socket pointer.
// Salvamos o ponteira para estrutura de soquete
// na estrutura de processo do processo atual.
    Process->priv = (void *) sock;

//
// fd
//

    _file->_file = __slot;

// Colocando na lista de arquivos abertos no processo.
    Process->Objects[__slot] = (unsigned long) _file;

    _file->used = TRUE;
    _file->magic = 1234;

    // debug_print ("socket_gramado: done\n");

// ok.
// Retornamos o fd na lista de arquivos abertos pelo processo.

    return (int) __slot;

fail:
    debug_print ("socket_gramado: [FAIL]\n");
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
    register int i=0;
    int __slot = -1;

    if ( (void*) sock == NULL ){
        debug_print ("socket_inet: sock\n");
        goto fail;
    }
    if (sock->magic!=1234){
        debug_print ("socket_inet: sock validation\n");
        goto fail;
    }
    if (family != AF_INET){
        debug_print ("socket_inet: family\n");
        goto fail;
    }

    sock->addr_in.sin_family      = AF_INET;
    sock->addr_in.sin_port        = 11369;  //??
    sock->addr_in.sin_addr.s_addr = SYS_SOCKET_IP(127,0,0,1);

// Process

    pid_t current_process = (pid_t) get_current_process();
    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        printf ("socket_inet: current_process\n");
        goto fail;
    }

    Process = (void *) processList[current_process];
    if ( (void *) Process == NULL ){
        printf("socket_inet: Process\n");
        goto fail;
    }
    if ( Process->used != TRUE || Process->magic != 1234 ){
        printf("socket_inet: Process validation\n");
        goto fail;
    }

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
    
    __slot=-1;
    //for ( i=3; i< NUMBER_OF_FILES; i++ )
    for ( i=3; i< 31; i++ )
    {
        if ( Process->Objects[i] == 0 )
        { 
            __slot = i; 
            break; 
        }
    };

// Fail
    if ( __slot == -1 ){
        printf ("socket_inet: No free slots\n");
        goto fail;
    }

//
// == Buffer ==========================
//

    char *buff = (char *) kmalloc(BUFSIZ);
    //char *buff = (char *) newPage ();
    if ( (void *) buff == NULL ){
        //Process->Objects[__slot] = (unsigned long) 0;
        debug_print ("socket_inet: [FAIL] Buffer allocation fail\n");
        printf      ("socket_inet: [FAIL] Buffer allocation fail\n");
        goto fail;
    }

//
// File
//

    _file = (void *) kmalloc( sizeof(file) );
    if ( (void *) _file == NULL  ){
        //Process->Objects[__slot] = (unsigned long) 0;
        printf ("socket_inet: _file fail\n");
        goto fail;
    }
// Clear the structure.
    memset( _file, 0, sizeof(struct file_d) );

    _file->pid = (pid_t) current_process;
    _file->uid = (uid_t) current_user;
    _file->gid = (gid_t) current_group;
    _file->____object = ObjectTypeSocket;

// sync

    _file->sync.sender = -1;
    _file->sync.receiver = -1;
    _file->sync.action = ACTION_NULL;
    _file->sync.can_read = TRUE;
    _file->sync.can_write = TRUE;
    _file->sync.can_execute = FALSE;
    _file->sync.can_accept = TRUE;
    _file->sync.can_connect = TRUE;

    _file->sync.block_on_read = FALSE;
    _file->sync.block_on_read_empty = TRUE;

    _file->sync.block_on_write = TRUE;
    _file->sync.block_on_write_full = TRUE;

    _file->sync.lock = FALSE;

// flags 
    _file->_flags = __SWR;
// No name for now.
    _file->_tmpfname = NULL;
    //_file->_tmpfname = "socket";

// Buffer support:

    _file->_base    = buff;
    _file->_p       = buff;
    _file->_lbfsize = BUFSIZ;
// Quanto falta
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

// fd
    _file->_file = __slot;

    _file->used = TRUE;
    _file->magic = 1234;

// Colocando na lista de arquivos abertos no processo.
    Process->Objects[__slot] = (unsigned long) _file;

    //debug_print ("socket_inet: done\n");

// ok
// Retornamos o fd na lista de arquivos abertos pelo processo.

    return (int) __slot;

fail:
    debug_print ("socket_inet: [FAIL]\n");
    refresh_screen();
    return (int) (-1);
}

int socket_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    struct process_d *p;
    file *f;

    debug_print ("socket_ioctl: TODO\n");

    if (fd < 0 || fd >= OPEN_MAX){
        return (int) (-EBADF);
    }

// process
    pid_t current_process = (pid_t) get_current_process();
    p = (void*) processList[current_process];
    if ( (void *) p == NULL ){
        debug_print("socket_ioctl: [FAIL] p\n");
        return -1;
    }

// file

    f = (file *) p->Objects[fd];
    if ( (void *) f == NULL ){
        debug_print("socket_ioctl: [FAIL] f\n");
        return -1;
    }
// #bugbug
// Se eh uma chamada vinda de ring3, entao nao conseguira
// acessar a estrutura ... problemas com registrador de segmentos.
    if (f->used != TRUE || f->magic != 1234 )
    {
        panic("socket_ioctl: validation\n");
    }

// Request

    switch (request){

        // #bugbug
        // Nao conseguimos usar direito os elementos da estrutura
        // Precisamos trabalhar na interrupçao do sistema,
        // na coisa dos segmentos de dados ...
        // Por causa do tipo de segmento, estamos escrevendo 
        // ou lendo no lugar errado.

        case 4000:
            debug_print ("socket_ioctl: [4000]\n");
            printf("socket_ioctl: [4000] fd %d pid %d #debug\n", fd, arg);
            refresh_screen();
            // Is it a valid pid?
            f->sync.sender = (pid_t) arg;
            return 0;
            break;

        case 4001:
            return (int) f->sync.sender;
            break;

        case 4002:
            return (int) f->sync.can_read;
            break;

        case 4003:
            return (int) f->sync.can_write;
            break;

        case 4004:
            return (int) f->sync.can_execute;
            break;

        // ...

        default:
            return (int) (-EINVAL);
            break;
    };

    return -1;
}

int socket_read ( unsigned int fd, char *buf, int count )
{
    debug_print ("socket_read:[TODO]\n");
    return -1;
}

int socket_write ( unsigned int fd, char *buf, int count )
{
    debug_print ("socket_write:[TODO]\n");
    return -1;
}

pid_t socket_get_gramado_port (int port)
{
//port
    if ( port<0 || port >31){
        debug_print ("socket_set_gramado_port: port fail\n");
        return (pid_t) -1;
    }

    return (pid_t) gramado_ports[port];
}

// Conjunto especiais de portas.
// Usados apenas na famíla AF_GRAMADO.
int socket_set_gramado_port (int port, pid_t pid)
{
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

    gramado_ports[port] = (pid_t) pid;

    return 0;
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
    register int i=0;
    int __slot = -1;

//#todo
//check sock arg.

    debug_print ("socket_unix:\n");

    if ( (void*) sock == NULL ){
        debug_print ("socket_unix: sock\n");
        goto fail;
    }
    if (sock->magic!=1234){
        debug_print ("socket_unix: sock validation\n");
        goto fail;
    }
    if (family != AF_UNIX){
        debug_print ("socket_unix: family\n");
        goto fail;
    }

    sock->addr.sa_family  = family;
    sock->addr.sa_data[0] = 'x'; 
    sock->addr.sa_data[1] = 'x';

// Process

    pid_t current_process = (pid_t) get_current_process();
    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        printf ("socket_unix: current_process\n");
        goto fail;
    }

    Process = (void *) processList[current_process];
    if ( (void *) Process == NULL ){
        printf("socket_unix: Process\n");
        goto fail;

    }
    if ( Process->used != TRUE || Process->magic != 1234 ){
        printf("socket_unix: Process validation\n");
        goto fail;
    }

// #todo
// Temos que criar uma rotina que procure slots em Process->Streams[]
// e colocarmos em process.c
// essa é afunção que estamos criando.
// process_find_empty_stream_slot ( struct process_d *process );

// #improvisando
// 0, 1, 2 são reservados para o fluxo padrão.
// Como ainda não temos rotinas par ao fluxo padrão,
// pode ser que peguemos os índices reservados.
// Para evitar, começaremos depois deles.

    __slot = -1;
    // Reserva um slot.
    //for ( i=3; i< NUMBER_OF_FILES; i++ )
    for ( i=3; i< 31; i++ )
    {
        if ( Process->Objects[i] == 0 )
        { 
            __slot = i; 
            break; 
        }
    };

// Check slot validation. 
    if ( __slot == -1 ){
        printf ("socket_unix: No free slots\n");
        goto fail;
    }

//
// == Buffer ================
//

    char *buff = (char *) kmalloc(BUFSIZ);
    //char *buff = (char *) newPage ();
    if ( (void *) buff == NULL ){
        //Process->Objects[__slot] = (unsigned long) 0;
        debug_print ("socket_unix: [FAIL] Buffer allocation fail\n");
        printf      ("socket_unix: [FAIL] Buffer allocation fail\n");
        goto fail;
    }

//
// File
//

    _file = (void *) kmalloc( sizeof(file) );
    if ( (void *) _file == NULL  ){
        //Process->Objects[__slot] = (unsigned long) 0;
        printf ("socket_unix: _file fail\n");
        goto fail;
    }
    memset( _file, 0, sizeof(struct file_d) );

// #todo: Podemos adiar isso para o fim da rotina.
    _file->used = TRUE;
    _file->magic = 1234;

    _file->pid = (pid_t) current_process;
    _file->uid = (uid_t) current_user;
    _file->gid = (gid_t) current_group;
    _file->____object = ObjectTypeSocket;

// sync

    _file->sync.sender = -1;
    _file->sync.receiver = -1;
    _file->sync.action = ACTION_NULL;
    _file->sync.can_read = TRUE;
    _file->sync.can_write = TRUE;
    _file->sync.can_execute = FALSE;
    _file->sync.can_accept = TRUE;
    _file->sync.can_connect = TRUE;

    _file->sync.block_on_read = FALSE;
    _file->sync.block_on_read_empty = TRUE;

    _file->sync.block_on_write = TRUE;
    _file->sync.block_on_write_full = TRUE;
        
    _file->sync.lock = FALSE;

    _file->_flags = __SWR;

// No name for now.
// #bugbug: 
// unix sockets has names.
// it's like a normal fs pathname.

    _file->_tmpfname = NULL;
    //_file->_tmpfname = "/tmp/socketXXX";    

// Buffer

    _file->_base = buff;
    _file->_p    = buff;
    _file->_lbfsize = BUFSIZ; 
// Quanto falta
    _file->_cnt = _file->_lbfsize;
    _file->_r = 0;
    _file->_w = 0;
    _file->socket_buffer_full = 0;  

    _file->socket = sock;

// O arquivo do soquete, o buffer?
    sock->private_file = (file *) _file; 

// Salvamos o ponteira para estrutura de soquete
// na estrutura de processo do processo atual.
    Process->priv = (void *) sock;

// fd.
    _file->_file = __slot;

//Colocando na lista de arquivos abertos no processo.
    Process->Objects[__slot] = (unsigned long) _file;

    //debug_print ("socket_unix: done\n");

    //ok.
    // Retornamos o fd na lista de arquivos abertos pelo processo.
    return (int) __slot;

fail:
    debug_print ("socket_unix: fail\n");
    refresh_screen();
    return (int) (-1);  
}

/*
 * sys_accept: 
 *     This is a work in progress.
 */
// accept() is used on the server side. 
// It accepts a received incoming attempt to create 
// a new TCP connection from the remote client, 
// and creates a new socket associated with 
// the socket address pair of this connection.
// #todo
// Pega um socket da lista de conexoes incompletas.
// Nosso maior objetivo aqui eh retornar o fd arquivo 
// de socket do cliente.
// #todo
// We need to create a new socket. Only this way the process
// will have a new file in p->Objects[].
// == todo =========================
// #solution
// We create a new socket and connect this 
// new socket with the client.
// This way we can return the fd of the socket.
// #obs:
// When write() writes in the new socket, the data
// will be copied to the client socket. But it can be only an option.
/*
 * From Linux 0.98.1:
 * For accept, 
 * we attempt to create a new socket, 
 * set up the link with the client, 
 * wake up the client, then 
 * return the new connected fd.
 */
// #importante: Retornando o fd do cliente.
// Dessa forma o servido pode escrever nele
// e o cliente poderá ler.

int 
sys_accept (
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{
// Server process.
    struct process_d *sProcess;
// Server socket and client socket.
    struct socket_d *sSocket;
    struct socket_d *cSocket;
// Files for the server and client sockets.
    file *sFile;
    file *cFile;   //#todo
// File descriptors for the server and client sockets.
    int fdServer = -1;
    int fdClient = -1;
// Iterator for the pending connections queue.
    register int i=0;
    int Verbose=FALSE;

    // #debug
    // debug_print ("sys_accept:\n");

    pid_t current_process = (pid_t) get_current_process();

//
// fd Server 
//

// #todo
// O argumento dá o descritor para o socket do servidor.
// A função accept seleciona um dos sockets da lista
// de conexões pendentes criadas por listen() e conecta
// com o socket do servidor.
// Ao fim devemos retornar o descritor do socket selecionado
// na lista de conexões pendentes.

    fdServer = sockfd;
    if ( fdServer < 0 || fdServer >= OPEN_MAX ){
        debug_print ("sys_accept: [FAIL] fdServer\n");
        return (int) (-EINVAL);
    }

// Check addr structure.
// #bugbug: 
// Ainda não sabemos qual é a estrutura de endereços usada.
// #bugbug: 
// Ainda não estamos usando isso.

    if ( (void *) addr == NULL ){
        debug_print ("sys_accept: [FAIL] addr\n");
        return (int) (-EINVAL);
    }

// Current process. (The server)
// The accept() was called by the server.

    if ( current_process < 0  || current_process >= PROCESS_COUNT_MAX ){
        debug_print ("sys_accept: [FAIL] current_process\n");
        printf      ("sys_accept: [FAIL] current_process\n");
        goto fail;
    }
// Server process
    sProcess = (struct process_d *) processList[current_process];
    if ( (void *) sProcess == NULL ){
        debug_print ("sys_accept: [FAIL] sProcess\n");
        printf      ("sys_accept: [FAIL] sProcess\n");
        goto fail;
    }
    if ( sProcess->used != TRUE || sProcess->magic != 1234 ){
        debug_print ("sys_accept: [FAIL] sProcess validation\n");
        printf      ("sys_accept: [FAIL] sProcess validation\n");
        goto fail;
    }

// file
// O objeto que se refere ao socket do servidor.
// The socket is a file and belongs to the process.

    sFile = (file *) sProcess->Objects[fdServer];
    if ( (void *) sFile == NULL ){
        debug_print ("sys_accept: sFile fail\n");
        printf      ("sys_accept: sFile fail\n");
        goto fail;
    }
    if ( sFile->used != TRUE || sFile->magic != 1234 ){
        debug_print ("sys_accept: [FAIL] sFile validation\n");
        printf      ("sys_accept: [FAIL] sFile validation\n");
        goto fail;
    }
// Is this file a socket?
    if ( is_socket(sFile) != TRUE ){
        debug_print ("sys_accept: sFile is not a socket object\n");
             printf ("sys_accept: sFile is not a socket object\n");
        goto fail;
    }
    if (sFile->sync.can_accept != TRUE){
        debug_print ("sys_accept: sFile can NOT accept connections\n");
             printf ("sys_accept: sFile can NOT accept connections\n");
        goto fail;
    }

// Get the server's private socket.
// And check its validation.

    sSocket = (struct socket_d *) sFile->socket;
    if ( (void *) sSocket == NULL ){
        debug_print ("sys_accept: [FAIL] sSocket\n");
        printf      ("sys_accept: [FAIL] sSocket\n");
        goto fail;
    }
    if ( sSocket->used != TRUE || sSocket->magic != 1234 ){
        debug_print ("sys_accept: [FAIL] sSocket validation\n");
        printf      ("sys_accept: [FAIL] sSocket validation\n");
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

// Socket ok!
// #todo
// Essa funcao nos enviou o fd do socket do servidor.
// Agora vamos olhar na lista de conexoes existentes nesse
// socket e pegarmos um dos fd da lista. Em ordem round robing.
// Esse fd será o socket do cliente.

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
    
    /*
    if ( sSocket->state == SS_CONNECTED )
    {
        debug_print ("sys_accept: Already connected!\n");
        //printf      ("sys_accept: Already connected!\n");
        //refresh_screen();
        //return -1;
        return (int) fdServer;
    }
    */


// #todo
// Na verdade precisamos pegar um da fila.

// #test
// Se a conexão do socket do servidor está pendente.
// Pega um socket da lista de conexoes pendentes.
// #bugbug
// Devemos retornar o descritor do socket cliente.
// #todo: Para devolver um descritor para o servidor,
// então o socket do cliente deve estar na lista de
// arquivos abertos pelo servidor.

// #bugbug
// A estado de SS_CONNECTING foi atribuido pelo connect().
// Se connect() preconectar os sockets, isso será ruim,
// pois poderíamos transmitir dados mesmo antes do accept()
// selecionar um da fila de conexoes pendentes. 
// ele tambem esta em um dos slots e no slot 31.

// Se o socket ja está conectado ou 
// esta esperando para se conectar.

    if ( sSocket->state == SS_CONNECTING || 
         sSocket->state == SS_CONNECTED )
    {
        //debug_print ("sys_accept: CONNECTING !\n");

        //Server socket. Pre-connect.
        //precisamos mudar no caso de erro no cliente.
        sSocket->state = SS_CONNECTED;

        // Se existe outro socket linkado ao socket do servidor.
        // #todo
        // Nesse momento pegamos o primeiro da lista de conexões pendentes.
        // Mas desejamos ter uma lista de conexões pendentes e 
        // nesse momento pegaremos um da lista seguindo uma ordem.

        // circula
        
        sSocket->backlog_head++;
        if ( sSocket->backlog_head >= sSocket->backlog_max ){
            sSocket->backlog_head=0;
        }
        i = sSocket->backlog_head;
        
        if ( i<0 || i >= sSocket->backlog_max ){
            panic("sys_accept: i is out of limits.\n");
        }

        // Probe for a valid pointer.
        // Ok 
        // Vamos pegar o ponteiro para estrutura de socket do cliente.
        // Isso foi colocado aqui na estrutura de socket do servidor
        // pela função connect();
        while ( i <= sSocket->backlog_max )
        {
            cSocket = 
                (struct socket_d *) sSocket->pending_connections[i];
            if ( (void*) cSocket != NULL ){
                break;
            }
            // next
            i++;
        };

        // Not valid Client socket
        if ( (void*) cSocket == NULL ){
            debug_print ("sys_accept: [FAIL] cSocket\n");
            sSocket->state = SS_CONNECTING;  //anula.
            goto fail;
        }

        // Valid Client socket
        // Vamos nos conectar a ele.
        if ( (void *) cSocket != NULL )
        {
            // check validation
            if( cSocket->used != TRUE || cSocket->magic != 1234 )
            {
                debug_print ("sys_accept: [FAIL] cSocket validation\n");
                sSocket->state = SS_CONNECTING;  //anula.
                goto fail;
            }

            // Na verdade o magic indica que eh 
            // uma conexao pendente.
            if ( cSocket->magic_string[0] == 'C')
            {
                //debug_print("MAGIC C\n");
                //printf ("magic: %s\m",cSocket->magic_string);
            }

            //ok: usar isso só para debug
            //debug_print ("sys_accept: done\n");

            cSocket->state = SS_CONNECTED;
            
            // Pegando o ponteiro da estrutura de arquivo 
            // associada ao socket do cliente.
            cFile = (file *) cSocket->private_file;
            // Salvando o ponteiro de estrutura de arquivo 
            // no slot prealocado na inicializacao.
            // Essa é a estrutura de processo do servidor.
            // Essa é a lista de arquivos abertos pelo processo.
            //sProcess->Objects[ sProcess->_client_sock_fd ] = cFile;
            sProcess->Objects[31] = (unsigned long) cFile;  //last
            cFile->_file = 31;
            
            //debug_print ("sys_accept: done\n");

            // #importante: Retornando o fd do cliente.
            // Dessa forma o servido pode escrever nele
            // e o cliente poderá ler.

            if ( Verbose == TRUE ){
                printf("sys_accept: Server's pid {%d}\n",current_process);
                printf("sys_accept: Server's socket fd {%d}\n",sockfd);
                printf("sys_accept: Breakpoint\n");
                refresh_screen();
                while(1){}
            }

            return (int) cFile->_file;  // 31 
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
    //refresh_screen();
    if( Verbose == TRUE ){
        refresh_screen();
    }
    return -1;
}

/*
 * sys_bind:
 *    When a socket is created with socket(), it exists in a 
 *    name space (address family) but has no address assigned to it. 
 *    bind() assigns the address specified by addr to the socket 
 *    referred to by the file descriptor sockfd.
 */
// bind() is typically used on the server side, and 
// associates a socket with a socket address structure, 
// i.e. a specified local IP address and a port number.
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
    register int i=0;
    int Verbose=FALSE;

    // #debug
    //debug_print ("sys_bind:\n");

    pid_t current_process = (pid_t) get_current_process();

    // #debug
    if (Verbose==TRUE){
        printf("sys_bind: PID %d | fd %d | \n",
            current_process, sockfd );
    }

// fd
    if ( sockfd < 0 || sockfd >= OPEN_MAX ){
        debug_print ("sys_bind: sockfd fail\n");
        printf      ("sys_bind: sockfd fail\n");
        return (int) (-EINVAL);
    }

// Check addr structure.
    if ( (void *) addr == NULL ){
        debug_print ("sys_bind: addr fail\n");
        printf      ("sys_bind: addr fail\n");
        goto fail;
    }

    if (current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        printf("sys_bind: current_process\n");
        goto fail;
    }

    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL ){
        debug_print ("sys_bind: p fail\n");
        printf      ("sys_bind: p fail\n");
        goto fail;
    }

// file
// O objeto do tipo socket.

    f = (file *) p->Objects[sockfd];
    if ( (void *) f == NULL ){
        debug_print ("sys_bind: f fail\n");
        printf      ("sys_bind: f fail\n");
        goto fail;
    }

    if ( is_socket(f) != TRUE ){
        debug_print ("sys_bind: f is not a socket object\n");
        printf      ("sys_bind: f is not a socket object\n");
        goto fail;
    }

// socket
// A estrutura de socket associada ao objeto do tipo socket.
    s = (struct socket_d *) f->socket;
    if ( (void *) s == NULL ){
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
    if (s->addr.sa_family == AF_GRAMADO)
    {
        debug_print ("sys_bind: [AF_GRAMADO] Binding the name to the socket.\n");
        // Always 14.
        for (i=0; i<14; i++){
            s->addr.sa_data[i] = addr->sa_data[i];
        }; 
        // #debug
        if (Verbose==TRUE){
            printf ("sys_bind: process %d | family %d | len %d\n", 
                current_process, addr->sa_family, addrlen  );
        }
        debug_print ("sys_bind: bind ok\n");
        return 0;
    }
//--

//++
// AF_UNIX ou AF_LOCAL
// See: http://man7.org/linux/man-pages/man7/unix.7.html
    if (s->addr.sa_family == AF_UNIX)
    {
        debug_print ("sys_bind: AF_UNIX not supported yet\n");
        printf      ("sys_bind: AF_UNIX not supported yet\n");
        //for (i=0; i<14; i++){ s->addr.sa_data[i] = addr->sa_data[i]; }; 
        return -1;
    }
//--    


//++
// AF_INET
    if (s->addr.sa_family == AF_INET)
    {
        debug_print ("sys_bind: AF_INET not supported yet\n");
        printf      ("sys_bind: AF_INET not supported yet\n");
        //for (i=0; i<14; i++){ s->addr.sa_data[i] = addr->sa_data[i]; }; 
        return -1;    
    } 
//--

// #fail
// A família é de um tipo não suportado.

    debug_print ("sys_bind: [FAIL] family not valid\n");
    printf      ("sys_bind: [FAIL] family not valid\n");

// fail

fail:
    debug_print ("sys_bind: [FAIL] Something is wrong!\n");
    printf      ("sys_bind: [FAIL] Something is wrong!\n");
    refresh_screen();
    return (int) (-1);
}   


/*
 * sys_connect:
 *     Connecting to a server given an address.
 */
// connect() is used on the client side, and 
// assigns a free local port number to a socket. 
// In case of a TCP socket, it causes an attempt 
// to establish a new TCP connection.
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
/*
 The backlog argument defines the maximum length to which the queue of
 pending connections for sockfd may grow.  If a connection request
 arrives when the queue is full, the client may receive an error with
 an indication of ECONNREFUSED or, if the underlying protocol supports
 retransmission, the request may be ignored so that a later reattempt
 at connection succeed.
*/
// IN: client fd, address, address len
// OUT: 0=ok <0=fail

int 
sys_connect ( 
    int sockfd, 
    const struct sockaddr *addr,
    socklen_t addrlen )
{

// #todo
// O socket do cliente precisa de um arquivo aberto no
// processo alvo.
// #bugbug:
// Se nao fecharmos o arquivo ao fim da conexao, entao
// a lista de arquivos abertos se esgotara rapidamente.

// Client process and server process.
    struct process_d *cProcess;
    struct process_d *sProcess;
    pid_t target_pid = (-1);  //fail
// Client socket and server socket.
    struct socket_d *client_socket;
    struct socket_d *server_socket;
    int client_socket_fd = -1;
// File.
    struct file_d *f;
// #importante
// No caso de endereços no estilo inet
// vamos precisar de outra estrututura.
    struct sockaddr_in *addr_in;
    int Verbose=FALSE;

    pid_t current_process = (pid_t) get_current_process();

    if (Verbose==TRUE){
        printf ("sys_connect: Client's pid {%d}\n", current_process );
        printf ("sys_connect: Client's socket id {%d}\n", sockfd );
    }

// Client fd.
// client_socket_fd é um soquete de quem quer se conectar.
// O addr indica o alvo.
    client_socket_fd = sockfd;
    if ( client_socket_fd < 0 || client_socket_fd >= OPEN_MAX ){
        debug_print ("sys_connect: client_socket_fd\n");
        printf      ("sys_connect: client_socket_fd\n");
        refresh_screen();
        return (int) (-EINVAL);
    }

// addr
// Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL ){
        printf ("sys_connect: addr\n");
        refresh_screen();
        return (int) (-EINVAL);
    }
// #todo: type.
// da um problema na compilação.
    //addr_in = (?) addr;
    addr_in = addr;

//  ==============

// Getting the target PID.
// #todo:
// Devemos obter o número do processo alvo dado um endereço.
// O tipo de endereço depende do tipo de domínio (família).

// Tente inet, ao menos que mudemos de planos por 
// encontrarmos af_gramado, af_unix ou af_local.

    int ____in = TRUE;

// #importante
// opções de domínio se o endereço é no estilo unix. 
// >>> sockaddr

// Vamos pegar o pid do processo associado a determinada porta.
// Apenas as famílias AF_GRAMADO e AF_UNIX.

    switch (addr->sa_family){

    // AF_GRAMADO = 8000
    // Vamos obter o número do processo alvo dado o endereço.
    // 32 ports only.

    case AF_GRAMADO:
    // Trabalhando com string.

        debug_print ("sys_connect: AF_GRAMADO ok\n");

        // ws: Window server
        if ( addr->sa_data[0] == 'w' && addr->sa_data[1] == 's' ){
            target_pid = (pid_t) gramado_ports[GRAMADO_WS_PORT]; 
        }
        // ns: Network server
        if ( addr->sa_data[0] == 'n' && addr->sa_data[1] == 's' ){ 
            target_pid = (pid_t) gramado_ports[GRAMADO_NS_PORT]; 
        }
        // fs: File system server
        if ( addr->sa_data[0] == 'f' && addr->sa_data[1] == 's' ){
            target_pid = (pid_t) gramado_ports[GRAMADO_FS_PORT]; 
        }
        // ...
        if ( target_pid<0 || target_pid >= PROCESS_COUNT_MAX ){
            printf ("sys_connect: AF_GRAMADO target_pid\n");
            goto fail;
        }
        if (Verbose==TRUE){
            printf ("sys_connect: target pid %d \n", target_pid);
        }
        // Logo abaixo, não tente inet, pois somos AF_GRAMADO.
        ____in = FALSE;
        break;

    //case AF_LOCAL:
    case AF_UNIX:
    // Trabalhando com pathname.

        // #todo
        // Podemos usar isso no caso do  window server.
        // Pois se trata de uma conexão local.
        // Essa conexão local usa endereços no sistema de arquivos.
        // #todo: Implementar isso.
        debug_print ("sys_connect: AF_UNIX\n");
        printf      ("sys_connect: AF_UNIX\n");
        //target_pid = -1;
        // não tente inet, somos af_unix
        ____in = FALSE;
        goto fail;
        break;
    };


// Tentaremos com outro formato de endereço, o sockaddr_in.
// Agora trabalharemos com IP e PORTA. Não mais com string
// ou pathname.
// Vamos pegar o pid do processo associado a determinada porta.
// Para a família AF_INET.

    if (____in == TRUE){

    // Opções de domínio se o endereço é no estilo internet.
    switch (addr_in->sin_family){

    case AF_INET:
    // Trabalhando com ip e porta.
    // Estamos usando inet em conexão local.
    // Então precisamos usar localhost como ip.

        debug_print ("sys_connect: AF_INET\n");
        //#debug
        //printf("sys_connect: AF_INET port {%d}\n", addr_in->sin_port);
 
        // WS - 4040
        // Se a porta for , então usaremos o pid do WS.
        if (addr_in->sin_port == PORTS_WS)
        {
            target_pid = (pid_t) gramado_ports[GRAMADO_WS_PORT];
            if (Verbose==TRUE){
                printf("sys_connect: [AF_INET] Connecting to the Window Server\n");
                printf("sys_connect: IP {%x}\n", addr_in->sin_addr.s_addr );
                printf("sys_connect: PORT {%d}\n", addr_in->sin_port);
                refresh_screen();
            }
            break;
        }

        // NS - 4041
        // Se a porta for , então usaremos o pid do NS.
        if (addr_in->sin_port == PORTS_NS)
        {
            target_pid = (pid_t) gramado_ports[GRAMADO_NS_PORT]; 
            if (Verbose==TRUE){
                printf("sys_connect: [AF_INET] Connecting to the Network Server\n");
                printf("sys_connect: IP {%x}\n", addr_in->sin_addr.s_addr );
                printf("sys_connect: PORT {%d}\n", addr_in->sin_port);
                refresh_screen();
                }
            break;
        }

        // PORTS_FS #todo

        // 21 - FTP
        if (addr_in->sin_port == 21){
            printf("sys_connect: [21] FTP #todo\n");
            goto fail;
        }

        // 23 - Telnet
        if (addr_in->sin_port == 23){
            printf("sys_connect: [23] Telnet #todo\n");
            goto fail;
        }

        // 67 - DHCP
        if (addr_in->sin_port == 67){
            printf("sys_connect: [67] DHCP #todo\n");
            goto fail;
        }

        // 80 - HTTP
        if (addr_in->sin_port == 80){
            printf("sys_connect: [80] HTTP #todo\n");
            goto fail;
        }

        // 443 - HTTPS 
        if (addr_in->sin_port == 443){
            printf("sys_connect: [443] HTTPS #todo\n");
            goto fail;
        }

        // #debug
        printf("sys_connect: [FAIL] Port not valid {%d}\n",
            addr_in->sin_port);

        goto fail;
        break;

        //...

    default:
        debug_print("sys_connect: domain not supported\n");
        printf("sys_connect: [FAIL] Family not supported {%d}\n",
            addr_in->sin_family);
        goto fail;
        break;

    };  // switch
    }   // if

// ====================================================================
// Check
// Have a valid target_pid ?

//__go:

//
// == Client process =============================
//

// Vamos obter o arquivo do tipo soquete
// que pertence ao sender.

    if (current_process<0 || current_process >= PROCESS_COUNT_MAX ){
        printf ("sys_connect: current_process\n");
        goto fail;
    }

// sender's process structure.
    cProcess = (struct process_d *) processList[current_process];
    if ( (void *) cProcess == NULL ){
        debug_print ("sys_connect: cProcess fail\n");
        printf      ("sys_connect: cProcess fail\n");
        goto fail;
    }

// #todo
// Check structure validation
    // if (cProcess->magic ...

// The client's socket file.
// #bugbug
// Estamos pegando o arquivo de socket do cliente
// Então estamos presumindo que é uma conexão local.
// Se o servidor fechar esse arquivo, então
// o cliente será incapaz de enviar mensagens?
// Por isso no momento do accept devemos
// criar um arquivo para o cliente. Que poderá ser fechado
// pelo sevidor para encessar a conexão ... até que
// o cliente se conecte novamente.
// #importante: Mas para isso o cliente precisa
// possuir um arquivo de socket ainda válido.
// O servidor não pode fechar o arquivo de socket do cliente remoto.
// E também não devemos permitir que isso aconteça na conexão local.

    f = (file *) cProcess->Objects[client_socket_fd];
    if ( (void *) f == NULL ){
        printf ("sys_connect: [FAIL] f. The client's socket\n");
        goto fail;
    }

// Is it a socket??

    int __is = -1;
    __is = is_socket((file *)f);
    if (__is != TRUE){
        printf ("sys_connect: [FAIL] f is not a socket\n");
        goto fail;
    }

// This file doesn't accept connections.
// #todo: 
// This way we can reject connections before the server binds
// with an address.

    if (f->sync.can_connect != TRUE){
        printf ("sys_connect: [PERMISSION FAIL] Client doesn't accept connections.\n");
        goto fail;
    }

//
// Client socket structure
//

// Socket structure in the sender's file.
// Pega a estrutura de socket associada ao arquivo.

    client_socket = (struct socket_d *) f->socket;
    if ( (void *) client_socket == NULL ){
        printf ("sys_connect: [FAIL] client_socket\n");
        goto fail;
    }

// The client socket needs to be unconnected.
// #perigo
// Só podemos conectar se o socket estiver nesse estado.
// #todo
// Caso fechar conexão podemos perder esse estado 
// naõ conseguirmos mais conectar.

    if (client_socket->state != SS_UNCONNECTED) {
        printf ("sys_connect: [FAIL] client socket is not SS_UNCONNECTED\n");
        goto fail;
    }

//
// == Server process ===============================
//

// #todo
// O arquivo de socket do cliente 
// precisa ter um fd no processo servidor.

// target pid.
// O pid do processo servidor.
// Pegamos o target_pid logo acima na porta solicitada.

    if (target_pid<0 || target_pid >= PROCESS_COUNT_MAX){
        debug_print ("sys_connect: target_pid\n");
        printf      ("sys_connect: target_pid\n");
        goto fail;
    }

// The server's process structure.
// O processo cliente chamou essa função e
// então pegaremos agora o processo alvo,
// que é um servidor.

    sProcess = (struct process_d *) processList[target_pid];
    if ( (void *) sProcess == NULL ){
        debug_print ("sys_connect: sProcess fail\n");
        printf      ("sys_connect: sProcess fail\n");
        goto fail;
    }

// #todo
// Checar a validade da estrutura de processo.
    // if ( sProcess->magic != ...

// Procurando um slot livre na lista de objetos abertos
// presente na estrutura do processo servidor.

    int __slot=-1;  //fail
    register int i=0;
    for (i=3; i<31; i++){
         if (sProcess->Objects[i] == 0){
             __slot = i;
             goto __OK_new_slot;
         }
    };

// #fail: 
// No more slots.
    panic ("sys_connect: [FIXME] We need a slot in the server\n");

// ok
__OK_new_slot:

    if (__slot == -1){
        printf("sys_connect: no empty slor\n");
        goto fail;
    }

// Esse é o socket do processo servidor.
// Sim, porque é o cliente que está tentando se conectar.
// Dessa forma o alvo é o servidor.

    server_socket = (struct socket_d *) sProcess->priv;
    if ( (void *) server_socket == NULL ){
        printf ("sys_connect: [FAIL] server_socket\n");
        goto fail;
    }

// Salvando o fd do socket do cliente.
    server_socket->clientfd_on_server = __slot;
    client_socket->clientfd_on_server = __slot;

// #todo
// Temos que rever as coisas por aqui. kkk
// incluimos como objeto do servidor o ponteiro para 
// o arquivo que representa o socket do cliente.
// O arquivo de socket do cliente agora tem um fd
// no processo servidor.
// Nossa intenção aqui é usar um dos slots livres
// encontrado em p->Objects[], mas por enquanto estamos usando 
// apenas o slot número 31.

    //sProcess->Objects[__slot] = (unsigned long) f;  // no que encontramos
    sProcess->Objects[31] = (unsigned long) f;  // no 31.

//
// == Connecting! ======================================
//

// #bugbug
// connect() eh chamado somente uma vez pelo cliente.
// A conexao deve ficar pendente numa lista e o accept
// seleciona uma delas.
// #test: 
// Pra começar, vamos deixar apenas uma pendente
// e o accept() selecionara ela.
// #todo
// Temos que colocar os pedidos de conexão em uma fila.
// O tamanho dessa fila foi determinado pelo servidor
// com a chamada listen(). Mas podemos ter um tamanho padrão.
// Talvez tamanho 1 para começar.
// Link:
// Conectando o socket do processo alvo ao ponto de
// conexão do processo cliente.
// Conectando o socket do cliente ao ponto de conecção do
// processo servidor.
// Flags:
// State:
// Acionando as flags que indicam a conecção.
// Nesse momento poderíamos usar a flag SS_CONNECTING
// e a rotina accept() mudaria para SS_CONNECTED. 
// #bugbug
// Nao podemos mudar o estado do servidor,
// estamos apenas entrando na fila e implorando para nos conectarmos.
// Quem realizara a conexão sera o accept(), 
// pegando o cliente da fila de conexões pendentes.

// Linking:
// Connecting
    client_socket->conn = server_socket;
    server_socket->conn = client_socket;
// Flags:
// State
    client_socket->state = SS_CONNECTING;
    server_socket->state = SS_CONNECTING;
// Magic signature
    client_socket->magic_string[0] = 'C';
    client_socket->magic_string[1] = 0; 

// #todo
// Precisamos de uma lista de conexões pendentes.
// O cliente invocou a conexão apenas uma vez
// e precisa usar o servidor varias vezes
// #obs: 
// Isso funcionou. Vamos tentar com lista.
// #obs: 
// Algumas implementacões usam lista encadeada de conexões pendentes. 
// 'server_socket->iconn'
// #bugbug: 
// Essa lista fica na estrutura de socket so servidor, 
// dessa forma o servidor pode ter mais de uma socket?

    //server_socket->connections_count++;
    //if(server_socket->connections_count >= server_socket->backlog_max )
    //    return ECONNREFUSED;

// circula

    int BacklogTail = 0;

    server_socket->backlog_tail++;
    if ( server_socket->backlog_tail >= server_socket->backlog_max ){
        server_socket->backlog_tail = 0;
    }
    BacklogTail = server_socket->backlog_tail;

// coloca na fila.
// Coloca o ponteiro para estrutura de socket
// na fila de conexões pendentes na estrutura do servidor.
// Isso será usado pelo accept() para encontrar
// a estrutura do socket do cliente.
    server_socket->pending_connections[BacklogTail] = 
        (unsigned long) client_socket;

// Em que posiçao estamos na fila.
    client_socket->client_backlog_pos = BacklogTail;

// #
// O cliente está esperando que sua conexão seja aceita pelo servidor.

    // #debug
    //debug_print("sys_connect: Pending connection\n");

    // #debug
    //if (Verbose==TRUE){
    //printf     ("sys_connect: Pending connection\n");
    //refresh_screen();
    //}

    // #debug 
    // #breakpoint
    if (Verbose==TRUE){
        printf("sys_connect: Breakpoint :)\n");
        refresh_screen();
        while(1){}
    }

//ok.
    return 0;

fail:
    debug_print("sys_connect: Fail\n");
    printf     ("sys_connect: Fail\n");
    refresh_screen();  // #bugbug: Slow!
    return -1;
}


int 
sys_getsockname ( 
    int sockfd, 
    struct sockaddr *addr, 
    socklen_t *addrlen )
{
// Process, file and socket.
    struct process_d  *p;
    struct file_d     *f;
    struct socket_d   *s;

    pid_t current_process = (pid_t) get_current_process();

    if ( sockfd < 0 || sockfd >= OPEN_MAX )
    {
        printf ("sys_getsockname: [FAIL ]sockfd \n");
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

// addr
// Usando a estrutura que nos foi passada.
    if ( (void *) addr == NULL ){
        printf ("sys_getsockname: addr fail\n");
        refresh_screen();
        return -1;
    }

// Everything is ok.
// So now we need to include the 'name' into the socket structure
// respecting the socket's family.
    register int n = 0;
    
    if (s->addr.sa_family == AF_GRAMADO)
    {
        // Binding the name to the socket.
        printf ("sys_getsockname: Getting the name and the size\n");
        addrlen[0] = n;
        // Always 14.
        for (n=0; n<14; n++){
            addr->sa_data[n] = s->addr.sa_data[n];
        };
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
 * sys_listen:
 *     É usado pra dizer que o servidor esta 
 * pronto para receber conecxões e 
 * a quantidade de clientes que podem ser conectados.
 */
// See:
// https://man7.org/linux/man-pages/man2/listen.2.html
/*
 The backlog argument defines the maximum length to which the queue of
 pending connections for sockfd may grow.  If a connection request
 arrives when the queue is full, the client may receive an error with
 an indication of ECONNREFUSED or, if the underlying protocol supports
 retransmission, the request may be ignored so that a later reattempt
 at connection succeed.
*/
// listen() is used on the server side, and 
// causes a bound TCP socket to enter listening state.
// IN:
// sockfd  = The fd of the server's socket.
// backlog = The server indicates the 'size of the list'.

int sys_listen (int sockfd, int backlog) 
{
    struct process_d  *p;
    file *f;
    struct socket_d  *s;
    int Backlog=0;

    pid_t current_process = (pid_t) get_current_process();

// #debug
    //debug_print ("sys_listen: [TODO]\n");
    //printf      ("sys_listen: [TODO] fd=%d backlog=%d\n",
        //sockfd, backlog);

// The fd of the server's socket.
    if ( sockfd < 0 || sockfd >= OPEN_MAX ){
        debug_print ("sys_listen: sockfd\n");
        printf      ("sys_listen: sockfd\n");
        return (int) (-EINVAL);
    }

// backlog:
// The server tell us the the 'size of the list'.
// Wrong n. Ajusting to default.
// It can't be bigger than the size of the array.
// #todo: Use SOCKET_MAX_PENDING_CONNECTIONS
    Backlog = backlog;

    if ( Backlog <= 0 ) { Backlog=1; }
    if ( Backlog >= 32 ){ Backlog=31; }

// We need to get the socket structure in the process structure.
// We need to clean the list. Not here. when creating the socket.

/*
    //int i=0;
    //for(i=0; i<32; i++) { s->pending_connections[i] = 0;};
    // Updating the list support.
    //s->backlog_max = backlog;  //max
    //s->backlog_pos = 0;        //current 
 */

// ==============================================

    if (current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        printf ("sys_listen: current_process\n");
        goto fail;
    }

// process
    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL ){
        debug_print ("sys_listen: p fail\n");
        printf      ("sys_listen: p fail\n");
        goto fail;
    }

// file 
// sender's file
// Objeto do tipo socket.
    f = (file *) p->Objects[sockfd];
    if ( (void *) f == NULL ){
        debug_print ("sys_listen: f fail\n");
        printf      ("sys_listen: f fail\n");
        goto fail;
    }

// Is it a socket object?
    int IsSocket = -1;
    IsSocket = (int) is_socket((file *)f);
    if(IsSocket != TRUE){
        debug_print ("sys_listen: f is not a socket\n");
        printf      ("sys_listen: f is not a socket\n");
        goto fail;
    }

// This is right place for doing this.

    //f->sync.can_accept = TRUE;

// Socket structure.
// Pega a estrutura de socket associada ao arquivo.
// socket structure in the senders file.

    //s = (struct socket_d *) p->priv; 
    s = (struct socket_d *) f->socket;
    if ( (void *) s == NULL ){
        debug_print ("sys_listen: s fail\n");
        printf      ("sys_listen: s fail\n");
        goto fail;
    }

    if ( f->socket != p->priv ){
        panic("sys_listen: [TEST] f->socket != p->priv\n");
    }

// Updating the socket structure.
    s->backlog_max = Backlog;
// This server is accepting new connections.
    s->AcceptingConnections = TRUE;
    // ...

    //debug_print ("sys_listen: [TODO] continue...\n");
    //printf      ("sys_listen: [TODO] continue...\n");

    // ...

//fake ok.
    return 0;
// ==============================================
fail:
    debug_print ("sys_listen: [FAIL]\n");
    printf      ("sys_listen: [FAIL]\n");
    refresh_screen();
    //while(1){}
    
    return -1;
}

// libc shutdown() function.
// See: https://linux.die.net/man/3/shutdown
int sys_socket_shutdown (int socket, int how)
{

    // #todo
    // desconectar dois sockets.
    // mas nao destruir o socket ...

// The current process.
    struct process_d *p;
// The file indicated by the fd.
    file *f;
// The socket structure for the file.
    struct socket_d *s;
// Is this file a socket object?
    int IsSocketObject = -1;

    debug_print ("sys_socket_shutdown: [TODO]\n");
    //printf      ("sys_socket_shutdown: [TODO] fd=%d how=%d\n",
    //    socket, how );

    // Invalid fd.
    if ( socket < 0 || socket >= OPEN_MAX )
    {
        debug_print ("sys_socket_shutdown: [FAIL] fd\n");
        printf      ("sys_socket_shutdown: [FAIL] fd\n");
        return (int) (-EBADF);
    }

// Process
    pid_t current_process = (pid_t) get_current_process();
    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL ){
        debug_print ("sys_socket_shutdown: p fail\n");
        printf      ("sys_socket_shutdown: p fail\n");
        goto fail;
    }

//
// File
//
 
// sender's file
// Objeto do tipo socket.

    f = (file *) p->Objects[socket];
    if ( (void *) f == NULL ){
        debug_print ("sys_socket_shutdown: f fail\n");
        printf      ("sys_socket_shutdown: f fail\n");
        goto fail;
    }

// Is this file a socket object?
    IsSocketObject = is_socket((file *)f);
    if (IsSocketObject != 1){
        debug_print ("sys_socket_shutdown: f is not a socket\n");
        printf      ("sys_socket_shutdown: f is not a socket\n");
        goto fail;
    }

//
// Socket
//

// Yes, This is a socket object.
// Let's get the socket structure associated with the file.
// Let's simply change the flag for this socket.
    s = (struct socket_d *) f->socket;
    if ( (void *) s == NULL ){
        debug_print ("sys_socket_shutdown: s fail\n");
        printf      ("sys_socket_shutdown: s fail\n");
        goto fail;
    // permanece conectado, mas usaremos outro da fila.
    }else{
        s->state = 216; 
        return 0;
    };

    // ...

fail:
    debug_print ("sys_socket_shutdown: [FAIL]\n");
    printf      ("sys_socket_shutdown: [FAIL]\n");
    return -1;
}

int 
update_socket ( 
    struct socket_d *socket, 
    unsigned int ip_ipv4, 
    unsigned short port )
{
    if ( (void *) socket ==  NULL ){
        return (int) -1;
    }
    socket->ip_ipv4 = (unsigned int)  ip_ipv4;
    socket->port = (unsigned short) port;
    return 0;
}

/*
 * sys_socket:
 * This is the socket() function implementation.
 * Estamos na klibc dentro do kernel base.
 */
// The function socket() creates an endpoint for communication and 
// returns a file descriptor for the socket.
// socket() creates a new socket of a certain type, 
// identified by an integer number, and 
// allocates system resources to it.
// See: 
// https://www.gnu.org/software/libc/manual/html_node/Sockets.html
// #example:
// tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
// udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
// raw_socket = socket(AF_INET, SOCK_RAW, protocol);
// #todo
// Fazer um switch para tratar os vários tipos.
// Se o protocolo for '0', então precisamos encontrar o 
// protocolo adequado.
// OUT:
//     fd if ok.
//     -1 if it fails.

int sys_socket ( int family, int type, int protocol )
{

    //#todo
    // call create_socket(...)
    // it will return a pointer.

// Socket structure.
    struct socket_d *__socket;
// Current process.
    struct process_d *p;
// ip:port. 
// Used in the socket struture.
    unsigned int _ipv4 = 
        (unsigned int) 0x00000000;
    unsigned long _ipv6 = 
        (unsigned long) 0x0000000000000000;
    unsigned short port = 
        (unsigned short) 0x0000;
    int Verbose = FALSE;


    pid_t current_process = (pid_t) get_current_process();
    
    // #debug
    // Slow.

    /*
    if ( Verbose == TRUE ){
        printf ("\n======================================\n");
        printf ("sys_socket: PID %d | family %d | type %d | protocol %d \n",
            current_process, family, type, protocol );
        refresh_screen();
    }
    */

    debug_print ("sys_socket:\n");

// Filters

    if (family < 0){
        debug_print ("sys_socket: family not supported\n");
        return (int) (-EINVAL);
    }

    if ( type != SOCK_STREAM &&
         type != SOCK_DGRAM  &&
         type != SOCK_RAW)
    {
        debug_print ("sys_socket: type not supported\n");
        return (int) (-EINVAL);
    }

// #todo
// We are accepting only the gramado native protocol for the sockets.
// Each kind of request has its own message structure.
// For now the message starts in the top of the buffer, 
// there is no ethernet header or tcp/ip header and the message
// is not in the payload. This is a plain for the future. #todo.
// 0 = GRAMADO NATIVE PROTOCOL.
    if (protocol < 0){
        debug_print ("sys_socket: protocol not supported\n");
        return (int) (-EINVAL);
    }

// #debug
// '0' is the only valid value for now.
    if( protocol != 0){
        panic ("sys_socket: protocol not supported yet.\n");
    }

// Current pid.
    if (current_process < 0 || current_process >= PROCESS_COUNT_MAX){
        debug_print ("sys_socket: current_process fail\n");
        panic       ("sys_socket: current_process fail\n");
    }

// Process structure.
    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL ){
        debug_print ("sys_socket: p\n");
        panic       ("sys_socket: p\n");
    }
    if (p->magic!=1234){
        panic ("sys_socket: p validation\n");
    }

// Socket structure.
// #todo:
// Create a helper function to do this job.
// This functions need to create the object and need to have this switch
// for different families. create_socket( family, type, protocol)
// it returns the socket structure pointer.
// Criamos um socket vazio.
// IN: ip and port.
    __socket = (struct socket_d *) create_socket_object();
    if ( (void *) __socket == NULL ){
        debug_print ("sys_socket: __socket\n");
        printf      ("sys_socket: __socket\n");
        goto fail;
    }

// family, type and protocol.
    __socket->family   = family;
    __socket->type     = type;      // DATAGRAM or STREAM 
    __socket->protocol = protocol;

// ip:port
// Initialized with '0'.
    __socket->ip_ipv4 = (unsigned int) _ipv4;
    __socket->ip_ipv6 = (unsigned long) _ipv6;
    __socket->port = 
        (unsigned short) port;

// pid, uid, gid.
    __socket->pid = (pid_t) current_process;
    __socket->uid = (uid_t) current_user;
    __socket->gid = (gid_t) current_group;

// #bugbug
// Set the private socket of a process.
// This is not good. 
// Some process will create more than one socket?
    p->priv = (struct socket_d *) __socket;

// Create socket file.
// #importante
// As rotinas logo abaixo criarão o arquivo 
// e retornarão o fd.
// family
// Setup the addr.

    switch (family){

    case AF_GRAMADO:
        debug_print ("sys_socket: AF_GRAMADO\n");
        __socket->connection_type = 1;  //local connection.
        return (int) socket_gramado ( (struct socket_d *) __socket, 
                         AF_GRAMADO, type, protocol );
        break;

    //case AF_LOCAL:
    case AF_UNIX:
        debug_print ("sys_socket: AF_UNIX\n");
        __socket->connection_type = 1;  //local connection
        return (int) socket_unix ( (struct socket_d *) __socket, 
                         AF_UNIX, type, protocol );
        break;

    //#bugbug: 
    //talvez precisamos rever sockaddr 
    //para essa função, e usarmos outra estrutura.               
    case AF_INET:
        debug_print ("sys_socket: AF_INET\n");
        __socket->connection_type = 0;//?;  //Is it really a remote connection?
        return (int) socket_inet ( (struct socket_d *) __socket, 
                         AF_INET, type, protocol );
        break;

    // ...

    default:
        debug_print ("sys_socket: [FAIL] bad family\n");
        //debug_print ("sys_socket: Couldn't create the file\n");
        goto fail;
        break;
    };

    // ...

fail:
    debug_print ("sys_socket: [FAIL] Something is wrong!\n");
    refresh_screen();
    return (int) (-1);
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

// ===============
    fd1 = sys_socket(family,type,protocol);
    sock1 = get_socket_from_fd(fd1);
    if( (void*) sock1 == NULL){
        debug_print("sock_socketpair: sock1\n");
        return -1;
    }

// ===============
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

static int __socket_initialize_gramado_ports(void)
{
    register int i=0;
    for (i=0; i<GRAMADO_PORT_MAX; i++){
        gramado_ports[i] = 0;
    };
    return 0;
}

// Initialize socket list.
int socket_init(void)
{
    register int i=0;

    for (i=0; i<32; i++){
        socketList[i] = (unsigned long) 0;
    };
    __socket_initialize_gramado_ports();
    // ...
    return 0;
}

//
// End
//

