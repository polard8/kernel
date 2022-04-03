
// sys.c

#include <kernel.h> 


// helper
// dado o fd, pegamos o ponteiro 
// para estrutura de arquivo na lista de
// objetos abertos no processo atual.
// ## Talvez essa rotina ja foi implementada
// em algum outro lugar.
// Prototype in rtl/sci/sys.h
file *get_file_from_fd(int fd)
{
    struct process_d *p;  // current process
    file *f;              // object

    pid_t current_pid = (pid_t) get_current_process();

    if( current_pid < 0 ||
        current_pid >= PROCESS_COUNT_MAX )
    {
        // msg
        return NULL;
    }

    p = (struct process_d *) processList[current_pid];

    if( (void*) p == NULL )
    {
        debug_print ("get_file_from_fd: p\n");
        panic       ("get_file_from_fd: p\n");
        //return NULL;
    }
    
    if(p->used != TRUE)
    {
        //msg
        return NULL;
    }

    if(p->magic != 1234)
    {
        //msg
        return NULL;
    }
    

    if (fd < 0 ||
        fd >= 32)
    {
        //msg
        return NULL;
    }

    f = (file *) p->Objects[fd];

    if( (void*) f == NULL )
    {
        //#debug
        printf("fd{%d} pid{%d}\n",fd,current_pid);
        //printf("entry0: %x\n", p->Objects[0]);
        //printf("entry1: %x\n", p->Objects[1]);
        //printf("entry2: %x\n", p->Objects[2]);
        //printf("entry3: %x\n", p->Objects[3]);
        //printf("entry4: %x\n", p->Objects[4]);
    }

    return (file *) f;
}


// See:
// unistd.h
// https://man7.org/linux/man-pages/man2/alarm.2.html
// alarm() returns the number of seconds remaining until any
//       previously scheduled alarm was due to be delivered, or zero if
//       there was no previously scheduled alarm.

unsigned long sys_alarm(unsigned long seconds)
{
    struct thread_d *t;
    unsigned long old=0;
    unsigned long seconds_remaining=0;

    unsigned long extra_ms=0;


    if (current_thread<0 || current_thread > THREAD_COUNT_MAX )
        return 0;
 
    t = (struct thread_d *) threadList[current_thread];

    if ( t->used != TRUE || t->magic != 1234 )
        return 0;


// Get the previous alarm.

    old = (unsigned long ) t->alarm;

// alarm() returns zero if
// there was no previously scheduled alarm.

    if (old<=0){
        // Zero seconds remaining.
        return 0;
    }

// Não ha o que fazer.
// O alarme que temos ja expirou.
// É trabalho do scheduler tratar ele.
// Não vamos chamar o scheduler durante uma syscall. 

    if (old < jiffies){
        // Zero seconds remaining.
        return 0;
    }



// O alarme que temos ainda é válido.
// O pit interrompe a 1000 ticks por segundo.
// Ex: 
// ( 8000-4000 )/1000 
// (4000/1000) 
// 4 segundos faltando.

    if (old > jiffies){
        seconds_remaining = (unsigned long) ((old - jiffies) / 1000);
    }


//
// Update.
//

// Update the thread info.

    if ( seconds == 0 ){
        extra_ms = (unsigned long) 0;
    }

    if ( seconds > 0 ){
        extra_ms = (unsigned long) (seconds*1000);
    }

    t->alarm = (unsigned long) ( jiffies + extra_ms ); 


// alarm() returns the number of seconds remaining until any
// previously scheduled alarm was due to be delivered.

    return (unsigned long) seconds_remaining;
}


// 250
// See: system.c
unsigned long sys_get_system_metrics ( int n )
{
    return (unsigned long) systemGetSystemMetrics ( (int) n );
}


// Only ring3 for now.
// OUT: ?
void *sys_create_process ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long res1,          //nothing
    unsigned long priority, 
    int ppid, 
    char *name,
    unsigned long iopl ) 
{
    struct process_d *new;

    char NewName[32];

//
// Not tested
//

    debug_print("sys_create_process: [TODO]\n");
    printf     ("sys_create_process: [TODO]\n");
    refresh_screen();
    //return NULL;

    // ==============

    struct thread_d *CurrentThread;

    CurrentThread = (struct thread_d *) threadList[current_thread];
    
    // No switch yet.
    if ((void*)CurrentThread==NULL){
        return NULL;
    }


    // Create a ring0 copy of the name.
    strncpy(NewName,name,16);
    NewName[16]=0;  //finalize


// Old pml4.

    unsigned long old_pml4=0;
    old_pml4 = CurrentThread->pml4_PA;  //save

    // Switch
    x64_load_pml4_table( kernel_mm_data.pml4_pa );

    // VA
    void *pml4_va = (void *) CloneKernelPML4();
    if ( pml4_va == 0 ){
        panic ("sys_create_process: pml4_va\n");
        //goto fail;
    }

    // PA
    unsigned long pml4_pa=0;
    pml4_pa = (unsigned long) virtual_to_physical ( 
                                  pml4_va, gKernelPML4Address );
    if ( pml4_pa == 0 ){
        panic ("sys_create_process: pml4_pa\n");
        //goto fail;
    }

//
// Create process
//

    pid_t current_pid = (pid_t) get_current_process();

    if(current_pid<0 || current_pid >= PROCESS_COUNT_MAX)
    {
        panic("sys_create_process: current_pid\n");
    }

    new = (void *) create_process ( 
                       NULL, NULL, NULL, 
                       (unsigned long) CONTROLTHREAD_BASE, //0x00200000 
                       PRIORITY_HIGH, 
                       (int) current_pid, 
                       (char *) NewName, 
                       RING3, 
                       (unsigned long ) pml4_va,
                       (unsigned long ) kernel_mm_data.pdpt0_va,
                       (unsigned long ) kernel_mm_data.pd0_va );

    if ((void*) new == NULL)
    {
        printf("sys_create_process: new\n");
        refresh_screen();
        goto fail;
    }

    printf("sys_create_process: done :)\n");
    refresh_screen();

    // Switch back
    x64_load_pml4_table( old_pml4 );

// done:

    return (void*) new;

// ==============

fail:
    printf("sys_create_process: fail\n");
    refresh_screen();

    // Switch back
    x64_load_pml4_table( old_pml4 );

    return NULL;
}


/*
 * sys_create_thread:
 *     Create thread system interface.
 */

// 72 - Create thread.
// #todo: 
// Enviar os argumentos via buffer.

void *sys_create_thread ( 
    struct room_d     *room,
    struct desktop_d  *desktop,
    struct window_d   *window,
    unsigned long init_rip, 
    unsigned long priority, 
    int ppid, 
    char *name )
{
    struct thread_d  *Thread;

    debug_print ("sys_create_thread:\n");

    // #todo:
    // Filtros, para ponteiros NULL.
    
    if ( init_rip == 0 ){
        debug_print ("sys_create_thread: [FAIL] init_rip\n");
        return NULL;
    }

    // Create thread.
    

// #todo
// Temos que checar o iopl do processo que chamou
// e a thread tem que estar no mesmo ring.

    int iopl = RING3;

    if ( ppid = WS_TID )
        iopl = RING0;

    // #bugbug #todo
    // Only ring3 for now.
    // We need to receive a parameter for that.
    
    Thread = (struct thread_d *) create_thread ( 
                                     room, desktop, window, 
                                     init_rip, 
                                     priority, 
                                     ppid, 
                                     name,
                                     iopl ); 

    if ( (void *) Thread == NULL ){
        debug_print ("sys_create_thread: [FAIL] Thread\n");
        return NULL;
    }

    Thread->saved = FALSE;

// #suspended:
// We have another syscall to put the thread in the standby state.

// Put the state in STANDBY.
    //SelectForExecution ( (struct thread_d *) Thread );

    return (struct thread_d *) Thread;
}



/*
 ************************************
 * sys_read:
 *     ring0 read() implementation.
 *     Called via syscall.
 */

// Service 18.
// #todo: There's a lot to do with synchronization.
// #todo
// We need to call one subfunctions for
// each different kind of file intead of implementing
// an internal sub-routine.
// #todo
// Isso deveria ser apenas um wrapper,
// chamando as rotinas apropriadas para cada tipo 
// de arquivo.
// OUT:
// 0 = Couldn't read.
// -1 = Error.

int 
sys_read (
    unsigned int fd, 
    char *ubuf, 
    int count )
{
    file *__file;

    struct socket_d   *s;
    int nbytes=0; 
    int ubuf_len=0;

    //debug_print("------------------------------------ R --\n");
    //debug_print("sys_read:\n");


// #bugbug
// O argumento é 'unsigned int'.
// Deveria ser int?

// fd
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_read: fd\n");
        printf     ("sys_read: fd\n");
        return (int) (-EINVAL);
    }

// buf
// todo: Checar a validade da região de memória.
    if ( (char *) ubuf == (char *) 0 ){
        debug_print ("sys_read: invalid ubuf address\n");
        printf      ("sys_read: invalid ubuf address\n"); 
        goto fail; 
    }

// count

    if ( count < 0 ){ 
        debug_print ("sys_read: count < 0\n");
        return -1;
        // return -EINVAL; 
    }

    if ( count == 0 ){ 
        debug_print ("sys_read: count 0\n");
        return 0; 
    }


// Size of the buffer.
    ubuf_len = strlen( (const char *) ubuf );

//Se a quantidade desejada é maior que o buffer disponível,
//temos um problema.
    if (count > ubuf_len){
        //debug_print ("sys_read: [FIXME] count too large\n");
    }

//Se o buffer disponível é maior que a quantidade desejada
//então não temos problemas, nem precisamos disso. 
    if (ubuf_len > count )
        ubuf_len = count;

    //#fixme
    if (ubuf_len > 512)
    {
        debug_print ("sys_read: [FIXME] limiting ubuf_len \n");
        //ubuf_len = 512;
    }


//
// File
//

// Get the object pointer.

    __file = (file *) get_file_from_fd(fd);

    if ( (void *) __file == NULL )
    {
        debug_print ("sys_read: __file not open\n");
        printf      ("sys_read: __file not open\n");
        goto fail; 
    }


    if ( __file->sync.can_read != TRUE )
    {
        debug_print ("sys_read: [PERMISSION] Can NOT read the file\n");
        printf      ("sys_read: [PERMISSION] Can NOT read the file\n");
        goto fail; 
    }

    /*
    // #todo
    // ainda nao inicializamos esse elemento.
    if( __file->is_readable == FALSE )
    {
        debug_print ("sys_read: Not readable\n");
        return -1;
    }
    */

    // #todo: Create thie element in the structure.
    // if( __file->is_directory == TRUE ){}


//==========================================================
// ::0
// stdin

    
    if ( __file->_file == 0 ){
        debug_print("sys_read: Reading from stdin\n");
        // Shortcut
        if ( __file->____object == ObjectTypeFile ){
            goto RegularFile;
        }
    }
    
//==========================================================
// ::1
// stdout

    if ( __file->_file == 1 ){
        debug_print("sys_read: Reading from stdout\n");
        // Shortcut
        if ( __file->____object == ObjectTypeFile ){
            goto RegularFile;
        }
    }

//==========================================================
// ::2
// stderr

    if ( __file->_file == 2 ){
        debug_print("sys_read: Reading from stderr\n");
        // Shortcut
        if ( __file->____object == ObjectTypeFile ){
            goto RegularFile;
        }
    }


//
// == Socket file ===========================================
//

// ==== Socket =======================
// Se o arquivo for um socket.
// #todo: 
// Now we can call socket_read(...)

    if ( __file->____object == ObjectTypeSocket )
    {
        // debug_print("sys_read: [DEBUG] Trying to read a socket object\n");
            
        // not reading yet
        if ((__file->_flags & __SRD) == 0) 
        {
            //debug_print("sys_read: [FAIL] flag __SRD \n");
            //yield (current_thread);
            goto fail;
        }

        nbytes = 0;

        // vazio? 
        // nao podemos ler.
        // acorda escritores e dorme.
        if (__file->socket_buffer_full == FALSE)
        { 
            debug_print("sys_read: [FAIL] can't read an empty buffer\n");
            //goto fail;
            
            debug_print("sys_read: WAKEUP WRITER\n");
            __file->_flags = 0;
            __file->_flags |= __SWR;                  // pode escrever
            do_thread_ready( __file->tid_waiting );   // acorda escritores. 
            __file->tid_waiting = -1;
            
                    // #bugbug
                    // Isso pode ser ruim pela natureza da chamada sys_read()
                    // que vem de uma syscall que nao salvou o contexto.
            
            if (__file->sync.block_on_read_empty == TRUE )
            {
                debug_print("sys_read: SLEEP READER\n");
                panic("sys_read: [DEBUG] Couldn't read socket. Buffer not full\n");

                __file->tid_waiting = current_thread;
                //do_thread_waiting (current_thread);
                yield (current_thread);
                goto fail;
            }
            yield (current_thread);
            goto fail;
        }

        // cheio? 
        // le e acorda escritores.
        if (__file->socket_buffer_full == TRUE)
        {
            if( __file->_flags & __SRD )
            {
                //debug_print ("sys_read: >>>> READ\n");
            
                // read!
                nbytes = (int) file_read_buffer ( 
                                   (file *) __file, 
                                   (char *) ubuf, 
                                   (int) count );
        
            if (nbytes <= 0){
                debug_print("sys_read: [FAIL] file_read_buffer fail when reading a socket \n");
                yield (current_thread);
                goto fail;
            }

            // ok
            if (nbytes > 0)
            {
                debug_print("sys_read: [DEBUG] lemos mais que 0 bytes em um socket.\n");
                __file->socket_buffer_full = FALSE;     // buffer vazio

                __file->_flags &= ~__SRD;  // nao posso mais LER.            
                __file->_flags |= __SWR;   // pode escrever também
                
                debug_print("sys_read: WAKEUP WRITER\n");
                do_thread_ready( __file->tid_waiting ); // acorda escritores.
                __file->tid_waiting = -1;
                debug_print("sys_read:done\n");
                
                return (int) nbytes;                    // bytes escritos.
            }
            }
        } 

        panic ("sys_read: [FAIL] Unexpected error when reading socket\n \n");
    }


//
// == Regular file ============================================
//

// ==== Regular file =======================
// Read a regular file.
// See: unistd.c
// #todo Tem que retornar a quantidade de bytes lido.
// #bugbug: Nem todos arquivos criados possuem essa flag configurada
// apropriadamente ...estamos fazendo isso.
// #hackhack
// We will open all the other kind of object
// with this IF right here.
// We need to fix it in the open() routines
// to give us the correct type.

RegularFile:

    if ( __file->____object == ObjectTypeFile )
    {

         //#debug
         //if( __file->_file == 5)
         //{
         //    if ( (__file->_flags & __SRD) == 0 )
         //        printf("cant read\n");
         //    if ( __file->_flags & __SRD )
         //        printf("can read\n");
         //    printf("sys_read-OUTPUT 5: %s \n",__file->_base);
         //    refresh_screen();
         //}

        //debug_print("sys_read: [DEBUG] Trying to read a regular file object\n");
        
        //Se não pode ler.
        if ( (__file->_flags & __SRD) == 0 )
        {
            //debug_print("sys_read: [FLAGS] Can't read!\n");
        
            //Não conseguimos ler.
            //nada de errado, apenas espera.
            //do_thread_waiting (current_thread);
            //__file->tid_waiting = current_thread;
            //__file->_flags |= __SWR;  //pode escrever.
            //scheduler();
            
            //printf("sys_read: __file->_flags & __SRD \n");
            //refresh_screen();
            
            goto fail;
        }
        
        nbytes = 0;

        // Se puder ler:
        // + Call a function to read a regular file.
        // + Sinalize that another process can write.
        // #todo: wake the one that was waiting to write.

        if ( __file->_flags & __SRD )
        {

            nbytes = (int) file_read_buffer ( 
                               (file *) __file, 
                               (char *) ubuf, 
                               (int) count );

            
            //#debug
            //if( __file->_file == 5)
            //{
            //    printf("nbytes %d\n",nbytes);
            //    refresh_screen();
            //}
 
            if(nbytes<=0)
            {
               //yield (current_thread);
               goto fail;
            }
            
            // Se conseguimos ler.
            if ( nbytes>0 )
            {

                //__file->_flags &= ~__SRD;  // nao posso mais LER.            
                //__file->_flags |= __SWR;   // pode escrever também

                // ok to write.
                __file->_flags |= __SWR;
                __file->sync.can_write = TRUE;
        
                // #test
                // Acordar quem esperava por esse evento
                //do_thread_ready( __file->tid_waiting );
                return (int) nbytes; 
            }
        
            //Não conseguimos ler.
            //nada de errado, apenas espera.
            //do_thread_waiting (current_thread);
            //__file->tid_waiting = current_thread;
            //__file->_flags |= __SWR;  //pode escrever.
            //scheduler();
            return 0;
        }

        // #todo
        // Do we need something here ?
        //return -1;
    }


// ========================================
// pseudo terminal multiplexer.

    if ( __file->____object == ObjectTypePTMX )
    {
        printk ("sys_read: [TODO] trying to read a PTMX device file\n");
        refresh_screen();
        return 0;
    }

// ========================================
// pty () pseudo terminal.

    if ( __file->____object == ObjectTypePTY )
    {
        printk ("sys_read: [TODO] trying to read a PTY device file\n");
        refresh_screen();
        return 0;
    }

// ========================================
// file system

    if ( __file->____object == ObjectTypeFileSystem )
    {
        printk ("sys_read: [TODO] trying to read a file system\n");
        refresh_screen();
        return 0;
    }

// ========================================
// See: pipe.c

    if ( __file->____object == ObjectTypePipe )
    {
        printk ("sys_read: [TODO] trying to read a pipe\n");
        return sys_read_pipe ( (int) fd, (char *) ubuf, (int) count ); 
    }

    // ...
    
    // ======================================================
    
    debug_print ("sys_read: [FAIL] Unknown object type\n");

// ==========================================

//
// Fail
//
    
// #bugbug
// See manual for the error:
// https://www.gnu.org/software/libc/manual/html_node/I_002fO-Primitives.html
// http://man7.org/linux/man-pages/man2/read.2.html

// A intenção é que um erro seja representado por -1 e não por 0.
// Zero representará fim de arquivo. 

fail:

    // #debug
    debug_print ("sys_read: [FAIL] something is wrong!\n");
    // printf      ("sys_read: [FAIL] something is wrong!\n");
    refresh_screen();

    //bloqueando, autorizando a escrita e reescalonando.
    //do_thread_waiting (current_thread);
    //__file->tid_waiting = current_thread;
    //__file->_flags |= __SWR;  //pode escrever      
    //scheduler();  //#bugbug: Isso é um teste  

    return (int) (-1); // fail !!! something is wrong!!!
}



/*
 ****************************
 * sys_write:
 *     Implemantation of write() for libc.
 */

// service 19.
// Copiar um buffer para um arquivo dado o descritor.
// Aqui devemos selecionar o dispositivo à escrever.
// See:
// https://github.com/zavg/linux-0.01/blob/master/fs/read_write.c
// https://linux.die.net/man/2/write
// ...
// #todo
// We need to call one subfunction for each different kind of file 
// intead of implementing an internal sub-routine.

// #todo
// Isso deveria ser apenas um wrapper,
// chamando as rotinas apropriadas para cada tipo 
// de arquivo.

// OUT:
// 0 = Couldn't read.
// -1 = Error.

int sys_write (unsigned int fd, char *ubuf, int count)
{

// #todo
// Copiar deve ser uma opcao e nao uma regra!
// Precisamos de uma flag para copyonwrite.
// atençao
// Podemos escrever num socket que nao eh o privado!!!
// existe a possibilidade de o processo atual estar 
// escrevendo em um socket que pertence a outro processo.
// mas que por causa da conexao possui o fd dele registrado
// em sua estrutura.
// Entao o fd passado por argumento nao precisa ser o mesmo
// do socket privado do processo. Pois poderemos estar
// escrevendo em outro socket que nao o privado.

    file *__file;

    struct socket_d  *s1;
    struct socket_d  *s2;
    int nbytes=0;
    int ubuf_len=0;
    size_t ncopy=0;

    //debug_print("------------------------------------ W --\n");
    //debug_print("sys_write: :)\n");


// fd
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_write: fd\n");
        printf     ("sys_write: fd\n");
        return (int) (-EINVAL);
    }

// ubuf
    if ( (char *) ubuf == (char *) 0 ){
        debug_print ("sys_write: invalid ubuf address\n");  goto fail;
    }

// count

    if ( count < 0 ){ 
        debug_print ("sys_write: count < 0\n");
        return -1; 
    }

    if ( count == 0 ){ 
        debug_print ("sys_write: count 0\n");
        return 0; 
    }

//
// Size of the buffer.
//

// len
    ubuf_len = strlen( (const char *) ubuf );

// Se a quantidade desejada é maior que o buffer disponível.
    if(count > ubuf_len){
        //debug_print("sys_write: [FIXME] count too long!\n");
    }

// se o buffer é maior que a quantidade desejada, 
// então não temos problemas
    if (ubuf_len > count ){
        ubuf_len = count;
        //debug_print ("sys_write: [FIXME] Ajusting ubuf_len\n");
    }

    // #debug: 
    // limits
    // Um socket tem o tamanho de BUFSIZ.
    
    if (ubuf_len > 512 )
    {
        ubuf_len = 512;
        debug_print ("sys_write: [FIXME] Ajusting ubuf_len to 512\n");
    }


//
// __file
//

// Get the object pointer from the list
// in the process structure.

    __file = (file *) get_file_from_fd(fd);
    
    if ( (void *) __file == NULL )
    {
        debug_print ("sys_write: __file not open\n");
        printf      ("sys_write: __file not open #hang\n");
        //printf      ("fd{%d} pid{%d}\n",fd,current_process);
        //printf("entry0: %x\n", __P->Objects[0]);
        //printf("entry1: %x\n", __P->Objects[1]);
        //printf("entry2: %x\n", __P->Objects[2]);
        //printf("entry3: %x\n", __P->Objects[3]);
        //printf("entry4: %x\n", __P->Objects[4]);
        //refresh_screen();
        //while(1){}
        goto fail;
    }

    //while (TRUE){
    //    if ( __file->sync.lock == FALSE ){ break; }
    //     yield (current_thread); 
    //};

    if ( __file->sync.can_write != TRUE )
    {
        debug_print ("sys_write: [PERMISSION] Can NOT write the file\n");
        printf      ("sys_write: [PERMISSION] Can NOT write the file\n");
        goto fail; 
    }

    /*
    // #todo
    // ainda nao inicializamos esse elemento.
    if( __file->is_writable == FALSE )
    {
        debug_print ("sys_write: Not writable\n");
        return -1;
    }
    */

    //#todo: Create thie element in the structure.
    //if( __file->is_directory == TRUE ){}


// =======================================================
// ::0
// stdin

    if ( __file->_file == 0 )
    {
        debug_print("sys_write: Writing into stdin\n");
        // If the file is a regular file.
        // Shortcut
        if ( __file->____object == ObjectTypeFile ){
            goto RegularFile;
        }
    }
    

// =======================================================
// ::1
// stdout

    if ( __file->_file == 1 )
    {
        debug_print("sys_write: Writing into stdout\n");
        
        // If the file is a console.
        if ( __file->____object == ObjectTypeVirtualConsole ){
            return (int) console_write ( 
                             (int) fg_console, 
                             (const void *) ubuf, 
                             (size_t) count );
        }
        // If the file is a regular file.
        // Shortcut
        if ( __file->____object == ObjectTypeFile ){
            goto RegularFile;
        }
    }

// =======================================================
// ::2
// stderr

    if ( __file->_file == 2 ){
        debug_print("sys_write: Writing into stderr\n");
        // Shortcut
        if ( __file->____object == ObjectTypeFile ){
            goto RegularFile;
        }
    }


//
// == Sockets ===============================================
//

    ncopy = count;
    
    // ==== Socket ===============================
    // Descobrindo o soquete que devemos copiar.
    // Se o arquivo é do tipo socket, então devemos
    // sabar onde está o buffer.
    // #todo: Talvez podemos chamar a função socket_write().
    // #todo: Lidar com a questao do copiar, pois
    // accept deve retornar o fd do cliente, para que o servidor
    // construa uma lista de clientes.
    // Entao copiar sera uma opçao, gerenciada por uma flag.
    
    // #bugbug
    // Nao podemos fazer a copia se os dois sockets 
    // estiverem com a conexao pendente.


    // #todo
    if ( __file->____object == ObjectTypeSocket )
    {
        //debug_print("sys_write: [DEBUG] Trying to write on a socket object \n");

        nbytes = 0;

        // #test
        // checking the synchronization struct
        //if( __file->sync.sender != current_process )
        //{
        //    printf("sys_write: sender %d current %d #debug\n",__file->sync.sender, current_process);
        //    refresh_screen();
        //    panic("sys_write: __file->sync.sender\n");
        //}

        // not writing yet
        if ((__file->_flags & __SWR) == 0) 
        {
            debug_print("sys_write: [FAIL] flag __SWR \n");
            //yield (current_thread);
            goto fail;
        }

        // cheio? 
        // Não podemos escrever porque o buffer está cheio.
        // Acorde os leitores para esvaziar.
        // Mas e se não tiver mais escritores.
        // #todo: Indicação da quantidade de escritores.
        // Sendo assim, vamos dizer que também podem ler
        // caso existam leitores. Mas não pode mais escrever.
        if ( __file->socket_buffer_full == TRUE )
        {
            debug_print("sys_write: [FAIL] can't write on a full buffer\n");

            debug_print("sys_write: WAKEUP READER\n");
            __file->_flags = 0; // não pode mais escrever.
            __file->_flags |= __SRD;                 // pode ler.
            do_thread_ready( __file->tid_waiting );  // acorda leitores
            __file->tid_waiting = -1;

            if ( __file->sync.block_on_write_full == TRUE )
            {
                 debug_print("sys_write: SLEEP WRITER\n");
                 __file->tid_waiting = current_thread;
                 //do_thread_waiting(current_thread);
                 yield (current_thread);
                 goto fail;
            }
            yield (current_thread); 
            goto fail;
        }

        // Se o buffer não estiver cheio,
        // Então escreva e acorde os leitores.
        if ( __file->socket_buffer_full == FALSE )
        {
            // Se podemos escrever.
            if( __file->_flags & __SWR )
            {
                //debug_print ("sys_write: >>>> WRITE\n");
                __file->_flags = 0;
            
                // Write in the socket buffer.
                nbytes = (int) file_write_buffer ( 
                                   (file *) __file, 
                                   (char *) ubuf, 
                                   (int) count );

                // fail
                if (nbytes <= 0){
                    debug_print("sys_write: [FAIL] file_write_buffer couldn't write on socket \n");
                    yield (current_thread);
                    goto fail;
                }

                // ok, write funcionou.
                if (nbytes>0)
                {
                    debug_print("sys_write: WAKEUP READER\n");
                    __file->socket_buffer_full = TRUE;       // buffer cheio
                    __file->_flags &= ~__SWR;                // nao posso mais ESCREVER.            
                    __file->_flags |= __SRD;                 // pode ler 
                    do_thread_ready( __file->tid_waiting );  // acorda leitores
                    __file->tid_waiting = -1;
                
                    // #bugbug
                    // Isso pode ser ruim pela natureza da chamada sys_write()
                    // que vem de uma syscall que nao salvou o contexto.
                    
                    if ( __file->sync.block_on_write == TRUE )
                    {
                        debug_print("sys_write: SLEEP WRITER\n");
                        __file->tid_waiting = current_thread;
                        //do_thread_waiting(current_thread);
                    }
                    
                    // #bugbug: test ...
                    //  impedir que eu mesmo me leia.
                    //yield (current_thread);
                    
                    return nbytes;                           // bytes written
                }
            }
        }

        panic("sys_write: [FAIL] unexpected error when writing on socket.\n");
    }


//
// Arquivos normais (regular)
//

RegularFile:

    // == Regular file =========================================


    // Tem que retonar o tanto de bytes escritos.
    // Escreve em uma stream uma certa quantidade de chars.

    if ( __file->____object == ObjectTypeFile )
    {
        //debug_print("sys_write: [DEBUG] Trying to write on a regular file object \n");

        //can't write!
        if ( (__file->_flags & __SWR) == 0)
        {
             debug_print("sys_write: [FLAGS] Can't write!\n");
             // Não conseguimos escrever ... 
             // nada de errado, apenas esperaremos.
             //do_thread_waiting (current_thread);
             //__file->tid_waiting = current_thread;
             //__file->_flags |= __SWR;  //pode escrever.
             //scheduler();
             return 0;
        }

        //#todo: ainda não colocamos essa flag na criação do arquivo.
        if (__file->_flags & __SWR)
        {
            // Regular file.
            nbytes = (int) file_write_buffer ( 
                               (file *) __file, 
                               (char *) ubuf, 
                               (int) count );

            // Avisa que o arquivo não está mais no modo escrita,
            // que agora pode ler.

            // Adiciona o bit que permite a leitura.
            // Assim o servidor pode ler o request.
            // #todo: wait on write.
            // #bugbug:
            // A questão é que se o cliente está esperando por resposta,
            // então ele lerá também.
            // Atualizamos a flag e acordamos quem esperava pelo evento.

            if (nbytes>0)
            { 
                __file->_flags = __SRD;
                __file->sync.can_read = TRUE;
                do_thread_ready( __file->tid_waiting );
                return (int) nbytes;
            }

            //suspenso.
            // Não conseguimos escrever ... 
            // nada de errado, apenas esperaremos.
            //do_thread_waiting (current_thread);
            //__file->tid_waiting = current_thread;
            //__file->_flags |= __SWR;  //pode escrever.
            //scheduler();
        
            debug_print ("sys_write: [FAIL] file_write_buffer fail!\n");
            return 0;
        }
 
        debug_print ("sys_write: [FAIL] Something is wrong!\n");
        
        return -1;
    } //regular file.



// ======================================================

    //pseudo terminal multiplexer.
    if ( __file->____object == ObjectTypePTMX )
    {
        printk ("sys_write: [TODO] trying to write a PTMX device file\n");
        refresh_screen();
        return 0;
    }

// ======================================================

    // pty () pseudo terminal.
    if ( __file->____object == ObjectTypePTY )
    {
        printk ("sys_write: [TODO] trying to write a PTY device file\n");
        refresh_screen();
        return 0;
    }

// ======================================================

// ======================================================

    // file system
    if ( __file->____object == ObjectTypeFileSystem )
    {
        printk ("sys_write: [TODO] trying to write a file system\n");
        refresh_screen();
        return 0;
    }

// ======================================================
    
    // See: pipe.c
    if ( __file->____object == ObjectTypePipe )
    {
        printk ("sys_write: [TODO] trying to write a pipe\n");
        return sys_write_pipe ( (int) fd, (char *)ubuf, (int) count ); 
    }

    // ...

//==============================================
    debug_print ("sys_write: [FAIL] Unknown object type!\n");
//==============================================

fail:
    // #debug
    debug_print ("sys_write: [FAIL] Something is wrong!\n");
    // printf      ("sys_write: [FAIL] something is wrong!\n");
fail2:
    //invalidate_screen();
    refresh_screen();
    // Não conseguimos escrever ... 
    // Estamos com problemas 
    //do_thread_waiting (current_thread);
    //__file->tid_waiting = current_thread;
    //__file->_flags |= __SWR;  //pode escrever.
    //scheduler();
    return (int) (-1);  // fail. something is wrong!!!!
}



// File read.
// It's called by sys_read.
// Copia à partir do início do arquivo.

int file_read_buffer ( file *f, char *buffer, int len )
{
    char *p;
    int local_len=0;
    
    p = buffer;

    
// #test
    local_len = (int) (len & 0xFFFF);

//
// Parameters validation
//

// Check file
    if ( (void *) f == NULL ){
        printf ("file_read_buffer: file\n");
        goto fail;
    }

// Check buffer
    if ( (void *) p == NULL ){
        printf ("file_read_buffer: p\n");
        goto fail;
    }

// Chech len
    if ( local_len > BUFSIZ ){
        printf ("file_read_buffer: local_len > BUFSIZ\n");
        goto fail;
    }

//=======================================

    if ( f->used != TRUE || f->magic != 1234 )
    {
        printf ("file_read_buffer: [FAIL] f validation\n");
        goto fail;
    }

    /*
    // stdin
    if( f->_file == 0 )
    {
        if( f->_lbfsize != PROMPT_SIZE)
        {
           printf ("file_read_buffer: [FAIL] Wrong size for stdin _lbfsize\n");
           goto fail;
        }
    }
    */

//=======================================

//
// Copy!
//

// #todo
// nao podemos ler mais que o limite do arquivo.
// A próxima leitura precisa ser depois dessa.


// =================================
// Socket:
// Se o arquivo é um socket, então não concatenaremos escrita ou leitura.
    if ( f->____object == ObjectTypeSocket )
    {    
        memcpy ( (void *) buffer, (const void *) f->_base, local_len ); 
        // You also can write now.
        // But i can still read.
        f->_flags |= __SWR;
        return local_len;
    }

// =================================
// Pipe:
// Não concatenaremos
    if ( f->____object == ObjectTypePipe )
    {
        memcpy ( (void *) buffer, (const void *) f->_base, local_len ); 
        // You also can write now.
        // But i can still read.
        f->_flags |= __SWR;
        return local_len;
    }


// =================================
// Regular file, tty, iobuffer.
// Nesse caso a leitura tem que respeitar os offsets e limites.
    if ( f->____object == ObjectTypeFile ||
         f->____object == ObjectTypeTTY  ||
         f->____object == ObjectTypeIoBuffer)
    {

        // Se o buffer tem tamanho 0.
        if ( f->_lbfsize <= 0 ){
            printf ("file_read_buffer: _lbfsize is 0\n");
            goto fail;
        }

        // Se o tamanho do buffer for maior que o padrão.
        if ( f->_lbfsize > BUFSIZ ){
            printf ("file_read_buffer: _lbfsize\n");
            goto fail;
        }

        // ler no início do arquivo.
        if ( f->_r < 0 )
        {
            f->_r = 0;
            printf ("file_read_buffer: f->_r = 0\n");
            goto fail;
        }
        
        // nao leremos depois do fim do arquivo.
        if ( f->_r > f->_lbfsize )
        {
            //#debug: provisorio
            printf ("file_read_buffer: f->_r > f->_lbfsize\n");
            goto fail;

            debug_print("file_read_buffer: f->_r > f->_lbfsize\n");

            f->_r = f->_lbfsize;
            f->_w = f->_lbfsize;
            f->_p = (f->_base + f->_lbfsize);
            f->_cnt = 0;

            return EOF;
        }

        // Se o offset de leitura for maior que
        // o offset de escrita, então temos que esperar.
        // #bugbug: mas talvez isso não seja assim para pipe.
        if ( f->_r > f->_w )
        {

            printf ("file_read_buffer: f->_r > f->_w\n");
            goto fail;

            debug_print("file_read_buffer: f->_r > f->_w\n");
            
            f->_r = f->_w;
            
            //faremos o ajuste logo abaixo.
            //f->_p = (f->_base + f->_r);

            // You also can write now.
            // But i can still read.
            //f->_flags = __SWR;

            //return 0;
        }
    
        if (local_len <= 0 )
        {
            printf ("file_read_buffer: local_len <= 0 :)FIRST\n");
            goto fail;

            //f->_flags = __SWR;
            return -1;
        }
        
        // Se a quantidade que desejamos ler
        // é maior que o espaço que temos.
        if( local_len > f->_lbfsize )
        {

            printf ("file_read_buffer: local_len > f->_lbfsize\n");
            goto fail;

            //printf ("file_read_buffer: [FAIL] local_len limits\n");
            //goto fail;
        
            //#test #bugbug
            // leia tudo então. hahaha
            local_len = (f->_lbfsize - 1);
        }
 
 
        // Se o tanto que queremos ler é maior
        // que o que nos resta da buffer,
        // então vamos ler apenas o resto do buffer.
        
        // so podemos ler ate o limite de espaço que temos no buffer.
        if(local_len > f->_cnt)
        {
            //printf ("file_read_buffer: local_len > f->_cnt\n");
            //goto fail;

            local_len = f->_cnt;
        }
 
       int delta = (f->_w - f->_r);
                
        // nada para ler.
        // pois o ponteiro de escrita e o de leitura sao iguais,
        if( delta == 0 )
        {
            // 0 bytes lidos,
            return 0;
        }
 
        // #delta
        // Se o tanto que queremos ler
        // é maior que o tanto que foi efetivamente escrito,
        // então leremos somente o que foi escrito.
        
        // se a diferença entra o ponteiro de escrita e o ponteiro
        // de leitura for menor que a quantidade que queremos ler.
        
        // Se queremos ler mais do que foi escrito.
        // entao vamos ler apenas o que foi escrito.
        if ( local_len > delta )
        { 
            local_len = delta;
        }

        // Vamos ler daqui.
        // A partir do offset de leitura.
        f->_p = (f->_base + f->_r);


        // read
        
        //#debug
        if (local_len <= 0 )
        {
            printf ("file_read_buffer: local_len <= 0 SECOND\n");
            goto fail;

            //printf("local_len\n");
            //refresh_screen();
            return -1;
        }
        
        //---
        memcpy ( (void *) buffer, (const void *) f->_p, local_len ); 
        
        //atualizamos o ponteiro de escrita
        f->_p = (f->_p + local_len);

        // atualizamos o offset de escrita.
        f->_r = (f->_r + local_len);

        if ( f->_r > f->_w )
            f->_r = f->_w;

        // You also can write now.
        // But i can still read.
        f->_flags = __SWR;
        f->sync.can_write = TRUE;

        return (int) local_len;
    }


fail:
    refresh_screen ();
    return EOF;
}


/*
 * file_write_buffer: 
 *     Escreve no arquivo uma certa quantidade de caracteres de uma 
 *     dada string.
 */
// Escreve no arquivo uma certa quantidade de caracteres de uma dada string 
// It's called by sys_write.

int 
file_write_buffer ( 
    file *f, 
    char *string, 
    int len )
{
    char *p;

    p = string;

    debug_print ("file_write_buffer:\n");

    if ( (void *) f == NULL ){
        printf ("file_write_buffer: file\n");
        goto fail;
    }

    if ( (void *) p == NULL ){
        printf ("file_write_buffer: p\n");
        goto fail;
    }

// Tentando escrever mais do que cabe no arquivo.
    if ( len >= BUFSIZ ){
        printf ("file_write_buffer: len > BUFSIZ\n");
        goto fail;
    }


//
// Copy!
//

// Socket file.
// Se o arquivo é um socket, então não concatenaremos 
// escrita ou leitura.
    if ( f->____object == ObjectTypeSocket ){
        memcpy ( (void *) f->_base, (const void *) string, len ); 
        return len;
    }

// não concatenaremos
    if ( f->____object == ObjectTypePipe ){
        memcpy ( (void *) f->_base, (const void *) string, len ); 
        return len;
    }

// Normal file.
// Tem que atualizar o ponteiro para que o próximo
// write seja depois desse write.
// Para isso o ponteiro precisa estar no base quando
// o write for usado pela primeira vez.

// Mas se o write for usado num arquivo aberto com 
// open(), então o ponteiro deve estar no fim do arquivo.
// Isso não significa que está no fim do buffer.
// Nesse caso o aplicative deveria usar rewind() antes
// para ter um ponteiro de escrita adequado.


    if ( f->____object == ObjectTypeFile ||     // regular file
         f->____object == ObjectTypeTTY  ||     // tty
         f->____object == ObjectTypeIoBuffer )  // ??
    {
        // #bugbug
        // Temos que ter um limite aqui ... !!!
        // #todo
    
        // se o tamanho do buffer for maior que o padrao.
        if ( f->_lbfsize > BUFSIZ ){
            printf ("file_write_buffer: _lbfsize\n");
            goto fail;
        }
    
        if (f->_w < 0)
        {
            f->_p = f->_base;
            f->_w = 0;
            f->_r = 0;
            f->_cnt = f->_lbfsize;
            return EOF;
        }

        // Se o offset de escrita ultrapassa os limites.
        if( f->_w >= BUFSIZ )
        {
            //#bugbug
            debug_print("file_write_buffer: f->_w >= BUFSIZ\n");
            printf     ("file_write_buffer: f->_w >= BUFSIZ\n");
            
            f->_w = BUFSIZ; 
            f->_cnt = 0;

            return EOF;
        }
        
        //if ( f->_w 
    
        // recalculando quanto espaço temos.
        //f->_cnt = (f->_lbfsize - f->_w);
    
        // Se a quantidade que temos ultrapassa os limites.
        
        // fim do arquivo.
        if( f->_cnt < 0)
        {
            f->_cnt = 0;
            f->_w = f->_lbfsize;
            f->_r = f->_lbfsize;
            f->_p = (f->_base + f->_w);
            return EOF;
        }
        
        // inicio do arquivo
        if( f->_cnt > f->_lbfsize )
        {
            printf ("file_write_buffer: _cnt\n");
            
            f->_cnt = f->_lbfsize;
            f->_p = f->_base; 
            f->_w = 0;
            f->_r = 0;
        }

        if( len < 0 )
            return -1;

        // Se o que desejamos escrever é maior que o espaço que temos.
        if( len > f->_cnt )
        {
            // Estamos no fim do arquivo
            if ( f->_cnt <= 0 )
            {
                f->_w = f->_lbfsize;
                f->_r = f->_lbfsize;
                f->_p = f->_base + f->_lbfsize;
                f->_cnt = 0; 
                return -1;
            }
            
            // Só podemos escrever esse tanto.
            if ( f->_cnt > 0 )
            {
                len = f->_cnt; 
            }
        }

        // write.
        // Se o offset de escrita é menor que o offset de leitura.
        // Então adiantaremos o offset de escrita.
        // pois nao devemos tocar no offset de leitura.
        if (f->_w < f->_r)
        {
            f->_w = f->_r;
            f->_cnt = ( f->_lbfsize - f->_w );
        }

        // vamos escrever aqui.
        f->_p = (f->_base + f->_w);

        //escrevemos usando o ponteiro de escrita.
        memcpy ( (void *) f->_p, (const void *) string, len ); 
    
        //atualizamos o ponteiro de escrita
        f->_p = (f->_p + len);

        // atualizamos o offset de escrita.
        f->_w = (f->_w + len);
    
        //atualizamos o quanto nos falta.
        f->_cnt = (f->_cnt - len);
        
        // You can read now.
        f->_flags = __SRD;
        f->sync.can_read = TRUE;
        
        debug_print ("file_write_buffer: ok, done\n");
           
        // retornamos a quantidade escrita no buffer.
        return len;
    }
    
    // unknown type.
    
fail:
    //printf ("file_write_buffer: fail\n");
    refresh_screen ();
    return EOF;
}


/*
 *  sys_close:
 * 
 */

// Fechar um dos objetos abertos do processo atual.
// O descritor é um índice na sua tabela de objetos abertos.

// See:
// https://man7.org/linux/man-pages/man2/close.2.html
// https://pubs.opengroup.org/onlinepubs/009695399/functions/close.html

int sys_close (int fd)
{

    file *object;

    struct process_d *p;
    pid_t current_process = (pid_t) get_current_process();


    // ??
    // Can we close this devices?
    
    /*
    if (fd == 0 || fd == 1 || fd == 2 )
    {
        debug_print("sys_close: [FIXME] We can't close the standard stream\n");
        // WHY NOT ???!!
        return (int) (-1);
    }
    */

    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_close: fd\n");
        return (int) (-EINVAL);
    }

    // Process.

    // #todo: Check overflow.
    if ( current_process < 0 ){
        debug_print("sys_close: current_process\n");
        goto fail;
    }

    p = (void *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_close: p\n");
        goto fail;
    }

    if ( p->used != TRUE || p->magic != 1234 )
    {
        debug_print("sys_close: p validation\n");
        goto fail;
    }

    // object
    // The object is a file structure.

    object = (file *) p->Objects[fd];
        
    if ( (void *) object == NULL )
    {
        debug_print("sys_close: object\n");
        return (int) (-1);
    }

    if ( object->used != TRUE || object->magic != 1234 )
    {
        debug_print("sys_close: object validation\n");
        goto fail;
    }


    // What type of object?
    // socket, pipe, virtual console, tty, regular file ??
 
    // ===============================================
    // socket
    if ( object->____object == ObjectTypeSocket )
    {
        debug_print("sys_close: Trying to close a socket object\n");
        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }

    // ==============================================
    // pipe
    if ( object->____object == ObjectTypePipe )
    {
        debug_print("sys_close: Trying to close a pipe object\n");
        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }


    // ====================================================
    // virtual console.
    if ( object->____object == ObjectTypeVirtualConsole ){
        debug_print("sys_close: Trying to close a virtual console object\n");
        return 0;
    }
 
    // =====================================================
    // tty
    if ( object->____object == ObjectTypeTTY )
    {
        debug_print("sys_close: Trying to close a tty object\n");
        object = NULL;
        p->Objects[fd] = (unsigned long) 0;
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }

    // #bugbug
    // Poderemos ter problemas aqui com os diversos tipos
    // de arquivos.

    // #bugbug
    // ugly test

    // ===========================================
    // regular file
    if ( object->____object == ObjectTypeFile )
    {
        debug_print("sys_close: [FIXME] trying to close a regular file\n");
        debug_print("sys_close: [FIXME] fsSaveFile\n");
                
        // #fixme: buffer limit
        if (object->_lbfsize < 512)
        {  
            debug_print("sys_close: [FIXME] Ajusting file size\n");
            object->_lbfsize = 512; 
        }

        // Save file in the root dir.
        // #bugbug: Where to save?

        fsSaveFile ( 
            VOLUME1_FAT_ADDRESS, 
            VOLUME1_ROOTDIR_ADDRESS, 
            FAT16_ROOT_ENTRIES,
            (char *)         object->_tmpfname, 
            (unsigned long) (object->_lbfsize/512),  // file_size, in sectors       
            (unsigned long)  object->_lbfsize,       // size_in_bytes,  
            (char *)         object->_base,          // buffer address          
            (char)           0x20 );                 // flag ??

        object = NULL;
        
        // ??
        p->Objects[fd] = (unsigned long) 0;
        
        debug_print("sys_close: [FIXME] Done\n");
        return 0;
    }

    //
    // Object type not supported.
    //
    
    debug_print("sys_close:[FAIL] Object type not supported yet \n");

fail:
    debug_print("sys_close: [FAIL] \n");
    return (int) (-1);
}

// Exit thread.
void sys_exit_thread (int tid)
{
    if ( tid < 0 ){
        //todo: message
        return;
    }

    exit_thread (tid);
}

int sys_fork (void)
{
    debug_print ("sys_fork: \n");
    return -1;
}


// #todo: 
// Rever esses argumentos.
// SVr4, 4.3BSD, POSIX.1-2001. and more.
// See: 
// https://man7.org/linux/man-pages/man2/fcntl.2.html

int sys_fcntl ( int fd, int cmd, unsigned long arg )
{
    debug_print ("sys_fcntl:\n");

// fd.
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_fcntl: fd\n");
        printf     ("sys_fcntl: fd\n");
        return (int) (-EINVAL);
    }

    if ( cmd < 0 ){
        debug_print ("sys_fcntl: cmd\n");
        return -1;
    }

//POSIX Table 6-1.
//See: fcntl.h
    switch (cmd){

    //duplicate file descriptor
    case F_DUPFD:
        debug_print ("sys_fcntl: [TODO] F_DUPFD\n");
        return -1;
        break;

    //get file descriptor flags
    case F_GETFD:
        debug_print ("sys_fcntl: [TODO] F_GETFD\n");
        return -1;
        break;

    //set file descriptor flags
    case F_SETFD:
         debug_print ("sys_fcntl: [TODO] F_SETFD\n");
         return -1;
         break;

    //get file status flags
    case F_GETFL:
        debug_print ("sys_fcntl: [TODO] F_GETFL\n");
        return -1;
        break;

    //set file status flags
    case F_SETFL:
        debug_print ("sys_fcntl: [TODO] F_SETFL\n");
        return -1;
        break;

    //get record locking information
    case F_GETLK:
        debug_print ("sys_fcntl: [TODO] F_GETLK\n");
        return -1;
        break;

    // set record locking information
    case F_SETLK:
        debug_print ("sys_fcntl: [TODO] F_SETLK\n");
        return -1;
        break;

    //set record locking info; wait if blocked
    case F_SETLKW:
        debug_print ("sys_fcntl: [TODO] F_SETLKW\n");
        return -1;
        break;

    //free a section of a regular file
    case F_FREESP:
        debug_print ("sys_fcntl: [TODO] F_FREESP\n");
        return -1;
        break;

    // ...

    default:
        debug_print ("sys_fcntl: default command\n");
        break;
    };

    debug_print ("sys_fcntl: FAIL\n");
    return -1; //#todo
}


// 178
// Only root dir.
//#todo: unsigned long sys_get_file_size ( char *path, unsigned long dir_address )
unsigned long sys_get_file_size ( char *path )
{
    unsigned long Size=0;


    if ( (void*) path == NULL ){
        debug_print("sys_get_file_size: [FAIL] path\n");
        return 0;
    }

    if ( *path == 0 ){
        debug_print("sys_get_file_size: [FAIL] *path\n");
        return 0;
    }


    //taskswitch_lock();
    //scheduler_lock();


    Size = (unsigned long) fsGetFileSize ( 
                               (unsigned char *) path, 
                               (unsigned long) VOLUME1_ROOTDIR_ADDRESS ); 
    
    //scheduler_unlock();
    //taskswitch_unlock();
    
    return (unsigned long) Size; 
}

// #todo
// Comment the purpose of this routine.
// It is used on socket communication.

int sys_get_file_sync (int fd, int request)
{
	
	// #deprecated


    struct process_d  *p;
    file *object;


    pid_t current_process = (pid_t) get_current_process();
    
    //#bugbug
    // Pensaremos nessa possibilidade.

    /*
    if (fd == 0 || fd == 1 || fd == 2 )
    {
        debug_print("sys_close: [FIXME] We can't close the standard stream\n");
        // WHY NOT ???!!
        return (int) (-1);
    }
    */

    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_get_file_sync: [FAIL] fd\n");
        return (int) (-1);
    }

    // == Process ================

    if ( current_process < 0 ){
        debug_print("sys_get_file_sync: current_process\n");
        return (int) (-1);
    }

    p = (void *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_get_file_sync: p\n");
        return (int) (-1);
    }

    // #todo
    // check validation

    // object
        
    object = (file *) p->Objects[fd];

    if ( (void*) object == NULL ){
        debug_print("sys_get_file_sync: [FAIL] object\n");
        return (int) (-1);
    }

    if ( object->used != TRUE || object->magic != 1234 )
    {
        debug_print("sys_get_file_sync: validation\n");
        return (int) (-1);
    }


    switch (request){

    // get last action
    case SYNC_REQUEST_GET_ACTION:
        return (int) object->sync.action;
        break;

    //case ?:
        //break;

    // ...
        
    default:
        debug_print("sys_get_file_sync: [FAIL] Default request\n");
        return (int) (-1);
        break;
    };

    // ...
    return 0;
}




// 10002
void sys_set_global_sync(int sync_id, int request, int data)
{
    struct kstdio_sync_d *s;
    
    s = (struct kstdio_sync_d *) syncList[sync_id];
    
    if( request == SYNC_REQUEST_SET_ACTION )
        s->action = data;
}


// 10003 
int sys_get_global_sync (int sync_id, int request)
{ 
    struct kstdio_sync_d *s;
    
    s = (struct kstdio_sync_d *) syncList[sync_id];
    
    if( request == SYNC_REQUEST_GET_ACTION )
    {
        return (int) s->action;
    }

    return -1; 
}


// 10004
int sync_count=0;
static int __saved_sync_id=0;
int sys_create_new_sync(void)
{
    struct kstdio_sync_d *s;
    s = (struct kstdio_sync_d *) kmalloc( sizeof(struct kstdio_sync_d) );
    if( (void*) s == NULL )
        return -1;
    s->used=TRUE;
    s->magic=1234;
    s->action = ACTION_NULL;
    sync_count++;
    if( sync_count > 0 && 
        sync_count < SYNC_COUNT_MAX )
    {
        syncList[sync_count] = (unsigned long) s;
        __saved_sync_id = (int) sync_count;
        return (int) sync_count;
    }
    return -1;
}

//provisorio, para testes
int get_saved_sync(void)
{
    return (int) __saved_sync_id;
}






// 85 
// Get PID of the current process.
//#todo: change to 'pid_t'
int sys_getpid (void)
{
    return (pid_t) get_current_process();
}


// 81
// Get the PID of the father.
int sys_getppid (void)
{
    struct process_d *p;
    pid_t pid = -1;

    pid_t current_process = (pid_t) get_current_process();

    pid = (int) current_process;

    if ( pid >= 0 && pid < PROCESS_COUNT_MAX )
    {
        p = (void *) processList[pid];

        if ( (void *) p == NULL ){ return (int) -1; }

        if ( p->used != 1 || p->magic != 1234 ){ return (int) -1; }

        return (int) p->ppid;
    }

    return (int) (-1);
}


// Helper function to initialize system's component
// after kernel initialization.
//  This is called by ring3 apps.

int sys_initialize_component (int n)
{

    if(n<0)
        return -1;


    switch (n)
    {
        
        case 1:
            //PS2_early_initialization();
            //PS2_initialize();
            return 0;
            break;

        //case 2:
            //break;

        //case 3:
            //break;

        //case 4:
            //break;

        // ...

        default:
            return -1;
            break;
    };
    
    return (int) 0;
}


// Called by sc82 in sci.c
int sys_ioctl ( int fd, unsigned long request, unsigned long arg )
{
    int retvalue = (-1);

    debug_print ("sys_ioctl: [FIXME] \n");

    // fd.
    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_ioctl: fd\n");
        printf     ("sys_ioctl: fd\n");
        return (int) (-EINVAL);
    }

// Enquanto sys_ioctl eh chamada pelos applicativos,
// io_ioctl eh chamada pelas rotinas dentro do kernel.
// See: drivers/io.c

    retvalue = (int) io_ioctl(fd,request,arg);

    if( retvalue<0){
        printf("sys_ioctl: io_ioctl fail\n");
    }
    
    return retvalue;
}



//#??? isso não pertence à fcntl.c ?
//SVr4,  4.3BSD,  POSIX.1-2001. 

// Syscall 16.
// #bugbug
// Precisamos de um endereço em ring 3
// para que a libc possa manipular o buffer ?
// ou open deve ser usado somente com dispositivos ??
// #obs:
// vamos retornar o indice da tabela de arquivos abertos 
// do processo atual.

int 
sys_open (
    const char *pathname, 
    int flags, 
    mode_t mode )
{
    int _ret = -1;

// #todo:
// check arguments.

// ??
// creat chama open.
// open tenta ler num arquivo que nao existe?

    debug_print ("sys_open: $ \n");

// See: fs.c
// OUT: fd

    _ret = (int) sys_read_file_from_disk ( 
                     (char *) pathname, 
                     flags, 
                     mode );

    if (_ret<0){
        printf ("sys_open: fail\n");
        return -1;
    }

    return (int) _ret;
}



/*
 ************************************
 * sys_reboot:
 *     Reboot, Serviço do sistema.
 *     Chamando uma rotina interna de reboot do sistema.
 */


// The service 110.
// It's called by gde_serv.c.
// The higher level routine for reboot.
// It's a wrapper, an interface.

void sys_reboot (void)
{
    debug_print("sys_reboot:\n");

// FAT cache.
// This is the FAT cache for the system disk.
// The boot partition.

// Message
    if(fat_cache_saved == FAT_CACHE_NOT_SAVED)
    {
        debug_print("sys_reboot: FAT_CACHE_NOT_SAVED\n");
        debug_print("sys_reboot: Saving FAT cache\n");
        fs_save_fat(VOLUME1_FAT_ADDRESS,VOLUME1_FAT_LBA,246);
        fat_cache_saved = FAT_CACHE_SAVED;
    }

//
// Reboot
//

    debug_print("sys_reboot: Rebooting...\n");
    hal_reboot();

    panic("sys_reboot:");
}

// 289
// See: sm/debug/debug.c
int sys_serial_debug_printk ( char *s )
{
    //#todo
    //if ( (void *) s == NULL )
        //return -1;
        
    debug_print ( (char *) s );
    return 0;
}

// #todo
// Comment the purpose of this routine.
// It is used on socket communication.

void sys_set_file_sync(int fd, int request, int data)
{

    //
    // #deprecated
    //

    struct process_d  *p;
    file *object;


    pid_t current_process = (pid_t) get_current_process();
    
    //#bugbug
    // Pensaremos nessa possibilidade.
    
    /*
    if (fd == 0 || fd == 1 || fd == 2 )
    {
        debug_print("sys_close: [FIXME] We can't close the standard stream\n");
        // WHY NOT ???!!
        return (int) (-1);
    }
    */

    if ( fd < 0 || fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_set_file_sync: [FAIL] fd\n");
        return;
    }

    // == Process ================

    if ( current_process < 0 ){
        debug_print("sys_set_file_sync: [FAIL] current_process\n");
        return;
    }

    p = (void *) processList[current_process];

    if ( (void *) p == NULL )
    {
        debug_print("sys_set_file_sync:  [FAIL] p\n");
        return;
    }

    // #todo
    // check validation

// object

    object = (file *) p->Objects[fd];

    if ( (void*) object == NULL )
    {
        debug_print("sys_set_file_sync: [FAIL] object\n");
        return;
    }

    if ( object->used != TRUE || object->magic != 1234 )
    {
        debug_print("sys_set_file_sync: validation\n");
        return;
    }

// request.

    switch (request){

    // set last action
    case SYNC_REQUEST_SET_ACTION:
        object->sync.action = data;
        break;
        
    // #test
    // reset
    // Now we can write
    case 216:
        
        //#debug
        printf("216:\n"); 
        refresh_screen();
        
        object->sync.action = 0;
        //object->_flags = (__SWR | __SRD); 
        object->_flags = __SWR;
        k_rewind(object);
        object->_r = 0;
        object->_w = 0;
        object->socket_buffer_full = FALSE; //empty buffer
        break;

    // #test
    // Now we can read
    case 217:

        //#debug
        printf("217:\n"); 
        refresh_screen();

        object->sync.action = 0;
        //object->_flags = (__SWR | __SRD); 
        object->_flags = __SRD;
        break;

    // ...
        
    default:
        debug_print("sys_set_file_sync: [FAIL] Default request\n");
        return;
        break;
    };

    // ...
}


/*
 * sys_shutdown:
 *     Chama uma rotina interna para desligar a máquina.
 */

void sys_shutdown (void)
{
    debug_print("sys_shutdown: [TODO]\n");
    //hal_shutdown();
}


// Usada por vários serviços de debug.
// Usada para debug.

void sys_show_system_info ( int n )
{
    if (n<0){
        debug_print("sys_show_system_info: [FAIL] n\n");
        return;
    }


    switch (n){
    case 1:  
        disk_show_info();        
        break;
    case 2:  
        volume_show_info();      
        break;
    case 3:  
        //memoryShowMemoryInfo();  
        break;
    case 4:
        //systemShowDevicesInfo();
        //pciInfo();
        break;
    case 5:  
        //KiInformation(); 
        break;
    // See: detect.c
    case 6:
        //show_cpu_info();
        break;
    // ...
    };

    refresh_screen();
}


// IN: fd
// OUT: 
// -1= error; 
// FALSE= nao pode ler; 
// TRUE= pode ler.

int sys_sleep_if_socket_is_empty ( int fd )
{
    struct process_d *p;
    file *object;


    pid_t current_process = (pid_t) get_current_process();


    if ( fd < 0 || 
         fd >= NUMBER_OF_FILES )
    {
        debug_print("sys_sleep_if_socket_is_empty: fd\n");
        return (int) (-1);
        //return -EINVAL;
    }

// #todo: max lim.

    if ( current_process < 0 || current_process >= PROCESS_COUNT_MAX ){
        debug_print("sys_sleep_if_socket_is_empty: current_process\n");
        return (int) (-1);
    }

    // process
    
    p = (void *) processList[current_process];

    if ( (void *) p == NULL ){
        debug_print("sys_sleep_if_socket_is_empty: p\n");
        return (int) (-1);
    }else{
        
        object = (file *) p->Objects[fd];
        
        // validation
        if ( (void *) object == NULL ){
            debug_print("sys_sleep_if_socket_is_empty: object\n");
            return (int) (-1);
        }else{
            
            //validation
            if (object->used != 1 || object->magic != 1234 ){
                debug_print("sys_sleep_if_socket_is_empty: calidation\n");
                return -1;
            }
            
            if ( object->____object != ObjectTypeSocket )
            {
                debug_print ("sys_sleep_if_socket_is_empty: [ERROR] only for sockets\n");
                return -1;
            }
            
            // TRUE or FALSE
            //return (int) object->socket_buffer_full;   
        
           // sim esta vazio, nao pode ler;  retorna FALSE
           if( object->socket_buffer_full == FALSE )
           {
               debug_print("sys_sleep_if_socket_is_empty: Buffer is empty. we can not read. sleeping\n");
               object->_flags |= __SWR;                  // pode escrever
               //todo: falg que nege a leitura.
               object->tid_waiting = current_thread;     // thread atual dorme   
               //do_thread_waiting (current_thread);
               return FALSE;  // nao pode ler
           }
           
           // O buffer esta cheio, pode ler. retorna TRUE
           if( object->socket_buffer_full == TRUE )
           {
               debug_print("sys_sleep_if_socket_is_empty: Buffer is empty. we can read\n");
               object->_flags |= __SRD;
               return TRUE;
           }
        };
    };  
    
    debug_print ("sys_sleep_if_socket_is_empty: [FAIL] Unexpected error \n");
    return -1;
}


// service 377.
// IN: Imported pointe to utsname structure.
int sys_uname (struct utsname *ubuf)
{
    debug_print("sys_uname:\n");

    if ( (void *) ubuf == NULL )
    {
        debug_print("sys_uname: ubuf\n");
        return -EINVAL;
    }

// Copy
// #todo
// We gotta get these information from pointer,
// not from 'defines'

// ##
// For now we're using default definitions.
// See:
// gramado/utsname.h
// gramado/0config/u.h
// gramado/0config/version.h

    memcpy ( 
        (void *)  ubuf->sysname, 
        (const void *) OS_NAME, 
        sizeof(OS_NAME) );

    memcpy ( 
        (void *)  ubuf->nodename, 
        (const void *) NODE_NAME, 
        sizeof(NODE_NAME) );

    memcpy ( 
        (void *)  ubuf->release, 
        (const void *) RELEASE_NAME, 
        sizeof(RELEASE_NAME) );    

    memcpy ( 
        (void *)  ubuf->version, 
        (const void *) VERSION_NAME, 
        sizeof(VERSION_NAME) ); 

    memcpy ( 
        (void *)  ubuf->machine, 
        (const void *) MACHINE_NAME, 
        sizeof(MACHINE_NAME) );    

//done:
    debug_print("sys_uname: done\n");
    return 0;
}


// sys_vsync:
//     Sincroniza o retraço vertical do monitor.
// #bugbug: Slow
void sys_vsync(void)
{
    hal_vsync();
}


