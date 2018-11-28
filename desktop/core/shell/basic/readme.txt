Portando o interpretador de basic do mikeos 4.5

Com isso poderemos usar os programas em Basic feitos para 
o mikeos 4.5


Nessa pasta ficarão vários arquivos em assembly que dão suporte
ao arquivo basic.asm.


Todos arquivos serão incluídos em basic.asm e esse será incluído 
ao shell como um comando interno.


As funções precisam mudar de nome para não darem conflito com as
funções do shell 

As funções poderão começar com 'basic_', para
não serem chamadas pelo shell.

Poderemos importar as funções as mesmas funções usadas pelo shell.
como printf da libc.para Isso o basic terá um stuc em C,
então o basic importará as
funções do stub.  'bstub.c'.




