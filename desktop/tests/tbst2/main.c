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

struct node 
{
    int pre;	// + - = 2 ; * / = 4
	int key; 
	struct node *left, *right, *parent; 
}; 


// A utility function to create a new BST node 
struct node *newNode(int item, int pre, struct node *parent) 
{ 
	struct node *temp = (struct node *)malloc(sizeof(struct node)); 
	temp->key = item;
    temp->pre = pre;	
	temp->left = temp->right = NULL; 
	temp->parent = parent;
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


//Em ordem
void exibirEmOrdem(struct node *root){
    if(root != NULL){
        exibirEmOrdem(root->left);
        printf("%c{%d} ", root->key, root->pre );
        exibirEmOrdem(root->right);
    }
}



//Pré-ordem
void exibirPreOrdem(struct node *root){
    if(root != NULL){
        printf("%c{%d} ", root->key, root->pre );
        exibirPreOrdem(root->left);
        exibirPreOrdem(root->right);
    }
}


//Pós-ordem
void exibirPosOrdem(struct node *root){
    if(root != NULL){
        exibirPosOrdem(root->left);
        exibirPosOrdem(root->right);
        printf("%c{%d} ", root->key, root->pre );
    }
}


//stack
int key_saved;

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key, int pre, struct node *parent) 
{ 
	/* If the tree is empty, return a new node */
	if (node == NULL) 
        return newNode(key, pre, parent); 

    //if (parent == NULL) 
	//    return newNode(key, pre, parent); 
	
	//#test
    //while ( node->pre > pre )
	//        node = node->parent;

    //if(key == '=')
    //{
	//    node = node->parent;	
	//}		

    //#test
	//right - como se fosse maior
	//if(key == '+' || key == '-' || key == '*' || key == '/')
    //{
	
        //while ( node->pre > pre )
	    //    node = node->parent;	
		
		//node = node->parent;
		
	//	node->right = insert( node->right, key, pre, parent );
	//    return node;
	//}
	
	//#test
	//
	//if(x >= '0' && x <= '9')
	//{
	//    node->key = key;
    //    return node;		
	//}
	
	
	/* Otherwise, recur down the tree */
	if (key < node->key)
	{ 		
		node->left = insert ( node->left, key, pre, parent ); 
	
	}else if (key > node->key){
	
		node->right = insert( node->right, key, pre, parent ); 
    };
	
	/* return the (unchanged) node pointer */
	return node; 
} 


// Devolve o altura de um nóh em uma árvore binária.

int height(struct node *h) {

    int u, v;
	
    if (h == NULL) 
		return -1;
    
	u = height(h->left);
    v = height(h->right);
    
	if (u > v)
    {		
	    return u+1;
	}else{ 
		return v+1;
	};
};

/*
void printnode(char c, int b) {
    int i;
    for (i = 0; i < b; i++) printf("   ");
    printf("%c\n", c);
}
void show (struct node *x, int b){
    
	if (x == NULL) 
	{
        printnode('*', b);
        return;
    }
    
	show ( x->right, b+1);    
    printnode(x->key, b);
    show (x->left, b+1);    
};
*/

//mov eax, 0
//add a, b
//add b, a 


unsigned long resolve_expressao(struct node *root)
{
	unsigned long resultado;
	
	if(root == NULL )
		return 0;
	
	switch(root->key)
	{
		case '*':
		    resultado = (unsigned long) ( resolve_expressao(root->left) * resolve_expressao(root->left) ); 
	        break;
			
		case '/':
		    resultado = (unsigned long) ( resolve_expressao(root->left) / resolve_expressao(root->left) ); 
	        break;
			
		case '+':
		    resultado = (unsigned long) ( resolve_expressao(root->left) + resolve_expressao(root->left) ); 
	        break;
			
		case '-':
		    resultado = (unsigned long) ( resolve_expressao(root->left) - resolve_expressao(root->left) ); 
	        break;
			
		default:
		    resultado = (unsigned long) root->key;
		    break;
	};   
	
	return resultado;
};
 

// Driver Program to test above functions 
// C program to demonstrate insert operation in binary search tree 
int bst_main() 
{ 
	/* Let us create following BST 
           50 
          /  \ 
        30    70 
        / \   / \ 
       20 40 60 80 */
	
	struct node *root = NULL; 
	struct node *rootsave;
	struct node *current = NULL; 	
	
	root    = insert(root, (int) '1', 2, NULL ); 
	current = insert(root, (int) '+', 2, root->parent);
	current = insert(root, (int) '2', 2, current->parent); 
	current = insert(root, (int) '-', 2, current->parent); 
	current = insert(root, (int) '3', 2, current->parent); 
	current = insert(root, (int) '*', 4, current->parent); 
	current = insert(root, (int) '4', 2, current->parent); 
    current = insert(root, (int) '/', 4, current->parent);
	current = insert(root, (int) '5', 2, current->parent);
	//current = insert(root, (int) 'f', 2, current->parent);
	
	int Height = (int) height(current);
	
	// print inoder traversal of the BST 
	//inorder(root); 
	
	printf("\n\n");
	//printf("[1 + 2 * 3 + 4]");
	//printf("[a / b]");
	printf("\n\n");
	
	printf("\n\n em ordem: \n");
	exibirEmOrdem(root);
	
	printf("\n\n pre ordem: \n");
	exibirPreOrdem(root);
	
	printf("\n\n pos ordem: \n");
	exibirPosOrdem(root);

	printf("\n\n");
	
	//#test
	//printf("last item height %d \n",Height);
	unsigned long r =  resolve_expressao(root);
	printf("EXP={%d}",r );
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

