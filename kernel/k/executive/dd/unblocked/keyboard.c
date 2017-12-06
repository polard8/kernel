
//esse será o driver de teclado.
#include <kernel.h>


/*
 ********************************************************
 * abnt2_keyboard_handler: 
 *     Keyboard handler for abnt2 keyboard.
 *     A interrupção de teclado vai chamar essa rotina.
 *     @todo: Usar keyboardABNT2Handler().
 */
//void keyboardABNT2Handler() 
//Esse será o handler do driver de teclado
//ele pega o scacode e passa para a entrada do line discipline dentro do kernel.
//
//@TODO: ISSO DEVERÁ IR PARA UM ARQUIVO MENOR ... OU AINDA PARA UM DRIVER.
//
// essa é a parte do driver de dispositivo de caractere.
void abnt2_keyboard_handler()
{
	//pega o scacode cru e envia para a disciplina de linhas que deve ficar no kernelbase.
    unsigned char scancode;    //Scancode.
	scancode = inportb(0x60);	
    LINE_DISCIPLINE(scancode);
}

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


    if(abnt2 == 1){
	    abnt2_keyboard_handler();
	};

    if(abnt2 != 1){
	    panic("O teclado nao eh abnt2.");
	};

    // KeKeyboard();	

	//Switch??

done:
    return;
};


