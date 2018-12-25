/*
 * File: api.c 
 *
 * Description:
 *     Application Programming Interface - (API).
 *
 *     Arquivo principal da API 32bit.
 *     Call Kernel via interrupt.
 *     Estamos em User Mode e usaremos os serviços do Kernel através de 
 * chamadas via interrupção.
 *     +As interrupções de serviços do KERNEL vão de 48 à 199.
 *     +A interrupções principal é a 200.
 *     +As interrupções de chamadas especiais vão de 201 até 215. 
 *     +As interrupções de serviços da GUI vão de 216 à 219.
 *
 * Attention: 
 *    Atenção ao passar argumentos via memória, pois utilizamos 
 * endereços lógicos.
 *
 *  @todo: logon, segurança, autenticação, bancodedados de autenticação.
 *         Heap support:
 *  @todo: Get PID, TID.       
 *
 * Obs:
 *     O kernel base deve proteger suas estruturas. Os processos devem 
 * proteger suas estruturas uns dos outros. É natural então que seja
 * passado somente o índice de uma lista de ponteiros de estruturas.
 * Quem tiver em mão o índice, solicita algum elemento da estrutura
 * para quem tem permissão de manipular a estrutura. 
 *     Passar o ponteiro de uma estrutura pode ser um problema de segurança,
 * além do transtorno de converter endereço lógico e físico. Mas existem
 * heaps de memória compartilhada, onde devem ficar algumas estruturas.
 * 
 * Obs:
 * Podemos passar todos os argumentos de uma estrutura para kernelmode
 * onde o kernel criou um estrutura semelhante e protegida. O kernel nos
 * devolve um índice que só pode ser manipulado pelo processo que pediu
 * para o kernel criar a estrutura. Assim essa estrutura fica protegida
 * dentro do heap do kernel. 
 *
 * Obs: Muitos dos recursos oferecidos aqui por essa api, que é ligada 
 *      às aplicações em tempo de compilação, serão oferecidos
 *      por uma api em user mode na forma de server, ou biblioteca
 *      de link dinâmico. (.so, .dll ...).
 *
 * In this file:
 * ============
 *     +sustem_call(....); - Interrupção do systema. Número 200.
 *     +system() - Interpreta um comando via argumento. 
 *     + Muitas outras ...
 *
 *
 * History: 
 *     2014 - Created by Fred Nora.
 *     2015 - New services.
 *     2016 - New services.
 *     2018 - Revision.
 *     ...
 */


//diretório 
//-I c:\gramado\include
#include <types.h>        //
#include <heap.h>         //
#include <api\api.h>      //


//message box button pointer
struct window_d *messagebox_button1;
struct window_d *messagebox_button2;


struct window_d *dialogbox_button1;
struct window_d *dialogbox_button2;


unsigned long 
mbProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 );
					 
unsigned long 
dbProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 );
					 
/*
 ***********************************************************************
 * system_call:  #ux4 (maior experiência)
 *    Interrupção de sistema, número 200, chama vários serviços do Kernel com 
 * a mesma interrupção. Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, O número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 *
 * 2015 - Created.
 * 2016 - Revisão.
 * ...
 */
void *system_call ( unsigned long ax, 
                    unsigned long bx, 
				    unsigned long cx, 
				    unsigned long dx )
{
    
	//##BugBug: Aqui 0 retorno não pode ser inteiro.
	//Temos que pegar unsigned long?? void*. ??
	int RET = 0;	
	//unsigned long RET = 0;
	
    //System interrupt. 	
	asm volatile ("int %1 \n"
	              : "=a"(RET)	
		          : "i"(IA32_SYSCALL_VECTOR), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
    //Nothing.
	
	return (void *) RET; 
};


/*
 * apiSystem: 
 *
 * Argumento:
 *    Interpreta um comando e envia uma systemcall para o kernel.
 *    Obs: Assim como system, isso deve chamar aplicativos. 
 * ?? Talvez deva chamar o próprio shell ??     
 */
int apiSystem (const char *command){
    
    // @todo: Checar se comando é válido, se os primeiros caracteres
	//        são espaço. Ou talvez somente compare, sem tratar o argumento.

	//@todo:
	// Criar rotina para pular os caracteres em branco no início do comando.
	
	//@todo: version, ...
	
	//OBS: ESSES SÃO OS COMANDOS DO SISTEMA, USADOS POR TODOS OS PROGRAMAS
	//     QUE INCLUIREM A API. 
	
	//test - Exibe uma string somente para teste.
	if ( api_strncmp( (char *) command, "test", 4 ) == 0 )
	{
	    printf("apiSystem: Testing commands..\n");
		goto exit;
	}; 	
  
	//ls - List files in a folder.
	if ( api_strncmp( (char *) command, "ls", 2 ) == 0 )
	{
	    printf("apiSystem: @todo: ls..\n");
		goto exit;
	}; 
	
	//makeboot - Cria arquivos e diretórios principais.
	if ( api_strncmp( (char *) command, "makeboot", 8 ) == 0 )
	{
	    printf("apiSystem: @todo: makeboot..\n");
		
		//ret_value = fs_makeboot();
		//if(ret_value != 0){
		//    printf("shell: makeboot fail!");
		//};
		
        goto exit;
    };
	
	//format.
	if ( api_strncmp( (char *) command, "format", 6 ) == 0 )
	{
	    printf("apiSystem: @todo: format..\n");
		//fs_format(); 
        goto exit;
    };	
	
	//debug.
	if ( api_strncmp( (char *) command, "debug", 5 ) == 0 )
	{
	    printf("apiSystem: @todo: debug..\n");
		//debug();
        goto exit;
    };
	
    //dir.
	if ( api_strncmp( (char *) command, "dir", 3 ) == 0 )
	{
	    printf("apiSystem: @todo: dir..\n");
		//fs_show_dir(0); 
        goto exit;
    };

	//newfile.
	if ( api_strncmp( (char *) command, "newfile", 7 ) == 0 )
	{
	    printf("apiSystem: ~newfile - Create empty file.\n");
		//fs_create_file( "novo    txt", 0);
        goto exit;
    };
	
	//newdir.
	if ( api_strncmp( (char *) command, "newdir", 7 ) == 0 )
	{
	    printf("apiSystem: ~newdir - Create empty folder.\n");
		//fs_create_dir( "novo    dir", 0);
        goto exit;
    };
	
    //mbr - Testa mbr.
    if ( api_strncmp( (char *) command, "mbr", 3 ) == 0 )
	{
	    printf("apiSystem: ~mbr\n");
		//testa_mbr();
		goto exit;
    }; 
	
    //root - Testa diretório /root.
    if ( api_strncmp( (char *) command, "root", 4 ) == 0 )
	{
	    printf("apiSystem: ~/root\n");
		//testa_root();
		goto exit;
    }; 

	//start.
    if ( api_strncmp( (char *) command, "start", 5 ) == 0 )
	{
	    printf("apiSystem: ~start\n");
		goto exit;
    }; 
	
	//help.
	//?? O que mostrar aqui ??
    if ( api_strncmp( (char *) command, "help", 4 ) == 0 )
	{
		printf("apiSystem: help stuff\n");
		//printf(help_string);
		//print_help();
		goto exit;
    };
	
	//cls.
    if ( api_strncmp( (char *) command, "cls", 3 ) == 0 )
	{
	    printf("apiSystem: cls\n");
		//black
	    //api_clear_screen(0);
        goto exit;
	};
	
	//save.
	if ( api_strncmp( (char *) command, "save", 4 ) == 0 )
	{
	    printf("apiSystem: ~save\n");
        goto exit;
    };
	
	//install.
	//muda um arquivo da area de transferencia para 
	//o sistema de arquivos...
	if ( api_strncmp( (char *) command, "install", 7 ) == 0 )
	{
	    printf("apiSystem: ~install\n");
		//fs_install();
        goto exit;
    };
	
	
	//boot - Inicia o sistema.
	if ( api_strncmp( (char *) command, "boot", 4 ) == 0 )
	{
	    printf("apiSystem: ~boot\n");
		//boot();
        goto exit;
    };

	//service
	if ( api_strncmp( (char *) command, "service", 7 ) == 0 )
	{
	    printf("apiSystem: ~service - rotina de servicos do kernel base\n");
		//test_services();
        goto exit;
    };

	//slots - slots de processos ou threads.
	if ( api_strncmp( (char *) command, "slots", 5 ) == 0 )
	{
	    printf("apiSystem: ~slots - mostra slots \n");
		//mostra_slots();
        goto exit;
    };
	
	
    //
    // Continua ...
    //
	
	//exit - Exit the current program
    if ( api_strncmp( (char *) command, "exit", 4 ) == 0 )
	{
		printf("apiSystem: exit\n");
		//exit(exit_code);
		apiExit(0);
		goto fail;
    };
		
    //reboot.
	if ( api_strncmp( (char *) command, "reboot", 6 ) == 0 )
	{
		printf("apiSystem: reboot\n");
		apiReboot();
		goto fail;
    };

	//shutdown.
    if ( api_strncmp( (char *) command, "shutdown", 8 ) == 0 )
	{
		printf("apiSystem: shutdown\n");
		apiShutDown();
        goto fail;
    };
	
	//@todo: exec
	
    //:default
	printf ("apiSystem: Unknown command!\n");
	
	//
	// o que devemos fazer aqui é pegar o nome digitado e comparar
	// com o nome dos arquivos do diretório do sistema. se encontrado,
	// devemos carregar e executar.
	//
	
// Fail. Palavra não reservada.	
fail:
    printf("apiSystem: FAIL\n");
    return (int) 1;

//@todo: Esse exit como variavel local precisa mudar de nome	
//       para não confundir com a função exit de sair do processo.
//       uma opção é usar 'done:'. 
exit:    
    return (int) 0;
};


//
// *IMPORTANTE: 
// @TODO: ESSAS ROTINAS ENUMERADAS PODEM CHAMAR AS CLASSES DO KERNEL
//              (RAM, CPU, DMA, UNBLOCKED, BLOCKED, THINGS)
//


/*
 * system1:
 *     int 201, serviço 1, Print pixel. (rever)
 */ 
int system1 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile (" int %1 \n"
		          : "=a"(ret_val)	
		          : "i"(201), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};



/*
 * system2:
 *     int 202, serviço 2, Print horizontal line.  (rever)
 */
int system2 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile (" int %1 \n"
		          : "=a"(ret_val)		
		          : "i"(202), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system3:
 *     int 203, serviço 3. Retângulo.  (rever)
 */
int system3 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(203), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system4:
 *     int 204, serviço 4. Putch.  (rever)
 */
int system4 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(204), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system5:
 *     int 205, serviço 5. Print string.  (rever)
 */
int system5 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(205), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system6:
 *     int 206, serviço 6. Message box using buffer.  (rever)
 */
int system6 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(206), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system7:
 *     int 207, serviço 7.  (rever)
 */
int system7 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(207), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system8:
 *     int 208, serviço 8.  (rever)
 */
int system8 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(208), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system9:
 *     int 209, serviço 9.
 *     Chama o procedimento da vez. 
 *     Executa outro procedimento.  (rever)
 */  
int system9 ( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(209), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system10:
 *     int 210, serviço 10. v
 */
int system10 ( unsigned long ax, 
               unsigned long bx, 
			   unsigned long cx, 
			   unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(210), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system11:
 *     int 211, serviço 11.  (rever)
 */
int system11 ( unsigned long ax, 
               unsigned long bx, 
			   unsigned long cx, 
			   unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(211), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system12:
 *     int 212, serviço 12.
 */
int system12 ( unsigned long ax, 
               unsigned long bx, 
			   unsigned long cx, 
			   unsigned long dx )
{
    int ret_val;
	
    asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(212), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};



/*
 * system13:
 *     int 213, serviço 13.
 */
int system13 ( unsigned long ax, 
               unsigned long bx, 
			   unsigned long cx, 
			   unsigned long dx )
{
    int ret_val;
	
	asm volatile (" int %1 \n"
		          : "=a"(ret_val)		
		          : "i"(213), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system14:
 *     int 214, serviço 14.  (rever)
 */
int system14 ( unsigned long ax, 
               unsigned long bx, 
			   unsigned long cx, 
			   unsigned long dx )
{
    int ret_val;
	
    asm volatile (" int %1 \n "
		          : "=a"(ret_val)		
		          : "i"(214), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * system15:
 *      int 215, serviço 15.  (rever)
 */
int system15 ( unsigned long ax, 
               unsigned long bx, 
			   unsigned long cx, 
			   unsigned long dx )
{
	int ret_val;
	
	asm volatile ("int %1\n"
		          : "=a"(ret_val)		
		          : "i"(215), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
	return (int) ret_val;
};


/*
 * refresh_buffer:
 *     int 200, serviços de 1 à 9.
 *     Refresh buffer.
 *     Atualiza um buffer dado seu número.  (rever)
 */
void refresh_buffer (unsigned long n){
	
	// Limits.
	if (n < 1 || n > 9)
	{
	    return;
	};
		
    switch (n){
		
        //refresh buffer 1,2,3
        
		case 1: 
		    system_call( 1, 0, 0, 0); 
			break;
        case 2: 
		    system_call( 2, 0, 0, 0); 
			break;
        case 3: 
		    system_call( 3, 0, 0, 0); 
			break;
                 
        //refresh screen     
        case 4: 
		    system_call( 4, 0, 0, 0); 
			break;
             
        //refresh title bar    
        case 5: 
		    system_call( 5, 0, 0, 0); 
			break;
                 
        //refresh menu bar     
        case 6: 
		    system_call( 6, 0, 0, 0); 
			break;
                 
        //refresh tollbar    
        case 7: 
		    system_call( 7, 0, 0, 0); 
			break;
                 
        //refresh status bar   
        case 8: 
		    system_call( 8, 0, 0, 0); 
			break;

        //refresh taskbar   
        case 9: 
		    system_call( 9, 0, 0, 0); 
			break;
                 
        default:
            //Nothing
			break;
    };
};


/*
 * print_string:
 *     int 200, serviço 10.
 *     Print string no buffer.  (rever)
 */
void print_string ( unsigned long x,  
                    unsigned long y,  
				    unsigned long color, 
				    unsigned char *string )
{	
    //system( 10, x, y, (unsigned long) string);        
};


/*
 * vsync:
 *     Int 200, serviço 15.
 *     Sincroniza o retraço vertical do monitor.  (rever)
 */
int vsync (){
	
	system_call ( SYSTEMCALL_VSYNC, 0, 0, 0 );
    
	return (int) 0;
};


/*
 * edit_box:
 *     Interrupção 200, serviço SYSTEMCALL_EDITBOX.  (rever)
 */
int edit_box ( unsigned long x,  
               unsigned long y, 
			   unsigned long height, 
			   unsigned long width)
{
	//@todo: Altura e largura negligenciados.
    system_call ( SYSTEMCALL_EDITBOX, x, y, 0 );
	
	return (int) 0;
};


/*
 * chama_procedimento:
 *     Interrupção 200, serviço SYSTEMCALL_CALL_SYSTEMPROCEDURE. 
 *     Chama o proximo procesimento de janela.
 *     Obs: Lembrando que estamos usando endereços lógicos.  (rever)
 */
int chama_procedimento (unsigned long proximo_procedure){
	
    system_call ( SYSTEMCALL_CALL_SYSTEMPROCEDURE, proximo_procedure, 0, 0 );    
	
	return (int) 0;
};


/*
 * SetNextWindowProcedure
 *     Interrupção 200, serviço SYSTEMCALL_SETPROCEDURE. 
 *     Setar o endereço do procedimento que deverá ser chamado. 
 *     Obs: Lembrando que estamos usando endereços lógicos.  (rever)
 */
int SetNextWindowProcedure (unsigned long next_procedure){
	
    system_call ( SYSTEMCALL_SETPROCEDURE, next_procedure, 0, 0 );
    
	return (int) 0;	
};


/*
 * set_cursor:
 *     Configura as posições do cursor.
 *     Interrupção 200, serviço SYSTEMCALL_SETCURSOR.  (rever)
 *     @todo: Criar o protótipo no header.
 */
int set_cursor (unsigned long x, unsigned long y){
	
    system_call ( SYSTEMCALL_SETCURSOR, x, y, 0 );
	
	return (int) 0;
};


/*
 * put_char:
 *     Put char.  (rever)
 */
void put_char ( unsigned long x,  
                unsigned long y,  
			    unsigned long color, 
			    unsigned char *ch )
{
    //return;    //Nothing for now.
};


/*
 * carrega_bitmap_16x16:
 *     Coloca um bitmap no buffer.
 *     interrupção 200, serviço SYSTEMCALL_LOAD_BITMAP_16x16, 
 *     pôe um bitmap no buffer.
 *
 *     ?? @todo: Rever, onde pega e pra onde vai.
 *
 * a - endreço da imagem. 
 * b - x
 * c - y 
 * d - null
 *
 * Obs: 
 *     Lembrar que estamos usando endereços lógicos.  (rever)
 */
void carrega_bitmap_16x16 ( unsigned long img_address, 
                            unsigned long x, 
						    unsigned long y )                           
{
    system_call ( SYSTEMCALL_LOAD_BITMAP_16x16, img_address, x, y ); 	
};


/*
 * apiShutDown:
 *     Desliga a máquina.
 *     Interrupção 200, serviço SYSTEMCALL_SHUTDOWN.
 *     Metodo? ACPI, APM ...  (rever)
 */
void apiShutDown (){
	
	// @todo: 
	// A API pode chamar algumas rotinas ainda aqui em user mode
	// antes de chamar o kernel.
	
	// Um messagebox pode aparece antes de chamar o kernel.
	
	//Argumentos podem ser enviados.
    system_call ( SYSTEMCALL_SHUTDOWN, 0, 0, 0 );
	
    while (1){
		
        asm ("pause");
	};	
};


/*
 * apiInitBackground:
 *     Initialize default background configuration.  (rever)
 */
void apiInitBackground (){
	
    //@todo: Implementar.	
    //return;    //Não há uma chamada para isso ainda.            
};


/*
 * MessageBox:
 *     Message box on gui->screen.
 *     Types=[1~5]
 *     @todo: Devemos considerar o retorno? E se a chamada falhar?
 */
int MessageBox ( int type, char *string1, char *string2 ){
    
    // Antes nós chamávamos o kernel, agora tentaremos 
    // implantar na api.
	
	//system_call ( SYSTEMCALL_MESSAGE_BOX, (unsigned long) type, 
	//	(unsigned long) string1, (unsigned long) string2 );
	

	//#debug
	//printf ("Testing new Message Box type=%d \n", type);

    int Response = 0;	
    int running = 1;

    //
    // Draw !
    //	
	
	struct window_d *hWnd;    //Window.
	struct window_d *pWnd;    //Parent.
	struct window_d *bWnd;    //Button.	
	
	
	//#todo: usar get system metrics
	
	// x and y
	// @todo centralizado: metade | um terço.
	// @todo: Pegar a métrica do dispositivo.
	unsigned long x  = (unsigned long) 10;       //deslocamento x
	unsigned long y  = (unsigned long) 300;       //deslocamento y
    unsigned long cx = (unsigned long) (800/2);  //largura   
    unsigned long cy = (unsigned long) (600/3);  //altura		

	int Button = 0;	
	
	unsigned long WindowClientAreaColor;
	unsigned long WindowColor;
	
	
	WindowClientAreaColor = COLOR_YELLOW;
	WindowColor = COLOR_PINK;	
	
	//Obs: Por enquanto para todos os tipos de messagebox 
	// estamos usando o mesmo tipo de janela.
	switch (type)
	{	
	    // Com botão, considera o título.
	    case 1:
		    apiBeginPaint();
		    Button = 1;
			//janela tipo simples.
	        hWnd = (void*) APICreateWindow (  WT_SIMPLE, 1, 1, string1, 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
			if ( (void *) hWnd == NULL ){
				printf("hWnd fail\n");
			};
			apiEndPaint();
            
			APIRegisterWindow (hWnd);
            APISetActiveWindow (hWnd);	
            APISetFocus (hWnd);	 			
		    break;
			
		// Sem botão, considera o título.	
	    case 2:
		    Button = 0;
	        hWnd = (void*) APICreateWindow( WT_POPUP, 1, 1, string1, 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		// Com botão, Título de alerta.	
	    case 3:
		    //janela de aplicativo.
	        Button = 1;
			hWnd = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1, "Alert", 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		//Com botão, título de mensagem do sistema.	
	    case 4:
		    Button = 1;
	        hWnd = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1, "System Message", 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		//Tipo negligenciado. Usamos o formato padrão.	
		default:
		    Button = 1;
	        hWnd = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1, "Error", 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
		    break;
	};
	
	
	//
	// button
	//
	
	//obs: o procedure vai precisar dos botões então tem que declarar global.
	
	//unsigned long app1Left = ((ScreenWidth/8) * 2);
	//unsigned long app2Left = ((ScreenWidth/8) * 3);
	
	//unsigned long app1Top = ( (ScreenHeight/10) * 8); 
	//unsigned long app2Top = app1Top; 



	//
	// botão de reboot
	//
	
    //.	
	messagebox_button1 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "OK",     
                                (cx/3), ((cy/4)*3), 80, 24,    
                                hWnd, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );
								
    APIRegisterWindow (messagebox_button1);


	//
	// botão de close
	//
	
    //.	
	messagebox_button2 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "CANCEL",     
                                ((cx/3)*2), ((cy/4)*3), 80, 24,    
                                hWnd, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );
								
    APIRegisterWindow (messagebox_button2);	
	
	
	//
	// string
	//
	
    apiDrawText ( (struct window_d *) hWnd,
        1*(cx/16), 1*(cy/3),
        COLOR_WINDOWTEXT, string1 );	
	
	
	//#bugbug
	//#importante devemos fazer o refresh só da janela.
	//refresh_screen ();

    apiShowWindow (hWnd);	
	
	//
	// loop
	//
	
	unsigned long message_buffer[5];	
	
	message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[3] = 0;
    message_buffer[4] = 0;	
		
Mainloop:
	
	while (running)
	{
		enterCriticalSection(); 
		system_call ( 111, (unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0], 
			(unsigned long)&message_buffer[0] );
		exitCriticalSection(); 
			
		if ( message_buffer[1] != 0 )
		{
	        
			Response = (int) mbProcedure ( (struct window_d *) message_buffer[0], 
		                        (int) message_buffer[1], 
		                        (unsigned long) message_buffer[2], 
		                        (unsigned long) message_buffer[3] );
			
			if (Response > 100)
			{
				printf ("Response=%d \n", Response );
				goto exit_messagebox;
			}
			message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;	
        };				
	};	

exit_messagebox:

	//#debug
	printf ("Exiting Message Box \n");
	
    return (int) Response;	
};


/*
 **************************************************
 * mbProcedure:
 *     O procedimento padrão de message box.
 */																
unsigned long 
mbProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 )
{
    switch (msg)
	{
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:	
				    printf ("scape\n");
                    return (unsigned long) 101;				   
				    break;
				   
                default:
				    //printf ("defaul keydown\n");
				    return (unsigned long) 0;
                    break; 
            };
        break;
	
        case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {	
				//Test.
				case VK_F1:
				    printf ("f1\n");
                    return (unsigned long) 102;
					break;
					
                //case VK_F2:
				    //Nothing.
				//	break;
									
				default:
				    //printf ("default sys key down\n");
				    return (unsigned long) 0;
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
		   //printf ("sys key up\n");
		   return (unsigned long) 0; 
           break;
		
        //@todo case command .. button ??
		
		default:
		    //printf ("default message\n");
		    return (unsigned long) 0;
            break;		
	};
	
	
done:
	//Refresh screen. 
	//?? deletar.
	//if(VideoBlock.useGui == 1){
	//    refresh_screen();
	//};
    printf ("done\n");	
	return (unsigned long) 0;
};




/*
 * DialogBox:
 *     
 *     Types=[1~5]
 *     @todo: Devemos considerar o retorno? E se a chamada falhar?
 */
int DialogBox ( int type, char *string1, char *string2 ){
    
    //
    // Antes nós chamávamos o kernel, agora tentaremos 
    // implantar na api.
	//
	
	//system_call ( SYSTEMCALL_MESSAGE_BOX, (unsigned long) type, 
	//	(unsigned long) string1, (unsigned long) string2 );
	

	//#debug
	//printf ("Testing dialog Box type=%d \n", type);

    int Response = 0;	
    int running = 1;

    //
    // Draw !
    //	
	
	struct window_d *hWnd;    //Window.
	struct window_d *pWnd;    //Parent.
	struct window_d *bWnd;    //Button.	
	
	
	//#todo: usar get system metrics
	
	// x and y
	// @todo centralizado: metade | um terço.
	// @todo: Pegar a métrica do dispositivo.
	unsigned long x  = (unsigned long) 10;       //deslocamento x
	unsigned long y  = (unsigned long) 300;       //deslocamento y
    unsigned long cx = (unsigned long) (800/2);  //largura   
    unsigned long cy = (unsigned long) (600/3);  //altura		

	int Button = 0;	
	
	unsigned long WindowClientAreaColor;
	unsigned long WindowColor;
	
	
	WindowClientAreaColor = COLOR_YELLOW;
	WindowColor = COLOR_PINK;	
	
	//Obs: Por enquanto para todos os tipos de messagebox 
	// estamos usando o mesmo tipo de janela.
	switch (type)
	{	
	    // Com botão, considera o título.
	    case 1:
		    apiBeginPaint();
		    Button = 1;
			//janela tipo simples.
	        hWnd = (void*) APICreateWindow (  WT_SIMPLE, 1, 1, string1, 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
			if ( (void *) hWnd == NULL ){
				printf("hWnd fail\n");
			};
			apiEndPaint();
            
			APIRegisterWindow (hWnd);
            APISetActiveWindow (hWnd);	
            APISetFocus (hWnd);	 			
		    break;
			
		// Sem botão, considera o título.	
	    case 2:
		    Button = 0;
	        hWnd = (void*) APICreateWindow( WT_POPUP, 1, 1, string1, 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		// Com botão, Título de alerta.	
	    case 3:
		    //janela de aplicativo.
	        Button = 1;
			hWnd = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1, "Alert", 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		//Com botão, título de mensagem do sistema.	
	    case 4:
		    Button = 1;
	        hWnd = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1, "System Message", 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
	        break;
			
		//Tipo negligenciado. Usamos o formato padrão.	
		default:
		    Button = 1;
	        hWnd = (void*) APICreateWindow( WT_OVERLAPPED, 1, 1, "Error", 
			                x, y, cx, cy, 
							NULL, 0, 
							WindowClientAreaColor, WindowColor); 
		    break;
	};
	
	
	//
	// button
	//
	
	//obs: o procedure vai precisar dos botões então tem que declarar global.
	
	//unsigned long app1Left = ((ScreenWidth/8) * 2);
	//unsigned long app2Left = ((ScreenWidth/8) * 3);
	
	//unsigned long app1Top = ( (ScreenHeight/10) * 8); 
	//unsigned long app2Top = app1Top; 



	//
	// botão de reboot
	//
	
    //.	
	dialogbox_button1 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "OK",     
                                (cx/3), ((cy/4)*3), 80, 24,    
                                hWnd, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );
								
    APIRegisterWindow (dialogbox_button1);


	//
	// botão de close
	//
	
    //.	
	dialogbox_button2 = (void *) APICreateWindow ( WT_BUTTON, 1, 1, "CANCEL",     
                                ((cx/3)*2), ((cy/4)*3), 80, 24,    
                                hWnd, 0, xCOLOR_GRAY1, xCOLOR_GRAY1 );
								
    APIRegisterWindow (dialogbox_button2);	
	
	
	//
	// string
	//
	
    apiDrawText ( (struct window_d *) hWnd,
        1*(cx/16), 1*(cy/3),
        COLOR_WINDOWTEXT, string1 );	
	
	//#bugbug
	//#importante devemos fazer o refresh só da janela.
	//refresh_screen ();

    apiShowWindow (hWnd);		 
	
	//
	// loop
	//
	
	unsigned long message_buffer[5];	
	
	message_buffer[0] = 0;
    message_buffer[1] = 0;
    message_buffer[3] = 0;
    message_buffer[4] = 0;	
		
Mainloop:
	
	while (running)
	{
		enterCriticalSection(); 
		system_call ( 111, (unsigned long)&message_buffer[0],
			(unsigned long)&message_buffer[0], 
			(unsigned long)&message_buffer[0] );
		exitCriticalSection(); 
			
		if ( message_buffer[1] != 0 )
		{
	        
			Response = (int) dbProcedure ( (struct window_d *) message_buffer[0], 
		                        (int) message_buffer[1], 
		                        (unsigned long) message_buffer[2], 
		                        (unsigned long) message_buffer[3] );
			
			if (Response > 100)
			{
				printf ("Response=%d \n", Response );
				goto exit_dialogbox;
			}
			message_buffer[0] = 0;
            message_buffer[1] = 0;
            message_buffer[3] = 0;
            message_buffer[4] = 0;	
        };				
	};	

exit_dialogbox:

	//#debug
	printf ("Exiting dialog Box \n");
	
    return (int) Response;	
};

/*
 **************************************************
 * dbProcedure:
 *     O procedimento padrão de message box.
 */																
unsigned long 
dbProcedure( struct window_d *window, 
                     int msg, 
   				     unsigned long long1, 
					 unsigned long long2 )
{
    switch (msg)
	{
        case MSG_KEYDOWN:
            switch(long1)
            {
                case VK_ESCAPE:	
				    printf ("scape\n");
                    return (unsigned long) 101;				   
				    break;
				   
                default:
				    //printf ("defaul keydown\n");
				    return (unsigned long) 0;
                    break; 
            };
        break;
	
        case MSG_SYSKEYDOWN:                 
            switch(long1)	       
            {	
				//Test.
				case VK_F1:
				    printf ("f1\n");
                    return (unsigned long) 102;
					break;
					
                //case VK_F2:
				    //Nothing.
				//	break;
									
				default:
				    //printf ("default sys key down\n");
				    return (unsigned long) 0;
				    break;
		    };              
        break;
		
	    case MSG_SYSKEYUP:
		   //printf ("sys key up\n");
		   return (unsigned long) 0; 
           break;
		
        //@todo case command .. button ??
		
		default:
		    //printf ("default message\n");
		    return (unsigned long) 0;
            break;		
	};
	
	
done:
	//Refresh screen. 
	//?? deletar.
	//if(VideoBlock.useGui == 1){
	//    refresh_screen();
	//};
    printf ("done\n");	
	return (unsigned long) 0;
};



/*
 * call_kernel:
 *     (FAST CALLS)
 *     @todo: Change name to apiCallKernel(...) 
 *
 *     Chama os serviços de Kernel. São usadas várias interrupções, 
 * uma para cada número de serviço. O Kernel pode oferecer vários 
 * serviços relativos à ele mesmo e à gerencia do sistema, como requests
 * por exemplo.
 *
 * Obs: Deve haver alguma restrição para o uso dessa chamada.
 * Quem deve usar ela são os drivers e servers. 
 * Os recursos acessados por essa chamada são mais críticos e 
 * sistemicamente importantes.  (rever)
 *
 * #todo: esse retorno deve ser unsigned long
 */
int call_kernel ( unsigned long int_number, 
                  unsigned long service_number, 
                  unsigned long arg1, 
                  unsigned long arg2, 
                  unsigned long arg3, 
                  unsigned long arg4,
                  unsigned long arg5, 
                  unsigned long arg6, 
                  unsigned long arg7, 
                  unsigned long arg8,
                  unsigned long arg9, 
                  unsigned long arg10, 
                  unsigned long arg11, 
                  unsigned long arg12 )
{
	int ret_val;
	
    switch (int_number){ 
                      
        //48 - Vários serviços de Kernel Requests.
        case KERNEL:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
    
        //49
        case KERNEL49:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL49), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        //50
        case KERNEL50:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL50), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
        
        //51     
        case KERNEL51:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL51), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        //52
        case KERNEL52:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL52), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;

        //53
        case KERNEL53:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL53), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
        
        //54     
        case KERNEL54:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL54), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;

        
        case KERNEL55:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL55), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case KERNEL56:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL56), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case KERNEL57:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL57), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        //
		// ...
		//
		
		case KERNEL199:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL199), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
        default:
            //Nothing.
            break;			
    };
	
	return (int) ret_val;
};



/*
 * call_gui:
 *     (FAST CALLS)
 *     Chama os serviçoos de GUI que estão
 *     em Kernel mode.
 *
 *     Uma interrupçãoo para cada serviço.
 *
 *     Quando o Kernel híbrido ofereçe
 *     rotinas gráficas há um ganho de desempenho.
 *
 *     Um subsistema de recursos gráficos em user mode
 *     pode usar essa chamada para utilizar recursos 
 *     gráficos do kernel.  (rever)
 *
 *  #todo: esse retorno deve ser unsigned long.
 */
int call_gui ( unsigned long int_number, 
               unsigned long service_number, 
               unsigned long arg1, 
               unsigned long arg2, 
               unsigned long arg3, 
               unsigned long arg4,
               unsigned long arg5, 
               unsigned long arg6, 
               unsigned long arg7, 
               unsigned long arg8,
               unsigned long arg9, 
               unsigned long arg10, 
               unsigned long arg11, 
               unsigned long arg12 )
{
	int ret_val;  
	
	//Vários serviços. 
			
    switch (int_number){      

        //Fast Create Window.		
        case FAST_CREATE_WINDOW:
		//case GUI:
            asm volatile ( " int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(FAST_CREATE_WINDOW), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
    
        case GUI217:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(GUI217), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case GUI218:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(GUI218), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case GUI219:
            asm volatile ( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(GUI219), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
		default:
		    //Nothing.
		    break; 
    };

	return (int) ret_val;
};
 

/*
 * APICreateWindow: 
 *     Cria uma janela com base em uma struct.
 *     Retorna o endereço da estrutura da janela criada. 
 *     Para que possa ser registrada na lista windowList[].
 * 
 *    Não é necessário passar todos os argumentos de uma vez só.
 *	  Podemos realizar 3 ou 4 chamadas para construírmos a janela.
 *	  Essa rotina tem 12 argumentos mas ela poderá realizar 3 chamadas
 *	  ao sistema para passar todos os argumentos.	
 *
 * Cria a janela dependendo do tipo:                              
 * =================================
 * 1 - POP-UP.
 * 2 - EDIT-BOX.
 * 3 - NORMAL ( bg + client area ).
 * 4 - NORMAL_EDIT ( bg + editbox).
 * 5 - MENUBAR.
 * 6 - TOOLBAR.
 * 7 - STATUSBAR.
 * 8 - TASKBAR.
 * 9 - ? 
 * CONTINUA ...
 *
 */
void *APICreateWindow( unsigned long type,        //1, Tipo de janela (popup,normal,...)
                       unsigned long status,      //2, Estado da janela (ativa ou nao)
                       unsigned long view,        //3, (min, max ...)
                       char *windowname,          //4, Título.                          
                       unsigned long x,           //5, Deslocamento em relação às margens do Desktop.                           
                       unsigned long y,           //6, Deslocamento em relação às margens do Desktop.
                       unsigned long width,       //7, Largura da janela.
                       unsigned long height,      //8, Altura da janela.
                       struct window_d *pWindow,  //9, Endereço da estrutura da janela mãe.
                       unsigned long onde,        //10, Ambiente.( Est� no desktop, barra, cliente ...)
                       unsigned long clientcolor, //11, Cor da área de cliente
                       unsigned long color )      //12, Color (bg) (para janela simples).
{ 
	struct window_d *Window;
	
    // Enviando tudo via argumento.
	// Esse método dá a possibilidade de enviarmos ainda 
	// mais argumentos. 
	// #importante: Isso está funcionado, Vamos fazer assim e 
	// não do jeito antigo.
	
	unsigned long message_buffer[12];
	
	//enterCriticalSection();
	message_buffer[0] = (unsigned long) type;
	message_buffer[1] = (unsigned long) status;
	message_buffer[2] = (unsigned long) view;
	message_buffer[3] = (unsigned long) windowname;
	message_buffer[4] = (unsigned long) x;
	message_buffer[5] = (unsigned long) y;
	message_buffer[6] = (unsigned long) width;
	message_buffer[7] = (unsigned long) height;
	message_buffer[8] = (unsigned long) pWindow;
	message_buffer[9] = (unsigned long) onde;
	message_buffer[10] = (unsigned long) clientcolor;
	message_buffer[11] = (unsigned long) color;
	
    Window = (void *) system_call ( 118 , (unsigned long) &message_buffer[0], 
					    (unsigned long) &message_buffer[0], 
						(unsigned long) &message_buffer[0] );
    
	//exitCriticalSection();								   
								   
	//Nothing.
	
	//Struct.
	if ( (void *) Window == NULL )
	{
	    return NULL;    //Fail.
    
	} else {
		
		// Obs: Temos as propriedades da janela criada.
		//      Talvez o endereço retornado esteja em área
		//      de memória protegida. Acessar essa estrutura pode 
		//      gerar um excessão.
        //      @todo: Cuidado com o retorno #bugbug 		
		
		
		// Se a janela criada for do tipo botão, então precisamos registrar. 
		// #obs: Podem haver outros tipo que precisam ser registrados.
		
		//if ( type == WT_BUTTON ){
			
		//    APIRegisterWindow (Window);
		//};
		
		//...
	    
		goto done;
	};
	
	//Nothing.
done:
	return (void *) Window;    
};


/*
 * APIRegisterWindow:
 *     Register Window.
 */
int APIRegisterWindow (struct window_d *window){
    
    // @todo: Filtrar argumento.	
	
	if ( (void *) window == NULL )
	{
		return (int) 1;
	};		
	
    system_call ( SYSTEMCALL_REGISTERWINDOW, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window);
		
    return (int) 0;	
};


/*
 * APICloseWindow:
 *     Close Window. 
 */
int APICloseWindow (struct window_d *window){
	
    // @todo: Filtrar argumento.	
	
	if ( (void *) window == NULL )
	{
		return (int) 1;
	};		
	
    system_call ( SYSTEMCALL_CLOSEWINDOW, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window );	
    
	return (int) 0;	
};


/*
 * APISetFocus:
 *     Set Focus.
 */
int APISetFocus (struct window_d *window){
	
    // @todo: Filtrar argumento.
    	
	if ( (void *) window == NULL )
	{
		return (int) 1;
	};		
	
    system_call ( SYSTEMCALL_SETFOCUS, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window );
		
	//a flag 1 indica que deve-se redesenha e efetuar refresh.
	//APIredraw_window (window,1);
		
    return (int) 0;	
};


/*
 * APIGetFocus:
 *     Get Focus.
 */
int APIGetFocus (){
	
    return (int) system_call ( SYSTEMCALL_GETFOCUS, 0, 0, 0 );	
};


/*
 * APIKillFocus:
 *     Kill Focus.
 */
int APIKillFocus (struct window_d *window){

    // @todo: Filtrar argumento.
	
	if ( (void *) window == NULL )
	{
		return (int) 1;
	};	
	
    system_call ( SYSTEMCALL_KILLFOCUS, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window );
		
	
	//a flag 1 indica que deve-se redesenha e efetuar refresh.
	//APIredraw_window ( window, 1 );
		
    return (int) 0;	
};


/*
 * APISetActiveWindow:
 *     Set Active Window.
 * @todo: Esse retorno pode ser void.
 */
int APISetActiveWindow (struct window_d *window){
	
    // @todo: Filtrar argumento.	
	
	if ( (void *) window == NULL )
	{
		return (int) 1;
	};
	
    system_call ( SYSTEMCALL_SETACTIVEWINDOW, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window );
		
	
	//a flag 1 indica que deve-se redesenha e efetuar refresh.
	//APIredraw_window ( window, 1 );
		
    return (int) 0;	
};


/*
 * APIGetActiveWindow:
 *     Get Active Window Id.
 */
int APIGetActiveWindow (){
	
    return (int) system_call ( SYSTEMCALL_GETACTIVEWINDOW, 0, 0, 0 );	
};


/*
 * APIShowCurrentProcessInfo:
 *     Mostra informações sobre o processo atual.
 */
void APIShowCurrentProcessInfo (){
	
	// @todo: Essa rotina devira apenas pegar os valores via system call
	//        e imprimir os valores obtidos usando rotinas em user mode.
	
	system_call ( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0 );
};



//*********
 
void APIresize_window ( struct window_d *window, 
                        unsigned long x, 
						unsigned long y )
{	
	system_call ( SYSTEMCALL_RESIZEWINDOW, (unsigned long) window, x, y );
};


/*
 * APIredraw_window:
 */
void APIredraw_window( struct window_d *window, unsigned long flags ){
	
	system_call ( SYSTEMCALL_REDRAWWINDOW, (unsigned long) window, 
		(unsigned long) flags, (unsigned long) flags );
};


void APIreplace_window ( struct window_d *window, 
                         unsigned long x, 
						 unsigned long y )
{
	system_call ( SYSTEMCALL_REPLACEWINDOW, (unsigned long) window, x, y );
};


void APImaximize_window (struct window_d *window){
	
	system_call ( SYSTEMCALL_MAXIMIZEWINDOW, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window);
};


void APIminimize_window (struct window_d *window){
	
	system_call ( SYSTEMCALL_MINIMIZEWINDOW, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window);	
};


//Envia uma mensagem PAINT para o aplicativo atualizar a área de trabalho.
void APIupdate_window (struct window_d *window){
	
	system_call ( 113, (unsigned long) window, 
		(unsigned long) window, (unsigned long) window);	
};


void *APIget_foregroung_window (){
	
	system_call ( SYSTEMCALL_GETFOREGROUNDWINDOW, 0, 0, 0 );	
};


void APIset_foregroung_window (struct window_d *window){
	
	system_call ( SYSTEMCALL_SETFOREGROUNDWINDOW, (unsigned long) window, 
	    (unsigned long) window, (unsigned long) window );
};


/*
 * exit:
 *     Torna zombie a thread atual.
 *     Mas o propósito é terminar sair do 
 *     programa, terminando o processo e
 *     liberar os recursos que o processo estava usando.
 */
void apiExit (int exit_code){
	
    system_call ( SYSTEMCALL_EXIT, (unsigned long) exit_code, 
		(unsigned long) exit_code, (unsigned long) exit_code );
    
    while (1){
		
		asm ("pause");
	};	
};


/*
 * kill:
 *     @todo: Poderia ser o envio de um sinal para um processo dado deu PID.  
 */
void kill (int exit_code){
	
	//#todo
    //return; //Não há uma chamada para isso ainda.
};


/*
 * dead_thread_collector:
 *     Aciona o coletor de threads zumbis.
 *     Procura em todos os slots por threads no estado ZOMBIE e fecha elas.
 *     @todo: Talvez essa rotina possa ser implemetada em user mode por um server,
 * ficando à cargo do kernel apenas fazer a realocação dos recursos de destruição das
 * estruturas. 
 */
void dead_thread_collector (){
	
    system_call ( SYSTEMCALL_DEAD_THREAD_COLLECTOR, (unsigned long) 0, 
		(unsigned long) 0, (unsigned long) 0 );	
};


/*
 * api_strncmp:
 *     Compara duas strings.
 *     @todo: Isso deve ser oferecido peloa libC e não pela api. 
 */
int api_strncmp (char *s1, char *s2, int len){
	
	int n = len;
	
	while (n > 0)
	{	
	    n--;
        
		if (*s1 != *s2)
		{
            return (int) 1;
        };
		
		*s1++;
		*s2++;
	};				
			
	if ( *s1 != '\0' || *s2 != '\0' ){
		
	    return (int) 2;
	};
	
	//Nothing.		
//done:

	return (int) 0;
};


/*
 * refresh_screen:
 *     Refresh Screen.
 *     Passa o conteúdo do backbuffer para o lfb.
 */
void refresh_screen (){
	
	system_call ( SYSTEMCALL_REFRESHSCREEN, 0, 0, 0 );
};


/*
 * api_refresh_screen:
 *     Refresh the LFB.
 *     Move the content of BackBuffer to LFB.
 */
void api_refresh_screen (){
	
	refresh_screen ();
};


/*
 * apiReboot:
 *     Reboot.
 */
void apiReboot (){
	
	// @todo: Fazer outras chamadas para
	//        as camadas de software de mais alto nível antes
    //        de efetuar o reboot de hardware propriamente dito. 	
	
    system_call ( SYSTEMCALL_REBOOT, 0, 0, 0 );	
};


/*
 * apiSetCursor: 
 *     Set cursor.
 */
void apiSetCursor ( unsigned long x, unsigned long y ){
	
    system_call ( SYSTEMCALL_SETCURSOR, x, y, 0 );	
};


/*
 * apiGetCursorX:
 *     Get cursor x. 
 */
unsigned long apiGetCursorX (){
	
    return (unsigned long) system_call ( SYSTEMCALL_GETCURSORX, 0, 0, 0 );
};


/*
 * apiGetCursorY:
 *     Get cursor y.
 */
unsigned long apiGetCursorY (){
	
    return (unsigned long) system_call (SYSTEMCALL_GETCURSORY, 0, 0, 0 );
};


/*
 * apiGetClientAreaRect:
 *     Get client area rect.
 */
void *apiGetClientAreaRect (){
	
    return (void *) system_call ( SYSTEMCALL_GETCLIENTAREARECT, 0, 0, 0 );	
};


/*
 * apiSetClientAreaRect:
 *     Enviar uma estrutura de retângulo criada em user mode para o kernel.
 */
void apiSetClientAreaRect (struct rect_d *r){
	
    system_call ( SYSTEMCALL_SETCLIENTAREARECT, (unsigned long) r, 
		(unsigned long) r, (unsigned long) r );
};


/*
 * apiCreateProcess:
 *     Create a process.
 */
void *apiCreateProcess( unsigned long process_eip, 
                        unsigned long process_priority, 
						char *name )
{
    return (void *) system_call ( SYSTEMCALL_CREATEPROCESS, process_eip, 
						process_priority, (unsigned long) name );		
};


/*
 * apiCreateThread:
 *     Create a thread.
 */
void *apiCreateThread( unsigned long thread_eip, 
                       unsigned long thread_priority, 
					   char *name )
{
    return (void *) system_call ( SYSTEMCALL_CREATETHREAD, thread_eip, 
						thread_priority, (unsigned long) name );		
};


/*
 ****************************************************************
 * apiStartThread:
 * coloca no estado standby para executar pela primeira vez
 * #BUGBUG: Não retornou. 
 */
void apiStartThread (void *Thread){

    system_call ( SYSTEMCALL_STARTTHREAD, (unsigned long) Thread, 
		(unsigned long) Thread, (unsigned long) Thread );	
};



/*
 * apiFOpen:
 *     Carrega na memória um arquivo.
 *     Usa um serviço do kernel para carregar um arquivo 
 * na memória.
 *     Obs: Devemos passar um endereço válido, previamente 
 * alocado. 
 */
void *apiFOpen(const char *filename, const char *mode){
	
    void *Ret;	
	
	enterCriticalSection();
	
	Ret = (void *) system_call ( SYSTEMCALL_READ_FILE, 
	                (unsigned long) filename, (unsigned long) mode, 0 );
					
	exitCriticalSection();
    
	return (void *) Ret;								
};


/*
 *************************************************************
 * apiSaveFile:
 *     Salva um arquivo no diretório raiz do volume de boot.
 *     Obs: Talvez possamos ter mais argumentos.
 *     #bugbug: Essa rotina seria mais fácil se todas as informações sobre
 * o arquivo fossem gerenciadas pelo kernel. Mas não é o que estamos fazendo agora.
 */
 
int
apiSaveFile ( char *file_name, 
              unsigned long file_size,  //size in sectors 
              unsigned long size_in_bytes,			
              char *file_address,
              char flag )  
{
    int Ret;
	
	
    // Enviando tudo via argumento.
	// Esse método dá a possibilidade de enviarmos ainda 
	// mais argumentos. 
	// #importante: Isso está funcionado, Vamos fazer assim e 
	// não do jeito antigo.
	
	unsigned long message_buffer[12];
	
	//enterCriticalSection();
	message_buffer[0] = (unsigned long) file_name;
	message_buffer[1] = (unsigned long) file_size;
	message_buffer[2] = (unsigned long) size_in_bytes;
	message_buffer[3] = (unsigned long) file_address;
	message_buffer[4] = (unsigned long) flag;
	//message_buffer[5] = (unsigned long) x;
	//message_buffer[6] = (unsigned long) x;
	//message_buffer[7] = (unsigned long) x;
	//message_buffer[8] = (unsigned long) x;
	//message_buffer[9] = (unsigned long) x;
	//message_buffer[10] = (unsigned long) x;
	//message_buffer[11] = (unsigned long) x;
		
	
	enterCriticalSection();
		
	Ret = (int) system_call ( SYSTEMCALL_WRITE_FILE,
	                (unsigned long) &message_buffer[0],     
                    (unsigned long) &message_buffer[0],  
                    (unsigned long) &message_buffer[0] );        
								
	exitCriticalSection(); 

    return (int) Ret;		
};


//Operação down em um semáforo indicado no argumento.
void apiDown (struct semaphore_d *s){
	
	int Status = 1;    //fail.
	
	if( (void*) s == NULL  )
	{
	    //Semáforo inválido, 
        //Bloquear a thread, não adianta fazer a system call.
        //@todo: Chamar rotina que bloqueia a thread.
		
		printf ("apiDown: *fail");
		while (1){
		    
            asm ("pause");			
		}
        
		//return;	
	};
		
tryAgain:	

	Status = (int) system_call( SYSTEMCALL_SEMAPHORE_DOWN, 
	                            (unsigned long) s, 
								(unsigned long) s, 
								(unsigned long) s );

    //0 = deu certo, entrada liberada na sessão crítica.
    //1 = algo deu errado espere tentando novamente.
    
	//Podemos entrar na região crítica.
	if(Status == 0){
		return;
	};
	
	//Devemos esperar, monitorando a flag ou bloquando a thread.
	if(Status = 1)
	{
		//
		// Opções:
		// + Bloqueamos a thread e quando ela acordar tentaremos novamente.
		// + Fazemos um loop monitorando a flag.
		//
		
		//Opção 1.
		//Exemplo: apiBlockThread(...)
		
		//Opção 2.
		goto tryAgain;
	};
	
fail:
	goto tryAgain;
};


//Operação up em um semáforo indicado no argumento.
void apiUp (struct semaphore_d *s){
	
	int Status = 1; //fail.
	
	if ( (void *) s == NULL  )
	{
	    //Semáforo inválido, 
        //Bloquear a thread, não adianta fazer a system call.
        //@todo: Chamar rotina que bloqueia a thread.
		
		printf ("apiUp: *fail");
		while (1){
		    
            asm ("pause");			
		}
        
		//return;		
	};

    //0 = deu certo, podemos asir da sessão crítica.
    //1 = algo deu errado, não conseguimos sair da sessão crítica.	
	
tryAgain:	

	Status = (int) system_call ( SYSTEMCALL_SEMAPHORE_UP, (unsigned long) s, 
						(unsigned long) s, (unsigned long) s );	

	//Ok , podemos sair sa sessão crítica.
	if (Status == 0){
		return;
	};

	//Deu errado a nossa tentativa d sair da sessão crítica.
	if (Status = 1)
	{
		//
		// Opções:
		// + Bloqueamos a thread e quando ela acordar tentaremos novamente.
		// + Fazemos um loop monitorando a flag.
		//
		
		//Opção 1.
		//Exemplo: apiBlockThread(...)
		
		//Opção 2.
		goto tryAgain;
	};	

fail:
	goto tryAgain;
};


//P (Proberen) testar.
void enterCriticalSection (){
	
	int S;
	
	while (1)
	{
	    S = (int) system_call( SYSTEMCALL_GET_KERNELSEMAPHORE, 0, 0, 0);
	    
		//Se deixou de ser 0 então posso entrar.
		//se ainda for 0, continuo no while.
		if( S == 1 ){
		    goto done;	
		};
		//Nothing.
	};
    //Nothing
done:
    //Muda para zero para que ninguém entre.
    system_call ( SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 0, 0, 0 );	
	return;
};

//V (Verhogen)incrementar.
void exitCriticalSection (){
	
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    system_call ( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0 );
};

void initializeCriticalSection (){
	
	//Inicializa em 1 o semáforo do kernel para que 
	//o primeiro possa usar.
	system_call ( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0 );
};


void apiBeginPaint (){
	
	enterCriticalSection ();
};


void apiEndPaint (){
	
	exitCriticalSection ();
};


//imprime um caractere usando o cursor do sistema.
void apiPutChar (int c){
	
	system_call ( SYSTEMCALL_SYS_PUTCHAR, c, c, c );
};


//Get process ID.
/*
int getpid(){
	return (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
}
*/



/*
 * apiDefDialog:
 *     Procedimento de janela adiado. 
 *     Usado pelos aplicativos ao fim dos 
 * seus procedimentos de janela.
 */
unsigned long 
apiDefDialog( struct window_d *window, 
              int msg, 
			  unsigned long long1, 
			  unsigned long long2 )
{
    
    //#todo

	return (unsigned long) 0;
};


/*
 * apiGetSystemMetrics:
 *     Obtem informações sobre dimensões e posicionamentos.
 */
 
unsigned long apiGetSystemMetrics (int index){
	
    return (unsigned long) system_call ( SYSTEMCALL_GETSYSTEMMETRICS, 
	                                     (unsigned long) index, 
										 (unsigned long) index, 
										 (unsigned long) index );
};


void api_set_current_keyboard_responder ( int i ){
	
    system_call ( SYSTEMCALL_SET_CURRENT_KEYBOARD_RESPONDER, 
	    (unsigned long) i, (unsigned long) i, (unsigned long) i );
};


int api_get_current_keyboard_responder (){
	
    return (unsigned long) system_call( SYSTEMCALL_GET_CURRENT_KEYBOARD_RESPONDER, 
	                                    (unsigned long) 0, 
										(unsigned long) 0, 
										(unsigned long) 0 );
};


void api_set_current_mouse_responder (int i){
	
    system_call ( SYSTEMCALL_SET_CURRENT_MOUSE_RESPONDER, (unsigned long) i, 
	    (unsigned long) i, (unsigned long) i );	
};


int api_get_current_mouse_responder (){
	
    return (unsigned long) system_call( SYSTEMCALL_GET_CURRENT_MOUSE_RESPONDER, 
	                                    (unsigned long) 0, 
										(unsigned long) 0, 
										(unsigned long) 0 );	
};


void api_set_window_with_text_input ( struct window_d *window ){
	
	if ( (void *) window == NULL ) {
		return;
	}
	
	if ( window->used != 1 || window->magic != 1234 ){
		return;
	}
	
    system_call ( SYSTEMCALL_SET_WINDOW_WITH_TEXT_INPUT, (unsigned long) window, 
	    (unsigned long) window, (unsigned long) window );
};


int api_get_window_with_text_input (){
	
    return (int) system_call ( SYSTEMCALL_GET_WINDOW_WITH_TEXT_INPUT, 
	                (unsigned long) 0, (unsigned long) 0, (unsigned long) 0 );	
};


/*
//enviamos um ponteiro par ao kernel carregar elementos na estrutura.
void api_receive_message( struct api_receive_message_d *m );
void api_receive_message( struct api_receive_message_d *m )
{
	//Enviamos para o kernel o ponteiro da estrutura que desejamos que ele 
	//coloque os valores.
	//o kernel deve atualizar a flag dizendo que tem alguma mensagems na estrutura.
    system_call( SYSTEMCALL_138, (unsigned long) m, (unsigned long) m, (unsigned long) m );
				 
};
*/


/*
 * gramadocore_init_execve:
 *     Executa um novo programa usando os recursos do processo INIT. 
 *     Utiliza-se o mesmo processo, apenas renomiamos o processo. 
 *     utiliza-se a mesma thread primária,
 * apenas renomeamos a thread.
 *
 * #importante: Por enquanto o shell tem uma dessa funcionando.
 */
 
int 
gramadocore_init_execve ( const char *filename, 
                          const char *argv[], 
                          const char *envp[] )
{
	
	//@todo: Ainda não implementada.
	
	//system_call( , , ,)
	
	return (int) -1;
};




/* UNIX style */
/* Ainda estamos testando isso. A rotina no kernel está 
clonando o a estrutura do processo mas ainda há outras coisas pra 
fazer como memória, diretório e a troca correta de diretório de 
páginas dutante o taskswitch */

int fork (){
	
    return (int) system_call ( SYSTEMCALL_FORK, (unsigned long) 0, 
					(unsigned long) 0, (unsigned long) 0 ); 
};



/*
 ********************************************************
 * execve:
 * Executes a new process.
 * PS: Does not return on success, and the text, data, bss, 
 * and stack of the calling process are overwritten by 
 * that of the program loaded. 
 */
 
int 
execve ( const char *filename, 
         const char *argv[], 
         const char *envp[] )
{
	
	//@todo: Ainda não implementada.
	
	return (int) -1;
};


/*
 * apiDialog:
 *     Diálogo de yes ou no.
 */
int apiDialog ( const char *string ){
	
    int Status = 1; // Yes!
	int ch;
	
	printf (string);
	
    while (1)
	{
	    ch = (int) api_getchar ();	    
		
		if ( ch != -1 )
	    {
	        switch (ch)
            {
				case VK_RETURN:
				    goto done;
                    break;				
					
			    case 'Y':
				case 'y':
				    printf("Yes\n");
			        Status = 1;
				    break;
				   
			    case 'N':
				case 'n':
			        printf("No\n");
					Status = 0;
				    break;
					
				//default:
				//    break;
		    };		   
		};
		
		asm ("pause");
	};
    
done:		
    return (int) Status;
};


int api_getchar (){
	
	return (int) system_call ( 137, 0, 0, 0 );
};


/*
 * apiDisplayBMP:
 *
 * Mostra na tela uma imagem bmp carregada na memória.
 * 
 * IN:
 *     address = endereço base
 *     x       = posicionamento 
 *     y       = posicionamento
 *     @todo: deletar w h 
 *
 *	// @todo: Criar defines para esses deslocamentos.
 */

static int nibble_count_16colors = 0;
 
int 
apiDisplayBMP ( char *address, 
                unsigned long x, 
				unsigned long y )
{
	int i, j, base, offset;
	
	unsigned long left, top, bottom;
	
	unsigned long color, color2;
	unsigned long pal_address;
	
	unsigned long Width;
	unsigned long Height;
	
	unsigned long xLimit, yLimit;
	
	struct bmp_header_d *bh;
	struct bmp_infoheader_d *bi;
	
	// Endereço base do BMP que foi carregado na memória
	unsigned char *bmp = (unsigned char *) address;
	
	// Variável para salvar rgba.
	unsigned char *c = (unsigned char *) &color;
    unsigned char *c2 = (unsigned char *) &color2;	
	
	unsigned long *palette = (unsigned long *) (address + 0x36);		
	unsigned char *palette_index = (unsigned char *) &pal_address;	
	
	
	// Limits
	
	xLimit = 800;
	yLimit = 600;
	
	
	//@todo: Refazer isso
	if ( x > xLimit || y > yLimit )
	{ 
        return (int) 1; 
	}
	

	
	//
	// @todo:
	// Testar validade do endereço.
	//
	
	
	if ( address == 0 )
	{
		//goto fail;
	};
	
	
	//
	// struct for Info header
	//
	
	bh = (struct bmp_header_d *) malloc ( sizeof(struct bmp_header_d) );
	
    if ( (void *) bh == NULL )
	{
		//goto fail;
	}	
	

	//
	// Signature.
	//
	
    unsigned short sig;
	
	sig = *( unsigned short * ) &bmp[0];
	
	bh->bmpType = sig;
	
	
	//
	// Size. ( 2 bytes )
	//
	
	unsigned short Size = *( unsigned short* ) &bmp[2];
	
	bh->bmpSize = Size;
	
	
	//
	// struct for Info header
	//
	
	//Windows bmp.
	bi = (struct bmp_infoheader_d *) malloc ( sizeof(struct bmp_infoheader_d) );
	
    if ( (void *) bi == NULL )
	{
		//goto fail;
	}	
	
	//The size of this header.
	bi->bmpSize = *( unsigned long * ) &bmp[14];
	
	// Width and height.
    Width = *( unsigned long * ) &bmp[18];
    Height = *( unsigned long * ) &bmp[22];	
	
	//@todo: checar validade da altura e da largura encontrada.
	
	// Salvar.
	bi->bmpWidth = (unsigned long) Width;
	bi->bmpHeight = (unsigned long) Height;
	
	
	/* Number of bits per pixel */
	//1, 4, 8, 16, 24 and 32.
	bi->bmpBitCount = *( unsigned short * ) &bmp[28];
	
	// Único suportado ainda.
	if ( bi->bmpBitCount != 24 )
	{
		//fail
	}
	
	
	// 0 = Nenhuma compressão.
	if ( bi->bmpCompression != 0 )
	{
		//fail
	}
	
	
	//
	// Draw !
	//
	
	left = x;    //
	top  = y; 
	
	
	//bottom = top + height;
	bottom = (top + bi->bmpHeight );

	// Início da área de dados do BMP.
	
	//#importante:
	//a base é diferente para os tipos.
	 

	switch (bi->bmpBitCount){
		
		//case 1:
		//    base = (0x36 + 0x40);
		//    break;
		    
		//case 2:
		//    base = (0x36 + 0x40);
		//    break;
			
		case 4:
		    //4bytes pra cada cor, 16 cores, 64bytes.
		    base = (0x36 + 0x40);
		    break; 
			
		case 8:
		    //4bytes pra cada cor, 256 cores, 1024bytes.
		    base = (0x36 + 0x400);
		    break; 
			
		default:
		    base = 0x36;
			break;
	};	
	

//1 - 1 bpp (Mono)
//4 - 4 bpp (Indexed)
//8 - 8 bpp (Indexed) bbgggrrr
//16565 - 16 bpp (5:6:5, RGB Hi color)
//16    - 16 bpp (5:5:5:1, RGB Hi color)
//160   - 16 bpp (5:5:5:1, RGBA Hi color)
//24 - 24 bpp (True color)
//32 - 32 bpp (True color, RGB)
//320 - 32 bpp (True color, RGBA)	


  
	// ## ABGR8888 ##
	// Little-endian
	// pegando os caracteres
	//
	// 0 = A (MSByte)(left byte) 
	// 1 = B 
	// 2 = G 
	// 3 = R
	//
	// Output long = 0xRRGGBBAA
    //	
	// Exemplo: gramado GUI
    //#define COLOR_RED   0xFF000000 
    //#define COLOR_GREEN 0x00FF0000
    //#define COLOR_BLUE  0x0000FF00

	
	for ( i=0; i < bi->bmpHeight; i++ )	
	{		
		for ( j=0; j < bi->bmpWidth; j++ )	
		{	
	        // 16 cores
            // Um pixel por nibble.
	        if ( bi->bmpBitCount == 4 )
	        {				
				offset = base;
							    
				palette_index[0] = bmp[offset];
												
                //segundo nibble.
				if( nibble_count_16colors == 2222 )
				{
					palette_index[0] = ( palette_index[0] & 0x0F);  
					color = (unsigned long) palette[  palette_index[0]  ];
					
					nibble_count_16colors = 0;
					base = base + 1;
					
				//primeiro nibble.	
				}else{

			        palette_index[0] =  ( (  palette_index[0] >> 4 ) & 0x0F);
					color = (unsigned long) palette[  palette_index[0] ];
				    
					nibble_count_16colors = 2222;
					base = base;
				};
	        };	

			// 256 cores
			// Próximo pixel para 8bpp
	        if( bi->bmpBitCount == 8 )
	        {   
				offset = base;
				color = (unsigned long) palette[  bmp[offset] ];
				
				base = base + 1;     
	        };			
			
			// 16bpp high color BMP
			// Próximo pixel para 16bpp
			// apenas 565 por enquanto.  
	        if ( bi->bmpBitCount == 16 )
	        {

			    //565
                //if(565 )
                //{
				    offset = base;					
					
				    //A
			        c[0] = 0;	

			        //b				
			        c[1] = bmp[offset];
			        c[1] = (c[1] & 0xF8);  // '1111 1000' 0000 0000  
				
				    //g
			        c2[0] = bmp[offset];
			        c2[0] = c2[0] &  0x07;    // '0000 0111' 0000 0000 
			        c2[1] = bmp[offset+1];
			        c2[1] = c2[1] &  0xE0;    //  0000 0000 '1110 0000' 
					c[2] = ( c2[0] | c2[1]  );
					
			        //r
			        c[3] = bmp[offset+1];
			        c[3] = c[3] & 0x1F;     // 0000 0000 '0001 1111' 										
		        
				    base = base + 2;    
				//};					
	        };			
			

			// Próximo pixel para 24bpp
	        if ( bi->bmpBitCount == 24 )
	        {
				offset = base;
			    
			    c[0] = 0; //A					
				
				c[1] = bmp[offset];
			    
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
										
		        base = base + 3;    
	        };
			
			
			// Próximo pixel para 32bpp
	        if ( bi->bmpBitCount == 32 )
	        { 
				//A
				//offset = base+3;
			    c[0] = 0;				
				
				offset = base;
			    c[1] = bmp[offset];
			
			    offset = base+1;
			    c[2] = bmp[offset];
			
			    offset = base+2;
			    c[3] = bmp[offset];
				
		        base = base + 4;    
	        };
			
			
			system_call ( SYSTEMCALL_BUFFER_PUTPIXEL, (unsigned long) color, 
				(unsigned long) left, (unsigned long) bottom );
			
			// Próximo pixel.
			left++; 
		};
		
		// Vamos para a linha anterior.
		bottom = bottom-1;
		
		// Reiniciamos o x.
		left = x;    
	};	
	
	// ## test palette 
	//int p;
	
	//if(bi->bmpBitCount == 8 )
	//{
	//    printf("\n");
	//    for( p=0; p<16; ++p )
	//    {
	//	   printf("%x\n",palette[p]);
	//    }
	//    printf("\n");
	//};
	
fail:	
    //printf("fail");	
done:	
	//Debug
	//printf("w={%d} h={%d}\n", bi->bmpWidth, bi->bmpHeight );
	return (int) 0;
};



//Coloca uma mensagem na estrutura de uma janela.
//ainda não temos filas de mensagem, então mensagens podem se perder 
//sendo sobrepostas.
unsigned long apiSendMessage ( struct window_d *window, 
                               int message,
                               unsigned long long1,
                               unsigned long long2 )
{	
	
	unsigned long message_buffer[5];
	
	//enterCriticalSection();
	message_buffer[0] = (unsigned long) window;
	message_buffer[1] = (unsigned long) message;
	message_buffer[2] = (unsigned long) long1;
	message_buffer[3] = (unsigned long) long2;  	
	
	
	return (unsigned long) system_call ( 114 , 
	                                     (unsigned long) &message_buffer[0], 
										 (unsigned long) &message_buffer[0], 
										 (unsigned long) &message_buffer[0] );	
};	



int apiDrawText ( struct window_d *window, 
                  unsigned long x, 
				  unsigned long y, 
				  unsigned long color, 
				  char *string )
{
	
	unsigned long msg[8];
	
    msg[0] = (unsigned long) window;
	msg[1] = (unsigned long) x;
	msg[2] = (unsigned long) y;
	msg[3] = (unsigned long) color;
	msg[4] = (unsigned long) string;
	//...
	
	return (int) system_call ( SYSTEMCALL_DRAWTEXT , 
	                (unsigned long) &msg[0], 
					(unsigned long) &msg[0], 
					(unsigned long) &msg[0] );		
};



struct window_d *apiGetWSScreenWindow (){
	
    return (struct window_d *) system_call ( 146 , 0, 0, 0 );
};


struct window_d *apiGetWSMainWindow (){
	
    return (struct window_d *) system_call ( 147 , 0, 0, 0 );
};


//create timer;
struct timer_d *apiCreateTimer ( struct window_d *window, 
                                 unsigned long ms, 
								 int type )
{
	return (struct timer_d *) system_call ( 222, 
	    (unsigned long) window, (unsigned long) ms, (unsigned long) type );
};


// pega informações varidas sobre o sys time.
unsigned long apiGetSysTimeInfo ( int n ){
	
	return (unsigned long) system_call ( 223, 
	    (unsigned long) n, (unsigned long) n, (unsigned long) n );
};

//mostra uma janela na tela. backbuffer ---> frontbuffer
void apiShowWindow (struct window_d *window){
	
    system_call ( 24, (unsigned long) window, 
	    (unsigned long) window, (unsigned long) window );	
};


//
// End.
//

