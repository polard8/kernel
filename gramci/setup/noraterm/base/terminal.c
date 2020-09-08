// são as sequẽncias que comandam o display para fazer as coisas.
// os comandos estão nos arquivos para o jeito unix-like.
// masos comandos podem vim através do procedimento de janela.

// #todo: 
// Colocar as rotinas de terminal virtual aqui,
// separadas do shell

#include "noraterm.h"  


/*
static int
utf8countBytes (int c)
{
    if (c < 0)
	    return 0;

    if (c <= 0x7F) {
	    return 1;
    } else if (c <= 0x7FF) {
	      return 2;
    } else if (c <= 0xFFFF) {
	      return 3;
    } else
	      return 4;
}
*/




/*
 ***************************************************
 * terminalInsertNextChar:
 *     Coloca um char na próxima posição do buffer.
 *     Memória de vídeo virtual, semelhante a vga.
 *     #todo: Esse buffer poderia ser um arquivo que o kernel
 * pudesse usar, ou o servidor de recursos gráficos pudesse usar.
 */

	//#importante:
	//o refresh é chamado no default do procedimento de janela

void terminalInsertNextChar (char c){
	
	// #todo
	// para alguns caracteres temos que efetuar o flush.
	// \n \r ... ??
			
	// Coloca no buffer.
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
}


// # terminal stuff
void terminalInsertNullTerminator (void){
	
	terminalInsertNextChar ( (char) '\0' );
}


// # terminal stuff
void terminalInsertLF (void){
	
	terminalInsertNextChar ( (char) '\n' );
}


// # terminal stuff
void terminalInsertCR (void){
    
	terminalInsertNextChar ( (char) '\r' );
}


// # terminal stuff
//line feed
void lf (void){
	
	//enquanto for menor que o limite de linhas, avança.
	if ( textCurrentRow+1 < __wlMaxRows )
	{
		textCurrentRow++; 
		return;
	}
	
	//#todo: Scroll up;
	//scrup();
}


// # terminal stuff
//carriege return
void cr (void){
	
    textCurrentCol = 0;
}


// # terminal stuff
// ??
//voltando uma linha.
void ri (void){
	
	//if ( screen_buffer_y > top ){
		
		// Volta uma linha.
	//	screen_buffer_y--;
	//	screen_buffer_pos = (screen_buffer_pos - columns); 
	//	return;
	//}
	
	//@todo:
	//scrdown();
}


// # terminal stuff
void del (void){
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) '\0';
	LINES[textCurrentRow].ATTRIBUTES[textCurrentCol] = 7;
}


/*
//inserindo uma string em uma posição do buffer de saída.
void shellInsertStringPos( unsigned long offset, char *string );
void shellInsertStringPos( unsigned long offset, char *string )
{
    //@todo
};
*/


/*
 preenche todo o buffer de saída com char ou atributo
void shellFillOutputBuffer( char element, int element_type )
{
	
}
*/



// # terminal stuff
// Insere um caractere sentro do buffer.

char 
terminalGetCharXY ( unsigned long x, 
                    unsigned long y )
{	
	if ( x >= __wlMaxColumns || y >= __wlMaxRows )
	{	
		return;
	}

	return (char) LINES[y].CHARS[x];
}


// # terminal stuff
// Insere um caractere sentro do buffer.

void 
terminalInsertCharXY ( unsigned long x, 
                       unsigned long y, 
                       char c )
{
	if ( x >= __wlMaxColumns || y >= __wlMaxRows )
	{	
		return;
	}

	LINES[y].CHARS[x] = (char) c;
	LINES[y].ATTRIBUTES[x] = 7;
}






// # terminal stuff
static void save_cur (void){
	
	textSavedCol = textCurrentCol;
	textSavedRow = textCurrentRow;
}


// # terminal stuff
static void restore_cur (void){
	
	textCurrentCol = textSavedCol;
	textCurrentRow = textSavedRow;
}



/*
 * terminalRefreshCurrentChar:
 *    refresh do char que está na posição usada pelo input.     
 *    em seguida fazemos a atualização das posições.
 */

// #test
// Vamos tentar imprimir na tela usando a api.

void terminalRefreshCurrentChar2 (void){
	
	int c = (int) LINES[textCurrentRow].CHARS[textCurrentCol];


    //
    // Exibe o char usando a api.
    //

    gde_put_char (c);
    
		
	// Atualiza os deslocamanentos dentro do buffer.
	
	// update
	textCurrentCol++;
	
	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			shellScroll ();
			while (1){}
		}
	}
	
	LINES[textCurrentRow].pos = textCurrentCol;
	LINES[textCurrentRow].right = textCurrentCol;
	
	
	//atualizando o cursor do sistema,
	//terminalSetCursor ( textCurrentRow, textCurrentCol );
	
}



/*
 * terminalRefreshCurrentChar:
 *    refresh do char que está na posição usada pelo input.     
 *    em seguida fazemos a atualização das posições.
 */

// #bugbug
// A libc não imprime na tela. Então o terminal virtual precisa usar a api
// ou enviar o servidor através de arquivo ou mensagem.

// #importante: No nosso caso vamos usar a api e impimir na tela.


void terminalRefreshCurrentChar (void){
	
	//#usar api.
	printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
	fflush(stdout);
	
	// Atualiza os deslocamanentos dentro do buffer.
	
	// update
	textCurrentCol++;
	
	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			shellScroll ();
			while (1){}
		}
	}
	
	LINES[textCurrentRow].pos = textCurrentCol;
	LINES[textCurrentRow].right = textCurrentCol;
}


// a intenção aqui é fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void terminalRefreshChar ( int line_number, int col_number ){
	
	if ( col_number > __wlMaxColumns || line_number > __wlMaxRows )
		return;
	
	terminalSetCursor ( col_number, line_number );

	//Mostra um char do screen buffer.
	printf ("%c", LINES[line_number].CHARS[col_number] );	
}



// a intenção aqui é fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void terminalRefreshLine ( int line_number ){
	
	if ( line_number > __wlMaxRows )
		return;	
	
	int lin = (int) line_number; 
	int col = 0;  
	
	
#ifdef SHELL_VERBOSE		
	//#debug
	printf ("terminalRefreshLine:\n");
#endif 

	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	
	terminalSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < __wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf ( "%c", LINES[lin].CHARS[col] );
	};
}


/*
 *******************************************
 * terminalRefreshScreen:
 * 
 *     #importante 
 *      
       #OBS
       NA VERDADE SE REFERE AO REFRESH DA ÁREA DE CLIENTE.
 *
 *     Copia o conteúdo do (screen_buffer) buffer de output 
 * para a tela. (dentro da janela). 
 * 
 * ## Acho que se trata de stdout.
 * É uma memória VGA virtual com caractere e atributo.
 * na hora de efetuar refresh precisamos considerar o atributo 
 * para sabermos a cor do caractere e de seu background.
 */

void terminalRefreshScreen (void){

    int i=0;
    int j=0;

	// Desabilita o cursor
    system_call ( 245, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0);


    // Colocaremos o texto do buffer no início da área de cliente.
    terminalSetCursor ( 0, 0 );


	if ( textTopRow == textBottomRow )
	{
        gde_message_box ( 3,
           "terminalRefreshScreen",
           "==");
	}
	    
	if ( textTopRow > textBottomRow )
	{
        gde_message_box ( 3,
           "terminalRefreshScreen",
           ">");
	}

    //
    // # hack hack
    //
    
    //textBottomRow = textTopRow +23;

    // Copiar o texto para a tela.
    //for ( i=textTopRow; i<textBottomRow; i++ ) //toda a área visível. ()
    for ( i=textTopRow; i < textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{
			// isso não coloca no buffer de arquivo.
		    gde_put_char  ( (int) LINES[i].CHARS[j] );
		}

		//printf ("\n");
	    terminal_write_char ('\n');
	};

    //#teste
    terminalSetCursor ( 0, __wlMaxRows -2 );
        
	// Reabilita o cursor
    system_call ( 244, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0);
}


/*
 *************************************
 * terminalClearScreen:
 *     Limpar a tela do shell.
 *     Usada pelo comando 'cls'.
 */
 
void terminalClearScreen (void){

	unsigned long left, top, right, bottom;
	
    // Desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, 
	    (unsigned long) 0);	
	
	
	if ( (void *) shell_info.terminal_window != NULL )
	{
		//Limpa o buffer,
		terminalClearBuffer ();
		
		//#todo:
		//limpar a janela.
		
		//redraw window.
		gde_redraw_window ( shell_info.terminal_window, 1 );	
		
		// Cursor.
        // Ajusta o cursor.
        //left = (terminal_rect.left/8);
        //top = (terminal_rect.top/8);
        //terminalSetCursor ( left, top );
        
	    // Copiamos o conteúdo do screenbuffer para 
	    // a área de cliente do shell.
        //terminalRefreshScreen ();
	    //shellRefreshVisibleArea();

		// Cursor.
        // Ajusta o cursor.
        left = (terminal_rect.left/8);
        top = (terminal_rect.top/8);
        terminalSetCursor ( left, top );
	    
	    // show client window.
	    gde_show_window (shell_info.terminal_window);		
	}


    /* 
	struct window_d *w;	
	w = (void *) shell_info.terminal_window;
	if ( (void *) w != NULL )
	{
		gde_redraw_window ( w, 1 );
	};
	*/
	
 
	
	// Reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, 
	    (unsigned long) 0);	
}


/*
 **********************************************
 * terminalSetCursor:
 *     Configurando o cursor. (stdio.h).
 *
 * @todo: 
 * Aqui quando definimos os valores o cursor no shell 
 * devemos considerar que a janela com o foco de entrada tambem tem um cursor...
 * Temos que atualizar o cursor da janela com foco de entrada se quizermos 
 * escrever corretamente dentro dela.
 * e isso se faz através de uma chamada ao kernel.
 */

void terminalSetCursor ( unsigned long x, unsigned long y ){

    //filtro
	if ( x >= __wlMaxColumns)
	{
		x = (__wlMaxColumns-1);
	} 
	
	if( y >= __wlMaxRows )
	{
		y = (__wlMaxRows-1);
	}	


    //Atualizando as variáveis globais usadas somente aqui no shell.
    // Não sei se precisamos disso. talvez deletar.
    g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;

	// Atualiza os ponteiros para o buffer de texto. (estrutura) 
	move_to ( x, y);
	
	// Coisas do kernel. 
	// Setando o cursor usado pelo kernel base.
	// Se isso for (0,0) então ficará no início da tela ???
	
	// #test
	// usaremos um posicionamento relativo.
	// considerando a janela do terminal.
	
	unsigned long __x, __y;

	__x = ( ( terminal_rect.left /8 ) + x ); 
	__y = ( ( terminal_rect.top  /8 ) + y );

	gde_set_cursor (__x,__y);
}



/*
 ****************************************
 * shellClearBuffer:
 *     Limpa o buffer da tela.
 *     Inicializamos com espaços.
 */


void terminalClearBuffer (void){

    int i=0;
    int j=0;

    for ( i=0; i<32; i++ )
    {
		for ( j=0; j<80; j++ )
		{
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		LINES[i].pos = 0;
    };
}



/*
 * shellShowScreenBuffer:
 *     Quando for efeturar o refresh da tela
 * é o conteúdo desse buffer que deve ser pintado 
 * no retãngulo que é a área de cliente do shell.  
 */
//mostra o buffer screen buffer, onde ficam 
//armazenados os caracteres e atributos datela
//do terminal virtual.

// #importante: 
// vamos mostrar todo o buffer de words, a partir 
// da posição atual do cursor, forçando um scroll

void terminalShowScreenBuffer (void)
{
	// Mostra a área visível dentro do buffer de linhas.
    terminalRefreshVisibleArea ();
}


/*
   #todo
 * Return true if any character cell starting at [row,col], for len-cells is
 * nonnull.
 */
/*
int
non_blank_line ( int row,
	             int col,
	             int len)
{
    int i;
    int found = 0;
	
	if ( row < 0 )
		return -1;
	
	if ( col < 0 )
		return -1;
	
	if ( len < 0 )
		return -1;
	
	for (i = col; i < len; i++) 
	{
	    if ( LINES[row].CHARS[i] ) 
		{
	        found = 1;
	        break;
	    }
	}
	
    return found;
}
*/



// Mostra a área visível dentro do buffer de linhas.
void terminalRefreshVisibleArea (void){

    unsigned long left, top, right, bottom;
    int i=0;
    int j=0;

    
    //desabilita o cursor
    system_call ( 245, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0);

    // Coloca o cursor no início da área de cliente.
    terminalSetCursor ( 0, 0 );

	// efetua o refresh do char atual, que agora é o primeiro 
	// depois os outros consecutivos.
	
	//textTopRow = 3;
	//textBottomRow = 3 + 25;
	
	if ( textTopRow > textBottomRow )
	{
		//#todo: usar MessageBox.
		printf ("shellRefreshVisibleArea: textTopRow fail");
	}


	//toda a área visível.
	//for ( i=0; i<25; i++ )	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{	
	        //refresh
            //printf ("%c", LINES[i].CHARS[j] );
            gde_put_char ( (int) LINES[i].CHARS[j]);
		}
	};

	//reabilita o cursor
	system_call ( 244, 
	    (unsigned long) 0, 
	    (unsigned long) 0, 
	    (unsigned long) 0);	
}


/*
 **********************************************
 * updateVisibleArea:
 *     Muda a área visível do buffer de arquivo.
 *     IN: 0=down 1=up
 */

void updateVisibleArea ( int direction ){

    // Limits.
    
    if (direction < 0)
        return;
    
    if (direction > 1)
        return;
    
    switch (direction)
    {
		// down
	    case 0:
	        if ( textBottomRow == DEFAULT_BUFFER_MAX_ROWS ){ return; }
	        textTopRow += textWheelDelta;
	        textBottomRow += textWheelDelta;
            break; 
		
		//up
	    case 1:
	        if ( textTopRow == 0 ){ return; }
	        textTopRow -= textWheelDelta;
	        textBottomRow -= textWheelDelta;
            break;
	}	
}



void terminalNewVisibleArea ( int text_top_row, int text_bottom_row )
{
	if ( text_top_row == text_bottom_row )
	{
        gde_message_box ( 3,
           "terminalNewVisibleArea",
           "==");
	}
	    
	if ( text_top_row > text_bottom_row )
	{
        gde_message_box ( 3,
           "terminalNewVisibleArea",
           ">");
	}
    
    
    //#todo:
    // Checar limites dos argumentos.

	textTopRow    = text_top_row;
	textBottomRow = text_bottom_row;
}


void testChangeVisibleArea(void)
{
	textTopRow += textWheelDelta;
	textBottomRow += textWheelDelta;	
}


/*
 **********************************************
 * testShowLines:
 *     #importante
 *     Um teste mostrando todas as linhas do buffer de linhas.
 *     #bugbug: Essa rotina é muito lenta. A linha demora para ser 
 * mostrada na tela.    
 */

void testShowLines (void){
	
	//enterCriticalSection (); 
	
	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	int i=0;
	int j=0;
	
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		
		printf ("\n");
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
	
	//exitCriticalSection (); 
}



void clearLine ( int line_number ){
	
    int lin = (int) line_number; 
	int col = 0;  
	
	int Offset = 0; //Deslocamento dentro do screen buffer.
	
	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	
	terminalSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < __wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf( "%c", screen_buffer[Offset] );
		    
		Offset++; //ignora o atributo.
	    Offset++;
	};
	
    //shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
}

//Qual será a linha que estará no topo da janela.
void textSetTopRow ( int number )
{
    textTopRow = (int) number; 	
}


int textGetTopRow (void)
{
    return (int) textTopRow; 	
}


//Qual será a linha que estará na parte de baixo da janela.
void textSetBottomRow ( int number )
{
    textBottomRow = (int) number; 	
}


int textGetBottomRow (void)
{
    return (int) textBottomRow; 	
}



void textSetCurrentRow ( int number )
{
    textCurrentRow = (int) number; 	
}


int textGetCurrentRow (void)
{
    return (int) textCurrentRow; 	
}



void textSetCurrentCol ( int number )
{
    textCurrentCol = (int) number; 	
}


int textGetCurrentCol (void)
{
    return (int) textCurrentCol; 	
}


/*
 * move_to:
 *    Move o cursor de posição.
 *    Assim o próximo char será em outro lugar da janela.
 */

void move_to ( unsigned long x, unsigned long y ){
	
	if ( x > __wlMaxColumns || y > __wlMaxRows )
		return;
	
	//screen_buffer_x = x;
	//screen_buffer_y = y;
	
	textCurrentCol = x;
	textCurrentRow = y;
	
	//screen_buffer_pos = ( screen_buffer_y * __wlMaxColumns + screen_buffer_x ) ;
}



/* credits: bsd*/
/* Pad STRING to COUNT characters by inserting blanks. */

int pad_to (int count, char *string){
	
    register int i;

    i = strlen (string);

    if (i >= count)
        string[i++] = ' ';
    else
    {
        while (i < count)
            string[i++] = ' ';
    }
    string[i] = '\0';

    return (i);
}


/*
void reset_terminal()
void reset_terminal(){
}
*/


//funcionou
// preencher com espaços do início da linha
//até a coluna atual
void terminal_clear_from_startofline (void)
{
    int i=0;
    unsigned long OldX, OldY;

    char temp;

    temp = 'X';

    //save
    OldX = textCurrentCol;
    OldY = textCurrentRow;

    terminalSetCursor ( 0, OldY );
    
    for (i=0; i<OldX; i++)
    {
		//coloca um char na posição atual.
        terminal_write_char (' ');
        //terminal_write_char ('X');
        //terminalInsertCharXY ( i, textCurrentRow, temp );
    }
    
    //Esse está funcionando.
    //A rotina acima que não está.
    terminalSetCursor ( OldX, OldY );
}


//funcionou
//preenche com espaço da coluna atual até o fim da linha.
void terminal_clear_to_endofline (void)
{

    int i=0;
    unsigned long OldX, OldY;

    char temp;

    temp = 'Y';
    
    //save
    OldX = textCurrentCol;
    OldY = textCurrentRow;

    //começa da coluna atual e vai até o fim da linha.
    for ( i=textCurrentCol; i< __wlMaxColumns; i++)
    {
		terminal_write_char (' ');
		//terminal_write_char ('Y');
        //terminalInsertCharXY ( i, textCurrentRow, temp );
    }

    terminalSetCursor ( OldX, OldY );
}



// Isso funcionou pacialmente ... 
void terminal_clear_to_endofdisplay (void)
{
    unsigned long x, y;
    
    unsigned long OldX, OldY;
    unsigned long NewX, NewY;    

    //save
    OldX = textCurrentCol;
    OldY = textCurrentRow;


    // Step1
    // Limpa o resto da linha atual.
    // mas o cursor volta na posição original.
        
    terminal_clear_to_endofline ();

    NewX = 0;
    NewY = OldY+1;
    

    // Step2
    // Limpa as linhas que faltam.
    // Começa da próxima linha. 
 
    if ( __wlMaxRows != DEFAULT_MAX_ROWS )
    {
		gde_message_box (3,
		    "terminal_clear_to_endofdisplay",
		    "__wlMaxRows limits");
    }

    if ( __wlMaxColumns != DEFAULT_MAX_COLUMNS )
    {
		gde_message_box (3,
		    "terminal_clear_to_endofdisplay",
		    "__wlMaxColumns limits");
    }


    if ( NewY >= __wlMaxRows )
    {
		gde_message_box ( 3,
		    "terminal_clear_to_endofdisplay",
		    "NewY fail");
    }

    if ( NewX >= __wlMaxColumns )
    {
		gde_message_box ( 3,
		    "terminal_clear_to_endofdisplay",
		    "NewX fail");
    }

    //for ( y=NewY; y<(NewY+8); y++ ) //funciona
    for ( y=NewY; y< (__wlMaxRows -2); y++ )
    {
		terminalSetCursor ( 0, y );
		
        //limpa uma linha desde o '0'.
        for (x=0; x< __wlMaxColumns; x++)
        {
			//coloca um char na posição atual.
            terminal_write_char (' ');
            //terminal_write_char ('Z');
        };
    };

		//MessageBox ( 3,
		    //"terminal_clear_to_endofdisplay",
		    //"fim");
    
    //while(1){}
    
    terminalSetCursor ( 0, (__wlMaxRows -3) );
}




// Interna. 
// Usada por terminal_scroll_display, logo abaixo.

    // Limpa a tela e  
    // copia o conteúdo do buffer na tela limpa.
    // #importante: Mostra apenas a área visível do buffer de arquivo.
    // Não meche no cursor.
void terminalCopyToScroll (void){

    unsigned long left, top, right, bottom;

    // Desabilita o cursor
    system_call ( 245, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0);


    //
    // A janela do terminal.
    //
    
    if ( (void *) shell_info.terminal_window != NULL )
    {

		// Redraw window.
		// Isso limpa a janela. (client area)
		// O Window server usar a estrutura de janela
		// para redezenhar ela.
		// Cor ??
		gde_redraw_window ( shell_info.terminal_window, 1 );

		//#todo
		//Limpa o buffer,
		//terminalClearBuffer ();

        // Cursor. Ajusta o cursor para 0,0.
        //terminalSetCursor ( left, top );
        
	    //??
	    // Copiamos o conteúdo do screen buffer para 
	    // a área de cliente do terminal.
	    
	    // Vamos colocar uma área visível maior possível para teste.
	    //pois pode ter coisa só no fim.
	    //terminalNewVisibleArea (0,23);  
        terminalRefreshScreen ();
	    //terminalRefreshVisibleArea();


        // Cursor. Ajusta o cursor para 0,0.
        //terminalSetCursor ( left, top );


        // show client window.
        // Agora com um novo texto nela.
        gde_show_window (shell_info.terminal_window);
    }

    //shellRefreshVisibleArea();
 
    // Reabilita o cursor
    system_call ( 244, 
        (unsigned long) 0, 
        (unsigned long) 0, 
        (unsigned long) 0);
}



void terminal_scroll_display (void)
{
    int i=0;
    unsigned long OldX, OldY;
    
    char temp;
    temp = ' ';
    

    //save
    OldX = textCurrentCol;
    OldY = textCurrentRow;


    // Limpa a tela e  
    // copia o conteúdo do buffer na tela limpa.
    // #importante: Mostra apenas a área visível do buffer de arquivo.
    // Não meche no cursor.
    terminalCopyToScroll ();
    
    //
    // Last line.
    //

    // Vamos limpar a última linha.
    
    // vamos posicionar o cursor no início da última linha.
    //terminalSetCursor ( 0, __wlMaxRows-1 );
    terminalSetCursor ( 0, __wlMaxRows-3 );  //teste
     
    if ( __wlMaxColumns != DEFAULT_MAX_COLUMNS )
    {
        gde_message_box ( 3,
           "terminal_scroll_display",
           "fail");
    }
     
    //limpa uma linha
    for (i=0; i<__wlMaxColumns; i++)
    {
        //coloca um char na posição atual.
        terminal_write_char ('$');
        //terminal_write_char (' ');
    };

    //terminalSetCursor ( OldX, OldY );
    terminalSetCursor ( 0, __wlMaxRows-3 );
}



void terminal_scroll_down (void)
{
    updateVisibleArea (0);
    terminal_scroll_display ();
}


void terminal_scroll_up (void)
{
    updateVisibleArea (1);
    terminal_scroll_display ();
}





