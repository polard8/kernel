
// hello3.
//
// O terminal virtual noraterm está chamando esse programa para fazer
// testes com a libc.
//


//See:
//https://solarianprogrammer.com/2019/04/08/c-programming-ansi-escape-codes-windows-macos-linux-terminals/

/*
export const reset = "\x1b[0m"
export const bright = "\x1b[1m"
export const dim = "\x1b[2m"
export const underscore = "\x1b[4m"
export const blink = "\x1b[5m"
export const reverse = "\x1b[7m"
export const hidden = "\x1b[8m" 
 */


// Credits:
/* vsprintf.c -- Lars Wirzenius & Linus Torvalds. */
/* Wirzenius wrote this portably, Torvalds fucked it up :-) */



// rtl
//#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
//#include <string.h>



/* we use this so that we can do without the ctype library */
#define __is_digit(c)	((c) >= '0' && (c) <= '9')

static int skip_atoi(const char **s)
{
	int i=0;

	while (__is_digit(**s))
		i = i*10 + *((*s)++) - '0';
	return i;
}

#define ZEROPAD	1		/* pad with zero */
#define SIGN	2		/* unsigned/signed long */
#define PLUS	4		/* show plus */
#define SPACE	8		/* space if plus */
#define LEFT	16		/* left justified */
#define SPECIAL	32		/* 0x */
#define SMALL	64		/* use 'abcdef' instead of 'ABCDEF' */

#define do_div(n,base) ({ \
int __res; \
__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
__res; })

static char * number(char * str, int num, int base, int size, int precision
	,int type)
{
	char c,sign,tmp[36];
	const char *digits="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int i;

	if (type&SMALL) digits="0123456789abcdefghijklmnopqrstuvwxyz";
	if (type&LEFT) type &= ~ZEROPAD;
	if (base<2 || base>36)
		return 0;
	c = (type & ZEROPAD) ? '0' : ' ' ;
	if (type&SIGN && num<0) {
		sign='-';
		num = -num;
	} else
		sign=(type&PLUS) ? '+' : ((type&SPACE) ? ' ' : 0);
	if (sign) size--;
	if (type&SPECIAL)
		if (base==16) size -= 2;
		else if (base==8) size--;
	i=0;
	if (num==0)
		tmp[i++]='0';
	else while (num!=0)
		tmp[i++]=digits[do_div(num,base)];
	if (i>precision) precision=i;
	size -= precision;
	if (!(type&(ZEROPAD+LEFT)))
		while(size-->0)
			*str++ = ' ';
	if (sign)
		*str++ = sign;
	if (type&SPECIAL)
		if (base==8)
			*str++ = '0';
		else if (base==16) {
			*str++ = '0';
			*str++ = digits[33];
		}
	if (!(type&LEFT))
		while(size-->0)
			*str++ = c;
	while(i<precision--)
		*str++ = '0';
	while(i-->0)
		*str++ = tmp[i];
	while(size-->0)
		*str++ = ' ';
	return str;
}


int ____Wirzenius_Torvalds_vsprintf(char *buf, const char *fmt, va_list args)
{
	int len;
	int i;
	char * str;
	char *s;
	int *ip;

	int flags;		/* flags to number() */

	int field_width;	/* width of output field */
	int precision;		/* min. # of digits for integers; max
				   number of chars for from string */
	int qualifier;		/* 'h', 'l', or 'L' for integer fields */

	for (str=buf ; *fmt ; ++fmt) {
		if (*fmt != '%') {
			*str++ = *fmt;
			continue;
		}
			
		/* process flags */
		flags = 0;
		repeat:
			++fmt;		/* this also skips first '%' */
			switch (*fmt) {
				case '-': flags |= LEFT; goto repeat;
				case '+': flags |= PLUS; goto repeat;
				case ' ': flags |= SPACE; goto repeat;
				case '#': flags |= SPECIAL; goto repeat;
				case '0': flags |= ZEROPAD; goto repeat;
				}
		
		/* get field width */
		field_width = -1;
		if (__is_digit(*fmt))
			field_width = skip_atoi(&fmt);
		else if (*fmt == '*') {
			/* it's the next argument */
			field_width = va_arg(args, int);
			if (field_width < 0) {
				field_width = -field_width;
				flags |= LEFT;
			}
		}

		/* get the precision */
		precision = -1;
		if (*fmt == '.') {
			++fmt;	
			if (__is_digit(*fmt))
				precision = skip_atoi(&fmt);
			else if (*fmt == '*') {
				/* it's the next argument */
				precision = va_arg(args, int);
			}
			if (precision < 0)
				precision = 0;
		}

		/* get the conversion qualifier */
		qualifier = -1;
		if (*fmt == 'h' || *fmt == 'l' || *fmt == 'L') {
			qualifier = *fmt;
			++fmt;
		}

		switch (*fmt) {
		case 'c':
			if (!(flags & LEFT))
				while (--field_width > 0)
					*str++ = ' ';
			*str++ = (unsigned char) va_arg(args, int);
			while (--field_width > 0)
				*str++ = ' ';
			break;

		case 's':
			s = va_arg(args, char *);
			len = strlen(s);
			if (precision < 0)
				precision = len;
			else if (len > precision)
				len = precision;

			if (!(flags & LEFT))
				while (len < field_width--)
					*str++ = ' ';
			for (i = 0; i < len; ++i)
				*str++ = *s++;
			while (len < field_width--)
				*str++ = ' ';
			break;

		case 'o':
			str = number(str, va_arg(args, unsigned long), 8,
				field_width, precision, flags);
			break;

		case 'p':
			if (field_width == -1) {
				field_width = 8;
				flags |= ZEROPAD;
			}
			str = number(str,
				(unsigned long) va_arg(args, void *), 16,
				field_width, precision, flags);
			break;

		case 'x':
			flags |= SMALL;
		case 'X':
			str = number(str, va_arg(args, unsigned long), 16,
				field_width, precision, flags);
			break;

		case 'd':
		case 'i':
			flags |= SIGN;
		case 'u':
			str = number(str, va_arg(args, unsigned long), 10,
				field_width, precision, flags);
			break;

		case 'n':
			ip = va_arg(args, int *);
			*ip = (str - buf);
			break;

		default:
			if (*fmt != '%')
				*str++ = '%';
			if (*fmt)
				*str++ = *fmt;
			else
				--fmt;
			break;
		}
	}
	*str = '\0';
	return str-buf;
}




static char __printbuf[1024];

static int ____Torvalds_printf(const char *fmt, ...)
{
	int this_tty_id = 0;
	
	va_list args;
	int i;

	va_start(args, fmt);
	
    //this_tty_id = (int) gramado_system_call ( 266, getpid(), 0, 0 );        	


	//write ( this_tty_id, 
	//    __printbuf,
	//    i=____Wirzenius_Torvalds_vsprintf(__printbuf, fmt, args) );


    // Escrevendo no console virtual.
    //IN: console number, buf, count
	write_VC ( 0, 
	    __printbuf,
	    i=____Wirzenius_Torvalds_vsprintf(__printbuf, fmt, args) );

	va_end(args);
	return i;
}









#define __ESC "\x1b"
#define __CSI "\x1b["

//char pos [] = "\x1B[0;0H";


#define STANDARD_ASCII_MAX 128





int
__PostMessageToProcess ( int pid, 
                         unsigned long window, 
                         int message,
                         unsigned long long1,
                         unsigned long long2 );
                          
int
__PostMessageToProcess ( int pid, 
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


    return (int) gramado_system_call ( 112 , 
                     (unsigned long) &message_buffer[0], 
                     (unsigned long) pid, 
                     (unsigned long) pid );
}


/*
 *********************************
 * main:
 * 
 */

	// #IMPORTANTE:
	// Apenas uma função de introdução usando o modo draw.
	// Depois todas as outras devem usar o modo NORMAL.
	// Nesse modo o terminal não será notificado.

int main2 ( int argc, char *argv[] );
int main2 ( int argc, char *argv[] ){

    FILE *fp;

    unsigned char count;
    unsigned char standard_ascii_max = STANDARD_ASCII_MAX;

    char buffer[512];
    char buffer2[] = "DURTY...........";

    int __terminal_pid = -1;




	//
	// Draw mode
	//

    //libc_set_output_mode (LIBC_DRAW_MODE);
    printf ("hello3: Testing libc in LIBC_DRAW_MODE ...\n"); 
    printf ("hello3 PID %d \n", getpid() );


    __terminal_pid = (int) gramado_system_call ( 1004, 0, 0, 0 ); 
    
    if ( __terminal_pid < 0)
    {
		printf ("We couldn'd connect to a virtual terminal! *exit");
		exit (-1);
    }
    
    printf ("Terminal PID %d \n",__terminal_pid);


    //
    // Say hello to terminal !
    //

    // msg 2001: O termilal dirá olá !
    
    unsigned long message_buffer[5];
    
    // Prepara o buffer.
    // window, MSG_TERMINALCOMMAND, 2001, 2001.
    message_buffer[0] = (unsigned long) 0;    //window
    message_buffer[1] = (unsigned long) 100;  //message;  
    message_buffer[2] = (unsigned long) 2001; //long1; 
    message_buffer[3] = (unsigned long) 2001; //long2; 

        // Pede para o kernel enviar uma mensagem para determinado processo.
        gramado_system_call ( 112 , 
              (unsigned long) &message_buffer[0], 
              (unsigned long) __terminal_pid, 
              (unsigned long) __terminal_pid );
                         
 
    // #importante
    // Já que conseguimos nos comunicar com  o terminal,
    // então podemos pedir para ele usar nosso stdout para
    // pegar o input.


    // Configurando o stdout da CurrentTTY,
    // Lugar de onde o terminal pega os chars
    // Passremos nossa stdout, usada pela nossa libc.

    gramado_system_call ( 1001, stdout, stdout, stdout );


	//
	// Normal mode
	//

	// #importante:
	// Habilitando o modo normal e usando ele até o fim.
	
    libc_set_output_mode (LIBC_NORMAL_MODE);
    printf ("hello3: Testing libc in LIBC_NORMAL_MODE ...\n"); 

	printf (" ==== Begin of test ==== \n");
	
	//
	// testing fread.
	//
	

	/*
    fp = fopen ("init.txt", "r");
    
    if (fp != NULL) 
    {
		//espearamos que isso escreva em fp.

        //fprintf (fp, "testing fprintf normal mode\n");
        
        //não funcionou.
        //sprintf( buffer, "fwrite durty" );
        
        //funcionou
        fwrite ( buffer2, 1, 7, fp);	
        
        //funcionou.
		//ler 32 bytes do arquivo e coloca-los no buffer.
        fread ( buffer, 1, 32, fp );
        
        // finalisa o arquivo.
        buffer[511] = 0;
                
        //fclose (rm);
    }else{
        printf("File Not Found.\r\n");
	};
    */

	// isso pode fazer com que o terminal imprima na tela.
	//fprintf ( stdout, ">>> normal mode fprintf <<<\n");
	
	//Escrevendo em stdout agora com printf.
	
	//printf ("done: fim do teste do fread.\n");
	//printf ("{Testando libc03 ...} ");
	//printf ("\n");
	
	/*
    for ( count=0; count<standard_ascii_max; count++ )
    {
		printf (" %d - %c", count, count);
        
		if ( count % 4 == 0 )
		{
            printf ("\n");
		}
    };	
	*/
	
	//esperando um pouquinho
	//for ( count=0; count < 99999; count++ )
	
	//printf ("{normal mode} ");
	//printf ("\n");
	//printf ("{Done!} ");
	//fprintf (stdout, "{fprintf} ");
	
	
	
	//
	//   TESTANDO LIBC 
	//
	
	// Testando rotinas da libc
	// Mostrando output no terminal noraterm.
	
//ex:
//http://kirste.userpage.fu-berlin.de/chemnet/use/info/libc/libc_7.html#SEC80
	
	//sprintf, snprintf, asprintf, obstack_printf 
	//vprintf, vfprintf, vsprintf, vsnprintf, vasprintf  
	
	//#test
	//Ok. Testamos essas funções de output e as string foram exibidas
	//no terminal virtual noraterm.
		
	printf ("{printf 1 ");
	printf ("2 ");
	printf ("3}\n");

    printf ("*\n");
    
    //printf ("Esse eh um texto grande .... um texto realmente grand ..... ooops\n");

	//printf("\x1b[1Am");  //cursor up
	//printf("\x1b[1Bm");  //cursor down
	//printf("\x1b[1Cm");
	//printf("\x1b[1Dm");
	//printf("\x1b[1Em");
	//printf("\x1b[1Fm");
	//printf("\x1b[1Gm");
	   
	puts ("{puts}\n");
	
	fprintf (stdout, "{fprintf}\n");
	
	
	// #test
	// vamos ler o stdout que deve ser o mesmo arquivo que 
    //  o terminal está colcoando suas coisas.

    
    char line[1024];
    //stdin = stdout;
	//Read a command line 
	
	//fscanf(stdout, "%s", line);
    
    while(1)
    {
        //int c = getchar(); 
        //printf ("%c", c); 
    }



    //fputc = putc

    //printf ("fputc={");
	  //fputc ('X',stdout);
	  //fputc (' ',stdout);
    //printf ("}\n");


    //printf ("putc={");
	  //putc ('Y',stdout);
	  //putc (' ',stdout);
    //printf ("}\n");
    

    //printf ("putchar={");
	  //putchar ('Z');
	  //putchar (' ');
    //printf ("}\n");
    
    
	//fputs("{fputs}\n",stdout);
	
	//
	// ESC tests
	//
	
	//testing scape s.
	//printf("\x1b[m");  
	//printf("\x1b[1;2;3m");  
	
   //  printf("\x1b[0m");	//Reset colors
     
  //printf("\x1b[2J");    // Clear the entire screen
  //printf("\x1b[1J");    // Clear the screen from cursor to the beginning
  //printf("\x1b[0J");    // Clear the screen from cursor to the end    
    
//printf("\x1b2dK");    // Clear the current line
//printf("\x1b1dK");    // Clear the current line from cursor to left (beginning of the line)
//printf("\x1b0dK");    // Clear the current line from cursor to right (end of the line) 
	
//printf("\x1b[6n");    // Print current cursor position	
	
	
	//testando o segundo \n
	//precisaremos renovar o buffer la no terminal?
	//printf ("Hello\n");  
	
    printf ("1 ");
    printf ("2 ");
    printf ("3 ");
    printf ("4 ");
    printf ("5 ");
    printf ("6\n");
    //printf ("7 ");
    //printf ("8 ");
    //printf ("9 ");
    //printf ("10 ");
    //printf ("11 ");
    //printf ("12 ");
    //printf ("13 ");
    //printf ("14 ");
    //printf ("15 \n");
    
	//#bugbug
	//Esse segundo teste não funcionou.
	//depois do \n a libc não se comportou como esperado.
	//provavelmente algo com a renovação do buffer.
	
	//testando escape sequencies,
	//printf ("{\033[0m} ");
	//printf ("{\x1b[0m} ");
	//printf ("*fim-do-test\n");
			    
    //printf ("Esse eh um texto grande .... um texto realmente grand ..... ooops\n");
	printf ("almost \n *hg... \n");  
	//printf ("*hang\n");
	printf (" ==== End of test ====\n");
	

done: 

	//
	// Draw mode
	//

    libc_set_output_mode (LIBC_DRAW_MODE);
    printf ("hello3: Done *hang\n"); 
    while(1){}

    
    // Testando a saída normal.
    // Aqui retornamos para o crt0.o.
    
    return 0;
}





/*
 * 
 * 
 * 
 * 
 */

// #test
// This app is called by noraterm.
// We write in a tty and noraterm reads from it.

int main ( int argc, char *argv[] ){


    int ____tty_id = -1;
    int ____this_tty_id = -1;
    char __wbuf2[512]; //line ?  write
    char __rbuf2[512]; //line ? read 
    int __w_size2 = 0;


    // link by pid
    // Linking against noraterm.
    
    gramado_system_call ( 267,
        getpid(),    // master (shell?)
        getppid(),   // slave pai (terminal?)
        0 );
            
    //
    // scr
    //    
        
        
        // Get the tty for this process.            
        ____this_tty_id = gramado_system_call ( 266, getpid(), 0, 0 );
        printf ("The tty for this process is %d\n", ____this_tty_id);
        
        
        while(1){
         //Escrevendo na tty desse processo e na tty slave pra leitura.
         write_ttyList ( ____this_tty_id, 
             __wbuf2, 
             __w_size2 = sprintf (__wbuf2,"hello3:THIS IS A MAGIC STRING\n")  );
        }
       
       
 
     //
     // get tty
     //      
       

     // Get the tty id of the parent process. The terminal.
     //____tty_id = gramado_system_call ( 266, getppid(), 0, 0 );
     //printf ("hello3: The tty for parent process is %d \n", 
         //____tty_id );
     
     
     //
     // write in the tty of parent
     //
        
        
     // Escrevendo na tty do processo pai para leitura.
     
     //write_ttyList ( ____tty_id, 
         //__wbuf2, 
         //__w_size2 = sprintf (__wbuf2,"hello3: THIS IS A MAGIC STRING \n")  );

            
    // usando o write_VC pra escrever no console virtual '0'. 
    //____Torvalds_printf ("Writing from hello3 ...\n");
    return 0;
}

















