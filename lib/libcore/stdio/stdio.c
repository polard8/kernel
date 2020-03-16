/*
 * File: stdio.c 
 *
 * Descrição:
 *     Rotinas de input/output para User Mode.
 *     Standard C language. C99.
 *
 * Environment:
 *     >>> Ring 3 <<<
 *
 * Credits:
 *     printf: https://www.menie.org/georges/embedded/small_printf_source_code.html
 *     stdio_fntos: Luiz Felipe
 *
 * History:
 *     2015 - Created.
 *     2015~2019 - Revision. 
 */
 
// See:
// http://kirste.userpage.fu-berlin.de/chemnet/use/info/libc/libc_7.html 


#include <limits.h>
//#include <string.h>


#include <stdio.h>
#include <types.h> 
#include <stdarg.h> 

#include <stdio_ext.h>

#include <stddef.h>
//#include <stdlib.h> 

#include <ctype.h>

//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

//system calls.
#include <stubs/gramado.h> 


//usada por uma função nesse documento. 
char **environ;

//#importante: Tem que inicializar isso.
static int __libc_output_mode = 0;
static int terminal___PID;


/*
int putchar(int c) {
  return fputc(c,stdout);
}
*/


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

//interna; Mudar o nome
static size_t stdio_strlen (const char *s);




//
// ===============================================================
//
/*
int
__SendMessageToProcess ( int pid, 
                          unsigned long window, 
                          int message,
                          unsigned long long1,
                          unsigned long long2 );
int
__SendMessageToProcess ( int pid, 
                          unsigned long window, 
                          int message,
                          unsigned long long1,
                          unsigned long long2 )
{
	unsigned long message_buffer[5];

	
    if (pid<0)
		return -1;
	
	message_buffer[0] = (unsigned long) window;
	message_buffer[1] = (unsigned long) message;
	message_buffer[2] = (unsigned long) long1;
	message_buffer[3] = (unsigned long) long2;
	//...

	return (int) system_call ( 112 , (unsigned long) &message_buffer[0], 
	                 (unsigned long) pid, (unsigned long) pid );
}
*/
//
// ===============================================================
//




// stdio_atoi:
// Talvez isso possa ir para o topo do 
// arquivo para servir mais funções.

int stdio_atoi (char *s){

    int rv=0; 
    char sign = 0;

    // Skip till we find either a digit or '+' or '-'.
    
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


    if (sign)
    { 
        return (-rv);
    }else{ 
        return (rv);
    };

    //     return (sign ? -rv : rv);
}


// stdio_fntos:
// rotina interna de support.
// isso deve ir para bibliotecas depois.
// não tem protótipo ainda.
// Credits: Luiz Felipe

void stdio_fntos (char *name){

    int  i, ns = 0;

    char ext[4];


    ext[0] = 0;
    ext[1] = 0;
    ext[2] = 0;
    ext[3] = 0;


    //const char ext[4];

    //Transforma em maiúscula enquanto não achar um ponto.

    while ( *name && *name != '.' )
    {
        if ( *name >= 'a' && *name <= 'z' )
            *name -= 0x20;

        name++;
        ns++;
    };


    // Aqui name[0] é o ponto.
    // Então constrói a extensão.

    for ( i=0; i < 3 && name[i+1]; i++ )
    {
        //Transforma uma letra da extensão em maiúscula.

        //if (name[i+1] >= 'a' && name[i+1] <= 'z')
        //    name[i+1] -= 0x20;

        //ext[i] = name[i+1];


        // #testando
        //Se não for letra então não colocamos no buffer de extensão;

        if (name[i+1] >= 'a' && name[i+1] <= 'z')
        {
            name[i+1] -= 0x20;
            ext[i] = name[i+1];
        }
    };


	// Acrescentamos ' ' até completarmos as oito letras do nome.


    while (ns < 8)
    {
        *name++ = ' ';
        ns++;
    };

	//Acrescentamos a extensão

    for (i=0; i < 3; i++)
        *name++ = ext[i];


    *name = '\0';
}



void debug_print (char *string)
{
    gramado_system_call ( 289, 
        (unsigned long) string,
        (unsigned long) string,
        (unsigned long) string );
}



//#todo
//https://linux.die.net/man/3/remove
int remove (const char *pathname)
{
    return (int) (-1);
}


/*linux klibc style*/
/*
static __inline__ int fclose(FILE *__f)
{
  extern int close(int);
  return close(fileno(__f));
}
*/



/*
 ****************************************
 * fclose:
 *     Close a file.
 *     If work, return 0. 
 */

int fclose (FILE *stream){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 232, 
                     (unsigned long) stream, 
                     (unsigned long) stream, 
                     (unsigned long) stream ); 
}


/*
 ***************************************
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

FILE *fopen ( const char *filename, const char *mode )
{
    FILE *__stream;
    
    
    __stream = (FILE *) malloc( sizeof(FILE) );
    
    if ( (void *) __stream == NULL )
        return NULL;
        
    //
    // size
    //
    
    stdio_fntos( (char *) filename);
    
    // get file size
    size_t s = (size_t) gramado_system_call ( 178, 
                            (unsigned long) filename,
                            0,
                            0 );
    
    
    if ( s <= 0 || s > 1024*1024 )
    {
        printf ("fopen: size\n");
        return NULL;
    }
    
    // endereço desejando.
    // ring 3.
    unsigned long address = (unsigned long) malloc(s);
    
    if (address == 0)
    {
        printf ("fopen: address\n");
        return NULL;
    }


    // load the file into the address.
    
    int status = -1;
    
    //IN: service, name, address, 0, 0 
    status = (int) gramado_system_call( 3, 
                      (unsigned long) filename, 
                      (unsigned long) address,  
                      0 );

    if (status < 0)
    {
        printf ("fopen: Couldn't load the file\n");
        return NULL;
    }
    

    //#todo    
    __stream->_file = -1;    

    //base.
    __stream->_base = (unsigned char *) address; 
    __stream->_p = __stream->_base;
        
    // size
    __stream->_lbfsize = (int) s;   
    __stream->_cnt = __stream->_lbfsize;
    
    

    // retornar a stream que criamos aqui. 
    
    return (FILE *) __stream;
}









/*
 * creat:
 *     Linux klibc style.
 */

int creat (const char *pathname, mode_t mode)
{
    return open (pathname, O_CREAT|O_WRONLY|O_TRUNC, mode);
}



/*
 *****************************************
 * scroll:
 *     Scroll the screen in (text mode).
 *     @todo: Mudar para tmScroll(void);
 *     @todo: Criar gmScroll(void) talvez;
 *     @todo: Essa rotina precisa ser revisada e aprimorada.
 *
 *     #todo: Talvez deva levar em conta o modo de operação.
 *            Se estamos ou full screen ou não.
 */

void scroll (void){

	//Início da tela.
    unsigned short *p1 = (unsigned short *) SCREEN_START;

	//Início da segunda linha.
    unsigned short *p2 = (unsigned short *) (SCREEN_START + 2 * SCREEN_WIDTH);
    unsigned short i, j;


	// Linhas.
	// Usa o valor default se passar dos limites.

    if ( g_rows == 0 || g_rows >= SCREEN_MAX_HEIGHT )
    {
        g_rows = SCREEN_HEIGHT;
    }


	// 24 vezes.

    for ( i=0; i < g_rows -1; i++ )
    {
	    //80 vezes.
		
		//Se a variável nao foi inicializada, usar valor default.
        
        if (g_columns == 0 || g_columns >= SCREEN_MAX_WIDTH)
        { 
            g_columns = SCREEN_WIDTH;
        }

		//modo texto
		//if(g_using_gui == 0)
		//{
		//    for( j=0; j < g_columns; j++ ){
		//        *p1++ = *p2++;
		//    };
		//};


		// modo gráfico.

        if (g_using_gui == 1)
        {

            for ( j=0; j < g_columns; j++ )
            {
                //*p1++ = *p2++;
                //@todo:
            };
        }
    };


	// Limpando a última linha.

	// modo gráfico.

    if (g_using_gui == 1)
    {
        for ( i=0; i < g_columns; i++ )
        { 
            //*p1++ = 0x07*256 + ' ';
            // @todo:
        };    
    }
}


/*musl style*/
/*
size_t __stdio_read(FILE *f, unsigned char *buf, size_t len)
{
	return __syscall_read(f->fd, buf, len);
}
*/

/*musl style*/
/*
size_t __stdio_write(FILE *f, const unsigned char *buf, size_t len)
{
	const unsigned char *stop = buf+len;
	ssize_t cnt = 1;
	for (; buf<stop && (cnt=__syscall_write(f->fd, buf, len))>0; buf+=cnt);
	return len-(stop-buf);
}
*/


/* Write the string in S and a newline to stdout.  */
/*glibc style.*/
//int DEFUN( puts, (s), CONST char *s)
/*
int puts ( const char *str )
{
	// Coloca uma string no stdout.
    return ( fputs ( s, stdout ) || putchar ('\n') == EOF ? EOF : 0 );
}
*/


/*musl style*/
/*
int puts(const char *s)
{
	return -(fputs(s, stdout) < 0 || putchar('\n') < 0);
}
*/


/*linux klibc style*/
/*
int puts(const char *s)
{
  if ( fputs ( s, stdout ) < 0 )
    return -1;

  return _fwrite ("\n", 1, stdout);
}
*/


/*uClib style*/
/*
int puts(const char *str)
{
	int n;

   // Let next fputc handle EOF or error. 
	n = fputs (str, stdout);	
	
	// Don't use putc since we want to
	// fflush stdout if it is line buffered.
	
	if (fputc('\n', stdout) == EOF) 
	{  
		return EOF;				 
	}
	
	return n + 1;
}
*/
	

/*
int puts(const char *str)
{
    int err = fputs(str, stdout);
    if (err >= 0)
        err = fputc('\n', stdout);
    return err;
}
*/










/*linux klibc style*/
/*
size_t _fread (void *buf, size_t count, FILE *f)
{
  size_t bytes = 0;
  ssize_t rv;
  char *p = buf;

  while ( count ) 
  {
    rv = read(fileno(f), p, count);
	  
    if ( rv == -1 ) {
		
      if ( errno == EINTR )
	continue;
      else
	break;
		
    } else if ( rv == 0 ) {
      break;
    }

    p += rv;
    bytes += rv;
    count -= rv;
  }

  return bytes;
}
*/


/*linux klibc style*/
/*
size_t fread (void *ptr, size_t size, size_t nmemb, FILE *f)
{
    return _fread (ptr, size*nmemb, f)/size;
}
*/



/*
 ************************
 * fread:
 *
 */

size_t fread (void *ptr, size_t size, size_t n, FILE *fp){

    return (size_t) gramado_system_call ( 607, 
                        (unsigned long) ptr, 
                        (unsigned long) n, 
                        (unsigned long) fp ); 
}


/*
 ************************
 * fwrite:
 *
 */

size_t fwrite (const void *ptr, size_t size, size_t n, FILE *fp){

    return (size_t) gramado_system_call ( 608, 
                        (unsigned long) ptr, 
                        (unsigned long) n, 
                        (unsigned long) fp ); 
}






// O prompt precisa ser inicializado pelo crt0 e
// quando ele sobre flush.
int prompt_putchar ( int c, int con_id )
{
	
	if ( con_id < 0 )
	    return -1;
	    
	if ( con_id >= 4 )
	    return -1;
	
	
   //#todo: overflow do prompt[]

    //eol
	if ( c != '\n' )
	{
        input ( (unsigned long) c );
        return c;
    }
    
    // se \n
	if ( c == '\n' )    
    {
       prompt_flush (con_id);
    }
} 



int prompt_put_string ( char *string )
{
	if ( (void *) string == NULL )
	    return -1;

    sprintf(prompt,(const char *) string);
    return 0;
}


int prompt_strcat (char *string)
{
	if ( (void *) string == NULL )
	    return -1;

    strcat(prompt,(const char *) string);
    return 0;
}


int prompt_flush ( int con_id )
{
	size_t len;
	
	if ( con_id < 0 )
	    return -1;
	    
	if ( con_id >= 4 )
	    return -1;

	//finaliza.
    input ('\0'); 
    len = strlen( (const char *) prompt );  

    gramado_system_call ( 66, (unsigned long) prompt, con_id, len );  
    prompt_clean ();
    
    return 0; 
}

void prompt_clean (){

    int i;

	// Linpando o buffer de entrada.
	
    for ( i=0; i<PROMPT_MAX_DEFAULT; i++ ){
        prompt[i] = (char) '\0';
    }


    prompt[0] = (char) '\0';
    prompt_pos = 0;
    prompt_status = 0;
    prompt_max = PROMPT_MAX_DEFAULT;  
}






/*
 ****************************************************************
 *    Construindo a função printf;
 ****************************************************************
 */


/*
 **********************************************************************
 * prints:
 *
 */
 
// #bubgug:
// Esses argumentos podem estar fora dos padrões.
// Mas a implementação feita pelo altor é assim mesmo. 

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


    for ( ; *string ; ++string )
    {
        printchar (out, *string);
        ++pc;
    };


    for ( ; width > 0; --width )
    {
        printchar (out,padchar);
        ++pc;
    };


	return pc;
}


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


    if (i == 0)
    {
        print_buf[0] = '0';
        print_buf[1] = '\0';

        return prints (out, print_buf, width, pad);
    }


    if ( sg && b == 10 && i < 0) 
    {
        neg = 1;
        u = -i;
    }

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
    }


    // Done.

    return pc + prints(out, s, width, pad);
}


/*
 *****************************************
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
}


/* 
 ****************************************************
 * printf:
 *     Imprime uma string formatada.
 *     Assuming sizeof(void *) == sizeof(int).
 * Obs: Temos uma chamada ao sistema para cada caractere.
 * 
 * Obs: Se passássemos apenas o ponteiro da string para o kernel pintá-la,
 * não estariamos usando o printf da biblioteca em user mode e sim 
 * a printf do kernel.
 */
 
// Padrão não tradicional, mas funciona. 

int printf3 ( const char *format, ... ){

    register int *varg = (int *)(&format);

    return (int) print ( 0, varg );
}


//
//=============================================================
//

// usada na printf2
void printf_atoi (int value, char* valuestring){

    int min_flag;
    char swap, *p;

    min_flag = 0;


    if (0 > value)
    {
        *valuestring++ = '-';

        value = -INT_MAX> value ? min_flag = INT_MAX : -value;
    }

    p = valuestring;


    do {

        *p++ = (char)(value % 10) + '0';

        value /= 10;
      
    } while (value);


    if (min_flag != 0)
    {
        ++*valuestring;
    }


    *p-- = '\0';


    while (p > valuestring)
    {
        swap = *valuestring;
        
        *valuestring++ = *p;
        
        *p-- = swap;
    }
}


//usada na printf2
void printf_i2hex (uint32_t val, char *dest, int len)
{
    char *cp;
    char x;
    uint32_t n;

    n = val;
    cp = &dest[len];


    while (cp > dest)
    {
        x = n & 0xF;
        n >>= 4;

        *--cp = x + ((x > 9) ? 'A' - 10 : '0');
    };

    dest[len+1] = '\0';
}



// #test 
// tentando implementar a printf do nelson cole.
// padrão tradicional, incompleta, não funciona ainda,
// estamo implementando

int printf2 ( const char *format, ... ){

    char *ap;
    va_start (ap,format);

    int index = 0;
    uint8_t u;
    int d;
    char c, *s;

    char buffer[256];

    while ( format[index] )
    {

		switch (format[index])
		{
		    case '%':
			    ++index;
			    switch (format[index])
			    {
			
                    case 'C':
			        case 'c':
				        c = (int8_t) va_arg (ap, int32_t);
				        putchar(c);
				        break;
     
                    case 'S':
			        case 's':
				        s = va_arg (ap, int8_t*);
				        //puts(s);
				        printf2(s);
						break;

			        case 'd':
			        case 'i':
				        d = va_arg (ap, int32_t);
				        //atoi(d, buffer);
				        printf_atoi(d, buffer);
						//puts(buffer);
						printf2(buffer);
				        break;

			        case 'U':
			        case 'u':
				        u = va_arg (ap, uint32_t);
				        //atoi(u, buffer);
				        printf_atoi (u, buffer);
						//puts(buffer);
				        printf2 (buffer);
						break;

			        case 'X':
			        case 'x':
				        d = va_arg (ap, int32_t);
				        //i2hex(d, buffer,8);
						//printf_i2hex(d, buffer,8);
				        //puts(buffer);
				        printf ("%x",d);
						break;
			
			        default:
				        putchar ('%');
				        putchar ('%');
				        break;
				
			    }
			    break;

		    default:
			    putchar ( format[index] );
			    break;
        };

        ++index;
    };


    return 0;
}



//
//=============================================================
//

//find next line
char *stdio_nextline ( char *string )
{
	
    char *p;

    p = (char *) strchr (string, '\n');
    
    if (p==NULL)
    {
        return (p);
    }

    ++p;

    
    if (*p=='\0')
    {
		//não há próxima linha
        return (NULL);
    
    } else {
		
		//retorna o ponteiro para a próxima linha.
        return (p);
    }
}


//next line sprintf
int nlsprintf ( char *out, const char *format, ... ){

    char *tmp;

    tmp = (char *) stdio_nextline (out);

    if (tmp == NULL )
    {
        return -1;
    }

    register int *varg = (int *)(&format);

    return (int) print( &tmp, varg );
}


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
}


static void printchar ( char **str, int c ){

    if (str) 
    {
		**str = c;
		
		++(*str);

    } else (void) putchar (c);
}


/*
int putchar(int c)
{
	return fputc(c, stdout);
}
*/

/*
int putchar(int c)
{
	return putc(c, stdout);
}
*/
	
/*glibc style*/
/*
int putchar (int __c)
{
  return __putc (__c, stdout);
}
*/






// Setup libc mode.
void libc_set_output_mode ( int mode ){

    switch (mode)
    { 
		case LIBC_DRAW_MODE:
			__libc_output_mode = mode;
			break;

		case LIBC_NORMAL_MODE:
			__libc_output_mode = mode;
			break;

		default:
			__libc_output_mode = LIBC_DRAW_MODE;
			printf ("libc_set_output_mode: fail");
			break;
    };
}



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

    // não é o range válido.
    if ( c <  ' ' && 
        c != '\r' && 
        c != '\n' && 
        c != '\t' && 
        c != '\b' )
    {
        return;
    }


    // #test
    // tentando implementa o backspace para o gdeshell,
    // pois ele usa printf no modo draw para exibir o char.
    
	if( c == '\b' )
    {
        if ( g_cursor_x > 0 )
        {
            g_cursor_x--;
            
            // Isso não apaga, 
            // pois o método de pintura é de transparância.
            _outbyte (' '); 
        }
        prev = c;   // Isso é um teste.
        return;
    }


	// carriege return 
	// Volta ao início da linha.
    if ( c == '\r' )
    {
        g_cursor_x = 0;
        prev = c;
        return;    
    }


	//Próxima linha e não início da linha.   
    if ( c == '\n' && prev != '\r' ) 
    {
        g_cursor_y++; 
        g_cursor_x = 0;  
        prev = c;
        return;
    }


    //Próxima linha e início da linha. 	   
    if ( c == '\n' && prev == '\r' ) 
    {
        g_cursor_y++;  
        prev = c;
        return;
    }


	//Tab.
	//@todo: Criar a var -> 'g_tab_size'.
    if ( c == '\t' )  
    {
        g_cursor_x += (4);    
        prev = c;
        return;         
    }


	//Space 
	//#todo:
	// ?? talvez devêssemos imprimir o caractere espaço. ??    
    if ( c == ' ' )  
    {
        g_cursor_x++; 
        prev = c;
        return; 
    }


    //Delete. 
    if ( c == 8 )  
    {
        g_cursor_x--; 
        prev = c;
        return; 
    }


    // Filtra as dimensões da janela onde esta pintando.
 
//checkLimits:

	//
	// Colunas.
	//

	//Definindo a largura que usaremos.
	//A largura precisa ser maior que '0' e menor que o limite máximo.
	//Obs: @todo: Essa rotina de definição pode ir para o momento da inicialização
	//da biblioteca. Ela contunua aqui porque está funcionando como um filtro.

    if ( g_columns == 0 || g_columns >= SCREEN_MAX_WIDTH )
    {
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
    if ( g_rows == 0 || g_rows >= SCREEN_MAX_HEIGHT )
    {
        g_rows = ROWS;
    }

    //O cursor não pode ultrapassar a altura definida.
	//se ultrapassar, chamaremos o scroll.
	//Obs: O scroll ainda não está implementado.
	//O scroll será feito depois que implementarmos o array de ponteiros
	//para estruturas de linha.
	
    if ( g_cursor_y > g_rows )
    { 
        scroll ();

        g_cursor_x = 0;             //O cursor deve fica na primeira coluna.
		g_cursor_y = (g_rows-1);    //O cursor deve ficar na última linha.
    }

    //
    // Draw!
    //

    // Imprime os caracteres normais.
    _outbyte (c);

	//Atualisa o prev.
    prev = c; 
}


/*
 ***********************************
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

	// #obs: 
	// Tamanho do char constante = 8. 
	// o que queremos é usar uma variável.

void _outbyte ( int c ){

	// #bugbug
	// Essa funçao nao é usada ... NÃO funciona.
	// printf usa outra coisa (65).

    gramado_system_call ( 7, 
        8*g_cursor_x,  8*g_cursor_y, 
        (unsigned long) c ); 

	//#todo
	//putc ( ch, stdout );
}



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
    if ( prompt_pos > prompt_max )
    {
        printf ("input: Full buffer!\n");
        return (unsigned long) 0;   
    }


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


        // backspace afetando o buffer da função input()
        case VK_BACKSPACE:
            if ( prompt_pos > 0 )
            {
                prompt_pos--; 
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


    return (unsigned long) 0;

input_done:

    return VK_RETURN;
}


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

/*
void *stdio_system_call ( unsigned long ax, 
                          unsigned long bx, 
                          unsigned long cx, 
                          unsigned long dx )
{
    int Ret = 0;

    //System interrupt.

    asm volatile ( " int %1 \n"
                   : "=a"(Ret)
                   : "i"(0x80), "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    return (void *) Ret; 
}
*/


/*
// Return BUFFER_SIZE. 
int input_file_buffer_size(void);
int input_file_buffer_size(void)
{
  return (BUFFER_SIZE);
}
*/


/*glibc style;*/
/* Read a character from stdin.  */
/*
//int DEFUN_VOID(getchar)
int getchar (void)
{
  return __getc(stdin);
}
*/


/*
int getchar(void)
{
	return getc(stdin);
}
*/




/*
 **************************************************
 * stdioInitialize:
 *     Inicializa stdio para usar o fluxo padrão.
 *     O retorno deve ser (int) e falhar caso dê algo errado.
 */

// #bugbug
// Essa estrutura lida com elementos de estrutura em ring3.
// #atenção: Algumas rotinas importantes estão usando esses elementos.

void stdioInitialize ()
{

    // Buffers para as estruturas.
    unsigned char buffer0[BUFSIZ];
    unsigned char buffer1[BUFSIZ];
    unsigned char buffer2[BUFSIZ];

    // Buffers.
    unsigned char buffer0_data[BUFSIZ];
    unsigned char buffer1_data[BUFSIZ];
    unsigned char buffer2_data[BUFSIZ];

    int status = 0;
    int i;
    
 
    //
    // Pointers.
    //

    stdin  = (FILE *) &buffer0[0];
    stdout = (FILE *) &buffer1[0];
    stderr = (FILE *) &buffer2[0];

    // Buffers.
    stdin->_base   = &buffer0_data[0];
    stdout->_base  = &buffer1_data[0];
    stderr->_base  = &buffer2_data[0];

    // p
    stdin->_p  = stdin->_base;
    stdout->_p = stdout->_base;
    stderr->_p = stderr->_base;
    
    // cnt
    //stdin->_cnt  = BUFSIZ;
    //stdout->_cnt = BUFSIZ;
    //stderr->_cnt = BUFSIZ;

    
    //#todo
    //stdin->_lbfsize  = 128;
    //stdout->_lbfsize = 128;
    //stderr->_lbfsize = 128;    


    stdin->_r = 0;
    stdout->_r = 0;
    stderr->_r = 0;
    
    stdin->_w = 0;
    stdout->_w = 0;
    stderr->_w = 0;
    
    // o kernel ainda não sabe disso.
    stdin->_file = 0;
    stdout->_file = 1;
    stderr->_file = 2;
    
	__libc_output_mode = LIBC_DRAW_MODE;
	

      // #importante:
      // Vamos conectar o processo filho ao processo pai
      // atraves das ttys dos processos.
      // o processo pai eh o terminal.
      // #bugbug:
      // Esse metodo nao funcionara no caso
      // do processo filho do shell
      
      gramado_system_call ( 267,
           getpid(),    //master
           getppid(),   //slave pai(terminal)
           0 );



    __libc_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );        

    //??
    prompt_clean();
}


/*
int __fflush_stdin(void) 
{
  return fflush(stdin);
}
*/


/*
int __fflush_stdout(void) 
{
  return fflush(stdout);
}
*/



//
// ================= low level =====================
//



/* 
 ***********************************
 * fflush: 
 *     Salva o buffer no arquivo associado a ele e limpa o buffer. 
 * Se for NULL então faz isso para todas stream abertas.
 * retorna 0 se funcionar e retorna EOF se falhar.
 */

int fflush (FILE *stream)
{
    int __ret = -1;
    
	// #todo:
	// Se for NULL faz flush em todos.

    if ( (void *) stream == NULL ){
        debug_print( "fflush: stream\n");
        return -1;
    }

    __ret  = (int) __fflush (stream);


    return (int) __ret;
}


// real flush.
int __fflush (FILE *stream)
{

     //debug_print( "__fflush:\n");
	
    // FIXME: fflush(NULL) should flush all open output streams.
    //ASSERT(stream);
    if ( (void *) stream == NULL ){
        debug_print( "__fflush: stream\n");
        return -1;
    }
 
    //if ( !stream->_w )
        //return 0;
        
        
    if ( (void *) stream->_base == NULL ){
        debug_print( "__fflush: _base\n");
        return -1;
    }   


    if ( stream->_w <= 0 )
    {  
        stream->_w = 0; 
        debug_print( "__fflush: *_w\n");
        return -1;
    } 
               
    
    // #todo: 
    // This is the desired way.           
    int rc = write ( fileno(stream), stream->_base, stream->_w );


    // ISSO FUNCIONA.
    // vamos testar no console virtual.
    //int rc = write_VC ( 0, stream->_base, stream->_w ); 
 
 
    // #test
    // Clear the buffer ???
    memset ( stream->_base, 0, stream->_lbfsize);
    rewind(stream);
 
 
    stream->_w = 0;
    //stream->error = 0;
    //stream->eof = 0;
    //stream->have_ungotten = false;
    //stream->ungotten = 0;
    
    if (rc < 0){
		
        //stream->error = errno;
        return EOF;
    }

    return 0;
}

int __getc ( FILE *stream ){

    int ch = 0;


    if ( (void *) stream == NULL ){
        printf ("__getc: stream struct fail\n");
        return EOF;
    }else{

		 //(--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))
		
		//#fim.
		//cnt decrementou e chegou a zero.
		//Não há mais caracteres disponíveis entre 
		//stream->_ptr e o tamanho do buffer.
		
		if ( stream->_cnt <= 0 )
		{
			stream->_flags = (stream->_flags | _IOEOF); 
			stream->_cnt = 0;
			
		    //printf ("#debug: fgetc: $\n");
			
			//isso funciona, significa que a estrutura tem ponteiro e base validos.
			//printf("show fgetc:: %s @\n", stream->_base );
		    //refresh_screen();
			
			return EOF;
		};

		//#debug
		//nao podemos acessar um ponteiro nulo... no caso endereço.
		
		if ( stream->_p == 0 )
		{
			printf ("__getc: stream struct fail\n");
		    //refresh_screen();
			return EOF;
			
		}else{
			
			// #obs: 
			// Tem que ter a opção de pegarmos usando o posicionamento
			// no buffer. O terminal gosta dessas coisas.
			
		    //Pega o char no posicionamento absoluto do arquivo
		    ch = (int) *stream->_p;
				
            stream->_p++;
            stream->_cnt--;

		    return (int) ch;
		
		}
		//fail
    };


	//#debug
    //printf ("fgetc: $$\n");
	//refresh_screen();

     return EOF;
}

int __putc (int ch, FILE *stream)
{   
     //debug_print( "__serenity_fputc:\n");
     
    //assert (stream);
    //assert (stream->_w < stream->_lbfsize);
    
    if ( (void *) stream == NULL )
    {   
       debug_print( "__putc: stream\n");
       return -1;
    } 

    //if (stream->_w > stream->_lbfsize)
    if (stream->_w > BUFSIZ)
    {   
       debug_print( "__putc: overflow\n");
       return -1;
    } 
    
    stream->_base[stream->_w++] = ch;

    if (stream->_w >= BUFSIZ)
    {
        fflush (stream);
        return ch;
    }
    
    //if (stream->_flags == _IONBF || (stream->_flags == _IOLBF && ch == '\n'))
    if ( ch == '\n')
    {    
		fflush (stream);
		return ch;
    }
    

   //debug_print( "__serenity_fputc: $\n");

    //if (stream->eof || stream->error)
        //return EOF;
    
    return ch;
}


//
// ============= Root =================
//


int getc (FILE *stream)
{
	// low level
    return (int) __getc (stream);
}

int putc (int ch, FILE *stream)
{
	// low level
    return (int) __putc (ch, stream);
}


int fgetc ( FILE *stream )
{
    return (int) getc (stream);
}


int fputc ( int ch, FILE *stream )
{
    return (int) putc (ch, stream);
}

//
// Root 2
//


int getchar (void)
{
    return (int) getc (stdin);
}

int putchar (int ch)
{
    return (int) putc ( (int) ch, stdout );
}

//
// Root 3
//

char *gets (char *s)
{
	register c;
	register char *cs;

	cs = s;
	while ((c = getchar()) != '\n' && c >= 0)
		*cs++ = c;
	if (c<0 && cs==s)
		return(NULL);
	*cs++ = '\0';
	return(s);
}

int puts (const char *s)
{
	register c;

	while (c = *s++)
		putchar(c);
	return(putchar('\n'));
}


//
// Root 4
//


//s n iop
char *fgets (char *s, int size, FILE *stream)
{
	register c;
	register char *cs;

	cs = s;
	while (--size>0 && (c = getc(stream))>=0) {
		*cs++ = c;
		if (c=='\n')
			break;
	}
	if (c<0 && cs==s)
		return(NULL);
	*cs++ = '\0';
	return(s);
}

//s iop
int fputs ( const char *s, FILE *stream )
{
	register r;
	register c;

	while (c = *s++)
		r = putc(c,stream);
	return(r);
}

//
// Root 5
//


int getw (FILE *stream)
{
	register i;

	i = getc(stream);
	
	//#todo
	//if (stream->_flags&_IOEOF)
		//return(-1);
		
	if (stream->eof == 1 )
		return EOF;
		
		
	return(i | (getc(stream)<<8));
}


//#test
int putw (int w, FILE *stream)
{
	putc (w, stream);
	putc (w>>8, stream);
}







/*
 * #opção.
int fprintf(FILE *fp, const char *fmt, ...)
{
    int err;

    va_list ap;
    va_start(ap, fmt);
       
    if ( (void *) fp == NULL )
        return EOF;


    err = vfprintf(fp, fmt, ap);
    va_end(ap);
    
    return err;
}
*/


/*
 ********************************
 * fprintf:     
 */

int fprintf ( FILE *stream, const char *format, ... ){

	//
	// Stream.
	//

    if ( (void *) stream == NULL )
        return EOF;


	// #obs:
	// Talvez essa chamada devesse ela mesma notificar o terminal.

    gramado_system_call ( 234, (unsigned long) stream, 
        (unsigned long) format, (unsigned long) format );

    //
    // Terminal.
    //

    // #bugbug
    // Rever isso e pegar a pid certo.

	// Pegamos o pid do terminal e enviamos uma 
	// notificação de evento para ele.
	int terminal___PID = -1;
	unsigned long message_buffer[5];
	
	//SÓ NOTIFICAREMOS O TERMINAL SE TIVERMOS NO MODO NORMAL
	if ( __libc_output_mode == LIBC_NORMAL_MODE )
	{
        //terminal___PID = (int) system_call ( 1004, 0, 0, 0 ); 
        terminal___PID = (int) gramado_system_call ( 1004, 0, 0, 0 ); 
	
	    if ( terminal___PID < 0 )
	    {
			//libc_set_output_mode (LIBC_DRAW_MODE);
		    //printf_draw ("fprintf:fail\n");
		    return -1;
	    }
		
        //if (pid<0)
		    //return -1;
	
	    message_buffer[0] = (unsigned long) 0;    //window
	    message_buffer[1] = (unsigned long) 100;  //message;  //MSG_TERMINALCOMMAND
	    message_buffer[2] = (unsigned long) 2008; //long1;    //2008  
	    message_buffer[3] = (unsigned long) 2008; //long2;    //2008
	    //...

	    //notifica o terminal de que ele tem mensagens.
        //return (int) system_call ( 112 , (unsigned long) &message_buffer[0], 
        //                (unsigned long) terminal___PID, (unsigned long) terminal___PID );

        return (int) gramado_system_call ( 112 , 
                         (unsigned long) &message_buffer[0], 
                         (unsigned long) terminal___PID, 
                         (unsigned long) terminal___PID );

        //#todo temos que usar essa chamada ao invés dessa rotina acima.
        //ok
	    // __SendMessageToProcess ( terminal___PID, NULL, MSG_TERMINALCOMMAND, 2008, 2008 );
    }


    return 0;
}


/*
int fputs (const char *s, FILE *stream) 
{
  return fwrite ( s, strlen(s), 1, stream );
}
*/


/*uClib style*/
/*
int fputs(const char *str, FILE *fp)
{
	int n;

    if ( (void *) fp == NULL )
        return EOF;


	n = strlen(str);

	_uClibc_fwrite((const unsigned char *)str, n, fp);
	if (fp->mode & __MODE_ERR) {
		n = EOF;
	}
	return n;
}
*/
	



//#todo: testar.
//Credits: Sombra OS.
void nputs (char *cp, int len)
{
	int i = len;
	char *str;

	for (str = cp; i; str++, i--)
        putchar ( (int) *str);
}


/*uClib style*/
	/* 
	 * Strictly speaking, this implementation is incorrect as the number
	 * of chars gets can read should be unlimited.  However, I can't
	 * imagine anyone wanting to gets() into a buffer bigger than INT_MAX.
	 *
	 * Besides, this function is inherently unsafe and shouldn't be used.
	 */
/* This is an UNSAFE function! */
/*
char *gets(char *str) 
{
	return fgets(str, INT_MAX, stdin);
}
*/


/*uClib style*/
/*
char *fgets(char *s, int count, FILE *fp)
{
	int ch;
	char *p;
	

    if ( (void *) fp == NULL )
        return EOF;
	
	p = s;
	
	//Guard against count arg == INT_MIN. 
	while (count-- > 1) 
	{		
		ch = getc (fp);
		
		if (ch == EOF) 
		{
			break;
		}
		
		*p++ = ch;
		
		if (ch == '\n') { break; }
	}
	
	if ( ferror(fp) || (s == p) ) 
	{
		return 0;
	}
	
	*p = 0;
	
	return s;
}
*/


 



/*dietlibc style*/
//isso deve ir para ring0
/*
int ungetc(int c, FILE *stream) 
{

    if ( (void *) stream == NULL )
        return EOF;

  if (stream->ungotten || c<0 || c>255)
    return EOF;
	
  stream->ungotten=1;
  stream->ungetbuf=(unsigned char)c;
  stream->flags&=~(ERRORINDICATOR|EOFINDICATOR);
	
  return c;
}
*/


/*
 *********************************
 * ungetc:
 */

int ungetc ( int c, FILE *stream ){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 606, 
                     (unsigned long) c, 
                     (unsigned long) stream, 
                     (unsigned long) stream );
}


/*linux - klibc style*/
/*
static __inline__ off_t ftell(FILE *__f)
{
  extern off_t lseek(int, off_t, int);
  return lseek(fileno(__f), 0, SEEK_CUR);
}
*/

// Dixaremos o kernel manipular a estrutura.
//This function returns the current file position of the stream stream. 
long ftell (FILE *stream){

    if ( (void *) stream == NULL )
        return (long) -1;

    return (long) gramado_system_call ( 249, 
                      (unsigned long) stream, 
                      (unsigned long) stream, 
                      (unsigned long) stream );
}


/*
 * fileno: 
 *     Gets the file id.
 *     The kernel gets this value from the stream struct.
 */
int fileno ( FILE *stream ){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 605, 
                     (unsigned long) stream, 
                     (unsigned long) stream, 
                     (unsigned long) stream );
}



int __gramado__getc ( FILE *stream ){


    int ch = 0;



    if ( (void *) stream == NULL ){
        printf ("fgetc: stream struct fail\n");
        return EOF;
    }else{

		 //(--(p)->_r < 0 ? __srget(p) : (int)(*(p)->_p++))
		
		//#fim.
		//cnt decrementou e chegou a zero.
		//Não há mais caracteres disponíveis entre 
		//stream->_ptr e o tamanho do buffer.
		
		if ( stream->_cnt <= 0 )
		{
			stream->_flags = (stream->_flags | _IOEOF); 
			stream->_cnt = 0;
			
		    //printf ("#debug: fgetc: $\n");
			
			//isso funciona, significa que a estrutura tem ponteiro e base validos.
			//printf("show fgetc:: %s @\n", stream->_base );
		    //refresh_screen();
			
			return EOF;
		};

		//#debug
		//nao podemos acessar um ponteiro nulo... no caso endereço.
		
		if ( stream->_p == 0 )
		{
			printf ("#debug: fgetc: stream struct fail\n");
		    //refresh_screen();
			return EOF;
			
		}else{
			
			// #obs: 
			// Tem que ter a opção de pegarmos usando o posicionamento
			// no buffer. O terminal gosta dessas coisas.
			
		    //Pega o char no posicionamento absoluto do arquivo
		    ch = (int) *stream->_p;
				
            stream->_p++;
            stream->_cnt--;

		    return (int) ch;
		
		}
		//fail
    };


	//#debug
    //printf ("fgetc: $$\n");
	//refresh_screen();

     return EOF;
}



/*linux klibc style.*/
//isso deve ir para ring0
/*
int fgetc(FILE *f)
{
  unsigned char ch;

    if ( (void *) f == NULL )
        return EOF;

  return ( _fread (&ch, 1, f) == 1) ? (int) ch : EOF;
}
*/


/*uClibb style*/
//isso deve ir para ring0
/*
int getc(FILE *stream)
{
    if ( (void *) stream == NULL )
        return EOF;

    return (((stream)->bufpos >= (stream)->bufread)?  fgetc(stream) : (*(stream)->bufpos++));
}
*/

/*
 *********************************
 * fgetc:
 *     #todo: chamar a rotina do kernel para pegar o char no arquivo,
 * pois agora o arquivo 'e gerenciado pelo kernel.
 */

/*
int fgetc ( FILE *stream ){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 136, 
                     (unsigned long) stream,  
                     (unsigned long) stream,  
                     (unsigned long) stream );
}
*/





/*
int feof(FILE *fp)
{
    if ( (void *) fp == NULL )
        return EOF;

    return fp->mode & __MODE_EOF;
}
*/


/*
 *********************************
 * feof:
 */

int feof ( FILE *stream ){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 193, 
                     (unsigned long) stream,  
                     (unsigned long) stream,  
                     (unsigned long) stream );
}


/*
 //This function clears the end-of-file and error indicators for the stream stream. 
void clearerr(FILE *fp)
{
    if ( (void *) fp == NULL )
        return EOF;

    //#bugbug: Isso precisa ser feito em ring0;
	//fp->mode &= ~(__MODE_EOF | __MODE_ERR);
}
*/


/*
 *********************************
 * ferror:
 */

int ferror ( FILE *stream ){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 194, 
                     (unsigned long) stream,  
                     (unsigned long) stream,  
                     (unsigned long) stream );    
}



/*linux - klibc style*/
/*
static __inline__ int fseek(FILE *__f, off_t __o, int __w)
{
    extern off_t lseek(int, off_t, int);

    if ( (void *) __f == NULL )
        return EOF;

    return (lseek(fileno(__f), __o, __w) == (off_t)-1) ? -1 : 0;
}
*/
	


/*
 **************************************
 * fseek:
 *     offset argument is the position that you want to seek to,
 *     and whence is what that offset is relative to.
 */

// The fseek function is used to change the file position of the stream stream. 

int fseek ( FILE *stream, long offset, int whence ){

    if ( (void *) stream == NULL )
        return EOF;

     return (int) gramado_system_call ( 195, 
                      (unsigned long) stream, 
                      (unsigned long) offset,  
                      (unsigned long) whence ); 
}


/*uClib style*/
/*
int putc(int c, FILE *stream)
{
    if ( (void *) stream == NULL )
        return EOF;

    return (((stream)->bufpos >= (stream)->bufwrite)?  fputc((c), (stream)) : (unsigned char) (*(stream)->bufpos++ = (c)) );
}
*/



/*linux klibc style*/
/*
int fputc(int c, FILE *f)
{
    unsigned char ch = c;
    
    if ( (void *) f == NULL )
        return EOF;
    
    return _fwrite(&ch, 1, f) == 1 ? ch : EOF;
}
*/


/*
 * #todo: Implementar isso.
int putw (int w, FILE *stream);
int putw (int w, FILE *stream)
{

    if ( (void *) stream == NULL )
        return EOF;

    if ( fwrite ( (const char*) &w, sizeof (w), 1, stream ) != 1 )
        return EOF;

    return 0;
}
*/


/*
ssize_t getline (char **lineptr, size_t *n, FILE *stream); 
ssize_t getline (char **lineptr, size_t *n, FILE *stream)
{
    if ( (void *) stream == NULL )
        return EOF;

     return getdelim (lineptr, n, '\n', stream);
}  
*/


/*
// colocando num buffer aqui em ring3
char __BUFFER[128];
unsigned int __buffer_pos;
int __buffer_putc ( int ch );
int __buffer_putc ( int ch )
{

    if ( __buffer_pos < 128 && ch != '\n' )
    { 
        __BUFFER[__buffer_pos] = c
        return ch;
    }
    
    if ( __buffer_pos >= 128 || ch == '\n' )
    {
        //flush
        flush_buffer ( (unsigned long) &__BUFFER[0] );
        __buffer_pos = 0;
        return ch;
    }
    
    return 0;
}
*/



// See: apple open source
/*
int
putc(c, fp)
	int c;
	register FILE *fp;
{
    if ( (void *) fd == NULL )
        return EOF;

	return (__sputc(c, fp));
}
*/



//apple open source.
/*
int
fputc(c, fp);
int
fputc(c, fp)
	int c;
	register FILE *fp;
{
    if ( (void *) fp == NULL )
        return EOF;

	return (putc(c, fp));
}
*/




//
// Flush.
//

int __serenity_fflush ( FILE *stream)
{

     //debug_print( "__serenity_fflush:\n");
	
    // FIXME: fflush(NULL) should flush all open output streams.
    //ASSERT(stream);
    if ( (void *) stream == NULL ){
        debug_print ( "__serenity_fflush: stream\n");
        return -1;
    }
 
    //if ( !stream->_w )
        //return 0;
        
        
    if ( (void *) stream->_base == NULL ){
        debug_print( "__serenity_fflush: _base\n");
        return -1;
    }   


    if ( stream->_w <= 0 ){   
        debug_print( "__serenity_fflush: _w\n");
        return -1;
    } 
               
    
    // #todo: 
    // This is the desired way.           
    // int rc = write ( fileno(stream), stream->_base, stream->_w );


    // ISSO FUNCIONA.
    // vamos testar no console virtual.
    int rc = write_VC ( 0, stream->_base, stream->_w ); 
 
 
    stream->_w = 0;
    //stream->error = 0;
    //stream->eof = 0;
    //stream->have_ungotten = false;
    //stream->ungotten = 0;
    
    if (rc < 0){
		
        //stream->error = errno;
        return EOF;
    }

    return 0;
}



int __serenity_fputc (int ch, FILE *stream)
{
     //debug_print( "__serenity_fputc:\n");
     
    //assert (stream);
    //assert (stream->_w < stream->_lbfsize);
    
    if ( (void *) stream == NULL )
    {   
       debug_print( "__serenity_fputc: stream\n");
       return -1;
    } 

    //if (stream->_w > stream->_lbfsize)
    if (stream->_w > BUFSIZ)
    {   
       debug_print( "__serenity_fputc: overflow\n");
       return -1;
    } 
    
    stream->_base[stream->_w++] = ch;

    if (stream->_w >= BUFSIZ)
    {
        __serenity_fflush(stream);
        return ch;
    }
    
    //if (stream->_flags == _IONBF || (stream->_flags == _IOLBF && ch == '\n'))
    if ( ch == '\n')
    {    
		__serenity_fflush (stream);
		return ch;
    }
    

   //debug_print( "__serenity_fputc: $\n");

    //if (stream->eof || stream->error)
        //return EOF;
    
    return ch;
}



int __serenity_putc (int ch, FILE *stream)
{   
    return __serenity_fputc (ch, stream);
}





/*
 ********************************
 * stdioSetCursor:
 *     estamos falando do posicionamento do cursor dentro da janela
 *     e não dentro do terminal.
 */

//34 - set cursor.

void stdioSetCursor ( unsigned long x, unsigned long y )
{
    gramado_system_call ( 34, x, y, 0 );
}


/*
 * stdioGetCursorX:
 *     Get cursor x. 
 *     estamos falando do posicionamento do cursor dentro da janela
 *     e não dentro do terminal.
 */ 

unsigned long stdioGetCursorX ()
{
    return (unsigned long) gramado_system_call ( 240, 0, 0, 0 );
}


/*
 * stdioGetCursorY:
 *     Get cursor y.
 *     estamos falando do posicionamento do cursor dentro da janela
 *     e não dentro do terminal. 
 */

unsigned long stdioGetCursorY (){
    
    return (unsigned long) gramado_system_call ( 241, 0, 0, 0 );
}


//======================================================================
// scanf support (start)
//======================================================================


int scanf ( const char *fmt, ... ){

    va_list ap;
    va_start (ap, fmt);

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
    int size = (int) stdio_strlen (fmt);


	nread = 0;
	
    while (*fmt)
    {

		c = *fmt;
		if (c == 0)
			return (0); //erro
		
		// pulando os espaços
		if ( isspace (c) ) 
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
				    gets (s);
				}else{
				    printf ("scanf: s null pointer\n");	
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
					gets (tmp);
					
					//converte essa string em dígito
					i[0] = (int) stdio_atoi (tmp);                     
					
				}else{
				    printf ("scanf: s null pointer\n");	
				}
				
				//testar ...
				//printf("string %s\n", s);
			
                //d = va_arg(ap, int);
                //printf("int %d\n", d);
                break;
            
			/* char */
			case 'c':    
                t = va_arg (ap, char *);
				if ( (void *) t != NULL )
				{
				
                    while (1)
                    {
			            ch = (int) getchar ();
						
						if ( ch != -1 )
						{
						    t[0] = ch;
                            //printf("scanf ch={%c}",ch);
						    break;	
						}			
					};	
					
				}else{
					printf ("scanf: c null pointer\n");
				}; 				 
                break;
				
			//default:
            //    break; 
				
        };//switch
    };


   //va_end (ap);
   
   return 0;
}
//======================================================================
// scanf support (end)
//======================================================================



/*
 * sscanf: 
 * Scan items from a string in accordance with a format.  This is much
 * simpler than the C standard function: it only recognises %d without a
 * field width, and does not treat space in the format string or the
 * input any differently from other characters.  The return value is the
 * number of characters from the input string that were successfully
 * scanned, not the number of format items matched as in standard sscanf.
 * e.mcmanus@opengroup.org, 12 Feb 97
 * Credits: apple open source.
 */

int sscanf ( const char *str, const char *format, ... ){

    const char *start = str;
    va_list args;

    va_start(args, format);


    for ( ; *format != '\0'; format++ )
    {

		if ( *format == '%' && format[1] == 'd' ){
			
			int positive;
			int value;
			int *valp;
			
			if (*str == '-') {
				positive = 0;
				str++;
			} else
				positive = 1;
			if (!isdigit(*str))
				break;
			value = 0;
			do {
				value = (value * 10) - (*str - '0');
				str++;
			} while (isdigit(*str));
			if (positive)
				value = -value;
			valp = va_arg(args, int *);
			*valp = value;
			format++;
		} else if (*format == *str) {
			str++;
		} else
			break;
	};


    va_end (args);


    return str - start;
}


//=============================================================
// printf (start)
//=============================================================
/*-
 * Copyright (c) 1986, 1988, 1991, 1993
 *	The Regents of the University of California.  All rights reserved.
 * (c) UNIX System Laboratories, Inc.
 * All or some portions of this file are derived from material licensed
 * to the University of California by American Telephone and Telegraph
 * Co. or Unix System Laboratories, Inc. and are reproduced herein with
 * the permission of UNIX System Laboratories, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *	@(#)subr_prf.c	8.3 (Berkeley) 1/21/94
 */

//typedef unsigned long size_t;
//typedef long ssize_t;
//#ifdef __64BIT__
//typedef unsigned long long uintmax_t;
//typedef long long intmax_t;
//#else
typedef unsigned int uintmax_t;
typedef int intmax_t;
//#endif
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef unsigned short u_short;
typedef unsigned long long u_quad_t;
typedef long long quad_t;
typedef unsigned long uintptr_t;
//typedef long ptrdiff_t;
//#define NULL ((void*)0)
#define NBBY    8               /* number of bits in a byte */
char const hex2ascii_data[] = "0123456789abcdefghijklmnopqrstuvwxyz";
#define hex2ascii(hex)  (hex2ascii_data[hex])
//#define va_list __builtin_va_list
//#define va_start __builtin_va_start
//#define va_arg __builtin_va_arg
//#define va_end __builtin_va_end

//#obs:
//vamos usar o que está em ctype.h
//#define toupper(c)  ((c) - 0x20 * (((c) >= 'a') && ((c) <= 'z')))

static size_t stdio_strlen (const char *s){

    size_t l = 0;

    while (*s++)
        l++;
    return l;
}


/* Max number conversion buffer length: 
 a u_quad_t in base 2, plus NUL byte. */
#define MAXNBUF	(sizeof(intmax_t) * NBBY + 1)

/*
 * Put a NUL-terminated ASCII number (base <= 36) in a buffer in reverse
 * order; return an optional length and a pointer to the last character
 * written in the buffer (i.e., the first character of the string).
 * The buffer pointed to by `nbuf' must have length >= MAXNBUF.
 */
 
static char *ksprintn ( char *nbuf, 
                        uintmax_t num, 
                        int base, 
                        int *lenp, 
                        int upper )
{
    char *p, c;

    p = nbuf;

	//*p = ' ';
	*p = 0;


    do {

		c = hex2ascii (num % base);
		
		*++p = upper ? toupper(c) : c;
		
    } while (num /= base);


    if (lenp)
        *lenp = p - nbuf;
    return (p);
}


/*
 * Scaled down version of printf(3).
 *
 * Two additional formats:
 *     The format %b is supported to decode error registers.
 *     Its usage is:
 *
 *	printf("reg=%bn", regval, "*");
 *
 * where  is the output base expressed as a control character, e.g.
 * 10 gives octal; 20 gives hex.  Each arg is a sequence of characters,
 * the first of which gives the bit number to be inspected (origin 1), and
 * the next characters (up to a control character, i.e. a character <= 32),
 * give the name of the register.  Thus:
 *
 *	kvprintf("reg=%bn", 3, "102BITTWO1BITONEn");
 *
 * would produce output:
 *
 *	reg=3
 *
 * XXX:  %D  -- Hexdump, takes pointer and separator string:
 *		("%6D", ptr, ":")   -> XX:XX:XX:XX:XX:XX
 *		("%*D", len, ptr, " " -> XX XX XX XX ...
 */
 
int 
kvprintf ( char const *fmt, 
           void (*func)( int, void * ), 
           void *arg, 
           int radix, 
           va_list ap )
{


	//#define PCHAR(c) { int cc=(c); if(func) (*func)(cc,arg); else *d++ = cc; retval++; }
    #define PCHAR(c) { int cc=(c); if(func) (*func)(cc,arg); else *d++ = cc; retval++; }


	char nbuf[MAXNBUF];
	char *d;
	const char *p, *percent, *q;
	u_char *up;

	int ch, n;
	uintmax_t num;
	int base, lflag, qflag, tmp, width, ladjust, sharpflag, neg, sign, dot;
	int cflag, hflag, jflag, tflag, zflag;
	int dwidth, upper;
	char padc;
	int stop = 0, retval = 0;


	num = 0;
	
	if (!func)
		d = (char *) arg;
	else
		d = NULL;



	if (fmt == NULL)
		fmt = "(fmt null)n";



	if (radix < 2 || radix > 36)
		radix = 10;


    for (;;)
    {

		padc = ' ';
		width = 0;
		
		while ( ( ch = (u_char) *fmt++ ) != '%' || stop ) 
		{
			//if (ch == '')
			//	return (retval);
			
			if (ch == 0)
			    return (retval);
			
			PCHAR (ch);
		}
		
		percent = fmt - 1;
		
		qflag = 0; 
		lflag = 0; 
		ladjust = 0; 
		sharpflag = 0; 
		neg = 0;
		
		sign = 0; 
		dot = 0; 
		dwidth = 0; 
		upper = 0;
		
		cflag = 0; 
		hflag = 0; 
		jflag = 0; 
		tflag = 0; 
		zflag = 0;
		
        reswitch:  
    
	    switch ( ch = (u_char) *fmt++ ){
			
		case '.':
			dot = 1;
			goto reswitch;
			
		case '#':
			sharpflag = 1;
			goto reswitch;
			
		case '+':
			sign = 1;
			goto reswitch;
			
		case '-':
			ladjust = 1;
			goto reswitch;
			
		case '%':
			PCHAR(ch);
			break;
			
		case '*':
			if (!dot) 
			{
				width = va_arg(ap, int);
				
				if (width < 0)
				{
					ladjust = !ladjust;
					width = -width;
				};
				
			} else {
				
				dwidth = va_arg(ap, int);
			};
			goto reswitch;
			
		case '0':
			if (!dot) 
			{
				padc = '0';
				goto reswitch;
			}
			
		case '1': 
		case '2': 
		case '3': 
		case '4':
		case '5': 
		case '6': 
		case '7': 
		case '8': 
		case '9':
			for ( n = 0;; ++fmt ) 
			{
				n = n * 10 + ch - '0';
				ch = *fmt;
				
				if (ch < '0' || ch > '9')
					break;
			}
			
			if (dot)
				dwidth = n;
			else
				width = n;
			goto reswitch;
			
		case 'b':
			num = (u_int)va_arg(ap, int);
			p = va_arg(ap, char *);
			
			for (q = ksprintn(nbuf, num, *p++, NULL, 0); *q;)
				PCHAR(*q--);

			if (num == 0)
				break;

			for (tmp = 0; *p;) 
			{
				n = *p++;
				
				if (num & (1 << (n - 1))) 
				{
					PCHAR(tmp ? ',' : '<');
					
					for (; (n = *p) > ' '; ++p)
						PCHAR(n);
					tmp = 1;
				} else
					for (; *p > ' '; ++p)
						continue;
			};
			
			if (tmp)
				PCHAR('>');
			break;
			
		case 'c':
			PCHAR(va_arg(ap, int));
			break;
			
		case 'D':
			up = va_arg(ap, u_char *);
			p = va_arg(ap, char *);
			
			if (!width)
				width = 16;
			while(width--) 
			{
				PCHAR(hex2ascii(*up >> 4));
				PCHAR(hex2ascii(*up & 0x0f));
				up++;
				
				if (width)
					for (q=p;*q;q++)
						PCHAR(*q);
			};
			break;
			
		case 'd':
		case 'i':
			base = 10;
			sign = 1;
			goto handle_sign;
			
		case 'h':
			if (hflag) 
			{
				hflag = 0;
				cflag = 1;
			} else
				hflag = 1;
			goto reswitch;
			
		case 'j':
			jflag = 1;
			goto reswitch;
			
		case 'l':
			if (lflag) 
			{
				lflag = 0;
				qflag = 1;
			} else
				lflag = 1;
			goto reswitch;
			
		case 'n':
			if (jflag)
				*(va_arg(ap, intmax_t *)) = retval;
			else if (qflag)
				*(va_arg(ap, quad_t *)) = retval;
			else if (lflag)
				*(va_arg(ap, long *)) = retval;
			else if (zflag)
				*(va_arg(ap, size_t *)) = retval;
			else if (hflag)
				*(va_arg(ap, short *)) = retval;
			else if (cflag)
				*(va_arg(ap, char *)) = retval;
			else
				*(va_arg(ap, int *)) = retval;
			break;
			
		case 'o':
			base = 8;
			goto handle_nosign;
			
		case 'p':
			base = 16;
			sharpflag = (width == 0);
			sign = 0;
			num = (uintptr_t)va_arg(ap, void *);
			goto number;
			
		case 'q':
			qflag = 1;
			goto reswitch;
			
		case 'r':
			base = radix;
			if (sign)
				goto handle_sign;
			goto handle_nosign;
			
		case 's':
			p = va_arg(ap, char *);
			if (p == NULL)
				p = "(null)";
			if (!dot)
				n = stdio_strlen (p);
			else
				for (n = 0; n < dwidth && p[n]; n++)
					continue;

			width -= n;

			if (!ladjust && width > 0)
				while (width--)
					PCHAR(padc);
			while (n--)
				PCHAR(*p++);
			if (ladjust && width > 0)
				while (width--)
					PCHAR(padc);
			break;
			
		case 't':
			tflag = 1;
			goto reswitch;
			
		// ?? case 'U': ??
		case 'u':
			base = 10;
			goto handle_nosign;
			
		case 'X':
			upper = 1;
		case 'x':
			base = 16;
			goto handle_nosign;
			
		case 'y':
			base = 16;
			sign = 1;
			goto handle_sign;
			
		case 'z':
			zflag = 1;
			goto reswitch;
			
        handle_nosign:
			sign = 0;
			if (jflag)
				num = va_arg(ap, uintmax_t);
			else if (qflag)
				num = va_arg(ap, u_quad_t);
			else if (tflag)
				num = va_arg(ap, ptrdiff_t);
			else if (lflag)
				num = va_arg(ap, u_long);
			else if (zflag)
				num = va_arg(ap, size_t);
			else if (hflag)
				num = (u_short)va_arg(ap, int);
			else if (cflag)
				num = (u_char)va_arg(ap, int);
			else
				num = va_arg(ap, u_int);
			goto number;
			
        handle_sign:
			if (jflag)
				num = va_arg(ap, intmax_t);
			else if (qflag)
				num = va_arg(ap, quad_t);
			else if (tflag)
				num = va_arg(ap, ptrdiff_t);
			else if (lflag)
				num = va_arg(ap, long);
			else if (zflag)
				num = va_arg(ap, ssize_t);
			else if (hflag)
				num = (short)va_arg(ap, int);
			else if (cflag)
				num = (char)va_arg(ap, int);
			else
				num = va_arg(ap, int);
			
        number:
			if (sign && (intmax_t)num < 0) {
				neg = 1;
				num = -(intmax_t)num;
			}
			p = ksprintn(nbuf, num, base, &tmp, upper);
			if (sharpflag && num != 0) {
				if (base == 8)
					tmp++;
				else if (base == 16)
					tmp += 2;
			}
			if (neg)
				tmp++;

			if (!ladjust && padc != '0' && width
			    && (width -= tmp) > 0)
				while (width--)
					PCHAR(padc);
			if (neg)
				PCHAR('-');
			if (sharpflag && num != 0) {
				if (base == 8) {
					PCHAR('0');
				} else if (base == 16) {
					PCHAR('0');
					PCHAR('x');
				}
			}
			if (!ladjust && width && (width -= tmp) > 0)
				while (width--)
					PCHAR(padc);

			while (*p)
				PCHAR(*p--);

			if (ladjust && width && (width -= tmp) > 0)
				while (width--)
					PCHAR(padc);

			break;
			
		default:
			
			while (percent < fmt)
				PCHAR(*percent++);
			
			/* Since we ignore an formatting argument it is no
			 * longer safe to obey the remaining formatting
			 * arguments as the arguments will no longer match
			 * the format specs. */
			 
			stop = 1;
			break;
		};
	};
#undef PCHAR
}


static void xxxputchar ( int c, void *arg ){

	/* add your putchar here */

    putchar ( (int) c );
}


/*
 *===========================================
 * printf:
 *     http://www.pagetable.com/?p=298
 */

int printf ( const char *fmt, ... ){
	
	// #todo
	// Talvez usar semáforo aqui.
	
    va_list ap;
    va_start(ap, fmt);

	//int 
	//kvprintf ( char const *fmt, 
    //       void (*func)( int, void* ), 
	//	   void *arg, 
	//	   int radix, //??10 gives octal; 20 gives hex.
	//	   va_list ap );	
	
	kvprintf ( fmt, xxxputchar, NULL, 10, ap );
	
	//#todo.
	va_end (ap);
	
	//#test
	//vamos pedir pro terminal virtual imprimir o conteúdo do buffer. 
	//MSG_TERMINALCOMMAND = 100
	//__SendMessageToProcess ( terminal___PID, 0, 100, 2008, 2008 );



    return 0;
}
//=============================================================
// printf end
//=============================================================


/*
 *===========================================
 * printf_draw:
 *     http://www.pagetable.com/?p=298
 */

// Nessa versão a rotina pintará na tela ao invés de
// colocar o char no arquivos.
// para isso ela configura o modo de output, voltando ao normal
// ao fim da rotina.
// >> Essa rotina é usada para debug no caso de não termos acesso
// a rotinas da api ou do x-server para pintura na tela.


int printf_draw ( const char *fmt, ... ){
	
	//Habilita o modo draw.
	libc_set_output_mode ( LIBC_DRAW_MODE );
	
	// #todo
	// Talvez usar semáforo aqui.
	
	va_list ap;
	va_start(ap, fmt);
	
	//int 
	//kvprintf ( char const *fmt, 
    //       void (*func)( int, void* ), 
	//	   void *arg, 
	//	   int radix, //??10 gives octal; 20 gives hex.
	//	   va_list ap );	
	
	kvprintf ( fmt, xxxputchar, NULL, 10, ap );
	
	//#todo.
	va_end (ap);
	
	
	//reabilita o modo normal. Onde os caracteres serão colocados 
	//no stdout.
	libc_set_output_mode ( LIBC_NORMAL_MODE );



    return 0;
}





/*glibc style*/
/* Optimizing.  */
/*
#ifdef	__OPTIMIZE__
extern __inline int vprintf (const char *__fmt, __gnuc_va_list __arg)
{

    if ( (void *) stdout == NULL )
        return EOF;

  return vfprintf (stdout, __fmt, __arg);
}
#endif 
*/


/*
 **********************
 * vfprintf:
 */

// #bugbug
// Estamos em ring3, não devemos acessar os elementos da estrutura de stream.

int vfprintf ( FILE *stream, const char *format, stdio_va_list argptr ){

    int size;


    //if ( (void *) stream == NULL )
        //return EOF;


    if ( (void *) stream == NULL )
    {
		return (int) (-1);
		
    } else {

		size = (int) stdio_strlen (format);
		
		//Se a string for maior que o tanto de bytes
		//disponíveis no arquivo
		if ( size > stream->_cnt )
		{
			return (int) (-1);
		}
		
		//recalcula o tanto de bytes disponíveis
		stream->_cnt = (int) (stream->_cnt - size);
		
		//coloca no buffer, usando o ponteiro atual.
		//#obs: isso provavelmente funcione, 
		//mas vamos tentar o segundo método.
		//sprintf ( stream->_ptr, format );
		//kvprintf ( format, NULL, stream->_ptr, 10, argptr );
		kvprintf ( format, NULL, stream->_p, 10, argptr );
		
		//atualiza o ponteiro atual.
		//stream->_ptr = stream->_ptr + size;
		stream->_p = stream->_p + size;
        
		return 0;
    };


    return (int) (-1);
} 


/* #bsd style */

int vprintf (const char *fmt, va_list ap){

    if ( (void *) stdout == NULL )
        return EOF;

    return vfprintf (stdout, fmt, ap);
}


//printf que escreve no stdout. 
int stdout_printf (const char *format, ...){

    va_list arg;
    int done;

    if ( (void *) stdout == NULL )
        return EOF;

    va_start (arg, format);
    done = vfprintf (stdout, format, arg);
    va_end (arg);

    return done;
}


//printf que escreve no stderr. 
int stderr_printf (const char *format, ... ){

    int done;
    
    va_list arg;
    va_start (arg, format);

    if ( (void *) stderr == NULL )
        return EOF;

    done = vfprintf (stderr, format, arg);
    va_end (arg);

    return done;
}
 
void perror (const char *str){
	
    stderr_printf (str);
}



// #bugbug
// Isso deve acontecer somente na estrutura de stream
// em ring 3.
// O ponto de leitura e escrita volta a ser a base.

void rewind (FILE *stream){

    if ( (void *) stream == NULL )
        return;


    stream->_p = stream->_base;
    stream->_w = 0;
    stream->_r = 0;

    //#bugbug
    // não mandamos ponteiro de estrutura de stream para o kernel
    // ele nem sabe o que é isso.
    
    /*
    gramado_system_call ( 609, 
        (unsigned long) stream, 
        (unsigned long) stream, 
        (unsigned long) stream ); 
    */
}


//#todo
int snprintf ( char *str, size_t count, const char *fmt, ... ){

    size_t ret;

    va_list ap;
    va_start (ap, fmt);


	//#todo 
	//Isso parece fácil
	//ret = vsnprintf(str, count, fmt, ap);


    va_end (ap);
    
    return ret;
}


// inicializa o fluxo padrão para o processo.
int stdio_initialize_standard_streams (void){

    if ( (void *) stdin == NULL )
        return EOF;

    if ( (void *) stdout == NULL )
        return EOF;

    if ( (void *) stderr == NULL )
        return EOF;


    return (int) gramado_system_call ( 700, 
                     (unsigned long) stdin, 
                     (unsigned long) stdout, 
                     (unsigned long) stderr ); 
}





/*credits: bsd*/
/*
 * Return the (stdio) flags for a given mode.  Store the flags
 * to be passed to an open() syscall through *optr.
 * Return 0 on error.
 */

/*
int
__sflags(const char *mode, int *optr);
int
__sflags(const char *mode, int *optr)
{
	int ret, m, o;

	//#todo: Falta essa macro. ela fica em assert.h
	//_DIAGASSERT(mode != NULL);

	switch (*mode++) {

	case 'r':	// open for reading 
		ret = __SRD;
		m = O_RDONLY;
		o = 0;
		break;

	case 'w':	// open for writing 
		ret = __SWR;
		m = O_WRONLY;
		o = O_CREAT | O_TRUNC;
		break;

	case 'a':	// open for appending 
		ret = __SWR;
		m = O_WRONLY;
		o = O_CREAT | O_APPEND;
		break;

	default:	// illegal mode 
		errno = EINVAL;
		return 0;
	}

	
	 //[rwa]\+ or [rwa]b\+ means read and write 
	 //e means set close on exec.
	 //f means open only plain files.
	 //l means don't follow symlinks.
	 //x means exclusive open.
	 
	for (; *mode; mode++)
		switch (*mode) {
		case '+':
			ret = __SRW;
			m = O_RDWR;
			break;
		case 'b':
			break;
		case 'e':
			o |= O_CLOEXEC;
			break;
		case 'f':
			o |= O_REGULAR;
			break;
		case 'l':
			o |= O_NOFOLLOW;
			break;
		case 'x':
			o |= O_EXCL;
			break;
		default:	// We could produce a warning here 
			break;
		}

	*optr = m | o;
	return ret;
}
*/


/*credits: bsd*/
// ?? wtf ??
/*
int
_fwalk(int (*function)(FILE *));
int
_fwalk(int (*function)(FILE *))
{
	FILE *fp;
	int n, ret;
	struct glue *g; //falta isso.

    //#todo: Falta essa macro. ela fica em assert.h
	_DIAGASSERT(function != NULL);

	ret = 0;
	for (g = &__sglue; g != NULL; g = g->next)
		for (fp = g->iobs, n = g->niobs; --n >= 0; fp++)
			if (fp->_flags != 0)
				ret |= (*function)(fp);
	return ret;
}
*/


/* 
 * apiStartTerminal:
 *     
 */

// 'Clona' e executa o noraterm como processo filho. 
// registra o terminal noraterm como terminal atual.
// pega o pid do terminal atual
// manda uma mensagem pedindo para o terminal dizer hello.

// #obs: Isso funcionou.


int libcStartTerminal (void){

    int PID;

    PID = (int) gramado_system_call ( 900, (unsigned long) "noraterm.bin", 0, 0 );

	// Exibe o PID para debug.
	//printf ("PID = %d \n", PID);

    //registra o terminal como terminal atual.
	gramado_system_call ( 1003, PID, 0, 0 ); 
		
	//invalida a variável.
	PID = -1;
		
	//pega o pid do terminal atual
	PID = (int) gramado_system_call ( 1004, 0, 0, 0 ); 
		
	if ( PID <= 0 )
	{
		printf ("PID fail. We can't send the message\n");
	    return -1;
	}
		
	//manda uma mensagem pedindo para o terminal dizer hello.
	//__SendMessageToProcess ( PID, NULL, MSG_TERMINALCOMMAND, 2001, 2001 );

	return (int) PID;
}



//
// stream buffer support
//

// see: 
// https://linux.die.net/man/3/setvbuf

void 
setbuf (FILE *stream, char *buf){

    if ( (void *) stream == NULL )
        return;

    gramado_system_call ( 610, 
        (unsigned long) stream, 
        (unsigned long) buf, 
        (unsigned long) buf ); 
}


//If buf is a null pointer, this function makes stream unbuffered. 
//Otherwise, it makes stream fully buffered using buf as the buffer. 
//The size argument specifies the length of buf.
//This function is provided for compatibility with old BSD code. 
//Use setvbuf instead. 

void 
setbuffer (FILE *stream, char *buf, size_t size){

    if ( (void *) stream == NULL )
        return;

    gramado_system_call ( 611, 
        (unsigned long) stream, 
        (unsigned long) buf, 
        (unsigned long) size ); 
}


//This function makes stream be line buffered, and allocates the buffer for you.
//This function is provided for compatibility with old BSD code. 
//Use setvbuf instead. 

void setlinebuf (FILE *stream){

    if ( (void *) stream == NULL )
        return;

    gramado_system_call ( 612, 
        (unsigned long) stream, 
        (unsigned long) stream, 
        (unsigned long) stream );
}


// #bugbug
// precisamos do argumento size.
int setvbuf (FILE *stream, char *buf, int mode, size_t size){

    if ( (void *) stream == NULL )
        return EOF;

    return (int) gramado_system_call ( 613, 
                     (unsigned long) stream, 
                     (unsigned long) buf, 
                     (unsigned long) mode ); 
}


unsigned int filesize (FILE * fp){

    if (!fp) 
        return 0;

    fseek (fp, 0, SEEK_END);

    unsigned int ret = (unsigned int) ftell (fp);

    rewind (fp);

    return ret;
}




char *fileread (FILE * fp){

    if (!fp) 
        return 0;

    unsigned int buffer_size = filesize (fp);

    char *buff = (char *) malloc (buffer_size);

    fread (buff, sizeof(char), buffer_size, fp);

    return buff;
}



int dprintf(int fd, const char *format, ...)
{
    if (fd<0)
        return EOF;
 
	return -1; 
}



int vdprintf(int fd, const char *format, va_list ap)
{ 
	return -1; 
}


int vsprintf(char *str, const char *format, va_list ap)
{ 
	return -1; 
}




int vsnprintf(char *str, size_t size, const char *format, va_list ap)
{ 
	return -1; 
}





int vscanf(const char *format, va_list ap)
{ 
	return -1; 
}



int vsscanf(const char *str, const char *format, va_list ap)
{ 
	return -1; 
}


int vfscanf (FILE *stream, const char *format, va_list ap)
{
    if ( (void *) stream == NULL )
        return EOF;

    return -1; 
}



//tmpnam(): 
//SVr4, 4.3BSD, C89, C99, POSIX.1-2001.  
//POSIX.1-2008 marks tmpnam() as obsolete.
char *tmpnam (char *s)
{ 
	return NULL; 
}




//tmpnam_r() is a nonstandard extension that is 
//also available on a few other systems.
char *tmpnam_r(char *s)
{ 
	return NULL; 
}






char *tempnam(const char *dir, const char *pfx)
{ 
	return NULL; 
}




/*
 ERRORS  for tmpfile();

       EACCES Search permission denied for directory in file's path prefix.

       EEXIST Unable to generate a unique filename.

       EINTR  The call was interrupted by a signal; see signal(7).

       EMFILE The per-process limit on the number of open file descriptors
              has been reached.

       ENFILE The system-wide limit on the total number of open files has
              been reached.

       ENOSPC There was no room in the directory to add the new filename.

       EROFS  Read-only filesystem.

 */



FILE *tmpfile(void)
{
	return (FILE *) 0;
}





FILE *fdopen(int fd, const char *mode)
{
	return (FILE *) 0;
}


FILE *freopen(const char *pathname, const char *mode, FILE *stream)
{
    if ( (void *) stream == NULL )
        return (FILE *) 0;

	return (FILE *) 0;
}



/* #todo it needs 'cookie_io_functions_t'
FILE *fopencookie(void *cookie, const char *mode,
                         cookie_io_functions_t io_funcs);
FILE *fopencookie(void *cookie, const char *mode,
                         cookie_io_functions_t io_funcs)
{
	return (FILE *) 0;
}
*/




FILE *open_memstream(char **ptr, size_t *sizeloc)
{
	return (FILE *) 0;
}


    

FILE *open_wmemstream(wchar_t **ptr, size_t *sizeloc)
{
	return (FILE *) 0;
}






FILE *fmemopen(void *buf, size_t size, const char *mode)
{
	return (FILE *) 0;
}





int fgetpos(FILE *stream, fpos_t *pos)
{
    if ( (void *) stream == NULL )
        return EOF;

	return -1; 
}




int fsetpos(FILE *stream, const fpos_t *pos)       
{
    if ( (void *) stream == NULL )
        return EOF;
 
	return -1; 
}




int fpurge(FILE *stream)      
{
    if ( (void *) stream == NULL )
        return EOF;
 
    return -1; 
}




//#todo: esse protótipo pertence à stdio_ext.h
void  __fpurge(FILE *stream)
{
    if ( (void *) stream == NULL )
        return;

}


//ctermid - get controlling terminal name
//POSIX.1-2001, POSIX.1-2008, Svr4.
char *ctermid(char *s)
{ 
   return NULL; 
}



//
// End.
//






