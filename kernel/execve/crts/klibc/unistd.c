

#include <kernel.h>

//SVr4,  4.3BSD,  POSIX.1-2001. 
int open (const char *pathname, int flags, mode_t mode ){
	
	//#obs:
	//vamos retornar o indice da tabela dea rquivos abertos do processo atual.
	
	
	struct process_d *p;
	FILE *stream;
	int i;
	
	//int pid = -1;
	
	if (current_process < 0)
		return -1;
	
	p = (void *) processList[current_process];
	
	if ( (void *) p == NULL )
	{
	    return -1;
	}else{
		
		//#bugbug
		//o argumento 'mode' recebido e' um unsigned short.
		//e o mode de fopen 'e um ponteiro.
		
		//filename, mode
		stream = (FILE *) fopen ( (const char *) pathname, (const char *) 0 );
	
		if ( (void *) stream == NULL )
		{
			printf ("klibc-unistd-open: fail\n"); 
		    return -1;
		}else{
		
		     // agora temos uma stream va'lida. 
			 // procurar um slot vazio na lista de arquivos abertos do processo atual.
	
			 //NUMBER_OF_FILES = nu'mero ma'ximo de arquivos abertos em um processo.
		     for ( i=0; i< NUMBER_OF_FILES; i++ )
			 {
				 // Se encontramos um slot vazio, 
				 // colocamos o ponteiro para a stream nele e retornamos o pid.
				 // tipo: unsigned long
			     if ( p->Streams[0] == 0 )
				 {
				     p->Streams[i] = (unsigned long) stream ;
					 return (int) i;
				 }
			 }
			 		
			 //Nao encontramos um slot vazio.
			 return -1;
		}		
	};
	
//fail:
	//printf("klibc-unistd-open(): todo!\n");
    return -1;
}

// fechar um dos arquivos abertos do processo atual.
// o descritor 'e um ipndice na sua tabela dearquivos abertos.
int close ( int fd )
{
	struct process_d *p;
	FILE *stream;
	
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
		 
		     //#todo
			 //fechar corretamente esse arquivo e liberar os recursos associados a ele.
			 
			 stream = NULL;
			 processList[fd] = (unsigned long) 0;
			 
			 //ok.
			 return 0;
		 }
	
	};
	
	//printf ("klibc-unistd-close: todo\n");
    return -1;
}








