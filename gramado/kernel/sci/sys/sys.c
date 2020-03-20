/*
 * File: sys.c
 *
 *
 * History:
 *     2019 - Created by Fred Nora.
 */


#include <kernel.h>



// 289
// See: sm/debug/debug.c
int sys_serial_debug_printk ( char *s )
{
    debug_print ( (char *) s );
    return 0;
}



/*
 * sys_ioctl:
 *     system call implementation of ioctl().
 *     Executa um dado comando em um dado dispositivo.
 */

// See:
// http://man7.org/linux/man-pages/man2/ioctl.2.html

// The ioctl() system call manipulates the 
// underlying device parameters of special files.
// In particular, many operating characteristics of
// character special files (e.g., terminals) may be controlled with
// ioctl() requests.  The argument fd must be an open file descriptor.
   
 
 // OK Isso é um wrapper.
 // Chamaremos tty_ioctl() ou outros ...  
       
// IN: fd, what to do, ?

int sys_ioctl ( int fd, unsigned long request, char *arg )
{
    struct process_d *p;
    file *f;


    debug_print ("sys_ioctl: TODO\n");

    // fd must to be on open file descriptor.
    if ( fd<0 || fd>31 ){
       debug_print("sys_ioctl: Invalid fd\n");
       return -1;
    }


    p = (struct process_d *) processList[current_process];

    if ( (void *) p == NULL )
        return -1;
        
    if ( p->used != 1 || p->magic != 1234 )
        return -1;
        
        
    // pega o arquivo.
    // checa o tipo de objeto.
    // Isso deve ser usado principalmente com dispositivos 
    // de caracteres como o terminal.

    f = (file *) p->Objects[fd];
    
    
    // #todo
    // Now we can use a swit to call different
    // functions, as tty_ioctl etc.
    
    switch(f->____object)
    {
        case ObjectTypeDevice:  //não usar isso.
            break;
            
        //case tty device:
            //tty_ioctl(...)
            
            
        //case console 
            //console_ioctl(...)
            
        //...    
            
        default:
            break;
    }


    //fail
    return -1;
}


int sys_fcntl ( int fd, int cmd, ... )
{

    if ( fd < 0 )
        return -1;
    
    if ( cmd < 0 )
        return -1;
    
    
    switch(cmd)
    {
        // lock operation.
        case F_SETLK:
            break;
            
        default:
            break;
    };


    return -1; //#todo
}


//#??? isso não pertence à fcntl.c ?
//SVr4,  4.3BSD,  POSIX.1-2001. 

// #bugbug
// Precisamos de um endereço em ring 3
// para que a libc possa manipular o buffer ?

// ou open deve ser usado somente com dispositivos ??
//#obs:
//vamos retornar o indice da tabela de arquivos abertos do processo atual.
int sys_open (const char *pathname, int flags, mode_t mode ){

    struct process_d *p;
    int i;
    int __Status = -1;
    
    // Ajust.
    read_fntos ( (char *) pathname );


    // Searching for the file only on the root dir.
    __Status = (int) KiSearchFile ( (unsigned char *) pathname, 
                         VOLUME1_ROOTDIR_ADDRESS );

    if (__Status == 1){
		
		 //#debug
         //printf("found\n");
    }else{
         printf("not found\n");
         return -1;
    };


    //taskswitch_lock ();
    //scheduler_lock ();
    //name , address.

     int Size = (int) fsGetFileSize ( (unsigned char *) pathname ); 
     //scheduler_unlock ();
     //taskswitch_unlock ();

    
    if( Size<=0 || Size> 1024*1024)
        return -1;



    // igual open();
    // #todo: flags e mode.
    // See: fs.c
    // IN: name, flags, mode;
    // OUT: fd.
    return (int) sys_read_file ( (char *) pathname, 0, 0 );
}


// fechar um dos arquivos abertos do processo atual.
// o descritor 'e um ipndice na sua tabela dearquivos abertos.

int sys_close ( int fd ){

	file *stream;
		
	struct process_d *p;
	int i;
	

	if ( fd < 0 || fd >= NUMBER_OF_FILES)
		return -1;
	
	if ( current_process < 0 )
		return -1;
	
	p = (void *) processList[current_process];
    
	if ( (void *) p == NULL )
	{
	    return -1;
	}else{
	
	     stream = (FILE *) processList[fd];
		 
		 if ( (void *) stream == NULL )
		 {
		     return -1;
		 }else{
		 
		     // #todo
			 // Fechar corretamente esse arquivo e liberar os recursos 
			 // associados a ele.
			 
			 stream = NULL;
			 processList[fd] = (unsigned long) 0;
			 
			 //ok.
			 return 0;
		 }
	
	};
	
	//printf ("klibc-unistd-close: todo\n");
    return -1;
}




/*
// checar se o usuário tem permissão 
// para abrir um objeto.
// vamos checar no processo atual qual é o usuário que está
// tentando abrir o objeto.
// Se permitido então colocaremos um fd na lista de arquivos
// abertos pelo processo.
int permission (file *f);
int permission (file *f)
{
    // ...
    
    return -1;
}
*/

// File read.
// It's called by sys_read.
// COpia à partir do início do arquivo.
int file_read_buffer ( file *f, char *buffer, int len ){

    char *p;

  
    p = buffer;

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

    //
    // Copy!
    //
    
    memcpy ( (void *) buffer, (const void *) f->_base, len ); 
    return (int) len;

fail:
    refresh_screen ();
    return EOF;
}


/*
 * file_write: 
 *     Escreve no arquivo uma certa quantidade de caracteres de uma 
 *     dada string.
 */
// Escreve no arquivo uma certa quantidade de caracteres de uma dada string 

// It's called by sys_write.
int file_write_buffer ( file *f, char *string, int len ){

    char *p;

    p = string;

  
    if ( (void *) f == NULL ){
        printf ("file_write_buffer: file\n");
        goto fail;
    }

    if ( (void *) p == NULL ){
        printf ("file_write_buffer: p\n");
        goto fail;
    }

    //
    // Copy!
    //

    memcpy ( (void *) f->_base, (const void *) string, len ); 
    return len;
    
fail:
    refresh_screen ();
    return EOF;
}




/*
 ************************************
 * sys_read;
 *     implementation os read() libc function.
 */

// Service 18.
// #todo: There's a lot to do with synchronization.

int sys_read (unsigned int fd, char *ubuf, int count){

    struct process_d *__P;
    
    file *__file;
    
    struct socket_d *s;
    
    int len;
    int nbytes = 0;


    
    // fd.
    if (fd<0 || fd>31){
        debug_print ("sys_read: fd\n");
        printf ("sys_read: fd\n");
        goto fail;
    }

    // count.
    if (count<=0){
        debug_print ("sys_read: count\n");
        printf ("sys_read: count\n");
        goto fail;
    }

    // Size of the buffer.
    len = strlen( (const char *) ubuf );
    if (len > count )
        len = count;


    // #todo: Limits.    
    if (len > 512)
        len = 512;
    

    // buf.
    // todo: Checar a validade da região de memória.
    if ( (char *) ubuf == (char *) 0 ){
        debug_print ("sys_read: invalid ubuf address\n");
        
        // #debug
        printf ("sys_read: invalid ubuf address\n"); 
        goto fail; 
    }
    

    // Process.
    __P = (struct process_d *) processList[current_process];

    if ( (void *) __P == NULL ){
        debug_print ("sys_read: __P\n");
        
        // #debug
        printf ("sys_read: __P\n");
        goto fail; 
    }


    // file.
    __file = (file *) __P->Objects[fd];  

    if ( (void *) __file == NULL ){
        debug_print ("sys_read: __file not open\n");
        
        printf ("sys_read: __file not open\n");
        goto fail; 
    }


    /*
    int object = (int) __file->____object; 
    switch(object)
    {
        case ObjectTypeSocket:
            //#todo: call socket_read(...)
            break;
        case ObjectTypeFile:  //regular file
           break;

        case 1:
            break;
        
        default:
            break;
    }
    */

    // maybe.    
    // is_char_dev?     read_char(...)
    // is_block_dev?    read_block(...)
    // is_
    
    
    //if ( __file->____object == ObjectTypeFile )
        //return (int) unistd_file_read ( (file *) __file, (char *) buf, (int) count );


    //if ( __file->____object == ObjectTypeDisk )
        // todo disk_read(...)


    //if ( __file->____object == ObjectTypeTTY )
        // tty_read (...) #todo criar função se não existe.


    //if pipe
    
    
    //if socket
    // socket_read()


    //
    // ==== Socket file ====
    //


    // #todo: 
    // Now we can call socket_read(...)
    
    
    // Se o arquivo for um socket.
    if ( __file->____object == ObjectTypeSocket )
    {

        
        // O socket do processo.
        // #bugbug
        // temos que inicializar essa variável, na hora da 
        // clonagem de processo e na hora da criação de processo.
        if ( (void *) __P->priv == NULL ){
            debug_print ("sys_read: __P->priv fail\n");
            
            printf ("sys_read: __P->priv fail\n");
            goto fail;
        }
         
        // Pega a estrutura de soquete.
        s = __P->priv;
        if ( (void *) s == NULL){
            debug_print ("sys_read: s fail\n");
            printf ("sys_read: s fail\n");
            goto fail;
        }


        // O arquivo usado pelo socket.
        // atenção
        // temos que inicializar essa variável, na hora da 
        // criação do socket.
        if ( (void *) s->private_file == NULL ){
            debug_print ("sys_read: s->private_file fail\n");
            
            printf ("sys_read: s->private_file fail\n");
            goto fail;
        }

        // O arquivo do socket precisa ser esse arquivo.
        if (__file != s->private_file){
            debug_print ("sys_read: __file fail\n");
            
            printf ("sys_read: __file fail\n");
            goto fail;
        }

        // Read!

        nbytes = 0;

        // #debug 
        // printf ("sys_read: pid %d reading socket file %d\n",
        //      current_process, __file->_file );
         

        // Buffer cheio:
        // + Lemos uma quantidade de bytes.
        // + 

        if (__file->socket_buffer_full == 1)
        {
            // OUT:
            // > 0 or EOF.
            nbytes = (int) file_read_buffer ( (file *) __file, 
                              (char *) ubuf, (int) count );
        
            // Se lemos alguma coisa:
            // + Sinalizamos que o buffer não está mais cheio.
            // + sinalizamos que podem escrever novamente.
            // #todo: Acordar quem espera para escrever.

            if (nbytes > 0){
                // #debug
                // printf ("read ok. %d bytes \n",nbytes);

                __file->socket_buffer_full = 0;
                __file->_flags |= __SWR;
                return (int) nbytes;
            }

            // Se nenhum byte foi lido: 
            // + A thread atual dorme,
            // + reescalonamos as threads e
            // + sinalizamos que podem escrever no arquivo.

            if (nbytes <= 0){
             
                // #debug
                //printf ("sys_read: The thread %d is waiting now \n", 
                    //current_thread);
                //refresh_screen();
                
                do_thread_waiting (current_thread);
                __file->tid_waiting = current_thread;
                __file->_flags |= __SWR;  //pode escrever      
                scheduler();
                return 0;
            }
        } // if it's full.
         
         
        // Se, no caso de socket, o buffer está vazio:
        // + A thread dorme.
        // + Sinaliza que a thread está esperando.
        // + Reescalonamos as threads;
        // + Sinalizamos que podem escrever no arquivo.

        //if (nbytes == 0)
        if (__file->socket_buffer_full == 0)
        {    
            //#debug
            //printf ("thread %d is waiting now \n", current_thread);
            //refresh_screen();

            do_thread_waiting (current_thread);
            __file->tid_waiting = current_thread;
            __file->_flags |= __SWR;  //pode escrever.
            scheduler();
            return 0;
        }  // if it's not full.

        panic ("sys_read: unexpected socket_buffer_full value \n");
    }  


    //
    // ==== Normal file ====
    //


    // Read a regular file.
    // See: unistd.c
    // #todo Tem que retornar a quantidade de bytes lido.
    
    // Se puder ler:
    // + Call a function to read a regular file.
    // + Sinalize that another process can write.
    // #todo: wake the one that was waiting to write.

    if ( __file->_flags & __SRD )
    {     
        nbytes = (int) file_read_buffer ( (file *) __file, 
                           (char *) ubuf, (int) count );

        // ok to write.
        __file->_flags = __SWR;
        return nbytes;
    }

    //
    // Fail!
    //

fail:

    debug_print ("sys_read: fail\n");
    refresh_screen();
    return 0;
}




/*
 ****************************
 * sys_write:
 *     Implemantation of write() for libc.
 *
 */

// service 19.
// copiar um buffer para uma stream.
// dado o fd.
// Aqui devemos selecionar o dispositivo à escrever.
// See:
// https://github.com/zavg/linux-0.01/blob/master/fs/read_write.c
// ...

int sys_write (unsigned int fd,char *ubuf,int count){

    struct process_d *__P;
    
    file *__file;
    file *__file2;
    
    struct socket_d *s1;
    struct socket_d *s2;
    
    int len;
    int nbytes = 0;
    size_t ncopy = 0;




    if (fd<0 || fd>31){
        debug_print ("sys_write: fd\n");
        goto fail;
    }


    if (count<=0){
        debug_print ("sys_write: count\n");
        goto fail;
    }

        
     
    // todo: Check validation for the memoru region.    
    if ( (char *) ubuf == (char *) 0 ){
        debug_print ("sys_write: invalid ubuf address\n");
        goto fail;
    }


    //
    // Size of the buffer.
    //

    // len
    len = strlen( (const char *) ubuf );
    if (len > count )
        len = count;
    
    // #bugbug: 
    // Precisamos da opção de salvarmos vários setores em
    // dispositivos de bloco.
    //if (len > 64 )
        //len = 64;
    

    if (len > 512 )
        len = 512;

    //
    // Process pointer.
    //
    
    
    
    __P = (struct process_d *) processList[current_process];

    if ( (void *) __P == NULL ){
        debug_print ("sys_write: __P\n");
        //printf ("sys_write: __P\n");
        goto fail;
    }


    //
    // __file.
    //

    __file = (file *) __P->Objects[fd]; 
    
    if ( (void *) __file == NULL ){
        debug_print ("sys_write: __file not open\n");
        //printf ("sys_write: __file not open\n");
        goto fail;
    }


    // switch
    // is_char_dev?     read_char(...)
    // is_block_dev?    read_block(...)
    // is_


    // >> Console.
    // Se o descritor usado por write() for de um arquivo
    // do tipo console, escreveremos no console 0.
    if ( __file->____object == ObjectTypeVirtualConsole ){
       // console number, buffer, size.
       return (int) console_write ( (int) 0, 
                        (const void *) ubuf, (size_t) count );
    }



    //
    // Write
    // and copy if it's a socket.
    // __file2
    //


    //
    // sockets
    //
    
    ncopy = count;
    
    // descobrindo o soquete que devemos copiar.
    
    if ( __file->____object == ObjectTypeSocket )
    {
        //pega a estrutura de soquete.
        s1 = __P->priv;
        if ( (void *) s1 == NULL){ 
            debug_print ("sys_write: s1 \n");
            goto fail;
        }    
         
        if (__file != s1->private_file){
            debug_print ("sys_write: __file\n");
            goto fail;
        }  

        //#debug
        //printf ("sys_write: (1) pid %d Writing in the socket file %d \n", 
            //current_process, __file->_file );
        //refresh_screen();
                 
        nbytes = (int) file_write_buffer ( (file *) __file, 
                           (char *) ubuf, (int) count );
                            
        // #debug
        //printf ("sys_write: written\n");
        //refresh_screen();
     
         //agora nosso arquivo esta pronto para leitura,
         //pois esperamos uma resposta.    
         //>>> nao posso ler  ... so poderei ler quando alguem mandar alguma coisa.
        __file->_flags |= __SRD;  
         
         
        // Connected ??
        // Esse ponteiro precisa ser inicializado
        // na criação da estrutura de socket.
        if ( (void *) s1->conn == NULL){ 
            debug_print("sys_write: s1->conn fail. No connection\n");
            //printf("sys_write: s1->conn fail. No connection\n");  //for real machine;
            goto fail;
        }    
         
        s2 = s1->conn;
         
        if ( (void *) s2 == NULL){    
            debug_print("sys_write: s2 fail. No connection\n");
            //printf("sys_write: s2 fail. No connection\n");  //for real machine;
            goto fail;
        }    

        // pega o arquivo.    
        __file2 = s2->private_file;
        
        if ( (void *) __file2 == NULL){
            debug_print ("sys_write: target file fail. __file2\n");
            //printf ("sys_write: target file fail. __file2\n");
            goto fail;
        }  

        if ( __file2->____object == ObjectTypeSocket )
        {
            
            // #debug
            //printf ("sys_write: (2)  pid %d  Writing in the socket file %d \n",
                //current_process, __file2->_file);
            //refresh_screen();
              
            //memcpy( (void *) fa->_base, (const void *) __file->_base, (size_t) ncopy );
         
            nbytes = (int) file_write_buffer ( (file *) __file2, 
                               (char *) ubuf, (int) ncopy );
                               
            
            //printf ("sys_write: written\n");
            //refresh_screen();
             
            if (nbytes>0) 
                __file2->socket_buffer_full = 1;
             
            //
            // thread
            //
             
            //se alguma thread estava esperando 
            //que alguem escrevesse, então acordamos ela.
             
            if (__file2->tid_waiting >0){
             
                //printf ("thread %d is ready now \n", __file2->tid_waiting);
                
                do_thread_ready(__file2->tid_waiting);
                __file2->tid_waiting = 0;
            }

            //pode ler.
            __file2->_flags |= __SRD;   
            
            return (int) nbytes;
        }
         
        debug_print("sys_write:  fail. target is not a socket.\n");
        
        //printf ("sys_write:  fail. target is not a socket.\n");
        //refresh_screen();
        return 0;
    }   


    //
    // Arquivos normais (regular)
    //
    
    //if pipe
    
    
    //if socket
    // socket_write()
    

    //tem que retonar o tanto de bytes escritos.
    //See: unistd.c
    // Escreve em uma stream uma certa quantidade de chars.
    
    
    //#todo: ainda não colocamos essa flag na criação do arquivo.
    //if (fp->_flags & __SWR)
        
    // Normal file.
    nbytes = (int) file_write_buffer ( (file *) __file, 
                       (char *) ubuf, (int) count );
    
    // Avisa que o arquivo não está mais no modo escrita,
    // que agora pode ler.

    // Adiciona o bit que permite a leitura.
    // Assim o servidor pode ler o request.
    // #todo: wait on write.
    // #bugbug:
    // A questão é que se o cliente está esperando por resposta,
    // então ele lerá também.
    __file->_flags |= __SRD;

    return (int) nbytes;


    //
    // fail.
    // 

fail:
    //refresh_screen();
    debug_print("sys_write: fail\n");
    return 0;
}


/*
int sys_fcntl(unsigned int fd, unsigned int cmd, unsigned long arg);
int sys_fcntl(unsigned int fd, unsigned int cmd, unsigned long arg)
{
    return -1;
}
*/


/*
 *****************************************************
 * sys_create_process:
 *     Create process system interface.
 */

        // 73 - Create process.
        // ??
        // #todo: enviar os argumentos via buffer.
        // #todo: Ok, nesse momento, precisamos saber qual é o 
        // processo pai do processo que iremos criar. Esse deve ser 
        // o processo atual ...  
        // PPID = 0. Nesse momento todo processo criado será filho 
        // do processo número 0. mas não é verdade. 
        // @todo: Precisamos que o aplicativo em user mode nos passe 
        // o número do processo pai, ou o proprio kernel identifica 
        // qual é o processo atual e determina que ele será o 
        // processo pai. 

void *sys_create_process ( struct room_d *room,
                           struct desktop_d  *desktop,
                           struct window_d *window,
                           unsigned long res1, 
                           unsigned long priority, 
                           int ppid, 
                           char *name,
                           unsigned long iopl, 
                           unsigned long res2 )
{

   //#bugbug
   // o argumento directory_address está errado.
   // deletar esse argumento. outra coisa no lugar.
   // o argumento init_eip também ta errado.

    struct process_d *p;
    struct thread_d *t;
    
    
   //
   // Carregar num endereço virtual temporário ..
   // converte o endereço virtual em físico, para
   // remapearmos depois.
   // Mas antes precisamos saber o tamanho da imagem.
   //
    
    unsigned long tmp_va = 0;
    unsigned long tmp_pa = 0;
        

    int fileret = -1;
    
    
    
    debug_print("sys_create_process:\n");

    //? kb 1024*?/4096 = 
    tmp_va = (unsigned long) allocPages(40); //40 páginas;

    //#todo: validation

    tmp_pa = (unsigned long) virtual_to_physical ( tmp_va, 
                                 gKernelPageDirectoryAddress ); 

            
            
	// loading image.
	

    
    fileret = (unsigned long) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                                  VOLUME1_ROOTDIR_ADDRESS, 
                                  name, 
                                  (unsigned long) tmp_va );


    // Se não encontramos init.bin
    if ( fileret != 0 )
    {
        fileret = (unsigned long) fsLoadFile ( VOLUME1_FAT_ADDRESS, 
                                      VOLUME1_ROOTDIR_ADDRESS, 
                                      name, 
                                      (unsigned long) tmp_va );

        
        if ( fileret != 0 ){
            panic ("sys_create_process: fileret \n");
        }
    }
 

    p = (void *) create_process ( room, desktop, window, 
                      (unsigned long) 0x00400000, //base
                      priority, 
                      ppid, 
                      name, 
                      RING3, //iopl??
                      (unsigned long ) CloneKernelPageDirectory() );

    if ( (void *) p == NULL ){
        panic ("sys_create_process: p\n");

    }else{

        fs_initialize_process_pwd ( p->pid, "no-pwd" );
    };
    
    
     // #bugbug
     // Precisa alocar um endereço físico para a nova imagem
     // mapear esse endereço em 0x400000 do diretorio do processo que
     // acabamos de criar;
     
     p->ImagePA = tmp_pa;

     CreatePageTable ( (unsigned long) p->DirectoryVA, 
            ENTRY_USERMODE_PAGES, p->ImagePA );
            
     // Com base no endereço físico, usamos a função acima
     // para atribuírmos um novo endereço virtual para a imagem.
     p->Image = 0x400000; // com base na entrada escolhida (ENTRY_USERMODE_PAGES)            
 
    
    //
    // Thread.
    //

	// Create thread.
    t = (struct thread_d *) create_thread ( room, desktop, window, 
                        0x00401000,  //entrypoint 
                        priority, 
                        p->pid, 
                        "control-thread" ); 

    if ( (void *) t == NULL ){
        return NULL;
    }

    // Marca ela como thread de cotnrole.
    p->control = t;
    
    SelectForExecution ( (struct thread_d *) t );


    return (struct process_d *) p;
}




// 85
// #bugbug: 
// Isso está retornando o ID do processo pai do processo atual.
// O que queremos é o ID do processo pai do processo que está chamando.
// Pega o id do processo atual.
int sys_getpid (void)
{
	// ??
    return (int) current_process;
}



//81
//#bugbug Isso está retornando o ID do processo atual.
//O que queremos é o ID do processo que está chamando
//Pega o ID do processo pai do processo atual.
int sys_getppid (void){
	
    int pid;
	int ppid;
	
	struct process_d *p;
	
	pid = (int) current_process;
	
	if ( pid >= 0 && pid < PROCESS_COUNT_MAX )
	{
		p = (void *) processList[pid]; 		
		
		if ( (void *) p == NULL )
		{
			return (int) -1;
		}
		
		if ( p->used != 1 || p->magic != 1234 ){
		    
			return (int) -1;	
		}
		
		return (int) p->ppid;
	}

    return (int) -1;	
}




/*
 *********************************************
 * sys_fork:
 *     
 */

// #todo 

int sys_fork (void){

    return (int) fork ();
}



//exit process.
//serviço do sistema.

void sys_exit_process ( int pid, int code ){
	
    if ( pid < 0 )
        return;

    exit_process ( pid, code );
}




/*
 *********************************************************
 * sys_create_thread:
 *     Create thread system interface.
 */

    // 72 - Create thread.
    // #todo: 
    // Enviar os argumentos via buffer.


void *sys_create_thread ( struct room_d *room,
                          struct desktop_d  *desktop,
                          struct window_d *window,
                          unsigned long init_eip, 
                          unsigned long priority, 
                          int ppid, 
                          char *name )
{
    struct thread_d *t;

    debug_print ("sys_create_thread:\n");

	//@todo filtros, para ponteiros NULL.

	// Create thread.
    t = (struct thread_d *) create_thread ( room, desktop, window, 
                        init_eip, 
                        priority, 
                        ppid, 
                        name ); 

    if ( (void *) t == NULL ){
        return NULL;
    }

    SelectForExecution ( (struct thread_d *) t );

    return (struct thread_d *) t;
}






//exit thread.
void sys_exit_thread (int tid){

    if ( tid < 0 )
        return;

    exit_thread (tid);
}



//90 Coletor de threads Zombie. (a tarefa idle pode chamar isso.)
void sys_dead_thread_collector (void)
{
    dead_thread_collector ();
}


/*
 * sys_vsync:
 *     Sincroniza o retraço vertical do monitor.
 */

void sys_vsync (void)
{
    hal_vsync ();
}


/* 
 **********************************
 * sys_showkernelinfo:
 *     Show kernel info. 
 */

void sys_showkernelinfo (void)
{
    KiInformation ();
}




/*
 * sys_showpciinfo:
 *     Mostra informações encontradas na interface PCI.
 */

int sys_showpciinfo (void)
{
    return (int) hal_showpciinfo ();
}

 
/*
 ************************************
 * sys_reboot:
 *     Reboot, Serviço do sistema.
 *     Chamando uma rotina interna de reboot do sistema.
 */

void sys_reboot (void)
{
    reboot ();
}


/*
 **********************************
 * sys_shutdown:
 *     Chama uma rotina interna para desligar a máquina.
 */

void sys_shutdown (void)
{
    hal_shutdown ();
}


// 178
unsigned long sys_get_file_size ( char *path ){

    unsigned long __size = 0;
    
    taskswitch_lock ();
    scheduler_lock ();
    
    __size = (unsigned long) fsGetFileSize ( (unsigned char *) path ); 
    
    scheduler_unlock ();
    taskswitch_unlock ();
    
    return (unsigned long) __size; 
}


// Usada por vários serviços de debug.
// Usada para debug.
void sys_show_system_info ( int n ){

    if (n<0)
        return;

    switch (n)
    {
        case 1:
            //diskShowCurrentDiskInfo();
            disk_show_info();
            break;

        case 2:
            //volumeShowCurrentVolumeInfo();
            volume_show_info();
            break;

        case 3:
            memoryShowMemoryInfo();
            break;

        case 4:
            systemShowDevicesInfo();
            break;
            
        case 5:
            KiInformation ();
            break;

        // ...
    };


    refresh_screen ();
}


