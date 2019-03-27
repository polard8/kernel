/*
 * File: i8042/ps2kbd.c
 *
 *     keyboard controller support.     
 *
 * env:
 *     Ring 0. Kernel base persistent code.
 *
 * 2018 - Created by Fred Nora.
 */


#include <kernel.h>

 

// Esta função será usada para ler dados do teclado na porta 0x60, fora do IRQ1
uint8_t keyboard_read (){
 
	kbdc_wait (0);
	
	uint8_t val = inportb (0x60);
    
	wait_ns (200);
    
	return val;
};


// Esta função será usada para escrever dados do teclado na porta 0x60, fora do IRQ1
void keyboard_write (uint8_t write){

	kbdc_wait(1);
	
	outb (0x60,write);
    
	wait_ns(200);
};


// Esta rotina faz o Auto-teste 0xaa êxito, 0xfc erro
int BAT_TEST (){
	
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
	

	for ( i=0; i<999; i++ )
	{
        val = (int) keyboard_read ();

		//Ok funcionou o auto teste
        if(val == 0xAA)
		{
			printf ("ps2kbd.c: BAT_TEST OK\n");
			return (int) 0;
		
		//falhou
		}else if ( val == 0xFC ){
        
			printf ("ps2kbd.c: BAT_TEST fail\n");
            return (int) -1; 
        }
    
		// #bugbug
		// Tentar novamente, indefinidas vezes.
        // Esse é o problema. Vamos tentar apenas algumas vezes e falhar se não der certo.
		// Reenviar o comando. 
        // obs: este comando não é colocado em buffer
        
		//printf ("ps2kbd.c: BAT_TEST %d\n", i);
		keyboard_write (0xFE);       
    };
	
	//fail
	printf ("ps2kbd.c: BAT_TEST %d times\n",i);
    return (int) -1; 	
}


/*
 ********************************** #bugbug: essa rotina falhou em gigabyte/intel/chipset=via
 * init_keyboard:
 *     ??
 *     Inicializa o driver de teclado.
 *
 *  @todo: enviar para o driver de teclado o que for de lá.
 *         criar a variável keyboard_type ;;; ABNT2 
 */

void ps2_keyboard_initialize (){
	
	
	//printf ("ps2_keyboard_initialize: 1\n");
	//refresh_screen();	
	
	//user.h
	ioControl_keyboard = (struct ioControl_d *) malloc( sizeof(struct ioControl_d) );
	
	if ( (void *) ioControl_keyboard == NULL )
	{
		printf("ps2_keyboard_initialize: ioControl_keyboard fail");
		die ();
		
	} else {
	    
	    ioControl_keyboard->id = 0;
	    ioControl_keyboard->used = 1;
	    ioControl_keyboard->magic = 1234;
	    
		ioControl_keyboard->tid = 0;  //qual threa está usando o dispositivo.
	    //ioControl_keyboard->
	};
	
    //int Type = 0;

    //
    // @todo: 
	//     Checar se o teclado é do tipo abnt2.   
	//     É necessário sondar parâmetros de hardware,
	//     como fabricante, modelo para configirar estruturas 
	//     e variáveis.
	//


/*
    switch(Type)
	{
	    //NULL
		case 0:	
		    break;
			
	    //Americano.
		case 1:	
		    break;

		//pt-ABNT2	
	    case 2:	
		    break;
			
		//...
		
		//Modelo americano
		default:	
		    break;
	}
	
*/
	
	//#debug
	//Tentando suprimir esse delay. OK
	//printf ("ps2_keyboard_initialize: 2\n");
	//refresh_screen();	

	
	
	// #test
	// Inicializando o buffer de teclado.
	// #bugbug: Não sabemos se nesse momento a estrutura de stream já é válida.
	
	int i;
	
	for ( i=0; i< current_stdin->_cnt ; i++){
		current_stdin->_base[i] = (char) 0;
	}
	
	for ( i=0; i<128; i++){
	    keybuffer[i] = 0;
	}
	
	keybuffer_head = 0;
	keybuffer_tail = 0;
	
	//
	// Set abnt2.
	//

	abnt2 = (int) 1;

    //Checar quem está tentando inicializar o módulo.    

	//model.
	
	//handler.
	
	//...

    //Key status.
	key_status = 0;
    escape_status = 0;
    tab_status = 0;
    winkey_status = 0;
    ctrl_status = 0;
    alt_status = 0;
    shift_status = 0;
	capslock_status = 0;
	scrolllock_status = 0;
	numlock_status = 0;
	//...
	
	//test
	//0xAB	Test first PS/2 port
	//0x00 test passed
	//0x01 clock line stuck low 
	//0x02 clock line stuck high
	//0x03 data line stuck low
	//0x04 data line stuck high
	


	//Leds.
	//LED_SCROLLLOCK 
	//LED_NUMLOCK 
	//LED_CAPSLOCK  	
	//keyboard_set_leds(LED_NUMLOCK);
	
 
	
	//#debug
	//Tentando suprimir esse delay. OK
	//printf ("ps2_keyboard_initialize: 3\n");
	//refresh_screen();	

	
	
    //#imporante:
	//não habilitaremos e não resetaremos o dispositivo.
    //habilitar e resetar fica para a inicialização do ps2.
	
	
	//Reseta o teclado
	kbdc_wait(1);
	outb(0x60,0xFF);
	
	wait_ns(200);
	
	// #bugbug
	// Isso pode travar ??
	// Espera os dados descer, ACK
    while(keyboard_read() != 0xFA);
	

	// #debug
	// Tentando suprimir esse delay. 
	//printf ("ps2_keyboard_initialize: 4\n");
	//refresh_screen();	
	
	//#bugbug
	//esse delay 'e necess'ario par aa rotina de auto teste funcionar na ma'quina real.
	// Ele foi movido para dentro da rotina de autotest.
	
	/*
	for (i=0; i<99000; i++)
	{
		wait_ns(200);
	}
	*/
	
    // Basic Assurance Test (BAT)
    
	if ( BAT_TEST () != 0) 
	{
        // Nelson aqui precisaremos de criar uma rotina de tratamento de erro do teclado
        printf ("[WARMING] ps2kbd.c:  BAT_TEST ignored\n");
		
		//#debug
		//refresh_screen();
		//while(1){}
    }  

	// #debug
	// Tentando suprimir esse delay. OK
	//printf ("ps2_keyboard_initialize: 5\n");
	//refresh_screen();	

	
    // espera nossa controladora termina
	kbdc_wait(1);
	
	//Debug support.
	scStatus = 0;
	
    g_driver_keyboard_initialized = (int) 1;
}


//Pega o status das teclas de modificação.
unsigned long keyboardGetKeyState ( unsigned char key ){
	
	unsigned long State = 0;
	
	switch (key){
		
		case VK_LSHIFT: 
		    State = shift_status; 
			break;

	    case VK_LCONTROL:
		    State = ctrl_status;
		    break;

	    case VK_LWIN:
		    State = winkey_status;
		    break;

	    case VK_LMENU:
		    State = alt_status;
		    break;

	    case VK_RWIN:
		    State = winkey_status;
		    break;

	    case VK_RCONTROL:
		    State = ctrl_status;
		    break;
			
	    case VK_RSHIFT:
		    State = shift_status;
		    break;

	    case VK_CAPITAL:
		    State = capslock_status;
		    break;

	    case VK_NUMLOCK:
		    State = numlock_status;
		    break;
			
		case VK_SCROLL:
            State = scrolllock_status;
            break;			
			
		//...
	};

	//Nothing.

    return (unsigned long) State;		
};


// Inicializa o status das teclas de modificação.
// são usadas em comjunto com outras teclas para criar atalhos.
// modificam temporariamente a função de outra tecla.
void ldisc_init_modifier_keys (){
	
	// Modifier keys.
	
	shift_status = 0;
	ctrl_status = 0;
	winkey_status = 0;
    
	// Alternate.
    alt_status = 0;

	// Alternate Graphic.
    //altgr_status = 0; //@todo
    
	// Function.
	//fn_status = 0;  //@todo
	
	//...
};


// modificam permanentemente a função de outra tecla.
//ativa as teclas extendidas.
void ldisc_init_lock_keys (){
	
    // Capital Lock.	
	capslock_status = 0;
	
	// Scrolling Lock.
	scrolllock_status = 0;
	
	// Number Lock.
	numlock_status = 0;	
};


/*
 * keyboardEnable:
 *     Enable keyboard.
 */

void keyboardEnable (){
	
	//Wait for bit 1 of status reg to be zero.
    
	while ( (inportb(0x64) & 2) != 0 )
	{
		//Nothing.
	};
	
	//Send code for setting Enable command.
    outportb(0x60,0xF4);
    //sleep(100);
}


/*
 * keyboardDisable:
 *     Disable keyboard.
 */

void keyboardDisable (){
	
	//Wait for bit 1 of status reg to be zero.
    
	while ( (inportb(0x64) & 2) != 0 )
	{
		//Nothing.
	};
	
	//Send code for setting disable command.
    outportb(0x60,0xF5);
    //sleep(100);
}


/*
 * keyboard_set_leds:
 *     Set keyboard flags.
 *     ED = Set led.
 */
void keyboard_set_leds (char flag){
	
	//@todo: filtro.

	//Wait for bit 1 of status reg to be zero.
    while( (inportb(0x64) & 2) != 0 ){
		//Nothing.
	};
	//Send code for setting the flag.
    outportb(0x60,0xED);            
    sleep(100);

	//Wait for bit 1 of status reg to be zero.
	while( (inportb(0x64) & 2) != 0 ){
	    //Nothing.	
	};
    //Send flag. 
	outportb(0x60,flag);
	sleep(100);
	
	//@todo mudar o status.
    //switch(flag)
    //{
		
	//}	
};



/*
 * KdGetWindowPointer:
 *     Retorna o ponteiro da estrutura de janela que pertence a thread.
 *     Dado o id de uma thread, retorna o ponteiro de estrutura da janela 
 * à qual a thread pertence.
 */

void *KdGetWindowPointer (int tid){
	
	struct thread_d *t;

	//@todo: filtrar argumento. 
	
	if ( tid < 0 )
        return NULL;
        
		
	// Structure.
	t = (void *) threadList[tid];

	if ( (void *) t == NULL )
	{
        return NULL;        
	};
	
	return (void *) t->window;
};


/*
 * KbGetMessage:
 *     Pega a mensagem na fila de mensagens na estrutura da thread
 * com foco de entrada.
 *
 * Na estrutura da thread com foco de entrada tem uma fila de mensagens.
 * Pegar a mensagem.
 * 
 * Para falha, retorna -1.
 *
 * @todo: bugbug: A mensagem deve estar na fila do processo, na
 *                estrutura do proceso. (Talvez não na thread e nem na janela.)
 */

int KbGetMessage (int tid){
	
	int ret_val;
	struct thread_d *t;
	
	// Structure.
	t = (void*) threadList[tid];

	if ( (void *) t != NULL )
	{
        ret_val = (int) t->msg;
	}else{
	    ret_val = (int) -1;    //Fail.
	};

	WindowProcedure->msgStatus = 0;    //Muda o status.
	return (int) ret_val;              //Retorna a mensagem.
};


/*
 * KbGetLongParam1:
 *    Pega o parametro "long1" do procedimento de janela de uma thread.
 */

unsigned long KbGetLongParam1 (int tid){
   	
	struct thread_d *t;
	
	// Structure.
	t = (void *) threadList[tid];

	if ( (void *) t == NULL)
	{
        return (unsigned long) 0;    //@todo: fail;
	};

    return (unsigned long) t->long1;
};


/*
 * KbGetLongParam2:
 *     Pega o parametro "long2" do procedimento de janela de uma thread.
 */
unsigned long KbGetLongParam2 (int tid){
	
	struct thread_d *t;
	
	// Structure.
	t = (void *) threadList[tid];

	if ( (void *) t == NULL)
	{
        return (unsigned long) 0;    //@todo: fail;
	};

    return (unsigned long) t->long2;
};



/*
 * reboot: 
 *     @todo: essa rotina poderá ter seu próprio arquivo.
 *     Reboot system via keyboard port.
 *     ?? #bugbug Por que o reboot está aqui ??
 *
 * *IMPORTANTE: a interface fechou o que tinha qe fechar,
 * hal chamou essa hotina para efetuar a parte de hardware reboot apenas.
 * @todo: Atribuições.
 *
 * Atribuições: 
 *     + Desabilitar as interrupções.
 *     + Salvar registros.
 *     + Salvar programas abertos e não salvos.
 *     + Fechar todas tarefas antes.
 *     + Efetuar o tipo de reboot especificado.
 *    + Outras ...
 */
 
void reboot (){
    
    //@todo: 
	// +criar uma variavel global que especifique o tipo de reboot.
    // +criar um switch para efetuar os tipos de reboot.
	// +criar rota de fuga para reboot abortado.
	// +Identificar o uso da gui antes de apagar a tela.
	//  modo grafico ou modo texto.
	//
	
	//
	// Video.
	//
	
	/*
	sleep(2000);
	//kclear(9);
    set_up_cursor(0,0);	
    set_up_text_color(0x0f, 0x09);
	printf("\n\n REBOOTING ...\n\n");


	//
	// Scheduler stuffs.
	//
	
	sleep(1000);
	printf("locking scheduler ...\n");
	scheduler_lock();
	
	//
	// Tasks.
	//
	
	//@todo: fazer função com while. semelhante ao dead task collector.
	
	sleep(1000);
	printf("killing tasks ...\n");
	//kill_thread(current_task); 
	
	//
	// Final message.
	//
	
	sleep(1000);
	printf("turning off ...\n");
    
	
	refresh_screen();
	
	//
	// Interruoções.
	//
	
	sleep(7000);
	asm("cli");
	
	*/
	
	
	// @todo: disable();
	
//
// Done.
//

    hal_reboot ();
	die ();
};



//Get alt Status.
int get_alt_status (){
	
    return (int) alt_status;
};


//Get control status.
int get_ctrl_status (){
	
    return (int) ctrl_status;
};

 
int get_shift_status (){
	
    return (int) shift_status;	
};
 

/*
 * kbdc_wait:
 *     Espera por flag de autorização para ler ou escrever.
 *     (Nelson Cole) 
 */
void kbdc_wait (unsigned char type){
	
	if (type==0)
	{
		//#bugbug rever
        while ( !inportb(0x64) & 1 )
		{
			outanyb (0x80);
			outanyb (0x80);
			outanyb (0x80);
			outanyb (0x80);
		};
		
    }else{
		
        while ( inportb(0x64) & 2 )
		{
			outanyb (0x80);
			outanyb (0x80);
			outanyb (0x80);
			outanyb (0x80);
		};
	};
};


//?? isso tá sem protótipo ??
void set_current_keyboard_responder ( int i ){
	
	current_keyboard_responder = i;
};


//?? isso tá sem protótipo ??
int get_current_keyboard_responder (){
	
	return (int) current_keyboard_responder;
};


/*
 * Constructor.
int keyboardKeyboard(){
	;
};
*/


/*
 obs: definido acima.
int keyboardInit(){
	;
};
*/


/*
void keyboard();
void keyboard()
{
	//@todo: Create global.
	if(gKeyboardType == 1){
		abnt2_keyboard_handler();
	}
	//...
	return;
}
*/


