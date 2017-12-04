/*
 * File: client.h
 
 //(network) Client process support.   network support
 *
 * Description:
 *     Header do gerenciador de atividades do processo cliente.
 *     Gerencia processos, janelas menus, client area ...
 *
 *
 */

/* 
typedef struct client_process_d client_process_t; 
struct client_process_d
{
	struct process_d *client;
};
client_process_t *ClientProcessHook; 
//...
*/

struct process_d *clientCP;    //Processo Cliente.
struct window_d  *clientCW;    //Janela do processo cliente.
struct rect_d    *clientCR;    //Área de cliente da janela do processo cliente.
//...         


FILE *client_stdio;
FILE *client_stdout;
FILE *client_stderr;

//
//Fim.
//

