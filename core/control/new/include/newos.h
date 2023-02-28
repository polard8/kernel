
// newos.h

#ifndef __NEWOS_H
#define __NEWOS_H    1

void newos_reboot(unsigned long reboot_flags);

unsigned long newos_get_system_metrics(int index);

pid_t newos_getpid(void);

int newos_start_thread( struct thread_d *thread );

int newos_get_current_runlevel(void);

unsigned long newos_get_memory_size_mb(void);

void *newos_alloc_shared_ring3_pages(pid_t pid, int number_of_bytes);

void newos_set_cursor( unsigned long x, unsigned long y );

#endif    

