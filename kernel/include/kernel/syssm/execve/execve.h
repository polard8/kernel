/*
 * File: executive.h 
 *
 */
 
 
int current_taskman_server; 


 

int init_executive (void);


             

// efetua o serviço execve, rodando um novo programa
// no processo atual;
int 
sys_execve ( int i,
             const char *arg1, 
             const char *arg2, 
             const char *arg3 );




//
// End.
//

