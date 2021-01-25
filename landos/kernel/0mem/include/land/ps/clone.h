


#ifndef __CLONE_H
#define __CLONE_H    1

// Clona e executa o filho dado o nome do filho.
pid_t clone_and_execute_process (const char *filename );

pid_t sys_fork_process (void);

pid_t clone_process (void);


#endif    



