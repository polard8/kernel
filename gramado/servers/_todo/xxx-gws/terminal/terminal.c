

// terminal.c

// gerenciamento de terminal virtual ...

//esse é o suporte dado  aos terminais virtuais 
//usados pelos aplicativos em modo texto.


//#include <kernel.h>

/*
//envia um caractere para a estrutura de terminal 
//de onde um aplicativo poderá pegar.
int terminalFeed(int terminal_id, int ch )
{
	
	struct terminal_d *t;
	
	
	if( terminal_id < 0 || terminal_id >= TERMINAL_COUNT_MAX)
	{
	   goto fail;	
	}
	
	t = (struct terminal_d *) terminalList[terminal_id];
	if( (void*) t == NULL ){
		goto fail;
	}else{
		
		if( t->used == 1 && t->magic == 1234 )
		{
			//@todo.
			//colocar o char na estrutura de terminal.
			t->inputCH = (char) ch;
			t->inputCHStatus = 1;
			goto done;
		}
	}
	
	
fail:
    return 1;	
done:
    return 0;
}
*/

/*
//inicializando um primeiro terminal. o terminal 0.
int init_system_terminal()
{
    struct terminal_d *t;	
	
	t = (void*) malloc( sizeof(struct terminal_d) );
	if( (void*) t == NULL )
	{
		printf("init_system_terminal");
		die();
	}else{
		
		//@toso: objects
		
		t->id = 0;
		t->used = 1;
		t->magic = 1234;
		
		t->inputCH = 0;
		t->inputCHStatus = 0;
		
		
		//#importante:
		//continua ...
		
	};
	
	
    return 0;	
};

*/

//
//
//


