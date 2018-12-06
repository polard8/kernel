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
void KeInformation();   

//Faults support.
void KeCpuFaults(unsigned long fault_number);

//Window support.
void KeSetFocus(int pid);
int KeGetFocus();

//File support.
//carrega um arquivo. 
int 
KeLoadFile ( struct channel_d *channel, 
             unsigned char *file_name, 
			 unsigned long file_address );

//Scheduler support.
void KeNewProcessScheduler();
void KeSaveCurrentContext();
void KeRestoreCurrentContext();	

//dispatch support.
void KeDispatchProcess();

void KeDoProcessReady(int pid);
void KeDoProcessRunning(int pid);
void KeDoProcessSleeping(int pid);
void KeDoProcessZombie(int pid);
void KeDoProcessDead(int pid);
void KeStartProcess(unsigned long pid, unsigned long *task_address);	
void KeWakeupProcess(int pid);
void KeProcessExit();
void KeKillProcess(int pid);
int KeFork();	
int KeExecProcess(int pid, unsigned long *process_address);

void KeSetQuantum(unsigned long q);
unsigned long KeGetQuantum();
void KeSetCurrentQuantum(unsigned long q);
unsigned long KeGetCurrentQuantum();
void KeSetNextQuantum(unsigned long q);
unsigned long KeGetNextQuantum();
int KeSetPriority();
int KeIncreasePriority(int pid);


//
// passando o comando para os processos.
//

void KeStartShell();
void KeStartTaskManager();


void KeSpawnTask(int id);   //spawn thread.
int KeSelectNextThread(int current);									
									
//Tasks??
int KeInitTask(int id);
void KeSaveContextOfNewTask(int id, unsigned long *task_address);
void KeReloadCurrentTask();
void KeShowTasksParameters();
void KeMostraSlots();
void KeMostraSlot(int id);
void KeMostraReg(int id);
void KeShowPreemptedTask();	
int KeCheckTaskContext( int task_id);
void KeInitTasks();	
int KeCreateTask( int task_id, 
                 unsigned long *task_eip, 
				 unsigned long *task_stack, 
				 unsigned long prior );
				 
//debug support.
void KeDebugBreakpoint();

//Finalization support.
void KeAbort();         // Global, qualquer módulo pode abortar. 
void KeReboot();


//
// End.
//

