
//#importante:
//Essas coisas não pertencem ao sheel e irão 
//para os lugarem que darão suporte ao terminal;(console)


#include "sh.h"


/*
 ***************************************************
 * shellInsertNextChar:
 *     Coloca um char na próxima posição do buffer.
 *     Memória de vídeo virtual, semelhante a vga.
 */
 
void shellInsertNextChar (char c){
		
	//cursor da linha
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) c;
	
	//refresh
	shellRefreshCurrentChar();
	
	//update
	textCurrentCol++;
	
	if (textCurrentCol >= 80 )
	{
		textCurrentCol = 0;
		
		textCurrentRow++;
		
		if ( textCurrentRow >= 25 )
		{
			shellScroll ();
			while(1){}
		}
	}
	
	LINES[textCurrentRow].pos = textCurrentCol;
	LINES[textCurrentRow].right = textCurrentCol;
};


//refresh do char que está na posição usada pelo input.
void shellRefreshCurrentChar (){
	
	printf ("%c", LINES[textCurrentRow].CHARS[textCurrentCol] );
};


/*
 ********************************************
 * shellScroll:
 *     @todo: Efetuar um scroll somente dentro 
 * da VGA virtual.
 * #importante: isso não deveria estar aqui,
 * deve ser uma rotina de automação, presente 
 * em alguma biblioteca, servidor ou kernel.
 */

void shellScroll (){
	
	//reajustando a área visível do buffer 
 

	//desliga o cursor
	//system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	

    testChangeVisibleArea();	//desloca a área visível usando delta.
	shellRefreshVisibleArea();
	
	//#todo:posicionar cursor
	
	//reabilita o cursor
	//system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


void testChangeVisibleArea (){
	
	textTopRow += textWheelDelta;
	textBottomRow += textWheelDelta;	
};


void updateVisibleArea( int direction ){
	
    switch (direction)
    {
	    case 0:
	        textTopRow += textWheelDelta;
	        textBottomRow += textWheelDelta;			
            break; 		
			
	    case 1:
	        textTopRow -= textWheelDelta;
	        textBottomRow -= textWheelDelta;					
            break; 		
	}	
};


//mostra a área visível dentro do buffer de linhas.
void shellRefreshVisibleArea (){
	
	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	
	//
	//seta o cursor no início da janela.
	//
	
	unsigned long left, top, right, bottom;
 
    left = (terminal_rect.left/8);
    top = (terminal_rect.top/8);
	
    shellSetCursor ( left, top );
	

	//
	// efetua o refresh do char atual, que agora é o primeiro 
	// depois os outros consecutivos.
	//
	
	int i=0;
	int j=0;
	
	//textTopRow = 3;
	//textBottomRow = 3 + 25;
	
	if ( textTopRow > textBottomRow )
	{
		printf("shellRefreshVisibleArea: textTopRow fail");
	}
	
	//toda a área visível.
	//for ( i=0; i<25; i++ )	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{	
	        //refresh
            printf ("%c", LINES[i].CHARS[j] );						
		}
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


/*
 * shellSetCursor:
 *     Configurando o cursor. (stdio.h).
 *
 * @todo: Aqui quando definimos os valores o cursor no shell 
 * devemos considerar que a janela com o foco de entrada tambem tem um cursor...
 * Temos que atualizar o cursor da janela com foco de entrada se quizermos 
 * escrever corretamente dentro dela.
 * e isso se faz através de uma chamada ao kernel.
 */
 
void shellSetCursor ( unsigned long x, unsigned long y ){
	
	// Coisas do kernel.
	
	//setando o cursor usado pelo kernel base.	
    apiSetCursor (x,y);
	
    //Atualizando as variáveis globais usadas somente aqui no shell.
    //setGlobals:	
    
	//#importante: ONDE ESTÃO DEFINIDAS ESSAS VARIÁVEIS ??
	
	g_cursor_x = (unsigned long) x;
    g_cursor_y = (unsigned long) y;	
	
	
	//
	// Coisas do screen buffer.
	//
    
	move_to ( x, y );
};


/*
 * move_to:
 *    Move o cursor de posição.
 *    Assim o próximo char será em outro lugar da janela.
 */
void move_to ( unsigned long x, unsigned long y ){
	
	if ( x > wlMaxColumns || y > wlMaxRows )
		return;
	
	//screen_buffer_x = x;
	//screen_buffer_y = y;
	
	textCurrentCol = x;
	textCurrentRow = y;
	
	//screen_buffer_pos = ( screen_buffer_y * wlMaxColumns + screen_buffer_x ) ;
};


//um teste mostrando todas as linhas do boffer de linhas.
void testShowLines(){
	
	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	int i=0;
	int j=0;
	
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    //LINES[i].CHARS[j] = (char) 'x';
		    //LINES[i].ATTRIBUTES[j] = (char) 7;
	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		printf ("\n");
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
};


/*
 * shellClearBuffer:
 *     Limpa o buffer da tela.
 */
void shellClearBuffer (){
	
	int i = 0;
	int j = 0;
	
	//inicializamos com espaços.
	for ( i=0; i<32; i++ )
	{
		for ( j=0; j<80; j++ ){
			
		    LINES[i].CHARS[j] = (char) ' ';
		    LINES[i].ATTRIBUTES[j] = (char) 7;
	    }
		
		LINES[i].left = 0;
		LINES[i].right = 0;
		
		LINES[i].pos = 0;
	};
};


/*
 * shellShowScreenBuffer:
 *     Quando for efeturar o refresh da tela
 * é o conteúdo desse buffer que deve ser pintado 
 * no retãngulo que é a área de cliente do shell.  
 */
//mostra o buffer screen buffer, onde ficam 
//armazenados os caracteres e atributos datela
//do terminal virtual.

//#importante: vamos mostrar todo o buffer de words, a partir 
//da posição atual do cursor, forçando um scroll

//Isso é só um teste.
void shellShowScreenBuffer (){
	
    shellRefreshVisibleArea();
};


/*
 *******************************************
 * shellRefreshScreen:
 * 
 *     #importante 
 *      
       #OBS
       NA VERDADE SE REFERE AO REFRESH DA ÁREA DE CLIENTE DO SHELL.
 *
 *     Copia o conteúdo do (screen_buffer) buffer de output 
 * para a tela. (dentro da janela). 
 * ## Acho que se trata de stdout.
 * É uma memória VGA virtual com caractere e atributo.
 * na hora de efetuar refresh precisamos considerar o atributo 
 * para sabermos a cor do caractere e de seu background.
 */
void shellRefreshScreen (){

	//desabilita o cursor
	system_call ( 245, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);
	
	int i=0;
	int j=0;
	
	for ( i=textTopRow; i<textBottomRow; i++ )
	{
		for ( j=0; j<80; j++ )
		{
		    //LINES[i].CHARS[j] = (char) 'x';
		    //LINES[i].ATTRIBUTES[j] = (char) 7;
	        
			printf ("%c", LINES[i].CHARS[j] );
		}
		printf ("\n");
	};

	//reabilita o cursor
	system_call ( 244, (unsigned long) 0, (unsigned long) 0, (unsigned long) 0);	
	
};


// a intenção aqui é fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void shellRefreshLine ( int line_number ){
	
	if ( line_number > wlMaxRows )
		return;	
	
	int lin = (int) line_number; 
	int col = 0;  
	
	
#ifdef SHELL_VERBOSE		
	//#debug
	printf("shellRefreshLine:\n");
#endif 

	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	
	shellSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < wlMaxColumns; col++ )
	{
	    //Mostra um char do screen buffer.
		printf( "%c", LINES[lin].CHARS[col] );
	};
};


// a intenção aqui é fazer o refresh de apenas uma linha do arquivo.
//#todo podemos fazer o mesmo para um char apenas.

void shellRefreshChar ( int line_number, int col_number ){
	
	if ( col_number > wlMaxColumns || line_number > wlMaxRows )
		return;
	
	shellSetCursor ( col_number, line_number );

	//Mostra um char do screen buffer.
	printf( "%c", LINES[line_number].CHARS[col_number] );	
};


static void del (void){
	
	LINES[textCurrentRow].CHARS[textCurrentCol] = (char) '\0';
	LINES[textCurrentRow].ATTRIBUTES[textCurrentCol] = 7;
};


//carriege return
static void cr (void){
	
    textCurrentCol = 0;
};


// ??
//voltando uma linha.
static void ri (void){
	
	//if ( screen_buffer_y > top ){
		
		// Volta uma linha.
	//	screen_buffer_y--;
	//	screen_buffer_pos = (screen_buffer_pos - columns); 
	//	return;
	//}
	
	//@todo:
	//scrdown();
};


//line feed
static void lf (void){
	
	//enquanto for menor que o limite de linhas, avança.
	if ( textCurrentRow+1 < wlMaxRows )
	{
		textCurrentRow++; 
		return;
	}
	
	//#todo: Scroll up;
	//scrup();
};


static void save_cur (void){
	
	textSavedCol = textCurrentCol;
	textSavedRow = textCurrentRow;
};


static void restore_cur (void){
	
	textCurrentCol = textSavedCol;
	textCurrentRow = textSavedRow;
};


// Insere um caractere dentro do buffer.
void 
shellInsertCharXY ( unsigned long x, 
                    unsigned long y, 
				    char c )
{
	
	if ( x >= wlMaxColumns || y >= wlMaxRows ){
		
		return;
	}

	LINES[y].CHARS[x] = (char) c;
	LINES[y].ATTRIBUTES[x] = 7;
};


char 
shellGetCharXY ( unsigned long x, 
                 unsigned long y )
{
	
	if ( x >= wlMaxColumns || y >= wlMaxRows ){
		
		return;
	}

	return (char) LINES[y].CHARS[x];
};


void shellInsertCR (){
    
	shellInsertNextChar ( (char) '\r' );		
};


void shellInsertLF (){
	
	shellInsertNextChar ( (char) '\n' );
};


void shellInsertNullTerminator (){
	
	shellInsertNextChar ( (char) '\0' );	
};


//usado para teste de scroll.
//imprime varias vezes o char indicado.
void testScrollChar ( int c ){
	
    int i;
	
    for ( i=0; i < (wlMaxColumns*26); i++ )
	{
	    //se chegamos no limite do screen_buffer
		//...
		shellInsertNextChar ((char) c);	
	}		
};


void clearLine ( int line_number )
{
    int lin = (int) line_number; 
	int col;  
	
	int Offset = 0; //Deslocamento dentro do screen buffer.
	
	//cursor apontando par ao início da janela.
	//usado pelo printf.
	//@todo: podemos colocar o cursor no 
	//início da área de cliente.
	//left será a coluna.
	
	shellSetCursor ( col, lin );
		
	//colunas.
	for ( col=0; col < wlMaxColumns; col++ )
	{
		
		//#BUGBUG 
		//NÃO USAMOS MAIS ESSE BUFFER!!!
		
	    //Mostra um char do screen buffer.
		//printf( "%c", screen_buffer[Offset] );
		    
		Offset++; //ignora o atributo.
	    Offset++;
	};
	
    //shell_buffer_pos = 0;  //?? posição dentro do buffer do shell.	
};

//Qual será a linha que estará no topo da janela.
void textSetTopRow ( int number )
{
    textTopRow = (int) number; 	
};

//Qual será a linha que estará na parte de baixo da janela.
void textSetBottomRow ( int number )
{
    textBottomRow = (int) number; 	
};

int textGetTopRow ()
{
    return (int) textTopRow; 	
};

int textGetBottomRow ()
{
    return (int) textBottomRow; 	
};



