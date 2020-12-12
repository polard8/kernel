/*
 * File: i8042/keyboard.c
 *
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


// See:
// http://danjovic.blogspot.com/2014/06/tabelas-de-scancodes-para-teclados-abnt.html
// http://kbdlayout.info/KBDBR/scancodes
// https://www.win.tue.nl/~aeb/linux/kbd/scancodes-5.html#ss5.12

 
#include <kernel.h>





//#define QUEUE_SIZE 32



//
// Obs: um driver de teclado precisa ter acesso as portas, 
// As opções são:
// + se o driver estiver em ser mode ele precisa de uma systemcall 
// para acessar as portas para configurar o controlador ps/2.
// +se o driver estiver em kernel mode, tudo o que ele precisa é de uma 
// biblioteca estática que acesse as portas por ele.



/*
 *************************** 
 * get_scancode:
 */

// Low level keyboard reader.
// Isso poderia usar uma rotina de tty

// #importante
// Isso é usado pelo serviço que pega mensagens de input. (111).
// Pega o scancode.
// Renova a fila do teclado
// O teclado esta lidando no momento com um buffer pequeno, 128 bytes.

unsigned long get_scancode (void){

    unsigned long SC = 0;



    SC = (unsigned char) PS2keyboardTTY._rbuffer->_base[keybuffer_head];


    PS2keyboardTTY._rbuffer->_base[keybuffer_head] = 0;

    keybuffer_head++;

    if ( keybuffer_head >= PS2keyboardTTY._rbuffer->_lbfsize )
    { 
        keybuffer_head = 0; 
    }

    return (unsigned long) SC; 
}


void put_scancode( char c )
{
    // #todo: 
    // Aqui podemos retornar.
    // Pois vamos precisar dessa estrutura para o buffer.
    
    if ( (void *) PS2keyboardTTY._rbuffer == NULL )
    {
        panic ("put_scancode: PS2keyboardTTY._rbuffer \n");
    }

    // #bugbug
    // Checar a validade.

    PS2keyboardTTY._rbuffer->_base[keybuffer_tail++] = (char) c;
    
    if ( keybuffer_tail >= PS2keyboardTTY._rbuffer->_lbfsize )
    {
        keybuffer_tail = 0;
    }

}



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
 */

	//#importante:
	// Provavelmente uma interrupção irá fazer esse trabalho de 
	// enviar o scancode para o kernel para que ele coloque na fila.
	// Nesse momento o kernel de sentir-se alertado sobre o evento de 
	// input e acordar a threa que está esperando por esse tipo de evento. 
	
	// #obs: 
    // Esse buffer está em gws/user.h 


// Low level keyboard writter.
// Isso poderia usar uma rotina de tty
// O teclado esta lidando no momento com um buffer pequeno, 128 bytes.

// PUT SCANCODE

void abnt2_keyboard_handler (void){

    static int __has_e0_prefix = 0;
    static int __has_e1_prefix = 0;

    wait_then_write (0x64,0xA7);  //Disable mouse port.


    // ??
    // See: Serenity os.
    //u8 status = IO::in8(I8042_STATUS);
    //if (!(((status & I8042_WHICH_BUFFER) == I8042_KEYBOARD_BUFFER) && (status & I8042_BUFFER_FULL)))
        //return;


    //não precisamos perguntar para o controlador se
    //podemos ler, porque foi uma interrupção que nos trouxe aqui.
    // #obs:
    // O byte pode ser uma resposta à um comando ou 
    // um scancode.

    unsigned char __raw=0;
    unsigned char val=0;

sc_again:

    // old way
    //__raw = in8(0x60);


    //===========================================
    
    //
    // #test
    // Testing with ack
    // credits: minix
    //
    
    // #define KEYBD		0x60	/* I/O port for keyboard data */
    // #define PORT_B          0x61	/* I/O port for 8255 port B (kbd, beeper...) */
    // #define KBIT		0x80	/* bit used to ack characters to keyboard */
    
    __raw = in8(0x60);		/* get the scan code for the key struck */
    val   = in8(0x61);		/* strobe the keyboard to ack the char */
    out8(0x61, val | 0x80);	/* strobe the bit high */
    out8(0x61, val);		/* now strobe it low */
    //===========================================



    //
    // == Queue ====================================
    //

    // Global keyboard tty.
    // #bugbug: 
    // Se estamos colocando na fila e retirando em seguida
    // entao nao precisamos colocar.
    // Vamos suspender o uso dessa fila ate termos um driver.

    // put_scancode(__raw); 
    // __raw = (unsigned char) get_scancode();


     // #bugbug
     // [Enter] in the numerical keyboard isn't working.
     // teclas do teclado extendido.
     // Nesse caso pegaremos dois sc da fila.
    // #obs:
    // O scancode é enviado para a rotina,
    // mas ela precisa conferir ke0 antes de construir a mensagem,
    // para assim usar o array certo.
    // See: ws/ps2kbd.c
    
    // #bugbug
    // Esse tratamento do scancode não faz sentido quando temos um
    // window server instalado. Nesse caso deveríamos deixar o
    // window server pegar os scancodes.
    // Mas por enquanto, essa rotina manda mensagens para o ws
    // caso tenha um instalado.


     if ( __raw == 0 )   {                      goto done;  }
     if ( __raw == 0xE0 ){ __has_e0_prefix = 1; goto done;  }
     if ( __raw == 0xE1 ){ __has_e1_prefix = 1; goto done;  }

     
     
     // + Build the message and send it to the thread's queue.
     // This routine will select the target thread.
     // + Or send the message to the input TTY.
     // This way the foreground process is able to get this data.
     // See: ps2kbd.c

    KEYBOARD_SEND_MESSAGE (__raw);

    // Clean the mess.
    __has_e0_prefix = 0;
    __has_e1_prefix = 0;

done:
    wait_then_write (0x64,0xA8);  // Reenable the mouse port.
    return;
}



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


	// Se o teclado ps2 não estiver inicializado !
    if ( __breaker_ps2keyboard_initialized == 0 )
        return;


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

    // pt-br keyboard.
    if (abnt2 == 1){
        abnt2_keyboard_handler();
        return;
    }

    if (abnt2 != 1){ panic("irq1_KEYBOARD: not abnt2\n"); }
}


//
// End.
//

