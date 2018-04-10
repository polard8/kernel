

/fs

 nesse diretório ficará o suporte aos diversos sistemas de arquivos suportados
pelo sistema.
Mesmo que o driver seja um servidor em user mode ele poderá ter algum código aqui
no kernel base que ajude a inicializar o servidor em user mode.
algum suporte a inicialização dos diversos sistemas de arquivos deverá ficar aqui mesmo.



    O sistema de arquivos será o controlador do sistema.
    Tudo será considerado um arquivo,
    Até mesmo o gerente de objetos estará sujeito ao sistema de aruqivos
    para isso o diretório /objects será criado mas nunca será salvo no disco.
Esse diretório conterá o arquivo raiz da gerência de objetos. Um descritor de
objeto significar o indice da entrada em /objects.


