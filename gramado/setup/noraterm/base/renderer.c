// rendering the text in the buffers onto the screen 
// we need to dispatch commands to a specific final display engine

// vamos pintar na tela.

// rotina de suporte a impressão na tela
// é o momento em que o terminal chama o servidor gráfico para impimir
// os caracteres na tela.
// >> o terminal usará recursos da api até que o servidor gráfico esteja disponível.
// >> o terminal poderá usar recursos da libc para pintar na tela, até que
// recursos da api ou da servidor gráfico estejam disponíveis.
// obs: não é trabalho da libc imprimir na tela.


#include "noraterm.h" 

//#test
//manda uma mensagem para o servidor de recursos gráficos avisando
//para ele pintar.
//int notify_server_paint(){
//}

//#test
//configurar no servidor os limites da área que será pintada.
//int notify_server_paint_setup(){
//}



