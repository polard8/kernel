

// File: pty.c


// "The PTY virtualizes a computer’s serial communications hardware, 
// exposing “master” and “slave” pseudo-devices:"
// Terminal apps connect to a master pseudo-device; 
// Command-Line applications 
// (e.g. shells like Cmd, PowerShell, and bash) connect to a slave pseudo-device.
// See: 
// https://devblogs.microsoft.com/commandline/windows-command-line-introducing-the-windows-pseudo-console-conpty/


// pty é um canal de comunicação com duas pontas.
// é semelhante ao canal com dois soquetes, um em cada ponta.
// Enquando os canais usam os termos server/client os pty
// usam os termos master/slave.

// See:
// ptmx - https://docs.oracle.com/cd/E19253-01/816-4855/termsub15-14/index.html
// http://poincare.matf.bg.ac.rs/~ivana/courses/ps/sistemi_knjige/pomocno/apue/APUE/0201433079/ch19lev1sec3.html


#include <kernel.h>

 
 

//#todo
/*
int 
pty_ioctl ( int fd, unsigned long request, char *arg );
int 
pty_ioctl ( int fd, unsigned long request, char *arg )
{
    return -1;
}
*/


// #todo
// copiar o conteúdo do buffer ??
// do slave para o master. do master para o slave.
/*
void pty_copy (struct tty_d *from, struct tty_d *to);
void pty_copy (struct tty_d *from, struct tty_d *to)
{
}
*/


/*
void pty_write (struct tty_d *tty);
void pty_write (struct tty_d *tty)
{
	
	if (tty->link)
		pty_copy (tty,tty->link);
}
*/


/*
int pty_open (struct tty_d *tty, FILE *stream);
int pty_open (struct tty_d *tty, FILE *stream)
{
}
*/

/*
int pty_close (struct tty_d *tty, FILE *stream);
int pty_close (struct tty_d *tty, FILE *stream)
{
}
*/




/*
//cria um arquivo para tty master.
//essa arquivo irá representá-lo.
//obs: não existe estrutura de pty;
FILE *pty_master_create (struct tty_d *pty);
FILE *pty_master_create (struct tty_d *pty)
{
	FILE *__stream;
	
	if ( (void *) pty == NULL )
	{
		return NULL;
	}
    
    //#todo: check validation


	__stream = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) __stream != NULL )
	{
		__stream->used = 1;
		__stream->magic = 1234;
		
		//#todo: continua ...
		
		//master
		pty->type = PTY_TYPE_MASTER;
		
		return (FILE *) __stream;
	}
	
	return NULL;
}
*/


/*
//cria um arquivo para tty slave
//se é que a estrutura ja não tenha seu arquivo.
//obs: não existe estrutura de pty;
FILE *pty_slave_create (struct tty_d *pty);
FILE *pty_slave_create (struct tty_d *pty)
{
	FILE *__stream;
	
	
	if ( (void *) pty == NULL )
	{
		return NULL;
	}

    //#todo: check validation
    
    
	__stream = (FILE *) malloc ( sizeof(FILE) );
	
	if ( (void *) __stream != NULL )
	{
		__stream->used = 1;
		__stream->magic = 1234;
		
		//#todo: continua ...
		
		//slave
		pty->type = PTY_TYPE_SLAVE;
		
		return (FILE *) __stream;
	}
	
	return NULL;
}
*/

/*
int pty_create_link ( struct tty_d *tty );
int pty_create_link ( struct tty_d *tty )
{

	if ( (void *) pty == NULL )
	{
		return NULL;
	}
	
	//pty->link = ?
	
    return 0;	
}
*/



// Ligar duas tty dados os pids dos processos que possuem as tty.
// isso será usado pelo terminal se ele tiver o pid do filho.
// Serviço: 267
int pty_link_by_pid ( int master_pid, int slave_pid )
{

    debug_print("pty_link_by_pid: [FIXME] \n");
    //return -1;


	// O slave é o terminal. pts. remember ?!

    struct tty_d *__master;
    struct tty_d *__slave;    

    struct process_d *pm;   //process master
    struct process_d *ps;   //process slave
    
    int master_tty_id = -1;
    int slave_tty_id = -1;


    //
    // Process
    //

    if ( master_pid < 0 || slave_pid < 0 )
    {
        printf ("pty_link_by_pid: pid\n");
        refresh_screen();
        return -1; 
    }


    pm = ( struct process_d *) processList[master_pid];

    if ( (void *) pm == NULL )
    {
        printf ("pty_link_by_pid: pm\n");
        refresh_screen();
        return -1; 
    }


    ps = ( struct process_d *) processList[slave_pid];

    if ( (void *) ps == NULL )
    {
        printf ("pty_link_by_pid: ps\n");
        refresh_screen();
        return -1; 
    }




    //
    // tty
    //
    
    if ( ( void * ) pm->tty == NULL || 
         ( void * ) ps->tty == NULL )
    {
        printf ("pty_link_by_pid: tty\n");
        refresh_screen();
        return -1; 
    }
    

    master_tty_id = pm->tty->index;
    slave_tty_id  = ps->tty->index;


    if ( master_tty_id < 0 || slave_tty_id < 0 )
    {
        printf ("pty_link_by_pid: tty id\n");
        refresh_screen();
        return -1; 
    }

    file *f_master;
    f_master = (file*) pm->Objects[master_tty_id];
    __master = ( struct tty_d *) f_master->tty; 
 
    if ( (void *) __master == NULL ) 
    {
        printf ("pty_link_by_pid: * __master\n");
        refresh_screen();
        return -1; 
    }

    file *f_slave;
    f_slave = (file*) ps->Objects[slave_tty_id];
    __slave = ( struct tty_d *) f_slave->tty; 
 
    if ( (void *) __slave == NULL ) 
    {
        printf ("pty_link_by_pid: __slave\n");
        refresh_screen();
        return -1; 
    }

    // Link!
    return (int) pty_link ( __master, __slave );
}



//#test
int pty_link ( struct tty_d *master, struct tty_d *slave )
{

    if ( (void *) master == NULL ){
        printf ("pty_link: master\n");
        goto fail;
    }

    if ( (void *) slave == NULL ){
        printf ("pty_link: slave\n");
        goto fail;
    }


	// #todo
	// Checar validade.
	
	master->link = slave;
	
	
	//#debug
    //printf ("pty_link: Linked. m=%d s=%d\n", 
        //master->index, master->link->index );
    //refresh_screen();
    
    return 0;
    
fail:
    refresh_screen();
    return -1;
}


//#test
int pty_unlink ( struct tty_d *tty ){

    if ( (void *) tty == NULL ){
        debug_print ("pty_unlink: tty\n");
        return -1;
    }


    tty->link = NULL;

    return 0;
}



int ptmx_open (void){

    int ptm_fd = -1;
    
    struct tty_d *master;
    struct tty_d *slave;
    
    
    master = (struct tty_d *) tty_create();
    slave  = (struct tty_d *) tty_create();


    //#todo check validation
    
    int status = -1;
    status = pty_link(master,slave);

    if (status < 0){
        debug_print ("ptmx_open: status\n");
        return -1;
    }


    // +abre uma tty master e coloca na lista de arquivos abertos
    // pelo processo
    // +cria uma tty stave e deixa bloqueada.
    // retorna o fd da tty master.
    
    return (int) ptm_fd;
}


//
// End.
//







