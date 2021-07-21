
// ts.h 
// header para rotinas de operação de troca de contexto de threads e processos.
// task switching


#ifndef __TS_H
#define __TS_H    1


void task_switch (void);
void psTaskSwitch (void);


unsigned long get_task_status (void);
void set_task_status( unsigned long status );

void taskswitch_lock (void);
void taskswitch_unlock (void);

void tsCallExtraRoutines(void);

#endif    


