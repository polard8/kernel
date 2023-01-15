
// tty.c

#include <kernel.h>  

static int new_tty_index=0;

// see: tty.h
struct tty_d  CONSOLE_TTYS[8];


/*
 * __tty_read:
 *     Read n bytes from a tty. raw buffer.
 * IN:
 *     tty    = Pointer to tty structure.
 *     buffer = Buffer.
 *     nr     = How many bytes.
 */
// Called by tty_read.

int 
__tty_read ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr )
{
    register int i=0;
    char data[TTY_BUF_SIZE];
    char c=0;
    char *b;

    b = buffer;

    // #debug
    printf("__tty_read:\n");

// tty structure.
    if ( (void *) tty == NULL ){
        printf ("__tty_read: tty\n");
        goto fail;
    }
    if ( tty->used != TRUE || tty->magic != 1234 ){
        printf ("__tty_read: tty validation\n");
        goto fail;
    }
// buffer
    if ( (char *) buffer == NULL ){
         panic ("__tty_read: Invalid buffer\n");
    }
// nr
    if (nr <= 0){
        printf ("__tty_read: nr\n");
        goto fail;
    }
    //if ( tty->stopped == TRUE )
        //return -1;
// Queue 
// A leitura nas filas vai depender do modo
// configurado.
// Temos basicamente os 'raw' e 'canonical'.
// ??
// Lembrando que no modo canônico teremos algum tipo de edição.
// então o usuário receberá uma fila somente depois que ele digitar
// [enter]
// Get data from the queue.
// Isso tem o mesmo tamanho
// da fila de tty.

    int rbytes=nr;
    if (rbytes<=0){
        return 0;
    }

// não se pode ler mais que o limite.
    if (rbytes>TTY_BUF_SIZE){
        rbytes=TTY_BUF_SIZE;
    }

    while (rbytes > 0)
    {
        // Empty
        // Isso acontece também quando a fila esta vazia.
        if ( tty->raw_queue.head == tty->raw_queue.tail ){
            printf("__tty_read: tty->raw_queue.head == tty->raw_queue.tail\n");
            return 0;
        }

        // Acabou a fila.
        if ( tty->raw_queue.tail > TTY_BUF_SIZE ){
            printf("__tty_read: tty->raw_queue.tail > TTY_BUF_SIZE\n");
            return 0;
        }

        // get one char
        c = tty->raw_queue.buf[ tty->raw_queue.tail ];
        // avança na fila
        tty->raw_queue.tail++;
        data[i] = c;
        i++;
        rbytes--;
        if (rbytes<=0){
            break;
        }
    };

// Quantidade de bytes no buffer local.
    if (i <= 0){
        printf("__tty_read: i <= 0\n");
        return 0;
    }

    if (i > TTY_BUF_SIZE){
        i = TTY_BUF_SIZE;
    }

// Send
// Copiando os bytes de nosso buffer local para
// o buffer de usuário.
    memcpy( (void *) b, (const void *) data, i ); 

    // #debug
    //printf("__tty_read: done\n");

// Retornamos a quantidade de bytes que tinha em nosso buffer local.
    return (int) i;
fail:
    refresh_screen();
    return (int) (-1);
}

/*
 * __tty_write:
 *     Write n bytes to a tty. raw buffer.
 * IN:
 *     tty    = Pointer to tty structure.
 *     buffer = Buffer.
 *     nr     = How many bytes.
 */
// #bugbug
// ?? Why
// We are sending a message to a process.

int 
__tty_write ( 
    struct tty_d *tty, 
    char *buffer, 
    int nr )
{
    register int i=0;
    char data[TTY_BUF_SIZE];
    char c=0;
    char *b;

    b = buffer;

    // #debug
    printf("__tty_write:\n");

// tty
    if ( (void *) tty == NULL ){
        debug_print ("__tty_write: tty\n");
        goto fail;
    }
    if ( tty->used != TRUE || tty->magic != 1234 ){
        printf ("__tty_write: tty validation\n");
        goto fail;
    }
// buffer
    if ( (char *) buffer == NULL ){
         panic ("__tty_write: Invalid buffer\n");
    }
// nr
    if (nr <= 0){
        printf ("__tty_write: nr\n");
        goto fail;
    }

    //if ( tty->stopped == TRUE )
        //return -1;

// Queue 
// A escrita nas filas vai depender do modo
// configurado.
// Temos basicamente os 'raw' e 'canonical'.
// ??
// Lembrando que no modo canônico teremos algum tipo de edição.
// então o usuário receberá uma fila somente depois que ele digitar
// [enter]
// Get data from the queue.
// Isso tem o mesmo tamanho
// da fila de tty.

    int wbytes=nr;
    if (wbytes<=0){
        return 0;
    }

// não se pode escrever mais que o limite.
    if (wbytes>TTY_BUF_SIZE){
        wbytes=TTY_BUF_SIZE;
    }

// Receive
// Copiando bytes do buffer do usuário para nosso buffer local.
    memcpy( (void *) data, (const void *) b, wbytes ); 

//buffer local
    i=0;

    while (wbytes > 0)
    {
        // Acabou a fila.
        if ( tty->raw_queue.head >= TTY_BUF_SIZE ){
            break;
        }

        //pega um char do buffer local
        c = data[i];
        // grava um char na fila do tty
        tty->raw_queue.buf[ tty->raw_queue.head ] = c;
        //avança na fila
        tty->raw_queue.head++;
        // Incrementa a quantidade que foi gravada.
        i++;
        // Quantos faltam.
        wbytes--;
        if (wbytes<=0){
            break;
        }
    };

done:
    
    //#debug
    printf("__tty_write: done\n");

// Quantidade de bytes que gravamos na tty
    if (i <= 0){
        return 0;
    }
    if (i > TTY_BUF_SIZE){
        i=TTY_BUF_SIZE;
    }
// Retornamos a quantidade que gravamos na fila da tty.
    return (int) i;
fail:
    refresh_screen();
    return (int) (-1);
}


/*
 * tty_read: service 272
 *     Ler uma certa quantidade de bytes, 
 * da tty para o buffer indicado no argumento.
 */
// #todo
// O aplicativo ou servidor poderia chamar essa rotina
// se ele tiver o fd do dispositivo tty onde o teclado esta
// colocando os bytes.
// /PS2KBD
// IN: 
// fd = indice na lista de arquivos abertos pelo processo.

int 
tty_read ( 
    int fd, 
    char *buffer, 
    int n )
{
    struct tty_d *__tty;
    struct process_d *p;
    file *f;

    debug_print ("tty_read: [FIXME]\n");

    pid_t current_process = (pid_t) get_current_process();

// fd
    if ( fd < 0 || fd > 31 ){
        return (int) (-EBADF);
    }

//#todo
    //if( (void*) buffer == NULL )
    //{
    //    return (int) (-EINVAL);
    //}

// #todo: 'n'

// process.
// Vamos pegar o ponteiro de estrutura
// do processo que chamou essa funçao

    if (current_process<0 || current_process >= PROCESS_COUNT_MAX){
        return -1;
    }
    p = (struct process_d *) processList[current_process];
    if ((void*) p == NULL){
        debug_print("tty_read: p\n");
        return -1;
    }
    if (p->magic != 1234){
        return -1;
    }

// file
// The object

    f = (file *) p->Objects[fd];
    if ((void*) f == NULL){
        debug_print("tty_read: f\n");
        return -1;
    }
    if (f->magic != 1234){
        return -1;
    }

    if ( f->____object != ObjectTypeTTY ){
        debug_print("tty_read: ____object\n");
        return -1;
    }

// tty
// Pega a tty representada pelo arquivo.

    __tty = (struct tty_d *) f->tty;
    if ( (void*) __tty == NULL ){
        debug_print("tty_read: __tty\n");
        return -1;
    }
    // #todo
    // if(__tty->magic != 1234)
    //     return -1;

// Read from tty device.
     return (int) __tty_read ( 
                      (struct tty_d *) __tty, 
                      (char *) buffer, 
                      (int) n );
}


// service 273
// IN: 
// fd = indice na lista de arquivos abertos pelo processo.
int 
tty_write ( 
    int fd, 
    char *buffer, 
    int n )
{
    struct tty_d *__tty;
    struct process_d *p;
    file *f;

    debug_print ("tty_write: [FIXME]\n");

    pid_t current_process = (pid_t) get_current_process();

// fd
    if ( fd < 0 || fd > 31 ){
        return (int) (-EBADF);
    }

//#todo
    //if( (void*) buffer == NULL )
    //{
    //    return (int) (-EINVAL);
    //}

// #todo: 'n'



// process
// vamos pegar o ponteiro do processo
// que chamou essa funçao, dentro da lista global
// de ponteiros de processos.

    if (current_process<0 || current_process >= PROCESS_COUNT_MAX){
        return -1;
    }
    p = (struct process_d *) processList[current_process];
    if ((void*) p == NULL){
        debug_print("tty_write: p\n");
        return -1;
    }
    if (p->magic != 1234){
       return 1;
    }

// file
    f = (file *) p->Objects[fd];
    if ((void*) f == NULL){
        debug_print("tty_write: f\n");
        return -1;
    }
    if (f->magic != 1234){
        return -1;
    }

// Object tty.
    if ( f->____object != ObjectTypeTTY ){
        debug_print("tty_write: ____object\n");
        return -1;
    }

// tty
// Pega a tty representada pelo arquivo.
    __tty = (struct tty_d *) f->tty;
    if ( (void*) __tty == NULL ){
        debug_print("tty_write: __tty\n");
        return -1;
    }
    // #todo
    // if(__tty->magic != 1234)
    //     return -1;

// Read tty
    return (int) __tty_write ( 
                     (struct tty_d *) __tty, 
                     (char *) buffer, 
                     (int) n );
}

// tty_reset_termios: 
// Reset termios in a given tty.
// See: tty.h
// #todo: use int as return.

int tty_reset_termios(struct tty_d *tty)
{
    if ( (void *) tty == NULL ){
        return (int) -1;
    }

    // #test
    // memset( &tty->termios, 0, sizeof(struct termios_d) );

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
    //tty->termios.c_cc[VEOL] = CEOL; 

// ^h
// (CERASE: <Ctrl>h or ASCII BS)
// 0x7f ??
// 8;  //BS
    tty->termios.c_cc[VERASE] = CERASE;

// ^c
// (CINTR: rubout or ASCII DEL)   
// 3;  //EOI  
    tty->termios.c_cc[VINTR] = CINTR;

// ^u
// (CKILL: <Ctrl>u or ASCII NAK)
// ? - 1;  //BS
    tty->termios.c_cc[VKILL] = CKILL;

// ^\
// (CQUIT: <Ctrl>\ or ASCII FS) 
// ? - 0x1C
//28; //FS
    tty->termios.c_cc[VQUIT] = CQUIT;

// ^z 
// (CSUSP: <Ctrl>z or ASCII SUB) 
// 26; //BS
    tty->termios.c_cc[VSUSP] = CSUSP;   

// #todo
    //tty->win_size.ws_col = 80;
    //tty->win_size.ws_row = 25;

    return 0;
}

/*
 * tty_create: 
 *    Create a tty structure.
 * OUT:
 *     pointer.
 */
// #test
// We are including a pointer to the RIT. raw input thread.
// This is the control thread of the window with focus on kgws.
// See: tty.h

struct tty_d *tty_create(void)
{
    file *__file;
    struct tty_d  *__tty;
    char __tmpname[64];
    register int i=0;

    debug_print ("tty_create: [FIXME] \n");

// Create structure.
    __tty = (struct tty_d *) kmalloc( sizeof(struct tty_d) );
    if ( (void *) __tty == NULL ){
        panic ("tty_create: __tty\n");   
    }
    memset( __tty, 0, sizeof(struct tty_d) );

    __tty->objectType = ObjectTypeTTY;
    __tty->objectClass = ObjectClassKernelObjects;
    __tty->used = TRUE;
    __tty->magic = 1234;

// Index
    __tty->index = (int) (new_tty_index & 0xFFFF);
    new_tty_index++;
// No thread for now.
// ?? What thread we need to use here?
    __tty->control = NULL;
// No user logged yet.
    __tty->user_info = NULL;
// #bugbug
// Security stuff.
// Maybe it will change when a user login into a terminal.
// Nao sei se essas estruturas estao prontas para isso nesse momento
// ou se esses ponteiros sao nulos.
    __tty->user_session = NULL;  // CurrentUserSession;
    __tty->room         = NULL;  // CurrentRoom;
    __tty->desktop      = NULL;  // CurrentDesktop;

// file pointer
// this file handles this tty object
// isso sera tratado la em baixo.
        //__tty->fp
// tty name
// isso sera tratado la em baixo.
        //__tty->name[?] 
    __tty->Name_len = 0;  //initialized
//#todo: Indice do dispositivo.
    // __tty->device = 0;   // initialized.
    __tty->driver = NULL;  //driver struct
    __tty->ldisc  = NULL;  //line discipline struct
// termios struct (not a pointer)
    tty_reset_termios(__tty);
// process group.
    __tty->gid = current_group;
// ??
// Quantos processos estao usando essa tty.
    __tty->pid_count=0;
    __tty->type = 0;
    __tty->subtype = 0;
    __tty->flags = 0;
// not stopped
    __tty->stopped = FALSE;
// process
    // __tty->process = KernelProcess;
// thread
    // __tty->thread  = ?
// Qual terminal virtual esta usando essa tty.
    __tty->virtual_terminal_pid = 0;
// Window.
// When we are using the kgws.
    //__tty->window = NULL;

// == buffers ===========================

// YES, We are using buffer.
    __tty->nobuffers = FALSE;

// queues

// raw queue
    __tty->raw_queue.cnt = 0;
    __tty->raw_queue.head = 0;
    __tty->raw_queue.tail = 0;
    for(i=0; i<TTY_BUF_SIZE; i++){ __tty->raw_queue.buf[i] = 0; }
// canonical queue
    __tty->canonical_queue.cnt = 0;
    __tty->canonical_queue.head = 0;
    __tty->canonical_queue.tail = 0;
    for(i=0; i<TTY_BUF_SIZE; i++){ __tty->canonical_queue.buf[i] = 0; }
// output queue
    __tty->output_queue.cnt = 0;
    __tty->output_queue.head = 0;
    __tty->output_queue.tail = 0;
    for(i=0; i<TTY_BUF_SIZE; i++){ __tty->output_queue.buf[i] = 0; }

// system metrics.

// cursor dimentions in pixels.
// #bugbug: determined.
    __tty->cursor_width_in_pixels = 8;
    __tty->cursor_height_in_pixels = 8;
//#todo
// it needs to be 'unsigned int'
    __tty->bg_color = COLOR_BLACK;
    __tty->fg_color = COLOR_WHITE;
// cursor position in chars.
    __tty->cursor_x = 0;
    __tty->cursor_y = 0;
// cursor margin.
    __tty->cursor_left = 0;
    __tty->cursor_top  = 0;

// #bugbug: 
// Constant cursor size.
// cursor limits.
    __tty->cursor_right  = 0+(gSavedX/8) -1;  // (screen width / char width)
    __tty->cursor_bottom = 0+(gSavedY/8) -1;  // (screen height/ char height)

// #bugbug
// Temos que completar as estruturas.
// São muitos elementos ...
// ...

    // goto __ok_register;
    //return (struct tty_d *) __tty;

    //panic ("tty_create: Crazy error!\n");
    //return NULL;

// ==========================================
//__ok_register:

    if ( (void *) __tty == NULL ){
        panic("tty_create: __tty\n");
    }

// mount point. 
// pathname.

// #test
// Isso é o ponto de montagem.
    int Index = (int) (__tty->index & 0xFFFF);
// clear buffer
    memset( __tmpname, 0, 64 );
    sprintf ( __tmpname, "/TTY%d", Index );

    //size_t NameSize = (size_t) strlen(__tmpname);
// ----

    char *newname = (char *) kmalloc(64);
    if ( (void*) newname == NULL ){
        panic("tty_create: newname\n");
    }
// clear buffer
    memset( newname, 0, 64 );
    strcpy(newname,__tmpname);

// File pointer.
// Agora registra o dispositivo pci na lista genérica
// de dispositivos.
// #importante: 
// Ele precisa de um arquivo 'file'.
    
    __file = (file *) kmalloc ( sizeof(file) );
    if ( (void *) __file == NULL ){
        panic ("tty_create: __file\n");
    }

    __file->used = TRUE;
    __file->magic = 1234;
    __file->____object = ObjectTypeTTY;
    __file->isDevice = TRUE;
// A estrutura de tty associada com esse arquivo.
    __file->tty = __tty;
// Esse é o arquivo que aponta para essa estrutura.
    __tty->fp = __file;
// sync
    __file->sync.sender = -1;
    __file->sync.receiver = -1;
    __file->sync.action = ACTION_NULL;
    __file->sync.can_read = TRUE;
    __file->sync.can_write = TRUE;
    __file->sync.can_execute = FALSE;
// tty is not a socket.
// Do not accet and do not connect.
    __file->sync.can_accept = FALSE;
    __file->sync.can_connect = FALSE;

    //Todo: create the file name.
    //__file->_tmpfname = "TTYX    TTY";
    //sprintf( (char *) __file->_tmpfname, "TTY%d", ?? );
    //strcpy (?,__file->_tmpfname);

// #todo
// precisamos pegar um slot livre na lista de objetos abertos pelo processo.
// O indice da tty é fd do arquivo que aponta para a tty.
    //__tty->index = __file->_file;
    //__tty->index = -1;

// Register device:
// #importante
// Essa é a tabela de montagem de dispositivos.
// O nome do dispositivo deve ser um pathname.
// Mas podemos ter mais de um nome.
// vamos criar uma string aqui usando sprint e depois duplicala.
// See: devmgr.c

    devmgr_register_device ( 
        (file *) __file,     // file 
        newname,             // pathname 
        DEVICE_CLASS_CHAR,   // class (char, block, network)
        DEVICE_TYPE_LEGACY,  // type (pci, legacy)
        NULL,                // Not a pci device.
        __tty );             // This is a tty device.

// ==========================================

// last check.
    if ( (void *) __tty == NULL ){
        panic ("tty_create: [FAIL] __tty");
    }

// ok.
    return (struct tty_d *) __tty;
}

// file to tty.
// OUT: tty pointer.
struct tty_d *file_tty (file *f)
{
    if ( (void *)f==NULL ){
        return (struct tty_d *) 0;
        //return NULL;
    }
    return (struct tty_d *) f->tty;
}

// #todo
// flush the output buffer to the current virtual console.
void tty_flush(struct tty_d *tty)
{
    // todo
    debug_print("tty_flush: [TODO]\n");
    
    if ( (void*) tty == NULL )
        return;
}

void tty_start (struct tty_d *tty)
{
    if ( (void *) tty == NULL ){
        debug_print("tty_start: tty\n");
        return;
    }
// Se não está parada.
    if (tty->stopped == FALSE){
        //debug_print("tty_start: not stopped\n");
        return;
    }
    tty->stopped = FALSE;
}

void tty_stop (struct tty_d *tty)
{
    if ( (void *) tty == NULL ){
        debug_print("tty_stop: tty\n");
        return;
    }
// Se ela já está parada.
    if (tty->stopped == TRUE){
        //debug_print("tty_stop: already stopped\n");
        return;
    }
    tty->stopped = TRUE;
}

// #todo: 
int tty_delete (struct tty_d *tty)
{
// Nothing to do.
    if ( (void *) tty == NULL ){
        debug_print ("tty_delete: tty\n");
        //debug_print("...");
        return -1;
    }
    //#bugbug: fast way
    //free (tty);
//reusar
    tty->magic = 216;
    tty_stop(tty);
    // ...
    return 0;
}

// Copia a estrutura de termios
// para o aplicativo em ring3 poder ler.
// #todo #maybe: Retornar a quantidade lida?
int 
tty_gets ( 
    struct tty_d *tty, 
    struct termios_d *termiosp )
{
    if ( (void *) tty == NULL ){
        debug_print("tty_gets: [FAIL] tty\n");
        return -1;
    }
    if ( (void *) termiosp == NULL ){
        debug_print("tty_gets: [FAIL] termiosp\n");
        return -1;
    }
// Copia a estrutura term da tty na estrutura de termios 
// que está em ring3.
    memcpy ( 
        termiosp, 
        &tty->termios, 
        sizeof(struct termios_d) );

    return 0;
}


// Copia de ring3 para o kernel.
int 
tty_sets ( 
    struct tty_d *tty, 
    int options, 
    struct termios_d *termiosp )
{
    int ret = -1;

    if ( (void *) tty == NULL ){
        debug_print("tty_sets: [FAIL] tty\n");
        return -1;
    }
    if (tty->magic != 1234){
        return -1;
    }

    if (options < 0){
        debug_print("tty_sets: [FAIL] options\n");
        return -1;
    }
    if ( (void *) termiosp == NULL ){
        debug_print("tty_sets: [FAIL] termiosp\n");
        return -1;
    }

// Options

    switch (options){

// Now. The change occurs immediately. 
    case TCSANOW:
        memcpy ( &tty->termios, termiosp, sizeof(struct termios_d) );
        break;
    // ...
    default:
        debug_print ("tty_sets: [FAIL] default\n");
        //ret = -EINVAL;
        ret = -1;
        break;
    };

    return (int) ret;
}


int tty_init_module (void)
{
    // Nothing for now!
    debug_print ("tty_init_module:\n");
    // ...
    return 0;
}

// tty_ioctl:
// Pegaremos a estrutura de tty.
// Dado o fd, pegaremos um arquivo que é um objeto tty.
// Esse arquivo traz um ponteiro para a estrutura tty.
// See:
// https://man7.org/linux/man-pages/man3/tcflush.3.html
// #todo
// See: 
// termios.h
// ioctls.h

int 
tty_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    struct process_d *p;
    file *f;
    struct tty_d *tty;
    pid_t current_process = -1;


    debug_print ("tty_ioctl: TODO\n");

    if ( fd < 0 || fd >= OPEN_MAX ){
        return (int) (-EBADF);
    }

// Current process.
// #todo
// podemos checar novamente se realmente se trata de
// um tty. Mas isso ja foi feito no wrapper sys_ioctl.

    current_process = (pid_t) get_current_process();
    if (current_process < 0 || current_process >= PROCESS_COUNT_MAX){ 
        return -1;
    }

// process
    p = (struct process_d *) processList[current_process];
    if ( (void *) p == NULL ){
        debug_print ("tty_ioctl: p\n");
        return -1;
    }
    if (p->magic != 1234){
        return -1;
    }

// file. (Object).
    f = (file*) p->Objects[fd];
    if ( (void *) f == NULL ){
        debug_print ("tty_ioctl: [FAIL] f\n"); 
        return -1;
    }
    if (f->magic != 1234){
        return -1;
    }

// Is it a tty object?
// Get tty struct!
    if (f->____object != ObjectTypeTTY){
        debug_print ("tty_ioctl: [FAIL] Not a tty file\n");
        return -1;
    }
    tty = f->tty;

// The command!

    switch (request){

// Get termios.
    case TCGETS:
        debug_print ("tty_ioctl: TCGETS\n");
        if ( (void*) arg == NULL ){
            return (int) (-EINVAL);
        }
        return (int) tty_gets ( tty, (struct termios_d *) arg );
        break;
// Set termios.
    case TCSETS:
        debug_print ("tty_ioctl: TCSETS\n");
        if ( (void*) arg == NULL ){
            return (int) (-EINVAL);
        }
        return (int) tty_sets ( 
                         tty, TCSANOW, (struct termios_d *) arg );
        break;
// ??
// Discards data written to the object referred to by fd .
    case TCFLSH:
        debug_print ("tty_ioctl: TCFLSH [TODO]\n");
        return -1;
        break;
    case TCIFLUSH:
        debug_print ("tty_ioctl: TCIFLUSH [TODO]\n");
        return -1;
        break;
    case TCOFLUSH:
        debug_print ("tty_ioctl: TCOFLUSH [TODO]\n");
        return -1;
        break;
    case TCIOFLUSH:
        debug_print ("tty_ioctl: TCIOFLUSH [TODO]\n");
        return -1;
        break;
// Set termio.   
    case TCGETA:
         debug_print ("tty_ioctl: TCGETA [TODO]\n");
         return -1;
         break;
// Get termio.
    case TCSETA:
         debug_print ("tty_ioctl: TCSETA [TODO]\n");
         return -1;
         break;

    // TCSETSF, TCSETSW, , TCSETAF, TCSETAW, , TCSBRK
    // TCXONC
    // TIOCGWINSZ, TIOCSWINSZ, TIOCGPGRP, TIOCSPGRP, TIOCNOTTY
    // TIOCEXCL, TIOCNXCL, TIOCSCTTY, TIOCGPGRP, TIOCSPGRP, TIOCOUTQ
    // TIOCINQ, TIOCSTI, TIOCMGET, TIOCMBIS, TIOCMBIC, TIOCMSET,
    // TIOCGSOFTCAR, TIOCSSOFTCAR

//CLEAN
    case 900:
        //tty->_rbuffer->_w = 0;
        //tty->_rbuffer->_r = 0;
        //tty->_rbuffer->_p = tty->_rbuffer->_base; 
        //tty->_rbuffer->_cnt = tty->_rbuffer->_lbfsize;
        //for( xxxi=0; xxxi<BUFSIZ; xxxi++){ tty->_rbuffer->_p[xxxi] = 0; };
        break;

    default:
        debug_print ("tty_ioctl: [FAIL] default\n");
        return (int) (-EINVAL);
        break;
    };

    //fail.
    return -1;
}

