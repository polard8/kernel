/*
 * File: console.c 
 *
 *     Console interface.
 * 
 *     This is a generic interface for a frame buffer based 
 * graphical consoles.
 * 
 *     The system have only '4' virtual consoles. 
 * Define in the struct list CONSOLE[].
 *     #bugbug: It uses the TTY structure. But the configuration
 * is kinda buggy and there is no buffers for now.
 *     
 *     We are using these console only to print chars 
 * in the screen in graphics mode.
 *     The scroll only works on full screen for now.
 * 
 *     This is a kind of emergency console, used by the developer
 * to test the system and to fix some critical condition.
 * 
 *     See: chardev/tty/ in 2io/
 */

// notes:
// Esse console é full screen e não precisa de muitos recursos gráficos.
// Somete o super user poderá usá-lo.
// Só existem quatro consoles virtuais. Um deles será usado para
// registrar o servidor gráfico.
// Para pseudo terminais veja: vt.c


// #todo:
// Control Sequence Introducer (CSI) 
// See:
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
// ...


#include <kernel.h>


extern unsigned long SavedX;
extern unsigned long SavedY;


//0=apaga 1=acende 
int consoleTextCursorStatus;


// Esse eh o marcador de estagio do escape sequence.
// Usado para manipular csi
static unsigned long __EscapeSequenceStage = 0;



#define NPAR  16
static unsigned long par[NPAR];
static unsigned long npar = 0;
static unsigned long ques = 0;
static unsigned char attr = 0x07;


void __local_ri (void)
{
    //#todo
}


// goto xy
void 
__local_gotoxy ( 
    int new_x, 
    int new_y, 
    int console_number )
{

    if (console_number<0){
        return;
    }

    if ( new_x >= (CONSOLE_TTYS[console_number].cursor_right-1) )
    {
        return;
    }

    if ( new_y >= (CONSOLE_TTYS[console_number].cursor_bottom-1) )
    {
        return;
    }

    CONSOLE_TTYS[console_number].cursor_x = new_x;
    CONSOLE_TTYS[console_number].cursor_y = new_y;
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
    saved_x = CONSOLE_TTYS[console_number].cursor_x;
    saved_y = CONSOLE_TTYS[console_number].cursor_y;
}

void __local_restore_cur (int console_number)
{
    CONSOLE_TTYS[console_number].cursor_x = saved_x;
    CONSOLE_TTYS[console_number].cursor_y = saved_y;
}


// See:
// https://en.wikipedia.org/wiki/Control_character
// https://en.wikipedia.org/wiki/C0_and_C1_control_codes#Device_control

void __local_insert_char ( int console_number )
{

    if(console_number<0){
        return;
    }

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

    //int i = CONSOLE[console_number].cursor_x;
    //int tmp;
    //int old = 0x20;
    
    // #bugbug
    // Não é possível fazer essa rotina pois não temos um buffer e chars.

    //while (i++ < CONSOLE[console_number].cursor_height ) {};
    
    console_putchar (0x20, console_number);
}


void __local_insert_line (int console_number)
{
    int oldtop    = 0;
    int oldbottom = 0;

    if(console_number<0){
        return;
    }


    oldtop    = CONSOLE_TTYS[console_number].cursor_top;
    oldbottom = CONSOLE_TTYS[console_number].cursor_bottom;

    CONSOLE_TTYS[console_number].cursor_top = CONSOLE_TTYS[console_number].cursor_y;
    
    //#bugbug: apontando par asi mesmo.
    //CONSOLE[console_number].cursor_bottom = CONSOLE[console_number].cursor_bottom;

    //if (console_number<0)
        //return;

    console_scroll(console_number);

    CONSOLE_TTYS[console_number].cursor_top    = oldtop;
    CONSOLE_TTYS[console_number].cursor_bottom = oldbottom;
}


void __local_delete_char(int console_number)
{

    if(console_number<0){
        return;
    }

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
    int oldtop    = 0;
    int oldbottom = 0;


    if(console_number<0){
        return;
    }

    oldtop    = CONSOLE_TTYS[console_number].cursor_top;
    oldbottom = CONSOLE_TTYS[console_number].cursor_bottom;


    CONSOLE_TTYS[console_number].cursor_top = CONSOLE_TTYS[console_number].cursor_y;
    
    //#bugbug: apontando para si mesmo.
    //CONSOLE[console_number].cursor_bottom = CONSOLE[console_number].cursor_bottom;

    //#todo
	//scrup();

    CONSOLE_TTYS[console_number].cursor_top    = oldtop;
    CONSOLE_TTYS[console_number].cursor_bottom = oldbottom;
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


// move to
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


// Fim da escape sequence.
// isso eh chamado quando encontramos um 'm'.
// O 'm' eh um marcador de fim de escape sequence.
// Entao vamos checar os parametros no buffer.
// Configuramos a variavel de atributo de acordo
// com o parametro encontrado.
// Ficaremos com o ultimo atributo. #bugbug ????

void csi_m(void)
{
    int i=0;
    int Ch=0;

    // #bugbug
    // Check 'npar'

    if (npar == 0){
        return;
    }

    for (i=0; i <= npar; i++)
    {
        Ch = (int) par[i];

        switch (Ch) {

        case 0:  attr=0x07;  break;
        case 1:  attr=0x0f;  break;
        case 4:  attr=0x0f;  break;
        case 7:  attr=0x70;  break;
        case 27: attr=0x07;  break;
        // default?

        };
    };
}


void csi_M ( int nr, int console_number )
{

    /*
	if ( nr > CONSOLE_TTYS[console_number].cursor_height )
		nr = CONSOLE_TTYS[console_number].cursor_height;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_delete_line(console_number);
    
    */
}


// move to
void csi_L (int nr, int console_number)
{
   /*
	if (nr > CONSOLE[console_number].cursor_height)
		nr = CONSOLE[console_number].cursor_height;
	else if (!nr)
		nr=1;
	while (nr--)
		__local_insert_line(console_number);
    */
}


void csi_P (int nr, int console_number)
{

    if (console_number<0){
        return;
    }

    if (nr > CONSOLE_TTYS[console_number].cursor_right -1 )
    {
        nr = CONSOLE_TTYS[console_number].cursor_right -1 ;
    } else {
        
        if (!nr)
        {
            nr = 1;
        }
    };

    if (nr<0)
        return;

    while (nr--){
        __local_delete_char(console_number);
    };
}


void csi_at (int nr, int console_number)
{

    if( console_number<0){
        return;
    }

    if (nr > CONSOLE_TTYS[console_number].cursor_right -1 )
    {
        nr = CONSOLE_TTYS[console_number].cursor_right -1 ;
    }else {
        
        if (!nr){
            nr=1;
        }
    };

    if (nr<0)
        return;

    while (nr--){
        __local_insert_char(console_number);
    };
}


/*
 ***************************************
 * _console_outbyte:
 * 
 *    Outputs a char on the console device;
 *    Low level function to draw the char into the screen.
 *    it calls the embedded window server.
 */

	// #test
	// Tentando pegar as dimensões do char.
	// #importante: 
	// Não pode ser 0, pois poderíamos ter divisão por zero.

// Called by console_outbyte.

void _console_outbyte (int c, int console_number)
{
    int cWidth  = get_char_width();
    int cHeight = get_char_height();

    // #todo: Check verflow
    if (console_number < 0){
        return;
    }

    if ( cWidth == 0 || cHeight == 0 )
    {
        debug_print ("_console_outbyte: char w h\n");
        panic       ("_console_outbyte: fail w h");
    }


    // #bugbug
    // Caso estejamos em modo texto.
    // Isso ainda não é suportado.

    if ( VideoBlock.useGui == FALSE )
    {
        debug_print ("_console_outbyte: kernel in text mode\n");
        panic       ("_console_outbyte: kernel in text mode\n");
    }


    // #Importante: 
    // Essa rotina não sabe nada sobre janela, ela escreve na tela como 
    // um todo. Só está considerando as dimensões do 'char'.
    // Caso estivermos em modo gráfico.
    // #importante: 
    // Essa rotina de pintura deveria ser exclusiva 
    // para dentro do terminal.
    // Então essa flag não faz sentido.
    // See: windows/char.c

    if ( VideoBlock.useGui == TRUE )
    {

        // ## NÃO TRANPARENTE ##
        // Se estamos no modo terminal então usaremos as cores 
        // configuradas na estrutura do terminal atual.
        // Branco no preto é um padrão para terminal.
        if ( stdio_terminalmode_flag == 1 ){
            d_draw_char ( 
                 (cWidth * CONSOLE_TTYS[console_number].cursor_x), 
                (cHeight * CONSOLE_TTYS[console_number].cursor_y), 
                c, COLOR_WHITE, 0x303030 );


        // ## TRANSPARENTE ##
        // Se não estamos no modo terminal então usaremos
        // char transparente.
        // Não sabemos o fundo. Vamos selecionar o foreground. 
        }else{
            d_drawchar_transparent ( 
                (cWidth  * CONSOLE_TTYS[console_number].cursor_x), 
                (cHeight * CONSOLE_TTYS[console_number].cursor_y), 
                CONSOLE_TTYS[console_number].cursor_color, 
                c );
        };
        // Nothing.
    }
}


/*
 *********************************************
 * console_outbyte:
 *     Trata o caractere a ser imprimido e chama a rotina /_outbyte/
 * para efetivamente colocar o caractere na tela.
 *
 * Essa rotina é chamada pelas funções: /putchar/scroll/.
 * @todo: Colocar no buffer de arquivo.
 */

// This functions calls _console_outbyte to draw
// the char into the screen.

void console_outbyte (int c, int console_number)
{
    // Copy.
    register int Ch = c;

    static char prev = 0;

    unsigned long __cWidth  = gwsGetCurrentFontCharWidth();
    unsigned long __cHeight = gwsGetCurrentFontCharHeight();


    // #todo: Check overflow.
    if (console_number<0){
        return;
    }

    if ( __cWidth == 0 || __cHeight == 0 )
    {
        panic ("console_outbyte: [FAIL] char size\n");
    }


    // Obs:
    // Podemos setar a posição do curso usando método,
    // simulando uma variável protegida.

//checkChar:

    //Opção  
    //switch ?? 


    // form feed - Nova tela.
    if ( Ch == '\f' )
    {
        CONSOLE_TTYS[console_number].cursor_y = CONSOLE_TTYS[console_number].cursor_top;
        CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;
        return;
    }

    // #obs: #m$. 
    // É normal \n retornar sem imprimir nada.

    // Início da próxima linha. 
    // not used!!!  "...\r\n";

    if ( Ch == '\n' && prev == '\r' ) 
    {
        // #todo: 
        // Melhorar esse limite.
        if ( CONSOLE_TTYS[console_number].cursor_y > (CONSOLE_TTYS[console_number].cursor_bottom) )
        {
            //debug_print ("console_outbyte: scroll 1\n"); 
            console_scroll (console_number);

            CONSOLE_TTYS[console_number].cursor_y = (CONSOLE_TTYS[console_number].cursor_bottom);
            prev = Ch; 
        }else{
            CONSOLE_TTYS[console_number].cursor_y++;
            CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;
            prev = Ch;
        };
        return;
    }


    // Próxima linha no modo terminal.
    // "...\n"

    if ( Ch == '\n' && prev != '\r' ) 
    {
        // se o line feed apareceu quando estamos na ultima linha
        if ( CONSOLE_TTYS[console_number].cursor_y > (CONSOLE_TTYS[console_number].cursor_bottom) )
        {

            //debug_print ("console_outbyte: scroll 2\n"); 
            console_scroll (console_number);
            
            CONSOLE_TTYS[console_number].cursor_y = (CONSOLE_TTYS[console_number].cursor_bottom);
            prev = Ch;

        }else{
            CONSOLE_TTYS[console_number].cursor_y++;

			//Retornaremos mesmo assim ao início da linha 
			//se estivermos imprimindo no terminal.
            if ( stdio_terminalmode_flag == 1 ){
                CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;	
            } 

			//verbose mode do kernel.
			//permite que a tela do kernel funcione igual a um 
			//terminal, imprimindo os printfs um abaixo do outro.
			//sempre reiniciando x.
            if ( stdio_verbosemode_flag == 1 ){
                CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;
            } 

			//Obs: No caso estarmos imprimindo em um editor 
			//então não devemos voltar ao início da linha.

            prev = Ch;
        };

        return;
    }


    // TAB
    // #todo: 
    // Criar a variável 'g_tab_size'.

    if ( Ch == '\t' ) 
    {
        CONSOLE_TTYS[console_number].cursor_x += (8);
        //g_cursor_x += (4); 
        prev = Ch;
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
    }


	//liberando esse limite.
	//permitindo os caracteres menores que 32.
	//if( c <  ' '  && c != '\r' && c != '\n' && c != '\t' && c != '\b' )
	//{
    //    return;
    //};


    // Apenas voltar ao início da linha.
    if ( Ch == '\r' )
    {
        CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;  
        prev = Ch;
        return; 
    }


    // #bugbug 
    // Com isso o ascii 0x20 foi pintado, 
    // mas como todos os bits do char na fonte estão desligados, 
    // então não pinta coisa alguma.

    if( Ch == 0x20 )  
    {
        CONSOLE_TTYS[console_number].cursor_x++;
        prev = Ch;
        return; 
    }


    // Backspace ?

    //if ( Ch == '\b' )
    if ( Ch == 0x8 )
    {
        CONSOLE_TTYS[console_number].cursor_x--; 
        prev = Ch;
        return;
    }


    //
    // == Limits =======================================
    //

    // Nao eh um escape sequense ...
    // mas chegamos no fim da linha ou na ultima linha.

    // fim da linha.
    // Limites para o número de caracteres numa linha.
    if ( CONSOLE_TTYS[console_number].cursor_x > (CONSOLE_TTYS[console_number].cursor_right) )
    {
        // voltamos ao inicio da linha e avançamos uma linha;
        CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;
        CONSOLE_TTYS[console_number].cursor_y++;

    // Incrementando.
    // Apenas incrementa a coluna.
    }else{ 
        CONSOLE_TTYS[console_number].cursor_x++;  
    };


	// #bugbug
	// Tem um scroll logo acima que considera um valor
	// de limite diferente desse.

	// Número máximo de linhas. (n pixels por linha.)
    if ( CONSOLE_TTYS[console_number].cursor_y > CONSOLE_TTYS[console_number].cursor_bottom )  
    { 
        //debug_print ("console_outbyte: scroll 3\n"); 
        console_scroll (console_number);

        CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left;
        CONSOLE_TTYS[console_number].cursor_y = CONSOLE_TTYS[console_number].cursor_bottom;
    }

    // Imprime os caracteres normais.
    // Nesse momento imprimiremos os caracteres.
    // Imprime os caracteres normais.
    // Atualisa o prev.

draw:
    _console_outbyte (Ch, console_number);
    prev = Ch;
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
    int cWidth  = get_char_width();
    int cHeight = get_char_height();



    if ( cWidth == 0 || cHeight == 0 )
    {
        panic ("console_putchar: char\n");
    }

    // flag on.
    stdio_terminalmode_flag = TRUE;

    // #todo
    // Check these limits.

    //  Console limits
    // CONSOLETTYS_COUNT_MAX
    // See: tty.h

    if ( console_number < 0 || console_number > 3 )
    {
        panic ("console_putchar: console_number\n");
    }

    // Draw the char into the backbuffer and
    // copy a small rectangle to the frontboffer.

    // Draw
    console_outbyte  ( (int) c, console_number );

    // Copy
    refresh_rectangle ( 
        (CONSOLE_TTYS[console_number].cursor_x * cWidth), 
        (CONSOLE_TTYS[console_number].cursor_y * cHeight), 
        cWidth, 
        cHeight );

    // flag off.
    stdio_terminalmode_flag = FALSE; 
}



// No escape sequence support.
ssize_t 
__console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
    // loop
    size_t __i = 0;

    char ch = 0; 
    char *data = (char *) buf;


    if ( console_number < 0 || console_number > 3 )
    {
       kprintf ("__console_write: console_number\n");
       goto fail;
    }

    if ( (void *) buf == NULL ){
        kprintf ("__console_write: buf\n");
        goto fail;
    }

    if (!count){
        kprintf ("__console_write: count\n");
        goto fail;
    }


    //
    // Write string
    //   
       
    // original - backup

    for (__i=0; __i<count; __i++){
        console_putchar ( (int) data[__i], console_number);
    };

    return (ssize_t) count;

fail:
    refresh_screen();
    return (ssize_t) (-1);
}



// #todo
// Isso é importante.
// Pegar input na estrutura de console do kernel.

ssize_t 
console_read ( 
    int console_number, 
    const void *buf, 
    size_t count )
{
    debug_print ("console_read: [TODO]\n");
    return -1;  //todo
}



/*
 *************************** 
 * console_write:
 * 
 */

// Called by sys_write() in sys.c.

// Tem escape sequence
// console number, buffer, size.

// IN: 
ssize_t 
console_write ( 
    int console_number, 
    const void *buf, 
    size_t count )
{

    // loop
    int i=0;
    
    char ch=0; 
    char *data = (char *) buf;
    size_t StringSize=0;



    //debug_print ("console_write: [test]\n");

    // Console number
    if ( console_number < 0 || console_number > 3 )
    {
        printf ("console_write: [FAIL] console_number\n");
        goto fail;
    }

    // Buffer
    if ( (void *) buf == NULL ){
        printf ("console_write: buf\n");
        goto fail;
    }

    // Count
    if (!count){
        printf ("console_write: count\n");
        goto fail;
    }


    //
    // Write string
    //   


    // Isso eh o contador de estagios do escape sequence.
    // Vamos percorret todos os bytes da sequencia quando
    // encontrarmos o marcador.
    
    // #todo
    // Esse marcador de estagio deve ser especifico para
    // cada console. CONSOLE[i].esc_stage
    
    __EscapeSequenceStage = 0; 

     StringSize = count;

    for (i=0; i<StringSize; i++)
    {
        // Get next char from the string.
        ch = data[i];

        // Select the stage in the escape sequence.
 
        switch (__EscapeSequenceStage){

            //================================================
            // Stage 0
            // Nao entramos em uma escape sequence.
            case 0:
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '0',console_number);
                //console_putchar ( '\n',console_number);

               // Is printable?
               if (ch >31 && ch <127){
                    console_putchar ( ch, console_number );
               
               // >>>> [ Escape ]
               // Entramos em uma escape sequence,
               // entao o proximo case inicia o tratamento da escape sequence.
               } else if (ch==27){
                   __EscapeSequenceStage=1;  // <<<<<<<--

               // ?? \n
               }else if (ch==10 || ch==11 || ch==12){
                   console_putchar ( ch, console_number );

               // Enter ? cr \n
               }else if (ch==13){ 
                   console_putchar ( ch, console_number ); 

               // Backspace
               }else if (ch==8) {
                   console_putchar ( ch, console_number );

               // Tab.S. horizontal tab
               } else if (ch==9) {
                   console_putchar ( ch, console_number ); 
               };
               break;
            
            //================================================
            // Stage 1
            // Acabamos de entrar na escape sequence.
            // Vamos checar o primeiro char.
            case 1:
            
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '1',console_number);
                //console_putchar ( '\n',console_number);
            
                // Zerando o marcador de estagio.
                // Isso porque o estagio mudara dependendo do char encontrado agora.
                __EscapeSequenceStage=0; 
                
                // '['
                // CSI.    '0x1b['
                if (ch=='['){
                    __EscapeSequenceStage = 2;
                
                // >>> nao eh csi ... o 'E' esta no lugar do '['
                
                }else if (ch=='E'){ 
                    __local_gotoxy ( 0, (CONSOLE_TTYS[console_number].cursor_y + 1), console_number );
                }else if (ch=='M'){
                    __local_ri ();   //scroll. deixa pra depois. kkk
                }else if (ch=='D'){
                    console_putchar ( ch, console_number );  //lf();
                }else if (ch=='Z'){
                    __respond (console_number);    //test
                
                //??
                // tivemos um 0x1b e o cursor esta em determinado lugar.
                }else if ( CONSOLE_TTYS[console_number].cursor_x == '7'){   //?? What L.T.
                    __local_save_cur (console_number);
                
                //??
                // tivemos um 0x1b e o cursor esta em determinado lugar.
                }else if ( CONSOLE_TTYS[console_number].cursor_x == '8' ){  //?? What L.T.
                    __local_restore_cur (console_number);
                };
                break;

            //================================================
            // Stage 2
            // Chegamos aqui depois de encontrarmos um CSI. '0x1b['
            // O que vem apos o '[' sao parametros separados por delimitadores
            // e terminados com um 'm'. 
            case 2:
            
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '2',console_number);
                //console_putchar ( '\n',console_number);
 
                // Limpando o array de parametros.
                for ( npar=0; npar<NPAR; npar++ ){ par[npar]=0; };
                npar=0;
                //Mudando de estago para checar os parametros.
                __EscapeSequenceStage=3;  // Next state.
                
                //Se o primeiro char apos o '[' for um '?'
                // entao vamos para o proximo estagio, mas quebraremos 
                // par ao for pegar o proximo char.
                // Caso contrario vamos para o proximo estago sem pegarmos o proximo char?
                if ( ques = ( ch == '?' ) ) 
                    break;

            //================================================
            // Stage 3
            case 3:
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '3',console_number);
                //console_putchar ( '\n',console_number);
            
                // Se encontramos um delimitador
                // e ainda nao acabou o array usado para parametros.
                // entao avançamos para o proximo char nos parametros.
                if ( ch == ';' && 
                     npar < NPAR-1) 
                {
                    // Avançamos, mas quebramos para que o for pegue
                    // o proximo char da string.
                    //#bugbug: Não moda de state??
                    npar++;  break;  

                // Isso nao eh um delimitador.
                // Checamos se eh um numero.
                } else if ( ch >= '0' && ch <='9'){

                    // Sim eh um numero.
                    // #bugbug?
                    // Multiplicamos o que estava no buffer por 10.
                    // Mas nem sei o que ja estava no buffer??
                    // porque fizemos isso ?
                    // o buffer provavelmente esta vazio no primeiro numero.
                    // Sendo assim qeubramos para tentarmos pegar mais numeros no for.
                    par[npar] = 10 * par[npar] + ch - '0';
                    break;

                 // Nao eh um delimitador nem um numero.
                 // entao vamos para o proximo estagio
                 // porque provavelmente eh uma letra.
                 // Nao precisamos quebrar, pois ja temos um char.
                 } else { 
                     __EscapeSequenceStage = 4;
                 }

            // Stage 4
            case 4:
                // #debug
                //console_putchar ( '@',console_number);
                //console_putchar ( '4',console_number);
                //console_putchar ( '\n',console_number);

                // Zerando o marcador de estagio.
                // Significa que se quebrarmos, vamos voltar para o estagio zero.
                // No estagio zero estamos fora da escape sequence.
 
                __EscapeSequenceStage=0;
                
                switch (ch){

                    // mudamos o cursor e saimos da escape sequence
                    case 'G': case '`':
                        if (par[0]){  par[0]--;  }
                        __local_gotoxy ( 
                            par[0], 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        break;

                    // Mudamos o cursor e saimos da escape sequence
                    case 'A':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x,  
                            CONSOLE_TTYS[console_number].cursor_y - par[0], 
                            console_number );
                        break;

                    case 'B': case 'e':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x, 
                            CONSOLE_TTYS[console_number].cursor_y + par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence 
                    case 'C': case 'a':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x + par[0], 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'D':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x - par[0], 
                            CONSOLE_TTYS[console_number].cursor_y, 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'E':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            0, 
                            CONSOLE_TTYS[console_number].cursor_y + par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'F':
                        if (!par[0]){  par[0]++;  }
                        __local_gotoxy ( 
                            0, 
                            CONSOLE_TTYS[console_number].cursor_y - par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'd':
                        if (par[0]){  par[0]--;  }
                        __local_gotoxy ( 
                            CONSOLE_TTYS[console_number].cursor_x, 
                            par[0], 
                            console_number );
                        break;

                    // mudamos o cursor e saimos da escape sequence
                    case 'H': case 'f':
                        if (par[0]){  par[0]--;  }
                        if (par[1]){  par[1]--;  }
                        __local_gotoxy ( 
                            par[1],
                            par[0], 
                            console_number );
                        break;

                    // Outros tratadores.
                    case 'J': csi_J  (par[0]);                 break;
                    case 'K': csi_K  (par[0]);                 break;
                    case 'L': csi_L  (par[0], console_number); break;
                    case 'M': csi_M  (par[0], console_number); break;
                    case 'P': csi_P  (par[0], console_number); break;
                    case '@': csi_at (par[0], console_number); break;


                    // FIM.
                    // Isso marca o fim da escape sequence,
                    // vamos quebrar e voltar para a string normal.
                    // Essa rotina cheaca os parametros e configura o atributo
                    // de acordo com o ultimo parametro.
                    case 'm': 
                        csi_m(); 
                        break;


                    // ??  #bugbug
                    // 0x1b[r
                    // Isso ajusta o top e o bottom.
                    case 'r':
                        if (par[0])  { par[0]--; }
                        if (!par[1]) { par[1] = CONSOLE_TTYS[console_number].cursor_bottom; }  
                        if (par[0] < par[1] &&
                            par[1] <= CONSOLE_TTYS[console_number].cursor_bottom ) 
                        {
                            // Ajuste feito por 'r'.
                            CONSOLE_TTYS[console_number].cursor_top    = par[0];
                            CONSOLE_TTYS[console_number].cursor_bottom = par[1];
                        }
                        break;

                    // Save cursor
                    case 's': 
                        __local_save_cur( console_number );
                        break;

                    // Restore cursor
                    case 'u': 
                        __local_restore_cur(console_number);
                        break;
                };
                break;

            // Stage fail
            default:
                printf ("console_write: default\n");
                goto fail;
                break;
        };
    };  // FOR 

// done:
    return (ssize_t) StringSize;
fail:
    refresh_screen();
    return -1;
}



/*
 ********************************************
 * console_scroll:
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
 * #todo: 
 * Fazer o scroll somente no stream stdin e 
 * depois mostrar ele pronto.
 */

// Called by __local_insert_line() and  console_outbyte().

void console_scroll (int console_number){

    // Salvar cursor.
    unsigned long OldX=0;
    unsigned long OldY=0;

    register int i=0;


    if ( VideoBlock.useGui != TRUE )
    {
        debug_print ("console_scroll: no GUI\n");
        panic       ("console_scroll: no GUI\n");
    }

    // #todo: check overflow
    if ( console_number < 0 ){
        panic ("console_scroll: [FAIL] console_number\n");
    }


    // Scroll the screen rectangle.
    // See: windows/rect.c

    scroll_screen_rect();

    // Clena the last line.
  
	// Salva cursor
    OldX = CONSOLE_TTYS[console_number].cursor_x; 
    OldY = CONSOLE_TTYS[console_number].cursor_y; 

    // Cursor na ultima linha.
    CONSOLE_TTYS[console_number].cursor_x =   CONSOLE_TTYS[console_number].cursor_left; 
    CONSOLE_TTYS[console_number].cursor_y = ( CONSOLE_TTYS[console_number].cursor_bottom); 


   // Limpa a últime linha.
   for ( i = CONSOLE_TTYS[console_number].cursor_x; 
         i < CONSOLE_TTYS[console_number].cursor_right; 
         i++ )
   {
        _console_outbyte (' ',console_number); 
   };


    // Reposiciona o cursor na última linha.
    CONSOLE_TTYS[console_number].cursor_x = CONSOLE_TTYS[console_number].cursor_left; 
    CONSOLE_TTYS[console_number].cursor_y = OldY;  //( CONSOLE[console_number].cursor_bottom -1); 

    refresh_screen();
}


/*
 ********************************
 * kclear:
 *     Limpa a tela em text mode.
 */

int kclear (int color, int console_number)
{
    int Status = -1;


    if ( VideoBlock.useGui == 1 )
    {
        backgroundDraw ( COLOR_BLUE );
        
        CONSOLE_TTYS[console_number].cursor_x = 0; 
        CONSOLE_TTYS[console_number].cursor_y = 0; 
        Status = 0;
        
    }else{ Status = -1; };

    return (int) Status;
}


 
// kclearClientArea: 
// Limpa a tela em text mode.
// deprecated
int kclearClientArea (int color)
{
    debug_print("kclearClientArea: deprecated\n");

    return (int) kclear (color, fg_console);
}



/*
 *************************************
 * insert_line:
 * 
 */

// Incluir uma linha no buffer de linhas da estrutura do tty atual.
// vamos copiar esse esquema do edito de textos em ring3.

int insert_line ( char *string, int line )
{
    debug_print ("insert_line: [TODO]\n");
    return (int) -1; 
}



/*
 *******************************************
 * REFRESH_STREAM:
 * 
 *     #IMPORTANTE
 *     REFRESH SOME GIVEN STREAM INTO TERMINAL CLIENT WINDOW !!
 */

// #todo
// Change this name. 
// Do not use stream in the base kernel.

void REFRESH_STREAM ( file *f )
{
    // loop
    int i=0;
    int j=0;

    char *ptr;

    int cWidth  = get_char_width();
    int cHeight = get_char_height();



    debug_print("console.c-REFRESH_STREAM: [FIXME] It is wrong!\n");

    if ( cWidth == 0 || cHeight == 0 )
    {
        panic ("REFRESH_STREAM: [FAIL] char w h\n");
    }


    j = (80*25);

    //
    // File
    //

    // #bugbug
    // Tem que checar a validade da estrutura e do ponteiro base.
    if ( (void *) f == NULL )
    { 
        panic ("REFRESH_STREAM: [FAIL] f\n");
    }


    // Pointer

    ptr = f->_base;

    // #bugbug
    // Tem que checar a validade da estrutura e do ponteiro base.
    //if ( (void *) c == NULL ){ ? }

    // Seleciona o modo terminal.

    //++
    stdio_terminalmode_flag = TRUE; 
    for ( i=0; i<j; i++ )
    {
        printf ("%c", *ptr );

        // #bugbug
        // It is very wrong!
        
        refresh_rectangle ( 
            (CONSOLE_TTYS[fg_console].cursor_x * cWidth), 
            (CONSOLE_TTYS[fg_console].cursor_y * cHeight),  
            cWidth, 
            cHeight );

        ptr++;
    };
    stdio_terminalmode_flag = FALSE; 
    //--
}


void console_set_current_virtual_console (int n)
{
    if ( n < 0 || n >= 4 ){
        debug_print ("console_set_current_virtual_console: Limits\n");
        return;
    }

    fg_console = n;
}


int console_get_current_virtual_console (void)
{
    return (int) fg_console;
}


// Called by: 
// __local_ps2kbd_procedure in ps2kbd.c

void jobcontrol_switch_console(int n)
{
    // #todo:
    // maybe we can do somo other configuration here.
 
    if ( n<0 || n >= CONSOLETTYS_COUNT_MAX )
    {
        debug_print("jobcontrol_switch_console: Limits\n");
        return;
    }

    console_set_current_virtual_console(n);
}


/*
 *********************************************
 * console_init_virtual_console:
 *
 *     Initializes a virtual console.
 */

// #bugbug
// #IMPORTANTE
// Essa função apresenta problemas de compilação
// quando incluímos mais código.

// #test
// We are including a pointer to the RIT. raw input thread.
// This is the control thread of the window with focus on kgws.

// See: console.h and tty.h

void console_init_virtual_console (int n)
{
    int ConsoleIndex = -1;


    debug_print ("console_init_virtual_console:\n");

    ConsoleIndex = n;

    if ( ConsoleIndex < 0 || ConsoleIndex >= CONSOLETTYS_COUNT_MAX  )
    {
        debug_print ("console_init_virtual_console: [FAIL] ConsoleIndex\n");
        panic       ("console_init_virtual_console: [FAIL] ConsoleIndex\n");
    }

    // Todo virtual console eh uma tty. Os 4.
    CONSOLE_TTYS[ConsoleIndex].objectType  = ObjectTypeTTY;
    CONSOLE_TTYS[ConsoleIndex].objectClass = ObjectClassKernelObjects;
    CONSOLE_TTYS[ConsoleIndex].used  = TRUE;
    CONSOLE_TTYS[ConsoleIndex].magic = 1234;

    // No thread for now.
    CONSOLE_TTYS[ConsoleIndex].control = NULL;

    // tty is a terminal, so the user logs on a terminal.
    // No user logged yet.
    CONSOLE_TTYS[ConsoleIndex].user_info = NULL;

    // Security stuff.
    // Nao sei se essas estruturas estao prontas para isso nesse momento
    // ou se esses ponteiros sao nulos.
    CONSOLE_TTYS[ConsoleIndex].user_session = NULL;  //CurrentUserSession;
    CONSOLE_TTYS[ConsoleIndex].room         = NULL;  // CurrentRoom;
    CONSOLE_TTYS[ConsoleIndex].desktop      = NULL;  // CurrentDesktop;

    // file pointer
    // this file handles this tty object
    // CONSOLE[ConsoleIndex]._fp
    
    // tty name
    //CONSOLE_TTYS[ConsoleIndex].name[?] 
    CONSOLE_TTYS[ConsoleIndex].Name_len = 0;  //initialized

    //#todo: Indice do dispositivo.
    // CONSOLE_TTYS[ConsoleIndex].device = 0;   // initialized.

    CONSOLE_TTYS[ConsoleIndex].driver = NULL;  //driver struct
    CONSOLE_TTYS[ConsoleIndex].ldisc  = NULL;  //line discipline struct

    //CONSOLE_TTYS[ConsoleIndex].termios??       //termios struct (not a pointer)

    // process group.
    CONSOLE_TTYS[ConsoleIndex].gid = current_group;

    // ??
    // Quantos processos estao usando essa tty.
    CONSOLE_TTYS[ConsoleIndex].pid_count=0;


    CONSOLE_TTYS[ConsoleIndex].type = 0;
    CONSOLE_TTYS[ConsoleIndex].subtype = 0;
        
    CONSOLE_TTYS[ConsoleIndex].flags = 0;

    // not stopped
    CONSOLE_TTYS[ConsoleIndex].stopped = FALSE;

    // process
    //CONSOLE_TTYS[ConsoleIndex].process = KernelProcess;
    
    // thread
    //CONSOLE_TTYS[ConsoleIndex].thread  = ?

    // Qual terminal virtual esta usando essa tty.
    CONSOLE_TTYS[ConsoleIndex].virtual_terminal_pid = 0;

    // Window.
    // When we are using the kgws.
    // CONSOLE_TTYS[ConsoleIndex].window = NULL;


    //
    // == buffers ===========================
    //

    // #bugbug
    // No buffers fo rthe virtual consoles.
    // remember: 
    // The virtual console is used only in the 'stdout' of a process.
    CONSOLE_TTYS[ConsoleIndex].nobuffers = TRUE;   // No buffers.
    CONSOLE_TTYS[ConsoleIndex]._rbuffer = (file *) 0; 
    CONSOLE_TTYS[ConsoleIndex]._cbuffer = (file *) 0;
    CONSOLE_TTYS[ConsoleIndex]._obuffer = (file *) 0;


    // cursor dimentions in pixel.
    // #bugbug: determinado
    CONSOLE_TTYS[ConsoleIndex].cursor_width_in_pixels = 8; 
    CONSOLE_TTYS[ConsoleIndex].cursor_height_in_pixels = 8;

    //cursor position in chars.
    CONSOLE_TTYS[ConsoleIndex].cursor_x = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_y = 0;

    // cursor margin
    CONSOLE_TTYS[ConsoleIndex].cursor_left = 0;
    CONSOLE_TTYS[ConsoleIndex].cursor_top  = 0;
    
    // cursor limits
    CONSOLE_TTYS[ConsoleIndex].cursor_right  = 0+(SavedX/8) -1;  // (screen width / char width)
    CONSOLE_TTYS[ConsoleIndex].cursor_bottom = 0+(SavedY/8) -1;  // (screen height/ char height)
    
    //everyone.
    CONSOLE_TTYS[ConsoleIndex].cursor_color = COLOR_WHITE; 


    if ( ConsoleIndex == 0){
        CONSOLE_TTYS[ConsoleIndex].cursor_color = COLOR_WHITE; 
    }

    if ( ConsoleIndex == 1){
        CONSOLE_TTYS[ConsoleIndex].cursor_color = COLOR_RED; 
    }

    if ( ConsoleIndex == 2){
        CONSOLE_TTYS[ConsoleIndex].cursor_color = COLOR_GREEN; 
    }

    if ( ConsoleIndex == 3){
        CONSOLE_TTYS[ConsoleIndex].cursor_color = COLOR_BLUE; 
    }


    //#todo
    // Buffers !!!
    //CONSOLE_TTYS[ConsoleIndex]._rbuffer ...
    //CONSOLE_TTYS[ConsoleIndex]._cbuffer ...    


    //#todo
    // Local mode flags.
    CONSOLE_TTYS[ConsoleIndex].termios.c_lflag = ECHO;


    //CONSOLE_TTYS[ConsoleIndex].vc_mode = 0;

    // #bugbug
    // A estrutura tem mais elementos que podem ser inicializados.
    // Tivemos problemas ao tentar inicializa-los.
}


//
// ============================================
//

// Ok. It is owrking on qemu
// Used by pitTimer() in pit.c
void consoleBlinkTextCursor(void)
{

    unsigned long __cWidth  = gwsGetCurrentFontCharWidth();
    unsigned long __cHeight = gwsGetCurrentFontCharHeight();


    // ------------------------------------

    if ( __cWidth == 0  ||  __cHeight == 0 ){
        panic ("pitBlinkTextCursor: char size\n");
    }

    // fail
    if ( fg_console < 0 )
        return;


    // fail
    if ( (void*) shared_buffer_cursor_icon == NULL )
        return;


    // Apaga.
    // Apaga mostrando o conteúdo do backbuffer.
         
    if ( consoleTextCursorStatus != TRUE )
    { 
        refresh_rectangle ( 
                    (CONSOLE_TTYS[fg_console].cursor_x + 1)  * __cWidth, 
                    CONSOLE_TTYS[fg_console].cursor_y        * __cHeight, 
                    32, 
                    32 );

        consoleTextCursorStatus = TRUE;
        goto done;
    }

    // Acende.
    // Acende mostrando um BMP diretamente no lfb.

    if ( consoleTextCursorStatus == TRUE )
    {
        bmpDisplayCursorBMP ( 
                    shared_buffer_cursor_icon, 
                    (CONSOLE_TTYS[fg_console].cursor_x + 1) * __cWidth, 
                    CONSOLE_TTYS[fg_console].cursor_y       * __cHeight );
         
        consoleTextCursorStatus = FALSE;
        goto done;
    }

done:
    return;
}

/*
 ********************************************** 
 * console_ioctl:
 * 
 */

// Podemos mudar as características de um console.

int 
console_ioctl ( 
    int fd, 
    unsigned long request, 
    unsigned long arg )
{
    debug_print ("console_ioctl: TODO\n");

    // #todo: Check overflow
    if (fd<0){
        debug_print ("console_ioctl: [ERROR] fd\n");
        return -1;
    }

    // #todo: Check overflow
    if (fg_console<0){
        debug_print ("console_ioctl: [ERROR] fg_console\n");
        return -1;
    }


    switch (request){

    // #test
    // Change the color of the char for the current virtual console.
    // ok. it is working.
    case 1000:
        CONSOLE_TTYS[fg_console].cursor_color = (unsigned long) arg;
        return 0;  //ok
        break;

    // cursor x position
    // #bugbug #todo  limits
    case 1001:
        CONSOLE_TTYS[fg_console].cursor_x = 0;  return 0;
        break;

    // cursor y position
    // #bugbug #todo  limits
    case 1002:
        CONSOLE_TTYS[fg_console].cursor_y = 0;  return 0;
        break;

    // switching the current virtual console.
    // We have onlu 4 virtual consoles.
    case 1003:
        if ( arg >= 0 && arg < CONSOLETTYS_COUNT_MAX )
        { 
            fg_console = arg;
            return 0; 
        }
        return -1;
        break; 

    // #todo:
    // There is no fflush here in ring0.
    // The ring3 libc is doing this job using write.
    case TCIFLUSH:
        debug_print ("console_ioctl: [TEST] flush\n");
        break;
        
    // #todo: Yes, we can return data from the console tty termios. 
    // case TCGETS:
    // ...
    
    default:
        debug_print ("console_ioctl: [TODO] request\n");
        break;
    };

    return -1;
}


// main routine.
// called by main.c
int VirtualConsole_initialize(void)
{
    // Virtual Console:
    // The kernel only have four virtual consoles.

    fg_console = 0;

    console_init_virtual_console(0);
    console_init_virtual_console(1);
    console_init_virtual_console(2);
    console_init_virtual_console(3);
    
    jobcontrol_switch_console(0);


		// Obs: 
		// O video já foi inicializado em main.c.
		// Isso atualiza a estrutura de console do console atual.

    // BANNER !
    // Welcome message. (Poderia ser um banner.) ??


    // Cursor:
    // See: 0mem/core/system.c
    
    set_up_cursor(0,0);

    return 0;
}



//============================================
// input:
// called by devices that are not block devices.
// probably keyboard and serial devices.
// See: keyboard.c and serial.c
// Called by DeviceInterface_PS2Keyboard() in ps2kbd.c


void 
console_interrupt(
    int target_thread, 
    int device_type, 
    int data)
{

    //int TargetThread = foreground_thread;
    int TargetThread = target_thread;
    int DeviceType   = device_type;
    int Data         = data;


    // #todo
    // E se não tivermos uma foreground thread ?
    // foreground representa a thred com 'foco de entrada'
    // >> então, se não tivermos uma thread com foco de entrada,
    // podemos mandar a mensagem para outra thread ?

    // #todo: Check overflow

    if ( TargetThread < 0 )
    {
        debug_print ("console_interrupt: [FAIL] TargetThread\n");
        
        // #todo
        // Maybe we can set the idle thread if it fail.

        return;
    }


    switch (DeviceType){

        // keyboard
        // data =  raw byte.
        // See: vt/draw/model/kgws.c
        case CONSOLE_DEVICE_KEYBOARD:
            debug_print("console_interrupt: input from keyboard device\n");
            UserInput_SendKeyboardMessage (TargetThread, Data);
            break;

        // COM port
        case CONSOLE_DEVICE_SERIAL:
            debug_print("console_interrupt: input from serial device\n");
            break;
 
        //network device.
        case CONSOLE_DEVICE_NETWORK:
            debug_print("console_interrupt: input from network device\n");
            break;

        // ...

        default:
            debug_print("console_interrupt: [FAIL] Default input device\n");
            break;
    };
}


/*
 * set_up_cursor:
 *     Setup cursor for the current virtual console.
 */

// #todo
// Maybe change to console_set_up_cursor();

// We need a routine to change the cursor inside a wigen window.
// The console has a window ? No ? ... but it has a dimension.
// See the tty structure at hal/dev/tty/tty.h

// We need to know that there is a difference between 
// printing at a given console and printing at a given window.
// The tty has a window, but we are not using it, we are using
// the margins for the console.

// #todo
// Quando estivermos colocando o cursor em uma janela e
// a janela não for válida, então colocamos o cursor na posição 0,0.

void set_up_cursor ( unsigned long x, unsigned long y )
{
    if (fg_console<0){ return; }

    CONSOLE_TTYS[fg_console].cursor_x = (unsigned long) x;
    CONSOLE_TTYS[fg_console].cursor_y = (unsigned long) y;
}


/*
 * get_cursor_x:
 *     Pega o valor de x.
 *     @todo: Isso pode ir para outro lugar.
 */
unsigned long get_cursor_x (void)
{
    return (unsigned long) CONSOLE_TTYS[fg_console].cursor_x;
}

/*
 * get_cursor_y:
 *     Pega o valor de y.
 *     @todo: Isso pode ir para outro lugar.
 */
unsigned long get_cursor_y (void)
{
    return (unsigned long) CONSOLE_TTYS[fg_console].cursor_y; 
}

//
// End.
//


