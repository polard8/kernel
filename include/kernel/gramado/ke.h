/*
 * File: ke.h
 *     Kernel External functions support.
 *     O objetivo é chamar rotinas que estão fora do kernel base.
 * As rotinas chamadas podem estar em servidores em user mode ou
 * em módulos em kernel mode.
 *
 * Histórico:
 *     Oct 2016 - Created.
 */


/*
 * Servers and Drivers:
 * ====================
 *
 * Chamadas aos módulos externos que estão em user mode.
 * São servers e drivers.
 * O Kernel pode chamá-los para uso próprio ou 
 * pode chamá-los para atender alguma solicitação
 * de cliente, que também está em user mode.
 * O Cliente chama solicida algum serviço de um Server
 * atravéz do kernel.
 *
 * @todo: Definir melhor o que deve ir para user modr e organizar.
 * por servidor por exemplo.
 */
 
 
//Informações sobre o kernel. módulo externo.
void KeInformation (void);   

//Faults support.
void KeCpuFaults (unsigned long fault_number);



//Window support.
// ?? process.c
void KeSetFocus (int pid);
int KeGetFocus (void);


//File support.
//carrega um arquivo. 
int 
KeLoadFile ( struct channel_d *channel, 
             unsigned char *file_name, 
			 unsigned long file_address );


//Scheduler support.
void KeNewProcessScheduler (void);
void KeSaveCurrentContext (void);
void KeRestoreCurrentContext (void);	


//dispatch support.
void KeDispatchProcess (void);

void KeDoProcessReady(int pid);
void KeDoProcessRunning(int pid);
void KeDoProcessSleeping(int pid);
void KeDoProcessZombie(int pid);
void KeDoProcessDead(int pid);
void KeStartProcess(unsigned long pid, unsigned long *task_address);	
void KeWakeupProcess(int pid);

void KeProcessExit (void);

void KeKillProcess (int pid);



int KeExecProcess (int pid, unsigned long *process_address);

void KeSetQuantum (unsigned long q);
unsigned long KeGetQuantum (void);

void KeSetCurrentQuantum (unsigned long q);
unsigned long KeGetCurrentQuantum (void);

void KeSetNextQuantum(unsigned long q);
unsigned long KeGetNextQuantum (void);


int KeSetPriority (void);


int KeIncreasePriority (int pid);


// Tasks ??
// #bugbug: Nao usar esse termo.


//spawn thread.

void KeSpawnTask (int id);

int KeSelectNextThread (int current);

void KeSaveContextOfNewTask ( int id, unsigned long *task_address );

void KeShowTasksParameters (void);


void KeShowPreemptedTask (void);	


int KeCheckTaskContext (int task_id);


//Finalization support.
// Global, qualquer módulo pode abortar. 
//void KeAbort();         



 


//
// End.
//

