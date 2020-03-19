/*
 * File: main.c 
 *
 * tbst - calculando expressões. isso deu certo.
 *     ...
 */
 
 
//
// Includes.
//      

#include "tbst.h" 


//===============================================================================

//buffer pra fazer conta usando pos order
int POS_BUFFER[32];

int buffer_offset = 0;

//===============================================================================



 
//
//  ## STACK ##
//

struct stack
{
	int top;
    int items[32];
};



struct node 
{ 
	int key; 
	struct node *left, *right; 
}; 


int my_isdigit(char ch){
	
    return(ch>='0' && ch<='9');
};


// A utility function to create a new BST node 
struct node *newNode (int item){
	
	struct node *temp = (struct node *)malloc ( sizeof(struct node) );
    
	//#todo: check validation
	
	temp->key = item; 
	temp->left = temp->right = NULL;
	
	return temp; 
}; 


// A utility function to do inorder traversal of BST 
void inorder (struct node *root){
	
	if (root != NULL) 
	{ 
		inorder(root->left); 
		printf("%d \n", root->key); 
		inorder(root->right); 
	} 
}; 


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
		
		//
		//  ## IMPORTANTE ##
		//
		
		//colocar num buffer pra usar no cálculo 
		//isso simula uma digitação
		POS_BUFFER[buffer_offset] = (int) (root->key + '0');
		buffer_offset++;
    };
};


/* A utility function to insert a new node with given key in BST */
struct node* insert ( struct node* node, int key ){
	
	/* If the tree is empty, return a new node */
	if (node == NULL) 
        return newNode(key); 

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

	/* Let us create following BST 
           - 
          /  \ 
         +     * 
        / \   / \ 
       4   3 2   5 */
	   
	   //4+3 - 2*5 = 12
	
int bst_main (){
	
	
	printf("bst_main:\n");
	
	buffer_offset = 0;
		
	struct node *root = NULL; 
	
	int i;
	int buffer1[32];
	int buffer2[32];
	
	int buffer1_offset = 0;
	int buffer2_offset = 0;
	
    ///int exp[] = { 4, '+', 3, '-', 2, '*', 5, '?'+'0' };
    //int exp[] = { 4, '+', 3, '-', 2, '*', 5, 111 };	
    int exp[] = { 4, '+', 3, '-', 2, '*', 5, '?' };	
	
	int c;
	
	printf("for\n");
    
	//colocamos nos buffers em ordem.
	for ( i=0; (c = exp[i]) != '?'; i++ )		
    {
		if ( c>= 0 && c<= 9 )
		{
			printf(">");
			
			//dígito
			buffer1[buffer1_offset] = (int) c;
            buffer1_offset++; 
			
		}else{
            
			printf("$");
			//operadores.
			buffer2[buffer2_offset] = (int) c;
			buffer2_offset++;
        }
    };
	
	
	//
	//visualizar os buffer,
	//pra depois nmanipular eles.
	buffer1[buffer1_offset] = (int) '?';
	buffer2[buffer2_offset] = (int) '?';
	
	//==========================================================================
	// #todo: NESSA HORA TEM QUE AJUSTAR A PRECEDÊNCIA DOS OPERADORES ## 
	// 
	//
	
	//inserindo root.
	root = insert ( root, '?' ); 
	

	//operadores +-*
	for ( i=0; (c = buffer2[i]) != '?'; i++ )
	{
		//if ( c>= 0 && c<= 9 )
		//{
		//	printf ("%d", c);
		//	continue;
		//}
		printf ("%c", c);
		insert ( root, buffer2[i] ); 		
	}
	
    buffer1_offset--;//ajustando par ao último válido 
	
	//for ( i=0; (c = buffer1[i]) != '?'; i++ )
	for ( i=buffer1_offset; (c = buffer1[i]); i-- )	
	{
		c = buffer1[i];//redundante
		
		if ( c>= 0 && c<= 9 )
		{
			printf ("%d", c);
			insert ( root, c );
            			
			//continue;
		}
		//printf ("%c", c);
	}	

	
	//#OK 
	//nos buffers estão na mesma ordem que na expressão.
	//agora vamos inserir na ordem inversa dos buffers.
	
	// ### root ##
	//insert 111. 
	// É um finalizador, representa o igual
	//depois vamos usar o igual =
	// x = 4+3 - 2*5
	//root = insert ( root, '?' ); 	
	//os operadores precisar sem inseridos na ordem da expressão.
	//insert(root, '+'); //
	//insert(root, '-'); //
	//insert(root, '*'); //
	//insert(root, 5);   // 
	//insert(root, 2);   //	
	//insert(root, 3);   // 
	//insert(root, 4);   //	
	
 
    // ??
	// print inoder traversal of the BST 
	// inorder(root); 
		
	printf("\n\n em ordem: ");
	exibirEmOrdem(root);
	
	printf("\n\n pre ordem: ");
	exibirPreOrdem(root);
	
	printf("\n\n pos ordem: ");
	exibirPosOrdem(root);

	printf("\n\n");
	
	return 0; 
}; 


//===============================================================================


void push ( struct stack *s, int x ){
	
    if ( s->top > 32 )
    {
		printf("Stack Overflow…!\n");
        return;
		
    }else{
		
		s->items[ ++s->top ] = x;
    }
};


int pop (struct stack *s){
	
    if ( s->top == -1)
	{
		printf("Stack Underflow…!\n");
        return 0; //??
		
    }else{
		
		return ( s->items[ s->top-- ] );
    };
};


int oper(char c,int opnd1,int opnd2){
	
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
    };
};


int eval ( int *str ){
	
    int i;
    int opnd1, opnd2, val;
	char c;
	
	struct stack stk;
    
	stk.top = -1;
	
    printf("\n eval:\n");	
	
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

	int i;	
	int max;
	
	printf("\n");
	printf("Initilizing TBST.BIN ...\n\n");
	
	
    libcInitRT();
    stdioInitialize();		

	bst_main(); 
	
	//finalizador
	POS_BUFFER[buffer_offset] = '?';	
	
	max = buffer_offset;
	
	printf("\n the pos order is: "); 
	if(max >32 || max <=0)
		printf("max fail");
	
	for (i=0; i<max; i++)
	{
		printf("%d ",POS_BUFFER[i]);
	}
    
    printf ("\n \n Result after evaluation is: %d \n", eval ( (int*) &POS_BUFFER[0] ) );	
	
	printf("DONE!");	
	
	
	//refresh_screen();
	return 0;
};


//
// End.
//

