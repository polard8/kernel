/*
 * File: executive\dd\unblocked\keyboard.c
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
	//   Estamos no driver de teclado.
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
	    panic("unblocked-KiKeyboard: not abnt2.\n");
	};

done:
    return;
};

//
//fim.
//

