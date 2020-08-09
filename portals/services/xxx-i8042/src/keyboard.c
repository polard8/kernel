/*
 * File: i8042/keyboard.c
 *     +handler for keyboard irq.    
 *
 * env:
 *     Ring 0. Kernel base persistent code.
 *
 * Driver de teclado presente dentro do Kernel Base.
 * Esse será o driver de teclado para o modelo abnt2.
 *
 * Ambiente: 
 *     Kernel mode.
 *
 * Teclados usados:
 *
 * @todo: Fazer rotinas para identificar fabricante e modelo.
 * @todo:
 *     Gerenciamento de caracteres, linhas e listas de linhas. Como acontece
 * no Unix, os caracteres recebidos aqui devem prosseguir até seu destino
 * final. O que envolve, algum tipo de disciplina de linhas, lista encadeadas 
 * de linha, emulador de terminal, fila do dispositivo gráfico, fila do
 * processo.
 * Obs: As listas de linhas ficam em lista encadeada, que provavelmente
 * pertence ao processo que está manipulando linhas.
 * Obs: A disciplica de linhas dentro do kernel serve também para movimentar
 * linhas de caracteres entre kernel mode e user mode, alimentar buffers de
 * dispositivos ou pegar linhas de caracteres nos buffers de dispositivos
 * como NIC, (placa de rede).
 *
 * >>>>>>> Não é responsabilidade do driver de teclado
 * encontrar o destino certo da mensagem, ele só precisa entregar ela pro
 * serviço de sistema responsável.
 *     
 *
 * Histórico: 
 *     2005~2013 - Created by Fred nora.
 *     2017      - Rotines was moved to ldisc.
 *     ...
 */

 
#include <kernel.h>

//
// Obs: um driver de teclado precisa ter acesso as portas, 
// As opções são:
// + se o driver estiver em ser mode ele precisa de uma systemcall 
// para acessar as portas para configurar o controlador ps/2.
// +se o driver estiver em kernel mode, tudo o que ele precisa é de uma 
// biblioteca estática que acesse as portas por ele.
//


/*
 * *******************************************************
 * abnt2_keyboard_handler: 
 *     Keyboard handler for abnt2 keyboard.
 *     fica dentro do driver de teclado.
 *
 *     A interrupção de teclado vai chamar essa rotina.
 *     @todo: Usar keyboardABNT2Handler().
 * void keyboardABNT2Handler() 
 * Esse será o handler do driver de teclado
 * ele pega o scacode e passa para a entrada do line discipline dentro do kernel.
 *
 * @TODO: ISSO DEVERÁ IR PARA UM ARQUIVO MENOR ... OU AINDA PARA UM DRIVER.
 * Pega o scacode cru e envia para a disciplina de linhas que deve ficar no kernelbase.
 * Essa é a parte do driver de dispositivo de caractere.
 *
 * #importante:
 * O driver deverá de alguma maneira notificar o kernel sobrea a ocorrência
 * do evento de input. Para que o kernel acorde as trheads que estão esperando 
 * por eventos desse tipo.
 *
 */

	//#importante:
	// Provavelmente uma interrupção irá fazer esse trabalho de 
	// enviar o scancode para o kernel para que ele coloque na fila.
	// Nesse momento o kernel de sentir-se alertado sobre o evento de 
	// input e acordar a threa que está esperando por esse tipo de evento. 
	
	
	// #obs: 
    // Esse buffer está em gws/user.h 

// PUT SCANCODE
void abnt2_keyboard_handler (){
	
    unsigned char scancode = inportb (0x60);	
		
	current_stdin->_base[keybuffer_tail++] = (char) scancode;
	
	if ( keybuffer_tail >= current_stdin->_cnt ){
		keybuffer_tail = 0;
	}
}

/*
// PUT SCANCODE
void abnt2_keyboard_handler (){
	
    unsigned char scancode = inportb (0x60);	
		
	keybuffer[keybuffer_tail++] = (char) scancode;
	
	if ( keybuffer_tail >= 128 ){
		keybuffer_tail = 0;
	}
};
*/


//#importante
//Isso é usado pelo serviço que pega mensagens de input. (111).
//pega o scancode.
//renova a fila do teclado

unsigned long get_scancode (){
	
	unsigned long SC = 0;
	
	SC = (unsigned char) current_stdin->_base[keybuffer_head];
					
	current_stdin->_base[keybuffer_head] = 0;
	
	keybuffer_head++;
	
	if ( keybuffer_head >= current_stdin->_cnt ){ 
	    keybuffer_head = 0; 
	};	
	
	return (unsigned long) SC; 	
}

/*
// GET SCANCODE
unsigned long get_scancode (){
	
	unsigned long SC = 0;
	
	SC = (unsigned char) keybuffer[keybuffer_head];
					
	keybuffer[keybuffer_head] = 0;
	
	keybuffer_head++;
	
	if ( keybuffer_head >= 128 ){ 
	    keybuffer_head = 0; 
	};	
	
	return (unsigned long) SC; 	
}
*/

/*
 **************
 * KiKeyboard:
 *     Interface pra chamar o driver de teclado
 *     atual.
 *     Essa é a rotina chamada na hora da interrupção de teclado.
 *     IRQ1.
 *     Essa rotina deve selecionar o handler a ser chamado de acordo
 *     com o driver instalado.
 */
 
void KiKeyboard (){
	
    //@todo: sondar o driver instalado.	
	//       um estrutura de dispositivo
	//       indica informações sobre o driver de teclado.
	//       como nome, pathname, entrypoint, versão.

	
	//@todo: Criar a variável keyboard_type no kernel base.
    //Não aqui ... pois cada driver deve ser para um tipo de teclado.
	
    if (abnt2 == 1)
	{
	    abnt2_keyboard_handler ();
	};

    if (abnt2 != 1)
	{
	    panic ("unblocked-KiKeyboard: not abnt2\n");
	};
}


//
// End.
//

