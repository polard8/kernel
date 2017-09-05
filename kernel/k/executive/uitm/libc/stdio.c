/*
 * File: stdio.c 
 *
 * Descrição:
 *     +Rotinas de input/output padrão.
 *     +Algumas rotinas de console.
 *
 * Ambiente:
 *     Apenas kernel mode.
 *
 *
 * @todo: Buffering and pipes.
 * 
 * Histórico: 
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */
  
 
#include <kernel.h>


//
// Funções importadas.
//

extern void background();  //Assembly.
extern void refresh_screen();


/*
 * fclose:
 *     Close a file.    
 */
int fclose(FILE *stream)
{	
	if( (void*) stream != NULL ){
		stream = NULL;
	};		

	//
	// @todo: Implementar.
	//


done:	
	return (int) 0;
}


/*
 * fopen:
 *     Open a file.
 */
FILE *fopen(const char *filename, const char *mode)
{
	//
	// @todo: precisamos de um retorno e de um buffer.
	//        e alocar memoria para a estrutura do arquivo.?? 
	//
	
	//FILE *f;
	
	//f = (void) malloc 
		
	//carregar_arquivo( (unsigned char *) filename, (unsigned long) address);
	 
	printf("fopen: @todo:\n");
    return NULL;	
};


/*
 * scroll:
 *     Scroll the screen in text mode.
 *     Scroll the screen in graphical mode.
 *     @todo Poderiam ser duas funções: ex: gui_scroll(). 
 *     @todo: Não realizar scroll da interface gráfica.
 *    
 *     *IMPORTANTE
 *     O Que devemos fazer é reordenar as linhas
 *     nos buffers de linhas
 *     para mensagens de texto em algum terminal. 
 *
 */
void scroll(void)
{
    unsigned short i;
    unsigned short j;
	
	//Início da tela.
	unsigned short *p1 = (unsigned short *) SCREEN_START;
	
	//Início da segunda linha.
    unsigned short *p2 = (unsigned short *) (SCREEN_START + 2 * SCREEN_WIDTH);

	//
	// Se estamos em Modo gráfico (GUI).
    //
	
	if(VideoBlock.useGui == 1)
	{
		//Modificar o backbuffer. BACKBUFFER_BASE
        
		//mover o backbuffer começando da segunda linha.
		//exclui a primeira linha e a segunda linha será a nova primeira.
		
		//so que na verdade isso deve ser feito apenas para a 
		//janela onde o texto está e não para o backbuffer inteiro.
		//por enquanto fica assim.
		
		
		//apaga a linha.
		for(i = 0; i < 70; i++){
		    //outbyte(" ");    	
		};
		
		//cada linha tem 800 pixel, cada char tem 8 pixel de largura,
		//a altura do char são pixel.
		//cada pixel tem 3 bytes.
		
		//move 74 linhas começando da segunda.
		
		//destino, origem(segunda linha), quantidade de bytes.
        //memcpy( (void*) BACKBUFFER_BASE, (const void*) BACKBUFFER_BASE + (g_cursor_right*8*3), (size_t) (g_cursor_right*8*3*8*(g_cursor_left-1)));        
        memcpy( (void*) BACKBUFFER_BASE, (const void*) BACKBUFFER_BASE + (100*8*3), (size_t) (100*8*3*8*(g_cursor_left-1)));        		

		//
        //Limpa a última linha.
        //
		
		g_cursor_x = g_cursor_left;
		g_cursor_y = g_cursor_bottom;
		
		for(i = g_cursor_left; i < g_cursor_right; i++){
		    printf("%c",' ');    	
		};
		//Nothing.
		
		
		//
		// Reposiciona o cursor na última linha.
		//
		
        g_cursor_x = g_cursor_left;
		g_cursor_y = g_cursor_bottom;
		
		
		
		goto done;
	};	
	
	//
	// Se estavermos em modo texto.
    //
	
	if(VideoBlock.useGui == 0)	
	{
	    //24 vezes.
        for(i=0; i < SCREEN_HEIGHT -1; i++)
	    {
	        //80 vezes
            for(j=0; j < SCREEN_WIDTH; j++){
                *p1++ = *p2++;
		    };
			//Nothing.
		};
	
	    //80 vezes.
        for(i=0; i < SCREEN_WIDTH; i++){
		    *p1++ = 0x07*256 + ' '; 
	    };
		//Nothing.
		
		goto done;
    };
	


    //Nothing.	
	
done:
	return;
};


/*
 * kclear:
 *     Limpa a tela em text mode.
 */
int kclear(int color)
{ 
    unsigned int i = 0;
	char *vm = (char *) g_current_vm;    //fis=0x000B8000, virtual=0x800000; 


//Graphic Mode.
gui_mode:
	if(VideoBlock.useGui == 1){
	    backgroundDraw(COLOR_BLACK);       
		return (int) 0; 		
	};
//Text Mode.
text_mode:	
	while(i < (SCREEN_WIDTH*SCREEN_HEIGHT*2)) 
    { 
        vm[i] = 219; 
        i++; 
        
        vm[i] = color; 
        i++; 
    };
	
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 0;
//done.
done: 
    return (int) 0; 
}; 


/*
 * kclearClientArea:
 *     Limpa a área de cliente em text mode.
 *     Limpa 24 das 25 linhas.
 *     Não limpa a primeira de cima.
 */
int kclearClientArea(int color)
{
	char *vm = (char *) g_current_vm;    //fis=0x000B8000; 	
    unsigned int i = (SCREEN_WIDTH*2);
      
    while(i < (SCREEN_WIDTH*SCREEN_HEIGHT*2)) 
    { 
        vm[i] = 219; 
        i++; 
        
        vm[i] = color; 
        i++; 
    };
	
	//Cursor.
	g_cursor_x = 0;
	g_cursor_y = 0;
    
done:
    return (int) 0; 
}; 


/*
 * kprintf:
 *     Rotina simples de escrita em kernel mode.
 */
int kprintf( char *message, unsigned int line, int color )
{ 
    char *vm = (char *) g_current_vm;    //fis=0xb8000, vir=0x800000; 
    unsigned int i; 

	i = (line*SCREEN_WIDTH*2); 

    while(*message!=0) 
    { 
        if(*message=='\n')
        { 
            line++; 
            i=(line*SCREEN_WIDTH*2); 
            *message++; 
        }
        else
        { 
            vm[i]=*message; 
            *message++; 
            i++; 
            vm[i]= color; 
            i++; 
        }; 
    };
	
done:	
    return (int) 0; 
}; 



/*
 * Segue aqui a função printf.  
 *
 */



//
//prints
//
static int prints( char **out, const char *string, int width, int pad)
{
    register int pc = 0, padchar = ' ';

    if(width > 0) 
	{
	    register int len = 0;
		register const char *ptr;
		
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
	};
	
	if( !(pad & PAD_RIGHT) ) 
	{
		for ( ; width > 0; --width){
		    printchar(out,padchar);
			++pc;
		};
	};
	
	for( ; *string ; ++string){
		printchar(out, *string);
		++pc;
	};
	
	for( ; width > 0; --width){
		printchar(out,padchar);
		++pc;
	};

done:	
	return pc;
};


//
//printi
//
static int printi( char **out, int i, int b, int sg, int width, int pad, int letbase)
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if(i == 0) {
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints(out, print_buf, width, pad);
	};
	
	

	if(sg && b == 10 && i < 0){
		neg = 1;
		u = -i;
	};

	s = print_buf + PRINT_BUF_LEN-1;
	*s = '\0';

	while (u) 
	{
		t = u % b;
		
		if ( t >= 10 )
		    t += letbase - '0' - 10;
		    *--s = t + '0';
		    u /= b;
	};

	if (neg) 
	{
		if ( width && (pad & PAD_ZERO) ) 
		{
		    printchar(out, '-');
			++pc;
			--width;
		}
		else 
		{
			*--s = '-';
		};
	};

	return pc + prints(out, s, width, pad);
};


//
//print
//
static int print(char **out, int *varg)
{
	register int width, pad;
	register int pc = 0;
	register char *format = (char *)(*varg++);
	char scr[2];

	for (; *format != 0; ++format) 
	{
		if (*format == '%') 
		{
			++format;
			width = pad = 0;
			
			if(*format == '\0') 
			    break;
			
			if(*format == '%') 
			    goto out;
			
			if(*format == '-') 
			{
				++format;
				pad = PAD_RIGHT;
			};
			
			while(*format == '0') 
			{
				++format;
				pad |= PAD_ZERO;
			};
			
			for( ; *format >= '0' && *format <= '9'; ++format) 
			{
				width *= 10;
				width += *format - '0';
			};
			
			if( *format == 's' ) 
			{
				register char *s = *((char **)varg++);
				pc += prints (out, s?s:"(null)", width, pad);
				continue;
			}
			
			if( *format == 'd' ){
				pc += printi (out, *varg++, 10, 1, width, pad, 'a');
				continue;
			}
			
			if( *format == 'x' ){
				pc += printi (out, *varg++, 16, 0, width, pad, 'a');
				continue;
			}
			
			if( *format == 'X' ){
				pc += printi (out, *varg++, 16, 0, width, pad, 'A');
				continue;
			}
			
			if( *format == 'u' ){
				pc += printi (out, *varg++, 10, 0, width, pad, 'a');
				continue;
			}
			
			if( *format == 'c' ) 
	        {
				/* char are converted to int then pushed on the stack */
				scr[0] = *varg++;
				scr[1] = '\0';
				pc += prints (out, scr, width, pad);
				continue;
			}
		}
		else 
		{
		    out:
			    printchar (out, *format);
			    ++pc;
		};
	};
	
	if (out) **out = '\0';
	return pc;
};


/*
 * printf:
 *     The printf function.
 *     Assuming sizeof(void *) == sizeof(int).
 */
int printf(const char *format, ...)
{    
    //sincronisa.  
    // vsync();
    
	register int *varg = (int *)(&format);
	return print(0, varg);
};


/* printf dentro da janela com o foco de entrada.
int window_printf(const char *format, ...);
int window_printf(const char *format, ...)
{    

	register int *varg = (int *)(&format);
	
    //sincronisa.  
   // vsync();
   
   
   if( (void*) WindowWithFocus == NULL){
	   return 0;
   }
    
	//Auterando a margem
		g_cursor_left = (WindowWithFocus->left/8);
		g_cursor_top =  (WindowWithFocus->top/8)+2;
		g_cursor_right = g_cursor_left+(320/8);
		g_cursor_bottom = g_cursor_top+(480/8);
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 	
		
		

	
	int r;

	r = print(0, varg);
	
		//voltando a margem normal a margem
		g_cursor_left = 0;
		g_cursor_top =  0;
		g_cursor_right = 256;
		g_cursor_bottom = 256;
		
		//cursor (0, mas com margem nova)
		g_cursor_x = g_cursor_left; 
		g_cursor_y = g_cursor_top; 		
	
	return (int) r;
};
*/


/*
 * panic:
 *     Kernel panic function.
 *     @todo: Esse função deve retornar void.
 */
int panic(const char *format, ...)
{           
	register int *varg = (int *)(&format);
	
gui_mode:
    if(VideoBlock.useGui == 1)
	{
	    backgroundDraw(COLOR_BLACK);
		printf("KERNEL PANIC:\n\n");
		print(0, varg);
		refresh_screen();
		while(1){}
	};

text_mode:
    if(VideoBlock.useGui == 0)
	{
	    kclear(0);
	    print(0, varg);
	    while(1){}        //No return.
	};
	
//Done.
done:	
	return (int) 0;
};


/*
 * sprintf:
 *     int sprintf ( char * str, const char * format, ... );
 *     Composes a string with the same text that would be 
 * printed if format was used on printf, 
 * but instead of being printed, the content is stored 
 * as a C string in the buffer pointed by str.
*/
int sprintf(char *str, const char *format, ...)
{
	
   // vsync();
	
    register int *varg = (int *)(&format);
	return print(&str, varg);
};


/*
 * fprintf:
 *
 */
int fprintf(FILE *stream, const char *format, ...)
{
    register int *varg = (int *)(&format);
	

	if( (void*) stream != NULL ){
        return 0;   //@todo Error. O erro deveria retornar 1.		
	};		

	char *str = (char *) stream->_ptr;
	
done:	
	return print(&str, varg);	
};


static void printchar(char **str, int c)
{
	//extern int putchar(int c);
	if(str) 
    {
		**str = c;
		++(*str);
	}
	else (void) putchar(c);
};


/*
 * putchar:
 *     Put a char on the screen. (libC).
 */
int putchar(int ch)
{    
    outbyte(ch);
    return ch;    
};


/*
 * The getchar function is equivalent to getc with stdin as the value of the stream argument.
int getchar(void);
int getchar(void)
{
	return 0;
}
*/


/*
 * outbyte:
 *     Trata o caractere a ser imprimido.
 */
void outbyte(int c)
{     
    //@todo: Colocar no buffer de arquivo.
       
    static char prev = 0;
        
	//nothing to do.	
    if( c <  ' '  && c != '\r' && c != '\n' && c != '\t' && c != '\b' )
    {
        return;
    };
                
    //Volta ao inicio da linha.        
    if( c == '\r' ){
        g_cursor_x = g_cursor_left;  //0
        prev = c;
        return;    
    };        
       
    
    //Início da próxima linha.    
    if( c == '\n' && prev != '\r' ) 
    {
        g_cursor_y++;
        g_cursor_x = g_cursor_left;  //0
        prev = c;
        return;
    };
        
    //Próxima linha.
	if( c == '\n' && prev == '\r' ) 
    {
        g_cursor_y++;
        prev = c;
        return; 
    };

    //tab
	//@todo: Criar a variável 'g_tab_size'.
    if( c == '\t' )  
    {
        g_cursor_x += (4); 
        prev = c;
        return;         
    };
        
    //space 
    if( c == ' ' )  
    {
        g_cursor_x++; 
        prev = c;
        return;         
    };
        
    //delete 
    if( c == 8 )  
    {
        g_cursor_x--;         
        prev = c;
        return;         
    };
        
     
    //
    // Filtra as dimensões da janela onde está pintando.
    // @todo: Esses limites precisam de variável global.
	//        mas estamos usando printf pra tudo.
	//        cada elemeto terá que impor seu próprio limite.
	//        O processo shell impoe seu limite.
	//        a janela impoe seu limite etc...
	//        Esse aqui é o limite máximo de uma linha.
    // poderia ser o limite imposto pela disciplina de linha
    // do kernel. para o máximo de input. Pois o input é
    // armazenado em uma linha.	 
	//
	
    if(g_cursor_x >= g_cursor_right)  //256 caracteres por linha no máximo
    {
        g_cursor_x = g_cursor_left;
        g_cursor_y++;  
		
    }else{
        
        g_cursor_x++; //incrementa coluna
                                 
    };
    
	
	//Número máximo de linhas. (8pixel por linha.)
    if(g_cursor_y > g_cursor_bottom)  //256 caracteres por coluna no máximo
    { 
	    scroll();
         
	    // DEBUG( tx, "SCROLL!");
         
        // MessageBox("scroll");
        g_cursor_y = g_cursor_bottom;
    };

    // Imprime os caracteres normais.
	_outbyte(c);
	
	// Atualisa o prev.	
	prev = c;	   

done:
    return;
};


/*
 * _outbyte:
 *     Essa rotina envia o caractere para a tela.
 *     @todo: Um switch percebe o modo de vídeo e como esse
 *            caractere deve ser construído.
 *            Criar uma estrutura para parâmetros de vídeo.
 * 
 */
void _outbyte(int c)
{
    unsigned long i;
	unsigned long x;
	unsigned long y;
	
	//Base atual da memória de vídeo 0x000B8000;
    //@todo: usar VideoBlock.currentVM.
	char *vm = (char *) g_current_vm;    

	char ch = (char) c;
	char ch_atributo = (char) g_char_attrib;
	

    /*
     * Caso estivermos em modo gráfico.
     */
	if(VideoBlock.useGui == 1)
	{
	    //	vsync();
		
		// @todo: A mensagem deve ir par aum buffer de linha,
		// antes de ser pintado ja janela apropriada.
		
	    switch(VideoBlock.vesaMode)
		{
			//
			// @todo: Testar gcharWidth, gcharHeight.
			//
			
		    //@todo: Listar aqui os modos VESA.
		    case 1:
			    my_buffer_char_blt( 8*g_cursor_x, 8*g_cursor_y, COLOR_WINDOWTEXT, c);
				  //my_buffer_char_blt( gcharWidth*g_cursor_x, gcharHeight*g_cursor_y, COLOR_WINDOWTEXT, c);
			    break;
		    default:
			    //modo gráfico vesa 640x480 24bpp, 8 pixel por caractere.
			    my_buffer_char_blt( 8*g_cursor_x, 8*g_cursor_y, COLOR_WINDOWTEXT, c);
			    //my_buffer_char_blt( gcharWidth*g_cursor_x, gcharHeight*g_cursor_y, COLOR_WINDOWTEXT, c);
				break;
		};

     	goto done;	
	};
 

	/*
	 * Caso estivermos em text mode.
	 */
    if(VideoBlock.useGui == 0)
	{
	    //calcula o valor do deslocamento para text mode 80x25.
	    y = (g_cursor_y * 80 *2);
        x = g_cursor_x*2;    
        i = y + x;

        
		//envia o caractere.
		vm[i+0] = ch;           //char
        vm[i+1] = ch_atributo;  //atributo (foreground,background)
	};
	
done:    
    return;     
};


/*
 * printf_main:
 *     Essa função testa a função printf() e seus recursos.
 *     Obs: We can implement this test in user mode.
 * Obs:
 *     If you compile this file with
 *     gcc -Wall $(YOUR_C_OPTIONS) -DTEST_PRINTF -c printf.c
 * you will get a normal warning:
 *   printf.c:214: warning: spurious trailing `%' in format
 * this line is testing an invalid % at the end of the format string.
 *
 * this should display (on 32bit int machine) :
 *
 * Hello world!
 * printf test
 * (null) is null pointer
 * 5 = 5
 * -2147483647 = - max int
 * char a = 'a'
 * hex ff = ff
 * hex 00 = 00
 * signed -3 = unsigned 4294967293 = hex fffffffd
 * 0 message(s)
 * 0 message(s) with %
 * justif: "left      "
 * justif: "     right"
 *  3: 0003 zero padded
 *  3: 3    left justif.
 *  3:    3 right justif.
 * -3: -003 zero padded
 * -3: -3   left justif.
 * -3:   -3 right justif.
 *
 */
int printf_main(void)
{

/*	
	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf("%s\n", ptr);
	printf("printf test\n");
	printf("%s is null pointer\n", np);
	printf("%d = 5\n", i);
	printf("%d = - max int\n", mi);
	printf("char %c = 'a'\n", 'a');
	printf("hex %x = ff\n", 0xff);
	printf("hex %02x = 00\n", 0);
	printf("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf("%d %s(s)%", 0, "message");
	printf("\n");
	printf("%d %s(s) with %%\n", 0, "message");
	
    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf("%s", buf);
	
    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf("%s", buf);
	
    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf("%s", buf);
	
    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf("%s", buf);
	
    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf("%s", buf);
*/

done:
	return (int) 0;
};


/*
 * input:
 *     Coloca os caracteres digitados em um buffer, (string). Para depois 
 * comparar a string com outra string, que é um comando.
 * 
 * Histórico:
 *     Versão 1.0, 2015 - Essa rotina foi criada por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */
unsigned long input(unsigned long ch)
{   
	char c = (char) ch;  //Converte 'unsigned long' em 'char'.
	
    //Limite.
	if(prompt_pos >= PROMPT_SIZE){ 
	    printf("Buffer cheio!\n");	
	    return (unsigned long) 0; 
	};
 
	//
	// Trata o caractere digitado. 
	//
	
	switch(c)
	{
	    //Enter.	
		//case 0x1C:
		case VK_RETURN:
		    prompt[prompt_pos] = (char )'\0';
            goto input_done;			
		    break;

	    //Backspace.
		case 0x0E:
            if(prompt_pos <= 0)
			{ 
			    prompt_pos = 0;
				prompt[prompt_pos] = (char ) '\0';
				break; 
			};
		    
			//Apaga o anterior (no buffer).
			prompt_pos--;
			prompt[prompt_pos] = (char ) '\0';
			
			//Apaga o atual no Backbuffer.
			printf("%c",' ');
			
			//Apaga o anterior no Backbuffer.
			g_cursor_x--;
			g_cursor_x--;
			//printf("%c",' ');
			
			//Volta o cursor.
			//g_cursor_x--;
			break;
			
		//...	
		
        //Para qualquer caractere que não sejam os especiais tratados acima.		
		default:
		    prompt[prompt_pos] = c;
		    prompt_pos++;          //incrementa fila.
			putchar(c);
			//printf("%c",' ');
			//g_cursor_x--;
			break;
	};
	
input_more:	
	return 0;

input_done:	
    return VK_RETURN;	
};


//
// End.
//
