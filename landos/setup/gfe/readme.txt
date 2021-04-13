
Esse é um aplicativo para rodar no sistema operacional gramado.
Roda apenas no ambiente gramado core, no processo init.

É um editor de testes para testar funcionalidades do sistema.
No momento usamos ele para testar o envio de uma string do shell
para o editor através do kernel via memória compartilhada.
O envio da mensagem funcionou.

crt0.asm contém o entry point, chamando main em seguida.


entry point em  
crt0 ()
  


função principal em main.c
gfeMain ();


flags na linha de comando poderão alterar o funcionamento desse aplicativo,
para que ele sirva de suporte ao desenvovledor.

ex: gfe.bin -ls