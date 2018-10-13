
// cedge.c - edge field for libc.

// extremidades das funções de impressão de caracteres ...
// aqui ficará só o output de byte.

#include <kernel.h>


/*
 **********************************************************************
 * _outbyte:
 *     @field 1
 *     Essa rotina efetivamente envia o caractere para a tela, não 
 * fazendo nenhum tipo de tratamento de caractere.
 *     Essa rotina é chamada pema rotina /outbyte/.
 *
 * Obs: 
 *     Um switch percebe o modo de vídeo e como esse caractere deve ser 
 * construído.
 * @todo: ?? Criar uma estrutura para parâmetros de vídeo. ??
 * 
 * #importante: Essa rotina de pintura deveria ser exclusiva para 
 * dentro do terminal. 
 */
void _outbyte (int c){
	
    unsigned long i;
	unsigned long x;
	unsigned long y;
	
    //O caractere.
	char ch = (char) c;
	char ch_atributo = (char) g_char_attrib;


	//suporte ao modo texto.
	//Base atual da memória de vídeo 0x000B8000;
    //@todo: usar VideoBlock.currentVM.
	char *vm = (char *) g_current_vm;    
	
	
	// #test
	// Tentando pegar as dimensões do char.
	// #importante: Não pode ser 0, pois poderíamos ter divisão por zero.
	
	
	int cWidth = get_char_width ();
	int cHeight = get_char_height ();
	
	if ( cWidth == 0 || cHeight == 0 )
	{
		//#debug
		printf("crts-libc-cedge-_outbyte: fail w h ");
		die();
	}
	
	// #Importante: 
	// Essa rotina não sabe nada sobre janela, ela escreve na tela como 
	// um todo. Só está considerando as dimensões do 'char'.


    // Caso estivermos em modo gráfico.
	 
	if ( VideoBlock.useGui == 1 )
	{

        //#importante: Essa rotina de pintura deveria ser exclusiva para 
        //dentro do terminal.
        //então essa flag não faz sentido.		
 
		if ( stdio_terminalmode_flag == 1 )
		{
			
			// ## NÃO TRANPARENTE ##
            // se estamos no modo terminal então usaremos as cores 
            // configuradas na estrutura do terminal atual.
            // Branco no preto é um padrão para terminal.			
            draw_char ( cWidth*g_cursor_x, cHeight*g_cursor_y, c, 
				COLOR_TERMINALTEXT, COLOR_TERMINAL2 );			
			
		}else{
			
			// ## TRANSPARENTE ##
		    // se não estamos no modo terminal então usaremos
		    // char transparente.
            // Não sabemos o fundo. Vamos selecionar o foreground.			
			drawchar_transparent ( cWidth*g_cursor_x, cHeight*g_cursor_y, 
				g_cursor_color, c );
		};
		
		//#testando ...
		//g_cursor_x++;
     	
		//goto done;
        return;		
	};
 
    // #bugbug
    // #testando
	// Caso estivermos em text mode.
    // #obs: Nunca usamos isso. :)
	
	if ( VideoBlock.useGui == 0 )
	{	
	    // Calcula o valor do deslocamento para text mode 80x25.
	    y = (g_cursor_y * 80 *2);
        x = g_cursor_x*2;    
        i = y + x;
        
		//envia o caractere e o atributo.
		vm[i+0] = ch;           
        vm[i+1] = ch_atributo;  
	};   
};


/*
 *******************************************************************
 * outbyte:
 *     Trata o caractere a ser imprimido e chama a rotina /_outbyte/
 * para efetivamente colocar o caractere na tela.
 *
 * Essa rotina é chamada pelas funções: /putchar/scroll/.
 * @todo: Colocar no buffer de arquivo.
 */
void outbyte (int c){
	
	static char prev = 0;
	
	// Obs:
	// Podemos setar a posição do curso usando método,
	// simulando uma variável protegida.
	
//checkChar:
        
      
    //switch ?? 

    //
    // m$. É normal \n retornar sem imprimir nada.
    //	
    
    //Início da próxima linha.    
    if ( c == '\n' && prev == '\r' ) 
    {
		if ( g_cursor_y >= (g_cursor_bottom-1) )
		{
	        
			scroll();
            g_cursor_y = (g_cursor_bottom-1);
			prev = c; 
			
		}else{
		    
			g_cursor_y++;
            g_cursor_x = g_cursor_left; //Por causa do prev.			
		    prev = c;
		};	
        return;
    };
	
        
    //Próxima linha.
	if ( c == '\n' && prev != '\r' ) 
    {
		if ( g_cursor_y >= (g_cursor_bottom-1) ){
	        
			scroll();
            g_cursor_y = (g_cursor_bottom-1);
		    prev = c;
			
		}else{
		    
			g_cursor_y++;
            
			//Retornaremos mesmo assim ao início da linha 
			//se estivermos imprimindo no terminal.
			if ( stdio_terminalmode_flag == 1 ){
			    g_cursor_x = g_cursor_left;	
			} 
			
			//verbose mode do kernel.
			//permite que a tela do kernel funcione igual a um 
			//terminal, imprimindo os printfs um abaixo do outro.
			//sempre reiniciando x.
			if ( stdio_verbosemode_flag == 1 ){
			    g_cursor_x = g_cursor_left;	
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
		g_cursor_x += (4); 
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
                
    //Volta ao inicio da linha.
    //	
    if( c == '\r' )
	{
        g_cursor_x = g_cursor_left;  
        prev = c;
        return;    
    };  	
       
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
        
    //delete 
    if( c == 8 )  
    {
        g_cursor_x--;         
        prev = c;
        return;         
    };
	
	
	//
	// limits
	//
        
     
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
	//
	
//checkLimits:	

// caracteres normais.
//default:


    // Imprime os caracteres normais.
	//_outbyte (c);

    //Limites para o número de caracteres numa linha.
    if ( g_cursor_x >= (g_cursor_right-1) )
	{
        g_cursor_x = g_cursor_left;
        g_cursor_y++;  
		
    }else{   
	
	    //
		// ## Incremento ##
		//
		
		// Apenas incrementa a coluna. 
        g_cursor_x++;                          
    };
    
	
	//Número máximo de linhas. (8 pixels por linha.)
    if( g_cursor_y >= g_cursor_bottom )  
    { 
	    scroll();
        g_cursor_y = g_cursor_bottom;
    };
	
	
	//
	// Nesse momento imprimiremos os caracteres.
	//

    // Imprime os caracteres normais.
	_outbyte (c);
	
	// Atualisa o prev.	
	prev = c;	   
};


