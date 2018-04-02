
Sobre o diretório:
=================


    Os headers presentes nesse diretório são do executive do kernel base.
    Oferecem acesso à rotinas dos módulos internos do kernel base
    o propósito é ser público dentro do kernel base,
    pra que qualquer módulo do kernel base possa ter acesso fácil 
    aos serviços oferecidos pelo executive.


    //Pastas para os recursos principais do sistema.

Apenas três pastas:
    /uitm - Gerencia recursos de interface com o usuário em modo texto
    /uigm - Gerencia recursos de interface com o usuário em modo gráfico
    /sm   - System management.




Sobre o emulador de terminal:
======================
     Interface do usuário em modo texto.
     O emulador de terminal será usado por muitos programas, desde o shell
até muitos programas de modo texto.
     Um programa de modo texto roda no emulador de terminal independente do shell.
     Já o shell poderá chamar programas de modo texto que rodarão em seu proprio terminal.


