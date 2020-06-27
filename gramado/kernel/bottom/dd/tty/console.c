/*
 * File: console.c 
 *
 *     Writing on the console device.
 */


// Esse console é full screen e não precisa de muitos recursos gráficos.
// Somete o super user poderá usá-lo.
// Só existem quatro consoles virtuais. Um deles será usado para
// registrar o servidor gráfico.
// Para pseudo terminais veja: vt.c


// #todo:
// Control Sequence Introducer (CSI) 
// See:
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
//



#include <kernel.h>


// Usado para manipular csi
static unsigned long __state = 0;

#define NPAR 16
static unsigned long npar, par[NPAR];
static unsigned long ques=0;
static unsigned char attr=0x07;



void __local_ri (void)
{
    //#todo
}

void __local_gotoxy ( int new_x, int new_y, int console_number )
{

   //deletar.
	//if (new_x>=columns || new_y>=lines)
		//return;
	//x=new_x;
	//y=new_y;
	//pos=origin+((y*columns+x)<<1);
		
     if ( new_x >= (TTY[console_number].cursor_right-1) )
         return;
         
    
    if ( new_y >= (TTY[console_number].cursor_bottom-1) )
        return;
        

    TTY[console_number].cursor_x = new_x; 
    TTY[console_number].cursor_y = new_y;
}



// #bugbug
// Isso tá errado.
#define __RESPONSE "\033[?1;2c"
void __respond (int console_number)
{
    char * p = __RESPONSE;

    while (*p) {
        
        //PUTCH(*p,tty->read_q);
        console_putchar ( (int) *p, console_number );
        p++;
    }

	//copy_to_cooked(tty);
}

static int saved_x=0;
static int saved_y=0;

void __local_save_cur (int console_number)
{
	saved_x = TTY[console_number].cursor_x;
	saved_y = TTY[console_number].cursor_y;
}

void __local_restore_cur (int console_number)
{
	TTY[console_number].cursor_x = saved_x;
	TTY[console_number].cursor_y = saved_y;
}


// See:
// https://en.wikipedia.org/wiki/Control_character
// https://en.wikipedia.org/wiki/C0_and_C1_control_codes#Device_control

void __local_insert_char ( int console_number )
{

	//int i=x;
	//unsigned short tmp,old=0x0720;
	//unsigned short * p = (unsigned short *) pos;

/*
	while (i++ < columns) {

		// Salvo o char da posição atual.
		tmp = *p;

        // coloco o char de controle na posição atual
        // ou o caractere salvo anteriomente.
		*p=old;

        // coloco o caractere salvo para uso futuro.
		old=tmp;

        //avança até o fim da linha.
		p++;
	}
*/

    //int i = TTY[console_number].cursor_x;
    //int tmp;
    //int old = 0x20;
    
    // #bugbug
    // Não é possível fazer essa rotina pois não temos um buffer e chars.

    //while (i++ < TTY[console_number].cursor_height ) {};
    
    console_putchar (0x20, console_number);
}

void __local_insert_line (int console_number)
{

	int oldtop,oldbottom;

	oldtop    = TTY[console_number].cursor_top;
	oldbottom = TTY[console_number].cursor_bottom;

	TTY[console_number].cursor_top    = TTY[console_number].cursor_y;
	TTY[console_number].cursor_bottom = TTY[console_number].cursor_bottom;
	
    console_scroll (console_number);

	TTY[console_number].cursor_top    = oldtop;
	TTY[console_number].cursor_bottom = oldbottom;
}


void __local_delete_char(int console_number)
{
	
	console_putchar ( ' ', console_number);
	    
/*
	int i;
	unsigned short * p = (unsigned short *) pos;

	if (x >= columns)
		return;

	i = x;
	while (++i < columns) 
	{
		*p = *(p+1);
		p++;
	}
	*p=0x0720;
*/
}


void __local_delete_line(int console_number)
{

    int oldtop,oldbottom;

	oldtop    = TTY[console_number].cursor_top;
	oldbottom = TTY[console_number].cursor_bottom;

	
	TTY[console_number].cursor_top    = TTY[console_number].cursor_y;
	TTY[console_number].cursor_bottom = TTY[console_number].cursor_bottom;

    //#todo
	//scrup();

	TTY[console_number].cursor_top    = oldtop;
	TTY[console_number].cursor_bottom = oldbottom;
}



void csi_J (int par)
{
	/*
	long count __asm__("cx");
	long start __asm__("di");

	switch (par) {
		case 0:   //erase from cursor to end of display 
			count = (scr_end-pos)>>1;
			start = pos;
			break;
		case 1:	//erase from start to cursor 
			count = (pos-origin)>>1;
			start = origin;
			break;
		case 2: // erase whole display 
			count = columns*lines;
			start = origin;
			break;
		default:
			return;
	}
	__asm__("cld\n\t"
		"rep\n\t"
		"stosw\n\t"
		::"c" (count),
		"D" (start),"a" (0x0720)
		:"cx","di");
		
	*/
}


void csi_K(int par)
{
   /*
	long count __asm__("cx");
	long start __asm__("di");

	switch (par) {
		case 0:	   //erase from cursor to end of line 
			if (x>=columns)
				return;
			count = columns-x;
			start = pos;
			break;
		case 1:	//erase from start of line to cursor 
			start = pos - (x<<1);
			count = (x<columns)?x:columns;
			break;
		case 2: //erase whole line 
			start = pos - (x<<1);
			count = columns;
			break;
		default:
			return;
	}
	__asm__("cld\n\t"
		"rep\n\t"
		"stosw\n\t"
		::"c" (count),
		"D" (start),"a" (0x0720)
		:"cx","di");
   */
}


void csi_m(void)
{
    int i;

	for (i=0;i<=npar;i++)
		switch (par[i]) {
			
			case 0:
			    attr=0x07;
			    break;
			case 1:
			    attr=0x0f;
			    break;
			case 4:
			    attr=0x0f;
			    break;
			case 7:
			    attr=0x70;
			    break;
			case 27:
			    attr=0x07;
			    break;
		}
}


void csi_M ( int nr, int console_number )
{

	if ( nr > TTY[console_number].cursor_height )
		nr = TTY[console_number].cursor_height;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_delete_line(console_number);
}


void csi_L (int nr, int console_number)
{

	if (nr > TTY[console_number].cursor_height)
		nr = TTY[console_number].cursor_height;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_insert_line(console_number);
}


void csi_P (int nr, int console_number)
{

	if (nr > TTY[console_number].cursor_right -1 )
		nr = TTY[console_number].cursor_right -1 ;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_delete_char(console_number);
}


void csi_at (int nr, int console_number)
{

	if (nr > TTY[console_number].cursor_right -1 )
		nr = TTY[console_number].cursor_right -1 ;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_insert_char(console_number);
}





/*
 ***************************************
 * _console_outbyte:
 * 
 *    Outputs a char on the console device;
 */
 

void _console_outbyte (int c, int console_number){
	
    unsigned long i;
	
	unsigned long x;
	unsigned long y;
	
    //O caractere.
	
	char ch = (char) c;	
	
	// #test
	// Tentando pegar as dimensões do char.
	// #importante: 
	// Não pode ser 0, pois poderíamos ter divisão por zero.
	
	
	int cWidth = get_char_width ();
	int cHeight = get_char_height ();
	

	if ( cWidth == 0 || cHeight == 0 ){
		debug_print ("_console_outbyte: char w h");
		panic ("_console_outbyte: fail w h ");
	}
	
	// #bugbug
	// Caso estejamos em modo texto.
	// Isso ainda não é suportado.
	
	if ( VideoBlock.useGui == 0 ){
		debug_print ("_console_outbyte: kernel in text mode");
	    panic ("_console_outbyte: kernel in text mode");
	}
	
	
	// #Importante: 
	// Essa rotina não sabe nada sobre janela, ela escreve na tela como 
	// um todo. Só está considerando as dimensões do 'char'.


    // Caso estivermos em modo gráfico.
    // #importante: 
    // Essa rotina de pintura deveria ser exclusiva para dentro do terminal.
    // Então essa flag não faz sentido.		
	 
    if ( VideoBlock.useGui == 1 )
    {
        if ( stdio_terminalmode_flag == 1 )
        {
			
			// ## NÃO TRANPARENTE ##
            // se estamos no modo terminal então usaremos as cores 
            // configuradas na estrutura do terminal atual.
            // Branco no preto é um padrão para terminal.
			
            draw_char ( cWidth * TTY[console_number].cursor_x, 
                       cHeight * TTY[console_number].cursor_y, 
                       c, 
                       COLOR_TERMINALTEXT, COLOR_TERMINAL2 );

		}else{
			
			// ## TRANSPARENTE ##
		    // se não estamos no modo terminal então usaremos
		    // char transparente.
            // Não sabemos o fundo. Vamos selecionar o foreground.
			
			drawchar_transparent ( 
			    cWidth* TTY[console_number].cursor_x, 
			    cHeight * TTY[console_number].cursor_y, 
				TTY[console_number].cursor_color, 
				c );
		};
		
		// Nothing.
	};
}


/*
 *******************************************************************
 * outbyte:
 *     Trata o caractere a ser imprimido e chama a rotina /_outbyte/
 * para efetivamente colocar o caractere na tela.
 *
 * Essa rotina é chamada pelas funções: /putchar/scroll/.
 * @todo: Colocar no buffer de arquivo.
 */

void console_outbyte (int c, int console_number){

    static char prev = 0;


    unsigned long __cWidth = gwsGetCurrentFontCharWidth();
    unsigned long __cHeight = gwsGetCurrentFontCharHeight();

    if ( __cWidth == 0  ||  __cHeight == 0 ){
        panic ("console_outbyte: char size\n");
    }


	// Obs:
	// Podemos setar a posição do curso usando método,
	// simulando uma variável protegida.
	
//checkChar:        
      
    //Opção  
    //switch ?? 


    //form feed - Nova tela.
    if ( c == '\f' )
    {
        TTY[console_number].cursor_y = TTY[console_number].cursor_top;
        TTY[console_number].cursor_x = TTY[console_number].cursor_left;
        return;
    }

    // #m$. 
    // É normal \n retornar sem imprimir nada.
    
    //Início da próxima linha. 
    if ( c == '\n' && prev == '\r' ) 
    {
		// #todo: 
		// Melhorar esse limite.
        if ( TTY[console_number].cursor_y >= (TTY[console_number].cursor_bottom-1) )
        {
            //debug_print ("console_outbyte: scroll 1\n"); 
            console_scroll (console_number);

            TTY[console_number].cursor_y = (TTY[console_number].cursor_bottom-1);

            prev = c; 

        }else{

            TTY[console_number].cursor_y++;
            TTY[console_number].cursor_x = TTY[console_number].cursor_left;
            prev = c;
        };

        return;
    };


    //Próxima linha no modo terminal.
    if ( c == '\n' && prev != '\r' ) 
    {
        if ( TTY[console_number].cursor_y >= (TTY[console_number].cursor_bottom-1) )
        {

            //debug_print ("console_outbyte: scroll 2\n"); 
            console_scroll (console_number);
            
            TTY[console_number].cursor_y = (TTY[console_number].cursor_bottom-1);
            prev = c;

        }else{

            TTY[console_number].cursor_y++;

			//Retornaremos mesmo assim ao início da linha 
			//se estivermos imprimindo no terminal.
            if ( stdio_terminalmode_flag == 1 )
            {
                TTY[console_number].cursor_x = TTY[console_number].cursor_left;	
            } 

			//verbose mode do kernel.
			//permite que a tela do kernel funcione igual a um 
			//terminal, imprimindo os printfs um abaixo do outro.
			//sempre reiniciando x.
            if ( stdio_verbosemode_flag == 1 )
            {
                TTY[console_number].cursor_x = TTY[console_number].cursor_left;
            } 

			//Obs: No caso estarmos imprimindo em um editor 
			//então não devemos voltar ao início da linha.

            prev = c;
        };

        return;
    };


	//tab
	//@todo: Criar a variável 'g_tab_size'.
    if( c == '\t' )  
    {
        TTY[console_number].cursor_x += (8);
        //g_cursor_x += (4); 
        prev = c;
        
        return; 

		//Não adianta só avançar, tem que apagar o caminho até lá.
		
		//int tOffset;
		//tOffset = 8 - ( g_cursor_left % 8 );
		//while(tOffset--){
		//	_outbyte(' ');
		//}
		//Olha que coisa idiota, e se tOffset for 0.
		//set_up_cursor( g_cursor_x +tOffset, g_cursor_y );
		//return;        
    };


	//liberando esse limite.
	//permitindo os caracteres menores que 32.
	//if( c <  ' '  && c != '\r' && c != '\n' && c != '\t' && c != '\b' )
	//{
    //    return;
    //};
 

    // Apenas voltar ao início da linha.
    if ( c == '\r' )
    {
        TTY[console_number].cursor_x = TTY[console_number].cursor_left;  
        prev = c;
        return;    
    }


    //#@todo#bugbug 
    //retirei esse retorno para o espaço, com isso 
    // o ascii 32 foi pintado, mas como todos os 
    //bits estão desligados, não pintou nada.
    //space 
    //if( c == ' ' )  
    //{
    //    g_cursor_x++; 
    //    prev = c;
    //    return;         
    //};
    
 
    // backspace ??
    if ( c == 8 )  
    {
        TTY[console_number].cursor_x--; 
        prev = c;
        return;
    }


	//
	// limits
	//

	// Filtra as dimensões da janela onde está pintando.
	// @todo: Esses limites precisam de variável global.
	//        mas estamos usando printf pra tudo.
	//        cada elemento terá que impor seu próprio limite.
	//        O processo shell impõe seu limite.
	//        a janela impõe seu limite etc...
	//        Esse aqui é o limite máximo de uma linha.
	// Poderia ser o limite imposto pela disciplina de linha
	// do kernel para o máximo de input. Pois o input é
	// armazenado em uma linha.	 


//checkLimits:

    //Limites para o número de caracteres numa linha.
    if ( TTY[console_number].cursor_x >= (TTY[console_number].cursor_right-1) )
    {
        TTY[console_number].cursor_x = TTY[console_number].cursor_left;
        TTY[console_number].cursor_y++;  

    }else{   

		// Incrementando.
		// Apenas incrementa a coluna.

        TTY[console_number].cursor_x++;  
    };

	// #bugbug
	// Tem um scroll logo acima que considera um valor
	// de limite diferente desse.

	// Número máximo de linhas. (n pixels por linha.)
    if ( TTY[console_number].cursor_y >= TTY[console_number].cursor_bottom )  
    { 
        //debug_print ("console_outbyte: scroll 3\n"); 
        console_scroll (console_number);

        TTY[console_number].cursor_y = TTY[console_number].cursor_bottom;
    }

	//
	// Imprime os caracteres normais.
	//

	// Nesse momento imprimiremos os caracteres.
    // Imprime os caracteres normais.
	// Atualisa o prev.

    _console_outbyte (c, console_number);

    prev = c;
}



/*
 *************************************** 
 * console_putchar:
 *     Put a char into the screen of a virtual console.
 */

// #importante
// Colocamos um caractere na tela de um console virtual.

// #bugbug: 
// Como essa rotina escreve na memória de vídeo,
// então precisamos, antes de uma string efetuar a
// sincronização do retraço vertical e não a cada char.

void console_putchar ( int c, int console_number ){
	
    // Getting char info.
	
	int cWidth = get_char_width ();
	int cHeight = get_char_height ();

    if ( cWidth == 0 || cHeight == 0 ){
        panic ("console_putchar: char");
    }


	// flag on.
	stdio_terminalmode_flag = 1;  


    //  Console limits

    if ( console_number < 0 || console_number >= 4 ){
        panic ("console_putchar: console_number");        
    }

    // Desenhar o char no backbuffer
	
	// #todo: 
	// Escolher um nome de função que reflita
	// essa condição de desenharmos o char no backbuffer.
	
    console_outbyte  ( (int) c, console_number );

	
	// Copiar o retângulo na memória de vídeo.

    refresh_rectangle ( 
        TTY[console_number].cursor_x * cWidth, 
        TTY[console_number].cursor_y * cHeight, 
        cWidth, 
        cHeight );

	// flag off.
	stdio_terminalmode_flag = 0;  
}



// No escape sequence support.
ssize_t 
__console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
    char ch=0; 
    size_t __i=0;
    char *data = (char *) buf;


    if ( console_number < 0 || console_number > 3 ){
       debug_print ("__console_write: console_number\n");
       return -1;
    }

 
    //#testing.
    if ( (void *) buf == NULL ){
        printf ("__console_write: buf\n");
        refresh_screen();
        return -1;
    }


    if (!count){
        printf ("__console_write: count\n");
        return -1;
    }

       
    //
    // Write string
    //   
       
    // original - backup

    for (__i=0; __i<count; __i++)
        console_putchar ( (int) data[__i], console_number);


    return (ssize_t) count;
}


ssize_t 
console_read ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
    debug_print ("console_read: [TODO]\n");
    return -1;  //todo
}



// Tem escape sequence
// console number, buffer, size.
ssize_t 
console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{

    char ch; 
    int i;  
    char *data = (char *) buf;

    //debug_print ("console_write: [test]\n");
    
    if ( console_number < 0 || console_number > 3 ){
        printf ("console_write: console_number\n");
        refresh_screen();
        return -1;
    }

    if ( (void *) buf == NULL ){
        printf ("console_write: buf\n");
        refresh_screen();
        return -1;
    }

    if (!count){
        printf ("console_write: count\n");
        refresh_screen();
        return -1;
    }


    //
    // Write string
    //   


    // Inicializando.
    // Dão dá mais pra confiar !
    __state = 0; 
 
    for (i=0; i<count; i++){

        ch = data[i];
                
        switch (__state){
                 
            // State 0
            case 0:
            // #debug
            //console_putchar ( '@',console_number);
            //console_putchar ( '0',console_number);
            //console_putchar ( '\n',console_number);

               // Printable ?
               if (ch >31 && ch <127) {

                    console_putchar ( ch, console_number );
               
               // Escape.
               } else if (ch==27) 
                   __state=1;
               else if (ch==10 || ch==11 || ch==12)
                   console_putchar ( ch, console_number );  // \n ???
               else if (ch==13)    
                   console_putchar ( ch, console_number );  //cr \n
               else if (ch==8) {
                   console_putchar ( ch, console_number );  // backspace.
               } else if (ch==9) {
                   console_putchar ( ch, console_number );  // horizontal tab
               }
               break;
            
            
            // State 1
            case 1:
            // #debug
            //console_putchar ( '@',console_number);
            //console_putchar ( '1',console_number);
            //console_putchar ( '\n',console_number);
            
                __state=0;
                
                if (ch=='[')
					__state=2;
				else if (ch=='E') 
					__local_gotoxy ( 0, (TTY[console_number].cursor_y + 1), console_number );
				else if (ch=='M')
					__local_ri ();   //scroll. deixa pra depois. kkk
				else if (ch=='D')
					console_putchar ( ch, console_number );  //lf();
				else if (ch=='Z')
					__respond (console_number);    //test
				else if ( TTY[console_number].cursor_x == '7')   //?? What L.T.
					__local_save_cur (console_number);
				else if ( TTY[console_number].cursor_x == '8' )  //?? What L.T.
					__local_restore_cur (console_number);
				break;
			
			
			//State 2
			case 2:
            // #debug
            //console_putchar ( '@',console_number);
            //console_putchar ( '2',console_number);
            //console_putchar ( '\n',console_number);
            
			    // Clean
				for ( npar=0; npar<NPAR; npar++ )
					par[npar]=0;
				npar=0;
				__state=3;  // Next state.
				if ( ques = ( ch == '?' ) ) 
					break;
					
            case 3:
            // #debug
            //console_putchar ( '@',console_number);
            //console_putchar ( '3',console_number);
            //console_putchar ( '\n',console_number);
            
				if ( ch==';' && npar<NPAR-1) {
					npar++;
					break;
				} else if ( ch >= '0' && ch <='9') {
					par[npar] = 10 * par[npar] + ch -'0';
					break;
				} else __state=4;

			case 4:
            // #debug
            //console_putchar ( '@',console_number);
            //console_putchar ( '4',console_number);
            //console_putchar ( '\n',console_number);
            
				__state=0;
				switch (ch) {
					case 'G': case '`':
						if (par[0]) par[0]--;
						__local_gotoxy (par[0], TTY[console_number].cursor_y, console_number);
						break;
					case 'A':
						if (!par[0]) par[0]++;
						__local_gotoxy ( TTY[console_number].cursor_x,  TTY[console_number].cursor_y - par[0], console_number);
						break;
					case 'B': case 'e':
						if (!par[0]) par[0]++;
						__local_gotoxy ( TTY[console_number].cursor_x, TTY[console_number].cursor_y + par[0], console_number);
						break;
					case 'C': case 'a':
						if (!par[0]) par[0]++;
						__local_gotoxy ( TTY[console_number].cursor_x + par[0], TTY[console_number].cursor_y, console_number);
						break;
					case 'D':
						if (!par[0]) par[0]++;
						__local_gotoxy ( TTY[console_number].cursor_x - par[0], TTY[console_number].cursor_y, console_number);
						break;
					case 'E':
						if (!par[0]) par[0]++;
						__local_gotoxy (0, TTY[console_number].cursor_y + par[0], console_number);
						break;
					case 'F':
						if (!par[0]) par[0]++;
						__local_gotoxy (0, TTY[console_number].cursor_y - par[0], console_number);
						break;
					case 'd':
						if (par[0]) par[0]--;
						__local_gotoxy ( TTY[console_number].cursor_x, par[0], console_number);
						break;
					case 'H': case 'f':
						if (par[0]) par[0]--;
						if (par[1]) par[1]--;
						__local_gotoxy (par[1],par[0], console_number);
						break;
					case 'J':
						csi_J (par[0]);
						break;
					case 'K':
						csi_K (par[0]);
						break;
					case 'L':
						csi_L (par[0], console_number);
						break;
					case 'M':
						csi_M (par[0], console_number );
						break;
					case 'P':
						csi_P (par[0], console_number);
						break;
					case '@':
						csi_at (par[0], console_number);
						break;
					case 'm':
						csi_m ();
						break;
					case 'r':
						if (par[0]) par[0]--;
						if (!par[1]) par[1] = TTY[console_number].cursor_height;  //?? da fuck
						if (par[0] < par[1] &&
						    par[1] <= TTY[console_number].cursor_height ) {
							TTY[console_number].cursor_top =par[0];
							TTY[console_number].cursor_bottom = par[1];
						}
						break;
					case 's':
					    __local_save_cur( console_number );
						break;
					case 'u':
						__local_restore_cur (console_number);
						break;
                }; 
                break;

            default:
                printf ("console_write: default\n");
                refresh_screen();
                return -1;
                break;
        };
    }; 

   //printf ("console_write: done\n");
   //refresh_screen();

    return count; 

}



/*
 ********************************************
 * scroll:
 *     Isso pode ser útil em full screen e na inicialização do kernel.
 *
 * *Importante: 
 * Um (retângulo) num terminal deve ser o lugar onde o buffer 
 * de linhas deve ser pintado. Obs: Esse retãngulo pode ser 
 * configurado através de uma função.
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

void console_scroll (int console_number){

	// Salvar cursor.
    unsigned long OldX, OldY;

    int i=0;


    if ( VideoBlock.useGui != 1 )
        panic ("console_scroll: no GUI");    


	// copia o retângulo.
	// #todo: olhar as rotinas de copiar retângulo.
	//See: comp/rect.c
    scroll_screen_rect ();

    //#debug
    //refresh_screen();
    //return;

    //Limpa a última linha.

	// Salva cursor
    OldX = TTY[console_number].cursor_x; 
    OldY = TTY[console_number].cursor_y; 

    // Cursor na ultima linha.
    TTY[console_number].cursor_x = TTY[console_number].cursor_left; 
    TTY[console_number].cursor_y = ( TTY[console_number].cursor_bottom -1); 


   // Limpa a últime linha.
   for ( i = TTY[console_number].cursor_x; i < TTY[console_number].cursor_right; i++ )
   {
        _console_outbyte (' ',console_number); 
   };


    // Reposiciona o cursor na última linha.
    TTY[console_number].cursor_x = TTY[console_number].cursor_left; 
    TTY[console_number].cursor_y = OldY;  //( TTY[console_number].cursor_bottom -1); 

    refresh_screen ();
}


/*
 ********************************
 * kclear:
 *     Limpa a tela em text mode.
 *     # isso não faz parte da lib c. Deletar.
 */

int kclear (int color, int console_number)
{

	int Status = -1;
	
	if ( VideoBlock.useGui == 1 )
	{
		backgroundDraw ( COLOR_BLUE );

		TTY[console_number].cursor_x = 0; 
		TTY[console_number].cursor_y = 0; 

		Status = 0;

	}else{
		Status = -1;
	};

	return (int) Status;
}


/* 
 * kclearClientArea: 
 */

// Limpa a tela em text mode.
// Isso não faz parte da lib c. Deletar.

int kclearClientArea (int color)
{
    return (int) kclear (color, current_vc);
}



/*
 *************************************
 * insert_line:
 * 
 */

// Incluir uma linha no buffer de linhas da estrutura do tty atual.
// vamos copiar esse esquema do edito de textos em ring3.

int insert_line ( char *string, int line ){

    debug_print ("insert_line:\n");

	/*
	
	int l;
	struct tty_line_d *Line;
	
	//if ( (void *) string == NULL )
	//	return -1;
	
    if ( (void *) CurrentTTY != NULL )
	{
        if ( CurrentTTY->used == 1 && CurrentTTY->magic == 1234 )
		{
			//Linha atual para se escrever no stdout do current tty
		    l = CurrentTTY->current_line;
			
			//Pega o ponteiro para estrutura de linha da linha atual.
			Line = (struct tty_line_d *) CurrentTTY->lines[l];
			
			if ( (void *) Line == NULL )
				return -1;
			
			//Buffer pra colocar chars.
		    //Line->CHARS[0]  
			//Line->ATTRIBUTES[0] 
				
			//inicio do texto dentro da linha atual
		    //CurrentTTY->left
			
			//fim do texto dentro da linha atual
			//CurrentTTY->right
			
			//posição do ponteiro dentro da linha atual.
			//CurrentTTY->pos
		
		}
	};
	*/


    return (int) -1; 
}



/*
 *******************************************
 * REFRESH_STREAM:
 * 
 *     #IMPORTANTE
 *     REFRESH SOME GIVEN STREAM INTO TERMINAL CLIENT WINDOW !!
 */

void REFRESH_STREAM ( FILE *stream ){

    char *c;

    int i=0;
    int j=0;


	 //#debug
	 //sprintf ( stream->_base, "TESTING STDOUT ..." );


    j = 80*25;
 
    c = stream->_base;


    int cWidth = get_char_width();
    int cHeight = get_char_height();

    if ( cWidth == 0 || cHeight == 0 ){
        panic ("REFRESH_STREAM: char w h ");
    }


    // Seleciona o modo terminal.

    //++
    stdio_terminalmode_flag = 1;  
    for ( i=0; i<j; i++ )
    {
		printf ("%c", *c );
		
	    refresh_rectangle ( 
	        TTY[current_vc].cursor_x * cWidth, 
	        TTY[current_vc].cursor_y * cHeight,  
		    cWidth, cHeight );
		
		c++;
    };
    stdio_terminalmode_flag = 0;  
    //--
}




void console_set_current_virtual_console ( int n )
{
    if ( n < 0 )
    {
        return;
    }
    
    if ( n >= 4 )
    {
         return;
    }
    
    current_vc = n;
}


int console_get_current_virtual_console (void)
{
    return (int) current_vc;
}


void console_init_virtual_console (int n)
{

    if ( n < 0 )
    {
        return;
    }
    
    if ( n >= 4 )
    {
         return;
    }

    TTY[n].cursor_x = 0;
    TTY[n].cursor_y = 0;
    TTY[n].cursor_width = 80;
    TTY[n].cursor_height = 80;
    TTY[n].cursor_left = 0;
    TTY[n].cursor_top = 0;
    TTY[n].cursor_right = 80;
    TTY[n].cursor_bottom = 80;
    TTY[n].cursor_color = COLOR_GREEN; //COLOR_TERMINALTEXT;
    
    // #bugbug
    // A estrutura tem mais elementos que podem ser inicializados.
    // Tivemos problemas ao tentar inicializa-los.
}


//
//=========
//


/*
int console_can_read( void);
int console_can_read( void)
{
   return 0;  //false
}
*/

/*
int console_can_write( void);
int console_can_write( void)
{
   return 1;  //true
}
*/


/*
 **************** 
 * console_ioctl:
 * 
 */

// Podemos mudar as características de um console.

int 
console_ioctl ( 
    int fd, 
    unsigned long request, 
    char *arg )
{
    debug_print ("console_ioctl: TODO\n");
    //switch(request){}
    return -1;
}


//
// End.
//


