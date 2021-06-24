


#include <kernel.h>  



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

    struct process_d * __p;


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
    
    __p = (struct process_d *) processList[current_process];
    

    if ( (void *) __p == NULL ){
        panic("__tty_write: __p\n");
    }


    if ( __p->used != 1 || __p->magic != 1234 ){
        panic("__tty_write: validation\n");
    }


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













