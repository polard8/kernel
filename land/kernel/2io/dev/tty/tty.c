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


extern unsigned long SavedX;
extern unsigned long SavedY;


// Ponteiros para os dispositivos
// que a tty atua.
// sendo que o primeiro dispositivo (canal) é o console.



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



/*
 ***********************************
 * tty_create: 
 *    Create a tty structure.
 * 
 * OUT:
 *     pointer.
 */

// #test
// We are including a pointer to the RIT. raw input thread.
// This is the control thread of the window with focus on kgws.

// See: tty.h

struct tty_d *tty_create (void){

    struct tty_d *__tty;

    // name
    char __tmpname[64];
    
    file *__file;


    debug_print ("tty_create: [FIXME] \n");


    __tty = (struct tty_d *) kmalloc ( sizeof(struct tty_d) );
    
    if ( (void *) __tty == NULL ){
        panic ("tty_create: __tty kmalloc fail \n");   
        //return NULL;
 
    }else{
        __tty->objectType  = ObjectTypeTTY;
        __tty->objectClass = ObjectClassKernelObjects;
        
        //__tty->index = ?;
        __tty->used = 1;
        __tty->magic = 1234;

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
        __tty->user_session = NULL;  //CurrentUserSession;
        __tty->room         = NULL;  // CurrentRoom;
        __tty->desktop      = NULL;  // CurrentDesktop;


        // file pointer
        // this file handles this tty object
        //isso sera tratado la em baixo.
        //__tty->_fp
    
        // tty name
        // isso sera tratado la em baixo.
        //__tty->name[?] 
        __tty->Name_len = 0;  //initialized

        //#todo: Indice do dispositivo.
        // __tty->device = 0;   // initialized.

        __tty->driver = NULL;  //driver struct
        __tty->ldisc  = NULL;  //line discipline struct
        
        //termios struct (not a pointer)
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
        __tty->stopped = 0;

        // process
        // __tty->process = KernelProcess;
    
        // thread
        // __tty->thread  = ?

        // Qual terminal virtual esta usando essa tty.
        __tty->virtual_terminal_pid = 0;

        // Window.
        // When we are using the kgws.
        //__tty->window = NULL;



        //
        // == buffers ===========================
        //

        // YES, We are using buffer.
        __tty->nobuffers = FALSE;   // No buffers.


        // Ponteiros para estruturas de arquivos.
        // Esses arquivos servem de buffers.

        // Buffers.        
        // Raw and canonical.
        __tty->_rbuffer = (file *) newPage();
        __tty->_cbuffer = (file *) newPage();
        
        //output buffer.
        __tty->_obuffer = (file *) newPage();
        

        if ( (void *) __tty->_rbuffer == NULL ||
             (void *) __tty->_cbuffer == NULL ||
             (void *) __tty->_obuffer == NULL   )
        {
            panic("tty_create: [FAIL] Buffers\n");
        }

        // Precisa validar

        __tty->_rbuffer->used = 1;
        __tty->_rbuffer->magic = 1234;  
               
        __tty->_cbuffer->used = 1;
        __tty->_cbuffer->magic = 1234;
        
        __tty->_obuffer->used  = 1;
        __tty->_obuffer->magic = 1234;


        // o buffer do arquivo. (_base)

        __tty->_rbuffer->_base  = (char *) newPage();
        __tty->_cbuffer->_base  = (char *) newPage();
        __tty->_obuffer->_base  = (char *) newPage();


        // buffer validation
        if ( (void *) __tty->_rbuffer->_base == NULL ||
             (void *) __tty->_cbuffer->_base == NULL ||
             (void *) __tty->_obuffer->_base == NULL   )
        {
            panic("tty_create: [FAIL] buffer validation\n");
        }

        //#test: objeto do tipo buffer de io.
        __tty->_rbuffer->____object = ObjectTypeIoBuffer;
        __tty->_cbuffer->____object = ObjectTypeIoBuffer;
        __tty->_obuffer->____object = ObjectTypeIoBuffer; 

        // #todo
        // o buffer tem o tamanho de uma pagina.
        // mas vamos usar o tamanho padraao por enquanto.
        __tty->_rbuffer->_lbfsize = BUFSIZ;
        __tty->_cbuffer->_lbfsize = BUFSIZ;
        __tty->_obuffer->_lbfsize = BUFSIZ; 
        
        //o quanto falta pra acabar.
        __tty->_rbuffer->_cnt = BUFSIZ;
        __tty->_cbuffer->_cnt = BUFSIZ;
        __tty->_obuffer->_cnt = BUFSIZ; 
        
        //offset de leitura.
        __tty->_rbuffer->_r = 0;
        __tty->_cbuffer->_r = 0;
        __tty->_obuffer->_r = 0; 
        
        //offset de escrita
        __tty->_rbuffer->_w = 0;
        __tty->_cbuffer->_w = 0;
        __tty->_obuffer->_w = 0; 




        // system metrics .
        
        // cursor dimentions in pixels.
        // #bugbug: determined.
        __tty->cursor_width_in_pixels  = 8;
        __tty->cursor_height_in_pixels = 8;

        __tty->cursor_color = COLOR_WHITE; 
        
        // cursor position in chars.
        __tty->cursor_x = 0;
        __tty->cursor_y = 0;
        
        // cursor margin
        __tty->cursor_left = 0;
        __tty->cursor_top  = 0;
        
        // cursor limits.
        __tty->cursor_right  = 0+(SavedX/8) -1;  // (screen width / char width)
        __tty->cursor_bottom = 0+(SavedY/8) -1;  // (screen height/ char height)
    

        // #bugbug
        // Temos que completar as estruturas.
        // São muitos elementos ...


        // ...

        goto __ok_register;
        //return (struct tty_d *) __tty;
    };


    panic ("tty_create: Crazy error!\n");   
    //return NULL;


// ==========================================
__ok_register:


    if ( (void *) __tty == NULL ){
        panic("tty_create: __tty");
    }

    //#test
    // isso não é o ponto de montagem.
    
    sprintf ( (char *) &__tmpname[0], 
        "/DEV_TTY%d", 
        __tty->index );
    
    char *newname = (char *) kmalloc (64);
    if ( (void*) newname == NULL ){
        panic("tty_create: newname");
    }
    strcpy (newname,__tmpname);


    // Agora registra o dispositivo pci na lista genérica
    // de dispositivos.
    // #importante: 
    // Ele precisa de um arquivo 'file'.
    
    __file = (file *) kmalloc ( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        panic ("tty_create: __file fail, can't register device");
    
    }else{

       // file
       
        __file->____object = ObjectTypeTTY;
        __file->used  = 1;
        __file->magic = 1234;

        __file->isDevice = 1;

        // A estrutura de tty associada com esse arquivo.
        __file->tty = __tty;

        // sync
        __file->sync.sender = -1;
        __file->sync.receiver = -1;
        __file->sync.stage = 0;
        __file->sync.can_read = TRUE;
        __file->sync.can_write = TRUE;
        __file->sync.can_execute = FALSE;
        
        // tty is not a socket.
        __file->sync.can_accept = FALSE;
        __file->sync.can_connect = FALSE;

        //Todo: create the file name.
        //__file->_tmpfname = "TTYX    TTY";
        //sprintf( (char *) __file->_tmpfname, "TTY%d", ?? );
        //strcpy (?,__file->_tmpfname);

        // Esse é o arquivo que aponta para essa estrutura.
        __tty->_fp = __file;
        
        
        // #todo
        // precisamos pegar um slot livre na lista de objetos abertos pelo processo.
        // O indice da tty é fd do arquivo que aponta para a tty.
        //__tty->index = __file->_file;
        __tty->index = -1;
        

        //
        // == Register ===========================================
        //

        // #importante
        // Essa é a tabela de montagem de dispositivos.
        // O nome do dispositivo deve ser um pathname.
        // Mas podemos ter mais de um nome.
        // vamos criar uma string aqui usando sprint e depois duplicala.
        // See: ??
        
        devmgr_register_device ( (file *) __file, 
             newname,                    // device name.  
             0,                          // class (char, block, network)
             1,                          // type (pci, legacy
             (struct pci_device_d *) 0,  // pci device
             NULL );                     // tty driver
    
    };
// ==========================================

    // last check.
    if ( (void *) __tty == NULL ){
        panic ("tty_create: [FAIL] __tty");
    }

    // ok.
    return (struct tty_d *) __tty;
}





/*
 *************************************************
 * __tty_read:
 *     Read n bytes from a tty. raw buffer
 * 
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

    // tty
    if ( (void *) tty == NULL ){
        debug_print ("__tty_read: tty\n");
        return -1;
    }

    // buffer
    if ( (char *) buffer == NULL ){
         panic ("__tty_read: invalid buffer \n");
    }

    // nr
    if ( nr <= 0 ){
        printf ("__tty_read: nr \n");
        refresh_screen();
        return -1;
    }

 
    //
    // File   (stdin)
    //
    
    // Arquivo de leitura.
 
    // #importante
    // Não usaremos mais o termo stream no kernel.
    // Isso então é um arquivo apontando pela tty.
    // Podemos usar o buffer da tty.   
            
    if ( (void *) tty->_rbuffer == NULL ){
         printf ("__tty_read: Invalid tty _buffer\n");
         refresh_screen();
         return -1;
    }


    //
    // _base. 
    //
    
    // A base do arquivo que serve de buffer.
    

    if ( (void *) tty->_rbuffer->_base == NULL ){
         printf ("__tty_read: invalid _base \n");
         refresh_screen();
         return -1;
    }

    // nao queremos ler mais que o tamanho do buffer.
    if ( nr > tty->_rbuffer->_lbfsize )
    {
        //#debug
        //panic("__tty_read: FAIL\n");
        
        printk("__tty_read: [FAIL] buffer overflow\n");
        refresh_screen();
        
        return 0; //escreveu '0' bytes.
    }

    // #debug
    // o offset de escrita indica o quanto foi escrito.
    if ( nr > tty->_rbuffer->_w )
    {
        debug_print("__tty_read: Reading extra bytes\n");
    }


    // #bugbug
    // tty se le tudo desde a base?
    tty->_rbuffer->_r = 0;

    
    // Copy
    // Copia da tty de leitura para o buffer indicado pelo aplicativo.
    // #debug       
    //printf ("__tty_read: Copiando para o buffer. \n");
    //refresh_screen ();

    memcpy ( 
        (void *) buffer, 
        (const void *) tty->_rbuffer->_base, 
        nr ); 


    //#debug
    //printf ( "debug_read >>>%s \n", buffer );
    //refresh_screen ();
           
    return (int) nr; 
}








/*
 *************************************************
 * __tty_write:
 *     Write n bytes to a tty. raw buffer.
 * 
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
    debug_print ("__tty_write: [DEBUG]\n");
        
    // tty
    if ( (void *) tty == NULL ){
        debug_print ("__tty_write: tty\n");
        return -1;
    }

    // buffer
    if ( (char *) buffer == NULL ){
         panic ("__tty_write: invalid buf \n");
    }

    // nr
    if ( nr <= 0 ){
        printf ("__tty_write: nr \n");
        refresh_screen();
        return -1;
    }

   
        
    //
    //  File (stdout) 
    //        
    
    // Checando a validade do arquivo.
    // O arquivo da tty de origem da transferência.

    if ( (void *) tty->_rbuffer == NULL ){
        printf ("__tty_write: Invalid tty _buffer\n");
        refresh_screen();
        return -1;
    }


    //
    // _base
    //
    
    // Essa é a base do arquivo da tty de origem.

    if ( (void *) tty->_rbuffer->_base == NULL ){
        printf ("__tty_write: * invalid _base \n");
        refresh_screen();
        return -1;
    }


    //
    // Copy 1.
    //

    // Copiando do buffer para o arquivo da tty de origem.

    //printf ("__tty_write: Copiando para tty->_buffer->_base \n");
    //refresh_screen();

    
    if ( nr > tty->_rbuffer->_lbfsize )
    {
        //#debug
        //panic("__tty_write: FAIL\n");
        
        printk("__tty_write: [FAIL] buffer overflow\n");
        refresh_screen();
        
        return 0; //escreveu '0' bytes.
    }

    // Estamos escrevendo no inicio da tty.
    // manteremos os offsets na base.
    
    tty->_rbuffer->_r = 0;
    
    // proximo para escreita.
    // mas essa rotina sempre vai escrever na base.
    tty->_rbuffer->_w = nr; 
    
    // quanto falta pra acabar.
    tty->_rbuffer->_cnt = ( tty->_rbuffer->_lbfsize - nr );

    memcpy ( 
        (void *) tty->_rbuffer->_base, 
        (const void *) buffer, 
        nr ); 

    //#debug
    //printf ( "debug_write >>>%s \n", tty->_buffer->_base );
    //refresh_screen ();

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


    //#debug
    //printf ("__tty_write: PID  %d\n", __p->pid);
    //printf ("__tty_write: PPID %d\n", __p->ppid);
    //refresh_screen();


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
    

   /*
    unsigned long message_address[8];

    message_address[0] = (unsigned long) 0; //w
    message_address[1] = (unsigned long) 444;   // alerta que tem que ler na ttyList[] do processo indicado.
    //message_address[2] = (unsigned long) __p->pid;
    //message_address[3] = (unsigned long) __p->pid;

    message_address[2] = (unsigned long) 0;
    message_address[3] = (unsigned long) 0;

    // Send
    ipc_send_message_to_process ( 
        (unsigned long) &message_address[0], 
        (int) PPID );
   */
    
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

    
    if ( target_pid<0 ){
        debug_print ("tty_send_message: target_pid\n");
        return -1;
    }

    // The process structure.

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


    // #todo 
    // Check validation.


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

    if ( (void *) tty->_rbuffer == NULL ){
        printf ("__tty_write: Invalid tty _buffer\n");
        refresh_screen();
        return -1;
    }


    //
    // _base
    //
    
    // Essa é a base do arquivo da tty de origem.

    if ( (void *) tty->_rbuffer->_base == NULL ){
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

    memcpy ( (void *) tty->_rbuffer->_base, (const void *) buffer, nr ); 
    
    

    //#debug
    printf ( "debug_write >>>%s \n", tty->_rbuffer->_base );
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


    // Send
    ipc_send_message_to_process ( 
        (unsigned long) &message_address[0], 
        (int) __p->pid );


    // #bugbug
    // Não devemos copiar aqui, pois assim damos a chance
    // do processo pai escrever diretamente na tty do filho
    // caso ele obtenha sua identificação.


    //printf( "DONE\n");
    //refresh_screen(); 

    return nr;
}



/*
 *********************************
 * tty_read:
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

    //Limits
    if ( fd < 0 || fd > 32 ){
        printf ("tty_read: invalid fd\n");
        refresh_screen();
        return -1;
    }


    p = (struct process_d *) processList[fd];

    if ((void*) p == NULL){
        debug_print("tty_read: p\n");
        return -1;
    }

    // Pega o arquivo.
    f = (file *) p->Objects[fd];

    if ((void*) f == NULL){
        debug_print("tty_read: f\n");
        return -1;
    }
    
    
    if( f->____object != ObjectTypeTTY ){
        debug_print("tty_read: ____object\n");
        return -1;
    }

    //pega a tty representada pelo arquivo
    __tty = (struct tty_d *) f->tty;
    
    if ( (void*) __tty == NULL ){
        debug_print("tty_read: __tty\n");
        return -1;
    }

    // Read tty.

     return (int) __tty_read ( 
                      (struct tty_d *) __tty, 
                      (char *) buffer, 
                      (int) n );
}


// IN: fd = indice na lista de arquivos abertos pelo processo.
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

    //Limits
    if ( fd < 0 || fd > 32 ){
        printf ("tty_write: invalid fd\n");
        refresh_screen();
        return -1;
    }


    p = (struct process_d *) processList[fd];

    if ((void*) p == NULL){
        debug_print("tty_write: p\n");
        return -1;
    }

    // Pega o arquivo.
    f = (file *) p->Objects[fd];

    if ((void*) f == NULL){
        debug_print("tty_write: f\n");
        return -1;
    }
    
    
    if( f->____object != ObjectTypeTTY ){
        debug_print("tty_write: ____object\n");
        return -1;
    }

    //pega a tty representada pelo arquivo
    __tty = (struct tty_d *) f->tty;
    
    if ( (void*) __tty == NULL ){
        debug_print("tty_write: __tty\n");
        return -1;
    }

    // Read tty.

    return (int) __tty_write ( (struct tty_d *) __tty, 
                     (char *) buffer, 
                     (int) n );
}



// #todo
// flush the output buffer to the current virtual console.
void tty_flush( struct tty_d *tty )
{
    // todo
    debug_print("tty_flush: [TODO]\n");
}


// Copia a estrutura de termios
// para o aplicativo em ring3 poder ler.
int 
tty_gets ( 
    struct tty_d *tty, 
    struct termios *termiosp )
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

    memcpy ( termiosp, &tty->termios, sizeof(struct termios) );

    return 0;
}



// Copia de ring3 para o kernel.
int 
tty_sets ( 
    struct tty_d *tty, 
    int options, 
    struct termios *termiosp )
{
    int ret = -1;


    if ( (void *) tty == NULL ){
        debug_print("tty_sets: [FAIL] tty\n");
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
            debug_print ("tty_sets: [FAIL] default\n");
            //ret = -EINVAL;
            ret = -1;
            break;
    };


    return (ret);
}



/*
 ******************************** 
 * tty_ioctl:
 * 
 */
 
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

    debug_print ("tty_ioctl: TODO\n");


    if (fd<0){
        debug_print ("tty_ioctl: fd\n");
        return -1;
    }


   // #todo
   // podemos checar novamente se realmente se trata de
   // um tty. Mas isso ja foi feito no wrapper sys_ioctl.
   

    //if (current_process < 0) 
        //return -1;

     
    p = ( struct process_d * ) processList[current_process];
    
    if ( (void *) p == NULL ){
        debug_print ("tty_ioctl: [FAIL] p\n");
        return -1;
    }


    // Object
    f = (file*) p->Objects[fd];
    
    if ( (void *) f == NULL ){
        debug_print ("tty_ioctl: [FAIL] f\n"); 
        return -1;
    }

    // Is it a tty object?
    if (f->____object != ObjectTypeTTY){
        debug_print ("tty_ioctl: [FAIL] Not a tty file\n");
        return -1;

    // Get tty struct!
    }else{
        tty = f->tty;
    };

    int xxxi=0;
    
    // The command!

    switch (request){

        // Get termios.
        case TCGETS:
            debug_print ("tty_ioctl: TCGETS\n");
            return (int) tty_gets ( tty, (struct termios *) arg );
            break;

        // Set termios.
        case TCSETS:
            debug_print ("tty_ioctl: TCSETS\n");
            return (int) tty_sets ( tty, 
                             TCSANOW, (struct termios *) arg );
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
             tty->_rbuffer->_w = 0;
             tty->_rbuffer->_r = 0;
             tty->_rbuffer->_p = tty->_rbuffer->_base; 
             tty->_rbuffer->_cnt = tty->_rbuffer->_lbfsize;
             for( xxxi=0; xxxi<BUFSIZ; xxxi++){ tty->_rbuffer->_p[xxxi] = 0; };
            break;
        
      
        default:
            debug_print ("tty_ioctl: [FAIL] default\n");
            return -1;
            break;
    };

    //fail.
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




void tty_stop (struct tty_d *tty){

    if ( (void *) tty == NULL ){
        debug_print("tty_stop: tty\n");
        return;
    }

    //se ela já está parada.
    if (tty->stopped == 1){
        //debug_print("tty_stop: already stopped\n");
        return;
    }

    tty->stopped = 1;
}


void tty_start (struct tty_d *tty){

    if ( (void *) tty == NULL ){
        debug_print("tty_start: tty\n");
        return;
    }

    //Se não está parada.
    if (tty->stopped == 0){
        //debug_print("tty_start: not stopped\n");
        return;
    }

    tty->stopped = 0;
}



/*
//linux-like
void tty_init_termios(struct tty_d *tty);
void tty_init_termios(struct tty_d *tty)
{
    tty_reset_termios(tty);
}
*/



/*
 //linux-like.
int tty_driver_install_tty (struct ttydrv_d *driver,struct tty_d *tty);
int tty_driver_install_tty (struct ttydrv_d *driver,struct tty_d *tty)
{
    // plug a tty to a ttydvr.
    // ttydvr->tty = tty;
    // ttydvr->ttys[i] = tty;
}
*/


/*
 **********************************************
 * tty_reset_termios: 
 *    Reset termios in a given tty.
 */

// See: ttydef.h

// #todo: use int as return.

void tty_reset_termios ( struct tty_d *tty )
{

    // #todo: Limits messages
    if ( (void *) tty == NULL ){
        debug_print("tty_reset_termios: tty\n");
        return;
    }

    // #check
    // Is it a valid termios structure pointer?

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
struct ttyldisc_d *ttyldisc_create (void){

    struct ttyldisc_d *__ttyldisc;


    __ttyldisc = (struct ttyldisc_d *) kmalloc ( sizeof(struct ttyldisc_d) );
    
    if ( (void *) __ttyldisc == NULL ){
        debug_print("ttyldisc_create: __ttyldisc\n");
        return NULL;
 
    }else{
        __ttyldisc->used = 1;
        __ttyldisc->magic = 1234;
        
        // ...
        
        // OK
        return (struct ttyldisc_d *) __ttyldisc;
    };

    // fail
    return (struct ttyldisc_d *) 0;
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




// #todo criar uma tty driver.  
struct ttydrv_d *ttydrv_create (void) {

    struct ttydrv_d *__ttydrv;


    debug_print ("ttydrv_create:\n");

    __ttydrv = (struct ttydrv_d *) kmalloc ( sizeof(struct ttydrv_d) );
    
    if ( (void *) __ttydrv == NULL ){
        debug_print ("ttydrv_create: __ttydrv\n");
        return NULL;

    }else{

        __ttydrv->used = 1;
        __ttydrv->magic = 1234;
        
        // ...

        return (struct ttydrv_d *) __ttydrv;
    };


    // fail
    return (struct ttydrv_d *) 0;
}



//#todo: deletar uma tty driver
int ttydrv_delete ( struct ttydrv_d *tty_driver ){


    debug_print ("ttydrv_delete:\n");

    // Nothing to do.
    if ( (void *) tty_driver == NULL ){
        debug_print ("ttydrv_delete: tty_driver\n");
        return -1;

    }else{
         
         //#bugbug: fast way
         //free (tty_driver);
         
         //reusar
         tty_driver->magic = 216;
         
         // ...
         
         // ok
         return 0;
    };

    // fail
    return -1;
}



// Return the pointer to a tty driver structure 
// given the device descriptor.

/*
struct ttydrv_d *get_tty_driver( int fd );
struct ttydrv_d *get_tty_driver( int fd )
{
    debug_print ("get_tty_driver: [TODO]\n");
    return (struct ttydrv_d *) 0;
}
*/


/*
//todo: open a tty device
int tty_open (file *f, struct inode_d *inode);
int tty_open (file *f, struct inode_d *inode)
{
    return -1;
}
*/


//OUT: tty pointer.
struct tty_d *file_tty (file *f)
{
    if ( (void *)f==NULL ){
        return (struct tty_d *) 0;
    }
    return (struct tty_d *) f->tty;
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
int initialize_tty_struct (struct tty_d *tty);
int initialize_tty_struct (struct tty_d *tty)
{
    return -1;
}
*/


/*
const char *tty_name( struct tty_d *tty );
const char *tty_name( struct tty_d *tty )
{
    if ( (void *) tty == NULL )
    {
        //return "NULL tty";
        return NULL;
    }

    return (const char *) tty->name;
}
*/


/*
const char *tty_driver_name( struct tty_d *tty);
const char *tty_driver_name( struct tty_d *tty)
{
    struct ttydrv_d *driver;
    
    if ( (void *) tty == NULL )
    {
        //return "NULL tty";
        return NULL;
    }
    
    driver = (struct ttydrv_d *) tty->driver;

    if ( (void *) driver == NULL )
    {
        //return "NULL tty driver";
        return NULL;
    }
    
   return (const char *) driver->name;
}
*/


/*
const char *tty_device_name( struct tty_d *tty);
const char *tty_device_name( struct tty_d *tty)
{
    struct device_d *device;

    if ( (void *) tty == NULL )
    {
        //return "NULL tty";
        return NULL;
    }
    
    device = (struct device_d *) tty->device;

    if ( (void *) device == NULL )
    {
        //return "NULL tty device";
        return NULL;
    }
    
   return (const char *) device->name;
}
*/


int tty_init_module (void)
{
    // Nothing for now!

    debug_print ("tty_init_module:\n");
    
    // ...
        
    return 0;
}


//
// End.
//




