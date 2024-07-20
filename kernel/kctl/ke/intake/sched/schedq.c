
// schedq.c

#include <kernel.h>

// List of heads.
// Each priority has its own queue.
unsigned long sched_queues[SCHEQ_COUNT_MAX];


// The current list
// Global queue.
struct thread_d  *currentq;

// ========================================

void scheq_set_element(int index, struct thread_d *head_thread)
{

// ----
// Invalid
    if (index<0){
        goto fail;
    }

// ----
// 0
    if (index == SCHED_CURRENT_QUEUE){
        sched_queues[SCHED_CURRENT_QUEUE] = (unsigned long) head_thread;
        return;
    }

// ----
// range: 1~6       
    if ( index >= SCHED_P1_QUEUE || index <= SCHED_P6_QUEUE )
    {
        sched_queues[index] = (unsigned long) head_thread;
        return;
    }

// ----
fail:
    return;
}

struct thread_d *schedq_get_element(int index)
{

// ----
// Invalid
    if (index<0){
        goto fail;
    }

// ----
// 0
    if (index == SCHED_CURRENT_QUEUE){
        return (struct thread_d *) sched_queues[SCHED_CURRENT_QUEUE];
    }

// ----
// range: 1~6       
    if ( index >= SCHED_P1_QUEUE || index <= SCHED_P6_QUEUE )
    {
        return (struct thread_d *) sched_queues[index];
    }

// ----
fail:
    return NULL;
}






