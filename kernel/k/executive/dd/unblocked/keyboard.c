
//esse será o driver de teclado.
#include <kernel.h>


/*
 * *******************************************************
 * abnt2_keyboard_handler: 
 *     Keyboard handler for abnt2 keyboard.
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
 */
void abnt2_keyboard_handler()
{
    unsigned char scancode;
	
	//
	// Pega o scancode. 
	//

	scancode = inportb(0x60);	
    	
	//
	// * Importante:
	//   Aqui chamamos uma rotina que deve ficar no kernel base.
    //   Se estamos no driver de teclado em kernel mode precisamos	
	//   de um método para chamar o kernel base. Talvez system call.
	//
	
callLineDiscipline:	
	LINE_DISCIPLINE(scancode);
	return;
};


/*
 *******************************************************************
 * KiKeyboard:
 *     Interface pra chamar o driver de teclado
 *     atual.
 *     Essa é a rotina chamada na hora da interrupção de teclado.
 *     IRQ1.
 *     Essa rotina deve selecionar o handler a ser chamado de acordo
 *     com o driver instalado.
 * 
 */
void KiKeyboard()
{
    //@todo: sondar o driver instalado.	
	//       um estrutura de dispositivo
	//       indica informações sobre o driver de teclado.
	//       como nome, pathname, entrypoint, versão.

	
	//@todo: Criar a variável keyboard_type no kernel base.
    //Não aqui ... pois cada driver deve ser para um tipo de teclado.
	
    if(abnt2 == 1){
	    abnt2_keyboard_handler();
	};

    if(abnt2 != 1){
	    panic("O teclado nao eh abnt2.");
	};

done:
    return;
};


