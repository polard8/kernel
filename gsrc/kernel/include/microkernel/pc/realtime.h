/*
 * Arquivo: realtime.h
 *
 * Descrição:
 *     Header do módolo realtime do kernel.
 *     Rotinas em realtime para multiprocessadores, ou quando está rodando 
 * apenas uma tarefa, a idle.
 *     As tarefas são confinadas em um processador, 
 * destinado para tarefas em real time.
 *
 * @todo: Fazer uma estrutura para gerenciar operações em realtime.
 */ 


/*
 * Flag para tornar realtime uma opção.
 */
int realtimeStatus; 

//lista de processadores dedicados a tarefa de realtime.
unsigned long realtimeprocessorList[32];

//
//fim.
//
