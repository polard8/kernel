
// libvt.h


//#define TAB_SIZE 8

struct terminal_line
{
    char CHARS[80];
    char ATTRIBUTES[80];
	
	//início e fim da string dentro da linha.
	//o resto é espaço.
	int left;
	int right;
	
	//posição do cursor dentro da linha.
	int pos;
};

