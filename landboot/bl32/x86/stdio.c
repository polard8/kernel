/*
 * File: stdio.c 
 *  
 * Descrição:
 *     Rotinas de input/output.
 *     Biblioteca C do Boot Loader.
 *     Inclui rotinas gráficas no fim do arquivo.
 *     Inclui vsync.
 *
 * 2015 - Created by Fred Nora.
 */

 
#include <bootloader.h>


extern unsigned long SavedBootBlock;
extern unsigned long SavedLFB;
extern unsigned long SavedX;
extern unsigned long SavedY;
extern unsigned long SavedBPP; 

 
extern void my_buffer_load_bitmap_16x16();


// =====================
// panic:
// Message support for fatal error.

void panic (const char *msg)
{
    if ( (void*) msg != NULL )
    {
        if ( *msg != 0 ){
            printf ("BL.BIN: [PANIC] %s\n", msg );
        }
    }

    die();
}


/*
 * scroll:
 *     Scroll the screen in text mode.
 *     #bugbug: Na verdade só usmos modo gráfico ainda.
 */
 
void scroll (void)
{

    //loop
    register unsigned short i=0;
    register unsigned short j=0;


	//inicio da tela
    unsigned short *p1 = (unsigned short *) ScreenStart;

	//inicio da segunda linha
    unsigned short *p2 = (unsigned short *) (ScreenStart + 2 * SCREEN_WIDTH) ;


	//24 vezes
    for (i=0; i < ROWS - 1; i++)
    {
        //80 vezes
        for (j=0; j < SCREEN_WIDTH; j++)
        {
            *p1++ = *p2++;
        };
    };

	//80 vezes
    for (i=0; i < SCREEN_WIDTH; i++)
    {
        *p1++ = 0x07*256 + ' '; 
        //*p1++ = REVERSE_ATTRIB*256 + ' ';
    };
}


/* 
 * bl_clear: 
 * Limpa a tela em text mode. 
 */
 
// #bugbug
// Não usamos mas esse modo de vídeo. 
 
int bl_clear (int color)
{

    //loop
    register unsigned int i=0;

    char *vidmemz = (char *) 0x000B8000; 

    while (i < (80*25*2)) 
    { 
        vidmemz[i] = 219;      i++; 
        vidmemz[i] = color;    i++; 
    };

    g_cursor_x = 0;
    g_cursor_y = 0;

    return 0; 
}


/*
 * kprintf:
 *     Imprime uma string em uma determinada linha. 
 *     @todo: Mudar para bl_print(...) 
 */

// #bugbug
// Não usamos mas esse modo de vídeo. 

// #deprecated

int kprintf ( char *message, unsigned int line, int color )
{
    //loop
    register unsigned int i = 0;

    char *vidmemp = (char *) 0x000B8000; 


    //if ( (void*) message == NULL ){ return -1; };
    //if ( *message == 0 )          { return -1; };

    i = (unsigned int) (line*80*2); 

    while (*message != 0) 
    { 
        if(*message == '\n')
        { 
            line++; 
            i = (unsigned int) (line*80*2); 
            *message++; 
        }
        else
        { 
            vidmemp[i] = *message; 
            *message++; 
            i++; 
            
            vidmemp[i] = color; 
            i++; 
        };
 
        //Nothing.
    }; 

    return 0; 
} 


/*
 * prints:
 *     Print string.
 *     Parte da função printf(). 
 */

static int prints ( 
    char **out, 
    const char *string, 
    int width, 
    int pad )
{

    register int pc = 0, padchar = ' ';


    if (width > 0) 
    {
	    register int len = 0;
		register const char *ptr;
		
		for (ptr = string; *ptr; ++ptr) ++len;
		if (len >= width) width = 0;
		else width -= len;
		if (pad & PAD_ZERO) padchar = '0';
    }

    if ( !(pad & PAD_RIGHT) ) 
    {
		for ( ; width > 0; --width)
		{
		    printchar (out, padchar);
			++pc;
		};
    }


	for ( ; *string ; ++string )
	{
		printchar (out, *string);
		++pc;
	};


	for ( ; width > 0; --width )
	{
		printchar (out, padchar);
		++pc;
	};


    //Nothing.

done:
    return pc;
}


/*
 * printi:
 *     Parte da função printf()
 */
 
static int printi ( 
   char **out, 
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
    
    //loop
    register unsigned int u = i;


    if (i == 0)
    {
        print_buf[0] = '0';
        print_buf[1] = '\0';

        return prints (out, print_buf, width, pad);
    }


	if (sg && b == 10 && i < 0)
	{
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
		    printchar (out, '-');
			++pc;
			--width;
		}else{
			*--s = '-';
		};
    }


// Done.

done:
    return pc + prints(out, s, width, pad);
}


/*
 * print:
 *     Parte da função printf()
 */

static int print (char **out, int *varg)
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

            if (*format == '\0') { break;    }
            if (*format == '%' ) { goto out; }

			if (*format == '-')
			{
				++format;
				pad = PAD_RIGHT;
			}

			while (*format == '0')
			{
				++format;
				pad |= PAD_ZERO;
			};
			
			for ( ; *format >= '0' && *format <= '9'; ++format)
			{
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

    if (out){ 
        **out = '\0'; 
    }

    return pc;
}


/*
 *****************************************
 * printf:
 *     Função printf() da lib C.
 * Obs:
 *     Assuming sizeof(void *) == sizeof(int). 
 */

int printf ( const char *format, ... )
{
    // sincronisa.  
    // vsync();
    
    register int *varg = (int *)(&format);

    return print (0, varg);
}


/*
 * sprintf:
 *     Lib C.
 */
 
int sprintf (char *out, const char *format, ... )
{
    // vsync();

    register int *varg = (int *)(&format);

    return print (&out, varg);
}


/*
 * printchar:
 *     Print a char.
 */

static void printchar (char **str, int c)
{

	//extern int putchar(int c);
    if (str) {

		**str = c;
		++(*str);

    } else { 
        putchar (c);
    };
}



/*
 * putchar:
 *     Put a char.
 */

int putchar (int ch)
{
    outbyte (ch);

    return ch; 
}


/*
 ****************************
 * outbyte:
 *     Trata o caractere antes de por na memória de video.
 */

void outbyte (int c)
{
    // Copy.
    register int Ch=c;

    static char prev = 0;

    //Sendo menor que espaço, não pode ser 'tab,return,back...)    

    if ( Ch <  ' '  && 
         Ch != '\r' && 
         Ch != '\n' && 
         Ch != '\t' && 
         Ch != '\b' )
    {
        return;
    }


    // Sendo maior que 'espaço'. 
    
	// Volta ao início da linha.
    if ( Ch == '\r' )
    {
        g_cursor_x = 0; //volta ao inicio da linha
        prev = Ch;
        return;    
    }
 
   
    // Vai pra próxima linha e volta ao inicio da linha.    
    if ( Ch == '\n' && prev != '\r' )
    {
        g_cursor_y++;      // proxima linha
        g_cursor_x = 0;    // inicio da linha 
        prev = Ch;
        return;
    };
        
    if ( Ch == '\n' && prev == '\r' )
    {
        g_cursor_y++;    //proxima linha
        prev = Ch;
        return; 
    }

    //tab
    if ( Ch == '\t' )
    {
        g_cursor_x += (4);    //criar a var -> 'g_tab_size'
        prev = Ch;
        return;         
    }
        
    //space 
    if ( Ch == ' ' )
    {
        g_cursor_x++; 
        prev = Ch;
        return;         
    }
        
    //delete 
    if ( Ch == 8 )
    {
        g_cursor_x--; 
        prev = Ch;
        return; 
    }

        
    /*
     *  Filtra as dimensões da janela onde esta pintando.
     */
	
    //limite horizontal	
    if ( g_cursor_x > 80)  // 80 = g_coluna_max 
    {
        g_cursor_x = 0;
        g_cursor_y++;  
    
    }else{
        g_cursor_x++;    //Incrementa coluna.                             
    };
    
    
	// Limite vertical. (@todo: Testando limite maior, ja que estamos em modo grafico.)
	if ( g_cursor_y > 74 ) //25 = g_linha_max (50*8 pixels) 
    { 
	    scroll();
        g_cursor_y = 74; //isso pode ir para dentro da função scroll().
    }

	// #importante:
	// Imprime os caracteres normais.

    _outbyte (Ch);


    prev = Ch;    //Atualisa o prev.

    //Nothing.

//done: 
    //return;
}


/*
 ***********************************************
 * _outbyte: 
 *     Coloca um char na tela. Com opções de modo de vídeo.
 */

// Called by outbyte().

void _outbyte (int c)
{

    unsigned long i=0;

    unsigned long x=0;
    unsigned long y=0;

    char ch = (char) c;
    char ch_atributo = (char) g_char_attrib;

    char *vm = (char *) 0x000B8000;  



    // Caso estivermos em modo gráfico.
    if (VideoBlock.useGui == 1)
    {
	    //vsync();
		
        switch (VideoBlock.vesaMode)
        {
		    //@todo: Listar aqui os modos VESA.
		    case 1:
			    my_buffer_char_blt( 8*g_cursor_x, 8*g_cursor_y, COLOR_WHITE, c);
			    break;
				
		    default:
			    //modo gráfico vesa 640x480 24bpp, 8 pixel por caractere.
			    my_buffer_char_blt( 8*g_cursor_x, 8*g_cursor_y, COLOR_WHITE, c);
			    break;
        };
        return;
        //goto done;
    }


	// Caso estivermos em text mode.
    if (VideoBlock.useGui == 0)
    {
	    //calcula o valor do deslocamento para text mode 80x25.
	    y = (unsigned long) (g_cursor_y *80 *2);
        x = (unsigned long) (g_cursor_x *2);    
        i = (unsigned long) (y + x);
        
		//envia o caractere.
        vm[i+0] = ch;             //char.
        vm[i+1] = ch_atributo;    //atributo (foreground,background).
    }

	//Nothing.

done:
    return; 
}


/*
 * printf_main:
 *     Testando a função printf().
 *
 * if you compile this file with
 *   gcc -Wall $(YOUR_C_OPTIONS) -DTEST_PRINTF -c printf.c
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
 */


int printf_main (void){
	
/*	
	char *ptr = "Hello world!";
	char *np = 0;
	int i = 5;
	unsigned int bs = sizeof(int)*8;
	int mi;
	char buf[80];

	mi = (1 << (bs-1)) + 1;
	
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

//done:	
	return 0;
}


/*
 * input:
 *     Coloca os caracteres digitados em uma string. 
 */

unsigned long input (unsigned long ch){
	
	//Converte.
	char c = (char) ch;    
	
	//Filtra limite.
	
	if (prompt_pos > 250)
	{ 
	    printf ("input: The command is too large");	
	    return (unsigned long) 0; 
	}
 	
	//Trata caractere digitado.
	
	switch (c)
	{
	    //enter
		case KEY_RETURN:
	    //case 0x1C:
		    prompt[prompt_pos] = (char )'\0';
            goto input_done;
		    break;

	    //backspace
		case 0x0E:
            if( prompt_pos <= 0 ){ 
			    prompt[prompt_pos] = (char ) '\0';
				break; 
			};
		    
			//Apaga o anterior no buffer.
			prompt_pos--;
			prompt[prompt_pos] = (char ) '\0';
			
			//Apaga o atual
			printf ("%c",' ');
			//Apaga o anterior
			g_cursor_x--;
			g_cursor_x--;
			printf ("%c",'_');
			g_cursor_x--;
			break;
			
		default:
		    prompt[prompt_pos] = c;
		    prompt_pos++;          //incrementa fila.
			putchar (c);
			printf ("%c",'_');
			g_cursor_x--;
			break;
	};


//Nothing.
input_more:
    return 0;

//Nothing.
input_done:
    return KEY_RETURN;

}


/*
 * my_buffer_horizontal_line:
 *     Pinta uma linha horinzontal no Back Buffer. 
 */

void 
my_buffer_horizontal_line ( 
    unsigned long x1,
    unsigned long y, 
    unsigned long x2, 
    unsigned long color )
{

    while (x1 < x2)
    {
        my_buffer_put_pixel ( color, x1, y, 0 );
        x1++;  
    };
}


/*
 * my_buffer_put_pixel: 
 *     Coloca um pixel o buffer 1.            
 * a = cor
 * b = x
 * c = y
 * d = null
 */
 
extern void gui_buffer_putpixel();

void 
my_buffer_put_pixel ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{

	//asm volatile(" \n "
	//	          : // no inputs
	//	          : "a"(ax), "b"(bx), "c"(cx), "d"(dx) );


	//#Warning
	//suspenso, vamos tentar não usar o assembly
	//gui_buffer_putpixel(); 
	//return;
	
	//SOFTWARELIB_BACKBUFFER EQU (0x1000000 - 0x800000)
	unsigned char *where = (unsigned char *) (0x1000000 - 0x800000); //0xC0800000;
		
	unsigned long color = (unsigned long) ax;
	
	char b, g, r, a;
	
	b = (color & 0xFF);
	g = (color & 0xFF00)   >> 8;
	r = (color & 0xFF0000) >> 16;
	a = (color >> 24) + 1;


	int x = (int) bx;
	int y = (int) cx;
	
	
	// = 3; 
	//24bpp
	int bytes_count=0;
	

    switch (SavedBPP){

    case 32:
        bytes_count = 4;
        break;

    case 24:
        bytes_count = 3;
        break;

    // ...

    //#bugbug
    default:
        bytes_count = 3;
        break;
    };



	// #importante
	// Pegamos a largura do dispositivo.
	
	int width = (int) SavedX; 
	
	int offset = (int) ( (bytes_count*width*y) + (bytes_count*x) );
	
	where[offset]    = b;
	where[offset +1] = g;
	where[offset +2] = r;

	//teste
	if ( SavedBPP == 32 )
	{
	    where[offset +3] = a;
	}
}


/*
 * my_buffer_char_blt:
 *     Draw a char using ROM's font. 
 */

void 
my_buffer_char_blt ( 
    unsigned long x, 
    unsigned long y, 
    unsigned long color, 
    unsigned long c )
{ 

    int x2=0; 
    int y2=0;
    unsigned char bit_mask = 0x80;

    // Font address and char address.
    //char height = 8

    char *work_char = (char*) 0x000FFA6E + (c * 8);


    for ( y2=0; y2<8; y2++ )
    {
        bit_mask = 0x80;

        for ( x2=0; x2<8; x2++ )
        {
            if ( (*work_char & bit_mask) ){
                my_buffer_put_pixel( color, x + x2, y, 0);
            } 
            bit_mask = ( bit_mask >> 1 );
        };
                       
		y++;            //Próxima linha.
		work_char++;    //Incrementa 8 bits.
	};
}


/*
 * vsync: 
 *     Sincroniza a pintura com o retraço vertical.
 *     OBS: Talvez deva usar cli e sti 
 */

void vsync (){

	//Wait until any previous retrace has ended 
    do {
     //nothing.
    }while ( gui_inb(0x3DA) & 8 );

	//Wait until a new retrace has just begun 
    do {
	 //nothing.
    } while( !(gui_inb(0x3DA) & 8) );
}


/*
 * gui_inb:
 *     Pega um byte na porta. 
 */

char gui_inb (int port){

    char value = 0;

    value = in8 (port);

	asm (" nop \n");
	asm (" nop \n");
	asm (" nop \n");
	asm (" nop \n"); 

    return value;
}


/*
void refresh_screen2();
void refresh_screen2()
{
    unsigned char *backbuffer  = (unsigned char *) (0x1000000 - 0x800000); 
    unsigned char *frontbuffer = (unsigned char *) g_lbf_pa; 

    int i=0;
    for(i=0; i<(800*600*6); i++)
        frontbuffer[i] = backbuffer[i];
}
*/



// color black
// 800x600x32
void clear_backbuffer(void)
{
    int i=0;

    // Backbuffer address.
    // Is this a good address ?
    // almos 16MB mark?

    // #todo
    // We can use unsigned longs.

    unsigned char *backbuffer  = (unsigned char *) (0x1000000 - 0x800000); 

    for (i=0; i<(800*600*4); i++)
    {
        backbuffer[i] = 0;
    };
}



//#bugbug
//@todo: Rever isso.
//    g_cursor_x = 0;
//    g_cursor_y = 0;
unsigned long get_cursor_x ()
{  
    //unsigned long *int_args  = (unsigned long *) 0x0090000;
    //return   int_args[4];
    
    return g_cursor_x;
}

//#bugbug
//@todo: Rever isso.
//    g_cursor_x = 0;
//    g_cursor_y = 0;
unsigned long get_cursor_y ()
{ 
    //unsigned long *int_args  = (unsigned long *) 0x0090000;
    //return  int_args[8]; 
    
    return g_cursor_y;
}


/*
 * carrega_bitmap_16x16:
 *     Carrega um bitmap de 16x16.
 *     Põe bitmap no buffer.
 *
 * @todo: Mudar o nome, colocar em outro arquivo.
 *
 * a - endereço da imagem. 
 * b - x
 * c - y 
 * d - null
 */

void 
carrega_bitmap_16x16 ( 
    unsigned long ax, 
    unsigned long bx, 
    unsigned long cx, 
    unsigned long dx )
{

    asm volatile (" \n "
        : // no inputs
        : "a"(ax), "b"(bx), "c"(cx), "d"(dx) );

    // Coloca no buffer. 
    // Não precisa esperar o retraço vertical.

    my_buffer_load_bitmap_16x16 (); 
}


//
// End.
//

