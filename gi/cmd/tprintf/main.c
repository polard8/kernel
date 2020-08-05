/*
 * File: main.c 
 *
 * Descrição: 
 *     Arquivo principal de IDLE.BIN.
 *     IDLE.BIN é um processo com apenas uma thread.
 *     IDLE.BIN é um aplicativo de 32bit em user mode. 
 *
 *     Esse programa deverá ser chamado sempre que o sistema estiver ocioso,
 * ou com falta de opções viáveis. Então esse programa deve ficar responsável 
 * por alguma rotina de manutenção do equilíbrio de sitema, ou por gerência de 
 * energia, com o objetivo de poupar energia nesse momento de ociosidade.
 *
 * O processo idle pode solicitar que processos de gerencia de energia entrem em
 * atuação. Pois a chamada do processo idle em si já é um indicativo de ociosidade
 * do sistema. Pode-se também organizar bancos de dados, registros, memória, buffer,
 * cache etc.
 *
 *     O sistema pode configurar o que esse processo faz quando a máquina 
 * está em idle mode. Quando não há nenhum processo pra rodar ou a cpu se 
 * encontra ociosa, pode-se usar alguma rotina otimizada presente neste 
 * programa. Parece que a intel oferece sujestões pra esse caso, não sei.
 * 
 * Obs: O entry point está em head.s
 *      Agora idle pode fazer systemcalls. 
 *
 * @todo: Criar argumento de entrada.
 *
 * Histórico:
 *     Versão 1.0, 2015 - Esse arquivo foi criado por Fred Nora.
 *     Versão 1.0, 2016 - Revisão.
 *     ...
 */
 
 
//
// Includes.
// 

#include <ctype.h> 
#include <types.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>



//
// Variáveis internas.
//

//Idle application support.
int idleStatus;
int idleError;
//...

//Idle driver support.
int driverInitialized;
//...


/*
struct idle
{
	struct thread_d *current_idle_thread;
	//int
}
*/

//
// Protótipos.
//
int TEST_PRINTF(void);
int TEST_PRINTF2(void);
int TEST_PRINTF3(void);


/*
 * Reads a command line.
 */
static int readline(char *line, int length, FILE *stream)
{
	int fd;   /* File descriptor.                */
	int size; /* # of characters left in buffer. */
	char *p;  /* Write pointer.                  */

	fd = fileno(stream);
	size = length;
	p =  line;

    while (size > 0)
    {
		unsigned char ch;
		
		/* Nothing read. */
		//if (read(fd, &ch, 1) != 1)
			//return (-1);

        ch = fgetc(stream);

        if( ch==-1) exit(1);
        
        if( ch == '\n' ){ *p++ = '\n'; return ch; }

       *p++ = ch;
        
        size--;
    }
}



/*
 * INICIALIZAÇÃO GENÉRICA PARA TESTE DE APLICATIVO.
 */

int main (int argc, char *argv[]){

    //FILE *f;
    
    //f = fopen("create1.txt", "r+"); 
    //f = fopen("kstdin.txt", "r+");
    //stdout = f;

    //stdin é um arquivo normal, vamos escrever nele.
    //assim o terminal poderá ler o stdout.
    //stdout = f;
    printf("\n");
    printf("tprintf.bin: Initilizing ...\n\n");
    printf("prompt={%s}*hang\n",prompt);

    //get size.
    //fseek(stderr, 0, SEEK_END);   // seek to end of file
    //size_t size = ftell(stderr);  // get current file pointer
    //fseek(stderr, 0, SEEK_SET);   // seek back to beginning of file
    //printf (">>>> size %d \n",size);  

   int s =-1;
   
//loop:
    
    //printf("$: "); fflush(stdout);
    //fseek(stdin, 0, SEEK_SET);   
    //size_t size = ftell(stderr);
    //printf (">>>> size %d \n",size);
    //fseek(stdin, 0, SEEK_SET);   
    
    /*
    int i=0;
    for(i=0;i<10;i++){
        int c = getc(stdin);
        
        if (c != 0 || c != -1)
            printf("%c\n",c);
        
        if (c=='\n') 
            printf("N"); fflush(stdout); 
        
        if (c==0)
            printf("0"); fflush(stdout);
    };
    */
    
char char_buffer[2];
    char line_buffer[128];
    char *str;
    int ch=0;
    int i=0;
    int nreads = 0;
    
    fseek(stdin, 0, SEEK_SET); 
    
    char_buffer[0] = 0;
    line_buffer[0] = 0;
    
    while(1){

        fseek(stdin, 0, SEEK_SET); 
    
        //leia 1.
        nreads = read( fileno(stdin), line_buffer, 128);
    
        // Se não lemos o byte
        if (nreads > 0)
        {
            printf("Line={%s}",line_buffer); 
            printf("\n");
            fflush(stdout);
            
            if ( strncmp ( line_buffer, "exit", 4 ) == 0 )
            {
                exit(0);
            } 
            //...
        }
      };    
    

    //goto loop;
    while(1);



    //perror("Testing perror!\n");

	printf("\n");
	printf("===============\n");
	printf("Testando printf, printf nao tradicional\n");	
	TEST_PRINTF();

	//printf("\n");
	//printf("===============\n");
	//printf("Testando printf2, printf tradicional\n");	
	//TEST_PRINTF2();	 
	
	printf("\n");	
	printf("===============\n");
	printf("Testando printf3, printf tradicional \n");	
	TEST_PRINTF3();	 	
	
	printf("DONE.\n");	


    //close(fileno(f));
    
	return 0;
}




/*
 * TEST_PRINTF2:
 *     Essa função testa a função printf() e seus recursos.
 *     Obs: We can implement this test in user mode.
 * Obs:
 *     If you compile this file with
 *     gcc -Wall $(YOUR_C_OPTIONS) -DTEST_PRINTF -c printf.c
 * you will get a normal warning:
 *   printf.c:214: warning: spurious trailing `%' in format
 * this line is testing an invalid % at the end of the format string.
 *
 * this should display (on 32bit int machine) :
 *
 * Hello world!
 * printf test
 * (null) is null pointer
 * 5 = 5
 * -2147483647 = - max int
 * char a = 'a'
 * hex ff = ff
 * hex 00 = 00
 * signed -3 = unsigned 4294967293 = hex fffffffd
 * 0 message(s)
 * 0 message(s) with %
 * justif: "left      "
 * justif: "     right"
 *  3: 0003 zero padded
 *  3: 3    left justif.
 *  3:    3 right justif.
 * -3: -003 zero padded
 * -3: -3   left justif.
 * -3:   -3 right justif.
 *
 */
	
	
	
//testando 
//não tradicional, mas funciona.

int TEST_PRINTF (void){

    int mi;
    int i=5;
    unsigned int bs = sizeof(int)*8;

    char *np = 0;
    char *ptr = "Hello world!";
    char buf[128];


    mi = (1 << (bs-1)) + 1;



	printf ("%s\n", ptr);
	printf ("printf test\n");
	printf("%s is null pointer\n", np);
	printf("%d = 5\n", i);
	printf("%d = - max int\n", mi);
	printf("char %c = 'a'\n", 'a');
	printf("hex %x = ff\n", 0xff);
	printf("hex %02x = 00\n", 0);
	printf("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf("%d %s(s)%", 0, "message");
	printf("\n");
	printf("%d %s(s) with %%\n", 0, "message");

    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf("%s", buf);

    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf("%s", buf);

    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf("%s", buf);

    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf("%s", buf);

    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf("%s", buf);

    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf("%s", buf);

    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf("%s", buf);


    return 0;
}


/*
 * TEST_PRINTF:
 *     Essa função testa a função printf() e seus recursos.
 *     Obs: We can implement this test in user mode.
 * Obs:
 *     If you compile this file with
 *     gcc -Wall $(YOUR_C_OPTIONS) -DTEST_PRINTF -c printf.c
 * you will get a normal warning:
 *   printf.c:214: warning: spurious trailing `%' in format
 * this line is testing an invalid % at the end of the format string.
 *
 * this should display (on 32bit int machine) :
 *
 * Hello world!
 * printf test
 * (null) is null pointer
 * 5 = 5
 * -2147483647 = - max int
 * char a = 'a'
 * hex ff = ff
 * hex 00 = 00
 * signed -3 = unsigned 4294967293 = hex fffffffd
 * 0 message(s)
 * 0 message(s) with %
 * justif: "left      "
 * justif: "     right"
 *  3: 0003 zero padded
 *  3: 3    left justif.
 *  3:    3 right justif.
 * -3: -003 zero padded
 * -3: -3   left justif.
 * -3:   -3 right justif.
 *
 */
	
 //testando a tradicional, incompleta
//não funciona, estamos implementando. 
int TEST_PRINTF2(void)
{


	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf2("%s\n", ptr);
	printf2("printf test\n");
	printf2("%s is null pointer\n", np);
	printf2("%d = 5\n", i);
	printf2("%d = - max int\n", mi);
	printf2("char %c = 'a'\n", 'a');
	printf2("hex %x = ff\n", 0xff);
	
	/*
	//podemos cancelar esse teste
	printf2("hex %02x = 00\n", 0);
	
	printf2("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf2("%d %s(s)%", 0, "message");
	printf2("\n");
	printf2("%d %s(s) with %%\n", 0, "message");
	
    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf2("%s", buf);
	
    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf2("%s", buf);
	
    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf2("%s", buf);
	
    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf2("%s", buf);
	
    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf2("%s", buf);
	
    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf2("%s", buf);
	
    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf2("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf2("%s", buf);
    */

done:
	return (int) 0;
};



int TEST_PRINTF3 (void){

    int mi;
    int i = 5;
    unsigned int bs = sizeof(int)*8;

    char *np = 0;	
    char *ptr = "Hello world!";
    char buf[128];


    mi = (1 << (bs-1)) + 1;



	printf3 ("%s\n", ptr);
	printf3 (" _(string 1 2 3 4)_ \n");
	printf3 ("%s is null pointer\n", np);
	
	printf3("%d = 5\n", i);
	printf3("%d = - max int\n", mi);
	printf3("char %c = 'a'\n", 'a');
	printf3("hex %x = ff\n", 0xff);
	printf3("hex %02x = 00\n", 0);
	printf3("signed %d = unsigned %u = hex %x\n", -3, -3, -3);
	printf3("%d %s(s)%", 0, "message");
	printf3("\n");
	printf3("%d %s(s) with %%\n", 0, "message");
	
    sprintf(buf, "justif: \"%-10s\"\n", "left"); 
    printf3("%s", buf);
	
    sprintf(buf, "justif: \"%10s\"\n", "right"); 
    printf3("%s", buf);
	
    sprintf(buf, " 3: %04d zero padded\n", 3); 
    printf3("%s", buf);
	
    sprintf(buf, " 3: %-4d left justif.\n", 3); 
    printf3("%s", buf);
	
    sprintf(buf, " 3: %4d right justif.\n", 3); 
    printf3("%s", buf);
	
    sprintf(buf, "-3: %04d zero padded\n", -3); 
    printf3("%s", buf);
	
    sprintf(buf, "-3: %-4d left justif.\n", -3); 
    printf3("%s", buf);
	
    sprintf(buf, "-3: %4d right justif.\n", -3); 
    printf3("%s", buf);



    return 0;
}

//
// End.
//

