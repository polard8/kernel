/*
 * File: line.h  
 *
 * Description:
 *     Line discipline, line management.
 *     Suporte ao gerenciamento de linhas para input e output.
 *     (tty driver) --> (line discipline) --> (terminal emulator)
 * Ex: O caractere gerado no driver de teclado, é enviado para a disciplica de linha
 * e depois é enviado para o emulador de terminal, que emula uma tela de terminal
 * dentro de uma janela.
 *
 * Sobre a disciplina de linha e o emulador de terminal: (Terminal Emulator.)
 * =========================================================================
 *     A tela de um terminal pode ser emulada em uma janela, então uma janela
 * vai agir como se fosse uma tela de terminal. Como acontece com aplicativos 
 * shell e máquinas virtuais.
 *     A disciplica de linha envia caracteres para o emulador de terminal.
 *
 *     Obs: *Importante: À disciplina de linha não precisa receber o caractere 
 * diretamente do driver de teclado. O método pode ser o seguinte: O driver de 
 * teclado envia o caractera para a fila do processo, o processo envia o 
 * caractere para o driver de TTY, o driver de TTY envia o caractere para a 
 * disciplina de linha e a disciplina de linha envia o caractere para o 
 * emulador de terminal.
 *
 * Ou ainda, o handler de teclado envia a tecla digitada para a fila de
 * mensagens no próprio driver de teclado. Liberando o driver de teclado
 * para receber outra digitação que possivelmente não demora. Uma flag deve
 * ser acionada dizendo que existe mensagem na fila do driver de teclado. Então
 * uma rotina no kernel base percebe a flag que diz haver mensagens na 
 * fila de teclado, pega a mensagem na fila de teclado e envia para a fila de 
 * mensagens do processo atual. O processo atual pegará as mensagens na fila
 * de mensagens do processo e fará sua própria disciplina de linhas
 *
 * O kernel base terá uma disciplina de linhas também. Manipulando linhas
 * conforme for conveniente para colocá-las em seu mini-shell e enviálas para
 * dispositivos de saída.
 *
 * Obs: O driver de TTY recebe do processo pedidos para escrever e ler caracteres no 
 * emulador de terminal. Esse emulador de terminal será uma instância do processo shell.
 * Ex: Se uma instância do processo shell está rodando e outro aplicativo deseja rodar
 * em modo texto, precisamos abrir uma nova instância do shell como emulador de terminal
 * para que o novo aplicativo possa rodar também em um emulador de terminal.
 *
 *       Para manipular arquivos, os processos podem usar o driver de io.
 *
 * Oct 2016 - Created.
 */ 

//
// Variáveis válidas para todas as linhas.
//

int lineLine;    //Troca de linha;(up down)
int lineLineMax;       //Número máximo de linhas suportadas.
int lineOffset;    //Deslocamento dentro da linha; (left right).
int lineOffsetMax;       //Número máximo de caracteres por linha.



//
// Estrutura para linha.
//

typedef struct line_d line_t;
struct line_d 
{
	object_type_t objectType;
	object_class_t objectClass;
	
    struct line_d *Next;        //Próxima linha. 
    struct buffer_d *Buffer;    //Buffer.
	//...
	
    //FILE *line_file; //Test.	
};

line_t *Line;
line_t *LineShell;
//line_t *Linex;
//line_t *Linex;
//line_t *Linex;
//...


//Linked list head.
struct line_d *LineHead;  


//Fluxo.
file *line_stdin;
file *line_stdout;
file *line_stderr;


//
// End.
//

