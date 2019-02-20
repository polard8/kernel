
/*
 'g_pagedpool_va' É o endereço virtual de uma área de memória pré alocada
 de onde tiraremos páginas de memória sob demanda.
 
 # Estamos alocando páginas, e lidando com endereços virtuais.
 
 */


#include <kernel.h>

/*
 ******************************************************
 * newPageFrame:
 *    Aloca apenas um frame de memória física e retorna o ponteiro.
 *    ? kernel mode ? user mode ?
 *    obs: isso funciona bem.
 *    Obs: Isso é usado pelo alocador de páginas, logo abaixo.
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
			New->free = 0;  //not free
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
    
	// Pega o id do pageframe e 
	// multiplica pelo tamanho do frame e 
	// adiciona à base.	
	
    // Novo frame.
	//New	= (void *) newPageFrame ();
	New	= (void *) page ();	
	
	if( New == NULL )
	{
		printf("pc-mm-newPage: New\n");
		goto fail;
		
	}else{
	    
        if ( New->used == 1 && New->magic == 1234 )
		{
			//pega o id 
			//checa o limite de slots.
			if ( New->id > 0 && New->id < PAGE_COUNT_MAX )
            {
				return (void *) ( base + (New->id * 4096) );
			}				
		};		
	};
	
 //
 // Fail !
 //
	
fail:
    return NULL;	
};




