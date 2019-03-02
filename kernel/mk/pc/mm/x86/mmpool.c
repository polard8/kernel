/*
 * File: mmpool.c
 *     ?
 *
 * g_pagedpool_va é o endereço virtual de uma área de memória pré alocada
 * de onde tiraremos páginas para o alocador.
 */


#include <kernel.h>


/*
 ******************************************************
 * newPageFrame:
 *    Aloca apenas uma página e retorna retorna o ponteiro de estrutura de página.
 */

void *page (){
	
	//#importante: 
	//Essa estrutura é para frame na memória física.
	struct page_d *New;
	
	int Index;	

	//procura slot vazio.
    for ( Index=0; Index < PAGE_COUNT_MAX; Index++ )
	{
	    New = (void*) pageAllocList[Index];
		
		if ( New == NULL )
		{
			New = (void*) malloc ( sizeof( struct page_d ) );
			
			if ( New == NULL ){
				printf("pc-mm-page:\n");
				//free
				goto fail;
			}
			
			//printf("$");
			
			New->id = Index;
			
			New->used = 1;
			New->magic = 1234;
			
			//not free
			New->free = 0;  
						
			New->next = NULL;
			
			
			//#bugbug ... isso tá errado.
			//endereço físico do inicio do frame.
			//New->address = (unsigned long) Address;
			//...
			
			pageAllocList[Index] = ( unsigned long ) New; 
		    return (void*) New;
		};
	};	

fail:
    return NULL;    
}


/*
 *********************************************************************
 * newPage:
 *     Aloca uma página e retorna seu endereço virtual inicial com base 
 * no id do pageframe e no endereço virtual inicial do pool de pageframes.
 * 
 *     ? kernel Mode ? ou user mode ?
 *     Obs: Isso funciona bem.
 * Obs: Alocaremos uma página de memória virtual e retornaremos 
 * o ponteiro para o início da página.
 * Para isso usaremos o alocador de frames de memória física.
 */

void *newPage (){
	
	//#importante: 
	//Essa estrutura é para frame na memória física.	
	struct page_d *New;
	
	// Esse é o endereço virtual do início do pool de pageframes.
	// Isso significa que num pool temos vários pageframes.
	
	unsigned long base = (unsigned long) g_pagedpool_va;	
	
	unsigned long va;
    unsigned long pa;
	   
	New	= (void *) page ();	
	
	if ( New == NULL )
	{
		printf("pc-mm-newPage: New\n");
		goto fail;
		
	}else{
	    
        if ( New->used == 1 && New->magic == 1234 )
		{
			// Pega o id 
			// Checa o limite de slots.
			
			if ( New->id > 0 && New->id < PAGE_COUNT_MAX )
            {
				//trava ou não??
			    New->locked = 0;
			    
				//contador de referências.
				New->ref_count = 1;	

			    //#importante
			    //precisamos pegar o endereço físico e dividir pelo tamanho da página.
				
				//pegando o endereço virtual.
				va = (unsigned long) ( base + (New->id * 4096) );
			    
				pa = (unsigned long) virtual_to_physical ( va, gKernelPageDirectoryAddress ); 
				
				
			    if ( ( pa % PAGE_SIZE) != 0 ) 
			    {		
			        pa = pa - ( pa % PAGE_SIZE);			
		 	    }	 	
			
			    New->frame_number = (pa / PAGE_SIZE);
			
			    if ( pa == 0 )
			    {
			        New->frame_number = 0;
			    }
				
				//retorn o endereço virtual	
				return (void *) ( base + (New->id * 4096) );
				//return (void *) va;
			}				
		};		
	};
	
 //
 // Fail !
 //
	
fail:
    return NULL;	
};




