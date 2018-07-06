
// ctype.h


/*gramado */
#define _C	0x01   /* Control */
#define	_U	0x02   /* Upper */
#define	_L	0x04   /* Lower */
#define	_D	0x08   /* dígito digit[0-9] */
#define _X	0x10   /* X digit */
#define _P	0x20   /* Punct */
#define	_S	0x40   /* Space  white space (space/lf/tab) */
#define	_B	0x80   /* Blank  hard space (0x20) */



//Apelidos para as letras.
#define _UPPER   _U  //letra maiúscula
#define _LOWER   _L  //letra minúscula.
#define _DIGIT   _D   //dígito digit[0-9]
#define _SPACE   _S  // \n \r \t
#define _PUNCT   _P  /* punctuation */
#define _CONTROL _C	 /* control character */
#define _HEX     _X  /* hexadecimal digit */
#define _BLANK   _B  /* space char */
//.





//in misc.c
extern char _ctype_[];


//partes: básico, intermediário e definitivo.

//
// # básico #
//

#define	__isalpha(c)   ((_ctype_+1)[c]&(_U|_L))
#define	__isupper(c)   ((_ctype_+1)[c]&_U)
#define	__islower(c)   ((_ctype_+1)[c]&_L)
#define	__isdigit(c)   ((_ctype_+1)[c]&_D)
#define	__isxdigit(c)  ((_ctype_+1)[c]&(_D|_X))
#define	__isspace(c)   ((_ctype_+1)[c]&_S)
#define __ispunct(c)   ((_ctype_+1)[c]&_P)
#define __isalnum(c)   ((_ctype_+1)[c]&(_U|_L|_D))
#define __isprint(c)   ((_ctype_+1)[c]&(_P|_U|_L|_D|_B))
#define __isgraph(c)   ((_ctype_+1)[c]&(_P|_U|_L|_D))
#define __iscntrl(c)   ((_ctype_+1)[c]&_C)
#define __isascii(c)   ((unsigned)(c)<=0177)
#define __toupper(c)   ((c)-'a'+'A')
#define __tolower(c)   ((c)-'A'+'a')
#define __toascii(c)   ((c)&0177)
 


//
// # intermediário #
//

//#define _isdigit(c) ((_ctype_+1)[c]&_D)
#define _isdigit(c) ((c) >= '0' && (c) <= '9') 
#define _isascii(c) (((unsigned) c)<=0x7f)
#define _toascii(c) (((unsigned) c)&0x7f)
//#define _isascii(c)	( (unsigned)(c) < 0x80 )
//#define _toascii(c)	((c) & 0x7f )
//#define _isascii(c)	(((c) & ~0x7f) == 0)	/* If C is a 7 bit value.  */
//#define _toascii(c)	((c) & 0x7f)		/* Mask off high bits.  */

//letter in ascci
//if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
 
//
// # definitivo #
//
 

//Sr.No.	Function & Description
//1	
//This function checks whether the passed character is alphanumeric.
int isalnum(int c);


//2	
//This function checks whether the passed character is alphabetic.
int isalpha(int c);


//3	
//This function checks whether the passed character is control character.
int iscntrl(int c);


//4	
//This function checks whether the passed character is decimal digit.
int isdigit(int c);


//5	
//This function checks whether the passed character has graphical representation using locale.
int isgraph(int c);


//6	
//This function checks whether the passed character is lowercase letter.
int islower(int c);

//7	
//This function checks whether the passed character is printable.
int isprint(int c);


//8	
//This function checks whether the passed character is a punctuation character.
int ispunct(int c);


//9	
//This function checks whether the passed character is white-space.
int isspace(int c);


//10	
//This function checks whether the passed character is an uppercase letter.
int isupper(int c);


//11	
//This function checks whether the passed character is a hexadecimal digit.
int isxdigit(int c);




//
// # Explicações #
//



//Sr.No.	Function & Description
//1	
//int tolower(int c);
//This function converts uppercase letters to lowercase.

//2	
//int toupper(int c)
//This function converts lowercase letters to uppercase.



//Character Classes
//Sr.No.	Character Class & Description
//1	
//Digits

//This is a set of whole numbers { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }.

//2	
//Hexadecimal digits

//This is the set of { 0 1 2 3 4 5 6 7 8 9 A B C D E F a b c d e f }.

//3	
//Lowercase letters

//This is a set of lowercase letters { a b c d e f g h i j k l m n o p q r s t u v w x y z }.

//4	
//Uppercase letters

//This is a set of uppercase letters {A B C D E F G H I J K L M N O P Q R S T U V W X Y Z }.

//5	
//Letters

//This is a set of lowercase and uppercase letters.

//6	
//Alphanumeric characters

//This is a set of Digits, Lowercase letters and Uppercase letters.

//7	
//Punctuation characters

//This is a set of ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _ ` { | } ~

//8	
//Graphical characters

//This is a set of Alphanumeric characters and Punctuation characters.

//9	
//Space characters

//This is a set of tab, newline, vertical tab, form feed, carriage return, and space.

//10	
//Printable characters

//This is a set of Alphanumeric characters, Punctuation characters and Space characters.

//11	
//Control characters

//In ASCII, these characters have octal codes 000 through 037, and 177 (DEL).

//12	
//Blank characters

//These are spaces and tabs.

//13	
//Alphabetic characters

//This is a set of Lowercase letters and Uppercase letters.



/*
' '     (0x20)	space (SPC)
'\t'	(0x09)	horizontal tab (TAB)
'\n'	(0x0a)	newline (LF)
'\v'	(0x0b)	vertical tab (VT)
'\f'	(0x0c)	feed (FF)
'\r'	(0x0d)	carriage return (CR)
*/




 








