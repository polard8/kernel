/*
 * File: context.h 
 *
 * Descrição:
 *     Header para rotinas de operações com contexto de threads e processos.
 *
 * * IMPORTANTE:
 * Obs:
 * @todo:
 * Existe um tipo de page fault causada por recarregar os registradores 
 * incorretamente. Acho que rotinas de checagem de conteúdo dos registradores 
 * antes de retornar devem ser mais severas. Os seja, depois de restaurar, 
 * tem que checar. Se não ouver falha, executa iretd. Mas se ouver falha, 
 * devemos bloquear a thread, checar novamente, tentar concertar se for algo 
 * simples e fechar a thread se o erro for grave ou persistir. Logo em seguida 
 * escalonar uma outra thread.
 *
 * oct 2016 - Created.
 */
void save_current_context();
void restore_current_context();

int contextCheckThreadRing0Context(int tid);
int contextCheckThreadRing3Context(int tid); 



//
//
//

