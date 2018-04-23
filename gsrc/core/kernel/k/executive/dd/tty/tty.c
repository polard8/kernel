/*
 * tty.c - Arquivo principal do Gerenciador de fluxo de caractere.
 *         Driver para interagir com os processos.
 *         O kernel recebeu o caractere de um dispositivo fisico
 * e enviou esse caractere para o driver tty, então o driver tty deve 
 * enviar esse caractere para o processo adequado...
 *o inverso também, o processo envia o caractere para o driver tty e 
 * o driver tty deve enviar o caractere para o dispositivo de saíta adequado 
 * atravéz do kernel.
 *
 */
 
#include <kernel.h> 
 
 
void *createTTYLine()
{
	struct ttyline_d *l;
	
	
	//Alocando memória para uma estrutura de linha.
	l = (void*) malloc( sizeof(struct ttyline_d) );

    if( (void*) l == NULL ){
		printf("createTTYLine:");
		refresh_screen();
		while(1){}
	}

	//@todo:
	//Inicializar as variáveis dentro da estrutura.
	
	int i;
	for(i = 0; i< TTYCHARS_COUNT_MAX; i++){
	    l->c[i] = 0;  //zerando o buffer de caracteres.	
	}
	
	l->used = 1;
	l->magic = 1234;
	l->empty = 1;
    //...	
	
	
	ttyLineCounter++;
	if(ttyLineCounter >= TTYLINES_COUNT_MAX){
		printf("createTTYLine: Line limits\n");
		refresh_screen();
		//free(l);
		return NULL;
	}else{
	    //developer_ttylines[ttyLineCounter] = (void*) l;	
		
		
		//
		// Precisamos de uma estrutura de texto ...
		// mas essa rotina é somente para tratamento de linhas.
		//
		
		// ?? A qual estrutura de texto essa linha pertence.
		
	}
	
	//...
	
done:	
    return (void*) l;	
}; 
 
 
/*
 * ttyInit:
 *     Inicialização do módulo.
 *
 */
int ttyInit()
{
	int i;
	for(i = 0; i< TTYLINES_COUNT_MAX; i++){
	    //developer_ttylines[i] = NULL;	
	}
	
	ttyLineCounter = 0;
	
	//
	input_line = (void*) createTTYLine(); 
	
	//...
done: 
	return (int) 0; 
};

