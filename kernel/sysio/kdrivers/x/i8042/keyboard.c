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



    SC = (unsigned char) current_stdin->_base[keybuffer_head];


    current_stdin->_base[keybuffer_head] = 0;

    keybuffer_head++;

    if ( keybuffer_head >= current_stdin->_lbfsize )
    { 
        keybuffer_head = 0; 
    }


    return (unsigned long) SC; 
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


    // ??
    // See: Serenity os.
    //u8 status = IO::in8(I8042_STATUS);
    //if (!(((status & I8042_WHICH_BUFFER) == I8042_KEYBOARD_BUFFER) && (status & I8042_BUFFER_FULL)))
        //return;


	//não precisamos perguntar para o controlador se
	//podemos ler, porque foi uma interrupção que nos trouxe aqui.

    unsigned char __raw = in8 (0x60);


    // #obs:
    // O byte pode ser uma resposta à um comando ou 
    // um scancode.

    switch (__raw)
    {
        // O controlador solicitou um resend. :)
        // case RESEND:        
        // break;
        
        // O controlador avisa que recenheceu o comando anterior.
        // case ACKNOWLEDGE:   
        // break;        
        
        // O scancoude.
        default: 
            break;           
    };





//__queue:

    // #todo: 
    // Aqui podemos retornar.
    // Pois vamos precisar dessa estrtuura pora o buffer.
    if ( (void *) current_stdin == NULL ){
        panic ("abnt2_keyboard_handler: current_stdin \n");
    }

    // #bugbug
    // Checar a validade.

    current_stdin->_base[keybuffer_tail++] = (char) __raw;
    
    if ( keybuffer_tail >= current_stdin->_lbfsize ){
        keybuffer_tail = 0;
    }
    
    
    // #bugbug
    // Porque estamos usando estrutura de thread dentro do driver.
    // #todo
    // Indicaremos a thread se precisarmos enviar esses dados.
    // Mas o driver de i8042 vai ficar dentro do kernel base
    // por enquanto.
    
    
//__thread:

    struct thread_d *t;
    
    t = (void *) threadList[current_thread];

    if ( (void *) t == NULL ){
        panic ("abnt2_keyboard_handler: Invalid thread calling \n");
    }    
    //{ return NULL; }
            
    if ( t->used != 1 || t->magic != 1234 ){
        panic ("abnt2_keyboard_handler: Validation. Invalid thread calling \n");
    }    
    //{ return NULL; }


	// Se não existe uma mensagem na thread, então vamos
	// pegar uma mensagem de teclado no buffer de teclado (stdin).
	// Mas e se retornar o valor zero, pois não tem nada no buffer?
	// Nesse caso vamos retornar essa função dizendo que não temos mensagem
	// ou tentaremos pegar mensagens em outro arquivo de input.
	// #teste Do mesmo modo, se o scancode for um prefixo, podemos
	// pegar o próximo scancode para termos uma mensagem.


            // #bugbug
            // Podemos ter loop infinito ?
sc_again:

     // Get char from current_stdin.
     __raw = (unsigned char) get_scancode ();

     //unsigned ch = raw & 0x7f;
     //int pressed = !(raw & 0x80);
            
     if ( __raw == 0 )
     { return; }

     // teclas do teclado extendido.
     // Nesse caso pegaremos dois sc da fila.
    
     if ( __raw == 0xE0 )
     {
         __has_e0_prefix = 1;
         goto sc_again;
     }

     //if ( __RAW == 0xE1 )
     //{
          __has_e1_prefix = 1;
          //goto sc_again;
     //}


    //#obs:
    //o scancode é enviado para a rotina,
    //mas ela precisa conferir ke0 antes de construir a mensagem,
    //para assim usar o array certo.

    KEYBOARD_SEND_MESSAGE (__raw);

    // Clean the mess
    __has_e0_prefix = 0;
    __has_e1_prefix = 0;
}



/*
 *********************
 * KiKeyboard:
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

void KiKeyboard (void){


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
    if (abnt2 == 1)
    {
        abnt2_keyboard_handler ();
        return;
    }

    if (abnt2 != 1)
    {
        panic ("KiKeyboard: not abnt2\n");
    }
}


//
// End.
//

