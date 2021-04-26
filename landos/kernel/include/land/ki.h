/*
 * File: ki.h
 * 
 *     Kernel Internal functions support.
 *     It is used as interface for internal functions.
 *
 * History:
 *     2016 - Created by Fred Nora.
 */


#ifndef ____KI_H 
#define ____KI_H


// Runtime support. 
int KiInitRuntime (void); 

// Informations support.
void KiInformation (void); 

// Kernel request support.   
// See: kernel/request.c
int KiRequest(void);  

// Unix signal support.
// See: klib/signal.c
int KiSignal(void);


// Spawn support. Spawn a thread.
void KiSpawnThread (int tid);


// #todo: 
// Conferir se esse protótipo já está em outro lugar,
// o lugar dele é aqui.
void KiCpuFaults (unsigned long number);


// Finalizations support.
void KiAbort (void); 


#endif  



//
// End.
//

