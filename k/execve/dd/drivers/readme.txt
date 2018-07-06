
 Sobre o diretório \drivers:
 ==========================

   Os drivers aqui no kernel base são simples.
   Oferecem rotinas primárias para os dispositivos
   mais tradicionais.
   
   Cada driver também oferece acesso ao driver 
   correspondente em user mode. se esse existir.

   O handler de interrupção que estiver aqui pode ser mudado
   pra dentro do driver em user mode se esse existir.   

   * É necessário para fims de portabilidade algum tipo de abstração e
     encapsulamento.

    manter-se o mais local possível.

   fim.