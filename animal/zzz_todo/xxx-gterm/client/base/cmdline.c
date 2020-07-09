// it's an emergency shell for noraterm
// its used to setup the terminal in the development step.


#include "noraterm.h" 


void ShowPID (){
	
	printf ("Current PID %d\n", 
	    (int) system_call ( SYSTEMCALL_GETPID, 0, 0, 0) );
}

void ShowPPID (){
	
	printf ("Current PID %d\n", 
	    (int) system_call( SYSTEMCALL_GETPPID, 0, 0, 0) );
}


void ShowUID (){
	
	printf ("Current UID %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTUSERID, 0, 0, 0) );
}


void ShowGID (){
	
	printf ("Current GID %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTGROUPID, 0, 0, 0) );
}


void ShowUserSessionID (){
	
	printf("Current user session %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTUSERSESSION, 0, 0, 0) );
}


void ShowWindowStationID (){
	
	printf("Current window station %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTWINDOWSTATION, 0, 0, 0) );
}


void ShowDesktopID (){
	
	printf("Current desktop %d\n", 
	    (int) system_call( SYSTEMCALL_GETCURRENTDESKTOP, 0, 0, 0) );
}



void shellShowProcessHeapPointer (){
	
	int id = (int) system_call( SYSTEMCALL_GETPID, 0, 0, 0); 
	
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
	                                                id, 0, 0 );
	
	printf("Current Process heap pointer address %x\n", 
	    (unsigned long) heap_pointer );
}


void shellShowKernelHeapPointer (){
	
	int id = 0;  //Id do processo kernel. 
	unsigned long heap_pointer = (unsigned long) system_call( SYSTEMCALL_GETPROCESSHEAPPOINTER, 
	                                                id, 0, 0 );
	
	printf("Current Process heap pointer address %x\n", 
	    (unsigned long) heap_pointer );
}


//mostra informações sobre o disco atual.
void shellShowDiskInfo (){
	
	//@todo: atualizar api.h
	system_call ( 251, 0, 0, 0 );
}


//mostra informações sobre o volume atual.
void shellShowVolumeInfo (){
	
	//@todo: atualizar api.h
	system_call ( 252, 0, 0, 0 );
}


//mostrar informações gerais sobre a memória.
void shellShowMemoryInfo (){
	
	system_call ( SYSTEMCALL_MEMORYINFO, 0, 0, 0 );
}


//mostrar informações gerais sobre a memória.
void shellShowPCIInfo (){
	
    system_call ( SYSTEMCALL_SHOWPCIINFO, 0, 0, 0 );	
}


//mostrar informações gerais sobre a memória.
void shellShowKernelInfo (){
	
	system_call ( SYSTEMCALL_SHOWKERNELINFO, 0, 0, 0 );
}



/*
 **********************************************************
 * shellExecuteThisScript:
 *     Aqui temos que carregar o arquivo de script indicado 
 * nos argumentos.
 * #importante:
 * Apenas colocaremos o arquivo em stdin, que é o pormpt[]
 * e retornaremos ao incio da função que compara, para 
 * comparar agora o que estava escrito no arquivo de script.
 * 
 * 	#todo:
 *	Essa função deve chamar o interpretador de script
 *
 * IN: Nome do arquivo.
 */
 
int shellExecuteThisScript ( char *script_name ){
	
    
 	//#todo:
	//Essa função deve chamar o interpretador de script	
	
	FILE *script_file;	
	int i;
	
	// Aqui temos que carregar o arquivo de script indicado 
	// nos argumentos.
	
	printf("shellExecuteThisScript:\n");	
	printf("Initializing script ...\n");
    printf("CurrentFile={%s}\n",script_name);
	
	
	// #ok 
    // Carregaremos o arquivo com o nome passado por argumento.	
	
    script_file = fopen (script_name,"rw");
	
	if ( (void *) script_file == NULL )
	{	
		printf ("shellExecuteThisScript: Can't open script file!\n");
		die("*");
	};
	
	//#Ok
	//atualizando a linha de comandos no prompt[], stdin.
	
	//#obs 
	//Talvez não precise copiar o conteúdo, e sim apenas 
    //mudar os ponteiros.
    
    //#todo 	
	//Fazer isso ao invés de copiar.
	//stdin = script_file;
	
	for ( i=0; i< 128; i++ )
	{	
		stdin->_base[i] = script_file->_base[i];
	}
	
	
	//
	// ## parser ##
	//
	
	//#todo
	//Chamaremos o parser, que num loop chamará o lexer yylex()
	
	//parser();
	
	
	//EOF_Reached = EOF;

    return 0;		
}



/*
 **************************************
 * absolute_pathname:
 * Retorna 1 nos seguintes casos:
 *
 * >/
 * >.
 * >./
 * >..
 * >../
 *
 * Credits: bash 1.05
 */
	
	// #importante:
	// Vamos checar se o pathname é absoluto ou relativo.
	// +Se tiver barra, significa que o pathname é absoluto e 
	// começa no diretório raiz do volume do sistema. root:/volume1/
	// +Se começar por root:/ também é absoluto.
	// +Pathname relativo é somente aquele que é apenas um nome 
	// de arquivo dentro do diretório atual. Como: 'name' ou name1/name2,
	// sem barra ou ponto.
	// $/ é o diretório raiz do volume do sistema.
	// $v/ é o diretório raiz do vfs.
	
int absolute_pathname ( char *string ){
	
	// Checar nulidade.
    if( !string || !strlen(string) )
        return (0);

	//Começa por barra.
	//Então essa barra significa o diretório raiz do 
	//volume do sistema. Ex: root:/volume1/
    if( *string == '/' )
        return (1);

	
	// .
    // É absoluto, pois estamos determinando o diretório.
	// Se for ponto, avança em seguida.
	if( *string++ == '.' )
    {
        // ./
		// Significa que se trata do diretório atual
		if( (!*string) || *string == '/' )
	        return (1);

        // ..
		// ../
		// Significa que se trata do diretório pai.
		// Se for ponto, avança em seguida.
		// se for barra ou nada é absoluto.
		//obs: o nada nesse caso significa que foi digitado apenas '..'
		if( *string++ == '.' )
	        if( !*string || *string == '/' )  
	            return (1);
		
		// ?? Continua ...
		// Se estamos aqui, significa que é um ponto que não é seguido 
		// de outro ponto ou barra.
		//?? deveríamos falhar com a opção 2. 
		return (2);
    }
	
	// root:/
	if ( *string == 'r' )
	{
	    if ( string[0] == 'r' &&
             string[1] == 'o' &&
             string[2] == 'o' &&
             string[3] == 't' &&
             string[4] == ':' &&
             string[5] == '/' )
	    {
		    return (1);		 
		}

        return (2);		
	};
	
	// #teste:
	// invendando esquema.
	// Volume do sistema.
	// O número do volume do sistema é um padrão.
	if ( *string == '$' )
	{
		
	    // root:/volume1/ = $/ (volume do sistema)	    
		if ( string[0] == '$' && 		
		     string[1] == '/' )
	    {
		    return (1);		 
		}
		
	    // root:/volume1/ = $v/ (vfs)
		if ( string[0] == '$' &&
             string[1] == 'v' && 		
		     string[2] == '/' )
	    {
		    return (1);		 
		}

        return (2);		
	};	
	
//fail:
//Não é absoluto.
	
    return 0;
}



//inicializaremos o supporte a pathname
int shellInitPathname (){
	
	int i;
	
	if (pathname_initilized == 1)
	{
		return 0;
		//goto done;
	}
	
	for ( i=0; i<PATHNAME_LENGHT; i++ ){
		
		pathname_buffer[i] = (char) '\0';
	}
	
	pathname_lenght = 0;
	
	//...
	
//done:	

    pathname_initilized = 1;
	
	return 0;
}

 
//inicializaremos o supporte a filename
int shellInitFilename (){
	
	int i;
	
	if (filename_initilized == 1)
	{	
		return 0;
		//goto done;
	}
	
	for ( i=0; i<FILENAME_LENGHT; i++ )
	{
		filename_buffer[i] = (char) '\0';
	}
	
	filename_lenght = 0;
	
    	
	//...
	
//done:
	
    filename_initilized = 1;
	
	return 0;
}



/* 
 Remove the last N directories from PATH.  
 Do not leave a blank path.
 PATH must contain enough space for MAXPATHLEN characters. 
 Credits: bash 1.05
 */

void shell_pathname_backup ( char *path, int n ){
	
    register char *p = path + strlen(path);
	
	unsigned long saveN = (unsigned long) n;

    //#debug 
	//printf("%s", path);
	
	if (*path)
        p--;

    while (n--)
    {
        while(*p == '/')
	        p--;

        while(*p != '/')
	        p--;

        *++p = '\0';
    };
	
	//@todo: Criar em kernelmode uma roptina que 
	//que faça o mesmo que a shell_pathname_backup 	
    //Atualizar no gerenciamento feito pelo kernel.
	
	system_call ( 176, (unsigned long) saveN, (unsigned long) saveN, 
        (unsigned long) saveN );				
}


// Imprime todas as strings de um vetor de ponteiros.
// Isso vai ser usado pelo echo.

void shell_print_tokenList ( char *token_list[], char *separator ){
	
	int i;
	char *token;
	
	token = (char *) token_list[0];
	
	if ( token == NULL )
	    return;
	    //goto fail;
	
	
	//token = (char *) tokenList[i];
		
	//	if( token == NULL ){
		
    //#todo: Limits.		
    
	for ( i=0; i,128; i++ )
    {
		token = (char *) token_list[i];

	    if ( token == NULL )
	        return;
		
		if ( strncmp ( (char *) token_list[i], "echo", 4 ) == 0 )
		    continue;	
		
		printf ("%s", token_list[i] );
		printf ("%s", separator );
    };
}


/* 
This way I don't have to know whether fclose is a function or a macro. 
Credits: bash 1.05.
 */
/*
int
stream_close( FILE *file );
int
stream_close( FILE *file )
{
     return ( fclose(file) );
};
*/



/* 
 Return the octal number parsed from STRING, or -1 to indicate
 that the string contained a bad number. 
 Credits: bash 1.05.
 */
/* 
int
read_octal( char *string );
int
read_octal( char *string )
{
    int result = 0;
    int digits = 0;
    
	while( *string && 
	       *string >= '0' && 
		   *string < '8' )
    {
        digits++;
        result = (result * 8) + *string++ - '0';
    };

    if(!digits || result > 0777 || *string)
        result = -1;

    
done:	
	return (result);
};
*/





/*  Credits: bash 1.05. */
/*
void 
decrement_variable( int *var );
void 
decrement_variable( int *var )
{
    *var = *var - 1;
};
*/



/* Check if it's a .bin file */
int is_bin ( char *cmd ){
	
    char *p;
	
	p = cmd;
	
	int len = strlen (p);
    
	if( len <= 4 ) 
		return 0;
	
    p += len - 4;
    
	if ( *p++ != '.' ) 
		return 0;
	
    if ( strncmp ( (char *) p, "bin", 3 ) == 0 )
	{
	    return 1;	
	}

    return 0;
}


/* Check if it's a .sh1 file */
int is_sh1 ( char *cmd ){
	
    char *p;
	
	p = cmd;
	
	int len = strlen (p);
    
	if ( len <= 4 ) 
		return 0;
	
    p += len - 4;
    
	if ( *p++ != '.' ) 
		return 0;
	
    if ( strncmp ( (char *) p, "sh1", 3 ) == 0 )
	{
	    return 1;	
	}
	
    return 0;
}


//cancelado;
//agora esta el login.c
int shellCheckPassword ()
{
    return -1; //deletar
}



/*
 **************************************************
 * shellPrompt:
 *     Inicializa o prompt.
 *     Na inicialização de stdio, 
 *     prompt foi definido como stdin->_base.
 */

void shellPrompt (){
	
	int i;
	
	// Limpando o buffer de entrada.
	
	for ( i=0; i<PROMPT_MAX_DEFAULT; i++ )
	{
		prompt[i] = (char) '\0';
	}
	
    prompt[0] = (char) '\0';
	prompt_pos = 0;
    prompt_status = 0;
	prompt_max = PROMPT_MAX_DEFAULT;  

    printf ("\n");
    printf ("[%s]", current_workingdiretory_string );	
	printf ("%s ", SHELL_PROMPT );
	
	// #bugbug
	// Me parece que isso deixou tudo mais lento.
	// Seriam os vários argumentos ??
    //printf ("\n[%s]%s ", current_workingdiretory_string, SHELL_PROMPT );		
}





//help message
//mostra o menú básico, para comandos que promovam experi?ncia do usuário.
void shellShowExperienceMenu (){

    printf (experience_banner);			
    //printf (help_banner);	
}

//help message
//mostra menu extra com recursos ainda não implementados completamente.
void shellShowTestsMenu (){

    printf (tests_banner);			
    //printf (help_banner);	
}


//drawing a tree
void shellTree (){
	
    printf (tree_banner);	
}


/*
 *******************************************
 * shellThread:
 *     Um thread dentro para testes.
 */

void shellThread (){
	
	printf("\n");
	printf("$\n");
	printf("$$\n");
	//printf("$$$\n");
    printf("#### This is a thread ####\n");
	//printf("$$$\n");
	printf("$$\n");
	printf("$\n");
    printf("\n");
	
    gde_show_backbuffer ();
	
	while (1){ asm ( "pause" ); };
}



void shellPipeTest (){

    int pipefd[2];
	
	//pipe()
	//system_call ( 247, (unsigned long) piprfd, (unsigned long) 0, (unsigned long) 0 );

    if ( pipe(pipefd) == -1 ) 
	{    
		printf ("fail\n");
		//perror("pipe");
               //exit (EXIT_FAILURE);
    }
	
	printf ("shellPipeTest: Pipes ( %d %d )\n", pipefd[0], pipefd[1] );	
}


/*
 ***
 * shellSocketTest:
 *     Rotina de testes de socket.
 *     Essas funções não petencem à libc, mas farão parte da libc no futuro,
 * pois socket na libc tem muitas opções.
 *
 * #obs: 
 * Estamos lidando com soquete que usam endereços de IP e número de porta.
 * Esse tipo de soquete é usado para RPC.
 * Outros tipos de soquete lidam com outros tipos de endereço.
 * Podemos usar soquetes para LPC que apenas conecte dois processos
 * e troquem mensagens via estrutura padrão de mensagem, 
 * ex: wind, msg, long1, long2. 
 */

void shellSocketTest (){
	
	// #todo: 
	// Isso é um ponteiro de estrutura de soquete,
	// mas não definimos ainda em user mode.
	
	void *socketHandle;
	
	//ipv4 address.
	unsigned long iplong;
	unsigned long port;     // short
	
	//ipv4 address.
	unsigned char ip[4];
	
	unsigned long tmp;
	
    printf ("\n");
    printf ("shellSocketTest:\n");

	
	//
	// Creating socket
	//
	
	// Testing 160, 161, 162, 163.
	
	printf ("Creating socket ...\n");
	socketHandle = (void *) system_call ( 160, (unsigned long) 0xC0A80164, 
							    (unsigned long) 0, (unsigned long) 0x22C3 );
	
	printf ("Updating socket info ...\n");
	system_call ( 163, (unsigned long) socketHandle, 
	    (unsigned long) 0xC0A80165, (unsigned long) 0x22C2 );
	
	printf ("Getting IP from socket ...\n");
	iplong = (unsigned long) system_call ( 161, (unsigned long) socketHandle, 
							    (unsigned long) socketHandle, (unsigned long) socketHandle);
	
	printf ("Getting port from socket ...\n");
	port = (unsigned long) system_call ( 162, (unsigned long) socketHandle,
						       (unsigned long) socketHandle, (unsigned long) socketHandle);
	
	//
	// Output
	//
		
	tmp = iplong;
	ip[3] = (char) ( tmp & 0x000000FF ); 
	
	tmp = iplong;
	tmp = (tmp >> 8);
	ip[2] = (char) ( tmp & 0x000000FF );
	
	tmp = iplong;
	tmp = (tmp >> 16);
	ip[1] = (char) ( tmp & 0x000000FF );
	
	tmp = iplong;
	tmp = (tmp >> 24);
	ip[0] = (char) ( tmp & 0x000000FF );
	
	
	printf ("\n");
	printf ("Socket: ( %d.%d.%d.%d:%d )\n", 
		ip[0], ip[1], ip[2], ip[3], port );
	
	printf ("Done\n");
}



/*
 Credits: gcc 0.9 
 Read chars from INFILE until a non-whitespace char
 and return that.  
 
 Comments, both Lisp style and C style, are treated 
 as whitespace.
 
 Tools such as genflags use this function.  
 */
/* 
int
read_skip_spaces (infile)
    FILE *infile;
{
    register int c;
    while (c = getc (infile))
    {
        if (c == ' ' || c == '\n' || c == '\t' || c == '\f')
	    ;
            else if (c == ';')
	             {
	                 while ((c = getc (infile)) && c != '\n') ;
	             }
                 else if (c == '/')
	                  {
	                      register int prevc;
	                      c = getc (infile);
	                      //if (c != '*')
	                          //dump_and_abort ('*', c, infile);
	  
	                      prevc = 0;
	                      while (c = getc (infile))
	                      {
	                          if (prevc == '*' && c == '/')
		                      break;
	                          prevc = c;
	                      }
	                  }
                      else break;
    }
    return c;
};
*/


/* 
 Credits: gcc 0.9
 Read an rtx code name into the buffer STR[].
 It is terminated by any of the punctuation chars 
 of rtx printed syntax.  
 */
/*
static void
read_name (str, infile)
     char *str;
     FILE *infile;
{
  register char *p;
  register int c;

  c = read_skip_spaces(infile);

  p = str;
  while (1)
    {
      if (c == ' ' || c == '\n' || c == '\t' || c == '\f')
	break;
      if (c == ':' || c == ')' || c == ']' || c == '"' || c == '/'
	  || c == '(' || c == '[')
	{
	  ungetc (c, infile);
	  break;
	}
      *p++ = c;
      c = getc (infile);
    }
  *p = NULL;
}
*/












