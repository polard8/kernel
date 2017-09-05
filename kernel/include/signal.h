/*
 * File: signal.h
 * 
 * Descrição:
 *     C library signal support.
 *     Obs: @todo: O suporte à outros tipos de sinais além do padrão C devem
 * ir para outro arquivo.
 *
 *     Header para o Signal Manager.
 *     Um sinal é uma forma limitada de comunicação entre processos e entre 
 * threads.
 *     A característica mais importante de um sinal é que ele não envolve a
 * transferência de mensagem na forma de dados, apenas o sinal propriamente
 * dito.
 *     Um sinal pode interromper a ação de um processo ou thread.
 *     A execução pode ser interrompida em qualquer operação que não seja atômica. 
 *     Um processo pode registrar uma rotina de tratamento de sinal 
 * (signal handler em inglês) para tratar um determinado sinal, se não for 
 * desejado que a rotina padrão para este sinal seja executada.
 * Rotinas de tratamento de sinais podem ser instaladas através de 
 * chamada de sistema.
 * Se uma rotina de tratamento não é instalada para um determinado sinal, 
 * a rotina padrão é utilizada. Obs: Isso está me parecendo interrupções
 * de software.
 *
 * Obs: signal.h é um arquivo cabeçalho da biblioteca padrão da linguagem de programação C??
 *
 * Histórico:
 *      Versão: 1.0, 2016 - Created.
 *      ...
 */

 /*
The C standard defines only 6 signals. They are all defined in signal.h header (csignal header in C++):[1]

SIGABRT - "abort", abnormal termination.
SIGFPE - floating point exception.
SIGILL - "illegal", invalid instruction.
SIGINT - "interrupt", interactive attention request sent to the program.
SIGSEGV - "segmentation violation, invalid memory access.
SIGTERM - "terminate", termination request sent to the program. 
 
 */
 
/*

Constante	Significado	Disponibilidade
SIGHUP	Desconexão	POSIX	
SIGINT	Interrupção	ANSI
SIGQUIT	Sair	POSIX
SIGILL	Instrução ilegal	ANSI
SIGABRT	Abortar	ANSI
SIGTRAP	Armadilha de rastreio	POSIX
SIGIOT	Armadilha para IOT	4.2 BSD
SIGEMT	Armadilha para EMT	4.2 BSD
SIGFPE	Exceção de ponto flutuante	ANSI
SIGKILL	Matar processo	POSIX
SIGBUS	Erro no BUS	4.2 BSD
SIGSEGV	Falha de segmentação	ANSI
SIGSYS	Argumento incorreto para syscall	4.2 BSD
SIGPIPE	Pipe quebrado	POSIX
SIGALRM	Alarme	POSIX
SIGTERM	Término	ANSI
SIGUSR1	Sinal definido pelo usuário 1	POSIX
SIGUSR2	Sinal definido pelo usuário 2	POSIX
SIGCHLD	Mudança de estado no processo filho	POSIX
SIGCLD	Mesmo que SIGCHLD	System V
SIGPWR	Reinício por falha de energia	System V
SIGXCPU	Excedeu o tempo de CPU	POSIX
SIGSTOP	Pausar execução	POSIX
SIGCONT	Continuar execução	POSIX

 */ 
 
/*
POSIX signals[edit]
The list below documents the signals specified in the Single Unix Specification. All signals are defined as macro constants in <signal.h> header file. The name of the macro constant consists of a "SIG" prefix followed by a mnemonic name for the signal.

SIGABRT
The SIGABRT signal is sent to a process to tell it to abort, i.e. to terminate. The signal is usually initiated by the process itself when it calls abort function of the C Standard Library, but it can be sent to the process from outside like any other signal.
SIGALRM, SIGVTALRM and SIGPROF
The SIGALRM, SIGVTALRM and SIGPROF signal is sent to a process when the time limit specified in a call to a preceding alarm setting function (such as setitimer) elapses. SIGALRM is sent when real or clock time elapses. SIGVTALRM is sent when CPU time used by the process elapses. SIGPROF is sent when CPU time used by the process and by the system on behalf of the process elapses.
SIGBUS
The SIGBUS signal is sent to a process when it causes a bus error. The conditions that lead to the signal being sent are, for example, incorrect memory access alignment or non-existent physical address.
SIGCHLD
The SIGCHLD signal is sent to a process when a child process terminates, is interrupted, or resumes after being interrupted. One common usage of the signal is to instruct the operating system to clean up the resources used by a child process after its termination without an explicit call to the wait system call.
SIGCONT
The SIGCONT signal instructs the operating system to continue (restart) a process previously paused by the SIGSTOP or SIGTSTP signal. One important use of this signal is in job control in the Unix shell.
SIGFPE
The SIGFPE signal is sent to a process when it executes an erroneous arithmetic operation, such as division by zero (the name "FPE", standing for floating-point exception, is a misnomer as the signal covers integer-arithmetic errors as well).[2]
SIGHUP
The SIGHUP signal is sent to a process when its controlling terminal is closed. It was originally designed to notify the process of a serial line drop (a hangup). In modern systems, this signal usually means that the controlling pseudo or virtual terminal has been closed.[3] Many daemons will reload their configuration files and reopen their logfiles instead of exiting when receiving this signal.[4] nohup is a command to make a command ignore the signal.
SIGILL
The SIGILL signal is sent to a process when it attempts to execute an illegal, malformed, unknown, or privileged instruction.
SIGINT
The SIGINT signal is sent to a process by its controlling terminal when a user wishes to interrupt the process. This is typically initiated by pressing Ctrl-C, but on some systems, the "delete" character or "break" key can be used.[5]
SIGKILL
The SIGKILL signal is sent to a process to cause it to terminate immediately (kill). In contrast to SIGTERM and SIGINT, this signal cannot be caught or ignored, and the receiving process cannot perform any clean-up upon receiving this signal.
SIGPIPE
The SIGPIPE signal is sent to a process when it attempts to write to a pipe without a process connected to the other end.
SIGPOLL
The SIGPOLL signal is sent when an event occurred on an explicitly watched file descriptor.[6] Using it effectively leads to making asynchronous I/O requests since the kernel will poll the descriptor in place of the caller. It provides an alternative to active polling.
SIGRTMIN to SIGRTMAX
The SIGRTMIN to SIGRTMAX signals are intended to be used for user-defined purposes. They are real-time signals.
SIGQUIT
The SIGQUIT signal is sent to a process by its controlling terminal when the user requests that the process quit and perform a core dump.
SIGSEGV
The SIGSEGV signal is sent to a process when it makes an invalid virtual memory reference, or segmentation fault, i.e. when it performs a segmentation violation.[7]
SIGSTOP
The SIGSTOP signal instructs the operating system to stop a process for later resumption.
SIGSYS
The SIGSYS signal is sent to a process when it passes a bad argument to a system call. In practice, this kind of signal is rarely encountered since applications rely on libraries (e.g. libc) to make the call for them.
SIGTERM
The SIGTERM signal is sent to a process to request its termination. Unlike the SIGKILL signal, it can be caught and interpreted or ignored by the process. This allows the process to perform nice termination releasing resources and saving state if appropriate. SIGINT is nearly identical to SIGTERM.
SIGTSTP
The SIGTSTP signal is sent to a process by its controlling terminal to request it to stop (terminal stop). It is commonly initiated by the user pressing Ctrl+Z. Unlike SIGSTOP, the process can register a signal handler for or ignore the signal.
SIGTTIN and SIGTTOU
The SIGTTIN and SIGTTOU signals are sent to a process when it attempts to read in or write out respectively from the tty while in the background. Typically, these signals are received only by processes under job control; daemons do not have controlling terminals and, therefore, should never receive these signals.
SIGTRAP
The SIGTRAP signal is sent to a process when an exception (or trap) occurs: a condition that a debugger has requested to be informed of — for example, when a particular function is executed, or when a particular variable changes value.
SIGURG
The SIGURG signal is sent to a process when a socket has urgent or out-of-band data available to read.
SIGUSR1 and SIGUSR2
The SIGUSR1 and SIGUSR2 signals are sent to a process to indicate user-defined conditions.
SIGXCPU
The SIGXCPU signal is sent to a process when it has used up the CPU for a duration that exceeds a certain predetermined user-settable value.[8] The arrival of a SIGXCPU signal provides the receiving process a chance to quickly save any intermediate results and to exit gracefully, before it is terminated by the operating system using the SIGKILL signal.
SIGXFSZ
The SIGXFSZ signal is sent to a process when it grows a file larger than the maximum allowed size.
*/ 


/*
Macro constants
type	macro	signal
int (signals)	SIGABRT	(Signal Abort) Abnormal termination, such as is initiated by the abort function.
SIGFPE	(Signal Floating-Point Exception) Erroneous arithmetic operation, such as zero divide or an operation resulting in overflow (not necessarily with a floating-point operation).
SIGILL	(Signal Illegal Instruction) Invalid function image, such as an illegal instruction. This is generally due to a corruption in the code or to an attempt to execute data.
SIGINT	(Signal Interrupt) Interactive attention signal. Generally generated by the application user.
SIGSEGV	(Signal Segmentation Violation) Invalid access to storage: When a program tries to read or write outside the memory it has allocated.
SIGTERM	(Signal Terminate) Termination request sent to program.
functions (handlers)	SIG_DFL	Default handling: The signal is handled by the default action for that particular signal.
SIG_IGN	Ignore Signal: The signal is ignored.
SIG_ERR	Special return value indicating failure.
*/


/*
#define SIGTERM //implementation defined
#define SIGSEGV //implementation defined
#define SIGINT //implementation defined
#define SIGILL //implementation defined
#define SIGABRT //implementation defined
#define SIGFPE //implementation defined
SIGTERM	termination request, sent to the program
SIGSEGV	invalid memory access (segmentation fault)
SIGINT	external interrupt, usually initiated by the user
SIGILL	invalid program image, such as invalid instruction
SIGABRT	abnormal termination condition, as is e.g. initiated by abort()
SIGFPE	erroneous arithmetic operation such as divide by zero
References
C11 standard (ISO/IEC 9899:2011):
7.14/3 Signal handling <signal.h> (p: 265)
C99 standard (ISO/IEC 9899:1999):
7.14/3 Signal handling <signal.h> (p: 246)
C89/C90 standard (ISO/IEC 9899:1990):
4.7 SIGNAL HANDLING <signal.h>
*/


/*
SIGABRT Encerramento anormal
SIGFPE Erro de ponto flutuante
SIGILL Instrução ilegal
SIGINT Sinal de CTRL+C
SIGSEGV Acesso ilegal ao armazenamento
SIGTERM Solicitação de finalização
*/


/*
Comentários (microsoft)
O argumento de sig deve ser uma das constantes manifestas listadas abaixo (definido em SIGNAL.H).
SIGABRT
Encerramento anormal. A ação padrão encerra o programa de chamada com o código de saída 3.
SIGABRT_COMPAT
Mesmo que SIGABRT. Para compatibilidade com outras plataformas.
SIGFPE
Erro de ponto flutuante, como o estouro, de divisão por zero, ou a operação inválida. A ação padrão encerra o programa de chamada.
SIGILL
Instrução ilegal. A ação padrão encerra o programa de chamada.
SIGINT
CTRL+C de interrupção. A ação padrão encerra o programa de chamada com o código de saída 3.
SIGSEGV
Acesso ilegal de armazenamento. A ação padrão encerra o programa de chamada.
SIGTERM
Solicitação de término enviada ao programa. A ação padrão encerra o programa de chamada com o código de saída 3.
SIG_ERR
Um tipo de retorno de um sinal que indica um erro ocorreu
*/

//
// Definições. padrão C.
//


//
// @todo: Criar estrutura e objeto do tipo signal
//


//tipo.
//sig_atomic_t


//
// Prototypes. padrão C.
//

//Set function to handle signal
//sig Valor do sinal.
//func Função a ser executada. O primeiro parâmetro é um valor de sinal e o 
//segundo parâmetro é um subcódigo que pode ser usado quando o primeiro parâmetro é SIGFPE.
//Valor Retornado
//signal retorna o valor anterior func que está associado ao sinal especificado. 
//Por exemplo, se o valor anterior de func era SIG_IGN, o valor de retorno também é SIG_IGN. 
//Um valor de retorno de SIG_ERR indica um erro; nesse caso, errno é definido como EINVAL.


//void (*signal(int sig, void (*func)(int)))(int);


//Generates a signal
//int raise(int sig);





//
// Fim.
//

