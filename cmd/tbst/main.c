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
 
#include <types.h>
#include <stddef.h>


//#importante
//presizamos só disso.
#include <stdlib.h>
#include <stdio.h>   


#include <ctype.h>
#include "api.h"      //api.
#include "tprintf.h" 


//===============================================================================

///buffer pra fazer conta usando pos order
int POS_BUFFER[32];

int buffer_offset = 0;


//===============================================================================

struct node 
{ 
	int key; 
	struct node *left, *right; 
}; 

// A utility function to create a new BST node 
struct node *newNode(int item) 
{ 
	struct node *temp = (struct node *)malloc(sizeof(struct node)); 
	temp->key = item; 
	temp->left = temp->right = NULL; 
	return temp; 
} 

// A utility function to do inorder traversal of BST 
void inorder(struct node *root) 
{ 
	if (root != NULL) 
	{ 
		inorder(root->left); 
		printf("%d \n", root->key); 
		inorder(root->right); 
	} 
} 


//Em ordem  a+b
//desce até o último pela esquerda, não havendo esquerda vai pra direita.
void exibirEmOrdem (struct node *root){
	
    if (root != NULL)
	{
		//visita a esquerda do próximo
		//só retorna no último então printf funciona 
		//mostrando o conteúdo do último 
		//ai visita a direita do último e desce pela esquerda,
		//não havendo esquerda vai pra direita.
        exibirEmOrdem (root->left);
        printf("%d ", root->key);
        
		exibirEmOrdem (root->right);
    }
};



//Pré-ordem  +ab
void exibirPreOrdem (struct node *root){
    
	if (root != NULL)
	{
        //imprime o conteúdo
		//desce até o último pela esquerda
		//visita a direita e desce até o último pela esquerda.
		printf("%d ", root->key);
        exibirPreOrdem(root->left);
        exibirPreOrdem(root->right);
    }
};


//Pós-ordem ab+
void exibirPosOrdem (struct node *root){
	
	//#importante
	//exibe em níveis. de baixo para cima.
    
	if (root != NULL)
	{
		//desce até o ultimo pela esquerda
		//visita o da direita e imprime;
        exibirPosOrdem(root->left);
        exibirPosOrdem(root->right);
		printf("%d ", root->key);
		
		if(buffer_offset<0 || buffer_offset >32)
		{
			printf("*buffer fail\n");
			return;
		}
		//colocar num buffer pra usar no cálculo 
		//isso simula uma digitação
		POS_BUFFER[buffer_offset] = (int) (root->key + '0');
		buffer_offset++;
		
		
    };
};


/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key) 
{ 
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key); 

	/* Otherwise, recur down the tree */
	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 

	/* return the (unchanged) node pointer */
	return node; 
} 



/*
 *********************************************************
 *
 */
// Driver Program to test above functions 
// C program to demonstrate insert operation in binary search tree 

int bst_main (){
	
	
	buffer_offset = 0;
	
	/* Let us create following BST 
           * 
          /  \ 
         +     - 
        / \   / \ 
       20 40 60 80 */
	
	struct node *root = NULL; 
	
	
	//4+3 - 2*5 = 12
	
	//insert 111
	root = insert ( root, '?' ); //3 

	insert(root, '+'); //
	insert(root, '-'); //
	insert(root, '*'); //
	
	insert(root, 5);   // 
	insert(root, 2);   //	
	insert(root, 3);   // 
	insert(root, 4);   //	
	
	//insert(root, '+'); //2
	//insert(root, '*'); //1
	
	//insert(root, 4); //d
	//insert(root, 3); //c
	//insert(root, 2); //b 
	//insert(root, 1); //a 	


	
	
	//insert(root, '+'); 
	//insert(root, 2); 
	//insert(root, 5); 

	// print inoder traversal of the BST 
	//inorder(root); 
	
	//printf("\n\n");
	//printf("[1 + 2 * 3 - 4]");
	//printf("\n\n");
	
	printf("\n\n em ordem: \n");
	exibirEmOrdem(root);
	
	printf("\n\n pre ordem: \n");
	exibirPreOrdem(root);
	
	printf("\n\n pos ordem: \n");
	exibirPosOrdem(root);

	printf("\n\n");
	
	return 0; 
}; 


//===============================================================================




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

void idleLoop();
void driverInitialize();      // processo sendo considerado um driver servidor.
void driverUninitialize();    // desinicializa.
int idleInit();               // processo sendo consideredo cliente.
unsigned long idleServices(unsigned long number);  //Principal.
//...




//Another loop.
void idleLoop(){
    while(1){}	
};

 




/*
 * driverInitialize:
 *     O Kernel solicitou a rotina de inicialização do processo Idle na forma 
 * de driver. Faremos uma chamada ao Kernel dizendo que o driver está 
 * inicializado. Na chamada passaremos alguns parâmetros, como: O número do 
 * serviço, 129 e o código de confirmação, 1234. 4321.
 *
 */
void driverInitialize()
{
	//printf("Idle: Initializing driver ...\n");
	//refresh_screen();

	driverInitialized = 1;	
	//system_call( 129, 4321, 4321, 4321 );	
	
done:	
	printf("IDLE.BIN: Initialized.\n");
	refresh_screen();
	return;
};


/*
 * driverUninitialize:
 *     This method is called to uninitialize the driver object. In a real 
 * driver, this is where the driver would clean up any resources held by 
 * this driver. (m$)
 */
void driverUninitialize()
{
	//
	// Dúvidas??
	// Devemos nos preparar para desinicializar o driver.
	// Desalocaremos os recursos usadados pelo driver, como memória, 
	// arquivos abertos ...
	// Obs: Não sei se atribuição do próprio driver liberar os recursos.
	// Mas de toda forma, no mínimo devemos avisar o Kernel que os recursos 
	// não são mais necessários.
	// @todo: Podemos enviar um comando para o kernel pedindo pra que ele não 
	// link esse driver ao sistema, ou que deixe ele não inicializado.
	//

	//printf("Idle: Unitializing driver ...\n");
	//refresh_screen();

	driverInitialized = 0;	
	
	//Faremos uma chamada para o Kernel 'deslinkar' o driver.
	//talvez 128. 127 126..???
	//system_call( ?? , 4321, 4321, 4321 ); 		
	
done:	
	printf("IDLE.BIN: Uninitialized.\n");
	refresh_screen();
	return;
};


/*
 * idleInit:
 *     Inicializando a aplicação Idle.
 */
int idleInit()
{
	idleStatus = 0;
	idleError = 0;
	
	//printf("Idle: Initializing idle application ..\n");
	//refresh_screen();
	//...
	return (int) 0;
};


/*
 *****************************************************************************
 * idleServices:
 *     Essa função oferece serviços de acordo com o número passado via 
 * argumento.
 * Essa deve ficar por último e ter acesso à qualquer rotina acima ou em
 * bibliotecas incluídas.
 */
unsigned long idleServices(unsigned long number)
{
    // Checar se o driver está inicializado.
	if(driverInitialized != 1){
		return (unsigned long) 1;    //erro
	}
	
	
	//
	// Selecionar o serviço.
	//
	
    switch(number)
    {
		case 0:
		    printf("Idle Driver: NULL service.\n");
		    idleLoop();
			break;
			
		case 1:
		    printf("Idle Driver: service 1.\n");
		    //idleLoop();
			break;

        //...			
		
		default:
		    printf("Idle Driver: default service.\n");        
			//idleLoop();
			break;
	};	
	
	
done:
    refresh_screen(); 
    return (unsigned long) 0;	
};

struct stack
{
	int top;
    int items[32];
};


void push(struct stack *s,int x)
{
    if ( s->top > 32 )
    {
		printf("Stack Overflow…!\n");
        return;
    }else{
		s->items[ ++s->top ]=x;
    }
};

int pop (struct stack *s)
{
    //if ( s->top < 0)
    if ( s->top == -1)
	{
		printf("Stack Underflow…!\n");
        return 0;
    }else{
		
		return ( s->items[ s->top-- ] );
    }
};


int oper(char c,int opnd1,int opnd2)
{
	//printf("oper: %c\n");
	
    switch (c)
    {
		
		//case '*': 
        case 90:  		
		    return (opnd1*opnd2);
			
        //case '+': 
		case 91:    
			return(opnd1+opnd2);        		
			
		//case '-': 
		case 93:
		    return(opnd1-opnd2);
			
		//case '/': 
		case 95:
		    return(opnd1/opnd2);
        
		//#todo
		case '^': 
		    return 0; //return(pow(opnd1,opnd2));
        
		default: 
		    printf("oper: Invalid operator…! %d\n", c);
			return 0;
    }
};

int my_isdigit(char ch){
	
    return(ch>='0' && ch<='9');
}


int eval ( int *str ){
	
    char c;
    int opnd1, opnd2, val;
    
	struct stack stk;
    
	stk.top = -1;
	//stk.top = 0;
	
	
    printf("\n eval:\n");	

	int i;
	
    //for ( i=0; (c = str[i]) != '?'; i++ )
    for ( i=0; (c = str[i]) != 111; i++ )		
    {

		if ( c>='0' && c<='9' )
		{
            push ( &stk, (int)( c - '0' ) );
        
		}else{
            
			//O problema é a ordem em que os operandos aparecem 
			//o último é a raiz.
			//e aqui a o operando raiz aparece no meio da expressão.
			
			opnd2 = pop (&stk);
            opnd1 = pop (&stk);
			
            val = oper ( c, opnd1, opnd2 );
            
			push ( &stk, val );
        }
    }
	
	//o resultado é o que sobrou na pilha
    return ( pop(&stk) );
}


/*
 ==================================================================================
 * iNICIALIZAÇÃO GENÉRICA PARA TESTE DE APLICATIVO.
 */

int testtest_main (){
	
	printf("\n");
	printf("Initilizing TBST.BIN ...\n\n");
	
	
    libcInitRT();
    stdioInitialize();		

	bst_main(); 
	
	//finalizador
	POS_BUFFER[buffer_offset] = '?';
		
	int i;
	
	int max = buffer_offset;
	
	
	printf("\n the pos order is: "); 
	if(max >32 || max <=0)
		printf("max fail");
	
	for (i=0; i<max; i++)
	{
		printf("%d ",POS_BUFFER[i]);
	}
    
	
    printf ("\n \n Result after evaluation is: %d \n", eval ( (int*) &POS_BUFFER[0] ) );	
	 
	 
	/*
	if ( isxdigit('a') )
	{
		printf("isxdigit a\n");
	}
	
	if ( isxdigit('f') )
	{
		printf("isxdigit f\n");
	}

	if ( isxdigit('0') )
	{
		printf("isxdigit 0\n");
	}

	if ( isxdigit('9') )
	{
		printf("isxdigit 9\n");
	}	
	*/
	
	
	/*
	if ( isalpha('a') )
	{
		printf("isalpha a\n");
	}
	
	if ( isalpha('z') )
	{
		printf("isalpha z\n");
	}

	if ( isalpha('A') )
	{
		printf("isalpha A\n");
	}

	if ( isalpha('Z') )
	{
		printf("isalpha Z\n");
	}	
	*/
	
	//isalnum(int c)
	
	/*
	if ( isalnum('a') )
	{
		printf("isalnum a\n");
	}
	
	if ( isalnum('z') )
	{
		printf("isalnum z\n");
	}

	if ( isalnum('0') )
	{
		printf("isalnum 0\n");
	}

	if ( isalnum('9') )
	{
		printf("isalnum 9\n");
	}
	*/
	
	//#todo 
	//vamos fazer rotinas de teste nas funções 
	//de ctype.h na libc do Gramado 0.4
	
	

	
	
	/*
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

    */ 	
	
	printf("DONE.");	
	refresh_screen();
	return 0;
};




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

int TEST_PRINTF(void)
{


	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf("%s\n", ptr);
	printf("printf test\n");
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


done:
	return (int) 0;
};



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



int TEST_PRINTF3(void)
{


	
	int mi;
	int i = 5;
	unsigned int bs = sizeof(int)*8;

	char *np = 0;	
	char *ptr = "Hello world!";
	char buf[80];
	
	

	mi = (1 << (bs-1)) + 1;
	
//	vsync();
	
	printf3("%s\n", ptr);
	printf3(" _(string 1 2 3 4)_ \n");
	printf3("%s is null pointer\n", np);
	
	
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

done:
	return (int) 0;
};


//
// End.
//

