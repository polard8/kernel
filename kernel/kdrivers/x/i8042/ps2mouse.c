/*
 * File: i8042/ps2mouse.c
 * 
 * env:
 *     Ring 0. Kernel base persistent code.
 * History:
 *     2018 - Created by fred Nora.
 */

 
#include <kernel.h>


extern unsigned long SavedX;            //Screen width. 
extern unsigned long SavedY;            //Screen height.


int MOUSE_BAT_TEST (void);

/*
 * mouse_write:
 *     Envia um byte para a porta 0x60.
 *     (Nelson Cole) */

void mouse_write (unsigned char write){
	
	kbdc_wait(1);
	outportb (0x64,0xD4);
	
	kbdc_wait(1);
	outportb (0x60,write);
}


/*
 **************************
 * mouse_read:
 *     Pega um byte na porta 0x60.
 *     (Nelson Cole) 
 */

unsigned char mouse_read (void)
{	
	kbdc_wait (0);
	
	return (unsigned char) inportb (0x60);
}


// Esta rotina faz o Auto-teste 0xaa êxito, 0xfc erro
int MOUSE_BAT_TEST (void){
    
    int val = -1;
	
	int i;

	// #todo:
	// Cuidado.
	// Diminuir isso se for possivel.
	// Nao funciona na maquina reala sem esse delay.
	
	for (i=0; i<99000; i++)
	{
		wait_ns(200);
	}		
	
	
    //while (1)
	for ( i=0; i<999; i++ )
	{
        val = mouse_read();

        if(val == 0xAA)
		{
			printf ("ps2mouse.c: MOUSE_BAT_TEST OK\n");
			return (int) 0;
        
		}else if(val == 0xFC){
			
			printf ("ps2mouse.c: MOUSE_BAT_TEST fail\n");
       		return (int) -1; 
       	}
    
        	// Reenviar o comando. 
        	// OBS: este comando não é colocado em buffer
        	mouse_write(0xFE);       
    };
	
	printf ("ps2kbd.c: MOUSE_BAT_TEST %d times\n",i);
}



/*
 **********************
 * mouse_install:
 *     ...
 */

void mouse_install (void){
	
	
	//printf ("mouse_install: 1\n");
	//refresh_screen();
	
	// 0xFF
	// Espera o dados descer (ACK)	
    // Basic Assurance Test (BAT)
	
	mouse_write (0xFF);
    while ( mouse_read() != 0xFA);	

	//printf ("mouse_install: 2\n");
	//refresh_screen();
	
    if ( MOUSE_BAT_TEST() != 0) 
	{
    	//printf("\n Mouse error!");
		printf ("[WARMING] ps2mouse.c:  MOUSE_BAT_TEST ignored\n");
    }

    // Use mouse default
	//Espera o dados descer (ACK)
	
	mouse_write (0xF6);
    while( mouse_read() != 0xFA);

	
	//printf ("mouse_install: 3\n");
	//refresh_screen();

	
    // habilita o mouse. (streaming)
	//Espera o dados descer (ACK)
	
	mouse_write (0xF4);
	while( mouse_read() != 0xFA);

    // Espera nossa controladora terminar.
	//printf ("mouse_install: 4\n");
	//refresh_screen();
    
	kbdc_wait (1);	
}


/*
 * getMouseData:
 *     Essa função é usada pela rotina kernelPS2MouseDriverReadData.
 * Input a value from the keyboard controller's data port, after checking
 * to make sure that there's some mouse data there for us.
 */

static unsigned char getMouseData (void){
	
    unsigned char data = 0;

    while ((data & 0x21) != 0x21)
        kernelProcessorInPort8(0x64, data);

    kernelProcessorInPort8(0x60, data);
	
	return (data);
}


/*
 * kernelPS2MouseDriverReadData:  
 *     Pega os bytes e salva em um array.
 *     Exibe um caractere na tela, dado as cordenadas.
 *     This gets called whenever there is a mouse interrupt
 *     @todo: Rever as entradas no array.         
 */

void kernelPS2MouseDriverReadData (void){
    //#suspensa !	
}


/*
 * load_mouse_bmp:  ## teste ##
 *     Carregando o arquivo MOUSE.BMP que é o ponteiro de mouse.
 *     Usar isso na inicialização do mouse.
 *     #bugbug isso pode ir para windowLoadGramadoIcons
 */

int load_mouse_bmp (void){
	
	int Status = 1;
	int Index;
 
	unsigned long fileret;
	
#ifdef KERNEL_VERBOSE
	printf("load_mouse_bmp:\n");
#endif	
	
	// #Importante
	// Fizemos um teste e funcionou com 500 páginas.
	// Foi suficiente para testarmos um pano de fundo.
	// Ret = (void*) allocPageFrames(500);  
	
    // Alocando duas páginas para um BMP pequeno. 8KB.	
	mouseBMPBuffer = (void *) allocPages(2);
	//mouseBMPBuffer = (void*) allocPages(10);
	//mouseBMPBuffer = (void*) allocPages(100);  //400KB
	
	if ( (void *) mouseBMPBuffer == NULL )
	{	
	    printf("unblocked-ldisc-load_mouse_bmp: mouseBMPBuffer\n");
		goto fail;		
	};
	
	
	//
	// ## Loading ...  ##
	//
	
	//read_fntos( (char *) arg1);
	
	
	//===================================
	// MOUSE
								
	fileret = (unsigned long) fsLoadFile ( VOLUME1_FAT_ADDRESS,
								VOLUME1_ROOTDIR_ADDRESS, 
	                            "MOUSE   BMP", 
	                            (unsigned long) mouseBMPBuffer );
								  
	if ( fileret != 0 )
	{
		printf("MOUSE.BMP FAIL\n");		
		// Escrevendo string na janela.
		//draw_text( gui->main, 10, 500, COLOR_WINDOWTEXT, "MOUSE.BMP FAIL");
		goto fail;	
	};
	
	// Render BMP file on backbuffer.
	//bmpDisplayBMP( mouseBMPBuffer, 20, 20 );
	//refresh_rectangle( 20, 20, 16, 16 );	
    //===================================							
	
	
//refresh_rectangle:

	//Isso funcionou ...
	//refresh_rectangle( 20, 20, 16, 16 );
	Status = (int) 0;
	goto done;
	
fail:
    printf("fail\n");
    Status = (int) 1;		
done:

#ifdef KERNEL_VERBOSE
    printf("done\n");
#endif	
	//refresh_screen();
    return (int) Status;	
};



// events.h
void set_current_mouse_responder ( int i ){
	
    current_mouse_responder = i;	
}


// events.h
int get_current_mouse_responder (void){
	
    return (int) current_mouse_responder;	
}


//==================================================================================
// Start - testing update_mouse
//==================================================================================

#define MOUSE_LEFT_BTN	  0x01
#define MOUSE_RIGHT_BTN	  0x02
#define MOUSE_MIDDLE_BTN  0x04
#define MOUSE_X_SIGN	  0x10
#define MOUSE_Y_SIGN	  0x20
#define MOUSE_X_OVERFLOW  0x40
#define MOUSE_Y_OVERFLOW  0x80

long mouse_x = 0;
long mouse_y = 0;

char mouse_packet_data = 0;
char mouse_packet_x = 0;
char mouse_packet_y = 0;
char mouse_packet_scroll = 0;

/*
 * ;;=====================================================
 * ;; _update_mouse:
 * ;;     Updates the mouse position.
 * ;;
 */

void update_mouse ( void ){
	
	
//======== X ==========	
//Testando o sinal de x.
//Do the x pos first.	
do_x:
    
	//pega o delta x
    //testa o sinal para x
	
	if( mouse_packet_data & MOUSE_X_SIGN ) 
	{
	    goto x_neg;
	}
		
//Caso x seja positivo.
x_pos:
	
	mouse_x += mouse_packet_x;
	goto do_y;
	
//Caso x seja negativo.	
x_neg:
    mouse_x -= ( ~mouse_packet_x + 1 );

	if (mouse_x > 0)
	{
	    goto do_y;
	}
    mouse_x = 0;
 
//======== Y ==========	
//Testando o sinal de x. 
//Do the same for y position.	
do_y:
    
	//Pega o delta y.
    //Testa o sinal para y.
	if ( mouse_packet_data & MOUSE_Y_SIGN )
	{
	    goto y_neg;
	}
	
//Caso y seja positivo.	
y_pos:
    mouse_y -= mouse_packet_y;
	
    if ( mouse_y > 0 )
	{
        goto quit;
	}
	mouse_y = 0;
	goto quit;
		

//Caso y seja negativo. 	
y_neg:
    mouse_y += ( ~mouse_packet_y + 1 );
	
quit:	
    return;
}


/*
 ********************************************************
 * mouseHandler:
 *     Handler de mouse. 
 *
 * *Importante: 
 *     Se estamos aqui é porque os dados disponíveis no 
 * controlador 8042 pertencem ao mouse.
 *
 * @todo: Essa rotina não pertence ao line discipline.
 * Obs: Temos externs no início desse arquivo.
 */
 
#define MOUSE_DATA_BIT 1
#define MOUSE_SIG_BIT  2
#define MOUSE_F_BIT  0x20
#define MOUSE_V_BIT  0x08 

//contador
static int count_mouse = 0;

// Buffer.
static char buffer_mouse[3];


int flagRefreshMouseOver;


void mouseHandler (void)
{	
    // #importante:
	// Essa será a thread que receberá a mensagem
	
	struct thread_d *t;
	
	
	// #importante:
	// Essa será a janela afetada por qualquer evento de mouse.
	// ID de janela.
	
    struct window_d *Window;
	int wID; 	
	
	
	// Coordenadas do mouse.
    // Obs: Isso pode ser global.
    // O tratador em assembly tem as variáveis globais do posicionamento.
    
	int posX=0;
    int posY=0;	

    //Char para o cursor provisório.
	//#todo: Isso foi subtituido por uma bmp. Podemos deletar.
    //static char mouse_char[] = "T";

	char *_byte;


	// Lendo um char no controlador.
	
	*_byte = (char) mouse_read();
	
	
	// #importante:
	// Contagem de interruções:
	// Obs: Precisamos esperar 3 interrupções.
	
	//#bugbug essa variável está inicializando toda vez que 
	//se chama o handler porque ela é interna. ??
	
	switch ( count_mouse )
	{
		// Essa foi a primeira interrupção.
		case 0:
		    //Pegamos o primeiro char.
		    buffer_mouse[0] = (char) *_byte;
            if(*_byte & MOUSE_V_BIT)
                count_mouse++;
		    break;
			
		// Essa foi a segunda interrupção.	
		case 1:
		    //Pegamos o segundo char.
		    buffer_mouse[1] = (char) *_byte;
			count_mouse++;
		    break;
			
		//#importante.
		// Essa foi a terceira interrupção.	
		case 2:
		    //Pegamos o terceiro char.
            buffer_mouse[2] = (char) *_byte;
			count_mouse = 0;
			
			//#importante:
			//A partir de agora já temos os três chars.
			
			//??
			//Colocando os três chars em variáveis globais.
            //Isso ficará assim caso não haja overflow ...
			
			mouse_packet_data = buffer_mouse[0];
	 	    mouse_packet_x = buffer_mouse[1];       
		    mouse_packet_y = buffer_mouse[2];
            
			// #importante:
			// #todo: Isso está em Assembly, lá em hwlib.inc, 
			// mas queremos que seja feito em C.
			// #obs: Uma rotina interna aqui nesse arquivo está tentando isso.
			
			//#importante.
		    //salvando antes de atualizar.
			//paga poder apagar daqui a pouco.
			saved_mouse_x = mouse_x;
		    saved_mouse_y = mouse_y;			
			
			update_mouse();			
			
		    // #importante:
			// Agora vamos manipular os valores obtidos através da 
			// função de atualização dos valores.
			
			//mouse_x = (mouse_x & 0x00000FFF ); 
		    //mouse_y = (mouse_y & 0x00000FFF );
			
			mouse_x = (mouse_x & 0x000003FF ); 
		    mouse_y = (mouse_y & 0x000003FF );		
		    
			// Checando limites.
            // #todo: Os valores foram determinados. 
			// Precisamos usar variáveis.
			
			if ( mouse_x < 1 ){ mouse_x = 1; }	
		    if ( mouse_y < 1 ){ mouse_y = 1; }
			
		    if(	mouse_x > (SavedX-16) )
			{ 
				mouse_x = (SavedX-16); 
		    }
		    
			if(	mouse_y > (SavedY-16) )
			{ 
				mouse_y = (SavedY-16); 
			}
			
			//
			// # Draw BMP #
		    //
			
            //nova técnica.
			// Isso está funcionando bem.			
            //+ copia no LFB um retângulo do backbuffer para apagar o ponteiro antigo.
            //+ decodifica o mouse diretamente no LFB.				
			//copiar para o lfb o antigo retângulo. 
			//Para apagar o ponteiro que está no lfb.
			
			refresh_rectangle ( saved_mouse_x, saved_mouse_y, 20, 20 );	      //apaga o antigo
			bmpDisplayMousePointerBMP ( mouseBMPBuffer, mouse_x, mouse_y );   //acende o novo.
          
            //#debug		  
		    //draw_text ( gui->main, mouse_x, mouse_y, COLOR_YELLOW, "+" );
		    //refresh_rectangle ( mouse_x, mouse_y, 8, 8 );		
			
			
			//#bugbug:
			//testando .... naõ vamos exibir o ponteiro ..
			//se não falhar é porque o problema está na exibição do ponteiro.
			//teste feito, falhou mesmo sem exibir o ponteiro, então o problema 
			//naõ está na exibição do ponteiro.
			
            break;

        default:
		    count_mouse = 0;
            break;		
	};
	
	
	// #importante 
	// Por outro lado o mouse deve confrontar seu posicionamento com 
	// todas as janelas, para saber se as coordenadas atuais estão passando 
	// por alguma das janelas. Se estiver, então enviaremos mensagens para essa 
	// janela que o mouse passou por cima. Ela deve ser sinalizada como hover,
	// 
	// #importante:
	// Se houver um click, o elemento com mousehover será afetado, e 
	// enviaremos mesagens para ele, se apertarem enter ou application key, 
	// quem recebe a mensagem é o first responder, ou seja, a janela com o 
	// foco de entrada.
    // Se clicarmos com o botão da direita, quem recebe a mensagem é 
    // a janela que o mouse está passando por cima.	
	
	
	//
	//  ## Button ##
	//
	
	// ===
	//Apenas obtendo o estado dos botões.
	
	mouse_buttom_1 = 0;
	mouse_buttom_2 = 0;
	mouse_buttom_3 = 0;
	
	
	// ## LEFT ##
	if( ( mouse_packet_data & MOUSE_LEFT_BUTTON ) == 0 )
	{
		//liberada.
		mouse_buttom_1 = 0;
	}else if( ( mouse_packet_data & MOUSE_LEFT_BUTTON ) != 0 )
	    {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
	        mouse_buttom_1 = 1;
	        mouse_buttom_2 = 0;
	        mouse_buttom_3 = 0;		  
	    }
			  
    
	// ## RIGHT ##
	if( ( mouse_packet_data & MOUSE_RIGHT_BUTTON ) == 0 )
	{
	    //liberada.
	    mouse_buttom_2 = 0;
	}else if( ( mouse_packet_data & MOUSE_RIGHT_BUTTON ) != 0 )
	    {
		    //pressionada.
		    //Não tem como pressionar mais de um botão por vez.
	        mouse_buttom_1 = 0;
	        mouse_buttom_2 = 1;
	        mouse_buttom_3 = 0;		  			 
	    }
			  
	
	// ## MIDDLE ##
	if( ( mouse_packet_data & MOUSE_MIDDLE_BUTTON ) == 0 )
	{
	    //liberada.
	    mouse_buttom_3 = 0;
	}else if( ( mouse_packet_data & MOUSE_MIDDLE_BUTTON ) != 0 )
	    {
	        //pressionada.
		    //Não tem como pressionar mais de um botão por vez.			 
	        mouse_buttom_1 = 0;
	        mouse_buttom_2 = 0;
	        mouse_buttom_3 = 1;		  			
	    }			
	
	
    // ===	
	// Confrontando o estado atual com o estado anterior para saber se ouve 
	// alguma alteração ou não.
	// 1 = ouve alteração.
	
	if( mouse_buttom_1 != old_mouse_buttom_1 ||
	    mouse_buttom_2 != old_mouse_buttom_2 ||
		mouse_buttom_3 != old_mouse_buttom_3 )
	{
		mouse_button_action = 1;
	}else{
		mouse_button_action = 0;
	};
	
	// #refletindo: 
	// ?? E no caso de apenas considerarmos que o mouse está se movendo, 
	// mandaremos para janela over. ???
	
	// #refletindo:
	// Obs: A mensagem over pode ser enviada apenas uma vez. 
	// será usada para 'capturar' o mouse ... 
	// e depois tem a mensagem para 'descapturar'.
	
	


    //##### sem escaneamento de janelas por enquanto, apenas mostre e mova o ponteiro #####
	
	//## então não enviaremos mensagens para a thread ###
	
	//
	//  ## Scan ##
	//
	
	//===========
	// (capture) - On mouse over. 
	//


	
	// wID = ID da janela.
	// Escaneamos para achar qual janela bate com os valores indicados.
	// Ou seja. Sobre qual janela o mouse está passando.
	
	// #BUGBUG
	// O problema nessa técnica são as sobreposição de janelas.
	// Quando uma janela está dentro da outr, então duas janelas
	// estão áptas a serem selecionadas.
	// Talvez devamos filtrar e só aceitarmos sondar procurando 
	// por controles.

	// #IMPORTANTE
	// Se for válido e diferente da atual, significa que 
	// estamos dentro de uma janela.
	// -1 significa que ouve algum problema no escaneamento.
	
	wID = (int) windowScan ( mouse_x, mouse_y );	
		
	//se houve problema no escaneamento de janela
	if ( wID == -1 )
	{ 
        
		//essa flag indica que podemos fazer o refresh da mouse ouver,
		//mas somente uma vez.
		if ( flagRefreshMouseOver == 1 )
		{
		    Window = (struct window_d *) windowList[mouseover_window];	
		    
			//#bugbug:
			//precisamos checar a validade da estrutura antes de usa-la.
			
			//#importante:
			//isso apaga o que pintamos na janela, o valor foi salvo logo abaixo.
			
			if ( (void *) Window != NULL ){
				
				refresh_rectangle ( Window->left, Window->top, 20, 20 );
			    //refresh_rectangle ( savedmouseoverwindowX, savedmouseoverwindowY, 20, 20 );
				
			}
			
			//não podemos mais fazer refresh.
			flagRefreshMouseOver = 0;
			
			//#importante
			//inicializa.
			mouseover_window = 0;
		}
			
	// Se não houve problema no escaneamento de janela ou seja, se encontramos 
	// uma janela. Então essa janela deve estar associada à uma thread para qual 
	// mandaremos a mensagem. Caso a thread for null ... apenas não enviamos.
	// A janela tem uma thread de controle, igual ao processo.
		
    }else{
		
		Window = (struct window_d *) windowList[wID];
		
		if ( (void *) Window == NULL )
		{
			//fail
			return;
		}
		
		if ( Window->used != 1 || Window->magic != 1234)
		{
			//fail
			return;
		}
			
		//#importante:
		//Nesse momento temos uma janela válida, então devemos 
		//pegar a thread associada à essa janela, dessa forma 
		//enviaremos a mensagem para a thread do aplicativo ao qual 
		//a janela pertence.
		
		t = (void *) Window->control;

		//se a estrutura da thread for inválida.
		if ( (void *) t == NULL )
		{
			//fail
			return;
		}
		
		//se a estrutura estiver corrompida.
		if ( t->used != 1 || t->magic != 1234 )
		{
			//fail
			return;
		}		
		
		//#bugbug 
		//#todo:
		// Deveriamos aqui checarmos a validade da estrutura ??
		
		//redraw_window(wScan);
        
        // #importante
		// Se um botão foi pressionado ou liberado, então enviaremos uma 
		// mensagem relativa ao estado do botão, caso contrário, enviaremos 
		// uma mensagem sobre a movimentação do mouse.
		
		//#importante
		// Se houve mudança em relação ao estado anterior.
		if ( mouse_button_action == 1 )
		{
			//Qual botão mudou seu estado??
			//Checaremos um por um.
			
			//1
			//Igual ao estado anterior
			if( mouse_buttom_1 == old_mouse_buttom_1 )
			{
				//...
			
			//Diferente do estado anterior.
			}else{
				
				//down
				if ( mouse_buttom_1 == 1 )
				{                
					
					//clicou
					if ( old_mouse_buttom_1 == 0 ){
						
						//#importante 
						//enviaremos a mensagem para a thread atual.
						
						if ( (void *) Window != NULL ){
						
                            t->window = Window;
						    t->msg = MSG_MOUSEKEYDOWN;
							t->long1 = 1;
							t->long2 = 0;
							
							t->newmessageFlag = 1;
						}
										    
					    //atualiza o estado anterior.
					    old_mouse_buttom_1 = 1;
					}
					
				}else{
					
					//up
					
					//#importante 
					//enviaremos a mensagem para a thread atual.
						
					if ( (void *) Window != NULL ){
						
                        t->window = Window;
					    t->msg = MSG_MOUSEKEYUP;
						t->long1 = 1;
						t->long2 = 0;
							
						t->newmessageFlag = 1;
					}						
						
					old_mouse_buttom_1 = 0;	
				}
			}; 
			
			
			//2
			//Igual ao estado anterior
			if ( mouse_buttom_2 == old_mouse_buttom_2 )
			{
				//...
				
			//Diferente do estado anterior.	
			}else{
				
				//down
				if ( mouse_buttom_2 == 1 )
				{
					
					//clicou
					if( old_mouse_buttom_2 == 0 ){
						
						
						if ( (void *) Window != NULL ){
						
                            t->window = Window;
						    t->msg = MSG_MOUSEKEYDOWN;
							t->long1 = 2;
							t->long2 = 0;
							
							t->newmessageFlag = 1;
						}						
				    
					    //atualiza o estado anterior.
					    old_mouse_buttom_2 = 1;
					}

                }else{
					
					//up
					if ( (void *) Window != NULL ){
						
                        t->window = Window;
					    t->msg = MSG_MOUSEKEYUP;
						t->long1 = 2;
						t->long2 = 0;
							
						t->newmessageFlag = 1;
					}	
						
					old_mouse_buttom_2 = 0;
				}
			}; 
			
			
			//3
			//Igual ao estado anterior
			if ( mouse_buttom_3 == old_mouse_buttom_3 )
			{
				//...
				
				
			//Diferente do estado anterior.	
			}else{
				
				//down
				if ( mouse_buttom_3 == 1 )
				{
					//clicou
					if ( old_mouse_buttom_3 == 0 ){
                        
						
						if ( (void *) Window != NULL ){
						
                            t->window = Window;
						    t->msg = MSG_MOUSEKEYDOWN;
							t->long1 = 3;
							t->long2 = 0;
							
							t->newmessageFlag = 1;
						}	 						
				    
					    //atualiza o estado anterior.
					    old_mouse_buttom_3 = 1;
					}

                }else{
					
					//up
					if ( (void *) Window != NULL ){
						
                        t->window = Window;
					    t->msg = MSG_MOUSEKEYUP;
						t->long1 = 3;
						t->long2 = 0;
							
						t->newmessageFlag = 1;
					}	
						
					old_mouse_buttom_3 = 0;
				}
			}; 
			
			//Ação concluída.
			mouse_button_action = 0;
			
			
		    // Se NÃO ouve alteração no estado dos botões, então apenas 
		    // enviaremos a mensagem de movimento do mouse e sinalizamos 
		    // qual é a janela que o mouse está em cima.
		}else{
			
			// #importante
			// Lembrando que estamos dentro de uma janela ...
			// por isso a mensagem é over e não move.
			
            //Obs: Se a janela for a mesma que capturou o mouse,
			//então não precisamos reenviar a mensagem.
			//Mas se o mouse estiver em cima de uma janela diferente da 
			//que ele estava anteriormente, então precisamos enviar uma 
			//mensagem pra essa nova janela.
			
			//#bugbug:
			//estamos acessando a estrutura, mas precisamos antes saber se ela é válida.
			
			if ( (void *) Window != NULL )
			{
			
                //;;;
			    if ( Window->id != mouseover_window )
			    {
				
                    if ( mouseover_window != 0 )
				    {
					
					    //if ( (void *) Window != NULL ){
						
                        t->window = (struct window_d *) windowList[mouseover_window];
					    t->msg = MSG_MOUSEEXITED;
						t->long1 = 0;
						t->long2 = 0;
						
						t->newmessageFlag = 1;
					    //}	
				    };
				
				
				    //Agora enviamos uma mensagem pra a nova janela que o mouse 
				    //está passando por cima.
						
                    t->window = Window;
					t->msg = MSG_MOUSEOVER;
					t->long1 = 0;
					t->long2 = 0;
						
					t->newmessageFlag = 1;
				
			
			        //ja que entramos em uma nova janela, vamos mostra isso.
				    
					
				    //botão.
					//#provisório ...
					//Isso é um sinalizador quando mouse passa por cima.
					//#test: Vamos tentar modificar as características do botão.
					
			        if ( Window->isButton == 1 )
				    {    
						//isso funciona.
			            //bmpDisplayCursorBMP ( fileIconBuffer, Window->left, Window->top );	
			        
					    //#test
                        update_button ( (struct button_d *) Window->button,
                            (unsigned char *) Window->button->string,
                            (int) Window->button->style,
                            (int) BS_HOVER,
                            (int) Window->button->type,
                            (unsigned long) Window->button->x, 
                            (unsigned long) Window->button->y, 
                            (unsigned long) Window->button->width, 
                            (unsigned long) Window->button->height, 
                            (unsigned long) Window->button->color );
						
						redraw_button ( (struct button_d *) Window->button );
						show_window_rect (Window);
					};
				
				    //não botão.
				    //if ( Window->isButton == 0 )
				    //{
				    //    bmpDisplayCursorBMP ( folderIconBuffer, Window->left, Window->top );		
				    //};
				
				    //nova mouse over
				    mouseover_window = Window->id;
				
				    //#importante:
				    //flag que ativa o refresh do mouseover somente uma vez.
				    flagRefreshMouseOver = 1;
			
			    }else{ 
			    
				    //nothing ...
				    //não precisamos reenviar a mensagem, pois o mouse 
				    //continua na mesma janela que antes.
                
				    //windowSendMessage ( (unsigned long) wScan, 
		            //    (unsigned long) MSG_MOUSEOVER, 
			        //    (unsigned long) 0, 
			        //    (unsigned long) 0 );				
				
			    };			
			    
				//;;;
			};
			
			//Ação concluída.
			//Para o caso de um valor incostante na flag.
			mouse_button_action = 0;			
		};
		
		
		//if ( wScan->isButton == 1 )
		//{
			//colocamos ao passarmos por cima do botão,
			//#obs: tem que dar refresh do retângulo no backbuffer quando sair
			//substituir essa imagem.
		//    bmpDisplayCursorBMP ( cursorIconBuffer, wScan->left, wScan->top);	
		//}
		
        //if ( wScan->isButton == 0 )
        //{
		    // #debug. (+)
		    // Isso coloca o (+) no frontbuffer.
		//    draw_text ( wScan, 0, 0, COLOR_YELLOW, "+" );
		//    refresh_rectangle ( wScan->left, wScan->top, 8, 8 );
		//}			
		
	};
};



/* 
 * *******************************************************************
 * ps2_mouse_initialize :
 *     Configurando o controlador PS/2, 
 *     e activar a segunda porta PS/2 (mouse).
 *     (Nelson Cole)(Fred Nora)
 *     É uma rotina de inicialização do controlador i8042 para 
 *     habilitar o segundo dispositivo, o mouse.
 *     Essa rotina deve rodar somente uma vez, durante inicialização.
 */
 
void ps2_mouse_initialize (void){
	
	int error_code = 0;
	
	unsigned char status;
	
    // Flush the output buffer
	//while ((inportb(0x64) & 1)) {
	//	inportb(0x60);
	//}
	
	
	//printf("ps2_mouse_initialize: enable second port\n");
	//refresh_screen();
	
	
	// Ativar a segunda porta PS/2.
	//kbdc_wait(1);
	//outportb(0x64,I8042_WRITE);    
	//kbdc_wait(1);
	//outportb(0x64,I8042_ENABLE_SECOND_PORT); //0xA8


	
	//printf("ps2_mouse_initialize: enable second device\n");
	//refresh_screen();
	
	
	// Activar o segundo despositivo PS/2, modificando o status de 
	// configuração do controlador PS/2. 
	// Lembrando que o bit 1 é o responsável por habilitar, desabilitar o 
	// segundo despositivo PS/2  ( o rato). 
	// Só para constar se vedes aqui fizemos duas coisas lemos ao mesmo tempo 
	// modificamos o byte de configuração do controlador PS/2 
	
	// Defina a leitura do byte actual de configuração do controlador PS/2.
	//0x20 Read "byte 0" from internal RAM
	
	kbdc_wait(1);    
	outportb(0x64,I8042_READ);    
	kbdc_wait(0);
	status = inportb(0x60)|2;  
	//status = inportb(0x60)| 3;  
	
	// defina, a escrita  de byte de configuração do controlador PS/2.
	kbdc_wait(1);
	outportb(0x64,I8042_WRITE);  
	// devolvemos o byte de configuração modificado.
	kbdc_wait(1);
	outportb(0x60,status);  	
	

    //Agora temos dois dispositivos sereais teclado e mouse (PS/2).

    //Activar a primeira porta PS/2
	kbdc_wait(1);
	outportb(0x64,0xAE);  

    // activar a segunda porta PS/2
	kbdc_wait(1);
	outportb(0x64,0xA8);

    // espera   
	kbdc_wait(1);	
	

	//## step 2 ##
	//checar se o mouse é de rolar ou não.
	
	
	//## step 3 ##
	//detectar a quantidade de botões.
	
	//## step 4 ##
	//configurar o sampling rate.
	//ativa o modo escrita,
	//envia o comando seguido de parâmetros.
	//0xF3 ...
	
	//## step 5 ##
	//configura a resolução do mouse
	//0xE8 ...
	
	
	//## step 6 ##	
	

 	//printf("ps2_mouse_initialize: restores defaults\n");
	//refresh_screen();

    //Restaura defaults do PS/2 mouse.
	//kbdc_wait(1);
	//outportb(0x64,I8042_WRITE);    
    //kbdc_wait(1);
    //mouse_write(MOUSE_SET_DEFAULTS);  //0xf6
    //while ( mouse_read() != I8042_ACKNOWLEDGE );

	
 	//printf("ps2_mouse_initialize: enable transmission\n");
	//refresh_screen();	

   // TODO: Pode ser interessante diminuir a sensibilidade do mouse
   // aqui!!!
  //( 0xF4 = Habilita o mouse streaming, Enable Data Reporting,ENABLE MOUSE TRANSMISSION )
  // Habilita o mouse streaming
  // Interessante notar que, no modo streaming,
  // 1 byte recebido do PS/2 mouse gerar  uma IRQ...
  // Talvez valha a pena DESABILITAR o modo streaming
  // para colher os 3 dados de uma s¢ vez na IRQ!
	//kbdc_wait(1);
	//outportb(0x64,I8042_WRITE);      
    //kbdc_wait(1);
    //mouse_write(MOUSE_ENABLE_DATA_REPORTING);  //0xf4
    //while ( mouse_read() != I8042_ACKNOWLEDGE );        
	
	
	
	//uint8_t tmp = inportb(0x61);
	//outportb(0x61, tmp | 0x80);
	//outportb(0x61, tmp & 0x7F);
	//inportb(0x60);	//mouse port
	
	 // Flush the output buffer
    //while ((inportb(0x64) & 1)) {
	//	inportb(0x60);
	//}	
  
  
init_mouse_exit:
    
	// Se ouve um erro, então analisamos e exibimos mensagem sobre ele.
	if (error_code != 0)
    {
	    //
        		
	}		
	
 	//printf("ps2_mouse_initialize: done\n");
	//refresh_screen();		
	
    //#imporante:
	//não habilitaremos e não resetaremos o dispositivo.
    //habilitar e resetar fica para a inicialização do ps2.
};


/*
 ***********************************************
 * init_mouse:
 *     Inicializando o mouse no controlador 8042.
 *     Carregando o bmp para o curso do mouse.
 */		

int ps2_mouse_globals_initialize (void){
	
    unsigned char response = 0;
    unsigned char deviceId = 0;
    int i; 
	int bruto = 1;  //Método.
	int mouse_ret;
	
	
	//printf("ps2_mouse_globals_initialize: inicializando estrutura\n");
	//refresh_screen();		
	
	
	//user.h
	ioControl_mouse = (struct ioControl_d *) malloc( sizeof(struct ioControl_d) );
	
	if ( (void *) ioControl_mouse == NULL )
	{
		printf("ldsic-init_mouse: ioControl_mouse fail");
		die();
	}else{
	    
	    ioControl_mouse->id = 0;
	    ioControl_mouse->used = 1;
	    ioControl_mouse->magic = 1234;
	    
		//Qual thread está usando o dispositivo.
		ioControl_mouse->tid = 0;  
	    //ioControl_mouse->
	};	
	
	
	//printf("ps2_mouse_globals_initialize: inicializando variaveis\n");
	//refresh_screen();		
	
	//
	// Estamos espaço para o buffer de mensagens de mouse.
	// mousemsg = ( unsigned char *) malloc(32);

		
	//Inicializando as variáveis usadas na rotina em Assemly
    //em hardwarelib.inc
    
	//Coordenadas do cursor.
	g_mousepointer_x = (unsigned long) 0;
    g_mousepointer_y = (unsigned long) 0;	
    mouse_x = 0;
    mouse_y = 0;
	
	//mouse_x = 0;
	//mouse_y = 0;
	
	//#bugbug: Essa inicialização está travando o mouse.
	//fazer com cuidado.
	
	//#bugbug. Cuidado com essa inicializaçao.
	g_mousepointer_width = 16;
	g_mousepointer_height = 16;
	

    //Bytes do controlador.
    //mouse_packet_data = 0;
    //mouse_packet_x = 0;
    //mouse_packet_y = 0;
    //mouse_packet_scroll = 0;
	
	//
	// ## BMP ##
	//
	
	//printf("ps2_mouse_globals_initialize: carregando bmp\n");
	//refresh_screen();		
	
	// Carregando o bmp do disco para a memória
	// e apresentando pela primeira vez.
 
    
	mouse_ret = (int) load_mouse_bmp ();	
	
	if (mouse_ret != 0)
	{
		printf("ldisc-init_mouse: load_mouse_bmp");
		die();
	}
	
	//printf("ps2_mouse_globals_initialize: done\n");
	//refresh_screen();	

    //initialized = 1;
    //return (kernelDriverRegister(mouseDriver, &defaultMouseDriver));	
	return (int) 0;
};


//
// End.
//

