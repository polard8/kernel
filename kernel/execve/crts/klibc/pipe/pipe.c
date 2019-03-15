/*
 * File: pipe.c
 *     Pipe support for klibc.
 *     ?? Pipes, socketpairs and FIFOs ??
 *     ?? pipe() and mkfifo(). ??
 *     pipe() which "returns" two file descriptors. 
 *     Internally the pipe is (normally) a circular buffer/queue.
 */


#include <kernel.h>


// criar duas estruturas de stream que apontam para o mesmo buffer.
// retorna os descritores de arquivo que estão na estrutura do processo atual.

int sys_pipe ( int *pipefd ){
	
	FILE *stream1;
	FILE *stream2;
		
	struct process_d *Process;

	
	Process = (void *) processList[current_process];
	
	if ( (void *) Process == NULL )
	{
		return -1;
	}else{
	
	     if ( Process->used != 1 || Process->magic != 1234 )
		 {
		     return -1;
		 }
		
		 //ok
	};
	
	//#todo
	//temos que criar uma rotina que procure slots em Process->Streams[]
	//e colocarmos em process.c
	//essa é afunção que estamos criando.
	// process_find_empty_stream_slot ( struct process_d *process );
	
	// procurar 2 slots livres.
    int i;
    int slot1 = -1;
	int slot2 = -1;
	
	// #improvisando
	// 0, 1, 2 são reservados para o fluxo padrão.
	// Como ainda não temos rotinas par ao fluxo padrão,
	// pode ser que peguemos os índices reservados.
	// Para evitar, começaremos depois deles.
	
	for ( i=3; i< NUMBER_OF_FILES; i++ )
	{
	    if ( Process->Streams[i] == 0 )
		{
			//reserva.
			Process->Streams[i] = 216;
			
		    slot1 = i;
			break;
		}
	}	

	for ( i=3; i< NUMBER_OF_FILES; i++ )
	{
	    if ( Process->Streams[i] == 0 )
		{
			//reserva.
			Process->Streams[i] = 216;
			
		    slot2 = i;
			break;
		}
	}	

	if ( slot1 == -1 || slot2 == -1 ) 
	{
		
		Process->Streams[i] = (unsigned long) 0;
		Process->Streams[i] = (unsigned long) 0;
		
	    return -1;
	}
	
	
	// buffer
	
	char *buff = (char *) malloc (BUFSIZ);
	//char *buff = (char *) newPage ();
	
    if ( (void *) buff == NULL )
	{
		 Process->Streams[i] = (unsigned long) 0;
		 Process->Streams[i] = (unsigned long) 0;		
	     return -1;
	}
	
	//estruturas 
	stream1 = (void *) malloc ( sizeof(FILE) );
	stream2 = (void *) malloc ( sizeof(FILE) );
	
	if ( (void *) stream1 == NULL || (void *) stream2 == NULL )
	{
		Process->Streams[i] = (unsigned long) 0;
		Process->Streams[i] = (unsigned long) 0;		
	    return -1;
	}else{
	
		// As duas estruturas compartilham o mesmo buffer.
		
        stream1->_base = buff;	
	    stream2->_base = buff;
		stream1->_ptr = buff;
		stream2->_ptr = buff;
		
		stream1->_tmpfname = NULL;
		stream2->_tmpfname = NULL;
		
		stream1->_bufsiz = BUFSIZ; 
		stream2->_bufsiz = BUFSIZ; 
		
		//quanto falta é igual ao tamanho.
		stream1->_cnt = stream1->_bufsiz;   
		stream2->_cnt = stream2->_bufsiz; 
		
		
		Process->Streams[i] = (unsigned long) stream1;
		Process->Streams[i] = (unsigned long) stream2;
		
		// #importante
		// Esse é o retorno esperado.
		// Esses índices representam o número do slot
		// na lista de arquivos abertos na estrutura do processo atual.
		
		pipefd[0] = slot1;
		pipefd[1] = slot2; 	
		
		//OK
		return 0;
	};
}


//#todo: rotina provisória
int sys_read_pipe ( int fd, int count ){
    return -1;
}

//#todo: rotina provisória
int sys_write_pipe ( int fd, int count ){
    return -1;
}







