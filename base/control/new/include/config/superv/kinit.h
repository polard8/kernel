/*
 * File: init.h
 *     Initialization support.
 * History:
 *     2015 - Created by Fred Nora.
 */

#ifndef __INIT_H
#define __INIT_H    1


// Initialization support.
struct initialization_d
{

// Current phase:
    int current_phase;

// Checkpoints:
// #bugbug> some names here are deprecated.
    int phase1_checkpoint; 
    int phase2_checkpoint;
    int phase3_checkpoint;
    int hal_checkpoint;
    int microkernel_checkpoint;
    int executive_checkpoint;
    int gramado_checkpoint;

//
// flags
//

// Se ja podemos usar o dispositivo serial para log.
    int serial_log;
// Se ja podemos usar o console virtual para log.
    int console_log;

    // ...
}; 

// No pointer.
// see: init.c
extern struct initialization_d  Initialization;

void init_globals (void);

#endif    


//
// End.
//

