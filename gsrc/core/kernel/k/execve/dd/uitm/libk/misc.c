/*
 * File: libk\misc.c
 *
 * Descrição:
 *    Rotinas variadas em kernel mode.
 *
 * Versão 1.0, 2015.
 */

 
#include <kernel.h>


/*
 * newLinkedlist:
 *     Cria uma nova linked list.
 */
void* newLinkedlist()
{
    /* allocate list */
    struct linkedlist_d *new_list; 
	
	new_list = (void*) malloc( sizeof(struct linkedlist_d) );
    if( (void*) new_list == NULL){
		return NULL;
	};

    /* put in the data  */
    //new_node->data  = new_data;
    
	new_list->head =  NULL;
    new_list->tail =  NULL;
	
done:
    return (void*) new_list;
};


/*
 * newNode:
 *     Cria um novo nodo.
 */
void* newNode()
{
    /* allocate node */
    struct node_d *new_node; 
	
	new_node = (void*) malloc( sizeof(struct node_d) );
    if( (void*) new_node == NULL){
		return NULL;
	};
 
    /* put in the data  */
    //new_node->data  = new_data;
    
	new_node->flink =  NULL;
 
done:
    return (void*) new_node;
};



void Removing_from_the_beginning(struct linkedlist_d *list)
{
    struct node_d *old_head;
    struct node_d *new_head;
	
	if( (void*) list == NULL){
	   return;
	};
	
	old_head = list->head;
	new_head = old_head->flink;
	
	list->head = new_head; 
	
done:
	return;
};


void Removing_from_the_middle(struct linkedlist_d *list)
{
  //todo identifica~çao do node que esta no meio,
};


void Removing_from_the_end(struct linkedlist_d *list)
{
    struct node_d *old_tail;
    struct node_d *new_tail;

	if( (void*) list == NULL){
	   return;
	};

	old_tail = list->tail;
	new_tail = old_tail->blink;
	
	list->tail = new_tail; 
	
done:
	return;
};


/*
 * set_up_system_color: 
 *     Configura cor padrão para o sistema.
 *     @todo: Isso pode ir para outro lugar.   
 */
void set_up_color(unsigned long color){   
	g_system_color = (unsigned long) color;	
	return;
};

/* 
 * set_up_text_color:
 *     Atribui o primeiro plano e o fundo que nós usaremos. 
 *     Top 4 bytes are the background,  bottom 4 bytes
 *     are the foreground color.
 *     @todo: Isso pode ir para outro lugar.
 */
void set_up_text_color(unsigned char forecolor, unsigned char backcolor)
{
    g_char_attrib = (backcolor << 4) | (forecolor & 0x0F);	
	return;
};


/*
 * set_up_cursor:
 *     Configura cursor.
 *     @todo: Isso pode ir para outro lugar.
 */
void set_up_cursor(unsigned long x, unsigned long y){   
	g_cursor_x = (unsigned long) x;
	g_cursor_y = (unsigned long) y;	
	return;
};

/*
 * get_cursor_x:
 *     Pega o valor de x.
 *     @todo: Isso pode ir para outro lugar.
 */
unsigned long get_cursor_x(){   	
	return (unsigned long) g_cursor_x;
};

/*
 * get_cursor_y:
 *     Pega o valor de y.
 *     @todo: Isso pode ir para outro lugar.
 */
unsigned long get_cursor_y(){         
    return (unsigned long) g_cursor_y; 	
};


//
// End.
//
