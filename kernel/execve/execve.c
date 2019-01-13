/*
 * Gramado Executive - The main file for the Executive module in the 
 * kernel base. 
 * (c) Copyright 2015-2016 Fred Nora.
 *
 * File: execve\execve.c 
 * 
 */
 
 
#include <kernel.h>
//#include "eidata.h"  //Executive Internal Data.

//unsigned char  EcecutiveName[] = "EXECUTIVE LAYER";


/*
 *****************************************************************
 * executive_gramado_core_init_execve:
 *
 *     Executa um programa no processo INIT dentro do ambiente Gramado Core. 
 *     Ou seja, na thread primária do processo INIT.
 *     Ou seja, a aplicação tem que ser compilada no mesmo endereço do INIT.
 *     #obs: Isso funcionou.
 *
 * #bugbug:
 * E se o aplicativo fechar a thread, como usaremos a thread do processo init? 
 * Talvez a solução para isso seria criar outra. 
 * Nos casos em que o aplicativo chama o exit, não está retornando para o 
 * shell. O fato é que quando chama o exit o estado da thread muda.
 *
 * IN:
 * serviço, file name, arg, env.
 */
 
int 
executive_gramado_core_init_execve ( int i,              
                                     const char *arg1,    //name
                                     const char *arg2,    //arg
                                     const char *arg3 )   //env
{
	int Status = 1;  //fail.
	
	//??
	//Esse é o primeiro argumento.
	int Plane = 0;
	
	char *s;
	struct thread_d *Thread;

	
	//Usados gerenciamento de arquivo.
	size_t l; //lenght.
 	char bin_string[] = ".bin";	
	//char xxx_string[] = ".xxx";	
	
	//#debug
	//printf("0=%s ",&argv[0]);
    //printf("1=%s ",&argv[1]);
    

	// #importante
	// Testando carregar um programa para rodar no processo INIT, 
	// usando a thread primária do processo !
	// É o mesmo que consierar que o processo INIT já seja o clone 
	// de outro válido.
		
    //??		
	//array de ponteiros.
	unsigned long *p = (unsigned long *) arg2;
    
	// #importante:
	// Memória compartilhada entre o kernel e o aplicativo.
	// O aplicativo vai ler esse trem 
	unsigned char *shared_memory = (unsigned char *) (0xC0800000 -0x100);
	
    // #IMPORTANTE:
    // PRECISAMOS ENVIAR A MENSAGEM SOMENTE DEPOIS QUE O NOVO PROGRAMA FOR 
	// COLOCADO NA MEMÓRIA, SENÃO AO COLOCAR O PROGRAMA NA MEMÓRIA A MENSAGEM 
    // SERÁ SOBRESCRITA.	
    // #TODO: CRIAR UM MECANISMO DE TROCA DE MENSAGENS MAIS EFICIENTE,
	// BASEADO NESSE.
	
    //=================================================
    //  ## CMD ##
    //	
		
	//#importante.
	//antes de tudo vamos testar o comando.
	//se ele não existir então nem vamos mexer na estrutura da trhead.
	//se não mexermos na estrutura da thread ele continuará presa no while 
	//do exit da libc.
	
	
		//
		// ## Load file ##
		//
		
		// #bugbug
		// # arg1=name ##
		
		// Devemos ver se a string não passa dos limites.
		
		// Como essa rotina é para executar um arquivo .bin,
		// caso não exista uma extensão .bin e o nome seja menor que 8, 
		// podemos adicionar a extensão .bin.
		
		l = (size_t) strlen ( (char *) arg1 );
		
		if ( l > 11 )
		{
		    // #fail 
			printf("executive_gramado_core_init_execve: File name fail\n");	
			//Obs: Não sairemos da função pois isso é um teste ainda.
			//goto fail;
		
		} else {
			
			
			//se não existe um ponto entre os oito primeiros chars,
            //então colocamos a extensão .bin logo após o nome passado.
            //e ele é pelo menos menor que 11, mas deveria ser menor que oito.			
			
			if ( arg1[0] != '.' && 
			     arg1[1] != '.' && 
                 arg1[2] != '.' && 
                 arg1[3] != '.' && 
                 arg1[4] != '.' && 
                 arg1[5] != '.' && 
                 arg1[6] != '.' && 
                 arg1[7] != '.' )
				{
                    //#bugbug: Já pegamos esse valor.					
				    //l = (size_t) strlen ( (char *) arg1);
                    
					if ( l > 8 )
					{
						printf("executive_gramado_core_init_execve: File without ext is too long\n");
					    //Obs: Não sairemos da função pois isso é um teste ainda.
					    //goto fail;
					}
					
		            strcat ( (char *) arg1, (const char *) bin_string );
			    };
				
			// #obs:	
			// Se estamos aqui, isso significa existe um ponto 
            // nos primeiros oito bytes.
            // Ainda não sabemos se todo o nome do arquivo está certo,
            // mas ja sabemos que não precisamos incluir uma extenção.			
		};
		
	
	read_fntos ( (char *) arg1 );
		
    Status = (int) fsLoadFile ( VOLUME1_ROOTDIR_ADDRESS, 
	                   (unsigned char *) arg1, 
	                   (unsigned long) 0x00400000 );
					
    //Status = (int) fsLoadFile ( (unsigned char *) arg1, 
	//                (unsigned long) 0x00400000 );					

	// Se não conseguimos carregar o arquivo, devemos abortar.
	if ( Status == 1 )
	{
			
		//printf("executive_gramado_core_init_execve: Status\n");
		printf("executive_gramado_core_init_execve: ERROR. Can't load file\n");
		goto fail;
	};	
	
	//Ok
	//O comando existe e o arquivo foi carregado.
	//mas precisamos saber se a assinatura de PE é válida.
				
			// #bugbug: 
			// Não deve existir suporte a PE dentro do kernel.
			// PE é proprietário.
			
	
	Status = (int) fsCheckELFFile ( (unsigned long) 0x00400000 );
	if ( Status == 0 )
	{
	    printf("ok, its a valid ELF file\n");
		goto format_ok;
		
	}		
	if ( Status == 1 )
	{
		//aí ferrou ... não podemos continuar com um arquivo corrompido.	
        //como carregamos novo arquivo na memória então a antiga thread vai falaher.		
		printf("executive_gramado_core_init_execve: ERROR. It's not a valid ELF file\n");
		die();
        goto fail;
    }
	
	
	
	Status = (int) fsCheckPEFile ( (unsigned long) 0x00400000 );
			
	if ( Status == 1 )
	{
		//aí ferrou ... não podemos continuar com um arquivo corrompido.	
        //como carregamos novo arquivo na memória então a antiga thread vai falaher.		
		printf("executive_gramado_core_init_execve: ERROR. It's not a valid PE file\n");
		//die();
        //goto fail;
    }	

	
format_ok:	
	
	//#debug
	//tentando receber uma linha de ocmando inteira.
	//printf("\nexecutive_gramado_core_init_execve: testing..\n\n");
	
	//# ISSO DEU CERTO #
	//testando se o shell transferiu toda alinha de comandos para a memória compartilhada.
	//printf(">>>cmdline2={%s}\n", shared_memory);
	
	
	//#IMPORTANTE:
	//se a linha de comandos está na memória compartilhada 
	//e o nome do arquivo programa foi passado via endereço 
	//então temos tudo o que é preciso 
	//para enviarmos a linha de comandos para o aplicativo.
	
	//...
	
	
	//## teste
	//
	//if( ! strcmp( (char*)argv[0], "-f" ) ) 
	//if( strncmp( (char*) &argv[1], "-f", 2 ) == 0 )
	//{
	//	printf("executive_gramado_core_init_execve: FOREGROUND\n");
    //    Plane = FOREGROUND;
    //}else{
	//	printf("executive_gramado_core_init_execve: BACKGROUND\n");
	//	Plane = BACKGROUND;
	//};
	
	//fail.
	//if( (const char *) filename == NULL ){
	//	return 1;
	//}
	
	//
	// ENVIANDO A MENSAGEM
	//
	
	//unsigned longs.
	//for( i=0; i<512; i++ )
	//{
        
		//Não queremos transferir o primeiro ponteiro 
		//pois ele é o nome do programa e não um argumento.
	//	shared_p[i] = p[i+1];
		
		//pipe[i] = src[i];
		//shared_memory[i] = src[i];
	//};
	
	//os ponteiros estão na memória compartilhada, 
	//mas as strings estão onde ??
	//provavelmente as strings ainda esteja na memória 
	//do shell, e o aplicativo não pode ler as strings que estão 
	//na memória do shell.
	//obs: o shell poderia copiar toda a linha de comando para 
	//a memória compartilhada.
	//printf(">>>shared_p0={%s}\n"     ,shared_p[0]);
	//printf(">>>shared_p1={%s}\n"     ,shared_p[1]);
	//printf(">>>shared_p2={%s}\n\n"   ,shared_p[2]);
	//printf(">>>shared_p3={%s}\n\n"   ,shared_p[3]);	
	
 
	//#debug
	//ok. isso funcionou.
	//printf("Showpipe={%s}\n",pipe);
	//printf("Showsharedmemory={%s}\n",shared_memory);	 
	
	
	// Pegar o ponteiro da thread primária do processo INIT.
    // o ponteiro vai continuar existindo mesmo que o deadthread collector 
	// tenha destruido a estrutura depois de um app mudar o estado para zombie 
	// por causa de um exit.
	//Então é melhor criarmos uma thread nova. Mas se fizermos isso
	//sem antes o deadthread collector ter destruido a estrutua e liberado a memória 
	//então a antiga estrutura de thread ficará sem porteiro e poderemos desalocar a memória 
	//usanda, ou pior, se não mudarmos o status ele pode querer destruir a que estamos criando
	//então só criaremos se o ponteiro for NULL, significando que o deadthread collector 
	//ja destruiu a estrutura e aproveitou a memória se conseguiu.
	
	//#importante:
	//Podemos eswperar que essa thread esteja no estado ZOMBIE.
	//Pois um aplicativo pode ter efetuado um exit.
	//se ela estiver no estado ZOMBIE
	
	//#importante
	//esperamos que tenha limpado IdleThread antes de usarmos o ponteiro.
	//isso é trabalho do exit e do deadthread collector.
	
	Thread = (struct thread_d *) IdleThread; 			
	
	if ( (void *) Thread == NULL )
	{
		//3imporante:
		//Vamos tornar isso um erro fatal por enquanto, para podermos refletir sobre 
		//esse assunto;
		printf("executive_gramado_core_init_execve: Thread Fail \n");
		die ();
		//goto fail;
		
	} else {
		
		//#importante:
		//Checar a flag de reaproveitamento.
		//Se a flag do reaproveitamento falhar então o exit no kernel
		//não acionou ela para a threa InitThread, que é nossa única reaproveitável.
		//por enquanto.
		//if ( Thread->used != 1 || Thread->magic != 1234 )
		//{
		//	printf("executive_gramado_core_init_execve: Validation fail \n");
		//	die();
			//goto fail;
		//}
		
 
        //
		// ## state ##
		//
		
		//Vamos seguir a sequência de nacimento de um thread.
		//e cancelaremos caso não for possível carregar o arquivo do 
		//programa.
		//INITIALIZED>STANDBY>READY>RUNNING ...
		
		Thread->state = INITIALIZED;
		
		// Significa que o contexto nunca foi salvo, pois o spawn 
		// não funciona em thread com o contexto salvo.
		
		Thread->saved = 0; 
		
		Thread->plane = Plane;
		
	    //Context.
	    //@todo: Isso deve ser uma estrutura de contexto.
		
	    Thread->ss  = 0x23;                          //RING 3.
	    Thread->esp = (unsigned long) 0x0044FFF0;    //idleStack; (*** RING 3)
	    Thread->eflags = 0x3200;  //0x3202, pois o bit 1 é reservado e está sempre ligado.
	    Thread->cs = 0x1B;                                
	    Thread->eip = (unsigned long) 0x00401000;   //entry point  	                                               
	    Thread->ds = 0x23; 
	    Thread->es = 0x23; 
	    Thread->fs = 0x23; 
	    Thread->gs = 0x23; 
	    Thread->eax = 0;
	    Thread->ebx = 0;
	    Thread->ecx = 0;
	    Thread->edx = 0;
	    Thread->esi = 0;
	    Thread->edi = 0;
	    Thread->ebp = 0;
		
		Thread->Next = NULL;
					
		queue_insert_data ( queue, 
		    (unsigned long) Thread, QUEUE_INITIALIZED );
            
			
		// #importante:
		// * MOVEMENT 1 ( Initialized ---> Standby ).
		SelectForExecution (Thread);    
            
		goto done; 
         
        //fail	
        //printf("executive_gramado_core_init_execve:  File support fail\n");
	};
	
	//fail	
fail:
    printf("executive_gramado_core_init_execve: #fail\n");
	//refresh_screen();
done:

    //#debug
	//printf(">>>shared_p0={%s}\n"     ,shared_p[0]);
	//printf(">>>shared_p1={%s}\n"     ,shared_p[1]);
	//printf(">>>shared_p2={%s}\n\n"   ,shared_p[2]);
	//printf(">>>shared_p3={%s}\n\n"   ,shared_p[3]);	
	//refresh_screen();
	//while(1){
	//	asm("hlt");
	//}
	//	
    
	
	//#debug
	//printf("done\n");	
	
	//
	// #Obs: 
	// +Não devemos emitir mensagens no caso de acerto.
	// +refresh_screen só no caso de erro.
	//
	
	//#bugbug
	//#obs: Estamos usando isso só por enquanto para debug.
	refresh_screen();
	
	return (int) Status;	
};



//=================================================
//execve para .exe 

/*
 *****************************************************************
 * executive_gramado_core_init_execve:
 *
 *     Executa um programa no processo INIT dentro do ambiente Gramado Core. 
 *     Ou seja, na thread primária do processo INIT.
 *     Ou seja, a aplicação tem que ser compilada no mesmo endereço do INIT.
 *     #obs: Isso funcionou.
 *
 * IN:
 * serviço, file name, arg, env.
 */
 
int 
executive_gramado_core_init_execve_exe ( int i,              
                                         const char *arg1,   //name
                                         const char *arg2,    //arg
                                         const char *arg3 )   //env
{
	int Status = 1;  //fail.
	
	//??
	//Esse é o primeiro argumento.
	int Plane = 0;
	
	char *s;
	struct thread_d *Thread;

	
	//Usados gerenciamento de arquivo.
	size_t l; //lenght.
 	//char bin_string[] = ".bin";	
	//char xxx_string[] = ".xxx";	
	char exe_string[] = ".exe";
	
	//#debug
	//printf("0=%s ",&argv[0]);
    //printf("1=%s ",&argv[1]);
    

	// #importante
	// Testando carregar um programa para rodar no processo INIT, 
	// usando a thread primária do processo !
	// É o mesmo que consierar que o processo INIT já seja o clone 
	// de outro válido.
		
    //??		
	//array de ponteiros.
	unsigned long *p = (unsigned long *) arg2;
    
	// #importante:
	// Memória compartilhada entre o kernel e o aplicativo.
	// O aplicativo vai ler esse trem 
	unsigned char *shared_memory = (unsigned char *) (0xC0800000 -0x100);
	
    // #IMPORTANTE:
    // PRECISAMOS ENVIAR A MENSAGEM SOMENTE DEPOIS QUE O NOVO PROGRAMA FOR 
	// COLOCADO NA MEMÓRIA, SENÃO AO COLOCAR O PROGRAMA NA MEMÓRIA A MENSAGEM 
    // SERÁ SOBRESCRITA.	
    // #TODO: CRIAR UM MECANISMO DE TROCA DE MENSAGENS MAIS EFICIENTE,
	// BASEADO NESSE.
	
	//#debug
	//tentando receber uma linha de ocmando inteira.
	//printf("\nexecutive_gramado_core_init_execve: testing..\n\n");
	
	//# ISSO DEU CERTO #
	//testando se o shell transferiu toda alinha de comandos para a memória compartilhada.
	//printf(">>>cmdline2={%s}\n", shared_memory);
	
	
	//#IMPORTANTE:
	//se a linha de comandos está na memória compartilhada 
	//e o nome do arquivo programa foi passado via endereço 
	//então temos tudo o que é preciso 
	//para enviarmos a linha de comandos para o aplicativo.
	
	//...
	
	
	//## teste
	//
	//if( ! strcmp( (char*)argv[0], "-f" ) ) 
	//if( strncmp( (char*) &argv[1], "-f", 2 ) == 0 )
	//{
	//	printf("executive_gramado_core_init_execve: FOREGROUND\n");
    //    Plane = FOREGROUND;
    //}else{
	//	printf("executive_gramado_core_init_execve: BACKGROUND\n");
	//	Plane = BACKGROUND;
	//};
	
	//fail.
	//if( (const char *) filename == NULL ){
	//	return 1;
	//}
	
	//
	// ENVIANDO A MENSAGEM
	//
	
	//unsigned longs.
	//for( i=0; i<512; i++ )
	//{
        
		//Não queremos transferir o primeiro ponteiro 
		//pois ele é o nome do programa e não um argumento.
	//	shared_p[i] = p[i+1];
		
		//pipe[i] = src[i];
		//shared_memory[i] = src[i];
	//};
	
	//os ponteiros estão na memória compartilhada, 
	//mas as strings estão onde ??
	//provavelmente as strings ainda esteja na memória 
	//do shell, e o aplicativo não pode ler as strings que estão 
	//na memória do shell.
	//obs: o shell poderia copiar toda a linha de comando para 
	//a memória compartilhada.
	//printf(">>>shared_p0={%s}\n"     ,shared_p[0]);
	//printf(">>>shared_p1={%s}\n"     ,shared_p[1]);
	//printf(">>>shared_p2={%s}\n\n"   ,shared_p[2]);
	//printf(">>>shared_p3={%s}\n\n"   ,shared_p[3]);	
	
 
	//#debug
	//ok. isso funcionou.
	//printf("Showpipe={%s}\n",pipe);
	//printf("Showsharedmemory={%s}\n",shared_memory);	 
	
	
	// Pegar o ponteiro da thread primária do processo INIT.
	// #bugbug: Perceba que isso é uma constante.
	// ?? usar uma variável, por exemplo:
	// init_thread ou dolly thread ou IdleThread->tid;
	
	//Thread = (struct thread_d *) threadList[0];
	
	Thread = (struct thread_d *) IdleThread; 
	
	if ( (void *) Thread == NULL )
	{
		//#fail
		printf("executive_gramado_core_init_execve: Thread Fail \n");
		goto fail;
		
	} else {
		
		if ( Thread->used != 1 || Thread->magic != 1234 )
		{
			printf("executive_gramado_core_init_execve: Validation fail \n");
			goto fail;
		}
		
		// Significa que o contexto nunca foi salvo, pois o spawn 
		// não funciona em thread com o contexto salvo.
		
		Thread->saved = 0; 
		
		Thread->plane = Plane;
		
	    //Context.
	    //@todo: Isso deve ser uma estrutura de contexto.
		
	    Thread->ss  = 0x23;                          //RING 3.
	    Thread->esp = (unsigned long) 0x0044FFF0;    //idleStack; (*** RING 3)
	    Thread->eflags = 0x3200;  //0x3202, pois o bit 1 é reservado e está sempre ligado.
	    Thread->cs = 0x1B;                                
	    
		//#importante
		//eip, entrypoint 
		
		Thread->eip = (unsigned long) 0x00401000;   	
        //Thread->eip = (unsigned long) 0x00400400;   			
	    
		Thread->ds = 0x23; 
	    Thread->es = 0x23; 
	    Thread->fs = 0x23; 
	    Thread->gs = 0x23; 
	    Thread->eax = 0;
	    Thread->ebx = 0;
	    Thread->ecx = 0;
	    Thread->edx = 0;
	    Thread->esi = 0;
	    Thread->edi = 0;
	    Thread->ebp = 0;
		
		Thread->Next = NULL;
		
		//
		// ## Load file ##
		//
		
		// #bugbug
		// # arg1=name ##
		
		// Devemos ver se a string não passa dos limites.
		
		// Como essa rotina é para executar um arquivo .bin,
		// caso não exista uma extensão .bin e o nome seja menor que 8, 
		// podemos adicionar a extensão .bin.
		
		l = (size_t) strlen ( (char *) arg1 );
		
		if ( l > 11 )
		{
		    // #fail 
			printf("executive_gramado_core_init_execve: File name fail\n");	
			//Obs: Não sairemos da função pois isso é um teste ainda.
			//goto fail;
		
		} else {
			
			
			//se não existe um ponto entre os oito primeiros chars,
            //então colocamos a extensão .bin logo após o nome passado.
            //e ele é pelo menos menor que 11, mas deveria ser menor que oito.			
			
			if ( arg1[0] != '.' && 
			     arg1[1] != '.' && 
                 arg1[2] != '.' && 
                 arg1[3] != '.' && 
                 arg1[4] != '.' && 
                 arg1[5] != '.' && 
                 arg1[6] != '.' && 
                 arg1[7] != '.' )
				{
                    //#bugbug: Já pegamos esse valor.					
				    //l = (size_t) strlen ( (char *) arg1);
                    
					if ( l > 8 )
					{
						printf("executive_gramado_core_init_execve: File without ext is too long\n");
					    //Obs: Não sairemos da função pois isso é um teste ainda.
					    //goto fail;
					}
					
		            //strcat ( (char *) arg1, (const char *) bin_string );
					strcat ( (char *) arg1, (const char *) exe_string );
			    };
				
			// #obs:	
			// Se estamos aqui, isso significa existe um ponto 
            // nos primeiros oito bytes.
            // Ainda não sabemos se todo o nome do arquivo está certo,
            // mas ja sabemos que não precisamos incluir uma extenção.			
		};
		
		
		// #bugbug
		// #importante: 
		// +Precisamos do ponteiro válido para filename.
		// +Não podemos auterá-lo e depois usá-lo.
		
		// #importante: 
		// Isso precisa ser nesse momento e não antes, pois pode corromper o 
		// espaço destinado aos argumentos dentro do vetor ao acrescentar 
		// zeros.
		
		// Isso está em fs/read.c
	    // fsLoadFile usa o formado "FILE    BIN".
        // Vamos transformar 'file.txt' em "FILE    BIN". 		
		
		read_fntos ( (char *) arg1 );
		
		//Status = (int) fsLoadFile ( (unsigned char *) arg1,  (unsigned long) 0x00400C00 );  
		 
        Status = (int) fsLoadFile ( VOLUME1_ROOTDIR_ADDRESS, 
		                   (unsigned char *) arg1,  
						   (unsigned long) 0x00400C00 );
		
		// Se não conseguimos carregar o arquivo, devemos abortar.
		if ( Status == 1 )
		{
			// @todo:
			// Configurar estrutura.
			
			//printf("executive_gramado_core_init_execve: Status\n");
			printf("executive_gramado_core_init_execve: ERROR. Can't load file\n");
			goto fail;
		};
		
		// Se conseguimos carregar o arquivo, devemos checar a validade 
		// do arquivo na memória.
		if ( Status == 0 )
		{
			// #bugbug: 
			// Não deve existir suporte a PE dentro do kernel.
			// PE é proprietário.
			
			//#bugbug 
			//teríazmos que checar por (MZ) para .exe
			
			//Status = (int) fsCheckPEFile ( (unsigned long) 0x00400000 );
			//
			//if ( Status == 1 ){
			//	printf("executive_gramado_core_init_execve: ERROR. It's not a valid PE file\n");
			//	//goto fail;
			//}
			
			// ??
			// Colocar a trhead na fila de inicializadas.
			
		    queue_insert_data ( queue, 
			    (unsigned long) Thread, QUEUE_INITIALIZED );
            
			
			// #importante:
			// * MOVEMENT 1 ( Initialized ---> Standby ).
			SelectForExecution (Thread);    
            
			goto done; 
        };	
         
        //fail	
        printf("executive_gramado_core_init_execve:  File support fail\n");
	};
	
	//fail	
fail:
    printf("executive_gramado_core_init_execve: #fail\n");
	//refresh_screen();
done:

    //#debug
	//printf(">>>shared_p0={%s}\n"     ,shared_p[0]);
	//printf(">>>shared_p1={%s}\n"     ,shared_p[1]);
	//printf(">>>shared_p2={%s}\n\n"   ,shared_p[2]);
	//printf(">>>shared_p3={%s}\n\n"   ,shared_p[3]);	
	//refresh_screen();
	//while(1){
	//	asm("hlt");
	//}
	//	
    
	
	//#debug
	//printf("done\n");	
	
	//
	// #Obs: 
	// +Não devemos emitir mensagens no caso de acerto.
	// +refresh_screen só no caso de erro.
	//
	
	//#bugbug
	//#obs: Estamos usando isso só por enquanto para debug.
	refresh_screen();
	
	return (int) Status;	
};


/* sys_showkernelinfo:
 *     Show kernel info. */

void sys_showkernelinfo (){
	
	KiInformation ();
};


/*
 ************************************************
 * init_executive:
 *
 *     Initialize the kernel executive.
 *     Archtecture (independent) inicialization. 
 */
 
int init_executive (){
	
    int Status = 0;
	
	//#debug
#ifdef KERNEL_VERBOSE
	printf("EXECUTIVE:\n");
#endif	
	
	// PCI - Pega informações da PCI.
	// CLOCK - Pega informações de Hora e Data.	
	
	init_pci();
    init_clock();
	//...
	
	diskATADialog( 1, FORCEPIO, FORCEPIO );
	
	// ??
	// configura a tabela do kernel de funções exportadas
	// e tabela de ponteiros para tabelas dos outros programas em kernel mode.
    // Status = (int) executive_config_exported_functions();

	//Continua ...
	
//Done:
    
	//@todo: Checar a validade de 'Initialization' ??

	//#debug
	//printf("Done!\n");
	
    Initialization.executive = 1;	
	
	return (int) Status;
};


//
// End.
//

