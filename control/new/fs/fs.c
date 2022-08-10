
// fs.c

#include <kernel.h>


//see: fs.h
struct filesystem_d  *root;

//
// == Cluster list ===============================
//

// Lista de clusters.
// Isso permite salvar um arquivo com 32 mil clusters ??
// #todo: Em que momento essa lista foi inicializada??

// #bugbug: 
// This list has 32 KB size.

// #bugbug
// Checar se essa 'e a quantidade limite de 
// entradas que podemos acessar na fat.
// Ou e' apenas o limite da lista.

//#define CLUSTERS_TO_SAVE_MAX  (8*1024) //#bugbug
#define CLUSTERS_TO_SAVE_MAX  (32*1024)

unsigned short fat16ClustersToSave[CLUSTERS_TO_SAVE_MAX];

// ========================================

//
// == Private functions: Prototypes ===========
//

static int __check_address_validation( unsigned long address );

//=============================

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
// return 'ssize_t'?

ssize_t 
sys_read (
    int fd,
    char *ubuf,        //#todo: use 'void *'
    size_t count )        //#todo: use 'size_t'.
{
    file *__file;
    ssize_t nbytes=0;

    struct socket_d  *s;
    int ubuf_len=0;

// #bugbug
// O argumento é 'unsigned int'.
// Deveria ser int?

// fd
    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (ssize_t) (-EBADF);
    }

// buf
// todo: Checar a validade da região de memória.

    if ( (void *) ubuf == NULL ){
        return (ssize_t) (-EINVAL);
    }

// count
    if (count < 0){ 
        return (ssize_t) (-EINVAL);
    }

    // Nothing to do.
    if (count == 0){ 
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
                nbytes = (ssize_t) file_read_buffer ( 
                                       (file *) __file, 
                                       (char *) ubuf, 
                                       (int) count );
        
                if (nbytes <= 0)
                {
                    debug_print("sys_read: [FAIL] file_read_buffer fail when reading a socket \n");
                    //yield (current_thread);
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

                    return (ssize_t) nbytes;                    // bytes escritos.
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

            nbytes = (ssize_t) file_read_buffer ( 
                                   (file *) __file, 
                                   (char *) ubuf, 
                                   (int) count );
 
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
                
                return (ssize_t) nbytes; 
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
        return (ssize_t) sys_read_pipe ( (int) fd, (char *) ubuf, (int) count ); 
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
    
//#bugbug: Isso pode degradar o desempenho.
    // printf      ("sys_read: [FAIL] something is wrong!\n");
    //refresh_screen();  

    //bloqueando, autorizando a escrita e reescalonando.
    //do_thread_waiting (current_thread);
    //__file->tid_waiting = current_thread;
    //__file->_flags |= __SWR;  //pode escrever      
    //scheduler();  //#bugbug: Isso é um teste  

// Something is wrong!
    return (ssize_t) (-1);
}


/*
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

// OUT:
// 0 = Couldn't read.
// -1 = Error.

ssize_t sys_write (int fd, char *ubuf, size_t count)
{
    file *__file;
    ssize_t nbytes=0;

    struct socket_d  *s1;
    struct socket_d  *s2;

    int ubuf_len=0;
    size_t ncopy=0;

    //debug_print("------------------------------------ W --\n");
    //debug_print("sys_write: :)\n");


// fd
    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (ssize_t) (-EBADF);
    }

// ubuf
    if ( (void *) ubuf == NULL ){
        return (ssize_t) (-EINVAL);
    }

// count
    if ( count < 0 ){ 
        return (ssize_t) (-EINVAL);
    }

    // Nothing to do.
    if ( count == 0 ){ 
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
// + Write on regular file.

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
// + Write on console.
// + Write on regular file.

    if ( __file->_file == 1 )
    {
        debug_print("sys_write: Writing into stdout\n");
        
        // If the file is a console.
        if ( __file->____object == ObjectTypeVirtualConsole )
        {
            return (int) console_write ( 
                             (int) fg_console, 
                             (const void *) ubuf, 
                             (size_t) count );
        }
        // If the file is a regular file.
        // Shortcut
        if ( __file->____object == ObjectTypeFile )
        {
            goto RegularFile;
        }
    }

// =======================================================
// ::2
// stderr
// + Write on regular file.

    if ( __file->_file == 2 )
    {
        debug_print("sys_write: Writing into stderr\n");
        // Shortcut
        if ( __file->____object == ObjectTypeFile )
        {
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
// saber onde está o buffer.
// #todo: Talvez podemos chamar a função socket_write().
// #todo: Lidar com a questao do copiar, pois
// accept deve retornar o fd do cliente, para que o servidor
// construa uma lista de clientes.
// Entao copiar sera uma opçao, gerenciada por uma flag.
    
// #bugbug
// Nao podemos fazer a copia se os dois sockets 
// estiverem com a conexao pendente.

    if ( __file->____object == ObjectTypeSocket )
    {
        // Can't write.
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
            // #todo: Ja fizemos isso logo acima.
            if( __file->_flags & __SWR )
            {
                //debug_print ("sys_write: >>>> WRITE\n");
                __file->_flags = 0;
            
                // Write in the socket buffer.
                nbytes = (ssize_t) file_write_buffer ( 
                                       (file *) __file, 
                                       (char *) ubuf, 
                                       (int) count );

                // fail
                if (nbytes <= 0)
                {
                    debug_print("sys_write: [FAIL] file_write_buffer couldn't write on socket \n");
                    //#todo: Isso pode afetar o desempenho.
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
                    
                    return (ssize_t) nbytes;
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
        // Can't write.
        if ( (__file->_flags & __SWR) == 0)
        {
             debug_print("sys_write: [FLAGS] Can't write!\n");
             return 0;
        }

        // Can write.
        if (__file->_flags & __SWR)
        {
            // Regular file.
            nbytes = (ssize_t) file_write_buffer ( 
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
                
                return (ssize_t) nbytes;
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
        
        return (ssize_t) (-1);
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
// pipe:
// See: pipe.c

    if ( __file->____object == ObjectTypePipe )
    {
        return (ssize_t) sys_write_pipe ( (int) fd, (char *) ubuf, (int) count ); 
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
    
// #bugbug: Isso pode degradar o desempenho.
    //refresh_screen();   
    
    // Não conseguimos escrever ... 
    // Estamos com problemas 
    //do_thread_waiting (current_thread);
    //__file->tid_waiting = current_thread;
    //__file->_flags |= __SWR;  //pode escrever.
    //scheduler();

// fail. something is wrong!
    return (ssize_t) (-1);
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
// OUT: fd.

int 
sys_open (
    const char *pathname, 
    int flags, 
    mode_t mode )
{
    int value = -1;

// #todo:
// check arguments.

    if ( (void*) pathname == NULL ){
        return (int) (-EINVAL);
    }

// ??
// creat chama open.
// open tenta ler num arquivo que nao existe?

    debug_print ("sys_open: $\n");


// #todo
// primeiro vamos checar se o arquivo 
// tem seu pathname registrado na tabela de dispositivos
// do diretorio dev/
// See: fs.h

    //#todo
    //Se encontrarmos uma entrada correspondente ao pathname,
    //então deve retornar o ponteiro para um arquivo,
    //então colocaremos esse ponteiro em uma entrada da lista de
    //arquivos abertos do processo.

    //fs_search_pathname_in_dev_dir(pathname);

// Searth for a device associated with this path
// in the deviceList[]
// See: devmgr.c

    file *dev_fp;
    dev_fp = (file *) devmgr_search_in_dev_list(pathname);

    if( (void*) dev_fp != NULL )
    {
        if(dev_fp->isDevice == TRUE )
        {
            // #todo 
            // Put it into the list inside the
            // current process structure
            // and return the fd.
            
        }
    }


// Vamos carregar o arquivo que esta no disco.
// See: fs.c
// OUT: fd

    value = 
        (int) sys_read_file_from_disk ( 
                  (char *) pathname, 
                  flags, 
                  mode );

    if (value<0){
        return (int) -1;
    }

    // The limit is 32.
    // Too many open files.
    if (value>31)
    {
        return (int) (-EMFILE);
    }

// fd
    return (int) value;
}


/*
 *  sys_close:
 */
// Fechar um dos objetos abertos do processo atual.
// O descritor é um índice na sua tabela de objetos abertos.
// #todo: Se fecharmos um socket, tem que antes destruir a estrutura
// de socket associada ao arquivo.
// See:
// https://man7.org/linux/man-pages/man2/close.2.html
// https://pubs.opengroup.org/onlinepubs/009695399/functions/close.html

int sys_close(int fd)
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

// Invalid fd
    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (int) (-EBADF);
    }

// Process
// #todo: There is a helper for that small routine.

    if ( current_process < 0 || 
         current_process >= PROCESS_COUNT_MAX )
    {
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
// nada sera salvo no disco.
    if ( object->____object == ObjectTypeSocket )
    {
        debug_print("sys_close: Trying to close a socket object\n");
        object->socket->used = FALSE; //invalidando a estrutura de socket
        object->socket->magic = 0;//invalidando a estrutura de socket
        object = NULL;   //destroi a estrutura de arquivo.
        //p->priv = NULL; //socket privado do processo.
        p->Objects[fd] = (unsigned long) 0;  // limpa o slot na estrutura de processo.
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
    if ( object->____object == ObjectTypeVirtualConsole )
    {
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


// #todo: 
// Rever esses argumentos.
// SVr4, 4.3BSD, POSIX.1-2001. and more.
// See: 
// https://man7.org/linux/man-pages/man2/fcntl.2.html

int sys_fcntl ( int fd, int cmd, unsigned long arg )
{
    debug_print ("sys_fcntl:\n");


    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (int) (-EBADF);
    }

    if ( cmd < 0 ){
        return (int) (-EINVAL);
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

    return (int) -1; //#todo
}



// Called by sc82 in sci.c
// Enquanto sys_ioctl eh chamada pelos applicativos,
// io_ioctl eh chamada pelas rotinas dentro do kernel.
// See: drivers/io.c

int sys_ioctl( int fd, unsigned long request, unsigned long arg )
{
    debug_print ("sys_ioctl: [FIXME] \n");

    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (int) (-EBADF);
    }

    return (int) io_ioctl(fd,request,arg);
}






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

// 10003
// Get action.
// See: kstdio.h
int sys_get_global_sync (int sync_id, int request)
{ 
    struct kstdio_sync_d *s;

    if( sync_id < 0 ||
        sync_id >= SYNC_COUNT_MAX )
    {
       //message? panic?
       return -1;
    }

    s = (struct kstdio_sync_d *) syncList[sync_id];
    
    if( request == SYNC_REQUEST_GET_ACTION )
    {
        return (int) s->action;
    }

    return -1; 
}

// 10002
// Set action.
// See: kstdio.h
void sys_set_global_sync(int sync_id, int request, int data)
{
    struct kstdio_sync_d *s;

    if( sync_id < 0 ||
        sync_id >= SYNC_COUNT_MAX )
    {
       //message? panic?
       return;
    }

    s = (struct kstdio_sync_d *) syncList[sync_id];
    
    if( request == SYNC_REQUEST_SET_ACTION )
        s->action = data;
}


// 10004
// Create sync structure and
// put the pointer into the list.
// See: kstdio.h
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


// Get the id.
// provisorio, para testes
// See: kstdio.h
int get_saved_sync(void)
{
    return (int) __saved_sync_id;
}


// service 10007
// #todo
// Comment the purpose of this routine.
// It is used on socket communication.
// #todo: Explain the output values.

int sys_get_file_sync (int fd, int request)
{
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

    if ( fd < 0 || fd >= OPEN_MAX )
    {
        return (int) (-EBADF);
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
    // check process validation

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

// ?? Why '0'?
    return 0;
}


// service 10006
// #todo
// Comment the purpose of this routine.
// It is used on socket communication.

void sys_set_file_sync(int fd, int request, int data)
{
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

    if ( fd < 0 || fd >= OPEN_MAX )
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

    if (p->magic != 1234){
        return;
    }

// object
// Everything is a file.

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
        //printf("216:\n"); 
        //refresh_screen();
        
        object->sync.action = 0;
        //object->_flags = (__SWR | __SRD); 
        object->_flags = __SWR;
        k_rewind(object);
        object->_r = 0;
        object->_w = 0;
        object->socket_buffer_full = FALSE; //empty buffer
        return;
        break;

    // #test
    // Now we can read
    case 217:

        //#debug
        //printf("217:\n"); 
        //refresh_screen();

        object->sync.action = 0;
        //object->_flags = (__SWR | __SRD); 
        object->_flags = __SRD;
        return;
        break;

    // ...
        
    default:
        debug_print("sys_set_file_sync: [FAIL] Default request\n");
        return;
        break;
    };

    // ...
}


// Get the device number in the dev_dir[] list
// given the pathname.
// ex: "/DEV/DEV1"

int sys_get_device_number_by_path( char *path )
{
   return -1;
}


// #test
// #todo
// Precisamos uma syscall para esse serviço.
// Open device by number.
// Index in the dev_dir[] list.
// Incluir o ponteiro para arquivo na lista 
// de arquivos abertos do processo atual.
// See: sys.h

int sys_open_device_by_number(int device_index)
{
    struct process_d *p;
    file *fp;
    int __slot=0;

    int i = device_index;

    if (i<0 || i>=32)
    {
        return (int) (-EINVAL);
    }

    if(dev_dir[i].magic != 1234)
        return (int) -1;

    if(dev_dir[i].initialized != TRUE)
        return (int) -1;

// get file pointer.
    fp = (file*) dev_dir[i].fp;
    
    if( (void*) fp == NULL )
        return (int) -1;

// put the pointer into the list.

    pid_t current_process = (pid_t) get_current_process();

    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL )
    {
        debug_print ("sys_open_device_by_number: p\n");
        return -1;
    }

    if ( p->used != TRUE || p->magic != 1234 ){
        debug_print ("sys_open_device_by_number: validation\n");
        return -1;
    }

// Procurando um slot livre.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ goto __OK; }
    };

// fail
    panic ("sys_open_device_by_number: No slots!\n");

// Slot found.
__OK:

    if ( __slot < 0 || __slot >= 32 )
    {
        printf ("sys_open_device_by_number: Slot fail\n");
        refresh_screen();
        return (int) (-1);
    }

// save
    p->Objects[__slot] = (unsigned long) fp;

// return fd.
    return (int) __slot;
}


// 178
// Only root dir.
//#todo: 
// unsigned long sys_get_file_size ( char *path, unsigned long dir_address )

unsigned long sys_get_file_size(char *path)
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

    Size = 
    (unsigned long) fsGetFileSize ( 
                        (unsigned char *) path, 
                        (unsigned long) VOLUME1_ROOTDIR_ADDRESS );

    return (unsigned long) Size; 
}


// IN: fd
// OUT: 
// -1= error; 
// FALSE= nao pode ler; 
// TRUE= pode ler.

int sys_sleep_if_socket_is_empty(int fd)
{
    struct process_d *p;
    file *object;

    pid_t current_process = (pid_t) get_current_process();

    if ( fd < 0 || 
         fd >= OPEN_MAX )
    {
        return (int) (-EBADF);
    }

// process

    if ( current_process < 0 || 
         current_process >= PROCESS_COUNT_MAX )
    {
        debug_print("sys_sleep_if_socket_is_empty: current_process\n");
        return (int) (-1);
    }

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




//get free slots in the file_table[]
int get_free_slots_in_the_file_table(void)
{
    file *tmp;
    int i=0;

    for (i=0; i<NUMBER_OF_FILES; i++)
    {
        tmp = (void*) file_table[i];
        
        // Nenhum file descritor está usando essa estrutura.
        if (tmp->used == TRUE && 
            tmp->magic == 1234 && 
            tmp->fd_counter == 0)
        { 
            return (int) i; 
        }
    };

    return -1;
}


//get free slots in the inode_table[]
int get_free_slots_in_the_inode_table(void)
{
    struct inode_d *tmp;
    int i=0;

    
    for (i=0; i<32; i++)
    {
        tmp = (void*) inode_table[i];
        
        // Se nenhum descritor de estrutura de arquivo 
        // está usando essa estrutura inode.
        if (tmp->used == TRUE && 
            tmp->magic == 1234 && 
            tmp->filestruct_counter == 0)
        { 
            return (int) i; 
        }
    }

    return -1;
}


// #todo: Describe this routine.
// credits: hoppy os.
// from 8.3
// not tested yet.
void 
from_FAT_name (
    char *src, 
    char *dst )
{

    int i=0;
    int j=0;
    int k=0;

    // #todo: debug messages.
    
    if ( (void *) src == NULL ){ return; }
    if ( (void *) dst == NULL ){ return; }

    if (*src == 0){ return;}
    if (*dst == 0){ return;}


// dirty
// pra saber o tamanho do nome exluindo os espaços.

    for (j=7; j >= 0 && src[j] == 0x20; j--)
    {
        // Nothing.
    };

    k=0;

// j eh o tamanho do nome calculado anteriormente.
// copia esse nome.

    for( i=0; i<=j; i++ )
    {
        dst[k++] = src[i];
    };
    
    
    if (*src != '.')
    {
        dst[k++] = '.';
    }

// dirty.
// pra saber o tamanho da extensao, excluindo os espaços.
    for (j=10; j>=8 && src[j]==0x20; j--)
    {
        // Nothing.
    };
    
    //
    if (j==7) {
    
        if (k==1){
           dst[k]=0;
        } else {

            if (dst[0]=='.'){
                dst[k]=0;
            }else{
                dst[k-1]=0;
            };
        };
    
    } else {
        
        for (i=8; i<=j; i++)
        {
            dst[k++] = src[i];
        };
        
        dst[k++] = 0;
    };
}


// #todo: Describe this routine.
// credits: hoppy os.
// to 8.3
// not tested yet.
void 
to_FAT_name (
    char *src,
    char *dst )
{
    int i=0;
    char *ptr;

    // Parent directory
    if ( !strcmp(src,"..") ) {
        strcpy(dst,src);
        i=2;
    
    // Current directory
    } else if (!strcmp(src,".")) {
        strcpy(dst,src);
        i=1;
    
    // Regular file.
    } else {
        
        ptr = src;

        i=0;
        
        // Começamos com o nome.
        while (i<8 && *ptr && *ptr != '.') 
        {
            dst[i++] = *ptr++;
        };
        
        // Completa com ' ' ate 8.
        while (i<8){ dst[i++] = 0x20; };
        
        if (*ptr == '.') { ptr++; }
        
        // Agora a extensao
        while (i<11 && *ptr){
            dst[i++] = *ptr++;
        };
    };

    // Completa com espaço ate o fim.
    // 'i' indica o offset de onde devemos começar.
    // Isso tambem vai completar com espaço quando a extensao
    // tiver menos que 3 chars.

    while (i<11){ dst[i++] = 0x20; };
}


/*
 * get_filesystem_type:
 *     Pega o tipo de sistema de arquivos.
 *     ?? #bugbug: De qual volume ??  
 */

int get_filesystem_type (void)
{
    return (int) g_currentvolume_filesystem_type;
}


/*
 * set_filesystem_type:
 *     Configura o tipo de sistema de arquivo.
 *     ?? #bugbug: De qual volume ?? 
 */

void set_filesystem_type (int type)
{
    g_currentvolume_filesystem_type = (int) type;
}


// Counting path levels.
// Credits: Sirius OS.
unsigned long fs_count_path_levels (unsigned char *path)
{
    unsigned long Counter=0;

    register int i=0;
    int MaxChars = 2000;  //(80*25), 25 lines.

    if ( (void*) path == NULL ){ return 0; }
    if ( *path == 0 )          { return 0; }

    for ( i=0; i < MaxChars; ++i )
    {
        if (path[i] == '/') { Counter++; }
        if (path[i] == '\0'){ break; }
    };

    return (unsigned long) Counter;
}


/*
 * get_file:
 *     Get the pointer given the index in file_table[].
 */
// na lista de arquivos do kernel.
void *get_file (int Index)
{
	//Limits.
	//@todo: max.

    if (Index < 0)
    {
        // ?? todo: message
        return NULL;
    }

    return (void *) file_table[Index];
}


/*
 * set_file:
 *     Put the pointer in the list, given the index.
 */
// na lista de arquivos do kernel.
void set_file ( void *file, int Index )
{

    if (Index < 0){
        // ?? todo: message
        return;
    }

	// #todo:
	// Limite m�ximo da lista.

	// Structure.

    if ( (void *) file == NULL )
    {
        // ?? todo: message
        return;
    }

	// Include pointer in the list.

    file_table[Index] = (unsigned long) file;
}



int fs_initialize_dev_dir(void)
{
    int i=0;

// Clear the list
    for(i=0; i<32; i++)
    {
        dev_dir[i].used = FALSE;
        dev_dir[i].magic = FALSE;
        dev_dir[i].initialized = FALSE;
        
        dev_dir[i].path[0] = 0;
        
        dev_dir[i].fp = NULL;
    };

    return 0;
}

// fsInit:
// Called by init() in init.c
int fsInit (void)
{
    int slot = -1;

    debug_print ("fsInit: [TODO]\n");
    
// Undefined fs!
    set_filesystem_type(FS_TYPE_NULL);

// Initialize fat16 support for the system's volume.
// #todo: 
// Devemos checar o tipo da partiçao de boot. 
// Se nao aqui, depois!

    fat16Init();

// Init dev/ dir.
    fs_initialize_dev_dir();

//
// == fileList =========================
//

// Initializing the file pointers
// volume1_rootdir_fp and volume2_rootdir_fp.
// See: kstdio.h


//
// == volume1_rootdir ================================
//

    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if (slot<0 || slot >= NUMBER_OF_FILES){
        panic("fsInit: slot");
    }
    volume1_rootdir_fp = (file *) file_table[slot];
    volume1_rootdir_fp->filetable_index = slot;

    if ( (void *) volume1_rootdir_fp == NULL ){
        panic ("fsInit: volume1_rootdir_fp \n");
    } else {
        volume1_rootdir_fp->used  = TRUE;
        volume1_rootdir_fp->magic = 1234;
        volume1_rootdir_fp->____object = ObjectTypeVolume;

        volume1_rootdir_fp->_base = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir_fp->_p    = (unsigned char *) VOLUME1_ROOTDIR_ADDRESS;
        volume1_rootdir_fp->_cnt = (32 * 512);
        volume1_rootdir_fp->_file = 0;
        volume1_rootdir_fp->_tmpfname = "VOLUME1 VOL";
        volume1_rootdir_fp->fd_counter = 1;

        // #bugbug: 
        // Validade da estrutura.
        
        // ...
        // inode support.
        // pega slot em inode_table[] 
        slot = get_free_slots_in_the_inode_table();
        if (slot<0 || slot >=32){
            panic("fsInit: volume1_rootdir_fp inode slot");
        }
        volume1_rootdir_fp->inode = (struct inode_d *) inode_table[slot];
        volume1_rootdir_fp->inodetable_index = slot;
        if ( (void*) volume1_rootdir_fp->inode == NULL ){
            panic("fsInit: volume1_rootdir_fp inode struct");
        }
        volume1_rootdir_fp->inode->filestruct_counter = 1;  //inicialize
        memcpy ( 
            (void*)       volume1_rootdir_fp->inode->path, 
            (const void*) volume1_rootdir_fp->_tmpfname, 
                  sizeof( volume1_rootdir_fp->inode->path ) );
        // ... 

        // File that represents a volume
        //#todo: Change to 'storage->__bootvolume_fp'.
        storage->__file = volume1_rootdir_fp; 
    };


//
// == volume2_rootdir =========================================== 
//
    // pega slot em file_table[] para
    slot = get_free_slots_in_the_file_table();
    if (slot<0 || slot >= NUMBER_OF_FILES){
        panic("fsInit: slot");
    }
    volume2_rootdir_fp = (file *) file_table[slot];
    volume2_rootdir_fp->filetable_index = slot;

    if ( (void *) volume2_rootdir_fp == NULL ){
        panic ("fsInit: volume2_rootdir_fp\n");
    }else{
        volume2_rootdir_fp->used  = TRUE;
        volume2_rootdir_fp->magic = 1234;
        volume2_rootdir_fp->____object = ObjectTypeVolume;
 
        volume2_rootdir_fp->_base = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir_fp->_p    = (unsigned char *) VOLUME2_ROOTDIR_ADDRESS;
        volume2_rootdir_fp->_cnt = (32 * 512);  // #bugbug: Check this size.
        volume2_rootdir_fp->_file = 0;          // ?
        volume2_rootdir_fp->_tmpfname = "VOLUME2 VOL";
        volume2_rootdir_fp->fd_counter = 1;

        // ...
        // inode support.
        // pega slot em inode_table[] 
        slot = get_free_slots_in_the_inode_table();
        if (slot<0 || slot >= 32){
            panic("fsInit: volume2_rootdir inode slot");
        }
        volume2_rootdir_fp->inode = (struct inode_d *) inode_table[slot];
        volume2_rootdir_fp->inodetable_index = slot;
        if ( (void*) volume2_rootdir_fp->inode == NULL ){
            panic("fsInit: volume2_rootdir_fp inode struct");
        }
        volume2_rootdir_fp->inode->filestruct_counter = 1;  //inicialize
        memcpy ( 
            (void*)       volume2_rootdir_fp->inode->path, 
            (const void*) volume2_rootdir_fp->_tmpfname, 
                  sizeof( volume2_rootdir_fp->inode->path ) );
        // ... 
    };


//
// == pipe_gramadocore_init_execve ================================ 
//

	//
	// ## Inicializando os pipes usados em execve ## 
	//

	//gramado core init execve 

    //#todo: mudar para pipe_gramadocore_init_execve_fp

	//aloca memoria para a estrutura.
    pipe_gramadocore_init_execve = (file *) kmalloc ( sizeof(file) );

    if ( (void *) pipe_gramadocore_init_execve == NULL ){
        panic ("fsInit: pipe_gramadocore_init_execve\n");
    }else{

        // Aloca memória para o buffer.
        // #todo: Define this variable in the top of the body.
        // #bugbug: Chech this size.
        unsigned long pipe0base = (unsigned long) kmalloc (512);

        if ( (void *) pipe0base == NULL ){
            panic ("fsInit: pipe0base\n");
        }

        pipe_gramadocore_init_execve->used  = TRUE;
        pipe_gramadocore_init_execve->magic = 1234;

        pipe_gramadocore_init_execve->_base = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_p    = (unsigned char *) pipe0base;
        pipe_gramadocore_init_execve->_cnt  = 512;  // #bugbug: Check this size.
        pipe_gramadocore_init_execve->_file = 0;    // ??
        pipe_gramadocore_init_execve->_tmpfname = "pipe0";

        // #todo
        //fileList[ ? ] = (unsigned long) pipe_gramadocore_init_execve;

        // 0
        Pipes[0] = (unsigned long) pipe_gramadocore_init_execve;
    };


// Initialize directory facility structures.
    init_directory_facilities();

// CWD Structure.
// Inicializa o pwd support.
    fsInitializeWorkingDiretoryString();

// Target dir struct
// Inicializa a estrutura de suporte ao target dir.
    fsInitTargetDir(VOLUME1_ROOTDIR_ADDRESS,"/");

    debug_print ("fsInit: done\n");
    return 0;
}


int init_directory_facilities(void)
{

    // '/'
    directory_facility_RootDir.dir_address = VOLUME1_ROOTDIR_ADDRESS;
    directory_facility_RootDir.dir_name[0] = '/';
    directory_facility_RootDir.dir_name[1] = 0;
    directory_facility_RootDir.name_size = 1;
    directory_facility_RootDir.initialized = TRUE;

    // EFI/
    directory_facility_EFIDir.dir_address = 0;
    directory_facility_EFIDir.dir_name[0] = 0;
    directory_facility_EFIDir.name_size = 0;
    directory_facility_EFIDir.initialized = FALSE;

    // GRAMADO/
    directory_facility_GramadoDir.dir_address = 0;
    directory_facility_GramadoDir.dir_name[0] = 0;
    directory_facility_GramadoDir.name_size = 0;
    directory_facility_GramadoDir.initialized = FALSE;

    // PROGRAMS/
    directory_facility_ProgramsDir.dir_address = 0;
    directory_facility_ProgramsDir.dir_name[0] = 0;
    directory_facility_ProgramsDir.name_size = 0;
    directory_facility_ProgramsDir.initialized = FALSE;


    // UBASE/
    directory_facility_ubaseDir.dir_address = 0;
    directory_facility_ubaseDir.dir_name[0] = 0;
    directory_facility_ubaseDir.name_size = 0;
    directory_facility_ubaseDir.initialized = FALSE;

    // USERS/
    directory_facility_usersDir.dir_address = 0;
    directory_facility_usersDir.dir_name[0] = 0;
    directory_facility_usersDir.name_size = 0;
    directory_facility_usersDir.initialized = FALSE;


    // ok
    return 0;
}


// Called by fsInit inthis document.
int fat16Init (void)
{
    debug_print ("fat16Init: [TODO]\n");

// Initializing the cache state.
    fat_cache_loaded = FAT_CACHE_NOT_LOADED;
    fat_cache_saved  = FAT_CACHE_NOT_SAVED;

// Set type.
    set_filesystem_type (FS_TYPE_FAT16);

// Structures and fat.

    // #todo
    fs_init_structures();
    fs_init_fat();

// done
    debug_print ("fat16Init: done\n");
    return 0;
}


// #todo
// Change the return type to 'int' and
// remove all the messages. Maybe.
// Create the 'root' filesystem structure.
void fs_init_structures (void)
{
    int Type=0;

    debug_print ("fs_init_structures: [TODO]\n");


//
// root
//

// struct
// Create the 'root' filesystem structure.
// Initialize the 'root' filesystem structure.
// "/"

    debug_print ("fs_init_structures: root\n");

    root = (void *) kmalloc ( sizeof(struct filesystem_d) );
    if ( (void *) root == NULL ){
        panic ("fs_init_structures: Couldn't create the root structure.\n");
    }

    root->objectType  = ObjectTypeFileSystem;
    root->objectClass = ObjectClassKernelObjects;
    root->used = TRUE;
    root->magic = 1234;
    root->name = (char *) ____root_name;


// #todo 
// #bugbug   volume_vfs  ??

// Se o volume do vfs ainda não foi criado 
// então não podemos prosseguir.

        //if ( (void *) volume_vfs == NULL )
        //{
        //    debug_print("fs_init_structures: [FAIL] volume_vfs not initialized");
        //    panic      ("fs_init_structures: [FAIL] volume_vfs not initialized");
        //}
        //volume_vfs->fs = root;
 

// Save is in the 'storage' low level structure.

    if( (void*) storage == NULL ){
         panic("fs_init_structures: storage");
    }

    storage->fs = (void*) root;
    // ...

// Type
// #bugbug: 
// Em qual disco e volume pegamos o tipo de sistema de arquivos?

    debug_print ("fs_init_structures: Type\n");


    // #bugbug
    // Why do we have this information?
    Type = (int) get_filesystem_type();

    Type = ( Type & 0xFFFF );

    if ( Type <= 0 ){
        panic ("fs_init_structures: [PANIC] Type\n");
    }else{
        root->type = (int) Type;
    };

    switch (Type){

    case FS_TYPE_FAT16:

        // Disk stuff.
        // spc - Sectors per cluster.
        root->spc = (int) VOLUME1_SPC;
        //root->spc = (int) get_spc(); 

        // Rootdir, Fat and data area.
        // #bugbug: Specific for fat16.
        
        // root dir
        root->rootdir_address   = VOLUME1_ROOTDIR_ADDRESS;
        root->rootdir_first_lba = VOLUME1_ROOTDIR_LBA;
        //root->rootdir_last_lba = 0;  //#todo 
        root->rootdir_size_in_sectors = 0;  //#todo
        
        // fat1
        root->fat_address     = VOLUME1_FAT_ADDRESS;
        root->fat_first_lba   = VOLUME1_FAT_LBA;
        //root->fat_last_lba = 0;  //#todo
        root->fat_size_in_sectors = 0;  //#todo
        
        // fat2
        // ...
        
        // dataarea
        //filesystem->dataarea_address = ??;
        root->dataarea_first_lba    = VOLUME1_DATAAREA_LBA; 
        //root->dataarea_last_lba = 0;  //#todo
        //root->dataarea_size_in_sectors = 0;  //#todo
 

        //root->fs_first_lba = 0;  //#todo
        
        //#todo (dataarea + dataarea size)?
        //root->fs_last_lba = 0;   

        //(mbrsize + reserved + rootdirsize + fat1size + fat2size +dataareasize)
        //root->fs_size_in_sectors = 0;


        // Root dir.
            
        // Number of entries in the root dir.
        // #bugbug: Specific for fat16.
        root->dir_entries = FAT16_ROOT_ENTRIES;
            
        // Size of the entry in bytes.
        // #bugbug: Specific for fat16.
        root->entry_size = FAT16_ENTRY_SIZE;
       
        // ...
        break;

    case FS_TYPE_EXT2:
    default:
        panic ("fs_init_structures: [todo] default Type\n");
        break;
    };
}


// #todo
// Change the return type to 'int' and
// remove all the messages. Maybe.
void fs_init_fat (void)
{
    debug_print ("fs_init_fat: [TODO]\n");

// root
// The root file system structure.
// "/"

    if ( (void *) root == NULL ){
        panic ("fs_init_fat: root\n");
    }

// ==================================

// fat
// Let's create the 'fat' structure.
// See:

    bootvolume_fat = (void *) kmalloc ( sizeof(struct fat_d) );

    if ( (void *) bootvolume_fat == NULL ){
        panic ("fs_init_fat: bootvolume_fat\n");
    }

// Populate it with some values found in the root structure.

    bootvolume_fat->initialized = FALSE;

// ??
// The same type of the root filesystem?
    bootvolume_fat->type = (int) root->type;

    bootvolume_fat->fat_address = (unsigned long) root->fat_address; 

    bootvolume_fat->fat_first_lba = (unsigned long) root->fat_first_lba;
    bootvolume_fat->fat_last_lba  = (unsigned long) root->fat_last_lba;

    //bootvolume_fat->fat_size_in_sectors = (unsigned long) root->fat_size_in_sectors;
    //bootvolume_fat->size_in_bytes = 0;  // (bootvolume_fat->fat_size_in_sectors / 2), se sector=512.
    //bootvolume_fat->size_in_kb = 0;     // bootvolume_fat->size_in_bytes/1024
    

// #todo
// Check this values.

// #todo
// What is this address?
// Is this the virtual address of the
// start of the fat table?

    if ( bootvolume_fat->fat_address == 0 ){
        panic ("fs_init_fat: bootvolume_fat->fat_address\n");
    }

// #bugbug: 
// Is it int ?
    if ( bootvolume_fat->type <= 0 ){
        panic ("fs_init_fat: fat->type\n");
    }


    bootvolume_fat->volume = NULL;

    // ...

    bootvolume_fat->initialized = TRUE;
    bootvolume_fat->used = TRUE;
    bootvolume_fat->magic = 1234;

// #bugbug
// Tem que passar esse ponteiro para algum lugar.
    //return;
}


// #todo: use int return.
void file_close (file *_file)
{
    debug_print("file_close: todo\n");

    if ( (void*) _file == NULL ){
        return;
    }
}


size_t file_get_len(file *_file)
{
    debug_print("file_get_len: todo\n");

    if ( (void*) _file == NULL ){
        return -1;
    }

    return (size_t) -1;
}


//OUT: inode structure.
struct inode_d *file_inode (file *f)
{
    if ( (void *)f==NULL )
    {
        return (struct inode_d *) 0;
    }

    return (struct inode_d *) f->inode;
}


//??
int file_truncate ( file *_file, size_t len)
{
    debug_print("file_truncate: todo\n");

    if ( (void*) _file == NULL )
        return -1;

    if(len<0)
        return -1;

    return -1;
}



// Check the signature in a elf header.
// OUT:
// 0 = OK. #todo: Isso poderia ser '1'.
// < 0 Means error.
// #todo
// We can do the same for some other types.
// Use TRUE or FALSE.

// #todo
// is address virtual or physical?
// Change this name to pa or va.

int fsCheckELFFile ( unsigned long address )
{
    if( address == 0 ){
        return 0;
    }

    return (int) elfCheckSignature(address);
}


/*
 * fsFAT16ListFiles:
 *     Mostra os nomes dos arquivos de um diret�rio.
 *     Sistema de arquivos fat16.
 * IN:
 *     dir_address = Ponteiro para um endere�o de mem�ria 
 *                   onde foi carregado o diret�rio. 
 */

// #todo
// is dir_address virtual or physical?
// Change this name to dir_pa or dir_va.

void 
fsFAT16ListFiles ( 
    const char     *dir_name, 
    unsigned short *dir_address, 
    int            number_of_entries )
{

    // iterator
    int i=0;

    // offset
    int j=0;  
    
    // Max number of entries.
    int max = number_of_entries;

    //8.3
    char NameString[12];

    // Buffer.
    unsigned short *shortBuffer = (unsigned short *) dir_address;
    unsigned char  *charBuffer  = (unsigned char *)  dir_address;

    if ( (void *) dir_name == NULL )
    {
        printf ("fsFAT16ListFiles: [FAIL] dir_name\n");
        goto fail;
    }

    if ( *dir_name == 0 ){
        printf ("fsFAT16ListFiles: [FAIL] *dir_name\n");
        goto fail;
    }

// banner message.
// #bugbug
// Missing string finalization.
        
    // printf ("fsFAT16ListFiles: Listing names in [%s]\n\n", 
    //        dir_name );
            
    // Number of entries.

    if ( number_of_entries <= 0 ){
        debug_print ("fsFAT16ListFiles: [FAIL] number_of_entries\n");
        goto fail;
    }

    // #bugbug
    // Number of entries.

    if ( number_of_entries >= 512 )
    {
        debug_print ("fsFAT16ListFiles: [FAIL] number_of_entries is too big\n");
        goto fail;
    }

// Show 'max' entries in the directory.

    i=0; 
    j=0;
    while (i < max)
    {
        // Not invalid and not free.
        if ( charBuffer[j] != FAT_DIRECTORY_ENTRY_LAST &&
             charBuffer[j] != FAT_DIRECTORY_ENTRY_FREE )
        {
             // #bugbug
             
             memcpy( 
                 (char*) NameString, 
                 (const char *) &charBuffer[j],
                 11 );
             
             NameString[11] = 0;  //finalize string
             
             printf ("%s\n", NameString );
        } 

        // (32/2) proxima entrada! 
        // (16 words) 512 vezes!
 
        //j += 16;  //short buffer  
          j += 32;  //char buffer
        
        i++;  
    }; 

    // ...
 
    goto done;

fail:
    printk ("fsFAT16ListFiles: fail\n");
done:
    refresh_screen();
}



/*
 * fsInitializeWorkingDiretoryString:
 *     Atualiza a string do diretorio de trabalho.
 * Essa eh a string que sera mostrada antes do prompt.
 * 'pwd'> 
 */

void fsInitializeWorkingDiretoryString (void)
{

    // #bugbug
    // We have some issues with string sizes.
    // Buffer overflow!

    // vamos contar o tamanho da string que estamos construindo.
    int string_count = 0;  
    
    //
    int string_size = 0;
    
    struct volume_d  *v;

    char volume_string[8];   


    debug_print ("fsInitializeWorkingDiretoryString:\n");

    // See: 
    // kernel/include/rtl/fs/fs.h

    CWD.initialized = FALSE;

    // volume string 
    
    volume_string[0] = 'v';
    volume_string[1] = 'o';
    volume_string[2] = 'l';
    volume_string[3] = 'u';
    volume_string[4] = 'm';
    volume_string[5] = 'e';
    volume_string[6] = (char)( '1' + (char) current_volume - (char) 1 );
    volume_string[7] = '\0';


	//'root:'
	//  ## volume list ##
	//primeiro colocamos a string que indica a lista de volumes. 

    sprintf ( CWD.path, FS_ROOT_STRING ); 

	//'/'
	// ## separador ##
    strcat ( CWD.path, FS_PATHNAME_SEPARATOR );


	//
	// volume root dir 
	//

    // #todo
    // Check overflow.

    if ( current_volume < 0 ){
        panic ("fsInitializeWorkingDiretoryString: current_volume\n");
    }


    v = (struct volume_d *) volumeList[current_volume];

    if ( (void *) v == NULL ){
        panic ("fsInitializeWorkingDiretoryString: v\n");
    }else{
        if ( v->used != TRUE || v->magic != 1234 ){
            panic ("fsInitializeWorkingDiretoryString: validation\n");
        }

        switch (v->id)
        {
			//case 0:
		        //global usada para string do nome do volume.
			//    current_volume_string = (char *) FS_VOLUME0_STRING;
			//    break;

			//case 1:
		        //global usada para string do nome do volume.
			//   current_volume_string = (char *) FS_VOLUME1_STRING;
			//   break;
			
            default:
		        //fail.
		        //printf("fsInitializeWorkingDiretoryString: default volume #todo\n");
		        //die();
                current_volume_string = (char *) volume_string; 
                break;
        };

        // #bugbug
        // We need to finalize the string.
        // limit 32.
        // See: volume.h
        
        // path string na estrutura do volume.
        
        string_size = sizeof(current_volume_string);

        if (string_size >= 32){
            debug_print ("fsInitializeWorkingDiretoryString: [FIXME] string size\n"); 
            return;
        }
        
        // copy the string. limit 32 bytes.
        sprintf ( v->path_string, current_volume_string );
        
        // finalize.
        v->path_string[31] = 0;

        // #bugbug
        // What is the limit for this string ? 32 bytes.
        // See: rtl/fs/path.h and globals.h

        strcat ( CWD.path, v->path_string );
	    //strcat ( CWD.path, current_volume_string );
	    
        CWD.path[31] = 0;
    };

    // #bugbug
    // What is the limit for this string ? 32 bytes.
    // See: rtl/fs/path.h and globals.h

    // Separador

    strcat ( 
        CWD.path, 
        FS_PATHNAME_SEPARATOR );


//
// Size
//

// #test

    CWD.path[31] = 0;

    int size;
    size = strlen(CWD.path);

    if (size > 31)
        size = 31;

    CWD.size = size;

// More ?...

    debug_print ("fsInitializeWorkingDiretoryString: done\n");

// See: 
// kernel/include/rtl/fs/fs.h

    CWD.initialized = TRUE;
}



/*
 * fsInitTargetDir:
 *     Para inicializarmos o sistema já com um alvo.
 */

// #todo
// is dir_address virtual or physical?
// Change this name to dir_pa or dir_va.

// using the structure 'current_target_dir'.
// IN:
// directory address, directory name.

int fsInitTargetDir (unsigned long dir_address, char *dir_name)
{
    int i=0;


    current_target_dir.used  = TRUE;
    current_target_dir.magic = 1234;

    for ( i=0; i<11; i++ ){
        current_target_dir.name[i] = '\0';
    };


// Dir address

    if (dir_address == 0)
        panic("fsInitTargetDir: dir_address\n");

    //current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
    current_target_dir.current_dir_address = (unsigned long) dir_address;

// Dir name
    
    if ( (void*) dir_name == NULL )
        panic("fsInitTargetDir: dir_name\n");

    if (*dir_name == 0)
        panic("fsInitTargetDir: *dir_name\n");

    //current_target_dir.name[0] = '/';
    //current_target_dir.name[1] = 0;

// Limits: 
// Copy 8 bytes only

    for ( i=0; i<8; i++ ){
        current_target_dir.name[i] = dir_name[i];
    };

// done:
    current_target_dir.initialized = TRUE;
    
    return 0;
}


/*
 * fsList
 *     Ring 0 routine to list files.
 */

// #todo
// Use 'pathname'.

int fsList ( const char *dir_name )
{
    int Absolute = FALSE;
    int i=0;


    debug_print ("fsList:\n");

// Directory name

    if ( (void *) dir_name == NULL ){
        debug_print ("fsList: [FAIL] dir_name\n");
        goto fail;
    }

    if ( *dir_name == 0 ){
        debug_print ("fsList: [FAIL] *dir_name\n");
        goto fail;
    }

// Copy name
// Limits: 
// Copy 8 bytes only

    for ( i=0; i<8; i++ ){
        current_target_dir.name[i] = dir_name[i];
    };
    current_target_dir.name[i] = '\0';


// #shortcut
// '[' 
// #todo: Document this feature.

    if ( dir_name[0] == '[' && dir_name[1] == 0 )
    {
        debug_print ("fsList: root\n");
        Absolute = TRUE;

        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
        // Clear the whole buffer.
        for ( i=0; i<11; i++ ){
            current_target_dir.name[i] = '\0';
        };
        // Create the name.
        current_target_dir.name[0] = '/';
        current_target_dir.name[1] = '\0'; 
    }


    // #bugbug
    // We are using the current directory address,
    // not the directory provide by the user.
    
    // #todo
    // Set up the current dir address, based on the
    // name provided by the user.

    //
    // == current_target_dir ====================
    //

    // directory address.
    
    if ( current_target_dir.current_dir_address == 0 )
    {
        debug_print ("fsList: [FAIL] current_target_dir.current_dir_address \n");
        goto fail;
    }
    
    // #bugbug
    // Missing string finalization.
    //printk ("fsList: current_target_dir.name = {%s}\n", current_target_dir.name);
    

// Listing ...
// IN:
// name, dir address, number of entries;
// No return value.

    fsFAT16ListFiles ( 
        (const char *)     current_target_dir.name,
        (unsigned short *) current_target_dir.current_dir_address, 
        256 );

    debug_print ("fsList: done\n");
    return 0;

fail:
    debug_print ("fsList: fail\n");
    refresh_screen();
    return -1;
}


/*
 *********************************
 * fsListFiles:
 *     Lista os arquivos em um diret�rio, dados os �ndices de disco, 
 * volume e diret�rio.
 */

// #bugbug
// Do not list this in ring0.

void 
fsListFiles ( 
    int disk_id, 
    int volume_id, 
    int directory_id )
{

    // #todo: 
    // Checar mais limites.
    // Use this: if ( disk_id < 0 || volume_id < 0 || directory_id < 0 )

    if ( disk_id == -1 || volume_id == -1 || directory_id == -1 )
    {
        debug_print ("fsListFiles: [FAIL] parameters\n");
        goto fail;
    }

    printf ("fsListFiles: disk={%d} vol={%d} dir={%d}\n", 
        disk_id, volume_id, directory_id );

	// Show!
	// Se o diret�rio selecionado � o diret�rio raiz do VFS.

    if ( current_disk == 0 && current_volume == 0 && current_directory == 0 )
    {
        debug_print ("fsListFiles: [FIXME] current\n");
        
        //vfsListFiles ();
        goto done;
    }

	// @todo: Suportar outros diret�rios.
	// ...

    goto done;

fail:
    printf ("fail\n");
done:
    refresh_screen ();
    return;
}


/*
 * fsGetFileSize: 
 * 
 */

// #bugbug: Isso dá problemas na máquina real.
// Essa rotina é chamada pela função fopen, por isso precisamos dela.
// Pega o tamanho de um arquivo que está no diretório raiz.
// #todo: 
// Podemos alterar para pegar de um arquivo que esteja no diretório alvo.

// #todo:
// Antes de carregar um arquivo o sistema de arquivos
// precisa preencher uma estrutura com informações sobre ele. 
// se já existir um registro é melhor.

// #bugbug
// Estamos com problemas na string do nome.

// #bugbug
// Loading the root dir everytime.

// #todo
// is dir_address virtual or physical?
// Change this name to dir_pa or dir_va.

unsigned long 
fsGetFileSize ( 
    unsigned char *file_name, 
    unsigned long dir_address )
{

    unsigned long FileSize=0;    // 64bit
    unsigned int intFileSize=0;  // 32bit
    
    int i=0;
    unsigned long max = 64;    //?? @todo: rever. Número máximo de entradas.
    unsigned long z = 0;       //Deslocamento do rootdir 
    unsigned long n = 0;       //Deslocamento no nome.

    // #bugbug
    // Estamos com problemas na string do nome.
 
    char NameX[13];
    int CmpStatus = (-1);

    int Spc=0;

	// #importante:
	// Poderíamos usar malloc ou alocador de páginas ??
	// #todo: 
	// Devemos carregar o diretório alvo.

    unsigned short *Dir = (unsigned short *) dir_address;//VOLUME1_ROOTDIR_ADDRESS;

	// #todo: Devemos carregar o diretório atual.
	//unsigned long current_dir_address = (unsigned long) Newpage();
    //#todo: devemos checar se o endereço é válido.
	//unsigned short *current_dir = (unsigned short *) current_dir_address;	
	// #todo: 
	// devemos chamar uma função que carregue um diretório no endereço passado 
	//via argumento.
    //...


    debug_print ("fsRootDirGetFileSize: $\n");


    if ( (void*) file_name == NULL ){
        printk("fsRootDirGetFileSize: [ERROR] file_name\n");
        goto fail;
    }

    if (*file_name == 0){
        printk("fsRootDirGetFileSize: [ERROR] *file_name\n");
        goto fail;
    }


    if (dir_address == 0){
        printk("fsRootDirGetFileSize: [ERROR] dir_address\n");
        goto fail;
    }


	// Lock ??.
	
	//taskswitch_lock();
	//scheduler_lock();	

		
	//	
	// ## ROOT ##
    //
    
    
//loadRoot:
	
	//Carrega o diretório raiz na memória.
	
//#ifdef KERNEL_VERBOSE	
	//printf ("fsRootDirGetFileSize: Loading root..\n"); 
//#endif	
	
	//#bugbug
    //pega o tamanho de um arquivo que está no diretório raiz.
    //#todo: 
    //podemos alterar para pegar de um arquivo que esteja no diretório alvo.	


    // #bugbug
    // Estamos chamando isso toda vez que
    // tentamos abrir um arquivo.

// Carregando o diretório raiz.
// #bugbug
// Case seja o diretório raiz ...
// e essa for a primeira vez que estamos carregando um arquivo.
// #todo: FIXME

    if(dir_address == VOLUME1_ROOTDIR_ADDRESS)
    {

        // #bugbug
        // We can not do this everytime this function
        // is called.

        fs_load_rootdir ( 
            VOLUME1_ROOTDIR_ADDRESS, 
            VOLUME1_ROOTDIR_LBA, 
            32 );
    }

	//#todo:
	//precisamos na verdade carregarmos o diretório corrente.
	
	// Continua ... 
	// Pegar mais informações sobre o sistema de arquivos.
	
	//#obs
	//Checa se é válida a estrutura do sistema de arquivos.
    //A intenção é obtermos a quantidade de entradas no diretório raiz.
	//#bugbug: Mas isso deveria ser feito para o diretório atual.

//
// == root filesystem structure ===============================
//

    if ( (void *) root == NULL ){
        panic ("fsRootDirGetFileSize: [FAIL] No root file system!\n");
    }else{

        // Setores por cluster.
        Spc = root->spc;
        if (Spc <= 0){ panic ("fsRootDirGetFileSize: [FAIL] spc\n"); }

        // Max entries ~ Número de entradas no rootdir.
        // #bugbug: 
        // Devemos ver o número de entradas no diretório raiz
        // #bugbug: Esse valor não é válido para todos os diretórios
        // por isso temos que usar estruturas para gerenciar
        // diretórios e entradas.

        max = root->dir_entries;
        if (max <= 0){ panic ("fsRootDirGetFileSize: [FAIL] max root entries\n"); }

        // More?! 
        // ...
    };


    //
    // file name
    //
    
    //#debug
    //vamos mostrar a string.
    //printf ("fsGetFileSize: file_name={%s}\n", file_name);
	
	//Busca simples pelo arquivo no diretório raiz.
	//todo: Essa busca pode ser uma rotina mais sofisticada. 
	//Uma função auxiliar.

	//Primero caractere da entrada:
	//0 = entrada vazia.
	//$ = entrada de arquivo deletado.
	//outros ...
	//ATENÇÃO:
    //Na verdade a variável 'root' é do tipo short.	 



	// Procura o arquivo no diretório raiz.
	
//search_file:


//
// file name limit.
//

// Se o tamanho da string falhou
// vamos ajustar.

    size_t szFileName = (size_t) strlen(file_name); 

    if ( szFileName > 11 )
    {
        printf ("fsRootDirGetFileSize: [FIXME] name size fail %d\n",
            szFileName );   
        szFileName = 11;
    }

// Compare.
// Copia o nome e termina incluindo o char 0.
// Compara 11 caracteres do nome desejado, 
// com o nome encontrado na entrada atual.

    i=0; 

    while ( i < max )
    {
        // Se a entrada não for vazia.
        if ( Dir[z] != 0 )
        {
            memcpy ( NameX, &Dir[z], szFileName );
            NameX[szFileName] = 0;

            CmpStatus = strncmp ( file_name, NameX, szFileName );

            if ( CmpStatus == 0 ){ goto found; }
            // Nothing.
        }; 

        // Next entry.
        // (32/2)  (16 words) 512 times!

        z += 16;    
        i++;        
    }; 

// Not found!

fail:

    if ( (void*) file_name != NULL ){
        printf ("fsRootDirGetFileSize: [FAIL] %s not found\n", file_name );
     }

    //if ( (void*) NameX != NULL )
        // printf ("fsRootDirGetFileSize: %s not found\n", NameX );

    refresh_screen ();
    return (unsigned long) 0;

// Found!

found:

    // #debug
    // printf("arquivo encontrado\n");
    // refresh_screen();
    // while(1){}

    // #debug
    // Pegando o tamanho do arquivo.
    // Offsets: 28 29 30 31

    //FileSize = *(unsigned long*) (VOLUME1_ROOTDIR_ADDRESS + (z*2) + 28 );
    intFileSize = *(unsigned int *) (dir_address + (z*2) + 28 );

    FileSize = (unsigned long) intFileSize;

	//printf ("%d \n" , root[ z+14 ]);
	//printf ("%d \n" , root[ z+15 ]);
	//printf ("done: FileSize=%d \n" , FileSize);

	//#debug
	//refresh_screen();
	//while(1){ asm("hlt"); }

    // #debug
    // printf ("fsRootDirGetFileSize: FileSize=%d \n" , FileSize );
    // refresh_screen ();

    return (unsigned long) ( FileSize & 0x00000000FFFFFFFF );
}


// WORKER
// Called by fsLoadFile
// Some invalid address.
// We can not load a file in the same addresses of the
// base kernel or the rootdir ...
// See: gva.h
// Protectng some core areas.
// OUT: 
// TRUE = OK | FALSE = FAIL

static int __check_address_validation( unsigned long address )
{
    int Status=TRUE;  //ok

// fat, rootdir, base kernel, lfb, backbuffer ...

    if ( address == VOLUME1_FAT_ADDRESS_VA )           { Status=FALSE; }
    if ( address == VOLUME1_ROOTDIR_ADDRESS_VA )       { Status=FALSE; }
    if ( address == KERNEL_IMAGE_BASE )                { Status=FALSE; }
    if ( address == DEFAULT_LFB_VIRTUALADDRESS )       { Status=FALSE; }
    if ( address == DEFAULT_BACKBUFFER_VIRTUALADDRESS ){ Status=FALSE; }
    // ...

// #todo
// We can check against some other core addresses.

//done:
    return (int) Status;
}


/*
 * fsLoadFile:
 *    It loads a file into the memory.
 * IN:
 *     fat_address  = FAT address.
 *     dir_addresss = Directory address.
 *     dir_entries  = Number of entries in the given directory.
 *     file_name    = File name.
 *     buffer = Where to load the file. The buffer.
 *     buffer_size_in_bytes = Maximum buffer size.
 * OUT: 
 *    1=fail 
 *    0=ok.
 */

// #bugbug
// Essa rotina somente consegue pegar o tamanho do arquivo
// se o arquivo estiver no diretório raiz.
// #todo: Criar uma rotina para pegar o tamanho do arquivo em 
// qualquer diretório.

// #obs
// Rotina específica para FAT16.
// Podemos mudar o nome para fsFat16LoadFile().
// Ou fs_Fat16_SFN_LoadFile()

// #bugbug
// This routine is nor respecting the number of entries
// in the diretory. It is using the limit of the root dir
// for all the directories, 512 entries.

// #todo
// Maybe we need to use a structure for that set of parameters.

// #todo
// is dir_address virtual or physical?
// Change this name to dir_pa or dir_va.

unsigned long 
fsLoadFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    const char *file_name, 
    unsigned long buffer,
    unsigned long buffer_size_in_bytes )
{
    int Status=-1;
    int i=0;
    int SavedDirEntry = 0;
    unsigned short next=0;

    int is_valid=FALSE;

// #todo: 
// Rever. Número máximo de entradas.
// #bugbug: 
// Esse eh o numero de entradas no diretorio raiz.

    unsigned long DirEntries = (unsigned long) (dir_entries & 0xFFFF);
    unsigned long MaxEntries = (unsigned long) FAT16_ROOT_ENTRIES;

// Address: Where to load the file.
    unsigned long Buffer      = (unsigned long) buffer;

// Size: maximum buffer size in size.
    unsigned long BufferSizeInBytes = 
        (unsigned long) (buffer_size_in_bytes & 0xFFFFFFFF);

    unsigned long z=0;  //Deslocamento do rootdir 
    unsigned long n=0;  //Deslocamento no nome.

// #bugbug: Na verdade uma rotina abaixo esta copiando
// mais do que o nome do arquivo, pois a rotina de copia
// esta copiando shorts e não chars.
// Então vamos aumentar esse buffer por enquanto.
    char tmpName[256];
    size_t FileNameSize = 0;
    unsigned long FileSize = 0;

    //int IsDirectory;

// Cluster inicial
    unsigned short cluster=0; 

// ?? 
// Primeiro setor do cluster.
    unsigned long S=0;  

// Usado junto com o endereço do arquivo.
    unsigned long SectorSize = SECTOR_SIZE;

// Sectors per cluster.
    int Spc=0;

    // #debug:
    debug_print ("fsLoadFile:\n");
    //printf      ("fsLoadFile:\n");


// Fat address and dir address.
// Vectors of 'short'

    if ( fat_address == 0 ){
        panic("fsLoadFile: [FAIL] fat_address\n");
    }

    if ( dir_address == 0 ){
        panic("fsLoadFile: [FAIL] dir_address\n");
    }

// Addresses.
    unsigned short *  fat = (unsigned short *) fat_address;
    unsigned short *__dir = (unsigned short *) dir_address;

// #debug
// We only support one address for now.

    if ( fat_address != VOLUME1_FAT_ADDRESS ){
        panic("fsLoadFile: Not valid fat address\n");
    }

//
// Initialize variables.
//

    /*
    if (____IsCdRom) {
        SectorSize = 2048;
    } else {
        SectorSize = SECTOR_SIZE;
    }
    */
 
// ...


// =======================

// How many entries in this directory.
// For now, this is the limit of the rootdir.

    //if ( MaxEntries == 0 || MaxEntries >= FAT16_ROOT_ENTRIES )
    if ( MaxEntries != FAT16_ROOT_ENTRIES )
    {
        panic ("fsLoadFile: MaxEntries limits\n");
    }

    if ( DirEntries > MaxEntries ){
        panic ("fsLoadFile: DirEntries\n");
    }

// #test: Used only for debug. 512 entries in rootdir.
    if (DirEntries != MaxEntries){
        panic ("fsLoadFile: [DEBUG] DirEntries IS LESS THE 512\n");
    }


// Buffer size in bytes
// Max = 512 pages.

    if ( BufferSizeInBytes == 0 ){
        panic("fsLoadFile: BufferSizeInBytes = 0\n");
    }


    if ( BufferSizeInBytes > (512*4096) ){
        panic("fsLoadFile: BufferSizeInBytes limits\n");
    }

// Root file system structure.
// + Checa se é válida a estrutura do sistema de arquivos.
// + Pega a quantidade de setores por cluster.
// + Pega o tamanho do diretório raiz. Ou seja, pega o número 
//    máximo de entradas.
// ...


// Root file system for the boot disk.

    if ( (void *) root == NULL ){
        panic ("fsLoadFile: root\n");
    }

    if ( root->used != TRUE || 
         root->magic != 1234)
    {
        panic ("fsLoadFile: root validation\n");
    }

    // Sectors Per Cluster.
    // #todo: We need a max limit.
    Spc = (int) root->spc;
    if (Spc <= 0){
        panic ("fsLoadFile: Spc\n");
    }

// Max entries 
// Número de entradas no rootdir.
// #bugbug: 
// Devemos ver o número de entradas no diretório corrente.
// Por enquanto so aceitamos 512.
    if ( root->dir_entries != MaxEntries )
    {
        panic ("fsLoadFile: root->dir_entries\n"); 
    }

    // ...


// Continua ... 
// Pegar mais informações sobre o sistema de arquivos.
// Busca simples pelo arquivo no diretório raiz.
// #todo: 
// Essa busca pode ser uma rotina mais sofisticada. Uma função auxiliar.
// Primero caractere da entrada:
// 0 = entrada vazia.
// $ = entrada de arquivo deletado.
// outros ...
// ATENÇÃO:
// Na verdade a variável 'root' é do tipo short.

// file name

    if ( (void *) file_name == NULL ){
        printf ("fsLoadFile: file_name\n");
        goto fail;
    }

    if ( *file_name == 0 ){
        printf ("fsLoadFile: *file_name\n");
        goto fail;
    }

//#debug
//vamos mostrar a string.
    //printf ("fsLoadFile: file_name={%s}\n", file_name);

// name size.
// Se o tamanho da string falhar, vamos ajustar.

    FileNameSize = (size_t) strlen (file_name); 

    if ( FileNameSize > 11 ){
         printf ("fsLoadFile: Name size %d\n", FileNameSize ); 
         //FileNameSize = 11;
         //return 1; //fail
         goto fail;
    }

//
// File size
//

// #bugbug
// Pegar o tamanho do arquivo e comparar com o limite do buffer.
// #bugbug: 
// Essa rotina so pega o tamanho dos arquivos que estao 
// no diretorio raiz.
// Comparando nosso tamanho obtido com o tamanho do buffer.
// Como a rotina de pegar o tamanho so pega no diretorio raiz
// por enquanto, entao vamos apenas emitir um alerta que 
// o tamanho do arquivo eh maior que o buffer, servira para debug.
// Isso porque em todas as tentativas de pegar o tamanho do arquivo
// fora do root, retornara 0.
// #todo
// Precisamos usar as estruturas de diretorio e 
// as estruturas de buffer.
    
    FileSize = 
        (unsigned long) fsGetFileSize( 
                           (unsigned char *) file_name, 
                           (unsigned long) dir_address );

// Queremos abrir um arquivo que contenha 0 bytes.
// New file.
    if (FileSize == 0)
    {
        debug_print ("fsLoadFile: [FIXME] FileSize\n");
        printf      ("fsLoadFile: [FIXME] FileSize %d\n", FileSize);
        //goto fail;
    }

// The file size can't be bigger than the buffer size.
    if ( FileSize >= BufferSizeInBytes )
    {
        debug_print ("fsLoadFile: [FIXME] Buffer Overflow\n");
             printf ("fsLoadFile: [FIXME] FileSize %d BufferSizeInBytes %d\n",
                 FileSize, BufferSizeInBytes );
        goto fail;
    }

// We are opening the root dir.

    //if ( file_name[0] == '/' && size == 1 )
    //{
    //}

//
// Search dirent
//

//
// Compare
//

// #bugbug
// #todo:
// Para a variável 'max' estamos considerando o número de
// entradas no diretório raiz. Mas precisamos considerar
// o número de entradas no diretório atual.
// >> Para isso vamos precisar de uma estrutura de diretório
// >> talvez a mesma usada em arquivos. (file)

// Descrição da rotina:
// Procura o arquivo no diretório raiz.
// Se a entrada não for vazia.
// Copia o nome e termina incluindo o char '0'.
// Compara 'n' caracteres do nome desejado, 
// com o nome encontrado na entrada atual.
// Se for encontrado o nome, então salvamos o número da entreda.
// Cada entrada tem 16 words.
// (32/2) próxima entrada! (16 words) 512 vezes!

    i=0; 
    while ( i < MaxEntries )
    {
        // Se a entrada não começar com a short '0x0000'.
        if ( __dir[z] != 0x0000 )
        {
            //#bugbug: Estamos movendo shorts e não chars.
            //memcpy ( tmpName, &__dir[z], (FileNameSize/2) );
            memcpy ( tmpName, &__dir[z], FileNameSize );
            tmpName[FileNameSize] = 0;

            Status = strncmp( file_name, tmpName, FileNameSize );

            if ( Status == 0 )
            {
                SavedDirEntry = i; 
                goto __found;
            }
        }; 
        z += 16;
        i++;
    }; 

// Not found.
// Saiu do while. 
// O arquivo não foi encontrado.

//notFound:
    debug_print ("fsLoadFile: File not found\n");
    printf      ("fsLoadFile 1: %s not found\n", file_name );  
    goto fail;

// Found.
// O arquivo foi encontrado.

__found:

    // #debug
    // printf ("file FOUND!\n");
    // refresh_screen();
    // while(1){}

//
// Cluster
//

// Get the initial cluster. 
// Check cluster Limits.
// (word). 
// (0x1A/2) = 13.
// Checar se 'cluster' está fora dos limites.
// +São 256 entradas de FAT por setor. 
// +São 64 setores por FAT. 
// Isso varia de acordo com o tamanho do disco.
// O número máximo do cluster nesse caso é (256*64).
// #todo
// Na verdade os dois primeiros clusters estão indisponíveis.

    cluster = (unsigned short) __dir[ z+13 ];

    if ( cluster <= 0 || cluster > 0xFFF0 )
    {
        debug_print ("fsLoadFile: Cluster limits\n");
        printf      ("fsLoadFile: Cluster limits %x \n", cluster );
        goto fail;
    }


// ========================================
// FAT
// Carrega fat na memória.

// #bugbug: 
// Não devemos carregar a FAT na memória toda vez que 
// formos carregar um arquivo. 
// Talvez ela deva ficar sempre na memória.
// Precisamos de estruturas para volumes que nos dê esse 
// tipo de informação

// #todo
// precisamos de uma estrutura que nos diga o tamanho
// da FAT para o volume que estamos atuando.
// Aliás, qual é o volume?

//loadFAT:
// 246?

    fs_load_fat(
        VOLUME1_FAT_ADDRESS,
        VOLUME1_FAT_LBA,
        246 );

// Load clusters.
// Carregar o arquivo, cluster por cluster.
// #todo: 
// Por enquanto, um cluster é igual à um setor, 512 bytes.
// Loop de entradas na FAT.
// #todo: 
// Esse loop é provisório, while pode ser problema.
// #todo
// Tabela temporária para salvar os números dos clusters
// usados pelo arquivo.
// ?? Qual será o tamanho dessa tabela ??

    //unsigned short tmp_table[1024];
    
    //#todo: Use while()

// #todo
// Create a helper function like this one.

    // int fsReadClusterChain ( char *file_address, short first_cluster, char *fat_address ){}

//
// == Load cluster chain ================
//

__loop_next_entry:

// #todo
// Esse while é para o caso de termos mais de um setor por cluster.
// Mas não é nosso caso até o momento.

	/*
	while(1)
	{	
	    //Calcula.
		//Primeiro setor do cluster. 
		S = fatClustToSect(cluster, Spc, VOLUME1_DATAAREA_LBA); 
		
		//Carrega 'x' setores começando de S.
		fatLoadCluster( S, file_address, Spc);
		
		//Pegar o próximo cluster na FAT.
		//O cluster atual contém o número do próximo.
		cluster = fat[cluster];
		
		//Ver se o cluster carregado era o último.
	    if(cluster == 0xFFFF || cluster == 0xFFF8){ goto done; };
		//Nothing.
    };
	*/


// #todo
// Poderia ter uma versão dessa função para ler
// um dado número de setores consecutivos.

// #todo
// #importante
// Esse é o momento em que vamos registrar na estrutura de arquivos
// quais foram os clusters usados pelo arquivo, para assim podermos
// salvar somente somente os setores modificados e não sempre o 
// arquivo todo.
// >> Mas não temos a estrutura de arquivos no momento.
// Mesmo assim, talvez ja possomos salvar os números dos clusters
// em uma tabela temporária.

    //tmp_table[tmp_table_index] = cluster;
    //tmp_table_index++;

// Some invalid address.
// We can not load a file in the same core addresses.

    is_valid = (int) __check_address_validation( (unsigned long) Buffer );
    if( is_valid != TRUE ){
        panic ("fsLoadFile: Not a valid address\n");
    }

//
// Read LBA
//

// Caution!
// Read lba.
// Increment buffer base address.
// Pega o próximo cluster na FAT.
// Configura o cluster atual.
// Ver se o cluster carregado era o último cluster do arquivo.
// Vai para próxima entrada na FAT.
// See: read_r.c

// #bugbug
// Vector overflow ?

    read_lba ( 
        Buffer, 
        ( VOLUME1_DATAAREA_LBA + cluster -2 ) ); 

    Buffer = (unsigned long) (Buffer + SectorSize); 

// #todo
// #important
// Check this value against a vector limit.
// We already did that a single time before.
// #bugbug: Não pode ser menor que 0, pois é unsigned short.

    if ( cluster <= 0 || cluster > 0xFFF0 )
    {
        panic("fsLoadFile: fat[] vector overflow.\n");
    }

    next = (unsigned short) fat[cluster];
    cluster = (unsigned short) (next & 0xFFFF);

// ?? done
// ?? message  
// salvar a tabela na estrutura de arquivo.
// Onde está a estrutura de arquivos ??
// Em que momento ela é criada ?
// #bugbug: tem arquivo carregado pelo kernel
// sem ter sido registrado na estrutura do processo kernel.

    if ( cluster == 0xFFFF || cluster == 0xFFF8 )
    { 
        return (unsigned long) 0; 
    }

    goto __loop_next_entry;

// Fail

fail:
    debug_print("fsLoadFile: [FAIL] \n");
    printf     ("fsLoadFile: [FAIL] file={%s}\n", file_name );
    refresh_screen ();
    return (unsigned long) 1;
}


// Not tested yet
unsigned long 
fsLoadFile2 ( 
    struct file_context_d *fc, 
    unsigned char *file_name )
{

    if ( (void*) fc == NULL ){
        debug_print("fsLoadFile2: fc\n"); 
        return 0;
    }

    if ( (void*) file_name == NULL ){
        debug_print("fsLoadFile2: file_name\n"); 
        return 0;
    }

    if (*file_name == 0){
        debug_print("fsLoadFile2: *file_name\n"); 
        return 0;
    }

    fc->file_name = file_name;

// #todo
// Return type.

    return fsLoadFile ( 
               (unsigned long)   fc->fat_address,
               (unsigned long)   fc->dir_address,
               (int)             fc->dir_entries,
               (unsigned char *) fc->file_name, 
               (unsigned long)   fc->file_address,
               (unsigned long)   fc->buffer_limit );
}


/*
 * fsLoadFileFromCurrentTargetDir:
 * 
 *     Carrega o diretório que está configurado como 'target dir' 
 * em algum lugar qualquer da memória. 
 *     Usa-se a estrutura current_target_dir pra gerenciar isso.
 */

// #bugbug
// too much allocation.
// How many times this function is called ??
// 4KB each time ?

int fsLoadFileFromCurrentTargetDir (void)
{
    int Ret = -1;
    int i=0;
    unsigned long new_address = 0;

// #bugbug
// 4KB

    unsigned long xxxTempFileSize = 4096;

    debug_print ("fsLoadFileFromCurrentTargetDir: [FIXME] Loading dir \n");

	//#bugbug
	//Isso 'e um limite para o tamanho do arquivo (apenas dir).
	//precisamos expandir isso.
	//aqui no m'aquimo o arquivo pode ter 4kb.
	//acho ques estamos falando somente de diret'orio aqui.

// #bugbug
// too much allocation.
// How many times this function is called ??
// 4KB each time ?

    new_address = (unsigned long) kmalloc ((size_t)xxxTempFileSize);

    if ( new_address == 0 ){
        debug_print ("fsLoadFileFromCurrentTargetDir: new_address\n");
        return -1;
    }

    current_target_dir.current_dir_address = (unsigned long) new_address;

    // ??
    // Se o endereço atual falhar, 
    // resetamos ele e retornamos.

    if ( current_target_dir.current_dir_address == 0 ){
        debug_print ("fsLoadFileFromCurrentTargetDir: [FAIL] invalid address\n");
        goto fail;
    }

	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) old_dir_addr=(%x) #debug \n",
	//    current_target_dir.name, current_target_dir.current_dir_address );


    //++
    //taskswitch_lock ();
    //scheduler_lock ();
    Ret = (int) fsLoadFile ( 
                    (unsigned long) VOLUME1_FAT_ADDRESS,                       // fat cache address
                    (unsigned long) current_target_dir.current_dir_address,    // src dir address 
                    (int) FAT16_ROOT_ENTRIES, //#bugbug: Number of entries.          // number of entries.
                    (const char *) current_target_dir.name,                 // file name 
                    (unsigned long)   current_target_dir.current_dir_address,  // file address
                    (unsigned long) xxxTempFileSize );                                    // #bugbug buffer limit 4KB.
    //scheduler_unlock ();
    //taskswitch_unlock ();
    //--


	//#debug
	//printf ("fsLoadFileFromCurrentTargetDir: dir_name=(%s) new_dir_addr=(%x) #debug \n",
	//   current_target_dir.name, current_target_dir.current_dir_address );

    debug_print ("fsLoadFileFromCurrentTargetDir: done\n");
    return (int) Ret;

fail:
    
    // #todo
    // debug message.
    
        current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
        for ( i=0; i<11; i++ ){
            current_target_dir.name[i] = '\0';
        };
        current_target_dir.name[0] = '/';
        current_target_dir.name[1] = '\0';
        return -1;
}


/*
 * fsUpdateWorkingDiretoryString:
 * 
 *     +Atualiza o pathname na estrutura do processo atual.
 *     +Atualiza o pathname na string global. 
 */ 

// Used by the service 175, cd command.

void fsUpdateWorkingDiretoryString ( char *string )
{
    struct process_d  *p;
    char *tmp;
    int i=0; 
    int string_size = 0;

    debug_print ("fsUpdateWorkingDiretoryString:\n"); 

    tmp = string;
    string_size = sizeof(string);


    pid_t current_process = (pid_t) get_current_process();


    // Initialized ?
    if ( CWD.initialized != TRUE )
    {
        debug_print ("fsUpdateWorkingDiretoryString: [FAIL] CWD not initialized\n"); 
        
        // #todo
        // Call the initialization routine.
        
        return;
    }

    // string

    if ( (void *) string == NULL ){
        debug_print ("fsUpdateWorkingDiretoryString: string\n"); 
        return;  
    }

    if (*string == 0){
        debug_print ("fsUpdateWorkingDiretoryString: *string\n"); 
        return;  
    }


    if (string_size <= 0){
        debug_print ("fsUpdateWorkingDiretoryString: [FAIL] string_size\n"); 
        return;  
    }

    // Current process.

    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");
    }else{
        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: p validation\n");
        }

        // Atualiza a string do processo atual. 
        // Concatenando.
        
        if ( (void *) string != NULL )
        {
            // #bugbug
            // We need to handle the string size limit.
            
            // Concatena string.
            strcat ( p->cwd_string, string );

            // Concatena separador.
            strcat ( p->cwd_string, FS_PATHNAME_SEPARATOR );

            // Atualiza a string global usando a string do 
            // processo atual.
            // #bugbug: nao precisamos disso ...
            // so precismos de cwd na estrutura de processo.
            
            // #importante
            // Respeitar o limite.
            
            for ( i=0; i<32; i++ )
            {
                CWD.path[i] = p->cwd_string[i];
            };
            CWD.path[31] = 0; //finaliza

            // #bugbug: rever isso.
            // Nome do diretório alvo atual.
            
            // nao precismos disso ...
            // ou usamos o cwd do processo ou
            // o diretorio raiz para paths absolutos.
            
            for ( i=0; i< 11; i++ )
            {
                current_target_dir.name[i] = *tmp;
                tmp++;
            };
            current_target_dir.name[11] = 0; //finaliza
        }
    };

    debug_print ("fsUpdateWorkingDiretoryString: done\n"); 
}

// helper function to handle fat cache status.
void fs_fat16_cache_not_saved(void)
{
    fat_cache_saved = FAT_CACHE_NOT_SAVED;
}

/*
 ************************************************
 * fs_fntos:
 *     
 *     'file name to string'.
 * 
 *     rotina interna de support.
 *     isso deve ir para bibliotecas depois.
 *     não tem protótipo ainda.
 * 
 * Created by: Luiz Felipe.
 * 2020 - Adapted by Fred Nora.
 */

 // #bugbug
 // Isso modifica a string lá em ring3.
 // prejudicando uma segunda chamada com a mesma string
 // pois já virá formatada.

// #bugbug
// const char * tornaria esse endereço em apenas leitura.

void fs_fntos ( char *name )
{
    int i  = 0;
    int ns = 0;

    char ext[4];
    ext[0] = 0;  ext[1] = 0;  ext[2] = 0;  ext[3] = 0;

    //#test

    if ( (void*) name == NULL ){ return; }

    if (*name == 0){ return; }


    // Transforma em maiúscula enquanto não achar um ponto.
    // #bugbug: E se a string já vier maiúscula teremos problemas.

    while ( *name && *name != '.' )
    {
        if ( *name >= 'a' && *name <= 'z' )
        {
            *name -= 0x20;
        }

        name++;
        ns++;
    };

    // #bugbug
    // Esse negócio de acrescentar a extensão
    // não é bom para todos os casos.

    if ( name[0] == '\0' && ns <= 8 )
    {
        ext[0] = 'B';  ext[1] = 'I';  ext[2] = 'N';  ext[3] = '\0';

        goto CompleteWithSpaces;
    }

    //if ( name[0] == '.' && ns < 8 )

    // Aqui name[0] é o ponto.
    // Então constrói a extensão colocando
    // as letras na extensão.

    for ( i=0; i < 3 && name[i+1]; i++ )
    {
        //Transforma uma letra da extensão em maiúscula.
 
        //if (name[i+1] >= 'a' && name[i+1] <= 'z')
        //    name[i+1] -= 0x20;

        //ext[i] = name[i+1];
    

        //#testando
        //Se não for letra então não colocamos no buffer de extensão;
        if ( name[i+1] >= 'a' && name[i+1] <= 'z' )
        {
            name[i+1] -= 0x20;

            ext[i] = name[i+1];
        }
    };



CompleteWithSpaces:

// Acrescentamos ' ' até completarmos as oito letras do nome.
// Acrescentamos a extensão
// Finalizamos.
 
    while (ns < 8)
    {
        *name++ = ' ';
        ns++;
    };

    for (i=0; i < 3; i++){  
        *name++ = ext[i];  
    };

    *name = '\0';
}


// Pega um fd na lista de arquivos do processo, dado o PID.
// Objects[i]

int fs_get_free_fd_from_pid (int pid)
{
    struct process_d *p;
    int __slot=0;


    //#todo max
    if ( pid<0 ){
        debug_print ("fs_get_free_fd_from_pid: [FAIL] pid\n");
        return -1;
    }

    // #bugbug
    // Check limit

//
// Process.
//
  
    p = (struct process_d *) processList[pid];
    if ( (void *) p == NULL ){
        debug_print ("fs_get_free_fd_from_pid: p\n");
        return -1;
    }
    if ( p->used != 1 || p->magic != 1234 ){
        debug_print ("fs_get_free_fd_from_pid: p validation\n");
        return -1;
    }


// Pick a free one.
// and return the index.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ return (int) __slot; }
    };

// fail.
    return -1;
}


/*
 * fs_initialize_process_cwd:
 *     Cada processo deve inicialiar seus dados aqui. 
 */

// #todo:
// handle return value ...
// What functions is calling us?

int fs_initialize_process_cwd ( int pid, char *string )
{
    struct process_d *p;
    int i=0;


    if (pid<0){
        debug_print ("fs_initialize_process_cwd: pid\n");
        return 1;
    }

// string

    if ( (void *) string == NULL ){
        panic ("fs_initialize_process_cwd: string\n");
        //return 1;
    }
    if (*string == 0){
        panic ("fs_initialize_process_cwd: *string\n");
        //return 1;
    }

// Current process.
// #importante
// Vamos copiar a string para a estrutura do processo atual.

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_initialize_process_cwd: p\n");
    }else{
        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_initialize_process_cwd: validation\n");
        }

        // ?? fixed size.
        for ( i=0; i<32; i++ ){ p->cwd_string[i] = string[i]; }
        
        p->cwd_string[31] = 0; // finalizing 
    };

    return 0;
}


/*
 * fs_load_path:
 *     Carrega nesse endereço o arquivo que está nesse path.
 *     ??: O endereço pode ser ring3?
 *     n levels.
 */

// IN:
// path:
//     Path de dois níveis.
//     Ex: "/BIN/GDESHELL.BIN"
// address:
//     Address to load the file.
// buffer_size:
//     Size of the buffer for the file.

// #bugbug
// Starts only on root dir.

// #ok
// Carregou um arquivo com 3 niveis.

// See:
// sys_load_path() and service 4004.

//    0 ---> ok.
// != 0 ---> fail

// #todo
// is address virtual or physical?
// Change this name to pa or va.
// Change to buffer_size_in_bytes ?

int 
fs_load_path ( 
    const char *path, 
    unsigned long address, 
    unsigned long buffer_size )
{

// #todo
// Work on that limit stuff.
// We have the limit given by the argument,
// that needs to be respected.
// And we have the size of the root dir.

    unsigned long MaxEntries = FAT16_ROOT_ENTRIES;  //512

    int i=0;         // Deslocamento dentro do buffer.
    int level=0;
    int l=0;
    unsigned long n_levels = 0;
    
    // Fail. 
    // Usado na função que carrega o arquivo.
    int Ret = -1;    
        
    char buffer[12];
    unsigned char *p;

    // Onde carregaremos o diretório.
    void *__src_buffer;
    void *__dst_buffer;
    void *__file_buffer;


// Path
    if ( (void*) path == NULL ){
        panic ("fs_load_path: path\n"); 
    }
    if (*path == 0){
        panic ("fs_load_path: *path\n"); 
    }

// Address
    if (address == 0){
        panic ("fs_load_path: address\n");
    }

// Buffer size
    if (buffer_size == 0){
        panic ("fs_load_path: buffer_size\n");
    }

//===================================

// File buffer
    __file_buffer = (void *) address;

// Counting the levels.
// Start with 0.
    n_levels = fs_count_path_levels(path);
    if (n_levels==0){
        panic ("fs_load_path: n_levels\n");
    }

    // #debug
    printf ("fs_load_path: path with %d levels\n",n_levels);
    
    level = 0;

// Local pointer.
    p = path;


// #bugbug
// Overflow quando colocarmos um diretorio maior que o buffer.

    // Primeiro src =  root address;
    __src_buffer = (void *) VOLUME1_ROOTDIR_ADDRESS;
    
    // 512 entradas de 32bytes.
    unsigned long limits = (512*32);


    // Not absolute   
    if ( p[0] != '/' ){
        panic ("fs_load_path: Not absolute pathname \n");
    }

//
// loop: 
// Carregar n levels.
//

    for (l=0; l<n_levels; l++)
    {
        printf ("[LEVEL %d]\n",l);

        // The level needs to start with '/', even the first one.
        if ( p[0] != '/' ){
            panic ("fs_load_path: All levels need to start with '/' \n");
        }

        // Skip the '/'.
        p++;

        // Walk 13 chars in the same level.
        for ( i=0; i<12; i++ )
        {
            // Copia o char para o buffer até que o char seja '/'
            // indicando inicio do próximo nível.
            // E se não houver próximo nível?
            // #debug Show the char.

            buffer[i] = (char) *p;

            printf ("%c", (char) *p);

            // + O ponto deve aparecer no último nível.
            // caso contrário falhou
            // + Precisa ter extensao por enquanto.
            // + Se o ponto está além do limite permitido.
            // + Se o ponto for antes do nono byte. OK.

            if ( *p == '.' )
            {
                if ( l != (n_levels-1) ){
                    panic ("fs_load_path: '.' found into a subdirectory\n");
                }

                // #bugbug
                // We can't start a filename with a dot.
                if (i == 0){
                    panic ("fs_load_path: [fail] Filename starting with a dot.\n");
                }

                // #bugbug
                // igual a 8 eh normal, maior que 8 eh problema
                if (i > 8){
                    panic ("fs_load_path: Filename bigger than 8.\n");
                }

                // O ponto foi encontrado dentro do range permitido.

                // Nome tem no máximo 8 chars.
                // Completamos com espaço, pois queremos o formato:
                // "FILE    123"
                if( i<=7 )
                {
                    while (i<=7){ 
                        buffer[i] = ' '; 
                        i++; 
                    };
                }
                
                if( i == 7 )
                    i=8;
                
                // Skip the dot '.'.
                // Yes it is a dot. See the IF statement above.
                p++;
                
                if( i != 8 ){
                    panic("fs_load_path: Extension base fail\n");
                }

                // Add the extension.
                //i=8;  // [8] [9] [10]
                while (i<11)
                {
                    if( *p == 0 ){ break; }
                    
                    buffer[i] = (char) *p;
                    i++;
                    p++;
                };
                
                //se o break funcionou.
                if(i<11){
                    while(i<11){
                        buffer[i] = ' ';  // 0 or ' '?
                        i++;
                    };
                }
                
                // Finalize the string.
                buffer[11] = 0;
                     
                printf ("\n");
                printf ("fs_load_path: This is the name {%s}\n",buffer); 


                //
                // Load file.
                //
    
                // Como esse é o último, então vamos usar o endereço desejado pelo usuário.
                __dst_buffer = (void *) __file_buffer;
    
                if ( (void *) __dst_buffer == NULL ){
                    panic ("fs_load_path: __dir\n");
                }

                
                // #bugbug
                // Se o diretório for o diretório raiz
                // então não podemos sondar menos que 512 entradas.
                // #todo: Temos que considerar o número de entradas
                // exatos de um diretório.
                // Podemos ter um limite estabelecido pelo sistema.
                
                // IN: 
                // fat address, dir address, filename, file address.
                
                // Load the file. (The last level)
                Ret = fsLoadFile ( 
                          (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                          (unsigned long) __src_buffer,         // dir address. onde procurar. 
                          (unsigned long) MaxEntries,          // #bugbug: Number of entries. 
                          (unsigned char *) buffer,             // nome 
                          (unsigned long) __dst_buffer,         // addr. Onde carregar.
                          limits );                             // tamanho do buffer onde carregar.             
                // ok.
                if ( Ret == 0 )
                {
                    printf ("Level %d loaded!\n\n",l);
                    
                    // #importante
                    // Esse nível tinha ponto, então deveria ser o último.
                    if ( l != (n_levels-1) )
                    {
                        printf ("fs_load_path: Directory name with '.'\n");
                        panic ("It needs to be the last level.\n");
                    }

                    // SUCCESS ?!!
                    debug_print ("fs_load_path: done\n");
                    return 0;

                }else{
                    panic ("fs_load_path: [FAIL] Loading level 0\n");
                };
            }


            // Se encontramos um indicador de próximo nível,
            // então esse nível não será considerado binário.
            // obs: 
            // Ao iniciar o for ele precisa encontrar esse mesmo char.
            
            if ( *p == '/' )
            {
                // Encontramos o indicador de proximo nivel,
                // o buffer ja tem chars que foram colocados um a um.
                // Nao encontramos ponto nesse nivel.
                // Vamos completar o nome do diretorio com espaços e finalizar.
                
                if (i<11)
                {
                    // Adicionando espaços.
                    // O formato desejado eh: "DIRXDIRX   "
                    // Nome do diretorio sem extensao.
                    while (i<11)
                    { 
                        //o primeiro espaço deve retirar a barra colocada antes
                        buffer[i] = ' ';  
                        i++; 
                    }
                }
                
                // Finalize the string.
                buffer[11] = 0;
                
                printf ("\n");
                printf ("fs_load_path: This is the name {%s}\n",buffer);

                //
                // Load directory.
                //

                // #bugbug
                // E se o arquivo for maior que a area alocada.
                // Alocando memória para carregar o diretório.
                
                unsigned long BUGBUG_OVERFLOW = (512*32);
                limits = BUGBUG_OVERFLOW;
                
                __dst_buffer = (void *) kmalloc (    BUGBUG_OVERFLOW    ); 
    
                if ( (void *) __dst_buffer == NULL ){
                    panic ("fs_load_path: __dir\n");
                }

                // IN: 
                // fat address, dir address, filename, file address.

                // Load the directory. (Not the last level)
                Ret = fsLoadFile ( 
                          (unsigned long) VOLUME1_FAT_ADDRESS,  // fat address
                          (unsigned long) __src_buffer,         // dir address. onde procurar.
                          (int) MaxEntries,                           // #bugbug: Number of entries.  
                          (const char *) buffer,             // nome que pegamos no path 
                          (unsigned long) __dst_buffer,         // onde carregar. 
                          (unsigned long) limits );                             // tamanho do buffer onde carregar.
                          
                          
                // ok.
                if ( Ret == 0 )
                {
                    printf ("Level %d loaded!\n\n",l);
                    
                    // O endereço onde carregamos o arquivo desse nível
                    // será o endereço onde vamos procurar o arquivo do próximo nível.
                    __src_buffer = __dst_buffer;
                    
                    break;

                }else{
                    panic ("fs_load_path: [*FAIL] Loading level 0\n");
                };
            }


            // Avançamos o char se não foi '.', nem '/'.
            p++;
        };
    };   

fail:
    debug_print ("fs_load_path: Fail\n");
    printf      ("fs_load_path: Fail\n");
    refresh_screen();
    return (-1);
}


/* 
 * fs_pathname_backup:
 *     Remove n nomes de diret�rio do pathname do processo indicado no 
 * argumento.
 *     Copia o nome para a string global.
 *     Remove the last N directories from PATH.  
 *     Do not leave a blank path.
 *     PATH must contain enough space for MAXPATHLEN characters. 
 *     #obs: O PID costuma ser do processo atual mesmo. 
 *     Credits: bash 1.05 
 */

// #todo: Describe 'n'.

void fs_pathname_backup ( int pid, int n ){

    struct process_d *p;
    int i=0;

// CWD

    if ( CWD.initialized != TRUE ){
        printf ("fs_pathname_backup: [FAIL] CWD not initialized\n"); 
        return;
    } 

// pid

    if ( pid<0 ){
        printf ("fs_pathname_backup: [FAIL] pid\n"); 
        return;
    }

// n

    if (n<0) {  return;  }
    if (n==0){  return;  }

// Process

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fsUpdateWorkingDiretoryString: p\n");
    }else{
        if ( p->used != TRUE || p->magic != 1234 ){
            panic ("fsUpdateWorkingDiretoryString: validation\n");
        }

        char *path = (char *) p->cwd_string;

        register char *s = path + strlen( path );
 
        if (*path){ s--; };

        while (n--)
        {
            while (*s == '/'){ s--; };
            while (*s != '/'){ s--; };

            *++s = '\0';
        };

        // Atualizando a string global.
        for ( i=0; i<32; i++ ){
            CWD.path[i] = p->cwd_string[i];
        };

        // Name.
        for ( i=0; i< 11; i++ ){
            current_target_dir.name[i] = '\0';
        };
    };
}


/*
 * fs_print_process_cwd
 *     Cada processo tem seu proprio pwd.
 *     Essa rotina mostra o pathname usado pelo processo. 
 */

// this is used by the pwd command. service 170.

int fs_print_process_cwd (int pid)
{
    struct process_d *p;


    debug_print ("fs_print_process_cwd:\n");
    printf      ("fs_print_process_cwd:\n");

// pid

    if (pid<0){
        debug_print ("fs_print_process_cwd: [FAIL] pid\n");
        return -1;
    }

// Process

    p = (struct process_d *) processList[pid];

    if ( (void *) p == NULL ){
        panic ("fs_print_process_cwd: p\n");
    }else{
        if ( p->used != 1 || p->magic != 1234 ){
            panic ("fs_print_process_cwd: validation\n");
        }

        // #bugbug
        // Is this element a pointer or a buffer ?
        // >>> This element is an array.
        
        if ( (void *) p->cwd_string != NULL )
        {
            //p->cwd_string[31] = 0;
            printf ("> PID=%d p->cwd_string {%s} \n", 
                p->pid, p->cwd_string);
        }

        // #bugbug
        // Is this element a pointer or a buffer ?

        if ( (void *) current_target_dir.name != NULL )
        {
            //current_target_dir.name[31] = 0;
            printf ("> PID=%d current_target_dir.name {%s} \n", 
                p->pid, current_target_dir.name);
        }

        refresh_screen();
        return 0;
    };

// fail
    debug_print ("fs_print_process_cwd: fail\n");   
    return -1;
}


void fs_show_file_info (file *f)
{

    if ((void*)f==NULL)
    {
        debug_print("fs_show_file_info: fail\n");
        return;
    }

    if (f->used == TRUE)
    {
        if ( (void*) f->_tmpfname != NULL )
        {
            printf ("Name={%s}\n",f->_tmpfname);
            //refresh_screen();
        }
    }
}


void fs_show_file_table(void)
{
    file *f;
    int i=0;


    printf ("\nfile_table:\n");
    
    for (i=0; i<32; i++)
    {
        f = (file*) file_table[i];
        
        if( (void*)f != NULL )
            fs_show_file_info(f);
    };

    refresh_screen();
}

void fs_show_inode_info (struct inode_d *i)
{
    if ( (void *) i == NULL )
    {
        debug_print("fs_show_inode_info: fail\n");
        return;
    }

    if (i->used == TRUE)
    {
        if ( (void*)i->path != NULL )
        {
            printf ("Name={%s}\n",i->path);
        }
    }  
}

void fs_show_inode_table(void)
{
    struct inode_d *inode;
    register int i=0;


    printf ("\n inode_table: \n");
    
    for (i=0; i<32; ++i)
    {
        inode = (struct inode_d *) inode_table[i];
        
        if ( (void*)inode != NULL )
        {
            if( inode->used == 1 && inode->magic == 1234 )
            {
                fs_show_inode_info(inode);
            }
        }
    };

    refresh_screen();
}

void fs_show_root_fs_info(void)
{
    //printf ("\n");
    printf ("fs_show_root_fs_info:\n");

// root fs structure.

    if ( (void *) root == NULL ){
        printf ("No root structure\n");
        goto fail;
    
    }else{

        if ( root->used != 1 || root->magic != 1234 ){
             printf ("Validation fail\n");
             goto fail;
        }

        printf ("name = %s \n",       root->name );
        printf ("Object type %d \n",  root->objectType );
        printf ("Object class %d \n", root->objectClass );
        printf ("type = %d \n",       root->type );
        printf ("Dir entries %d \n",  root->dir_entries );
        printf ("Entry size %d \n",   root->entry_size );
        // ...
        goto done;
    }; 

fail:
    printf("fail\n");
done:
    refresh_screen();
    return;
}


// sys_pwd -  Service 170.
void sys_pwd (void)
{
    // #todo: Check overflow.

    pid_t current_process = (pid_t) get_current_process();

    if ( current_process < 0 || 
         current_process >= PROCESS_COUNT_MAX )
    {
        panic ("sys_pwd: [FAIL] current_process\n");
    }

    fs_print_process_cwd (current_process);
}


/*
 * fsSaveFile:
 *     Salva um arquivo no disco.
 *     Somente no diretório raiz.
 */

// It was called by sys_write_file() in fs.c.
// It was called by sys_read_file when the file does not exist.
// #obs
// Isso salva um arquivo.
// Também poderia ser usado para criar um arquivo ou diretório ? 
// #todo: #test
// Número máximo de entradas na lista de clusters. 
// Quantas?
// A FAT tem 246 setores, 123 KB
// fsSaveFile:
//     Salva um arquivo. 
//     Onde? #todo vamos fornecer o endereço do diretorio.
// IN: 
// name, size in sectors, size in bytes, adress, flag. 
// OUT:
// #bugbug
// O nome nao esta ficando certo na entrada.
// #todo
// is dir_address virtual or physical?
// Change this name to dir_pa or dir_va.

int
fsSaveFile ( 
    unsigned long fat_address,
    unsigned long dir_address,
    int dir_entries,
    const char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{

    int Status = 0;

    unsigned long i = 0; 
    unsigned long j = 0;    // Deslocamento na lista, tem que ser zero.
    unsigned long c = 0;    // Deslocamento na FAT.

    unsigned short first=0;
    unsigned short next=0;
    unsigned short sector=0;

    // Directory entry buffer.
    char DirEntry[32];

    //Entry size in words.
    int EntrySize = 0;
    int Offset = 0;
    int FreeIndex = -1;


    // #debug:
    debug_print ("fsSaveFile:\n");
    //printf      ("fsSaveFile:\n");


    // Updating fat address and dir address.
    
    if ( fat_address == 0 ){
        panic("fsSaveFile: [FAIL] fat_address\n");
    }

    if ( dir_address == 0 ){
        panic("fsSaveFile: [FAIL] dir_address\n");
    }

    unsigned short *fat   = (unsigned short *) fat_address; //VOLUME1_FAT_ADDRESS;
    unsigned short *__dir = (unsigned short *) dir_address; //VOLUME1_ROOTDIR_ADDRESS;


    // #debug
    // We only support one address for now.
    if ( fat_address != VOLUME1_FAT_ADDRESS ){
        panic("fsSaveFile: [FIXME] We only support ONE fat address for now!\n");
    }


    if ( (void *) file_name == NULL )
    {
        debug_print ("fsSaveFile: [ERROR] file_name\n");
        printf      ("fsSaveFile: [ERROR] file_name\n"); 
        goto fail;
    }

    if ( *file_name == 0 )
    {
        debug_print ("fsSaveFile: [ERROR] *file_name\n");
        printf      ("fsSaveFile: [ERROR] *file_name\n"); 
        goto fail;
    }


    // #bugbug
    // Esse endereço eh valido ?
    
    /*
    printf ("name address = %x \n", &file_name );
    printf ("name    = %s \n", file_name ); 
    printf ("size    = %d \n", file_size );       // Size in sectors.
    printf ("nbytes  = %d \n", size_in_bytes );
    printf ("address = %x \n", file_address );
    printf ("flag    = %x \n", flag );
    printf ("entries = %d \n", dir_entries );
    */

    if ( dir_entries == 0 || dir_entries > FAT16_ROOT_ENTRIES )
    {
        panic ("fsSaveFile: [FAIL] max dir entries");
    }


	// file_size
	// #todo: 
	// precisamos implementar um limite para o tamanho do arquivo,
	// principamente nessa fase de teste.

    // #bugbug
    // Limite provisorio
    if ( file_size > 16 )
    {
        debug_print ("fsSaveFile: [FIXME] Size in sectors\n");
        printf      ("fsSaveFile: [FIXME] Size in sectors = %d \n", 
            file_size ); 
        goto fail;
    }

// Load root dir and FAT.
    fs_load_rootdir( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );
    fs_load_fat(VOLUME1_FAT_ADDRESS,VOLUME1_FAT_LBA,246);

// Procurando cluster livre na fat.
// Nesse momento construimos uma lista de clusters livres.
// #todo: 
// Essa lista já devia existir e agora somente 
// usaríamos.
// #todo: Essa rotina poderia seruma helper function?

//SearchEmptyEntries:
 
	// #bugbug
	// Obs: Esse limite é improvisado.

    while ( i < CLUSTERS_TO_SAVE_MAX )
    {
        //procurando cluster livre na fat.
        //@todo:isso poderia ser uma função.

        if (fat[c] == 0)
        {
            // Encontrado todos os espaços livres 
            // que o arquivo precisa.
            // Marca o fim.
            // #importante: 
            // Se der certo, saímos do loop.
            // #bugbug: Esse size deve ter um limite.
            // file_size = file size in sectors, (clusters??)
            if (file_size == 0)
            {
                fat16ClustersToSave[j] = (unsigned short) 0xfff8; 
                goto save_file;
            }

            //salva um endereço livre
            //salvamos um índice na fat dentro da lista
            //incrementa a lista

            fat16ClustersToSave[j] = (unsigned short) c; 
            j++; 

            // Decrementa o tamanho do arquivo!
            file_size--; 
        };

        c++;    // Incrementa o deslocamento na fat. 
        i++;    // Incrementa a quantidade de busca.
    }; 

    // Fail
    // Nossa busca por clusters livres dentro da fat não deu certo.
    // Provavelmente não encontramos uma quantidade suficiente.

out_of_range:  

    printf ("fsSaveFile: No free cluster \n");
    goto fail;


    // #debug
    //refresh_screen();
    //while(1){ asm("hlt"); }

// #importante:
// Deu certo. Encontramos na fat todos os clusters que o arquivo precisa.   
// Salva o arquivo.
// O arquivo tem na lista todos os clusters que ele precisa.

    //
    // Save!
    // 

save_file:

    //#debug
    //printf("fsSaveFile: save_file: \n"); 
    //refresh_screen();
  
    // Início da lista.
    i = 0; 

    //
    // Size limits.
    //

    // #bugbug
    // Limite máximo improvisado.
    // 2KB.

    j = (512*4); 

    // Pegamos o primeiro da lista.
    first = fat16ClustersToSave[i];

	// #debug
	// printf("first={%x}\n",first);

    // Create directory entry
    // Name/ext 8.3

    DirEntry[0]  = (char) file_name[0];
    DirEntry[1]  = (char) file_name[1];
    DirEntry[2]  = (char) file_name[2];
    DirEntry[3]  = (char) file_name[3];
    DirEntry[4]  = (char) file_name[4];
    DirEntry[5]  = (char) file_name[5];
    DirEntry[6]  = (char) file_name[6];
    DirEntry[7]  = (char) file_name[7];
    DirEntry[8]  = (char) file_name[8];
    DirEntry[9]  = (char) file_name[9];
    DirEntry[10] = (char) file_name[10];

    // Flag. (attributes ?)
    //====================
    // 0x01: read only
    // 0x02: hidden
    // 0x04: system
    // 0x08: volume label
    // 0x10: * Directory
    // 0x20: * Archive
 
    DirEntry[11] = flag; 

    // Reserved.
    DirEntry[12] = 0; 

    // Creation time. 14 15 16
    DirEntry[13] = 0x08;  DirEntry[14] = 0x08;  DirEntry[15] = 0xb6;

    // Creation date.
    DirEntry[16] = 0xb6;  DirEntry[17] = 0x4c;

    // Access date.
    DirEntry[18] = 0xb8;  DirEntry[19] = 0x4c;

	// ??
	// First cluster. 
	// 0 para fat12 ou 16
    DirEntry[20] = 0;
    DirEntry[21] = 0;

    // Modifield time.
    DirEntry[22] = 0xa8;  DirEntry[23] = 0x49;

    // Modifield date.
    DirEntry[24] = 0xb8;  DirEntry[25] = 0x4c;

    // First cluster. Low word.
    // 0x1A and 0x1B
    DirEntry[26] = (char) (first); 
    DirEntry[27] = (char) (first >> 8); 

    // size_in_bytes - File size in bytes.
    // 4 bytes: (28,29,30,31)

    DirEntry[28] = (char) size_in_bytes;
    size_in_bytes = (size_in_bytes >> 8);
    DirEntry[29] = (char) size_in_bytes;
    size_in_bytes = (size_in_bytes >> 8);
    DirEntry[30] = (char) size_in_bytes;
    size_in_bytes = (size_in_bytes >> 8);
    DirEntry[31] = (char) size_in_bytes;

	// #importante:
	// Vamos encontrar uma entrada livre no diretório para
	// salvarmos o nome do arquivo.
	// Copia o nome para dentro da entrada do diretório.
	// Obs: As entradas são de 32 bytes. Como root[] é um 
	// array de short então faremos um deslocamento de 16 shorts.
	// root[]
	// #importante: root[] é um array de short.	
	// IN: 
	// Endereço do diretótio e número máximo de entradas.
	// #todo: 
	// Talvez possamos ampliar esse número para o máximo 
	// de entradas no diretório.
	// #bugbug: A quantidade de entrada depende to diretório.
	// See: search.c


    // IN: 
    // directory address, max number of entries.
    
    FreeIndex = (int) findEmptyDirectoryEntry ( 
                          dir_address, 
                          dir_entries );

    if ( FreeIndex == -1 ){
        printf ("fsSaveFile: [FAIL] No empty entry\n");
        goto fail;
    }

    // 32/2 = 16 words.
    // Offset:
    // Deslocamento dentro do diretório.
    // representa o início da entrada que encontramos.
    // Encontramos multiplicando o índice da entrada pelo 
    // tamanho da entrada.
    // Copy entry into the root in the memory.
    // Copia 32 bytes.
 
    EntrySize = (FAT16_ENTRY_SIZE/2);
    Offset = (int) ( FreeIndex * EntrySize );

    // FAT16_DIRENTRY_SIZE = 32
    memcpy ( &__dir[Offset], DirEntry, 32 );

// reset
// Reiniciamos o controlador antes de usarmos.


//resetIDE:

	//#debug
	//printf("fsSaveFile: reset and while\n"); 
    //refresh_screen();

	//reset_ide0 ();
	
	// ## Save ##
    // Vamos ao salvamento propriamente dito.

    i=0; 

	//#debug 
	//improvisando um endereço válido

    unsigned long address = (unsigned long) file_address;


    //
    // Save!
    //
    
    // Saving the file into the disk.
    // Cluster by cluster.

//SavingFile:

    // Routine:
    // +Pega um conteúdo da lista.
    // +Encontrada a assinatura na lista!
    // ...

    // #bugbug
    // E se o primeiro for um marcador de fim de arquivo?

    //next = list[0];
    //if (next == 0xFFF8)
        //what??


    // Loop

    while (TRUE){
 
        // Pegamos o atual na lista.
        // Se ele eh o sinalizador de fim de lista, 
        // entao entao colocamos o sinalizador de fim de arquivo
        // no offset indicado pelo penultimo elemento da lista.
        
        next = fat16ClustersToSave[i];

        // #debug.
        printf ("fsSaveFile: [DEBUG] next={%x}\n", next);

        if ( next == 0xFFF8 ){

            next = fat16ClustersToSave[i-1];
            
            fat[next] = 0xFFF8;

            goto do_save_dir_and_fat;

        // Se não é assinatura ainda.
        }else{

            // #bugbug
            // Estamos usando isso sem nem mesmo checar seu valor.
            // precisamos de limtes aqui. Para evitarmos overflow.
            
            // Grava na fat o endereço do próximo cluster
            fat[next] = fat16ClustersToSave[i+1];
 
            //#debug 
            //printf("write_lba\n");
            //refresh_screen();

            disk_ata_wait_irq ();

            //grava - aqui next esta certo!!!
            //write_lba ( (unsigned long) address, VOLUME1_DATAAREA_LBA + next -2 );
            ataWriteSector ( 
                (unsigned long) address, 
                (unsigned long) ( VOLUME1_DATAAREA_LBA + next -2), 
                0, 
                0 );

            address += 512; 
        }; 

        //Próximo valor da lista.
        i++;

        // #bugbug
        // Limitando o tamanho do arquivo a 16 entradas.
        // Why??

        // #bugbug
        // Limite provisorio.
        if (i > 16)
        {
            debug_print ("fsSaveFile: [FIXME] write sectors limit\n");
            printf      ("fsSaveFile: [FIXME] write sectors limit\n");
            goto fail;
        }

        // ??
    };

    //
    // FAIL
    //

    debug_print ("fsSaveFile: Loop fail\n");
    goto fail;
   
    //
    // == done ========================================
    //

    // Saving rood dir and FAT.
    // Nesse momento já salvamos os clusters do arquivo.
    // OK. Funcionou no qemu.
    // #bugbug
    // Não vamos mais salvar a fat toda vez que salvarmos
    // um arquivo.
    // Vamos salvar a FAT apenas no fim da sessão.
    // Como ainda não temos shutdown, então vamos salvar 
    // quando chamarmos reboot.
    // #important
    // Updating the cache state.

do_save_dir_and_fat:

    debug_print ("fsSaveFile: [DEBUG] do_save_dir_and_fat\n");
    
    // Save root
    // #bugbug: We need to save a directory, not the root.

    // IN: root dir address, root dir lba, root dir size in sectors.

    //if ( dir_address == ROO...
    fs_save_rootdir( VOLUME1_ROOTDIR_ADDRESS, VOLUME1_ROOTDIR_LBA, 32 );

    // Sinalizando que o cache de fat precisa ser salvo.

    fs_fat16_cache_not_saved();

    debug_print ("fsSaveFile: done\n");
    printf      ("fsSaveFile: done\n");
    refresh_screen();
    return 0;

fail:
    debug_print ("fsSaveFile: [FAIL]\n");
    printf      ("fsSaveFile: [FAIL]\n");
    refresh_screen ();
    return (int) 1;

}

/*
 *****************************
 * sys_write_file_to_disk:
 *     Interface para salvar arquivo ou diretório.
 *     Isso pode ser usado para criar um diretório ou 
 * copiar um diretório. 
 */

// #todo:
// vamos fazer igual ao sys_read_file 
// e criarmos opções ... se possível.

// IN: 
// name, size in sectors, size in bytes, adress, flag.

int
sys_write_file_to_disk ( 
    char *file_name, 
    unsigned long file_size,
    unsigned long size_in_bytes,
    char *file_address,
    char flag )  
{
    int __ret = -1;

    debug_print ("sys_write_file_to_disk:\n");


    if ( (void*) file_name == NULL )
    {
        return (int) (-EINVAL);
    }

    if ( *file_name == 0 )
    {
        return (int) (-EINVAL);
    }

    //++
    // See: sci/fs/write.c
    //taskswitch_lock ();
    //scheduler_lock ();

    __ret = (int) fsSaveFile ( 
                      VOLUME1_FAT_ADDRESS, 
                      VOLUME1_ROOTDIR_ADDRESS, 
                      FAT16_ROOT_ENTRIES,
                      (char *) file_name,    
                      (unsigned long) file_size,       
                      (unsigned long) size_in_bytes,  
                      (char *) file_address,          
                      (char) flag );                  

    //scheduler_unlock ();
    //taskswitch_unlock ();
    //--

    debug_print ("sys_write_file_to_disk: done\n");
    
    return (int) __ret;
}



/*
 * sys_read_file_from_disk: 
 *     This is called by sys_open() in sys.c
 */

// usada por open()
// tem que retornar o fd e colocar o ponteiro na lista de arquivos
// abertos.
// Carrega um arquivo do disco para a memoria.
// funcionou.
// #bugbug
// Na minha m�quina real, �s vezes d� problemas no tamanho do arquivo.
// #bugbug
// Estamos alocando mem�ria em ring para carregar o arquivo
// e depois estamos usando o buffer em ring3 passado pelo usu�rio.
// >>> vamos confiar no usu�rio e usarmos
// #bugbug
// precisamos colocar os arquivos também na lista
// global de arquivos abertos. file_table[]
// E na lista de inodes. inode_table[]
// See: fs.c
// #bugbug
// Nao seria o read() usado para ler um arquivo ja aberto ??
// sim. a rotina de suporte para read esta em sys_read e 
// nao chama essa aqui.
// essa aqui poderia ter outro nome, pois ela carrega um arquivo
// poderia chamar-se load.

int 
sys_read_file_from_disk ( 
    char *file_name, 
    int flags, 
    mode_t mode )
{
    int __ret = -1;

    file  *__file;
    size_t FileSize=-1;
    
    struct process_d *p;

    int __slot = -1;  // ofd.
    int Status = -1;

    void *buff;


    debug_print ("sys_read_file_from_disk: $\n");

    pid_t current_process = (pid_t) get_current_process();


// filename
    if ( (void*) file_name == NULL ){
        return (int) (-EINVAL);
    }
    if (*file_name == 0){
        return (int) (-EINVAL);
    }


// Convertendo o formato do nome do arquivo.    
// >>> "12345678XYZ"
// #todo: 
// Não fazer isso em ring3.

    fs_fntos ( (char *) file_name );

// #debug

    //printf ("sys_read_file_from_disk: FILE={%s}\n",
    //    file_name);
    //refresh_screen();

// #bugbug
// We need to search in the inode list. inode_table[]
// If the file is found in the inode list, so we don't
// need to load it again, just increment the counter.

    // #todo
    // fs_search_inode_table(file_name);

// Searching for the file only on the root dir.
// Quando não existe, tentamos criar.
// #bugbug: Então 'cat' não deve chamar essa função.

    Status = 
        (int) search_in_dir( file_name, VOLUME1_ROOTDIR_ADDRESS );

// Found.
    if (Status == TRUE){
        goto __go;
    }

// Not found.
    if (Status != TRUE)
    {
         //#debug
         printf ("sys_read_file_from_disk: [FIXME] File not found!\n");
         refresh_screen();
         
         // Create a new one.
         // #todo: Use sys_crete_empty_file.
         if (flags & O_CREAT)
         {
             debug_print ("sys_read_file_from_disk: [O_CREAT] Creating a new file\n"); 

             buff = (void*) kmalloc(1024);
             
             if ((void*)buff==NULL){
                 printf("sys_read_file_from_disk: buff\n");
                 goto fail;
             }

             //++
             // See: fs/write.c
             __ret = 
                 (int) fsSaveFile ( 
                           VOLUME1_FAT_ADDRESS, 
                           VOLUME1_ROOTDIR_ADDRESS, 
                           FAT16_ROOT_ENTRIES, 
                           (char *) file_name, 
                           (unsigned long) 1,   //2,     // size in sectors 
                           (unsigned long) 512, //1024,  // size in bytes  
                           (char *) buff,         // buffer ?
                           (char) 0x20 );         // flag 
              //--
              
              // Ok
              if (__ret == 0)
              {
                  debug_print("sys_read_file_from_disk: Created new file\n");
                  //refresh_screen();
                  goto __go;
              }
         }

         printf("sys_read_file_from_disk: [FIXME] Can't create new file\n");
         goto fail;
    }

__go:

// Process.
  
    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL ){
        printf("sys_read_file_from_disk: p\n");
        goto fail;
    }
    if ( p->used != TRUE || p->magic != 1234 ){
        printf("sys_read_file_from_disk: p validation\n");
        goto fail;
    }

// Procurando um slot livre.
    for (__slot=0; __slot<32; __slot++)
    {
         if ( p->Objects[__slot] == 0 ){ goto __OK; }
    };

// fail
    //panic ("sys_read_file_from_disk: No slots!\n");
    printf("sys_read_file_from_disk: No slots!\n");
    goto fail;

// Slot found.
__OK:

    if ( __slot < 0 || __slot >= 32 )
    {
        printf ("sys_read_file_from_disk: Slot fail\n");
        goto fail;
    }

// File struct

    __file = (file *) kmalloc( sizeof(file) );
    
    if ( (void *) __file == NULL ){
        printf ("sys_read_file_from_disk: __file\n");
        goto fail;
    }

// initialize.
    __file->used = TRUE;
    __file->magic = 1234;
    __file->pid = (pid_t) current_process;
    __file->uid = (uid_t) current_user;
    __file->gid = (gid_t) current_group;

// #bugbug [FIXME]
// We need a type in read().

// #bugbug
// This function was called by sys_open, and open
// is able to open any kind of file.
// Why are we using this type here?

    __file->____object = ObjectTypeFile;


// ==================
// #todo #bubug
// Permissoes:
// As permissoes dependem do tipo de arquivo.

// #bugbug: Let's do this for normal files for now.
    __file->sync.can_read  = TRUE;
    __file->sync.can_write = TRUE;

    __file->sync.action = ACTION_NULL;
        // ==================

// #todo:
// We need to get the name in the inode.

    //__file->_tmpfname = NULL;

    __file->_lbfsize = BUFSIZ;

    // inicializando apenas.
    __file->_r = 0;
    __file->_w = 0;
    __file->_cnt = BUFSIZ;  // anda temos bastante espaço. todo o buffer

// #
// This is gonna be the return value.
    __file->_file = __slot;

    __file->fd_counter = 1; //inicializando. 

// #todo
// Se ele não foi encontrado na lista de inodes
// e tivemos que carrega-lo do disco, então
// precisamos colocar ele na lista de inodes.. inode_table[]
// Atenção: O arquivo será carregado logo abaixo.

// #todo
// atualizar a tabela  global de arquivos. file_table[]

//
// buffer
//

// buffer padrão
// #bugbug: open chama isso. E se o arquivo for maior que o buffer ?
// open() precisa alocar outro buffer.

    __file->_base = (char *) kmalloc(BUFSIZ);
    
    if ( (void *) __file->_base == NULL ){
        printf ("sys_read_file_from_disk: __file->_base\n");
        goto fail;
    }

// #debug
    //printf ("FILE_AGAIN={%s}\n",file_name);
    //refresh_screen();

// File size.
// #bugbug: 
// OUT: 'unsigned long' ?

    FileSize = 
        (size_t) fsGetFileSize( 
                      (unsigned char *) file_name,
                      (unsigned long) VOLUME1_ROOTDIR_ADDRESS );

    if (FileSize <= 0){
        printf ("sys_read_file_from_disk: FileSize\n");
        goto fail;
    }


// Limits.
    //if ( FileSize < __file->_lbfsize )
    //{ 
    //    FileSize = __file->_lbfsize; 
    //}

// Limits.
// Se o arquivo for maior que buffer disponivel.
// Podemos aumentar o buffer.

    if (FileSize >= __file->_lbfsize)
    {

        // #debug
        printf("sys_read_file_from_disk: [todo] File size out of limits\n");
        printf("Size {%d}\n",FileSize);
        goto fail;

        // #bugbug: Provisório.
        // Limite - 1MB.
        if (FileSize > 1024*1024)
        {
            printf ("sys_read_file_from_disk: File size out of limits\n");
            printf ("%d bytes \n",FileSize);
            refresh_screen();
            return (-1);
        }
        
        // Allocate new buffer.
        __file->_base = (char *) kmalloc(FileSize);
        
        if ( (void *) __file->_base == NULL ){
            printf ("sys_read_file_from_disk: Couldn't create a new buffer\n");
            refresh_screen();
            return -1;             
        }
 
        // Temos um novo buffer size.
        __file->_lbfsize = (int) FileSize;
    }

// #paranoia.
// Checando os limites novamente.
// #bugbug: Provisório.
// Limits - 1MB
    //if (FileSize > 1024*1024)
    //{
    //    printf ("sys_read_file_from_disk: File size out of limits\n");
    //    refresh_screen();
    //    return -1;
    //}

// #paranoia.
// Checando base novamente.

    if ( (void *) __file->_base == NULL ){
        printf("sys_read_file_from_disk: __file->_base (again)\n");
        goto fail;
    }

// Pointer.
    __file->_p = __file->_base;

// Offsets
// Atualizando os offsets que foram apenas inicializados.

    // vamos ler do começo do arquivo.
    __file->_r = 0;


// O ponteiro de escrita mudou 
// pois escrevemos um arquivo inteiro no buffer.

    __file->_w = FileSize;

// #bugbug

    if ( FileSize >= BUFSIZ )
    {
        printf ("sys_read_file_from_disk: the file is larger than the buffer \n");
        refresh_screen();

        __file->_cnt = 0;
    }

// Agora temos menos espaço no buffer.
    __file->_cnt = ( BUFSIZ - FileSize );


// Load.
// Load the file into the memory.
 
    Status = 
        (int) fsLoadFile ( 
                  VOLUME1_FAT_ADDRESS, 
                  VOLUME1_ROOTDIR_ADDRESS, 
                  FAT16_ROOT_ENTRIES,  //#bugbug: Number of entries.
                  file_name, 
                  (unsigned long) __file->_base,
                  __file->_lbfsize );

    if (Status != 0){
        printf ("sys_read_file_from_disk: fsLoadFile fail\n");
        goto fail;
    }

// #bugbug
// Agora é a hora de atualizarmos as tabelas ....
// Depois de carregarmos o arquivo.

//
// Pointer. (mode)
//

// Ajusta o ponteiro para depois do tamanho do arquivo.
// Dependendo do modo.
// See:
// https://linux.die.net/man/2/open

           /*
           O_RDONLY        open for reading only
           O_WRONLY        open for writing only
           O_RDWR          open for reading and writing
           O_NONBLOCK      do not block on open or for data to become available
           O_APPEND        append on each write
           O_CREAT         create file if it does not exist
           O_TRUNC         truncate size to 0
           O_EXCL          error if O_CREAT and the file exists
           O_SHLOCK        atomically obtain a shared lock
           O_EXLOCK        atomically obtain an exclusive lock
           O_NOFOLLOW      do not follow symlinks
           O_SYMLINK       allow open of symlinks
           O_FSYNC         write will save into the disk. :)
           */

// Saving into de disk ?
// You can use the O_FSYNC open mode to make write always 
// store the data to disk before returning;    

     // Default ???

    //if (mode == 0)
    //{
          debug_print ("sys_read_file_from_disk: default mode\n");
          __file->_p = __file->_base;
    //}


// The file is opened in append mode. 
// O offset fica no fim do arquivo.
    if ( mode & O_APPEND)        
    { 
        debug_print ("sys_read_file_from_disk: O_APPEND\n");
        //__file->_p = __file->_base + s;
    }

    if ( mode & O_ASYNC )        
    { 
         debug_print ("sys_read_file_from_disk: O_ASYNC\n");
    }

    /* 
    // Enable the close-on-exec flag for the new file descriptor.
    if ( mode & O_CLOEXEC )        
    { 
         debug_print ("sys_read_file: O_CLOEXEC\n");
    }
    */


    if ( mode & O_CREAT ){
         debug_print ("sys_read_file_from_disk: O_CREAT\n");
    }

// #importante
// Se não liberarmos para leitura então read()
// não poderá ler.

    // ok to read
    __file->_flags = (__file->_flags | __SRD);

    // ok to write
    //__file->_flags = (__file->_flags | __SWR);


// Salva o ponteiro de estrutura de arquivo.  
// Ja checamos fd.
    p->Objects[__slot] = (unsigned long) __file;


    //#debug
    //printf ("process name: %s\n",p->__processname);
    //printf ("fd %d\n",__file->_file);
    //printf("sys_read_file_from_disk-OUTPUT: %s \n",__file->_base);
    //refresh_screen();

// Done.
// Vamos retornar o fd.
// Pois essa rotina eh usada por open();

done:
    debug_print("sys_read_file_from_disk: done\n");
    return (int) __file->_file;

fail:
    refresh_screen();
    return -1;
}


// ==============================
// Service 43
// See: fs_create_empty_file()

int sys_create_empty_file( char *file_name )
{
    int __ret = -1;


    //char *FileName;
    //FileName = (char *) file_name;

// #bugbug: 
// We need a buffer in another place.
// #todo: Allocate space for a new file.
    char buffer[512];
    //char *buf;

// How many bytes.
    int FileSizeInBytes = 512;

// How many sectors.
// (FileSizeInBytes/512)
    int NumberOfSectors = 1;


    debug_print ("sys_create_empty_file:\n");


    if ( (void*) file_name == NULL ){
        return (int) (-EINVAL);
    }
    if (*file_name == 0){
        return (int) (-EINVAL);
    }

// Change the string format.
    fs_fntos( (char *) file_name );


// 0x20 = file.
// See: write.c
    __ret = 
        (int) fsSaveFile ( 
                  VOLUME1_FAT_ADDRESS, 
                  VOLUME1_ROOTDIR_ADDRESS, 
                  FAT16_ROOT_ENTRIES,
                  (char *)         file_name,
                  (unsigned long)  NumberOfSectors, 
                  (unsigned long)  FileSizeInBytes,  
                  (char *)         &buffer[0], 
                  (char)           0x20 ); 

    if (__ret<0)
    {
        debug_print("sys_create_empty_file: fail\n");
        return -1;
    }

// #todo
// the file structure.

    return (int) __ret;
}


// ================================
// Service 44
// See: fs_create_empty_directory
int sys_create_empty_directory ( char *dir_name )
{
    int __ret=0;

// #bugbug: 
// We need a buffer in another place.

    char buffer[512];
    int size_in_bytes = 512; 
    int number_of_sectors = 1;


    debug_print ("sys_create_empty_directory:\n");

    if ( (void*) dir_name == NULL )
    {
        return (int) (-EINVAL);
    }

    if ( *dir_name == 0 )
    {
        return (int) (-EINVAL);
    }


    fs_fntos ( (char *) dir_name );


// See: write.c
// 0x10 = directory. 
    __ret = 
        (int) fsSaveFile ( 
                  VOLUME1_FAT_ADDRESS, 
                  VOLUME1_ROOTDIR_ADDRESS, 
                  FAT16_ROOT_ENTRIES,
                  (char *)         dir_name,
                  (unsigned long)  number_of_sectors, 
                  (unsigned long)  size_in_bytes, 
                  (char *)         &buffer[0], 
                  (char)           0x10 ); 

    if (__ret<0)
    {
        debug_print("sys_create_empty_directory: fail\n");
        return -1;
    }

// #todo
// the file structure.

    return (int) __ret;
}


void set_global_open_file ( void *file, int Index )
{

	// #todo:
	// Limite m�ximo da lista.


// Structure
    if ( (void *) file == NULL )
    {
        // ?? todo: message
        return;
    }

    if (Index < 0){
        // ?? todo: message
        return;
    }

// Include pointer in the list.

     file_table[Index] = (unsigned long) file;
}

void *get_global_open_file (int Index)
{

//Limits.
//@todo: max. NUMBER_OF_FILES

    if (Index < 0){
        // ?? todo: message
        return NULL;
    }

    return (void *) file_table[Index];
}


/*
 *  sys_cd_command:
 * 
 */
// Service 175. cd command.
// #todo
// ou usamos o cwd do processo ou
// o diretorio raiz para paths absolutos.

void sys_cd_command ( const char *string )
{
    int i=0;

    if ( (void*) string == NULL ){
        debug_print("sys_cd_command: string\n");
        return;
    }

    if ( *string == 0 ){
        debug_print("sys_cd_command: *string\n");
        return;
    }


    // Reset global structure and cwd on process structure.


    // #bugbug
    // Talvez esse tipo de tratamento precise 
    // ser feito pelo próprio shell.

    if ( string[1] == 0 )
    {

        // $ cd /
        // We also need to clean the name in the process structure.
        if (string[0] == '/'){
            debug_print("sys_cd_command: reseting\n");
            
            //if ( directory_facility_RootDir.initialized == TRUE){
            //    fsInitTargetDir(
            //        directory_facility_RootDir.dir_address,
            //        directory_facility_RootDir.dir_name );
            //}

            fsInitTargetDir(VOLUME1_ROOTDIR_ADDRESS,"/");
            //#bugbug: invalid pid
            //fs_initialize_process_cwd ( current_directory, "/" );
            return;
        }

        // ...

        return;
    }

// Atualiza na estrutura de processo.
// Atualiza na estrutura global para diretorio alvo.
    fsUpdateWorkingDiretoryString( (char *) string );
// Isso carrega o diretorio que agora 'e o diretorio alvo.
    fsLoadFileFromCurrentTargetDir();
    // ...
}

// helper.
// Loading a image given the filename and its virtual address.
int 
fs_load_image( 
    const char *filename, 
    unsigned long image_va )
{

// #todo:
// Explain better all these variables.

    int Status=-1;

// The address of the rootdir.
// Is it a physical address.
// #see: base/new/include/mm/x64gpa.h

    unsigned long dir_va = VOLUME1_ROOTDIR_ADDRESS;
    //unsigned long dir_va = VOLUME1_ROOTDIR_PA;

    unsigned long dir_entries = FAT16_ROOT_ENTRIES;

    char *path;
    char *name;

    unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (unsigned long) (512 * 4096);

    // para 32 entradas.
    // ????????
    unsigned long BUGBUG_OVERFLOW = ( 32*128 );


//
// Check parameters for image support
//

    if ( (void*) filename == NULL ){
        panic ("fs_load_image: [ERROR] filename\n");
    }
    if ( *filename == 0 ){
        panic ("fs_load_image: [ERROR] *filename\n");
    }
    path = filename;
    name = filename;
    if (path[0] == '.' && path[1] == '/')
    {
        debug_print ("fs_load_image: [FIXME] Can't execute from cwd \n");
        printf      ("fs_load_image: [FIXME] Can't execute from cwd \n");
        goto fail;
    }

//
// Loop
//

// Search
// Convertendo o formato do nome do arquivo.
// >>> "12345678XYZ"
// Procura o nome no diretório. 
// Que em nosso caso ainda é o diretório raiz.
// Convert and search.
// Fail if it was not found.

__search:

    fs_fntos ( (char *) name );
    Status = (int) search_in_dir(name,dir_va);
    if (Status == 1){ 
        goto __found; 
    }
    debug_print ("fs_load_image: [FAIL] File not found!\n");
    printf      ("fs_load_image: [FAIL] File not found!\n");
    goto fail;

// The file was found into the directory.
__found:

// ============================

// [3]
// #debug.

    debug_print ("fs_load_image: [3] Loading the image.\n");
         //printf ("fs_load_image: [3] Loading the image.\n");

// Loading from rootdir?
// >> Load file:
// #importante: 
// Carregando a imagem do processo filho.
// Se o carregamento falhar, temos que abortar a clonagem,
// caso contrário, executa a cópia da imagem do pai. ??
// #bugbug: Essa rotina começou a falhar aqui. Convertendo 
// num formato errado.
// Movemos essa conversão para o início dessa função,
// onde checaremos se o arquivo está no diretório.
// #bugbug
// Se isso não está funcionando direito e uma thread 
// defeituosa fica remanescente quando digitamos um 
// comando errado então vamos matar a thread e o processo.
// #todo
// Num ambiente 'mp' precisaremos de um lock aqui.

    //#debug
    //printf ("do_clone_execute_process: %s\n",filename);

    //unsigned long BUGBUG_IMAGE_SIZE_LIMIT = (unsigned long) (512 * 4096);


    if ( dir_va == 0 ){
        panic("fs_load_image: dir_va\n");
    }

    if ( (void *) image_va == NULL ){
        panic("fs_load_image: image_va\n");
    }

    Status = 
        (int) fsLoadFile ( 
                  VOLUME1_FAT_ADDRESS, 
                  (unsigned long) dir_va,       //#bugbug: This is only for the root dir.
                  (unsigned long) dir_entries,  //#bugbug: Number of entries. 
                  name, 
                  (unsigned long) image_va,
                  BUGBUG_IMAGE_SIZE_LIMIT );

// ok?
    return (int) Status;
fail:
    panic("fs_load_image: fail\n");
    return -1;
}


//
// End.
//

