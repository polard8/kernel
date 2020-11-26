/*
 * File: ldisc.c
 *
 * Descrição:
 *    Esse será o gerenciador de Line Discipline.
 *    Ficará dentro do kernel base e receberá as entradas 
 * dos dispositivos de caractere e enviará para as filas apropriadas.
 *    Por enquanto os scancodes de teclado são tratados e enviados 
 * para a fila de mensagem da janela apropriada. Principalmente a janela 
 * com o foco de entrada. 
 *
 */

// See:
// https://en.wikipedia.org/wiki/Line_discipline

// #todo
// A disciplina de linhas poderia chamar o procedimento de janelas padrão
// do gramado x-server ao invés de chamar o procedimento de janelas do sistema.


// #importante
// Essas rotinas estão ligadas as formas de input.
// seus possíveis lugares são: 
// + line discipline
// + x server
// + terminal virtual.

#include <kernel.h>



//ldisc
//inicializando a fila de mensagens do sistema
//com ponteiros para estruturas de mensagens ...
//es estruturas serão reutilizáveis.

void initialize_system_message_queue (void){

    struct message_d *m;

    int i=0;


	for ( i=0; i<SYSTEM_MESSAGE_QUEUE_MAX; i++ )
	{
		
		m = (void *) kmalloc ( sizeof(struct message_d) );
		
		if ( (void *) m == NULL )
		{
			panic ("ldisc-initialize_system_message_queue:");
		}else{

			m->objectType = ObjectTypeMessage;
			m->objectClass = ObjectClassKernelObjects;
		    m->used = 1;
			m->magic = 1234;
			m->empty = 1;

            system_message_queue[i] = (unsigned long) m;
		}; 
	};


	system_message_write = 0;
	system_message_read = 0;
}


//Deprecated
unsigned long 
ldisc_dialog ( 
    struct window_d *window, 
    int msg, 
    unsigned long long1, 
    unsigned long long2 ) 
{
    return 0;
}



//
// End.
//


