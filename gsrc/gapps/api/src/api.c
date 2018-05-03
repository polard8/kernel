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
 * Histórico: 
 *     Version 1.0, 2014 - Esse arquivo foi criado por Fred Nora.
 *     Version 1.0, 2015 - Implimentação de novas chamadas.
 *     Version 1.0, 2016 - Implementação de novas chamadas.
 *     ...
 */


//...
#include <types.h>   //privado
#include <heap.h>    //privado
#include <api.h>     //público, exportado para as aplicações.



/*
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
void *system_call( unsigned long ax, 
                   unsigned long bx, 
				   unsigned long cx, 
				   unsigned long dx )
{
    
	//##BugBug: Aqui 0 retorno não pode ser inteiro.
	//Temos que pegar unsigned long?? void*. ??
	int RET = 0;	
	//unsigned long RET = 0;
	
    //System interrupt. 	
	asm volatile("int %1 \n"
	             : "=a"(RET)	
		         : "i"(SYSTEM), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
    //Nothing.
done:
	return (void *) RET; 
};


/*
 * apiSystem: 
 *
 * Argumento:
 *    Interpreta um comando e envia uma systemcall para o kernel.
 */
int apiSystem(const char *command)
{
    //
    // @todo: Checar se comando é válido, se os primeiros caracteres
	//        são espaço. Ou talvez somente compare, sem tratar o argumento.
    //	

	
	//
	//@todo:
	// Criar rotina para pular os caracteres em branco no início do comando.
	//
	
	//@todo: version, ...
	
	//
	//OBS: ESSES SÃO OS COMANDOS DO SISTEMA, USADOS POR TODOS OS PROGRAMAS
	//     QUE INCLUIREM A API. 
	//
	
	//test - Exibe uma string somente para teste.
	if( api_strncmp( (char *) command, "test", 4 ) == 0 ){
	    printf("apiSystem: Testing commands ...\n");
		goto exit;
	}; 	
  
	//ls - List files in a folder.
	if( api_strncmp( (char *) command, "ls", 2 ) == 0 ){
	    printf("apiSystem: @todo: ls ...\n");
		goto exit;
	}; 
	
	//makeboot - Cria arquivos e diretórios principais.
	if( api_strncmp( (char *) command, "makeboot", 8 ) == 0 )
	{
	    printf("apiSystem: @todo: makeboot ...\n");
		
		//ret_value = fs_makeboot();
		//if(ret_value != 0){
		//    printf("shell: makeboot fail!");
		//};
        goto exit;
    };
	
	//format.
	if( api_strncmp( (char *) command, "format", 6 ) == 0 )
	{
	    printf("apiSystem: @todo: format ...\n");
		//fs_format(); 
        goto exit;
    };	
	
	//debug.
	if( api_strncmp( (char *) command, "debug", 5 ) == 0 )
	{
	    printf("apiSystem: @todo: debug ...\n");
		//debug();
        goto exit;
    };
	
    //dir.
	if( api_strncmp( (char *) command, "dir", 3 ) == 0 )
	{
	    printf("apiSystem: @todo: dir ...\n");
		//fs_show_dir(0); 
        goto exit;
    };

	//newfile.
	if( api_strncmp( (char *) command, "newfile", 7 ) == 0 )
	{
	    printf("apiSystem: ~newfile - Create empty file.\n");
		//fs_create_file( "novo    txt", 0);
        goto exit;
    };
	
	//newdir.
	if( api_strncmp( (char *) command, "newdir", 7 ) == 0 )
	{
	    printf("apiSystem: ~newdir - Create empty folder.\n");
		//fs_create_dir( "novo    dir", 0);
        goto exit;
    };
	
    //mbr - Testa mbr.
    if( api_strncmp( (char *) command, "mbr", 3 ) == 0 )
	{
	    printf("apiSystem: ~mbr\n");
		//testa_mbr();
		goto exit;
    }; 
	
    //root - Testa diretório /root.
    if( api_strncmp( (char *) command, "root", 4 ) == 0 )
	{
	    printf("apiSystem: ~/root\n");
		//testa_root();
		goto exit;
    }; 

	//start.
    if( api_strncmp( (char *) command, "start", 5 ) == 0 )
	{
	    printf("apiSystem: ~start\n");
		goto exit;
    }; 
	
	//help.
	//?? O que mostrar aqui ??
    if( api_strncmp( (char *) command, "help", 4 ) == 0 )
	{
		printf("apiSystem: help stuff\n");
		//printf(help_string);
		//print_help();
		goto exit;
    };
	
	//cls.
    if( api_strncmp( (char *) command, "cls", 3 ) == 0 )
	{
	    printf("apiSystem: cls\n");
		//black
	    //api_clear_screen(0);
        goto exit;
	};
	
	//save.
	if( api_strncmp( (char *) command, "save", 4 ) == 0 )
	{
	    printf("apiSystem: ~save\n");
        goto exit;
    };
	
	//install.
	//muda um arquivo da area de transferencia para 
	//o sistema de arquivos...
	if( api_strncmp( (char *) command, "install", 7 ) == 0 )
	{
	    printf("apiSystem: ~install\n");
		//fs_install();
        goto exit;
    };
	
	
	//boot - Inicia o sistema.
	if( api_strncmp( (char *) command, "boot", 4 ) == 0 )
	{
	    printf("apiSystem: ~boot\n");
		//boot();
        goto exit;
    };

	//service
	if( api_strncmp( (char *) command, "service", 7 ) == 0 )
	{
	    printf("apiSystem: ~service - rotina de servicos do kernel base\n");
		//test_services();
        goto exit;
    };

	//slots - slots de processos ou threads.
	if( api_strncmp( (char *) command, "slots", 5 ) == 0 )
	{
	    printf("apiSystem: ~slots - mostra slots \n");
		//mostra_slots();
        goto exit;
    };
	
	
    //
    // Continua ...
    //
	
	//exit - Exit the current program
    if( api_strncmp( (char *) command, "exit", 4 ) == 0 )
	{
		printf("apiSystem: exit\n");
		//exit(exit_code);
		exit(0);
		goto fail;
    };
		
    //reboot.
	if( api_strncmp( (char *) command, "reboot", 6 ) == 0 )
	{
		printf("apiSystem: reboot\n");
		apiReboot();
		goto fail;
    };

	//shutdown.
    if( api_strncmp( (char *) command, "shutdown", 8 ) == 0 )
	{
		printf("apiSystem: shutdown\n");
		apiShutDown();
        goto fail;
    };
	
	//@todo: exec
	
    //:default
	printf("apiSystem: Unknown command!\n");
	
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
int system1( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{
    int ret_val;
	
	//
	// ATENÇÃO: Não enviar argumentos via memória.
	//
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
	
    // salvando os argumentos

	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
    //chamando a interrupção.
    asm volatile( " int %1 \n"
		          : "=a"(ret_val)	
		          : "i"(201), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

done:
	return (int) ret_val;
};



/*
 * system2:
 *     int 202, serviço 2, Print horizontal line.  (rever)
 */
int system2( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
  
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4	
	*/
	
	
	//
    // Chamando a interrup��o.
	//
	
    asm volatile( " int %1 \n"
		          : "=a"(ret_val)		
		          : "i"(202), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

				  
done:
	return (int) ret_val;
};



/*
 * system3:
 *     int 203, serviço 3. Retângulo.  (rever)
 */
int system3( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{

    int ret_val;
		
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos

	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
    // Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(203), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

//
// Done.
//
done:
	return (int) ret_val;
};


/*
 * system4:
 *     int 204, serviço 4. Putch.  (rever)
 */
int system4( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{

    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
  	
    // salvando os argumentos
    
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(204), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system5:
 *     int 205, serviço 5. Print string.  (rever)
 */
int system5( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{

    int ret_val;

    /*	
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
 
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(205), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system6:
 *     int 206, serviço 6. Message box using buffer.  (rever)
 */
int system6( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{

    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
 
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(206), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system7:
 *     int 207, serviço 7.  (rever)
 */
int system7( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
  
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(207), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system8:
 *     int 208, serviço 8.  (rever)
 */
int system8( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{

    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *)0x900000;
	
    // salvando os argumentos
  
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
    //
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(208), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system9:
 *     int 209, serviço 9.
 *     Chama o procedimento da vez. 
 *     Executa outro procedimento.  (rever)
 */  
int system9( unsigned long ax, 
             unsigned long bx, 
			 unsigned long cx, 
			 unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
  
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(209), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system10:
 *     int 210, serviço 10. v
 */
int system10( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
 
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(210), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system11:
 *     int 211, serviço 11.  (rever)
 */
int system11( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
  
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
    //
	// CAll.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(211), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};


/*
 * system12:
 *     int 212, serviço 12.
 */
int system12( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos

	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
	// Call.
	//
	
    asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(212), "a"(ax), "b"(bx), "c"(cx), "d"(dx));

done:
	return (int) ret_val;
};



/*
 * system13:
 *     int 213, serviço 13.
 */
int system13( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
   
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
    // Call.
    //
	
	asm volatile( " int %1 \n"
		          : "=a"(ret_val)		
		          : "i"(213), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );
				  
//
// Done.
//
done:
	return (int) ret_val;
};


/*
 * system14:
 *     int 214, serviço 14.  (rever)
 */
int system14( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    int ret_val;
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
  
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
    // Call.
	//
	
    asm volatile( " int %1 \n "
		          : "=a"(ret_val)		
		          : "i"(214), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

//
// Done.
//				  
done:
	return (int) ret_val;
};


/*
 * system15:
 *      int 215, serviço 15.  (rever)
 */
int system15( unsigned long ax, 
              unsigned long bx, 
			  unsigned long cx, 
			  unsigned long dx )
{
    //
	// Return.
	//
	
	int ret_val;
	
	
	/*
	unsigned long *int_args  = (unsigned long *) 0x900000;
	
    // salvando os argumentos
 
	int_args[4]  = ax;  //arg1 ... so usa o primeiro .
    int_args[8]  = bx;  //arg2
	int_args[12] = cx;  //arg3
	int_args[16] = dx;  //arg4
	*/
	
	//
    // Call.
    //
	
	asm volatile( "int %1\n"
		          : "=a"(ret_val)		
		          : "i"(215), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

//
// Done.
//

done:
	return (int) ret_val;
};


/*
 * refresh_buffer:
 *     int 200, serviços de 1 à 9.
 *     Refresh buffer.
 *     Atualiza um buffer dado seu número.  (rever)
 */
void refresh_buffer(unsigned long n)
{
	// Limits.
	if(n < 1 || n > 9){
	    return;
	};
	
	// Number.	
    switch(n)
    {   
        //refresh buffer 1,2,3
        case 1: system_call( 1, 0, 0, 0); break;
        case 2: system_call( 2, 0, 0, 0); break;
        case 3: system_call( 3, 0, 0, 0); break;
                 
        //refresh screen     
        case 4: system_call( 4, 0, 0, 0); break;
             
        //refresh title bar    
        case 5: system_call( 5, 0, 0, 0); break;
                 
        //refresh menu bar     
        case 6: system_call( 6, 0, 0, 0); break;
                 
        //refresh tollbar    
        case 7: system_call( 7, 0, 0, 0); break;
                 
        //refresh status bar   
        case 8: system_call( 8, 0, 0, 0); break;

        //refresh taskbar   
        case 9: system_call( 9, 0, 0, 0); break;
                 
        default:
            //Nothing
			break;
    };
    //Nothing.
done:
    return;
};


/*
 * print_string:
 *     int 200, serviço 10.
 *     Print string no buffer.  (rever)
 */
void print_string( unsigned long x,  
                   unsigned long y,  
				   unsigned long color, 
				   unsigned char *string )
{

    //
	// Call.
	//
	
    //system( 10, x, y, (unsigned long) string);        
    
//
// Done.
//

done:	
	return;
};


/*
 * vsync:
 *     Int 200, serviço 15.
 *     Sincroniza o retraço vertical do monitor.  (rever)
 */
int vsync(){
	system_call(SYSTEMCALL_VSYNC,0,0,0);
    return (int) 0;
};


/*
 * edit_box:
 *     Interrupção 200, serviço SYSTEMCALL_EDITBOX.  (rever)
 */
int edit_box( unsigned long x,  
              unsigned long y, 
			  unsigned long height, 
			  unsigned long width)
{
	//@todo: Altura e largura negligenciados.
    system_call( SYSTEMCALL_EDITBOX, x, y, 0);
	return (int) 0;
};


/*
 * chama_procedimento:
 *     Interrupção 200, serviço SYSTEMCALL_CALL_SYSTEMPROCEDURE. 
 *     Chama o proximo procesimento de janela.
 *     Obs: Lembrando que estamos usando endereços lógicos.  (rever)
 */
int chama_procedimento( unsigned long proximo_procedure){	
    system_call( SYSTEMCALL_CALL_SYSTEMPROCEDURE, proximo_procedure, 0, 0);    
	return (int) 0;
};


/*
 * SetNextWindowProcedure
 *     Interrupção 200, serviço SYSTEMCALL_SETPROCEDURE. 
 *     Setar o endereço do procedimento que deverá ser chamado. 
 *     Obs: Lembrando que estamos usando endereços lógicos.  (rever)
 */
int SetNextWindowProcedure(unsigned long next_procedure){
    system_call( SYSTEMCALL_SETPROCEDURE, next_procedure, 0, 0);    
	return (int) 0;	
};


/*
 * set_cursor:
 *     Configura as posições do cursor.
 *     Interrupção 200, serviço SYSTEMCALL_SETCURSOR.  (rever)
 *     @todo: Criar o protótipo no header.
 */
int set_cursor(unsigned long x, unsigned long y){
    system_call( SYSTEMCALL_SETCURSOR, x, y, 0);
	return (int) 0;
};


/*
 * put_char:
 *     Put char.  (rever)
 */
void put_char( unsigned long x,  
               unsigned long y,  
			   unsigned long color, 
			   unsigned char *ch )
{
    return;    //Nothing for now.
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
void carrega_bitmap_16x16( unsigned long img_address, 
                           unsigned long x, 
						   unsigned long y )                           
{
    system_call( SYSTEMCALL_LOAD_BITMAP_16x16, img_address, x, y); 	
	return;
};


/*
 * apiShutDown:
 *     Desliga a máquina.
 *     Interrupção 200, serviço SYSTEMCALL_SHUTDOWN.
 *     Metodo? ACPI, APM ...  (rever)
 */
void apiShutDown()
{
	
	//
	// @todo: 
	// A API pode chamar algumas rotinas ainda aqui em user mode
	// antes de chamar o kernel.
	//
	
	//
	// Um messagebox pode aparece antes de chamar o kernel.
	//
	
	//Argumentos podem ser enviados.
    system_call( SYSTEMCALL_SHUTDOWN, 0, 0, 0);
    while(1){};	
};


/*
 * apiInitBackground:
 *     Initialize default background configuration.  (rever)
 */
void apiInitBackground()
{
    //@todo: Implementar.	
    return;    //Não há uma chamada para isso ainda.            
};


/*
 * MessageBox:
 *     Message box on gui->screen.
 *     Types=[1~5]
 *     @todo: Devemos considerar o retorno? E se a chamada falhar?
 */
void MessageBox(int type, char *string1, char *string2){
	system_call( SYSTEMCALL_MESSAGE_BOX, (unsigned long) type, (unsigned long) string1, (unsigned long) string2);
	return;
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
 */
int call_kernel( unsigned long int_number, 
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
	
	int ret_val;    //Retorno.
	
    switch(int_number)
    { 
                      
        //48 - Vários serviços de Kernel Requests.
        case KERNEL:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
    
        //49
        case KERNEL49:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL49), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        //50
        case KERNEL50:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL50), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
        
        //51     
        case KERNEL51:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL51), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        //52
        case KERNEL52:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL52), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;

        //53
        case KERNEL53:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL53), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
        
        //54     
        case KERNEL54:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL54), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;

        
        case KERNEL55:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL55), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case KERNEL56:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL56), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case KERNEL57:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL57), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        //
		// ...
		//
		
		case KERNEL199:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(KERNEL199), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
        default:
            //Nothing.
            break;			
    };
	//Nothing.
// Done.
done:
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
 */
int call_gui( unsigned long int_number, 
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
	
	int ret_val;    //Retorno.
	
    switch(int_number)
    { 
         
        //Vários serviços. 

        //Fast Create Window.		
        case FAST_CREATE_WINDOW:
		//case GUI:
            asm volatile( " int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(FAST_CREATE_WINDOW), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
    
        case GUI217:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(GUI217), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case GUI218:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(GUI218), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
             
        case GUI219:
            asm volatile( "int %1 \n"
		                  : "=a"(ret_val)		
		                  : "i"(GUI219), "a"(arg1), "b"(arg2), "c"(arg3), "d"(arg4) );
	                       break;
		default:
		    //Nothing.
		    break; 
    };
// Done.
done:
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
		
	//
	// Call. ( int 200, service SYSTEMCALL_BUFFER_CREATEWINDOW. )
	//
	
	//
	// @todo:  É necessário criar um fastcall que envie bastante argumentos 
	//         para o kernel e que o kernel atenda a chamada prontamente.
	//     
	//
	
	
	//
	// @todo: test. poderia enviar um ponteiro pra uma estrutura de retãngulo.
	//
	
	//struct rect_d *r;
	
	//r->x  = (unsigned long) x;
	//r->y  = (unsigned long) y;
	//r->cx = (unsigned long) width;
	//r->cy = (unsigned long) height;
	
	
	
	//suporte 47 , status
    system_call( SYSTEMCALL_CREATEWINDOW0, 
	                               (unsigned long) status, 
								   (unsigned long) clientcolor, 
								   (unsigned long) color ); 

    //suporte 48 x,y,janela mãe.
    system_call( SYSTEMCALL_CREATEWINDOW1, 
	                               (unsigned long) x, 
								   (unsigned long) y, 
								   (unsigned long) pWindow ); 

    //suporte 49, largura , altura
    system_call( SYSTEMCALL_CREATEWINDOW2, 
	                               (unsigned long) width, 
								   (unsigned long) height, 
								   (unsigned long) 0 ); 								   
	
	
	
	//Número do serviço(10), tipo , view, nome 
    Window = (void *) system_call( SYSTEMCALL_BUFFER_CREATEWINDOW, 
	                               (unsigned long) type, 
								   (unsigned long) view, 
								   (unsigned long) windowname ); 
	//Nothing.
	
	//Struct.
	if( (void*) Window == NULL ){
	    return NULL;    //Fail.
    }else{
		
		//
		// Obs: Temos as propriedades da janela criada.
		//      Talvez o endereço retornado esteja em área
		//      de memória protegida. Acessar essa estrutura pode 
		//      gerar um excessão.
        //      @todo: Cuidado com o retorno #bugbug 		
		//
		
		//...
	    goto done;
	};
	//Nothing.
done:
	return (void*) Window;    
};


/*
 * APIRegisterWindow:
 *     Register Window.
 *
 */
int APIRegisterWindow(struct window_d *window)
{
    //
    // @todo: Filtrar argumento.
    //	
	
	if( (void*) window == NULL ){
		return (int) 1;
	};		
	
    system_call( SYSTEMCALL_REGISTERWINDOW, 
	             (unsigned long) window, 
				 (unsigned long) window, 
				 (unsigned long) window);		
    return (int) 0;	
};


/*
 * APICloseWindow:
 *     Close Window. 
 */
int APICloseWindow(struct window_d *window)
{
    //
    // @todo: Filtrar argumento.
    //	
	
	if( (void*) window == NULL ){
		return (int) 1;
	};		
	
    system_call( SYSTEMCALL_CLOSEWINDOW, 
	             (unsigned long) window, 
				 (unsigned long) window, 
				 (unsigned long) window );	
    return (int) 0;	
};


/*
 * APISetFocus:
 *     Set Focus.
 */
int APISetFocus(struct window_d *window)
{
    //
    // @todo: Filtrar argumento.
    //	
	
	if( (void*) window == NULL ){
		return (int) 1;
	};		
	
    system_call( SYSTEMCALL_SETFOCUS, 
	             (unsigned long) window, 
				 (unsigned long) window, 
				 (unsigned long) window );	
    return (int) 0;	
};


/*
 * APIGetFocus:
 *     Get Focus.
 */
int APIGetFocus(){
    return (int) system_call( SYSTEMCALL_GETFOCUS, 0, 0, 0);	
};


/*
 * APIKillFocus:
 *     Kill Focus.
 */
int APIKillFocus(struct window_d *window)
{

    //
    // @todo: Filtrar argumento.
    //	
	
	if( (void*) window == NULL ){
		return (int) 1;
	};	
	
    system_call( SYSTEMCALL_KILLFOCUS, 
	             (unsigned long) window, 
				 (unsigned long) window, 
				 (unsigned long) window );	
    return (int) 0;	
};


/*
 * APISetActiveWindow:
 *     Set Active Window.
 * @todo: Esse retorno pode ser void.
 */
int APISetActiveWindow(struct window_d *window)
{
    //
    // @todo: Filtrar argumento.
    //	
	
	if( (void*) window == NULL ){
		return (int) 1;
	};
	
    system_call( SYSTEMCALL_SETACTIVEWINDOW, 
	             (unsigned long) window, 
				 (unsigned long) window, 
				 (unsigned long) window );	
    return (int) 0;	
};


/*
 * APIGetActiveWindow:
 *     Get Active Window Id.
 */
int APIGetActiveWindow(){
    return (int) system_call( SYSTEMCALL_GETACTIVEWINDOW, 0, 0, 0);	
};


/*
 * APIShowCurrentProcessInfo:
 *     Mostra informações sobre o processo atual.
 */
void APIShowCurrentProcessInfo()
{
	//
	// @todo: Essa rotina devira apenas pegar os valores via system call
	//        e imprimir os valores obtidos usando rotinas em user mode.
	//
	
	
	system_call( SYSTEMCALL_CURRENTPROCESSINFO, 0, 0, 0);
	return;
};



//*********
 
void APIresize_window(struct window_d *window, unsigned long x, unsigned long y){	
	system_call( SYSTEMCALL_RESIZEWINDOW, (unsigned long) window, x, y);
	return;
}


void APIredraw_window(struct window_d *window){
	system_call( SYSTEMCALL_REDRAWWINDOW , (unsigned long) window, (unsigned long) window, (unsigned long) window);
	return;
}


void APIreplace_window(struct window_d *window, unsigned long x, unsigned long y){
	system_call( SYSTEMCALL_REPLACEWINDOW , (unsigned long) window, x, y);
	return;	
}


void APImaximize_window(struct window_d *window){
	system_call( SYSTEMCALL_MAXIMIZEWINDOW, (unsigned long) window, (unsigned long) window, (unsigned long) window);
	return;	
}


void APIminimize_window(struct window_d *window){
	system_call( SYSTEMCALL_MINIMIZEWINDOW, (unsigned long) window, (unsigned long) window, (unsigned long) window);
	return;	
}


void *APIget_foregroung_window(){
	system_call( SYSTEMCALL_GETFOREGROUNDWINDOW, 0, 0, 0);
	return;	
}


void APIset_foregroung_window(struct window_d *window){
	system_call( SYSTEMCALL_SETFOREGROUNDWINDOW, (unsigned long) window, (unsigned long) window, (unsigned long) window);
	return;	
}


/*
 * exit:
 *     Torna zombie a thread atual.
 *     Mas o propósito é terminar sair do 
 *     programa, terminando o processo e
 *     liberar os recursos que o processo estava usando.
 */
void exit(int exit_code)
{	
    system_call( SYSTEMCALL_EXIT, (unsigned long) exit_code, 
				 (unsigned long) exit_code, (unsigned long) exit_code );
    //Nothing.
wait_forever:	
    while(1){};	
};


/*
 * kill:
 *     @todo: Poderia ser o envio de um sinal para um processo dado deu PID.  
 */
void kill(int exit_code)
{	
    return; //Não há uma chamada para isso ainda.
};


/*
 * dead_thread_collector:
 *     Aciona o coletor de threads zumbis.
 *     Procura em todos os slots por threads no estado ZOMBIE e fecha elas.
 *     @todo: Talvez essa rotina possa ser implemetada em user mode por um server,
 * ficando à cargo do kernel apenas fazer a realocação dos recursos de destruição das
 * estruturas. 
 */
void dead_thread_collector()
{	
    system_call( SYSTEMCALL_DEAD_THREAD_COLLECTOR, 
	             (unsigned long) 0, 
				 (unsigned long) 0, 
				 (unsigned long) 0 );	
done:	
    return;
};


/*
 * api_strncmp:
 *     Compara duas strings.
 *     @todo: Isso deve ser oferecido peloa libC e não pela api. 
 */
int api_strncmp(char *s1, char *s2, int len)
{
	int n = len;
	
	while(n > 0)
	{	
	    n--;
        
		if(*s1 != *s2){
            return (int) 1;
        };
		
		*s1++;
		*s2++;
	};				
			
	if (*s1 != '\0' || *s2 != '\0' ){	
	    return (int) 2;
	};
	//Nothing.		
done:
	return (int) 0;
};


/*
 * refresh_screen:
 *     Refresh Screen.
 *     Passa o conteúdo do backbuffer para o lfb.
 */
void refresh_screen(){
	system_call(SYSTEMCALL_REFRESHSCREEN, 0, 0, 0);
	return;
};


/*
 * api_refresh_screen:
 *     Refresh the LFB.
 *     Move the content of BackBuffer to LFB.
 */
void api_refresh_screen(){
	refresh_screen();
	return;
};


/*
 * apiReboot:
 *     Reboot.
 */
void apiReboot()
{
	//
	// @todo: Fazer outras chamadas para
	//        as camadas de software de mais alto nível antes
    //        de efetuar o reboot de hardware propriamente dito. 	
	//
	
    system_call(SYSTEMCALL_REBOOT, 0, 0, 0);	
};


/*
 * apiSetCursor: 
 *     Set cursor.
 */
void apiSetCursor( unsigned long x, unsigned long y){
    system_call(SYSTEMCALL_SETCURSOR, x, y, 0);	
	return;
};


/*
 * apiGetCursorX:
 *     Get cursor x. 
 */
unsigned long apiGetCursorX(){
    return (unsigned long) system_call(SYSTEMCALL_GETCURSORX, 0, 0, 0);
};


/*
 * apiGetCursorY:
 *     Get cursor y.
 */
unsigned long apiGetCursorY(){
    return (unsigned long) system_call(SYSTEMCALL_GETCURSORY, 0, 0, 0);
};


/*
 * apiGetClientAreaRect:
 *     Get client area rect.
 */
void *apiGetClientAreaRect(){
    return (void *) system_call(SYSTEMCALL_GETCLIENTAREARECT, 0, 0, 0);	
};


/*
 * apiSetClientAreaRect:
 *     Enviar uma estrutura de retângulo criada em user mode para o kernel.
 */
void apiSetClientAreaRect(struct rect_d *r){
    system_call( SYSTEMCALL_SETCLIENTAREARECT, 
	             (unsigned long) r, 
				 (unsigned long) r, 
				 (unsigned long) r );
    return;	
};


/*
 * apiCreateProcess:
 *     Create a process.
 */
void *apiCreateProcess( unsigned long process_eip, 
                        unsigned long process_priority, 
						char *name )
{
    return (void *) system_call( SYSTEMCALL_CREATEPROCESS, 
	                             process_eip, 
								 process_priority, 
								 (unsigned long) name );		
};


/*
 * apiCreateThread:
 *     Create a thread.
 */
void *apiCreateThread( unsigned long thread_eip, 
                       unsigned long thread_priority, 
					   char *name )
{
    return (void *) system_call( SYSTEMCALL_CREATETHREAD, 
	                             thread_eip, 
								 thread_priority, 
								 (unsigned long) name );		
};


//coloca no estado standby para executar pela primeira vez
void apiStartThread(void *Thread)
{

    system_call( SYSTEMCALL_STARTTHREAD, 
	             (unsigned long) Thread, 
				 (unsigned long) Thread, 
				 (unsigned long) Thread );	
	return;
}

/*
 * apiFOpen:
 *     Carrega na memória um arquivo.
 *     Usa um serviço do kernel para carregar um arquivo na memória.
 *     Obs: Devemos pasasr um endereço válido, previamente alocado. 
 */
void *apiFOpen(const char *filename, const char *mode)
{	
	return (void*) system_call( SYSTEMCALL_READ_FILE, 
	                            (unsigned long) filename, 
								(unsigned long) mode, 
								0 );
};


//Operação down em um semáforo indicado no argumento.
void apiDown(struct semaphore_d *s)
{
	int Status = 1;    //fail.
	
	if( (void*) s == NULL  )
	{
	    //Semáforo inválido, 
        //Bloquear a thread, não adianta fazer a system call.
        //@todo: Chamar rotina que bloqueia a thread.
		while(1){}		
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
void apiUp(struct semaphore_d *s)
{
	int Status = 1; //fail.
	
	if( (void*) s == NULL  )
	{
	    //Semáforo inválido, 
        //Bloquear a thread, não adianta fazer a system call.
        //@todo: Chamar rotina que bloqueia a thread.
		while(1){}		
	};

    //0 = deu certo, podemos asir da sessão crítica.
    //1 = algo deu errado, não conseguimos sair da sessão crítica.	
	
tryAgain:	

	Status = (int) system_call( SYSTEMCALL_SEMAPHORE_UP, 
	                            (unsigned long) s, 
								(unsigned long) s, 
								(unsigned long) s );	

	//Ok , podemos sair sa sessão crítica.
	if(Status == 0){
		return;
	};

	//Deu errado a nossa tentativa d sair da sessão crítica.
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




//P (Proberen) testar.
void enterCriticalSection()
{
	int S;
	
	while(1)
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
    system_call( SYSTEMCALL_CLOSE_KERNELSEMAPHORE, 0, 0, 0);	
	return;
};

//V (Verhogen)incrementar.
void exitCriticalSection()
{
	//Hora de sair. Mudo para 1 para que outro possa entrar.
    system_call( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0);
    return;	
};

void initializeCriticalSection()
{
	//Inicializa em 1 o semáforo do kernel para que 
	//o primeiro possa usar.
	system_call( SYSTEMCALL_OPEN_KERNELSEMAPHORE, 0, 0, 0);
    return;
};

void apiBeginPaint(){
	enterCriticalSection();
	return;
}

void apiEndPaint(){
	exitCriticalSection();
	return;
}


//imprime um caractere usando o cursor do sistema.
void apiPutChar( int c )
{
	system_call( SYSTEMCALL_SYS_PUTCHAR, c, c, c);
    return;	
}

//Get process ID.
/*
int getpid(){
	return (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0);
}
*/



/*
 ***********************************************
 * apiDefDialog:
 *     Procedimento de janela adiado. 
 *     Usado pelos aplicativos ao fim dos seus procedimentos de janela.
 */
unsigned long 
apiDefDialog( struct window_d *window, 
              int msg, 
			  unsigned long long1, 
			  unsigned long long2 )
{
	//@todo:
	//Função ainda não implementada.
	return (unsigned long) 0;
};


//Obtem informações sobre dimensões e posicionamentos.
unsigned long apiGetSystemMetrics( int index ){
    return (unsigned long) system_call( SYSTEMCALL_GETSYSTEMMETRICS, 
	                                    (unsigned long) index, 
										(unsigned long) index, 
										(unsigned long) index );
};



void api_set_current_keyboard_responder( int i ){
    system_call( SYSTEMCALL_SET_CURRENT_KEYBOARD_RESPONDER, 
	             (unsigned long) i, 
				 (unsigned long) i, 
				 (unsigned long) i );
};

int api_get_current_keyboard_responder(){
    return (unsigned long) system_call( SYSTEMCALL_GET_CURRENT_KEYBOARD_RESPONDER, 
	                                    (unsigned long) 0, 
										(unsigned long) 0, 
										(unsigned long) 0 );
};


void api_set_current_mouse_responder( int i ){
    system_call( SYSTEMCALL_SET_CURRENT_MOUSE_RESPONDER, 
	             (unsigned long) i, 
	             (unsigned long) i, 
				 (unsigned long) i );	
};

int api_get_current_mouse_responder()
{
    return (unsigned long) system_call( SYSTEMCALL_GET_CURRENT_MOUSE_RESPONDER, 
	                                    (unsigned long) 0, 
										(unsigned long) 0, 
										(unsigned long) 0 );	
};



void api_set_window_with_text_input( struct window_d *window )
{
	if( (void*) window == NULL ) {
		return;
	}
	
	if( window->used != 1 || window->magic != 1234 ){
		return;
	}
	
    system_call( SYSTEMCALL_SET_WINDOW_WITH_TEXT_INPUT, 
	             (unsigned long) window, 
	             (unsigned long) window, 
				 (unsigned long) window );
}


int api_get_window_with_text_input()
{
    return (int) system_call( SYSTEMCALL_GET_WINDOW_WITH_TEXT_INPUT, 
	                          (unsigned long) 0, 
				  			  (unsigned long) 0, 
							  (unsigned long) 0 );	
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


//
// End.
//

