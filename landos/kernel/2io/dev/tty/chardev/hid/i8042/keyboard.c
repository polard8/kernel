/*
 * File: i8042/keyboard.c
 *
 *     Handler for keyboard irq.
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
 * History
 *     2005 - Created by Fred nora.
 */


// See:
// http://danjovic.blogspot.com/2014/06/tabelas-de-scancodes-para-teclados-abnt.html
// http://kbdlayout.info/KBDBR/scancodes
// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-5.html#ss5.12

 
#include <kernel.h>











/*
 *********************
 * irq1_KEYBOARD:
 * 
 *     # Keyboard handler #
 * 
 *     Interface pra chamar o driver de teclado atual.
 *     Essa é a rotina chamada na hora da interrupção de teclado.
 *     IRQ1.
 *     Essa rotina deve selecionar o handler a ser chamado de acordo
 *     com o driver instalado.
 */

	//#todo: 
	// Sondar o driver instalado.
	// um estrutura de dispositivo indica informações sobre o 
	// driver de teclado. como nome, pathname, entrypoint, versão.

	// #todo: 
	// Criar a variável keyboard_type no kernel base.
	// Não aqui ... pois cada driver deve ser para um tipo de teclado.


// #todo
// We need to send the input data to the TTY.
// The foreground process is able to read it using stdin.


__VOID_IRQ 
irq1_KEYBOARD (void)
{

    // #importante
    // O que faria um driver que nao esta dentro do kernel?
    // O driver carregavel se resume em pegar o RAW BYTE e 
    // entregar para o kernel. Nenhum processamento eh feito.
    // Nem mesmo o kernel deve fazer processamento, ele deve
    // passar para o window serve o raw byte e o window server 
    // vai ver o que faz.
    //  


    // Se o teclado ps2 não estiver inicializado !
    if ( __breaker_ps2keyboard_initialized == FALSE ){
        return;
    }


    // Contando as interrupções desse tipo.
    g_profiler_ints_irq1++;


    // #debug
    // Testando se o teclado continua funcionando.
    // Pois ele pode estar enviando sc para o buffer
    // mas não tem thread para pegar.
    // >> na máquina real.
    
    //refresh_rectangle ( 0, 0, 20, 20 );
    //bmpDisplayMousePointerBMP (terminalIconBuffer, 0, 0 ); 

    ____whatchdog_ps2_keyboard = 0;

    // #todo
    // O driver de teclado precisa escrever em seu fluxo padrão,
    // pois é tudo o que ele tem.
    // Depois ele avisa o kernel chamando a tty (slave) ao qual o
    // driver está conectado.
    // >> No momento esse handler está colocando num buffer em
    // current_stdin os scancodes obtidos na digitação.

    // Disable mouse port.
    wait_then_write (0x64,0xA7);


    // #todo
    // Quando tem uma interrupção de teclado,
    // o handler da irq precisa chamar uma função
    // exportada pelo driver de teclado responsavel
    // pelo tratamento dessa interrupção.
    // Esse driver pode estar dentro do kernel ou
    // carregável. No caso de ser carregável, a thread
    // precisa receber um sinal que indique que
    // o kernel deve chamar essa função dentro do driver
    // na próxima vez que o driver receber tempo de processamento,
    // ou imadiatamente se o driver estiver ligado dinamicamente
    // ao kernel.
    // ??: Ainda não tenho muita certeza disso tudo.
    
    // pt-br keyboard.
    // Defined in kernel.h
    // See: ps2kbd.c

    if (abnt2 == TRUE){
        DeviceInterface_PS2Keyboard();
        goto done;
    }
    if (abnt2 != TRUE){ panic("irq1_KEYBOARD: not abnt2\n"); }


done:

    // #bugbug
    // Se estivermos usando uma inicialização reduzida,
    // onde habilitamos somente a porta do teclado,
    // não podemos habilitar a porta do mouse, sem a 
    // devida inicialização.

    // Só reabilitaremos se a configuração de ps2 
    // nos disser que o segundo dispositivo esta em uso.
    
    // Reabilitando a porta de um dispositivo que
    // ja foi devidamente inicializado.

    if ( PS2.used == TRUE )
    {
        // Reenable the mouse port.
        if ( PS2.mouse_initialized == TRUE ){
            wait_then_write (0x64,0xA8);
        }
    }
}


//
// End.
//

