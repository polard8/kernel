

// ts.h 
// header para rotinas de operação de troca de contexto de threads e processos.
// task switching


#ifndef __TS_H
#define __TS_H    1



void psTaskSwitch (void);

void task_switch (void);

void taskswitch_lock (void);

void taskswitch_unlock (void);


#endif    


//
// End.
//

