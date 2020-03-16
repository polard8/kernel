/*
 * File: ki.h
 *     Kernel Internal functions support.
 *     Interfaces para chamar diversas rotinas presentes
 * dentro do kernel base. 
 *     É acrescentado filtros antes de se chamar as rotinas 
 * propriamente ditas. Há mais de uma maneira de acessar uma
 * rotina do kernel, pode ser atravpes de interfaces como essas
 * ou através de estruturas de classes, que invocam métodos.
 *
 * Histórico:
 *     Oct 2016 - Created.
 */


//Runtime support. 
int KiInitRuntime (void);        

// Informations support.
void KiInformation (void); 


//Requests support.   
int KiRequest (void);  


// Spawn support. spawn a thread.
void KiSpawnTask (int id);

//ipc.
//void KiCalloutTest (void);
//void KiCallfarTest (void);


//## bugbug ##
// Isso deveria estar no módulo /pc em microkernel.


void *createCreateInitThread (void);



void *KiCreateRing0Idle (void);





//@todo: Conferir se esse protótipo já está em outro lugar,
//o lugar dele é aqui.
void KiCpuFaults (unsigned long number);


// Finalizations support.
void KiAbort (void); 


//
// End.
//

