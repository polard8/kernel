/*
 * File: keyboard.c  
 *
 *  Descrição:
 *     Driver básico de teclado para o Boot Loader.
 *
 * Obs:
 * O padrão de teclado usado precisa ser revisto.
 * Pelo jeito estamos usando o padrão americano. Mas 
 * é possível adaptar para ABNT2 se muitos problemas.
 * Podemos copiar do driver do núcleo.
 *
 * Histórico:
 *     2015 - Adaptado de versões antigas por Fred Nora.
 *     2016 - Revisão.
 */

 
#include <bootloader.h>


//
// Variáveis internas.
//

//Status.
unsigned long key_status;     //*Importante.

//Key status.
unsigned long escape_status;
unsigned long tab_status;  
unsigned long winkey_status;
unsigned long ctrl_status;
unsigned long alt_status;
unsigned long shift_status;

//Outros.
unsigned long ambiente = 0;
unsigned long prompt_pos;
unsigned long destroy_window = 1; 
unsigned long quit_message = 1;


/* 
 * KBDUS:
 *     Means US Keyboard Layout. 
 *
 * This is a scancode table used to layout a standard US keyboard. 
 * I have left some comments in to give you an idea of what key is what, 
 * even though I set it's array index to 0. 
 * You can change that to whatever you want using a macro, if you wish! 
 */

 
// #todo:
// Esse arquivo foi melhor trabalhado no Kernel. Podemos aproveitar 
// coisas de lá.
 
 
/* 
 * No shift (MAP) 
 */
 
static unsigned char map[128] = {

/* scan  0- 7 */
0   ,    //scancode 0 - (). 
033 ,    //scancode 1 - (). 
'1' ,    //scancode 2 - (1).
'2' ,    //scancode 3 - (2).
'3' ,    //scancode 4 - (3).
'4' ,    //scancode 5 - (4).
'5' ,    //scancode 6 - (5).
'6' ,    //scancode 7 - (6).

/* scan  8-15 */
'7' , 
'8' , 
'9' , 
'0' , 
'-' , 
'=' , 
VK_BACK, 
VK_TAB,

/* scan 16-23 */		
'q' , 
'w' , 
'e' , 
'r' , 
't' , 
'y' , 
'u' , 
'i' ,

/* scan 24-31 */		
'o' , 
'p' , 
'´' , 
'[' , 
KEY_RETURN, 
KEY_CTRL, 
'a' , 
's' ,

/* scan 32-39 */		
'd' , 
'f' , 
'g' , 
'h' , 
'j' , 
'k' , 
'l' , 
'ç' ,	

/* scan 40-47 */  	
'~' , 
']' , 
KEY_SHIFT, 
']' , 
'z' , 
'x' , 
'c' , 
'v' ,

/* scan 48-55 */	  	
'b' , 
'n' , 
'm' , 
',' , 
'.' , 
';' , 
115 , 
KEY_SHIFT,

/* scan 56-63 */		
VK_MENU, 
KEY_SPACE,  
KEY_SHIFT,  
VK_F1,  
VK_F2, 
VK_F3,  
VK_F4, 
VK_F5,		
 
/* scan 64-71 */
VK_F6,     
VK_F7,     
VK_F8,     
VK_F9,     
VK_F10, 
NUM|L, 
STP|L,   
VK_HOME,
     
/* scan 72-79 */    		
VK_UP,   
'9' ,   
'+' ,   
VK_LEFT,   
'5' ,   
VK_RIGHT,   
'.' ,  
'1' ,		

/* scan 80-87 */
VK_DOWN,   
'3' ,   
VK_INSERT,   
VK_DELETE,     
 0 ,     
 0 ,    
 0 ,     
VK_F10,		
 
// Outros ...  
VK_F11, VK_F2, VK_F3, VK_LWIN, VK_RWIN, 
VK_F6, VK_F7, VK_F8,
VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, 
VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,0,0,0,0,0,0,
VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, 
VK_F6, VK_F7, VK_F8, VK_F9, VK_F10,0,0,0,0,0,0, 
};
 

/* 
 * Shift (MAP).
 */
static unsigned char shift[128] = {	
0,     033  , '!'  , '@'  , '#'  , '$'  , '%'  , '^'  ,		/* scan  0- 7 */
'&'  , '*'  , '('  , ')'  , '_'  , '+'  , 0177 ,'\t'  ,		/* scan  8-15 */
'Q'  , 'W'  , 'E'  , 'R'  , 'T'  , 'Y'  , 'U'  , 'I'  ,		/* scan 16-23 */
'O'  , 'P'  , '['  , ']'  , KEY_RETURN , CTL  , 'A'  , 'S'  ,		/* scan 24-31 */
'D'  , 'F'  , 'G'  , 'H'  , 'J'  , 'K'  , 'L'  , ':'  ,		/* scan 32-39 */
'"'  , '~'  , SHF  , '|'  , 'Z'  , 'X'  , 'C'  , 'V'  ,		/* scan 40-47 */
'B'  , 'N'  , 'M'  , '<'  , '>'  , '?'  , SHF  ,   '*',		/* scan 48-55 */
ALT  , ' '  , CPS|L,     0,     0, ' '  ,     0,     0,		/* scan 56-63 */
    0,     0,     0,     0,     0, NUM|L, STP|L,   '7',		/* scan 64-71 */
  '8',   '9',   '-',   '4',   '5',   '6',   '+',   '1',		/* scan 72-79 */
  '2',   '3',   '0',   '.',     0,     0,     0,     0,		/* scan 80-87 */
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
};


/* 
 * CTL, Control (MAP). 
 */
static unsigned char ctl[128] = {	
0,     033  , '!'  , 000  , '#'  , '$'  , '%'  , 036  ,		/* scan  0- 7 */
'&'  , '*'  , '('  , ')'  , 037  , '+'  , 034  ,'\177',		/* scan  8-15 */
021  , 027  , 005  , 022  , 024  , 031  , 025  , 011  ,		/* scan 16-23 */
017  , 020  , 033  , 035  , '\r' , CTL  , 001  , 013  ,		/* scan 24-31 */
004  , 006  , 007  , 010  , 012  , 013  , 014  , ';'  ,		/* scan 32-39 */
'\'' , '`'  , SHF  , 034  , 032  , 030  , 003  , 026  ,		/* scan 40-47 */
002  , 016  , 015  , '<'  , '>'  , '?'  , SHF  ,   '*',		/* scan 48-55 */
ALT  , ' '  , CPS|L,     0,     0, ' '  ,     0,     0,		/* scan 56-63 */
CPS|L,     0,     0,     0,     0,     0,     0,     0,		/* scan 64-71 */
    0,     0,     0,     0,     0,     0,     0,     0,		/* scan 72-79 */
    0,     0,     0,     0,     0,     0,     0,     0,		/* scan 80-87 */
    0,     0,   033, '7'  , '4'  , '1'  ,     0, NUM|L,		/* scan 88-95 */
'8'  , '5'  , '2'  ,     0, STP|L, '9'  , '6'  , '3'  ,		/*scan  96-103*/
'.'  ,     0, '*'  , '-'  , '+'  ,     0,     0,     0,		/*scan 104-111*/
0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
};



/*
 *************************************************
 * keyboardHandler:
 * 
 *     Keyboard interrupt handler. 
 */

void keyboardHandler(void){


    // Step 0: 
    // Declarações.


    // Variáveis para armazenar valores que pegaremos.

    unsigned char raw_byte=0;
    unsigned char scancode=0;

    unsigned long status=0;

	//@todo: ?? Por que esses valores ??
	
    //Suporte ao envio de mensagens. 

    unsigned char *msg = (unsigned char *) 0x00090500; 
    unsigned long mensagem=0; 

	//Suporte ao envio de char.

    unsigned char *wParam  = ( unsigned char *) 0x00090120; 
    unsigned long ch=0;


	// @todo: 
	// Uma biblioteca de video satisfatória deve existir no Boot Loader.


    // Text mode screen buffer.

    unsigned char *screen = (unsigned char *) 0x000B8000; 


    // Step1: 
    
    // Get the raw byte.
    // This is not the scancode.
    

    raw_byte = in8(0x60);

    // #todo
    // Temos que considerar o teclado extendido.

    // Elimina o último bit.
    scancode = (raw_byte & 0x7F);


    //
    // Step 2: 
    // Trata a mensagem.
    //    
    
    // Vamos checar o bit no raw byte que
    // diz se a tecla foi liberada ou não.
    
    // Se a tecla foi liberada.
    if (raw_byte & 0x80)
    {
        //Analiza a tecla.
        status = map[scancode]; 

        //Se for teclas especiais, que são importantes para o sistema.         
        if ( status == KEY_ALT || 
             status == KEY_WINKEY || 
             status == KEY_CTRL || 
             status == KEY_SHIFT )
        {     
              //Prepara.
              mensagem = MSG_SYSKEYUP;
              
              //Envia.
              key_status = mensagem;
              msg[0] = mensagem;  
        }else{  //Se for tecla comum.

            // Prepara.
            mensagem = MSG_KEYUP;

            //Envia.
            key_status = mensagem;
            msg[0] = mensagem;
        };

    
        // Analiza.
        // Se for do sistema usa o mapa de caracteres apropriado. 
        if (key_status == MSG_SYSKEYUP)
        {
            ch = shift[scancode];  //Pega.
            wParam[0] = ch;        //Envia.
        }


		// Analiza.
		// Se for tecla normal, pega o mapa de caracteres apropriado.
        if (key_status == MSG_KEYUP)
        {
            ch = map[scancode];  //Pega.
            wParam[0] = ch;      //Envia.
        }

        //Nothing.

    // Se a tecla foi pressionada ---------------------
    }else{  


        // Pegando status.   
        status = map[scancode]; 
 
        if ( status == KEY_ALT || 
             status == KEY_WINKEY || 
             status == KEY_CTRL || 
             status == KEY_SHIFT )
        {
            //Pega.
            mensagem = MSG_SYSKEYDOWN;
            //Envia. 
            key_status = mensagem;   
            msg[0] = mensagem;  
        
        }else{ 
            
            // Pega.
            mensagem = MSG_KEYDOWN;
            // Envia.
            key_status = mensagem; 
            msg[0] = mensagem;
       };


        // Analiza.
        if (key_status == MSG_SYSKEYDOWN)
        {
            ch = shift[scancode];
            wParam[0] = ch;         //Envia.
        }


        // Analisa.
        if (key_status == MSG_KEYDOWN)
        {
            ch = map[scancode];
            wParam[0] = ch;    //Envia. 
        };

		//Nothing.
    };



	// Step 3: 
	// Debug support.


	// #debug: 
	// Envia um caractere pra tela.

    // Haha!
    screen[76] = (char) ch;
    screen[77] = (char) 9; 



	// Step 4: 
	// Send message to Boot Loader procedure.

    //
    // procedure
    //

    bl_procedure ( 
        0, 
        (int) mensagem, 
        (unsigned long) ch, 
        (unsigned long) status );

   
    // put into the queue.

    keyboard_queue[keyboard_queue_tail] = ch;
    
    keyboard_queue_tail++;
    if( keyboard_queue_tail > 8 ){
        keyboard_queue_tail = 0;
    }

    // Avisa que uma tecla foi digitada.

    keyboard_flag = TRUE;

	// Step 5: 
	// EOI.

    out8(0x20,0x20);     
}



char keyboad_get_char(void)
{
    char ch=0;

    ch = keyboard_queue[keyboard_queue_head];

    keyboard_queue_head++;
    if( keyboard_queue_head > 8 ){
        keyboard_queue_head = 0;
    }

    keyboard_flag = FALSE;
}


char keyboard_wait_key(void)
{
    while(keyboard_flag != TRUE)
    {
         //nothing
    };
    
    return keyboad_get_char();
}


//
// End.
//

