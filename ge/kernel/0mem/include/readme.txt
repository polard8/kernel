
    Como esse include/ pertence aos
    módulos dentro de kernel/, então podemos
    retirar todas as pastas daqui e deixar
    os headers soltos. Inclusive kernel.h pode ir para dentro
    da pasta include/ o que permite incluir todos os arquivos usando #include "xxx"
    ao invés de #include <xxxx/zzz>


   Headers:
   
    kernel.h
	    Main header for the kernel base.
   
    /kernel
       Kernel base, ring 0.

