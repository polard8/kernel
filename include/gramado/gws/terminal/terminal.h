/*
 * File: terminal.h
 *
 * Descrição:
 *     Terminal emulator. (Teclado e Monitor).
 *     Terminal é onde o computador recebe input e envia output.
 *     pode haver terminal virtual como no linux(tty0 ~tty5)
 *     Configurações do terminal atual.
 *     Pode-se usar a tela inteira como terminal.
 *     Obs: O Shell poderá configurar o terminal atual
 *          para que os caracteres digitados
 *          sejam enviados pelo kernel para o termonal certo.
 *          Inclusive o buffer que o shell usa pode estar dentro do kernel.
 *          Inclusive o shell pode se apropriar do procedimento de shell
 *          existente dentro do kernel base e do procedimento de janela do sistema.
 *
 * Sobre o emulador de terminal: (Terminal Emulator.)
 * =============================
 *     A tela de um terminal pode ser emulada em uma janela, então uma janela
 * vai agir como se fosse uma tela de terminal. Como acontece com aplicativos shell
 * e máquinas virtuais.
 *     A disciplica de linha envia caracteres para o emulador de terminal.
 *
 *     Obs: À disciplina de linha não precisa receber o caractere diretamente
 * do driver de teclado. O método pode ser o seguinte: O driver de teclado envia
 * o caractera para a fila do processo, o processo envia o caractere para o driver
 * de TTY, o driver de TTY envia o caractere para a disciplina de linha e a
 * disciplina de linha envia o caractere para o emulador de terminal.
 *
 * Obs: O driver de TTY recebe do processo pedidos para escrever e ler caracteres no 
 * emulador de terminal.
 *       Para manipular arquivos, os processos podem usar o driver de io.
 * 
 *
 * Versão 1.0, 2016.
 */

/*

Attaching to a terminal:
A process can use the AttachTerminal function to attach to a terminal. A process can be attached to one terminal.
A terminal can have many processes attached to it.

The system creates a new terminal when it starts a terminal process,
*/


//test 
//#bugbug
#define DEFAULT_TERMINAL_LEFT 0
#define DEFAULT_TERMINAL_TOP  0
 
//Constantes.
#define TERMINAL_LIN_MAX    100    //Número máximo de linhas. 
#define TERMINAL_COL_MAX     74    //Número máximo de colunas.


#define TERMINAL_COUNT_MAX 8

//
// Número do terminal atual.
//

//
int terminalLine;       //Troca de linha;(up down)
int terminalOffset;     //Deslocamento dentro da linha; (left right).
int terminalLineMax;    //Número máximo de linhas suportadas.
int terminalOffsetMax;  //Número máximo de caracteres por linha.


//char teminalfeedCH;
//int teminalfeedCHStatus;


/*

[ Reflexão sobre o retângulo onde aparecem os caracteres no terminal virtual: ]

Um terminal virtual terá uma janela de instância e o retângulo que 
compreende a área de cliente dessa janela. Esse retângulo deve ser o lugar 
onde os caracteres serão pintados. 

Mas podemos desvincular esse retângulo da janela de instância e usarmos 
apenas o retângulo que compreende a área de cliente da janela.

Pois bem, no modo full screen do terminal virtual podemos simplesmente 
desabilitar a janela de instância e usarmos apenas um retângulo do tamanho da tela inteira.

Isso libera a estrutura de janela. Para isso a estrutura de terminal deve 
conter um ponteiro para janela e um ponteiro para retângulo.

Para efeito de teste, podemos escrever no retângulo do terminal, sem
criarmos uma janela completa, daquelas que tem barra de títulos e tudo mais.  

Uma função deve ser oferecida para configurar esse retângulo do terminal virtual 
atual.

Ou seja, o lugar natural de imprimir caracteres de terminal é nesse retângulo 
configurável.

*/

//Struct para terminal.
typedef struct terminal_d terminal_t;
struct terminal_d
{
	object_type_t objectType;
	object_class_t objectClass;

    int id;    //Slot number.(NÚMERO DO TERMINAL)
    
	int used;
    int magic;
	
	//@todo: Instance.
	
    int	LinMax;
	int	ColMax;
	int FullScreen;    //flag.
	
	// *IMPORTANTE: 
	// Essa será a janela para uma instância de terminal.
    struct window_d *window;    
	
	// *IMPORTANTE: 
	// Os caracteres serão pintados nesse retângulo.
	// @todo: Uma função deve oferecer a oportunidade de configurar esse
	// até o limite da área de cliente da janela de instãncia do terminal.

	//informações básicas sobre o retângulo
    unsigned long left; 
	unsigned long top;
	unsigned long width;
	unsigned long height;
	
	//informações extras sobre o retângulo.
	struct rect_d *rect;
	
	//
	// Buffers.
	//

	//?? generic.
	struct buffer_d *buffer;
	
	//Toda instancia de terminal deve ter seu próprio input buffer.
    void *InputBuffer;
	//struct buffer_d *InputBuffer;	
	
	
	//Toda instancia de terminal deve ter seu próprio Terminal Screen Buffer.
    //void *TerminalScreenBuffer;
	//struct buffer_d *TerminalScreenBuffer;	
	
	
	//caractere que os aplicativos pegarão via getch()
	char inputCH;
	int inputCHStatus; //status da mensagem de char ;;; empty ??
	
    //char prompt[128];
    //unsigned long prompt_pos;
	
	//struct process_d *Owner;
	//int UserId;                
};
terminal_t *CurrentTerminal;
//...


//List.
//(Control+F1) Aciona o primeiro terminal
//(Control+F2)
//(Control+F3)
//(Control+F4)
//(Control+F5)
//(Control+F6)
//(Control+F7)
//(Control+F8) 
unsigned long terminalList[TERMINAL_COUNT_MAX]; //TERMINAL_COUNT_MAX



/*
 * A do terminal que tem a janela ativa e o foco de entrada.
 *
 *
 */
struct window_d *terminalActiveWindow;
struct window_d *terminalWindowWithFocus;
//...

//envia um caractere para a estrutura de terminal 
//de onde um aplicativo poderá pegar.
int terminalFeed(int terminal_id, int ch );
//int init_system_terminal();

//
//fim.
//

