
// #todo
// Move this file to kdrivers/tty/  !!!

#ifndef ____X_VIRTCON_H
#define ____X_VIRTCON_H


//
// Virtual Consoles.
//

// Gerencia de consoles virtuais.
// F1 ~ F7

// consoles para terminais virtuais dentro do kernel
// e x-server console.

// #importante
// O desenvolvedor do kernel pode ficar usando um dos 
// terminais virtuais dentro do kernel e deixar o console
// do x-server para outros desenvolvedores.
// O sistema iniciará em um dos consoles virtuais, o console
// do x-server só será inicializado pelo processo /init
// se assim estiver configurado.

// 7 consoles virtuais acessarão o driver de vídeo
// oferecendo a possibilidade do kernel exibir conteúdo
// na tela.
// Provavelmente exibirão na tela o conteúdo de arquivos. São
// terminais virtuais dentro do kernel. (unix like e linux fazem isso.)
//

// F1 ~ F6 - As sessões são no formato de texto. sem janelas.
// As janelas são coisas do x-server. (x=janela)
// Essas sessões provavelmente lerão arquivos e usrão buffer
// assim como fazem os terminais virtuais fora do kenel.

// F7 - O sétimo é uma sessão do x-server.
// quando utilizamos o xserver então a sessão é no formato de gui.


// F8 ~ ... serão sessões do x-server apenas.
// Sessões de modo 'texto' só podem ficar nas primeiras posições,
// de F1 ~ F7, mas o x-server pode usar isso também.

// #todo
// A estrutura aqui terá elementos que são ponteiros para
// estruturas que ja existem e dão suporte a terminal e tty.

//
// pts
//

// os pseudo terminais usarão s sessão do x-server para 
// enviar dados para o driver de video.

// Isso dará acesso aos dados da tty.
struct virtual_console_d 
{
    int id;

    int used;
    int magic;

    // 0 = 'text'
    // 1 = 'x-server'
    int mode;
    
    struct user_info_d *user_info;
    
    struct usession_d *usession;
    struct room_d     *room;     //window station
    struct desktop_d  *desktop;

    struct tty_d *tty;
};

unsigned long virtualconsoleList[12];

#endif   











