

// gramcc.h




// ## ARQUIVOS PARA TESTE ##

//#define STRING_CFILE "int main(){ return 1234; }\t"
//#define STRING_CFILE "\nint\nmain()\n{\n  return 0x1234;\n}\t\n //comment1  ... \n /* comment2 */ \n "
//#define STRING_CFILE "\nint\nmain()\n{\n  //This is a comment! \n \n /* This is another comment! */ \n return 0x1234;\n}\t\n  \n "
//#define STRING_CFILE "\nint\n test_Main()\n{\n  //This is a comment! \n \n /* This is another comment! */ \n return 0x1234;\n}\t\n  \n "

#define STRING_CFILE "int main(){\n"\
"    return 0x1234;                      \n"\
"};                                      \n"\
"    // this is a comment ...            \n"\
"    /* This is another comment ...  */  \n"\
"\t \n \n                                \n"


/*
char STRING_CFILE[] = "\n"
    "int \n"
    "main()\n"
    "{"
	"//comment1 \n"
	" comment2  \n"
    "    return 0x1234;\n"
    "} /\n"
    "\n";
*/


FILE *finput; 


// ## file support ##

#define INFILE_SIZE 512
#define OUTFILE_SIZE 512

char infile[INFILE_SIZE];
char outfile[OUTFILE_SIZE];

unsigned long infile_size;
unsigned long outfile_size;


// ## stack support ##


//#testando 
//Isso será a pilha para os argumentos ou expressões matemáticas.
char stack[512];

//xxx() if(((( ))))       ... tem que dar zero no final. 
int stack_count;
int stack_index;   //current index.
int stack_flag;    //aciona para sinalizar que devemos colocar o próximo elemento na pilha.
 

//#testando 
//informações sobre o identificador atual. Encontrado no momento.
#define ID_TOKEN 0 //qual é o token, deve ser sempre TOKENIDENTIFIER
#define ID_CLASS 1 //qual é a classe do identificador, se ele é uma var, string, struct, function, enum etc ...
#define ID_STACK_OFFSET 2  //armazenará o índice na pilha onde está o ideitividador 
#define ID_VALUE 3   // o valor armazenado na variável. 
#define ID_ADDRESS 4 //o endereço de memória referente ao ideitificador.Com base no endereço inicial da compilação.
#define ID_TYPE 5    // qual é o tipo de dado armazenado na variável, caso seja uma variável. Ou qual é o tipo de retorno da função.
//...
#define ID_CLASS_VAR       100
#define ID_CLASS_STRING    101
#define ID_CLASS_STRUCT    102
#define ID_CLASS_FUNCTION  103
#define ID_CLASS_ENUM      104
#define ID_CLASS_LABEL     105
//...
//8 elementos que explicam o identificador.
int id[8];


unsigned long program_header_address;
unsigned long program_text_address;
unsigned long program_data_address;
unsigned long program_bss_address;




//#debug
//flag para mostrar o arquivo em assembly.
int asm_flag;

//criar um simbolo
//ele pode ser de uma variável ou uma função...
//ele terá caracterrísticas

//
// # defines usados para simular arquivos #
//

// Arquivo em C.
//#define file_c "void main () { }"
//#define file_c "void main(){ return; }\t"
//#define file_c "void main(){ return; }\t"
//#define file_c "int main(){ return 1234; }\t"
//...


// Arquivo intermediário,
char file_i[512];

// Arquivo em assembly.
char file_s[512];


#define SYMBOLTYPE_FUNCTION           1
#define SYMBOLTYPE_FUNCTION_PROTOTYPE 2
#define SYMBOLTYPE_FUNCTION_EXTERN    3
#define SYMBOLTYPE_VARIABLE           4
#define SYMBOLTYPE_VARIABLE_EXTERN    5
#define SYMBOLTYPE_SCTRUCT            6
//...


//current tmp file.
char *temp_filename;

/* Length of the prefix.  */
int temp_filename_length;

/* Define the list of temporary files to delete.  */
struct temp_file
{
  char *name;
  struct temp_file *next;
};

struct temp_file *temp_file_queue;



//variável.
typedef struct variable_d variable_t;
struct variable_d
{
    int used;
    int magic;
    
};

//símbolos tipados.
//funções e variáveis.
typedef struct symbol_d sysmbol_t;
struct symbol_d
{
    int used;
    int magic;

	int id;
	
    int type;      // função ou variável ou protótipo ou extern.
    char *string;  // void, int, xxx, y ...
	
	
	//caso o simbolo seja uma função;
	struct function_d *function;
	
	//caso o símbolo seja uma variável.
	struct variable_d *variable;
};

//tipos
typedef struct type_d type_t;
struct type_d
{
    int used;
    int magic;

	int id;
	
    int type;
    char *string; // string que representa o tipo.	
};


#define FUNCTION_COUNT_MAX 32

unsigned long functionList[FUNCTION_COUNT_MAX];

int gramcc_main ( int argc, char *argv[] );


