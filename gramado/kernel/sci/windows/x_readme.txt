
   x-server dentro do base kernel.
   
   
   /x/i8042 - drivers para os controladores de mouse e teclado ps/2.
   /x/video - drivers para controladores de vídeo.
   
   
  ------------------

 Essa é a parte de mais baixo nível do x-server.
 São os drivers de teclado, mouse e vídeo.
 
 IN: teclado, mouse
 OUT: vídeo.
 
 
 Todo input deve começar por aqui.
 Todo output deve terminar aqui, para que esse módulo acesse a
 memória de vídeo.
 
 Somente esse módulo pode receber input de teclado e mouse.
 Somente esse módulo pode acessar o controlador de vídeo
 para enviar conteúdo para o lfb ou acessar o controlador de vídeo. 
