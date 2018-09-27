//
// marcos - queue  - teste
//

//==========================================
// marlls1989 - marcos - queue 


typedef struct ld_queue_t {
	//pthread_mutex_t lock;
	//pthread_cond_t wait;
	volatile size_t reads, writes;
	size_t size;
	void **data;
} ld_queue_t;

ld_queue_t *ld_keyboard_queue;  //fila para o teclado.


void xinit_queue(ld_queue_t *queue);
void xdestroy_queue(ld_queue_t *queue);
static void xresize_queue(ld_queue_t *queue, size_t new_size);
void xenqueue(void *element, ld_queue_t *queue);
void *xdequeue(ld_queue_t *queue);


