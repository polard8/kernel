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
int KiInitRuntime();        

// Informations support.
void KiInformation(); 

//Requests support.   
void KiRequest();  

// Spawn support. spawn a thread.
void KiSpawnTask(int id);

//ipc.
void KiCalloutTest();
void KiCallfarTest();

// Finalizations support.
void KiShutDown(); 
void KiReboot();
void KiAbort(); 


//
// End.
//

