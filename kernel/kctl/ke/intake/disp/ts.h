// ts.h 
// Context switch support.
// Created Fred Nora.

#ifndef __TS_H
#define __TS_H    1

extern unsigned long task_switch_status;

// ------------------------

void psTaskSwitch (void);
void tsCallExtraRoutines(void);

void taskswitch_lock (void);
void taskswitch_unlock (void);

unsigned long get_task_status (void);
void set_task_status( unsigned long status );

#endif    

