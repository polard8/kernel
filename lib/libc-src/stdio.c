/*
 * File: stdio.c 
 *
 * Descrição:
 *     Rotinas de input/output para User Mode.
 *     Standard C language. C99.
 *
 * Credits:
 *     printf: https://www.menie.org/georges/embedded/small_printf_source_code.html
 *     stdio_fntos: Luiz Felipe
 *
 * History:
 *     2015 - Created.
 *     2015~2018 - Revision. 
 */


#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 
#include <ctype.h>


// Testando define.

#define	SYSTEMCALL_READ_LBA    1
#define	SYSTEMCALL_WRITE_LBA   2
#define	SYSTEMCALL_READ_FILE   3
#define	SYSTEMCALL_WRITE_FILE  4

#define VK_RETURN      0x1C 
#define VK_BACKSPACE   0x0E 
#define VK_BACK	       0x0E  
#define VK_TAB         0x0F 
//PRINT_BUF_LEN


//internas.
// estamos falando do posicionamento do cursor dentro da janela 
// e não dentro do terminal. 
void stdioSetCursor( unsigned long x, unsigned long y );
unsigned long stdioGetCursorX(); 
unsigned long stdioGetCursorY(); 


//rotina interna de support.
//isso deve ir para bibliotecas depois.
//não tem protótipo ainda.
// Credits: Luiz Felipe

void stdio_fntos (char *name){
	
    int  i, ns = 0;
    char ext[4];
    //const char ext[4];
	
    //transforma em maiúscula
	while ( *name && *name != '.' )
	{
        if ( *name >= 'a' && *name <= 'z' )
            *name -= 0x20;

        name++;
        ns++;
    };

    // aqui name[0] é o ponto.
	// então constroi a extensão.
	for ( i=0; i < 3 && name[i+1]; i++ )
	{
        if(name[i+1] >= 'a' && name[i+1] <= 'z')
            name[i+1] -= 0x20;

        ext[i] = name[i+1];
    };

    while (ns < 8){
		
        *name++ = ' ';
        ns++;
    };

    for (i=0; i < 3; i++)
        *name++ = ext[i];

    *name = '\0';
};


/*
 *
 * stdio_system_call:
 *     >> Protótipo de função interna. #encapsulada
 *     As funções padrão de stdio chamarão os recursos do
 * kernel atravéz dessa rotina.
 *     System call usada pelo módulo stdio. 
 *     Interrupção de sistema, número 200, chama vários serviços do Kernel 
 * com a mesma interrupção.
 *     Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, o Número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 */
void *stdio_system_call( unsigned long ax, 
                         unsigned long bx, 
				         unsigned long cx, 
				         unsigned long dx );

						 
/*
 ************************************************
 * fclose:
 *     Close a file.
 *     If work, return 0.
 */
int fclose (FILE *stream){
	
	// @todo: Implementar.
	
	//provisório.
	if ( (void *) stream != NULL ){
		
		stream->_ptr = NULL;
		stream->_cnt = 0;
		stream->_base = NULL;
		stream->_flag = 0;
		stream->_file = 0;
		stream->_charbuf = 0;
		stream->_bufsiz = 0;
		stream->_tmpfname = NULL;
		
		stream = NULL;
	};		
	
	//...

	return (int) 0;
};


/*
 **************************************************************
 * fopen:
 *     Open a file.
 *     @todo: Abrir onde? saída padrão?
 *     @retorna o que? o endereço do buffer?
 *     Obs: Tem função na api que carrega um arquivo em um buffer.
 *
 * #obs: Deveríamos checar o tamanho do arquivo antes de criar o buffer.
 *
 * #todo: E se o ponteiro para o nome do arquivo for inválido? tem que  
 * falhar e retornar null.
 */
FILE *fopen ( const char *filename, const char *mode ){

    //#importante:
	//#bugbug
	//#todo: Repare que não tem alocação nesse caso.
	//precisamos de alocadores.
	
	//buffer para a estrutura de stream.
	
	unsigned char struct_buffer[BUFSIZ];  //struct
	unsigned char buffer[BUFSIZ];         //file.
	
	
	//unsigned char *a = (unsigned char *) filename;
	unsigned long m = (unsigned long) mode;
	

	//Criando as estruturas.
	//struct _iobuf *stream;
	FILE *stream;

	stream = (FILE *) &struct_buffer[0];
	  
	//Colocamos aqui o endereço onde o arquivo foi carregado.  
	stream->_base = &buffer[0];
	
	stream->_ptr = &buffer[0];
	
	
	//Podemos medir o tamanho do arquivo antes e colocarmos
	//o valor aqui ... pode ser checando na entrada de diretório.
	stream->_cnt = PROMPT_MAX_DEFAULT;
	
	stream->_file = 0;
	stream->_tmpfname = (char *) filename;	
	

	// @todo: Criar filtros para os argumentos. Retornar NULL
	// se os argumentos forem inválidos.
	
	//#test
	if ( (char *) filename == NULL )
	    return NULL;
	
	//transformando a string do nome de file.txt em 'FILE    TXT'
	stdio_fntos( (char *) filename );
	
	//@todo: 
	// Chamar uma  rotina que carregue um arquivo ...
	// usar a mesma chamada pela api.
	
	
    stdio_system_call ( SYSTEMCALL_READ_FILE, (unsigned long) filename, 
		(unsigned long) &buffer[0], (unsigned long) &buffer[0] );		
	
	
	//if( (void*) a == NULL ){
	//    printf("Error: Invalid name.");
	//    return NULL;	
	//};
	
	return (FILE *) stream; 
};


/*
 * scroll:
 *     Scroll the screen in (text mode).
 *     @todo: Mudar para tmScroll(void);
 *     @todo: Criar gmScroll(void) talvez;
 *     @todo: Essa rotina precisa ser revisada e aprimorada.
 */
void scroll (void){
	
	//Início da tela.
	unsigned short *p1 = (unsigned short *) SCREEN_START;
	
	//Início da segunda linha.
    unsigned short *p2 = (unsigned short *) (SCREEN_START + 2 * SCREEN_WIDTH);
    unsigned short i,j;
	
	//linhas.
	//usa o valor default se passar dos limites.
	if( g_rows == 0 || g_rows >= SCREEN_MAX_HEIGHT ){
		g_rows = SCREEN_HEIGHT;
	};
	
	//24 vezes.
    for( i=0; i < g_rows -1; i++ )
	{
	    //80 vezes.
		
		//Se a variável nao foi inicializada, usar valor default.
		if(g_columns == 0 || g_columns >= SCREEN_MAX_WIDTH){ 
		    g_columns = SCREEN_WIDTH;
		};
		
        
		//modo texto
	    //if(g_using_gui == 0)
		//{	
		//    for( j=0; j < g_columns; j++ ){
        //        *p1++ = *p2++;
		//    };
		//};
		
		//modo gráfico.
	    if(g_using_gui == 1)	
		{	
		    for( j=0; j < g_columns; j++ )
			{
                //*p1++ = *p2++;
		        //@todo:
			};
		};
		
	};
	
	
	//
	// Limpando a última linha.
	//
	
	//80 vezes.
    
	//modo texto
	//if(g_using_gui == 0){
	//    for( i=0; i < g_columns; i++ ){ *p1++ = 0x07*256 + ' '; };
	//}
	
	//modo gráfico.
	if(g_using_gui == 1)
	{
	    for( i=0; i < g_columns; i++ )
		{ 
	        //*p1++ = 0x07*256 + ' ';
			//@todo:	
		};    
	};
		
    
//done:
	return;
};


/*
 * app_clear:
 *    (#bugbug: Isso não faz mais sentido, deletar.) 
 *     Limpa a tela.
 *     0x800000 = Endereço virtual da memoria de vídeo.
 *     g_current_vm; 0x000B8000fis = 0x800000vir
 * @todo: Mudar para tmClearScreen(int color);
 */

//#bugbug: deletando isso... 
 /*
int app_clear (int color)
{
    unsigned int i = 0;	
	char *vm = (char *) 0x00800000;  //Endereço virtual da VGA. b8000Fis.    

	//modo texto
	//if(g_using_gui == 0)
	//{	
	//    while(i < (SCREEN_WIDTH*SCREEN_HEIGHT*2)) 
    //    { 
    //        vm[i] = 219; 
    //        i++; 
    //    
    //        vm[i] = color; 
    //        i++; 
    //    };
	//};
	
	//modo gráfico.
	if(g_using_gui == 1)
	{
	    g_cursor_x = 0;
	    g_cursor_y = 0;
		
		//@todo:
		//Limpar a tela do terminal.
		
		//...
	};
	    
done:
    return (int) 0; 
};
*/ 
 
 
/*
 ***********************
 * puts:
 */
int puts ( const char *str ){
	
	//provisório ...
	return (int) printf ("%s",str);
};


/*
 ****************************************************************
 *    Construindo a função printf;
 *****************************************************************
 */


/*
 **********************************************************************
 * prints:
 *
 */
static int prints ( char **out, const char *string, int width, int pad ){
	
    register int pc = 0, padchar = ' ';

    
	// filtro: e se width for menor que 0??
	
	//if(width < 0){
	//	return (int) 1;
	//}
	
	if ( width > 0 ) 
	{
	    register int len = 0;
		register const char *ptr;
		
		for(ptr = string; *ptr; ++ptr) ++len;
		if(len >= width) width = 0;
		else width -= len;
		if(pad & PAD_ZERO) padchar = '0';
	};
	
	if ( !(pad & PAD_RIGHT) ) 
	{
		for ( ; width > 0; --width ){
		    printchar ( out,padchar );
			++pc;
		};
	};
	
	for ( ; *string ; ++string ){
		printchar(out, *string);
		++pc;
	};
	
	for ( ; width > 0; --width ){
		printchar(out,padchar);
		++pc;
	};

	return pc;
};


/*
 ***************************************
 * printi:
 *     used by printf.
 */
static int printi ( char **out, 
                    int i, 
					int b, 
					int sg, 
					int width, 
					int pad, 
					int letbase )
{
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;
	
	char print_buf[PRINT_BUF_LEN];
	
	if (i == 0){
		print_buf[0] = '0';
		print_buf[1] = '\0';		
		return prints (out, print_buf, width, pad);
	};
	
	if ( sg && b == 10 && i < 0) 
	{
		neg = 1;
		u = -i;
	};

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) 
	{
		t = u % b;
		
		if (t >= 10)
		    t += letbase - '0' - 10;
		    *--s = t + '0';
		    u /= b;
	};

	if (neg) 
	{
		if ( width && (pad & PAD_ZERO) ) 
		{
		    printchar (out, '-');
			++pc;
			--width;
		
		}else{
			*--s = '-';
		};
	};
	
    //Nothing.
//done:

	return pc + prints(out, s, width, pad);
};


/*
 ************************************************
 * print:
 *     Used by printf.
 */
static int print ( char **out, int *varg ){
	
	register int width, pad;
	register int pc = 0;
	register char *format = (char *) (*varg++);
	char scr[2];

	for ( ; *format != 0; format++ ) 
	{
		//switch.
		if ( *format == '%' ) 
		{
			++format;
			width = pad = 0;
			
			if ( *format == '\0' ) 
			    break;
			
			if ( *format == '%' ) 
			    goto out;
			
			if ( *format == '-' ){
				++format;
				pad = PAD_RIGHT;
			};
			
			while ( *format == '0' ){
				++format;
				pad |= PAD_ZERO;
			};
			
			for ( ; *format >= '0' && *format <= '9'; ++format ){
				width *= 10;
				width += *format - '0';
			};
			
			//string
			if ( *format == 's' ){
				
				register char *s = *( (char **) varg++ );
				pc += prints ( out, s?s:"(null)", width, pad);
				continue;
			}
			
			//int
			if ( *format == 'd' ){
				pc += printi ( out, *varg++, 10, 1, width, pad, 'a');
				continue;
			}
			
			//hexa
			if ( *format == 'x' ){
				pc += printi ( out, *varg++, 16, 0, width, pad, 'a');
				continue;
			}
			
			if ( *format == 'X' ){
				pc += printi ( out, *varg++, 16, 0, width, pad, 'A');
				continue;
			}
			
			if ( *format == 'u' ){
				pc += printi ( out, *varg++, 10, 0, width, pad, 'a');
				continue;
			}
			
			//char
			//char are converted to int then pushed on the stack. 
			if ( *format == 'c' ){
				
				scr[0] = *varg++;
				scr[1] = '\0';
				pc += prints ( out, scr, width, pad);
				continue;
			}
			
			//Nothing.
		
		}else{
			
		    out:
			    printchar ( out, *format );
			    ++pc;
		};
		//Nothing.
	};
	
	if (out) 
	    **out = '\0';
	
	return (int) pc;
};



/* 
 ***********************************************************************
 * printf:
 *     Imprime uma string formatada.
 *     Assuming sizeof(void *) == sizeof(int).
 * Obs: Temos uma chamada ao sistema para cada caractere.
 * 
 * Obs: Se passássemos apenas o ponteiro da string para o kernel pintá-la,
 * não estariamos usando o printf da biblioteca em user mode e sim 
 * a printf do kernel.
 */
 
int printf ( const char *format, ... ){
    
	register int *varg = (int *)(&format);
	
	return (int) print ( 0, varg );
};


/*
 *****************************************************************
 * sprintf:
 *     Emprime uma string formatada em 'out'.
 *     Escreve em um buffer de caracteres.
 * @todo: ??
 * Em caso de sucesso, a função retorna o número de caracteres 
 * da string formatada. Em caso de erro, um valor negativo é retornado.
 */
 
//opção 
//int sprintf(char *str, const char *format, ...) ?? 

int sprintf ( char *out, const char *format, ... ){
	
    register int *varg = (int *)(&format);
	
	return (int) print( &out, varg );
};


static void printchar ( char **str, int c ){
	
	if (str) 
    {
		**str = c;
		
		++(*str);
	
	}else (void) putchar(c);
};


/*
 **********
 * putchar:
 *     Put a char in the screen.
 *     Obs: Isso funciona bem. 
 *
 *     #importante: O kernel pinta o char no backbuffer e
 *     em seguida efetua um refresh do char para mostra-lo na tela.
 */
int putchar (int ch){
    
	// Opções:
	// +Chamar a função 'putchar' oferecida pelo kernel 
	// e utilizar o cursor gerenciado pelo kernel.
	// +chamar a função 'outbyte' com cursor gerenciado em user mode.
	
	// *importante:
	// Queremos que o kernel gerencie as mensagens de digitação,
	// então devemos usar a opção que permite o kernel usar seu próprio cursor.
	
    
	//#atenção
	//Estamos deixando o kernel gerenciar as mensagens de digitação 
	//usando seu próprio cursor.
    //put char.
	
	stdio_system_call ( 65, (unsigned long) ch, (unsigned long) ch, 
		(unsigned long) ch );
	
	return (int) ch;    
};


/*
 **********
 * outbyte:
 * @todo: Colocar no buffer de arquivo.
 * #obs: essa função chamará _outbyte.
 *
 * #importante: Não me lebro se o kernel efetua o refresh do char 
 * nesse caso.
 */
 
void outbyte (int c){
	
    static char prev = 0;
        
	// spaces.	
    if( c <  ' ' && 
	    c != '\r' && 
		c != '\n' && 
		c != '\t' && 
		c != '\b' )
	{
        return;
    };
	
	//#testando.
	//nada para imprimir.
	//?? onde fica o tratamento de backspace.??
	//if( c == '\b' )
    //{
	//	return;
	//}		
	
	// carriege return 
	// Volta ao início da linha.
	if ( c == '\r' )
	{	
        g_cursor_x = 0;
        prev = c;
        return;    
    };        
      
	//Próxima linha e não início da linha.   
    if ( c == '\n' && prev != '\r' ) 
    {
        g_cursor_y++;      
        g_cursor_x = 0;    
        prev = c;
        return;
    };
       
    //Próxima linha e início da linha. 	   
    if ( c == '\n' && prev == '\r' ) 
    {
        g_cursor_y++;  
        prev = c;
        return;
	};

    //Tab.
	//@todo: Criar a var -> 'g_tab_size'.
    if ( c == '\t' )  
    {
        g_cursor_x += (4);    
        prev = c;
        return;         
    };
        
    //Space 
	//#todo:
	// ?? talvez devêssemos imprimir o caractere espaço. ??    
	if ( c == ' ' )  
    {
        g_cursor_x++; 
        prev = c;
        return;         
    };
        
    //Delete. 
    if ( c == 8 )  
    {
        g_cursor_x--;         
        prev = c;
        return;         
    };
        
    // Filtra as dimensões da janela onde esta pintando.
//checkLimits:	
	
	//
	// Colunas.
	//
	
	//Definindo a largura que usaremos.
	//A largura precisa ser maior que '0' e menor que o limite máximo.
	//Obs: @todo: Essa rotina de definição pode ir para o momento da inicialização
	//da biblioteca. Ela contunua aqui porque está funcionando como um filtro.
	//
    if ( g_columns == 0 || g_columns >= SCREEN_MAX_WIDTH ){
		g_columns = COLUMNS;
	}
	
	//O cursor não pode ultrapassar a largura definida.
	if ( g_cursor_x > g_columns )
	{
        g_cursor_x = 0;
        g_cursor_y++;  
    }else{
		//Se não alcançamos o limite, apenas incrementa o x.
        g_cursor_x++;    
    };
    
	// Linhas.
	
	//Definindo a altura que usaremos.
	//A altura precisa ser maior que '0' e menor que o limite máximo.
	if ( g_rows == 0 || g_rows >= SCREEN_MAX_HEIGHT ){
		g_rows = ROWS;
	}
	
    //O cursor não pode ultrapassar a altura definida.	
	//se ultrapassar, chamaremos o scroll.
	//Obs: O scroll ainda não está implementado.
	//O scroll será feito depois que implementarmos o array de ponteiros
	//para estruturas de linha.
	
	if ( g_cursor_y > g_rows )
	{ 
	    scroll();
        g_cursor_x = 0;             //O cursor deve fica na primeira coluna.
		g_cursor_y = (g_rows-1);    //O cursor deve ficar na última linha.
    };

    // Imprime os caracteres normais.

	_outbyte (c);

	//Atualisa o prev.
    prev = c;     	
};


/*
 ***********
 * _outbyte:
 *     Just output a byte on the screen.
 *
 *     Obs: A função não se preocupa com o cursor.
 *          Essa rotina está preparada somente par ao modo gráfico.
 *          Talvez usaremos um selecionador de modo.   
 *
 * #obs: 
 * #importante: Não me lebro se o kernel efetua o refresh do char 
 * nesse caso.
 */
  
void _outbyte ( int c ){
	
	//#obs: Tamanho do char constante = 8. 
	//o que queremos é usar uma variável.
	
	stdio_system_call ( 7, 8*g_cursor_x,  8*g_cursor_y, (unsigned long) c ); 
};


/*
 ************************************************************
 * input:
 *     Coloca os caracteres digitados em uma string. 'prompt[]'
 *     #bugbug: 
 *     Deveríamos considerar o posicionamento dentro do arquivo.
 *     Dentro da stream.
 */
unsigned long input ( unsigned long ch ){
	
	//save cursor position.
	unsigned long tmpX, tmpY;
	
	// Convert.
	char c = (char) ch;    
	
	// Ajust prompt max.
	if ( prompt_max == 0 || prompt_max >= PROMPT_MAX_DEFAULT )
	{
		prompt_max = PROMPT_MAX_DEFAULT;
	}
	
	//Filtra limite.
	//retornar 1??
	if ( prompt_pos > prompt_max ){
		
	    printf ("input: Full buffer!\n");	
	    return (unsigned long) 0;   
	};
 
	// Trata caractere digitado.
	switch (c)
	{
	    //Enter.	
		case VK_RETURN:
		    prompt[prompt_pos] = (char ) '\0';
            goto input_done;			
		    break;

	    // Obs: O tab avança o cursor, mas precisamos 
		// pintar o espaço onde estava o cursor.
		// Por isso talvez seja bom um while de espaços.
		// Mas no buffer fica apenas o '\t'.
		case VK_TAB:
		    prompt[prompt_pos] = (char ) '\t';
			//for( i=0; i<4; i++)
			//{ printf("%c", (char) ' '); }
		    goto input_done;
			break;
			
		case VK_BACKSPACE:
            
			//Se estamos no início da linha.
			if(prompt_pos <= 0)
			{
                prompt_pos = 0; 				
			    prompt[prompt_pos] = (char ) '\0';
				break; 
			};
		    
			//altera o buffer.
			//Apaga o anterior.
			prompt_pos--;                        //volta um no buffer.
			prompt[prompt_pos] = (char ) '\0';   //apaga no buffer.
			
			//altera a tela no modo gráfico com janelas.
			tmpX = stdioGetCursorX(); 
			tmpY = stdioGetCursorY();
			
			//Volta um na tela.
			tmpX--;
			stdioSetCursor(tmpX,tmpY);
			
			//apaga a tela.
			printf ("%c", (char) ' '); 
			
			//altera a tela no modo gráfico com janelas.
			tmpX = stdioGetCursorX(); 
			tmpY = stdioGetCursorY();
			
			//Volta um na tela.
			tmpX--;
			stdioSetCursor(tmpX,tmpY);
			break;
			
		//Continua ...
		
		// Vamos deixar o sistema mostrar o cursor.
		// Coloca carctere normal no buffer.
		// Incrementa posicionamento no buffer.
		default:
		    prompt[prompt_pos] = c;
		    prompt_pos++;
			break;
			
	};
	
//input_more:	
	return (unsigned long) 0;

input_done:	
    return VK_RETURN;	
};


/*
 ********************
 * stdio_system_call:
 *     System call usada pelo módulo stdio.  
 *     Função interna. 
 *     As funções padrão de stdio chamarão recursos do kernel atravéz dessa 
 * rotina.
 *     Interrupção de sistema, número 200, personalizada para stdio.
 *     Chama vários serviços do Kernel com a mesma interrupção.
 *     Essa é a chamada mais simples.
 *
 * Argumentos:
 *    eax = arg1, o Número do serviço.
 *    ebx = arg2. 
 *    ecx = arg3.
 *    edx = arg4.
 */
void *stdio_system_call ( unsigned long ax, 
                          unsigned long bx, 
				          unsigned long cx, 
				          unsigned long dx )
{
    int Ret = 0;	
	
    //System interrupt.
 	
	asm volatile ( " int %1 \n"
		           : "=a"(Ret)	
		           : "i"(200), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

	return (void *) Ret; 
};


/*
// Return BUFFER_SIZE. 
int input_file_buffer_size(void);
int input_file_buffer_size(void)
{
  return (BUFFER_SIZE);
}
*/


// getchar:
// pegando diretamente do kernel e não do arquivo.
// me parece que o tradicional é pegar do arquivo,
// mas isso acontece em outras situações.
//@todo:
//Podemos pegar esse char e colocá-lo stdin 
//slave (local) de input.

int getchar (void){
	
	return (int) stdio_system_call ( 137, 0, 0, 0 ); 
};


/*
 **************************************************
 * stdioInitialize:
 *     Inicializa stdio para usar o fluxo padrão.
 *     O retorno deve ser (int) e falhar caso dê algo errado.
 */
void stdioInitialize (){
	
	//register int i;
	int i;
	
	// Buffers para as estruturas.
	unsigned char buffer0[BUFSIZ];
	unsigned char buffer1[BUFSIZ];
	unsigned char buffer2[BUFSIZ];
	
	
	// Alocando espaço para as estruturas.
	stdin = (FILE *) &buffer0[0];	
	stdout = (FILE *) &buffer1[0];	
	stderr = (FILE *) &buffer2[0];

    // A biblioteca tem 3 pequenos buffers,
	// que serão usados como base para os stream.
	// ?? Podemos almentar esses buffers ?? @todo: testar.

	//stdin - Usando o buffer 'prompt[.]' como arquivo.
	stdin->_base = &prompt[0];
	stdin->_ptr = stdin->_base;
	stdin->_cnt = PROMPT_MAX_DEFAULT;
	stdin->_file = 0;
	stdin->_tmpfname = "stdin";
	//...
	
	//stdout - Usando o buffer 'prompt_out[.]' como arquivo.
	stdout->_base = &prompt_out[0];
	stdout->_ptr = stdout->_base;
	stdout->_cnt = PROMPT_MAX_DEFAULT;
	stdout->_file = 1;
	stdout->_tmpfname = "stdout";
	//...
	
	//stderr - Usando o buffer 'prompt_err[.]' como arquivo.
	stderr->_base = &prompt_err[0];
	stderr->_ptr = stderr->_base;
	stderr->_cnt = PROMPT_MAX_DEFAULT;
	stderr->_file = 2;
	stderr->_tmpfname = "stderr";	
	//...
	
	// Limpando os buffers.
	
	//#bugbug: Cuidado com o tamanho.
	
	for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
		
		prompt[i] = (char) '\0';
		prompt_out[i] = (char) '\0';
		prompt_err[i] = (char) '\0';
	}
};


/*
 ********************************
 * fflush:
 *     Limpa uma stream.
 */
int fflush ( FILE *stream ){
	
	register int i = 0;
	
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
	}
		
	// Limits.	
	if ( stream->_bufsiz == 0 || stream->_bufsiz > BUFSIZ ){
		
		return (int) (-1);
	}
    
    //
	// Clear.
    //
	
    // #bugbug: 
	// Se essa base aponta para um lugar inválido poderemos 
	// ter uma page fault.
	
    for ( i=0; i < stream->_bufsiz; i++ )
	{
	    stream->_base[i] = (char) '\0';		
	}		
		
	//@todo: atualizar os contadores de tamanho.	
	stream->_bufsiz = 0;
	
	return (int) 0;
};


/*
 ********************************
 * fprintf:
 *      
 */
int fprintf ( FILE *stream, const char *format, ... ){
	
	int size;
	
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
		
	} else {
		
		size = (int) strlen (format);
		
		if ( size > stream->_cnt )
		{
			return (int) (-1);
		}
		
		stream->_cnt = (int) (stream->_cnt - size);
		
		sprintf ( stream->_ptr, format );
		
		stream->_ptr = stream->_ptr + size;
        
		return (int) 0;		
	};
	
	return (int) (-1);
};


/*
 ********************************
 * fputs:
 *      
 */
int fputs ( const char *str, FILE *stream ){
	
	int size;
	
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
		
	} else {
		
		size = (int) strlen (str);
		
		if ( size > stream->_cnt )
		{
			return (int) (-1);
		}
		
		stream->_cnt = (int) (stream->_cnt - size);
		
		sprintf( stream->_ptr, str );
		
		stream->_ptr = stream->_ptr + size;
		
        return (int) 0;		
	};
	
	return (int) (-1);
};


/*
 *********************************
 * gets:
 *
 * os: gets() devolve um ponteiro para s
 */
char *gets (char *s){
	
    int ch;
    int t;
	char *p;
	
    //salva
	p = s; 	
	
	while (1)
	{
        ch = (int) getchar ();
		
        if ( ch != -1 )
		{
            switch (ch) 
		    {
				/* termina a string */
			    case '\n':
				case VK_RETURN: 
                    s[t] =  (char) '\0'; 
                    goto done;
				    break;
            
                case '\b':
				case VK_BACKSPACE:
			        if(t > 0){ 
					    t--;
					};
                    break;
            
			    default:
                    s[t] = (char) ch;
					++t;
					break;
           };
		};
		
		asm ("pause");
    };
	
    s[t] = (char) '\0';
	
done:	
    return (char *) p;
};


/*
 *********************************
 * ungetc:
 *
 */
int ungetc ( int c, FILE *stream ){
	
    if (c == EOF) 
	    return (int) c;	
	
	if ( (void *) stream == NULL )
	{
		return (int) EOF;
	}

	//@todo: flag oef.
	//stream->flags = (stream->flags & ~_IOEOF);
	
	stream->_ptr--;
	
	stream->_ptr[0] = (char) c;
	
    return (int) c;	
};


/*
 *********************************
 * fgetc:
 *
 */
int fgetc ( FILE *stream ){
	
    int ch;	
 
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
		
	} else {
		
		//Não há mais caracteres disponíveis entre 
		//stream->_ptr e o tamanho do buffer.
		if ( stream->_cnt <= 0 )
		{
			stream->_flag = (stream->_flag | _IOEOF); 
			stream->_cnt = 0;
			
			return (int) (-1);
		};
				
		//pega o char
		ch = (int) *stream->_ptr; 
		
		stream->_ptr++;
		
		stream->_cnt--;
		
        return (int) ch;		
	};
	
    return (int) (-1);	
};


/*
 *********************************
 * feof:
 *
 */
int feof ( FILE *stream ){
	
    int ch;	
 
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
		
	} else {
	
	    ch = fgetc (stream);
		
        if ( ch == EOF )
		{
			return (int) 1;
		}else{
			return (int) 0;
		};
	};
	
	//checar se o eof foi atingido.
	// return( (stream->_flag & _IOEOF) );
	
	return (int) 0;
};


/*
 *********************************
 * ferror:
 *
 */
int ferror ( FILE *stream ){
	
	if ( (void *) stream == NULL ){
		
		return (int) (-1);
	}
	
    return (int) ( ( stream->_flag & _IOERR ) );
};


/*
 **************************************
 * fseek:
 *     offset argument is the position that you want to seek to,
 *     and whence is what that offset is relative to.
 */
int fseek ( FILE *stream, long offset, int whence ){
	
	if ( (void *) stream == NULL )
	{
	    goto fail;	
	}
	
	//checar limites do offset.
	
	switch (whence){
		
		case SEEK_SET:    
		    stream->_ptr = (stream->_base + offset); 
			goto done;
			break;
			
		case SEEK_CUR:
		    stream->_ptr = (stream->_ptr + offset);
		    goto done;
			break;

		case SEEK_END:
		    stream->_ptr = ((stream->_base + stream->_bufsiz) + offset); 
		    goto done;
			break;

        default:
		    goto fail;
			break;
	};
	
fail:	
    return (int) (-1);	
done:	
    return (int) (0);	
};


/*
 *****************************************
 * fputc:
 *
 */
int fputc ( int ch, FILE *stream ){
	
	if ( (void *) stream == NULL )
	{
	    return (int) (-1);	
		
	}else{
		
        sprintf ( stream->_ptr, "%c", ch);
	
	    stream->_ptr++;
	    stream->_cnt--;		
	};

    return (int) (0);		
};


/*
 ********************************
 * stdioSetCursor:
 *     estamos falando do posicionamento do cursor dentro da janela
 *     e não dentro do terminal.
 */
void stdioSetCursor ( unsigned long x, unsigned long y ){
	
	//34 - set cursor.
    stdio_system_call ( 34, x, y, 0 );	
};


/*
 * stdioGetCursorX:
 *     Get cursor x. 
 *     estamos falando do posicionamento do cursor dentro da janela
 *     e não dentro do terminal.
 */  
unsigned long stdioGetCursorX (){
	
    return (unsigned long) stdio_system_call ( 240, 0, 0, 0 );
};


/*
 * stdioGetCursorY:
 *     Get cursor y.
 *     estamos falando do posicionamento do cursor dentro da janela
 *     e não dentro do terminal. 
 */
unsigned long stdioGetCursorY (){
	
    return (unsigned long) stdio_system_call ( 241, 0, 0, 0 );
};


//======================================================================
// scanf support (start)
//======================================================================

//todo
//faltam outros switches ... temos apenas o %s 

//atoi. # talvez isso possa ir para o topo do 
//arquivo para servir mais funções.
int stdio_atoi (char * s){
	
    int rv=0; 
    char sign = 0;

    /* skip till we find either a digit or '+' or '-' */
    while (*s) 
	{
	    if (*s <= '9' && *s >= '0')
		    break;
	    if (*s == '-' || *s == '+') 
		    break;
	    s++;
    }; 	  

    if (*s == '-')
	    sign=1;

    //     sign = (*s == '-');
    if (*s == '-' || *s == '+') 
	    s++;

    while (*s && *s >= '0' && *s <= '9') 
	{
	    rv = (rv * 10) + (*s - '0');
        s++;
    };

    if (sign) return (-rv);
        else return (rv);
     
    //     return (sign ? -rv : rv);
};


int scanf ( const char *fmt, ... ){
	
    va_list ap;
	va_start(ap, fmt);
	
    int d;
    char *s;

	//%c
    int ch;
	
	//usado em %d
	int *i;
	char tmp[80];
	
	
	//o char.
	int c;
	
	char *cp;
	
	char *t;

	int nread;
	int size = (int) strlen (fmt);
	
	nread = 0;
	
    while (*fmt)
	{
		c = *fmt;
		if (c == 0)
			return (0); //erro
		
		// pulando os espaços
		if ( isspace(c) ) 
		{
			while ( size > 0 && isspace(*fmt) )
			{
				nread++; 
				size--; 
				fmt++;
			};
			
			continue;
		}
		
        switch (*fmt++) 
		{
			/* string */
            case 's':              
				//pego o ponteiro para  a string, depois é só usar o gets. ??
				s = va_arg(ap, char *);
				
				//usaremos esse ponteiro para colocar uma string digitada.
				if ( (void *) s != NULL )
				{
				    gets(s);					
				}else{
				    printf("scanf s null pointer\n");	
				}
				
				//testar ...
				//printf("string %s\n", s);
                break;
            
			/* int */
			case 'd': 
				//pego o ponteiro para  a string, depois é só usar o gets. ??
				i = va_arg(ap, int *);
				
				//usaremos esse ponteiro para colocar uma string digitada.
				if( (void *) i != NULL )
				{
				    //pego uma string de caracteres, que são números digitados.
					gets(tmp);
					
					//converte essa string em dígito
					i[0] = (int) stdio_atoi (tmp);                     
					
				}else{
				    printf("scanf s null pointer\n");	
				}
				
				//testar ...
				//printf("string %s\n", s);
			
                //d = va_arg(ap, int);
                //printf("int %d\n", d);
                break;
            
			/* char */
			case 'c':    
                t = va_arg(ap, char *);
				if ( (void *) t != NULL )
				{
				
                    while (1)
                    {
			            ch = (int) getchar();
						
						if ( ch != -1 )
						{
						    t[0] = ch;
                            //printf("scanf ch={%c}",ch);							
						    break;	
						}			
					};	
					
				}else{
					printf("scanf c null pointer\n");
				}; 				 
                break;
				
			//default:
            //    break; 			
				
        };//switch
	};
   // va_end(ap);
   
   return (int) 0;
};

//======================================================================
// scanf support (end)
//======================================================================




//
// End.
//

