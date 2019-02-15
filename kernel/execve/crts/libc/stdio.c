/*
 * File: execve/crts/libc/stdio.c 
 *
 * Descrição:
 *     +Rotinas de input/output padrão.
 *     +Algumas rotinas de console.
 *
 * Environment:
 *     >>> Ring 0 <<<
 *
 *
 * @todo: Buffering and pipes.
 *        Priorizar operações com disco.
 * 
 * Credits:
 *     printf support - Georges Menie's tutorial.
 *     https://www.menie.org/georges/embedded/small_printf_source_code.html
 *     
 * History:
 *     2015 - Create by Fred Nora.
 *
 */
  
 
#include <kernel.h>


//Herdadas do Boot Loader.
// De onde vem isso ?? head.s
// @todo: Devemos chamar o módulo hal para obtermos esses valores.
//depois salvamos em variáveis internas usadas pela gui.
extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 


//
// Funções importadas.
//

extern void background();  //Assembly.
extern void refresh_screen();


/*
 *********************************************
 * fclose:
 *     Close a file. */

int fclose (FILE *stream){
	
	if ( (void *) stream == NULL )
	{	
	    return -1;		
	}else{
		
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
}


/*
 ********************************************************************
 * fopen:
 *     @field 2
 *     Open a file.
 *     
 *     #todo: 
 *     Mas já temos recursos para abrimos arquivos maiores 
 *     usando essa função. É só obtermos o tamanho do arquivo 
 *     e alocarmos um buffer do tamanho necessário
 */

FILE *fopen ( const char *filename, const char *mode ){
	
    unsigned long fileret;
	struct _iobuf *stream;
	
	//Buffer usado cara colocar a estrutura.
    unsigned char struct_buffer[1024];
	
	//Buffer para armazenar o arquivo que vamos abrir.
	char *file_buffer;		
	
	//buffer da estrutura.
	stream = (FILE *) &struct_buffer[0];	
	
	
	//#test
	//temos que fazer isso de um jeito melhor
	size_t s = (size_t) fsGetFileSize ( (unsigned char *) filename );


	/*
	 *usado para alocar mais páginas.
	Ret = (void*) allocPages(2);      //8KB. para imagem pequena.
	if( (void*) Ret == NULL ){
	    printf("Ret fail\n");
        goto fail;	
        //return NULL;		
	}
    */	
	
	//alocando apenas uma página.
	//4KB
	//Buffer do arquivo.
	//@todo: Deve ser maior. Do tamanho do arquivo.
	//Podemos usar outra rotina de alocação de página.
	
	//#todo:
	//já temos recursos para alocar memória para um buffer maior.
	//obs: Essa alocação vai depender do tamanho do arquivo.
	
	//stream->_cnt = PROMPT_MAX_DEFAULT;
	stream->_cnt = s;	
	
	//file_buffer = (char *) newPage();
	
	file_buffer = (char *) malloc (s);
	
	if ( (char *) file_buffer == NULL )
	{
		printf("fopen: file_buffer");
		die();
	}	
	  

	stream->_base = file_buffer;
	stream->_ptr = stream->_base;
	
	stream->_file = 0;
	stream->_tmpfname = (char *) filename;	
	
	fsUpdateWorkingDiretoryString ( (char *) filename );
	
	int i;
	if ( current_target_dir.current_dir_address == 0 )
	{
	    printf("sys_read_file2: current_target_dir.current_dir_address fail \n");
		
		//reset.
		current_target_dir.current_dir_address = VOLUME1_ROOTDIR_ADDRESS;
		
		for ( i=0; i< 11; i++ )
		{
			current_target_dir.name[i] = '\0';
		}		
		
		//return -1;
		return (FILE *) 0;
	}
	
	// Loading file.
				
    fileret = fsLoadFile ( VOLUME1_FAT_ADDRESS, 
			      current_target_dir.current_dir_address,  
	              (unsigned char *) current_target_dir.name, 
	              (unsigned long) stream->_base );				
	
	if ( fileret != 0 )
	{	
		printf("fopen: fsLoadFile fail\n");
		
		stream = NULL;	
		return NULL;
	}
	
	//...

	return (FILE *) stream; 	
}


//#todo
size_t fread (void *ptr, size_t size, size_t n, FILE *fp)
{
    return -1;
}

//#todo
size_t fwrite (const void *ptr, size_t size, size_t n, FILE *fp)
{
	return -1;
}

/* 
 * fflush: 
 * Salva o buffer no arquivo associado a ele.
 * e limpa o buffer. 
 * Se for NULL então faz isso para todas stream abertas.
 * retorna 0 se funcionar e retorna EOF se falhar.
 */

int fflush ( FILE *stream ){
	
	register int i = 0;
	
	if ( (void *) stream == NULL )
	{
		//#todo: 
		//limpa todas as streams abertas.
		return (int) (-1);
	}
		
	// Limits.
    // Se o buffer tiver vazizo ou for maior que o limite.	
	if ( stream->_bufsiz == 0 || stream->_bufsiz > BUFSIZ )
	{
		
		printf("fflush: buffer size limits\n");
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
	    //limpa
		stream->_base[i] = (char) '\0';	
	}
    
	stream->_ptr = stream->_base;     //walk	
    stream->_bufsiz = BUFSIZ; 		  //tamanho
	stream->_cnt = stream->_bufsiz;   //quanto falta é igual ao tamanho.
	
	
	return 0;
}









/*
 ************************************************************************
 * scroll:
 *     Isso pode ser útil em full screen e na inicialização do kernel.
 *
 * *Importante: Um (retângulo) num terminal deve ser o lugar onde o buffer 
 * de linhas deve ser pintado. Obs: Esse retãngulo pode ser configurado através 
 * de uma função.
 *     Scroll the screen in text mode.
 *     Scroll the screen in graphical mode.
 *     @todo Poderiam ser duas funções: ex: gui_scroll(). 
 *    
 * * IMPORTANTE
 *   O que devemos fazer é reordenar as linhas nos buffers de linhas
 *     para mensagens de texto em algum terminal.
 * 
 * @todo: Ele não será feito dessa forma, termos uma disciplica de linhas
 * num array de linhas que pertence à uma janela.
 *
 * @todo: Fazer o scroll somente no stream stdin e depois mostrar ele pronto.
 *
 */

void scroll (void){
	
	// #suspenso

	// Isso funciona para a tela inteira.
    // mas temos que criar um scroll de janela.	
	
/*	
	
    unsigned short i;
    unsigned short j;


	//indice para o backbuffer.
	int Start, End;
	int Source, Dest;
	
	// ponteiros usados no modo gráfico.
	unsigned char *backbuffer = (unsigned char *) BACKBUFFER_BASE;
	
	// ponteiros usados no modo texto.
	
	//Início da tela e início da segunda linha.
	unsigned short *p1 = (unsigned short *) SCREEN_START;
    unsigned short *p2 = (unsigned short *) (SCREEN_START + 2 * SCREEN_WIDTH);

	//salvar cursor.
	unsigned long OldX, OldY;
	
	
	//
	// Se estamos em Modo gráfico (GUI).
    //

//graphics_mode:
	
	if ( VideoBlock.useGui == 1 )
	{
	
		//Modificar o backbuffer. BACKBUFFER_BASE
        
		//mover o backbuffer começando da segunda linha.
		//exclui a primeira linha e a segunda linha será a nova primeira.
		
		//so que na verdade isso deve ser feito apenas para a 
		//janela onde o texto está e não para o backbuffer inteiro.
		//por enquanto fica assim.
		
		//#bugbug: 
		//Valores determinados para width e height.
		//Precisamos pegar valores salvos.
		
		Start = 0;
		Source = Start+(3*800*8);  //Começa da segunda linha.
		Dest = 0;                  //destino o início do backbuffer.
		
		End = (3*800)*600;       //termina ao fim de 600 linhas.
		
		//copy. 
		//Contagem do total a ser transferido.
		for ( Start=0; Start < End; Start++ ){
			
            backbuffer[Start] = backbuffer[Source];
            Source++;    			
		};
		
        //Limpa a última linha.
		
		//salva cursor
		OldX = g_cursor_x;
		OldY = g_cursor_y;
		
		//cursor na ultima linha.
		//g_cursor_x = 0;
		g_cursor_x = g_cursor_left;
		g_cursor_y = (g_cursor_bottom-1);
		
		for ( i = g_cursor_x; i < g_cursor_right; i++ ){
		    _outbyte(' ');    	
		};
	
		// Reposiciona o cursor na última linha.	
		
		g_cursor_x = g_cursor_left;
		g_cursor_y = OldY;
		
		refresh_screen();
		goto done;
	};

	// Se estavermos em modo texto.
	
//text_mode:
	
	if ( VideoBlock.useGui == 0 )	
	{
	    //24 vezes.
        for ( i=0; i < (SCREEN_HEIGHT -1); i++ )
	    {
	        //80 vezes
            for ( j=0; j < SCREEN_WIDTH; j++ ){
                *p1++ = *p2++;
		    };
			//Nothing.
		};
	
	    //80 vezes.
        for ( i=0; i < SCREEN_WIDTH; i++ ){
		    *p1++ = 0x07*256 + ' '; 
	    };
		
		//Nothing.
		goto done;
    };
	
    //Nothing.	
	
*/
	
done:
	return;
};


/*
 * kclear:
 *     Limpa a tela em text mode.
 *     # isso não faz parte da lib c, mudar para 
 *     o field 3.
 */

int kclear (int color) {

	int Status = -1;
	
	if ( VideoBlock.useGui == 1 )
	{
		backgroundDraw ( COLOR_BLUE );

		g_cursor_x = 0;
		g_cursor_y = 0;

		Status = 0;

	}else{
		Status = -1;
	};

	return Status;
}


/* kclearClientArea: */

int kclearClientArea (int color){
	
    return (int) kclear (color);	
}


/*
 * kprint:
 * #bugbug: Nao temos mais suporte a modo texto. */

int kprint ( char *message, unsigned int line, int color ){	
    return (int) -1; 
}



/*
 *==============================================================================
 *  ==== Segue aqui o suporte a função 'printf' ====
 *
 * #obs:
 * Em user mode temos uma modelo mais tradiciona de printf,
 * talvez seja bom implementa-lo aqui tambem.
 */


/*
 *****************************
 * prints:
 *     Rotina de suporta a printf. */

static int prints ( char **out, const char *string, int width, int pad ){
	
	register int pc = 0, padchar = ' ';

    if (width > 0) 
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
	
	for ( ; *string; ++string ){
		
		printchar(out, *string);
		++pc;
	};
	
	for ( ; width > 0; --width ){
		
		printchar(out,padchar);
		++pc;
	};

//done:	
	return (int) pc;
};


/*
 ****************************************
 * printi:
 *     Rotina de suporta a printf.
 */

static int 
printi ( char **out, 
         int i, 
		 int b, 
		 int sg, 
		 int width, 
		 int pad, 
		 int letbase )
{
	char print_buf[PRINT_BUF_LEN];
	register char *s;
	register int t, neg = 0, pc = 0;
	register unsigned int u = i;

	if ( i == 0 ) 
	{
		print_buf[0] = '0';
		print_buf[1] = '\0';
		return prints (out, print_buf, width, pad);
	};
	
	if ( sg && b == 10 && i < 0 ){
		
		neg = 1;
		u = -i;
	}

	s = ( print_buf + ( PRINT_BUF_LEN -1 ) );
	
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
		}else {
			
			*--s = '-';
		};
	};

	// #obs: retorna pc + o retorno da função.
	
	return (int) pc + prints(out, s, width, pad);
};


/*
 ****************************************
 * print:
 *     Rotina de suporta a printf.
 *
 */
static int print ( char **out, int *varg ){
	
	register int width, pad;
	register int pc = 0;
	register char *format = (char *) (*varg++);
	char scr[2];

	for( ; *format != 0; ++format ) 
	{
		if ( *format == '%' ) 
		{
			++format;
			width = pad = 0;
			
			if ( *format == '\0' ) 
			    break;
			
			if ( *format == '%' ) 
			    goto out;
			
			if ( *format == '-' ) 
			{
				++format;
				pad = PAD_RIGHT;
			};
			
			while ( *format == '0' ) 
			{
				++format;
				pad |= PAD_ZERO;
			};
			
			for ( ; *format >= '0' && *format <= '9'; ++format ){
				
				width *= 10;
				width += *format - '0';
			};
			
			if ( *format == 's' ) 
			{
				register char *s = *((char **)varg++);
				pc += prints (out, s?s:"(null)", width, pad);
				continue;
			}
			
			if ( *format == 'd' ){
				pc += printi (out, *varg++, 10, 1, width, pad, 'a');
				continue;
			}
			
			if ( *format == 'x' ){
				pc += printi (out, *varg++, 16, 0, width, pad, 'a');
				continue;
			}
			
			if ( *format == 'X' ){
				pc += printi (out, *varg++, 16, 0, width, pad, 'A');
				continue;
			}
			
			if ( *format == 'u' ){
				pc += printi (out, *varg++, 10, 0, width, pad, 'a');
				continue;
			}
			
			if ( *format == 'c' ) 
	        {
				/* char are converted to int then pushed on the stack */
				scr[0] = *varg++;
				scr[1] = '\0';
				pc += prints (out, scr, width, pad);
				continue;
			}
		
		}else{
			
		    out:
			    printchar (out, *format);
			    ++pc;
		};
	};
	
	if (out) 
        **out = '\0';
	
	return (int) pc;
};


/*
 ***************************************************
 * printf:
 *     @field 2
 *     The printf function.
 *     Assuming sizeof(void *) == sizeof(int).
 *
 * Em user mode temos uma modelo mais tradiciona de printf,
 * talvez seja bom implementa-lo aqui tambem.
 */

int printf ( const char *format, ... ){

	register int *varg = (int *) (&format);

	return (int) print ( 0, varg );
}


/*
 * puts: */

int puts ( const char *str ){
	
	//provisório ...
	return (int) printf ("%s",str);
}


/*
 *************************************************
 * panic:
 *     # isso não faz parte da lib c, poderia ir para o @field 3.
 *     Kernel panic function.
 *     @todo: Esse função deve retornar void.
 *     Essa função faz parte da libC ??
 *     Essa rotina deveria ir para outro lugar.
 *     provavelmente em /sm
 */
 
void panic ( const char *format, ... ){
	
	register int *varg = (int *)(&format);
	
	printf("crts-libc-stdio-panic: KERNEL PANIC\n");
		
    switch ( VideoBlock.useGui )
    {
		//text mode
		case 0:
	        //kclear(0);
	        print(0,varg);		
		    break;
		
		//graphics mode
		case 1:
	        //backgroundDraw(COLOR_BLACK);
		    //printf("crts-libc-stdio-panic: KERNEL PANIC\n");
		    print(0,varg);		
		    break;

        default:
	        //backgroundDraw(COLOR_BLACK);
		    //printf("crts-libc-stdio-panic: KERNEL PANIC\n");
		    print ( 0, varg );			
            break; 		
	};
	
    die();	
}


/*
 **********************************************************************
 * sprintf:
 *     @field 2
 *     int sprintf ( char * str, const char * format, ... );
 *     Composes a string with the same text that would be 
 * printed if format was used on printf, 
 * but instead of being printed, the content is stored 
 * as a C string in the buffer pointed by str.
 */

int sprintf ( char *str, const char *format, ... ){
		
    register int *varg = (int *) (&format);
	return (int) print (&str, varg);
}


/*
 ************************************************
 * fprintf:
 *     @field 2
 */

int fprintf ( FILE *stream, const char *format, ... ){
	
    register int *varg = (int *) (&format);
	
	if ( (void*) stream != NULL )
	{
		//??
		//@todo Error. O erro deveria retornar 1.
        return 0;   		
	};		

	char *str = (char *) stream->_ptr;
	
	return (int) print (&str, varg);	
}

/*
 #opçao
int fprintf ( FILE *stream, const char *format, ... ){
	
	int size;
	
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
		
	} else {
		
		size = (int) stdio_strlen (format);
		
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

*/



/*
 ********************************
 * fputs:      
 */

int fputs ( const char *str, FILE *stream ){
	
	int size;
	
	if ( (void *) stream == NULL )
	{
		return (int) (-1);
		
	} else {
		
		//size = (int) stdio_strlen (str);
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
 * ungetc:
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



long ftell (FILE *stream)
{
	if ( (void *) stream == NULL )
	{
		return (long) 0; //-1
	}	
	
    return (long) (stream->_ptr - stream->_base);	
};


int fileno ( FILE *stream ){

	if ( (void *) stream == NULL )
	{
		return (long) -1; 
	}	
	return (int) stream->_file;  //fd
};


/*
 *********************************
 * fgetc:
 *     #precisamos exportar isso como serviço. (#136)
 */

int fgetc ( FILE *stream ){
	
    int ch;	
 
	if ( (void *) stream == NULL )
	{
		printf ("#debug: fgetc: stream struct fail\n");
		refresh_screen();
		
		return (int) (-1);
		
	} else {
		
		//#fim.
		//cnt decrementou e chegou a zero.
		//Não há mais caracteres disponíveis entre 
		//stream->_ptr e o tamanho do buffer.
		
		if ( stream->_cnt <= 0 )
		{
			stream->_flag = (stream->_flag | _IOEOF); 
			stream->_cnt = 0;
			
		    //printf ("#debug: fgetc: $\n");
			
			//isso funciona, significa que a estrutura tem ponteiro e base validos.
			//printf("show fgetc:: %s @\n", stream->_base );
		    //refresh_screen();			
			
			return (int) (-1);
		};
		
		//#debug
		//n~ao podemos acessar um ponteiro nulo... no caso endereço.
		if ( stream->_ptr == 0 )
		{
			printf ("#debug: fgetc: stream struct fail\n");
		    refresh_screen();
			return (int) (-1);
			
		}else{
			
		    //pega o char
		    ch = (int) *stream->_ptr; 	
				
			stream->_ptr++;
		    stream->_cnt--;
			
		    return (int) ch;				
		
		}
		//fail
	};
	
    printf ("#debug: fgetc: $$\n");
	refresh_screen();				
	
    return (int) (-1);	
};



/*
 *********************************
 * feof:
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


//(since C99)	
//int fscanf( FILE *restrict stream, const char *restrict format, ... );
//(until C99)
int fscanf (FILE *stream, const char *format, ... ){
	
	printf ("fscanf: todo \n");
    return -1;
}


/*
int vfprintf ( FILE *stream, const char *format, stdio_va_list argptr );
int vfprintf ( FILE *stream, const char *format, stdio_va_list argptr ){
}
*/


void rewind ( FILE * stream ){
	
	if ( (void *) stream == NULL )
		return;
	
    //apota par o início do arquivo.
	//#bugbug: isso vai sobrescrever
	//as coisas que ainda estão no arquivo;
	
	stdin->_ptr = stdin->_base;
    stdin->_bufsiz = BUFSIZ; 		
	stdin->_cnt = stdin->_bufsiz;		
}








/*
 *************************************************************
 * printchar:
 *     Coloca o caractere na string ou imprime.
 * Essa função chama uma rotina que deverá tratar o caractere e em seguida 
 * enviá-lo para a tela.
 * Essa rotina é chamada pelas funções: /print/printi/prints.
 */

static void printchar (char **str, int c)
{
	if (str){
		
		**str = c;
		++(*str);
		
	}else (void) putchar (c);
}


/*
 ********************************************************************
 * putchar:
 *     Put a char on the screen. (libC).
 *     Essa rotina chama uma rotina de tratamento de caractes, somente
 * depois é que o caractere será enviado para a tela.
 *     Essa rotina é chamada pelas funções: /printchar/input/.
 */

int putchar (int ch){ 
   
    //Em cedge.c
    outbyte (ch);
    
	return (int) ch;    
}


/*
 * getchar:
 *    @todo isso deve er oferecido como serviço pelo kernel.
 *
 * The getchar function is equivalent to getc with stdin as the value of the stream argument.
 */
/* 
int getchar()
{
	//terminal.h
	
	
	//erro
	if( teminalfeedCHStatus != 1 )
	{
		return (int) -1;
	}
	
	
done:
    teminalfeedCHStatus = 0;
	return (int) teminalfeedCH;
}
*/


/*
 essa função é legal ... habilitar quando der.
 
void stdio_ClearToEndOfLine();
//limpa com caracteres em branco até antes da posição do cursor.
void stdio_ClearToEndOfLine()
{
    unsigned u;
    unsigned long OldX, OldY;
    
    OldX = g_cursor_x;
	OldY = g_cursor_y;
	
	//de onde o cursor está até o fim da linha.
	for( u = g_cursor_x; u < g_cursor_right; u++ )
	{
       _outbyte(' ');
    }
	
    g_cursor_x = OldX;
	g_cursor_y = OldY;

}
*/


/*
 essa função é legal ... habilitar quando der.
 
void stdio_ClearToStartOfLine();
//limpa com caracteres em branco até antes da posição do cursor.
void stdio_ClearToStartOfLine()
{
    unsigned u;
    unsigned long OldX, OldY;
    
    OldX = g_cursor_x;
	OldY = g_cursor_y;
	
	//Início da linha.
    g_cursor_x = 0;
	g_cursor_y = OldY;	
	
	//de onde o cursor está até o fim da linha.
	for( u = g_cursor_x; u < g_cursor_right; u++ )
	{
       _outbyte(' ');
    }
	
    g_cursor_x = OldX;
	g_cursor_y = OldY;

}
*/


/*
 * printf_main:
 *     #todo: Esse teste de biblioteca pode pertencer à framework,
 * deve ir para o @field 3.     
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
/*	 
int printf_main (void){
	
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


done:
	return (int) 0;
};
*/


/*
 ******************************************************************
 * input:
 *     Coloca os caracteres digitados em um buffer, (string). 
 * Para depois comparar a string com outra string, que é um comando.
 * 
 *     Devemos nos certificar que input(.) não imprima nada.
 *
 * History:
 *     2015 - Created by Fred Nora.
 *     ...
 */

unsigned long input ( unsigned long ch ){
	
	int i;
	
	// Converte 'unsigned long' em 'char'.
	char c = (char) ch;  	

    if( g_inputmode == INPUT_MODE_LINE )	
    {
        //Limite.
	    if(prompt_pos >= PROMPT_SIZE)
	    {
	        printf("input: INPUT_MODE_LINE full buffer!\n");	
	        refresh_screen();
			return (unsigned long) 0; 
	    };
    };
	
	if(g_inputmode == INPUT_MODE_MULTIPLE_LINES )
	{
		//tem que ter o tamanho de um arquivo.
		if(prompt_pos >= PROMPT_SIZE)
		{
	        printf("input: INPUT_MODE_MULTIPLE_LINES full buffer\n");	
	        refresh_screen();
			return (unsigned long) 0; 			
		}
	};
	
	
	// Trata o caractere digitado. 
	
	switch (c)
	{
		
	    //Enter.	
		//+se for modo comando devemos finalizar com zero.
		//+se for modo texto, devemos apenas incluir os caracteres \r \n.		
		//case 0x1C:
		case VK_RETURN:
            //modo linha 
			if(g_inputmode == INPUT_MODE_LINE )
			{
			    prompt[prompt_pos] = (char )'\0'; //end of line.
			    //@todo: ?? ldiscCompare();
				//o compare está no aplicativo.
	            for(i=0; i<PROMPT_MAX_DEFAULT;i++)
	            {
		            prompt[i] = (char) '\0';
		            prompt_out[i] = (char) '\0';
		            prompt_err[i] = (char) '\0';
	            };
                prompt_pos = 0;				
				goto input_done;
			};
            //modo multiplas linhas 
		    if(g_inputmode == INPUT_MODE_MULTIPLE_LINES ){
			    prompt[prompt_pos] = (char )'\r';
                prompt_pos++;
				prompt[prompt_pos] = (char )'\n';
				prompt_pos++;				
			};			
		    break;

	    //Backspace.
		case 0x0E:
		
            if ( prompt_pos <= 0 ){
				
			    prompt_pos = 0;
				prompt[prompt_pos] = (char ) '\0';
				break; 
			}
		    
			//Apaga o anterior (no buffer).
			prompt_pos--;
			prompt[prompt_pos] = (char ) '\0';
			break;
			
		//...	
		
        //Para qualquer caractere que não sejam os especiais tratados acima.		
		default:
		    prompt[prompt_pos] = c;
		    prompt_pos++;          //incrementa fila
			break;
	};
	
input_more:	
	return 0;
input_done:	
    return VK_RETURN;	
};



/*
 *****************
 * stdioInitialize:
 *     Inicializando stdio pertencente ao kernel base.
 *     Inicializa as estruturas do fluxo padrão.
 *     Quem chamou essa inicialização ?? Em que hora ??
 *
 * #bugbug: Pelo jeito somente depois dessa inicialização é que temos mensagens 
 * com printf decentes. Então a inicialização do kernel precisa disso.
 * >> precisamos antecipar essa inicilização. Mas ela precisa ser depois da
 * inicialização da paginação.
 */
 
int stdioInitialize (){
	
	int Status = 0;
	
	int i;

	// Buffers para as estruturas.
	unsigned char *buffer0;
	unsigned char *buffer1;
	unsigned char *buffer2;
	
	int cWidth = get_char_width ();
	int cHeight = get_char_height ();
	
	if ( cWidth == 0 || cHeight == 0 )
	{
		panic ("stdioInitialize: Char info");
	}	
	

	// #bugbug:
	//  4KB alocados para cada estrutura. Isso é muito.
	//  Mas ao mesmo tempo estamos economizando o heap 
	//  usado pelo malloc.
	//  Podemos alocar 4KB para o buffer. 'prompt'
	
	
	// Alocando uma página para cada buffer.
	// 4KB size.
	// #importante
	// Obs: Essas páginas são alocadas em user mode.
	
	
	//4KB
	buffer0 = (unsigned char *) newPage(); 
	if( (unsigned char *) buffer0 == NULL )
	{
		printf("buffer0\n");
        goto fail;
	}
	
	//4KB
	buffer1 = (unsigned char *) newPage();
	if( (unsigned char *) buffer1 == NULL )
	{
		printf("buffer1\n");
        goto fail;
	}
	
	//4KB
	buffer2 = (unsigned char *) newPage();
	if( (unsigned char *) buffer2 == NULL )
	{
		printf("buffer2\n");
        goto fail;
	}
	
	//
	// Alocando memória para o fluxo padrão do 
	// processo kernel.
	// Estamos apenas alocando memória para a estrutura.
	//
	
	stdin = (FILE *) &buffer0[0];	
	stdout = (FILE *) &buffer1[0];	
	stderr = (FILE *) &buffer2[0];	
	  

    // Configurando a estrutura de stdin. 
	stdin->_base = &prompt[0];
	stdin->_ptr =  &prompt[0];
	stdin->_cnt = PROMPT_MAX_DEFAULT;
	stdin->_file = 0;
	stdin->_tmpfname = "k-stdin";
	//...

    // Configurando a estrutura de stdout.
	stdout->_base = &prompt_out[0];
	stdout->_ptr = &prompt_out[0];
	stdout->_cnt = PROMPT_MAX_DEFAULT;
	stdout->_file = 1;
	stdout->_tmpfname = "k-stdout";
	//...
	
    // Configurando a estrutura de stderr.
	stderr->_base = &prompt_err[0];
	stderr->_ptr =  &prompt_err[0];
	stderr->_cnt = PROMPT_MAX_DEFAULT;
	stderr->_file = 2;
	stderr->_tmpfname = "k-stderr";	
	//...
	
	
	//
    // #importante
    // Salvando os ponteiros na lista de arquivos.	
	//
	Streams[0] = (unsigned long) stdin;
	Streams[1] = (unsigned long) stdout;
	Streams[2] = (unsigned long) stderr;
	
	//Os próximos são inicializados em fs.c
	//Streams[3] volume0 root dir (vfs) 
	//Streams[4] volume1 root dir (boot volume)
    //Streams[5] volume2 root dir  (system volume)	 
	//...  	
	
	
	
    //Configurando o array global para ser o 
    //mesmo que o array local.	
	gStreams = (unsigned long *) &Streams[0];
	
	//Número de streams no array global
	g_nstream = NUMBER_OF_FILES;
	
	//
	// Flag para o tipo de input.
	// # Multiplas linhas.
	//
	
	g_inputmode = INPUT_MODE_MULTIPLE_LINES;
	
	
	//  ## Cursor ##
	
	// Inicializa o cursor com margens bem abertas.	
	
	g_cursor_left = (0);
	g_cursor_top = (0); 

	//@todo:
	//Isso é complicado.
	//Temos que pegar esses valores.
	//g_cursor_width = ?;
	//g_cursor_height = ?;	
	
	//#bugbug 
	//#todo: precisamos as dimensões do char com base na fonte antes de tudo.
	//?? Talvez aqui devamos inicializar a fonte e as dimensões de char..
	//pois estamos na inicialização da libc. Mas isso ja pode ter acontecido na 
	//inicialização do kernel, quando era necessário algum tipo de fonte para 
	//mensagens de debug.
	//?? será que já configuramos as dimensões da tela. Devemos usar as variáveis.
	//?? se as dimensões da tela foram configuradas na inicialização,
	//então podemos usar as variáveis aqui.
	
	//precisamos saber as dimensões da tela e do char.
	//g_cursor_right = (800/8);
	//g_cursor_bottom = (600/8);
	
	g_cursor_right = (SavedX/cWidth);
	g_cursor_bottom = (SavedY/cHeight);
	
	
	
    //x e y.
	g_cursor_x = g_cursor_left; 
	g_cursor_y = g_cursor_top;  		
	
	// Default color.
	// Não sabemos se o esquema de cores do sistema já
	// está configurado, então usaremos uma cor padrão.
	// A QUALQUER HORA O KERNEL PODE ESCREVER NO TERMINAL 
	// E PARA USARMOS JANELAS PRETAS TEMOS QUE CONFIGURA A 
	// COR DA FONTE, ENTÃO JANELAS TERÃO FONTE PRETA.
	g_cursor_color = COLOR_TERMINALTEXT;
	
	
	//
	// #importante:
	// Preenche os arquivos do fluxo padrão do kernel base
	// com 'zeros'.
	//

	for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
		
		prompt[i] = (char) '\0';
		prompt_out[i] = (char) '\0';
		prompt_err[i] = (char) '\0';
	};

	// Inicializa o deslocamento dentro do arquivo de entrada.
	// #bugbug @todo: Poderíamos ter posicionamento dentro 
	// dos 3 arquivos. Mas isso reflete apenas o posicionamento 
	// dentro de stdin por enquanto.
	
    prompt_pos = 0;	
	
	// Done !

    return (int) 0;	
	
fail:
    panic ("crts-libc-stdio-stdioInitialize: fail\n");
};


//
// End.
//
