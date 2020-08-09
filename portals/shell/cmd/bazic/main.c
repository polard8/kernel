
// bazic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MEM_SIZE	1024
#define VAR_START	(MEM_SIZE / 2)
#define MAX_STRING_SIZE 128


static unsigned char memory[MEM_SIZE];
static unsigned char *programEnd;
static unsigned char *variables;
static unsigned char *variablesEnd;

typedef struct {
    unsigned short num;
    unsigned short len;
} ProgramLine;

typedef struct {
    char *name;
    unsigned char tok;
} Token;

enum {
    VAL_END = 0,
    VAL_INT,
    VAL_FLOAT,
    VAL_STRING,
    VAL_UNKNOWN
};

typedef struct {
    int	type;
    int	valInt;
    float valFloat;
    // string
    char *valStr;
    unsigned int length;
} Value;


static void dumpData(unsigned char *data, int len)
{
    int i = 0;
    unsigned char buf[17];

    memset(buf, 0, sizeof(buf));

    while (len--) {
	fprintf(stderr, "%02X ", data[i]);
	buf[i % 16] = (data[i] > 0x20 && data[i] < 0x80) ? data[i] : '.';
	if (i > 0 && i % 16 == 15) {
	    fprintf(stderr, "  %s\n", buf);
	    memset(buf, 0, sizeof(buf));
	}
	i++;
    }

    i = (15 - i % 16 + 1) * 3 + 2;
    while (i--) {
	fprintf(stderr, " ");
    }

    fprintf(stderr, "%s\n", buf);

    fprintf(stderr, "\n");
}

void PutChar(char c)
{
    putchar(c);
}

void PutString(char *s)
{
    puts(s);
}

enum {
    T_ABS = 0x80,
    T_PRINT,
    T_END,
    T_EQU,
    T_LT,
    T_LE,
    T_GT,
    T_GE,
    T_NEQ,
    T_PLUS,
    T_MINUS,
    T_MUL,
    T_DIV,
    T_MOD,
    T_LSHIFT,
    T_RSHIFT,
    T_LBRACKET,
    T_RBRACKET,
    T_COLON,
    T_COMMA,
    T_SEMICOLON,
    T_DOLLAR,
};

static const Token tokenz[] = {
    { "abs"	, T_ABS		},
    { "print"	, T_PRINT	},
    { "end"	, T_END		},
    { "="	, T_EQU		},
    { "<"	, T_LT		},
    { "<="	, T_LE		},
    { ">"	, T_GT		},
    { ">="	, T_GE		},
    { "<>"	, T_NEQ		},
    { "+"	, T_PLUS	},
    { "-"	, T_MINUS	},
    { "*"	, T_MUL		},
    { "/"	, T_DIV		},
    { "%"	, T_MOD		},
    { "<<"	, T_LSHIFT	},
    { ">>"	, T_RSHIFT	},
    { "("	, T_LBRACKET	},
    { ")"	, T_RBRACKET	},
    { ":"	, T_COLON	},
    { ","	, T_COMMA	},
    { ";"	, T_SEMICOLON	},
    { "$"	, T_DOLLAR	},
};

static int findToken(char *tok, int len)
{
    int i;
    for (i = 0; i < sizeof(tokenz) / sizeof(Token); i++) {
	if (!strncmp(tokenz[i].name, tok, len) && (strlen(tokenz[i].name) == len)) {
	    return tokenz[i].tok;
	}
    }

    return -1;
}

static char *findTokenName(unsigned char tok)
{
    int i;
    for (i = 0; i < sizeof(tokenz) / sizeof(Token); i++) {
	if (tokenz[i].tok == tok) {
	    return tokenz[i].name;
	}
    }

    return NULL;
}

static int deTokenized(unsigned char *tokStr, int len)
{
    while (len--) {
	if (*tokStr == 0xff) {
	    int len = *++tokStr;
	    printf("\"");
	    while (len--) {
		printf("%c", *++tokStr);
	    }
	    printf("\"");
	    tokStr++;
	} else if (*tokStr >= 0x80) {
	    char *name = findTokenName(*tokStr++);
	    if (name) {
		printf(" %s ", name);
	    } else {
		printf(" ???");
	    }
	} else {
	    printf("%c", *tokStr++);
	}
    }

    printf("\n");

    return 0;
}

static unsigned char *findVariable(char *var)
{
    unsigned char *ptr = variables;

    while (*ptr) {
	if (*ptr == VAL_INT || *ptr == VAL_FLOAT || *ptr == VAL_STRING) {
	    if ((strlen(var) == ptr[1]) &&
		!strncmp(var, (char *)&ptr[2], ptr[1])) {
		return ptr;
	    }
	}
	if (*ptr == VAL_STRING) {
	    ptr += 1 + 1 + ptr[1];
	    ptr += 1 + ptr[0];
	} else {
	    ptr += 1 + 1 + ptr[1] + 4; // val_type + name length + name + value (int/float = 4 bytes);
	}
    }

    return NULL;
}

static int setVariable(char *var, Value *val)
{
    int newVar = 0;
    unsigned char *ptr = findVariable(var);

    if (ptr) {
	if (val->type == VAL_STRING || *ptr == VAL_STRING) {
	    unsigned char *ptr1 = ptr + 1 + 1 + ptr[1]; // type + varlen + varname;
	    if (*ptr != VAL_STRING) {
		ptr1 += 4; // int/float 4 bytes
	    } else {
		ptr1 += 1 + ptr1[0]; // strlen + string
	    }
	    int len = variablesEnd - ptr1;
	    memmove(ptr, ptr1, len);
	    variablesEnd -= (ptr1 - ptr);
	    ptr = NULL;
	} else {
	    *ptr = val->type;
	    ptr += 1 + 1 + ptr[1];
	}
    }

    if (!ptr) {
	newVar = 1;
	ptr = variablesEnd;
	*ptr++ = val->type;
	*ptr++ = strlen(var);
	memcpy(ptr, var, strlen(var));
	ptr += strlen(var);
    }

    if (val->type == VAL_STRING) {
	*ptr++ = val->length;
	memcpy(ptr, val->valStr, val->length);
	ptr += val->length;
    } else {
	unsigned char *tmp1;
	if (val->type == VAL_INT) {
	    tmp1 = (unsigned char *)&val->valInt;
	} else if (val->type == VAL_FLOAT) {
	    tmp1 = (unsigned char *)&val->valFloat;
	}

	*ptr++ = tmp1[0];
	*ptr++ = tmp1[1];
	*ptr++ = tmp1[2];
	*ptr++ = tmp1[3];
    }

    if (newVar) {
	variablesEnd = ptr;
    }

    dumpData(variables, variablesEnd - variables);

    return 0;
}

static int getVariable(char *var, Value *val)
{
    unsigned char *ptr = findVariable(var);
    if (ptr) {
	unsigned char *tmp1;
	val->type = *ptr;
	ptr += 1 + 1 + ptr[1];
	if (val->type == VAL_INT) {
	    tmp1 = (unsigned char *)&val->valInt;
	} else if (val->type == VAL_FLOAT) {
	    tmp1 = (unsigned char *)&val->valFloat;
	}
	tmp1[0] = *ptr++;
	tmp1[1] = *ptr++;
	tmp1[2] = *ptr++;
	tmp1[3] = *ptr++;
    } else {
	val->type = VAL_INT;
	val->valInt = 0;
    }

    return 0;
}

static int expr_data(unsigned char **str, Value *val)
{
    char num = 0;
    char dot = 0;
    char alpha = 0;
    char floatnum = 0;
    int type = VAL_UNKNOWN;

    char tmp[16];
    char *ptr = tmp;

    while (*(*str) && *(*str) < 0x80) {
	if ((*(*str) == 'E' || (*(*str) == 'e')) && !floatnum && !alpha && num > 0 && dot < 2) {
	    *ptr++ = *(*str)++;
	    if (!*(*str)) {
		continue;
	    }
	    if (*(*str) == T_PLUS || *(*str) == T_MINUS || isdigit(*(*str))) {
		if (*(*str) == T_PLUS) {
		    *ptr++ = '+';
		    (*str)++;
		} else if (*(*str) == T_MINUS) {
		    *ptr++ = '-';
		    (*str)++;
		} else {
		    *ptr++ = *(*str)++;
		    num++;
		}
		floatnum++;
		alpha++;
		continue;
	    }
	}
	if (isdigit(*(*str))) {
	    num++;
	}
	if (isalpha(*(*str))) {
	    alpha++;
	}
	if (*(*str) == '.' && !alpha) {
	    dot++;
	}
	*ptr++ = *(*str)++;
    }
    *ptr = 0;
    if ((floatnum && alpha == 1 && dot < 2) || (dot == 1 && num && !alpha)) {
	type = VAL_FLOAT;
    } else if (num && !alpha && !dot) {
	type = VAL_INT;
    }
#ifdef DEBUG
    fprintf(stderr, "num=%d, dot=%d, alpha=%d, floatnum=%d\n", num, dot, alpha, floatnum);
    fprintf(stderr, "data %s (type %d)\n", tmp, type);
#endif

    val->type = type;
    if (type == VAL_INT) {
	val->valInt = strtol(tmp, NULL, 0);
#ifdef DEBUG
	fprintf(stderr, "valInt = %d\n", val->valInt);
#endif
    } else if (type == VAL_FLOAT) {
	val->valFloat = strtof(tmp, NULL);
#ifdef DEBUG
	fprintf(stderr, "valFloat = %f\n", val->valFloat);
#endif
    } else {
	getVariable(tmp, val);
    }

    return 0;
}

static int getValType(Value *r, Value *l)
{
    if (r->type == VAL_FLOAT || l->type == VAL_FLOAT) {
	if (r->type == VAL_INT) {
	    r->type = VAL_FLOAT;
	    r->valFloat = r->valInt;
	}
	if (l->type == VAL_INT) {
	    l->type = VAL_FLOAT;
	    l->valFloat = l->valInt;
	}
	return VAL_FLOAT;
    }
    return VAL_INT;
}

static int expr1(unsigned char **str, Value *val);
static int expr2(unsigned char **str, Value *val);
static int expr3(unsigned char **str, Value *val);
static int expr4(unsigned char **str, Value *val);
static int expr5(unsigned char **str, Value *ret);

static int expr(unsigned char **str, Value *ret)
{
    expr1(str, ret);

    return 0;
}

static int expr1(unsigned char **str, Value *ret)
{
    Value val;
    Value val2;
    unsigned char tok;

    expr2(str, &val);

    while ((tok = *(*str))) {
	if (tok != T_EQU && tok != T_NEQ &&
	    tok != T_LT && tok != T_LE &&
	    tok != T_GT && tok != T_GT) {
	    break;
	}
	(*str)++;
	expr2(str, &val2);
	int type = getValType(&val, &val2);
	if (tok == T_EQU) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt == val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat == val2.valFloat;
	    }
	} else if (tok == T_NEQ) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt != val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat != val2.valFloat;
	    }
	} else if (tok == T_LT) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt < val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat < val2.valFloat;
	    }
	} else if (tok == T_LE) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt <= val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat <= val2.valFloat;
	    }
	} else if (tok == T_GT) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt > val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat > val2.valFloat;
	    }
	} else {
	    if (type == VAL_INT) {
		val.valInt = val.valInt >= val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat >= val2.valFloat;
	    }
	}
    }

    ret->type = val.type;
    ret->valInt = val.valInt;
    ret->valFloat = val.valFloat;

    return 0;
}

static int expr2(unsigned char **str, Value *ret)
{
    Value val;
    Value val2;
    unsigned char tok;

    expr3(str, &val);

    while ((tok = *(*str))) {
	if (tok != T_PLUS && tok != T_MINUS) {
	    break;
	}
	(*str)++;
	expr3(str, &val2);
	int type = getValType(&val, &val2);
	if (tok == T_PLUS) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt + val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat + val2.valFloat;
	    }
	} else {
	    if (type == VAL_INT) {
		val.valInt = val.valInt - val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat - val2.valFloat;
	    }
	}
    }

    ret->type = val.type;
    ret->valInt = val.valInt;
    ret->valFloat = val.valFloat;

    return 0;
}

static int expr3(unsigned char **str, Value *ret)
{
    Value val;
    Value val2;
    unsigned char tok;

    expr4(str, &val);

    while ((tok = *(*str))) {
	if (tok != T_MUL && tok != T_DIV) {
	    break;
	}
	(*str)++;
	expr4(str, &val2);
	int type = getValType(&val, &val2);
	if (tok == T_MUL) {
	    if (type == VAL_INT) {
		val.valInt = val.valInt * val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat * val2.valFloat;
	    }
	} else {
	    if (type == VAL_INT) {
		val.valInt = val.valInt / val2.valInt;
	    } else if (type == VAL_FLOAT) {
		val.valFloat = val.valFloat / val2.valFloat;
	    }
	}
    }

    ret->type = val.type;
    ret->valInt = val.valInt;
    ret->valFloat = val.valFloat;

    return 0;
}

static int expr4(unsigned char **str, Value *ret)
{
    Value val;
    if (*(*str) == T_MINUS) {
	(*str)++;
	expr5(str, &val);
	val.valInt = -val.valInt;
	val.valFloat = -val.valFloat;
    } else {
	expr5(str, &val);
    }

    ret->type = val.type;
    ret->valInt = val.valInt;
    ret->valFloat = val.valFloat;

    return 0;
}

static int expr5(unsigned char **str, Value *ret)
{
    Value val;

    if (*(*str) == T_LBRACKET) {
	(*str)++;
	expr1(str, &val);
	if (*(*str) != T_RBRACKET) {
	    fprintf(stderr, "Missed right bracket\n");
	    return 1;
	}
	(*str)++;
    } else {
	expr_data(str, &val);
    }

    ret->type = val.type;
    ret->valInt = val.valInt;
    ret->valFloat = val.valFloat;

    return 0;
}

static int f_print(unsigned char **str)
{
    while (*(*str) && *(*str) != T_COLON) {
	if (*(*str) == T_COMMA) {
	    PutChar(' ');
	    (*str)++;
	    continue;
	} else if (*(*str) == T_SEMICOLON) {
	    PutString("    ");
	    (*str)++;
	    continue;
	}
	if (*(*str) == 0xFF) {
	    int len = *++(*str);
	    while (len--) {
		(*str)++;
		PutChar(*(*str));
	    }
	    (*str)++;
	} else {
	    Value val;
	    expr(str, &val);
	    if (val.type == VAL_INT) {
		printf("%d", val.valInt);
	    } else {
		printf("%f", val.valFloat);
	    }
	}
    }
    printf("\n");
    return 0;
}

static int toExecute(unsigned char *str, int len)
{
    while (*str) {
	if (*str >= 0x80) {
	    if (*str == T_COLON) {
		str++;
		continue;
	    }
	    if (*str == T_PRINT) {
		str++;
		f_print(&str);
		continue;
	    }
	    // extract token
break;
	} else {
	    // extract variable name
	    int isString = 0;
	    char varName[16];
	    char *ptr = varName;
	    while (len > 0 && *str < 0x80) {
		*ptr++ = *str++;
		len--;
	    }
	    *ptr = 0;
#ifdef DEBUG
	    fprintf(stderr, "Variable %s[%02X/%02X]\n", varName, *str, T_DOLLAR);
#endif
	    if (*str == T_DOLLAR) {
		str++;
		isString = 1;
	    }

	    if (*str != T_EQU) {
		fprintf(stderr, "'=' expected\n");
		return 1;
	    }
	    str++;
	    len--;

	    Value val;
	    if (isString) {
		if (*str++ != 0xFF) {
		    fprintf(stderr, "String expected");
		    return 1;
		}
		val.type = VAL_STRING;
		val.length = *str++;
		
		//val.valStr = alloca(MAX_STRING_SIZE);
		val.valStr = malloc (MAX_STRING_SIZE);
				
		memcpy(val.valStr, str, val.length);
		str += val.length;
	    } else {
		expr(&str, &val);
#ifdef DEBUG
		if (val.type == VAL_INT) {
		    fprintf(stderr, "expression = %d\n", val.valInt);
		} else {
		    fprintf(stderr, "expression = %f\n", val.valFloat);
		}
#endif
	    }
fprintf(stderr, ">>> %d %d\n", val.type, val.length);
	    setVariable(varName, &val);
	}
    }
    return 0;
}

static int tokenizer(char *str)
{
    int toMemory = 0;
    unsigned short strNumber;
    char *ptr = str;
    char *ptre = ptr;
    unsigned char tokStr[80];
    unsigned char *tokPtr = tokStr;

    memset(tokStr, 0, sizeof(tokStr));

    while (isdigit(*ptre)) {
	strNumber = strNumber * 10 + *ptre - '0';
	ptre++;
    }

    if (ptre > ptr) {
	toMemory = 1;
	ptr = ptre;
    }

    while (*ptr) {
	while (*ptr == ' ' || *ptr == '\t') {
	    ptr++;
	}

	ptre = ptr;

	if (*ptre == '"') {
	    int skip = 0;
	    ptre++;
	    while (*ptre && (skip || *ptre != '"')) {
		skip = 0;
		if (*ptre == '\\') {
		    skip = 1;
		}
		ptre++;
	    }
	    if (!*ptre) {
		fprintf(stderr, "Opened double quote!\n");
		return 1;
	    }
	    fprintf(stderr, "string %d\n", ptre - ptr + 1);
	    ptre++;
	} else {
	    while (isalnum(*ptre)) {
		ptre++;
	    }

	    if (ptr == ptre && *ptr) {
		ptre++;
		if ((*ptr == '<' || *ptr == '>' || *ptr == '=') &&
		    (*ptre == '<' || *ptre == '>' || *ptre == '=')) {
		    ptre++;
		}
	    }
	}

	int tok;

	if ((tok = findToken(ptr, ptre - ptr)) > 0) {
	    fprintf(stderr, "found %d\n", tok);
	    *tokPtr++ = tok;
	} else {
	    if ((tokPtr - tokStr) + (ptre - ptr) > sizeof(tokStr)) {
		fprintf(stderr, "Line too long\n");
		return 1;
	    }
	    if (*ptr == '"') {
		tokPtr[0] = 0xff; 		//string
		tokPtr[1] = ptre - ptr - 2;	// without ""
		memcpy(tokPtr + 2, ptr + 1, ptre - ptr - 2);
	    } else {
		memcpy(tokPtr, ptr, ptre - ptr);
	    }
	    tokPtr += (ptre - ptr);
	}
	ptr = ptre;
    }

    // zero end of tokenized string
    tokPtr++;

    dumpData(tokStr, tokPtr - tokStr);

    deTokenized(tokStr, tokPtr - tokStr);

    toExecute(tokStr, tokPtr - tokStr);

    if (toMemory) {
	fprintf(stderr, "toMemory\n");
    } else {
	fprintf(stderr, "toExecute\n");
    }

    return 0;
}


// main
int main (int argc, char *argv[]){

    char str[80];

    int poolsz = 80;
    

    programEnd = memory;
    variables = memory + VAR_START;
    variablesEnd = variables;


    // ===========================
    
    printf ("bazic: Initializing ...\n");

    --argc; 
    ++argv;
    
    // -s
    if (argc > 0 && **argv == '-' && (*argv)[1] == 's') 
    { 
        //src = 1; 
        --argc; 
        ++argv; 
    }

    // -d
    if (argc > 0 && **argv == '-' && (*argv)[1] == 'd') 
    { 
        //debug = 1; 
        --argc; 
        ++argv; 
    }


    if (argc < 1) { 
        printf("usage: bazic [-s] [-d] file ...\n"); 
        return -1; 
    }

    
    
    
    /*
    if (gets(str)){
	tokenizer(str);
    }
    */


    //
    // Open!
    //
    int fd = -1;

    if ((fd = open(*argv, 0, 0)) < 0){ 
        printf("could not open(%s)\n", *argv); 
        return -1; 
    }

    //
    // Read!
    // 
    int i=0;   

    if ( (i = read(fd, str, poolsz-1)) <= 0 ){ 
        printf ("read() returned %d\n", i); 
        return -1; 
    }

    // Finalize.
    str[i] = 0;
    close (fd);

    tokenizer(str);
    
    return 0;
}





